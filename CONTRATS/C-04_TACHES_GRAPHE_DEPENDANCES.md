# C-04 — Tâches / graphe / dépendances

| Champ | Valeur |
| --- | --- |
| **ID** | C-04 |
| **Nom** | Tâches / graphe / dépendances |
| **Statut documentaire** | **VALIDÉ** — validation humaine explicite ; audit 48/48 PASS ; dettes d’implémentation conservées (§18) |
| **Profondeur** | Détaillée (registre) |
| **Ordre de rédaction** | 4 |
| **Bloquant** | Oui (avant chantiers procéduraux riches / invalidation monde / Cas B robuste) |
| **Dépendances amont** | **C-03** (Project existant — addendum fermé ; périmètre S3 suffisant) · **C-01** / **C-02** (frontières terrain / spatial) |
| **Références** | Registre C-04 · DG-11 · DG-11.6 · ODC-F4 · TaskTypes / TaskSubsystem · décisions humaines A1–K6 (48) |

Ce document formalise les **48 décisions humaines C-04** reprises **sans modification de sens**.  
Il n’invente aucune règle supplémentaire.  
Il constitue la **règle opérationnelle** C-04 après validation humaine et inscription **VALIDÉ** dans le suivi.

**C-03** reste un addendum fermé : C-04 part d’un Project existant et ne crée aucune nouvelle règle Intention→Project.

---

## 1. Objet / rôle

C-04 est l’**autorité du graphe opérationnel des tâches** et de leur **cycle de vie**.

Il garantit :

- la cohérence du graphe ;
- la hiérarchie et la décomposition des tâches ;
- la readiness ;
- les dépendances ;
- le claim ;
- la progression ;
- les réservations au niveau du **mécanisme** de tâche ;
- les blocages / échecs ;
- la réévaluation après changement du monde.

C-04 **n’est pas** :

- l’exécuteur physique des unités ;
- l’autorité terrain ;
- le propriétaire du SitePrep ;
- le propriétaire des règles métier Terraform ;
- le propriétaire de l’économie concurrentielle détaillée ;
- le propriétaire de l’écologie.

---

## 2. Décisions validées (source de vérité)

Les **48** décisions suivantes sont reprises **sans modification** :

### A — Périmètre

| # | Décision |
| --- | --- |
| **A1** | Graphe + cycle de vie + hiérarchie/décomposition + readiness + claim + progress + blocage + invalidation. C-04 est l’autorité runtime de la tâche, pas seulement son conteneur de données. |
| **A2** | Aucune dépendance au type concret d’unité. C-04 raisonne en capacités/exigences abstraites. La sélection et l’exécution concrètes relèvent de C-07. |
| **A3** | C-04 n’applique jamais lui-même les effets matériels. Il orchestre l’état de la tâche et peut exiger une preuve de complétion fournie par le système exécutant ou métier. |

### B — Cycle de vie

| # | Décision |
| --- | --- |
| **B1** | États contractuels : **Pending → Ready → Reserved → Running → Completed / Failed / Blocked / Cancelled**. Aucun nouvel état fondateur n’est ajouté maintenant. |
| **B2** | Les transitions sont **contractuelles et contraintes**. Une tâche ne peut pas passer arbitrairement d’un état à n’importe quel autre. |
| **B3** | `Completed` signifie : **les conditions de complétion contractuelles de la tâche sont satisfaites**. `Progress = 100 %` n’est pas à lui seul une preuve suffisante. |
| **B4** | **Blocked** = impossibilité ou absence de condition permettant actuellement de poursuivre, mais situation potentiellement récupérable. **Failed** = échec d’exécution ou impossibilité terminale de la tentative actuelle, nécessitant une décision explicite, une nouvelle tâche ou une recréation pour repartir. Donc : `Blocked` n’est pas terminal ; `Failed` n’est pas automatiquement réessayé. |
| **B5** | Une tâche peut être annulée par : le joueur ; ou un système explicitement autorisé par le contrat propriétaire du chantier/projet. C-04 fournit le mécanisme d’annulation mais ne décide pas seul qui possède cette autorité métier. |

