# Fondation terrain — GardenFervor

| Champ | Valeur |
|---|---|
| Fichier | `TERRAIN_FOUNDATION.md` (racine GardenFervor) |
| Rôle | Point d’entrée **opérationnel** du chantier fondation terrain |
| Création | **2026-10-12** |
| Nature | Documentaire et préparatoire. **Pas** un Design Gate, **pas** un contrat, **pas** un registre d’audits, **pas** une autorisation d’implémentation. |

**Design Gate : aucun contrat ni statut modifié — création du référentiel central de la fondation terrain.**

Ce document **ne remplace pas** `REGLES_PROJET.md`, `ETAT_PROJET.md`, les contrats VALIDÉ, `designGate.js`, les rapports `ExternalTechnologyAudits/`, ni le code.

En cas de contradiction : **Design Gate React / contrats > preuves ODC (`Saved/ODC_F*_*.txt`) > rapports d’audit canoniques > `ETAT_PROJET.md` / `HISTORIQUE_MODIFICATIONS.md` > ce fichier.** Signaler, ne pas trancher silencieusement (`REGLES_PROJET.md` §0).

---

## A. Objectif et périmètre

GardenFervor est un RTS territorial. Le relief conditionne l’implantation, l’accès, les travaux et une partie des possibilités du territoire (DG-08.1 VALIDÉ). Le jeu vise un terrain **visuellement réaliste** (M4 / RVT, ODC-F2 PASS), **modifiable par les unités** (08.2, C-08, ODC-F8), et **compatible à long terme** avec des simulations de sol, d’eau et d’écosystèmes (DG-09, C-15 / C-16 / C-17 — conception, ≠ runtime).

Le terrain n’est **pas** seulement un maillage. Distinguer, sans figer l’architecture 08.7 :

| Couche | Question | Propriétaire contractuel (actuel) |
|---|---|---|
| Données autoritaires | Quelle hauteur le gameplay lit-il ? | C-01 : `RuntimeTerraformStore` (D1) |
| Représentation géométrique | Quel mesh / Landscape montre le relief modifié ? | **08.7 À DÉFINIR** (D3 n’impose aucune techno) |
| Rendu et matériaux | M4, RVT, instances | Présentation (00.6.A2) ; F2 PASS = île visuelle packaged, pas F1 |
| Couches et peintures | Poids techniques vs sol / biome | C-01 D14 (technique) ; sémantique hors C-01 (C-16, etc.) |
| Collision / navigation | Suivent-elles le relief **réellement** modifié ? | 00.5.G5 VALIDÉ comme exigence ; **non démontré** shipping |
| Outils de modification | Qui écrit, avec quelle API, quel métier | C-01 (Store) ; C-08 (opération Terraformer) ; 08.2 Raise/Lower/Paint |
| Persistance | Le relief survit-il à une relance ? | C-01 D12 capacité ; **C-19** politique ; runtime **OFF** |
| Consommateurs futurs | Sol, eau, écosystèmes, accès | C-16 / C-15 / C-17 / C-02 — lisent C-01, ne possèdent pas la hauteur |

**Ce document ne choisit pas** l’architecture finale de ces couches. 08.7 reste ouvert.

**Hors périmètre immédiat :** intégration TerraDyne, amendement de contrats, activation persist, implémentation écologique, Case B.

---

## B. État de référence de GardenFervor

Code **présent** ≠ système **validé**. Statuts ci-dessous : implémenté (code) / preuve identifiée / partiellement validé / non validé / inconnu.

### B.1 Données autoritaires — `RuntimeTerraformStore`

