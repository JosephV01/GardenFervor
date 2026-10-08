# C-02 — Substrat spatial (cellules / dirty / queries)

| Champ | Valeur |
| --- | --- |
| **ID** | C-02 |
| **Nom** | Substrat spatial (cellules / dirty / queries) |
| **Statut documentaire** | **REVUE / DRAFT DE TRAVAIL** — rédigé sur décisions humaines ; **non VALIDÉ** |
| **Profondeur** | Détaillée (registre) |
| **Ordre de rédaction** | 2 |
| **Bloquant** | Oui (avant gameplay fondé sur soil/water spatial ; avant F9+ / eco) |
| **Dépendances amont** | **C-01** (VALIDÉ) |
| **Références** | Registre C-02 · DG 00.5.S2/S3/S5 · 00.6.M3 · DG-08.5 · DG-09.1/09.3 · REGLES §7bis · décisions humaines A1–F3 |

Ce document formalise les **décisions humaines C-02 validées** (A1–F3).  
Il n’invente aucune règle de gameplay supplémentaire.  
Il ne constitue pas une règle officielle tant qu’il n’est pas **VALIDÉ** dans le suivi.

---

## 1. Objet / rôle

C-02 définit le **substrat spatial commun** de GardenFervor :

- comment l’espace logique est découpé en cellules ;
- comment localiser et invalider des zones (Dirty) ;
- quelles lectures spatiales (queries) sont garanties ;
- comment rester cohérent avec l’autorité terrain **C-01** ;
- quelles frontières séparent C-02 des contrats métier et écologiques.

C-02 est une infrastructure de **lecture / invalidation spatiale**.  
Ce n’est pas un contrat métier d’écologie, de chantier, de Terraformer, de planification d’unités, ni l’autorité du relief.

---

## 2. Décisions validées (source de vérité)

Les décisions suivantes sont reprises **sans modification** :

### A — Cellules

| # | Décision |
| --- | --- |
| **A1** | Une cellule est à la fois : une unité spatiale logique ; une référence permettant de localiser les événements ; une référence permettant l’invalidation/recalcul ; une zone pouvant exposer des informations spatiales. La cellule **n’est pas** une unité de déformation du terrain. |
| **A2** | Granularité hybride : C-02 impose une contrainte contractuelle de granularité **suffisante** ; la valeur numérique exacte reste technique/configurable ; `16×16` **n’est pas** contractuel. La granularité C-02 ne doit jamais dégrader la résolution réelle de déformation de C-01. |
| **A3** | Une grille spatiale principale commune est utilisée. Des subdivisions locales peuvent être utilisées lorsqu’un système nécessite une précision supérieure. Ne pas créer plusieurs grilles mondiales concurrentes sans décision ultérieure. |
| **A4** | C-02 fournit un voisinage de base. Les systèmes peuvent demander une extension locale du voisinage selon leurs besoins. |
| **A5** | `QueryCell` n’est pas une obligation contractuelle à ce stade. |

### B — Dirty

| # | Décision |
| --- | --- |
| **B1** | Une cellule Dirty signifie qu’elle a été affectée et qu’une réévaluation locale peut être nécessaire. C-02 localise le changement ; les consommateurs décident ce qu’ils recalculent. |
| **B2** | Le mécanisme des canaux Dirty est contractuel et **extensible**. La liste actuelle des canaux ne doit pas être figée comme liste définitive de tous les futurs systèmes. |
| **B3** | C-02 fournit le mécanisme de déclaration Dirty. Les contrats propriétaires définissent quels systèmes peuvent déclarer quels canaux. |
| **B4** | Après consommation, C-02 remet son propre état Dirty à zéro. Les consommateurs restent responsables de leur propre suivi. |
| **B5** | Dirty est un état runtime/session. Il n’est pas persistant et ne fait pas partie de la sauvegarde du monde. |
| **B6** | C-02 ne garantit pas qu’un consommateur existe ou qu’un Dirty sera consommé. |
| **B7** | Aucune expiration temporelle automatique du Dirty. |
| **B8** | La forme contractuelle du Dirty est : **cellules** + **canaux**. Les rectangles/zones intermédiaires restent des détails d’implémentation. |

### C — Queries

