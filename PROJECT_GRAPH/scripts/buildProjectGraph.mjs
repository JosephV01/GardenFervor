#!/usr/bin/env node
/**
 * GardenFervor — Project Graph builder
 * Run from repo root: node PROJECT_GRAPH/scripts/buildProjectGraph.mjs
 * Only writes under PROJECT_GRAPH/
 */

import fs from 'fs';
import path from 'path';
import { fileURLToPath } from 'url';
import { execSync } from 'child_process';
import { curatedNodes, curatedEdges, CURATED_VERSION } from './curatedGraph.mjs';

const __dirname = path.dirname(fileURLToPath(import.meta.url));
const GRAPH_ROOT = path.resolve(__dirname, '..');
const REPO_ROOT = path.resolve(GRAPH_ROOT, '..');

const RELATION_TYPES = new Set([
  'DEPENDS_ON', 'OWNS', 'PRODUCES', 'CONSUMES', 'READS', 'WRITES', 'EXECUTES',
  'SIGNALS', 'INVALIDATES', 'PERSISTS', 'VALIDATES', 'GOVERNS', 'CONSTRAINS',
  'VISUALIZES', 'INTEGRATES_WITH',
]);

const VIEW_DEFS = [
  { file: 'GardenFervor_ProjectGraph.mmd', title: 'MASTER', filter: () => true },
  {
    file: 'GardenFervor_SystemsGraph.mmd',
    title: 'SYSTEMS',
    filter: (n) =>
      ['WORLD_TERRAIN', 'SPATIAL', 'PROJECTS_TASKS', 'UNITS_EXECUTION', 'ECONOMY_RESOURCES', 'BUILDINGS_INFRA', 'UI_INPUT', 'GAME_DEMO', 'DATA'].includes(n.category),
  },
  {
    file: 'GardenFervor_RulesGraph.mmd',
    title: 'RULES',
    filter: (n) =>
      ['GOVERNANCE', 'DESIGN_GATE', 'CONTRACTS', 'WORLD_TERRAIN', 'SPATIAL', 'PROJECTS_TASKS', 'UNITS_EXECUTION'].includes(n.category)
      && (n.category !== 'WORLD_TERRAIN' || n.id.startsWith('sys_') || n.id.startsWith('c_')),
  },
  {
    file: 'GardenFervor_DataFlowGraph.mmd',
    title: 'DATA_FLOW',
    filter: (n) =>
      n.category === 'DATA'
      || ['sys_project', 'sys_task', 'sys_spatial', 'sys_runtime_store', 'sys_landscape_terraform', 'sys_physical_economy', 'sys_unit_agent'].includes(n.id),
  },
  {
    file: 'GardenFervor_ExecutionGraph.mmd',
    title: 'EXECUTION',
    filter: (n) =>
      ['sys_project', 'sys_siteprep', 'sys_task', 'sys_unit_agent', 'sys_terraform_tool', 'sys_landscape_terraform', 'sys_physical_economy', 'sys_spatial', 'sys_case_b', 'data_project_record', 'data_task_record', 'data_stock', 'data_height_store'].includes(n.id)
      || ['c_03', 'c_04', 'c_05', 'c_07', 'c_08'].includes(n.id),
  },
  {
    file: 'GardenFervor_ValidationGraph.mmd',
    title: 'VALIDATION',
    filter: (n) =>
      n.category === 'VALIDATION'
      || n.id.startsWith('sys_')
      || n.id.startsWith('evid_')
      || n.id.startsWith('ext_'),
  },
  {
    file: 'GardenFervor_ExternalGraph.mmd',
    title: 'EXTERNAL',
    filter: (n) =>
      ['CONTENT_EXTERNAL', 'TOOLING', 'WORLD_TERRAIN'].includes(n.category)
      || n.id.startsWith('ext_')
      || n.id === 'sys_visual_runtime_gate'
      || n.id === 'sys_landscape_terraform'
      || n.id === 'c_01'
      || n.id === 'c_23',
  },
];

function exists(rel) {
  return fs.existsSync(path.join(REPO_ROOT, rel));
}

function readText(rel) {
  const p = path.join(REPO_ROOT, rel);
  if (!fs.existsSync(p)) return null;
  return fs.readFileSync(p, 'utf8');
}