| Point | Constat | État | Source |
|---|---|---|---|
| Classe | `UGardenFervorRuntimeTerraformStore` : base + delta CPU, `SampleWorldHeight` = base + delta, brushes hauteur et paint | Implémenté | `Source/GardenFervor/RTS/Terraform/GardenFervorRuntimeTerraformStore.h` |
| Rôle contractuel | Autorité unique de la hauteur après terraform ; Landscape / affichage ≠ seconde vérité | Décision VALIDÉ | C-01 D1 ; 08.6 ; 00.5.S4 ; 00.6.A2 |
| Grille île | Landscape documenté **4033×4033**, cellules spatiales 253×253, `cellQuads=16` | Documenté (historique) | `HISTORIQUE_MODIFICATIONS.md` (paramètres prouvés) |
| QuadSize | Défaut code **100** UU ; valeur cooked exacte du DataAsset île : **non rouverte** ici | Partiel / inconnu cooked | AUDIT-02 TF-11 |
| Conformité D2 | Dette E1 : `ApplyBrushAt` peut retourner `bStoreOk \|\| bLandscapeOk` | Implémenté **non conforme** D2 | C-01 E1 · `GardenFervorLandscapeTerraformSubsystem.cpp` |
| Lecteurs | Spatial `QueryTerrain` lit le Store ; `GroundUtils` seulement si overlay runtime | Partiel (E2, E3) | C-01 E2–E3 |

### B.2 Terraformation runtime existante

| Point | Constat | État | Source |
|---|---|---|---|
| Façade | `UGardenFervorLandscapeTerraformSubsystem::ApplyBrushAt` | Implémenté | `GardenFervorLandscapeTerraformSubsystem.h/.cpp` |
| Chemin visuel actuel | Commentaire d’en-tête (2026-10-05) : overlay PMC retiré ; monde visible = **Landscape + M4** ; PIE/éditeur = **LandscapeEdit** ; Store sans mesh pour extents Spatial / redo F1 | Documenté dans le code | Même header |
| Flags | `bUseRuntimeTerraformOverlay = false` ; `bEnableRuntimeTerraformPersistence = false` | Config / défauts code | `GardenFervorDeveloperSettings.h` ; F1 gate |
| Agents | Brushes branchés agents → Store + LandscapeEdit **session-only** PIE | Partiellement validé (F8 données ; visuel PIE) | `ETAT_PROJET.md` ; ODC-F8 ; C-01 E5 |
| ODC-F8 | Terraformer industriel **PASS** | Preuve gate | `Saved/ODC_F8_TerraformOperationGate.txt` |
| ODC-F1 | Terrain runtime Base+Delta shipping **INVALIDÉ / À REFAIRE** | Preuve gate | `Saved/ODC_F1_RuntimeTerrainGate.txt` (2026-10-05) |
| Métier | Raise / Lower / Paint techniques ; Compact = alias Lower côté agent | Implémenté ; écart lexique D13 | C-01 E7–E8 ; C-08 VALIDÉ, Case B **suspendu** |

F8 **PASS** ne clôt pas F1. 08.6 : visibilité, physique (G5) et persistance se vérifient **séparément**.

### B.3 Représentation, collision, peinture

| Composant | Rôle déclaré dans le code | État vis-à-vis des preuves |
|---|---|---|
| Landscape + MIC `Island_UE5Preset5_Inst` | Référence visuelle actuelle (08.6 / 08.7, sans garantie d’être finale) | F2 PASS packaged (MI, RVT, UDS, UDW) — `Saved/ODC_F2_VisualTerrainGate.txt` |
| `AGardenFervorRuntimeTerraformVisualizer` | Overlay local brush ; « Landscape M4 stays the visual base » | Code présent ; overlay **désactivé** (`bUseRuntimeTerraformOverlay=false`) |
| `AGardenFervorRuntimeTerraformCollision` | PMC collision coarse, stride 16, cooldown 0,35 s, cap 257 | Code présent ; G5 shipping **NON VALIDÉ** (08.6, F1) |
| Paint Store | Poids techniques (D14) | Code ; sémantique sol **hors** C-01 |

### B.4 Persistance

