# C-16 — Sol

| Champ | Valeur |
| --- | --- |
| **ID** | C-16 |
| **Nom** | Sol |
| **Statut documentaire** | **VALIDÉ** — validation humaine explicite ; audit final PASS ; contrat de conception uniquement ; points ouverts P1–P10 et O1–O9 C-15 conservés ; dettes stub / Dirty Soil conservées |
| **Profondeur** | Détaillée (registre) |
| **Ordre de rédaction** | 16 |
| **Bloquant** | Oui (avant simulation de sol réelle — registre) |
| **Dépendances amont (registre)** | **C-02** · **C-01** |
| **Voisinage opérationnel** | **C-15** (vérité hydrologique) · **C-17** (écosystèmes) · **C-14** (emprise d’ouvrage) · **C-08** (travaux) |
| **Références** | Registre C-16 · DG-00.5 O1–O4 · W3 · X1 · X2 · 00.6.F1 · F2 · M2 · A1 · DG-08.5 · DG-09.1 · 09.2 · 09.4 · 09.5 · C-01 D4/D5/D14/E4/E7 · C-02 C1/C5/B3/D3/F3 · C-15 G / §3.5 / O3 · cadrage accepté A1–K1 |

Ce document formalise le **cadrage sol déjà accepté** (questionnaire A1–K1) et les **décisions de conception déjà VALIDÉES**.  
Il n’invente aucune règle supplémentaire.  
Il constitue la **règle officielle de conception** C-16 après validation humaine et inscription **VALIDÉ** dans le suivi.  
La clôture est **documentaire**. Elle **n’autorise pas** l’implémentation d’une simulation de sol, ni le démarrage de C-17, ni une preuve runtime d’humidité / fertilité / compaction, ni une implémentation hydrologique.

**Case B** demeure **suspendu**.  
**C-17** demeure **non commencé**.  
**C-15** demeure **VALIDÉ** ; ses points **O1–O9** restent **ouverts** et **inchangés**.  
**ODC-F9** n’est **pas** démarré par cette clôture.

---

## 1. Identité et finalité

C-16 est le contrat de la **vérité métier du sol gameplay** : humidité métier, fertilité et compaction du sol ; conditions observables **dérivées** (notamment « sol fertile » et « zones sèches », au sens `09.2`) ; informations de lecture et de changement exposées aux consommateurs.

Il s’appuie sur **00.5.O1–O4** (VALIDÉ) sans les remplacer.

Niveau de garantie de ce contrat :

- formaliser le **périmètre fondateur** et les **frontières** ;  
- rendre auditable ce que C-16 **lit, possède, expose et signale** ;  
- conserver **ouverts** les points non arbitrés ;  
- **ne pas** figer unité, barème, maille, fréquence chiffrée, algorithme, solveur ni API C++.

Ce contrat **ne crée pas** de nouvelles décisions de conception. Les identifiants **A1–K1** ci-dessous sont le **cadrage accepté**, pas un second Design Gate.

---

## 2. Référentiel des décisions utilisées

### 2.1 Conception VALIDÉE (Design Gate — non modifié ici)

**00.5.O1** (VALIDÉ) — reprise intégrale :

> « Attributs du sol dès le fondateur : humidité, fertilité et compaction. Profondeur/composition différées tant qu’elles ne démontrent pas une valeur gameplay indispensable. »

**00.5.O2** (VALIDÉ) — reprise intégrale :

> « Le sol évolue dès le fondateur selon l’eau, les travaux, l’occupation et les transformations du territoire. Mise à jour événementielle et basse fréquence ; pas de simulation continue permanente. »

**00.5.O3** (VALIDÉ) — reprise intégrale :

> « Influence de l’eau et de l’usage simulée via des états/seuils et des règles discrètes simples. Les transitions importantes peuvent être déclenchées par événements territoriaux ou par mises à jour basse fréquence. »

**00.5.O4** (VALIDÉ) — reprise intégrale :

> « Le sol est une couche réelle de gameplay et d’écologie dès le fondateur, avec sa propre vérité gameplay. Sa représentation visuelle reste séparée de cette vérité et ne dépend pas de M4. »

Lecture opératoire de O4 pour C-16 : C-16 porte la **vérité sol**. Les **états écologiques cibles** (prairie, forêt, zone humide) restent **C-17** (`09.2`). O4 n’autorise pas C-16 à absorber C-17.

