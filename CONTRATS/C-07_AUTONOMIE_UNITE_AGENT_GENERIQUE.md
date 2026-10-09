# C-07 — Autonomie unité (agent générique)

| Champ | Valeur |
| --- | --- |
| **ID** | C-07 |
| **Nom** | Autonomie unité (agent générique) |
| **Statut documentaire** | **VALIDÉ** — validation humaine explicite ; audit indépendant final 47/47 PASS ; dettes d’implémentation conservées (§23) |
| **Profondeur** | Détaillée (registre) |
| **Ordre de rédaction** | 7 |
| **Bloquant** | Oui (autonomie visible / avant C-08 · Case B — registre) |
| **Dépendances amont** | **C-04** · **C-06\*** (addendum fermé — S3) |
| **Références** | Registre C-07 · DG-04 · DG-11.6 · UnitTaskAgent · ODC-F5 · décisions humaines A1–J4 (47) |

Ce document formalise les **47 décisions humaines C-07** reprises **sans modification de sens**.  
Il n’invente aucune règle supplémentaire.  
Il constitue la **règle opérationnelle** C-07 après validation humaine et inscription **VALIDÉ** dans le suivi.  
Il ne constitue **pas** une autorisation d’implémentation ni une réactivation de Case B.

**Case B** demeure **suspendu** jusqu’à décision humaine explicite de réouverture.

Référentiel des lettres validées (identité des options) :

```text
A1=C A2=C A3=B A4=B A5=C
B1=B B2=B B3=B B4=B B5=B
C1=B C2=B C3=B C4=B C5=B
D1=B D2=B D3=B D4=B D5=B
E1=C E2=B E3=B E4=B E5=B
F1=B F2=B F3=B F4=B F5=B
G1=B G2=B G3=B G4=B
H1=B H2=A H3=B H4=B
I1=B I2=B I3=B I4=B I5=B
J1=B J2=B J3=B J4=B
```

Le **sens opératoire** de chaque décision est celui de §2 ci-dessous (référentiel d’autorité).

---

## 1. Identité et finalité

C-07 est le contrat des **règles génériques d’exécution autonome** par les unités.

Il définit un **agent générique** qui **prend en charge, exécute et rapporte** les tâches, **sans posséder le graphe ni son cycle de vie** (A1).

Agent **commun** : les **capacités** et les **opérations concrètes** proviennent des **systèmes compétents** (A2).  
L’agent **orchestre** l’exécution et **délègue les effets** aux systèmes métier (A3).  
Les **transitions** de tâche passent par les **API autorisées de C-04** (A4).

---

## 2. Décisions validées (source de vérité)

Les **47** décisions suivantes sont reprises **fidèlement**.

### A — Périmètre et responsabilités

| # | Lettre | Décision |
| --- | --- | --- |
| **A1** | C | Agent générique qui **prend en charge, exécute et rapporte** les tâches, **sans posséder le graphe ni son cycle de vie**. |
| **A2** | C | Agent **commun** ; **capacités** et **opérations concrètes** provenant des **systèmes compétents**. |
| **A3** | B | L’agent **délègue les effets** aux systèmes métier et **orchestre** l’exécution. |
| **A4** | B | Les **transitions** passent par les **API autorisées de C-04**. |
| **A5** | C | **Préserver** le fallback existant des capacités comme **dette** ; **ne pas ouvrir C-06**. |

### B — Recherche, compatibilité et claim

| # | Lettre | Décision |
| --- | --- | --- |
| **B1** | B | Utiliser le **mécanisme de sélection de C-04**. |
| **B2** | B | Respecter les **capacités effectives** de l’unité et les **exigences** de la tâche. |
| **B3** | B | Obtenir un **claim valide avant** le déplacement opérationnel ou l’exécution. |
| **B4** | B | En l’absence de tâche admissible, **rester disponible** et **réévaluer** sans inventer de travail. |
| **B5** | B | Si le claim est **refusé ou perdu** : **arrêter** l’action concernée, **abandonner** la prise en charge devenue invalide et **rechercher** une tâche admissible. |

