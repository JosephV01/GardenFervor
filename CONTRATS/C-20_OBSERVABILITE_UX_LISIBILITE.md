# C-20 — Observabilité / UX lisibilité

| Champ | Valeur |
| --- | --- |
| **ID** | C-20 |
| **Nom** | Observabilité / UX lisibilité |
| **Statut documentaire** | **VALIDÉ** — validation humaine explicite ; audit final PASS ; contrat de conception uniquement ; R7 C-18 et O1–O9 / P1–P10 / Q1–Q12 conservés ouverts |
| **Profondeur** | Hybride (X3) — **détaillée** sur les familles de X5 ; **secondaire** ailleurs |
| **Ordre de rédaction** | 20 |
| **Nécessité** | **Requise** au compteur 16 (X2). `PARTIEL` dans le registre décrit la **couverture actuelle** (DG-13 + C6), **pas** une facultativité |
| **Bloquant** | Oui — avant de déclarer une UX **produit** ou un HUD DG-13 **en service** (X9). **N’invalide pas** S3 / C6 |
| **Dépendances amont (registre)** | **C-04** · **C-07** · **C-09** — C-04 et C-07 sont **VALIDÉS** ; C-09\* demeure addendum **fermé** (cité, non ouvert) |
| **Voisinage opérationnel** | **DG-13** (13.1–13.5) · **C-11** (informations agrégées) · **C-18** (règle exprimable, R7) · **C-19** (S14, présentation save) · **C-21** (cadence, **non ouvert**) · PE / C6 (faits de preuve) |
| **Références** | Registre C-20 · suivi C-20 · DG-13.1–13.5 · `00.6` V1–V4, H1, P1 · C-04 F1/F2 · C-07 J1/J2 · C-11 §12 · C-18 13.1, Q6, Q19, R7 · C-19 S8, S14, §16 · ETAT C6 · cadrage C-20 X1–X10 · L1–L3 |

Ce document formalise le **cadrage observabilité / UX lisibilité déjà accepté** (décisions humaines X1–X10 et L1–L3).  
Il n’invente aucune règle supplémentaire.  
Il constitue la **règle officielle de conception** C-20 après validation humaine explicite.  
La clôture est **documentaire**. Elle **n’autorise aucune** implémentation (X4).

Trois plans sont **distingués** partout dans ce contrat :

1. **Politique de présentation** — ce que le joueur doit pouvoir comprendre, et selon quelle couche.  
2. **Comportement actuel vérifié** — HUD, smokes, Demo présents dans le dépôt.  
3. **Travaux UX futurs** — recensés, **non autorisés** par ce `VALIDÉ` documentaire (X4).

**Case B** demeure **suspendu**.  
**ODC-F9** n’est **pas** démarré.  
**C-21** demeure **non ouvert**.  
**C-19** demeure **VALIDÉ** comme contrat de **conception** ; persist runtime **OFF**.  
**C-15**, **C-16**, **C-17** et **C-18** demeurent **VALIDÉ** comme contrats de **conception**. Leurs points ouverts restent **inchangés**.  
Les addenda C-03\* · C-06\* · C-09\* · C-10\* · C-13\* restent **fermés**.  
S3 / C6 restent des **preuves de cohorte**, pas une UX produit DG-13.

---

## 1. Identité et finalité

C-20 est le contrat de l’**observabilité et de la lisibilité UX** de GardenFervor (X1).

Le titre canonique est **Observabilité / UX lisibilité**.  
Le titre court de fiche registre « Observabilité / UX » désigne le même contrat ; il ne le remplace pas (X1).

C-20 **présente**. Il **ne possède pas** les règles métier (X7).

**Présenter** consiste à rendre compréhensibles au joueur les faits établis par leurs systèmes propriétaires, selon leur importance et leur disponibilité, sans créer de vérité métier, imposer une technologie d’interface ni définir la cadence de mise à jour (L2).

Niveau de garantie de ce contrat :

