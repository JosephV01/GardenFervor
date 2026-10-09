# C-08 — Terraformer opérationnel

| Champ | Valeur |
| --- | --- |
| **ID** | C-08 |
| **Nom** | Terraformer opérationnel |
| **Statut documentaire** | **VALIDÉ** — validation humaine explicite ; audit indépendant final 58/58 PASS ; dettes d’implémentation conservées (§22) |
| **Profondeur** | Détaillée (registre) |
| **Ordre de rédaction** | 8 |
| **Bloquant** | Oui (avant Case B / Demo Case B — registre) |
| **Dépendances amont** | **C-01** · **C-05** · **C-07** |
| **Références** | Registre C-08 · DG-08 · DG-11.6 · LandscapeTerraformSubsystem · UnitTaskAgent · ODC-F8 · décisions humaines A1–L4 (58) |

Ce document formalise les **58 décisions humaines C-08** reprises **sans modification de sens**.  
Il n’invente aucune règle supplémentaire.  
Il constitue la **règle opérationnelle** C-08 après validation humaine et inscription **VALIDÉ** dans le suivi.  
Il ne constitue **pas** une autorisation d’implémentation ni une réactivation de Case B.

**Case B** demeure **suspendu** jusqu’à décision humaine explicite de réouverture.

Référentiel des lettres validées (identité des options) :

```text
A1=C A2=B A3=B A4=B A5=B
B1=B B2=B B3=B B4=B B5=B
C1=B C2=B C3=B C4=B C5=B
D1=B D2=B D3=B D4=B D5=B
E1=B E2=B E3=B E4=B E5=B
F1=B F2=B F3=B F4=B F5=B
G1=B G2=B G3=B G4=B G5=B
H1=B H2=B H3=B H4=B H5=B
I1=B I2=B I3=B I4=B
J1=B J2=B J3=B J4=B J5=B J6=B
K1=B K2=B K3=B K4=B
L1=B L2=B L3=B L4=B
```

Le **sens opératoire** de chaque décision est celui de §2 ci-dessous (référentiel d’autorité).

---

## 1. Identité et finalité

C-08 est le contrat du **métier des opérations de terrassement** : résultats attendus, déroulement, décomposition opérationnelle, effets, matière, vérification et critères de réussite (A1).

Il relie :

- l’opération demandée ;
- la zone et le résultat attendus ;
- sa décomposition en étapes, sous-étapes, zones et passes ;
- le travail exécuté par les unités ;
- la transformation effective du relief ;
- les matériaux produits, déplacés ou consommés ;
- la vérification du résultat ;
- la reprise après interruption.

Il **ne** prend **pas** possession des systèmes voisins (A1) — notamment C-01, C-02, C-04, C-05, C-07, C-11, C-12, ni DG-11.6.

---

## 2. Décisions validées (source de vérité)

Les **58** décisions suivantes sont reprises **fidèlement**.

### A — Périmètre et responsabilités

| # | Lettre | Décision |
| --- | --- | --- |
| **A1** | C | Définir le **métier** des opérations de terrassement, leurs **résultats attendus**, leur **déroulement** et leurs **critères de réussite**, **sans** prendre possession des systèmes voisins. |
| **A2** | B | Distinguer les opérations métier **Creuser**, **Remblayer** et **Aplanir** des mécanismes techniques **Raise**, **Lower** et **Paint**. |
| **A3** | B | Identifier **explicitement** le type d’opération et ses paramètres ; **ne pas** déduire le métier de `DisplayName`. |
| **A4** | B | L’opération **reçoit** une cible ou un objectif du **système demandeur** ; C-08 en précise le **sens métier** et les **critères de réalisation**. |
| **A5** | B | L’opération exprime les **capacités** et **moyens nécessaires** ; les unités compatibles exécutent selon leurs **caractéristiques réelles**. |

### B — Modèle commun d’une opération

| # | Lettre | Décision |
| --- | --- | --- |
| **B1** | B | Une opération définit au minimum : **type**, **zone**, **objectif**, **exigences**, **travail restant**, **effets attendus**, **conditions de complétion**. |
| **B2** | B | Une opération nécessitant une cible **ne peut pas commencer** tant que celle-ci n’est pas définie ou résolue ; l’absence doit être **signalée**. |
| **B3** | B | Une opération métier peut nécessiter **plusieurs tâches** liées, avec dépendances et hiérarchie gérées par **C-04**. |
| **B4** | B | C-08 peut définir les **unités de travail** nécessaires ; **C-04** reste propriétaire du **graphe** et du **cycle de vie** des tâches. |
| **B5** | B | L’opération est terminée lorsque les **conditions de résultat** sont vérifiées et que les **effets matériels** sont correctement comptabilisés. |

