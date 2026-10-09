# C-14 — Infrastructures (lifecycle)

| Champ | Valeur |
| --- | --- |
| **ID** | C-14 |
| **Nom** | Infrastructures (lifecycle) |
| **Statut documentaire** | **VALIDÉ** — validation humaine explicite ; audit indépendant final 15/15 PASS ; points ouverts §18 et dettes d’implémentation / preuve F9 conservés |
| **Profondeur** | Fondamentale (registre) |
| **Ordre de rédaction** | 14 |
| **Bloquant** | Oui (avant ODC-F9 — registre) |
| **Dépendances amont** | **C-02** · **C-05** · **C-12** (VALIDÉS documentairement) |
| **Références** | Registre C-14 · DG-10 (10.1–10.5) · DG-02 · DG-06 / 00.5.N4 · C-01 · C-04 · C-07 · C-08 · C-11 · C-13\* · décisions humaines A1–F1 (15) |

Ce document formalise les **15 décisions humaines C-14** reprises **sans modification de sens**.  
Il n’invente aucune règle supplémentaire.  
Il constitue la **règle opérationnelle** C-14 après validation humaine et inscription **VALIDÉ** dans le suivi.  
Il ne constitue **pas** une autorisation d’implémentation complète du lifecycle, d’ouverture de C-10/C-13\*, une preuve ODC-F9, ni une réactivation de Case B.

**Case B** demeure **suspendu** jusqu’à décision humaine explicite de réouverture.  
**C-10\*** et **C-13\*** demeurent addenda **fermés**.  
**C-12** demeure **VALIDÉ** ; ses décisions A1–G3 restent **inchangées**.

Référentiel des lettres validées (identité) :

```text
A1 A2 A3
B1 B2 B3
C1 C2 C3
D1 D2 D3
E1 E2
F1
```

Le **sens opératoire** de chaque décision est celui de §2 ci-dessous (référentiel d’autorité).

---

## 1. Identité et finalité

C-14 est le contrat des **règles métier du cycle de vie des infrastructures** : de la demande ou planification jusqu’à la fin d’utilisation, en passant par la construction, la mise en service, le démontage, la récupération et la restauration éventuelle du site (A1, A3).

Il s’appuie sur la conception **DG-10** (VALIDÉE) sans la remplacer, et s’intègre aux graphes **C-04**, à l’exécution **C-07**, à la préparation **C-05**, aux services spatiaux **C-02**, aux réservations **C-11** et à l’utilisation logistique **C-12**, sans absorber leurs responsabilités (B2, B3, C1–C3).

La première implémentation **peut** ne couvrir qu’un sous-ensemble limité, explicite et vérifiable. Les fonctionnalités non implémentées **ne doivent pas** être présentées comme opérationnelles (A1).

---

## 2. Décisions validées (source de vérité)

Les **15** décisions suivantes sont reprises **fidèlement**.

### A — Périmètre et cycle de vie

| # | Décision |
| --- | --- |
| **A1** | C-14 définit le cycle de vie global d’une infrastructure, de sa construction à sa fin d’utilisation, en incluant le démontage, la récupération et la restauration éventuelle du site. La première implémentation peut ne couvrir qu’un sous-ensemble limité, explicite et vérifiable. Les fonctionnalités non implémentées ne doivent pas être présentées comme opérationnelles. |
| **A2** | C-14 couvre les infrastructures temporaires et permanentes dans un modèle de cycle de vie cohérent, avec des règles spécifiques lorsque leur durée de vie ou leur usage l’exige. Une infrastructure temporaire peut être retirée après sa mission. Une infrastructure permanente n’est pas automatiquement démontée à la fin du chantier qui l’a créée. |
| **A3** | Le contrat distingue les grandes étapes suivantes : demande ou planification, construction, construction achevée, mise en service, fin d’utilisation, démontage, récupération et restauration lorsque celle-ci est applicable. Les états d’attente, de blocage et d’échec doivent rester cohérents avec le système de tâches **C-04**, sans créer inutilement un deuxième cycle de vie des tâches. Les transitions autorisées et les conditions exactes de chaque état devront être précisées sans confondre « Achevé », « En service », « démonté », « récupéré » et « restauré ». |

