#!/usr/bin/env node
/**
 * Validate Roadmap SoT + generated artifacts.
 * Usage: node ROADMAP/scripts/validateRoadmap.mjs
 */

import fs from 'fs';
import path from 'path';
import { fileURLToPath } from 'url';
import { createHash } from 'crypto';

const __dirname = path.dirname(fileURLToPath(import.meta.url));
const ROOT = path.resolve(__dirname, '..');
const REPO = path.resolve(ROOT, '..');

const REQUIRED_STATUSES = new Set([
  'VALIDÉ', 'TERMINÉ', 'EN COURS', 'À CONCEVOIR', 'À FAIRE', 'BLOQUÉ',
  'SUSPENDU', 'ABANDONNÉ', 'NON DÉFINI', 'PARTIEL',
]);

let errors = 0;
let warnings = 0;
function fail(m) { console.error('FAIL:', m); errors += 1; }
function warn(m) { console.warn('WARN:', m); warnings += 1; }
function ok(m) { console.log('OK:', m); }

function main() {
  const mdPath = path.join(ROOT, 'GardenFervor_ROADMAP.md');
  const htmlPath = path.join(ROOT, 'GardenFervor_ROADMAP.html');
  const dataPath = path.join(ROOT, 'data', 'roadmap.data.json');

  if (!fs.existsSync(mdPath)) fail('missing GardenFervor_ROADMAP.md');
  else ok('SoT markdown present');
  if (!fs.existsSync(htmlPath)) fail('missing GardenFervor_ROADMAP.html — run build');
  else ok('HTML present');
  if (!fs.existsSync(dataPath)) fail('missing data/roadmap.data.json — run build');
  else ok('JSON present');

  if (!fs.existsSync(dataPath)) {
    console.log(`Validation finished: errors=${errors}`);
    process.exit(1);
  }

  const data = JSON.parse(fs.readFileSync(dataPath, 'utf8'));
  const md = fs.readFileSync(mdPath, 'utf8');
  const hash = createHash('sha256').update(md).digest('hex');
  if (data.generation?.mdHash !== hash) {
    fail('HTML/JSON hash does not match current Markdown — rebuild required');
  } else ok('generation hash matches Markdown');

  if (!data.meta?.version) fail('meta.version missing');
  if (!data.now?.summary) fail('now.summary missing');
  if (!data.next?.id) fail('next.id missing');
  if (!Array.isArray(data.phases) || data.phases.length < 5) fail('too few phases');

  const ids = new Set();
  for (const p of data.phases) {
    if (!p.id) fail('phase without id');
    if (ids.has(p.id)) fail(`duplicate phase ${p.id}`);
    ids.add(p.id);
    if (!REQUIRED_STATUSES.has(p.status) && p.status !== 'PARTIEL') {
      warn(`phase ${p.id} unusual status: ${p.status}`);
    }
    for (const j of p.jalons || []) {
      if (!j.id) fail(`jalon without id in ${p.id}`);
      if (ids.has(j.id)) fail(`duplicate jalon ${j.id}`);
      ids.add(j.id);
      if (j.phase && j.phase !== p.id) warn(`jalon ${j.id} phase attr ${j.phase} != ${p.id}`);
    }
  }

  const html = fs.readFileSync(htmlPath, 'utf8');
  if (!html.includes('const DATA =')) fail('HTML missing embedded DATA');
  else ok('HTML embeds DATA');
  if (!html.includes('Source de vérité')) warn('HTML missing SoT reminder');

  // Cross-checks against repo docs (signal only)
  const suivi = fs.existsSync(path.join(REPO, 'CONTRATS/00_SUIVI_CONTRATS.md'))
    ? fs.readFileSync(path.join(REPO, 'CONTRATS/00_SUIVI_CONTRATS.md'), 'utf8')
    : '';
  if (suivi.includes('C-01') && suivi.includes('**VALIDÉ**')) {
    const c01 = data.phases.flatMap((p) => p.jalons || []).find((j) => j.id === 'P2.J1');
    if (c01 && c01.status !== 'VALIDÉ') fail('Roadmap C-01 jalon not VALIDÉ but suivi says VALIDÉ');
    else ok('C-01 status coherent with suivi');
  }
  if (suivi.includes('C-02') && /C-02[\s\S]{0,200}\*\*VALIDÉ\*\*/.test(suivi)) {
    const c02 = data.phases.flatMap((p) => p.jalons || []).find((j) => j.id === 'P2.J2');
    if (c02 && c02.status !== 'VALIDÉ') fail('Roadmap C-02 jalon not VALIDÉ but suivi says VALIDÉ');
    else ok('C-02 status coherent with suivi');
  }

  const caseB = data.phases.flatMap((p) => p.jalons || []).find((j) => j.id === 'P1.J2');
  if (caseB && caseB.status !== 'SUSPENDU') warn('Case B expected SUSPENDU');
  else ok('Case B SUSPENDU');

  if (data.next?.id !== 'next-c18') warn(`next expected next-c18, got ${data.next?.id}`);
  else ok('next work is C-18 DRAFT / REVUE');

  if ((data.parseIssues || []).length) {
    for (const i of data.parseIssues) warn(`parse issue: ${i}`);
  }

  console.log('');
  console.log(`phases=${data.phases.length} jalons=${data.phases.reduce((n, p) => n + (p.jalons?.length || 0), 0)}`);
  console.log(`Validation finished: errors=${errors} warnings=${warnings}`);
  process.exit(errors > 0 ? 1 : 0);
}

main();
