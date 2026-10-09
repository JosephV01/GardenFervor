# C-11 — Réservations

| Champ | Valeur |
| --- | --- |
| **ID** | C-11 |
| **Nom** | Réservations |
| **Statut documentaire** | **VALIDÉ** — validation humaine explicite ; audit indépendant final 23/23 PASS ; dettes d’implémentation / preuves manquantes conservées (§13.1) |
| **Profondeur** | Détaillée (registre) |
| **Ordre de rédaction** | 11 |
| **Bloquant** | Oui (avant multi-chantier — registre) |
| **Dépendances amont** | **C-04** (mécanisme) · preuves S3 / PE disponibles ; **C-09\*** · **C-10\*** restent addenda **fermés** (A1) |
| **Références** | Registre C-11 · DG-05.3 · C-04 I1–I3 · C-07 G1–G3 · C-08 H2–H3 · TaskSubsystem · PhysicalEconomySubsystem · décisions humaines A1–G1 (23) |

Ce document formalise les **23 décisions humaines C-11** reprises **sans modification de sens**.  
Il n’invente aucune règle supplémentaire.  
Il constitue la **règle opérationnelle** C-11 après validation humaine et inscription **VALIDÉ** dans le suivi.  
Il ne constitue **pas** une autorisation d’implémentation, d’ouverture de C-09/C-10, ni une réactivation de Case B.

**Case B** demeure **suspendu** jusqu’à décision humaine explicite de réouverture.

Référentiel des lettres validées (identité des options) :

```text
A1 A2 A3 A4
B1 B2 B3 B4
C1 C2 C3 C4
D1 D2 D3 D4
E1 E2 E3 E4
F1 F2
G1
```

Le **sens opératoire** de chaque décision est celui de §2 ci-dessous (référentiel d’autorité).

---

## 1. Identité et finalité

C-11 est le contrat des **règles détaillées d’allocation concurrente** de ressources et de matières provenant des **stocks** : demandes, attributions, priorités, cohérence physique, libération et observabilité (A2).

Il complète le **mécanisme** et les **garanties minimales** déjà fixés par **C-04** (I1–I3), sans remplacer le graphe ni le cycle de vie des tâches.

---

## 2. Décisions validées (source de vérité)

Les **23** décisions suivantes sont reprises **fidèlement**.

### A — Périmètre et responsabilités

| # | Décision |
| --- | --- |
| **A1** | C-11 avance avec les contrats **validés** et les **preuves disponibles**. **C-09** et **C-10** restent **fermés**. Toute lacune réellement bloquante est **signalée séparément**, sans réouverture implicite. |
| **A2** | C-11 porte sur l’**allocation concurrente** de ressources et de matières provenant des **stocks**. Les **claims de tâches**, les **capacités d’unités** et le **transport avancé** ne relèvent **pas** de ce contrat. |
| **A3** | Le **claim de tâche** et la **réservation de stock** sont **distincts**. **C-04** gère les tâches ; **C-11** définit l’arbitrage des allocations concurrentes. L’exécution **ne réserve pas une seconde fois** les mêmes quantités. |
| **A4** | Le **stock réel** et ses quantités **non libres** déterminent la disponibilité. Toute réservation possède un **bénéficiaire identifiable**. |

### B — Demandes et allocations

| # | Décision |
| --- | --- |
| **B1** | Une demande précise : **bénéficiaire**, **ressource**, **quantité demandée**, **stock concerné** ou sa **règle de sélection**, **contexte** de la demande et **priorité** applicable. |
| **B2** | Par défaut, une demande est **accordée intégralement** ou **refusée**. Le travail partiel s’exprime par des **demandes distinctes** correspondant aux étapes réellement exécutables. |
| **B3** | Toutes les ressources nécessaires à une **même étape** doivent être réservées **atomiquement**. Si une ressource requise manque, **aucune** allocation partielle de cette tentative ne reste immobilisée. |
| **B4** | `SpoilDirt` et `FillDirt` **ne deviennent pas automatiquement** des ressources économiques. **Aucune** conversion économique implicite n’est autorisée. |

### C — Priorités et concurrence