### C — Prérequis / readiness / graphe

| # | Décision |
| --- | --- |
| **C1** | `Ready` signifie que : **les prérequis de la tâche sont satisfaits et que la tâche peut être proposée à l’exécution**. `Ready` ne signifie pas qu’une unité est déjà affectée. |
| **C2** | La readiness est une responsabilité de **C-04 / TaskSubsystem**. |
| **C3** | C-04 garantit un **ordre topologique cohérent** lorsque les dépendances le permettent. Le graphe n’est pas obligé d’être linéaire. |
| **C4** | Une dépendance cyclique structurellement invalide doit : être détectée ; empêcher une interprétation silencieuse du graphe ; être rendue observable comme erreur structurelle. C-04 ne casse pas automatiquement le cycle en supprimant une dépendance. |
| **C5** | Les tâches indépendantes peuvent être exécutées en parallèle lorsqu’aucune dépendance ou réservation ne l’interdit. Le parallélisme est donc une propriété possible du graphe, pas une obligation d’exécution. |

### D — Progress / effets / complétion

| # | Décision |
| --- | --- |
| **D1** | `Progress` représente **l’avancement abstrait de l’exécution de la tâche**. Il ne représente pas automatiquement : une quantité de matière ; une distance ; un temps ; un effet terrain. |
| **D2** | Les effets matériels sont produits par le système exécutant/métier concerné. C-04 peut demander qu’un effet attendu soit vérifié avant de considérer la tâche comme terminée. **C-04 ne produit pas lui-même l’effet.** |
| **D3** | L’agent d’exécution ou le système autorisé appelle `CompleteTask` **après satisfaction des conditions contractuelles de complétion**. Le simple `Progress = 1` ne déclenche pas automatiquement `Completed`. |
| **D4** | Si `Progress = 100 %` mais qu’un effet requis n’est pas confirmé : **la tâche ne peut pas être considérée comme correctement `Completed`.** Elle doit être réévaluée puis : rester dans son état d’exécution ; devenir `Blocked` ; ou devenir `Failed` ; selon la cause réelle. Aucun effet manquant n’est artificiellement appliqué par C-04. |
| **D5** | Une tâche peut être exécutée en **plusieurs pulses/phases**, avec interruption et reprise. C-04 garantit que l’état de progression peut survivre à ces phases. La mécanique physique détaillée de reprise appartient à C-07 et aux contrats métier concernés. |

### E — Claim / assignation

| # | Décision |
| --- | --- |
| **E1** | Un `claim` signifie qu’une unité devient **responsable de la tâche pour son exécution courante**. Le claim ne signifie pas automatiquement que la tâche est déjà `Running`. |
| **E2** | La compatibilité repose sur les **capacités requises par la tâche** et les capacités disponibles de l’unité. La priorité, distance, opportunité, etc. peuvent ensuite intervenir dans le choix entre plusieurs tâches compatibles. |
| **E3** | Une unité qui ne possède pas les capacités requises **ne peut pas claim la tâche**. |
| **E4** | Une tâche claimée/réservée ne peut pas être simultanément claimée par une autre unité, sauf mécanisme contractuel explicitement prévu. |

### F — Blocage / échec / observabilité

| # | Décision |
| --- | --- |
| **F1** | Toute tâche `Blocked` doit exposer une **cause primaire**. |
| **F2** | Une cause primaire est obligatoire. Des informations secondaires peuvent exister, mais elles ne remplacent jamais la cause primaire. |
| **F3** | Lorsqu’un blocage disparaît : **C-04 doit pouvoir réévaluer la tâche et la remettre `Ready` lorsque ses conditions sont à nouveau satisfaites.** Une tâche ne passe pas directement de `Blocked` à `Running` sans repasser par une condition de readiness valide. |
| **F4** | `Failed` reste `Failed` tant qu’aucune décision explicite de reprise, recréation ou remplacement n’est intervenue. Aucune réactivation automatique. |

