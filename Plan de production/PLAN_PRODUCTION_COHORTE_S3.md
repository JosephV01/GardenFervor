# PLAN DE PRODUCTION — Cohorte forestière S3 (Cas A)

**Date :** 2026-10-06  
**Statut :** plan opérationnel — **implémentation non démarrée**  
**Contrôle final :** `PASS — PRÊT POUR IMPLÉMENTATION CONTRÔLÉE`  
(`Audit de readiness pré-implémentation/CONTROLE_FINAL_PRE_IMPLEMENTATION_COHORTE.md`)

**Sources (ne pas inventer de règles) :** Formalisation 01 · 02 · 03 · DG-14.3 / 14.4 · préparation contrats C7→C6

**Pilotage avancement :** `Plan de production/Roadmap/index.html`  
(source : `Roadmap/src/roadmap.data.js` — ce Plan = *comment* ; roadmap = *où*)

---

## A. Objet

Produire la **première preuve jouable minimale** de la boucle GardenFervor ancrée sur la petite exploitation forestière :

```
Intention → Project → Analyze → (Prepare si nécessaire)
  → U1 Extraction → Stock A → U2 Transport → Stock B
  → U3 Construction → En service → résultat observable
```

**Premier passage = Cas A** (terrain déjà prêt — pas de Terraform obligatoire).

Démontrer que les décisions formalisées sont **exécutables** en session PIE, de façon lisible et réversible, sans construire le jeu complet.

---

## B. Périmètre

| Inclus | Détail |
| --- | --- |
| Clé PE `Timber` | C7 |
| Extract/Haul paramétrés ResourceKey | C1 |
| Caps U1 / U2 / U3 | C2 |
| Stocks A ≠ B session | Stocks |
| Expand Project générique Cas A | C3 |
| Entrée Intention→Project dédiée | C4 |
| Achevé ≠ En service ; critère S3 | C5 |
| Smoke / observabilité PE | C6 |
| Unités / forestière placeholder | Contenu minimal preuve |
| Validation humaine PIE par tranche | §F |

---

## C. Hors périmètre

- Écologie complète · catalogue bâtiments/unités complet · routes · infrastructures complètes  
- Progression · Ages / recherche · UI finale DG-13 · sauvegarde monde · multijoueur  
- Optimisation avancée · **Terraform Case B** · intégrations environnementales non nécessaires  
- Autres ressources que Timber · autres unités hors U1/U2/U3 (+ Analyse cap si sur U1)  
- Systèmes anticipatoires · Owner stocks · prod continue · coûts inventés  
- EconomyComponent / Harvest / Wood AoE / TownCenter / House comme fondation  
- ExpandForest · Worker universel · BeginPlace/TrySpend comme entrée  
- LevelPad comme modèle forestier (LevelPad terrain peut rester parallèle)  
- F1 shipping Base+Delta  

---

## D. Chaîne de production

### Contrats

```
C7 → C1 → C2 → Stocks → C3 → C4 → C5 → C6
```

### Tranches d’implémentation (traduction)

| Tranche | Contrats | Titre |
| --- | --- | --- |
| **T0** | — | Garde-fous / branche de travail (doc seule si besoin) |
| **T1** | C7 | Clé `Timber` |
| **T2** | C1 | OperationalResourceKey Extract/Haul |
| **T3** | C2 | Caps + defs U1/U2/U3 |
| **T4** | Stocks | CreateStock A/B liés Project |
| **T5** | C3 | Expand générique Cas A |
| **T6** | C4 | Smoke Intention→Project |
| **T7** | C5 | Achevé / En service S3 |
| **T8** | C6 | Observabilité smoke/PE |
| **T9** | Intégration | Preuve bout-en-bout Cas A |

T0 est optionnel (pas de code obligatoire).  
**Ne pas fusionner T1–T9 en une seule tâche.**

---

## E. Tranches détaillées

### T1 — C7 Timber