- formaliser le **périmètre** et les **frontières** ;  
- rendre auditable ce que C-20 **présente**, **cite** et **n’exige pas** ;  
- imposer les champs de X10 ;  
- **ne pas** figer layout, widget, couleur, animation, techno UI, Hertz, wording HUD exact, ni API.

Les identifiants **X1–X10** et **L1–L3** ci-dessous sont le **cadrage accepté**, pas un second Design Gate.

---

## 2. Référentiel des décisions utilisées

### 2.1 Cadrage accepté (questionnaire C-20 — pas de nouvelle conception)

| # | Contenu accepté |
| --- | --- |
| **X1=A** | Titre **Observabilité / UX lisibilité**. |
| **X2=A** | **REQUIS** au compteur 16. `PARTIEL` = couverture actuelle, pas facultativité. |
| **X3=C** | Profondeur **hybride** : détaillée sur les familles de X5 ; secondaire ailleurs. |
| **X4=C** | Un futur `VALIDÉ` = **conception documentaire** + **liste** de travaux UX futurs, **sans** autorisation d’implémentation. |
| **X5=B** | **Noyau** DG-13.1–13.5 + présentation save (C-19 S14) + présentation des faits **déjà** observables chez C-04, C-07, C-11 et PE C6. Smokes, Demo, mécanique de sélection : **cités seulement**. |
| **X6=B** | HUD existant = **non-autorité / dette**. Ne pas le légitimer. Ne pas le redessiner. |
| **X7=A** | C-20 **n’ajoute aucun fait métier**. Il présente seulement des faits propriétaires **déjà exposables**. |
| **X8=B** | Eau / sol / éco : présentation **conditionnelle** à une lecture propriétaire **utilisable**. Absente ou invalide ≠ valeur par défaut. |
| **X9=B** | **Bloquant** avant de déclarer une UX produit ou un HUD DG-13 en service. **N’invalide pas** S3 / C6. |
| **X10=A** | Champs imposés : couches permanent / à la demande / caché · cause primaire · présentation save · non-objectifs · frontières. |
| **L1** | Exclusions du cadrage + sélection ≠ autorité métier + aucune donnée exigée si le propriétaire ne la garantit pas + dettes voisines signalées, non corrigées. |
| **L2** | Définition de « présenter » reprise au §1. |
| **L3** | Uniquement les écarts de l’audit de cadrage ; pas de chantier de correction. |

### 2.2 Sources déjà VALIDÉES (lues, non réécrites)

| Source | Reprise pour C-20 |
| --- | --- |
| **DG-13.1–13.5** | Exigences de lisibilité **inchangées**. C-20 en organise la **présentation**. Il ne les redéfinit pas. |
| **00.6 V1–V4, H1** | Compréhension minimale ; caché par défaut ; couches ; cause primaire ; signaux d’attention. Cités, non rouverts. |
| **C-04 F1 / F2** | Tâche `Blocked` : **cause primaire** obligatoire. Secondaires possibles, jamais substitut. |
| **C-07 J1 / J2** | Étapes importantes distinguables ; rapport exploitable (réussite, interruption, problèmes). |
| **C-11 §12** | Informations **agrégées** exposables : disponibilité, quantités mobilisées / transit, cause, bénéficiaire si pertinent. Détails fins cachés par défaut. |
| **C-18 13.1 / Q19 / R7** | C-18 = règle **exprimable**. C-20 = **présentation**. Pas de wording HUD imposé par C-18. |
| **C-18 Q6** | `TechComponent`, Ages, HUD FWSG = **legacy isolé**, non-autorité. |
| **C-19 S8 / S14 / §16** | C-19 ne porte **pas** l’UX. Présentation save = C-20. Cadence / Hertz = **C-21**. |
| **C6** | Observabilité **smoke / PE** ; pas HUD FWSG ; pas UI DG-13 complète. Preuve de cohorte, **pas** UX produit. |

C-20 **ne rouvre** aucun de ces textes.

---

## 3. Portée d’un `VALIDÉ` (X4)