### G — Invalidation du monde

| # | Décision |
| --- | --- |
| **G1** | Lorsqu’un changement du monde peut rendre une tâche invalide ou non viable : **C-04 doit permettre sa réévaluation.** L’invalidation ne signifie pas automatiquement annulation de toute la tâche ou de tout le chantier. |
| **G2** | Les catégories d’événements pertinentes sont : Ressource ; Transport ; Unité ; Terrain ; Technologie ; Priorité ; mais uniquement **lorsqu’elles modifient réellement la viabilité, les prérequis, l’ordre ou la solution de la tâche**. Cette décision reste cohérente avec DG-11.6. |
| **G3** | La portée de la réévaluation est : **locale par défaut**, puis élargie si l’invalidation touche un élément essentiel, une dépendance structurante ou un hard gate. Pas de recalcul global systématique. |
| **G4** | **C-02 localise et signale la modification. C-04 décide de sa conséquence sur le graphe des tâches.** C-02 ne décide jamais qu’une tâche est invalide. |
| **G5** | C-04 porte le **mécanisme générique d’invalidation/réévaluation des tâches**. DG-11.6 porte le comportement **au niveau du chantier** : recalcul local ; recalcul élargi ; suspension ; blocage ; cause primaire ; reprise éventuelle. Les deux contrats sont complémentaires et non concurrents. |

### H — Expand / Project / C-05

| # | Décision |
| --- | --- |
| **H1** | Le système Project peut **construire le graphe** à partir du Project, conformément aux règles de C-04. Mais : **TaskSubsystem reste l’autorité runtime du graphe et de son cycle de vie.** |
| **H2** | C-04 définit le **principe contractuel de transformation Project → graphe de tâches** : tâches produites ; dépendances ; prérequis ; données nécessaires ; cohérence du graphe. Il ne devient pas propriétaire de l’Intention→Project. |
| **H3** | **C-05 décide si et quand un chantier nécessite un SitePrep.** C-04 reçoit et orchestre les tâches résultantes. C-04 ne décide pas qu’un terrain doit être préparé. |
| **H4** | Le mélange actuel dans `ExpandWorkSite` est une **dette de séparation**, pas une raison de lancer un refactor dans C-04. |

### I — Réservations

| # | Décision |
| --- | --- |
| **I1** | C-04 définit le **principe contractuel de réservation lié à une tâche** : une tâche peut devoir obtenir une réservation nécessaire avant d’atteindre l’état permettant son exécution. |
| **I2** | C-04 définit le mécanisme et les garanties minimales. **C-11 définit les règles détaillées de concurrence, arbitrage, partage, priorité, économie et conflits de réservation.** |
| **I3** | Lorsqu’une réservation nécessaire n’est pas disponible : la tâche ne peut pas entrer dans l’état d’exécution qui nécessite cette réservation ; la cause doit être observable ; si elle était déjà engagée et perd sa ressource nécessaire, elle doit être réévaluée et peut devenir `Blocked`. Aucun `Failed` automatique. |

### J — Frontières C-07 / C-08 / C-03

| # | Décision |
| --- | --- |
| **J1** | C-07 est responsable de : rechercher une tâche compatible ; la claim ; l’exécuter ; produire les actions/effets relevant de son domaine ; fournir les éléments permettant la validation de complétion. C-07 ne définit pas le graphe. |
| **J2** | Pour `Terraform` : **C-04 définit la tâche générique et son orchestration. C-08 définit les règles métier Terraform.** Cela comprend notamment, au stade approprié : Creuser ; Remblayer ; Aplanir ; cibles ; profils ; tolérances ; critères de complétion ; gestion des matériaux déplacés ; interaction unité/chantier. Ces paramètres ne doivent **pas** être inventés dans C-04. |
| **J3** | C-03 reste fermé. C-04 part d’un **Project existant** et ne crée pas de nouvelles règles Intention→Project. |
| **J4** | `Ecology` reste une capacité structurelle du système de tâches, sans recevoir maintenant sa sémantique métier complète. Les règles écologiques appartiendront aux contrats concernés. |