### C — Creuser

| # | Lettre | Décision |
| --- | --- | --- |
| **C1** | B | Creuser **retire réellement** du relief dans une zone définie, selon un objectif de travail dont le résultat est **observable**. |
| **C2** | B | La matière extraite doit être **reliée** au travail réellement effectué et au matériau effectivement retiré. |
| **C3** | B | La quantité extraite est déterminée à partir du **résultat terrain réel**, selon une **politique explicite** de conversion relief↔matière. **Aucune formule numérique** n’est décidée ici. |
| **C4** | B | La matière doit rester **traçable** ; si elle ne peut être comptabilisée ou placée selon les règles disponibles, l’opération **ne** doit **pas** être déclarée correctement terminée. |
| **C5** | B | Réussite : objectif de retrait atteint selon les critères de l’opération **et** résultat matériel **cohérent**. |

### D — Remblayer

| # | Lettre | Décision |
| --- | --- | --- |
| **D1** | B | Remblayer exige une matière **disponible ou réservée** selon les mécanismes appropriés **avant** de produire les effets qui en dépendent. |
| **D2** | B | Résultat terrain et matière réellement déposée restent **cohérents** selon la politique de conversion et de traitement définie. |
| **D3** | B | Matière insuffisante : **ne pas** produire les effets qui en dépendent ; **signaler** la cause ; permettre une **réévaluation**. |
| **D4** | B | Chaque dépôt réellement accompli doit être **pris en compte** (terrain, matériaux, progression). |
| **D5** | B | Matière restante : **conservée** et comptabilisée selon les règles applicables ; **aucune** consommation fictive ni suppression automatique. |

### E — Aplanir

| # | Lettre | Décision |
| --- | --- | --- |
| **E1** | B | Aplanir transforme **progressivement** une surface vers un **profil** ou une **condition de nivellement** cible, via un **outil** et des **passes**. |
| **E2** | B | **Aplanir** et **compacter** sont des notions métier **distinctes** ; un compactage éventuel a ses propres conditions et résultats. |
| **E3** | B | Pas de création ni disparition **silencieuse** de matière ; mouvements locaux, retraits et apports **comptabilisés** selon les règles de l’opération. |
| **E4** | B | Les passes suivent les **caractéristiques opérationnelles** du véhicule et de son outil ; **pas** de largeur universelle imposée. |
| **E5** | B | Après les passes prévues, le résultat terrain doit **satisfaire** les critères définis pour l’opération. |

### F — Zones, passes et décomposition spatiale

| # | Lettre | Décision |
| --- | --- | --- |
| **F1** | B | Permettre un découpage en **zones**, **sous-zones**, **bandes** ou **passes** lorsque l’opération l’exige. |
| **F2** | B | Géométrie des passes fondée sur les caractéristiques **disponibles** du véhicule et de l’outil, complétées par les exigences de l’opération. |
| **F3** | B | Le découpage organise le travail **sans réduire** la précision de déformation offerte par **C-01**. |
| **F4** | B | **C-02** reste la référence spatiale ; C-08 peut utiliser un **découpage opérationnel spécialisé**. |
| **F5** | B | Le plan de travail indique portions **traitées**, **restantes** ou nécessitant une **nouvelle passe** (éviter trous et répétitions involontaires). |

### G — Progression, effets et vérification

| # | Lettre | Décision |
| --- | --- | --- |
| **G1** | B | Les effets peuvent être produits **au cours** de l’exécution, au fur et à mesure des unités de travail réelles. |
| **G2** | B | Pour les opérations Terraform, **Progress** reste cohérent avec le travail réel (portions, dépôts, étapes validées). |
| **G3** | B | Le résultat est vérifié via la vérité terrain **C-01** et les conditions métier ; les effets matériels doivent être **cohérents**. |
| **G4** | B | Une reprise tient compte du **travail restant** et des portions / effets **déjà accomplis**. |
| **G5** | B | Le nombre d’interventions et de passes dépend du travail **nécessaire** ; **aucun** nombre universel de pulses. |