### B — Responsabilités et construction

| # | Décision |
| --- | --- |
| **B1** | C-14 définit un propriétaire métier unique pour l’état réel du cycle de vie de chaque infrastructure. Les tâches, les unités, le rendu visuel et l’interface peuvent consulter cet état, mais ne doivent pas devenir des sources de vérité concurrentes. Le choix de l’architecture C++ concrète doit respecter l’architecture réelle du projet. |
| **B2** | C-14 possède les règles générales du cycle de vie des infrastructures. **C-13\*** conserve son périmètre fermé relatif au critère de cohorte « Achevé / En service ». **DG-02** reste propriétaire du modèle de définition et des propriétés des bâtiments. C-14 peut exploiter ces définitions sans absorber leurs responsabilités. Aucun addendum clôturé ne doit être rouvert. |
| **B3** | Une intention ou un besoin autorisé génère le travail nécessaire à l’infrastructure. **C-04** porte les tâches et leurs dépendances ; **C-07** exécute les tâches ; **C-05** gère la préparation du site ; **C-08** demeure propriétaire des opérations métier relevant de son domaine. C-14 définit le résultat attendu du cycle de vie sans créer un second gestionnaire de tâches ni imposer au joueur de gérer manuellement chaque étape ordinaire. |

### C — Terrain, ressources et accès

| # | Décision |
| --- | --- |
| **C1** | C-14 déclare l’emprise et les besoins d’occupation de l’infrastructure. **C-02** fournit les services spatiaux et les notifications pertinents. **C-01** reste propriétaire de la vérité du relief. **C-05** conserve la responsabilité de décider et de vérifier la préparation du site. C-14 ne doit pas dupliquer ces systèmes ni s’attribuer leur autorité. |
| **C2** | C-14 définit les besoins et résultats métier en ressources liés au cycle de vie. **C-11** demeure propriétaire des réservations de stock. **C-08** demeure propriétaire des opérations métier concernant les matières. Toute consommation, récupération ou redistribution doit correspondre à un effet réel confirmé. Le démontage ne doit pas générer automatiquement des matériaux fictifs. Les quantités récupérables et leurs règles restent ouvertes lorsqu’aucune décision existante ne les précise. |
| **C3** | C-14 définit le cycle de vie des infrastructures qui rendent des accès ou des réseaux disponibles. **C-12** utilise les accès disponibles pour le transport, mais ne construit pas lui-même l’infrastructure manquante. Les règles d’accès, de capacité et de saturation doivent respecter **DG-06 / N4**. Leur validation de conception ne signifie pas que leur fonctionnement opérationnel est déjà démontré. |

### D — Partage et durée de vie

| # | Décision |
| --- | --- |
| **D1** | Une infrastructure peut servir plusieurs bénéficiaires lorsque son état et les règles d’autorisation le permettent. Le système doit distinguer son existence, sa disponibilité, son utilisation effective et son indisponibilité. Les conflits et autorisations doivent être traités explicitement, sans inventer de capacité illimitée ni de nouvelle hiérarchie de priorités. |
| **D2** | La catégorie et la politique de fin d’utilisation doivent être explicites. Une infrastructure temporaire possède une fin d’utilisation prévue ou une condition de retrait. Une infrastructure permanente n’est pas démontée automatiquement à la fin d’un chantier. L’absence de date ou de condition ne doit pas entraîner de conversion implicite de catégorie. |
| **D3** | Le démontage, la récupération des éléments et la restauration éventuelle du site sont des résultats distincts et vérifiables. Une infrastructure démontée n’est pas automatiquement considérée comme entièrement récupérée. La récupération complète des matériaux ne signifie pas non plus que le terrain est restauré. |

### E — Code existant et validation ODC-F9

