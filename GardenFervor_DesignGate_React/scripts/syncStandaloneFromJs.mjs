/**
 * Sync standalone HTML + designGate.data.json from src/data/designGate.js
 * Usage: node scripts/syncStandaloneFromJs.mjs
 * Source of truth: designGate.js only.
 */
import fs from 'fs';
import path from 'path';
import { fileURLToPath, pathToFileURL } from 'url';

const __dirname = path.dirname(fileURLToPath(import.meta.url));
const root = path.resolve(__dirname, '..');
const jsPath = path.join(root, 'src', 'data', 'designGate.js');
const htmlPath = path.join(root, 'GardenFervor_DESIGN_GATE_v0.1.html');
const jsonPath = path.join(root, 'designGate.data.json');

const mod = await import(pathToFileURL(jsPath).href);
const { DESIGN_GATE, STATUS_META, getSectionStats, toMarkdown } = mod;

function serializeGate(gate) {
  return {
    version: gate.version,
    title: gate.title,
    principles: gate.principles,
    sections: gate.sections.map((section) => ({
      id: section.id,
      code: section.code,
      title: section.title,
      ...(section.status != null ? { status: section.status } : {}),
      goal: section.goal,
      tags: section.tags ?? [],
      dependsOn: section.dependsOn ?? [],
      impacts: section.impacts ?? [],
      items: section.items.map((i) => {
        const out = {
          id: i.id,
          code: i.code,
          title: i.title,
          status: i.status,
          subpoints: i.subpoints ?? [],
          dependsOn: i.dependsOn ?? [],
          impacts: i.impacts ?? []
        };
        if (i.decision != null) out.decision = i.decision;
        if (i.question != null) out.question = i.question;
        if (i.example != null) out.example = i.example;
        if (i.rationale != null) out.rationale = i.rationale;
        return out;
      })
    })),
    validationRules: gate.validationRules,
    outOfScope: gate.outOfScope
  };
}

const payload = {
  STATUS_META,
  DESIGN_GATE: serializeGate(DESIGN_GATE)
};

const jsonText = JSON.stringify(payload, null, 2) + '\n';
fs.writeFileSync(jsonPath, jsonText, 'utf8');

let html = fs.readFileSync(htmlPath, 'utf8');
const startMarker = '<script id="data" type="application/json">';
const start = html.indexOf(startMarker);
if (start < 0) {
  console.error('ERROR: data script block not found in HTML');
  process.exit(1);
}
const jsonStart = start + startMarker.length;
const end = html.indexOf('</script>', jsonStart);
if (end < 0) {
  console.error('ERROR: closing script tag not found');
  process.exit(1);
}

const pretty = JSON.stringify(payload, null, 2);
html = html.slice(0, jsonStart) + '\n' + pretty + '\n' + html.slice(end);
fs.writeFileSync(htmlPath, html, 'utf8');

// Validate round-trip
const html2 = fs.readFileSync(htmlPath, 'utf8');
const s = html2.indexOf(startMarker) + startMarker.length;
const e = html2.indexOf('</script>', s);
const parsed = JSON.parse(html2.slice(s, e));
const flatJs = DESIGN_GATE.sections.flatMap((sec) => sec.items);
const flatHtml = parsed.DESIGN_GATE.sections.flatMap((sec) => sec.items);
const counts = (items) =>
  items.reduce((a, i) => {
    a[i.status] = (a[i.status] || 0) + 1;
    return a;
  }, {});

const rulesJs = DESIGN_GATE.validationRules;
const rulesHtml = parsed.DESIGN_GATE.validationRules;

console.log(
  JSON.stringify(
    {
      ok:
        DESIGN_GATE.sections.length === parsed.DESIGN_GATE.sections.length &&
        flatJs.length === flatHtml.length &&
        JSON.stringify(counts(flatJs)) === JSON.stringify(counts(flatHtml)) &&
        rulesJs.length === rulesHtml.length &&
        rulesJs.every((r, i) => r === rulesHtml[i]),
      sections: { js: DESIGN_GATE.sections.length, html: parsed.DESIGN_GATE.sections.length },
      items: { js: flatJs.length, html: flatHtml.length },
      statusCounts: { js: counts(flatJs), html: counts(flatHtml) },
      validationRules: { js: rulesJs.length, html: rulesHtml.length },
      markdownBytes: toMarkdown(DESIGN_GATE).length,
      getSectionStatsSample: getSectionStats(DESIGN_GATE.sections[0])
    },
    null,
    2
  )
);
