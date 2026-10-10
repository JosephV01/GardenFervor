# GardenFervor — Historique des modifications détaillées

Document **obligatoire** pour tout agent (humain ou IA) qui reprend le projet.  
Il doit permettre, **à tout moment**, de savoir : ce qui existe, pourquoi, comment le prouver, et ce qui reste ouvert.

| Document | Rôle |
| --- | --- |
| `GardenFervor_ODC_v1.0` | Direction produit / phases / gates (contrat) |
| `GardenFervor_DesignGate_React/src/data/designGate.js` | **Source de vérité conception** (document vivant) |
| `REGLES_PROJET.md` | Règles opérationnelles + process modification |
| `ETAT_PROJET.md` | **Snapshot courant** (court) |
| **Ce fichier** | **Mémoire longue** : inventaire + historique détaillé validé |
| `Saved/ODC_F*_*.txt` | Preuves brutes de gates |

**Règle d’entretien :** après **chaque modification validée** (gate PASS, fix accepté, règle ajoutée), ajouter une entrée en §4 **avant** de considérer la tâche livrée. Mettre aussi à jour `ETAT_PROJET.md` et le delta chat (`REGLES_PROJET.md` §1bis).

Dernière entrée historique : **2026-10-10 — C-21-CLOSE**.

---

## 0. Comment un agent doit lire ce document

1. Lire §1 (carte) + §2 (état pointé) + §3 (inventaire) — contexte complet.
2. Parcourir §4 du **plus récent au plus ancien** pour les décisions et pièges.
3. Ne pas réinventer : réutiliser chemins, commandes et conventions listés.
4. Avant de modifier : `ETAT_PROJET.md` + dernière entrée §4.
5. Après validation : nouvelle entrée §4 + refresh `ETAT_PROJET.md` + delta humain.

---

## 1. Carte projet (référence fixe)

| Élément | Valeur |
| --- | --- |
| Engine | Unreal Engine **5.8** |
| Genre | RTS / gestion d’unités / terraformation / écosystèmes |
| Gameplay | C++ / DataAssets ; Blueprint complémentaire |
| Carte cible | `/Game/GardenFervor/Maps/GardenFervorIsland` |
| Socle visuel | M4 Magic Map Material + RVT + UDS/UDW (**présentation**) |
| Terrain runtime | **Interim** : LandscapeEdit (PIE/éditeur) + store extents Spatial. **Cible F1** : Base+Delta shipping (M4 = rendu) |
| Archive packaged de preuve | `Packaged/Win64Dev` |
| Doc M4 officielle | https://aaronneal.online/docs/m4/ |
| ODC extrait texte | `Saved/GardenFervor_ODC_v1.0_extracted.txt` |

Principe directeur ODC : le joueur **ne construit pas** le monde directement ; il définit conditions / moyens / priorités.

Roadmap ODC (ordre verrouillé) :  
F1 Terrain → F2 M4/UDS/UDW → **F3 Spatial** → **F4 Project/Task** → F5 Autonomy → … → F20 Shipping.

---

## 2. État courant (résumé)

> Source de vérité courte : **`ETAT_PROJET.md`**.

| Phase | Statut | Preuve |
| --- | --- | --- |
| ODC-F1 | **À REFAIRE** | `Saved/ODC_F1_RuntimeTerrainGate.txt` (INVALIDÉ) |
| ODC-F2 | **PASS** | `Saved/ODC_F2_VisualTerrainGate.txt` |
| ODC-F3 | **PASS** | `Saved/ODC_F3_SimulationSubstrateGate.txt` |
| ODC-F4 | **PASS** | `Saved/ODC_F4_TaskGraphGate.txt` |
| ODC-F5 | **PASS (humain)** | `Saved/ODC_F5_AutonomyGate.txt` + PIE |
| ODC-F6 | **PASS** | `Saved/ODC_F6_EconomyGate.txt` |
| ODC-F7 | **PASS (humain)** | `Saved/ODC_F7_LogisticsGate.txt` + PIE |
| ODC-F8 | **PASS** | `Saved/ODC_F8_TerraformOperationGate.txt` |

Prochain pas ODC : **F9 Infrastructure** (après validation humaine F8).

---

## 3. Inventaire — ce qui est déjà en place

### 3.1 Terrain (`Source/GardenFervor/RTS/Terraform/`)

| Composant | Fichier(s) | Rôle actuel |
| --- | --- | --- |
| Façade | `GardenFervorLandscapeTerraformSubsystem` | LandscapeEdit (éditeur/PIE) ; store extents ; pas d’overlay PMC |
| Store CPU | `GardenFervorRuntimeTerraformStore` | Extents / sampling pour Spatial (pas de save) |
| Base height | `GardenFervorIslandBaseHeightData` + `DA_IslandBaseHeight` | Bake de référence (réutilisable F1 redo) |
| Collision / Visualizer PMC | `*RuntimeTerraformCollision` / `*Visualizer` | **Inactifs** (non spawnés) |
| Save | `GardenFervorTerraformSaveGame` | **Désactivé** en dev |
| Types | `GardenFervorTerraformTypes` | Modes Raise/Lower/Paint |
| Ground | `RTS/Types/GardenFervorGroundUtils` | Traces Landscape (pas hauteur overlay) |

**Conventions actuelles :**

- `bUseRuntimeTerraformOverlay=False` ; `bEnableRuntimeTerraformPersistence=False`
- `gf.Terraform.UseEditorLandscapeEdit=1` (défaut)
- Jamais MID / `UpdateMaterialInstances` sur Landscape à runtime
- Spatial : `NotifySpatialLandscapeBrush` après LandscapeEdit
- Cook : `/Game/GardenFervor/RTS/Data` always cook

**Commandes :**

| Commande | Rôle |
| --- | --- |
| `gf.Terraform.ResetToLandscape` | Purge acteurs PMC + FillAuto (M4 base) |
| `gf.Terraform.FillAuto` | Paint Auto plein Landscape |
| `gf.Terraform.BakeBaseHeight` | Bake DataAsset (éditeur) |
| `gf.Terraform.RuntimeSmokeTest` / `RuntimePersistVerify` | **Hors service** jusqu’à F1 redo |

**Gate F1 :** INVALIDÉ — voir `Saved/ODC_F1_RuntimeTerrainGate.txt`.

### 3.2 Visuel M4 / RVT / UDS / UDW (F2) — `RTS/Environment/`

| Composant | Fichier(s) | Rôle |
| --- | --- | --- |
| Gate visuelle | `GardenFervorVisualRuntimeGate` | `gf.Visual.RuntimeGate` |

**Faits prouvés packaged (GPU) :**

- MI Landscape : `Island_UE5Preset5_Inst` (MIC/Material, **pas MID**).
- RVT : 3 volumes natifs / 3 nommés ; `r.VirtualTextures=1`.
- Acteurs Ultra Dynamic Sky + Ultra Dynamic Weather présents.
- MagicMapMaterialBP présent (helper setup) — M4 reste couche présentation.

**Règles M4 :** doc officielle d’abord ; Auto = base visuelle ; Paint ≠ variables écologiques ; biomes M4 ≠ écosystème GF.

### 3.3 Spatial substrate (F3) — `RTS/Spatial/`

| Composant | Fichier(s) | Rôle |
| --- | --- | --- |
| Types | `GardenFervorSpatialTypes` | CellId, dirty mask Terrain/Slope/Soil/Water, samples |
| Subsystem | `GardenFervorSpatialSubsystem` | Bind store, MarkDirty, ConsumeDirty, Query* |
| Gate | `GardenFervorSpatialRuntimeGate` | `gf.Spatial.RuntimeGate` |

**Paramètres prouvés :** landscape `4033×4033` → cells `253×253` (64009), `cellQuads=16`.  
Dirty local : 1 puis 9 cellules << total.  
Queries : Terrain (Z+pente) réel via store ; Soil/Water = **stubs** par cellule (vrai simu = F10/F11).

### 3.4 Project / Task graph (F4) — `RTS/Projects/` + `RTS/Tasks/`

| Composant | Fichier(s) | Rôle |
| --- | --- | --- |
| Project types | `GardenFervorProjectTypes` | Id, status ODC, objective, zone |
| Project subsystem | `GardenFervorProjectSubsystem` | Create, ExpandToTasks (LevelPad), Activate, Sync |
| Task types | `GardenFervorTaskTypes` | Type, status, prereqs, reservation, BlockCause |
| Task subsystem | `GardenFervorTaskSubsystem` | Graph, readiness, reserve/release, topo order |
| Gate | `GardenFervorTaskRuntimeGate` | `gf.Task.RuntimeGate` |

**Chaîne smoke LevelPad :** Analyze → Prepare → Extract(FillDirt) → Raise → Verify.  
**Preuve :** deps + MissingResource + exclusive conflict + Project Completed.

### 3.5 Autonomie unité (F5) — `RTS/Units/` + Task claim API

| Composant | Fichier(s) | Rôle |
| --- | --- | --- |
| Capabilities | `GardenFervorUnitDefinition` | `Capabilities` (Worker / Terraform) ; fallback runtime par rôle |
| Claim API | `GardenFervorTaskSubsystem` | `FindBestReadyTaskForCapabilities`, `TryClaimTask`, `ReleaseClaim`, `SetTaskProgress` |
| Agent | `GardenFervorUnitTaskAgent` | SEEK→RESERVE→TRAVEL→PREPARE→EXECUTE→VERIFY→DELIVER→REPLAN |
| Gate | `GardenFervorAutonomyRuntimeGate` | `gf.Autonomy.RuntimeGate` |

**Faits prouvés packaged (NullRHI) :** Worker + Terraformer complètent LevelPad en 30 steps instant, sans ordres manuels.  
**Commande :** `gf.Autonomy.RuntimeGate` → `Saved/AutonomyRuntimeGate.txt`

### 3.6 RTS gameplay legacy (gel)

Sous `Source/GardenFervor/RTS/` : Buildings, Economy, Production, Resources, Selection, Tech, Camera, Data.  
Harvest / TC / Ages / RMB = **legacy** — ne pas étendre ; l’agent F5 est le chemin ODC.

### 3.7 Config critique

| Fichier | Clé | Valeur / note |
| --- | --- | --- |
| `Config/DefaultEngine.ini` | `GameUserSettingsClassName` | `/Script/AutoSettings.AutoSettingsGameUserSettings` |
| `Config/DefaultEngine.ini` | `[SystemSettings]` | `CommonUI.Debug.CheckGameViewportClientValid=0` |
| `Config/DefaultInput.ini` | `[/Script/EnhancedInput.EnhancedInputDeveloperSettings]` | `bEnableUserSettings=True` + `UserSettingsClass=/Script/AutoSettingsInput.AutoSettingsEnhancedInputUserSettings` |
| | | **Important :** `EnhancedInputDeveloperSettings` est `config=Input` → **pas** dans DefaultEngine |

### 3.8 Packaging / preuves

- Preuves shipping : **toujours le packaged** `Packaged/Win64Dev`, pas le binaire projet si Zen store actif (`ue.projectstore` casse souvent `Binaries/Win64`).
- BuildCookRun typique : `-platform=Win64 -clientconfig=Development -cook -stage -pak -archive` ; `-skipbuild` si seul config/content ; `-build` si C++ changé.
- Gates NullRHI OK pour terraform/spatial/task/autonomy ; **GPU requis** pour VisualGate UDW.
- Markers écrits sous `FPaths::ProjectSavedDir()` du **binaire lancé** (packaged → `Packaged/.../Saved/`).

### 3.9 Outils Python / content

`Content/Python/` — scripts setup/diagnostic M4/terraform (hors runtime shipping).  
Redirects packages M4 → `GardenFervor/Environment` dans `DefaultEngine.ini` `[CoreRedirects]`.

---

## 4. Historique chronologique des modifications validées

Format d’entrée (à dupliquer) :

```
### YYYY-MM-DD — ID — Titre court
- Intention :
- Statut : VALIDÉ | PARTIEL | ANNULÉ
- Avant → Après :
- Changements (fichiers / systèmes) :
- Preuves :
- Pièges / leçons :
- Dette ouverte créée ou réduite :
- Suite ODC :
```

---

### 2026-10-10 — C-21-CLOSE — Cadences de simulation et budgets temporels VALIDÉ (clôture documentaire)

- **Intention :** synchroniser le suivi après clôture formelle du contrat de conception C-21 (validation humaine + audit final PASS).
- **Statut :** VALIDÉ (humain) — **contrat de conception uniquement** · **pas de code gameplay** · ODC-F9 **non démarré** · C-03·C-06·C-09·C-10·C-13 addenda **fermés** · Case B reste **suspendu** · points ouverts O6, P9, C-17 Q8, R6, O-FREQ, O-OVER, O-EXC, O-INST, O-SCALE conservés · **aucune implémentation de scheduler / Hertz / budgets / éco / sol / eau / DG-07 / persist / UX**
- **Décisions :** cadrage **T1 + B1–B8** inchangé ; fréquence ≠ progression ≠ FPS ; pas de tick universel ; frontières C-02 / C-07 / vérités ; Design Gate non modifié
- **Fichiers :** suivi / registre / ETAT / HISTORIQUE → compteur **16 / 16** (le fichier `C-21_CADENCES_SIMULATION_BUDGETS_TEMPORELS.md` déjà `VALIDÉ` à l’étape 10)
- **Design Gate :** aucune modification
- **Suite :** aucun contrat requis restant au compteur 16 · C-22·C-23 NON REQUIS · pas d’implémentation de cadence · addenda et Case B non ouverts automatiquement · commit/push / Hub seulement sur autorisation

### 2026-10-10 — C-20-CLOSE — Observabilité / UX lisibilité VALIDÉ (clôture documentaire)

- **Intention :** synchroniser le suivi après clôture formelle du contrat de conception C-20 (validation humaine + audit final PASS).
- **Statut :** VALIDÉ (humain) — **contrat de conception uniquement** · **pas de code gameplay** · **C-21 non commencé** · ODC-F9 **non démarré** · C-03·C-06·C-09·C-10·C-13 addenda **fermés** · Case B reste **suspendu** · points ouverts R7 C-18, O1–O9, P1–P10, Q1–Q12 C-17, R1–R8 / R11 conservés · **aucune implémentation UX / HUD DG-13 / persist / F1 / DG-07**
- **Décisions :** cadrage **X1–X10 · L1–L3** inchangé ; noyau DG-13.1–13.5 + save S14 + faits déjà exposables C-04/C-07/C-11/PE C6 ; HUD = dette ; Design Gate non modifié
- **Fichiers :** suivi / registre / ETAT / HISTORIQUE → compteur **15 / 16** (le fichier `C-20_OBSERVABILITE_UX_LISIBILITE.md` déjà `VALIDÉ` à l’étape 10)
- **Design Gate :** aucune modification
- **Suite :** prochain contrat requis = C-21 (ne pas démarrer sans ordre explicite) · pas d’implémentation UX · addenda et Case B non ouverts automatiquement · commit/push / Hub seulement sur autorisation

### 2026-10-10 — C-19-CLOSE — Persistance / sauvegarde VALIDÉ (clôture documentaire)