Ce contrat est **`VALIDÉ`**. Il reste un **contrat de conception**.

Un `VALIDÉ` C-20 **n’autorise pas**, à lui seul :

- d’implémenter un HUD, un overlay, un écran de sauvegarde ou un widget ;  
- de modifier le HUD existant ;  
- de déclarer une UX produit ou un HUD DG-13 **en service** sans preuve distincte (X9) ;  
- d’ouvrir C-21 ;  
- d’activer la persistance runtime, F1, DG-07, Ages ou un mapping Wood ↔ Timber ;  
- de fermer O1–O9, P1–P10, Q1–Q12, R1–R8, R11 ;  
- de modifier `designGate.js`.

La **liste** des travaux UX futurs (§15) est un recensement. Elle **n’est pas** une autorisation.

---

## 4. Périmètre — détaillé vs secondaire (X3, X5)

### 4.1 Familles traitées en **détail** (X5)

1. Organisation de présentation de **DG-13.1–13.5**.  
2. Présentation de la **sauvegarde** (C-19 S14) — écran, flux joueur, observabilité produit de la save ; **sans** politique persist ni cadence.  
3. Présentation des faits **déjà** exposables chez :  
   - **C-04** (`Blocked` et sa cause primaire F1/F2 ; les tâches individuelles restent cachées par défaut — `00.6` V2, DG-13.5 conforme V2) ;  
   - **C-07** (étapes / rapport J1–J2, sans autorité de cycle de vie) ;  
   - **C-11** (informations agrégées §12) ;  
   - **PE C6** (lectures Stock A/B `Timber` déjà observées par la preuve C6).

### 4.2 Familles **citées seulement** (X5)

- smokes (`gf.Project.Smoke*` et assimilés) ;  
- Investor Demo / C-22 ;  
- mécanique de **sélection** (clic, marquee, commandes).

Ces éléments sont du **contexte** ou de la **preuve**. Ils ne sont **pas** des autorités produit autonomes.

### 4.3 Ailleurs : traitement **secondaire** (X3)

Tout ce qui n’est pas au §4.1 est **cité** s’il faut une frontière, **sans** règle de présentation détaillée.  
C-20 n’étend pas silencieusement le détail à C-01, C-02, C-05, C-08, C-12, C-14, C-18 runtime, C-22 ou C-23.

---

## 5. Couches d’information (X10)

Toute information que C-20 présente appartient à **une** de ces couches.  
Les couches reprennent DG-13.5 / `00.6` V2–V3 / H1. C-20 **n’ajoute pas** de quatrième couche.

| Couche | Rôle |
| --- | --- |
| **Permanent** | Ce que le joueur doit pouvoir comprendre **maintenant** pour décider ou voir l’état utile (13.3, 13.5, 00.6 H1). |
| **À la demande** | Motif, besoin, prochaine action, causes secondaires, détail local — **accessibles**, non dominants (13.2, 13.3, 13.5). |
| **Caché** | Tâches individuelles fines, files, réservations détaillées, ordre exact, ticks, scores internes, matrices, métriques sans conséquence (13.3, 13.5, `00.6` V2, C-11 §12). |

Une information **sans fait propriétaire exposable** n’entre dans **aucune** couche (X7, L1).  
C-20 **ne fixe pas** comment ces couches sont réalisées à l’écran (pas de layout, widget, couleur, animation, techno UI — DG-13.4 / 13.5).

---

## 6. DG-13 — organisation de présentation (sans réécriture)

C-20 **n’édite pas** 13.1–13.5. Il dit seulement **comment** les présenter dans son périmètre.

