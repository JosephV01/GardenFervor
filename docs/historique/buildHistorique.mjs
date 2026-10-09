/**
 * Build docs/historique.html from HISTORIQUE_MODIFICATIONS.md §4
 *
 * Usage (repo root):
 *   node docs/historique/buildHistorique.mjs
 *
 * Invoked by docs/syncPages.mjs
 *
 * Source of truth: HISTORIQUE_MODIFICATIONS.md — never invent dates or statuses.
 */
import fs from 'fs';
import path from 'path';
import { createHash } from 'crypto';
import { fileURLToPath } from 'url';

const __dirname = path.dirname(fileURLToPath(import.meta.url));
const repoRoot = path.resolve(__dirname, '../..');
const sourcePath = path.join(repoRoot, 'HISTORIQUE_MODIFICATIONS.md');
const outPath = path.join(repoRoot, 'docs', 'historique.html');

const CATEGORIES = [
  { id: 'contrats', label: 'Contrats et gouvernance', color: '#7bd7a8' },
  { id: 'conception', label: 'Conception et Design Gate', color: '#8ecdf8' },
  { id: 'technique', label: 'Architecture et technique', color: '#e5c28d' },
  { id: 'roadmap', label: 'Roadmap et jalons', color: '#c4a7e7' },
  { id: 'documentation', label: 'Documentation et procédures', color: '#9ec4b6' },
  { id: 'hub', label: 'Hub, outils et synchronisation', color: '#e89a9a' },
];