### H — Matériaux, réservations et transport

| # | Lettre | Décision |
| --- | --- | --- |
| **H1** | B | Relation métier explicite entre matériau excavé, matériau disponible pour remblayer et résultats terrain, dans le cadre **DG-08**. |
| **H2** | B | Distinguer matière **réservée**, **réellement utilisée** et **reliquat** ; seule la consommation justifiée par le travail effectif peut être confirmée. |
| **H3** | B | C-08 précise besoins et résultats matériels ; **C-11** définit concurrence et arbitrage détaillés. |
| **H4** | B | C-08 exprime besoin de matière et résultat du dépôt ; **C-07** exécute ; **C-12** approfondit le transport ; stocks sous autorités compétentes. |
| **H5** | B | SpoilDirt / FillDirt restent des **matériaux internes** selon les règles définies, sauf liaison **explicitement validée** avec l’économie globale. |

### I — Interruption, reprise, blocage et échec

| # | Lettre | Décision |
| --- | --- | --- |
| **I1** | B | Les modifications réelles déjà accomplies **restent réelles** ; l’opération conserve les informations pour poursuivre ou réconcilier le travail restant. |
| **I2** | B | Effet appliqué mais comptabilité incomplète : **pas** de succès tant que l’incohérence n’est pas résolue ; **pas** de répétition aveugle de l’effet. |
| **I3** | B | Impossibilité temporaire : **signaler** le motif ; situation **récupérable** possible ; **C-04** autorité sur l’état de la tâche. |
| **I4** | B | C-08 fournit l’**état métier** et les **preuves de résultat** ; C-04 conserve l’autorité sur l’état de la tâche. |

### J — Interfaces entre contrats

| # | Lettre | Décision |
| --- | --- | --- |
| **J1** | B | **C-01** = autorité du relief ; C-08 demande les modifications via le système compétent et vérifie à partir d’informations cohérentes avec cette vérité. |
| **J2** | B | **C-02** = référence spatiale ; C-08 exploite les infos nécessaires sans posséder Dirty ni imposer la granularité de déformation. |
| **J3** | B | C-08 = métier et besoins de décomposition ; **C-04** = hiérarchie, dépendances, états, orchestration. |
| **J4** | B | **C-05** décide si une préparation est nécessaire ; C-08 produit la **preuve métier** de satisfaction des conditions. |
| **J5** | B | **C-07** exécute les tâches ; C-08 définit l’opération, paramètres fonctionnels et critères de résultat. |
| **J6** | B | C-08 fournit une preuve métier de préparation ; **C-05** décide si elle satisfait **SiteReady**. |

### K — Portée, modes existants et Case B

| # | Lettre | Décision |
| --- | --- | --- |
| **K1** | B | Formaliser C-08 **sans** réactiver, implémenter ou valider Case B ; réactivation = autorisation explicite distincte. |
| **K2** | B | C-08 définit les états d’opération nécessaires à une reprise cohérente ; la **persistance** reste au système compétent (**C-19** notamment). |
| **K3** | B | Ne pas attribuer automatiquement à **Paint** une signification écologique ou économique ; Raise/Lower/Paint restent **distincts** du modèle métier. |
| **K4** | B | L’outil joueur peut partager des mécanismes techniques, mais **n’est pas** à lui seul la spécification du métier Terraform des unités. |

### L — Preuves, validation et maturité produit

| # | Lettre | Décision |
| --- | --- | --- |
| **L1** | B | Tests accélérés prouvent uniquement ce qu’ils couvrent ; validation produit : déplacement réel, effet terrain, comportement observable. |
| **L2** | B | Validation : opération réelle, cohérence relief↔matière lorsque pertinente, satisfaction des critères de résultat. |
| **L3** | B | Opération progressive : changements réels **observables** pendant le travail et cohérents avec l’avancement. |
| **L4** | B | Contrôles courts et ciblés (relief, matériaux, passes, interruption, vérification) + validation visuelle humaine lorsque suffisant. |

---

## 3. Portée et responsabilités

### 3.1 Ce que C-08 possède

| Domaine | Responsabilité |
| --- | --- |
| Métier | Creuser · Remblayer · Aplanir (+ compactage distinct si ouvert) |
| Opération | Type, paramètres, objectif, critères, travail restant |
| Décomposition | Unités de travail, zones, passes (besoins) — graphe = C-04 |
| Effets | Moment et sens métier des transformations (via C-01) |
| Matière | Besoins, résultats, cohérence relief↔matériaux (cadre DG-08) |
| Preuve | Preuve métier de résultat / préparation pour C-05 |