| Item | C-20 en présente | C-20 n’en fait pas |
| --- | --- | --- |
| **13.1** | Disponible / verrouillé / raison utile / prochaine étape, **si** C-18 (ou le propriétaire compétent) fournit un fait exprimable | Règle de déblocage, catalogue, arbre technique |
| **13.2** | Cause → conséquence → action possible, **si** le propriétaire a une cause | Diagnostic métier nouveau, microgestion |
| **13.3** | État + activité (et destination si le propriétaire la rend pertinente) ; motif / besoin / prochaine action à la demande | États d’unité nouveaux, files internes |
| **13.4** | Ouverture de possibilités, **si** C-18 fournit le fait exprimable | Arbre de bonus, nouvel arbre technologique, interface graphique |
| **13.5** | Classement en couches §5 ; alerte seulement si conséquence gameplay déjà établie par un propriétaire (dont N4 pour la saturation) | Layout, widget, couleur, animation, techno UI |

Les règles de déblocage restent **DG-02 / DG-07 / C-18**.  
Les règles d’autonomie restent **DG-04 / C-07**.  
Les causes de blocage restent **C-04 / DG-11 / propriétaires compétents**.

---

## 7. Cause primaire (X10)

Lorsqu’un propriétaire **définit** une cause primaire, C-20 la présente en **priorité** sur les secondaires.

| Propriétaire | Fait déjà tranché | Présentation C-20 |
| --- | --- | --- |
| **C-04 F1 / F2** | Tâche `Blocked` : cause primaire obligatoire | Couche **permanente** pour cette cause. Secondaires **à la demande**. Jamais l’inverse. |
| **DG-13.2 / `00.6` V4** | Une cause principale compréhensible ; secondaires à la demande | C-20 n’invente pas la cause. Il n’en affiche pas une autre à la place. |
| **C-11 §12** | Cause de blocage d’allocation, si le propriétaire l’expose | Présentée comme fait C-11, pas comme nouvelle règle de stock. |

Si le propriétaire **n’a pas** de cause exposable, C-20 **n’en fabrique pas** (X7, L1).

---

## 8. Faits propriétaires déjà exposables (X5, X7)

C-20 peut présenter **uniquement** :

| Propriétaire | Faits déjà exposables (rappel, non créés ici) |
| --- | --- |
| **C-04** | Si `Blocked` : cause primaire (F1/F2). Les tâches individuelles restent cachées par défaut (`00.6` V2 ; DG-13.5 conforme V2). |
| **C-07** | Distinguabilité des étapes importantes (J1) ; rapport réussite / interruption / problèmes (J2). Les états agent d’orchestration ne deviennent pas autorité de cycle de vie. |
| **C-11** | Disponibilité agrégée ; quantités mobilisées ou en transit ; cause ; bénéficiaire si pertinent (§12). |
| **PE C6** | Lectures Stock A / Stock B **`Timber`** déjà observées par `gf.Project.SmokeCohortObservability` / la chaîne C6. **Pas** HUD FWSG. **Pas** nouvelle ResourceKey. C-09\* **non ouvert**. |

C-20 **ne nomme pas** un libellé qui impliquerait un fait absent.  
Il **n’exige** aucune donnée que le propriétaire ne garantit pas (L1).

---

## 9. Présentation de la sauvegarde (C-19 S14, X10)

C-19 porte la **politique** persist / load / migration.  
C-20 porte l’**observabilité produit** de la save : ce que le joueur doit pouvoir comprendre d’une sauvegarde ou d’une reprise, **lorsque** C-19 fournit un fait de politique présentable.

C-20 **peut** présenter, sans implémenter :

- qu’une sauvegarde monde **opérationnelle** n’existe pas tant que le chemin actuel est non opérationnel (C-19 S12) ;  
- les familles **admises / conditionnelles / exclues** déjà nommées par C-19, comme **information**, pas comme nouvelle politique ;  
- qu’une save incompatible serait **refusée** (principe C-19 S11), sans schéma.

C-20 **ne définit pas** :

- ce qui est persisté ;  
- le régime session-only / durable ;  
- les flags, SaveGame, load, F1 ;  
- les cadences, temporisations, Hertz (**C-21**).

S3 / Investor Demo restent **hors** exigence de sauvegarde monde (C-19 S13). C-20 ne les y replace pas.

---

## 10. Eau / sol / éco (X8)

Présentation **conditionnelle**.