| Point | Constat | État | Source |
|---|---|---|---|
| API | `SaveRuntimeTerraform` / `LoadRuntimeTerraform` existent ; skip si persist OFF | Implémenté, **inactif** | Subsystem ; C-01 E6 |
| Politique | Session-only **aujourd’hui** ; durable = cible conception shipping, **sans** activation technique | C-19 VALIDÉ conception ≠ runtime | C-19 S7 ; `bEnableRuntimeTerraformPersistence` false |
| Classes SaveGame | `GardenFervorTerraformSaveGame.h/.cpp` | Présentes ; **pas** une sauvegarde monde opérationnelle | C-19 : ne pas présenter le chemin C++ comme save opérationnelle |

### B.5 M4, RVT, UDS, UDW

| Point | Constat | État | Source |
|---|---|---|---|
| ODC-F2 | Packaged : MIC île, 3 volumes RVT, UDS=1, UDW=1, `r.VirtualTextures=1` | **PASS** (2026-10-05) | `Saved/ODC_F2_VisualTerrainGate.txt` |
| Assets GF | Masters sous `Content/GardenFervor/Environment/Materials/MasterMaterials/` (`M4UE5MasterMat`, etc.) | Présents | AUDIT-03 §7.2 |
| Doc M4 | Peinture = Landscape Paint Layers ; pas de chemin TerraDyne officiel | Officiel | https://aaronneal.online/docs/m4/ |
| Graphes exacts | Listing éditeur des nœuds Landscape de `M4UE5MasterMat` | **Non fait** (A03-V1) | AUDIT-03 |

F2 prouve un **rendu d’île packaged**, pas un relief terraformé shipping (F1 INVALIDÉ).

---

## C. Contrats et contraintes de conception

**Aucun statut n’est modifié ici.** Formulations reprises, non réinterprétées.

| Réf. | Exigence (extrait) | Statut | Conséquence chantier | Source |
|---|---|---|---|---|
| **C-01 D1** | `RuntimeTerraformStore` = autorité de la hauteur. Landscape / affichage ≠ seconde vérité. | VALIDÉ (contrat documentaire, 2026-10-11) ≠ conformité runtime | Toute techno d’affichage doit **suivre** le Store, pas le remplacer | `CONTRATS/C-01_TERRAIN_RUNTIME.md` |
| **C-01 D2–D3, D6, D10** | Succès = Store modifié ; shipping = fiable **et** visible **sans** imposer une techno ; affichage peut suivre après | VALIDÉ ; dettes E1, E5 ouvertes | E5 (présentation) et succès Store sont séparés | C-01 |
| **C-01 D4, D5, D14** | Relief seulement ; dirty vers les autres systèmes ; paint technique sans sémantique sol | VALIDÉ | Sol / eau / éco ne s’accrochent pas aux poids comme vérité | C-01 ; C-16 |
| **C-01 D12** | Relief persistable ; save/load = **C-19** | VALIDÉ ; E6 ouverte | Ne pas activer persist sans ordre C-19 | C-01 ; C-19 |
| **C-01 D13** | Métier : Creuser / Remblayer / Aplanir (détail = C-08) | VALIDÉ ; E7–E8 lexique | Raise/Lower/Paint = technique | C-01 ; C-08 |
| **C-02 F1** | C-02 **ne possède jamais** la hauteur. C-01 reste l’autorité. | VALIDÉ | Spatial lit, n’écrit pas le relief | `CONTRATS/C-02_SUBSTRAT_SPATIAL.md` |
| **08.6** | Après terraform, Store Base+Delta = vérité hauteur. Critères **séparés** : données / visibilité / G5 / persist. Aucune architecture présélectionnée. E5/E6 non autorisés par 08.6. F1 PASS seulement si shipping durable **complet**. | **VALIDÉ** (principes, 2026-10-11) | Autorise l’étude 08.7, **pas** l’implémentation E5/E6 | `designGate.js` `dg08-06` |
| **00.5.S4** | Landscape = base initiale tant qu’aucune modif. Après terraform, Store = vérité. Landscape/M4 ≠ seconde vérité hauteur. G5 non prouvé par la seule visibilité. | VALIDÉ (amendé avec 08.6) | Réconcilié avec D1 | `designGate.js` `dg00-05-s4` |
| **00.6.A2** | Données GF = vérité ; M4/UDS/UDW = représentation. Aucune règle gameplay ne lit l’apparence. | VALIDÉ | M4 n’est pas l’autorité | `designGate.js` `dg00-06-a2` |
| **00.5.G5** | Collision et navigation suivent le relief réellement modifié. Proxies ≠ vérité physique finale. | VALIDÉ (exigence) | Preuve G5 **manquante** shipping | `designGate.js` `dg00-05-g5` |
| **08.7** | **Aucune** architecture technique retenue. Candidates (WPO Landscape M4, géométrie tuilée, Landscape runtime) à comparer sur preuves. Landscape+M4 = référence visuelle **d’étude**, sans garantie. WPO / Landscape runtime / géométrie tuilée **non choisis**. E5/E6 non autorisés par 08.6. | **`À DÉFINIR`** | Chantier ouvert ; **ne pas** le clôturer par un audit | `designGate.js` `dg08-07` |
| **08.1–08.5** | Relief conditionnant ; Raise/Lower/Paint ; travaux ; accès ; dirty écologique sans peindre l’éco | VALIDÉ | Cadre métier, pas le chemin mesh | `designGate.js` |
| **C-08** | Opération Terraformer ; 58 décisions | VALIDÉ ; Case B **suspendu** | Pas de Case B automatique | `CONTRATS/C-08_TERRAFORMER_OPERATIONNEL.md` |
| **C-15 / C-16 / C-17** | Eau / sol / végétation | VALIDÉ **conception** ≠ runtime | Consommateurs futurs de C-01 | Contrats dédiés |
| **C-19** | Politique persist ; S7 hybride session-only aujourd’hui | VALIDÉ conception ≠ runtime | Interdit d’activer persist sans ordre | `CONTRATS/C-19_PERSISTANCE_SAUVEGARDE.md` |
| **ODC-F1 / F2** | F1 INVALIDÉ ; F2 PASS | Preuves techniques | F2 ≠ F1 | `Saved/ODC_F1_*.txt`, `ODC_F2_*.txt` |

