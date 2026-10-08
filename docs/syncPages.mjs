/**
 * Synchronise toutes les pages GitHub Pages sous docs/.
 *
 * Usage (depuis la racine du dépôt) :
 *   node docs/syncPages.mjs
 *
 * - Roadmap  → docs/roadmap.html
 * - Design Gate → docs/design-gate.html
 * - Contrats → docs/contracts.html (depuis contractsSuivi.js)
 * - Hub      → docs/index.html (bandeau d’état + liens)
 * - Présentation Investor Demo → docs/presentation-client.html
 * - Project Graph → docs/project-graph.html (depuis PROJECT_GRAPH/)
 *
 * Sources de vérité : Markdown CONTRATS/, roadmap.data.js, designGate.js,
 * Investor Demo/PrésentationClientHtml/PrésentationClient.html,
 * PROJECT_GRAPH/GardenFervor_ProjectGraph.html.
 * Ne pas inventer de VALIDÉ.
 */
import fs from 'fs';
import path from 'path';
import { fileURLToPath, pathToFileURL } from 'url';
import { spawnSync } from 'child_process';

const __dirname = path.dirname(fileURLToPath(import.meta.url));
const repoRoot = path.resolve(__dirname, '..');
const docsDir = __dirname;

function runNode(scriptRel) {
  const script = path.join(repoRoot, scriptRel);
  const r = spawnSync(process.execPath, [script], { cwd: repoRoot, encoding: 'utf8' });
  if (r.stdout) process.stdout.write(r.stdout);
  if (r.stderr) process.stderr.write(r.stderr);
  if (r.status !== 0) {
    console.error('FAILED:', scriptRel);
    process.exit(r.status ?? 1);
  }
}

console.log('— Sync roadmap —');
runNode(path.join('Plan de production', 'Roadmap', 'scripts', 'syncRoadmap.mjs'));

console.log('— Sync Design Gate —');
runNode(path.join('GardenFervor_DesignGate_React', 'scripts', 'syncStandaloneFromJs.mjs'));

console.log('— Sync contrats + hub —');
const suiviMod = await import(
  pathToFileURL(
    path.join(repoRoot, 'GardenFervor_DesignGate_React', 'src', 'data', 'contractsSuivi.js')
  ).href + `?t=${Date.now()}`
);
const roadmapMod = await import(
  pathToFileURL(
    path.join(repoRoot, 'Plan de production', 'Roadmap', 'src', 'roadmap.data.js')
  ).href + `?t=${Date.now()}`
);

const SUIVI = suiviMod.CONTRACTS_SUIVI;
const roadmapPayload = roadmapMod.serializeRoadmap();
const active = SUIVI.contracts.find((c) => c.id === SUIVI.activeContractId);
const today = new Date().toISOString().slice(0, 10);

const ordered = SUIVI.displayOrder
  .map((id) => SUIVI.contracts.find((c) => c.id === id))
  .filter(Boolean);

function displayStatus(c) {
  if (c.productionStatus === 'VALIDÉ' && c.dedicatedValidated !== false) return 'VALIDÉ';
  if (c.productionStatus === 'NON COMMENCÉ') {
    if (c.category === 'SUFFISANT') return 'SUFFISANT';
    if (c.category === 'NON REQUIS') return 'NON REQUIS';
    return 'À FAIRE';
  }
  return c.productionStatus;
}

const contractsJson = {
  activeId: SUIVI.activeContractId,
  order: SUIVI.displayOrder,
  progress: SUIVI.progress,
  lastSync: today,
  caseB: SUIVI.caseB,
  contracts: ordered.map((c) => {
    const out = {
      id: c.id,
      order: c.order == null ? '—' : String(c.order),
      name: c.name,
      status: displayStatus(c),
      category: c.category,
      coverage: c.coverage,
      blocking: !!c.blocking,
      note: c.note || '',
      dependsOn: c.dependsOn || [],
      providesTo: c.providesTo || [],
    };
    if (c.file) out.file = c.file;
    if (c.detail) {
      out.detail = {
        decisions: `${c.detail.decisionsTaken} / ${c.detail.decisionsTotal}`,
        frontiers: (c.detail.frontiers || []).map((f) => `${f.id} — ${f.label}`),
        gaps: c.detail.gaps || [],
      };
    }
    return out;
  }),
};