- **Intention :** synchroniser le suivi après clôture formelle du contrat de conception C-19 (validation humaine + audit final PASS).
- **Statut :** VALIDÉ (humain) — **contrat de conception uniquement** · **pas de code gameplay** · **C-20 non commencé** · ODC-F9 **non démarré** · C-03·C-06·C-09·C-10·C-13 addenda **fermés** · Case B reste **suspendu** · points ouverts O5, P8, Q7, R5, R1–R8 / R11, O1–O9, P1–P10 et Q1–Q12 C-17 conservés · **aucune implémentation persist / F1 / DG-07**
- **Décisions :** cadrage **S1–S14 · L1–L3** inchangé ; familles T/R/L/I ; E/X conditionnels ; P/K exclus ; Dirty hors save ; hybride session / durable ; Design Gate non modifié
- **Fichiers :** suivi / registre / ETAT / HISTORIQUE → compteur **14 / 16** (le fichier `C-19_PERSISTANCE_SAUVEGARDE.md` déjà `VALIDÉ` à l’étape 10)
- **Design Gate :** aucune modification
- **Suite :** prochain contrat requis = C-20 (ne pas démarrer sans ordre explicite) · pas d’implémentation persist · addenda et Case B non ouverts automatiquement · commit/push / Hub seulement sur autorisation

### 2026-10-10 — C-18-CLOSE — Technologie / progression VALIDÉ (clôture documentaire)

- **Intention :** clôturer formellement le contrat de conception C-18 après validation humaine et audit final PASS.
- **Statut :** VALIDÉ (humain) — **contrat de conception uniquement** · **pas de code gameplay** · **C-19 non commencé** · ODC-F9 **non démarré** · C-03·C-06·C-09·C-10·C-13 addenda **fermés** · Case B reste **suspendu** · points ouverts R1–R8, R11, O1–O9, P1–P10 et Q1–Q12 C-17 conservés · Ages = legacy isolé · **aucune implémentation DG-07**
- **Décisions :** cadrage **Q1–Q31** inchangé ; 07.1–07.7 repris intégralement ; frontières Ages / `RequiredAge` / FWSG ; Design Gate non modifié
- **Fichiers :** `CONTRATS/C-18_TECHNOLOGIE_PROGRESSION.md` · suivi / registre / ETAT / HISTORIQUE → compteur **13 / 16**
- **Design Gate :** aucune modification
- **Suite :** prochain contrat requis = C-19 (ne pas démarrer sans ordre explicite) · pas d’implémentation DG-07 · addenda et Case B non ouverts automatiquement · commit/push / Hub seulement sur autorisation

### 2026-10-10 — C-18-DRAFT — Technologie / progression (brouillon publié)

- **Intention :** synchroniser le Hub et les registres avec le brouillon C-18 poussé (`632b6eec5d4ed8e515968c72175491d0b1a12d2c`).
- **Statut :** PARTIEL — **DRAFT / BROUILLON — non validé** · compteur **reste 12 / 16** · **pas de runtime** · Ages = legacy isolé · ODC-F9 **non démarré** · addenda C-03·C-06·C-09·C-10·C-13 **fermés** · Case B **suspendu** · O1–O9, P1–P10, Q1–Q12 C-17 **ouverts**
- **Décisions :** cadrage **Q1–Q31** déjà formalisé dans le contrat ; cette entrée **n’ajoute** aucune règle de gameplay
- **Fichiers :** contrat déjà sur `origin/main` · suivi / registre / ETAT / HISTORIQUE / miroir Hub / roadmap / graphe alignés sur DRAFT
- **Design Gate :** aucune modification
- **Suite :** revue humaine de C-18 · **ne pas** valider ni implémenter · C-19 non commencé · C-17 fichier local encore **non suivi Git**

### 2026-10-10 — C-17-CLOSE — Végétation / écosystèmes VALIDÉ (clôture documentaire)

- **Intention :** clôturer formellement le contrat de conception C-17 après validation humaine et audit final PASS.
- **Statut :** VALIDÉ (humain) — **contrat de conception uniquement** · **pas de code gameplay** · **C-18 non commencé** · ODC-F9 **non démarré** · C-03·C-06·C-09·C-10·C-13 addenda **fermés** · Case B reste **suspendu** · points ouverts Q1–Q12, O1–O9 C-15 et P1–P10 C-16 conservés · **aucune implémentation écologique**
- **Décisions :** cadrage **A1–K1** — vérité végétation / états écologiques ; E1–E4 repris intégralement ; frontières C-01/C-02/C-08/C-14/C-15/C-16/C-19/C-21 ; Design Gate non modifié
- **Fichiers :** `CONTRATS/C-17_VEGETATION_ECOSYSTEMES.md` · suivi / registre / ETAT / HISTORIQUE → compteur **12 / 16**
- **Design Gate :** aucune modification
- **Suite :** prochain contrat requis = C-18 (ne pas démarrer sans ordre explicite) · pas d’implémentation écologique · addenda et Case B non ouverts automatiquement · commit/push seulement sur autorisation

### 2026-10-10 — C-16-CLOSE — Sol VALIDÉ (clôture documentaire)

- **Intention :** clôturer formellement le contrat de conception C-16 après validation humaine et audit final PASS.
- **Statut :** VALIDÉ (humain) — **contrat de conception uniquement** · **pas de code gameplay** · **C-17 non commencé** · ODC-F9 **non démarré** · C-03·C-06·C-09·C-10·C-13 addenda **fermés** · Case B reste **suspendu** · points ouverts P1–P10 et O1–O9 C-15 conservés · **aucune implémentation sol**
- **Décisions :** cadrage **A1–K1** — vérité métier du sol ; O1–O4 repris intégralement ; frontières C-01/C-02/C-08/C-14/C-15/C-17/C-19/C-21 ; Design Gate non modifié
- **Fichiers :** `CONTRATS/C-16_SOL.md` · suivi / registre / ETAT / HISTORIQUE → compteur **11 / 16**
- **Design Gate :** aucune modification
- **Suite :** prochain contrat requis = C-17 (ne pas démarrer sans ordre explicite) · pas d’implémentation sol · addenda et Case B non ouverts automatiquement · commit/push seulement sur autorisation

### 2026-10-10 — C-15-CLOSE — Hydrologie VALIDÉ (clôture documentaire)

- **Intention :** clôturer formellement le contrat opérationnel C-15 après validation humaine et audit après correction PASS.
- **Statut :** VALIDÉ (humain) — **pas de code gameplay** · **C-16 non commencé** · ODC-F9 **non démarré** · C-03·C-06·C-09·C-10·C-13 addenda **fermés** · Case B reste **suspendu** · points ouverts O1–O9 conservés · **aucune implémentation hydrologique**
- **Décisions :** cadrage **A–G** — vérité hydrologique ; W1 repris intégralement ; frontières C-01/C-02/C-14/C-16/C-17 ; Design Gate non modifié
- **Fichiers :** `CONTRATS/C-15_HYDROLOGIE.md` · suivi / registre / ETAT / HISTORIQUE / ROADMAP / PROJECT_GRAPH / Hub contrats · état-global · historique → compteur **10 / 16**
- **Design Gate :** aucune modification (W1 déjà VALIDÉ)
- **Suite :** prochain contrat requis = C-16 (ne pas démarrer sans ordre explicite) · pas d’implémentation eau · addenda et Case B non ouverts automatiquement

### 2026-10-10 — PRES-CLIENT-LOT10 — Intégration des 10 illustrations fournies

- **Intention :** remplacer les visuels conceptuels par les 10 images utilisateur, sans toucher à la capture S3 ni au gameplay.
- **Statut :** documentaire / présentation — **pas de gameplay** · **C-15 non commencé** · 9/16 inchangé
- **Avant → Après :** 7 WebP conceptuels hérités → 10 WebP issus des PNG/WebP fournis ; S3 192×192 conservé
- **Placement :** 06/07 et 08/09 associés selon le contenu réel (pont / nivellement ; bassin / mare), pas selon le nom du fichier source
- **Inchangé :** originaux `01-…png` à `10-…png` ; Unreal ; Design Gate ; contrats
- **Suite :** commit/push seulement sur autorisation

### 2026-10-10 — PRES-CLIENT-VISUEL — Refonte visuelle présentation client

- **Intention :** remplacer la page React+Base64 (~19,5 Mo) par un HTML statique avec images WebP externes, en distinguant preuve S3 et vision.
- **Statut :** VALIDÉ (documentaire / présentation) — **pas de gameplay** · **C-15 non commencé** · 9/16 inchangé
- **Avant → Après :** 20 WebP inline + galerie lot1 opaque → 8 WebP nommés + légendes Prototype / Vision
- **Changements :** `Investor Demo/PrésentationClientHtml/PrésentationClient.html` · `images/*.webp` · copies `docs/` · registre §2.8 · ETAT
- **Limitation :** aucune capture S3 haute définition dans le dépôt ; pastille 192×192 = placeholders BasicShapes
- **Suite :** commit/push seulement sur autorisation ; captures PIE humaines encore utiles

### 2026-10-09 — DG-00.5-W1-CLOSE — Clôture documentaire W1 (impact + Hub)

- **Intention :** consigner la confirmation humaine d’impact de `00.5.W1` et la synchronisation ciblée déjà faite de `docs/design-gate.html`. Pas de nouvelle décision.
- **Statut :** VALIDÉ (documentaire) — formulation et statut item inchangés (`VALIDÉ`) · **C-15 non commencé** · compteurs **9/16**
- **Avant → Après :** confirmation d’impact et Hub encore ouverts dans `DG-00.5-W1-HORIZON` → confirmation **acquise** ; Hub local aligné et vérifié visuellement
- **Inchangé :** texte W1 ; W2, W3, W4, X1, X2 ; contrats ; aucun runtime
- **Changements (fichiers / systèmes) :** `ETAT_PROJET.md` · cette entrée — SoT et vues DG **non réécrites**
- **Preuves :** quatre vues W1 identiques (JS / JSON / HTML local / `docs/design-gate.html`) ; validation humaine explicite de l’impact
- **Dette ouverte :** alignement éventuel de W3 / W4 / X1 / X2 (autorisation distincte) ; C-15 non commencé
- **Suite :** ne pas démarrer C-15 sans ordre explicite ; pas de commit/push dans cette clôture

### 2026-10-09 — DG-00.5-W1-HORIZON — Clarification d’horizon hydrologique (W1)

- **Intention :** lever l’ambiguïté d’horizon de `00.5.W1` : conserver le grain fondateur, limiter l’exclusion d’hydrodynamique détaillée au fondateur, et inscrire l’ambition à long terme sans pré-approuver un modèle.
- **Statut :** PARTIEL — formulation appliquée dans la SoT ; **confirmation humaine d’impact encore requise** ; statut item W1 laissé `VALIDÉ` (aucun statut intermédiaire documenté pour une révision de décision déjà VALIDÉE)
- **Avant → Après :**
  - Avant : « Pas d’hydrodynamique détaillée » sans horizon temporel explicite
  - Après : exclusion limitée au **périmètre du fondateur** + objectif à long terme d’une simulation hydrologique réaliste et approfondie, sans phénomène / algorithme / solveur / implémentation pré-approuvés
- **Inchangé :** W2, W3, W4, X1, X2 ; frontières C-01 / C-02 / C-14 / C-16 / C-17 ; C-15 non rédigé ; aucun runtime eau ; compteurs contrats 9/16
- **Changements (fichiers / systèmes) :** `GardenFervor_DesignGate_React/src/data/designGate.js` · vues locales `designGate.data.json` + `GardenFervor_DESIGN_GATE_v0.1.html` · `ETAT_PROJET.md` · cette entrée
- **Preuves :** texte W1 = formulation approuvée ; `node GardenFervor_DesignGate_React/scripts/syncStandaloneFromJs.mjs` (vues locales) ; `docs/design-gate.html` **non publié**
- **Pièges / leçons :** le script standalone écrit aussi `docs/design-gate.html` — ne pas le traiter comme publication autorisée ; W3 / W4 / X1 / X2 gardent un wording voisin encore non aligné
- **Dette ouverte :** confirmation humaine de la clarification W1 ; éventuel alignement ultérieur de W3 / W4 / X1 / X2 (autorisation distincte) ; C-15 non commencé
- **Suite :** validation humaine de l’impact → alors seulement publication Hub / clôture W1 / éventuel questionnaire C-15

### 2026-10-09 — DOC-MAINT-REGISTRE — Registre de maintenance documentaire + miroir Hub historique

- **Intention :** inventaire durable des documents à maintenir et chronologie Hub générée depuis HISTORIQUE §4, sans gameplay ni nouveau contrat.
- **Statut :** VALIDÉ (documentaire) — **pas de code gameplay** · **C-15 non commencé** · compteurs contrats **inchangés** (9/16)
- **Avant → Après :** pas de registre central ni page Hub historique → `REGISTRE_MAINTENANCE_DOCUMENTAIRE.md` + `docs/historique.html` (build depuis §4) + carte Hub
- **Changements (fichiers / systèmes) :** `REGISTRE_MAINTENANCE_DOCUMENTAIRE.md` · `docs/historique/*` · `docs/historique.html` · `docs/syncPages.mjs` · `docs/index.html` · `docs/GITHUB_PAGES.md` · `REGLES_PROJET.md` (pointeur)
- **Preuves :** `node docs/historique/buildHistorique.mjs` · `node docs/syncPages.mjs` (ok)
- **Pièges / leçons :** ne pas maintenir un second historique parallèle ; HTML = miroir uniquement
- **Suite :** commit/push séparés sur autorisation ; C-15 non démarré

### 2026-10-09 — C-14-CLOSE — Infrastructures (lifecycle) VALIDÉ (clôture documentaire)

- **Intention :** clôturer formellement le contrat opérationnel C-14 après validation humaine et audit final PASS FINAL (15/15).
- **Statut :** VALIDÉ (humain) — **pas de code gameplay** · **C-15 non commencé** · ODC-F9 **non démarré** · C-03·C-06·C-09·C-10·C-13 addenda **fermés** · Case B reste **suspendu** · points ouverts §18 conservés
- **Décisions :** **15/15** (A1–F1) — lifecycle infrastructures ; propriété d’état ; frontières C-01/C-02/C-04/C-05/C-07/C-08/C-11/C-12/C-13\* ; C-10 fermé ; DG-10 non modifié
- **Fichiers :** `CONTRATS/C-14_INFRASTRUCTURES_LIFECYCLE.md` · suivi / registre / ETAT / HISTORIQUE / ROADMAP / PROJECT_GRAPH / Hub état-global → compteur **9 / 16**
- **Design Gate :** aucune modification (DG-10 déjà VALIDÉ)
- **Suite :** prochain contrat requis = C-15 (ne pas démarrer sans ordre explicite) · ODC-F9 non démarré automatiquement · addenda C-09/C-10/C-13 non ouverts automatiquement

### 2026-10-09 — C-12-CLOSE — Transport / logistique VALIDÉ (clôture documentaire)