| # | Décision |
| --- | --- |
| **C1** | C-02 garantit réellement les informations spatiales liées au **terrain**. L’architecture doit rester extensible pour permettre aux futurs contrats propriétaires d’ajouter leurs propres données. Les stubs Soil/Water ne doivent pas être présentés comme une simulation fonctionnelle déjà garantie. |
| **C2** | C-02 est la référence spatiale pour les lectures gameplay nécessitant une cohérence avec le runtime. Les usages purement techniques ou de présentation peuvent rester hors C-02. |
| **C3** | C-02 garantit : la **hauteur** ; la **possibilité d’obtenir la pente**. La méthode mathématique précise de calcul de la pente n’est pas figée par le contrat. |
| **C4** | Après une modification réelle du terrain, C-02 doit fournir une information de terrain cohérente avec cette modification. Le mécanisme technique de synchronisation n’est pas contractuellement imposé. |
| **C5** | Les capacités Soil/Water peuvent rester présentes comme capacités extensibles. Leur validité fonctionnelle dépendra des contrats propriétaires correspondants. |
| **C6** | La précision de `QueryTerrain` doit être au minimum celle de la donnée terrain fournie par C-01. C-02 ne doit pas dégrader cette précision. |
| **C7** | La pente est une capacité garantie, mais ses paramètres et sa méthode de calcul restent techniques tant qu’ils ne sont pas décidés ultérieurement. |
| **C8** | `WorldToCell` doit être déterministe dans le périmètre couvert et doit pouvoir signaler explicitement une position hors périmètre. |

### D — Synchronisation

| # | Décision |
| --- | --- |
| **D1** | La garantie porte sur le résultat observable : une modification réelle doit aboutir à une information spatiale cohérente. Le mécanisme interne des étapes de synchronisation reste technique. |
| **D2** | Les deux mécanismes Dirty suivants restent fonctionnellement distincts : Dirty C-01 / terrain / présentation / upload ; Dirty C-02 / cellules spatiales. Une optimisation future peut les rapprocher ou les fusionner uniquement si les garanties contractuelles restent inchangées. |
| **D3** | C-02 effectue uniquement les traitements spatiaux fondamentaux qui relèvent de son contrat. Les systèmes métier restent responsables de leurs propres recalculs. C-02 ne devient pas propriétaire de l’écologie, de l’eau, du foliage, etc. |
| **D4** | Le Dirty C-02 identifie contractuellement les cellules affectées. Des systèmes spécialisés peuvent obtenir ou exploiter une précision locale supérieure lorsque nécessaire. Le Dirty ne doit pas être confondu avec la précision géométrique exacte de la modification terrain. |

### E — Performance

| # | Décision |
| --- | --- |
| **E1** | Traitement localisé privilégié ; pas de scan global permanent ; un traitement global exceptionnel reste possible lorsqu’un futur contrat l’exige explicitement. |
| **E2** | Pas de tick spatial global permanent. Les traitements événementiels/localisés sont privilégiés. Un balayage périodique exceptionnel reste possible si un futur contrat le justifie. |
| **E3** | Ne pas fixer maintenant de nombre maximal universel de cellules traitées par événement. Le contrat peut imposer le principe de maîtrise des coûts ; les valeurs numériques restent techniques/profilables. |

### F — Frontières

| # | Décision |
| --- | --- |
| **F1** | C-02 **ne possède jamais** la hauteur terrain et ne modifie pas l’autorité terrain. **C-01** reste l’autorité de hauteur. |
| **F2** | C-02 ne décide pas des autorisations gameplay. L’autorisation appartient au système demandeur / contrat métier concerné. Les garde-fous techniques restent dans les contrats propriétaires appropriés. |
| **F3** | C-02 ne possède pas l’écologie. Il fournit les informations spatiales nécessaires et peut préparer les capacités d’extension correspondantes. Les systèmes écologiques restent propriétaires de leurs données et règles. |

---

## 3. Responsabilités

### 3.1 Ce que C-02 garantit

1. **Cellules logiques (A1, A2, A3)**  
   Une grille spatiale principale commune découpe l’espace en cellules logiques.  
   La cellule sert de référence de localisation, d’invalidation/recalcul et d’exposition d’informations spatiales.  
   Elle n’est pas l’unité de déformation du terrain (celle-ci reste sous C-01).

2. **Granularité suffisante sans dégrader C-01 (A2)**  
   La granularité C-02 doit être suffisante pour le rôle du substrat.  
   La valeur numérique exacte (ex. nombre de quads Landscape par arête) est technique/configurable et **non contractuelle**.  
   C-02 ne doit jamais dégrader la résolution réelle de déformation de C-01.

3. **Voisinage de base (A4)**  
   C-02 fournit un voisinage de base. Les systèmes peuvent demander une extension locale selon leurs besoins.

