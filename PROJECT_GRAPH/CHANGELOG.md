# PROJECT_GRAPH — CHANGELOG

## 2026-10-10 — 1.0.7 — Clôture C-20 VALIDÉ

- Nœud `c_20` : documentStatus **VALIDÉ** (conception) ; HUD = dette ; ≠ UX produit / HUD DG-13.
- Compteur canonique **15 / 16**. C-21 demeure NON COMMENCÉ.
- Aucune implémentation UX.

## 2026-10-10 — 1.0.6 — Clôture C-19 VALIDÉ

- Nœud `c_19` : documentStatus **VALIDÉ** (conception) ; persist OFF ; ≠ flags / SaveGame / F1.
- Compteur canonique **14 / 16**. C-20 demeure NON COMMENCÉ.
- Aucune implémentation persist runtime.

## 2026-10-10 — 1.0.5 — Clôture C-18 VALIDÉ

- Nœud `c_18` : documentStatus **VALIDÉ** (conception) ; Ages / `RequiredAge` / FWSG = legacy ; ≠ runtime DG-07.
- Compteur canonique **13 / 16**. C-19 demeure NON COMMENCÉ.
- Aucune implémentation de recherche ni déblocage DG-07.

## 2026-10-10 — 1.0.4 — Alignement C-16/C-17 VALIDÉ · C-18 DRAFT

- Nœuds `c_16` / `c_17` : documentStatus **VALIDÉ** (conception) ; fichiers référencés. C-17 noté **non suivi Git**.
- Nœud `c_18` : documentStatus **REVUE** · fichier `C-18_TECHNOLOGIE_PROGRESSION.md` · DRAFT non validé · Ages = legacy.
- DEPENDS_ON registre : C-14←C-02/C-05/C-12 · C-15/C-16←C-01/C-02 · C-17←C-15/C-16/C-01 · C-18←C-00/C-03\*.
- Aucune implémentation écologique ni déblocage DG-07. Addenda fermés inchangés.

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
