# GardenFervor — Registre des contrats comportementaux

**Fichier :** `CONTRATS/00_REGISTRE_CONTRATS.md`  
**Statut :** **AUDIT REGISTRE — VALIDÉ** (ce document uniquement)  
**Date d’audit :** 2026-10-08  
**Portée :** inventaire et priorisation — **aucun contrat individuel rédigé ici**

---

## 1. Pourquoi ce registre existe

Le Design Gate (DG-00 → DG-14) et l’ODC définissent **ce que le jeu doit être**.  
Les preuves T1→T9 / ODC-F* prouvent **ce qui existe déjà** pour un périmètre contrôlé.

Entre les deux, l’implémentation structurelle nécessite des **contrats opérationnels** : règles d’entrée/sortie, états, fin, échec, invalidation, observabilité — assez précises pour qu’un agent ou un humain n’ait **pas à inventer** de règles fondamentales en cours de code.

Le signal déclencheur de cet audit est **Case B / Terraformer** : le concept « unité autonome de terraformation » existe (DG-08, ODC-F8, code agent), mais le **contrat opérationnel** (décomposition spatiale du travail, relation tâche ↔ brush réel, progression observable) était insuffisant — d’où un Raise en burst immédiat sous InstantMode, compatible logiquement avec une tâche Complétée mais incompatible avec la perception d’une préparation progressive.

Ce registre :

1. inventorie les systèmes / sous-systèmes comportementaux du projet **réel** ;
2. juge si un **contrat autonome** est requis, partiel, suffisant ailleurs, ou non nécessaire ;
3. fixe l’**ordre logique de rédaction** par dépendances ;
4. marque les contrats **bloquants** pour toute implémentation structurelle future.

Les contrats individuels (`01_…`, `02_…`, etc.) seront rédigés **ultérieurement**, uniquement dans l’ordre défini ici, et uniquement sur ordre explicite.

---

## 2. Périmètre et méthode

### Périmètre

- Systèmes **comportementaux** (pas chaque classe C++).
- Croisement : Design Gate · ODC · `REGLES_PROJET.md` · `ETAT_PROJET.md` · `HISTORIQUE_MODIFICATIONS.md` · formalisations readiness · Plan production S3 · architecture `Source/GardenFervor/` · Investor Demo (consommateur uniquement) · enseignement Case B.

### Méthode

Pour chaque système :

1. preuve d’existence (code / doc / gate) ;
2. qualité documentaire (conception DG vs contrat opérationnel) ;
3. risques si on implémente sans préciser ;
4. dépendances amont / aval ;
5. décision : contrat autonome oui/non + profondeur + ordre.

### Distinction importante

| Couche | Rôle | Exemple |
| --- | --- | --- |
| **Conception (DG)** | Décisions VALIDÉES de design | DG-08 Raise/Lower/Paint ; DG-04 autonomie |
| **Preuve (T*/ODC)** | Existence contrôlée d’un sous-ensemble | T9 Cas A ; ODC-F8 brush |
| **Contrat opérationnel** | Règles d’exécution pour implémenter sans invention | « Quand ApplyBrushAt ? Combien ? Critère de fin ? » |

DG VALIDÉ ≠ contrat opérationnel suffisant pour toute extension.

### Hors périmètre de cet audit

- Modifier le Design Gate, la Roadmap, T1→T9, Case A, Investor Demo, C++, Case B.
- Rédiger un contrat individuel.
- Arbitrer silencieusement une contradiction : signaler seulement.

---

## 3. Tableau synthétique

Légende **Contrat** : `REQUIS` · `PARTIEL` · `SUFFISANT` (ailleurs) · `NON REQUIS`  
Légende **État code** : `I` implémenté · `P` partiel · `V` prévu · `N` non commencé

