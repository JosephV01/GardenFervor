# PROJECT_GRAPH — CHANGELOG

## 2026-10-10 — 1.0.3 — Clôture C-15

- Nœud `c_15` : documentStatus **VALIDÉ** · fichier `CONTRATS/C-15_HYDROLOGIE.md`.
- C-16 demeure NON COMMENCÉ. Aucune implémentation hydrologique.
- Régénération JSON / vues / HTML / CURRENT_STATE.

## 2026-10-08 — 1.0.2 — Clôture C-05

- Nœud `c_05` : documentStatus **VALIDÉ** · fichier `CONTRATS/C-05_WORKSITE_SITEPREP.md`.
- Relation `c_05 → sys_siteprep` : confiance HIGH (contrat VALIDÉ).
- Frontière `c_04 ↔ c_05` : notes mises à jour (plus FUTURE).

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