function gitInfo() {
  try {
    const head = execSync('git rev-parse HEAD', { cwd: REPO_ROOT, encoding: 'utf8' }).trim();
    const short = execSync('git rev-parse --short HEAD', { cwd: REPO_ROOT, encoding: 'utf8' }).trim();
    const branch = execSync('git rev-parse --abbrev-ref HEAD', { cwd: REPO_ROOT, encoding: 'utf8' }).trim();
    const dirty = execSync('git status --porcelain', { cwd: REPO_ROOT, encoding: 'utf8' })
      .split('\n')
      .filter(Boolean).length;
    return { head, short, branch, dirtyFiles: dirty, workingTree: dirty > 0 ? 'dirty' : 'clean' };
  } catch {
    return { head: 'unknown', short: 'unknown', branch: 'unknown', dirtyFiles: -1, workingTree: 'unknown' };
  }
}

function listDirNames(rel) {
  const p = path.join(REPO_ROOT, rel);
  if (!fs.existsSync(p)) return [];
  return fs.readdirSync(p, { withFileTypes: true }).filter((d) => d.isDirectory()).map((d) => d.name);
}

function scanSourceSubsystems() {
  const rts = path.join(REPO_ROOT, 'Source/GardenFervor');
  const found = [];
  if (!fs.existsSync(rts)) return found;
  function walk(dir) {
    for (const ent of fs.readdirSync(dir, { withFileTypes: true })) {
      const full = path.join(dir, ent.name);
      if (ent.isDirectory()) walk(full);
      else if (ent.name.endsWith('.h')) {
        const text = fs.readFileSync(full, 'utf8');
        if (/UWorldSubsystem|UTickableWorldSubsystem|UGameInstanceSubsystem/.test(text)
          || /class GARDENFERVOR_API UGardenFervor\w+Component/.test(text)
          || /class GARDENFERVOR_API UGardenFervor\w+Subsystem/.test(text)) {
          found.push(path.relative(REPO_ROOT, full).replace(/\\/g, '/'));
        }
      }
    }
  }
  walk(rts);
  return found;
}

function scanEvidence() {
  const saved = path.join(REPO_ROOT, 'Saved');
  if (!fs.existsSync(saved)) return [];
  return fs.readdirSync(saved)
    .filter((n) => /Gate|ODC_/i.test(n) && n.endsWith('.txt'))
    .map((n) => `Saved/${n}`);
}

function scanContractFiles() {
  const dir = path.join(REPO_ROOT, 'CONTRATS');
  if (!fs.existsSync(dir)) return [];
  return fs.readdirSync(dir).filter((n) => n.endsWith('.md')).map((n) => `CONTRATS/${n}`);
}

function verifyPaths(nodes, edges) {
  const anomalies = [];
  for (const n of nodes) {
    for (const f of [...(n.sourceFiles || []), ...(n.sourceDocuments || [])]) {
      if (!f || f.endsWith('/')) {
        const dir = f.replace(/\/$/, '');
        if (dir && !exists(dir)) {
          anomalies.push({ type: 'MISSING_PATH', nodeId: n.id, path: f });
        }
        continue;
      }
      if (!exists(f)) {
        anomalies.push({ type: 'MISSING_PATH', nodeId: n.id, path: f });
      }
    }
  }
  const ids = new Set(nodes.map((n) => n.id));
  for (const edge of edges) {
    if (!ids.has(edge.from)) anomalies.push({ type: 'DANGLING_EDGE_FROM', edgeId: edge.id, from: edge.from });
    if (!ids.has(edge.to)) anomalies.push({ type: 'DANGLING_EDGE_TO', edgeId: edge.id, to: edge.to });
    if (!RELATION_TYPES.has(edge.type)) anomalies.push({ type: 'INVALID_RELATION_TYPE', edgeId: edge.id, relation: edge.type });
  }
  const seen = new Set();
  for (const n of nodes) {
    if (seen.has(n.id)) anomalies.push({ type: 'DUPLICATE_NODE_ID', nodeId: n.id });
    seen.add(n.id);
  }
  return anomalies;
}

function detectUnmappedSystems(nodes, discoveredHeaders) {
  const mapped = new Set();
  for (const n of nodes) {
    for (const f of n.sourceFiles || []) {
      if (f.endsWith('.h') || f.endsWith('.cpp')) mapped.add(f);
      if (f.endsWith('/')) {
        // directory coverage — skip exact match
      }
    }
  }
  const unmapped = [];
  for (const h of discoveredHeaders) {
    const covered = [...mapped].some((m) => h === m || h.startsWith(m.replace(/[^/]+$/, '')) || m.includes(path.basename(h, '.h')));
    // Heuristic: if any curated node lists this exact header
    const exact = nodes.some((n) => (n.sourceFiles || []).includes(h));
    if (!exact) {
      // Only flag subsystem headers not mentioned
      if (/Subsystem\.h$/.test(h) || /RuntimeGate\.h$/.test(h)) {
        unmapped.push(h);
      }
    }
  }
  return unmapped;
}