- **Intention :** clôturer formellement le contrat opérationnel C-12 après validation humaine et audit final PASS (25/25).
- **Statut :** VALIDÉ (humain) — **pas de code gameplay** · **C-14 non commencé** · C-03·C-06·C-09·C-10 addenda **fermés** · Case B reste **suspendu**
- **Décisions :** **25/25** (A1–G3) — cycle transport ; réservation≠chargement ; transit ; accès/DG-06/N4 conception≠runtime ; frontiers C-04/C-05/C-07/C-08/C-11/C-14/C-19 ; C-10 fermé
- **Fichiers :** `CONTRATS/C-12_TRANSPORT_LOGISTIQUE.md` · suivi / registre / ETAT / HISTORIQUE / ROADMAP / PROJECT_GRAPH → compteur **8 / 16**
- **Design Gate :** aucune modification
- **Suite :** prochain contrat requis = C-14 (ne pas démarrer sans ordre explicite) · addenda C-09/C-10 non ouverts automatiquement

### 2026-10-09 — C-11-CLOSE — Réservations VALIDÉ (clôture documentaire)

- **Intention :** clôturer formellement le contrat opérationnel C-11 après validation humaine et audit final PASS (23/23).
- **Statut :** VALIDÉ (humain) — **pas de code gameplay** · **C-12 non commencé** · C-03·C-06·C-09·C-10 addenda **fermés** · Case B reste **suspendu**
- **Décisions :** **23/23** (A1–G1) — allocation concurrente stocks ; claim ≠ réservation ; priorités ; non-préemption ; réconciliation E2 ; frontiers C-04/C-05/C-07/C-08/C-12/C-19
- **Fichiers :** `CONTRATS/C-11_RESERVATIONS.md` · suivi / registre / ETAT / HISTORIQUE / ROADMAP / PROJECT_GRAPH → compteur **7 / 16**
- **Design Gate :** aucune modification
- **Suite :** prochain contrat requis = C-12 (ne pas démarrer sans ordre explicite) · addenda C-09/C-10 non ouverts automatiquement

### 2026-10-09 — C-08-CLOSE — Terraformer opérationnel VALIDÉ (clôture documentaire)

- **Intention :** clôturer formellement le contrat opérationnel C-08 après validation humaine et audit final PASS (58/58).
- **Statut :** VALIDÉ (humain) — **pas de code gameplay** · **C-11 non commencé** · C-03·C-06·C-09·C-10 addenda **fermés** · Case B reste **suspendu**
- **Décisions :** **58/58** (A1–L4) — métier Creuser/Remblayer/Aplanir ≠ Raise/Lower/Paint ; décomposition ; matière↔relief ; SiteReady via preuve métier ; Case B non réactivé
- **Fichiers :** `CONTRATS/C-08_TERRAFORMER_OPERATIONNEL.md` · suivi / registre / ETAT / HISTORIQUE / ROADMAP / PROJECT_GRAPH → compteur **6 / 16**
- **Design Gate :** aucune modification
- **Suite :** prochain contrat requis = C-11 (ne pas démarrer sans ordre explicite) · addenda C-09/C-10 non ouverts automatiquement

### 2026-10-09 — C-07-CLOSE — Autonomie unité (agent générique) VALIDÉ (clôture documentaire)

- **Intention :** clôturer formellement le contrat opérationnel C-07 après validation humaine et audit final PASS (47/47).
- **Statut :** VALIDÉ (humain) — **pas de code gameplay** · **C-08 non commencé** · C-03 et C-06 addenda **fermés** · Case B reste **suspendu**
- **Décisions :** **47/47** (A1–J4) — agent générique, claim, exécution, Progress≠effets, frontiers C-04/C-05/C-08, InstantMode≠preuve produit
- **Fichiers :** `CONTRATS/C-07_AUTONOMIE_UNITE_AGENT_GENERIQUE.md` · suivi / registre / ETAT / HISTORIQUE / ROADMAP / PROJECT_GRAPH → compteur **5 / 16**
- **Design Gate :** aucune modification
- **Suite :** prochain contrat requis = C-08 (ne pas démarrer sans ordre explicite)

### 2026-10-08 — C-05-CLOSE — WorkSite / SitePrep VALIDÉ (clôture documentaire)

- **Intention :** clôturer formellement le contrat opérationnel C-05 après validation humaine et audit final PASS (62/62).
- **Statut :** VALIDÉ (humain) — **pas de code gameplay** · **C-07 non commencé** · C-03 et C-06 addenda **fermés** · Case B reste **suspendu**
- **Décisions :** **62/62** (A1–N3) · D5=C · D6=B — besoin SitePrep, SiteReady≠tâche, prep progressive, frontières C-04/C-08/C-01/C-02, invalidation, observabilité
- **Fichiers :** `CONTRATS/C-05_WORKSITE_SITEPREP.md` · suivi / registre / ETAT / HISTORIQUE / ROADMAP / PROJECT_GRAPH → compteur **4 / 16**
- **Design Gate :** aucune modification
- **Suite :** prochain contrat requis = C-07 (ne pas démarrer sans ordre explicite) · C-06* reste fermé

### 2026-10-08 — C-04-CLOSE — Tâches / graphe / dépendances VALIDÉ (clôture documentaire)

- **Intention :** clôturer formellement le contrat opérationnel C-04 après validation humaine et audit final PASS (48/48).
- **Statut :** VALIDÉ (humain) — **pas de code gameplay** · **C-05 non commencé** · C-03 addendum **fermé** · Case B reste **suspendu**
- **Décisions :** **48/48** (A1–K6) — graphe, cycle de vie, hiérarchie, Progress≠effets, claim, invalidation, frontières
- **Fichiers :** `CONTRATS/C-04_TACHES_GRAPHE_DEPENDANCES.md` · suivi / registre / ETAT / HISTORIQUE / ROADMAP / PROJECT_GRAPH → compteur **3 / 16**
- **Design Gate :** aucune modification
- **Suite :** prochain contrat requis = C-05 (ne pas démarrer sans ordre explicite)

### 2026-10-08 — C-02-CLOSE — Substrat spatial VALIDÉ (clôture documentaire)

- **Intention :** clôturer formellement le contrat opérationnel C-02 après validation humaine et audit final PASS.
- **Statut :** VALIDÉ (humain) — **pas de code gameplay** · **C-03 non commencé** · Case B reste **suspendu**
- **Décisions :** **31/31** (A1–F3) — cellules, Dirty, queries, sync, perf, frontières
- **Fichiers :** `CONTRATS/C-02_SUBSTRAT_SPATIAL.md` · `CONTRATS/00_SUIVI_CONTRATS.md` → compteur **2 / 16**
- **Design Gate :** aucune modification
- **Suite :** prochain ordre officiel = C-03 (addendum* — ne pas démarrer sans ordre explicite)

### 2026-10-07 — T9-CLOSE — Preuve S3 Cas A VALIDÉ (clôture documentaire)

- **Intention :** enregistrer la validation humaine PIE + audit final PASS ; roadmap T9 → VALIDÉ ; sync `docs/index.html`.
- **Statut :** VALIDÉ (humain) — **pas de code gameplay supplémentaire** · **aucun travail suivant démarré**
- **Preuve PIE :** `gf.Project.SmokeCohortS3` → ok=1 · Intention→Analyze→WorkSite AlreadyReady→U1 Extract Timber→A→U2 Withdraw/cargo/Deposit B→U3 Complete→En service→obs PE
- **UnrealEditor-Cmd :** interrompu au lancement — **non bloquant** ; preuve fonctionnelle = smoke PIE uniquement
- **Roadmap :** **9/9 VALIDÉ (100 %)** · `nextSliceId=null` · cohorte S3 Cas A **clôturée**
- **LinkedPitStockId :** conserve identité Stock A PE · risque sémantique Pit/LevelPad documenté · **ne pas renommer**
- **Design Gate :** aucune modification
- **Suite :** aucun travail gameplay hors ordre explicite

### 2026-10-07 — T9-S3 — Preuve end-to-end cohorte Cas A (VALIDATION)

- **Intention :** intégrer T1–T8 en une preuve jouable S3 Cas A (pas forêt complète).
- **Statut :** code livré · roadmap T9 = **VALIDATION** · **pas VALIDÉ**
- **Chaîne :** Intention → Analyze → WorkSite AlreadyReady → U1 Extract Timber → Stock A → U2 Withdraw/cargo/Deposit B → U3 Construct → Complete → En service → lecture PE C6
- **Agent :** Extract/Haul utilisent `Task.OperationalResourceKey` (fallback SpoilDirt legacy si unset) · Build Construction → `MarkConstructionComplete`
- **ExpandWorkSite :** crée Analyze→Extract→Transport→Build (caps Extraction/Transport/Construction) · **aucune** Terraform
- **Smoke :** `gf.Project.SmokeCohortS3` · spawn U1/U2/U3 · autonomie instantanée · ok si A→0 B≥1 Complete EnService
- **Preuve PIE (technique) :** ok=1 steps=24 · Analyze/Extract/Haul/Construct=Completed · A=0→0 B=0→1 · Complete=1 EnService=1 · C6 PE live · CasA no terraform
- **Non modifié :** LinkedPitStockId (Stock A) · HUD FWSG · EconomyComponent/Wood · Design Gate · LevelPad Spoil
- **Suite :** validation humaine formelle → VALIDÉ (clôture documentaire)

### 2026-10-07 — T8-CLOSE — C6 observabilité PhysicalEconomy VALIDÉ (clôture documentaire)

- **Intention :** enregistrer la validation humaine PIE de T8/C6 ; roadmap T8 → VALIDÉ ; sync `docs/index.html`.
- **Statut :** VALIDÉ (humain) — **pas de code gameplay supplémentaire** · **T9 non démarré**
- **Preuve PIE :** `gf.Project.SmokeCohortObservability` · Stock A id=1 Timber 0.0→0.0 · Stock B id=2 Timber 0.0→1.0 · A stable · B +1 · PE live · no mirror · ok=1 · EnService=0 tant que Complete=0
- **Roadmap :** 8/9 VALIDÉ (89 %) · prochaine = T9 · T9 reste À FAIRE
- **Design Gate :** aucune modification
- **Suite :** T9 Preuve bout-en-bout uniquement sur ordre explicite

### 2026-10-07 — T8-C6 — Observabilité PhysicalEconomy Stock A/B Timber (VALIDATION)

- **Intention :** contrat C6 — état Timber Stock A/B observable depuis PhysicalEconomy (pas HUD legacy).
- **Statut :** code livré · roadmap T8 = **VALIDATION** · **pas VALIDÉ**
- **Changement :** `GardenFervorCohortObservabilityHelpers` (lecture live `GetAvailable` + clé PE Timber) · `GetCohortPhysicalEconomyStatusLine` · smoke `gf.Project.SmokeCohortObservability` · T7 service B délègue à la même lecture Live
- **Preuve attendue PIE :** lecture initiale → `Deposit` Timber Stock B → relecture ; A inchangé ; B augmente ; pas de miroir
- **Non modifié :** LinkedPitStockId · HUD FWSG · EconomyComponent · Design Gate · T9
- **Suite :** validation humaine PIE → VALIDÉ → T9 sur ordre

### 2026-10-07 — T7-CLOSE — C5 Complete ≠ En service VALIDÉ (clôture documentaire)

- **Intention :** enregistrer la validation humaine PIE de T7/C5 ; roadmap T7 → VALIDÉ ; sync `docs/index.html`.
- **Statut :** VALIDÉ (humain) — **pas de code gameplay supplémentaire** · **T8 non démarré**
- **Preuve PIE :** `gf.Project.SmokeCohortService` · step1 Complete sans Timber → InService=0 ok=1 · step2 Stock B Timber → InService=1 ok=1 · pas de Withdraw
- **Roadmap :** 7/9 VALIDÉ (78 %) · prochaine = T8 · T8…T9 restent À FAIRE
- **Rappel :** critère S3 uniquement — **pas** une règle universelle pour tous les chantiers
- **Design Gate :** aucune modification
- **Suite :** T8 Observabilité uniquement sur ordre explicite

### 2026-10-07 — T7-C5 — Complete ≠ En service S3 (VALIDATION)

- **Intention :** contrat C5 — Achevé distinct d’En service ; critère cohorte Stock B Timber.
- **Statut :** code livré · roadmap T7 = **VALIDATION** · **pas VALIDÉ**
- **Changement :** `bConstructionComplete` / `bInService` · `GardenFervorRefreshCohortServiceState` · smoke `gf.Project.SmokeCohortService`
- **Critère S3 :** Complete ∧ `GetAvailable(Stock B, Timber) > 0` → En service · **pas** de consommation · **pas** coût inventé · **pas** règle universelle
- **Stock B :** `LinkedStockId` · clé PE `Timber` · Stock A non utilisé pour le service
- **Suite :** validation humaine PIE → VALIDÉ → T8 sur ordre

### 2026-10-07 — T6-CLOSE — C4 Intention → Project VALIDÉ (clôture documentaire)

- **Intention :** enregistrer la validation humaine PIE de T6/C4 ; roadmap T6 → VALIDÉ ; sync `docs/index.html`.
- **Statut :** VALIDÉ (humain) — **pas de code gameplay supplémentaire** · **T7 non démarré**
- **Preuve PIE :** `gf.Project.SmokeCohortIntention` → Project Draft `WorkSite` · aucun spend · aucun expand · aucune unité
- **Roadmap :** 6/9 VALIDÉ (67 %) · prochaine = T7 · T7…T9 restent À FAIRE
- **Note :** log Niagara observé en PIE hors périmètre T6 (non anomalie C4)
- **Design Gate :** aucune modification
- **Suite :** T7 En service S3 uniquement sur ordre explicite

### 2026-10-07 — T6-C4 — Intention → Project smoke (VALIDATION)

- **Intention :** contrat C4 — Intention joueur → Project sans économie legacy.
- **Statut :** code livré · roadmap T6 = **VALIDATION** · **pas VALIDÉ**
- **Changement :** `CreateProjectFromIntention` · `OriginIntention` · smoke `SmokeStartCohortIntentionNear` / `gf.Project.SmokeCohortIntention`
- **Résultat :** Project Draft `WorkSite` · intention `Smoke_Cohort_C4` · **pas** ExpandWorkSite · **pas** unités · **pas** TrySpend/BeginPlace/EconomyComponent
- **Non modifié :** T1–T5 · LinkedPitStockId · HUD FWSG · Design Gate · T7+
- **Suite :** validation humaine PIE (console) → VALIDÉ → T7 sur ordre

### 2026-10-07 — T5-CLOSE — C3 WorkSite Cas A VALIDÉ (clôture documentaire)

- **Intention :** enregistrer la validation humaine de T5/C3 ; roadmap T5 → VALIDÉ ; sync `docs/index.html`.
- **Statut :** VALIDÉ (humain) — **pas de code gameplay supplémentaire** · **T6 non démarré**
- **Roadmap :** 5/9 VALIDÉ (56 %) · prochaine = T6 · T6…T9 restent À FAIRE
- **Contrôle technique :** T1→T5 PASS · LinkedPitStockId PASS (risque sémantique noté, non bloquant)
- **Note conservée :** `LinkedPitStockId` = identité Stock A PE cohorte — risque sémantique Pit/LevelPad ; WorkSite ne réactive pas la legacy ; **ne pas renommer** · T4 intact
- **Design Gate :** aucune modification
- **Suite :** T6 Intention smoke uniquement sur ordre explicite