| Lecture propriétaire | Présentation C-20 |
| --- | --- |
| **Utilisable** (le propriétaire la fournit comme fait exposable) | Peut être présentée selon les couches §5 et DG-13 / 09.2 **déjà** VALIDÉS |
| **Absente, inconnue, invalide ou non utilisable** | **Aucune** valeur par défaut. **Aucun** indicateur intérimaire inventé |

C-15 O1–O9, C-16 P1–P10, C-17 Q1–Q12 restent **ouverts**. C-20 **ne les ferme pas**.

---

## 11. Preuves — C6 / S3 vs UX produit (X9)

Deux niveaux **distincts** :

| Niveau | Statut | Ce que C-20 en dit |
| --- | --- | --- |
| **Preuve de cohorte** C6 / S3 | **VALIDÉE** (ETAT / suivi production) | Observabilité smoke / PE. **Pas** HUD FWSG. **Pas** UI DG-13 complète. **Non invalidée**. |
| **UX produit / HUD DG-13 en service** | **Absente** | Déclaration **bloquée** tant qu’une preuve produit distincte n’existe pas (X9). |

Un smoke, une ligne de statut, un overlay Demo ou le HUD actuel **ne constituent pas** cette preuve produit.

---

## 12. HUD existant (X6)

Le dépôt contient `UGardenFervorRTSHUDWidget` (ressources Food / Wood / Stone / Gold, Age, menu, train, outils terraform, sélection, ligne smoke LevelPad) et `UGardenFervorSelectionComponent`.

**Constat, pas règle cible :**

- ce HUD **n’est pas** l’UX produit DG-13 ;  
- il **n’est pas** autorité (aligné C-18 Q6 pour FWSG / Ages) ;  
- C-20 le **signale** comme dette / non-autorité ;  
- C-20 **ne le légitime pas** ;  
- C-20 **ne le redessine pas**.

Aucun mapping Wood ↔ Timber. Aucune autorité Ages.

---

## 13. Smokes, Demo, sélection (X5, L1)

| Élément | Rôle dans C-20 |
| --- | --- |
| Smokes `gf.Project.*` | Preuve / diagnostic. **Pas** surface produit. |
| Investor Demo (C-22) | Présentation S3. **NON REQUIS** comme contrat gameplay. **Pas** SoT C-20. |
| Sélection | Mécanique d’entrée. **Pas** une autorité métier. C-20 n’en tire aucun fait. |

C-23 (M4 / UDS) reste **rendu**. C-20 n’en fait pas une vérité gameplay.

---

## 14. Travaux UX futurs (X4) — non autorisés

Recensement seulement. **Aucune** implémentation n’est ouverte.

1. Présentation produit des familles §4.1 (13.1–13.5, save, faits C-04 / C-07 / C-11 / PE C6).  
2. Preuve **distincte** permettant de déclarer une UX produit ou un HUD DG-13 en service (X9).  
3. Remplacement éventuel du HUD legacy — **hors** cette rédaction ; **hors** légitimation du HUD actuel.  
4. Présentation environnementale **si** lectures propriétaires utilisables (X8).  
5. Wording / flux save **après** que C-19 reste la politique et C-21 la cadence.

Ces travaux exigent une **autorisation humaine distincte**.

---

## 15. Responsabilités et frontières

### 15.1 Ce que C-20 garantit (présentation)

1. Titre et nécessité X1 / X2.  
2. Définition L2.  
3. Couches §5.  
4. Cause primaire **lorsque** le propriétaire la définit.  
5. Présentation save selon S14, sans persist ni Hertz.  
6. Présentation conditionnelle eau / sol / éco (X8).  
7. Blocage de la déclaration UX produit (X9) sans invalider S3 / C6.  
8. Signalement du HUD comme dette (X6).

### 15.2 Ce que C-20 ne possède pas

