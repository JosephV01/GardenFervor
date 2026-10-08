# PROJECT_GRAPH — CHANGELOG

## 2026-10-08 — 1.0.1 — Clôture C-04

- Nœud `c_04` : documentStatus **VALIDÉ** · fichier contrat référencé.
- Relation `c_04 → sys_task` : confiance HIGH (contrat VALIDÉ).
- Relation FUTURE `c_02 → c_04` : frontière G4 contractuelle ; runtime encore dette.
- Régénération JSON / vues / HTML / CURRENT_STATE.

## 2026-10-08 — 1.0.0 — Création initiale

- Création du dossier `PROJECT_GRAPH/` (absent auparavant).
- Graine curatée `scripts/curatedGraph.mjs` (systèmes, contrats C-00…C-23, DG, preuves ODC-F1…F8, cohorte S3, M4/UDS).
- Générateur `buildProjectGraph.mjs` : scan dépôt, anomalies, JSON, 7 vues Mermaid, HTML interactif, `CURRENT_STATE.md`.
- Validateur `validateProjectGraph.mjs`.
- Documentation `README.md`.
- Aucune modification hors `PROJECT_GRAPH/`.