### 2026-10-07 — T5-C3 — Extension site générique WorkSite Cas A (VALIDATION)

- **Intention :** contrat C3 — préparation/extension de site paramétrée ; Cas A = déjà prêt, sans Terraform.
- **Statut :** code livré · roadmap T5 = **VALIDATION** · **pas VALIDÉ**
- **Changement :** `SitePrep` params + `GardenFervorApplySitePreparation` · objective `WorkSite` · `ExpandWorkSite` · LevelPad inchangé
- **Cas A :** `AlreadyReady` → `bSiteReady` · stocks A/B via EnsureCohort · **aucune** Raise/Lower/Paint · **pas** ExpandForest · **pas** Extract/Transport/Build
- **LinkedPitStockId :** mapping Stock A PE uniquement sur WorkSite ; ExpandLevelPad conserve sa sémantique Spoil pit (legacy parallèle) — pas de rename
- **Design Gate :** aucune modification
- **Suite :** validation humaine T5 → VALIDÉ → T6 sur ordre

### 2026-10-07 — T4-CLOSE — Stocks A/B VALIDÉ (clôture documentaire)

- **Intention :** enregistrer la validation humaine de T4 ; roadmap T4 → VALIDÉ ; sync `docs/index.html`.
- **Statut :** VALIDÉ (humain) — **pas de code gameplay supplémentaire** · **T5 non démarré**
- **Roadmap :** 4/9 VALIDÉ · prochaine = T5 · T5…T9 restent À FAIRE
- **Contrôle technique :** T1+T2+T3+T4 PASS · aucune anomalie
- **Note pour T5 :** `LinkedPitStockId` sert d’identité Stock A cohorte (mapping PE) **sans** réactivation Pit/Quarry/Worker — **risque sémantique à surveiller à l’expand** ; ne pas modifier T4 pour renommer
- **Design Gate :** aucune modification
- **Suite :** T5 Expand Cas A uniquement sur ordre explicite

### 2026-10-07 — T4-STOCKS — Stocks A/B PhysicalEconomy (VALIDATION)

- **Intention :** contrat T4 — deux stocks PE distincts liés au Project (structure, pas transport).
- **Statut :** code livré · roadmap T4 = **VALIDATION** · **pas VALIDÉ**
- **Changement :** `GardenFervorEnsureCohortStocks` + accessors A/B ; mapping `LinkedPitStockId`=A · `LinkedStockId`=B ; commentaires T4 sur `ProjectTypes`
- **API :** `PhysicalEconomy::CreateStock` existant — pas de seconde architecture
- **Non modifié :** Transport/Extract/Build · T1–T3 · Expand (T5) · Design Gate · legacy Wood
- **Suite :** validation humaine T4 → VALIDÉ → T5 sur ordre

### 2026-10-07 — T3-CLOSE — C2 capacités U1/U2/U3 VALIDÉ (clôture documentaire)

- **Intention :** enregistrer la validation humaine de T3/C2 ; roadmap T3 → VALIDÉ ; sync `docs/index.html`.
- **Statut :** VALIDÉ (humain) — **pas de code gameplay supplémentaire** · **T4 non démarré**
- **Roadmap :** 3/9 VALIDÉ · prochaine = T4 · T4…T9 restent À FAIRE
- **Contrôle technique :** T1+T2+T3 PASS · aucune anomalie
- **Design Gate :** aucune modification
- **Suite :** T4 Stocks A/B uniquement sur ordre explicite

### 2026-10-07 — T3-C2 — Capacités U1/U2/U3 (VALIDATION)

- **Intention :** contrat C2 — clés de capacités Extraction / Transport / Construction + rôles cohorte U1/U2/U3 sur UnitDefinition.
- **Statut :** code livré · roadmap T3 = **VALIDATION** · **pas VALIDÉ**
- **Changement :** `GardenFervorUnitCapabilityTypes.h` (enum + helpers) ; commentaire C2 sur `UGardenFervorUnitDefinition::Capabilities`
- **Représentation :** U1→Extraction · U2→Transport · U3→Construction via `GardenFervorCohortUnitCapabilities` — pas de sous-classes C++
- **Non modifié :** Extract/Haul/Build opérationnels · Worker legacy · Timber · Design Gate · T4…
- **Suite :** validation humaine T3 → VALIDÉ → T4 sur ordre

### 2026-10-07 — T2-CLOSE — C1 OperationalResourceKey VALIDÉ (clôture documentaire)

- **Intention :** enregistrer la validation humaine de T2/C1 ; roadmap T2 → VALIDÉ ; sync `docs/index.html`.
- **Statut :** VALIDÉ (humain) — **pas de code gameplay supplémentaire** · **T3 non démarré**
- **Roadmap :** 2/9 VALIDÉ · prochaine = T3 · T3…T9 restent À FAIRE
- **Contrôle technique :** T1+T2 PASS · aucune anomalie
- **Design Gate :** aucune modification
- **Suite :** T3 C2 U1/U2/U3 uniquement sur ordre explicite

### 2026-10-07 — T2-C1 — OperationalResourceKey sur Task (VALIDATION)

- **Intention :** contrat C1 — tâche porte une clé PE générique pour Extract/Transport futurs.
- **Statut :** code livré · roadmap T2 = **VALIDATION** · **pas VALIDÉ**
- **Changement :** `FGardenFervorTaskRecord::OperationalResourceKey` (`FName`, défaut None) dans `GardenFervorTaskTypes.h`
- **Usage cohorte :** assigner via `GardenFervorPhysicalResourceKey(Timber)` — pas de branche `if Timber`
- **Non modifié :** agent Extract/Haul (encore Spoil hardcodé — tranche ultérieure) · legacy · Design Gate
- **Suite :** validation humaine T2 → VALIDÉ → T3 sur ordre

### 2026-10-07 — T1-CLOSE — C7 Timber VALIDÉ (clôture documentaire)

- **Intention :** enregistrer la validation humaine de T1/C7 ; roadmap T1 → VALIDÉ ; sync `docs/index.html`.
- **Statut :** VALIDÉ (humain) — **pas de code gameplay supplémentaire** · **T2 non démarré**
- **Roadmap :** 1/9 VALIDÉ · prochaine = T2 · T2…T9 restent À FAIRE
- **Design Gate :** aucune modification
- **Suite :** T2 C1 ResourceKey uniquement sur ordre explicite

### 2026-10-06 — T1-TIMBER — C7 clé PE `Timber` (VALIDATION)

- **Intention :** implémenter uniquement C7 — ResourceKey officielle `Timber` dans PhysicalEconomy types.
- **Statut :** code livré · roadmap T1 = **VALIDATION** · **pas VALIDÉ** (attente humaine)
- **Changement :** `GardenFervorPhysicalResourceTypes.h` — enum + `GardenFervorPhysicalResourceKey(Timber)` → `FName("Timber")`
- **Non modifié :** EconomyComponent · Wood legacy · Harvest · unités · stocks · tasks · terraform · Design Gate
- **Suite :** validation humaine T1 → VALIDÉ roadmap → T2 sur ordre

### 2026-10-06 — ROADMAP-PAGES — Publication GitHub Pages via `docs/index.html`

- **Intention :** exposer la roadmap à `https://JosephV01.github.io/GardenFervor/` depuis `/docs`.
- **SoT inchangée :** `Plan de production/Roadmap/src/roadmap.data.js`
- **Sync :** écrit aussi `docs/index.html` (autonome) ; doc activation manuelle `docs/GITHUB_PAGES.md`
- **Gameplay / Design Gate :** aucune modification
- **Suite :** activer Pages dans Settings GitHub (branch `main` / folder `/docs`) si pas encore fait

### 2026-10-06 — ROADMAP-INDEX — Roadmap HTML renommée `index.html`

- **Intention :** nom fixe `index.html` pour publication / accès en ligne (GitHub Pages).
- **Avant → Après :** `GardenFervor_ROADMAP.html` → `Plan de production/Roadmap/index.html`
- **Règle :** la vue roadmap **reste toujours** `index.html` ; sync met à jour ce fichier uniquement.
- **Suite :** push GitHub

### 2026-10-06 — ROADMAP-PROD — Roadmap de production (suivi T1–T9)

- **Intention :** mettre en place la vue de pilotage de production avant T1, distincte Design Gate / Plan / ETAT / HISTORIQUE.
- **Statut :** VALIDÉ (outil de suivi) — **pas un nouveau DG** · **≠ démarrage T1**
- **Source de vérité :** `Plan de production/Roadmap/src/roadmap.data.js`
- **Vue :** `Plan de production/Roadmap/index.html` (**nom fixe** pour publication en ligne) — sync `scripts/syncRoadmap.mjs`
- **État initial :** T1–T9 = À FAIRE · 0/9 VALIDÉ · prochaine = T1 · aucune EN COURS
- **Règle :** code terminé ≠ VALIDÉ (validation humaine Plan requise)
- **Design Gate / gameplay :** **aucune modification**
- **Suite :** ordonner T1 puis passer la tranche en EN COURS dans la roadmap

### 2026-10-06 — PLAN-PROD-S3 — Contrôle final PASS + Plan de production cohorte S3

- **Intention :** contrôler la readiness finale puis ouvrir le Plan de production opérationnel de la preuve S3 Cas A (documentaire).
- **Statut :** VALIDÉ (process) — **pas un nouveau DG** · **≠ démarrage code**
- **Contrôle final :** `PASS — PRÊT POUR IMPLÉMENTATION CONTRÔLÉE` — `Audit de readiness pré-implémentation/CONTROLE_FINAL_PRE_IMPLEMENTATION_COHORTE.md`
- **Plan :** `Plan de production/PLAN_PRODUCTION_COHORTE_S3.md` — tranches T1…T9 (C7→C1→C2→Stocks→C3→C4→C5→C6→preuve)
- **Périmètre :** preuve Cas A seulement ; Case B Terraform / écologie / UI / save / Ages hors plan
- **Design Gate :** **aucune modification**
- **Code / assets :** **aucune modification** · **implémentation non démarrée**
- **Suite :** ordonner T1 (Timber) explicitement pour commencer l’implémentation contrôlée

### 2026-10-06 — FORMALISATION-03-ARB — Arbitrages C7 · C4 · C5 · C6 ENREGISTRÉS

- **Intention :** formaliser les 4 arbitrages humains validés (support `ARBITRAGES_C7_C4_C5_C6.md`), sans implémentation ni Design Gate.
- **Statut :** VALIDÉ (décision préparatoire readiness) — **pas un nouveau DG** · **≠ autorisation d’implémenter**
- **C7 :** ResourceKey PE officielle = **`Timber`** (PascalCase) ; vérité `PhysicalResourceTypes.h` ; `Wood` = legacy seulement
- **C4 :** Intention→Project via mécanisme dédié minimal ; sans EconomyComponent / TrySpend / BeginPlace / Ages / coûts FWSG ; pas d’UI finale
- **C5 :** Achevé ≠ En service ; réussite cohorte S3 = Achevé + Stock B Timber > 0 → En service ; critère **cohorte** (pas universel jeu) ; pas de coût inventé
- **C6 :** Observabilité smoke/PE ; minimum chaîne complète + blocage ; HUD FWSG jamais vérité ; pas UI DG-13
- **Cohérence :** complète le nom de clé laissé ouvert en Formalisation 01 ; aligne Formalisation 02 S3/Option A — **aucune contradiction bloquante**
- **Doc :** `Audit de readiness pré-implémentation/FORMALISATION_03_ARBITRAGES_C7_C4_C5_C6.md`
- **Design Gate :** **aucune modification**
- **Code / assets / smoke :** **aucune modification** · **implémentation non démarrée**
- **Suite :** dernier contrôle avant implémentation ; code cohorte **uniquement sur ordre explicite** (DG-14.4)

### 2026-10-06 — FORMALISATION-02-KIT — Kit minimal cohorte forestière ARBITRÉ

- **Intention :** formaliser les arbitrages humains post-clarifications 01–05 (readiness) en kit officiel de preuve DG-14.3, sans implémentation ni modification Design Gate.
- **Statut :** VALIDÉ (décision préparatoire readiness) — **pas un nouveau DG** · **≠ autorisation d’implémenter**
- **Service :** S3 — production → transport → construction minimale → En service → conséquence fonctionnelle observable
- **Bois :** Option A — disponibilité Stock B (PhysicalEconomy) ; aucun coût inventé pour la preuve
- **Stocks :** A → transport → B ; A≠B obligatoires ; indépendants PE ; pas d’Owner
- **Roster :** U1 Exploitation (`Extraction` + ResourceKey) · U2 Transport distinct (Withdraw→cargo→Deposit) · U3 Construction/Service (rôle distinct, pas Worker fourre-tout)
- **Analyse :** `Analyze` générique — pas de ForestAnalysis
- **Terraform :** conditionnel ; 1ʳᵉ preuve = Cas A (terrain déjà prêt) ; Cas B complémentaire ultérieur
- **Anti-hardcode :** pas d’`ExpandForest()` ; données / caps / tâches / stocks / paramètres Project
- **Hors cohorte :** infra complète, catalogue bâtiments, prod continue, écologie, Ages/recherche, legacy économie/Harvest/Wood AoE/TC, routes, Owner stocks, lots, UI complète, etc.
- **Doc :** `Audit de readiness pré-implémentation/FORMALISATION_02_KIT_COHORTE_FORESTIERE.md`
- **Design Gate :** **aucune modification** (DG-14 inchangé ; pas de DG-15)
- **Code / assets :** **aucune modification** · **implémentation non démarrée**
- **Plan de production :** non rempli (aucune trace artificielle)
- **Suite :** préparation de l’implémentation contrôlée sur ordre explicite (DG-14.4) — **pas d’implémentation ici**

### 2026-10-06 — FORMALISATION-01-ECO — Fondation économie / bois / stocks (cohorte) ARBITRÉE

- **Intention :** formaliser les arbitrages humains post-clarifications 01–03 (readiness), sans implémentation ni modification Design Gate.
- **Statut :** VALIDÉ (décision préparatoire readiness) — **pas un nouveau DG**
- **Autorité cohorte :** `PhysicalEconomy` seule pour ressources/quantités/stocks/mouvements ; legacy Economy/ResourcePool/Ages/Harvest/HUD FWSG = non-autorité
- **Bois :** clé PE + float agrégé + StockId localisé ; pas de Wood AoE / lots / masse-volume
- **Stocks :** indépendants, `StockId` int32 ; pas d’Owner runtime ; références via Project/Task ; persist identité+contenu **plus tard** (non implémentée)
- **Transport :** Source/Dest/Reservation StockId ; Withdraw→cargo→Deposit ; Spoil/Fill hors économie joueur
- **Progression / coûts :** Ages/recherche hors cohorte ; aucun coût construction inventé ici
- **Doc :** `Audit de readiness pré-implémentation/FORMALISATION_01_FONDATATION_ECONOMIE_BOIS_STOCKS.md`
- **Suite :** bloquant readiness n°1 traité → kit/catalogue cohorte (DG-14.3) sur ordre ; **pas d’implémentation ici**