| # | Décision |
| --- | --- |
| **C1** | Ordre de priorité successif : (1) **priorité du chantier explicitement définie par le joueur** ; (2) **urgence** ; (3) **proximité**. « Chantier joueur » = chantier dont le joueur a défini la priorité. |
| **C2** | Les priorités départagent les demandes **avant** attribution. Une nouvelle demande prioritaire **ne reprend pas automatiquement** une réservation déjà accordée. |
| **C3** | À priorité équivalente : départager par **ancienneté** de la demande, puis par un **identifiant stable**. |
| **C4** | **Aucune** promotion automatique de priorité fondée uniquement sur la durée d’attente. L’attente et sa cause restent **observables**. |

### D — Blocage et libération

| # | Décision |
| --- | --- |
| **D1** | **Aucune** préemption automatique d’une réservation déjà accordée. Toute réattribution exige un **événement valide** ou une **libération autorisée**. |
| **D2** | `Blocked` **ne libère pas automatiquement** toutes les réservations. Les allocations encore nécessaires peuvent être **conservées** ; celles devenues inutiles ou invalides sont libérées par le **propriétaire compétent**. |
| **D3** | Les quantités **non consommées** sont libérées lorsqu’elles deviennent inutiles, notamment après **achèvement**, **annulation**, **abandon explicite** ou **invalidation pertinente**, selon les responsabilités du système propriétaire. |
| **D4** | **Aucune** expiration arbitraire après un délai fixe. Les réservations sont **réconciliées** à partir d’**événements pertinents**, complétés par une **vérification de sécurité ciblée**. |

### E — Stock et cohérence physique

| # | Décision |
| --- | --- |
| **E1** | Une quantité **réservée** ou **en transit** n’est **pas** librement disponible pour une nouvelle demande. **C-12** conserve la responsabilité du transport avancé. |
| **E2** | Les allocations **ne peuvent pas dépasser silencieusement** le stock réel. Toute incohérence impose une **réconciliation déterministe** et le **signalement** des bénéficiaires affectés. |
| **E3** | Une matière est **consommée** uniquement lorsqu’un **effet métier réel** justifie cette consommation et que le **système compétent** confirme la quantité effectivement utilisée. |
| **E4** | **Réévaluer** les demandes lors des changements pertinents : disponibilité, libération, priorité ou modification du besoin. Compléter par une **vérification de sécurité ciblée**. |

### F — Chargement et lisibilité

| # | Décision |
| --- | --- |
| **F1** | Avant la reprise des effets d’une tâche, ses réservations doivent être **restaurées ou réacquises**, puis **vérifiées**. C-11 définit l’**invariant métier** ; **C-19** reste responsable du **mécanisme** de persistance. |
| **F2** | Présenter une information **agrégée** et compréhensible : disponibilité, quantités mobilisées ou en transit, cause du blocage et bénéficiaire concerné lorsque pertinent. Les **détails techniques fins** restent cachés. |

### G — Critères de preuve

| # | Décision |
| --- | --- |
| **G1** | Le contrat définit des critères **vérifiables** portant sur : demandes concurrentes, priorités, égalités, allocations atomiques, libérations, insuffisance de stock, transit, effets partiels et reprise après chargement. Séparer strictement les **règles cibles** des **capacités actuellement démontrées** par le runtime. |

---

## 3. Périmètre et exclusions

### 3.1 Inclus (A2)

- demandes d’allocation concurrente sur stocks ;
- attribution, refus, atomicité d’étape ;
- priorités et départage ;
- conservation / libération / réconciliation ;
- cohérence stock réel ↔ allocations ;
- distinction réservé / transit / libre ;
- invariants de reprise après chargement ;
- observabilité agrégée ;
- critères de preuve (G1).

### 3.2 Exclus (A2, A3)

| Domaine | Autorité |
| --- | --- |
| Claim / graphe / états de tâche | **C-04** |
| Capacités d’unités | **C-06\*** / systèmes unités (hors C-11) |
| Transport avancé | **C-12** |
| SitePrep / SiteReady | **C-05** |
| Exécution générique | **C-07** |
| Métier Terraform / besoins matière opération | **C-08** |
| Mécanisme de sauvegarde | **C-19** |
| Ouverture C-09 / C-10 | **Interdite** par ce contrat (A1) |

---

## 4. Vocabulaire

