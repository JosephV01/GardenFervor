# PROJECT_GRAPH — CURRENT_STATE

Généré : **2026-10-10T15:11:06.165Z**
HEAD : `b0c3367c3453da96df39d3fba3988e9b31839ffb` (dirty, 89 fichiers dirty)
Curated schema : `1.0.0`

## Inventaire

| Métrique | Valeur |
| --- | ---: |
| Nœuds | 88 |
| Relations | 117 |
| Relations HIGH | 94 |
| Relations MEDIUM | 23 |
| Relations LOW | 0 |
| Relations ACTIVE | 111 |
| Relations FUTURE | 6 |
| Relations UNVERIFIED | 0 |
| Contrats (registre) | 24 |
| Contrats fichiers présents | 14 |
| Preuves inventoriées | 9 |
| Gates Saved détectés | 14 |
| Headers systèmes scannés | 13 |
| Intégrations externes | 4 |

## Catégories

- **BUILDINGS_INFRA** : 3
- **CONTENT_EXTERNAL** : 4
- **CONTRACTS** : 24
- **DATA** : 8
- **DESIGN_GATE** : 10
- **ECONOMY_RESOURCES** : 2
- **GAME_DEMO** : 2
- **GOVERNANCE** : 5
- **PROJECTS_TASKS** : 4
- **SPATIAL** : 1
- **TOOLING** : 3
- **UI_INPUT** : 3
- **UNITS_EXECUTION** : 4
- **VALIDATION** : 9
- **WORLD_TERRAIN** : 6

## Implémentation (nœuds)

- **IMPLEMENTED** : 37
- **LEGACY** : 3
- **PARTIAL** : 27
- **PLANNED** : 3
- **STUB** : 1
- **SUSPENDED** : 2
- **n/a** : 15

## Contrats VALIDÉS (documentaire)

- C-01 — Terrain runtime
- C-02 — Substrat spatial
- C-04 — Tâches / graphe / dépendances
- C-05 — WorkSite / SitePrep
- C-07 — Autonomie unité
- C-08 — Terraformer opérationnel
- C-11 — Réservations
- C-12 — Transport / logistique
- C-14 — Infrastructures
- C-15 — Hydrologie
- C-16 — Sol
- C-17 — Végétation / écosystèmes
- C-18 — Technologie / progression
- C-19 — Persistance / sauvegarde

## Systèmes SUSPENDED / LEGACY / STUB

- **STUB** — DG-09 Environnement / écosystèmes
- **LEGACY** — RuntimeTerraformVisualizer
- **LEGACY** — RuntimeTerraformCollision
- **SUSPENDED** — TerraformSaveGame
- **LEGACY** — EconomyComponent
- **SUSPENDED** — Case B RequiresTerraform

## Anomalies / écarts

- Aucune anomalie structurelle bloquante.

## Avertissements architecturaux

- Aucun.

## Systèmes potentiellement absents du graphe (scan)

- Aucun header Subsystem/RuntimeGate non référencé.

## Sources inspectées

- REGLES_PROJET.md
- ETAT_PROJET.md
- HISTORIQUE_MODIFICATIONS.md
- CONTRATS/
- GardenFervor_DesignGate_React/src/data/designGate.js
- Source/GardenFervor/
- Saved/ODC_*Gate.txt
- GardenFervor.uproject
- Content/
- docs/

## Frontières contractuelles clés (contrôles)

- C-01 = autorité terrain (gouverne Store / contraint Landscape)
- C-02 = référence spatiale (gouverne SpatialSubsystem)
- C-03 = addendum fermé (NON COMMENCÉ)
- C-04 = graphe tâches (contrat VALIDÉ ; runtime TaskSubsystem présent)
- C-05 = SitePrep (contrat VALIDÉ ; helpers présents ; Case B SUSPENDED)
- C-07 = autonomie unité (contrat VALIDÉ ; runtime UnitTaskAgent présent ; dettes documentées)
- C-08 = Terraformer opérationnel (contrat VALIDÉ ; métier formalisé ; runtime partiel ; Case B SUSPENDED)
- C-11 = Réservations (contrat VALIDÉ ; concurrence formalisée ; runtime / preuves multi-chantier partielles)

## Règle

Ce fichier est une **projection**. En cas de conflit : dépôt réel > contrats/règles > preuves > documentation descriptive.
