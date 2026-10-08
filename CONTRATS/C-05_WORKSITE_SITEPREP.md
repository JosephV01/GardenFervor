# C-05 — WorkSite / SitePrep (Cas A/B)

| Champ | Valeur |
| --- | --- |
| **ID** | C-05 |
| **Nom** | WorkSite / SitePrep (Cas A/B) |
| **Statut documentaire** | **VALIDÉ** — validation humaine explicite ; audit 62/62 PASS ; dettes d’implémentation conservées (§20) |
| **Profondeur** | Détaillée (registre) |
| **Ordre de rédaction** | 5 |
| **Bloquant** | Oui (avant reprise Case B / Demo Case B — registre) |
| **Dépendances amont** | **C-01** · **C-04** |
| **Références** | Registre C-05 · DG-11 · DG-11.6 · SitePrepTypes · ApplySitePreparation · ExpandWorkSite · T5 / T9 Cas A · décisions humaines A1–N3 (62) |

Ce document formalise les **62 décisions humaines C-05** reprises **sans modification de sens**.  
Il n’invente aucune règle supplémentaire.  
Il constitue la **règle opérationnelle** C-05 après validation humaine et inscription **VALIDÉ** dans le suivi.  
Il ne constitue **pas** une autorisation d’implémentation ni une réactivation de Case B.

**Case B** demeure **suspendu** jusqu’à décision humaine explicite de réouverture.

---

## 1. Objet / rôle

C-05 est le contrat qui décide **si un WorkSite doit être préparé avant de pouvoir poursuivre son chantier**, et qui définit la notion de **site prêt**.

Il répond principalement à quatre questions :

1. Le site doit-il être préparé ?
2. Quel site doit l’être ?
3. Quand est-il considéré comme prêt ?
4. La suite du chantier peut-elle maintenant être autorisée ?

C-05 **ne** :

- exécute pas le terrassement ;
- modifie pas le terrain ;
- définit pas les véhicules, trajectoires, Creuser / Remblayer / Aplanir ;
- devient pas l’autorité du graphe ;
- remplace pas C-04 ni C-08 ;
- décide pas qu’un chantier est **En service**.

---

## 2. Décisions validées (source de vérité)

Les **62** décisions suivantes sont reprises **sans modification**.  
**D5 = C** · **D6 = B** (confirmés explicitement).

### A — Périmètre

| # | Décision |
| --- | --- |
| **A1** | C-05 possède : la décision de nécessité du SitePrep ; son état contractuel ; ses préconditions ; ses postconditions ; la condition de passage vers la suite du chantier. Il ne possède pas l’exécution. |
| **A2** | C-05 est principalement défini pour les **WorkSite**. Les autres modèles de Project restent hors contrat tant qu’ils ne nécessitent pas explicitement cette formalisation. |
| **A3** | C-05 est **indépendant du type d’unité**. Il décrit un besoin de préparation de site, pas l’engin qui réalisera cette préparation. |
| **A4** | C-05 ne modifie jamais directement : la hauteur ; les surfaces ; les ressources ; les unités ; les infrastructures. Il demande/requiert une préparation ; les contrats et systèmes spécialisés produisent les effets. |

### B — Modes de SitePrep

| # | Décision |
| --- | --- |
| **B1** | Conserver les trois modes existants : `None` · `AlreadyReady` · `RequiresTerraform`. Aucun quatrième mode fondateur maintenant. |
| **B2** | **None** = aucun SitePrep n’est requis pour ce Project. **AlreadyReady** = une obligation de préparation existe conceptuellement mais le site est déjà conforme à son entrée de chantier. **RequiresTerraform** = le site doit être préparé avant l’ouverture de la suite opérationnelle. |
| **B3** | Le choix du mode doit être déterminé **avant l’ouverture de la chaîne opérationnelle dépendante du SitePrep**. Il ne doit pas être découvert accidentellement après le début du chantier. |
| **B4** | Le besoin de préparation est déterminé par les **conditions du chantier et du site**, pas simplement par : la disponibilité d’une unité ; une réservation temporairement indisponible ; un manque de ressource logistique. Ces problèmes relèvent de C-04 / C-07 / C-11 / DG-11.6 selon leur nature. |

### C — Zone de préparation