### 3.2 Ce que C-08 ne possède pas

| Domaine | Autorité |
| --- | --- |
| Vérité hauteur | **C-01** |
| Référence spatiale / Dirty | **C-02** |
| Graphe / états de tâche | **C-04** |
| Besoin SitePrep / SiteReady | **C-05** |
| Exécution générique unité | **C-07** |
| Concurrence réservations | **C-11** |
| Transport avancé | **C-12** |
| Persistance shipping | **C-19** |
| Réaction chantier globale | **DG-11.6** |

---

## 4. Vocabulaire métier

| Terme | Sens dans C-08 |
| --- | --- |
| **Opération Terraform (métier)** | Intention de terrassement typée (Creuser / Remblayer / Aplanir…), avec zone, objectif et critères. |
| **Creuser** | Retrait réel de relief selon objectif ; matière produite liée au retrait (C1–C5). |
| **Remblayer** | Apport de matière puis effet terrain cohérent (D1–D5). |
| **Aplanir** | Mise progressive vers un profil / condition de nivellement via passes (E1–E5). |
| **Compacter** | Notion métier **distincte** d’Aplanir ; conditions propres si ouverte (E2). |
| **Raise / Lower / Paint** | Mécanismes techniques de modification (C-01 / runtime) — **pas** les opérations métier finales (A2, K3). |
| **Zone / sous-zone / bande / passe** | Unités de planification du travail (F1–F5) — ≠ grille C-02, ≠ résolution C-01. |
| **Travail restant** | Portion / étapes encore à accomplir pour atteindre les critères (B1, F5, G4). |
| **Preuve métier** | Résultat vérifié (relief + matière cohérents) fourni aux demandeurs, notamment C-05 (B5, G3, J6). |
| **SpoilDirt / FillDirt** | Matériaux **internes** (DG-08 / H5) ; relation métier avec excavation / remblai (H1). |

---

## 5. Modèle commun d’une opération

### 5.1 Identification (A3, B1)

Une opération est identifiée par un **type explicite** et des **paramètres**, jamais par un `DisplayName` d’affichage (A3).

Informations contractuelles minimales (B1) :

1. type d’opération ;
2. zone (et découpage éventuel) ;
3. objectif / cible ;
4. exigences (capacités, matière, préconditions) ;
5. travail restant ;
6. effets attendus ;
7. conditions de complétion.

### 5.2 Origine de la cible (A4, B2)

- Le **système demandeur** (ex. C-05 / Project) fournit la cible ou l’objectif (A4).
- C-08 en précise le **sens métier** et les **critères de réalisation** (A4).
- Sans cible requise définie ou résolue : **pas de démarrage** ; absence **signalée** (B2).
- Un offset SitePrep n’est **pas** automatiquement un profil ni une preuve de réussite (constat ; B2).

### 5.3 Capacités et unités (A5)

L’opération déclare les **capacités / moyens** nécessaires.  
Les unités compatibles exécutent selon leurs **caractéristiques réelles** (outil, largeur, etc.) — pas une règle figée par modèle unique (A5, E4, F2).

### 5.4 Relation opération ↔ tâches (B3, B4, J3)

```text
Opération métier C-08
        │
        ▼ besoins de décomposition
C-04 — tâches / sous-tâches / dépendances / cycle de vie
        │
        ▼ claim / exécution
C-07 — unités
        │
        ▼ demandes de modification
C-01 — vérité relief
```

- Une opération peut se décomposer en **plusieurs tâches** C-04 (B3).
- C-08 définit les **unités de travail** ; C-04 possède le graphe (B4, J3).
- Pas d’ordonnanceur concurrent à C-04 (J3).

### 5.5 Complétion métier (B5)

Terminée **seulement si** :

- conditions de résultat vérifiées ;
- effets matériels correctement comptabilisés.

≠ succès d’un brush, ≠ fin de timer, ≠ `Completed` de tâche seul (B5, G3, J6).

---

## 6. Creuser

