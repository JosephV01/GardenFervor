# Investor Demo — Architecture (étape 1)

## Dépôt inspecté

| Élément | Valeur réelle |
| --- | --- |
| Racine | `C:\Users\sahel\Documents\Unreal Projects\GardenFervor` |
| Remote | `https://github.com/JosephV01/GardenFervor.git` |
| Carte jeu | `/Game/GardenFervor/Maps/GardenFervorIsland` (`Content/GardenFervor/Maps/`) |
| Roadmap SoT | `Plan de production/Roadmap/src/roadmap.data.js` |
| État S3 | **T1→T9 VALIDÉ · 9/9 · 100 % · nextSliceId = null** |

## Couches

```text
┌─────────────────────────────────────────┐
│  Investor Demo (présentation)           │
│  README · Documentation · Presentation  │
│  futurs : Scenes / Placeholders visuels │
└──────────────────┬──────────────────────┘
                   │ observe / déclenche (futur)
                   ▼
┌─────────────────────────────────────────┐
│  Systèmes GardenFervor validés (T1–T9)  │
│  Project · Task · UnitTaskAgent · PE    │
│  Cohort stocks / service / C6           │
└─────────────────────────────────────────┘
```

## Interdits structurels

- Dupliquer PhysicalEconomy, Project, Task ou stocks dans `Investor Demo/`
- Compteur miroir Timber / faux Complete / faux En service
- Seconde Roadmap concurrente
- Modification Design Gate ou statuts T1→T9 pour besoin démo
- Terraform obligatoire pour Cas A (la démo suit Cas A : site déjà prêt)

## Point d’ancrage technique (référence, non rebranché à l’étape 1)

| Contrat | Ancrage réel (Source) |
| --- | --- |
| T1 Timber | `GardenFervorPhysicalResourceTypes` |
| T2 ResourceKey | `FGardenFervorTaskRecord::OperationalResourceKey` |
| T3 U1/U2/U3 | `GardenFervorUnitCapabilityTypes` |
| T4 Stocks A/B | `GardenFervorCohortStockHelpers` (`LinkedPitStockId` = A) |
| T5 WorkSite | `ExpandWorkSite` + SitePrep `AlreadyReady` |
| T6 Intention | `CreateProjectFromIntention` |
| T7 Service | `GardenFervorRefreshCohortServiceState` |
| T8 Obs. | `GardenFervorCohortObservabilityHelpers` |
| T9 Chaîne | `SmokeDemonstrateCohortS3Near` / `gf.Project.SmokeCohortS3` |

## Note stocks

`LinkedPitStockId` = identité Stock A PE de cohorte.  
Risque sémantique Pit/LevelPad documenté en Roadmap — **ne pas renommer** dans la couche démo.

## Étape 2 — scène visuelle VALIDÉE

| Élément | Emplacement |
| --- | --- |
| Map | `/Game/GardenFervor/InvestorDemo/L_InvestorDemo_S3` |
| Materials PH | `/Game/GardenFervor/InvestorDemo/Materials/` |
| Caméra | `Demo_PlayerStart_Overview` + GameMode → `AGardenFervorStrategyPawn` |
| Validation | Humaine — chaîne Intention→…→En service lisible |

Aucun système T1→T9 n’est invoqué par la scène à l’étape 2.  
Script générateur temporaire supprimé après validation.  
Polish futur : `TextRender` parfois inversés selon la vue (non bloquant).