| ID | Portée reprise |
| --- | --- |
| **00.5.W3** | L’eau influence réellement sols et écosystèmes dès la boucle minimale, via états / seuils **simples**. **Pas** de simulation détaillée des échanges eau-sol. Influence conçue ; chiffres = **O3 C-15**, non tranchés ici. |
| **00.5.X1** | Sol : simulé réellement + fréquence réduite + agrégé ; humidité, fertilité, compaction. |
| **00.5.X2** | Hors fondateur notamment : profondeur / composition détaillée du sol ; géologie détaillée ; toute simulation sans conséquence démontrée. |
| **00.6.F1** | Couche sol active seulement si un bâtiment ou une transformation a un impact déclaré pertinent. Sinon : pas d’effet gameplay obligatoire ; visuel possible. |
| **00.6.F2** | « Simulé réellement » = vérité capable de conséquences, pas un calcul chaque frame. |
| **00.6.M2** | Agrégation par défaut hors zone d’action ; instances fines seulement si identité gameplay. |
| **00.6.A1** | Paint / termes moteur = techniques. Discours gameplay : surface, sol, végétation, état du terrain. |
| **08.5** | Un dirty de relief n’est **pas** une peinture écologique. Eau / sols / végétation : invalidation / mise à jour locale, pas transition forcée. |
| **09.1** | Sol = vérité gameplay DG-09. États + seuils + dirty ; basse fréquence et événements. Activation **00.6.F1**. |
| **09.2** | Sol fertile et zones sèches = **conditions ou états du sol**, pas des écosystèmes cibles. Prairie / forêt / zone humide = C-17. |
| **09.4** | Impacts d’emprise / activité sur le sol : règles environnementales DG-09 ; catalogue = DG-10 ; exécution = DG-11. C-16 porte la **vérité sol**, pas le catalogue. |
| **09.5** | Le joueur vise des états ou transformations ; il ne peint pas le résultat écologique. |

### 2.2 Cadrage accepté (questionnaire C-16 — pas de nouvelle conception)

| # | Contenu accepté |
| --- | --- |
| **A1=B** | Vérité fondatrice = les trois attributs O1 **et** des conditions observables **dérivées** (notamment « sol fertile », « zones sèches » au sens `09.2`). **Pas** de nouveau type écologique. Aucun seuil de dérivation fixé. |
| **A2=A** | **Une seule** vérité sol gameplay : C-16. |
| **B1=C** | Humidité métier = grandeur **sol**, distincte de la profondeur d’eau C-15. **Unité, échelle et représentation restent ouvertes**. |
| **B2=A+C** | Fertilité = **attribut propre** du sol. « Sol fertile » peut en être dérivé (`09.2`). **Barème différé**. |
| **B3=A** | Vocabulaire C-16 : **compaction du sol** (attribut). Distinct de `Compact` technique (alias Lower, C-01 E7) **et** de l’opération métier compactage de C-08. Aucun lien de comportement n’est fixé ici. |
| **C1=A** | Stub `QuerySoil` / `FGardenFervorSoilSample` = **dette technique**, pas une simulation garantie (C-02 C1/C5). |
| **C2=A** | Distinguer à terme : lecture **valide** ; **absence d’information métier** ; état **inconnu** ; lecture **invalide**. Ne pas figer maintenant le mapping sur `{ Moisture, bValid }`. |
| **C3=A** | `Moisture = 0.5` à l’init = constante **technique** de stub. **Aucune** signification métier officielle. |
| **D1=A** | C-16 lit relief, spatial, eau (quand C-15 rend la lecture utilisable), emprise utile. Il n’écrit ni hauteur, ni grille, ni vérité eau, ni écosystème, ni Paint. |
| **E1=A** | Après un signal pertinent, **C-16 décide** s’il réévalue le sol. |
| **E2=A** | Une invalidation / un Dirty **ne garantit pas** qu’un nouvel état métier soit déjà calculé. |
| **F1=A** | C-16 **portera** la réaction métier du sol aux lectures hydrologiques **valides** au sens C-15. Les **seuils chiffrés** et le partage écosystèmes restent **O3 C-15** / futur C-17. Identifiant de **cadrage C-16**, distinct de la décision Design Gate **00.6.F1**. |
| **G1=A** | C-16 possède la **signification métier** du canal Dirty `Soil`. Un Dirty `Soil` sans recalcul C-16 **n’est pas** une preuve de simulation. L’émission actuelle par C-01 (E4) = **dette signalée**, non corrigée ici. **≠ O8** (canal `Water`). |
| **H1=A** | Les cellules C-02 **localisent / invalident / exposent**. Elles **n’imposent pas** une vérité sol à la même granularité. Pas de maille chiffrée. |
| **H2=A** | Principes : événementiel + basse fréquence. **Pas** de Hertz, pas de tick sol permanent. Valeurs = futur / C-21. |
| **I1=A** | Exposer, lorsque C-16 sera VALIDÉ et implémenté : attributs fondateurs, conditions dérivées pertinentes, sémantique de validité, signal de changement local. **Pas** d’API C++ complète imposée ici. |
| **J1=A** | Capacité persistable à **préserver**. Politique save/load = **C-19**. |
| **K1=A** | Exclusions §10. |