### 2026-10-06 — DG-14-CLOSE — Conditions de validation et passage à l’implémentation VALIDÉ (clôture section)

- **Intention :** clôturer DG-14 après 4/4 items VALIDÉ et audit PASS — CLÔTURABLE.
- **Statut :** VALIDÉ (statut section `DG-14` uniquement ; 4/4 items déjà VALIDÉ inchangés)
- **Avant → Après :** section `DG-14` sans statut de clôture → `status: 'VALIDÉ'`
- **Audit :** chaîne 14.1→14.2→14.3→14.4 cohérente ; frontières claires ; non circulaire ; compatible DG-00→DG-13 ; aucune correction indispensable
- **Rappel :** clôture = conditions de passage définies ; **≠ démarrage d’implémentation** ; **≠ cohorte construite/validée**
- **Sync :** JSON + HTML via `node scripts/syncStandaloneFromJs.mjs`
- **Suite :** démarrage implémentation contrôlée / cohorte **uniquement sur ordre explicite**

### 2026-10-06 — DG-14.4 — Passage en implémentation contrôlée VALIDÉ

- **Intention :** inscrire la décision FAISABLE (reformulée) pour `14.4` uniquement.
- **Statut :** VALIDÉ — `14.4` ; **`14.1`–`14.3` inchangés** ; **parent DG-14 ouvert** (non clôturé)
- **Avant → Après :** DG-14 3/4 → **4/4 VALIDÉ**
- **Points clés :** conditions démarrage 1–4 ; limite = cohorte seule ; preuve réversible ; validation humaine après construction ; ≠ production de masse / validation auto
- **Sync :** JSON + HTML via `node scripts/syncStandaloneFromJs.mjs`
- **Suite :** clôture parent DG-14 sur ordre explicite — **aucune implémentation ni cohorte démarrée ici**

### 2026-10-06 — DG-14.3 — Cohorte minimale de preuve VALIDÉ

- **Intention :** inscrire la décision confirmée pour `14.3` uniquement (faisabilité FAISABLE).
- **Statut :** VALIDÉ — `14.3` ; **`14.1`/`14.2` inchangés** ; **`14.4` et parent DG-14 ouverts**
- **Avant → Après :** DG-14 2/4 → **3/4 VALIDÉ**
- **Points clés :** plus petit ensemble jouable ; 9 critères ; ancrage 12.5/02.11 forestier ; preuve nécessaire ≠ substitut 14.1/14.2/14.4 ; pas de catalogue complet immédiat
- **Sync :** JSON + HTML via `node scripts/syncStandaloneFromJs.mjs`
- **Suite :** `14.4` sur ordre explicite — pas de démarrage de cohorte contenu ni d’implémentation ici

### 2026-10-06 — DG-14.2 — Gate de cohérence globale VALIDÉ

- **Intention :** inscrire la décision confirmée pour `14.2` uniquement.
- **Statut :** VALIDÉ — `14.2` ; **`14.1` inchangé** ; **`14.3`–`14.4` et parent DG-14 ouverts**
- **Avant → Après :** DG-14 1/4 → **2/4 VALIDÉ**
- **Points clés :** contradictions bloquantes = vision / règles fondamentales / dépendances critiques / source de vérité / comportement observable ; secondaires non bloquants ; distinct de 14.1
- **Sync :** JSON + HTML via `node scripts/syncStandaloneFromJs.mjs`
- **Suite :** `14.3` sur ordre explicite — pas d’implémentation ici

### 2026-10-06 — DG-14.1 — Critère de complétude VALIDÉ

- **Intention :** inscrire la décision confirmée pour `14.1` uniquement.
- **Statut :** VALIDÉ — `14.1` ; **`14.2`–`14.4` et parent DG-14 ouverts**
- **Avant → Après :** DG-14 0/4 → **1/4 VALIDÉ**
- **Points clés :** complétude suffisante (6 critères) ; implémenter pour valider le comportement attendu, pas pour épuiser toute question théorique
- **Sync :** JSON + HTML via `node scripts/syncStandaloneFromJs.mjs`
- **Suite :** `14.2` sur ordre explicite — pas d’implémentation ici

### 2026-10-06 — DG-13-CLOSE — UX et lisibilité VALIDÉ (clôture section)

- **Intention :** clôturer DG-13 après 5/5 items VALIDÉ et audit PASS.
- **Statut :** VALIDÉ (statut section `DG-13` uniquement ; 5/5 items déjà VALIDÉ inchangés)
- **Avant → Après :** section `DG-13` sans statut de clôture → `status: 'VALIDÉ'`
- **Audit :** cohérent avec `00.6`, `04.7`, `07.6`, `11.4`, `11.6`/`11.7`, `N4`, DG-12 ; aucune régression microgestion / arbre de bonus / internes permanents
- **Sync :** JSON + HTML via `node scripts/syncStandaloneFromJs.mjs`
- **Suite :** prochain sujet Design Gate sur ordre explicite — **pas de questionnaire du bloc suivant** dans cette opération

### 2026-10-06 — DG-13.5 — Éviter la surcharge VALIDÉ

- **Intention :** inscrire la décision confirmée pour `13.5` uniquement.
- **Statut :** VALIDÉ — `13.5` ; **`13.1`–`13.4` inchangés** ; **parent DG-13 non clôturé**
- **Avant → Après :** DG-13 4/5 → **5/5 VALIDÉ**
- **Points clés :** primaire/secondaire/détail/alerte ; critère utilité décisionnelle ; jamais permanents V2/H ; conforme N4
- **Sync :** JSON + HTML via `node scripts/syncStandaloneFromJs.mjs`
- **Suite :** audit / clôture parent DG-13 sur ordre explicite — pas de questionnaire DG-14 ici

### 2026-10-06 — DG-13.4 — Comprendre la progression VALIDÉ

- **Intention :** inscrire la décision confirmée pour `13.4` uniquement.
- **Statut :** VALIDÉ — `13.4` ; **`13.1`–`13.3` inchangés** ; **`13.5` et parent DG-13 ouverts**
- **Avant → Après :** DG-13 3/5 → **4/5 VALIDÉ**
- **Points clés :** progression = ouverture (pas arbre de bonus) ; possibilité → moyen → transformation ; conforme `07.6`
- **Sync :** JSON + HTML via `node scripts/syncStandaloneFromJs.mjs`
- **Suite :** `13.5` sur ordre explicite — pas de clôture DG-13 ici

### 2026-10-06 — DG-13.3 — Comprendre une unité VALIDÉ

- **Intention :** inscrire la décision confirmée pour `13.3` uniquement.
- **Statut :** VALIDÉ — `13.3` ; **`13.1`/`13.2` inchangés** ; **`13.4`–`13.5` et parent DG-13 ouverts**
- **Avant → Après :** DG-13 2/5 → **3/5 VALIDÉ**
- **Points clés :** permanent = État + activité + destination ; à la demande = motif/besoin/prochaine action ; internes cachés ; conforme `04.7`
- **Sync :** JSON + HTML via `node scripts/syncStandaloneFromJs.mjs`
- **Suite :** `13.4` sur ordre explicite — pas de clôture DG-13 ici

### 2026-10-06 — DG-13.2 — Comprendre un blocage VALIDÉ

- **Intention :** inscrire la décision confirmée pour `13.2` uniquement.
- **Statut :** VALIDÉ — `13.2` ; **`13.1` inchangé** ; **`13.3`–`13.5` et parent DG-13 ouverts**
- **Avant → Après :** DG-13 1/5 → **2/5 VALIDÉ**
- **Points clés :** Cause principale → Conséquence → Action ; Priorité = attention ; secondaires à la demande ; conforme V4/04.7/11.6
- **Sync :** JSON + HTML via `node scripts/syncStandaloneFromJs.mjs`
- **Suite :** `13.3` sur ordre explicite — pas de clôture DG-13 ici

### 2026-10-06 — DG-13.1 — Comprendre ce qui est disponible VALIDÉ

- **Intention :** inscrire la décision confirmée pour `13.1` uniquement.
- **Statut :** VALIDÉ — `13.1` ; **`13.2`–`13.5` et parent DG-13 inchangés / ouverts**
- **Avant → Après :** DG-13 0/5 → **1/5 VALIDÉ**
- **Points clés :** Disponible / Verrouillé / raison courte (V4) / prochaine étape sans solution chantier (`11.4`) ; pas d’arbre technique
- **Sync :** JSON + HTML via `node scripts/syncStandaloneFromJs.mjs`
- **Suite :** `13.2` sur ordre explicite — pas de clôture DG-13 ici

### 2026-10-06 — DG-12-CLOSE — Interaction entre les systèmes VALIDÉ (clôture section)

- **Intention :** clôturer DG-12 après 6/6 items VALIDÉ et audit PASS.
- **Statut :** VALIDÉ (statut section `DG-12` uniquement ; 6/6 items déjà VALIDÉ inchangés)
- **Avant → Après :** section `DG-12` sans statut de clôture → `status: 'VALIDÉ'`
- **Sync :** JSON + HTML via `node scripts/syncStandaloneFromJs.mjs`
- **Suite :** prochain sujet Design Gate sur ordre explicite — **pas de questionnaire du bloc suivant** dans cette opération

### 2026-10-06 — DG-12-ITEMS — Interaction entre les systèmes 12.1–12.6 VALIDÉ

- **Intention :** inscrire les décisions confirmées du questionnaire DG-12 (matrices + preuve + contradictions).
- **Statut :** VALIDÉ — `12.1` à `12.6` ; **parent DG-12 non clôturé**
- **Avant → Après :** DG-12 0/6 → **6/6 VALIDÉ**
- **Points clés :** matrices hybrides déclaratives ; rail/maintenance différés ; preuve = petite exploitation forestière ; aucune contradiction bloquante fondatrice
- **Sync :** JSON + HTML via `node scripts/syncStandaloneFromJs.mjs`
- **Suite :** audit / clôture parent DG-12 sur ordre explicite — pas de questionnaire DG-13 ici

### 2026-10-06 — DG-11-CLOSE — Chantiers et exécution procédurale VALIDÉ (clôture section)

- **Intention :** clôturer DG-11 après 8/8 items VALIDÉ et audit PASS.
- **Statut :** VALIDÉ (statut section `DG-11` uniquement ; 8/8 items déjà VALIDÉ inchangés)
- **Avant → Après :** section `DG-11` sans statut de clôture → `status: 'VALIDÉ'`
- **Sync :** JSON + HTML via `node scripts/syncStandaloneFromJs.mjs`
- **Suite :** prochain sujet Design Gate sur ordre explicite — **pas de questionnaire du bloc suivant** dans cette opération

### 2026-10-06 — DG-11-ITEMS — Chantiers 11.6 / 11.7 / 11.8 VALIDÉ

- **Intention :** inscrire les décisions confirmées du questionnaire DG-11 (blocs A–C).
- **Statut :** VALIDÉ — `11.6`, `11.7`, `11.8` ; **`11.1`–`11.5` inchangés** ; **parent DG-11 non clôturé**
- **Avant → Après :** DG-11 5/8 → **8/8 VALIDÉ**
- **Points clés :** recalcul chantier ≠ 04.5 ; fin Achevé/En service/Bloqué/Annulé/Abandonné/Récupération ; rejouabilité contextuelle sans RNG
- **Sync :** JSON + HTML via `node scripts/syncStandaloneFromJs.mjs`
- **Suite :** audit / clôture parent DG-11 sur ordre explicite — pas de questionnaire suivant ici

### 2026-10-06 — DG-10-CLOSE — Infrastructures VALIDÉ (clôture section)

- **Intention :** clôturer DG-10 après 5/5 items VALIDÉ et audit PASS.
- **Statut :** VALIDÉ (statut section `DG-10` uniquement ; 5/5 items déjà VALIDÉ inchangés, y compris `10.2`)
- **Avant → Après :** section `DG-10` sans statut de clôture → `status: 'VALIDÉ'`
- **Sync :** JSON + HTML via `node scripts/syncStandaloneFromJs.mjs`
- **Suite :** prochain sujet Design Gate sur ordre explicite — **pas de questionnaire DG-11** dans cette opération

### 2026-10-06 — DG-10-ITEMS — Infrastructures 10.1 / 10.3 / 10.4 / 10.5 VALIDÉ

- **Intention :** inscrire les décisions confirmées du questionnaire DG-10 (blocs A–D).
- **Statut :** VALIDÉ — `10.1`, `10.3`, `10.4`, `10.5` ; **`10.2` inchangé** ; **parent DG-10 non clôturé**
- **Avant → Après :** DG-10 1/5 → **5/5 VALIDÉ**
- **Points clés :** temporaires = installations chantier/carrière/chemin ; permanentes = routes/fixes/eau ; partage hybride N4 ; impacts déclarés DG-10 / comportements DG-09
- **Sync :** JSON + HTML via `node scripts/syncStandaloneFromJs.mjs`
- **Suite :** audit / clôture parent DG-10 sur ordre explicite — pas de questionnaire suivant ici

### 2026-10-06 — DG-09-CLOSE — Environnement et écosystèmes VALIDÉ (clôture section)

- **Intention :** clôturer DG-09 après 6/6 items VALIDÉ et audit PASS.
- **Statut :** VALIDÉ (statut section `DG-09` uniquement ; 6/6 items déjà VALIDÉ inchangés, y compris `09.5`)
- **Avant → Après :** section `DG-09` sans statut de clôture → `status: 'VALIDÉ'`
- **Sync :** JSON + HTML via `node scripts/syncStandaloneFromJs.mjs`
- **Suite :** prochain sujet Design Gate sur ordre explicite — **pas de questionnaire DG-10** dans cette opération

### 2026-10-06 — DG-09-ITEMS — Environnement et écosystèmes 09.1 / 09.2 / 09.3 / 09.4 / 09.6 VALIDÉ

- **Intention :** inscrire les décisions confirmées du questionnaire DG-09 (blocs A–E).
- **Statut :** VALIDÉ — `09.1`, `09.2`, `09.3`, `09.4`, `09.6` ; **`09.5` inchangé** ; **parent DG-09 non clôturé**
- **Avant → Après :** DG-09 1/6 → **6/6 VALIDÉ**
- **Points clés :** couches Sol/Eau/Végétation/État ; Prairie/Forêt/Zone humide ; dirty = maj locale ; impacts fiche+emprise ; grands ouvrages = ordre 02.10/07.7
- **Sync :** JSON + HTML via `node scripts/syncStandaloneFromJs.mjs`
- **Suite :** audit / clôture parent DG-09 sur ordre explicite — pas de questionnaire suivant ici

### 2026-10-06 — DG-08-CLOSE — Terrain et terraform VALIDÉ (clôture section)

- **Intention :** clôturer DG-08 après 5/5 items VALIDÉ et audit PASS.
- **Statut :** VALIDÉ (statut section `DG-08` uniquement ; 5/5 items déjà VALIDÉ inchangés, y compris `08.1`/`08.2`)
- **Avant → Après :** section `DG-08` sans statut de clôture → `status: 'VALIDÉ'`
- **Sync :** JSON + HTML via `node scripts/syncStandaloneFromJs.mjs`
- **Suite :** prochain sujet Design Gate sur ordre explicite — **pas de questionnaire DG-09** dans cette opération