### K — Hiérarchie / décomposition / sous-tâches

| # | Décision |
| --- | --- |
| **K1** | C-04 doit supporter contractuellement des **tâches composées** pouvant contenir des sous-tâches. Cette hiérarchie est une capacité du graphe, pas une nouvelle spécialisation métier de C-04. |
| **K2** | Une tâche composée sert à **orchestrer ses sous-tâches**. Les unités ne claiment et n’exécutent normalement que les **tâches exécutables terminales**. Une tâche parent ne doit pas devenir une seconde tâche physique concurrente de ses enfants. |
| **K3** | Une tâche composée ne peut être `Completed` que lorsque : toutes ses sous-tâches obligatoires sont elles-mêmes correctement terminées ; les conditions globales de complétion de la tâche parent sont satisfaites. La progression du parent est une **vue agrégée de l’avancement de ses enfants**, et non une preuve indépendante de résultat. Aucune formule de pondération universelle n’est imposée maintenant. |
| **K4** | C-04 fournit le **mécanisme générique de décomposition**. Le contrat métier concerné définit ce que signifient les sous-tâches : **C-05** pour la préparation de SitePrep ; **C-08** pour la décomposition des opérations Terraform ; les contrats métier futurs pour leurs propres domaines. C-04 ne décide donc pas lui-même qu’un terrassement doit utiliser telle quantité de sous-zones, telle largeur d’engin ou telle méthode d’épandage. |
| **K5** | Une tâche composée peut être **décomposée ou affinée lorsque le contexte réel devient suffisamment connu**, notamment pour tenir compte : de la zone réellement concernée ; des ressources disponibles ; des unités ; des contraintes du monde ; de la solution opérationnelle retenue. Les sous-tâches créées rejoignent alors le graphe C-04 normal et suivent les mêmes règles de dépendances, readiness, claim, progress, blocage et invalidation. |
| **K6** | C-04 doit pouvoir représenter des sous-tâches portant sur des **zones ou portions de travail distinctes** : zone ; sous-zone ; bande/passe ; portion de chantier ; autre découpage spatial fourni par le contrat métier. Cette subdivision opérationnelle : **n’est pas la grille C-02** et **ne définit jamais la résolution de déformation C-01**. Le contrat métier concerné choisit la géométrie et la granularité nécessaires à l’opération. |

---

## 3. Vocabulaire minimal

| Terme | Sens dans C-04 |
| --- | --- |
| **Tâche** | Unité du graphe opérationnel portant un type, un statut, des dépendances, éventuellement une zone, des capacités requises, une progression et des conditions de complétion. |
| **Tâche composée (parent)** | Tâche qui orchestre des sous-tâches ; non exécutée physiquement par une unité comme concurrente de ses enfants (K2). |
| **Tâche exécutable (terminale)** | Tâche que les unités peuvent claim et exécuter (K2). |
| **Graphe** | Ensemble de tâches liées par dépendances et/ou hiérarchie, sous autorité runtime de C-04 / TaskSubsystem (A1, H1). |
| **Readiness** | Détermination que les prérequis sont satisfaits et que la tâche peut être proposée à l’exécution (C1, C2). |
| **Claim** | Responsabilité courante d’une unité sur une tâche ; n’implique pas automatiquement `Running` (E1). |
| **Progress** | Avancement abstrait d’exécution ; ≠ matière, distance, temps, effet terrain (D1). |
| **Complétion** | Satisfaction des conditions contractuelles de la tâche ; distincte de Progress = 100 % (B3, D3, D4). |
| **Blocked** | Situation potentiellement récupérable avec cause primaire (B4, F1). |
| **Failed** | Tentative terminale ; pas de réessai automatique (B4, F4). |
| **Invalidation / réévaluation** | Remise en cause de la viabilité d’une tâche après changement du monde ; portée locale par défaut (G1–G3). |