| # | Décision |
| --- | --- |
| **E1** | Le mécanisme `BuildingPlacement` existant est préservé. Son statut et sa frontière avec le futur cycle de vie doivent être documentés. Le placement manuel peut demeurer un mécanisme technique ou de prototype jusqu’à une décision explicite de migration. C-14 ne doit ni supprimer ni réécrire ce mécanisme par anticipation. Cette préservation ne fait pas du placement manuel le mécanisme définitif de gestion des infrastructures. |
| **E2** | La cible recommandée pour la première preuve ODC-F9 est une cohorte limitée mais représentative démontrant : une infrastructure temporaire avec construction, utilisation, démontage et récupération ; une infrastructure permanente dont l’utilisation est confirmée ; la restauration du site lorsque celle-ci est applicable au cas choisi. Les critères définitifs doivent rester alignés sur la fiche ODC-F9 officielle. Cette recommandation ne constitue pas une preuve qu’ODC-F9 est déjà opérationnel ni une autorisation de commencer son implémentation. |

### F — Limites et périmètre initial

| # | Décision |
| --- | --- |
| **F1** | C-14 n’intègre pas prématurément la simulation économique complète de l’entretien, le catalogue exhaustif des rails et autres familles futures d’infrastructures, ni les extensions de Case B suspendu. Le contrat reste extensible. Une dépendance incontournable doit être démontrée et autorisée avant d’élargir ce périmètre. Une lacune ne justifie pas la réouverture automatique de C-10 ou de Case B. |

---

## 3. Périmètre et exclusions

### 3.1 Inclus (A1, A2, A3)

- cycle de vie global des infrastructures (construction → fin d’utilisation → démontage / récupération / restauration éventuelle) (A1) ;  
- infrastructures **temporaires** et **permanentes** dans un modèle cohérent (A2) ;  
- grandes étapes du cycle et distinction des résultats « Achevé », « En service », « démonté », « récupéré », « restauré » (A3) ;  
- propriétaire unique de l’état runtime du cycle (B1) ;  
- génération du travail via intention / besoin autorisé, sans second graphe de tâches (B3) ;  
- déclaration d’emprise et besoins d’occupation (C1) ;  
- besoins / résultats métier en ressources liés au cycle, sans matières fictives (C2) ;  
- lifecycle des infrastructures d’accès / réseaux utilisés par C-12 (C3) ;  
- partage contrôlé multi-bénéficiaires (D1) ;  
- politiques de fin d’utilisation selon catégorie (D2) ;  
- distinction démontage / récupération / restauration (D3) ;  
- documentation du placement manuel existant sans migration forcée (E1) ;  
- cible de preuve ODC-F9 recommandée, non exécutée (E2) ;  
- hors-périmètre immédiat explicite (F1).

### 3.2 Exclus / hors autorité C-14

| Domaine | Autorité |
| --- | --- |
| Vérité du relief | **C-01** (C1) |
| Services spatiaux / dirty / queries | **C-02** (C1) |
| Graphe, dépendances, cycle de vie des **tâches** | **C-04** (A3, B3) |
| WorkSite / SitePrep / `SiteReady` | **C-05** (B3, C1) |
| Agent générique / sélection / exécution | **C-07** (B3) |
| Opérations métier matières (Terraform / matières) | **C-08** (B3, C2) |
| Réservations / concurrence stocks | **C-11** (C2) |
| Utilisation logistique des accès / transport | **C-12** (C3) — **ne construit pas** l’infra manquante |
| Critère cohorte Achevé / En service | **C-13\*** fermé (B2) |
| Définition / propriétés des bâtiments | **DG-02** (B2) |
| Conception accès / saturation | **DG-06 / N4** (C3) — conception ≠ runtime démontré |
| Simulation économique d’entretien complète | **Hors périmètre immédiat** (F1) |
| Catalogue exhaustif rails / familles futures | **Hors périmètre immédiat** (F1) |
| Case B | **Suspendu** (F1) |
| Ouverture C-10 | **Interdite** automatiquement (F1) |
| Mécanisme de sauvegarde | **C-19** (hors décisions C-14 — non absorbé) |

---

## 4. Définitions