| | |
| --- | --- |
| **Objectif** | Enregistrer la clé officielle `Timber` dans PE types |
| **Dépendances** | F03 C7 |
| **Modifier/créer** | `GardenFervorPhysicalResourceTypes.h` (enum + helper) |
| **Résultat** | `GardenFervorPhysicalResourceKey(Timber) == "Timber"` |
| **Validation humaine** | Compile ; helper retourne Timber ; Wood enum legacy intact |
| **Arrêt** | Si collision forcée avec Wood legacy |
| **Ne pas ajouter** | EconomyComponent Wood · DA AoE · masse/volume |

### T2 — C1 ResourceKey opérationnel

| | |
| --- | --- |
| **Objectif** | Extract/Haul génériques paramétrés (plus de Spoil implicite pour cohorte) |
| **Dépendances** | T1 |
| **Modifier/créer** | Champ tâche `OperationalResourceKey` ; `UnitTaskAgent` Deposit/Withdraw |
| **Résultat** | Même agent : Spoil (LevelPad) ou Timber selon tâche |
| **Validation** | Gate/smoke Spoil inchangé ou non régressé ; Deposit Timber possible en test minimal |
| **Arrêt** | Si branche `if Timber` spécialisée dans l’unité |
| **Ne pas ajouter** | ForestExtraction · second haul agent |

### T3 — C2 Roster U1/U2/U3

| | |
| --- | --- |
| **Objectif** | Trois rôles par caps données |
| **Dépendances** | T2 (utile) ; peut démarrer defs en parallèle de T2 si caps seules |
| **Modifier/créer** | UnitDefs (DA ou transient) Capabilities `Extraction` / `Transport` / `Construction` (+ `Analyse` sur U1 si retenu) |
| **Résultat** | Matching tâches sans Worker fourre-tout pour cohorte |
| **Validation** | Trois unités ; claims séparés |
| **Arrêt** | Si tout repasse par Worker |
| **Ne pas ajouter** | 3 classes C++ inutiles · Ages train cost obligatoire |

### T4 — Stocks A/B

| | |
| --- | --- |
| **Objectif** | Deux stocks distincts session pour Timber |
| **Dépendances** | T1 ; PE CreateStock existant |
| **Modifier/créer** | Création A/B à l’expand (ou helper Project) ; mapping LinkedPit≈A / LinkedStock≈B OK |
| **Résultat** | A≠B ; GetAvailable distincts |
| **Validation** | Ids différents ; Deposit A visible |
| **Arrêt** | Si un seul stock forcé |
| **Ne pas ajouter** | SaveGame · Owner · bâtiment dépôt |

### T5 — C3 Expand générique Cas A

| | |
| --- | --- |
| **Objectif** | Project → Analyze → Extract → Transport → Build → Verify (pas Prepare/Terraform) |
| **Dépendances** | T2 · T3 · T4 |
| **Modifier/créer** | Objective générique + expand paramétrique ; pose caps + OperationalResourceKey=Timber + Source/Dest |
| **Résultat** | Graphe prêt sans ExpandForest / sans LevelPad copié |
| **Validation** | Liste tâches + caps correctes ; site prêt (Cas A) |
| **Arrêt** | Si ExpandForest nommé ou Spoil sur chaîne forêt |
| **Ne pas ajouter** | Cas B Terraform · planner IA complet |

### T6 — C4 Intention → Project

| | |
| --- | --- |
| **Objectif** | Entrée dédiée minimale sans économie legacy |
| **Dépendances** | T5 |
| **Modifier/créer** | Smoke `Start Forest Cohort` (ou équivalent) Create→Expand→Activate ; spawn U1/U2/U3 |
| **Résultat** | Intention→Project sans TrySpend/BeginPlace/Ages |
| **Validation** | Action → Project Running ; HUD Wood FWSG inchangé |
| **Arrêt** | Si ConfirmPlace/TrySpend réutilisé |
| **Ne pas ajouter** | UI DG-13 · catalogue placement complet |

### T7 — C5 En service S3

