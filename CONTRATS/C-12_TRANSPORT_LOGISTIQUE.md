# C-12 — Transport / logistique

| Champ | Valeur |
| --- | --- |
| **ID** | C-12 |
| **Nom** | Transport / logistique |
| **Statut documentaire** | **VALIDÉ** — validation humaine explicite ; audit indépendant final 25/25 PASS ; dettes d’implémentation / preuves partielles conservées (§17) |
| **Profondeur** | Détaillée (registre) |
| **Ordre de rédaction** | 12 |
| **Bloquant** | Oui (au-delà S3 — registre) |
| **Dépendances amont** | **C-07** · **C-10\*** (addendum **fermé** — G3) · preuves haul S3 / ODC-F7 disponibles |
| **Références** | Registre C-12 · DG-06 · 00.5.N4 · C-04 · C-07 I5/E5 · C-08 H4 · C-11 E1 · TaskTypes Transport · UnitTaskAgent · PhysicalEconomy · décisions humaines A1–G3 (25) |

Ce document formalise les **25 décisions humaines C-12** reprises **sans modification de sens**.  
Il n’invente aucune règle supplémentaire.  
Il constitue la **règle opérationnelle** C-12 après validation humaine et inscription **VALIDÉ** dans le suivi.  
Il ne constitue **pas** une autorisation d’implémentation complète de la logistique, d’ouverture de C-09/C-10, ni une réactivation de Case B.

**Case B** demeure **suspendu** jusqu’à décision humaine explicite de réouverture.

Référentiel des lettres validées (identité) :

```text
A1 A2 A3 A4
B1 B2 B3 B4
C1 C2 C3 C4
D1 D2 D3 D4
E1 E2 E3
F1 F2 F3
G1 G2 G3
```

Le **sens opératoire** de chaque décision est celui de §2 ci-dessous (référentiel d’autorité).

---

## 1. Identité et finalité

C-12 est le contrat des **règles métier du transport et de la logistique** au-delà de la preuve élémentaire A→B : demandes, cycle matière, accès, progression, interruptions, observabilité et frontières (A1).

Il s’intègre au graphe **C-04** et à l’exécution **C-07**, sans les remplacer. Il s’appuie sur les réservations **C-11** pour le prélèvement concurrentiel.

---

## 2. Décisions validées (source de vérité)

Les **25** décisions suivantes sont reprises **fidèlement**.

### A — Périmètre et modèle logistique

| # | Décision |
| --- | --- |
| **A1** | C-12 formalise les règles métier du transport et de la logistique **au-delà** de la preuve élémentaire A→B. Il distingue les capacités **actuellement démontrées** des règles contractuelles **cibles** et des fonctions **restant à implémenter**. La preuve actuelle **ne vaut pas** validation complète des réseaux, de l’accès ou de la gestion de flux multiples. |
| **A2** | Modèle de référence : demande identifiée → affectation d’une unité compatible → accès à la source → **chargement confirmé** → déplacement → **dépôt réel** à destination → **confirmation du résultat**. Chaque transport identifie au minimum : quantité, ressource, source, destination, bénéficiaire. Le **déplacement visuel seul** ne prouve pas un transfert de matière. |
| **A3** | C-12 définit l’**utilisation logistique** des accès, itinéraires, réseaux et capacités disponibles. **C-14** reste responsable du **cycle de vie** des infrastructures (construction, usage, démontage, récupération). C-12 peut reconnaître un accès impossible **sans** prendre en charge la construction de l’infrastructure manquante. |
| **A4** | Les règles de conception validées dans **DG-06**, notamment réseaux et saturation **N4**, constituent la référence. C-12 définit leur place dans le fonctionnement logistique **sans inventer** de seuils, formules ou valeurs d’équilibrage absents des décisions de conception. Distinguer la règle de conception de sa **mise en œuvre effective**. |

### B — Demandes, tâches, réservations et priorités