| # | Décision |
| --- | --- |
| **C1** | La zone de base du SitePrep est celle définie par le **WorkSite / ZoneBounds**. C-05 doit pouvoir exprimer : « cette partie du terrain doit être prête ». |
| **C2** | Le découpage interne de la zone en sous-zones, cellules de travail, bandes, passes, secteurs n’est **pas** imposé par C-05. Ce découpage appartient au système métier approprié, notamment C-08. |
| **C3** | Les subdivisions opérationnelles du SitePrep peuvent être plus fines que la grille C-02. Elles ne constituent pas une nouvelle grille mondiale. |
| **C4** | C-05 ne définit aucun nombre fixe de sous-zones. La granularité nécessaire dépend de la préparation réelle à effectuer. |

### D — SiteReady

| # | Décision |
| --- | --- |
| **D1** | `SiteReady` représente un **état de conformité du site**, pas l’état d’une tâche. |
| **D2** | `SiteReady = true` uniquement lorsque **toutes les conditions nécessaires à l’ouverture de la suite du chantier sont satisfaites**. |
| **D3** | La simple fin d’une tâche Terraform **ne suffit pas à elle seule** à déclarer `SiteReady`. Il faut une validation du résultat attendu. |
| **D4** | C-05 doit pouvoir recevoir une **preuve de préparation réussie** produite par le système métier responsable. C-08 pourra notamment fournir la preuve relative au terrassement. |
| **D5** | C-05 **ne fixe pas** lui-même les valeurs numériques détaillées du résultat terrain (hauteur exacte, tolérance, pente, largeur de passe, quantité de matériau, profil, etc.). Ces règles appartiennent au contrat métier approprié. |
| **D6** | Une fois `SiteReady`, le chantier peut franchir la frontière de préparation et poursuivre la chaîne opérationnelle prévue. `SiteReady` **ne signifie pas** : chantier construit ; chantier achevé ; infrastructure en service. |

### E — Préparation progressive

| # | Décision |
| --- | --- |
| **E1** | C-05 doit permettre qu’un SitePrep soit composé de **plusieurs étapes successives**. |
| **E2** | Une étape de préparation peut elle-même être composée de **sous-étapes**. Ceci doit rester compatible avec la hiérarchie générique définie par C-04. |
| **E3** | C-05 ne définit pas le contenu détaillé de ces étapes. Il définit : que la préparation peut être progressive ; que toutes les étapes requises doivent être satisfaites avant `SiteReady`. |
| **E4** | La fin d’une sous-étape ne signifie pas automatiquement `SiteReady`. Seule la satisfaction de l’ensemble des conditions nécessaires le permet. |
| **E5** | Le système doit pouvoir représenter une préparation partiellement réalisée. Les règles de calcul du pourcentage, des passes et du travail physique ne relèvent pas de C-05. |

### F — Relation avec C-04

| # | Décision |
| --- | --- |
| **F1** | C-05 **détermine le besoin de SitePrep et ses conditions**. C-04 est ensuite l’autorité du graphe des tâches. |
| **F2** | C-05 produit vers C-04 un **besoin / objectif de préparation**, pas un second graphe concurrent. |
| **F3** | C-04 peut transformer ce besoin en : tâche parent ; sous-tâches ; tâches terminales ; dépendances ; readiness ; progress ; blocages. C-05 n’en prend pas l’ownership. |
| **F4** | Lorsque `RequiresTerraform` est actif : **les tâches opérationnelles dépendantes du site restent bloquées tant que le SitePrep requis n’est pas terminé**. |
| **F5** | Lorsque `AlreadyReady` est actif : aucune tâche de préparation Terraform n’est nécessaire par ce contrat. |

### G — Cas A / Cas B

| # | Décision |
| --- | --- |
| **G1** | **Cas A = site déjà prêt.** Le système peut initialiser `SiteReady = true` sans exécuter de préparation Terraform. |
| **G2** | **Cas B = préparation requise.** Le système doit initialiser `SiteReady = false` et ouvrir le besoin de préparation. |
| **G3** | Le contrat C-05 doit pouvoir être validé indépendamment de la réactivation de Case B. Case B reste suspendu tant qu’il n’est pas explicitement rouvert. |
| **G4** | Quand la préparation est réellement validée : `RequiresTerraform` → SitePrep terminé → `SiteReady = true` → suite du chantier autorisée. |
| **G5** | C-05 ne doit pas imposer que l’étape finale soit toujours une tâche nommée `Terraform`. Le contrat exprime le résultat de SitePrep ; les futures préparations pourront éventuellement utiliser d’autres systèmes. |