| Terme | Sens dans C-14 |
| --- | --- |
| **Infrastructure** | Aménagement ou équipement territorial servant de support, d’accès, de liaison ou de fonctionnement (aligné vocabulaire DG / DG-10), soumis au cycle de vie C-14. |
| **Temporaire** | Infrastructure dont la mission et la fin d’utilisation / condition de retrait sont prévues ; peut être retirée après sa mission (A2, D2). |
| **Permanente** | Infrastructure destinée à demeurer ; **n’est pas** démontée automatiquement à la fin du chantier qui l’a créée (A2, D2). |
| **Demande / planification** | Étape où un besoin ou une intention autorisée ouvre le travail nécessaire (A3, B3). |
| **Construction** | Phase de réalisation des travaux d’infrastructure (A3). |
| **Construction achevée (« Achevé »)** | Travaux de construction de l’infrastructure terminés — **distinct** de la mise en service (A3). |
| **Mise en service (« En service »)** | Infrastructure utilisable selon sa fonction — **distinct** de « Achevé », « démonté », « récupéré », « restauré » (A3). *Le critère cohorte S3 de C-13\* n’est pas généralisé ici (B2).* |
| **Fin d’utilisation** | Fin de mission ou condition de retrait selon la catégorie (A3, D2). |
| **Démontage** | Retrait de l’infrastructure en tant qu’objet / présence opérationnelle — **ne vaut pas** récupération complète ni restauration du site (D3). |
| **Récupération** | Récupération des éléments / matières réellement récupérables — **ne vaut pas** restauration du terrain (C2, D3). |
| **Restauration** | Remise éventuelle du site lorsque applicable — résultat **distinct** et vérifiable (A1, D3, E2). |
| **Existence** | L’infrastructure est présente dans le modèle métier (D1). |
| **Disponibilité** | L’infrastructure peut être utilisée selon son état et les autorisations (D1). |
| **Utilisation effective** | Usage réel par un ou plusieurs bénéficiaires (D1). |
| **Indisponibilité** | État où l’usage n’est pas autorisé ou possible malgré l’existence éventuelle (D1). |
| **Emprise** | Occupation spatiale déclarée par C-14 ; services spatiaux via C-02 ; relief via C-01 ; préparation via C-05 (C1). |
| **Bénéficiaire** | Entité autorisée à utiliser une infrastructure partagée lorsque les règles le permettent (D1). |

---

## 5. Cycle de vie et transitions (A3, A2, D2, D3)

### 5.1 Grandes étapes

```text
Demande / planification
    → Construction
    → Construction achevée (Achevé)
    → Mise en service (En service)
    → Fin d’utilisation
    → Démontage
    → Récupération
    → Restauration (lorsque applicable)
```

Ces étapes sont des **jalons métier** du cycle d’infrastructure. Elles **ne constituent pas** un second cycle de vie des tâches (A3). Attente, blocage et échec des travaux restent cohérents avec **C-04**.

### 5.2 Distinctions obligatoires (A3, D3)

| Ne pas confondre | Avec |
| --- | --- |
| Construction achevée | Mise en service |
| Mise en service | Démontage |
| Démontage | Récupération complète |
| Récupération | Restauration du site |
| Fin d’utilisation temporaire | Démontage automatique d’une permanente |

### 5.3 Règles de catégorie (A2, D2)

- **Temporaire** : fin d’utilisation prévue ou condition de retrait **explicite** ; peut être retirée après mission.  
- **Permanente** : **pas** de démontage automatique à la fin du chantier créateur.  
- Absence de date / condition → **pas** de conversion implicite temporaire ↔ permanente (D2).

### 5.4 Transitions — précision ouverte

Les **transitions autorisées** et les **conditions exactes** de chaque état **doivent être précisées** (A3) sans inventer ici de délais, formules, politiques de repli ou catalogues d’exceptions non validés. Tant que ces précisions ne sont pas tranchées par décision humaine supplémentaire, elles restent **ouvertes** (§18).

---

## 6. Propriété de l’état runtime (B1)

C-14 exige un **propriétaire métier unique** de l’état réel du cycle de vie de chaque infrastructure.

| Acteur | Rôle autorisé |
| --- | --- |
| Propriétaire C-14 (à implémenter selon l’architecture réelle) | Source de vérité de l’état lifecycle |
| Tâches (C-04) | Consulter uniquement ; toute évolution de l’état du cycle de vie relève exclusivement du propriétaire métier unique défini par C-14. |
| Unités / agent (C-07) | Exécuter ; **pas** vérité concurrente |
| Rendu / UI | Afficher / consulter ; **pas** vérité concurrente |