function architecturalChecks(nodes) {
  const byId = Object.fromEntries(nodes.map((n) => [n.id, n]));
  const warnings = [];
  const expect = [
    ['c_01', 'Terrain authority contract should exist'],
    ['c_02', 'Spatial contract should exist'],
    ['sys_runtime_store', 'Runtime store system'],
    ['sys_spatial', 'Spatial system'],
    ['sys_task', 'Task system'],
    ['sys_case_b', 'Case B suspended marker'],
  ];
  for (const [id, msg] of expect) {
    if (!byId[id]) warnings.push({ type: 'MISSING_EXPECTED_NODE', id, msg });
  }
  if (byId.c_03 && byId.c_03.documentStatus !== 'NON COMMENCÉ') {
    warnings.push({ type: 'C03_STATUS_UNEXPECTED', msg: 'C-03 expected closed addendum (NON COMMENCÉ) unless intentionally opened' });
  }
  // ETAT vs suivi divergence
  const etat = readText('ETAT_PROJET.md') || '';
  const suivi = readText('CONTRATS/00_SUIVI_CONTRATS.md') || '';
  if (/prochain ordre = C-03/i.test(etat) && /Prochain contrat autorisé\s*:\s*\nC-03/i.test(suivi)) {
    warnings.push({
      type: 'DOC_DIVERGENCE',
      msg: 'ETAT_PROJET et suivi indiquent C-03 comme prochain, mais C-03 est addendum SUFFISANT* fermé ; prochain obligatoire compteur = C-04 (registre ordre 4).',
    });
  }
  if (byId.c_01?.documentStatus === 'VALIDÉ' && !exists('CONTRATS/C-01_TERRAIN_RUNTIME.md')) {
    warnings.push({ type: 'VALIDATED_WITHOUT_FILE', id: 'c_01' });
  }
  if (byId.c_02?.documentStatus === 'VALIDÉ' && !exists('CONTRATS/C-02_SUBSTRAT_SPATIAL.md')) {
    warnings.push({ type: 'VALIDATED_WITHOUT_FILE', id: 'c_02' });
  }
  return warnings;
}