### 2026-10-06 — DG-08-ITEMS — Terrain et terraform 08.3 / 08.4 / 08.5 VALIDÉ

- **Intention :** inscrire les décisions confirmées du questionnaire DG-08 (blocs A–C).
- **Statut :** VALIDÉ — `08.3`, `08.4`, `08.5` ; **`08.1`/`08.2` inchangés** ; **parent DG-08 non clôturé**
- **Avant → Après :** DG-08 2/5 → **5/5 VALIDÉ**
- **Points clés :** travaux Nettoyage/Défrichage/Terrassement ; déblai/remblai joueur ; mobilité = 03.6 ; accès+coûts en DG-08 ; écologie → DG-09 via dirty
- **Sync :** JSON + HTML via `node scripts/syncStandaloneFromJs.mjs`
- **Suite :** audit / clôture parent DG-08 sur ordre explicite — pas de questionnaire suivant ici

### 2026-10-06 — DG-07-CLOSE — Recherche et progression VALIDÉ (clôture section)

- **Intention :** clôturer DG-07 après 7/7 items VALIDÉ et audit PASS.
- **Statut :** VALIDÉ (statut section `DG-07` uniquement ; 7/7 items déjà VALIDÉ inchangés, y compris `07.2`/`07.5`)
- **Avant → Après :** section `DG-07` sans statut de clôture → `status: 'VALIDÉ'`
- **Sync :** JSON + HTML via `node scripts/syncStandaloneFromJs.mjs`
- **Suite :** prochain sujet Design Gate sur ordre explicite — **pas de questionnaire DG-08** dans cette opération

### 2026-10-06 — DG-07-ITEMS — Recherche et progression 07.1 / 07.3 / 07.4 / 07.6 / 07.7 VALIDÉ

- **Intention :** inscrire les décisions confirmées du questionnaire DG-07 (blocs A–E).
- **Statut :** VALIDÉ — `07.1`, `07.3`, `07.4`, `07.6`, `07.7` ; **`07.2`/`07.5` inchangés** ; **parent DG-07 non clôturé**
- **Avant → Après :** DG-07 2/7 → **7/7 VALIDÉ**
- **Points clés :** principal hub ≠ recherche ; schémas durables non consommés ; tech = capacités (pas arbre bonus) ; horizontal prioritaire ; env. = portes 02.10 → effets DG-09
- **Sync :** JSON + HTML via `node scripts/syncStandaloneFromJs.mjs`
- **Suite :** audit / clôture parent DG-07 sur ordre explicite — pas de questionnaire suivant ici

### 2026-10-06 — DG-06-CLOSE — Logistique et transport VALIDÉ (clôture section)

- **Intention :** clôturer DG-06 après 5/5 items VALIDÉ et audit PASS.
- **Statut :** VALIDÉ (statut section `DG-06` uniquement ; 5/5 items déjà VALIDÉ inchangés, y compris `06.4`/N4)
- **Avant → Après :** section `DG-06` sans statut de clôture → `status: 'VALIDÉ'`
- **Sync :** JSON + HTML via `node scripts/syncStandaloneFromJs.mjs`
- **Suite :** prochain sujet Design Gate sur ordre explicite — **pas de questionnaire DG-07** dans cette opération

### 2026-10-06 — DG-06-ITEMS — Logistique 06.1 / 06.2 / 06.5 VALIDÉ

- **Intention :** inscrire les décisions confirmées du questionnaire DG-06 (blocs A–C) ; saturation = N4 sans toucher `06.4`.
- **Statut :** VALIDÉ — `06.1`, `06.2`, `06.5` ; **`06.3`/`06.4` inchangés** ; **parent DG-06 non clôturé**
- **Avant → Après :** DG-06 2/5 → **5/5 VALIDÉ**
- **Points clés :** chemins/routes/spécialisé ; rail/maritime différés ; support auto vs infra stratégique joueur ; chaîne transport = micro-cycle 04.4
- **Sync :** JSON + HTML via `node scripts/syncStandaloneFromJs.mjs`
- **Suite :** audit / clôture parent DG-06 sur ordre explicite — pas de questionnaire suivant ici

### 2026-10-06 — DG-05-CLOSE — Ressources et économie VALIDÉ (clôture section)

- **Intention :** clôturer DG-05 après 4/4 items VALIDÉ et audit PASS.
- **Statut :** VALIDÉ (statut section `DG-05` uniquement ; 4/4 items déjà VALIDÉ inchangés)
- **Avant → Après :** section `DG-05` sans statut de clôture → `status: 'VALIDÉ'`
- **Sync :** JSON + HTML via `node scripts/syncStandaloneFromJs.mjs`
- **Suite :** prochain sujet Design Gate sur ordre explicite — **pas de questionnaire DG-06** dans cette opération

### 2026-10-06 — DG-05-ITEMS — Ressources et économie 05.1–05.4 VALIDÉ

- **Intention :** inscrire les décisions confirmées du questionnaire DG-05 (blocs A–D).
- **Statut :** VALIDÉ — `05.1`…`05.4` ; **parent DG-05 non clôturé** ; DG-00…DG-04 inchangés
- **Avant → Après :** DG-05 0/4 → **4/4 VALIDÉ**
- **Points clés :** taxonomie 5 couches + bois extrait ; chaîne moyenne + lots ; stocks localisés + réservation + priorité 04.2 ; progressives via tech/bâtiments/territoire ; env. minimal → DG-09
- **Sync :** JSON + HTML via `node scripts/syncStandaloneFromJs.mjs`
- **Suite :** audit / clôture parent DG-05 sur ordre explicite — pas de questionnaire suivant ici

### 2026-10-06 — DG-04-CLOSE — Autonomie des unités VALIDÉ (clôture section)

- **Intention :** clôturer DG-04 après 7/7 items VALIDÉ et audit PASS.
- **Statut :** VALIDÉ (statut section `DG-04` uniquement ; 7/7 items déjà VALIDÉ inchangés)
- **Avant → Après :** section `DG-04` sans statut de clôture → `status: 'VALIDÉ'`
- **Sync :** JSON + HTML via `node scripts/syncStandaloneFromJs.mjs`
- **Suite :** prochain sujet Design Gate sur ordre explicite — **pas de questionnaire DG-05** dans cette opération

### 2026-10-06 — DG-04-ITEMS — Autonomie des unités 04.1–04.7 VALIDÉ

- **Intention :** inscrire les décisions confirmées du questionnaire DG-04 (blocs A–G).
- **Statut :** VALIDÉ — `04.1`…`04.7` ; **parent DG-04 non clôturé** ; `03.8`, `02.13`, DG-00…DG-03 inchangés
- **Avant → Après :** DG-04 0/7 → **7/7 VALIDÉ**
- **Points clés :** filtre compatibilité puis priorité/distance ; hybride besoins+affectation ; priorité soft/hard ; déplacement réel+proxies ; micro-cycle = 1 tâche ; replanif événementielle+balayage ; intervention H4 ; lisibilité V4
- **Sync :** JSON + HTML via `node scripts/syncStandaloneFromJs.mjs`
- **Suite :** audit / clôture parent DG-04 sur ordre explicite — pas de DG-05 ici

### 2026-10-06 — DG-03-CLOSE — Unités VALIDÉ (clôture section)

- **Intention :** clôturer DG-03 après 8/8 items VALIDÉ et audit PASS.
- **Statut :** VALIDÉ (statut section `DG-03` uniquement ; 8/8 items déjà VALIDÉ inchangés)
- **Avant → Après :** section `DG-03` sans statut de clôture → `status: 'VALIDÉ'`
- **Sync :** JSON + HTML via `node scripts/syncStandaloneFromJs.mjs`
- **Suite :** prochain sujet Design Gate sur ordre explicite — **pas de questionnaire DG-04** dans cette opération

### 2026-10-06 — DG-03-ITEMS — Unités 03.3 / 03.6 / 03.7 / 03.8 VALIDÉ

- **Intention :** inscrire les décisions confirmées du questionnaire DG-03 (blocs A–D).
- **Statut :** VALIDÉ — uniquement `03.3`, `03.6`, `03.7`, `03.8` ; `03.1`/`03.2`/`03.4`/`03.5` et `02.13` inchangés ; **parent DG-03 non clôturé**
- **Avant → Après :** DG-03 4 VALIDÉ / 4 À DÉFINIR → **8/8 VALIDÉ**
- **Points clés :** familles Extraction/Terraformer/Construction/Analyse/Transport-Logistique ; mobilité mixte hard gate/pénalité ; kit principal+analyse ; canevas+annexes ; autonomie → DG-04
- **Sync :** JSON + HTML via `node scripts/syncStandaloneFromJs.mjs`
- **Suite :** audit / clôture parent DG-03 sur ordre explicite — pas de questionnaire DG-04 ici

### 2026-10-06 — DG-02-CLOSE — Bâtiments et constructions VALIDÉ (clôture section)

- **Intention :** clôturer DG-02 après audit de cohérence PASS et 13/13 items VALIDÉ.
- **Statut :** VALIDÉ (statut section `DG-02` uniquement ; 13/13 items déjà VALIDÉ inchangés, y compris `02.13`)
- **Avant → Après :** section `DG-02` sans statut de clôture → `status: 'VALIDÉ'`
- **Sync :** `designGate.data.json` + HTML via `node scripts/syncStandaloneFromJs.mjs`
- **Suite :** prochain sujet Design Gate sur ordre explicite — **pas de questionnaire DG-03** dans cette opération

### 2026-10-06 — DG-02-AH — Blocs A–H VALIDÉ (02.2–02.4, 02.7–02.10, 02.12)

- **Intention :** inscrire les décisions confirmées des blocs A–H du questionnaire DG-02.
- **Statut :** VALIDÉ — `02.2`, `02.3`, `02.4`, `02.7`, `02.8`, `02.9`, `02.10`, `02.12` ; **`02.13` inchangé** ; `02.1`/`02.5`/`02.6`/`02.11` inchangés
- **Avant → Après :** 5 VALIDÉ / 8 À DÉFINIR → **13/13 VALIDÉ** dans DG-02
- **Points clés :** fiche canevas+annexes ; familles fondatrices (Prod/Transfo et Log/Transport fusionnés ; pas Maintenance ; infra transverse mixte) ; catalogue ≤4 intentions + extraction hybride ; fonctionnement événementiel dominant ; évolution hybride ; déblocages candidats→DG-07 ; deux couches impact env. ; canevas+annexes (02.12)
- **Sync :** JSON + HTML via `node scripts/syncStandaloneFromJs.mjs`
- **Suite :** audit de cohérence DG-02 / clôture section sur ordre explicite — pas de nouveau questionnaire dans cette opération

### 2026-10-06 — DG-02.13-J1J10 — Interdépendances VALIDÉ (J1–J10)

- **Intention :** inscrire les arbitrages confirmés du questionnaire interdépendances.
- **Statut :** VALIDÉ — `02.13` uniquement ; `02.4` et `02.7` mis en cohérence partielle (restent À DÉFINIR) ; aucun autre VALIDÉ modifié
- **Avant → Après :** `02.13` À DÉFINIR (principes) → VALIDÉ (principes + J1–J10) ; `02.4`/`02.7` enrichis des règles relationnelles sans clôturer le reste
- **Arbitrages :** hard/soft orthogonal ; fournisseur vivant ; auto+prioriser/exclure ; minCount vs redondance-Synergie ; OR+filtre ; soft→Dégradé / hard→Bloquée / reprise auto ; événementiel ; cycles Précondition interdits ; signal seulement si problème (V4) ; cibles combinables
- **Sync :** JSON + HTML via `node scripts/syncStandaloneFromJs.mjs`
- **Suite :** audit de cohérence `02.13` puis reprise blocs A–H DG-02

### 2026-10-06 — DG-02.13-INTERDEP — Interdépendances bâtiments (principes inscrits, À DÉFINIR)

- **Intention :** intégrer la conception déclarative des interdépendances entre bâtiments avant de poursuivre le questionnaire DG-02.
- **Statut :** PARTIEL — item **`02.13` À DÉFINIR** avec principes retenus en `decision` (non VALIDÉ) ; enrichissement `02.4` / `02.7` / `02.12` (subpoints) ; **aucun** item déjà VALIDÉ modifié
- **Avant → Après :** absents → `02.13` + champs fiche/fonctionnement liés aux relations ; compteurs items 182 → 183
- **Principes inscrits :** 4 natures (Précondition / Dépendance / Synergie / Opportunité) ; schéma fiche min. ; recherche auto de fournisseurs ; indisponibilité dynamique → états puis reprise auto ; pas de logique spéciale par bâtiment ; éviter cycles impossibles ; joueur ne gère pas manuellement les relations
- **Ouvert :** mapping hard/soft, résolution fournisseurs, redondance, alternatives, dynamiques, visibilité V4 — questionnaire DG-02 suite
- **Sync :** `designGate.data.json` + HTML via `node scripts/syncStandaloneFromJs.mjs`
- **Suite :** questionnaire ciblé **02.13** (puis reprise blocs A–H DG-02)

### 2026-10-06 — DG-01-CLOSE — Boucle fondamentale VALIDÉ (clôture section)

- **Intention :** clôturer DG-01 après audit de cohérence final PASS.
- **Statut :** VALIDÉ (statut section `DG-01` uniquement ; 6/6 items déjà VALIDÉ inchangés)
- **Avant → Après :** section `DG-01` sans statut de clôture → `status: 'VALIDÉ'` ; items `01.1`–`01.6` inchangés
- **Sync :** `designGate.data.json` + HTML via `node scripts/syncStandaloneFromJs.mjs`
- **Reporté aux DG suivants :** fiches/dépendances/vivant/familles/exemple forestier (DG-02) ; unités analyse/exécution + interventions (DG-03/04) ; accès auto + modes transport (DG-06) ; cascades/recherche/transformations majeures (DG-07) ; effets territoriaux vs majeures (DG-09) ; infra support/cycle de vie (DG-10) ; chaîne procédurale + solution cachée (DG-11) ; kit de départ + critères compréhension boucle
- **Suite :** prochain sujet Design Gate sur ordre explicite (pas de questionnaire dans cette opération)

### 2026-10-06 — DG-01.5-01.6 — Résultat fonctionnel + Boucle d’expansion VALIDÉ

- **Intention :** inscrire les décisions confirmées du questionnaire DG-01 (blocs A/B).
- **Statut :** VALIDÉ — uniquement `01.5` et `01.6` ; `01.1`–`01.4` et le reste du Design Gate inchangés
- **Avant → Après :** `01.5` / `01.6` À DÉFINIR → VALIDÉ (formulations auteur)
- **01.5 :** vivant = mise en service + ≥1 fonction utilisable ; réseaux exigés = prérequis durs ; non essentiels = dégradé ; production = conséquence ; maintenance différée ; cascades auto si fonction utilisable + DG-07
- **01.6 :** expansion hybride ; schéma général non obligatoire par bâtiment ; effets territoriaux dès le départ ; transformations majeures plus tard ; transport dès besoin chantier ; modes transport = déblocages ; schéma + exemple + critères de compréhension
- **Sync :** `designGate.data.json` + HTML via `node scripts/syncStandaloneFromJs.mjs`
- **Suite :** prochain sujet Design Gate sur ordre explicite (pas de questionnaire immédiat)