| ID | Système | Contrat | Profondeur | Doc actuelle | État code | Dépendances amont | Bloquant | Ordre |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| C-00 | Cadre / invariants fondateurs | NON REQUIS | — | DG-00 VALIDÉ | I | — | non | — |
| C-01 | Terrain runtime (vérité hauteur / shipping) | REQUIS | fondamentale | DG-08 · ODC-F1 À REFAIRE | P | C-00 | **oui** | 1 |
| C-02 | Substrat spatial (cellules / dirty / queries) | PARTIEL→REQUIS | détaillée | DG-08/09 · ODC-F3 PASS stubs | P | C-01 | **oui** | 2 |
| C-03 | Projet / Intention→Project | SUFFISANT* | secondaire | DG-01/11 · C4 · T6 | I (S3) | C-00 | non* | 3* |
| C-04 | Tâches / graphe / dépendances | PARTIEL | détaillée | DG-11 · ODC-F4 · **C-04 VALIDÉ** | I (S3) | C-03 | **oui** | 4 |
| C-05 | WorkSite / SitePrep (Cas A/B) | PARTIEL→REQUIS | détaillée | DG-11 · SitePrepTypes · T5 | P | C-01 · C-04 | **oui** | 5 |
| C-06 | Capacités / roster unités | SUFFISANT* | secondaire | DG-03 · UnitCapabilityTypes · T3 | I (S3) | C-00 | non* | 6* |
| C-07 | Autonomie unité (agent générique) | PARTIEL | détaillée | DG-04 · UnitTaskAgent · ODC-F5 | I | C-04 · C-06 | **oui** | 7 |
| C-08 | Terraformer opérationnel | REQUIS | détaillée | DG-08 · F8 · agent Terraform | P | C-01 · C-05 · C-07 | **oui** | 8 |
| C-09 | Économie physique / ResourceKey | SUFFISANT* | secondaire | DG-05 · C7 · T1/T2 | I (Timber) | C-00 | non* | 9* |
| C-10 | Stocks localisés A/B | SUFFISANT* | secondaire | DG-05 · C3 · T4 | I (S3) | C-09 | non* | 10* |
| C-11 | Réservations | PARTIEL | détaillée | DG-05.3 | P | C-09 · C-10 · C-04 | oui (avant multi-chantier) | 11 |
| C-12 | Transport / logistique | PARTIEL | détaillée | DG-06 · ODC-F7 · haul A→B | P | C-07 · C-10 | oui (au-delà S3) | 12 |
| C-13 | Construction / Achevé / En service | SUFFISANT* | secondaire | DG-02/11 · C5 · T7 | I (critère cohorte) | C-05 · C-10 | non* | 13* |
| C-14 | Infrastructures (lifecycle) | REQUIS | fondamentale | DG-10 · ODC-F9 non démarré | N | C-02 · C-05 · C-12 | **oui** (avant F9+) | 14 |
| C-15 | Hydrologie | REQUIS | détaillée | DG-09 · Spatial stub | N/P | C-02 · C-01 | oui (avant sim eau) | 15 |
| C-16 | Sol | REQUIS | détaillée | DG-09 · Spatial stub | N/P | C-02 · C-01 | oui (avant sim sol) | 16 |
| C-17 | Végétation / écosystèmes | PARTIEL→REQUIS | détaillée | DG-09 | N | C-15 · C-16 · C-01 | oui (avant eco) | 17 |
| C-18 | Technologie / progression | PARTIEL | détaillée | DG-07 · Ages legacy FWSG | P | C-00 · C-03 | oui (avant déblocages réels) | 18 |
| C-19 | Persistance / sauvegarde | REQUIS | fondamentale | DG · save Terraform désactivé | N/P | C-01 · C-09 · C-03 | **oui** (avant shipping) | 19 |
| C-20 | Observabilité / UX lisibilité | PARTIEL | secondaire→détaillée | DG-13 · C6 smoke | P | C-04 · C-07 · C-09 | non (preuve) / oui (produit) | 20 |
| C-21 | Simulation / fréquences / perf | PARTIEL | fondamentale | DG-00.5/00.6 | P | C-00 · C-02 | oui (avant scale) | 21 |
| C-22 | Investor Demo | NON REQUIS | — | Investor Demo docs | I (prés.) | consomme C-03…C-13 | non | — |
| C-23 | Présentation M4 / UDS | NON REQUIS† | secondaire | ODC-F2 · doc M4 externe | I | C-01 (rendu) | non† | — |

\* **SUFFISANT** pour le **périmètre cohorte S3 Cas A déjà VALIDÉ** — pas pour toute extension jeu.  
† Contrat autonome M4 non requis côté GardenFervor si on reste « M4 = rendu » ; tout gameplay terrain reste dans C-01.

---

## 4. Fiches détaillées (justification)

### C-00 — Cadre / invariants fondateurs