### H — Relation avec C-08

| # | Décision |
| --- | --- |
| **H1** | **C-05** décide si le site doit être préparé et quand il est prêt. **C-08** décide comment le terrassement réalise cette préparation. |
| **H2** | C-08 peut définir une préparation détaillée (quadrillage, apports, aplanissement, contrôle, etc.). C-05 n’a pas besoin de connaître cette mécanique interne. |
| **H3** | C-08 fournit à C-05 le résultat métier nécessaire pour déterminer si les conditions de préparation sont satisfaites. |
| **H4** | C-05 ne définit pas : Creuser ; Remblayer ; Aplanir ; engin ; largeur de travail ; trajectoire ; tas de terre ; quantité de terre ; tolérance géométrique. |
| **H5** | Le terrassement réellement effectué doit pouvoir modifier le terrain progressivement via C-01, puis être vérifié avant la déclaration finale de `SiteReady`. |

### I — Relation avec C-01

| # | Décision |
| --- | --- |
| **I1** | C-05 ne possède jamais la hauteur. C-01 reste l’autorité du relief. |
| **I2** | C-05 peut **consommer une preuve de résultat terrain** provenant des systèmes métier concernés. |
| **I3** | C-05 ne transforme aucune information de hauteur en vérité parallèle. |
| **I4** | Une différence entre résultat attendu et relief réellement obtenu doit empêcher une validation erronée de `SiteReady`. |

### J — Relation avec C-02

| # | Décision |
| --- | --- |
| **J1** | C-02 reste la référence spatiale. |
| **J2** | C-02 peut signaler qu’une zone pertinente a changé. Il ne décide jamais à lui seul : « SitePrep invalide ». |
| **J3** | C-05 doit pouvoir réévaluer le SitePrep lorsqu’une modification affecte réellement les conditions de préparation. |
| **J4** | C-05 ne doit pas surveiller en permanence toute la carte. La réévaluation doit être ciblée sur la zone / les conditions concernées. |

### K — Invalidation et évolution du SiteReady

| # | Décision |
| --- | --- |
| **K1** | `SiteReady` est un **état courant**, pas un trophée définitif. |
| **K2** | Une modification réelle du monde peut rendre un site précédemment prêt à nouveau non conforme. |
| **K3** | Dans ce cas : `SiteReady` → invalidé → SitePrep à réévaluer. La suite du chantier peut alors être suspendue / réévaluée selon C-04 et DG-11.6. |
| **K4** | C-05 ne décide pas seul du statut global du chantier après invalidation. Il signale l’état SitePrep. DG-11.6 décide la conséquence au niveau chantier. |
| **K5** | Les causes d’invalidation doivent être observables (ex. terrain modifié ; zone de préparation modifiée ; condition de préparation devenue fausse). Les autres catégories de changement qui concernent directement une tâche restent du domaine de C-04. |

### L — Blocage / échec / reprise

| # | Décision |
| --- | --- |
| **L1** | Un SitePrep impossible à poursuivre doit exposer une **cause primaire**. |
| **L2** | Une préparation temporairement impossible peut rester récupérable. Elle ne devient pas automatiquement abandonnée. |
| **L3** | C-05 ne décide pas d’un abandon définitif. |
| **L4** | Lorsque les conditions redeviennent viables, C-05 doit pouvoir redevenir évaluable et permettre la reprise du SitePrep via C-04. |
| **L5** | Un échec technique ponctuel du système d’exécution ne doit pas être confondu avec : « le site est définitivement impossible à préparer ». |

### M — Observabilité

| # | Décision |
| --- | --- |
| **M1** | Le joueur et les systèmes concernés doivent pouvoir connaître au minimum : si une préparation est requise ; si elle est déjà satisfaite ; si elle est en cours ; si elle est bloquée ; pourquoi ; si le site est prêt. |
| **M2** | L’état détaillé des opérations internes reste lisible via C-04 et les systèmes métier. C-05 ne doit pas dupliquer tout le graphe de tâches. |
| **M3** | La différence suivante doit rester visible : SitePrep requis ≠ SitePrep terminé ≠ SiteReady ≠ Chantier Achevé ≠ Chantier En service. |

