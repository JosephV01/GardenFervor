/**
 * Sync roadmap HTML + JSON from src/roadmap.data.js
 * Usage:
 *   node "Plan de production/Roadmap/scripts/syncRoadmap.mjs"
 *
 * Source of truth (edit only): src/roadmap.data.js
 *
 * Outputs:
 *   - Plan de production/Roadmap/index.html  (working view)
 *   - Plan de production/Roadmap/roadmap.data.json
 *   - docs/roadmap.html                       (GitHub Pages — roadmap published page)
 *
 * Note: docs/index.html is the documentation hub (not overwritten by this sync).
 */
import fs from 'fs';
import path from 'path';
import { fileURLToPath, pathToFileURL } from 'url';

const __dirname = path.dirname(fileURLToPath(import.meta.url));
const roadmapRoot = path.resolve(__dirname, '..');
const repoRoot = path.resolve(roadmapRoot, '..', '..');
const jsPath = path.join(roadmapRoot, 'src', 'roadmap.data.js');
const htmlShellPath = path.join(roadmapRoot, 'index.html');
const jsonPath = path.join(roadmapRoot, 'roadmap.data.json');
const pagesHtmlPath = path.join(repoRoot, 'docs', 'roadmap.html');

const mod = await import(pathToFileURL(jsPath).href + `?t=${Date.now()}`);
const payload = mod.serializeRoadmap();
const pretty = JSON.stringify(payload, null, 2) + '\n';

fs.writeFileSync(jsonPath, pretty, 'utf8');

if (!fs.existsSync(htmlShellPath)) {
  console.error('ERROR: HTML shell missing:', htmlShellPath);
  process.exit(1);
}

let html = fs.readFileSync(htmlShellPath, 'utf8');
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
fs.writeFileSync(htmlShellPath, html, 'utf8');

fs.mkdirSync(path.dirname(pagesHtmlPath), { recursive: true });
fs.writeFileSync(pagesHtmlPath, html, 'utf8');

const p = payload.progress;
console.log(
  `Roadmap synced · ${p.done}/${p.total} VALIDÉ (${p.percent}%) · next=${payload.meta.nextSliceId}`,
);
console.log(`Working: ${htmlShellPath}`);
console.log(`Pages:   ${pagesHtmlPath}`);