### 2026-10-06 — DG-00-CLOSE — Cadre VALIDÉ (clôture section)

- **Intention :** clôturer DG-00 après audit de cohérence final PASS.
- **Statut :** VALIDÉ (statut section `DG-00` uniquement ; 94/94 items déjà VALIDÉ inchangés)
- **Avant → Après :** section `DG-00` sans statut de clôture → `status: 'VALIDÉ'` ; items 00.1–00.7 + 00.5.* + 00.6.* inchangés
- **Sync :** `designGate.data.json` + `GardenFervor_DESIGN_GATE_v0.1.html` via `node scripts/syncStandaloneFromJs.mjs` (sérialiseur : champ `section.status` si présent)
- **Reporté aux DG suivants :** extensions territoriales ; valeurs de durée ; qualité ressources ; pertes/maintenance/usure ; déblai/remblai joueur ; fiches d’impact bâtiment→eau/sol/végétation ; états écologiques aquatiques ; configurations d’équipement ; économie d’entretien réseaux ; grille logique vs grille de construction ; + K1–K4 / V4 / P1 / Y2
- **Suite :** questionnaire **DG-01** (boucle / règles fondamentales du gameplay)

### 2026-10-06 — DG-00.6-CLOSE — Limites de complexité VALIDÉ

- **Intention :** clôturer DG-00.6 après audit de cohérence PASS.
- **Statut :** VALIDÉ (parent `00.6` uniquement ; 29 sous-items V→P déjà VALIDÉ inchangés)
- **Avant → Après :** parent `00.6` À DÉFINIR → VALIDÉ
- **Changements :** `designGate.js` (parent) ; sync JSON + HTML ; `ETAT_PROJET.md`
- **Contraintes reportées aux DG suivants :** (1) fiches bâtiment = impacts eau/sol/végétation ; (2) K1–K4 avant toute nouvelle mécanique ; (3) garde-fous V4, P1, Y2
- **Suite :** prochain sujet Design Gate (hors clôture cadre DG-00)

### 2026-10-06 — DG-00.6-ITEMS — Limites de complexité : V→P VALIDÉ

- **Intention :** figer lisibilité, charge cognitive, coupe, réalisme, exceptions et critères de validation.
- **Statut :** PARTIEL — 29 sous-items `00.6.V1`…`P3` VALIDÉ ; parent `00.6` reste **À DÉFINIR**
- **Changements :** `designGate.js` ; sync JSON + HTML ; `ETAT_PROJET.md`
- **Suite :** ordre explicite requis pour passer `00.6` → VALIDÉ

### 2026-10-06 — DG-00.5-CLOSE — Périmètre de simulation VALIDÉ

- **Intention :** clôturer DG-00.5 après audit de cohérence PASS.
- **Statut :** VALIDÉ (parent `00.5` uniquement ; 58 sous-items S→X déjà VALIDÉ inchangés)
- **Avant → Après :** parent `00.5` À DÉFINIR → VALIDÉ
- **Changements :** `designGate.js` (parent) ; sync JSON + HTML ; `ETAT_PROJET.md`
- **Reporté à 00.6 (sans modifier 00.5) :** (1) conditions déclenchant couches eau/sol/végétation liées aux bâtiments ; (2) sens opérationnel de « simulé réellement » pour systèmes basse fréquence ; (3) distinction Paint technique vs vocabulaire gameplay
- **Suite :** questionnaire / décisions **00.6**

### 2026-10-06 — DG-00.5-X — Périmètre simu : X1–X3 VALIDÉ

- **Intention :** figer classification des modes de simu, hors périmètre fondateur et règle d’or nuancée.
- **Statut :** PARTIEL — `00.5.X1`…`X3` VALIDÉ ; parent `00.5` reste **À DÉFINIR** (non clôturé)
- **Changements :** `designGate.js` ; sync JSON + HTML ; `ETAT_PROJET.md`
- **Suite :** ordre explicite requis pour passer `00.5` → VALIDÉ, puis `00.6`

### 2026-10-06 — DG-00.5-N — Périmètre simu : N1–N4 VALIDÉ

- **Intention :** figer réseaux hybrides (graphe + zones d’accès), saturation conditionnellement visible, temporaires/durables.
- **Statut :** PARTIEL — `00.5.N1`…`N4` VALIDÉ ; parent `00.5` reste **À DÉFINIR**
- **Changements :** `designGate.js` ; sync JSON + HTML ; `ETAT_PROJET.md`
- **Suite :** questionnaire X1–X3 (sans inscription tant que non confirmé)

### 2026-10-06 — DG-00.5-E — Périmètre simu : E1–E4 VALIDÉ

- **Intention :** figer prairie/forêt/zone humide + mesure état actuel/cible sans peinture du résultat.
- **Statut :** PARTIEL — `00.5.E1`…`E4` VALIDÉ ; parent `00.5` reste **À DÉFINIR**
- **Changements :** `designGate.js` ; sync JSON + HTML ; `ETAT_PROJET.md`
- **Suite :** questionnaire N1–N4 (sans inscription tant que non confirmé)

### 2026-10-06 — DG-00.5-O — Périmètre simu : O1–O4 VALIDÉ

- **Intention :** figer le sol comme couche gameplay/écologie (humidité, fertilité, compaction) indépendante de M4.
- **Statut :** PARTIEL — `00.5.O1`…`O4` VALIDÉ ; parent `00.5` reste **À DÉFINIR**
- **Changements :** `designGate.js` ; sync JSON + HTML ; `ETAT_PROJET.md`
- **Suite :** questionnaire E1–E4 (sans inscription tant que non confirmé)

### 2026-10-06 — DG-00.5-W — Périmètre simu : W1–W4 VALIDÉ

- **Intention :** figer le grain d’hydrologie logique (connectée, non fluide) et sa séparation du visuel M4/UDW.
- **Statut :** PARTIEL — `00.5.W1`…`W4` VALIDÉ ; parent `00.5` reste **À DÉFINIR**
- **Changements :** `designGate.js` ; sync JSON + HTML ; `ETAT_PROJET.md`
- **Suite :** questionnaire O1–O4 (sans inscription tant que non confirmé)

### 2026-10-06 — DG-00.5-G — Périmètre simu : G1–G5 VALIDÉ

- **Intention :** figer le grain de simulation du terrain (hauteur, pente dérivée, surface gameplay, Raise/Lower, nav).
- **Statut :** PARTIEL — `00.5.G1`…`G5` VALIDÉ ; parent `00.5` reste **À DÉFINIR**
- **Changements :** `designGate.js` ; sync JSON + HTML ; `ETAT_PROJET.md`
- **Suite :** questionnaire W1–W4 (sans inscription tant que non confirmé)

### 2026-10-06 — DG-00.5-B — Périmètre simu : B1–B7 VALIDÉ

- **Intention :** figer le grain de simulation bâtiments / infrastructures.
- **Statut :** PARTIEL — `00.5.B1`…`B7` VALIDÉ ; parent `00.5` reste **À DÉFINIR**
- **Changements :** `designGate.js` ; sync JSON + HTML (`syncStandaloneFromJs.mjs`) ; `ETAT_PROJET.md`
- **Suite :** questionnaire G1–G5 (sans inscription tant que non confirmé)

### 2026-10-06 — DG-HTML-SYNC — HTML autonome + miroir JSON

- **Intention :** aligner le HTML standalone et le snapshot JSON sur `designGate.js` sans toucher aux décisions.
- **Statut :** VALIDÉ (sync process)
- **Changements :** `GardenFervor_DESIGN_GATE_v0.1.html` (bloc data) ; `designGate.data.json` ; script `scripts/syncStandaloneFromJs.mjs`
- **Preuves :** 15 sections / 122 items ; 57 VALIDÉ / 65 À DÉFINIR ; 14 validationRules (dont maintenance)
- **Suite :** après chaque MAJ de `designGate.js` → `node scripts/syncStandaloneFromJs.mjs`

### 2026-10-06 — DG-00.5-U — Périmètre simu : U1–U10 VALIDÉ

- **Intention :** figer le grain de simulation des unités (position, déplacement, états, coopération…).
- **Statut :** PARTIEL — `00.5.U1`…`U10` VALIDÉ ; parent `00.5` reste **À DÉFINIR**
- **Changements :** `designGate.js` ; miroir JSON (U1–U10) ; `ETAT_PROJET.md`
- **Suite :** questionnaire B1–B7 (sans inscription tant que non confirmé)

### 2026-10-06 — DG-00.5-R — Périmètre simu : R1–R6 VALIDÉ

- **Intention :** figer le grain et les règles de simulation des ressources / stocks / matière.
- **Statut :** PARTIEL — `00.5.R1`…`R6` VALIDÉ ; parent `00.5` reste **À DÉFINIR**
- **Changements :** `designGate.js` ; miroir JSON (R1–R6) ; `ETAT_PROJET.md`
- **Suite :** questionnaire U1–U10 (sans inscription tant que non confirmé)

### 2026-10-06 — DG-00.5-ST — Périmètre simu : S1–S6 + T1–T5 VALIDÉ

- **Intention :** figer échelle spatiale et temporelle du périmètre de simulation.
- **Statut :** PARTIEL — sous-items S/T VALIDÉ ; parent `00.5` reste **À DÉFINIR**
- **Avant → Après :** S/T absents → 11 items `00.5.S1`…`S6` + `00.5.T1`…`T5` VALIDÉ (formulations auteur).
- **Changements :** `designGate.js` ; miroir `designGate.data.json` (ces items) ; `ETAT_PROJET.md`
- **Suite :** questionnaire R1–R6 (sans inscription tant que non confirmé)

### 2026-10-06 — DG-00.4 — Vocabulaire officiel VALIDÉ

- **Intention :** verrouiller le lexique design/joueur avant les décisions de contenu.
- **Statut :** VALIDÉ (uniquement item `00.4` ; aucun autre statut DG modifié)
- **Avant → Après :** `00.4` À DÉFINIR → VALIDÉ avec définitions confirmées (bâtiment/construction/infrastructure, chantier/opération/tâche, recherche/technologie/schéma non linéaire, ressource/stock/matière, production vs transformation territoriale, termes interdits, Accès/Réseau/Déblocage/Implantation/Mise en service).
- **Changements :** `GardenFervor_DesignGate_React/src/data/designGate.js` ; miroir `designGate.data.json` (item 00.4)
- **Ouvert volontairement :** déblai/remblai (plus tard)
- **Suite :** `00.5` ou `00.6` (cadre DG-00)

### 2026-10-06 — DESIGN-GATE-MAINT — Maintenance permanente Design Gate React

- **Intention :** figer le cycle conception ↔ implémentation autour du Design Gate React vivant.
- **Statut :** VALIDÉ (règles de process ; aucun item gameplay passé à VALIDÉ)
- **Avant → Après :** Design Gate consultable mais sans obligation de maintenance agent → §7octies + validationRules + compte rendu obligatoire.
- **Changements :** `REGLES_PROJET.md` §7octies ; `designGate.js` validationRules ; README React ; `ETAT_PROJET.md`
- **Preuves :** règles écrites ; pas de changement gameplay Unreal
- **Suite :** toute décision utilisateur met à jour `designGate.js` immédiatement

### 2026-10-05 — ODC-F8 — Terraformer industriel (ops + données)

- **Intention :** RaiseGrade agent applique une vraie opération terrain mesurable (pas soft complete).
- **Statut :** VALIDÉ (gate packaged PASS=1) — validation humaine PIE demandée
- **Avant → Après :** RaiseGrade complétait sans brush → ApplyBrushAt store (+ LandscapeEdit PIE) ; deltaZ mesuré ; dirty spatial.
- **Changements :** `ApplyBrushAt` dual plane ; `UnitTaskAgent` Terraform pulses ; `TerraformOperationRuntimeGate` (`gf.Terraform.OperationGate`)
- **Preuves :** `Saved/ODC_F8_TerraformOperationGate.txt` ; log `F8_PackagedTerraformOpGate.log`
- **Limites :** packaged = preuve store ; visual Landscape = PIE session-only ; F1 redo pour shipping visual
- **Suite :** validation humaine PIE, puis F9

### 2026-10-05 — F7-HUMAN-OK — Validation humaine logistique

- **Intention :** clôturer F7 côté joueur (haul pit→pad observable).
- **Statut :** VALIDÉ
- **Constat humain :** OK (Start LevelPad / flux PitSpoil→PadSpoil→Fill→Completed).
- **Suite :** ODC-F8 Terraformer industriel.

### 2026-10-05 — ODC-F7 — Logistique (pit → haul → pad)

- **Intention :** le chantier dépend réellement du transport (pas de spoil magique sur le pad).
- **Statut :** VALIDÉ (gate packaged PASS=1) — validation humaine PIE demandée
- **Avant → Après :** un seul stock co-localisé → fosse + pad séparés + tâche HaulSpoil ; transform pad impossible tant que Spoil reste à la fosse.
- **Changements :** ExpandLevelPad (7 tâches), PhysicalEconomy Withdraw, UnitTaskAgent cargo haul, LogisticsRuntimeGate, smoke HUD Pit/Pad/Fill
- **Preuves :** `Saved/ODC_F7_LogisticsGate.txt` ; log `F7_PackagedLogisticsGate.log`
- **Limites assumées :** un flux LevelPad ; pas routes/accès bloqués ; pas brush map (F8)
- **Suite :** validation humaine, puis F8

### 2026-10-05 — ODC-F6 — Économie physique minimale

- **Intention :** chaîne matière réelle alimente un chantier (pas de FillDirt magique).
- **Statut :** VALIDÉ (gate packaged PASS=1) — validation humaine PIE demandée
- **Avant → Après :** pool stub seedé → stocks physiques Spoil→Fill→consume ; LevelPad 6 tâches ; Extract produit / Raise consomme (planner corrigé).
- **Changements :** `PhysicalEconomySubsystem`, `EconomyRuntimeGate`, Project ExpandLevelPad, TaskSubsystem réservations StockId, UnitTaskAgent effets matière, smoke UI
- **Preuves :** `Saved/ODC_F6_EconomyGate.txt` ; `EconomyRuntimeGate.txt` ; log `F6_PackagedEconomyGate2.log`
- **Profondeur assumée :** stocks co-localisés (pas F7 transport) ; pas de brush map (F8) ; AoE legacy gelé
- **Suite :** validation humaine Start LevelPad (Spoil/Fill), puis F7

### 2026-10-05 — F5-HUMAN-OK — Validation humaine + méthode AgentRules