### C — Déplacement et arrivée

| # | Lettre | Décision |
| --- | --- | --- |
| **C1** | B | **Déplacement réel** en fonctionnement normal ; **téléportation** réservée aux tests ou démonstrations **explicitement identifiés**. |
| **C2** | B | **InstantMode** accélère les tests mais **ne valide pas à lui seul** le comportement produit. |
| **C3** | B | **Confirmer l’arrivée effective** via le système de déplacement **avant** le travail. |
| **C4** | B | Face à une **impossibilité persistante de déplacement** : signaler une **cause exploitable** et transmettre la situation à **C-04** ; **pas de `Failed` automatique**. |
| **C5** | B | Conserver une phase **`Prepare` facultative** sans dupliquer la readiness ni les prérequis de C-04. |

### D — Exécution et Progress

| # | Lettre | Décision |
| --- | --- | --- |
| **D1** | B | `Progress` représente l’**avancement de l’exécution**, pas une preuve universelle d’effet matériel. |
| **D2** | B | Permettre plusieurs **pulses / phases**, **interruptions** et **reprises**. |
| **D3** | B | Mécanisme **générique** qui **délègue** l’opération au **système compétent**. |
| **D4** | B | Les **timers** peuvent rythmer l’exécution, mais l’avancement doit rester **cohérent** avec le travail engagé ou accompli. |
| **D5** | B | Une interruption récupérable **préserve la progression utile** ; une **remise à zéro** doit être **justifiée**. |

### E — Effets, vérification et complétion

| # | Lettre | Décision |
| --- | --- | --- |
| **E1** | C | Le **système métier** détermine le **moment approprié** des effets ; opérations **progressives** ou **discrètes** possibles. |
| **E2** | B | Le **résultat attendu** doit être **confirmé** avant complétion par le **mécanisme compétent**. |
| **E3** | B | L’agent **demande** la complétion **après confirmation** ; **C-04** reste l’autorité de transition. |
| **E4** | B | Une **reprise** tient compte du travail déjà fait et **évite la répétition accidentelle** des effets. |
| **E5** | B | **Transport** doit **finaliser sa progression** de manière cohérente et **confirmer le résultat de transport** requis avant complétion. |

### F — Interruption, blocage et échec

| # | Lettre | Décision |
| --- | --- | --- |
| **F1** | B | **Signaler à C-04** une interruption récupérable et **préserver** la progression utile. |
| **F2** | B | Fournir à C-04 une **raison exploitable** ; le blocage et sa **cause primaire** utilisent les mécanismes contractuels. |
| **F3** | B | Ne signaler un **échec terminal** que lorsque les conditions le justifient ; la **transition passe par C-04**. |
| **F4** | B | **Aucune réactivation automatique** de `Failed` ; les situations récupérables suivent le mécanisme de **réévaluation de `Blocked`**. |
| **F5** | B | **Libérer correctement** la responsabilité de l’agent quand il cesse de prendre en charge la tâche, en coordination avec **C-04** et les **réservations**. |

### G — Réservations et cargaison

| # | Lettre | Décision |
| --- | --- | --- |
| **G1** | B | Utiliser les **API existantes** de réservation. |
| **G2** | B | Si une réservation nécessaire **disparaît** : **arrêter** l’action concernée et **signaler** la situation à C-04. |
| **G3** | B | Demander la **libération appropriée** via le **système propriétaire** ; aucune libération globale arbitraire. |
| **G4** | B | **Cargaison traçable**, sans perte ni duplication ; récupération concrète selon les **contrats métier** concernés. |

### H — Changements du monde