| Terme | Sens dans C-11 |
| --- | --- |
| **Demande** | Intention d’allocation portant les champs de B1. |
| **Bénéficiaire** | Identité traçable de qui détient ou attend l’allocation (A4). |
| **Disponible** | Quantité du stock réel **non** réservée et **non** immobilisée comme non libre (A4, E1 ; aligné DG-05.3). |
| **Réservation / allocation** | Quantité rendue non libre pour un bénéficiaire identifiable. |
| **Accordée** | Demande entièrement satisfaite pour l’étape concernée (B2). |
| **Refusée** | Demande non accordée ; aucune immobilisation résiduelle de la tentative atomique (B2, B3). |
| **Atomicité d’étape** | Toutes les ressources requises d’une même étape ou rien (B3). |
| **Priorité chantier joueur** | Priorité **explicitement définie par le joueur** pour ce chantier (C1). |
| **Urgence / proximité** | Critères de départage après la priorité chantier joueur (C1) — **seuils numériques = points ouverts**. |
| **Préemption** | Reprise forcée d’une réservation déjà accordée au profit d’une autre demande — **interdite automatiquement** (D1, C2). |
| **Réconciliation** | Correction déterministe face à une incohérence matérielle (stock réel insuffisant) — **≠** préemption par priorité (E2, §9.5). |
| **Transit** | Quantité engagée dans un mouvement ; non libre pour d’autres (E1) ; détail transport → C-12. |
| **Consommation** | Retrait définitif justifié par un effet métier réel confirmé (E3). |

---

## 5. Responsabilités et frontières

| Contrat | Responsabilité | Relation à C-11 |
| --- | --- | --- |
| **C-04** | Graphe, dépendances, cycle de vie, claim, mécanisme et garanties générales de réservation liée à la tâche (I1–I3) | C-11 détaille concurrence / arbitrage sans remplacer C-04 |
| **C-05** | WorkSite, SitePrep, `SiteReady` | Pas d’arbitrage détaillé des stocks (C-05 B4, N1) |
| **C-07** | Exécution ; utilisation des API existantes ; pas de double-réservation (A3, C-07 G1) | Ne possède pas l’arbitrage concurrentiel |
| **C-08** | Besoins et résultats matière des opérations métier | Pas possession de l’arbitrage (C-08 H3) ; Spoil/Fill internes (B4, C-08 H5) |
| **C-11** | Demandes, allocation, concurrence, priorité, cohérence, libération des réservations de ressources/stocks | — |
| **C-12** | Transport et logistique avancés | Transit non libre (E1) ; pas redéfini ici |
| **C-19** | Mécanismes de persistance | Invariant reprise (F1) ; mécanisme save hors C-11 |
| **C-09\* / C-10\*** | Addenda économie / stocks | **Fermés** ; C-11 n’ouvre pas (A1) |

---

## 6. Invariants normatifs

1. **Deux couches distinctes** : claim tâche (C-04) ≠ réservation stock (C-11) (A3).  
2. **Pas de double réservation** des mêmes quantités par l’exécution (A3).  
3. **Bénéficiaire identifiable** pour toute allocation (A4).  
4. **Disponibilité** = stock réel moins quantités non libres (A4, E1).  
5. **Atomicité d’étape** : tout ou rien pour une tentative (B3).  
6. **Pas de préemption automatique** par priorité (D1, C2).  
7. **Pas de matière fictive** ; pas de dépassement silencieux du stock (E2).  
8. **Consommation** seulement si effet métier réel confirmé (E3).  
9. **SpoilDirt / FillDirt** : pas de conversion économique automatique (B4).  
10. **Pas d’expiration arbitraire** par délai fixe (D4).

---

## 7. Contenu d’une demande et règles d’allocation

### 7.1 Contenu obligatoire (B1)

Une demande doit préciser :

1. bénéficiaire ;  
2. ressource ;  
3. quantité demandée ;  
4. stock concerné **ou** règle de sélection de stock ;  
5. contexte de la demande ;  
6. priorité applicable.

*Point ouvert :* formalisme exact de la « règle de sélection » et du « contexte » (structure de données) — non inventé ici.

### 7.2 Accord / refus (B2)

- Par défaut : **intégral** ou **refus**.  
- Travail partiel = **plusieurs demandes** correspondant aux étapes réellement exécutables — pas une allocation partielle silencieuse de la même demande.

### 7.3 Atomicité (B3)

Si une ressource requise de l’étape manque : **aucune** allocation partielle de **cette tentative** ne reste immobilisée.

### 7.4 Matières opérationnelles (B4)