### N — Frontières / non-objectifs

| # | Décision |
| --- | --- |
| **N1** | C-05 ne possède pas : le graphe ; l’exécution unité ; l’autorité terrain ; le métier Terraform ; les règles détaillées de réservation ; l’économie ; l’écologie ; le statut En service. |
| **N2** | C-05 ne doit pas corriger maintenant les dettes de : `ExpandWorkSite` ; LevelPad vs WorkSite ; lexique C3/C4 ; `LinkedPitStockId` ; `TargetHeightOffsetCm`. |
| **N3** | C-05 peut conserver les champs existants utiles à son fonctionnement, mais le contrat privilégie les **garanties fonctionnelles** plutôt que de figer inutilement les noms internes. |

---

## 3. Vocabulaire

| Terme | Sens contractuel C-05 |
| --- | --- |
| **WorkSite** | Objectif / modèle de Project pour lequel C-05 est principalement défini (A2). |
| **SitePrep** | Besoin et état contractuel de préparation d’un site avant ouverture de la suite opérationnelle dépendante. |
| **Mode** | `None` · `AlreadyReady` · `RequiresTerraform` (B1, B2). |
| **Zone de préparation** | Emprise de base exprimée via WorkSite / `ZoneBounds` (C1). |
| **SiteReady** | État de **conformité du site** permettant l’ouverture de la suite du chantier (D1, D2, D6). |
| **Preuve de préparation** | Signal / résultat métier indiquant que les conditions de préparation sont satisfaites (D3, D4, H3). |
| **Cas A** | Site déjà prêt — `AlreadyReady` · `SiteReady = true` sans préparation Terraform (G1, F5). |
| **Cas B** | Préparation requise — `RequiresTerraform` · `SiteReady = false` + besoin de préparation (G2). **Suspendu** en produit (G3). |
| **Chaîne opérationnelle** | Suite du chantier dépendante du site (extract / transport / build, etc.) — hors détail C-05. |

Les noms de champs runtime (`bSiteReady`, `SitePrep.Mode`, etc.) peuvent être utilisés lorsqu’ils portent déjà ces garanties ; le contrat ne fige pas inutilement les noms internes (N3).

---

## 4. Responsabilités

| Domaine | Propriétaire |
| --- | --- |
| Nécessité du SitePrep | **C-05** (A1, F1) |
| État contractuel SitePrep / préconditions / postconditions | **C-05** (A1) |
| Condition de passage vers la suite du chantier | **C-05** via `SiteReady` (A1, D2, D6, F4) |
| Exécution physique / effets monde | **Hors C-05** — systèmes spécialisés (A4, N1) |
| Autorité du graphe de tâches | **C-04** (F1–F3) |
| Exécution des unités | **C-07** (N1) |
| Métier Terraform / jugement géométrique détaillé | **C-08** (H1–H4) |
| Vérité du relief | **C-01** (I1) |
| Référence spatiale / Dirty | **C-02** (J1, J2) |
| Conséquence chantier après invalidation | **DG-11.6** (K4) |
| Achevé / En service | **Hors C-05** (notamment C-13\* / C-14) (D6, M3, N1) |

---

## 5. Modes de SitePrep

Trois modes seulement (B1) :

| Mode | Signification (B2) | Effet structurel |
| --- | --- | --- |
| **None** | Aucun SitePrep requis pour ce Project | Pas d’obligation de préparation au titre de C-05 |
| **AlreadyReady** | Obligation conceptuelle satisfaite à l’entrée | Cas A — voir §10 |
| **RequiresTerraform** | Préparation requise avant suite opérationnelle | Cas B — voir §11 |

Règles associées :

- Choix du mode **avant** ouverture de la chaîne opérationnelle dépendante (B3).
- Détermination par **conditions chantier / site**, pas par indisponibilité unité / réservation / logistique seule (B4).

---

## 6. Zone de préparation

- Zone de base = WorkSite / `ZoneBounds` (C1).
- C-05 exprime : « cette partie du terrain doit être prête » (C1).
- Découpage interne (sous-zones, cellules, bandes, passes, secteurs) **non imposé** par C-05 → métier approprié, notamment C-08 (C2, C4).
- Subdivisions opérationnelles peuvent être plus fines que la grille C-02 ; elles ne forment **pas** une grille mondiale (C3).