function categorize(entryId, title) {
  const id = String(entryId || '');
  const t = String(title || '');
  if (/^C-\d/i.test(id) || /CLOSE/i.test(id) && /^C-/i.test(id)) return 'contrats';
  if (/^DG-/i.test(id) || /^DESIGN-GATE/i.test(id)) return 'conception';
  if (/^ROADMAP-PAGES/i.test(id) || /^DG-HTML-SYNC/i.test(id) || /GitHub Pages/i.test(t)) return 'hub';
  if (/^ROADMAP-/i.test(id) || /^PLAN-PROD/i.test(id) || /^T\d/i.test(id)) return 'roadmap';
  if (/^ODC-/i.test(id) || /^F\d/i.test(id) || /^FIX-/i.test(id) || /^TERRAIN-/i.test(id) || /^RESET-/i.test(id) || /^AUDIT-/i.test(id) || /^T01-/i.test(id)) {
    return 'technique';
  }
  if (/^DOC-/i.test(id) || /^FORMALISATION-/i.test(id) || /REGLES|ETAT|HISTORIQUE|MAINT/i.test(id)) {
    return 'documentation';
  }
  if (/Pages|sync|Hub|HTML/i.test(t)) return 'hub';
  if (/Design Gate|DG-/i.test(t)) return 'conception';
  if (/contrat|VALIDÉ \(clôture/i.test(t)) return 'contrats';
  return 'documentation';
}

function stripMdLight(s) {
  return String(s ?? '')
    .replace(/\*\*([^*]+)\*\*/g, '$1')
    .replace(/`([^`]+)`/g, '$1')
    .trim();
}

function extractField(block, names) {
  for (const name of names) {
    const re = new RegExp(`^-\\s*\\*\\*${name}\\s*:\\*\\*\\s*(.+)$`, 'im');
    const m = block.match(re);
    if (m) return stripMdLight(m[1]);
  }
  return null;
}

function parseHistorique(md) {
  const marker = '## 4. Historique chronologique des modifications validées';
  const start = md.indexOf(marker);
  if (start < 0) {
    throw new Error('Section « ## 4. Historique chronologique… » introuvable dans HISTORIQUE_MODIFICATIONS.md');
  }
  let body = md.slice(start + marker.length);
  const nextH2 = body.search(/\n## [0-9]/);
  if (nextH2 >= 0) body = body.slice(0, nextH2);

  // Ignore fenced examples (ex. « ### YYYY-MM-DD — ID — Titre court »)
  body = body.replace(/```[\s\S]*?```/g, '');

  // Prefer « date — ID — titre » ; fallback « date — titre » (ex. F0)
  const headingRe = /^###\s+(.+)$/gm;
  const rawHeads = [...body.matchAll(headingRe)];
  const matches = [];
  for (const m of rawHeads) {
    const rest = m[1].trim();
    const parts = rest.split(/\s+—\s+/);
    if (parts.length >= 3) {
      matches.push({
        index: m.index,
        full: m[0],
        dateRaw: parts[0].trim(),
        entryId: parts[1].trim(),
        title: parts.slice(2).join(' — ').trim(),
      });
    } else if (parts.length === 2) {
      matches.push({
        index: m.index,
        full: m[0],
        dateRaw: parts[0].trim(),
        entryId: parts[1].trim().split(/\s+/)[0] || parts[1].trim(),
        title: parts[1].trim(),
      });
    }
  }
  if (!matches.length) {
    throw new Error('Aucune entrée ### date — ID — titre dans §4');
  }

  const entries = [];
  for (let i = 0; i < matches.length; i++) {
    const m = matches[i];
    const dateRaw = m.dateRaw;
    const entryId = m.entryId;
    const title = m.title;
    if (dateRaw === 'YYYY-MM-DD' || entryId === 'ID') continue;
    const from = m.index + m.full.length;
    const to = i + 1 < matches.length ? matches[i + 1].index : body.length;
    const block = body.slice(from, to);

    const dateOk = /^\d{4}-\d{2}-\d{2}$/.test(dateRaw);
    const intention = extractField(block, ['Intention']);
    const statut = extractField(block, ['Statut']);
    const fichiers =
      extractField(block, ['Fichiers', 'Changements \\(fichiers / systèmes\\)', 'Changements']) ||
      null;
    const suite = extractField(block, ['Suite', 'Suite ODC']);
    const decisions = extractField(block, ['Décisions']);
    const designGate = extractField(block, ['Design Gate']);

    const summary =
      intention ||
      decisions ||
      (statut ? statut.slice(0, 220) : null) ||
      'Résumé non structuré dans la source (voir HISTORIQUE_MODIFICATIONS.md).';

    entries.push({
      date: dateOk ? dateRaw : null,
      dateLabel: dateRaw,
      dateAvailable: dateOk,
      id: entryId,
      title,
      category: categorize(entryId, title),
      status: statut,
      summary,
      files: fichiers,
      suite,
      designGate,
      order: i,
    });
  }

  return entries;
}

function escapeHtml(s) {
  return String(s ?? '')
    .replace(/&/g, '&amp;')
    .replace(/</g, '&lt;')
    .replace(/>/g, '&gt;')
    .replace(/"/g, '&quot;');
}

if (!fs.existsSync(sourcePath)) {
  console.error('ERROR: missing', sourcePath);
  process.exit(1);
}

const md = fs.readFileSync(sourcePath, 'utf8');
const sourceHash = createHash('sha256').update(md).digest('hex');
const entries = parseHistorique(md);
const today = new Date().toISOString().slice(0, 10);

const payload = {
  builtAt: today,
  source: 'HISTORIQUE_MODIFICATIONS.md',
  sourceSection: '§4',
  sourceHash,
  categories: CATEGORIES,
  entryCount: entries.length,
  entries,
};

const json = JSON.stringify(payload);

const html = `<!DOCTYPE html>
<html lang="fr">
<head>
  <meta charset="utf-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1" />
  <meta name="description" content="GardenFervor — historique des modifications (miroir de HISTORIQUE_MODIFICATIONS.md)" />
  <title>GardenFervor — Historique des modifications</title>
  <script crossorigin src="https://unpkg.com/react@18.3.1/umd/react.production.min.js"></script>
  <script crossorigin src="https://unpkg.com/react-dom@18.3.1/umd/react-dom.production.min.js"></script>
  <style>
    :root{
      --bg:#0e1413;--panel:#141d1b;--line:#26332f;--muted:#8fa19b;--text:#e9efec;
      --accent:#7bd7a8;--amber:#e5c28d;--font:Inter,ui-sans-serif,system-ui,"Segoe UI",sans-serif;
    }
    *{box-sizing:border-box}
    body{margin:0;font-family:var(--font);color:var(--text);background:radial-gradient(circle at 80% -10%,rgba(83,150,117,.12),transparent 28%),var(--bg);line-height:1.5}
    a{color:var(--accent)}
    .wrap{max-width:920px;margin:0 auto;padding:28px 20px 72px}
    .top{display:flex;justify-content:space-between;gap:12px;flex-wrap:wrap;align-items:flex-start;margin-bottom:18px}
    .back{font-size:12px;font-weight:700;text-decoration:none;border:1px solid var(--line);padding:7px 10px;border-radius:8px;background:#18211f;color:#dce7e2}
    .eyebrow{font-size:10px;letter-spacing:.16em;font-weight:800;color:#71877f}
    h1{margin:6px 0 8px;font-size:clamp(1.55rem,3vw,2.15rem);letter-spacing:-.03em}
    .lead{margin:0;color:var(--muted);font-size:14px;max-width:640px}
    .meta{display:flex;flex-wrap:wrap;gap:8px;margin:14px 0 18px}
    .chip{font-size:11px;border:1px solid var(--line);background:#131b19;border-radius:999px;padding:5px 10px;color:#b7cbc2}
    .toolbar{display:flex;flex-wrap:wrap;gap:10px;align-items:center;margin:0 0 20px;padding:12px;border:1px solid var(--line);border-radius:12px;background:var(--panel)}
    .toolbar input[type="search"]{flex:1 1 180px;min-width:160px;background:#101816;border:1px solid var(--line);border-radius:8px;color:var(--text);padding:8px 10px;font:inherit;font-size:13px}
    .filters{display:flex;flex-wrap:wrap;gap:6px}
    .filters button{cursor:pointer;font:inherit;font-size:11px;font-weight:700;border:1px solid var(--line);background:#18211f;color:#c5d6cf;border-radius:999px;padding:6px 10px}
    .filters button[aria-pressed="true"]{border-color:#4d7a62;background:#1a2c24;color:#e8fff3}
    .filters button:focus{outline:2px solid var(--accent);outline-offset:2px}
    .empty{padding:28px 16px;border:1px dashed var(--line);border-radius:12px;color:var(--muted);text-align:center;font-size:14px}
    .day{margin:0 0 22px}
    .dayHead{position:sticky;top:0;z-index:2;display:flex;align-items:baseline;gap:10px;padding:8px 0;background:linear-gradient(180deg,rgba(14,20,19,.96),rgba(14,20,19,.88) 70%,transparent);backdrop-filter:blur(4px)}
    .dayHead time{font-size:13px;font-weight:800;letter-spacing:.04em;color:#dbe9e3}
    .dayHead span{font-size:11px;color:var(--muted)}
    .timeline{position:relative;margin:0;padding:0 0 0 18px;list-style:none}
    .timeline::before{content:"";position:absolute;left:5px;top:4px;bottom:4px;width:2px;background:linear-gradient(180deg,#3d6350,transparent)}
    .item{position:relative;margin:0 0 12px;padding:12px 14px 12px 16px;border:1px solid var(--line);border-radius:12px;background:#121a18}
    .item::before{content:"";position:absolute;left:-16px;top:18px;width:9px;height:9px;border-radius:50%;background:var(--dot,#7bd7a8);box-shadow:0 0 0 3px #0e1413}
    .itemHead{display:flex;flex-wrap:wrap;gap:8px;align-items:center;margin-bottom:6px}
    .cat{font-size:10px;font-weight:800;letter-spacing:.06em;text-transform:uppercase;color:#0e1413;background:var(--dot,#7bd7a8);border-radius:999px;padding:3px 8px}
    .eid{font-size:11px;font-weight:800;color:#8fb3a4}
    .stat{font-size:11px;color:var(--amber)}
    .item h2{margin:0 0 6px;font-size:1.05rem;letter-spacing:-.02em;font-weight:750}
    .item p{margin:0 0 6px;font-size:13px;color:#c5d6cf}
    .item .more{margin:0;font-size:12px;color:var(--muted)}
    .warn{color:#e5c28d;font-size:11px}
    footer{margin-top:28px;padding-top:14px;border-top:1px solid var(--line);color:#5f736a;font-size:11px;display:flex;justify-content:space-between;gap:10px;flex-wrap:wrap}
    @media(max-width:640px){
      .wrap{padding:20px 14px 56px}
      .item{padding:12px}
      .timeline{padding-left:14px}
      .item::before{left:-13px}
    }
  </style>
</head>
<body>
  <div id="root"></div>
  <script>
    const DATA = ${json};
  </script>
  <script>
    const { createElement: h, useMemo, useState } = React;

    const catMap = Object.fromEntries(DATA.categories.map((c) => [c.id, c]));

    function App() {
      const [cat, setCat] = useState('all');
      const [q, setQ] = useState('');

      const filtered = useMemo(() => {
        const query = q.trim().toLowerCase();
        return DATA.entries.filter((e) => {
          if (cat !== 'all' && e.category !== cat) return false;
          if (!query) return true;
          const blob = [e.id, e.title, e.summary, e.status, e.files, e.dateLabel]
            .filter(Boolean)
            .join(' ')
            .toLowerCase();
          return blob.includes(query);
        });
      }, [cat, q]);

      const byDay = useMemo(() => {
        const groups = [];
        let current = null;
        for (const e of filtered) {
          const key = e.dateAvailable ? e.date : 'unavailable:' + e.dateLabel;
          if (!current || current.key !== key) {
            current = {
              key,
              dateLabel: e.dateAvailable ? e.date : e.dateLabel,
              dateAvailable: e.dateAvailable,
              items: [],
            };
            groups.push(current);
          }
          current.items.push(e);
        }
        return groups;
      }, [filtered]);

      return h('div', { className: 'wrap' },
        h('div', { className: 'top' },
          h('div', null,
            h('div', { className: 'eyebrow' }, 'MÉMOIRE LONGUE · MIROIR'),
            h('h1', null, 'Historique des modifications'),
            h('p', { className: 'lead' },
              'Chronologie générée depuis HISTORIQUE_MODIFICATIONS.md (§4). Source canonique : Markdown racine — pas d’historique parallèle.')
          ),
          h('a', { className: 'back', href: 'index.html' }, '← Hub')
        ),
        h('div', { className: 'meta' },
          h('span', { className: 'chip' }, DATA.entryCount + ' entrées'),
          h('span', { className: 'chip' }, 'Build ' + DATA.builtAt),
          h('span', { className: 'chip' }, 'Hash ' + DATA.sourceHash.slice(0, 12))
        ),
        h('div', { className: 'toolbar' },
          h('input', {
            type: 'search',
            placeholder: 'Rechercher (id, titre, résumé…)',
            value: q,
            'aria-label': 'Recherche dans l’historique',
            onChange: (ev) => setQ(ev.target.value),
          }),
          h('div', { className: 'filters', role: 'group', 'aria-label': 'Filtrer par catégorie' },
            h('button', {
              type: 'button',
              'aria-pressed': cat === 'all' ? 'true' : 'false',
              onClick: () => setCat('all'),
            }, 'Tout'),
            ...DATA.categories.map((c) =>
              h('button', {
                key: c.id,
                type: 'button',
                'aria-pressed': cat === c.id ? 'true' : 'false',
                style: cat === c.id ? { borderColor: c.color } : undefined,
                onClick: () => setCat(c.id),
              }, c.label)
            )
          )
        ),
        filtered.length === 0
          ? h('div', { className: 'empty' }, 'Aucun événement ne correspond au filtre ou à la recherche.')
          : byDay.map((g) =>
              h('section', { className: 'day', key: g.key },
                h('div', { className: 'dayHead' },
                  h('time', null, g.dateLabel),
                  h('span', null, g.items.length + (g.items.length > 1 ? ' événements' : ' événement')),
                  !g.dateAvailable ? h('span', { className: 'warn' }, 'date partielle / non normalisée dans la source') : null
                ),
                h('ul', { className: 'timeline' },
                  g.items.map((e) => {
                    const c = catMap[e.category] || { label: e.category, color: '#7bd7a8' };
                    return h('li', {
                      key: e.order + '-' + e.id,
                      className: 'item',
                      style: { '--dot': c.color },
                    },
                      h('div', { className: 'itemHead' },
                        h('span', { className: 'cat' }, c.label),
                        h('span', { className: 'eid' }, e.id),
                        e.status ? h('span', { className: 'stat' }, e.status.length > 90 ? e.status.slice(0, 90) + '…' : e.status) : null
                      ),
                      h('h2', null, e.title),
                      h('p', null, e.summary),
                      e.files ? h('p', { className: 'more' }, 'Concerné : ' + e.files) : null,
                      e.suite ? h('p', { className: 'more' }, 'Suite : ' + e.suite) : null
                    );
                  })
                )
              )
            ),
        h('footer', null,
          h('span', null, 'Source : ' + DATA.source + ' · ' + DATA.sourceSection),
          h('span', null, 'Régénérer : node docs/historique/buildHistorique.mjs')
        )
      );
    }

    ReactDOM.createRoot(document.getElementById('root')).render(h(App));
  </script>
</body>
</html>
`;

fs.writeFileSync(outPath, html, 'utf8');

const catsUsed = [...new Set(entries.map((e) => e.category))];
const missingCats = CATEGORIES.filter((c) => !catsUsed.includes(c.id)).map((c) => c.id);

console.log(
  JSON.stringify(
    {
      ok: true,
      out: 'docs/historique.html',
      source: 'HISTORIQUE_MODIFICATIONS.md',
      entries: entries.length,
      categoriesUsed: catsUsed,
      categoriesEmpty: missingCats,
      sourceHash: sourceHash.slice(0, 12),
      builtAt: today,
      bytes: Buffer.byteLength(html, 'utf8'),
    },
    null,
    2
  )
);