C-01 VALIDÉ = clôture **documentaire** (dettes E1–E7 ouvertes). Ce n’est **pas** un PASS F1.

---

## D. Évaluation TerraDyne

Détail : rapports canoniques, pas ce fichier.

Référentiel : `ExternalTechnologyAudits/01_TerraDyne/`.  
Prototype (hors dépôt GF) : `C:\Users\sahel\Documents\Unreal Projects\TerraDyneOSS_Proto_270c311`.

| Audit | Conclusion utile | Ce que ce n’est pas |
|---|---|---|
| **AUDIT-01** | **Favorable sous réserves** sur proto isolé HoleFix : Raise/Lower visuels, peintures overlay, collision **après** délai. Persist host non câblée ; perf RTS / 25 cm / éco **NON VALIDÉ**. | Pas un PASS F1. Pas GardenFervor. Validations **utilisateur**, pas Cursor. |
| **AUDIT-02** | **Option B recommandée** : GF conserve l’autorité (`RuntimeTerraformStore`). Option A = **incompatibilité contractuelle** (D1, 08.6, S4, A2, C-02 F1), pas une preuve que le plugin « ne marche pas ». Adaptateur Store → `FTerraDyneChunkData` **absent**. | **Pas** une décision 08.7. **Pas** une autorisation d’intégration. |
| **AUDIT-03** | OSS **0.4** commit `270c31117e20e491ef5333dd7e2f9dc133fcdc38`. Conversion Landscape **éditeur**, 4 couches, ≠ Store. 0.7 (8 couches + binding) **annoncé**, hors proto. M4 campagne **D** (MIC incomplet). Refus d’adoption = **mécanisme générique** (7 expressions, option défaut off). Appartenance du graphe `M4UE5MasterMat` à ce refus = **non établie**. | Pas une incompatibilité universelle de M4. Pas une compatibilité positive. Pas 0.7. |
| **Synthèse** | `06_Final_Synthesis/FINAL_SYNTHESIS.md` — consolide B + D restreint ; `Content/M4` proto **inventorié**, non testé. | Pas un 4ᵉ audit. Pas une décision. |

