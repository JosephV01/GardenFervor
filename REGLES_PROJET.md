# GardenFervor — Règles projet & interactions

Document vivant. Toute règle utile au projet ou à la collaboration agent/humain doit y être ajoutée au fil du temps.  
Ce fichier ne remplace pas l’ODC (`GardenFervor_ODC_v1.0`) : il en extrait les contraintes opérationnelles et les règles de travail quotidiennes.

**Statuts :** `VERROUILLÉ` · `VALIDÉ` · `À CONFIRMER` · `CONVENTION`

---

## 0. Comment utiliser ce document

1. Lire avant une tâche non triviale (terrain, M4, cook, gates).
2. En cas de conflit : **ODC (phases techniques) / Design Gate React (règles de gameplay) > ce document > habitudes de session**.  
   Si **Design Gate ≠ implémentation** : ne pas résoudre silencieusement — signaler et trancher avec l’humain.
3. Toute nouvelle règle durable doit être **ajoutée ici** (pas seulement dans le chat).
4. Les preuves de gate restent dans `Saved/ODC_F*_*.txt` ; ce document pointe vers elles.
5. **Toute modification** suit la section **1bis** (état → delta → historique → nouvel état).
6. Mémoire agent : lire `HISTORIQUE_MODIFICATIONS.md` en reprise de contexte.

---

## 1. Interactions agent ↔ humain

| Règle | Statut |
| --- | --- |
| `PROCEDER` = continuer la suite logique déjà validée, sans redemander confirmation | CONVENTION |
| Informer brièvement le résultat d’une tâche (PASS/FAIL + suite), sans long récap | CONVENTION |
| Chaque modification : livrer le **delta humain** (section 1bis), pas seulement « c’est fait » | CONVENTION |
| Après chaque modification : rapport **5 points** AgentRules (modifié / apporte / avant-après / validation humaine / résultat attendu) | VALIDÉ |
| Après travail à impact conception : ligne obligatoire **Design Gate :** `Aucune modification` / `Mis à jour : DG-XX / XX.X` / `Nouveau point à définir : DG-XX / XX.X` | VALIDÉ |
| Ne pas considérer un jalon terminé uniquement parce que ça compile ; validation humaine pour le comportement observable | VALIDÉ |
| Ne pas éditer les fichiers de plan Cursor sauf demande explicite | CONVENTION |
| Ne pas committer / pousser / créer de PR sans demande explicite | CONVENTION |
| Ne pas poser de questions de clarification si la suite est déjà claire dans le contexte | CONVENTION |
| Ajouter ici toute règle d’interaction répétée qui mérite d’être durable | CONVENTION |

---

## 1bis. Processus obligatoire — chaque modification

À suivre **à chaque** changement au projet (code, config, content, cook, gate, doc de règles).  
Objectif : l’humain doit toujours savoir **où on en est** et **ce qui a bougé** entre deux interventions.

### Fichiers d’état / mémoire

| Fichier | Rôle |
| --- | --- |
| `ETAT_PROJET.md` (racine) | Snapshot courant du projet : phase ODC, derniers gates, risques connus, prochain pas |
| `HISTORIQUE_MODIFICATIONS.md` (racine) | Mémoire longue agent : inventaire + historique détaillé validé |
| `GardenFervor_DesignGate_React/src/data/designGate.js` | **Source de vérité conception** (document vivant) |
| `Plan de production/Roadmap/src/roadmap.data.js` | **Source de vérité roadmap de production** (pilotage T1–Tn) |
| `Plan de production/PLAN_PRODUCTION_COHORTE_S3.md` | Plan opérationnel (comment produire la preuve S3) |
| `Saved/ODC_F*_*.txt` | Preuves techniques détaillées (inchangé) |

Roadmap : SoT `Plan de production/Roadmap/src/roadmap.data.js` · sync `node "Plan de production/Roadmap/scripts/syncRoadmap.mjs"` · **publication Pages roadmap = `docs/roadmap.html`**.  
Hub GitHub Pages : **`docs/index.html`** → liens vers roadmap / Design Gate / contrats (`docs/GITHUB_PAGES.md`).  
**Après toute modification documentaire publiée :** `node docs/syncPages.mjs` puis push — tient hub + pages `docs/` à jour.  
**Code terminé ≠ VALIDÉ** : le statut `VALIDÉ` d’une tranche exige la validation humaine du Plan de production.