| Règle | Décision |
| --- | --- |
| Sens | Retrait **réel** de relief dans une zone, objectif observable (C1) |
| Matière | Reliée au travail et au matériau effectivement retiré (C2) |
| Quantité | Issue du résultat terrain réel via politique de conversion **explicite** ; **pas** de formule numérique dans ce contrat (C3) |
| Traçabilité | Si non comptabilisable / non plaçable selon règles : **pas** de terminaison correcte (C4) |
| Réussite | Objectif de retrait atteint **et** résultat matériel cohérent (C5) |

**Interdit comme comportement métier final :** produire de la matière sans retrait de relief correspondant (constat runtime ; C1–C2).

---

## 7. Remblayer

| Règle | Décision |
| --- | --- |
| Précondition matière | Disponible ou réservée avant effets dépendants (D1) |
| Cohérence | Terrain ↔ matière déposée selon politique de conversion (D2) |
| Insuffisance | Pas d’effet sans matière ; signaler ; réévaluer (D3) |
| Dépôts partiels | Chaque dépôt réel comptabilisé (terrain, matière, progression) (D4) |
| Reliquat | Conservé / comptabilisé ; pas de consommation fictive ni suppression auto (D5) |

Plusieurs dépôts successifs (rotations) sont un cas nominal du modèle progressif (D4, G1, L3).

---

## 8. Aplanir

| Règle | Décision |
| --- | --- |
| Sens | Transformation progressive vers profil / condition de nivellement via outil et passes (E1) |
| ≠ CompactSite | Ne pas assimiler Aplanir à un petit Lower technique (E1) |
| Matière | Pas de création / disparition silencieuse ; mouvements comptabilisés (E3) |
| Passes | Selon véhicule + outil ; pas de largeur universelle (E4) |
| Fin | Passes prévues **puis** critères terrain satisfaits (E5) |

---

## 9. Compactage (distinct)

**Aplanir** et **compacter** sont des notions métier **distinctes** (E2).

- Une éventuelle opération de compactage aura ses propres conditions et résultats (E2).
- La **politique spécialisée** du compactage reste un **point ouvert** (§23) — non inventée ici.
- L’alias technique actuel `CompactSite` (petit Lower) n’est **pas** le métier de compactage (constat / dette §22).

---

## 10. Zones et décomposition opérationnelle

| Règle | Décision |
| --- | --- |
| Découpage | Zones, sous-zones, bandes, passes lorsque requis (F1) |
| ≠ centre unique | Le travail au seul centre de `ZoneBounds` n’est pas le modèle métier (constat ; F1) |
| Précision | Découpage **sans** réduire la précision C-01 (F3) |
| C-02 | Référence spatiale générale ; découpage C-08 **spécialisé** possible (F4) |
| Couverture | Plan : traité / restant / nouvelle passe (F5) |

Les cellules C-02 **ne** sont **pas** automatiquement la résolution du travail ni de la déformation (F3, F4 ; aligné C-04 K6).

---

## 11. Passes et caractéristiques des outils

| Règle | Décision |
| --- | --- |
| Géométrie | Caractéristiques véhicule + outil + exigences opération (F2, E4) |
| Largeurs | **Pas** de valeur numérique imposée ici (points ouverts §23) |
| Interventions | Nombre nécessaire au travail — pas de « 3 pulses » universels (G5) |

L’outil joueur peut partager des mécanismes techniques C-01 ; il **n’est pas** la spécification du métier autonome (K4).

---

## 12. Progression et effets

| Règle | Décision |
| --- | --- |
| Moment des effets | Au cours de l’exécution, par unités de travail réelles (G1) |
| Progress | Cohérent avec travail réel (portions, dépôts, étapes) (G2) |
| Progressif observable | Changements réels observables pendant le travail si opération progressive (L3) |
| ≠ timer seul | Un timer C-07 peut rythmer ; il ne prouve pas la transformation (G2 ; C-07 D1/E1) |

---

## 13. Vérification du résultat

| Règle | Décision |
| --- | --- |
| Source | Vérité terrain **C-01** + conditions métier de l’opération (G3, J1) |
| Matière | Effets matériels cohérents avec le résultat (G3, B5) |
| ≠ ApplyBrushAt seul | Succès technique d’un brush ≠ réussite métier (G3, B5) |
| ≠ Task Completed | État tâche C-04 ≠ preuve métier (I4, J6) |

Méthode de mesure et tolérances numériques : **ouvertes** (§23) — non inventées.

---

## 14. Matière, réservations et reliquats