---

## 7. SiteReady

### 7.1 Nature

`SiteReady` = **état de conformité du site** (D1).  
Ce n’est **pas** l’état d’une tâche.

### 7.2 Condition de vérité

`SiteReady = true` **uniquement** lorsque **toutes** les conditions nécessaires à l’ouverture de la suite du chantier sont satisfaites (D2).

### 7.3 Interdiction de réduction

```text
SiteReady  ≠  Terraform Task Completed
```

La fin d’une tâche Terraform peut **contribuer** à la validation, mais **ne suffit pas à elle seule** (D3).  
Il faut une **validation du résultat attendu** et une **preuve de préparation réussie** du système métier responsable (D3, D4).  
C-08 peut notamment fournir la preuve relative au terrassement (D4, H3).

### 7.4 Valeurs numériques

C-05 **ne fixe pas** hauteur exacte, tolérance, pente, largeur de passe, quantité de matériau, profil, etc. (D5).

### 7.5 Effet et non-effets

Une fois `SiteReady`, la frontière de préparation peut être franchie et la chaîne opérationnelle prévue peut se poursuivre (D6).

`SiteReady` **ne signifie pas** (D6, M3) :

- chantier construit ;
- chantier achevé ;
- infrastructure en service.

---

## 8. Préparation progressive

C-05 autorise explicitement une préparation composée d’étapes et sous-étapes (E1, E2) :

```text
Préparation
├── Étape 1
│   └── Sous-étapes…
├── Étape 2
├── …
└── Vérification / conditions finales
        ↓
    SiteReady (si toutes conditions satisfaites)
```

Règles :

- Compatible avec la **hiérarchie générique C-04** (E2, F3).
- Contenu détaillé des étapes **hors C-05** (E3) — notamment C-08 pour le terrassement (H2, H4).
- Fin d’une sous-étape ≠ `SiteReady` automatique (E4).
- Préparation partiellement réalisée représentable ; calculs % / passes / travail physique hors C-05 (E5).

C-05 **ne définit pas** : largeur véhicule / outil ; trajectoire ; nombre de passes ; hauteur cible ; tolérance ; quantité de terre ; méthodes de déversement / aplanissement ; Creuser ; Remblayer ; Aplanir (H4, D5, §18).

---

## 9. Relation avec C-04

```text
C-05
  → décide du besoin de SitePrep
  → définit ses conditions
  → détermine SiteReady
        ↓
C-04
  → possède l’autorité du graphe
  → orchestre les tâches
```

| Règle | Décision |
| --- | --- |
| C-05 détermine besoin + conditions ; C-04 = autorité graphe | F1 |
| C-05 produit un besoin / objectif de préparation, **pas** un second graphe | F2 |
| C-04 transforme le besoin (parent, sous-tâches, dépendances, readiness, progress, blocages) | F3 |
| `RequiresTerraform` : tâches ops dépendantes du site **bloquées** tant que SitePrep non terminé | F4 |
| `AlreadyReady` : aucune tâche de préparation Terraform nécessaire au titre de C-05 | F5 |

Le mélange actuel décision SitePrep + création de graphe dans `ExpandWorkSite` est une **dette** (N2, §20), non une règle nouvelle.

---

## 10. Cas A — site déjà prêt

| Élément | Règle |
| --- | --- |
| Mode | `AlreadyReady` (B2, G1) |
| Initialisation | `SiteReady = true` sans exécuter de préparation Terraform (G1) |
| Tâches prep Terraform | Aucune nécessaire au titre de C-05 (F5) |
| Preuve produit | Cas A déjà prouvé (T5 / T9) — hors formalisation nouvelle |

---

## 11. Cas B — préparation requise

| Élément | Règle |
| --- | --- |
| Mode | `RequiresTerraform` (B2, G2) |
| Initialisation | `SiteReady = false` + ouverture du besoin de préparation (G2) |
| Flux validé | `RequiresTerraform` → SitePrep terminé → `SiteReady = true` → suite autorisée (G4) |
| Étape finale | Non imposée comme tâche toujours nommée `Terraform` (G5) |
| Statut produit | **Suspendu** — le présent contrat **ne réactive pas** Case B (G3) |

Ce document décrit la règle contractuelle Case B. Il **n’autorise pas** l’implémentation ni la Demo Case B.

---

## 12. Relation avec C-08