function mermaidEscape(label) {
  return String(label).replace(/"/g, "'").replace(/[<>]/g, '');
}

function toMermaid(nodes, edges, title) {
  const ids = new Set(nodes.map((n) => n.id));
  const filteredEdges = edges.filter((e) => ids.has(e.from) && ids.has(e.to));
  const byCat = new Map();
  for (const n of nodes) {
    if (!byCat.has(n.category)) byCat.set(n.category, []);
    byCat.get(n.category).push(n);
  }
  const lines = [`%% ${title} — generated by buildProjectGraph.mjs`, 'flowchart TB'];
  let gi = 0;
  for (const [cat, list] of byCat) {
    lines.push(`  subgraph G${gi}_${cat}["${cat}"]`);
    for (const n of list) {
      const status = n.validationStatus && n.validationStatus !== 'n/a'
        ? n.validationStatus
        : (n.implementationStatus || n.designStatus || '');
      const label = mermaidEscape(`${n.name}\\n[${status}]`);
      lines.push(`    ${n.id}["${label}"]`);
    }
    lines.push('  end');
    gi += 1;
  }
  for (const edge of filteredEdges) {
    const kind = edge.relationKind === 'FUTURE' ? 'FUTURE:' : edge.relationKind === 'UNVERIFIED' ? 'UNVERIFIED:' : '';
    const style = edge.relationKind === 'FUTURE' || edge.confidence === 'LOW' ? '-.->' : '-->';
    lines.push(`  ${edge.from} ${style}|${kind}${edge.type}| ${edge.to}`);
  }
  return `${lines.join('\n')}\n`;
}

function buildHtml(data) {
  const payload = JSON.stringify(data).replace(/</g, '\\u003c');
  return `<!DOCTYPE html>
<html lang="fr">
<head>
<meta charset="utf-8"/>
<meta name="viewport" content="width=device-width, initial-scale=1"/>
<title>GardenFervor — Project Graph</title>
<style>
  :root {
    --bg:#0f1410; --panel:#1a221c; --ink:#e8efe6; --muted:#9aab9c;
    --line:#3a4a3c; --accent:#7cb87a; --warn:#d4a24c; --danger:#c07070; --future:#6a8cbf;
  }
  * { box-sizing:border-box; }
  body { margin:0; font-family: "Segoe UI", system-ui, sans-serif; background:var(--bg); color:var(--ink); height:100vh; display:grid; grid-template-columns: 320px 1fr; }
  aside { border-right:1px solid var(--line); padding:12px; overflow:auto; background:var(--panel); }
  h1 { font-size:15px; margin:0 0 8px; }
  .meta { font-size:11px; color:var(--muted); margin-bottom:12px; line-height:1.4; }
  label { display:block; font-size:11px; color:var(--muted); margin:8px 0 4px; }
  input, select { width:100%; background:#101610; color:var(--ink); border:1px solid var(--line); border-radius:4px; padding:6px 8px; }
  .chips { display:flex; flex-wrap:wrap; gap:4px; margin-top:8px; }
  .chip { font-size:10px; border:1px solid var(--line); padding:2px 6px; border-radius:999px; cursor:pointer; color:var(--muted); }
  .chip.on { background:#243028; color:var(--accent); border-color:var(--accent); }
  #canvasWrap { position:relative; overflow:hidden; }
  canvas { display:block; width:100%; height:100%; cursor:grab; }
  #detail { margin-top:12px; font-size:12px; line-height:1.45; border-top:1px solid var(--line); padding-top:10px; }
  #detail code { color:var(--accent); font-size:11px; }
  .badge { display:inline-block; font-size:10px; padding:1px 5px; border-radius:3px; margin-right:4px; background:#243028; }
  .badge.FUTURE { background:#1e2a3a; color:var(--future); }
  .badge.SUSPENDED,.badge.INVALIDÉ { background:#3a2418; color:var(--warn); }
  .legend { font-size:10px; color:var(--muted); margin-top:10px; }
</style>
</head>
<body>
<aside>
  <h1>GardenFervor — Project Graph</h1>
  <div class="meta" id="meta"></div>
  <label>Recherche</label>
  <input id="search" placeholder="id, nom, catégorie…"/>
  <label>Vue</label>
  <select id="view">
    <option value="MASTER">MASTER</option>
    <option value="SYSTEMS">SYSTEMS</option>
    <option value="RULES">RULES / CONTRACTS</option>
    <option value="DATA_FLOW">DATA FLOW</option>
    <option value="EXECUTION">EXECUTION</option>
    <option value="VALIDATION">VALIDATION</option>
    <option value="EXTERNAL">EXTERNAL / CONTENT</option>
  </select>
  <label>Catégories</label>
  <div class="chips" id="cats"></div>
  <label>Statut implémentation</label>
  <select id="implFilter">
    <option value="">(tous)</option>
    <option>IMPLEMENTED</option>
    <option>PARTIAL</option>
    <option>STUB</option>
    <option>LEGACY</option>
    <option>SUSPENDED</option>
    <option>PLANNED</option>
    <option>UNKNOWN</option>
    <option>n/a</option>
  </select>
  <div class="legend">
    Drag = pan · Molette = zoom · Clic = détail<br/>
    Trait plein = ACTIVE · pointillé = FUTURE/faible confiance
  </div>
  <div id="detail"><em>Sélectionnez un nœud</em></div>
</aside>
<div id="canvasWrap"><canvas id="c"></canvas></div>
<script>
const DATA = ${payload};
const VIEW_FILTERS = {
  MASTER: () => true,
  SYSTEMS: (n) => ['WORLD_TERRAIN','SPATIAL','PROJECTS_TASKS','UNITS_EXECUTION','ECONOMY_RESOURCES','BUILDINGS_INFRA','UI_INPUT','GAME_DEMO','DATA'].includes(n.category),
  RULES: (n) => ['GOVERNANCE','DESIGN_GATE','CONTRACTS'].includes(n.category) || n.id.startsWith('sys_') && ['WORLD_TERRAIN','SPATIAL','PROJECTS_TASKS','UNITS_EXECUTION'].includes(n.category),
  DATA_FLOW: (n) => n.category === 'DATA' || ['sys_project','sys_task','sys_spatial','sys_runtime_store','sys_landscape_terraform','sys_physical_economy','sys_unit_agent'].includes(n.id),
  EXECUTION: (n) => ['sys_project','sys_siteprep','sys_task','sys_unit_agent','sys_terraform_tool','sys_landscape_terraform','sys_physical_economy','sys_spatial','sys_case_b','data_project_record','data_task_record','data_stock','data_height_store','c_03','c_04','c_05','c_07','c_08'].includes(n.id),
  VALIDATION: (n) => n.category === 'VALIDATION' || n.id.startsWith('sys_') || n.id.startsWith('evid_') || n.id.startsWith('ext_'),
  EXTERNAL: (n) => ['CONTENT_EXTERNAL','TOOLING'].includes(n.category) || ['ext_m4','ext_uds','ext_ue_plugins','sys_visual_runtime_gate','sys_landscape_terraform','c_01','c_23'].includes(n.id),
};
const CAT_COLOR = {
  GOVERNANCE:'#8fb58d', DESIGN_GATE:'#c4b27a', CONTRACTS:'#d4a24c', WORLD_TERRAIN:'#7cb87a',
  SPATIAL:'#6a8cbf', PROJECTS_TASKS:'#b78fd4', UNITS_EXECUTION:'#e07a7a', ECONOMY_RESOURCES:'#7ac4b0',
  BUILDINGS_INFRA:'#a09080', UI_INPUT:'#90a0b0', GAME_DEMO:'#c090a0', DATA:'#a0c4e0',
  VALIDATION:'#90d0a0', CONTENT_EXTERNAL:'#80a0d0', TOOLING:'#a0a0a0'
};
const canvas = document.getElementById('c');
const ctx = canvas.getContext('2d');
let nodes = [], edges = [], selected = null;
let transform = { x: 40, y: 40, s: 1 };
let drag = null;

document.getElementById('meta').textContent =
  (DATA.generationInfo?.generatedAt || '') + ' · HEAD ' + (DATA.generationInfo?.git?.short || '?') +
  ' · nodes ' + DATA.nodes.length + ' · edges ' + DATA.edges.length;

const cats = [...new Set(DATA.nodes.map(n => n.category))].sort();
const catState = Object.fromEntries(cats.map(c => [c, true]));
const catsEl = document.getElementById('cats');
cats.forEach(c => {
  const el = document.createElement('span');
  el.className = 'chip on'; el.textContent = c;
  el.onclick = () => { catState[c] = !catState[c]; el.classList.toggle('on', catState[c]); layout(); draw(); };
  catsEl.appendChild(el);
});

function activeNodes() {
  const view = document.getElementById('view').value;
  const q = document.getElementById('search').value.trim().toLowerCase();
  const impl = document.getElementById('implFilter').value;
  return DATA.nodes.filter(n => {
    if (!VIEW_FILTERS[view](n)) return false;
    if (!catState[n.category]) return false;
    if (impl && (n.implementationStatus || '') !== impl) return false;
    if (!q) return true;
    return (n.id + ' ' + n.name + ' ' + n.category + ' ' + (n.responsibility||'')).toLowerCase().includes(q);
  });
}

function layout() {
  nodes = activeNodes();
  const ids = new Set(nodes.map(n => n.id));
  edges = DATA.edges.filter(e => ids.has(e.from) && ids.has(e.to));
  const byCat = {};
  nodes.forEach(n => { (byCat[n.category] ||= []).push(n); });
  let col = 0;
  Object.keys(byCat).sort().forEach(cat => {
    byCat[cat].forEach((n, i) => {
      n._x = col * 220;
      n._y = i * 54;
    });
    col++;
  });
}

function resize() {
  const wrap = document.getElementById('canvasWrap');
  canvas.width = wrap.clientWidth * devicePixelRatio;
  canvas.height = wrap.clientHeight * devicePixelRatio;
  ctx.setTransform(devicePixelRatio, 0, 0, devicePixelRatio, 0, 0);
  draw();
}

function worldFromEvent(ev) {
  const r = canvas.getBoundingClientRect();
  return {
    x: (ev.clientX - r.left - transform.x) / transform.s,
    y: (ev.clientY - r.top - transform.y) / transform.s,
  };
}

function draw() {
  const w = canvas.clientWidth, h = canvas.clientHeight;
  ctx.clearRect(0, 0, w, h);
  ctx.save();
  ctx.translate(transform.x, transform.y);
  ctx.scale(transform.s, transform.s);
  const pos = Object.fromEntries(nodes.map(n => [n.id, n]));
  for (const e of edges) {
    const a = pos[e.from], b = pos[e.to];
    if (!a || !b) continue;
    ctx.beginPath();
    ctx.strokeStyle = e.relationKind === 'FUTURE' ? '#6a8cbf' : (e.confidence === 'HIGH' ? '#5a6e5c' : '#8a7a4a');
    ctx.lineWidth = selected && (selected.id === e.from || selected.id === e.to) ? 2 : 1;
    if (e.relationKind === 'FUTURE' || e.confidence === 'LOW') ctx.setLineDash([4, 4]); else ctx.setLineDash([]);
    ctx.moveTo(a._x + 80, a._y + 16);
    ctx.lineTo(b._x + 80, b._y + 16);
    ctx.stroke();
    ctx.setLineDash([]);
    ctx.fillStyle = '#9aab9c';
    ctx.font = '9px sans-serif';
    ctx.fillText(e.type, (a._x + b._x) / 2 + 40, (a._y + b._y) / 2 + 12);
  }
  for (const n of nodes) {
    const col = CAT_COLOR[n.category] || '#aaa';
    ctx.fillStyle = '#1a221c';
    ctx.strokeStyle = selected?.id === n.id ? '#fff' : col;
    ctx.lineWidth = selected?.id === n.id ? 2 : 1;
    roundRect(n._x, n._y, 160, 40, 6);
    ctx.fill(); ctx.stroke();
    ctx.fillStyle = col;
    ctx.font = 'bold 11px sans-serif';
    ctx.fillText(n.name.slice(0, 28), n._x + 8, n._y + 16);
    ctx.fillStyle = '#9aab9c';
    ctx.font = '9px sans-serif';
    ctx.fillText((n.implementationStatus || n.designStatus || ''), n._x + 8, n._y + 30);
  }
  ctx.restore();
}

function roundRect(x,y,w,h,r) {
  ctx.beginPath();
  ctx.moveTo(x+r,y); ctx.arcTo(x+w,y,x+w,y+h,r); ctx.arcTo(x+w,y+h,x,y+h,r);
  ctx.arcTo(x,y+h,x,y,r); ctx.arcTo(x,y,x+w,y,r); ctx.closePath();
}

function showDetail(n) {
  selected = n;
  const rel = DATA.edges.filter(e => e.from === n.id || e.to === n.id);
  document.getElementById('detail').innerHTML = \`
    <div><strong>\${n.name}</strong> <span class="badge">\${n.category}</span>
    \${n.implementationStatus==='SUSPENDED'?'<span class="badge SUSPENDED">SUSPENDED</span>':''}
    \${n.validationStatus==='INVALIDÉ'?'<span class="badge INVALIDÉ">INVALIDÉ</span>':''}</div>
    <div>\${n.responsibility || ''}</div>
    <div>design: <code>\${n.designStatus}</code> · impl: <code>\${n.implementationStatus}</code> · valid: <code>\${n.validationStatus}</code></div>
    <div>confidence: <code>\${n.confidence}</code></div>
    <div style="margin-top:6px"><b>Sources</b><br/>\${[...(n.sourceDocuments||[]),...(n.sourceFiles||[])].map(s=>'<code>'+s+'</code>').join('<br/>') || '—'}</div>
    <div style="margin-top:6px"><b>Relations (\${rel.length})</b><br/>\${rel.map(e => {
      const other = e.from === n.id ? e.to : e.from;
      const dir = e.from === n.id ? '→' : '←';
      return '<span class="badge '+(e.relationKind||'')+'">'+e.relationKind+'</span> '+dir+' <code>'+e.type+'</code> '+other+' <span style="color:#9aab9c">('+e.source+')</span>';
    }).join('<br/>')}</div>
    \${n.notes ? '<div style="margin-top:6px;color:#d4a24c">'+n.notes+'</div>' : ''}
  \`;
  draw();
}

canvas.addEventListener('mousedown', ev => {
  const p = worldFromEvent(ev);
  const hit = [...nodes].reverse().find(n => p.x >= n._x && p.x <= n._x+160 && p.y >= n._y && p.y <= n._y+40);
  if (hit) showDetail(hit);
  drag = { x: ev.clientX, y: ev.clientY, tx: transform.x, ty: transform.y };
});
window.addEventListener('mouseup', () => drag = null);
canvas.addEventListener('mousemove', ev => {
  if (!drag) return;
  transform.x = drag.tx + (ev.clientX - drag.x);
  transform.y = drag.ty + (ev.clientY - drag.y);
  draw();
});
canvas.addEventListener('wheel', ev => {
  ev.preventDefault();
  const factor = ev.deltaY > 0 ? 0.9 : 1.1;
  transform.s = Math.min(2.5, Math.max(0.3, transform.s * factor));
  draw();
}, { passive:false });

['search','view','implFilter'].forEach(id => {
  document.getElementById(id).addEventListener('input', () => { layout(); draw(); });
  document.getElementById(id).addEventListener('change', () => { layout(); draw(); });
});
window.addEventListener('resize', resize);
layout(); resize();
</script>
</body>
</html>
`;
}

function writeCurrentState(data, scan) {
  const byCat = {};
  for (const n of data.nodes) {
    byCat[n.category] = (byCat[n.category] || 0) + 1;
  }
  const conf = { HIGH: 0, MEDIUM: 0, LOW: 0 };
  const kinds = { ACTIVE: 0, FUTURE: 0, UNVERIFIED: 0 };
  for (const e of data.edges) {
    conf[e.confidence] = (conf[e.confidence] || 0) + 1;
    kinds[e.relationKind || 'ACTIVE'] = (kinds[e.relationKind || 'ACTIVE'] || 0) + 1;
  }
  const impl = {};
  for (const n of data.nodes) {
    const k = n.implementationStatus || 'n/a';
    impl[k] = (impl[k] || 0) + 1;
  }
  const lines = [
    '# PROJECT_GRAPH — CURRENT_STATE',
    '',
    `Généré : **${data.generationInfo.generatedAt}**`,
    `HEAD : \`${data.generationInfo.git.head}\` (${data.generationInfo.git.workingTree}, ${data.generationInfo.git.dirtyFiles} fichiers dirty)`,
    `Curated schema : \`${data.generationInfo.curatedVersion}\``,
    '',
    '## Inventaire',
    '',
    `| Métrique | Valeur |`,
    `| --- | ---: |`,
    `| Nœuds | ${data.nodes.length} |`,
    `| Relations | ${data.edges.length} |`,
    `| Relations HIGH | ${conf.HIGH || 0} |`,
    `| Relations MEDIUM | ${conf.MEDIUM || 0} |`,
    `| Relations LOW | ${conf.LOW || 0} |`,
    `| Relations ACTIVE | ${kinds.ACTIVE || 0} |`,
    `| Relations FUTURE | ${kinds.FUTURE || 0} |`,
    `| Relations UNVERIFIED | ${kinds.UNVERIFIED || 0} |`,
    `| Contrats (registre) | ${data.nodes.filter((n) => n.category === 'CONTRACTS').length} |`,
    `| Contrats fichiers présents | ${scan.contractFiles.filter((f) => f.startsWith('CONTRATS/C-')).length} |`,
    `| Preuves inventoriées | ${data.nodes.filter((n) => n.category === 'VALIDATION').length} |`,
    `| Gates Saved détectés | ${scan.evidenceFiles.length} |`,
    `| Headers systèmes scannés | ${scan.discoveredHeaders.length} |`,
    `| Intégrations externes | ${data.nodes.filter((n) => n.category === 'CONTENT_EXTERNAL').length} |`,
    '',
    '## Catégories',
    '',
    ...Object.entries(byCat).sort().map(([k, v]) => `- **${k}** : ${v}`),
    '',
    '## Implémentation (nœuds)',
    '',
    ...Object.entries(impl).sort().map(([k, v]) => `- **${k}** : ${v}`),
    '',
    '## Contrats VALIDÉS (documentaire)',
    '',
    ...data.nodes
      .filter((n) => n.category === 'CONTRACTS' && n.documentStatus === 'VALIDÉ')
      .map((n) => `- ${n.name}`),
    '',
    '## Systèmes SUSPENDED / LEGACY / STUB',
    '',
    ...data.nodes
      .filter((n) => ['SUSPENDED', 'LEGACY', 'STUB'].includes(n.implementationStatus))
      .map((n) => `- **${n.implementationStatus}** — ${n.name}`),
    '',
    '## Anomalies / écarts',
    '',
    ...(data.anomalies.length
      ? data.anomalies.map((a) => `- \`${a.type}\` — ${JSON.stringify(a)}`)
      : ['- Aucune anomalie structurelle bloquante.']),
    '',
    '## Avertissements architecturaux',
    '',
    ...(data.warnings.length
      ? data.warnings.map((w) => `- \`${w.type}\` — ${w.msg || JSON.stringify(w)}`)
      : ['- Aucun.']),
    '',
    '## Systèmes potentiellement absents du graphe (scan)',
    '',
    ...(scan.unmappedHeaders.length
      ? scan.unmappedHeaders.map((h) => `- \`${h}\``)
      : ['- Aucun header Subsystem/RuntimeGate non référencé.']),
    '',
    '## Sources inspectées',
    '',
    ...data.generationInfo.sourcesInspected.map((s) => `- ${s}`),
    '',
    '## Frontières contractuelles clés (contrôles)',
    '',
    '- C-01 = autorité terrain (gouverne Store / contraint Landscape)',
    '- C-02 = référence spatiale (gouverne SpatialSubsystem)',
    '- C-03 = addendum fermé (NON COMMENCÉ)',
    '- C-04 = graphe tâches (contrat VALIDÉ ; runtime TaskSubsystem présent)',
    '- C-05 = SitePrep (contrat VALIDÉ ; helpers présents ; Case B SUSPENDED)',
    '- C-07 = autonomie unité (contrat VALIDÉ ; runtime UnitTaskAgent présent ; dettes documentées)',
    '- C-08 = Terraformer opérationnel (contrat VALIDÉ ; métier formalisé ; runtime partiel ; Case B SUSPENDED)',
    '- C-11 = frontières FUTURE marquées tant que contrat non VALIDÉ',
    '',
    '## Règle',
    '',
    'Ce fichier est une **projection**. En cas de conflit : dépôt réel > contrats/règles > preuves > documentation descriptive.',
    '',
  ];
  fs.writeFileSync(path.join(GRAPH_ROOT, 'CURRENT_STATE.md'), lines.join('\n'), 'utf8');
}

function main() {
  const generatedAt = new Date().toISOString();
  const git = gitInfo();
  const discoveredHeaders = scanSourceSubsystems();
  const evidenceFiles = scanEvidence();
  const contractFiles = scanContractFiles();
  const contentDirs = listDirNames('Content');

  const nodes = curatedNodes.map((n) => ({
    ...n,
    lastVerified: generatedAt,
  }));
  const edges = curatedEdges.map((e) => ({ ...e }));

  const anomalies = verifyPaths(nodes, edges);
  const warnings = architecturalChecks(nodes);
  const unmappedHeaders = detectUnmappedSystems(nodes, discoveredHeaders);

  // Content dirs present but not in graph
  for (const d of contentDirs) {
    if (['M4', 'UltraDynamicSky', 'GardenFervor', 'Python', 'Collections', 'Developers'].includes(d)) continue;
    warnings.push({ type: 'CONTENT_DIR_UNMAPPED', msg: `Content/${d} présent mais non mappé explicitement` });
  }

  const sourcesInspected = [
    'REGLES_PROJET.md',
    'ETAT_PROJET.md',
    'HISTORIQUE_MODIFICATIONS.md',
    'CONTRATS/',
    'GardenFervor_DesignGate_React/src/data/designGate.js',
    'Source/GardenFervor/',
    'Saved/ODC_*Gate.txt',
    'GardenFervor.uproject',
    'Content/',
    'docs/',
  ];

  const data = {
    metadata: {
      title: 'GardenFervor Project Graph',
      description: 'Projection documentaire de l’architecture — pas une source de vérité parallèle',
      relationTypes: [...RELATION_TYPES],
    },
    generationInfo: {
      generatedAt,
      curatedVersion: CURATED_VERSION,
      generator: 'PROJECT_GRAPH/scripts/buildProjectGraph.mjs',
      git,
      sourcesInspected,
      scan: {
        discoveredHeaderCount: discoveredHeaders.length,
        evidenceFileCount: evidenceFiles.length,
        contractFileCount: contractFiles.length,
        contentDirs,
      },
    },
    nodes,
    edges,
    sources: {
      contractFiles,
      evidenceFiles,
      discoveredHeaders,
    },
    statuses: {
      document: ['VALIDÉ', 'NON COMMENCÉ', 'REVUE', 'RÉDACTION', 'SUSPENDU', 'BLOQUÉ'],
      implementation: ['IMPLEMENTED', 'PARTIAL', 'STUB', 'LEGACY', 'SUSPENDED', 'PLANNED', 'UNKNOWN', 'n/a'],
      validation: ['PASS', 'INVALIDÉ', 'PARTIAL', 'n/a'],
      confidence: ['HIGH', 'MEDIUM', 'LOW'],
      relationKind: ['ACTIVE', 'FUTURE', 'UNVERIFIED'],
    },
    anomalies,
    warnings,
  };

  fs.mkdirSync(path.join(GRAPH_ROOT, 'data'), { recursive: true });
  fs.mkdirSync(path.join(GRAPH_ROOT, 'graph'), { recursive: true });

  fs.writeFileSync(
    path.join(GRAPH_ROOT, 'data', 'projectGraph.data.json'),
    `${JSON.stringify(data, null, 2)}\n`,
    'utf8',
  );

  for (const view of VIEW_DEFS) {
    const vNodes = nodes.filter(view.filter);
    const mmd = toMermaid(vNodes, edges, view.title);
    fs.writeFileSync(path.join(GRAPH_ROOT, 'graph', view.file), mmd, 'utf8');
  }

  fs.writeFileSync(
    path.join(GRAPH_ROOT, 'GardenFervor_ProjectGraph.html'),
    buildHtml(data),
    'utf8',
  );

  writeCurrentState(data, { discoveredHeaders, evidenceFiles, contractFiles, unmappedHeaders });

  console.log('PROJECT_GRAPH build complete');
  console.log(`  nodes=${nodes.length} edges=${edges.length}`);
  console.log(`  anomalies=${anomalies.length} warnings=${warnings.length}`);
  console.log(`  unmappedHeaders=${unmappedHeaders.length}`);
  console.log(`  git=${git.short} (${git.workingTree})`);
  if (anomalies.length) {
    console.log('Anomalies:');
    for (const a of anomalies.slice(0, 20)) console.log(' ', a);
  }
  if (warnings.length) {
    console.log('Warnings:');
    for (const w of warnings.slice(0, 20)) console.log(' ', w.type, w.msg || '');
  }
}

main();