- **Rôle :** identité RTS, intention joueur, autonomie, monde comme matière, projet interne (DG-00 / principes P1–P7).
- **État :** conception VALIDÉE ; appliquée en règles projet.
- **Doc :** **suffisante** au niveau conception.
- **Contrat autonome :** **non** — un second document redondant avec DG-00 / REGLES.
- **Risque si manquant :** faible (déjà SoT Design Gate).
- **Ordre :** n/a (référence permanente, pas rédaction).

### C-01 — Terrain runtime

- **Sous-systèmes :** `LandscapeTerraformSubsystem` · `RuntimeTerraformStore` · BaseHeight · collision/visualizer inactifs · persistence off.
- **Rôle :** vérité hauteur / paint runtime ; shipping Base+Delta (cible F1) vs interim LandscapeEdit.
- **État code :** **partiel** (F8 données OK ; F1 shipping **À REFAIRE** ; PMC inactif).
- **Doc :** DG-08 VALIDÉ (concept) ; ODC-F1 incompleté opérationnellement pour shipping.
- **Contrat autonome :** **oui — fondamentale**.
- **Manque opérationnel :** vérité packaged vs PIE ; qui écrit quoi (store vs Landscape) ; dirty Spatial ; ce que « fin d’op terrain » garantit pour le gameplay.
- **Amont :** C-00 · **Aval :** C-02 · C-05 · C-08 · C-15…C-17 · C-19.
- **Bloquant :** **oui** pour toute vérité terrain shipping et pour Cas B « réel » durable.
- **Critère minimal futur contrat :** planes donnée/présentation ; modes Raise/Lower/Paint ; dirty ; non-objectifs (pas M4 gameplay).
- **Ordre 1.**

### C-02 — Substrat spatial

- **Sous-systèmes :** `SpatialSubsystem` · cells · dirty · QuerySoil/Water stubs.
- **État :** F3 PASS mais soil/water = stubs.
- **Doc :** partielle (DG-08/09 + F3) ; comportements environnementaux non liés.
- **Contrat :** **requis détaillé** avant de brancher eco/infra sur queries.
- **Amont :** C-01 · **Aval :** C-14…C-17 · C-21.
- **Bloquant :** **oui** dès qu’un système lit soil/water comme vérité.
- **Ordre 2.**

### C-03 — Projet / Intention→Project

- **Preuve :** `CreateProjectFromIntention` · C4 · T6 VALIDÉ · Demo Case A.
- **Doc opérationnelle S3 :** **suffisante**.
- **Contrat autonome :** **non requis maintenant** ; éventuel addendum si multi-objectifs / multi-projets hors WorkSite.
- **Ordre 3\*** (addendum seulement si besoin).

### C-04 — Tâches / graphe / dépendances

- **Sous-systèmes :** `TaskSubsystem` · TaskTypes · claim · readiness · progress.
- **État :** I pour chaînes S3 / LevelPad.
- **Contrat dédié :** **VALIDÉ** — `CONTRATS/C-04_TACHES_GRAPHE_DEPENDANCES.md` · **48/48** décisions A1–K6 · audit PASS.
- **Dettes d’implémentation (hors décision) :** Progress vs effets runtime ; invalidation monde non câblée ; multi-pulse ; mélange ExpandWorkSite ; LevelPad/WorkSite ; pool legacy ; Ecology.
- **Amont :** C-03 · **Aval :** C-05 · C-07 · C-08 · C-11 · C-12.
- **Bloquant :** **oui** (toujours pour chantiers riches / Case B — contrat opérationnel désormais disponible).
- **Ordre 4.**

### C-05 — WorkSite / SitePrep

- **Sous-systèmes :** `SitePrepTypes` · `ApplySitePreparation` · `ExpandWorkSite` · Cas A AlreadyReady · Cas B RequiresTerraform (code partiel, **suspendu**).
- **État :** Cas A VALIDÉ (T5/T9) · Cas B non VALIDÉ / suspendu.
- **Manque :** contrat Cas B (quand non prêt ; critères prêts ; pas de timer ; interaction Terraform).
- **Contrat :** **requis détaillé** avant reprise Case B / prep obligatoire.
- **Amont :** C-01 · C-04 · **Aval :** C-08 · C-13 · Demo Case B.
- **Bloquant :** **oui** pour Case B.
- **Ordre 5.**

### C-06 — Capacités / roster

- **Preuve :** Extraction/Transport/Construction · U1/U2/U3 · T3.
- **Suffisant pour S3.** Extension (Terraform comme capacité cohorte, équipements U6) → addendum.
- **Contrat autonome :** **non requis** tant que roster S3 suffit.
- **Ordre 6\***.