---

## 4. Responsabilités

### 4.1 Ce que C-04 garantit

1. **Autorité runtime du graphe (A1, H1)**  
   TaskSubsystem (ou équivalent) est l’autorité du cycle de vie des tâches une fois créées.

2. **États et transitions (B1, B2)**  
   Les états listés en B1 ; transitions contraintes.

3. **Readiness et topologie (C1–C4)**  
   Calcul de readiness ; ordre topologique cohérent lorsque possible ; cycles structurels détectés et observables, sans réparation silencieuse.

4. **Claim / capacités abstraites (A2, E1–E4)**  
   Compatibilité par capacités ; exclusion de claim concurrent sauf mécanisme contractuel prévu.

5. **Progress et non-application d’effets (A3, D1–D4)**  
   Progress abstrait ; effets hors C-04 ; CompleteTask après conditions ; Progress 100 % insuffisant seul.

6. **Multi-pulse / survie de Progress (D5)**  
   L’état de progression peut survivre aux interruptions/reprises ; mécanique physique détaillée hors C-04.

7. **Blocage / échec / cause primaire (B4, F1–F4)**  
   Cause primaire obligatoire si Blocked ; sortie de Blocked via réévaluation → Ready ; Failed non auto-réactivé.

8. **Mécanisme d’annulation (B5)**  
   Mécanisme fourni ; autorité métier d’annulation hors C-04 seul.

9. **Invalidation / réévaluation des tâches (G1–G5)**  
   Réévaluation possible ; locale par défaut ; C-04 décide la conséquence sur le graphe après signal C-02 (ou autre source pertinente) ; complémentaire à DG-11.6 (chantier).

10. **Principe Project → graphe (H2)**  
    Ce que signifie transformer un Project en graphe cohérent ; sans posséder Intention→Project.

11. **Réservation liée à la tâche — principe (I1–I3)**  
    Mécanisme et garanties minimales ; détail concurrentiel → C-11.

12. **Hiérarchie et décomposition (K1–K6)**  
    Tâches composées / terminales ; complétion parent agrégée ; décomposition dynamique ; sous-tâches spatiales ≠ grille C-02 ≠ résolution C-01.

### 4.2 Ce que C-04 ne garantit pas / ne fait pas

- Appliquer des effets matériels (A3, D2).
- Définir le métier Terraform (J2) ni les paramètres d’outil/bande/tolérance/quantité (K4, K6).
- Décider le SitePrep (H3).
- Définir Intention→Project (J3).
- Règles concurrentielles détaillées de réservation (I2).
- Exécution physique unité (J1 / C-07).
- Autorité hauteur (C-01).
- C-04 ne réalise pas la localisation ni la déclaration Dirty du changement spatial, qui relèvent de C-02 ; C-04 détermine en revanche la conséquence de ce changement sur le graphe des tâches conformément à G4.
- Sémantique Ecology complète (J4).
- Formule de pondération universelle du Progress parent (K3).
- Parallélisme obligatoire d’exécution (C5).

---

## 5. Hiérarchie des tâches

### 5.1 Capacité contractuelle

C-04 doit supporter :

```text
Tâche composée
├── Sous-tâche
├── Sous-tâche
└── Sous-tâches exécutables (terminales)
```

Exemple conceptuel (non normatif métier) :

```text
Mise à niveau
├── Cadrage
├── Quadrillage
├── Apport de terre
│   ├── Zone 1
│   ├── Zone 2
│   └── …
└── Aplanissement
    ├── Passe 1
    └── …
```

### 5.2 Parent vs terminales

- Parent = orchestration (K2).
- Unités : claim / exécution **normalement** des terminales seulement (K2).
- Parent ≠ seconde tâche physique concurrente de ses enfants (K2).

