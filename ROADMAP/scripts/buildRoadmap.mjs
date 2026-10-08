#!/usr/bin/env node
/**
 * Build GardenFervor global Roadmap HTML from Markdown SoT.
 * Usage: node ROADMAP/scripts/buildRoadmap.mjs
 */

import fs from 'fs';
import path from 'path';
import { fileURLToPath } from 'url';
import { execSync } from 'child_process';
import { createHash } from 'crypto';

const __dirname = path.dirname(fileURLToPath(import.meta.url));
const ROOT = path.resolve(__dirname, '..');
const REPO = path.resolve(ROOT, '..');
const MD_PATH = path.join(ROOT, 'GardenFervor_ROADMAP.md');

const STATUSES = new Set([
  'VALIDÉ', 'TERMINÉ', 'EN COURS', 'À CONCEVOIR', 'À FAIRE', 'BLOQUÉ',
  'SUSPENDU', 'ABANDONNÉ', 'NON DÉFINI', 'PARTIEL', 'PASS', 'INVALIDÉ',
  'NON TERMINÉE', 'VALIDÉE', 'PARTIELLE', 'TERMINÉE', 'n/a',
]);

function parseKvBlock(raw) {
  const out = {};
  for (const line of raw.split(/\r?\n/)) {
    const t = line.trim();
    if (!t || t.startsWith('#')) continue;
    const i = t.indexOf(':');
    if (i < 0) continue;
    const k = t.slice(0, i).trim();
    const v = t.slice(i + 1).trim();
    out[k] = v;
  }
  return out;
}

function parseMarkdown(text) {
  const issues = [];
  const metaMatch = text.match(/<!--RM:META\s*([\s\S]*?)-->/);
  if (!metaMatch) issues.push('Missing <!--RM:META-->');
  const meta = metaMatch ? parseKvBlock(metaMatch[1]) : {};

  const nowMatch = text.match(/<!--RM:NOW\s*([\s\S]*?)-->/);
  if (!nowMatch) issues.push('Missing <!--RM:NOW-->');
  const now = nowMatch ? parseKvBlock(nowMatch[1]) : {};

  const nextMatch = text.match(/<!--RM:NEXT\s*([\s\S]*?)-->/);
  if (!nextMatch) issues.push('Missing <!--RM:NEXT-->');
  const next = nextMatch ? parseKvBlock(nextMatch[1]) : {};

  const phases = [];
  const phaseRe = /<!--RM:PHASE\s*([\s\S]*?)-->([\s\S]*?)<!--\/RM:PHASE-->/g;
  let pm;
  while ((pm = phaseRe.exec(text))) {
    const attrs = parseKvBlock(pm[1]);
    const body = pm[2];
    const jalons = [];
    const jalonRe = /<!--RM:JALON\s*([\s\S]*?)-->([\s\S]*?)(?=<!--RM:JALON|<!--\/RM:PHASE-->|$)/g;
    let jm;
    while ((jm = jalonRe.exec(body))) {
      const jAttrs = parseKvBlock(jm[1]);
      const jBody = jm[2];
      const works = [];
      const workRe = /<!--RM:WORK\s*([\s\S]*?)-->/g;
      let wm;
      while ((wm = workRe.exec(jBody))) {
        works.push(parseKvBlock(wm[1]));
      }
      jalons.push({ ...jAttrs, works });
    }
    phases.push({ ...attrs, jalons });
  }

  const cleanPhases = phases.filter((p) => p.id);
  if (!cleanPhases.length) issues.push('No phases parsed');
  if (cleanPhases.length !== phases.length) {
    issues.push(`Dropped ${phases.length - cleanPhases.length} phase block(s) without id`);
  }

  return { meta, now, next, phases: cleanPhases, issues };
}

function gitShort() {
  try {
    return execSync('git rev-parse --short HEAD', { cwd: REPO, encoding: 'utf8' }).trim();
  } catch {
    return 'unknown';
  }
}