| # | Lettre | Décision |
| --- | --- | --- |
| **H1** | B | L’agent **ne devient pas** consommateur autonome du Dirty spatial ; il **réagit** aux changements de tâche et décisions transmis par **C-04**. |
| **H2** | A | **Vérifier** la validité du claim et des conditions d’exécution aux moments nécessaires, notamment **avant les opérations produisant des effets**. |
| **H3** | B | Lorsqu’une tâche est **invalidée** : arrêter les opérations qui ne sont plus autorisées, **préserver** les données pertinentes de reprise et **suivre** les instructions de C-04. |
| **H4** | B | **Signaler** l’indisponibilité de l’unité, **cesser** l’exécution si nécessaire et **laisser C-04** gérer la tâche. |

### I — Frontières métier

| # | Lettre | Décision |
| --- | --- | --- |
| **I1** | B | Les règles métier **Terraform** relèvent du système compétent et de **C-08**. |
| **I2** | B | **C-05** décide du besoin de SitePrep ; l’agent **exécute** les tâches résultantes via **C-04**. |
| **I3** | B | L’agent **rapporte** l’exécution Build mais **ne décide pas seul** du statut global Achevé / En service. |
| **I4** | B | Utiliser les **systèmes économiques et matériels compétents**. |
| **I5** | B | C-07 assure l’**exécution générique** ; **C-12** formalise les règles de transport plus avancées. |

### J — Observabilité et preuves

| # | Lettre | Décision |
| --- | --- | --- |
| **J1** | B | Les **étapes importantes** de l’exécution doivent être **distinguables**. |
| **J2** | B | Fournir un **rapport exploitable** de réussite, interruption et problèmes rencontrés. |
| **J3** | B | Distinguer **tests accélérés**, **exécution réelle** et **validation produit**. |
| **J4** | B | Tests **courts et ciblés**, complétés par **validation humaine rapide** lorsque celle-ci suffit. |

---

## 3. Vocabulaire

| Terme | Sens contractuel C-07 |
| --- | --- |
| **Agent** | Prise en charge / exécution / rapport génériques ; sans ownership du graphe ni du cycle de vie tâche (A1, A2). |
| **Unité** | Porteuse de capacités effectives ; opérations via systèmes compétents (A2, B2). |
| **Claim** | Autorisation d’exécution à obtenir **avant** déplacement opérationnel / exécution (B3). |
| **Progress** | Avancement d’exécution ; ≠ preuve universelle d’effet (D1). |
| **InstantMode** | Accélération de test ; ≠ validation produit à lui seul (C2, J3). |
| **Prepare** | Phase locale facultative ; ≠ readiness / prérequis C-04 (C5). |
| **Vérification** | Confirmation du résultat par le mécanisme compétent avant demande de complétion (E2). |
| **Complétion** | Demande via C-04 après confirmation (E3) ; ≠ Achevé / En service (I3). |
| **Interruption récupérable** | Signalée à C-04 ; Progress utile préservé (F1, D5). |
| **Failed** | Échec terminal justifié, transition via C-04 ; pas de réactivation auto (F3, F4). |
| **Blocked** | Situation récupérable réévaluable via mécanismes C-04 (F4). |

---

## 4. Relation agent / unité / tâche

```text
Unité (capacités effectives)
    ↓
Agent C-07 (orchestre ; prend en charge ; exécute ; rapporte)
    ↓ transitions via API C-04 (A4)
C-04 TaskSubsystem (graphe, readiness, cycle de vie, claim, Progress, Complete…)
    ↓ effets délégués (A3)
Systèmes métier (économie / matière I4 · Terraform C-08 / I1 · …)
    ↓ relief
C-01 (autorité hauteur)
```

L’agent ne possède ni le graphe ni le cycle de vie de la tâche (A1).

---

## 5. Recherche et sélection

- Sélection via le **mécanisme C-04** (B1).
- Respect des capacités effectives et des exigences de tâche (B2).
- Sans tâche admissible : rester disponible, réévaluer, **ne pas inventer** de travail (B4).
- Readiness / dépendances / graphe restent **C-04** (A1, A4).

