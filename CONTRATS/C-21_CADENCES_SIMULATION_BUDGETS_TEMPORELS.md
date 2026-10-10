# C-21 — Cadences de simulation et budgets temporels

| Champ | Valeur |
| --- | --- |
| **ID** | C-21 |
| **Nom** | Cadences de simulation et budgets temporels |
| **Statut documentaire** | **VALIDÉ** — validation humaine explicite ; audit final PASS ; contrat de conception uniquement ; O6, P9, C-17 Q8, R6, S14 et O-FREQ / O-OVER / O-EXC / O-INST / O-SCALE conservés ouverts |
| **Profondeur** | Fondamentale (registre) — **partielle** sur les chiffres (volontairement ouverts) |
| **Ordre de rédaction** | 21 |
| **Nécessité** | **Requise** au compteur 16. `PARTIEL` dans le registre = couverture actuelle (principes DG-00.5 / 00.6), **pas** une facultativité |
| **Bloquant** | Oui — avant de déclarer un **scale** de simulation (registre). **N’invalide pas** S3 / ODC-F2–F8 |
| **Dépendances amont (registre)** | **C-00** = DG-00 (pas de contrat dédié) · **C-02** `VALIDÉ` |
| **Voisinage opérationnel** | **00.5.T1–T5** · **00.5.X1–X3** · **00.6.M3 / 00.6.F2 / P3** · C-02 E1–E3 · C-07 (métier agent, InstantMode) · C-04 (graphe de tâches) · C-15 / C-16 / C-17 / C-18 / C-19 / C-20 (renvois de cadence, **chiffres encore ouverts**) |
| **Références** | Registre C-21 · suivi C-21 · DG-00.5 / 00.6 · C-02 E1–E3 · cadrage accepté T1 + B1–B8 · ETAT / REGLES §7bis |

Ce document formalise le **cadrage temporel déjà accepté** (titre T1 et orientations B1–B8).  
Il n’invente aucune règle supplémentaire.  
Il constitue la **règle officielle de conception** C-21 après validation humaine explicite.  
La clôture est **documentaire**. Elle **n’autorise pas**, à elle seule, l’implémentation d’un scheduler, de Hertz, de budgets runtime, ni d’une simulation écologique, hydrologique ou de sol.

**Case B** demeure **suspendu**.  
**ODC-F9** n’est **pas** démarré.  
**C-15**, **C-16**, **C-17**, **C-18**, **C-19** et **C-20** demeurent **VALIDÉ** comme contrats de **conception**. Leurs points ouverts de cadence (O6, P9, C-17 Q8, R6, S14, cadence UX) restent **ouverts**.  
Les addenda C-03\* · C-06\* · C-09\* · C-10\* · C-13\* restent **fermés**.

Aucun système de cadence C-21 n’existe dans le runtime actuel. Ce contrat **ne le présente pas** comme implémenté.

---

## 1. Identité et finalité

C-21 est le contrat des **règles temporelles transversales** de GardenFervor (B1).

Le titre canonique est **Cadences de simulation et budgets temporels** (T1).  
Les intitulés de fiche « Simulation / fréquences / perf » et « Simulation / fréquences » désignent le même contrat ; ils ne le remplacent pas.

C-21 **cadre le temps d’exécution**. Il **ne possède pas** les vérités de données ni le métier des agents (B4).

**Cadencer** consiste à dire **quand**, **selon quel mode**, et **sous quelle contrainte de calcul** une couche déjà propriétaire peut avancer une simulation, sans créer la vérité simulée, sans imposer un tick universel, et sans figer un chiffre arbitraire (B1, B3, B6).

Niveau de garantie de ce contrat :

- formaliser le **périmètre** et les **frontières** ;  
- distinguer **fréquence de simulation**, **progression temporelle** et **FPS** (B2) ;  
- rendre auditable ce que C-21 **autorise comme cadre**, **cite** et **n’exige pas** ;  
- **ne pas** figer Hertz, période, quota de cellules, budget milliseconde, seuil de drop, ni API C++.