4. **Mécanisme Dirty (B1–B8)**  
   C-02 localise les cellules affectées et expose des canaux Dirty extensibles.  
   Forme contractuelle : cellules + canaux.  
   Après consommation, l’état Dirty **de C-02** est remis à zéro.  
   Dirty = runtime/session, non persisté, sans expiration temporelle automatique, sans garantie qu’un consommateur existe.

5. **Queries terrain (C1–C8)**  
   Lecture gameplay cohérente avec le runtime pour le terrain : hauteur (via autorité C-01) et possibilité d’obtenir la pente, sans dégrader la précision C-01.  
   `WorldToCell` déterministe dans le périmètre ; signal explicite hors périmètre.  
   Après modification réelle du terrain : information de terrain cohérente (résultat observable ; mécanisme technique libre).

6. **Extensibilité (C1, C5, B2, F3)**  
   Architecture ouverte aux données/canaux des contrats propriétaires futurs.  
   Capacités Soil/Water = extensibles ; validité fonctionnelle = contrats propriétaires (ex. C-15, C-16).  
   Stubs ≠ simulation garantie.

7. **Performance de principe (E1–E3)**  
   Traitement localisé et événementiel privilégié ; pas de scan/tick spatial global permanent ; maîtrise des coûts sans plafond numérique universel figé ici.

### 3.2 Ce que C-02 ne garantit pas / non-responsabilités

| Non-responsabilité | Appartenance |
| --- | --- |
| Autorité / écriture / déformation de la hauteur | **C-01** — F1, A1 |
| Méthode mathématique exacte de la pente | Technique / décision ultérieure — C3, C7 |
| Valeur numérique de granularité (ex. `16×16`) | Technique/configurable — A2 |
| Obligation d’API `QueryCell` | Hors obligation actuelle — A5 |
| Simulation fonctionnelle Soil / Water / végétation / écologie / foliage | Contrats propriétaires (C-15…C-17, …) — C1, C5, F3, D3 |
| Autorisations gameplay | Demandeurs / contrats métier — F2 |
| Consommation obligatoire du Dirty ; suivi métier post-Dirty | Consommateurs — B1, B4, B6, D3 |
| Persistance Dirty / politique save | **C-19** (Dirty hors sauvegarde monde) — B5 |
| Dirty Store / présentation / upload GPU | **C-01** (plan distinct) — D2 |
| Recalcul chantier, agent, Terraformer, économie | C-04, C-05, C-07, C-08, … |
| Mécaniques métier Creuser / Remblayer / Aplanir / terrassement | Hors C-02 (C-01 D13 + contrats métier) |
| Présentation Landscape / M4 / UDS | **C-23** |
| Plusieurs grilles mondiales concurrentes | Interdit sans décision ultérieure — A3 |

---

## 4. Cellules / représentation spatiale

### 4.1 Définition (A1)

Une **cellule** C-02 est :

1. une unité spatiale **logique** ;
2. une référence pour **localiser** les événements ;
3. une référence pour **invalidation / recalcul** ;
4. une zone pouvant **exposer** des informations spatiales.

Elle **n’est pas** une unité de déformation du terrain.

### 4.2 Relation à la résolution terrain C-01 (A2, D4, F1)

- La déformation et la vérité de hauteur restent à la résolution / autorité **C-01**.
- La cellule C-02 est une agrégation logique pour localisation, Dirty et lectures spatiales.
- Le Dirty cellules **ne se confond pas** avec la précision géométrique exacte de la modification terrain (D4).
- La granularité C-02 ne doit jamais **dégrader** la résolution de déformation C-01 (A2).
- Aucune valeur numérique de granularité (dont `16×16`) n’est contractuelle (A2).

### 4.3 Grille principale et subdivisions (A3)

- **Une** grille spatiale principale commune.
- Des **subdivisions locales** sont autorisées quand un système a besoin d’une précision supérieure.
- Plusieurs grilles mondiales concurrentes : **non**, sauf décision ultérieure explicite.

### 4.4 Voisinage (A4)

- C-02 fournit un **voisinage de base**.
- Extension locale possible à la demande des systèmes consommateurs.
- Le détail (4/8/autre, rayon) du voisinage de base n’est pas figé numériquement ici.

### 4.5 `QueryCell` (A5)

Non obligatoire contractuellement à ce stade.  
Les lectures peuvent s’appuyer sur `WorldToCell` et les queries au point / capacités garanties sans imposer une API `QueryCell`.

---

## 5. Dirty / invalidation

### 5.1 Signification (B1)

Une cellule Dirty indique qu’elle **a été affectée** et qu’une réévaluation locale peut être nécessaire.

C-02 **localise** ; les consommateurs **décident** quoi recalculer.

### 5.2 Forme contractuelle (B8)