### 2.3 Contrats amont déjà VALIDÉS (lus, non réécrits)

| Source | Reprise pour C-16 |
| --- | --- |
| **C-01 D4** | C-01 gère uniquement le relief. Le sol n’est pas son autorité. |
| **C-01 D5** | Toute modification réelle du relief est **signalée**. C-01 ne décide pas la réaction sol. |
| **C-01 D14** | Paint technique ≠ sol / fertilité / biome gameplay. |
| **C-01 E7** | `Compact` technique = alias Lower. Distinct de la compaction du sol C-16 **et** de l’opération métier compactage C-08. |
| **C-02 C1 / C5** | Stub Soil ≠ simulation garantie. Validité fonctionnelle sol = contrat propriétaire (C-16). |
| **C-02 B3** | C-02 fournit le mécanisme Dirty. Les propriétaires définissent les émetteurs de chaque canal. |
| **C-02 D3 / F3** | C-02 n’est pas propriétaire du sol. Il localise, invalide et expose des lectures spatiales. |
| **C-15 G / §3.5** | C-15 n’est pas propriétaire de l’humidité métier, de la fertilité ni de la compaction. Il fournit des lectures / signaux eau. |
| **C-15 O3** | Seuils chiffrés eau → sol / écosystèmes **ouverts**. Ce contrat **ne les ferme pas**. |

---

## 3. Responsabilités et données sous autorité

### 3.1 Ce que C-16 possède

1. La **vérité métier du sol gameplay** : humidité métier, fertilité, compaction du sol (O1, A2).  
2. Les **conditions dérivées** « sol fertile » et « zones sèches » (`09.2`), en tant que lectures de sol, **pas** comme écosystèmes (A1). Aucun seuil de dérivation n’est fixé.  
3. Les **règles** d’évolution fondatrices selon l’eau, les travaux, l’occupation et les transformations (O2), **sans** barèmes chiffrés.  
4. La **réaction métier du sol** aux lectures hydrologiques valides au sens C-15 (**cadrage F1**) — **sans** inventer les seuils (O3 C-15 ouvert).  
5. La **sémantique fonctionnelle** des lectures sol exposées, y compris les distinctions C2 **lorsque** leur représentation est tranchée.  
6. La décision de **réévaluer** l’état sol après un signal pertinent (E1).  
7. La **signification métier** du canal Dirty `Soil` (G1).

### 3.2 Ce que C-16 lit

| Lecture | Autorité | Usage C-16 |
| --- | --- | --- |
| Hauteur, pente, surface de relief | **C-01** (via C-02 pour le relais spatial) | Situer une évolution liée aux transformations du territoire (O2) |
| Cellules, hors-périmètre, Dirty mécanisme | **C-02** | Localiser, invalider, exposer (H1) |
| Lectures / signaux hydrologiques | **C-15** | Réaction sol **si** la lecture est utilisable au sens C-15 ; **pas** de nouvelle sémantique `QueryWater` |
| Existence / emprise d’une structure | **C-14** | Activer une conséquence sol seulement si un impact déclaré le justifie (**00.6.F1**, `09.4`) |
| Signaux de travaux / occupation | C-08 / C-04 / C-05 / C-07 (selon le cas) | Causes d’évolution O2 — C-16 n’absorbe pas leur métier |
| Impact déclaré d’une construction | DG-09.4 / fiches (hors catalogue C-16) | Activation **00.6.F1** |

### 3.3 Ce que C-16 expose

Lorsque le contrat sera VALIDÉ **et** qu’une implémentation aura été **autorisée distinctement** :