| # | Décision |
| --- | --- |
| **B1** | Une demande provient d’un **projet**, d’une **tâche** ou d’un **système métier autorisé**. Elle identifie au minimum : ressource, quantité demandée, source, destination, bénéficiaire. Les unités **ne déplacent pas** arbitrairement les stocks. |
| **B2** | Le transport s’intègre au graphe de tâches **C-04**. C-12 définit les **conditions métier** propres au transport ; C-04 reste propriétaire du cycle de vie, des dépendances et des transitions d’état. **Pas** de second système indépendant de gestion des tâches. |
| **B3** | Toute matière à prélever suit les règles de réservation **C-11**. Une réservation **ne vaut pas** chargement : le prélèvement physique intervient uniquement au **chargement réel confirmé**. Les réservations conservent les exigences C-11 : **tout ou rien**, ou refus. Les demandes partielles sont **découpées explicitement** plutôt que d’affaiblir l’atomicité. |
| **B4** | Les conflits de **réservation** relèvent de **C-11**. Les priorités propres aux **flux et réseaux** relèvent des règles de conception **DG-06**. Ne pas inventer de hiérarchie supplémentaire pour les situations non déjà couvertes. Priorité d’un stock et priorité d’un flux logistique **ne sont pas** automatiquement identiques. |

### C — Matière, chargement et livraison

| # | Décision |
| --- | --- |
| **C1** | Le stock source est diminué lorsque le **chargement réel** est effectué et **confirmé**. Une réservation seule **ne constitue pas** un prélèvement physique. |
| **C2** | Une fois chargée, la matière est un **chargement transporté par l’unité**. Elle n’est plus disponible dans le stock source et **n’est pas encore** disponible dans le stock destination. Une même quantité ne peut pas être simultanément libre à la source, transportée et disponible à destination. |
| **C3** | La livraison est effective uniquement après **dépôt réel** et **confirmation** par le système métier responsable. L’arrivée de l’unité ou une animation **ne suffit pas**. |
| **C4** | Une demande peut être satisfaite en **plusieurs transports** lorsque les contraintes réelles l’exigent. Quantités livrées et restantes restent **traçables**. Le reliquat demeure à traiter jusqu’à satisfaction ou **invalidation explicite**. Chaque réservation respecte C-11 ; livrer en plusieurs fois **ne justifie pas** une réservation partielle silencieuse. |

### D — Capacités, compatibilité et accès

| # | Décision |
| --- | --- |
| **D1** | La capacité est une propriété **explicite** de l’unité ou de sa configuration, **lorsqu’elle est définie**. N’inventer **aucune** capacité numérique commune aux unités. |
| **D2** | Une unité ne transporte une ressource que si ses capacités et les données disponibles l’**autorisent**. Une compatibilité non définie **ne doit pas** être supposée silencieusement. |
| **D3** | Le modèle de base porte sur un transport **source→destination**. Relais, hubs et chaînes multi-étapes **peuvent** étendre le système, mais **ne sont pas imposés** comme fonctionnalités fondatrices sans décision et preuve supplémentaires. |
| **D4** | L’exécution requiert un **accès valide** à la source, à la destination et au parcours nécessaire selon les règles de circulation disponibles. Un accès devenu invalide doit être **signalé** ; le système **ne téléporte pas** l’unité et **ne considère pas** la livraison réussie par défaut. |

### E — Affectation et partage des moyens

| # | Décision |
| --- | --- |
| **E1** | **C-07** reste propriétaire de l’agent générique, de la sélection et de l’exécution des tâches. C-12 fournit les **exigences métier** propres au transport : capacité, compatibilité, source, destination et conditions logistiques. |
| **E2** | Unités, ressources et capacités logistiques sont **partagées selon leur état réel**. Un chantier ne dispose **pas** artificiellement d’une capacité indépendante des moyens effectivement disponibles. Conflits résolus selon **C-11** et **DG-06**, sans nouvelle hiérarchie implicite. |
| **E3** | La progression métier reflète les **actions et quantités réellement accomplies**. Le trajet parcouru **n’est pas** assimilé à une quantité livrée. La vérification du résultat métier **précède** la confirmation du succès ; **C-04** conserve la responsabilité de la **terminaison** de la tâche. |

### F — Interruptions, invalidations et récupération