---

## 6. Capacités et compatibilité

- Capacités effectives de l’unité ↔ exigences de la tâche (B2, A2).
- Fallback capacités existant (ex. Worker / Terraform hardcodés si DA vide) : **dette** à préserver ; **ne pas ouvrir C-06** (A5) — voir §23.

---

## 7. Claim et prise en charge

- Claim valide **avant** déplacement opérationnel ou exécution (B3).
- Transitions via API C-04 (A4).
- Claim refusé ou perdu → arrêter, abandonner la prise en charge invalide, rechercher une tâche admissible (B5).
- Libération de responsabilité coordonnée avec C-04 et réservations (F5, G3).

---

## 8. Déplacement et arrivée

- Fonctionnement normal : **déplacement réel** (C1).
- Téléportation / InstantMode : tests ou démos **explicitement identifiés** (C1) ; InstantMode **n’est pas** une preuve produit complète (C2, J3).
- Confirmer l’**arrivée effective** via le système de déplacement **avant** le travail (C3).
- Impossibilité persistante de déplacement → cause exploitable + transmission à C-04 ; **pas de Failed automatique** (C4).

---

## 9. Préparation locale (`Prepare`)

Phase **`Prepare` facultative** (C5) :

- ne duplique **pas** la readiness ni les prérequis de C-04 ;
- ne produit pas d’effets métier non autorisés ;
- reste distincte de la confirmation de résultat (E2).

---

## 10. Exécution et progression

| Règle | Décision |
| --- | --- |
| Progress = avancement d’exécution ≠ preuve universelle d’effet | D1 |
| Multi-pulses / phases, interruptions, reprises | D2 |
| Mécanisme générique ; délégation au système compétent | D3, A3 |
| Timers possibles ; avancement cohérent avec le travail engagé / accompli | D4 |
| Interruption récupérable : Progress utile préservé ; reset justifié | D5 |

---

## 11. Interruption et reprise

- Signaler l’interruption récupérable à C-04 et préserver la progression utile (F1, D5).
- Reprise : tenir compte du travail déjà fait ; éviter la répétition accidentelle des effets (E4).
- Détails physiques par métier : ouverts (§24).

---

## 12. Effets métier

- Le **système métier** choisit le moment des effets ; progressive ou discrète (E1).
- Délégation d’orchestration par l’agent (A3, D3).
- Terraform métier → système compétent + **C-08** (I1) — pas d’architecture définitive via `DisplayName` / RaiseGrade / LowerGrade (dette §23).
- Économie / matière → systèmes compétents (I4).
- Relief → **C-01** (autorité) ; l’agent déclenche via le système approprié.

---

## 13. Vérification et complétion

```text
Progress
    ≠
effet produit (moment = métier, E1)
    ≠
résultat confirmé (E2)
    ≠
CompleteTask via C-04 (E3)
    ≠
Chantier Achevé / En service (I3)
```

- Confirmation du résultat **avant** demande de complétion (E2).
- Demande de complétion **après** confirmation ; transition = **C-04** (E3).
- **Transport** : finaliser Progress de façon cohérente et confirmer le résultat de transport requis avant complétion (E5).

---

## 14. Blocage et échec

| Situation | Traitement |
| --- | --- |
| Interruption récupérable | Signaler à C-04 ; préserver Progress utile (F1, D5) |
| Blocked | Raison exploitable + cause primaire via mécanismes contractuels (F2) ; réévaluation (F4) |
| Échec terminal (Failed) | Seulement si justifié ; transition via C-04 (F3) |
| Failed | Pas de réactivation automatique ; récupérable → voie Blocked (F4) |
| Cessation de prise en charge | Libérer responsabilité agent + coordination réservations (F5, G3) |

Liste exhaustive des causes : **non inventée** (§24).

---

## 15. Libération du claim et des réservations