- les **attributs fondateurs** (humidité métier, fertilité, compaction du sol) **dans la représentation alors tranchée** ;  
- les **conditions dérivées** pertinentes (« sol fertile » / « zones sèches », au sens `09.2`) ;  
- une **sémantique de validité** de lecture (C2) ;  
- un **signal** de changement sol aux consommateurs (C-17, UX, tâches le cas échéant) ;  
- **aucune** vérité de relief, d’eau, d’écosystème ou de rendu.

Tant que C-16 n’est pas VALIDÉ et implémenté, le stub **n’est pas** cette exposition (C1).

### 3.4 Ce que C-16 signale

Après un changement **réel** de l’état métier du sol, C-16 signale les zones / cellules concernées.  
Il ne prescrit pas la réaction des consommateurs (même principe que C-01 D5 et C-15 §3.4).

Le canal Dirty `Soil` de C-02 peut servir de **mécanisme d’invalidation**. Son usage fonctionnel n’est garanti que lorsque C-16 l’emploie comme propriétaire. Un Dirty `Soil` émis **sans** réévaluation C-16 **n’est pas** une preuve de simulation (G1, E2).

### 3.5 Non-responsabilités

| Domaine | Autorité |
| --- | --- |
| Hauteur / déformation / shipping du relief | **C-01** |
| Grille, Dirty *mécanisme*, `WorldToCell`, queries terrain | **C-02** |
| Vérité hydrologique, `QueryWater`, O1–O9 | **C-15** |
| Lifecycle infrastructures | **C-14** |
| Prairie / forêt / zone humide, végétation, composition écologique | **C-17** |
| Catalogue et progression des ouvrages | DG-10 / DG-07 / **C-14** |
| Exécution procédurale des travaux ; opération métier compactage (politique ouverte dans C-08) | DG-11 / C-04 / C-05 / C-07 / **C-08** |
| `Compact` / `CompactSite` technique (alias Lower) | **C-01 E7** — **≠** compaction du sol C-16 ; **≠** métier compactage C-08 |
| Apparence du sol, M4, Paint | Présentation / C-01 D14 — **O4**, **A1** |
| Tick spatial global, budgets / Hertz | Technique / **C-21** |
| Politique de sauvegarde | **C-19** |

---

## 4. Modèle sol fondateur

### 4.1 Nature du modèle (O1, X1, X2, A1)

Le fondateur simule une **vérité sol réelle**, à **fréquence réduite**, sous forme **agrégée**.

Inclus dès le fondateur :

- humidité métier ;  
- fertilité ;  
- compaction du sol ;  
- conditions dérivées « sol fertile » et « zones sèches » (`09.2`) — sans seuil de dérivation.

Hors fondateur (O1, X2, K1) :

- profondeur / composition détaillée du sol ;  
- géologie détaillée ;  
- tout phénomène, barème ou solveur non décidé explicitement.

### 4.2 Attributs et conditions (B1, B2, B3, A1)

| Famille | Statut fondateur | Non fixé ici |
| --- | --- | --- |
| Humidité métier | Attribut sol, **distinct** de `DepthCm` C-15 | Unité, échelle, représentation (B1=C) |
| Fertilité | Attribut propre ; peut fonder la condition « fertile » | Barème (B2) |
| Compaction du sol | Attribut métier C-16 | Barème ; lien éventuel aux travaux |
| Condition « sol fertile » | Dérivée, lecture de sol (`09.2`) | Seuil de dérivation |
| Condition « zones sèches » | Dérivée, lecture de sol (`09.2`) | Seuil de dérivation |

Distinction lexicale (B3, C-01 E7, C-08 §9) — **aucune règle de comportement ajoutée** :

- `Compact` / `CompactSite` = alias technique de `Lower` (C-01 E7) ; C-08 constate que cet alias n’est **pas** le métier de compactage ;  
- **compacter / compactage** = opération métier **C-08**, distincte d’Aplanir ; la politique spécialisée reste **ouverte** dans C-08 ;  
- **compaction du sol** = attribut métier **C-16** (O1). Le lien éventuel entre l’opération C-08 et cet attribut **n’est pas tranché ici**.

C-16 **ne réduit pas** la vérité sol au seul `Moisture` du stub.  
C-16 **ne crée pas** d’état métier distinct nommé « sec » : le libellé retenu est « zones sèches » (`09.2`).

### 4.3 Invariants fondateurs (uniquement dérivés)