Les identifiants **T1** et **B1–B8** ci-dessous sont le **cadrage accepté**, pas un second Design Gate.

---

## 2. Référentiel des décisions utilisées

### 2.1 Cadrage accepté (questionnaire / orientations C-21 — pas de nouvelle conception)

| # | Contenu accepté |
| --- | --- |
| **T1** | Titre **Cadences de simulation et budgets temporels**. |
| **B1** | C-21 définit les règles temporelles **transversales** : modes d’exécution, cadences, planification (au sens **ordonnancement temporel**, ≠ graphe C-04) et budgets de **calcul**. |
| **B2** | Distinguer **fréquence de simulation**, **progression temporelle** et **FPS**. Ce ne sont pas la même grandeur et elles ne se substituent pas. |
| **B3** | Autoriser des **stratégies adaptées** aux besoins des couches. **Ne pas** imposer de tick universel. |
| **B4** | C-21 **n’absorbe pas** C-02 (dirty / événementiel / cellules), C-07 (métier des agents) ni les contrats de **vérité de données**. |
| **B5** | Le cadre s’applique aux **systèmes futurs** sans inventer leurs fréquences. |
| **B6** | Principes de **mesure** et de **justification** des budgets. **Aucun** chiffre arbitraire. |
| **B7** | Encadrer les **dépassements** sans compromettre **silencieusement** la cohérence physique, écologique ou métier. |
| **B8** | Préparer une **montée en charge mesurable**. **Ne pas** promettre des performances non démontrées. |

### 2.2 Sources déjà VALIDÉES (lues, non réécrites)

| Source | Reprise pour C-21 |
| --- | --- |
| **00.5.T1** | Temps réel RTS. Pas d’accélération globale au fondateur. Pause solo = interface, pas mode de simulation. |
| **00.5.T2** | Trois **ordres** de durée (court / moyen / long). **Valeurs chiffrées** encore À DÉFINIR — C-21 ne les invente pas. |
| **00.5.T3** | Rythme différencié (production, chantiers, recherche, écologie). Effets écologiques perceptibles en session. |
| **00.5.T4** | **Pas de tick universel.** Fréquence adaptée : rapide (interaction / déplacement), événementielle (chantiers / production), basse (sol / écologie / végétation). |
| **00.5.T5** | Écologie perceptible en session ; maturation complète éventuellement plus longue. |
| **00.5.X1** | Modes **cumulables** par couche (simulé réellement + fréquence / agrégation / événementiel selon la couche). Classification **citée**, non rouverte. |
| **00.5.X2 / X3** | Hors-périmètre fondateur et règle d’or de simulation : C-21 ne les élargit pas. |
| **00.6.M3** | Outils : événements, seuils, dirty/local, fréquences adaptées, états discrets. |
| **00.6.F2** | « Simulé réellement » = vérité capable de conséquences, **pas** calcul chaque frame. |
| **00.6.P3** | Compatible temps réel via fréquences adaptées / dirty local. Validation technique définitive = **mesure en contexte réel**. **Aucun budget numérique arbitraire figé au Design Gate.** |
| **00.6.V2** | Détails de tick **cachés** au joueur par défaut. C-21 ne les expose pas comme UX. |
| **C-02 E1** | Traitement **localisé** privilégié ; pas de scan global permanent ; exception globale seulement si un contrat l’exige. |
| **C-02 E2** | **Pas** de tick spatial global permanent. Événementiel / localisé privilégié. Balayage périodique exceptionnel seulement si un contrat le justifie. |
| **C-02 E3** | Maîtrise des coûts ; **pas** de max universel de cellules par événement figé dans C-02. |
| **REGLES §7bis** | Simulation par cellules + dirty ; **pas** de scan monde entier par tick. |
| **C-15 F / O6 · C-16 H2 / P9 · C-17 Q8 · C-18 R6 · C-19 S14 · C-20** | Renvoient les **valeurs** de cadence / Hertz / temporisation à C-21. C-21 **accepte le renvoi** et **laisse les chiffres ouverts**. |