Distinctions à **conserver** :

1. TerraDyne **OSS 0.4** dans le proto ≠ manuel 0.4.1 ≠ forum 0.7.0.
2. HoleFix : validations **manuelles de l’utilisateur** (`Packaged/Win64ShippingHoleFix/TerraDyneOSS_Proto.exe`). Collision **pendant** le debounce = FUT-05 **non exécuté**.
3. Compatibilité M4 / DynamicMesh : **non démontrée** ; D conservé avec **portée restreinte**.
4. `Content/M4` désormais dans le proto (inventaire 2026-10-12, synthèse) : **présence ≠ fonctionnement**. Tests réels **non réalisés**. N’invalide pas rétroactivement AUDIT-03 (`M4_Eval` incomplet).
5. Adaptateur autorité GF → `FTerraDyneChunkData` : **non démontré**.
6. Persist complète et perf RTS TerraDyne : **non validées**.

Les limites de TerraDyne **ne prouvent pas** qu’une autre candidate 08.7 (WPO, Landscape runtime, autre géométrie) est viable. 08.7 exige des **preuves comparées**.

`04_Decision_Records/` : **aucune** décision d’architecture enregistrée.

---

## E. Problèmes à résoudre pour une fondation définitive

Sans implémentation. Sans seuils chiffrés inventés.

### E.1 Autorité et cohérence des données

| | |
|---|---|
| **État** | Contrats : Store = autorité. Code : Store existe ; E1–E3 lecteurs / retour `ApplyBrushAt` non uniformes. |
| **Preuve** | C-01 ; 08.6 ; code Store + dettes E1–E3. |
| **Inconnu** | Tous les lecteurs gameplay lisent-ils le Store **aujourd’hui** (E2) ? |
| **Amont** | Aucune techno d’affichage ne doit précéder D1. |
| **Si ouvert** | Double vérité ; F1 et G5 illisibles. |
| **Résolu quand** | D1/D2 tenus dans le code **et** documentés ; pas seulement un contrat VALIDÉ. |

### E.2 Représentation géométrique et mise à jour des hauteurs

| | |
|---|---|
| **État** | PIE : LandscapeEdit session-only. Shipping visuel terraform : F1 INVALIDÉ. 08.7 ouvert. Overlay PMC code présent, flag off. |
| **Preuve** | F1 ; header Subsystem ; 08.7. |
| **Inconnu** | Quelle candidate 08.7 satisfait D3 + G5 + M4 sans seconde autorité. |
| **Amont** | E.1 ; 08.6 critères séparés. |
| **Si ouvert** | F1 reste À REFAIRE ; unités voient un Landscape non modifié en packaged. |
| **Résolu quand** | Décision **humaine** 08.7 + preuve de visibilité shipping du relief Store (E5), **sans** changer D1. |

### E.3 Matériaux, M4, couches peintes

| | |
|---|---|
| **État** | F2 PASS (île M4 packaged). Terraform visible ≠ F2. M4 sur TerraDyne : D campagne ; graphe master non listé ; `Content/M4` proto non testé. |
| **Preuve** | F2 ; AUDIT-03 (portée restreinte) ; synthèse §D. |
| **Inconnu** | Nœuds Landscape vivants de `M4UE5MasterMat` ; comportement du MIC **complet** sur DynamicMesh ; RVT hors binding 0.7 annoncé. |
| **Amont** | Peut s’étudier **sans** trancher 08.7, dans le proto isolé, **sans** intégrer. |
| **Si ouvert** | Risque de choisir une géométrie 08.7 incompatible avec le rendu cible. |
| **Résolu quand** | Cause réelle observée (assets + code), documentée ; pas un présupposé de correctif. |

### E.4 Synchronisation données / rendu / collision