const contractsHtml = buildContractsHtml(contractsJson);
fs.writeFileSync(path.join(docsDir, 'contracts.html'), contractsHtml, 'utf8');

const hubPath = path.join(docsDir, 'index.html');
let hub = fs.readFileSync(hubPath, 'utf8');
const statusBlock = buildHubStatus({
  today,
  roadmap: roadmapPayload,
  suivi: SUIVI,
  active,
});
const start = '<!-- SYNC:STATUS:START -->';
const end = '<!-- SYNC:STATUS:END -->';
if (!hub.includes(start) || !hub.includes(end)) {
  console.error('ERROR: hub markers SYNC:STATUS missing in docs/index.html');
  process.exit(1);
}
hub =
  hub.slice(0, hub.indexOf(start) + start.length) +
  '\n' +
  statusBlock +
  '\n    ' +
  hub.slice(hub.indexOf(end));

// Keep contracts card blurb current
hub = hub.replace(
  /(<a class="card" href="contracts\.html">[\s\S]*?<p>)([\s\S]*?)(<\/p>)/,
  `$1Pilotage documentaire C-01→C-21 · ${SUIVI.progress.validated}/${SUIVI.progress.required} validés · actif ${SUIVI.activeContractId} (${active ? displayStatus(active) : '—'}).$3`
);
hub = hub.replace(
  /(<a class="card" href="roadmap\.html">[\s\S]*?<p>)([\s\S]*?)(<\/p>)/,
  `$1${roadmapPayload.meta.globalState} · progression ${roadmapPayload.progress.done}/${roadmapPayload.progress.total} (${roadmapPayload.progress.percent}%).$3`
);

fs.writeFileSync(hubPath, hub, 'utf8');

console.log('— Sync présentation Investor Demo —');
const presentationSrc = path.join(
  repoRoot,
  'Investor Demo',
  'PrésentationClientHtml',
  'PrésentationClient.html'
);
const presentationDst = path.join(docsDir, 'presentation-client.html');
if (!fs.existsSync(presentationSrc)) {
  console.error('ERROR: missing presentation source:', presentationSrc);
  process.exit(1);
}
fs.copyFileSync(presentationSrc, presentationDst);
console.log('Copied → docs/presentation-client.html');

const presentationImagesSrc = path.join(
  repoRoot,
  'Investor Demo',
  'PrésentationClientHtml',
  'images'
);
const presentationImagesDst = path.join(docsDir, 'images');
if (fs.existsSync(presentationImagesSrc)) {
  fs.cpSync(presentationImagesSrc, presentationImagesDst, { recursive: true });
  console.log('Copied → docs/images/ (incl. lot1 gallery)');
}

console.log('— Sync Project Graph —');
const projectGraphSrc = path.join(
  repoRoot,
  'PROJECT_GRAPH',
  'GardenFervor_ProjectGraph.html'
);
const projectGraphDst = path.join(docsDir, 'project-graph.html');
if (!fs.existsSync(projectGraphSrc)) {
  console.error('ERROR: missing Project Graph source:', projectGraphSrc);
  process.exit(1);
}
fs.copyFileSync(projectGraphSrc, projectGraphDst);
console.log('Copied → docs/project-graph.html');

console.log(
  JSON.stringify(
    {
      ok: true,
      hub: 'docs/index.html',
      roadmap: `${roadmapPayload.progress.done}/${roadmapPayload.progress.total}`,
      contracts: `${SUIVI.progress.validated}/${SUIVI.progress.required}`,
      active: SUIVI.activeContractId,
      activeStatus: active ? displayStatus(active) : null,
      presentation: 'docs/presentation-client.html',
      presentationImages: 'docs/images/',
      projectGraph: 'docs/project-graph.html',
      syncedAt: today,
    },
    null,
    2
  )
);