### C-07 — Autonomie unité (agent)

- **Sous-systèmes :** `UnitTaskAgent` (Seek→…→Verify) · InstantMode · Travel.
- **Doc :** DG-04 VALIDÉ (principes) ; **opérationnel partiel** (InstantMode masque durée/déplacement ; Execute ne produit pas les effets terrain — Verify le fait).
- **Manque :** contrat Instant vs réel ; quand appliquer effets ; interruption/reprise ; rapport de blocage.
- **Contrat :** **requis détaillé**.
- **Amont :** C-04 · C-06 · **Aval :** C-08 · C-12 · C-20.
- **Bloquant :** **oui** pour tout comportement « autonome visible ».
- **Ordre 7.**

### C-08 — Terraformer opérationnel *(signal Case B)*

- **Sous-systèmes :** tâche `Terraform` · cap `Terraform` · `UnitId=Terraformer` · `ApplyBrushAt` ×N même point · TerraformToolComponent (joueur).
- **État :** brush réel ODC-F8 ; agent LevelPad/Cas B smoke ; **perception progressive absente**.
- **Manque (checklist audit) :** décomposition spatiale du travail ; progression pendant Execute ; relation tâche↔brushes ; coopération ; interruption ; échec (Landscape manquant) ; reprise ; invalidation ; replanification ; critères de fin (au-delà de CompleteTask) ; observabilité ; interaction terrain (C-01).
- **Contrat :** **requis détaillé** — **bloquant** avant Case B Investor Demo ou prep « réelle » attendue.
- **Amont :** C-01 · C-05 · C-07 · **Aval :** Case B · infra travaux.
- **Ordre 8.**

### C-09 / C-10 — Économie physique · Stocks A/B

- **Preuve :** Timber · Deposit/Withdraw/GetAvailable · stocks distincts · T1/T2/T4/T9.
- **Suffisant pour S3 Cas A.**
- **Contrat autonome :** **non requis** pour le périmètre VALIDÉ ; extensions (multi-ressources, owners) → addenda après C-11.
- **Ordre 9\* / 10\***.

### C-11 — Réservations

- **État :** champ `Reservation` sur tâches (LevelPad FillDirt) ; cohorte Timber sans réservation complexe.
- **Doc :** DG-05.3 concept ; opérationnel mince.
- **Contrat :** **partiel → requis** avant concurrence multi-unités / multi-chantiers sur stocks.
- **Ordre 11.**

### C-12 — Transport / logistique

- **État :** haul A→B VALIDÉ ; réseaux DG-06 / saturation N4 non implémentés.
- **Contrat :** **partiel** — addendum S3 non requis ; **requis détaillé** avant réseaux.
- **Ordre 12.**

### C-13 — Construction / Achevé / En service

- **Preuve :** C5 · MarkConstructionComplete · RefreshCohortServiceState · T7/T9.
- **Suffisant pour critère cohorte** (pas règle universelle tous bâtiments — déjà documenté).
- **Contrat autonome :** **non requis** tant qu’on reste critère cohorte.
- **Ordre 13\***.

### C-14 — Infrastructures

- **État :** **non commencé** (ODC-F9 annoncé) · DG-10 VALIDÉ conceptuellement.
- **Contrat :** **requis fondamentale** avant F9+ — sinon invention de lifecycle.
- **Amont :** C-02 · C-05 · C-12.
- **Ordre 14.**

### C-15 / C-16 / C-17 — Eau · Sol · Végétation/écosystèmes

- **État :** Spatial stubs · DG-09 VALIDÉ · pas de sim réelle.
- **Contrats :** **requis** avant comportements eco (ordre Eau/Sol avant végétation).
- **Ordre 15 · 16 · 17.**

### C-18 — Technologie / progression

- **État :** Ages/Tech legacy FWSG vs DG-07 VALIDÉ — **tension** (voir § Zones d’ambiguïté).
- **Contrat :** **partiel → requis** avant déblocages « vrais » hors HUD legacy.
- **Ordre 18.**

### C-19 — Persistance / sauvegarde

- **État :** `bEnableRuntimeTerraformPersistence=False` · save terrain désactivé.
- **Contrat :** **requis fondamentale** avant shipping / F1 redo durable.
- **Ordre 19.**

### C-20 — Observabilité / UX