| Contractuel | Non contractuel (implémentation) |
| --- | --- |
| Cellules dirty | Rectangles / sphères / AABB intermédiaires |
| Canaux dirty | Détails de conversion zone → cellules |

### 5.3 Canaux (B2, B3)

- Mécanisme de canaux : **contractuel** et **extensible**.
- La liste de canaux observée dans l’implémentation actuelle **n’est pas** la liste définitive de tous les futurs systèmes.
- C-02 fournit le **mécanisme de déclaration**.
- Les **contrats propriétaires** définissent quels systèmes peuvent déclarer quels canaux.

### 5.4 Cycle de vie (B4, B5, B6, B7)

| Étape | Règle |
| --- | --- |
| Déclaration | Via mécanisme C-02 ; droits = contrats propriétaires (B3) |
| Persistance | Runtime/session uniquement ; **hors** sauvegarde monde (B5) |
| Expiration | **Aucune** expiration temporelle automatique (B7) |
| Consommation | Remet l’état Dirty **de C-02** à zéro (B4) |
| Suivi consommateur | Responsabilité du consommateur (B4) |
| Obligation de consommation | **Aucune** (B6) |

---

## 6. Queries

### 6.1 Garanties terrain (C1, C3, C6, C7)

| Capacité | Statut contractuel |
| --- | --- |
| Hauteur | Garantie — lue depuis l’autorité **C-01**, sans dégrader sa précision (C3, C6, F1) |
| Pente | Capacité garantie (possibilité d’obtenir) ; méthode et paramètres **non figés** (C3, C7) |
| Soil / Water | Capacités **extensibles** possibles ; validité fonctionnelle = contrats propriétaires ; stubs ≠ sim garantie (C1, C5) |

### 6.2 Référence spatiale gameplay (C2)

C-02 est la référence spatiale pour les lectures gameplay nécessitant une cohérence avec le runtime.  
Usages purement techniques ou de présentation : peuvent rester hors C-02.

### 6.3 Cohérence après modification (C4, D1)

Après une **modification réelle** du terrain (C-01), C-02 doit fournir une information de terrain **cohérente** avec cette modification.  
Garantie = **résultat observable** ; mécanisme technique de synchronisation **non imposé**.

### 6.4 `WorldToCell` (C8)

- Déterministe dans le périmètre couvert.
- Doit pouvoir signaler explicitement une position **hors périmètre**.

### 6.5 Extensibilité (C1, C5)

L’architecture reste ouverte pour que les contrats propriétaires ajoutent leurs données / lectures.  
C-02 ne présente pas les stubs Soil/Water comme simulation déjà garantie.

---

## 7. Source de vérité des données

| Donnée | Autorité | Rôle C-02 |
| --- | --- | --- |
| Hauteur terrain | **C-01** | Relais de lecture / query ; jamais propriétaire (F1) |
| Pente | Dérivée de la hauteur C-01 (méthode technique) | Capacité d’obtention garantie (C3, C7) |
| Identité / emprise cellule | **C-02** | Grille principale + conversions (A1–A3, C8) |
| État Dirty cellules + canaux | **C-02** | Déclaration, stockage runtime, consommation (B*) |
| Dirty Store / upload / présentation | **C-01** | Plan distinct (D2) |
| Sol / eau / végétation / écologie (vérité) | Contrats propriétaires (C-15…C-17, …) | Accueil spatial / extension seulement (F3) |
| Autorisation d’agir | Contrats métier / demandeurs | Hors C-02 (F2) |

---

## 8. Synchronisation

1. **Résultat (D1, C4)** — Modification réelle → information spatiale terrain cohérente observable. Étapes internes = techniques.
2. **Deux Dirty (D2)** — Dirty C-01 (terrain / présentation / upload) ≠ Dirty C-02 (cellules). Fusion future seulement si garanties inchangées.
3. **Périmètre de traitement (D3)** — C-02 : traitements spatiaux fondamentaux uniquement. Recalculs métier / eco = propriétaires.
4. **Précision Dirty vs géométrie (D4)** — Dirty = cellules affectées ; précision géométrique exacte du relief = C-01 / systèmes spécialisés.

---

## 9. Performance

| Principe | Décision |
| --- | --- |
| Localisé privilégié ; pas de scan global permanent | E1 |
| Traitement global exceptionnel si futur contrat l’exige | E1 |
| Pas de tick spatial global permanent ; événementiel privilégié | E2 |
| Balayage périodique exceptionnel si futur contrat le justifie | E2 |
| Maîtrise des coûts ; pas de max universel de cellules/événement figé | E3 |

---

## 10. Entrées / sorties