- API de réservation existantes (G1).
- Réservation nécessaire disparue → arrêter l’action et signaler à C-04 (G2).
- Libération via le **système propriétaire** ; pas de libération globale arbitraire (G3).
- Libération de la responsabilité agent à la cessation de prise en charge (F5).
- Remise à zéro de Progress seulement si justifiée (D5) — l’écart runtime `ReleaseClaim` → Progress=0 est une **dette** (§23), pas une règle souhaitée.

---

## 16. Cargaison et transport

- Cargaison **traçable**, sans perte ni duplication ; récupération selon contrats métier (G4).
- C-07 = exécution générique des tâches Transport déjà définies ; **C-12** = règles de transport avancées (I5).

---

## 17. Réaction aux changements du monde

```text
C-02  localise / signale (Dirty)
  → C-04  décide des conséquences sur les tâches
  → C-07  réagit aux changements / décisions transmis (H1)
```

- Vérifier claim et conditions d’exécution aux moments nécessaires, notamment avant effets (H2).
- Tâche invalidée → arrêter ops non autorisées, préserver données de reprise, suivre C-04 (H3).
- Unité indisponible → signaler, cesser si nécessaire, laisser C-04 gérer la tâche (H4).
- SitePrep = **C-05** (I2) ; réaction chantier = **DG-11.6**.

---

## 18. Observabilité et rapports

- Étapes importantes distinguables (J1).
- Rapport exploitable : réussite, interruption, problèmes (J2).
- États agent (Seek, Travel, Execute…) = lisibilité d’orchestration, **pas** autorité de cycle de vie tâche (A1).

---

## 19. Preuves et validation

Distinguer (J3) :

| Niveau | Rôle |
| --- | --- |
| **Tests accélérés** (ex. InstantMode) | Accélération / smoke — pas validation produit seule (C2) |
| **Exécution réelle** | Déplacement réel, effets, reprise observables (C1, J3) |
| **Validation produit** | Preuve ciblée + humaine si suffisant (J4) |

- Tests courts et ciblés ; validation humaine rapide lorsque suffisante (J4).
- Un gate Instant existant (ex. ODC-F5) **≠** validation produit complète de C-07 (C2, J3).
- **Case A** : constats documentés conservés (preuves existantes).
- **Case B** : **suspendu** — ce contrat n’autorise pas sa réactivation.

---

## 20. Frontières contractuelles

| Contrat / élément | Frontière |
| --- | --- |
| **C-01** | Autorité du relief. |
| **C-02** | Référence spatiale / Dirty ; agent non consommateur autonome (H1). |
| **C-04** | Graphe, readiness, cycle de vie, transitions API (A1, A4, B1). |
| **C-05** | Besoin / conformité SitePrep ; agent exécute les tâches résultantes via C-04 (I2). |
| **C-06\*** | Addendum fermé ; fallback capacités = dette (A5) — ne pas ouvrir. |
| **C-08** | Métier Terraform (I1). |
| **C-11** | Concurrence / réservations détaillées (au-delà des API utilisées — G1). |
| **C-12** | Transport avancé (I5). |
| **C-13\*** | Achevé / En service — agent rapporte Build, ne décide pas seul (I3). |
| **DG-04** | Principes autonomie (conception). |
| **DG-11.6** | Réaction au niveau du chantier. |

---

## 21. Non-objectifs

C-07 ne fixe pas :

- métier Creuser / Remblayer / Aplanir / passes / tolérances / largeurs / trajectoires / quantités de terre (I1) ;
- autorité graphe ou readiness (A1, A4) ;
- décision SitePrep (I2) ;
- autorité hauteur (C-01) ;
- statut En service / Achevé du chantier (I3) ;
- règles C-11 / C-12 complètes ;
- ouverture de C-06 (A5) ;
- réactivation Case B ;
- correction des dettes §23 dans cette rédaction.

---

## 22. Dépendances