`ETAT_PROJET.md` est la **baseline** courte entre deux modifications.  
`HISTORIQUE_MODIFICATIONS.md` est la **mémoire complète** : un agent doit pouvoir tout reconstituer sans le chat.

### Contenu minimal de l’état (`ETAT_PROJET.md`)

- **Phase ODC** en cours + dernier gate PASS/FAIL
- **Ce qui fonctionne** (faits prouvés, 3–8 puces max)
- **Ce qui est cassé / risqué** (connu)
- **Prochain pas** attendu
- **Horodatage** de la dernière mise à jour

### Cycle (ordre fixe)

```
1. ÉTAT AVANT   → lire ETAT_PROJET.md + dernière entrée HISTORIQUE_MODIFICATIONS.md
2. INTENTION    → une phrase : pourquoi on touche, critère de succès
3. MODIFICATION → faire le travail (minimal)
4. DELTA HUMAIN → message chat au format ci-dessous (obligatoire)
5. ÉTAT APRÈS   → mettre à jour ETAT_PROJET.md
6. HISTORIQUE   → ajouter une entrée VALIDÉE dans HISTORIQUE_MODIFICATIONS.md (§4)
```

Sans **ÉTAT AVANT** clair, ne pas commencer.  
Sans **DELTA HUMAIN** + **entrée historique** (si modification validée), la modification n’est pas considérée livrée.

### Delta humain (message chat — format obligatoire)

L’humain doit voir le **changement entre avant et après**, pas un journal de travail agent.

```
### Delta
- Avant : <fait pertinent de la baseline>
- Après : <nouveau fait comparable>
- Fichiers / preuves : <chemins clés seulement>
- À vérifier côté humain : <1–3 checks concrets, ou « rien »>
- Suite : <prochain pas>
```

Règles du delta :

| Règle | Statut |
| --- | --- |
| Comparer **Avant / Après** sur les mêmes axes (gate, comportement, config, UI…) | CONVENTION |
| Lister uniquement ce que l’humain doit **remarquer ou retester** | CONVENTION |
| Pas de roman : si rien de visible en jeu, le dire explicitement (« impact config/cook seulement ») | CONVENTION |
| Si échec : delta = Avant → Après (échec) + cause courte + blocage éventuel | CONVENTION |
| Micro-fix typo isolée : delta en 2 lignes OK, mais Avant/Après reste obligatoire | CONVENTION |
| Toute modif validée : entrée append-only dans `HISTORIQUE_MODIFICATIONS.md` | CONVENTION |

### Exemple (réduit)

```
### Delta
- Avant : F2 non clos ; AutoSettings UserSettingsClass encore en erreur packaged
- Après : F2 PASS ; erreur EnhancedInput absente ; VisualGate PASS=1
- Fichiers / preuves : Config/DefaultInput.ini ; Saved/ODC_F2_VisualTerrainGate.txt
- À vérifier côté humain : lancer packaged, confirmer rendu île + ciel/météo
- Suite : ODC-F3 Spatial
```

---

## 2. Documents de référence