| Règle | Décision |
| --- | --- |
| Relation métier | Excavé ↔ disponible remblai ↔ résultat terrain (H1, DG-08) |
| Réservé / utilisé / reliquat | Distinction obligatoire (H2) |
| Confirmation | Seule consommation justifiée par travail effectif (H2) |
| Concurrence | Besoins C-08 ; arbitrage **C-11** (H3) |
| Transport | Besoin / dépôt C-08 ; exécution C-07 ; approfondissement **C-12** (H4) |
| Économie | SpoilDirt / FillDirt internes sauf liaison explicite validée (H5) |

---

## 15. Interruption, reprise, blocage et échec

| Situation | Règle |
| --- | --- |
| Terrain déjà modifié | Modifications **restent** ; infos de reprise / réconciliation conservées (I1) |
| Effet sans compta | Pas de succès ; pas de rejeu aveugle de l’effet (I2) |
| Impossible temporaire | Signal + récupérable possible ; états tâche = **C-04** (I3) |
| Autorité états | État métier / preuves = C-08 ; état tâche = C-04 (I4) |
| Reprise | Travail restant + portions / effets déjà accomplis (G4) |

Mécanique technique exacte de réconciliation : **ouverte** (§23).

---

## 16. Interfaces C-01 / C-02 / C-04 / C-05 / C-07

| Contrat | Interface |
| --- | --- |
| **C-01** | Autorité relief ; C-08 demande modifications et vérifie via cette vérité (J1) |
| **C-02** | Référence spatiale ; C-08 n’impose pas Dirty ni granularité de déformation (J2) |
| **C-04** | Graphe, hiérarchie, dépendances, états, orchestration (J3, B3, B4) |
| **C-05** | Décide besoin de préparation ; consomme preuve métier C-08 pour SiteReady (J4, J6) |
| **C-07** | Exécute les tâches ; ne possède pas le métier Terraform (J5) |

Architecture cible :

```text
Demande de terrassement
        │
        ▼
C-05 — préparation requise ?
        │
        ▼
C-08 — définition opération (Creuser / Remblayer / Aplanir)
        │
        ▼
C-04 — tâches / sous-tâches
        │
        ▼
C-07 — exécution unités
        │
        ▼
C-01 — modifications relief
        │
        ▼
C-08 — preuve métier
        │
        ▼
C-05 — SiteReady si conditions satisfaites
```

---

## 17. Interfaces C-11 / C-12 / économie / C-19

| Élément | Frontière |
| --- | --- |
| **C-11** | Concurrence et réservations détaillées (H3) |
| **C-12** | Transport avancé (H4) |
| **Économie globale** | Pas d’intégration automatique Spoil/Fill ; liaison explicite uniquement (H5, DG-08) |
| **Stocks** | Autorité des systèmes compétents (H4) |
| **C-19** | Persistance ; C-08 définit états de reprise, pas le save (K2) |

---

## 18. SiteReady et preuve métier

| Règle | Décision |
| --- | --- |
| Preuve | C-08 fournit la preuve métier de préparation / résultat (J4, J6, B5) |
| Décision SiteReady | **C-05** uniquement (J6) |
| Interdit | Terraform `Completed` ⇒ SiteReady automatique (J6 ; aligné C-05 D3) |
| En service | Hors C-08 (C-13\* / chantier) |

---

## 19. Case A / Case B

| Cas | Statut dans ce contrat |
| --- | --- |
| **Case A** | Hors obligation Terraform ; inchangé (preuves S3 existantes) |
| **Case B** | **Suspendu** — formaliser C-08 **ne** réactive **pas**, n’implémente pas et ne valide pas Case B (K1) |

Toute reprise Case B exige une **autorisation humaine explicite distincte** (K1).

---

## 20. Preuves et critères de validation

| Règle | Décision |
| --- | --- |
| Instant / accéléré | Couverture limitée ; ≠ validation produit complète (L1) |
| Critère métier | Opération réelle + cohérence relief↔matière si pertinente + critères satisfaits (L2) |
| Progressif | Changements observables cohérents avec l’avancement (L3) |
| Pratique | Contrôles courts ciblés + validation visuelle humaine si suffisant (L4) |

---

## 21. Frontières et non-objectifs

C-08 **ne** :