| | |
|---|---|
| **État** | Exigence G5 VALIDÉ. Collision Store (PMC) code présent, non prouvée shipping. LandscapeEdit PIE ≠ collision packaged. |
| **Preuve** | 00.5.G5 ; C-01 E5 ; collision header. |
| **Inconnu** | Navmesh ; traces ; délai de rebuild 0,35 s vs gameplay. |
| **Amont** | E.1 (quoi synchroniser) ; E.2 (sur quoi). |
| **Si ouvert** | Unités marchent sur un relief faux (anti-08.1 / G5). |
| **Résolu quand** | Preuve G5 **distincte** de la visibilité (08.6 critère 4). |

### E.5 Modifications successives ou concurrentes

| | |
|---|---|
| **État** | Store additif game-thread (inspection A02). C-04 / C-11 hors vertex. Multi-unités RTS sur le même relief : **non exercé** comme preuve fondation. |
| **Preuve** | AUDIT-02 §7 ; C-08. |
| **Inconnu** | Deux Terraformers, overlapping brushes, streaming. |
| **Amont** | E.1 ; métier C-08. |
| **Si ouvert** | Travaux autonomes incohérents (DG-04 / C-08). |
| **Résolu quand** | Comportement défini **et** observé ; pas une démo un joueur un brush. |

### E.6 Sauvegarde, chargement, reconstruction déterministe

| | |
|---|---|
| **État** | Persist OFF. C-19 conception VALIDÉ. D12 exige la **capacité**. |
| **Preuve** | C-19 ; C-01 E6 ; F1 (persist annulée). |
| **Inconnu** | Format, migration, round-trip Store. |
| **Amont** | Politique C-19 ; **ordre explicite** avant activation code. |
| **Si ouvert** | Shipping durable impossible (08.6 : F1 PASS seulement si critères complets dont persist). |
| **Résolu quand** | Round-trip validé **sous** politique C-19, pas un SaveGame proto TerraDyne. |

### E.7 Résolution, mémoire, performances, grande taille

| | |
|---|---|
| **État** | Grille 4033² documentée. Pas 25 cm île **non démontré**. TerraDyne clamp 32–256 / pas démo 107,5 UU ≠ île GF (TF-11). GPU TD stub. |
| **Preuve** | HISTORIQUE ; A01 TF-05 ; A02 TF-11. |
| **Inconnu** | Budget frame île ; coût d’une géométrie tuilée vs Landscape. |
| **Amont** | 08.7 compare sur preuves ; **pas** de seuil inventé ici. |
| **Si ouvert** | Choix 08.7 à l’aveugle. |
| **Résolu quand** | Mesures **nommées** sur la config cible, après décision de mesurer. |

### E.8 Sol, eau, écosystèmes

| | |
|---|---|
| **État** | Contrats conception VALIDÉ ; stubs spatiaux ; pas de simu runtime. Dirty 08.5 prévu. |
| **Preuve** | C-15/16/17 ; ETAT ; 08.5 ; 09.1. |
| **Inconnu** | Fréquences, grilles, ce que chaque couche lit du Store. |
| **Amont** | E.1 (une hauteur) ; D4 (frontières). |
| **Si ouvert** | Accrocher l’éco à M4 ou aux 4 poids TD = confusion démontrable (A02). |
| **Résolu quand** | Pas requis pour **démarrer** E.3 proto ; requis avant de déclarer la fondation **définitive**. |

### E.9 Dépendances techniques et maintenance

| | |
|---|---|
| **État** | M4 (Aaron Neal) ; UDS/UDW ; RVT ; Landscape UE 5.8 ; TerraDyne évalué hors intégration (OSS 0.4, fork local EngineVersion 5.8.0). |
| **Preuve** | F2 ; A03 TF-12. |
| **Inconnu** | Coût de fork M4 ; portage 0.7 (achat, RVT not bound). |
| **Amont** | Ne pas acheter / porter sans décision humaine. |
| **Si ouvert** | Lock-in ou dette de materials. |
| **Résolu quand** | Risques de maintenance **explicités** dans le dossier 08.7, pas avant. |

---

## F. Matrice des blocages et dépendances