C-21 **ne rouvre** aucun de ces textes.

---

## 3. Portée d’un `VALIDÉ`

Ce contrat est **`VALIDÉ`**. Il reste un **contrat de conception**.

Un `VALIDÉ` C-21 **n’autorise pas**, à lui seul :

- d’implémenter un scheduler, un ticker global, des Hertz ou des budgets runtime ;  
- d’attribuer une période chiffrée à l’eau, au sol, à l’écologie, à la recherche ou à l’UX ;  
- d’implémenter C-15 / C-16 / C-17 / DG-07 / persist / HUD DG-13 ;  
- de modifier InstantMode, le graphe de tâches ou le Dirty spatial ;  
- de modifier `designGate.js` ;  
- de déclarer un scale perf **shipping**.

La **liste** des paramètres ultérieurs (§12.2) est un recensement. Elle **n’est pas** une table de valeurs.

---

## 4. Trois grandeurs distinctes (B2)

C-21 **interdit** de confondre :

| Grandeur | Sens dans ce contrat | Ce que ce n’est pas |
| --- | --- | --- |
| **Fréquence de simulation** | Rythme auquel une **couche propriétaire** est **autorisée** à recalculer ou avancer sa vérité | Ni le FPS, ni la durée gameplay d’une tâche |
| **Progression temporelle** | Avance du **temps de jeu** dans une couche (durée d’une tâche, d’un chantier, d’une maturation) | Ni le tick moteur, ni le budget CPU |
| **FPS** | Cadence de **présentation / frame** | Ni la vérité simulée, ni la preuve qu’une couche a avancé |

Conséquences obligatoires (B2) :

1. Un frame rendu **ne prouve pas** qu’une couche a simulé.  
2. Une couche peut avancer **sans** tourner à chaque frame (`00.6.F2`).  
3. Raccourcir une durée métier (progression) **n’est pas** augmenter le FPS.  
4. `InstantMode` appartient au **métier C-07** (C2 / J3 : accélération de test ; masque **durée et déplacement** ; ≠ preuve produit à lui seul). C-21 peut le **classer** comme mode de progression temporelle ; il **ne redéfinit pas** ses règles d’agent.

---

## 5. Responsabilités de C-21 (B1)

C-21 **possède** :

1. la **classification** des modes d’exécution **temporels** (événementiel, périodique adapté, exception globale justifiée, immédiat / temps réel) — **distincte** de la classification des couches `00.5.X1`, citée et **non rouverte** ;  
2. le **cadre** de cadence par **famille de couches**, sans chiffre (B3, B5) ;  
3. la **planification temporelle** = **quand** une couche **peut** consommer du travail de simulation (ordonnancement), distincte du **quoi** (C-04, propriétaires) ;  
4. les **principes** de budgets de calcul : mesure, justification, dépassement (B6, B7) ;  
5. le **vocabulaire** qui sépare fréquence, progression et FPS (B2) ;  
6. l’exigence qu’une montée en charge se **démontre**, pas qu’elle se déclare (B8).

C-21 **n’écrit pas** hauteur, cellules, tâches, stocks, eau, sol, végétation, déblocages, save ou HUD.

---

## 6. Modes et stratégies — pas de tick universel (B3)

### 6.1 Interdiction

Il **n’existe pas** de tick universel GardenFervor (`00.5.T4`, C-02 E2, REGLES §7bis).  
C-21 **n’en crée pas**.

### 6.2 Stratégies autorisées (cadre, pas implémentation)

Les stratégies sont **cumulables** et **adaptées à la couche** (`00.5.X1`, B3) :

| Stratégie | Usage de principe | Interdit d’en déduire |
| --- | --- | --- |
| **Événementielle / dirty** | Réagir à un signal propriétaire ou à un Dirty C-02 | Qu’un Dirty **est** déjà un recalcul métier (C-02 / C-16 E2) |
| **Périodique adaptée** | Basse fréquence pour couches lentes (sol / éco / eau au sens X1) | Un Hertz figé |
| **Immédiate / interaction** | Déplacement, saisie, lecture d’accès au moment d’agir | Un tick monde à 60 Hz |
| **Exception globale** | Seulement si un contrat l’exige (C-02 E1–E2) | Un scan monde par frame |