`SpoilDirt` / `FillDirt` restent hors conversion économique implicite (aligné DG-08 / C-08 H5).

---

## 8. Priorité et arbitrage

### 8.1 Ordre (C1)

Avant attribution, départager dans cet ordre :

1. priorité du chantier **explicitement définie par le joueur** ;  
2. urgence ;  
3. proximité.

### 8.2 Moment (C2)

Les priorités s’appliquent **avant** attribution.  
Une nouvelle demande plus prioritaire **ne reprend pas automatiquement** une réservation **déjà accordée**.

### 8.3 Égalité (C3)

Priorité équivalente → **ancienneté** de la demande, puis **identifiant stable**.

### 8.4 Attente (C4)

Pas de promotion automatique de priorité **seulement** parce que l’attente dure.  
Attente et cause restent observables.

*Points ouverts :* définition opérationnelle mesurable d’« urgence » et de « proximité » ; format de l’identifiant stable.

---

## 9. Blocage, libération et réconciliation — distinction D1 / E2

### 9.1 Non-préemption (D1)

Une réservation **valide déjà accordée** n’est **pas** reprise au seul motif qu’une **nouvelle** demande est plus prioritaire.  
Réattribution seulement si :

- **libération autorisée** (D3), ou  
- **événement valide** rendant l’allocation caduque, ou  
- **réconciliation d’intégrité** au sens de E2 (§9.5) — **pas** une préemption générale.

### 9.2 Tâche `Blocked` (D2)

`Blocked` (autorité d’état = **C-04**) **ne** vide **pas** automatiquement toutes les réservations.  
- Conservables : allocations encore nécessaires.  
- À libérer : inutiles ou invalides, par le **propriétaire compétent**.

### 9.3 Libération (D3)

Quantités non consommées libérées lorsqu’elles deviennent inutiles, notamment : achèvement, annulation, abandon explicite, invalidation pertinente — selon responsabilités du propriétaire.

### 9.4 Expiration (D4)

Pas de TTL arbitraire. Réconciliation sur **événements pertinents** + **vérification de sécurité ciblée**.

### 9.5 Réconciliation d’intégrité vs préemption (E2, D1) — **point de cohérence obligatoire**

| Situation | Règle |
| --- | --- |
| Nouvelle demande plus prioritaire, réservation antérieure **valide**, stock **cohérent** | **Pas** de reprise automatique (D1, C2) |
| Stock réel **insuffisant** / incohérence matérielle (allocations > réalité) | **Réconciliation déterministe** (E2) : aucune matière fictive ; ne pas masquer l’allocation devenue impossible ; **signaler** les bénéficiaires affectés |
| Effet de la réconciliation | Peut rendre une allocation **impossible à honorer** et obliger libération / réévaluation — ceci **n’est pas** une préemption « parce que priorité » |

La réconciliation d’intégrité **ne sert pas de prétexte** à une préemption générale fondée sur la priorité.

---

## 10. Stock, transit et consommation

| Règle | Décision |
| --- | --- |
| Transit / réservé | Non libre pour une nouvelle demande (E1) |
| Transport avancé | **C-12** (E1) |
| Dépassement silencieux | **Interdit** (E2) |
| Consommation | Effet métier réel + confirmation du système compétent (E3) |
| Réévaluation | Sur changements pertinents + vérif. sécurité ciblée (E4) |

---

## 11. Reprise après chargement

Avant reprise des **effets** d’une tâche (F1) :

1. réservations **restaurées** ou **réacquises** ;  
2. puis **vérifiées**.

- **Invariant métier** = C-11.  
- **Mécanisme de persistance** = **C-19**.

---

## 12. Informations observables

Information **agrégée** et compréhensible (F2) :

- disponibilité ;  
- quantités mobilisées ou en transit ;  
- cause de blocage ;  
- bénéficiaire concerné lorsque pertinent.

Détails techniques fins (files internes, IDs bruts, etc.) : **cachés** par défaut (aligné DG-00.6 conceptuellement ; pas de nouvelle règle UX inventée).

---

## 13. Critères de conformité et preuves attendues (G1)

Critères **vérifiables** devant pouvoir être démontrés (tests ciblés / gates / observation) :