- **État :** C6 smoke/PE · Demo overlay · pas DG-13 produit.
- **Contrat :** secondaire pour preuves ; **détaillé** avant UX produit.
- **Ordre 20.**

### C-21 — Simulation / performance

- **Doc :** DG-00.5/00.6 (modes, dirty, fréquences) — principes VALIDÉS.
- **Contrat :** **partiel** — formaliser budgets/fréquences par couche avant scale.
- **Ordre 21** (peut avancer en parallèle après C-02).

### C-22 — Investor Demo

- **Rôle :** présentation consommant T1→T9 / PE / (futur) Case B.
- **Contrat autonome gameplay :** **non requis** — docs Investor Demo suffisent.
- **Règle :** ne jamais en faire une architecture parallèle.

### C-23 — M4 / UDS

- **Rôle :** présentation visuelle (ODC-F2 PASS).
- **Contrat GardenFervor autonome :** **non requis** si frontière « rendu ≠ gameplay » maintenue ; doc M4 externe pour intégration visuelle.

---

## 5. Ordre officiel de rédaction

Ordre **par dépendances** (pas thématique). Les entrées marquées `\*` ne sont rédigées que si le périmètre S3 ne suffit plus.

| Ordre | ID | Titre de contrat futur (indicatif) | Condition de démarrage |
| --- | --- | --- | --- |
| 1 | C-01 | Terrain runtime — vérité / shipping / dirty | Avant F1 redo ou vérité Cas B durable |
| 2 | C-02 | Substrat spatial — queries & dirty sémantique | Après C-01 |
| 3* | C-03 | Projet / Intention (addendum multi-objectif) | Seulement si hors WorkSite S3 |
| 4 | C-04 | Tâches — effets, progress, invalidation | Avant chantiers riches / Cas B robuste |
| 5 | C-05 | WorkSite / SitePrep Cas A|B | Avant reprise Case B |
| 6* | C-06 | Capacités (addendum) | Si nouvelles caps hors S3 |
| 7 | C-07 | Autonomie agent — Instant vs réel, effets | Avant C-08 |
| 8 | C-08 | Terraformer opérationnel | Après C-01 · C-05 · C-07 — **avant Case B Demo** |
| 9*–10* | C-09 · C-10 | PE / Stocks (addenda) | Multi-ressources / ownership |
| 11 | C-11 | Réservations concurrentes | Avant multi-chantier |
| 12 | C-12 | Logistique / réseaux | Avant DG-06 réseaux |
| 13* | C-13 | Service universel (addendum) | Si critère hors cohorte |
| 14 | C-14 | Infrastructures lifecycle | Avant ODC-F9 |
| 15 | C-15 | Hydrologie | Après C-02 |
| 16 | C-16 | Sol | Après C-02 |
| 17 | C-17 | Végétation / écosystèmes | Après C-15 · C-16 |
| 18 | C-18 | Progression / tech (hors Ages legacy) | Avant déblocages DG-07 runtime |
| 19 | C-19 | Persistance | Avant shipping |
| 20 | C-20 | Observabilité produit | Avant UX DG-13 complète |
| 21 | C-21 | Simulation / fréquences | Avant scale perf |

**Prochaine rédaction recommandée (si ordre explicite humain) :**  
`C-01` **ou**, si Case B est prioritaire après terrain minimal déjà accepté en PIE : enchaîner **C-05 → C-07 → C-08** sans sauter C-01 si la vérité shipping est exigée.

---

## 6. Contrats bloquants

Absence = **interdire** l’implémentation structurelle listée :

| ID | Bloque |
| --- | --- |
| **C-01** | F1 shipping · vérité terrain packaged · Cas B « durable » |
| **C-02** | Tout gameplay fondé sur soil/water spatial |
| **C-04** | Chantiers procéduraux / invalidation monde |
| **C-05** | Case B WorkSite / prep obligatoire |
| **C-07** | Autonomie visible non InstantMode |
| **C-08** | Terraformer « prépare progressivement » · Investor Demo Case B |
| **C-11** | Concurrence stocks multi-agents |
| **C-14** | ODC-F9 infrastructures |
| **C-15…C-17** | Sim environnementale réelle |
| **C-19** | Shipping / save monde |

---

## 7. Contrats non requis (documents autonomes)