- ne possède pas la hauteur (C-01) ;
- ne possède pas Dirty / grille C-02 comme vérité de travail ;
- ne remplace pas le graphe C-04 ;
- ne décide pas SitePrep / SiteReady (C-05) ;
- n’embarque pas la logique métier dans C-07 ;
- ne définit pas concurrence C-11 ni transport C-12 ;
- n’attribue pas à Paint un sens écologique / économique (K3) ;
- n’invente pas de formules, largeurs, tolérances ou profils numériques ;
- ne réactive pas Case B (K1) ;
- ne corrige pas les dettes §22.

---

## 22. Dettes et écarts d’implémentation connus

Constats runtime — **pas** des règles souhaitées ; **non corrigés** ici :

| Dette | Nature |
| --- | --- |
| Effets à Verify | Agent Terraform applique `ApplyBrushAt` en Verify, pas au fil de Execute (écart G1) |
| 3 pulses même point | Nombre fixe au même lieu (écart G5, F1) |
| DisplayName Raise/Lower/Compact | Métier déduit de l’affichage (écart A3, E1, E2) |
| Cibles / profils / tolérances | Absents côté métier |
| Zones / passes | Absents |
| ExtractSpoil sans Lower | Matière sans retrait de relief (écart C1–C2) |
| FillDirt ≠ delta hauteur | Consommation non reliée au résultat terrain (écart D2) |
| Aplanir | Absent ; CompactSite = petit Lower (écart E1–E2) |
| SiteReady ≈ Terraform Completed | Écart J6 / C-05 D3 |
| ApplyBrushAt `Store \|\| Landscape` | Dette C-01 E1 |
| GroundUtils / overlay | Dette C-01 E2 |
| Persistance relief off | Dette C-01 / C-19 |
| Collision / visualizer PMC | Inactifs |
| Textes gates vs code | Ex. mentions EXECUTE vs Verify réel |

---

## 23. Points ouverts / hors périmètre

Aucun arbitrage nouveau. Restent ouverts :

- valeurs numériques des profils et tolérances ;
- formule précise volume déplacé ↔ variation de hauteur ;
- largeurs véhicules / outils ;
- géométrie concrète des passes ;
- détails d’implémentation du calcul de quantité ;
- API exacte de preuve et de réconciliation ;
- politique spécialisée du compactage ;
- stratégie de sauvegarde concrète (C-19) ;
- réactivation de Case B ;
- campagne de preuves produit post-VALIDÉ.

---

## 24. Dépendances

| Direction | Éléments |
| --- | --- |
| **Amont** | **C-01** · **C-05** · **C-07** |
| **Aval** | Case B (si autorisé) · infra travaux |
| **Complémentaire** | C-02 · C-04 · C-11 · C-12 · C-19 · DG-08 · DG-11.6 |

---

## 25. Couverture des 58 décisions

| Bloc | Décisions | Lettres | Section(s) principales |
| --- | --- | --- | --- |
| A | A1–A5 | C,B,B,B,B | §1–§3, §5 |
| B | B1–B5 | B×5 | §5 |
| C | C1–C5 | B×5 | §6 |
| D | D1–D5 | B×5 | §7 |
| E | E1–E5 | B×5 | §8–§9 |
| F | F1–F5 | B×5 | §10–§11 |
| G | G1–G5 | B×5 | §12–§13 |
| H | H1–H5 | B×5 | §14, §17 |
| I | I1–I4 | B×4 | §15 |
| J | J1–J6 | B×6 | §16, §18 |
| K | K1–K4 | B×4 | §11, §17, §19 |
| L | L1–L4 | B×4 | §20 |

**Total : 58 / 58.**

Contrôle de clôture :

- audit indépendant final : **PASS** (58/58) ;
- validation humaine : **acquise** ;
- dettes = constats (§22) ;
- frontières préservées ;
- Case B **suspendu** ;
- statut **VALIDÉ**.

---

## 26. Statut

| État | Valeur |
| --- | --- |
| Document | `CONTRATS/C-08_TERRAFORMER_OPERATIONNEL.md` |
| Statut | **VALIDÉ** |
| Règle officielle | **Oui** — validation humaine ; audit indépendant final 58/58 PASS |
| Décisions | **58 / 58** (A1–L4) |
| Compteur global | **6 / 16** (C-03, C-06, C-09, C-10 hors dénominateur) |
| Case B | **Suspendu** |

---

*Fin C-08 — VALIDÉ. C-03, C-06, C-09 et C-10 demeurent addenda fermés. Case B demeure suspendu. Aucune implémentation ni contrat suivant démarrés par cette clôture.*