| | |
| --- | --- |
| **Objectif** | Achevé ≠ En service ; critère cohorte |
| **Dépendances** | T5 (Build) · T4 (Stock B) · T6 (chaîne lancée) |
| **Modifier/créer** | État En service distinct ; transition Achevé ∧ GetAvailable(B,Timber)>0 |
| **Résultat** | Pas En service si B vide ; En service si B>0 après Achevé |
| **Validation** | Deux jalons visibles ; pas de coût inventé |
| **Arrêt** | Si complete == En service sans B |
| **Ne pas ajouter** | Prod continue · règle universelle tous bâtiments · réseaux |

### T8 — C6 Observabilité

| | |
| --- | --- |
| **Objectif** | Lisibilité preuve PE |
| **Dépendances** | T6–T7 (idéal) ; peut itérer dès T4 |
| **Modifier/créer** | Smoke line cohorte : Project, tâche, A/B Timber, Achevé/En service, BlockReason ; overlay optionnel |
| **Résultat** | Validation humaine sans debugger ni HUD FWSG |
| **Validation** | Checklist §G lisible en PIE |
| **Arrêt** | Si vérité = chips Wood HUD |
| **Ne pas ajouter** | UI complète · i18n polish |

### T9 — Preuve bout-en-bout Cas A

| | |
| --- | --- |
| **Objectif** | Chaîne S3 complète observable |
| **Dépendances** | T1–T8 |
| **Modifier/créer** | Ajustements d’intégration uniquement |
| **Résultat** | Intention→…→En service + Timber B>0 |
| **Validation** | Checklist §G complète (humain) |
| **Arrêt** | Voir §H |
| **Ne pas ajouter** | Case B · nouvelles features |

---

## F. Validation

| Moment | Type | Durée cible |
| --- | --- | --- |
| Après T1–T3 | Compile + check ciblé | Minutes |
| Après T4–T5 | PIE/smoke partiel si possible | Court |
| Après T6 | PIE Intention→Project | Quelques secondes d’observation |
| Après T7–T8 | PIE jalons + smoke PE | Court |
| Après T9 | PIE preuve S3 complète | Session courte |

Privilégier **validation humaine PIE/editor**.  
Éviter suites de tests automatisés longs sauf gates déjà existants (non régression Spoil LevelPad si touché).

---

## G. Point de preuve final

L’humain constate en PIE (Cas A) :

| # | Observation | Source de vérité |
| --- | --- | --- |
| 1 | Intention exprimée (smoke dédié) | Entrée C4 |
| 2 | Project existe / Running ou Completed | ProjectSubsystem |
| 3 | Analyze complétée | Task |
| 4 | U1 extrait | Agent + caps Extraction |
| 5 | Timber dans Stock A | PE GetAvailable |
| 6 | U2 transporte | Phase Haul |
| 7 | Timber dans Stock B | PE GetAvailable |
| 8 | U3 construit → **Achevé** | Building / Task |
| 9 | **En service** (Achevé ∧ B>0) | État service + PE |
| 10 | Résultat / blocage lisibles | Smoke C6 — **pas** HUD FWSG |

---

## H. Réversibilité — arrêt et réouverture

**Arrêter l’implémentation et rouvrir une décision** si :

- contradiction fondamentale avec F01/F02/F03 ou DG-14.3  
- source de vérité ambiguë (PE vs EconomyComponent)  
- dépendance legacy inattendue devenue nécessaire  
- comportement contraire au contrat (ex. En service sans Timber B)  
- impossibilité de démontrer clairement le résultat en PIE  

Alors : **pas de contournement** ; documenter ; arbitrage humain avant reprise.

---

## I. Ordre et discipline

1. Suivre T1→T9 (dépendances §E).  
2. Une tranche à la fois ; validation avant d’empiler.  
3. **Aucun code** tant que l’humain n’a pas ordonné le démarrage d’une tranche.  
4. Ce plan **applique** DG-14.1→14.4 ; il ne remplace aucun DG.  

---

## J. État actuel

| Élément | État |
| --- | --- |
| Plan | **Créé** (ce fichier) |
| Implémentation | **Non démarrée** |
| Prochaine action humaine | Ordonner T1 (ou contrôle/lecture du plan) |

---

*Fin.*