| # | Décision |
| --- | --- |
| **F1** | Une interruption **conserve** l’état réel du transport, de l’unité et de son chargement. La demande est suspendue ou bloquée avec une **cause identifiable**, puis peut reprendre à partir de l’état réel lorsque les conditions le permettent. Pas de remise arbitraire à la source ni suppression des effets déjà réalisés. |
| **F2** | Une invalidation (destination / parcours) est **détectée et expliquée**. La solution est **réévaluée** par les systèmes compétents. Aucun retour à la source, choix automatique d’une autre destination ou échec définitif n’est **imposé universellement** sans règle validée. |
| **F3** | L’annulation suit **C-04** et les règles de libération **C-11**. La matière déjà chargée **ne disparaît pas** automatiquement : son état physique reste **traçable** jusqu’à une résolution explicite (réaffectation, dépôt ou autre issue autorisée). |

### G — Information, persistance et frontières

| # | Décision |
| --- | --- |
| **G1** | Exposer les informations nécessaires : demande, bénéficiaire, source, destination, quantité pertinente, état général, cause de blocage. Les détails internes des réservations restent soumis à la lisibilité **C-11**. Le joueur comprend pourquoi un transport avance, attend ou est bloqué **sans** tous les détails techniques. |
| **G2** | C-12 définit les **données logistiques** dont la cohérence doit être préservée (chargements en cours, états de transit). **C-19** demeure propriétaire du **mécanisme** de persistance. La reprise après sauvegarde ne doit **ni dupliquer ni perdre fictivement** la matière. Aucune sauvegarde complète n’est déclarée opérationnelle **sans preuve**. |
| **G3** | Frontières : **C-04** graphe/cycle de vie ; **C-05** WorkSite/SitePrep/`SiteReady` ; **C-07** agent/exécution ; **C-08** opérations métier matières/résultats ; **C-11** réservations/concurrence ; **C-12** transport/logistique ; **C-14** cycle de vie infrastructures ; **C-19** mécanisme persistance. **C-10** reste **fermé** malgré sa dépendance déclarée ; documenter les lacunes **sans** réouverture automatique ni invention de règles. |

---

## 3. Périmètre et exclusions

### 3.1 Inclus (A1, A2)

- demandes de transport autorisées et contenu minimal (B1) ;
- cycle métier chargement → transit → dépôt → confirmation (A2, C1–C3) ;
- intégration au graphe C-04 sans second runtime de tâches (B2) ;
- liaison aux réservations C-11 (B3, C4) ;
- capacité / compatibilité lorsqu’elles sont définies (D1, D2) ;
- accessibilité des trajets et signalement d’invalidité (D4) ;
- partage réel des moyens entre chantiers (E2) ;
- progression et preuves métier (E3) ;
- interruptions, invalidations, annulation avec chargement (F1–F3) ;
- observabilité agrégée (G1) ;
- invariants de cohérence pour persistance (G2) ;
- distinction preuve runtime ≠ règles cibles (A1, §17).

### 3.2 Exclus

| Domaine | Autorité |
| --- | --- |
| Cycle de vie / graphe / états de tâche | **C-04** (B2, E3, G3) |
| WorkSite / SitePrep / `SiteReady` | **C-05** (G3) |
| Agent générique / sélection / exécution | **C-07** (E1, G3) |
| Métier Terraform / besoins matière opération | **C-08** (G3) |
| Arbitrage concurrentiel des stocks | **C-11** (B3, B4, G3) |
| Cycle de vie des infrastructures | **C-14** (A3, G3) |
| Mécanisme de sauvegarde | **C-19** (G2, G3) |
| Ouverture C-09 / C-10 | **Interdite** (G3) |
| Case B / gameplay produit | **Suspendu** — hors ce contrat |

---

## 4. Vocabulaire et cycle d’un transport