| Direction | Éléments |
| --- | --- |
| **Amont** | **C-04** · **C-06\*** (fermé) |
| **Aval** | **C-08** · **C-12** · **C-20** |
| **Complémentaire** | C-01 · C-02 · C-05 · C-11 · C-13\* · DG-04 · DG-11.6 |

---

## 23. Dettes et écarts d’implémentation connus

Constats runtime — **pas** des règles souhaitées ; **non corrigés** ici :

| Dette | Nature |
| --- | --- |
| InstantMode | Masque déplacement et durée dans smokes / gates (écart vs C1/C2 produit) |
| Effets à Verify | Nombreuses opérations appliquent les effets seulement en Verify |
| Terraform pulses | `ApplyBrushAt` ×N au Verify ; Progress Execute sans effet relief |
| DisplayName Raise/Lower | Sémantique métier dans l’agent — non architecture définitive (I1) |
| ReleaseClaim → Progress=0 | Écart avec D5 / F1 (perte de progression utile) |
| Interruption | Traitement Block/Fail / reprise insuffisamment formalisé côté agent |
| Transport / Progress | Peut Complete sans Progress finalisé — écart E5 |
| MarkConstructionComplete | Appel depuis l’agent — frontière C-13\* / I3 à clarifier ultérieurement |
| Capacités fallback | Worker/Terraform hardcodés si DA vide — **dette à préserver** ; ne pas ouvrir C-06 (A5) |
| Deliver après Verify | Transition d’orchestration opaque hors Transport |

---

## 24. Points ouverts / hors périmètre

Aucun arbitrage nouveau. Restent ouverts :

- détails d’interruption / reprise **par métier** ;
- critères spécialisés de résultat (surtout C-08) ;
- API d’exécution métier exactes non encore contractualisées ;
- table exhaustive des causes d’échec ;
- transport avancé (C-12) ;
- extensions capacités / roster (C-06\* — non ouvert ici, A5) ;
- réactivation Case B ;
- campagne de preuves produit ciblées post-VALIDÉ.

---

## 25. Couverture des 47 décisions

| Bloc | Décisions | Lettres | Section(s) principales |
| --- | --- | --- | --- |
| A | A1–A5 | C,C,B,B,C | §1, §2.A, §4, §20 |
| B | B1–B5 | B×5 | §2.B, §5–§7 |
| C | C1–C5 | B×5 | §2.C, §8–§9, §19 |
| D | D1–D5 | B×5 | §2.D, §10–§11 |
| E | E1–E5 | C,B,B,B,B | §2.E, §12–§13 |
| F | F1–F5 | B×5 | §2.F, §14–§15 |
| G | G1–G4 | B×4 | §2.G, §15–§16 |
| H | H1–H4 | B,A,B,B | §2.H, §17 |
| I | I1–I5 | B×5 | §2.I, §12, §20 |
| J | J1–J4 | B×4 | §2.J, §18–§19 |

**Total : 47 / 47.**

Contrôle de clôture :

- audit indépendant final : **PASS** (47/47) ;
- validation humaine : **acquise** ;
- dettes = constats (§23) ;
- frontières préservées ;
- Case B **suspendu** ;
- statut **VALIDÉ**.

---

## 26. Statut

| État | Valeur |
| --- | --- |
| Document | `CONTRATS/C-07_AUTONOMIE_UNITE_AGENT_GENERIQUE.md` |
| Statut | **VALIDÉ** |
| Règle officielle | **Oui** — validation humaine ; audit indépendant final 47/47 PASS |
| Décisions | **47 / 47** (A1–J4) |
| Compteur global | **5 / 16** (C-03 et C-06 hors dénominateur) |
| Case B | **Suspendu** |

---

*Fin C-07 — VALIDÉ. C-03 et C-06 demeurent addenda fermés. Case B demeure suspendu. Aucune implémentation ni C-08 démarrés par cette clôture.*