C-21 **peut**, plus tard, **autoriser** un balayage périodique exceptionnel au titre de E2. Il **ne l’active pas** ici et **n’en fixe pas** la période.

### 6.3 Planification temporelle ≠ C-04

« Planification » dans B1 signifie : **ordonnancement du droit de calculer**.  
Cela **n’est pas** :

- le graphe de tâches, la readiness ou le claim (**C-04**) ;  
- l’affectation d’une unité (**C-07**) ;  
- le choix d’une intention joueur.

---

## 7. Frontières (B4)

| Domaine | Autorité | C-21 |
| --- | --- | --- |
| Dirty, cellules, queries spatiales | **C-02** | Peut **consommer** le fait qu’un Dirty existe pour **autoriser** un travail ; ne définit pas les canaux ni la grille |
| Métier agent, InstantMode, cycle Seek→Deliver | **C-07** | Classe le mode temporel ; **ne change pas** les règles d’agent |
| Graphe / dépendances / Blocked | **C-04** | N’invente pas de tâche « tick » |
| Hauteur / relief | **C-01** | Signale éventuellement qu’un travail terrain a un coût ; n’écrit pas le relief |
| Eau / sol / végétation / éco | **C-15 / C-16 / C-17** | Cadre de cadence **futur** ; **pas** les vérités, seuils ni formules |
| Recherche / déblocages | **C-18** | R6 (Hertz recherche) **reste ouvert** |
| Politique persist | **C-19** | Temporisations save **ouvertes** (S14) |
| Présentation / HUD | **C-20** | Cadence d’affichage ≠ fréquence de simulation (B2) |
| Identité / invariants | **DG-00 / C-00** | Cités, non recopiés en second contrat |
| Rendu M4 | **C-23 / vendor** | FPS de présentation, pas vérité |

---

## 8. Couches futures — cadre sans fréquences inventées (B5)

C-21 s’applique aux couches **déjà conçues** et à celles **pas encore simulées**.

Pour une couche future (eau runtime, sol runtime, éco, infra F9, etc.) :

1. le **propriétaire de vérité** reste le contrat de données ;  
2. C-21 fournit seulement le **droit** d’avoir une stratégie temporelle **parmi** §6.2 ;  
3. la **première valeur chiffrée** (période, Hertz, quota) exige une **mesure** et une **justification** (B6) — elle n’est **pas** écrite ici ;  
4. l’absence de chiffre **n’autorise pas** à inventer un défaut « raisonnable » dans un autre contrat.

Les principes X1 déjà VALIDÉS (eau / sol / éco = fréquence réduite + agrégé ; unités = fréquence adaptée ; chantiers = événementiel) sont des **orientations de famille**, pas des périodes.

---

## 9. Budgets de calcul — mesure et justification (B6)

Un **budget** C-21 est une **contrainte de travail de calcul** (temps CPU / volume de travail par fenêtre), **pas** une ressource économique.

Règles obligatoires :

1. **Aucun** chiffre n’est officiel tant qu’il n’est pas **mesuré** en contexte réel (`00.6.P3`) et **justifié** par un effet gameplay, une cohérence de couche ou une viabilité observée.  
2. Une constante de code, un timeout de gate ou un `AddTicker` de smoke **n’est pas** un budget C-21.  
3. Un budget se déclare avec au minimum : couche concernée, grandeur (temps ou volume), fenêtre, **moyen de mesure**, critère de succès, et ce qui se passe en dépassement (B7).  
4. C-02 E3 reste : pas de max universel de cellules figé « pour faire propre ».

C-21 **n’écrit aucun** milliseconde, Hertz, ni quota.

---

## 10. Dépassements (B7)

Si un travail de simulation **dépasse** un budget **un jour justifié** :