- **Intention :** clôturer F5 côté humain et figer la collaboration (rapport 5 points après chaque modif).
- **Statut :** VALIDÉ
- **Constat humain :** unités se déplacent / se regroupent / projet Completed ; **pas** de changement Landscape visible (= attendu jusqu’à F8).
- **Méthode :** rapports post-modif = sections 1–5 AgentRules (modifié / apporte / avant-après / validation humaine / résultat attendu) ; M4 doc-first ; pas de jalon « compile = done ».
- **Suite :** ODC-F6.

### 2026-10-05 — F5-SMOKE-UI — Bouton / commande LevelPad provisoire

- **Intention :** permettre une validation humaine PIE sans attendre l’UX F14.
- **Statut :** VALIDÉ (compile Editor)
- **Avant → Après :** pas de moyen joueur de démarrer un LevelPad → bouton HUD **Start LevelPad** + `gf.Project.SmokeLevelPad` (create/activate + FillDirt + ensure W/T).
- **Changements :** `GardenFervorProjectSubsystem.*`, `GardenFervorRTSHUDWidget.*`
- **Suite :** validation humaine en PIE, puis ODC-F6.

### 2026-10-05 — ODC-F5 — Autonomie unité (TaskAgent)

- **Intention :** brancher unités sur le task graph ; plusieurs unités terminent un LevelPad sans micro-ordres.
- **Statut :** VALIDÉ
- **Avant → Après :** unités hors graph → `UnitTaskAgent` SEEK→…→VERIFY + claim API ; LevelPad Completed packaged PASS=1 (30 steps).
- **Changements :**
  - `GardenFervorUnitDefinition.h` (Capabilities)
  - `GardenFervorTaskTypes.h` (AssignedUnitInstanceId)
  - `GardenFervorTaskSubsystem.*` (Find/Claim/Release/Progress)
  - `GardenFervorUnitTaskAgent.*`, `GardenFervorAutonomyRuntimeGate.*`
  - `GardenFervorUnitBase.*` (composant agent)
  - `Content/Python/create_rts_sample_data.py` (capabilities DA)
- **Preuves :** `Saved/ODC_F5_AutonomyGate.txt` ; marker `AutonomyRuntimeGate.txt` ; log `F5_PackagedAutonomyGate.log`
- **Pièges :** preuves sur packaged ; instant mode gate seulement (travel teleport).
- **Dette :** DELIVER soft ; EXECUTE terraform soft (F8) ; pool stub (F6) ; DC preemption polish.
- **Suite :** ODC-F6 (F1 shipping parallèle).

### 2026-10-05 — AUDIT-PRE-F5 — Alignement ODC vs gameplay unités

- **Intention :** inventaire de ce qu’il faut geler / brancher avant F5, sans toucher map/T01.
- **Statut :** VALIDÉ (audit uniquement)
- **Verdict :** F2–F4 + move/sélection + TerraformTool + T01 = keep ; boucle AoE (Harvest/TC/FWSG/Ages/RMB) = legacy à isoler ; F5 = UnitTaskAgent → TaskSubsystem.
- **Preuves :** `Saved/ODC_AUDIT_PRE_F5.txt` ; canvas `odc-pre-f5-audit`
- **Contraintes :** pas de suppression T01 ; pas d’edit carte/M4/layers sans validation humaine.
- **Suite :** F5 autonomie.

### 2026-10-05 — T01-TERRAFORMER-MESH — Remplacement placeholder Terraformer

- **Intention :** remplacer le mesh placeholder (cylindre/cône) par `FieldUnits/Terraforming/T01/Terraforming_T01`.
- **Statut :** VALIDÉ
- **Avant → Après :** cone/cylindre teinté → StaticMesh T01 + `M_Terraforming_T01_Inst` ; `bUseAuthoredAppearance` (pas de MID BasicShape).
- **Changements :** `GardenFervorUnitDefinition.h`, `GardenFervorUnitBase.*`, `Content/Python/setup_terraformer_t01.py`, `DA_Unit_Terraformer`, import `Terraforming_T01.uasset`
- **Suite :** F5.

### 2026-10-05 — TERRAIN-SESSION-ONLY — Raise/paint Landscape non persistants

- **Intention :** les edits hauteur/peinture ne doivent pas rester sur la map (dev).
- **Statut :** VALIDÉ (compile)
- **Avant → Après :** LandscapeEdit écrivait les final maps (persistait) → snapshot plein Landscape au 1er brush ; **restore à Deinitialize/Stop Play** ; `SetShouldDirtyPackage(false)` ; `bSessionOnlyLandscapeEdits=True`.
- **Changements :** `LandscapeTerraformSubsystem.*`, `DeveloperSettings.h`, `DefaultGame.ini`, `ETAT_PROJET.md`, `REGLES_PROJET.md`
- **Note :** si la map était déjà dirty d’avant, recharger sans sauver ou `gf.Terraform.ResetToLandscape`.
- **Suite :** F5.

### 2026-10-05 — DOC-ETAT-SYNC — Alignement état réel post-reset terrain

- **Intention :** synchroniser ETAT / HISTORIQUE inventaire / REGLES / gate F1 avec le code réel ; supprimer les mentions trompeuses (F1 PASS, overlay actif, F5 bloqué).
- **Statut :** VALIDÉ
- **Avant → Après :** docs disaient encore F1 PASS + PMC actifs → F1 **À REFAIRE** ; inventaire LandscapeEdit ; F5 **Suivant** (non bloqué) ; `ODC_F1_*.txt` = INVALIDÉ.
- **Changements :** `ETAT_PROJET.md`, `HISTORIQUE_MODIFICATIONS.md` (§1–3, §5), `REGLES_PROJET.md` (§3–4, §7), `Saved/ODC_F1_RuntimeTerrainGate.txt`, `DefaultEngine.ini` (commentaire)
- **Suite :** ODC-F5.

### 2026-10-05 — RESET-TERRAIN-ODC — Suppression overlay PMC, retour Landscape+M4

- **Intention :** le terrain runtime PMC était inutilisable (damier/noir/outils morts). Revenir à l’architecture ODC : **M4/Landscape = monde visible** ; simu terrain à refaire proprement (F1).
- **Statut :** VALIDÉ (compile) ; validation humaine PIE requise
- **Avant → Après :** overlay PMC (visualizer/collision) + save/load → **overlay hard-OFF** ; brushes = LandscapeEdit ; store sans mesh pour Spatial ; `gf.Terraform.ResetToLandscape` (purge PMC + FillAuto) ; F1 marqué RESET.
- **Changements :** `LandscapeTerraformSubsystem.*`, `GroundUtils.cpp`, `DeveloperSettings.h`, `DefaultGame.ini`, `ETAT_PROJET.md`, `REGLES_PROJET.md`
- **Architecture ODC rappelée :** Terrain STATE → M4/Landscape (rendu). Pas de PMC comme surface joueur.
- **Pièges :** ne pas réactiver `bUseRuntimeTerraformOverlay` avant refonte F1 ; FillAuto pour rétablir couche Auto.
- **Suite :** ODC-F5 (F1 shipping en parallèle / après).

### 2026-10-05 — FIX-PAINT-NOSAVE — Peintures noires + save OFF en dev
- **Statut :** **SUPERSEDÉ** par RESET-TERRAIN-ODC

### 2026-10-05 — FIX-TERRAIN-LOCAL — Checkerboard + brush angulaire
- **Statut :** **SUPERSEDÉ** par RESET-TERRAIN-ODC

### 2026-10-05 — FIX-PIE-OVERLAY — Île noire + IntFitsIn PIE
- **Statut :** **SUPERSEDÉ** par RESET-TERRAIN-ODC

### 2026-10-05 — FIX-PIE-VSM — Crash PIE IntFitsIn / narrowing
- **Statut :** VALIDÉ (`r.Shadow.Virtual.Enable=0` conservé ; distinct de RVT)

### 2026-10-05 — ODC-F4 — Projet → tâche (Task graph)

- **Intention :** Project/Task graph, dépendances, réservations, causes de blocage ; projet simple → chaîne visible.
- **Statut :** VALIDÉ (PASS)
- **Avant → Après :** pas de Projects/Tasks → subsystems + planner LevelPad + gate packaged PASS=1.
- **Changements :**
  - `Source/GardenFervor/RTS/Projects/*` (types + ProjectSubsystem)
  - `Source/GardenFervor/RTS/Tasks/*` (types + TaskSubsystem + TaskRuntimeGate)
  - `GardenFervor.Build.cs` includes Projects/Tasks
  - Chaîne smoke : Analyze→Prepare→Extract→Raise→Verify
- **Preuves :** `Saved/ODC_F4_TaskGraphGate.txt` ; marker `TaskRuntimeGate.txt` ; log `F4_PackagedTaskGate2.log` ; Project Completed status=4.
- **Pièges :** ordre d’éval des args `Line(..., Printf(status))` ; pool FillDirt stub ; conflict task hors ProjectId.
- **Dette :** pas de binding unités (F5) ; économie réelle (F6) ; UI tâches (F14).
- **Suite ODC :** F5 Autonomie.

---

### 2026-10-05 — DOC-H1 — Création historique agent-complet

- **Intention :** document dédié mémoire longue + rétroaction de tout l’existant.
- **Statut :** VALIDÉ
- **Avant → Après :** pas d’historique central → `HISTORIQUE_MODIFICATIONS.md` + obligation d’update dans `REGLES_PROJET.md`.
- **Changements :** ce fichier ; §1bis REGLES (entrée historique obligatoire) ; référence dans `ETAT_PROJET.md`.
- **Preuves :** fichier présent à la racine.
- **Pièges / leçons :** `ETAT_PROJET` reste court ; le détail vit ici.
- **Dette :** aucune.
- **Suite ODC :** F4 (inchangé).

---

### 2026-10-05 — DOC-R1 — REGLES_PROJET + process delta + ETAT

- **Intention :** centraliser règles projet/interactions ; forcer état avant/après + delta humain.
- **Statut :** VALIDÉ
- **Avant → Après :** règles dispersées chat → `REGLES_PROJET.md` + `ETAT_PROJET.md` + §1bis.
- **Changements :** racine `REGLES_PROJET.md`, `ETAT_PROJET.md`.
- **Preuves :** documents ; process utilisé pour F3.
- **Pièges :** EnhancedInput doit vivre dans `DefaultInput.ini` (`config=Input`).
- **Dette :** —.
- **Suite :** F3 puis F4.

---

### 2026-10-05 — ODC-F3 — Spatial substrate

- **Intention :** cellules logiques, dirty régional, API queries ; gate « modif locale ≠ île entière ».
- **Statut :** VALIDÉ (PASS)
- **Avant → Après :** pas de Spatial → `UGardenFervorSpatialSubsystem` + gate packaged PASS=1.
- **Changements :**
  - `Source/GardenFervor/RTS/Spatial/*` (Types, Subsystem, RuntimeGate)
  - `GardenFervor.Build.cs` include `RTS/Spatial`
  - `PeekDirtyRect` sur store ; hook dans `ApplyBrushAt`
  - Fix ordre d’éval log World→Cell ; `SampleRuntimeWorldHeight` force `EnsureRuntimeInitialized`
- **Preuves :** `Saved/ODC_F3_SimulationSubstrateGate.txt` ; marker packaged `SpatialRuntimeGate.txt` ; log `F3_PackagedSpatialGate2.log` ; cells 253×253 ; dirty 1 puis 9 ; center (0,0) / second (11,11).
- **Pièges :** binaire projet + Zen store → utiliser packaged ; NullRHI OK pour ce gate.
- **Dette :** soil/water stubs ; collision full-island ; simu hydro/sol = F10/F11.
- **Suite ODC :** F4 Projet → tâche.

---

### 2026-10-05 — ODC-F2 — Visual terrain (M4 / RVT / UDS / UDW)

- **Intention :** prouver socle visuel runtime packaged sans casser M4.
- **Statut :** VALIDÉ (PASS)
- **Avant → Après :** F1 OK mais AutoSettings EnhancedInput en erreur + pas de gate visuelle → VisualGate PASS=1 + configs quiet.
- **Changements :**
  - `GardenFervorVisualRuntimeGate` + `gf.Visual.RuntimeGate`
  - `GameUserSettingsClassName` AutoSettings (Engine)
  - `UserSettingsClass` AutoSettings EnhancedInput dans **`DefaultInput.ini`**
  - CVar CommonUI viewport check désactivé temporairement
- **Preuves :** `Saved/ODC_F2_VisualTerrainGate.txt` ; MI `Island_UE5Preset5_Inst` ; 3 RVT ; UDS/UDW ; GPU windowed.
- **Pièges :** ne pas mettre EnhancedInput settings dans DefaultEngine ; VisualGate besoin GPU (pas NullRHI pour UDW).
- **Dette :** ShaderMap None noise ; warning CDO test AutoSettings.
- **Suite ODC :** F3.

---

### 2026-10-05 — ODC-F1 — Terrain runtime Cook/Package/Persist

- **Intention :** overlay Base+Delta shipping : raise/paint/save/load + persist relaunch.
- **Statut :** **INVALIDÉ** (2026-10-05 — RESET-TERRAIN-ODC ; preuve PMC non retenue)
- **Avant → Après :** preuve packaged smoke + persist → chemin retiré ; gate fichier marqué INVALIDÉ.
- **Preuves (historiques, non rejouables) :** ancienne archive packaged ; fichier gate réécrit.
- **Suite :** F1 redo propre (M4 = rendu).

---

### 2026-10-05 (et avant) — F0 / socle runtime terraform overlay

- **Intention :** remplacer LandscapeEdit editor-only par overlay runtime Base+Delta pour shipping.
- **Statut :** **INVALIDÉ** avec F1 (chemin PMC retiré)
- **Note :** fichiers store/base height conservés pour F1 redo ; visualizer/collision non utilisés.

---

## 5. Dette technique ouverte (agrégat)

| ID | Sujet | Gravité | Notes |
| --- | --- | --- | --- |
| F1R | F1 Base+Delta shipping à refaire | Élevé | LandscapeEdit interim ; M4 = rendu |
| SIM | Soil/Water spatial stubs | Attendu | F10/F11 |
| RES | Task resource pool stub | Attendu | F6 |
| AUT | Units ↔ task graph | Attendu | F5 |
| ZEN | Zen store vs Binaries projet | Moyen | Gates sur packaged |
| SHD | ShaderMap None packaged | Bas | F2 |
| AS | AutoSettings test CDO warning | Bas | Plugin |
| CUI | CommonGameViewport non adopté | Bas | CVar temporaire |
| VSM | VSM off en PIE | Moyen | `r.Shadow.Virtual.Enable=0` |

---

## 6. Checklist livraison agent (après modif validée)

- [ ] Entrée ajoutée en **§4** (format complet)
- [ ] `ETAT_PROJET.md` réécrit (phase, faits, risques, suite)
- [ ] Si nouvelle règle durable → `REGLES_PROJET.md`
- [ ] Si gate ODC → `Saved/ODC_F*_*.txt`
- [ ] Delta humain posté dans le chat (§1bis)
- [ ] §2 de ce fichier mis à jour si phase ODC a changé
- [ ] §3 / §5 mis à jour si inventaire ou dette a changé

---

*Ne pas tronquer l’historique : les entrées §4 sont append-only. Les corrections se font par une nouvelle entrée « amendement », pas en réécrire le passé.*