| Document | Rôle |
| --- | --- |
| ODC v1.0 (`GardenFervor_ODC_v1.0`) | Document directeur produit / architecture / gates |
| [Doc M4 officielle](https://aaronneal.online/docs/m4/) | Source de vérité Magic Map Material |
| `Saved/ODC_F*_*.txt` | Preuves de gates (PASS/FAIL) |
| Ce fichier | Règles opérationnelles + collaboration |
| `ETAT_PROJET.md` | Baseline courte entre deux modifications (§1bis) |
| `HISTORIQUE_MODIFICATIONS.md` | Inventaire + historique détaillé (mémoire agent) |

---

## 3. Principes produit (rappel ODC)

| Règle | Statut |
| --- | --- |
| Le joueur ne construit pas le monde directement : il définit conditions, moyens, priorités | VERROUILLÉ |
| Engine cible : Unreal Engine **5.8** | VERROUILLÉ |
| Gameplay principal : **C++ / DataAssets** ; Blueprint complémentaire | VERROUILLÉ |
| Socle visuel : **M4 + RVT + UDS/UDW** (présentation, pas simulation écologique) | VERROUILLÉ |
| Terrain : **interim** LandscapeEdit (éditeur/PIE) ; **cible** Base+Delta shipping avec M4 = rendu (pas PMC plein-île) | VERROUILLÉ |
| Chaque phase ODC-Fx se termine par un **gate** clair avant d’enchaîner | VERROUILLÉ |

---

## 4. Terrain

| Règle | Statut |
| --- | --- |
| Monde visible = **Landscape + M4** ; ne pas utiliser un PMC comme surface joueur | VERROUILLÉ |
| Interim : brushes LandscapeEdit **session-only** (`bSessionOnlyLandscapeEdits=True`) — snapshot → restore Stop Play ; jamais dirty package | VERROUILLÉ |
| `bEnableRuntimeTerraformPersistence=False` en dev ; save/load terrain seulement pour un futur gate F1 | CONVENTION |
| Ne jamais assigner un **MID** ni appeler `UpdateMaterialInstances` sur le Landscape à runtime | VALIDÉ |
| `gf.Terraform.ResetToLandscape` = purge PMC résiduels + FillAuto (base M4 Auto) | CONVENTION |
| APIs `ULandscapeInfo::Layers` / édition éditeur : `WITH_EDITOR` | VALIDÉ |
| Cible F1 redo : Base height immuable + delta + paint + sampling + persistence ; M4 reste le rendu | VERROUILLÉ |
| Gate F1 fichier : `Saved/ODC_F1_RuntimeTerrainGate.txt` — **INVALIDÉ** jusqu’à refonte | VALIDÉ |

---

## 5. Magic Map Material (M4)

| Règle | Statut |
| --- | --- |
| **Consulter la doc officielle M4 en premier** ; forums seulement si absent de la doc. Ne jamais implémenter M4 « au feeling » | VERROUILLÉ |
| Doc : https://aaronneal.online/docs/m4/ | VERROUILLÉ |
| Auto Material = couche visuelle de base ; Paint Layers = logique M4, **pas** stockage des variables écologiques | VERROUILLÉ |
| Conserver MI Island M4 (ex. `Island_UE5Preset5_Inst`) ; dériver des instances contrôlées, ne pas réécrire le parent | VERROUILLÉ |
| RVT : intégration visuelle Landscape ↔ objets ; ne pas détourner pour la simu écologique | VERROUILLÉ |
| Fonctions M4 hors socle initial (ex. générateur terrain M4) : ne pas activer sans besoin prouvé | VERROUILLÉ |
| Biomes M4 ≠ biomes / écosystème GardenFervor (systèmes distincts) | VERROUILLÉ |

---

## 6. UDS / UDW

| Règle | Statut |
| --- | --- |
| UDS/UDW = présentation (ciel, météo, ambiance) uniquement | VERROUILLÉ |
| Ne pas en faire la source de vérité des variables écologiques | VERROUILLÉ |
| Les gates visuels runtime se font en **GPU** (pas NullRHI) pour UDW | VALIDÉ |

---

## 7. Gates ODC (état)

| Phase | Contenu | Preuve | Statut |
| --- | --- | --- | --- |
| ODC-F1 | Terrain runtime Base+Delta shipping | `Saved/ODC_F1_RuntimeTerrainGate.txt` | **À REFAIRE** (INVALIDÉ) |
| ODC-F2 | M4 / RVT / UDS / UDW runtime packaged | `Saved/ODC_F2_VisualTerrainGate.txt` | PASS |
| ODC-F3 | Spatial substrate (cells + dirty + queries) | `Saved/ODC_F3_SimulationSubstrateGate.txt` | PASS |
| ODC-F4 | Projet → tâche (graph + réservations + blocages) | `Saved/ODC_F4_TaskGraphGate.txt` | PASS |
| ODC-F5 | Autonomie unité | `Saved/ODC_F5_AutonomyGate.txt` + PIE humain | **PASS** |
| ODC-F6 | Économie physique minimale | `Saved/ODC_F6_EconomyGate.txt` | PASS |
| ODC-F7 | Logistique | `Saved/ODC_F7_LogisticsGate.txt` + PIE humain | **PASS** |
| ODC-F8 | Terraformer industriel | `Saved/ODC_F8_TerraformOperationGate.txt` | PASS |

Commandes utiles :

- `gf.Visual.RuntimeGate` → `Saved/VisualRuntimeGate.txt`
- `gf.Spatial.RuntimeGate` → `Saved/SpatialRuntimeGate.txt`
- `gf.Task.RuntimeGate` → `Saved/TaskRuntimeGate.txt`
- `gf.Autonomy.RuntimeGate` → `Saved/AutonomyRuntimeGate.txt`
- `gf.Economy.RuntimeGate` → `Saved/EconomyRuntimeGate.txt`
- `gf.Logistics.RuntimeGate` → `Saved/LogisticsRuntimeGate.txt`
- `gf.Terraform.OperationGate` → `Saved/TerraformOperationGate.txt`
- `gf.Project.SmokeLevelPad` → UI **Start LevelPad** (provisoire, zone près caméra)
- `gf.Terraform.ResetToLandscape` / `gf.Terraform.FillAuto` (éditeur)
- `gf.Terraform.RuntimeSmokeTest` / `RuntimePersistVerify` — **hors service** jusqu’à F1 redo

### 7bis. Spatial (F3+)

| Règle | Statut |
| --- | --- |
| Simulation par cellules logiques + dirty regions ; pas de scan monde entier par tick | VERROUILLÉ |
| API commune : `UGardenFervorSpatialSubsystem` (bind store, MarkDirty, ConsumeDirty, Query*) | VALIDÉ |
| Sol/eau gameplay ≠ paint M4 / UDW (stubs OK jusqu’à F10/F11) | VERROUILLÉ |
| Terraform doit notifier le spatial après brush (LandscapeEdit interim ; dirty rect store quand F1 redo) | VALIDÉ |

### 7ter. Project / Task (F4+)

| Règle | Statut |
| --- | --- |
| Task graph **indépendant** du type d’unité (F5 branche les unités ensuite) | VERROUILLÉ |
| Projet simple → chaîne de tâches visible (planner `ExpandProjectToTasks`) | VALIDÉ |
| Dépendances + Ready/Blocked ; cause primaire via `GetPrimaryFailureReason` | VALIDÉ |
| Réservations exclusives : pas deux tâches incompatibles sur la même clé | VALIDÉ |
| Pool ressources tâche = stub jusqu’à économie F6 | CONVENTION |

### 7septies. Terraform ops (F8+)

| Règle | Statut |
| --- | --- |
| Opération terraform = donnée store (+ LandscapeEdit visible en PIE session-only) | VALIDÉ |
| RaiseGrade agent doit changer une hauteur mesurée ; pas complete soft | VALIDÉ |
| Visual shipping Base+Delta PMC = F1 redo (pas contourné en F8) | CONVENTION |

### 7sexies. Logistique (F7+)

| Règle | Statut |
| --- | --- |
| Fosse ≠ pad : Spoil extrait à la fosse, haul obligatoire vers le pad | VALIDÉ |
| Sans haul, transform/consommation pad ne peut pas aboutir | VALIDÉ |
| Arbiter multi-projets / routes / accès bloqués = profondeur ultérieure | CONVENTION |

### 7quinquies. Économie physique (F6+)

| Règle | Statut |
| --- | --- |
| Économie ODC ≠ compteurs AoE Food/Wood/Stone/Gold (legacy gelé) | VERROUILLÉ |
| Stocks site + Deposit / Transform / Reserve / CommitConsume | VALIDÉ |
| Extract produit ; Raise consomme (pas l’inverse) | VALIDÉ |
| Transport entre sites = F7 ; brush Landscape = F8 | CONVENTION |

### 7octies. Design Gate React (maintenance permanente)

Source : `GardenFervor_DesignGate_React/src/data/designGate.js` (+ UI `src/main.jsx`).  
Cycle : **Design Gate → Décision → Implémentation → Validation → Mise à jour Design Gate → suite**.

| Règle | Statut |
| --- | --- |
| Consulter le Design Gate avant toute mécanique gameplay importante (décisions, statuts, dépendances) | VERROUILLÉ |
| Décision utilisateur → mise à jour **immédiate** de `designGate.js` (statut, deps, questions résolues, impacts) | VERROUILLÉ |
| Décision manquante / ambiguïté / contradiction / nouvelle dépendance → l’identifier **dans** le Design Gate, pas seulement dans le code | VERROUILLÉ |
| Fin de jalon significatif → vérifier si règles/rôles/dépendances/hypothèses ont changé ; mettre à jour avant clôture doc | VERROUILLÉ |
| `VALIDÉ` uniquement sur confirmation explicite de conception — jamais parce que le code « marche » | VERROUILLÉ |
| Divergence Design Gate ↔ code → signaler **Design Gate ≠ implémentation** ; trancher avec l’humain | VERROUILLÉ |
| Code existant ≠ autorité de design si contradiction avec une décision VALIDÉE ; code non décidé ≠ design officiel | VERROUILLÉ |
| Après modification des données : vérifier que l’UI React affiche contenu / statuts / deps / questions / progression | VALIDÉ |
| Compte rendu : ligne **Design Gate :** aucune modif / mis à jour DG-XX / nouveau point à définir | VALIDÉ |
| Ne pas inventer de règles manquantes pour débloquer l’implémentation | VERROUILLÉ |

---

## 8. Config / plugins (leçons packaged)

| Règle | Statut |
| --- | --- |
| `GameUserSettingsClassName` → `DefaultEngine.ini` `[/Script/Engine.Engine]` | VALIDÉ |
| `EnhancedInputDeveloperSettings` (`config=Input`) → **`DefaultInput.ini`**, pas `DefaultEngine.ini` | VALIDÉ |
| AutoSettings attend `AutoSettingsGameUserSettings` + `AutoSettingsEnhancedInputUserSettings` | VALIDÉ |
| CommonUI viewport warning : `CommonUI.Debug.CheckGameViewportClientValid=0` tant que CommonGameViewport non adopté | CONVENTION |
| Après changement de config shipped : **recook/stage** (ou `-skipbuild` si binaire inchangé) | VALIDÉ |
| Préférer le **packaged** pour les preuves shipping ; le binaire projet + Zen store peut être trompeur | VALIDÉ |

---

## 9. Architecture & code

| Règle | Statut |
| --- | --- |
| Code gameplay sous `Source/GardenFervor/RTS/` selon découpage ODC (Terraform, Environment, Data, …) | VERROUILLÉ |
| Catalogue contenu : `/Game/GardenFervor/RTS/Data` (ex. `DA_RTS_Catalog`) | VERROUILLÉ |
| Données dynamiques = subsystems/runtime ; DataAssets = définitions stables | VERROUILLÉ |
| Persistance : stocker référence stable + deltas, pas une « nouvelle carte » permanente | VERROUILLÉ |
| Toucher le minimum de fichiers ; pas de docs markdown non demandés hors ce fichier / preuves gate | CONVENTION |

---

## 10. Production & validation

| Règle | Statut |
| --- | --- |
| Preuve avant dépendance forte (« preuves puis construction ») | VERROUILLÉ |
| Un gate FAIL bloque l’enchaînement de phase | VERROUILLÉ |
| Distinguer preuve `-game` / éditeur et preuve **Cook/Package** | VERROUILLÉ |
| Mesurer tôt la combinaison RTS + terrain dynamique + M4 + RVT + météo | VERROUILLÉ |

---

## 11. Journal des ajouts

| Date | Ajout |
| --- | --- |
| 2026-10-05 | Création du document ; socle ODC + règles M4/terrain/gates F1–F2 + conventions d’interaction |
| 2026-10-05 | §1bis processus obligatoire état → delta humain → nouvel état ; fichier `ETAT_PROJET.md` |
| 2026-10-05 | ODC-F3 Spatial PASS ; §7bis règles spatial ; suite F4 |
| 2026-10-05 | `HISTORIQUE_MODIFICATIONS.md` ; §1bis étape 6 historique obligatoire |
| 2026-10-05 | ODC-F4 Task graph PASS ; §7ter Project/Task ; suite F5 |
| 2026-10-05 | Terrain reset : F1 INVALIDÉ ; interim LandscapeEdit+M4 ; F5 non bloqué ; sync §3–4–7 |
| 2026-10-05 | `bSessionOnlyLandscapeEdits` : restore Landscape au Stop Play |
| 2026-10-06 | §7octies maintenance permanente Design Gate React (`designGate.js`) |

---

*Mettre à jour la section 11 à chaque ajout de règle.*