```text
C-05
  → LE SITE DOIT-IL ÊTRE PRÉPARÉ ?
  → LE SITE EST-IL PRÊT ?
C-08
  → COMMENT LE TERRASSEMENT EST-IL RÉALISÉ ?
  → COMMENT LE RÉSULTAT EST-IL JUGÉ MÉTIER ?
```

| Règle | Décision |
| --- | --- |
| C-05 = si / quand prêt ; C-08 = comment terrasser | H1 |
| Mécanique interne détaillée (quadrillage, apports, passes, contrôle) = C-08 | H2 |
| C-08 fournit à C-05 le résultat métier pour les conditions | H3 |
| Creuser / Remblayer / Aplanir / engins / largeurs / trajectoires / quantités / tolérances = hors C-05 | H4 |
| Modification progressive via C-01 puis vérification avant `SiteReady` | H5 |

---

## 13. Relation avec C-01

```text
C-01 = vérité du relief
C-05 = condition de préparation du site
```

| Règle | Décision |
| --- | --- |
| C-05 ne possède jamais la hauteur | I1 |
| C-05 peut consommer une preuve de résultat terrain | I2 |
| Aucune vérité parallèle de hauteur dans C-05 | I3 |
| Écart résultat attendu ↔ relief réel → pas de `SiteReady` erroné | I4 |

---

## 14. Relation avec C-02

```text
C-02
  → référence spatiale / localisation du changement
C-05
  → détermine si ce changement affecte réellement le SitePrep
```

| Règle | Décision |
| --- | --- |
| C-02 = référence spatiale | J1 |
| Signal Dirty ≠ décision seule « SitePrep invalide » | J2 |
| C-05 peut réévaluer si les conditions de préparation sont affectées | J3 |
| Réévaluation ciblée — pas de surveillance permanente de toute la carte | J4 |

C-05 ne remplace pas C-02 et n’est pas propriétaire du Dirty spatial.

---

## 15. Invalidation / évolution du SiteReady

| Règle | Décision |
| --- | --- |
| `SiteReady` = état courant, pas trophée définitif | K1 |
| Modification réelle du monde peut rendre un site à nouveau non conforme | K2 |
| Flux : SiteReady → invalidé → SitePrep à réévaluer ; suite via C-04 / DG-11.6 | K3 |
| C-05 signale l’état SitePrep ; DG-11.6 décide la conséquence chantier | K4 |
| Causes d’invalidation observables ; invalidation tâche directe = C-04 | K5 |

Aucune logique concurrente de statut chantier n’est créée dans C-05.

---

## 16. Blocage / échec / reprise

| Règle | Décision |
| --- | --- |
| SitePrep impossible à poursuivre → **cause primaire** exposée | L1 |
| Impossible temporaire → récupérable ; pas d’abandon automatique | L2 |
| C-05 ne décide pas d’abandon définitif | L3 |
| Conditions à nouveau viables → C-05 réévaluable ; reprise via C-04 | L4 |
| Échec technique ponctuel d’exécution ≠ site définitivement impossible | L5 |

---

## 17. Observabilité

Minimum lisible (M1) :

- préparation requise ou non ;
- déjà satisfaite ;
- en cours ;
- bloquée + pourquoi (cause primaire) ;
- site prêt (`SiteReady`).

État détaillé des opérations → C-04 et systèmes métier ; C-05 ne duplique pas le graphe (M2).

Distinctions visibles (M3) :

```text
SitePrep requis
≠ SitePrep terminé
≠ SiteReady
≠ Chantier Achevé
≠ Chantier En service
```

---

## 18. Frontières et non-objectifs

C-05 **ne possède pas** (N1) :

- le graphe ;
- l’exécution unité ;
- l’autorité terrain ;
- le métier Terraform ;
- les règles détaillées de réservation ;
- l’économie ;
- l’écologie ;
- le statut En service.

C-05 **ne corrige pas maintenant** les dettes listées en §20 (N2).

C-05 privilégie les **garanties fonctionnelles** plutôt que de figer inutilement les noms internes (N3).

---

## 19. Dépendances

| Direction | Éléments |
| --- | --- |
| **Amont** | **C-01** · **C-04** (registre) |
| **Aval** | **C-08** · **C-13\*** · **C-14** · Demo Case B (lorsque autorisée) |
| **Complémentaire** | DG-11 · DG-11.6 · C-02 (spatial) · C-07 (exécution) · C-11 (selon nature des blocages) |