1. **Une seule vérité sol gameplay** (A2, O4). Le rendu / Paint n’en est pas une copie concurrente.  
2. **Non-confusion Compact** (B3, C-01 E7, C-08 §9) : compaction du sol ≠ `Compact` / Lower technique ≠ opération métier compactage C-08.  
3. **Cohérence avec le relief signalé** (O2, D1) : une évolution liée à une transformation de territoire ne peut pas ignorer qu’un relief a changé ; elle ne peut pas non plus **écrire** ce relief.  
4. **Pas de peinture** (`09.5`, `08.5`, E2) : un brush ou un visuel ne produit pas à lui seul un état sol « fini ».  
5. **Activation 00.6.F1** : effet gameplay obligatoire seulement si un impact déclaré le justifie.  
6. **Non-réduction** : l’état sol n’est pas seulement `Moisture`.

Aucun seuil d’humidité, de fertilité, de compaction ou de temps n’est fixé ici.

---

## 5. États, lectures et incertitude (sémantique seulement)

### 5.1 Contenu minimal d’un état sol (A1, O1)

| Famille | Contenu attendu | Non fixé ici |
| --- | --- | --- |
| Localisation | Zone / cellules concernées (via C-02) | Taille de maille |
| Attributs | Humidité métier, fertilité, compaction du sol | Représentation C++ / unités |
| Conditions dérivées | « Sol fertile » / « zones sèches » lorsqu’elles sont distinguables (`09.2`) | Autres libellés ; seuils (P2, P6) |
| Évolution | Changements **observables** après réévaluation réelle | Catalogue exhaustif des transitions |

### 5.2 Distinctions exigées (C2)

Les consommateurs doivent pouvoir, **à terme**, distinguer :

| Situation | Sens | Ne pas confondre avec |
| --- | --- | --- |
| Valeur **valide** | La lecture appartient au modèle C-16 et peut être utilisée | — |
| **Absence d’information métier** | Le modèle n’expose pas (encore) d’attribut exploitable | Lecture invalide |
| **Inconnu** | Information non disponible | Valeur stub `0.5` |
| **Invalide** | La requête ne peut pas être honorée (hors périmètre, non lié, erreur) | Absence d’information métier |

**Règle acceptée :** `Moisture == 0.5` du stub **n’est pas** une humidité métier officielle (C3).  
**Règle acceptée :** une lecture stub `bValid == true` **n’est pas** automatiquement une vérité C-16 (C1).

Le mapping technique de ces quatre situations sur `{ Moisture, bValid }` **reste ouvert** (C2). Ce n’est **pas** le point **O1** de C-15 (`QueryWater`).

---

## 6. API existante (constat, non redéfinie)

Inspectée dans `GardenFervorSpatialTypes.h` et `GardenFervorSpatialSubsystem.cpp` :

| Champ | Constat actuel | Rôle contractuel C-16 |
| --- | --- | --- |
| `FGardenFervorSoilSample::Moisture` | `float`, commentaire « stub gameplay moisture 0..1 (not M4 paint) » | **Pas** l’humidité métier officielle |
| `FGardenFervorSoilSample::bValid` | `bool` | Validité d’échantillon spatial, **pas** vérité C-16 |
| `QuerySoil(WorldLocation)` | hors cellule / index invalide → sample par défaut (`bValid=false`, `Moisture=0.5f`) ; sinon `bValid=true` + `SoilMoisture` | Relais C-02 ; sémantique métier = C-16, non encore garantie |
| `SoilMoisture` init | `0.5f` | Constante technique (C3) |
| Fertilité / compaction runtime | **Absentes** | Dettes par rapport à O1 |
| Canal Dirty `Soil` | Présent (enum) | Mécanisme C-02 ; métier = C-16 (G1) |

Hors périmètre ou cellule non résolue, `QuerySoil` retourne le sample par défaut de `FGardenFervorSoilSample` : `bValid = false` et `Moisture = 0.5f` (valeur d’initialisation du struct). Cette `0.5f` n’a **aucune** signification métier validée (C3) et **ne doit pas** être interprétée comme une humidité réelle. Le quadruplet sémantique C2 n’est **pas** figé par ce constat.

C-16 **n’impose pas** une nouvelle API par préférence (I1). Toute évolution d’interface devra rester compatible avec le constat ou la documenter explicitement **après** décision.

Tant que C-16 n’est pas VALIDÉ et implémenté, les consommateurs **ne doivent pas** traiter le stub `QuerySoil` comme vérité sol.

---

## 7. Échanges avec les systèmes voisins