### 5.3 Complétion et Progress parent

- Parent `Completed` seulement si sous-tâches obligatoires correctement terminées **et** conditions globales parent satisfaites (K3).
- Progress parent = vue agrégée des enfants, **pas** preuve indépendante de résultat (K3).
- Pas de formule de pondération universelle imposée (K3).

### 5.4 Propriété de la décomposition

| Domaine | Qui définit le sens des sous-tâches |
| --- | --- |
| Mécanisme générique | **C-04** (K4) |
| SitePrep | **C-05** (K4, H3) |
| Terraform opérationnel | **C-08** (K4, J2) |
| Autres domaines | Contrats métier futurs (K4) |

### 5.5 Décomposition dynamique

Affinage possible quand le contexte réel est suffisamment connu (zone, ressources, unités, contraintes, solution) ; les nouvelles sous-tâches rejoignent le graphe normal (K5).

### 5.6 Sous-tâches spatiales

Portions distinctes (zone, sous-zone, bande/passe, portion de chantier, autre découpage métier) (K6) :

- **≠** grille C-02 ;
- **≠** résolution de déformation C-01 ;
- géométrie / granularité choisies par le contrat métier.

---

## 6. Cycle de vie et transitions

### 6.1 États (B1)

```text
Pending → Ready → Reserved → Running → Completed
                                      → Failed
                                      → Blocked
                                      → Cancelled
```

Aucun nouvel état fondateur dans ce contrat.

### 6.2 Transitions (B2)

Toute transition doit respecter les contraintes du cycle. Pas de passage arbitraire.

### 6.3 Completed (B3)

Conditions contractuelles de complétion satisfaites.  
**Progress = 100 % n’est pas une preuve suffisante.**

### 6.4 Blocked vs Failed (B4)

| | Blocked | Failed |
| --- | --- | --- |
| Nature | Potentiellement récupérable | Tentative terminale |
| Suite | Réévaluation possible → Ready (F3) | Décision explicite / nouvelle tâche / recréation (F4) |
| Auto-retry | Non applicable comme Failed | **Interdit** |

### 6.5 Annulation (B5)

Mécanisme C-04 ; autorité métier : joueur ou système autorisé par le contrat propriétaire du chantier/projet.

---

## 7. Readiness, dépendances, topologie, parallélisme

| Règle | Décision |
| --- | --- |
| Ready = prérequis OK + proposable ; pas d’unité déjà affectée | C1 |
| Responsabilité readiness = C-04 / TaskSubsystem | C2 |
| Ordre topologique cohérent si dépendances le permettent ; graphe non forcément linéaire | C3 |
| Cycle structurel : détecté, non silencieux, observable ; pas de casse auto de dépendance | C4 |
| Parallélisme possible si aucune dépendance/réservation ne l’interdit ; pas d’obligation | C5 |

---

## 8. Progression, effets, complétion, reprise

### 8.1 Distinction centrale

```text
Progression
≠
effet matériel
≠
preuve de complétion
```

### 8.2 Règles

| Règle | Décision |
| --- | --- |
| Progress = avancement abstrait | D1 |
| Effets produits hors C-04 ; C-04 peut exiger vérification avant Completed | D2, A3 |
| CompleteTask après conditions ; Progress = 1 ≠ Completed auto | D3 |
| Progress 100 % sans effet requis → pas Completed ; réévaluation → Running / Blocked / Failed ; pas d’effet artificiel par C-04 | D4 |
| Multi-pulse + survie du Progress ; reprise physique détaillée → C-07 / métier | D5 |

---

## 9. Claim et capacités

| Règle | Décision |
| --- | --- |
| Claim = responsabilité courante ; ≠ Running automatique | E1 |
| Compatibilité = capacités requises vs disponibles ; priorité/distance/opportunité ensuite | E2 |
| Sans capacités requises → claim interdit | E3 |
| Pas de claim concurrent sauf mécanisme contractuel prévu | E4 |
| Pas de dépendance au type concret d’unité | A2 |