| Domaine | Autorité |
| --- | --- |
| Vérité hauteur / paint | **C-01** |
| Dirty / grille | **C-02** |
| Intention → Project | **C-03\*** (fermé) |
| Graphe, readiness, cause de tâche | **C-04** |
| WorkSite / SitePrep | **C-05** |
| Capacités / roster | **C-06\*** (fermé) |
| Exécution autonome, rapport agent | **C-07** |
| Métier Terraform | **C-08** |
| ResourceKey / stocks (règles) | **C-09\*** / **C-10\*** (fermés) |
| Allocation concurrente | **C-11** |
| Transport / réseaux | **C-12** |
| Achevé / En service (critère) | **C-13\*** (fermé) |
| Lifecycle infrastructures | **C-14** |
| Eau / sol / éco (vérité) | **C-15** / **C-16** / **C-17** |
| Autorisation / déblocage | **C-18** / DG-07 |
| Politique persist / load / migration | **C-19** |
| Cadence / Hertz / budgets | **C-21** (non ouvert) |
| Investor Demo | **C-22** (non requis) |
| Rendu M4 | **C-23** / vendor |
| Exigences de lisibilité fondatrices | **DG-13** (inchangé) |
| Sélection (mécanique) | Runtime existant — **pas** autorité métier (L1) |

---

## 16. Non-objectifs

C-20 ne fixe pas :

- layout, widgets, couleurs, animations, technologie UI ;  
- textes HUD exacts ;  
- cadence de rafraîchissement ;  
- faits métier, barèmes, catalogues, ResourceKey ;  
- mapping Wood ↔ Timber, Ages, `RequiredAge`, runtime DG-07 ;  
- persistance runtime, flags, SaveGame, F1 ;  
- réouverture des addenda, Case B, ODC-F9, C-21 ;  
- correction des dettes voisines (L1, L3) ;  
- redesign du HUD existant (X6).

---

## 17. Exclusions (L1)

Reprise du cadrage, plus les précisions confirmées :

- addenda C-03\* · C-06\* · C-09\* · C-10\* · C-13\* ;  
- Case B ;  
- ODC-F9 automatique ;  
- F1 / architecture shipping relief ;  
- persistance runtime ;  
- C-21 (cadence, Hertz, temporisations, budgets) ;  
- invention de vérité métier, y compris eau / sol / éco / tech / tâches ;  
- spec graphique (DG-13.4 / 13.5) ;  
- **sélection comme autorité métier** ;  
- **exigence d’une donnée** que le propriétaire ne garantit pas ;  
- **correction**, dans C-20, des dettes des contrats ou du runtime voisins.

---

## 18. Points explicitement ouverts

| # | Sujet | Pourquoi ce n’est pas tranché ici |
| --- | --- | --- |
| **R7 C-18** | Wording HUD de disponibilité / verrou **implémenté** | C-18 laisse R7 ouvert. C-20 porte la présentation de conception, **pas** le wording figé ni le code. |
| **O1–O9, P1–P10, Q1–Q12** | Données eau / sol / éco | Présentation **conditionnelle** (X8). Points **inchangés**. |
| **R1–R8, R11** hors le renvoi R7 | Catalogue, coûts, Hertz recherche, cycle tâches | **Inchangés**. R6 / cadence = C-21. |
| **C-21** | Fréquences / Hertz | **Non ouvert**. |
| Textes / layout / widgets | DG-13.4 / 13.5 | **Hors** contrat. |
| Preuve UX produit | X9 | Travail **futur**, non autorisé ici. |

---

## 19. Écarts signalés — audit de cadrage seulement (L3)

Ces écarts existaient **avant** cette rédaction. C-20 **ne les corrige pas**.