```text
C-01  vérité relief  ──signale──►  C-16  (peut réévaluer ; n’écrit pas le Store)
C-02  cellules/dirty/queries  ◄──►  C-16  (accueil spatial ; pas propriétaire du sol)
C-15  vérité eau  ──expose lectures/signaux──►  C-16  (réaction sol ; O3 ouvert)
C-14  lifecycle  ──expose existence/emprise──►  C-16
C-16  vérité sol  ──expose lectures / signaux──►  C-17 · UX · tâches
M4 / Paint  ◄──représentent──  C-16   (jamais l’inverse)
```

| Contrat | C-16 lit | C-16 n’absorbe pas |
| --- | --- | --- |
| **C-01** | Signal de modification de relief | Écriture Store, Paint gameplay, `Compact`=Lower |
| **C-02** | Cellules, hors-périmètre, Dirty mécanisme, relais `QuerySoil` | Propriété de la grille ; stub = sim |
| **C-15** | Lectures / signaux eau **utilisables au sens C-15** | O1–O9, `QueryWater`, vérité hydraulique |
| **C-14** | Existence / emprise si impact sol déclaré | Cycle construction / démontage |
| **C-17** | — (futur consommateur) | États prairie / forêt / zone humide |
| **C-04 / C-05 / C-07 / C-08** | Signaux de travaux / occupation | Graphe, SitePrep, agent, métier Terraform, opération compactage C-08 |
| **C-19** | — | Politique de sauvegarde |
| **C-21** | — | Budgets / Hertz |

**O3 C-15 :** dépendance **ouverte**. Le **cadrage F1** porte le *cadre* de la réaction sol ; il **n’invente pas** les chiffres et **ne ferme pas** le partage C-17.

**O8 C-15 :** concerne uniquement le canal Dirty **`Water`**. Non fusionné avec G1 / Dirty `Soil`.

---

## 8. Réactions aux changements et temporalité

### 8.1 Comportement contractuel (O2, E1, E2, H2, X1)

- La vérité sol fondatrice est **réellement effectuée** lorsque C-16 sera implémenté (pas un décor M4, pas le stub).  
- Causes d’évolution déjà VALIDÉES : eau, travaux, occupation, transformations du territoire (O2).  
- C-16 **décide** la réévaluation après un signal pertinent (E1).  
- Un Dirty / une invalidation **seule** n’équivaut pas à un nouvel état métier déjà calculé (E2).  
- Traitement **localisé et événementiel** privilégié ; basse fréquence possible en principe (H2).  
- **Pas** de tick sol mondial permanent, **pas** de période en Hertz.

### 8.2 Ce qui n’est pas imposé

- unité ou échelle d’humidité / fertilité / compaction ;  
- maille égale à la cellule C-02 ;  
- solveur, schéma numérique ;  
- scan global à chaque frame.

Ces choix sont des **optimisations ou décisions techniques** futures (éventuellement C-21). Ils ne peuvent pas contredire O1–O4 / X1 / **00.6.F1** / cadrage A1–K1.

### 8.3 Transitions observables

Après un changement **réel** (réévaluation C-16 effectuée) :

1. l’état sol concerné n’est plus celui d’avant ;  
2. la zone affectée est identifiable ;  
3. les lectures exposées (lorsque valides au sens C-16) reflètent le nouvel état, **sans** attendre M4 / Paint (O4).

Le catalogue exact des transitions **n’est pas** fixé ici.

---

## 9. Interactions eau–sol–écosystèmes (cadrage F1, W3, G C-15)

**Conception (W3, O3 DG) :** l’eau influence le sol dès la boucle minimale, par états / seuils simples.

**Opérationnel dans ce contrat (conception ; ≠ runtime) :**

- C-15 **établit** la vérité hydrologique et **fournit** les lectures / signaux ;  
- C-16 **portera** la réaction **sol** à ces lectures **lorsqu’elles sont utilisables** ;  
- C-16 **n’impose pas** de sémantique à `QueryWater` et **ne ferme pas O1 ni O3** ;  
- C-17 **portera** les conséquences écologiques ; C-16 ne les définit pas ;  
- les échanges eau-sol **détaillés** restent hors fondateur (W3, X2) ;  
- **aucun seuil chiffré** n’est inscrit.

La possibilité d’une interaction future plus précise est **préservée**. Elle n’est pas une autorisation d’implémentation.

---

## 10. Exclusions (K1)