Le choix de l’architecture C++ concrète **n’est pas imposé** par ce contrat au-delà de : respect de l’architecture réelle du projet et unicité de la vérité métier (B1).

---

## 7. Construction, tâches et unités (B3)

1. Une **intention** ou un **besoin autorisé** génère le travail nécessaire.  
2. **C-04** porte tâches et dépendances.  
3. **C-07** exécute.  
4. **C-05** prépare / vérifie le site lorsque requis.  
5. **C-08** reste propriétaire des opérations métier matières de son domaine.  
6. **C-14** définit le **résultat attendu** du cycle de vie.

Interdits par B3 :

- second gestionnaire de tâches parallèle à C-04 ;  
- imposer au joueur la microgestion manuelle de chaque étape ordinaire du cycle.

---

## 8. Frontière C-13\* et DG-02 (B2)

| Domaine | Règle |
| --- | --- |
| **C-14** | Règles générales du cycle de vie des infrastructures |
| **C-13\*** | Périmètre **fermé** — critère de cohorte « Achevé / En service » ; **ne pas rouvrir** |
| **DG-02** | Modèle de définition et propriétés des bâtiments ; C-14 peut **exploiter** sans absorber |

Aucun addendum clôturé (dont C-10\*, C-13\*) n’est rouvert par C-14 (B2, F1).

---

## 9. Emprise et spatial (C1)

| Responsabilité | Propriétaire |
| --- | --- |
| Déclaration d’emprise / besoins d’occupation | **C-14** |
| Services spatiaux et notifications | **C-02** |
| Vérité du relief | **C-01** |
| Décision et vérification de préparation du site | **C-05** |

C-14 **ne duplique pas** C-01 / C-02 / C-05 et **ne s’attribue pas** leur autorité.

---

## 10. Ressources, consommation et récupération (C2, D3)

- C-14 définit besoins et résultats métier en ressources **liés au cycle de vie**.  
- **C-11** : réservations de stock.  
- **C-08** : opérations métier matières.  
- Toute consommation, récupération ou redistribution = **effet réel confirmé**.  
- Le démontage **ne génère pas** automatiquement des matériaux fictifs.  
- Quantités récupérables et règles détaillées : **ouvertes** si non déjà décidées ailleurs (C2).  
- Démontage ≠ récupération ≠ restauration (D3).

---

## 11. Accès, réseaux et frontière C-12 (C3)

- C-14 : cycle de vie des infrastructures qui **rendent disponibles** accès ou réseaux.  
- C-12 : **utilise** les accès disponibles ; **ne construit pas** l’infrastructure manquante (aligné C-12 A3).  
- Accès / capacité / saturation : respect de **DG-06 / N4** en conception.  
- Validation de conception **≠** fonctionnement opérationnel déjà démontré (C3).

Aucune formule de saturation, aucun seuil numérique ni hiérarchie de priorité nouvelle n’est inventée ici (D1, C3).

---

## 12. Partage et capacité (D1)

Une infrastructure peut servir **plusieurs bénéficiaires** si état + autorisations le permettent.

Le système distingue explicitement :

1. existence ;  
2. disponibilité ;  
3. utilisation effective ;  
4. indisponibilité.

Conflits et autorisations : **traités explicitement**.  
Interdits : capacité illimitée inventée ; nouvelle hiérarchie de priorités inventée (D1).

---

## 13. Placement manuel existant (E1)

| Élément | Statut dans C-14 |
| --- | --- |
| `UGardenFervorBuildingPlacementComponent` | **Préservé** — mécanisme technique / prototype possible |
| Migration vers le cycle C-14 | **Ouverte** — uniquement sur décision explicite |
| Suppression / réécriture anticipée | **Interdite** par E1 |
| Mécanisme définitif de gestion des infrastructures | **Non** — le placement manuel ne l’est pas par préservation |

Frontière documentaire : le placement manuel n’est **pas** assimilé au propriétaire d’état lifecycle C-14 (B1, E1).

---

## 14. Preuve ODC-F9 (E2)