| Terme | Sens dans C-12 |
| --- | --- |
| **Demande de transport** | Intention autorisée portant les champs de B1 / A2. |
| **Bénéficiaire** | Identité traçable pour qui le transport est effectué (A2, B1). |
| **Chargement confirmé** | Prélèvement physique réellement effectué ; diminue le stock source (C1). |
| **Transit / chargement porté** | Matière sur l’unité ; non libre à la source ; non disponible à destination (C2 ; aligné C-11 E1). |
| **Dépôt réel** | Transfert physique vers le stock destination, confirmé par le système métier (C3). |
| **Livraison effective** | Dépôt réel + confirmation métier — pas l’arrivée seule (C3). |
| **Reliquat** | Quantité restante d’une demande après livraisons partielles traçables (C4). |
| **Accès valide** | Source, destination et parcours conformes aux règles de circulation disponibles (D4). |
| **Progression métier** | Mesure des actions/quantités accomplies, distincte du trajet parcouru (E3). |

### 4.1 Cycle de référence (A2)

```text
Demande identifiée
    → Affectation unité compatible (C-07 + exigences C-12)
    → Accès source
    → Chargement confirmé (C1)
    → Déplacement
    → Dépôt réel destination
    → Confirmation résultat métier (C3)
```

Alignement conceptuel avec DG-06.5 (Ordonnancement → Chargement → Déplacement → Déchargement → Stockage → Retour) **sans** imposer ici des étapes non tranchées par les 25 décisions.

---

## 5. Demande et bénéficiaire (B1)

Une demande précise au minimum :

1. ressource ;  
2. quantité demandée ;  
3. source ;  
4. destination ;  
5. bénéficiaire.

Origine : projet, tâche ou système métier **autorisé** — pas un déplacement arbitraire d’unité (B1).

*Point ouvert :* formalisme exact de la structure de données de demande — non inventé ici.

---

## 6. Intégration au graphe C-04 (B2, E3)

- Les transports s’expriment comme tâches (ou ensembles de tâches) du graphe **C-04**.  
- C-12 fixe les **conditions métier** (chargement, dépôt, accès, progression).  
- **C-04** reste seul propriétaire des états, dépendances et de la **terminaison** (E3).  
- Pas de second scheduler de tâches parallèle (B2).

---

## 7. Réservation, prélèvement et concurrence C-11 (B3, B4, C1, C4)

| Règle | Décision |
| --- | --- |
| Prélever seulement après réservation conforme C-11 | B3 |
| Réservation ≠ chargement | B3, C1 |
| Atomicité C-11 (tout ou rien / refus) | B3 |
| Demandes partielles = découpes explicites de demandes/réservations | B3, C4 |
| Conflits de stock → C-11 | B4 |
| Priorités flux/réseaux → DG-06 (sans hiérarchie inventée) | B4, A4 |
| Stock et flux : priorités **non** automatiquement identiques | B4 |

---

## 8. Chargement, transit, dépôt et confirmation (C1–C3)

1. **C1** — Diminution stock source au chargement réel confirmé.  
2. **C2** — Chargement porté par l’unité ; exclusivité d’état (pas libre source + transit + disponible destination).  
3. **C3** — Livraison = dépôt réel + confirmation système métier compétent.

Invariant : pas de réussite fictive fondée sur le seul déplacement (A2, C3, E3).

---

## 9. Quantités, capacités, compatibilité et livraisons partielles (C4, D1–D3)

- **C4** — Plusieurs transports pour une même demande si contraintes réelles ; traçabilité livré/reliquat ; invalidation explicite pour clôturer le reliquat.  
- **D1** — Capacité = donnée explicite unité/configuration **si définie** ; aucune capacité numérique commune inventée.  
- **D2** — Compatibilité ressource ↔ unité seulement si autorisée par données ; pas de compatibilité universelle silencieuse.  
- **D3** — Base = source→destination ; hubs/relais = extension future non imposée au fondateur.

*Points ouverts :* valeurs numériques de capacité ; politique détaillée de découpe des lots ; règles fondatrices éventuelles pour hubs.

---

## 10. Accès, itinéraires, réseaux, saturation (A3, A4, D4)