---

## 10. Blocage, échec, observabilité

| Règle | Décision |
| --- | --- |
| Blocked → cause primaire obligatoire | F1, F2 |
| Secondaires possibles, jamais substitut de la cause primaire | F2 |
| Fin de blocage → réévaluation → Ready si conditions OK ; pas Blocked→Running direct | F3 |
| Failed stable jusqu’à décision explicite | F4 |

L’observabilité détaillée produit (UX) relève notamment de C-20 / DG-13 ; C-04 impose la **cause primaire** pour Blocked.

---

## 11. Invalidation et réévaluation

### 11.1 Séparation des responsabilités

```text
C-02
  → localise / signale le changement spatial

C-04
  → détermine la conséquence sur le graphe des tâches

DG-11.6
  → traite la réaction au niveau du chantier
    (recalcul local / élargi, suspension, blocage, cause primaire, reprise)
```

C-02 ne décide jamais qu’une tâche est invalide (G4).  
C-04 et DG-11.6 sont complémentaires, non concurrents (G5).

### 11.2 Règles

| Règle | Décision |
| --- | --- |
| Changement pouvant invalider → C-04 permet la réévaluation ; ≠ annulation auto tâche/chantier | G1 |
| Catégories pertinentes si impact réel : Ressource, Transport, Unité, Terrain, Technologie, Priorité | G2 |
| Portée locale par défaut ; élargie si essentiel / dépendance structurante / hard gate ; pas de global systématique | G3 |

---

## 12. Project → graphe et SitePrep

| Règle | Décision |
| --- | --- |
| Project peut construire le graphe ; TaskSubsystem = autorité runtime | H1 |
| C-04 = principe Project → graphe (tâches, deps, prereqs, données, cohérence) ; pas Intention→Project | H2, J3 |
| C-05 décide SitePrep ; C-04 orchestre les tâches résultantes | H3 |
| Mélange `ExpandWorkSite` = dette de séparation ; pas de refactor imposé par C-04 | H4 |

---

## 13. Réservations

| Règle | Décision |
| --- | --- |
| Principe : réservation liée à la tâche avant état d’exécution nécessitant cette réservation | I1 |
| Mécanisme + garanties minimales C-04 ; concurrence détaillée → C-11 | I2 |
| Indisponible → pas d’entrée dans l’état d’exécution requis ; cause observable ; perte en cours → réévaluation, peut Blocked ; pas Failed automatique | I3 |

---

## 14. Exécution (C-07) et Terraform (C-08)

### 14.1 C-07

Recherche compatible · claim · exécution · effets de son domaine · éléments de validation de complétion.  
**Ne définit pas le graphe** (J1).

### 14.2 Type Terraform

Le type de tâche `Terraform` est accepté dans le système de types.

C-04 = tâche générique + orchestration.  
**C-08** = métier (Creuser, Remblayer, Aplanir, cibles, profils, tolérances, critères, matériaux, interaction unité/chantier, largeur d’outil/véhicule, méthodes) — **non inventés dans C-04** (J2, K4, K6).

### 14.3 Ecology

Type/capacité structurelle sans sémantique métier complète maintenant (J4).

---

## 15. Frontières contractuelles

| Contrat / élément | Frontière |
| --- | --- |
| **C-01** | Autorité hauteur / relief. C-04 ne l’écrit pas. Les effets terrain viennent des systèmes exécutant/métier via C-01. |
| **C-02** | Localise/signale Dirty spatial. Ne décide pas l’invalidité d’une tâche (G4). Sous-tâches spatiales C-04 ≠ grille C-02 (K6). |
| **C-03** | Fermé. C-04 part d’un Project existant (J3). |
| **C-05** | SitePrep : si/quand préparer. C-04 orchestre les tâches résultantes (H3). Décomposition prep métier → C-05 (K4). |
| **C-07** | Exécution unité. Ne définit pas le graphe (J1, A2). |
| **C-08** | Métier Terraform et décomposition opérationnelle (J2, K4). |
| **C-11** | Concurrence / arbitrage réservations détaillés (I2). |
| **DG-11.6** | Réaction au **niveau chantier** ; C-04 = mécanisme **tâche** (G5). |