### 14.1 Cible recommandée (non exécutée)

Cohorte limitée mais représentative démontrant :

1. une infrastructure **temporaire** : construction, utilisation, démontage et récupération ;  
2. une infrastructure **permanente** : utilisation confirmée ;  
3. **restauration** du site lorsque applicable au cas choisi.

### 14.2 Limites

- Critères définitifs : alignés sur la **fiche ODC-F9 officielle** (lorsqu’elle existe / sera tenue).  
- Cette section **n’est pas** une preuve que ODC-F9 est opérationnel.  
- Cette section **n’autorise pas** le démarrage de l’implémentation ODC-F9.  
- ODC-F9 n’est **pas** déclaré PASS ni exécuté.

---

## 15. Hors périmètre immédiat (F1)

C-14 **n’intègre pas prématurément** :

- simulation économique complète de l’entretien ;  
- catalogue exhaustif des rails et autres familles futures ;  
- extensions de **Case B** (suspendu).

Le contrat reste **extensible**. Une dépendance incontournable doit être **démontrée et autorisée** avant élargissement. Une lacune **ne justifie pas** la réouverture automatique de C-10 ou Case B.

---

## 16. Frontières synthétiques

| Contrat / décision | Responsabilité | Relation à C-14 |
| --- | --- | --- |
| **C-01** | Vérité relief | Emprise / effets sol via autorités propres (C1) |
| **C-02** | Spatial / dirty / queries | Services consommés (C1) |
| **C-04** | Tâches / graphe | Travaux ; pas 2ᵉ cycle tâche (A3, B3) |
| **C-05** | SitePrep / `SiteReady` | Préparation ; ≠ lifecycle infra (B3, C1) |
| **C-07** | Agent / exécution | Exécute ; pas vérité lifecycle (B1, B3) |
| **C-08** | Ops matières | Consommation / matières réelles (C2) |
| **C-11** | Réservations | Stocks ; pas inventer matières (C2) |
| **C-12** | Transport / logistique | Utilise accès ; ne construit pas (C3) |
| **C-13\*** | Critère cohorte Achevé/En service | **Fermé** (B2) |
| **C-14** | Lifecycle infrastructures | — |
| **DG-02** | Définitions bâtiments | Exploitables, non absorbées (B2) |
| **DG-06 / N4** | Accès / saturation (conception) | Respectées ; runtime non assumé démontré (C3) |
| **DG-10** | Conception infrastructures | Référence conceptuelle ; ≠ preuve runtime |
| **C-10\*** | Stocks A/B addendum | **Fermé** (F1) |
| **Case B** | Demo / gameplay produit | **Suspendu** (F1) |

---

## 17. État réel de l’implémentation (lecture seule — ≠ règles cibles)

Qualification : **vérifié dans le code** lors de la rédaction, sauf mention contraire.

### 17.1 Mécanismes constatés

| Mécanisme | Nature | Qualification |
| --- | --- | --- |
| `AGardenFervorBuildingBase` · `BeginConstruction` · `bConstructionComplete` | Acteur bâtiment + construction locale (timer / completion) | **Vérifié** — partiel vs cycle C-14 |
| `UGardenFervorBuildingPlacementComponent` | Ghost + placement manuel + appel `BeginConstruction` | **Vérifié** — préservé (E1) |
| `UGardenFervorBuildingDefinition` | Coût, durée, mesh, âge, classe | **Vérifié** — pas de champs lifecycle temp/perm / réseau identifiés dans l’en-tête inspecté |
| `MarkConstructionComplete` · `bInService` · `ConstructWorkSite` (projet S3) | Critère cohorte Achevé / En service | **Vérifié** — **partiel** ; relève du périmètre C-13\* / cohorte, pas du lifecycle C-14 complet |
| API universelle démontage / récupération / restauration d’infrastructure | — | **Absent dans le périmètre inspecté** (`Source/GardenFervor/RTS`) |
| Owner runtime unique d’état lifecycle C-14 | — | **Absent** (à créer selon architecture réelle — B1) |
| Réseaux / saturation N4 opérationnels | — | **Non démontrés** (conception DG-06/N4) |

### 17.2 Preuves

