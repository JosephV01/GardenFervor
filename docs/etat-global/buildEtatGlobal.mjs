/**
 * Build docs/etat-global.html from etatGlobal.data.js + contractsSuivi.js
 *
 * Usage (repo root):
 *   node docs/etat-global/buildEtatGlobal.mjs
 *
 * Invoked by docs/syncPages.mjs
 */
import fs from 'fs';
import path from 'path';
import { fileURLToPath, pathToFileURL } from 'url';

const __dirname = path.dirname(fileURLToPath(import.meta.url));
const repoRoot = path.resolve(__dirname, '../..');
const outPath = path.join(repoRoot, 'docs', 'etat-global.html');

const dataMod = await import(pathToFileURL(path.join(__dirname, 'etatGlobal.data.js')).href + `?t=${Date.now()}`);
const suiviMod = await import(
  pathToFileURL(path.join(repoRoot, 'GardenFervor_DesignGate_React', 'src', 'data', 'contractsSuivi.js')).href +
    `?t=${Date.now()}`
);

const ETAT = dataMod.ETAT_GLOBAL;
const SUIVI = suiviMod.CONTRACTS_SUIVI;
const today = new Date().toISOString().slice(0, 10);

function displayStatus(c) {
  if (c.productionStatus === 'VALIDÉ' && c.dedicatedValidated !== false) return 'VALIDÉ';
  if (c.productionStatus === 'NON COMMENCÉ') {
    if (c.category === 'SUFFISANT') return 'SUFFISANT*';
    if (c.category === 'NON REQUIS') return 'NON REQUIS';
    return 'NON COMMENCÉ';
  }
  return c.productionStatus;
}

const contracts = SUIVI.displayOrder
  .map((id) => SUIVI.contracts.find((c) => c.id === id))
  .filter(Boolean)
  .map((c) => {
    const note = ETAT.contractsNotes[c.id] || {};
    return {
      id: c.id,
      name: c.name,
      status: displayStatus(c),
      category: c.category,
      inCounter: (SUIVI.progress.requiredIds || []).includes(c.id),
      blocking: !!c.blocking,
      dependsOn: c.dependsOn || [],
      providesTo: c.providesTo || [],
      file: c.file || null,
      officialNote: c.note || '',
      runtime: note.runtime || '—',
      debt: note.debt || '—',
    };
  });

const payload = {
  builtAt: today,
  live: {
    validated: SUIVI.progress.validated,
    required: SUIVI.progress.required,
    activeId: SUIVI.activeContractId,
    nextId: SUIVI.nextAuthorizedId,
    caseB: SUIVI.caseB,
  },
  editorial: ETAT,
  contracts,
};

