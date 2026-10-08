#!/usr/bin/env node
/**
 * Validate generated Project Graph artifacts.
 * Run: node PROJECT_GRAPH/scripts/validateProjectGraph.mjs
 */

import fs from 'fs';
import path from 'path';
import { fileURLToPath } from 'url';

const __dirname = path.dirname(fileURLToPath(import.meta.url));
const GRAPH_ROOT = path.resolve(__dirname, '..');
const REPO_ROOT = path.resolve(GRAPH_ROOT, '..');

const REQUIRED = [
  'data/projectGraph.data.json',
  'GardenFervor_ProjectGraph.html',
  'CURRENT_STATE.md',
  'README.md',
  'graph/GardenFervor_ProjectGraph.mmd',
  'graph/GardenFervor_SystemsGraph.mmd',
  'graph/GardenFervor_RulesGraph.mmd',
  'graph/GardenFervor_DataFlowGraph.mmd',
  'graph/GardenFervor_ExecutionGraph.mmd',
  'graph/GardenFervor_ValidationGraph.mmd',
  'graph/GardenFervor_ExternalGraph.mmd',
];

const RELATION_TYPES = new Set([
  'DEPENDS_ON', 'OWNS', 'PRODUCES', 'CONSUMES', 'READS', 'WRITES', 'EXECUTES',
  'SIGNALS', 'INVALIDATES', 'PERSISTS', 'VALIDATES', 'GOVERNS', 'CONSTRAINS',
  'VISUALIZES', 'INTEGRATES_WITH',
]);

let errors = 0;
let warnings = 0;

function fail(msg) {
  console.error(`FAIL: ${msg}`);
  errors += 1;
}
function warn(msg) {
  console.warn(`WARN: ${msg}`);
  warnings += 1;
}
function ok(msg) {
  console.log(`OK: ${msg}`);
}

function main() {
  for (const rel of REQUIRED) {
    const p = path.join(GRAPH_ROOT, rel);
    if (!fs.existsSync(p)) fail(`missing ${rel}`);
    else ok(`present ${rel}`);
  }

  const dataPath = path.join(GRAPH_ROOT, 'data/projectGraph.data.json');
  if (!fs.existsSync(dataPath)) {
    console.error('Cannot continue without data JSON');
    process.exit(1);
  }

  let data;
  try {
    data = JSON.parse(fs.readFileSync(dataPath, 'utf8'));
    ok('JSON parse');
  } catch (e) {
    fail(`JSON invalid: ${e.message}`);
    process.exit(1);
  }

  if (!Array.isArray(data.nodes) || !Array.isArray(data.edges)) {
    fail('nodes/edges must be arrays');
  }

  const ids = new Set();
  for (const n of data.nodes || []) {
    if (!n.id) fail('node without id');
    if (ids.has(n.id)) fail(`duplicate node id ${n.id}`);
    ids.add(n.id);
    if (!n.category) fail(`node ${n.id} missing category`);
    if (!n.confidence) warn(`node ${n.id} missing confidence`);
  }

  for (const e of data.edges || []) {
    if (!ids.has(e.from)) fail(`edge ${e.id} from missing node ${e.from}`);
    if (!ids.has(e.to)) fail(`edge ${e.id} to missing node ${e.to}`);
    if (!RELATION_TYPES.has(e.type)) fail(`edge ${e.id} invalid type ${e.type}`);
    if (!e.source) warn(`edge ${e.id} missing source`);
    if (!e.confidence) warn(`edge ${e.id} missing confidence`);
  }

  // Mermaid basic sanity
  for (const f of REQUIRED.filter((r) => r.endsWith('.mmd'))) {
    const text = fs.readFileSync(path.join(GRAPH_ROOT, f), 'utf8');
    if (!text.includes('flowchart')) fail(`${f} missing flowchart`);
    else ok(`mermaid ${path.basename(f)}`);
  }

  // HTML
  const html = fs.readFileSync(path.join(GRAPH_ROOT, 'GardenFervor_ProjectGraph.html'), 'utf8');
  if (!html.includes('const DATA =')) fail('HTML missing embedded DATA');
  else ok('HTML embeds DATA');
  if (!html.includes('<canvas')) fail('HTML missing canvas');
  else ok('HTML has canvas');

  // Architectural coherence checks (signal only)
  const byId = Object.fromEntries((data.nodes || []).map((n) => [n.id, n]));
  if (byId.c_01?.documentStatus !== 'VALIDÉ') warn('C-01 expected VALIDÉ in suivi');
  if (byId.c_02?.documentStatus !== 'VALIDÉ') warn('C-02 expected VALIDÉ in suivi');
  if (byId.c_04?.documentStatus !== 'VALIDÉ') warn('C-04 expected VALIDÉ');
  if (byId.c_05?.documentStatus !== 'VALIDÉ') warn('C-05 expected VALIDÉ');
  if (byId.c_03 && byId.c_03.documentStatus !== 'NON COMMENCÉ') warn('C-03 expected closed (NON COMMENCÉ)');
  if (!byId.sys_runtime_store) fail('missing sys_runtime_store');
  if (!byId.sys_spatial) fail('missing sys_spatial');
  if (!byId.sys_task) fail('missing sys_task');
  if (byId.sys_case_b?.implementationStatus !== 'SUSPENDED') warn('Case B expected SUSPENDED');

  // Ensure generator did not claim to write outside PROJECT_GRAPH (soft check: no path write list)
  ok(`nodes=${data.nodes.length} edges=${data.edges.length}`);
  if (Array.isArray(data.anomalies) && data.anomalies.length) {
    warn(`data.anomalies count=${data.anomalies.length}`);
  }

  console.log('');
  console.log(`Validation finished: errors=${errors} warnings=${warnings}`);
  process.exit(errors > 0 ? 1 : 0);
}

main();