---

## 16. Non-objectifs

C-04 ne fixe pas :

- largeur de véhicule, nombre de cases, largeur de bande, trajectoire ;
- quantité de terre, tolérance, méthode de terrassement ;
- sémantique Ecology complète ;
- règles Intention→Project ;
- UX produit complète (C-20) ;
- correction des dettes d’implémentation listées ci-dessous.

---

## 17. Dépendances

| Direction | Éléments |
| --- | --- |
| **Amont** | Project existant (C-03 fermé / S3) ; frontières C-01, C-02 |
| **Aval** | C-05 · C-07 · C-08 · C-11 · C-12 · C-20 (registre) |
| **Complémentaire** | DG-11 / DG-11.6 |

---

## 18. Dettes connues (hors contrat — non corrigées ici)

Ces écarts runtime/documentaires sont **conservés comme dettes** ; ils ne deviennent pas de nouvelles règles C-04 :

| Dette | Nature |
| --- | --- |
| Progress / effets | Runtime tend à lier Progress≈Complete / effets tardifs — écart à combler **après** VALIDÉ, sans inventer ici |
| Invalidation monde | Mécanisme G* peu ou pas câblé (Dirty C-02 → tâches) |
| Multi-pulse / reprise | D5 contractuel ; mécanique physique encore côté C-07 / métier |
| `ExpandWorkSite` | Mélange SitePrep + ops (H4) |
| LevelPad / WorkSite | Deux planners coexistants |
| Pool ressources legacy | Stub TaskSubsystem + PE |
| Ecology | Type présent, sémantique absente (J4) |
| Lexique cohorte C3/C4 | ≠ IDs registre C-03/C-04 |

---

## 19. Points ouverts / hors périmètre

Aucun arbitrage nouveau n’est introduit. Les sujets suivants restent **hors décisions actuelles** (à traiter ailleurs si besoin) :

- formule exacte d’agrégation du Progress parent (explicitement non imposée — K3) ;
- table exhaustive des transitions état→état (principe B2 seulement) ;
- liste fermée des causes primaires de BlockCause ;
- API exacte d’invalidation / abonnement aux signaux C-02 ;
- sémantique métier Ecology, Terraform détaillée, SitePrep détaillée.

---

## 20. Couverture des 48 décisions

| Bloc | Décisions | Section(s) principales |
| --- | --- | --- |
| A | A1–A3 | §1, §2.A, §4 |
| B | B1–B5 | §2.B, §6 |
| C | C1–C5 | §2.C, §7 |
| D | D1–D5 | §2.D, §8 |
| E | E1–E4 | §2.E, §9 |
| F | F1–F4 | §2.F, §10 |
| G | G1–G5 | §2.G, §11 |
| H | H1–H4 | §2.H, §12 |
| I | I1–I3 | §2.I, §13 |
| J | J1–J4 | §2.J, §14, §15 |
| K | K1–K6 | §2.K, §5 |

**Total : 48 / 48.**

---

## 21. Statut

| État | Valeur |
| --- | --- |
| Document | `CONTRATS/C-04_TACHES_GRAPHE_DEPENDANCES.md` |
| Statut | **VALIDÉ** |
| Règle officielle | **Oui** — validation humaine ; audit 48/48 PASS |
| Décisions | **48 / 48** (A1–K6) |
| Compteur global | **3 / 16** (C-03 hors dénominateur) |

---

*Fin C-04 — VALIDÉ. C-03 demeure addendum fermé. Aucune implémentation ni C-05 démarrés par cette clôture.*