- profondeur / composition détaillée du sol ; géologie détaillée (X2, O1) ;  
- vérité hydrologique, `QueryWater`, O1–O9 (C-15) ;  
- prairie / forêt / zone humide, végétation (C-17, `09.2`) ;  
- Paint / M4 comme vérité sol (O4, A1, D14) ;  
- identifier `Compact` technique (alias Lower) à la compaction du sol (B3) ; identifier l’opération métier compactage C-08 à l’attribut compaction du sol ; aucun lien de comportement fixé ici ;  
- catalogue d’ouvrages et portes de progression (DG-10 / C-14) ;  
- solveur, Hertz, maille chiffrée, API C++ imposée par préférence ;  
- politique de sauvegarde (C-19) ;  
- Case B ; addenda C-03 / C-06 / C-09 / C-10 / C-13 ; ODC-F9 ;  
- implémentation sol ou eau.

---

## 11. Critères observables pour un audit ultérieur

Un audit indépendant pourra vérifier ce contrat **sans** exiger une implémentation, s’il constate que le document :

1. reprend O1–O4 **intégralement** ;  
2. formalise A1–K1 sans nouvelle conception ;  
3. ne réduit pas le sol à `Moisture` ;  
4. distingue compaction du sol, `Compact` technique (Lower) et opération métier compactage C-08 ;  
5. respecte les frontières C-01 / C-02 / C-15 / C-17 / C-19 / C-21 ;  
6. documente `QuerySoil` / `Moisture` / `bValid` **tels qu’ils existent** ;  
7. refuse de traiter le stub comme vérité C-16 ;  
8. refuse de donner un sens métier à `Moisture == 0.5` ;  
9. laisse **ouvert** le mapping C2 et **O3 C-15** ;  
10. ne fusionne pas Dirty `Soil` avec **O8** ;  
11. n’impose ni Hertz, ni maille, ni solveur, ni API C++ ;  
12. n’invente aucun seuil chiffré ;  
13. signale les divergences amont au lieu de les corriger.

Critères de **conformité runtime** (uniquement **après** validation du contrat **et** autorisation d’implémenter) — indicatifs, non exécutés :

- une lecture sol gameplay ne provient pas de M4 / Paint ;  
- humidité métier ≠ `QueryWater.DepthCm` ;  
- fertilité et compaction du sol existent comme vérité C-16, pas seulement `Moisture` ;  
- un Dirty `Soil` sans recalcul C-16 n’est pas présenté comme simulation ;  
- le stub n’est plus présenté comme vérité.

---

## 12. Points explicitement ouverts

Identifiants **P*** = ouverts **C-16**. Ils **ne remplacent pas** O1–O9 de C-15.

| # | Sujet | Pourquoi ce n’est pas tranché ici |
| --- | --- | --- |
| P1 | Unité / échelle / représentation de l’humidité métier | B1=C : principe seulement |
| P2 | Barème de fertilité et règle de dérivation « fertile » | B2 : attribut oui, chiffres non |
| P3 | Barème de compaction du sol | Aucun chiffre accepté |
| P4 | Mapping C2 sur `{ Moisture, bValid }` ou champs futurs | C2 : sémantique oui, technique non |
| P5 | Catalogue des transitions sol | Dépend travaux, C-15, C-17, décisions non prises |
| P6 | Autres conditions dérivées au-delà de « sol fertile » / « zones sèches » (`09.2`) | A1 n’a pas fixé de catalogue supplémentaire ; aucun état distinct « sec » |
| P7 | Émetteurs autorisés du canal Dirty `Soil` | G1 : métier = C-16 ; émission C-01 E4 = dette, non tranchée comme droit |
| P8 | Persistance de l’état sol | J1 : capacité oui ; politique = C-19 |
| P9 | Fréquences / budgets numériques | H2 / X1 : principe ; valeurs = C-21 |
| P10 | Topologie C++ du propriétaire d’état sol | I1 : pas d’API imposée |
| — | **O3 C-15** (seuils eau → sol / écosystèmes) | **Reste O3** ; le cadrage F1 ne le ferme pas |
| — | **O1, O2, O4–O9 C-15** | Inchangés ; hors rédaction C-16 |

---

## 13. État réel de l’implémentation (lecture seule — ≠ règles cibles)

Qualification : **vérifié dans le dépôt** lors de la rédaction.