1. le dépassement doit être **observable** pour le diagnostic technique (pas nécessairement pour le joueur — `00.6.V2`) ;  
2. il est **interdit** de rattraper en silence en :  
   - sautant une cohérence **physique** (relief / accès) ;  
   - sautant une cohérence **écologique** (état actuel / cible) ;  
   - sautant une cohérence **métier** (tâche, stock, SiteReady, lifecycle) ;  
3. les stratégies admissibles **de principe** sont : reporter le surplus à une fenêtre suivante, réduire le **volume** traité (local / dirty), ou **signaler** l’incapacité ;  
4. **choisir** laquelle, et avec quels seuils, reste **ouvert** (§12). C-21 pose l’interdiction du silence, pas l’algorithme.

Un drop de FPS **n’autorise pas** à corrompre une vérité propriétaire.

---

## 11. Montée en charge (B8)

C-21 **prépare** un scale mesurable :

- plus de cellules dirty, plus de couches actives, plus d’unités **peuvent** exiger des stratégies §6.2 plus strictes ;  
- la preuve est une **mesure** avant / après, sur un contexte déclaré ;  
- **aucune** cible de FPS, de nombre d’unités ou de km² n’est promise ici.

S3 / ODC-F3–F8 **ne sont pas** une preuve de scale C-21.

---

## 12. Principes obligatoires / paramètres ultérieurs / preuves / ouverts

### 12.1 Obligatoires dès ce contrat

- T1, B1–B8.  
- Séparation B2.  
- Pas de tick universel (B3).  
- Frontières B4.  
- Pas de chiffre arbitraire (B6).  
- Pas de dépassement silencieux qui casse une cohérence (B7).  
- Pas de promesse de perf non mesurée (B8).

### 12.2 Paramètres à déterminer ultérieurement (volontairement ouverts)

| Paramètre | Pourquoi ouvert |
| --- | --- |
| Hertz / périodes par couche | B5, B6, O6 / P9 / C-17 Q8 / R6 |
| Quotas de cellules ou de jobs par fenêtre | C-02 E3 + B6 |
| Budgets ms / frame ou / seconde | `00.6.P3` |
| Seuil et politique fine de dépassement | B7, choix non tranché |
| Accélération globale | Interdite au fondateur (`00.5.T1`) ; également hors périmètre fondateur (`00.5.X2`) ; hors C-21 fondateur |
| Cadence UX / debounce save | C-20 / C-19 S14 — valeurs non fixées |
| Hertz d’une activité de recherche | C-18 R6 |

### 12.3 Preuves encore nécessaires (après implémentation autorisée — pas maintenant)

| Preuve | Ce qu’elle devrait montrer |
| --- | --- |
| Mesure de cadence | Une couche avance **sans** tick universel, selon sa stratégie |
| Mesure de budget | Un budget justifié est **respecté ou signalé** (B7) |
| Non-confusion B2 | FPS stable ≠ simulation avancée ; InstantMode ≠ Hertz |
| Scale | Un contexte plus chargé **mesuré**, pas déclaré |
| Non-régression vérité | Un report / drop n’a pas inventé ni effacé une vérité propriétaire |

Aucune de ces preuves n’existe aujourd’hui au titre C-21.

### 12.4 Sujets explicitement ouverts

| # | Sujet | Pourquoi ce n’est pas tranché |
| --- | --- | --- |
| **O-FREQ** | Première table chiffrée | B6 ; renvois amont ouverts |
| **O-OVER** | Politique fine de dépassement | B7 pose l’interdit, pas l’algo |
| **O-EXC** | Si / quand un balayage global exceptionnel est justifié | C-02 E1–E2 ; C-21 peut l’autoriser plus tard, pas ici |
| **O-INST** | Articulation normative InstantMode ↔ progression C-21 | C-07 reste propriétaire ; C-21 ne l’étend pas |
| **O-SCALE** | Critères chiffrés de « scale atteint » | B8 interdit la promesse |
| O1–O9, P1–P10, Q1–Q12, R1–R8, R11 | Points des contrats amont | **Inchangés** |