function statusClass(s) {
  const u = String(s || '').toUpperCase();
  if (u.includes('VALIDÉ') || u === 'TERMINÉ' || u === 'PASS') return 'ok';
  if (u.includes('COURS') || u === 'PARTIEL' || u.includes('PARTIEL')) return 'wip';
  if (u.includes('SUSPEND') || u.includes('BLOQU')) return 'stop';
  if (u.includes('CONCEVOIR') || u.includes('FAIRE') || u.includes('PLAN')) return 'todo';
  if (u.includes('INVALID') || u.includes('ABANDON')) return 'bad';
  return 'muted';
}

function buildHtml(data) {
  const payload = JSON.stringify(data).replace(/</g, '\\u003c');
  const phases = data.phases;
  const doneish = phases.filter((p) => /VALIDÉ|TERMINÉ/.test(p.status)).length;
  const pct = phases.length ? Math.round((doneish / phases.length) * 100) : 0;

  return `<!DOCTYPE html>
<html lang="fr">
<head>
<meta charset="utf-8"/>
<meta name="viewport" content="width=device-width, initial-scale=1"/>
<title>${data.meta.title || 'GardenFervor Roadmap'}</title>
<style>
:root{
  --bg:#0e1413; --panel:#141d1b; --line:#26332f; --muted:#8fa19b; --text:#e9efec;
  --ok:#7bd7a8; --wip:#e5c28d; --todo:#8ecdf8; --stop:#e0a0a0; --bad:#f0b4b4; --accent:#7bd7a8;
  --font: Inter, ui-sans-serif, system-ui, "Segoe UI", sans-serif;
}
*{box-sizing:border-box}
body{margin:0;font-family:var(--font);background:radial-gradient(circle at 85% -10%,rgba(83,150,117,.14),transparent 30%),var(--bg);color:var(--text);line-height:1.5}
.wrap{max-width:1100px;margin:0 auto;padding:28px 18px 72px}
.top{display:flex;justify-content:space-between;gap:12px;flex-wrap:wrap;align-items:center;margin-bottom:14px}
.back{font-size:12px;font-weight:700;text-decoration:none;border:1px solid var(--line);padding:7px 10px;border-radius:8px;background:#18211f;color:#dce7e2}
.eyebrow{font-size:10px;letter-spacing:.16em;font-weight:800;color:#71877f;text-transform:uppercase}
h1{margin:6px 0 8px;font-size:clamp(1.7rem,3.5vw,2.4rem);letter-spacing:-.03em}
.lead{margin:0;color:var(--muted);max-width:720px;font-size:14px}
.now{
  margin:18px 0;padding:16px 18px;border-radius:14px;border:1px solid #3d6350;
  background:linear-gradient(135deg,#172822,#121c19);box-shadow:0 16px 38px rgba(0,0,0,.2)
}
.now h2{margin:0 0 6px;font-size:1.05rem}
.now p{margin:0;color:#c5d6cf;font-size:14px}
.next{
  margin:0 0 18px;padding:14px 16px;border-radius:12px;border:1px solid #3a5270;
  background:#152028
}
.next strong{color:var(--todo)}
.barWrap{margin:10px 0 4px}
.bar{height:10px;background:#1a2421;border-radius:99px;overflow:hidden}
.fill{height:100%;background:linear-gradient(90deg,#5bb98e,#9fe2bd);width:${pct}%}
.metaRow{display:flex;flex-wrap:wrap;gap:8px;margin-top:10px;font-size:12px;color:var(--muted)}
.badge{display:inline-flex;align-items:center;padding:3px 8px;border-radius:999px;font-size:10px;font-weight:800;border:1px solid transparent}
.badge.ok{background:#143026;border-color:#244c3b;color:var(--ok)}
.badge.wip{background:#30241a;border-color:#5a4229;color:var(--wip)}
.badge.todo{background:#152a37;border-color:#284b62;color:var(--todo)}
.badge.stop{background:#2b2020;border-color:#4d3636;color:var(--stop)}
.badge.bad{background:#3a1f1f;border-color:#7a3d3d;color:var(--bad)}
.badge.muted{background:#1a2220;border-color:#33403c;color:#9aada5}
.controls{display:grid;grid-template-columns:1.4fr .8fr .8fr;gap:10px;margin:16px 0}
@media(max-width:800px){.controls{grid-template-columns:1fr}}
input,select{width:100%;background:#101610;color:var(--text);border:1px solid var(--line);border-radius:8px;padding:8px 10px}
.tabs{display:flex;gap:6px;flex-wrap:wrap;margin:8px 0 16px}
.tab{border:1px solid var(--line);background:#18211f;color:var(--muted);border-radius:999px;padding:6px 12px;font-size:12px;font-weight:700;cursor:pointer}
.tab.on{border-color:#3d6350;color:var(--ok);background:#15231e}
.phase{border:1px solid var(--line);background:var(--panel);border-radius:14px;margin:0 0 12px;overflow:hidden}
.phase>header{padding:14px 16px;cursor:pointer;display:flex;justify-content:space-between;gap:12px;align-items:flex-start}
.phase>header:hover{background:#182320}
.phase h3{margin:0;font-size:1.05rem}
.phase .sub{margin:4px 0 0;color:var(--muted);font-size:12px}
.phase .body{display:none;padding:0 16px 14px;border-top:1px solid var(--line)}
.phase.open .body{display:block}
.jalon{margin:10px 0;padding:10px 12px;border-radius:10px;background:#111816;border:1px solid #202b28}
.jalon h4{margin:0 0 4px;font-size:.95rem}
.jalon p{margin:0;color:var(--muted);font-size:12px}
.works{margin:6px 0 0;padding-left:16px;color:#a7bbb3;font-size:12px}
.detail{margin-top:8px;font-size:11px;color:#7d9189}
footer{margin-top:28px;color:#5f736a;font-size:11px;display:flex;justify-content:space-between;gap:10px;flex-wrap:wrap}
.note{font-size:12px;color:var(--wip);margin-top:8px}
</style>
</head>
<body>
<div class="wrap">
  <div class="top">
    <div>
      <div class="eyebrow">GardenFervor · Roadmap globale</div>
      <h1>Où en est le projet — et où va-t-il</h1>
      <p class="lead">Source de vérité : <code>ROADMAP/GardenFervor_ROADMAP.md</code>. Cette page est générée — ne pas éditer le contenu ici.</p>
    </div>
    <a class="back" href="index.html">← Hub documentation</a>
  </div>

  <section class="now">
    <h2>Où en est GardenFervor ?</h2>
    <p id="nowSummary"></p>
    <div class="barWrap"><div class="bar"><div class="fill"></div></div></div>
    <div class="metaRow" id="nowMeta"></div>
  </section>

  <section class="next">
    <div><span class="badge todo">PROCHAIN</span> <strong id="nextTitle"></strong></div>
    <p id="nextNote" style="margin:8px 0 0;color:#b7c9d8;font-size:13px"></p>
  </section>

  <div class="controls">
    <input id="q" placeholder="Rechercher une phase, un jalon, un contrat…"/>
    <select id="statusFilter">
      <option value="">Tous les statuts</option>
      <option>VALIDÉ</option>
      <option>TERMINÉ</option>
      <option>EN COURS</option>
      <option>PARTIEL</option>
      <option>À CONCEVOIR</option>
      <option>À FAIRE</option>
      <option>SUSPENDU</option>
      <option>BLOQUÉ</option>
      <option>NON DÉFINI</option>
    </select>
    <select id="horizonFilter">
      <option value="">Tous les horizons</option>
      <option>Acquis</option>
      <option>Actuel</option>
      <option>Prochain</option>
      <option>Après validation</option>
      <option>À planifier</option>
      <option>Phase ultérieure</option>
    </select>
  </div>

  <div class="tabs">
    <button class="tab on" data-view="all">Vue globale</button>
    <button class="tab" data-view="now">Maintenant</button>
    <button class="tab" data-view="next">Prochain</button>
  </div>

  <div id="phases"></div>

  <p class="note" id="genInfo"></p>
  <footer>
    <span>Phases terminées / validées (approx.) : ${doneish}/${phases.length} (${pct}%)</span>
    <span>Ne confond pas avec la Roadmap S3 (cohorte T1–T9)</span>
  </footer>
</div>
<script>
const DATA = ${payload};
const root = document.getElementById('phases');
document.getElementById('nowSummary').textContent = DATA.now.summary || '';
document.getElementById('nowMeta').innerHTML = [
  ['Conception', DATA.now.conception],
  ['Réalisation', DATA.now.realisation],
  ['Validation', DATA.now.validation],
  ['Contrats', (DATA.now.contracts_validated||'?') + '/' + (DATA.now.contracts_required||'?')],
  ['S3 Cas A', DATA.now.s3_case_a],
  ['Case B', DATA.now.case_b],
  ['Design Gate', DATA.now.design_gate],
  ['ODC-F1', DATA.now.odc_f1],
].map(([k,v]) => '<span class="badge '+statusClass(v)+'">'+k+': '+esc(v)+'</span>').join('');
document.getElementById('nextTitle').textContent = DATA.next.title || '';
document.getElementById('nextNote').textContent = DATA.next.note || '';
document.getElementById('genInfo').textContent =
  'Généré le ' + (DATA.generation?.generatedAt || '') +
  ' · MD ' + (DATA.generation?.mdHash || '').slice(0,12) +
  ' · HEAD ' + (DATA.generation?.git || '') +
  ' · v' + (DATA.meta.version || '');

function statusClass(s){
  const u = String(s||'').toUpperCase();
  if (u.includes('VALIDÉ') || u === 'TERMINÉ' || u === 'PASS') return 'ok';
  if (u.includes('COURS') || u.includes('PARTIEL')) return 'wip';
  if (u.includes('SUSPEND') || u.includes('BLOQU')) return 'stop';
  if (u.includes('CONCEVOIR') || u.includes('FAIRE') || u.includes('PLAN') || u.includes('REFAIRE')) return 'todo';
  if (u.includes('INVALID') || u.includes('ABANDON')) return 'bad';
  return 'muted';
}
function esc(s){return String(s??'').replace(/[&<>"]/g,c=>({ '&':'&amp;','<':'&lt;','>':'&gt;','"':'&quot;' }[c]));}

let view = 'all';
document.querySelectorAll('.tab').forEach(btn => {
  btn.onclick = () => {
    document.querySelectorAll('.tab').forEach(b => b.classList.remove('on'));
    btn.classList.add('on');
    view = btn.dataset.view;
    render();
  };
});
['q','statusFilter','horizonFilter'].forEach(id => {
  document.getElementById(id).addEventListener('input', render);
  document.getElementById(id).addEventListener('change', render);
});

function render(){
  const q = document.getElementById('q').value.trim().toLowerCase();
  const st = document.getElementById('statusFilter').value;
  const hz = document.getElementById('horizonFilter').value;
  root.innerHTML = '';
  for (const p of DATA.phases) {
    if (view === 'now' && !['Actuel','Acquis'].includes(p.horizon) && p.status !== 'EN COURS' && p.status !== 'PARTIEL') continue;
    if (view === 'next' && p.horizon !== 'Prochain' && p.id !== 'P2' && p.id !== 'P4') continue;
    if (hz && p.horizon !== hz) continue;
    if (st && p.status !== st && !(p.jalons||[]).some(j => j.status === st)) continue;
    const blob = (p.id+' '+p.title+' '+p.status+' '+(p.jalons||[]).map(j=>j.title+' '+j.status).join(' ')).toLowerCase();
    if (q && !blob.includes(q)) continue;

    const el = document.createElement('article');
    el.className = 'phase' + (view !== 'all' || p.horizon === 'Actuel' || p.horizon === 'Prochain' ? ' open' : '');
    const jalonsHtml = (p.jalons||[]).map(j => {
      if (st && j.status !== st && p.status !== st) return '';
      const works = (j.works||[]).map(w => '<li>'+esc(w.title)+' <span class="badge '+statusClass(w.status)+'">'+esc(w.status)+'</span></li>').join('');
      return '<div class="jalon"><h4>'+esc(j.id)+' — '+esc(j.title)+
        ' <span class="badge '+statusClass(j.status)+'">'+esc(j.status)+'</span></h4>'+
        (j.note ? '<p>'+esc(j.note)+'</p>' : '')+
        '<div class="detail">Prérequis: '+esc(j.depends||'—')+' · Débloque: '+esc(j.unlocks||'—')+
        '<br/>Sources: '+esc(j.sources||'—')+'</div>'+
        (works ? '<ul class="works">'+works+'</ul>' : '')+
        '</div>';
    }).join('');
    el.innerHTML =
      '<header><div><h3>'+esc(p.id)+' — '+esc(p.title)+'</h3>'+
      '<p class="sub">Horizon: '+esc(p.horizon||'—')+' · Dépend: '+esc(p.depends||'—')+' · Débloque: '+esc(p.unlocks||'—')+'</p></div>'+
      '<span class="badge '+statusClass(p.status)+'">'+esc(p.status)+'</span></header>'+
      '<div class="body">'+jalonsHtml+
      '<div class="detail">Sources phase: '+esc(p.sources||'—')+'</div></div>';
    el.querySelector('header').onclick = () => el.classList.toggle('open');
    root.appendChild(el);
  }
}
render();
</script>
</body>
</html>
`;
}