- Utilisation logistique des accès / itinéraires / réseaux / capacités disponibles (A3).  
- Construction / lifecycle infrastructures → **C-14** (A3).  
- Accès invalide → **signaler** ; pas de téléportation ; pas de livraison réussie par défaut (D4).  
- DG-06 / N4 : référence de conception ; **pas** de seuils/formules inventés ; conception ≠ mise en œuvre (A4).  
- Saturation visible selon N4 (conséquence réelle) — sans inventer de métriques permanentes.

*Points ouverts :* seuils/formules de saturation opérationnels ; politique universelle de repli (retour source vs autre destination) — explicitement **non imposée** (F2).

---

## 11. Partage des moyens entre chantiers (E1, E2)

- Exigences transport fournies par C-12 ; affectation/exécution par **C-07** (E1).  
- Moyens partagés selon état réel ; pas de capacité artificielle par chantier (E2).  
- Arbitrages via **C-11** (stocks) et **DG-06** (flux/réseaux) — pas de 3ᵉ hiérarchie implicite (E2, B4).

---

## 12. Progression, preuves et terminaison (E3, C3)

- Progression = actions/quantités accomplies, **pas** distance parcourue seule (E3).  
- Vérification résultat métier avant succès (E3, C3).  
- Terminaison de tâche = **C-04** (E3).

---

## 13. Interruption, invalidation, annulation (F1–F3)

| Situation | Règle |
| --- | --- |
| Interruption en trajet | Conserver état réel (unité + chargement) ; suspendre/bloquer avec cause ; reprise depuis l’état réel (F1) |
| Destination / parcours invalide | Détecter + expliquer ; réévaluer via systèmes compétents ; pas de politique universelle inventée (F2) |
| Annulation avec chargement | Suivre C-04 + libérations C-11 ; matière chargée reste traçable jusqu’à résolution explicite (F3) |

---

## 14. Informations joueur (G1)

Exposer de façon compréhensible :

- demande ;  
- bénéficiaire ;  
- source / destination ;  
- quantité pertinente ;  
- état général ;  
- cause de blocage.

Détails fins de réservation : règles C-11 / lisibilité — cachés par défaut lorsque non nécessaires (G1).

---

## 15. Persistance — frontière C-19 (G2)

| Responsabilité | Autorité |
| --- | --- |
| Données à préserver (chargements, états de transit, cohérence matière) | **C-12** (invariant métier) |
| Mécanisme de sauvegarde / chargement | **C-19** |
| Interdiction | Dupliquer ou perdre fictivement la matière à la reprise |
| Déclaration « save opérationnelle » | **Interdite** sans preuve correspondante |

---

## 16. Responsabilités et frontières (G3)

| Contrat | Responsabilité | Relation à C-12 |
| --- | --- | --- |
| **C-04** | Graphe, dépendances, cycle de vie, terminaison | Transport = tâches C-04 ; pas de 2ᵉ graphe |
| **C-05** | WorkSite, SitePrep, `SiteReady` | Manque logistique ≠ SitePrep |
| **C-07** | Agent, sélection, exécution | Consomme exigences C-12 (E1) |
| **C-08** | Opérations métier matières / résultats | Besoins/résultats ; transport approfondi ici (H4) |
| **C-11** | Réservations / concurrence stocks | Prérequis prélèvement ; transit non libre |
| **C-12** | Transport / règles métier logistiques | — |
| **C-14** | Lifecycle infrastructures | Accès manquant signalé ; construction hors C-12 |
| **C-19** | Mécanisme persistance | G2 |
| **C-10\*** | Stocks A/B (addendum) | **Fermé** ; lacunes documentées, pas de réouverture (G3) |

---

## 17. État réel de l’implémentation (lecture seule — ≠ règles cibles)

### 17.1 Mécanismes constatés

| Mécanisme | Nature |
| --- | --- |
| `EGardenFervorTaskType::Transport` + `SourceStockId` / `DestStockId` | Structure tâche |
| Capabilité Transport (U2) | Matching unités |
| Agent : Travel → `Withdraw` → Travel → `Deposit` (`LoadHaulFromSource` / `UnloadHaulAtDest`) | Exécution haul |
| Cargo `CarriedResource` / `CarriedAmount` | Transit porté par l’unité (pas stock PE destination) |
| Expansion HaulSpoil / HaulResource | LevelPad / WorkSite / cohort |
| `gf.Logistics.RuntimeGate` | Gate F7 |