### Entrées

| Entrée | Description | Qui |
| --- | --- | --- |
| Store / vérité terrain | Emprise + hauteur | **C-01** |
| Déclaration Dirty | Cellules / canaux (éventuellement via zone convertie en cellules) | Émetteurs autorisés par contrats propriétaires |
| Point monde | Pour `WorldToCell` / queries | Consommateurs |
| Demande de voisinage étendu | Extension locale | Systèmes consommateurs (A4) |

### Sorties

| Sortie | Description |
| --- | --- |
| Identifiant / ensemble de cellules | Localisation logique |
| Dirty (cellules + canaux) | État d’affectation consommable |
| Hauteur / pente (via query terrain) | Lectures garanties C3–C7 |
| `WorldToCell` (+ hors périmètre) | C8 |
| Capacités extensibles (ex. Soil/Water) | Non garanties comme sim tant que contrats propriétaires absents |

---

## 11. Frontières avec les autres contrats

| Contrat | C-02 | Autre |
| --- | --- | --- |
| **C-01** | Queries hauteur/pente ; Dirty cellules ; grille | Autorité hauteur ; déformation ; Dirty présentation/upload ; signal de modification |
| **C-04** | Peut fournir Dirty / localisation pour invalidation | Recalcul graphe / tâches |
| **C-05** | Localisation / lectures spatiales si besoin | SitePrep / `bSiteReady` / Cas A·B |
| **C-07** | Lectures spatiales cohérentes runtime si besoin | Agent / InstantMode / effets |
| **C-08** | Dirty / queries sur zones travaillées | Décomposition Terraformer, fin de grade |
| **C-14** | Grille / Dirty / queries pour infra | Lifecycle infrastructures |
| **C-15…C-17** | Accueil spatial, canaux extensibles, Dirty localisation | Vérité et règles eco / eau / sol / végétation |
| **C-19** | — | Save/load ; Dirty C-02 **hors** sauvegarde monde (B5) |
| **C-21** | Principes perf E1–E3 | Budgets / fréquences détaillés si besoin |
| **C-23** | — | Présentation M4 / UDS |

---

## 12. Limites

C-02 peut échouer / signaler hors périmètre / no-op technique si :

- store / bind terrain non prêt ;
- position hors périmètre couvert (`WorldToCell`) ;
- déclaration Dirty sans canaux pertinents (détail d’implémentation).

C-02 n’applique pas de hard gates gameplay, coûts, permissions d’unités, ni transitions écologiques.

---

## 13. Non-objectifs

C-02 ne définit **pas** :

- mécaniques métier Creuser / Remblayer / Aplanir ;
- règles de terrassement ou de chantier ;
- règles d’écologie, de foliage ou d’eau ;
- règles d’autorisation gameplay ;
- valeur numérique contractuelle de granularité (ex. `16×16`) ;
- méthode mathématique figée de la pente ;
- obligation `QueryCell` ;
- persistance du Dirty ;
- correction des dettes C-01 (ApplyBrushAt, GroundUtils, F1, etc.) ;
- Case B / Terraformer opérationnel.

---

## 14. Critères futurs de conformité

Après **validation** humaine du contrat et alignement d’implémentation, C-02 pourra être jugé conforme lorsque :

1. Grille principale + cellules selon A1–A3 ; granularité configurable sans dégrader C-01.  
2. Dirty = cellules + canaux ; consommation remet à zéro l’état C-02 ; session-only ; pas d’expiration auto.  
3. Queries terrain : hauteur via C-01, pente disponible, précision ≥ C-01 ; cohérence observable après modification réelle.  
4. `WorldToCell` déterministe + hors périmètre explicite.  
5. Soil/Water non présentés comme sim garantie.  
6. C-02 constitue la référence spatiale pour les lectures gameplay nécessitant une cohérence avec le runtime (C2) ; les usages purement techniques ou de présentation peuvent rester hors C-02.  
7. Dirty C-01 et Dirty C-02 restent distincts fonctionnellement (D2).  
8. Pas de scan/tick spatial global permanent (E1–E2).  
9. Frontières F1–F3 respectées.

---

## 15. Statut

| Couche | État |
| --- | --- |
| Décisions humaines A1–F3 | Reprises dans ce document |
| Contrat opérationnel C-02 | **REVUE / DRAFT DE TRAVAIL** |
| Validation suivi | **Non acquise** — ≠ `VALIDÉ` |
| Implémentation | Hors portée de cette rédaction |

---

*Fin C-02 — draft de travail en revue. Non VALIDÉ. Compteur global inchangé jusqu’à validation humaine.*