function main() {
  if (!fs.existsSync(MD_PATH)) {
    console.error('Missing SoT:', MD_PATH);
    process.exit(1);
  }
  const md = fs.readFileSync(MD_PATH, 'utf8');
  const mdHash = createHash('sha256').update(md).digest('hex');
  const parsed = parseMarkdown(md);
  const generatedAt = new Date().toISOString();
  const git = gitShort();

  const data = {
    meta: parsed.meta,
    now: parsed.now,
    next: parsed.next,
    phases: parsed.phases,
    generation: {
      generatedAt,
      mdHash,
      git,
      source: 'ROADMAP/GardenFervor_ROADMAP.md',
      generator: 'ROADMAP/scripts/buildRoadmap.mjs',
    },
    parseIssues: parsed.issues,
  };

  fs.mkdirSync(path.join(ROOT, 'data'), { recursive: true });
  fs.writeFileSync(path.join(ROOT, 'data', 'roadmap.data.json'), `${JSON.stringify(data, null, 2)}\n`);
  const html = buildHtml(data);
  fs.writeFileSync(path.join(ROOT, 'GardenFervor_ROADMAP.html'), html);

  // Mirror for react folder (presentation shell pointer)
  fs.writeFileSync(
    path.join(ROOT, 'react', 'README.md'),
    `# React / vue Roadmap\n\nLa vue interactive est **générée** depuis \`../GardenFervor_ROADMAP.md\` vers \`../GardenFervor_ROADMAP.html\`.\n\nAucune dépendance React/npm dédiée n’est installée : la page autonome évite une seconde architecture frontend.\n\nPour régénérer :\n\n\`\`\`bash\nnode ROADMAP/scripts/buildRoadmap.mjs\n\`\`\`\n`,
  );

  console.log('Roadmap build complete');
  console.log(`  phases=${data.phases.length}`);
  console.log(`  jalons=${data.phases.reduce((n, p) => n + (p.jalons?.length || 0), 0)}`);
  console.log(`  mdHash=${mdHash.slice(0, 12)}`);
  console.log(`  git=${git}`);
  if (parsed.issues.length) {
    console.log('Parse issues:');
    for (const i of parsed.issues) console.log(' ', i);
  }
}

main();