function buildHubStatus({ today, roadmap, suivi, active }) {
  const aStatus = active ? displayStatus(active) : '—';
  return `    <section class="statusStrip" aria-label="État projet synchronisé">
      <div class="statusCard">
        <span>Roadmap</span>
        <strong>${escapeHtml(roadmap.meta.globalState)}</strong>
        <em>${roadmap.progress.done}/${roadmap.progress.total} VALIDÉ (${roadmap.progress.percent}%)</em>
      </div>
      <div class="statusCard accent">
        <span>Contrats</span>
        <strong>${suivi.activeContractId} · ${escapeHtml(aStatus)} · ${suivi.progress.validated}/${suivi.progress.required}</strong>
        <em>Prochain autorisé : ${escapeHtml(suivi.nextAuthorizedId || '—')} (non commencé) · ${escapeHtml(active?.note || '')}</em>
      </div>
      <div class="statusCard">
        <span>Case B</span>
        <strong>${escapeHtml(suivi.caseB.status)}</strong>
        <em>${escapeHtml(suivi.caseB.note)}</em>
      </div>
      <div class="statusCard">
        <span>Sync Pages</span>
        <strong>${today}</strong>
        <em>node docs/syncPages.mjs</em>
      </div>
    </section>`;
}

function escapeHtml(s) {
  return String(s ?? '')
    .replace(/&/g, '&amp;')
    .replace(/</g, '&lt;')
    .replace(/>/g, '&gt;')
    .replace(/"/g, '&quot;');
}

function buildContractsHtml(data) {
  const json = JSON.stringify(data, null, 2);
  return `<!DOCTYPE html>
<html lang="fr">
<head>
  <meta charset="utf-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1" />
  <title>GardenFervor — Suivi des contrats</title>
  <style>
    :root{font-family:Inter,ui-sans-serif,system-ui,"Segoe UI",sans-serif;color:#e9efec;background:#0e1413;line-height:1.5;--bg:#0e1413;--line:#26332f;--muted:#8fa19b;--text:#e9efec;--accent:#7bd7a8;--amber:#e5c28d}
    *{box-sizing:border-box}body{margin:0;background:radial-gradient(circle at 80% -10%,rgba(83,150,117,.12),transparent 26%),var(--bg);color:var(--text)}
    a{color:var(--accent)}.wrap{max-width:1100px;margin:0 auto;padding:28px 20px 64px}
    .top{display:flex;justify-content:space-between;gap:12px;align-items:center;margin-bottom:18px;flex-wrap:wrap}
    .back{font-size:12px;font-weight:700;text-decoration:none;border:1px solid var(--line);padding:7px 10px;border-radius:8px;background:#18211f;color:#dce7e2}
    .eyebrow{font-size:10px;letter-spacing:.16em;font-weight:800;color:#71877f}
    h1{margin:6px 0 8px;font-size:clamp(1.6rem,3vw,2.2rem);letter-spacing:-.03em}
    .lead{margin:0;color:var(--muted);font-size:14px;max-width:720px}
    .rule{margin:16px 0;border-left:2px solid var(--accent);padding:8px 0 8px 12px;color:#bac9c3;font-size:13px}
    .hero{display:grid;grid-template-columns:1.4fr .8fr;gap:14px;margin:18px 0}
    .panel{border:1px solid var(--line);background:#131b19;border-radius:12px;padding:16px}
    .progressLabel{display:flex;justify-content:space-between;font-size:12px;color:#81938d}
    .progressLabel strong{font-size:22px;color:#dbe9e3}
    .bar{height:9px;background:#1a2421;border-radius:99px;overflow:hidden;margin:12px 0 8px}
    .fill{height:100%;background:linear-gradient(90deg,#5bb98e,#9fe2bd)}
    .meta{font-size:11px;color:#70837c}
    .active{border-color:#3d6350;background:linear-gradient(135deg,#172822,#121c19)}
    .active h2{margin:4px 0 6px;font-size:1.15rem}
    .badges{display:flex;flex-wrap:wrap;gap:5px;margin:8px 0}
    .badge{display:inline-flex;padding:3px 8px;border-radius:99px;border:1px solid transparent;font-size:9px;font-weight:800}
    .revue{background:#1a2438;border-color:#3a5278;color:#9ec4f5}
    .nonval{background:#3a1f1f;border-color:#7a3d3d;color:#f0b4b4}
    .todo{background:#2b2718;border-color:#4b4330;color:#e6d7a6}
    .suff{background:#1a2220;border-color:#33403c;color:#9aada5}
    .block{background:#2b2020;border-color:#4d3636;color:#e6a9a9}
    .partiel{background:#2a2418;border-color:#53462e;color:#e2c994}
    .grid{display:grid;grid-template-columns:1.1fr .9fr;gap:12px;margin-top:14px}
    .list{display:flex;flex-direction:column;gap:6px}
    .row{border:1px solid #202b28;background:#111816;border-radius:10px;padding:10px 12px;width:100%;text-align:left;color:inherit;font:inherit;cursor:pointer}
    .row.active{border-color:#4d7a62;background:#15231e}
    .rowTop{display:flex;gap:8px;align-items:center;font-size:12px}
    .id{font-weight:900;color:#8fb3a4;min-width:40px}
    .name{color:#d5e2dc;font-weight:650}
    .detail h3{margin:0 0 4px;font-size:1.4rem}
    .detail .fname{margin:0 0 10px;color:var(--muted);font-size:13px}
    .dec{font-size:28px;font-weight:850;margin:4px 0 12px}
    .blockTitle{font-size:10px;text-transform:uppercase;letter-spacing:.1em;font-weight:850;color:#7d9189;margin:14px 0 6px}
    ul{margin:0;padding-left:18px;color:#a7bbb3;font-size:12px}
    li{margin:4px 0}
    .gaps{background:#1a1712;border:1px solid #3a3224;border-radius:8px;padding:10px 12px}
    .gapNote{margin:0 0 6px;font-size:11px;color:var(--amber)}
    footer{margin-top:24px;color:#5f736a;font-size:11px;display:flex;justify-content:space-between;gap:10px;flex-wrap:wrap}
    @media(max-width:900px){.hero,.grid{grid-template-columns:1fr}}
  </style>
</head>
<body>
  <div class="wrap">
    <div class="top">
      <div>
        <div class="eyebrow">GARDENFERVOR</div>
        <h1>Suivi des contrats</h1>
        <p class="lead">Contracts / Operational Architecture — vue publiée synchronisée.</p>
      </div>
      <a class="back" href="index.html">← Hub documentation</a>
    </div>
    <div class="rule"><strong>Règle :</strong> Décidé → Rédigé → En revue → Validé. Un fichier rédigé n’est pas VALIDÉ.</div>
    <div class="hero" id="hero"></div>
    <div class="grid">
      <section class="list" id="list"></section>
      <aside class="panel detail" id="detail"></aside>
    </div>
    <footer>
      <span>Source : CONTRATS/*.md · miroir contractsSuivi.js</span>
      <span>Sync : node docs/syncPages.mjs · ${data.lastSync}</span>
    </footer>
  </div>
  <script id="data" type="application/json">
${json}
  </script>
  <script>
  (function () {
    const data = JSON.parse(document.getElementById('data').textContent);
    const byId = Object.fromEntries(data.contracts.map(c => [c.id, c]));
    let selected = data.activeId;
    const active = byId[data.activeId];
    const pct = Math.round((data.progress.validated / Math.max(1, data.progress.required)) * 100);
    document.getElementById('hero').innerHTML =
      '<div class="panel active"><div class="eyebrow">Contrat actif</div><h2>' + active.id + ' — ' + active.name + '</h2>' +
      '<p style="margin:0;color:#a7bbb3;font-size:13px">' + (active.note || '') + '</p><div class="badges">' +
      '<span class="badge ' + statusClass(active.status) + '">' + active.status + '</span>' +
      (active.status === 'REVUE' ? '<span class="badge nonval">NON VALIDÉ</span>' : '') +
      (active.blocking ? '<span class="badge block">BLOQUANT</span>' : '') +
      '</div>' +
      (active.detail ? '<div style="font-size:13px;color:#b7cbc2">Décisions : <strong style="font-size:20px;color:#e9efec">' + active.detail.decisions + '</strong></div>' : '') +
      '</div><div class="panel"><div class="progressLabel"><span>Contrats autonomes requis validés</span><strong>' +
      data.progress.validated + ' / ' + data.progress.required + '</strong></div><div class="bar"><div class="fill" style="width:' + pct +
      '%"></div></div><div class="meta">Progression ' + pct + '% · sync ' + data.lastSync +
      ' · Case B ' + data.caseB.status + '</div></div>';

    function statusClass(s) {
      if (s === 'REVUE') return 'revue';
      if (s === 'SUFFISANT') return 'suff';
      return 'todo';
    }
    function renderDetail(c) {
      const deps = (c.dependsOn || []).join(' · ') || '—';
      const prov = (c.providesTo || []).map(id => c.id + ' → ' + id).join('<br>') || '—';
      let html = '<div class="eyebrow">Fiche contrat</div><h3>' + c.id + '</h3><p class="fname">' + c.name + '</p>';
      html += '<div class="badges"><span class="badge ' + statusClass(c.status) + '">' + c.status + '</span>';
      if (c.status === 'REVUE') html += '<span class="badge nonval">NON VALIDÉ</span>';
      if (c.blocking) html += '<span class="badge block">BLOQUANT</span>';
      if (c.coverage === 'partielle' && c.category === 'REQUIS') html += '<span class="badge partiel">PARTIEL</span>';
      html += '</div>';
      if (c.note) html += '<p style="margin:0 0 8px;font-size:13px;border-left:2px solid var(--accent);padding-left:10px">' + c.note + '</p>';
      if (c.file) html += '<p class="fname">Fichier : ' + c.file + '</p>';
      if (c.detail) {
        html += '<div class="blockTitle">Décisions</div><div class="dec">' + c.detail.decisions + '</div>';
        html += '<div class="blockTitle">Frontières</div><ul>' + c.detail.frontiers.map(f => '<li>' + f + '</li>').join('') + '</ul>';
        html += '<div class="blockTitle">Écarts constatés</div><div class="gaps"><p class="gapNote">Écarts constatés — pas des corrections automatiques.</p><ul>' +
          c.detail.gaps.map(g => '<li>' + g + '</li>').join('') + '</ul></div>';
      }
      html += '<div class="blockTitle">Dépendances (registre)</div><p style="font-size:12px;color:#b6c7c0;margin:0 0 6px"><strong>Dépend de :</strong> ' + deps + '</p>';
      html += '<p style="font-size:12px;color:#b6c7c0;margin:0">' + prov + '</p>';
      document.getElementById('detail').innerHTML = html;
    }
    function renderList() {
      const list = document.getElementById('list');
      list.innerHTML = data.order.map(id => {
        const c = byId[id];
        const activeCls = id === data.activeId ? ' active' : '';
        const sel = id === selected ? ' style="outline:1px solid #3d5a4c"' : '';
        return '<button class="row' + activeCls + '" data-id="' + id + '"' + sel + ' type="button">' +
          '<div class="rowTop"><span class="id">' + c.id + '</span><span class="name">' + c.name + '</span>' +
          (id === data.activeId ? '<span class="badge revue" style="margin-left:auto">ACTIF</span>' : '') +
          '</div><div class="badges"><span class="badge ' + statusClass(c.status) + '">' + c.status + '</span>' +
          (c.status === 'REVUE' ? '<span class="badge nonval">NON VALIDÉ</span>' : '') +
          (c.blocking ? '<span class="badge block">BLOQUANT</span>' : '') +
          '</div></button>';
      }).join('');
      list.querySelectorAll('.row').forEach(btn => {
        btn.addEventListener('click', () => {
          selected = btn.getAttribute('data-id');
          renderList();
          renderDetail(byId[selected]);
        });
      });
    }
    renderList();
    renderDetail(byId[selected]);
  })();
  </script>
</body>
</html>
`;
}
