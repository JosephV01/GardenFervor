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

## Étape 2B — versionnement Git

| Élément | Décision |
| --- | --- |
| Stratégie | Blobs Git standards sous `Content/GardenFervor/InvestorDemo/` uniquement |
| Git LFS | Absent du dépôt · **non activé** (tailles trop faibles pour le justifier) |
| `.gitignore` | Aucune exclusion de `Content/` · aucune règle générale Content ajoutée |
| `.gitattributes` | Aucun · non nécessaire |
| Reproductibilité | clone → ouvrir `L_InvestorDemo_S3` · meshes = Engine BasicShapes |

## P0 — isolement runtime = VALIDÉ

| Élément | Valeur |
| --- | --- |
| Statut | **VALIDÉ** (validation humaine PIE confirmée) |
| GameMode | `AGardenFervorInvestorDemoGameMode` (opérationnel) |
| PlayerController | `AGardenFervorInvestorDemoPlayerController` |
| Pawn | `AGardenFervorStrategyPawn` (réutilisé) |
| Binding | `Config/DefaultEngine.ini` → `+GameModeMapPrefixes=(Prefix="L_InvestorDemo",…)` |
| Island | `AGardenFervorGameMode` **inchangé** |

**Absents du boot Demo (confirmés en PIE) :** TC · Worker · ResourceNodes · init FWSG · Ages · HUD FWSG · BuildMenu · LevelPad · BeginPlace.  
**Inchangés :** T1→T9 · Design Gate · Roadmap T1→T9.  
**Étape 3 :** **VALIDÉ** — `FGardenFervorInvestorDemoS3Bridge` + `AGardenFervorInvestorDemoS3Director` · `gf.InvestorDemo.RunS3` / F8 · APIs T1→T9 réelles · Case A sans Terraform · validation humaine PIE **PASS**.  
**Étape 4 :** **VALIDÉ** — caméra guidée · 10 beats · UI légère (carte haut-gauche) · pauses · conclusion · correctif overlay · validation humaine **PASS**. Gameplay T1→T9 inchangé.  
**Étape 5 :** **VALIDÉ** — narration accessible · cause/action/résultat · autonomie mise en évidence · bouton **LANCER LA DÉMONSTRATION** → `RunS3CasA` · one-shot · validation humaine **PASS**.  
**Git LFS :** `L_InvestorDemo_S3.umap` tracké spécifiquement (pas `*.umap` global).  
Helper éditeur optionnel : `Content/Python/set_investor_demo_gamemode.py`.