| Mécanisme | Qualification |
| --- | --- |
| `FGardenFervorSoilSample` (`Moisture`, `bValid`) | **Présent** — stub |
| `QuerySoil` | **Présent** — hors périmètre / index invalide → `bValid=false` avec `Moisture` technique `0.5f` du sample par défaut ; sinon `bValid=true` + tableau. `0.5f` ≠ humidité métier |
| `SoilMoisture` initialisé à `0.5` | **Présent** — pas une humidité métier |
| Fertilité / compaction runtime | **Absentes** |
| Conditions « sol fertile » / « zones sèches » | **Absentes** |
| Canal Dirty `Soil` | **Présent** (enum C-02) |
| Émission Dirty `Soil` au brush relief | **Présente** (`NotifySpatialLandscapeBrush` : Terrain\|Slope\|Soil\|Water) — écart C-01 E4 |
| Vérité distincte M4 / Paint | Commentaire stub seulement |
| Preuve runtime sol C-16 | **Aucune** |

Les règles §2–§11 sont **normatives cibles**. Le runtime actuel est une **dette**, pas une preuve.

---

## 14. Vérification documentaire — divergences signalées (non corrigées)

Ces écarts existent **avant** ou **autour** de C-16. Ce contrat **ne les résout pas** en modifiant C-01, C-02, C-15, le registre ou le suivi.

1. **C-01 E4 vs D4/D5 / G1.** Le brush relief dirty `Soil \| Water`. C-01 ne possède pas le sol. C-16 reprend : C-01 signale le relief ; C-16 décide la réévaluation sol. Le droit d’émission `Soil` reste **P7**. Le canal `Water` reste **O8 C-15**, non fusionné.

2. **C-02 stub vs C-02 C1/C5.** `QuerySoil` retourne `bValid=true` dans le périmètre alors qu’aucune sim sol n’existe. C-16 confirme : **pas de vérité fonctionnelle** tant que le contrat n’est pas VALIDÉ et implémenté.

3. **O1 vs stub.** Conception : trois attributs. Runtime : un seul scalaire `Moisture`. Dette d’implémentation, pas une réduction officielle de O1.

4. **Registre vs voisinage.** Amont officiel C-16 = **C-02 · C-01**. C-15 / C-17 / C-14 sont des **frontières**. Le registre n’est pas modifié par ce fichier.

5. **Suivi.** La clôture documentaire met à jour `00_SUIVI_CONTRATS.md` (C-16 = **VALIDÉ**, compteur **11 / 16**). Cela ne démarre pas C-17 et n’autorise aucune implémentation.

6. **W3 / cadrage F1 vs O3 C-15.** Influence conçue ; réaction sol **portée** par C-16 ; chiffres et part C-17 **ouverts** (O3). Pas d’effet runtime déclaré. **00.6.F1** reste l’activation de couche, distincte du cadrage F1.

7. **Compteur 11/16.** Ce fichier est **VALIDÉ** documentairement comme contrat de conception. Il n’est **pas** une preuve runtime.

---

## 15. Invariants

1. Une seule vérité sol gameplay : C-16 (A2, O4).  
2. Fondateur = humidité métier + fertilité + compaction du sol + conditions « sol fertile » / « zones sèches » (O1, A1, `09.2`).  
3. Humidité métier ≠ profondeur d’eau C-15 (B1).  
4. Compaction du sol ≠ `Compact` / Lower (C-01 E7) ≠ opération compactage C-08 (B3).  
5. Stub `QuerySoil` ≠ simulation C-16 (C1).  
6. `Moisture == 0.5` ≠ humidité officielle (C3).  
7. Invalidation ≠ état métier déjà recalculé (E2).  
8. C-01 / C-02 / C-15 / C-17 / C-19 / C-21 restent dans leurs autorités.  
9. O1–O9 C-15 inchangés ; O3 non fermé.  
10. Ce document n’autorise aucune implémentation.

---

## 16. Hors autorisation

Ce contrat **VALIDÉ** **n’autorise pas** :

- l’implémentation d’une simulation de sol ;  
- le remplacement du stub par une vérité métier ;  
- l’implémentation hydrologique ;  
- le démarrage de C-17, C-21 ou ODC-F9 ;  
- la modification du Design Gate, de C-15 ou des contrats amont ;  
- la fermeture de P1–P10 ou de O1–O9 C-15 ;  
- la réouverture de Case B.

**Arrêt après clôture :** aucune implémentation, aucun démarrage de C-17.

---

*Fin C-16 — VALIDÉ. C-17 demeure non commencé. Case B demeure suspendu. Points ouverts P1–P10 et O1–O9 C-15 conservés. Aucune implémentation sol ni contrat suivant démarrés par cette clôture.*