### 17.2 Preuves

| Preuve | État |
| --- | --- |
| ODC-F7 (`Saved/ODC_F7_LogisticsGate.txt`) — PASS humain | **Partielle** — flux LevelPad / haul pit→pad |
| S3 Timber A→B (cohort / smokes) | **Partielle** — haul élémentaire |
| Réseaux / routes / blocking d’accès | **Manquante** (limites F7 explicites) |
| Arbitre priorité multi-projets / multi-flux | **Manquante** |
| Transfert atomique PE dédié | **Absent** (Withdraw+Deposit seulement) |
| Saturation N4 opérationnelle | **Non démontrée** (DG-06 / N4 = conception) |
| Hubs / multi-étapes | **Non imposés** (D3) — absents |
| Save/load chargements (G2) | **À démontrer** (C-19) |

Les règles §2–§15 sont des **invariants normatifs** ; le runtime peut être **en dette** sans les invalider (A1).

---

## 18. Dépendances, lacunes et points ouverts

| Direction | Éléments |
| --- | --- |
| **Amont opérationnel** | C-07 · preuves F7 / S3 · C-11 VALIDÉ |
| **Amont registre** | C-10\* — **fermé** (G3) ; lacune éventuelle = signalement séparé, pas réouverture |
| **Conception** | DG-06 · 00.5.N4 |
| **Aval / voisin** | C-14 · C-19 |

Aucun arbitrage nouveau. Restent **ouverts** s’ils ne sont pas tranchés par les 25 décisions :

- formalisme exact de la structure « demande » ;  
- valeurs numériques de capacité / compatibilité détaillée ;  
- seuils et formules de saturation opérationnelle ;  
- politique universelle de repli après invalidation de parcours (F2) ;  
- résolution détaillée matière chargée après annulation (catalogue d’issues autorisées) au-delà de F3 ;  
- hubs / relais multi-étapes (D3) ;  
- ouverture éventuelle de C-10 si lacune bloquante **signalée séparément** ;  
- implémentation gameplay ;  
- réactivation Case B.

---

## 19. Couverture des 25 décisions

| Bloc | Décisions | Section(s) principales |
| --- | --- | --- |
| A | A1–A4 | §2.A, §3, §4, §10, §17 |
| B | B1–B4 | §2.B, §5–§7 |
| C | C1–C4 | §2.C, §8–§9 |
| D | D1–D4 | §2.D, §9–§10 |
| E | E1–E3 | §2.E, §11–§12 |
| F | F1–F3 | §2.F, §13 |
| G | G1–G3 | §2.G, §14–§16, §18 |

**Total : 25 / 25 (A1–G3).**

Contrôle de clôture :

- audit indépendant final : **PASS** (25/25) ;  
- validation humaine : **acquise** ;  
- 0 décision nouvelle ;  
- frontières C-04 / C-05 / C-07 / C-08 / C-11 / C-14 / C-19 préservées ;  
- C-10 non ouvert ;  
- Case B **suspendu** ;  
- aucune valeur numérique / formule inventée ;  
- preuve F7 ≠ validation réseaux / multi-flux (A1) — dettes §17 conservées ;  
- statut **VALIDÉ**.

---

## 20. Statut

| État | Valeur |
| --- | --- |
| Document | `CONTRATS/C-12_TRANSPORT_LOGISTIQUE.md` |
| Statut | **VALIDÉ** |
| Règle officielle | **Oui** — validation humaine ; audit indépendant final 25/25 PASS |
| Décisions | **25 / 25** (A1–G3) |
| Compteur global | **8 / 16** (C-03, C-06, C-09, C-10, C-13 hors dénominateur) |
| Case B | **Suspendu** |

---

*Fin C-12 — VALIDÉ. C-03, C-06, C-09 et C-10 demeurent addenda fermés. Case B demeure suspendu. Aucune implémentation ni contrat suivant démarrés par cette clôture.*
