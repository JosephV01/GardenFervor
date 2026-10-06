/**
 * Sync index.html + roadmap.data.json from src/roadmap.data.js
 * Usage (from repo root or this folder):
 *   node "Plan de production/Roadmap/scripts/syncRoadmap.mjs"
 * Source of truth: src/roadmap.data.js only.
 * HTML view MUST remain named index.html (GitHub Pages / online).
 */
import fs from 'fs';
import path from 'path';
import { fileURLToPath, pathToFileURL } from 'url';

const __dirname = path.dirname(fileURLToPath(import.meta.url));
const root = path.resolve(__dirname, '..');
const jsPath = path.join(root, 'src', 'roadmap.data.js');
const htmlPath = path.join(root, 'index.html');
const jsonPath = path.join(root, 'roadmap.data.json');

const mod = await import(pathToFileURL(jsPath).href + `?t=${Date.now()}`);
const payload = mod.serializeRoadmap();
const pretty = JSON.stringify(payload, null, 2) + '\n';

fs.writeFileSync(jsonPath, pretty, 'utf8');

if (!fs.existsSync(htmlPath)) {
  console.error('ERROR: HTML shell missing:', htmlPath);
  process.exit(1);
}

let html = fs.readFileSync(htmlPath, 'utf8');
const startMarker = '<script id="roadmap-data" type="application/json">';
const start = html.indexOf(startMarker);
if (start < 0) {
  console.error('ERROR: roadmap-data script block not found in HTML');
  process.exit(1);
}
const jsonStart = start + startMarker.length;
const end = html.indexOf('</script>', jsonStart);
if (end < 0) {
  console.error('ERROR: closing script tag not found');
  process.exit(1);
}

html = html.slice(0, jsonStart) + '\n' + pretty + html.slice(end);
fs.writeFileSync(htmlPath, html, 'utf8');

const p = payload.progress;
console.log(`Roadmap synced · ${p.done}/${p.total} VALIDÉ (${p.percent}%) · next=${payload.meta.nextSliceId}`);