| Preuve | État |
| --- | --- |
| DG-10 (10.1–10.5) | Conception **VALIDÉE** — **pas** preuve runtime |
| S3 / C5 Achevé + En service (Timber Stock B) | **Partielle** — critère cohorte, pas cycle 10.2 C-14 |
| ODC-F9 | **Absent / non démarré** dans le dépôt inspecté (aucun `Saved/ODC_F9*` constaté) |
| Lifecycle temporaire complet (construction→démontage→récupération) | **Non démontré** |
| Restauration de site post-démontage | **Non démontrée** |

Les règles §2–§15 sont des **invariants normatifs** ; le runtime peut être **en dette** sans les invalider (A1).

---

## 18. Dépendances, risques et points ouverts

| Direction | Éléments |
| --- | --- |
| **Amont registre** | C-02 · C-05 · C-12 VALIDÉS |
| **Conception** | DG-10 · DG-02 · DG-06 / N4 |
| **Aval annoncé** | ODC-F9 (non démarré) |
| **Voisinage fermé** | C-13\* · C-10\* · Case B suspendu |

**Risques** (signalement, pas correction) :

- confusion Achevé/En service cohorte (C-13\*) vs lifecycle infrastructure (C-14) ;  
- confusion placement manuel legacy vs mécanisme définitif (E1) ;  
- présenter une V1 partielle comme cycle complet opérationnel (A1) ;  
- inventer matières au démontage (C2) ;  
- confondre démontage / récupération / restauration (D3).

Restent **ouverts** s’ils ne sont pas tranchés par les 15 décisions :

- conditions exactes et catalogue des transitions d’état (A3) ;  
- architecture C++ concrète du propriétaire d’état (B1) ;  
- quantités récupérables et barèmes de récupération (C2) ;  
- formalisme détaillé des autorisations / conflits de partage au-delà de D1 ;  
- critères définitifs de la fiche ODC-F9 officielle (E2) ;  
- décision explicite de migration hors `BuildingPlacement` (E1) ;  
- élargissements futurs (entretien économique, rails, etc.) uniquement si démontrés et autorisés (F1) ;  
- implémentation gameplay ;  
- réactivation Case B.

---

## 19. Couverture des 15 décisions

| Bloc | Décisions | Section(s) principales |
| --- | --- | --- |
| A | A1–A3 | §2.A, §3, §4, §5, §17 |
| B | B1–B3 | §2.B, §6–§8 |
| C | C1–C3 | §2.C, §9–§11 |
| D | D1–D3 | §2.D, §5, §10, §12 |
| E | E1–E2 | §2.E, §13–§14, §17 |
| F | F1 | §2.F, §15, §18 |

**Total : 15 / 15 (A1–F1).**

Contrôle rédactionnel (auto-contrôle, **≠** audit indépendant) :

- 15 décisions reprises ;  
- 0 décision nouvelle introduite comme règle ;  
- frontières C-01 / C-02 / C-04 / C-05 / C-07 / C-08 / C-11 / C-12 / C-13\* / DG-02 / DG-06 préservées ;  
- C-10 non ouvert ; Case B **suspendu** ;  
- ODC-F9 non déclaré PASS ;  
- placement manuel non migré de force ;  
- points ouverts §18 conservés ;  
- statut **VALIDÉ**.

---

## 20. Statut

| État | Valeur |
| --- | --- |
| Document | `CONTRATS/C-14_INFRASTRUCTURES_LIFECYCLE.md` |
| Statut | **VALIDÉ** |
| Règle officielle | **Oui** — validation humaine ; audit indépendant final 15/15 PASS |
| Décisions | **15 / 15** (A1–F1) |
| Compteur global | **9 / 16** (C-03, C-06, C-09, C-10, C-13 hors dénominateur) |
| Case B | **Suspendu** |
| C-10\* / C-13\* | **Fermés** |
| C-12 | **VALIDÉ** (A1–G3 inchangées) |

---

*Fin C-14 — VALIDÉ. C-10 et C-13\* demeurent addenda fermés. Case B demeure suspendu. Points ouverts §18 conservés. Aucune implémentation ni contrat suivant démarrés par cette clôture.*