| ID | Justification |
| --- | --- |
| **C-00** | DG-00 / principes déjà SoT |
| **C-03 / C-06 / C-09 / C-10 / C-13** *(périmètre S3 Cas A)* | Preuves T1→T9 + formalisations C4–C7 suffisent |
| **C-22** | Investor Demo = docs présentation, pas architecture |
| **C-23** | M4 = rendu ; doc vendor + ODC-F2 |

Ne pas créer un fichier contrat par classe (`*Subsystem`, `*Component`, widget Demo).

---

## 8. Zones d’ambiguïté / contradictions *(signalées, non arbitrées)*

1. **ETAT_PROJET** dit encore « implémentation cohorte non démarrée / readiness » alors que **T1→T9 = 9/9 VALIDÉ** et Investor Demo étapes 3–5 VALIDÉES — **divergence doc ↔ réalité** (à réconcilier hors cet audit).
2. **Ages / Tech FWSG** (Island) vs **DG-07** progression intentionnelle — deux stacks ; Demo isolement P0 les sépare, Island legacy reste.
3. **`LinkedPitStockId` = Stock A** — sémantique Pit/LevelPad vs cohorte (déjà noté Roadmap) — ne pas renommer sans décision.
4. **Cas B code présent** (RequiresTerraform / smoke) vs **Plan S3 « ne pas ajouter Case B »** vs **statut suspendu** — trois signaux ; aucune validation Case B.
5. **DG-14.4** « passage implémentation » vs implémentation déjà massivement présente — le Gate conception ≠ gel du code existant, mais le discours doc est flou.
6. **InstantMode** : outil de preuve vs comportement produit — non tranché dans un contrat (renvoie C-07).

---

## 9. Cas B — constat d’audit

**Case B reste suspendu.**  
Aucune modification de Case B, Terraformer, `ApplyBrushAt`, Investor Demo dans le cadre de cet audit.

### Signal

- Concept Terraformer + tâche Terraform + brush réel : **existent**.
- Contrat opérationnel (travail spatial progressif, observabilité de la préparation, fin ≠ burst InstantMode) : **insuffisant**.
- Audit PIE : Raise soudain = comportement **volontaire actuel** de l’agent (effets en Verify + InstantMode smoke), pas une fausse fin `bSiteReady` avant Complete.

### Conséquence registre

- **C-05** + **C-07** + **C-08** (et **C-01** si vérité terrain shipping) sont **bloquants** avant toute reprise Case B / Demo Case B.
- Ne pas brancher Investor Demo Case B tant que C-08 n’est pas rédigé **et** validé humainement.

---

## 10. Champs typiques des futurs contrats détaillés

À utiliser **selon besoin** (pas de checklist mécanique pour tous) :

| Système | Champs particulièrement nécessaires |
| --- | --- |
| C-01 | responsabilité vérité · planes donnée/présentation · dirty · limites · non-objectifs |
| C-04 | états tâche · progress vs effets · invalidation · prereqs |
| C-05 | préconditions SitePrep · Cas A/B · postconditions bSiteReady · pas de timer |
| C-07 | Instant vs réel · interruption · reprise · échec · observabilité agent |
| C-08 | décomposition spatiale · fin · échec Landscape · coopération · observabilité |
| C-14 | cycle de vie · temporaire/permanent · partage |
| C-19 | ce qui est persisté · migration · session-only |

---

## 11. Sources croisées (preuve d’audit)

| Source | Usage |
| --- | --- |
| `designGate.js` DG-00…14 | conception VALIDÉE |
| `ETAT_PROJET.md` · `HISTORIQUE_MODIFICATIONS.md` · `REGLES_PROJET.md` | état / process |
| Formalisations C4–C7 · Plan S3 | arbitrages cohorte |
| `Source/GardenFervor/RTS/{Terraform,Spatial,Projects,Tasks,Units,Economy}` | réalité code |
| Investor Demo docs + Game/*InvestorDemo* | consommation S3 Cas A |
| Audit Case B Raise instantané (session) | signal C-08 |

---

## 12. Règle de suite

1. Aucun contrat individuel sans ordre humain explicite.  
2. Rédiger dans l’**ordre officiel §5**.  
3. Un contrat `SUFFISANT*` S3 ne bloque pas le jeu actuel VALIDÉ.  
4. Case B / Demo Case B : **interdit** jusqu’à validation humaine des contrats bloquants C-05 · C-07 · C-08 (et C-01 si exigé).

---

*Fin du registre — aucun contrat individuel créé.*