Architecture de séparation :

```text
C-05
├── Doit-on préparer ?
├── Quelle zone ?
├── Quelles conditions doivent être satisfaites ?
├── Le site est-il prêt ?
└── Peut-on ouvrir la suite du chantier ?
          │
          ▼
        C-04   graphe des tâches
          │
          ▼
        C-07   exécution des unités
          │
          ▼
        C-08   métier Terraform
          │
          ▼
        C-01   vérité du terrain
          │
          ▼
        C-05   preuve → SiteReady
```

Avec C-02 en support :

```text
C-02 « cette zone a changé »
  → C-05 « cela affecte-t-il réellement la préparation ? »
  → C-04 « quelles tâches doivent être réévaluées ? »
```

---

## 20. Dettes connues (hors contrat — non corrigées ici)

Constats d’implémentation / lexique ; **pas** de nouvelles règles C-05 (N2) :

| Dette | Nature |
| --- | --- |
| `ExpandWorkSite` | Mélange décision SitePrep + création de graphe + sémantique Raise/Lower |
| LevelPad / WorkSite | Deux expanders coexistants |
| Case B | Code / smoke présents mais **produit suspendu** |
| Ready runtime | Tendance actuelle : Ready ≈ Terraform Completed — **écart** avec D3 |
| Décomposition spatiale prep | Absente aujourd’hui (sous-zones / passes) |
| `LinkedPitStockId` | Risque sémantique Stock A vs Pit |
| `TargetHeightOffsetCm` | Champ présent sans contrat de cible / tolérance dans C-05 |
| Lexique cohorte C3 / C4 | ≠ IDs registre C-03 / C-04 / C-05 |

---

## 21. Points ouverts / hors périmètre

Aucun arbitrage nouveau. Restent **hors décisions C-05** :

- géométrie précise du résultat terrain ;
- tolérances, profils, seuils numériques ;
- mécanique détaillée des opérations Terraform (Creuser / Remblayer / Aplanir, passes, véhicules, trajectoires, matériaux) ;
- API exacte de preuve métier SiteReady ;
- table exhaustive des causes primaires SitePrep ;
- formalisation SitePrep pour d’autres objectifs Project que WorkSite (A2) ;
- réactivation produit de Case B (G3).

---

## 22. Couverture des 62 décisions

| Bloc | Décisions | Section(s) principales |
| --- | --- | --- |
| A | A1–A4 | §1, §2.A, §4 |
| B | B1–B4 | §2.B, §5 |
| C | C1–C4 | §2.C, §6 |
| D | D1–D6 | §2.D, §7 |
| E | E1–E5 | §2.E, §8 |
| F | F1–F5 | §2.F, §9 |
| G | G1–G5 | §2.G, §10, §11 |
| H | H1–H5 | §2.H, §12 |
| I | I1–I4 | §2.I, §13 |
| J | J1–J4 | §2.J, §14 |
| K | K1–K5 | §2.K, §15 |
| L | L1–L5 | §2.L, §16 |
| M | M1–M3 | §2.M, §17 |
| N | N1–N3 | §2.N, §18, §20 |

**Total : 62 / 62.**

Contrôle interne (rédaction) :

- D5 = C · D6 = B ;
- aucune décision nouvelle ;
- `SiteReady` ≠ Terraform Completed · ≠ Achevé · ≠ En service ;
- C-01 = relief · C-02 = spatial · C-04 = graphe · C-08 = métier Terraform ;
- Case B **suspendu** ;
- préparation progressive compatible C-04 ;
- aucune valeur numérique inventée.

---

## 23. Statut

| État | Valeur |
| --- | --- |
| Document | `CONTRATS/C-05_WORKSITE_SITEPREP.md` |
| Statut | **VALIDÉ** |
| Règle officielle | **Oui** — validation humaine ; audit 62/62 PASS |
| Décisions | **62 / 62** (A1–N3) · D5=C · D6=B |
| Compteur global | **4 / 16** (C-03 hors dénominateur) |
| Case B | **Suspendu** |

---

*Fin C-05 — VALIDÉ. C-03 demeure addendum fermé. Case B demeure suspendu. Aucune implémentation ni C-07 démarrés par cette clôture.*