| ID | Question | Dépendances | État de preuve | Bloque quoi ? | Prochaine action autorisée |
|---|---|---|---|---|---|
| TF-Q1 | Tenue runtime de D1/D2 (lecteurs, `ApplyBrushAt`) | Contrats déjà VALIDÉ | Dettes E1–E3 **documentées**, non refermées | Toute présentation qui lirait le Landscape comme vérité | Audit code ciblé **sur ordre** ; pas d’intégration |
| TF-Q2 | Architecture 08.7 (présentation) | TF-Q1 (autorité) ; preuves G5, M4, perf | **À DÉFINIR** | E5, F1 shipping visuel | Comparaison documentée ; **pas** d’implémentation E5 |
| TF-Q3 | M4 sur candidat mesh / proto TD | Peut avancer **sans** 08.7 tranché | D campagne ; graphe non listé ; `Content/M4` non testé | Un choix 08.7 « TerraDyne mesh + M4 » | Investigation proto **si l’humain l’autorise** (§H) |
| TF-Q4 | Collision / nav G5 | TF-Q2 (sur quelle géométrie) ; 08.6 critères séparés | Exigence VALIDÉ ; shipping **NON VALIDÉ** | F1 complet ; unités | Tests **après** candidat 08.7, ou diagnostic PIE distinct |
| TF-Q5 | Persist relief | C-19 ; TF-Q1 | Conception VALIDÉ ; code OFF | F1 shipping durable (08.6) | **Interdit** d’activer sans ordre C-19 |
| TF-Q6 | Concurrent / multi-unités | C-08 ; TF-Q1 | `INCONNU` runtime fondation | Case B (déjà suspendu) | Pas Case B automatique |
| TF-Q7 | Échelle / perf | TF-Q2 | NON VALIDÉ | Solidité d’un choix 08.7 | Mesures **si** demandées ; pas de seuils ici |
| TF-Q8 | Sol / eau / éco | TF-Q1 ; D4 | Conception seulement | Fondation « définitive », pas le diagnostic M4 proto | Pas d’implémentation éco |
| TF-Q9 | Intégration TerraDyne | Décision 08.7 ; adaptateur ; M4 ; G5 ; C-19 | Audits : **non autorisée** | — | **Interdite** par les audits et par 08.7 ouvert |

TF-Q3 **n’est pas** bloqué par TF-Q5 ni TF-Q8. TF-Q2 **est** bloqué par l’absence de décision humaine 08.7, pas par l’absence d’un test M4 proto — mais un test M4 **informe** TF-Q2.

---

## G. Décisions et recommandations : séparation stricte

### G.1 Décisions déjà validées (sources canoniques)

- 08.1–08.6 VALIDÉ (principes Base+Delta, Store autorité après terraform, critères séparés).
- 00.5.S4, 00.5.G5, 00.6.A2 VALIDÉ.
- C-01 D1–D14 VALIDÉ **documentaire** (dettes E1–E7 ouvertes).
- C-02 F1, C-08, C-15/16/17 conception, C-19 conception : VALIDÉ selon leurs documents.
- ODC-F2 PASS ; ODC-F8 PASS ; ODC-F1 **INVALIDÉ**.
- Case B **suspendu**.
- Landscape + M4 = **référence visuelle d’étude**, explicitement **sans** être l’architecture finale (08.6, 08.7).

### G.2 Recommandations issues des audits (non adoptées)

- **Option B** (AUDIT-02 / synthèse) : GardenFervor conserve l’autorité ; ne pas faire de TerraDyne la vérité hauteur.
- Ne pas fonder M4+TerraDyne sur l’OSS 0.4 du proto (AUDIT-03) ; 0.7 non transférable par rustine ; RVT annoncé non bound.
- Ne pas traiter PHASE3A proto comme canonique (AUDIT-02).
- Hybride Store → `LoadFromData` : **possible sous conditions**, **non démontré**, **non recommandé** comme issue principale tant que l’adaptateur manque.

Ces points restent dans **G.2** jusqu’à une décision humaine distincte (08.7 ou enregistrement dans `04_Decision_Records/`).