| Domaine | Critère cible |
| --- | --- |
| Demandes concurrentes | Attribution selon C1–C3 sans double allocation silencieuse |
| Priorités | Ordre C1 ; pas de reprise auto (C2) |
| Égalités | Ancienneté puis id stable (C3) |
| Atomicité | B3 respecté |
| Libérations | D2–D3 ; pas de TTL arbitraire (D4) |
| Insuffisance stock | E2 : réconciliation + signal |
| Transit | E1 : non libre |
| Effets partiels | B2 : demandes distinctes ; E3 : conso justifiée |
| Reprise chargement | F1 |

### 13.1 Constats runtime (lecture seule — **≠** règles cibles)

| Mécanisme constaté | Nature |
| --- | --- |
| `FGardenFervorResourceReservation` (ResourceKey, Amount, bExclusive, bHeld, StockId) | Structure tâche |
| `TryAcquireReservation` / claim → réserve | API TaskSubsystem |
| `TryReserve` / `ReleaseReserve` / `CommitConsume` | API PhysicalEconomy |
| LevelPad FillDirt + exclusive | Cas S3 mince |
| Pool legacy / ResourcePool | Chemin alternatif possible |

| Preuve | État |
| --- | --- |
| F4 / F6 / F7 smokes (résa FillDirt, conflit exclusif) | **Partielles** pour S3 |
| Multi-chantier / priorité joueur / urgence / proximité / atomicité multi-ressources / reprise save | **Manquantes** ou non formalisées produit |
| Cohérence E2 sous diminution réelle de stock concurrente | **À démontrer** |

Les règles §2–§12 sont des **invariants normatifs** ; le runtime actuel peut être **en dette** sans les invalider (G1).

---

## 14. Dépendances et références

| Direction | Éléments |
| --- | --- |
| **Amont opérationnel** | **C-04** · preuves PE / stocks S3 |
| **Amont registre (addenda)** | C-09\* · C-10\* — **fermés** ; pas ouverts par C-11 (A1) |
| **Complémentaire** | C-05 · C-07 · C-08 · DG-05.3 |
| **Aval / voisin** | **C-12** · **C-19** |

---

## 15. Sujets non couverts / points ouverts

Aucun arbitrage nouveau. Restent ouverts s’ils ne sont pas tranchés par les 23 décisions :

- seuils / formules d’urgence et de proximité ;  
- structure exacte des données « contexte » / « règle de sélection de stock » ;  
- format de l’identifiant stable ;  
- table exhaustive des « événements pertinents » de réconciliation ;  
- politique détaillée multi-ressources au-delà de l’atomicité d’étape ;  
- ouverture éventuelle de C-09/C-10 si lacune bloquante **signalée séparément** (A1) ;  
- implémentation gameplay ;  
- réactivation Case B.

---

## 16. Couverture des 23 décisions

| Bloc | Décisions | Section(s) principales |
| --- | --- | --- |
| A | A1–A4 | §2.A, §3, §5, §14 |
| B | B1–B4 | §2.B, §7 |
| C | C1–C4 | §2.C, §8 |
| D | D1–D4 | §2.D, §9 |
| E | E1–E4 | §2.E, §9.5, §10 |
| F | F1–F2 | §2.F, §11–§12 |
| G | G1 | §2.G, §13 |

**Total : 23 / 23.**

Contrôle de clôture :

- audit indépendant final : **PASS** (23/23) ;  
- validation humaine : **acquise** ;  
- D1 / E2 distingués (§9.5) ;  
- frontières C-04 / C-05 / C-07 / C-08 / C-12 / C-19 préservées ;  
- C-09 / C-10 non ouverts ;  
- Case B **suspendu** ;  
- aucune valeur numérique inventée ;  
- preuves runtime manquantes = constats (§13.1), **pas** validation produit ;  
- statut **VALIDÉ**.

---

## 17. Statut

| État | Valeur |
| --- | --- |
| Document | `CONTRATS/C-11_RESERVATIONS.md` |
| Statut | **VALIDÉ** |
| Règle officielle | **Oui** — validation humaine ; audit indépendant final 23/23 PASS |
| Décisions | **23 / 23** (A1–G1) |
| Compteur global | **7 / 16** (C-03, C-06, C-09, C-10 hors dénominateur) |
| Case B | **Suspendu** |

---

*Fin C-11 — VALIDÉ. C-03, C-06, C-09 et C-10 demeurent addenda fermés. Case B demeure suspendu. Aucune implémentation ni contrat suivant démarrés par cette clôture.*