1. **DG-13 VALIDÉ ≠ HUD DG-13 produit.** Conception close ; surface produit absente.  
2. **HUD FWSG / Age** vs C-18 Q6 (legacy isolé).  
3. **C6 « pas HUD »** vs ligne smoke déjà affichée par `UGardenFervorRTSHUDWidget`.  
4. **C-15 O5** dit encore « C-19 non rédigé » alors que C-19 est `VALIDÉ` conception.  
5. **`CONTRATS/C-17_VEGETATION_ECOSYSTEMES.md`** encore **non suivi Git** (`??`) alors que C-17 est `VALIDÉ` au suivi.  
6. **InstantMode** et DisplayName Raise/Lower dans l’agent — dettes C-07 / C-08, pas des règles C-20.  
7. **Wood** à l’écran vs vérité **`Timber`** (C7 / C-18 Q22).  
8. **Pied de C-19** encore rédigé comme si le suivi était à l’étape 11.  
9. **Registre §10** n’a pas de ligne de champs C-20 (X10 les pose ici ; le registre n’est **pas** modifié à cette étape).

Aucun autre écart n’est ajouté. Aucun chantier de correction n’est ouvert.

---

## 20. Invariants

1. Titre : **Observabilité / UX lisibilité** (X1).  
2. REQUIS au 16 ; `PARTIEL` = couverture (X2).  
3. Hybride : détail = X5 ; le reste = secondaire (X3).  
4. Ce `VALIDÉ` reste **documentaire** et n’autorise pas l’implémentation (X4).  
5. Présenter = L2.  
6. Aucun fait métier créé (X7).  
7. Couches : permanent / à la demande / caché (X10).  
8. Cause primaire = celle du propriétaire, si elle existe (X10).  
9. Save = présentation S14 ; cadence = C-21.  
10. Eau / sol / éco conditionnels (X8).  
11. UX produit bloquée sans preuve distincte ; S3 / C6 conservés (X9).  
12. HUD actuel = dette, non redessiné (X6).  
13. Sélection ≠ autorité métier (L1).  
14. Addenda, Case B, F9, F1, persist runtime, C-21 : non ouverts.

---

## 21. Vérification

Critères **documentaires** de ce contrat — pas des preuves runtime :

| Critère | Attendu |
| --- | --- |
| Fidélité | X1–X10 et L1–L3 repris ; **aucune** règle ajoutée |
| Statut | **VALIDÉ** — conception uniquement |
| DG-13 | Cité, non réécrit |
| Faits | Tous renvoyés à un propriétaire déjà exposable |
| UI | Aucun layout / widget / couleur / Hertz |
| Preuves | S3 / C6 non invalidés ; HUD / smokes / Demo ≠ UX produit |
| Voisins | Non modifiés ; addenda fermés ; C-21 fermé |
| Dettes | Signalées §19, non corrigées |

Validation humaine **finale** enregistrée. Clôture **documentaire** (étape 10).  
Suivi / compteur / Hub restent à l’étape 11.

---

## 22. Hors autorisation

Ce contrat **VALIDÉ** **n’autorise pas** :

- l’implémentation d’une UX, d’un HUD, d’un overlay ou d’un écran de sauvegarde ;  
- la légitimation ou le redesign du HUD existant ;  
- de déclarer une UX produit ou un HUD DG-13 en service sans preuve distincte ;  
- l’ouverture de C-21 ou d’un addendum ;  
- la fermeture des questions ouvertes amont ;  
- la modification du Design Gate, des registres, du suivi, de l’historique, du Hub ou des contrats voisins ;  
- la correction des écarts §19.

---

## 23. Correspondance cadrage

| Décision | Section |
| --- | --- |
| X1 | §1 |
| X2 | en-tête, §1 |
| X3 | §4 |
| X4 | §3, §14, §22 |
| X5 | §4, §8, §13 |
| X6 | §12 |
| X7 | §1, §8 |
| X8 | §10 |
| X9 | §11 |
| X10 | §5, §7, §9, §16, §15 |
| L1 | §13, §17 |
| L2 | §1 |
| L3 | §19 |

---

*Fin C-20 — VALIDÉ. La clôture est documentaire. C-21 demeure non ouvert. Case B demeure suspendu. R7 C-18 et O1–O9 / P1–P10 / Q1–Q12 conservés. Aucune implémentation UX ni contrat suivant démarrés par cette clôture. Le suivi / compteur restent à l’étape 11.*