const json = JSON.stringify(payload);
const html = `<!DOCTYPE html>
<html lang="fr">
<head>
  <meta charset="utf-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1" />
  <meta name="description" content="GardenFervor — état global du projet : systèmes, maturité, preuves, priorités" />
  <title>GardenFervor — État global du projet</title>
  <script crossorigin src="https://unpkg.com/react@18.3.1/umd/react.production.min.js"></script>
  <script crossorigin src="https://unpkg.com/react-dom@18.3.1/umd/react-dom.production.min.js"></script>
  <style>
    :root{
      --bg:#0e1413;--panel:#141d1b;--line:#26332f;--muted:#8fa19b;--text:#e9efec;
      --accent:#7bd7a8;--amber:#e5c28d;--blue:#8ecdf8;--danger:#e89a9a;
      --font:Inter,ui-sans-serif,system-ui,"Segoe UI",sans-serif;
    }
    *{box-sizing:border-box}
    body{margin:0;font-family:var(--font);color:var(--text);background:radial-gradient(circle at 80% -10%,rgba(83,150,117,.12),transparent 28%),var(--bg);line-height:1.5}
    a{color:var(--accent)}
    .shell{display:grid;grid-template-columns:220px 1fr;min-height:100vh}
    .nav{position:sticky;top:0;height:100vh;overflow:auto;border-right:1px solid var(--line);background:#101816;padding:18px 14px}
    .nav .eyebrow{font-size:10px;letter-spacing:.16em;font-weight:800;color:#71877f}
    .nav a{display:block;color:#b7cbc2;text-decoration:none;font-size:12px;padding:6px 8px;border-radius:8px;margin:2px 0}
    .nav a:hover,.nav a:focus{background:#1a2622;outline:none}
    .main{padding:28px 22px 72px;max-width:1080px}
    .top{display:flex;justify-content:space-between;gap:12px;flex-wrap:wrap;align-items:flex-start;margin-bottom:16px}
    .back{font-size:12px;font-weight:700;text-decoration:none;border:1px solid var(--line);padding:7px 10px;border-radius:8px;background:#18211f;color:#dce7e2}
    h1{margin:6px 0 8px;font-size:clamp(1.55rem,3vw,2.2rem);letter-spacing:-.03em}
    .lead{margin:0;color:var(--muted);font-size:14px;max-width:760px}
    .stats{display:grid;grid-template-columns:repeat(4,minmax(0,1fr));gap:10px;margin:16px 0}
    .stat{border:1px solid var(--line);background:var(--panel);border-radius:12px;padding:12px}
    .stat span{display:block;font-size:10px;text-transform:uppercase;letter-spacing:.1em;color:#6f857c;font-weight:800}
    .stat strong{display:block;margin-top:6px;font-size:18px;color:#dce7e2}
    .callout{border:1px solid var(--line);border-radius:12px;padding:12px 14px;margin:12px 0;background:#131b19}
    .callout.warn{border-color:#5a4229;background:#1c1812}
    .callout.ok{border-color:#3d6350;background:#15231e}
    .callout.bad{border-color:#5a3030;background:#1c1414}
    .callout h3{margin:0 0 6px;font-size:13px}
    .callout p{margin:0;font-size:13px;color:#b7cbc2}
    section{margin:28px 0}
    section>h2{margin:0 0 10px;font-size:13px;letter-spacing:.12em;text-transform:uppercase;color:#86a399;border-bottom:1px solid var(--line);padding-bottom:8px}
    .toolbar{display:flex;flex-wrap:wrap;gap:8px;margin:10px 0 14px;align-items:center}
    input[type=search],select{background:#101715;border:1px solid var(--line);color:var(--text);border-radius:8px;padding:8px 10px;font:inherit;font-size:13px}
    input[type=search]{min-width:220px;flex:1}
    .chip{display:inline-flex;align-items:center;padding:3px 9px;border-radius:999px;font-size:10px;font-weight:800;letter-spacing:.04em;border:1px solid transparent}
    .chip.ok{background:#145c38;border-color:#5dffb0;color:#e8fff3}
    .chip.warn{background:#5a4218;border-color:#ffc86a;color:#fff6e6}
    .chip.bad{background:#6a1f1f;border-color:#ff8f8f;color:#fff5f5}
    .chip.muted{background:#2a3834;border-color:#9ec4b6;color:#e8f5f0}
    .chip.blue{background:#1a3a6e;border-color:#8ec5ff;color:#f0f7ff}
    table{width:100%;border-collapse:collapse;font-size:12px}
    th,td{border-bottom:1px solid #1f2a27;padding:8px 8px;text-align:left;vertical-align:top}
    th{color:#7d9189;font-size:10px;text-transform:uppercase;letter-spacing:.08em}
    details.card{border:1px solid var(--line);background:#111816;border-radius:12px;margin:8px 0;padding:0}
    details.card>summary{cursor:pointer;list-style:none;padding:12px 14px;display:flex;gap:10px;align-items:flex-start;flex-wrap:wrap}
    details.card>summary::-webkit-details-marker{display:none}
    details.card[open]>summary{border-bottom:1px solid var(--line)}
    .body{padding:12px 14px 14px;font-size:13px;color:#b7cbc2}
    .body p{margin:0 0 8px}
    .grid2{display:grid;grid-template-columns:1fr 1fr;gap:10px}
    .panel{border:1px solid var(--line);background:var(--panel);border-radius:12px;padding:12px 14px}
    .panel h3{margin:0 0 6px;font-size:14px}
    .steps{display:flex;flex-wrap:wrap;gap:6px;margin-top:8px}
    .step{font-size:11px;padding:4px 8px;border-radius:8px;background:#18211f;border:1px solid #2a3834}
    .step.demontre{border-color:#3d6350;color:#9fe2bd}
    .step.partiel{border-color:#8a6828;color:#ffc86a}
    .step.concu{border-color:#3a5270;color:#8ecdf8}
    .step.absent{border-color:#6a1f1f;color:#ff8f8f}
    footer{margin-top:28px;color:#5f736a;font-size:11px;display:flex;justify-content:space-between;gap:10px;flex-wrap:wrap}
    .rec{font-size:12px;color:var(--amber)}
    @media(max-width:900px){.shell{grid-template-columns:1fr}.nav{position:relative;height:auto}.stats,.grid2{grid-template-columns:1fr}}
  </style>
</head>
<body>
  <div id="root"></div>
  <script id="payload" type="application/json">${json.replace(/</g, '\\u003c')}</script>
  <script>
  (function () {
    const h = React.createElement;
    const data = JSON.parse(document.getElementById('payload').textContent);
    const E = data.editorial;
    const live = data.live;

    const VERDICT_CLASS = {
      'Démontré': 'ok',
      'Démontré (sous InstantMode gates)': 'ok',
      'Partiellement opérationnel': 'warn',
      'Non disponible': 'bad',
      'À vérifier': 'blue',
      'Conçu seulement': 'blue',
    };
    const CODE_CLASS = {
      'Implémenté': 'ok',
      'Implémenté (S3)': 'ok',
      'Implémenté (Timber)': 'ok',
      'Partiel': 'warn',
      'Partiel (API off)': 'warn',
      'Absent / stubs': 'bad',
      'Absent (contrat)': 'bad',
    };

    function Chip({ children, kind }) {
      return h('span', { className: 'chip ' + (kind || 'muted') }, children);
    }

    function Callout({ title, children, kind }) {
      return h('div', { className: 'callout ' + (kind || '') },
        h('h3', null, title),
        h('p', null, children)
      );
    }

    function Nav() {
      const links = [
        ['#vue', 'Vue générale'],
        ['#maturite', 'Maturité'],
        ['#systemes', 'Systèmes'],
        ['#scenarios', 'Scénarios'],
        ['#contrats', 'Contrats'],
        ['#preuves', 'Preuves'],
        ['#travaux', 'Travaux restants'],
        ['#priorites', 'Priorités'],
        ['#feuille', 'Feuille de route'],
        ['#risques', 'Risques'],
        ['#refs', 'Références'],
      ];
      return h('aside', { className: 'nav', 'aria-label': 'Sommaire' },
        h('div', { className: 'eyebrow' }, 'GARDENFERVOR'),
        h('div', { style: { fontWeight: 800, margin: '8px 0 12px', fontSize: 14 } }, 'État global'),
        h('a', { className: 'back', href: 'index.html', style: { display: 'inline-block', marginBottom: 12 } }, '← Hub'),
        ...links.map(([href, label]) => h('a', { href, key: href }, label))
      );
    }

    function SystemsSection() {
      const [q, setQ] = React.useState('');
      const [domain, setDomain] = React.useState('Tous');
      const [code, setCode] = React.useState('Tous');
      const domains = ['Tous', ...Array.from(new Set(E.systems.map((s) => s.domain)))];
      const codes = ['Tous', ...Array.from(new Set(E.systems.map((s) => s.codeState)))];
      const filtered = E.systems.filter((s) => {
        const hay = [s.name, s.function, s.playerValue, s.limits, s.proof, ...(s.refs || [])].join(' ').toLowerCase();
        if (q && !hay.includes(q.toLowerCase())) return false;
        if (domain !== 'Tous' && s.domain !== domain) return false;
        if (code !== 'Tous' && s.codeState !== code) return false;
        return true;
      });
      return h('section', { id: 'systemes' },
        h('h2', null, 'C · Inventaire des systèmes'),
        h('p', { style: { color: 'var(--muted)', fontSize: 13, marginTop: 0 } },
          'Chaque fiche distingue conception, code réel, preuves et limites. Un contrat VALIDÉ n’implique pas une capacité complète.'),
        h('div', { className: 'toolbar' },
          h('input', { type: 'search', placeholder: 'Rechercher un système, fichier, preuve…', value: q, onChange: (e) => setQ(e.target.value), 'aria-label': 'Recherche systèmes' }),
          h('select', { value: domain, onChange: (e) => setDomain(e.target.value), 'aria-label': 'Filtrer domaine' },
            domains.map((d) => h('option', { key: d, value: d }, d))),
          h('select', { value: code, onChange: (e) => setCode(e.target.value), 'aria-label': 'Filtrer état code' },
            codes.map((d) => h('option', { key: d, value: d }, d))),
          h(Chip, { kind: 'muted' }, filtered.length + ' / ' + E.systems.length)
        ),
        filtered.map((s) =>
          h('details', { className: 'card', key: s.id },
            h('summary', null,
              h('strong', { style: { minWidth: 180 } }, s.name),
              h(Chip, { kind: 'muted' }, s.domain),
              h(Chip, { kind: CODE_CLASS[s.codeState] || 'warn' }, s.codeState),
              h(Chip, { kind: 'blue' }, s.docState)
            ),
            h('div', { className: 'body' },
              h('p', null, h('strong', null, 'Fonction : '), s.function),
              h('p', null, h('strong', null, 'Pour le joueur : '), s.playerValue),
              h('p', null, h('strong', null, 'Preuve : '), s.proof),
              h('p', null, h('strong', null, 'Limites : '), s.limits),
              h('p', null, h('strong', null, 'Dépendances : '), s.depends),
              h('p', null, h('strong', null, 'Suite justifiée : '), s.next),
              h('p', null, h('strong', null, 'Références : '), (s.refs || []).join(' · '))
            )
          )
        )
      );
    }

    function App() {
      return h('div', { className: 'shell' },
        h(Nav),
        h('main', { className: 'main' },
          h('div', { className: 'top' },
            h('div', null,
              h('div', { className: 'eyebrow', style: { fontSize: 10, letterSpacing: '.16em', fontWeight: 800, color: '#71877f' } }, 'DOCUMENTATION'),
              h('h1', null, E.meta.title),
              h('p', { className: 'lead' }, E.meta.subtitle + ' — ' + E.identity.maturityOneLiner)
            ),
            h('a', { className: 'back', href: 'index.html' }, '← Hub documentation')
          ),

          h('div', { className: 'stats', 'aria-label': 'Compteurs synchronisés' },
            h('div', { className: 'stat' }, h('span', null, 'Contrats'), h('strong', null, live.validated + ' / ' + live.required)),
            h('div', { className: 'stat' }, h('span', null, 'Dernier VALIDÉ'), h('strong', null, live.activeId)),
            h('div', { className: 'stat' }, h('span', null, 'Prochain officiel'), h('strong', null, live.nextId)),
            h('div', { className: 'stat' }, h('span', null, 'Case B'), h('strong', null, live.caseB.status))
          ),
          h('p', { style: { fontSize: 12, color: 'var(--muted)', marginTop: -6 } },
            'Compteurs issus de contractsSuivi.js (miroir du suivi officiel) · sync build ' + data.builtAt +
            ' · audit de référence git ' + E.meta.gitHeadAtAudit),

          h('section', { id: 'vue' },
            h('h2', null, 'A · Vue générale'),
            h(Callout, { title: 'Ce n’est pas encore un RTS jouable complet', kind: 'warn' },
              E.identity.what + ' ' + E.identity.notWhat),
            h('div', { className: 'grid2' },
              h('div', { className: 'panel' },
                h('h3', null, 'Rôle du joueur'),
                h('p', null, E.identity.playerRole)
              ),
              h('div', { className: 'panel' },
                h('h3', null, 'Rôle des unités'),
                h('p', null, E.identity.unitsRole)
              )
            ),
            h('div', { className: 'grid2', style: { marginTop: 10 } },
              h('div', { className: 'panel' },
                h('h3', null, 'Acquis'),
                h('ul', null, E.identity.acquis.map((x, i) => h('li', { key: i }, x)))
              ),
              h('div', { className: 'panel' },
                h('h3', null, 'Obstacles à une boucle complète'),
                h('ul', null, E.identity.obstacles.map((x, i) => h('li', { key: i }, x)))
              )
            ),
            h('table', { style: { marginTop: 14 } },
              h('thead', null, h('tr', null, h('th', null, 'Question'), h('th', null, 'Réponse'))),
              h('tbody', null, E.executiveQa.map((row, i) =>
                h('tr', { key: i },
                  h('td', null, row.q),
                  h('td', null, row.a, row.recommendation ? h('div', { className: 'rec' }, 'Recommandation (non officielle)') : null)
                )
              ))
            )
          ),

          h('section', { id: 'maturite' },
            h('h2', null, 'B · État de maturité'),
            h('p', { style: { color: 'var(--muted)', fontSize: 13 } },
              'Chaque couche répond à une question différente. Conception VALIDÉE ≠ produit shipping.'),
            h('div', { className: 'grid2' },
              E.maturityLayers.map((m) =>
                h('div', { className: 'panel', key: m.id },
                  h('h3', null, m.label, ' ', h(Chip, { kind: m.state.startsWith('VALID') ? 'ok' : m.state === 'NON' ? 'bad' : 'warn' }, m.state)),
                  h('p', null, m.meaning),
                  h('p', { style: { fontSize: 11, color: '#7d9189' } }, m.evidence)
                )
              )
            ),
            h(Callout, { title: 'Légende des états', kind: '' },
              E.legend.map((l) => l.label + ' — ' + l.meaning).join(' · '))
          ),

          h(SystemsSection),

          h('section', { id: 'scenarios' },
            h('h2', null, 'D · Scénarios de gameplay'),
            E.scenarios.map((sc) =>
              h('details', { className: 'card', key: sc.id, open: sc.id === 'D' || sc.id === 'E' },
                h('summary', null,
                  h('strong', null, sc.id + ' — ' + sc.title),
                  h(Chip, { kind: VERDICT_CLASS[sc.verdict] || 'warn' }, sc.verdict)
                ),
                h('div', { className: 'body' },
                  h('p', null, h('strong', null, 'Ce qui marche : '), sc.works),
                  h('p', null, h('strong', null, 'Ce qui manque : '), sc.missing),
                  h('div', { className: 'steps' },
                    sc.steps.map((st, i) => h('span', { className: 'step ' + st.state, key: i }, st.label + ' · ' + st.state))
                  )
                )
              )
            )
          ),

          h('section', { id: 'contrats' },
            h('h2', null, 'E · Contrats et décisions'),
            h('p', { style: { color: 'var(--muted)', fontSize: 13 } },
              'Statuts officiels synchronisés depuis contractsSuivi.js. Notes runtime = éditorial (etatGlobal.data.js).'),
            h('div', { className: 'toolbar' },
              h(Chip, { kind: 'ok' }, live.validated + ' VALIDÉS'),
              h(Chip, { kind: 'muted' }, 'Addenda* hors compteur'),
              h(Chip, { kind: 'warn' }, 'Case B ' + live.caseB.status),
              h(Chip, { kind: 'blue' }, 'Prochain ' + live.nextId)
            ),
            h('table', null,
              h('thead', null, h('tr', null,
                h('th', null, 'ID'), h('th', null, 'Intitulé'), h('th', null, 'Statut'),
                h('th', null, 'Compteur'), h('th', null, 'Runtime'), h('th', null, 'Dette / blocage')
              )),
              h('tbody', null, data.contracts.map((c) =>
                h('tr', { key: c.id },
                  h('td', null, c.id),
                  h('td', null, c.name),
                  h('td', null, h(Chip, { kind: c.status.startsWith('VALID') ? 'ok' : c.status.includes('SUFF') ? 'muted' : c.status === 'NON REQUIS' ? 'muted' : 'warn' }, c.status)),
                  h('td', null, c.inCounter ? 'Oui' : 'Non*'),
                  h('td', null, c.runtime),
                  h('td', null, c.debt)
                )
              ))
            ),
            h('p', { style: { fontSize: 12, color: 'var(--muted)' } }, live.caseB.note)
          ),

          h('section', { id: 'preuves' },
            h('h2', null, 'F · Gates et preuves techniques'),
            E.gates.map((g) =>
              h('details', { className: 'card', key: g.id },
                h('summary', null,
                  h('strong', null, g.id + ' — ' + g.title),
                  h(Chip, { kind: String(g.result).includes('INVALID') ? 'bad' : String(g.result).includes('PASS') || String(g.result).includes('VALID') ? 'ok' : 'warn' }, g.result)
                ),
                h('div', { className: 'body' },
                  h('p', null, h('strong', null, 'Date / env. : '), g.date + ' · ' + g.env),
                  h('p', null, h('strong', null, 'Testé : '), g.tested),
                  h('p', null, h('strong', null, 'Permet de conclure : '), g.shows),
                  h('p', null, h('strong', null, 'Ne permet pas : '), g.doesNotShow),
                  h('p', null, h('strong', null, 'Fichier : '), g.file)
                )
              )
            )
          ),

          h('section', { id: 'travaux' },
            h('h2', null, 'G · Travaux restants'),
            h('table', null,
              h('thead', null, h('tr', null,
                h('th', null, 'Domaine'), h('th', null, 'Problème'), h('th', null, 'Bénéfice'),
                h('th', null, 'Prérequis'), h('th', null, 'Succès'), h('th', null, 'Source'), h('th', null, 'Bloquant')
              )),
              h('tbody', null, E.remainingWork.map((w, i) =>
                h('tr', { key: i },
                  h('td', null, w.domain),
                  h('td', null, w.problem),
                  h('td', null, w.benefit),
                  h('td', null, w.prereq),
                  h('td', null, w.success),
                  h('td', null, w.source === 'roadmap' ? 'Roadmap' : 'Éditorial'),
                  h('td', null, w.blocking ? 'Oui' : 'Non')
                )
              ))
            )
          ),

          h('section', { id: 'priorites' },
            h('h2', null, 'H · Priorités P0–P4'),
            Object.entries(E.priorities).map(([key, block]) =>
              h('div', { key, style: { marginBottom: 14 } },
                h('h3', { style: { fontSize: 14, margin: '0 0 8px' } }, key + ' — ' + block.title),
                h('table', null,
                  h('thead', null, h('tr', null,
                    h('th', null, 'Travail'), h('th', null, 'Pourquoi'), h('th', null, 'Débloque'),
                    h('th', null, 'Coût du report'), h('th', null, 'Preuve')
                  )),
                  h('tbody', null, block.items.map((it, i) =>
                    h('tr', { key: i },
                      h('td', null, it.work, it.type ? h('div', { className: 'rec' }, it.type) : null),
                      h('td', null, it.why),
                      h('td', null, it.unlocks),
                      h('td', null, it.costOfDelay),
                      h('td', null, it.proof)
                    )
                  ))
                )
              )
            ),
            h(Callout, { title: 'Roadmap officielle vs recommandation', kind: 'warn' },
              E.roadmapCompare.officialNext + ' ' + E.roadmapCompare.alternative)
          ),

          h('section', { id: 'feuille' },
            h('h2', null, 'I · Feuille de route'),
            h('table', null,
              h('thead', null, h('tr', null,
                h('th', null, 'Jalon'), h('th', null, 'Objectif'), h('th', null, 'Prérequis'),
                h('th', null, 'Validation'), h('th', null, 'Ne pas commencer avant')
              )),
              h('tbody', null, E.milestones.map((m) =>
                h('tr', { key: m.id },
                  h('td', null, m.id + ' ' + m.title),
                  h('td', null, m.objective),
                  h('td', null, m.prereq),
                  h('td', null, m.validation),
                  h('td', null, m.doNotStart)
                )
              ))
            ),
            h(Callout, { title: 'Garde-fou', kind: 'ok' },
              'Cette page n’ouvre pas le prochain contrat, ne modifie aucun statut et ne démarre aucun gameplay. Prochain officiel affiché : ' + live.nextId + '.')
          ),

          h('section', { id: 'risques' },
            h('h2', null, 'J · Risques, dettes et garde-fous'),
            h('table', null,
              h('thead', null, h('tr', null, h('th', null, 'Risque'), h('th', null, 'Impact'), h('th', null, 'Mitigation'))),
              h('tbody', null, E.risks.map((r, i) =>
                h('tr', { key: i }, h('td', null, r.risk), h('td', null, r.impact), h('td', null, r.mitigation))
              ))
            ),
            h(Callout, { title: 'Acquis', kind: 'ok' }, E.conclusion.acquired),
            h(Callout, { title: 'Manque pour un jeu jouable (produit)', kind: 'bad' }, E.conclusion.missing),
            h(Callout, { title: 'Décision à prendre (recommandation)', kind: 'warn' }, E.conclusion.decision)
          ),

          h('section', { id: 'refs' },
            h('h2', null, 'K · Références et maintenance'),
            h('p', { style: { fontSize: 13, color: 'var(--muted)' } }, E.meta.originNote),
            h('p', { style: { fontSize: 13 } },
              h('strong', null, 'Vérifié le '), E.meta.verifiedAt,
              ' · git audit ', E.meta.gitHeadAtAudit, ' — ', E.meta.gitMessageAtAudit),
            h('ul', null, E.meta.sources.map((s, i) => h('li', { key: i }, s))),
            h('p', { style: { fontSize: 13 } },
              'Mise à jour : éditer ', h('code', null, 'docs/etat-global/etatGlobal.data.js'),
              ' et/ou le suivi des contrats, puis ', h('code', null, 'node docs/syncPages.mjs'),
              '. Voir ', h('code', null, 'docs/etat-global/README.md'), '.')
          ),

          h('footer', null,
            h('span', null, 'https://josephv01.github.io/GardenFervor/etat-global.html'),
            h('span', null, 'Source éditoriale versionnée · compteurs live depuis contractsSuivi.js')
          )
        )
      );
    }

    ReactDOM.createRoot(document.getElementById('root')).render(h(App));
  })();
  </script>
</body>
</html>
`;

fs.writeFileSync(outPath, html, 'utf8');
const live = payload.live;
console.log(
  JSON.stringify(
    {
      ok: true,
      out: 'docs/etat-global.html',
      contracts: `${live.validated}/${live.required}`,
      active: live.activeId,
      next: live.nextId,
      caseB: live.caseB.status,
      builtAt: today,
      bytes: html.length,
    },
    null,
    2
  )
);