---

## 13. Non-objectifs

C-21 ne fixe pas :

- Hertz, périodes, ms, quotas, seuils ;  
- solveurs, algorithmes d’eau / sol / éco ;  
- vérités de données ;  
- métier agent, graphe de tâches, SitePrep, lifecycle ;  
- layout HUD, wording, techno UI (C-20) ;  
- politique persist / F1 / DG-07 ;  
- Case B, addenda, ODC-F9 ;  
- un scheduler « déjà là » dans le dépôt.

---

## 14. État réel du dépôt (constat — pas une cible)

Constat d’audit, **non corrigé** ici :

1. **Pas** de module C-21 / Hertz / budget officiel.  
2. Dirty spatial **événementiel** (`MarkDirty*` / `ConsumeDirtyCells`) — autorité **C-02**.  
3. `InstantMode` utilisé dans des **gates** — autorité **C-07**, dette de preuve temps réel déjà signalée ailleurs.  
4. Tickers `FTSTicker` dans des **gates** = harness de test, **pas** une cadence C-21.  
5. Eau / sol / éco : **conception** C-15/16/17 ; stubs Spatial ≠ simulation cadencée.  
6. `CONTRATS/C-17_VEGETATION_ECOSYSTEMES.md` encore **non suivi Git** (`??`).  
7. Compteur officiel **15/16** ; C-21 **NON COMMENCÉ** au suivi jusqu’à l’étape 11.

C-21 **ne corrige** aucun de ces écarts.

---

## 15. Invariants

1. Titre : **Cadences de simulation et budgets temporels** (T1).  
2. C-21 = règles temporelles transversales (B1).  
3. Fréquence ≠ progression ≠ FPS (B2).  
4. Pas de tick universel ; stratégies adaptées (B3).  
5. C-02 / C-07 / vérités de données restent propriétaires (B4).  
6. Couches futures : cadre sans fréquences inventées (B5).  
7. Budget = mesure + justification ; pas de chiffre arbitraire (B6).  
8. Dépassement : pas de cohérence silencieuse sacrifiée (B7).  
9. Scale = mesurable ; pas de perf promise (B8).  
10. Conception ≠ implémentation.

---

## 16. Hors autorisation

Ce contrat **VALIDÉ** **n’autorise pas** :

- l’implémentation d’un scheduler, de Hertz ou de budgets ;  
- la fermeture de O6 / P9 / C-17 Q8 / R6 / S14 ;  
- la modification du Design Gate, du registre, du suivi, de l’historique, du Hub ou des contrats voisins ;  
- la correction des constats §14 ;  
- l’ouverture d’un autre contrat.

---

## 17. Correspondance cadrage

| Décision | Section |
| --- | --- |
| T1 | §1, en-tête |
| B1 | §1, §5, §6.3 |
| B2 | §4 |
| B3 | §6 |
| B4 | §7 |
| B5 | §8 |
| B6 | §9 |
| B7 | §10 |
| B8 | §11 |

---

## 18. Vérification documentaire

| Critère | Attendu |
| --- | --- |
| Fidélité | T1 + B1–B8 repris ; **aucune** Hertz inventée |
| Statut | **VALIDÉ** — conception uniquement |
| DG / C-02 | Cités, non réécrits |
| Runtime | Aucun scheduler présenté comme existant |
| Voisins | Non modifiés |
| Chiffres | Tous ouverts (§12.2) |

Validation humaine **finale** enregistrée. Clôture **documentaire** (étape 10).  
Suivi / compteur / Hub restent à l’étape 11.

---

*Fin C-21 — VALIDÉ. La clôture est documentaire. Case B demeure suspendu. Addenda fermés. O6, P9, C-17 Q8, R6, S14 et O-FREQ / O-OVER / O-EXC / O-INST / O-SCALE conservés. Aucune implémentation de cadence ni contrat suivant démarrés par cette clôture. Le suivi / compteur restent à l’étape 11.*