### G.3 Décisions encore nécessaires

- **08.7** : quelle architecture technique satisfait 08.6 (autorité Store, critères indépendants, G5) — **`À DÉFINIR`**.
- Autoriser ou non E5 (présentation shipping) et E6 (persist C-19) — **non autorisés** par 08.6.
- Réouvrir Case B — **non**.
- Intégrer TerraDyne — **non**.
- Activer overlay PMC / persist flags — **non** sans ordre.
- Trancher le graphe M4 / voie matériaux — investigation **future**, pas une décision actuelle.

---

## H. Prochaine étape

**Autorisée uniquement par ordre explicite de l’utilisateur.** Ce fichier ne la lance pas.

**Recommandation :** mission délimitée de **clarification et reproduction du problème matériaux M4** dans le prototype TerraDyne isolé, parce que `Content/M4` y est désormais présent (synthèse 2026-10-12), alors qu’AUDIT-03 n’avait qu’un `M4_Eval` incomplet.

Périmètre suggéré (à confirmer, pas à exécuter) :

- lecture seule puis, **si autorisé**, observation dans le proto **sans** modifier GardenFervor ;
- lister le graphe de `M4UE5MasterMat` (A03-V1) ;
- constater ce qui compile, s’affiche, ou échoue sur le DynamicMesh — **sans** présumer du correctif ;
- **ne pas** intégrer, **ne pas** changer D1, **ne pas** toucher 08.7.

**Interdit tant qu’un ordre distinct ne le dit pas :** intégration TerraDyne, transfert d’autorité, modification de contrat / `designGate.js`, activation persist, E5/E6, Case B, compilation/packaging GF « pour voir ».

---

## I. Journal de maintenance

| | |
|---|---|
| **Création** | 2026-10-12 |
| **Sources examinées** | `REGLES_PROJET.md` ; `ETAT_PROJET.md` ; `HISTORIQUE_MODIFICATIONS.md` ; `REGISTRE_MAINTENANCE_DOCUMENTAIRE.md` (existence) ; `designGate.js` (08.6, 08.7, 00.5.S4, 00.6.A2, 00.5.G5) ; C-01, C-02, C-08, C-15 mention, C-16 mention, C-19 ; AUDIT-01/02/03 ; `FINAL_SYNTHESIS.md` ; headers Store / Visualizer / Collision / LandscapeTerraformSubsystem / DeveloperSettings ; `Saved/ODC_F1_*.txt`, `ODC_F2_*.txt` |
| **Limites** | Pas de nouvelle inspection runtime ; pas d’ouverture éditeur ; QuadSize cooked non relu ; `designGate.js` a des modifications Git **préexistantes** non analysées ici ; pas d’inventaire exhaustif de tous les lecteurs de hauteur |
| **Mise à jour** | Après décision 08.7, clôture de dette C-01 E*, preuve F1/G5/persist, audit techno, ou mission M4 proto. Éditer ce fichier ; **ne pas** y copier les rapports d’audit. Pointer vers eux. |
| **Événements** | Changement D1/08.6/08.7 ; PASS/FAIL F1 ; activation persist ; intégration (si un jour autorisée) ; nouveau verdict M4 **prouvé** |

`REGLES_PROJET.md` §1bis et `REGISTRE_MAINTENANCE_DOCUMENTAIRE.md` exigeraient en principe d’enregistrer ce fichier dans ETAT / HISTORIQUE / registre. **Non fait dans cette mission** (périmètre : ce seul fichier). À rattraper sur ordre.

---

## J. Rappels de lecture

- Fonctionnement **HoleFix proto** ≠ validation **GardenFervor**.
- Code présent ≠ VALIDÉ.
- Recommandation d’audit ≠ décision 08.7.
- Le terrain n’est **pas** définitif tant que 08.7, F1, G5 et la politique persist applicable n’ont pas les preuves et décisions requises.

`Design Gate : aucun contrat ni statut modifié — création du référentiel central de la fondation terrain.`
