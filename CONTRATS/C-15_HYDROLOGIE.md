# C-15 — Hydrologie

| Champ | Valeur |
| --- | --- |
| **ID** | C-15 |
| **Nom** | Hydrologie |
| **Statut documentaire** | **VALIDÉ** — validation humaine explicite ; audit après correction PASS ; points ouverts O1–O9 et dettes d’implémentation / stub `QueryWater` conservés |
| **Profondeur** | Détaillée (registre) |
| **Ordre de rédaction** | 15 |
| **Bloquant** | Oui (avant simulation d’eau réelle — registre) |
| **Dépendances amont (registre)** | **C-02** · **C-01** |
| **Voisinage opérationnel** | **C-14** (lifecycle des structures) · **C-16** (sol) · **C-17** (écosystèmes) |
| **Références** | Registre C-15 · DG-00.5 W1–W4 · 00.5.X1 · 00.5.X2 · 00.6.F1 · DG-08.5 · DG-09.1 · 09.2 · 09.4 · 09.5 · 09.6 · C-01 D4/D5 · C-02 C1/C5/D3/F3 · cadrage accepté A–G |

Ce document formalise le **cadrage hydrologique déjà accepté** et les **décisions de conception déjà VALIDÉES**.  
Il n’invente aucune règle supplémentaire.  
Il constitue la **règle opérationnelle** C-15 après validation humaine et inscription **VALIDÉ** dans le suivi.  
Il **n’autorise pas** l’implémentation d’une simulation hydrologique, ni le démarrage de C-16 / C-17, ni une preuve runtime d’eau.

**Case B** demeure **suspendu**.  
**C-16** et **C-17** demeurent **non commencés**.  
**ODC-F9** n’est **pas** démarré par cette clôture.

---

## 1. Identité et finalité

C-15 est le contrat de la **vérité hydrologique gameplay** : rivières, lacs et retenues comme **états ou structures hydrauliques connectés** ; informations observables ; connectivité simulée ; ruissellement et accumulation **simplifiés**.

Il s’appuie sur **00.5.W1** (VALIDÉ, formulation clarifiée et publiée) sans la remplacer.

Niveau de garantie de ce contrat :

- formaliser le **périmètre fondateur** et les **frontières** ;  
- rendre auditable ce que C-15 **lit, possède, expose et signale** ;  
- conserver **ouverts** les points non arbitrés ;  
- **ne pas** figer algorithme, solveur, fréquence chiffrée ni précision finale.

Ce contrat **ne crée pas** de nouvelles décisions de conception. Les lettres **A–G** ci-dessous sont le **cadrage accepté**, pas un second Design Gate.

---

## 2. Référentiel des décisions utilisées

### 2.1 Conception VALIDÉE (Design Gate — non modifié ici)

**00.5.W1** (VALIDÉ) — reprise intégrale, mot pour mot :

> « Le fondateur simule dès sa première version une hydrologie logique connectée : rivières, lacs et retenues comme états ou structures hydrauliques de gameplay ; connectivité simulée ; ruissellement et accumulation simplifiés. L’hydrodynamique détaillée est hors du périmètre du fondateur. »
>
> « L’objectif à long terme de GardenFervor est de permettre une simulation hydrologique réaliste et approfondie, cohérente avec le relief et capable d’interagir avec les systèmes du sol et des écosystèmes. »
>
> « Cette cible à long terme ne pré-approuve aucun phénomène particulier, algorithme, solveur, niveau de précision ou implémentation. Les étapes futures devront être décidées explicitement selon les critères de conception applicables, notamment la cohérence du gameplay, la lisibilité, les performances et le réalisme. »

| ID | Portée reprise |
| --- | --- |
| **00.5.W2** | Vérité gameplay de l’eau **indépendante** des systèmes visuels. M4 / UDW peuvent représenter ; ils ne définissent jamais la vérité. |
| **00.5.W3** | L’eau influence réellement sols et écosystèmes dès la boucle minimale, via états / seuils **simples** et un grain spatial adapté. **Pas** de simulation détaillée des échanges eau-sol. |
| **00.5.W4** | Une retenue / un lac / une rivière nécessite une connectivité hydraulique logique : zone, niveau ou état, entrées / sorties et connexions pertinentes. **Pas** de simulation fluide complète. |
| **00.5.X1** | Eau : simulée réellement + fréquence réduite + agrégée ; hydrologie logique connectée, sans physique fluide complète. |
| **00.5.X2** | Hors fondateur notamment : simulation fluide détaillée ; toute simulation sans conséquence gameplay, environnementale ou de compréhension démontrée. |
| **00.6.F1** | Couches eau / sol / végétation actives seulement si un bâtiment ou une transformation a un impact déclaré pertinent. Sinon : pas d’effet gameplay obligatoire ; visuel possible. |
| **08.5** | Eau / sols / végétation reportés à DG-09. Un dirty de relief n’est **pas** une peinture écologique. |
| **09.1** | Eau = vérité gameplay DG-09. Simulation fondatrice : états + seuils + dirty, basse fréquence et événements. Activation conforme à F1. |
| **09.2** | Lac et rivière sont d’abord des états / structures **hydrologiques** (W*). Un état écologique aquatique associé est **ultérieur**. Zone humide = écosystème cible (C-17), pas un type hydrologique C-15. |
| **09.4** | Effets d’emprise / activité sur l’eau : règles environnementales DG-09 ; catalogue = DG-10 ; exécution = DG-11. C-15 porte la **vérité hydraulique**, pas le catalogue. |
| **09.5** | Le joueur vise des états ou transformations ; il ne peint pas le résultat écologique. |
| **09.6** | Grands ouvrages : retenues, lacs, rivières, restauration hydraulique, zones humides (périmètre conceptuel). Catalogue et exécution hors C-15 (DG-10 / DG-11 / C-14). |

### 2.2 Cadrage accepté (à formaliser — pas de nouvelle conception)

| # | Contenu accepté |
| --- | --- |
| **A** | C-15 définit la vérité hydrologique. Couvre rivières, lacs, retenues comme structures ou états connectés ; relations et informations observables. Fondateur = connectivité simulée + ruissellement et accumulation simplifiés. Architecture ouverte à une simulation ultérieure plus réaliste, **sans** figer algorithme, solveur ou précision. |
| **B** | Un état hydrologique n’est **pas** réductible à un seul nombre de niveau. Il comprend au minimum : zones et localisation ; niveau ou état de l’eau ; entrées, sorties et connexions ; cohérence des relations ; changements et transitions observables. Invariants fondateurs seulement s’ils découlent des décisions confirmées. Pas de seuils chiffrés inventés. |
| **C** | Connectivité **hybride** : relations structurelles explicites lorsqu’une connexion appartient au modèle ; chemins d’écoulement déterminés à partir du terrain et des conditions hydrologiques lorsque cela relève du modèle ; cohérence relief / connexions / écoulement / accumulation. Garanties, pas algorithme unique. |
| **D** | Frontières : C-01 = hauteur / relief ; C-02 = cellules, invalidation, lectures spatiales ; C-14 = lifecycle infrastructures ; C-15 = vérité hydrologique et ses règles ; C-16 = sol ; C-17 = conséquences / états écologiques ; M4 / UDS / UDW = présentation uniquement. |
| **E** | Distinguer lecture valide, absence d’eau, donnée inconnue / non disponible, lecture invalide. Ne pas confondre automatiquement une profondeur valide de zéro avec une lecture invalide. Rester cohérent avec `QueryWater` existant (`DepthCm`, `bValid`). Si la sémantique complète n’est pas encore confirmée : **point ouvert**. |
| **F** | Simulation réellement effectuée, fréquence adaptée, données pouvant être agrégées (X1). Pas de tick global permanent imposé, pas de fréquence numérique arbitraire, pas de solveur imposé. Distinguer comportement contractuel et optimisation technique future. |
| **G** | C-15 fournit les informations hydrologiques aux consommateurs. Il **n’est pas** propriétaire de la fertilité, de l’humidité métier du sol, de la végétation, de la composition écologique ou de leurs transitions. Les échanges eau-sol détaillés et les conséquences écologiques approfondies ne sont **pas** déclarés opérationnels tant que C-16 / C-17 ne les définissent pas. La possibilité d’interactions futures cohérentes est préservée. |

### 2.3 Contrats amont déjà VALIDÉS (lus, non réécrits)

| Source | Reprise pour C-15 |
| --- | --- |
| **C-01 D4** | C-01 gère uniquement le relief. L’eau n’est pas son autorité. |
| **C-01 D5** | Toute modification réelle du relief est **signalée**. C-01 ne décide pas la réaction hydrologique. |
| **C-02 C1 / C5** | Stubs Soil / Water ≠ simulation garantie. Validité fonctionnelle eau = contrat propriétaire (C-15). |
| **C-02 D3 / F3** | C-02 n’est pas propriétaire de l’eau. Il localise, invalide et expose des lectures spatiales. |
| **C-02 B\*** | Dirty = cellules + canaux extensibles ; session-only ; C-15 consomme / décide le recalcul métier. |
| **C-14** | Lifecycle des infrastructures (y compris éventuels ouvrages / réseaux d’eau). C-15 ne possède pas ce cycle. |

---

## 3. Responsabilités et données sous autorité

### 3.1 Ce que C-15 possède

1. La **vérité hydrologique gameplay** des rivières, lacs et retenues (W1, W4, A).  
2. Les **règles** de connectivité, d’écoulement simplifié et d’accumulation simplifiée du fondateur (W1, C).  
3. L’**état hydrologique** au sens de B : localisation / zones ; niveau ou état ; entrées, sorties, connexions ; cohérence relationnelle ; transitions observables.  
4. La **sémantique fonctionnelle** des lectures d’eau exposées aux consommateurs, y compris ce que signifie une profondeur nulle **lorsque** cette sémantique est tranchée (E, C-02 C5).  
5. La décision de **recalculer** l’état hydraulique après un signal pertinent (relief, structure, condition hydrologique) (F, C-01 D5).

### 3.2 Ce que C-15 lit

| Lecture | Autorité | Usage C-15 |
| --- | --- | --- |
| Hauteur, pente, surface de relief | **C-01** (via C-02 pour le relais spatial) | Déterminer les chemins d’écoulement et la cohérence relief ↔ eau (C) |
| Cellules, hors-périmètre, Dirty | **C-02** | Localiser, invalider, exposer |
| Existence / emprise d’une structure hydraulique | **C-14** | Une retenue ou un ouvrage n’existe comme infrastructure que selon C-14 ; C-15 en lit l’existence / l’emprise, pas le lifecycle |
| Impact déclaré d’une construction | DG-09.4 / fiches (hors catalogue C-15) | Activer une conséquence hydraulique seulement si pertinente (F1) |

### 3.3 Ce que C-15 expose

- des **informations hydrologiques observables** : présence ou absence d’eau (lorsque distinguable), profondeur ou état, appartenance à une zone / structure, connexions pertinentes ;  
- un **signal** de changement hydrologique aux consommateurs (C-16, C-17, C-14, tâches / UX le cas échéant) ;  
- **aucune** vérité de sol, d’écosystème ou de rendu.

### 3.4 Ce que C-15 signale

Après un changement **réel** de l’état hydrologique, C-15 signale les zones / cellules concernées.  
Il ne prescrit pas la réaction des consommateurs (même principe que C-01 D5).

Le canal Dirty `Water` de C-02 peut servir de **mécanisme d’invalidation**. Son usage fonctionnel n’est garanti que lorsque C-15 l’emploie comme propriétaire. Un Dirty `Water` émis **sans** recalcul C-15 **n’est pas** une preuve de simulation.

### 3.5 Non-responsabilités

| Domaine | Autorité |
| --- | --- |
| Hauteur / déformation / shipping du relief | **C-01** |
| Grille, Dirty mécanisme, `WorldToCell`, queries terrain | **C-02** |
| Lifecycle infrastructures, démontage, restauration de site | **C-14** |
| Humidité métier, fertilité, compaction du sol | **C-16** (W3 influence via lectures C-15 ; propriété = C-16) |
| Prairie / forêt / zone humide, végétation, composition écologique | **C-17** |
| Catalogue et progression des grands ouvrages | DG-10 / DG-07 / **C-14** |
| Exécution procédurale des travaux | DG-11 / C-04 / C-05 / C-07 / C-08 |
| Apparence de l’eau, M4, UDS, UDW | Présentation (C-23 / vendor) — **W2** |
| Tick spatial global, budgets numériques, solveur | Technique / **C-21** futur — non figé ici |
| Persistance | **C-19** (non rédigé) — capacité persistable à préserver, politique ouverte |

---

## 4. Modèle hydrologique fondateur

### 4.1 Nature du modèle (W1, A, X1, X2)

Le fondateur simule une **hydrologie logique connectée**, réellement effectuée, à **fréquence réduite** et sous forme **agrégée**.

Inclus dès le fondateur :

- rivières, lacs, retenues comme **états ou structures** de gameplay ;  
- **connectivité** simulée ;  
- **ruissellement** simplifié ;  
- **accumulation** simplifiée.

Hors fondateur (W1, X2) :

- hydrodynamique / simulation fluide **détaillée** ;  
- tout phénomène, algorithme ou solveur non décidé explicitement.

L’exclusion d’une hydrodynamique détaillée **vaut pour le fondateur**. Elle n’interdit pas définitivement une simulation plus réaliste. L’objectif à long terme de W1 **n’autorise pas** d’implémenter maintenant un solveur complexe.

### 4.2 Objets hydrauliques (W4, 09.2)

| Objet | Statut fondateur |
| --- | --- |
| Rivière | État ou structure hydrologique connectée |
| Lac | État ou structure hydrologique connectée |
| Retenue | État ou structure hydrologique connectée |
| Zone humide | **Pas** un type C-15 — écosystème cible **C-17** (09.2, 00.5.E1) |
| État écologique aquatique associé à un lac / une rivière | **Ultérieur** (09.2) |

Une retenue, un lac ou une rivière **exige** : une zone ; un niveau ou un état ; des entrées / sorties et connexions pertinentes (W4).  
C-15 ne réduit pas ces objets à un sprite d’eau ni à un seul scalaire.

### 4.3 Invariants fondateurs (uniquement dérivés)

Les invariants suivants découlent des décisions confirmées. Ils ne sont **pas** des lois physiques chiffrées.

1. **Une seule vérité eau gameplay** (W2). Le rendu n’en est pas une copie concurrente.  
2. **Cohérence avec le relief** (W1, C) : l’écoulement et l’accumulation fondateurs ne peuvent pas ignorer la hauteur / la pente lues depuis C-01.  
3. **Connectivité** (W4, C) : un objet hydraulique du modèle n’est pas un volume isolé sans relations.  
4. **Pas de peinture** (09.5, 08.5) : une opération de relief ou un visuel ne produit pas à lui seul un état hydraulique « fini ».  
5. **Activation F1** : une couche eau n’a d’effet gameplay obligatoire que si un impact déclaré le justifie.  
6. **Non-réduction** (B) : l’état hydrologique n’est pas seulement `DepthCm`.

Aucun seuil de débit, de volume, de pente critique ou de temps de remplissage n’est fixé ici.

---

## 5. États, connexions et transitions

### 5.1 Contenu minimal d’un état hydrologique (B, W4)

Pour chaque zone ou structure hydraulique du modèle :

| Famille | Contenu attendu | Non fixé ici |
| --- | --- | --- |
| Localisation | Zone / emprise / cellules concernées | Taille de maille (C-02, technique) |
| Niveau ou état | Information d’occupation hydraulique (niveau, présence, état discret) | Barèmes chiffrés |
| Relations | Entrées, sorties, connexions pertinentes | Topologie C++ concrète |
| Cohérence | Relations compatibles avec le relief et les autres objets du modèle | Test numérique de conservation |
| Évolution | Changements et transitions **observables** | Catalogue exhaustif des transitions |

### 5.2 Connectivité hybride (C)

Deux mécanismes **coexistent** ; aucun n’est l’algorithme unique du projet :

1. **Relation structurelle explicite** — lorsqu’une connexion hydraulique **appartient au modèle** (ex. ouvrage, liaison déclarée entre deux zones).  
2. **Détermination depuis le terrain** — lorsqu’un chemin d’écoulement **relève du modèle**, il se déduit du relief (C-01) et des conditions hydrologiques (C-15).

Garantie contractuelle : le résultat observable reste **cohérent** entre relief, connexions, écoulement simplifié et accumulation simplifiée.  
Le choix d’implémentation (graphe, drainage, combinaison) reste **technique** tant qu’il respecte cette garantie et W1.

### 5.3 Transitions

C-15 doit permettre de constater qu’un état hydraulique **a changé**, **où**, et **en quoi** (même exigence minimale que C-01 D8, appliquée à l’eau).

Les transitions exactes (création d’une retenue, rupture de connexion, assèchement, débordement, etc.) **ne sont pas catalogueées** ici : plusieurs d’entre elles dépendent de C-14 (existence d’ouvrage), de C-01 (relief) ou de décisions non prises.

Un dirty de relief (08.5) **invalide / met à jour localement** les couches concernées. Il **ne force pas** à lui seul une transition hydraulique ou écologique.

---

## 6. Lectures, unités et sémantique de validité

### 6.1 API existante (constat, non redéfinie)

L’interface runtime actuelle, inspectée dans `GardenFervorSpatialTypes.h` et `GardenFervorSpatialSubsystem.cpp` :

| Champ | Unité / type | Rôle actuel |
| --- | --- | --- |
| `FGardenFervorWaterSample::DepthCm` | **centimètres** (`float`) | Profondeur d’eau gameplay (commentaire code : couche gameplay, pas UDW) |
| `FGardenFervorWaterSample::bValid` | `bool` | Validité de l’échantillon |
| `UGardenFervorSpatialSubsystem::QueryWater(WorldLocation)` | retourne le sample | Lecture spatiale |

Comportement **constaté** du stub (≠ garantie C-15) :

- hors cellule / hors périmètre : `bValid = false`, `DepthCm` reste `0` ;  
- dans le périmètre : `bValid = true`, `DepthCm` lu dans `WaterDepthCm` (initialisé à `0`, clampé `≥ 0` au dirty) ;  
- le stub **ne distingue pas** « aucune eau » d’une simulation réelle ; C-02 C1 l’interdit déjà de présenter comme simulation garantie.

C-15 **n’impose pas** une nouvelle API par préférence. Toute évolution d’interface devra rester compatible avec ces unités (`cm`) ou les documenter explicitement avant changement.

### 6.2 Distinctions exigées (E)

Les consommateurs doivent pouvoir, **à terme**, distinguer :

| Situation | Sens | Ne pas confondre avec |
| --- | --- | --- |
| Valeur **valide** | La lecture appartient au modèle et peut être utilisée | — |
| **Aucune eau** | Absence hydrologique réelle dans une zone connue du modèle | Lecture invalide |
| **Inconnu / non disponible** | Le modèle n’a pas (encore) d’information exploitable | Zéro valide |
| **Invalide** | La requête ne peut pas être honorée (hors périmètre, non lié, erreur) | Absence d’eau |

**Règle déjà acceptée :** une profondeur **valide égale à zéro n’est pas automatiquement** une lecture invalide.

### 6.3 Point ouvert — sémantique complète de `QueryWater`

La paire actuelle `{ DepthCm, bValid }` **ne porte pas** à elle seule les quatre situations de 6.2.

Ce brouillon **n’invente pas** :

- un troisième champ ;  
- la règle « `bValid && DepthCm == 0` ≡ absence d’eau » comme décision officielle ;  
- la règle « stub `bValid == true` partout ≡ eau connue ».

Tant que ce point n’est pas tranché, les consommateurs **ne doivent pas** traiter le stub `QueryWater` comme vérité hydrologique C-15.

---

## 7. Échanges avec les systèmes voisins

```text
C-01  vérité relief  ──signale──►  C-15  (réévalue l’eau ; ne lit pas le Landscape comme vérité)
C-02  cellules/dirty/queries  ◄──►  C-15  (accueil spatial ; pas propriétaire de l’eau)
C-14  lifecycle ouvrage   ──expose existence/emprise──►  C-15
C-15  vérité eau  ──expose lectures / signaux──►  C-16 · C-17 · UX · tâches
M4 / UDS / UDW  ◄──représentent──  C-15   (jamais l’inverse)
```

| Contrat | C-15 lit | C-15 n’absorbe pas |
| --- | --- | --- |
| **C-01** | Hauteur / pente ; signal de modification de relief | Écriture du Store, shipping visuel, paint technique |
| **C-02** | Cellules, hors-périmètre, Dirty, relais de query | Propriété de la grille ; dirty présentation C-01 |
| **C-14** | Existence, emprise, disponibilité d’une structure | Cycle construction / démontage / restauration |
| **C-16** | — (futur consommateur) | Humidité métier, fertilité, compaction |
| **C-17** | — (futur consommateur) | États prairie / forêt / zone humide, végétation |
| **C-04 / C-05 / C-07 / C-08** | Signaux utiles aux travaux | Graphe, SitePrep, agent, terraformation métier |
| **C-19** | — | Politique de sauvegarde |
| **C-21** | — | Budgets / fréquences numériques |

**Réseaux d’eau (10.3) :** une infrastructure « réseau d’eau » relève du **lifecycle C-14** et de la conception DG-10. Son **effet hydraulique** relève de C-15 lorsqu’il est déclaré. Ni C-14 ni C-15 n’absorbent l’autre.

**Zones humides (09.2, 09.6) :** intention ou état écologique = **C-17**. Conditions hydrologiques nécessaires = lectures **C-15**. Pas de peinture directe (09.5).

---

## 8. Réactions aux changements et temporalité

### 8.1 Comportement contractuel (F, X1, 09.1)

- La simulation fondatrice est **réellement effectuée** (pas un décor figé, pas un visuel UDW).  
- Fréquence **adaptée / réduite** et données **agrégables**.  
- Modifications de relief (C-01) ou de conditions / structures hydrologiques : C-15 doit pouvoir **invalider localement** puis **rétablir une cohérence** observable entre relief, connexions, écoulement et accumulation.  
- Traitement **localisé et événementiel** privilégié — aligné sur C-02 E1/E2, sans en faire un tick spatial global permanent.

### 8.2 Ce qui n’est pas imposé

- période en Hertz ou en secondes ;  
- un tick monde permanent dédié à l’eau ;  
- un solveur, un schéma numérique, une conservation de volume chiffrée ;  
- un scan global à chaque frame.

Ces choix sont des **optimisations ou décisions techniques** futures (éventuellement C-21). Ils ne peuvent pas contredire W1 / X1 / F.

### 8.3 Transitions observables

Après un changement réel, un auditeur doit pouvoir constater :

1. que l’état hydrologique concerné n’est plus celui d’avant ;  
2. la zone affectée ;  
3. que les lectures exposées (lorsque valides au sens de C-15) reflètent le nouvel état, **sans** attendre que M4 / UDW aient convergé (W2, même principe que C-01 D6).

---

## 9. Interactions eau–sol–écosystèmes (G, W3)

**Conception (W3) :** l’eau influence sols et écosystèmes dès la boucle minimale, par états / seuils simples.

**Opérationnel aujourd’hui :**

- C-15 **établit** la vérité hydrologique et **fournit** les informations nécessaires ;  
- C-16 / C-17 **posséderont** les règles d’humidité métier, de fertilité, de végétation et de transitions écologiques ;  
- C-15 **n’implémente pas** ces règles ;  
- les échanges eau-sol **détaillés** restent hors fondateur (W3, X2) ;  
- les conséquences écologiques **approfondies** ne sont **pas** déclarées opérationnelles : C-16 et C-17 n’existent pas encore comme contrats.

La possibilité d’une interaction future plus réaliste (W1 § long terme) est **préservée**. Elle n’est pas une autorisation d’implémentation.

---

## 10. Exclusions et objectif à long terme

### 10.1 Hors fondateur

- hydrodynamique détaillée / fluide complet (W1, X2) ;  
- biologie individuelle, chaînes alimentaires, etc. (X2 — hors C-15) ;  
- état écologique aquatique associé comme vérité C-15 (09.2) ;  
- peinture écologique ou hydraulique (09.5, 08.5) ;  
- catalogue d’ouvrages et portes de progression (09.6, 02.10, 07.7) ;  
- Case B ; addenda C-03 / C-06 / C-09 / C-10 / C-13 ; ODC-F9.

### 10.2 Objectif à long terme (W1, non opératoire)

Permettre une simulation hydrologique **réaliste et approfondie**, cohérente avec le relief, capable d’interagir avec sol et écosystèmes.

Cette phrase :

- **n’est pas** une spécification d’implémentation ;  
- **n’interdit pas** d’y parvenir plus tard ;  
- **n’approuve pas** un phénomène, un algorithme, un solveur ou une précision.

Toute étape au-delà du fondateur exige une **décision explicite** (cohérence gameplay, lisibilité, performances, réalisme).

### 10.3 Architecture d’évolution

Le modèle fondateur doit rester **extensible** (A) : ajouter des phénomènes ou une précision ne doit pas exiger de renier la vérité unique C-15, la frontière W2, ni les autorités C-01 / C-02 / C-14 / C-16 / C-17.

---

## 11. Critères observables pour un audit ultérieur

Un audit indépendant pourra vérifier ce brouillon **sans** exiger une implémentation, s’il constate que le document :

1. reprend W1 **intégralement** (fondateur + hors-fondateur + long terme + non pré-approbation) ;  
2. ne réduit pas l’hydrologie à un seul scalaire (B) ;  
3. décrit une connectivité **hybride** sans imposer un algorithme (C) ;  
4. respecte les frontières D (C-01, C-02, C-14, C-16, C-17, présentation) ;  
5. documente `QueryWater` / `DepthCm` / `bValid` **tels qu’ils existent**, unités en **cm** ;  
6. refuse d’assimiler `DepthCm == 0` valide à une lecture invalide (E) ;  
7. laisse **ouvert** le quadruplet valide / absence / inconnu / invalide ;  
8. n’impose ni tick global, ni Hertz, ni solveur (F) ;  
9. ne déclare pas C-16 / C-17 opérationnels (G) ;  
10. n’invente aucun seuil chiffré, aucun nouveau item Design Gate, aucune API imposée par préférence ;  
11. signale les divergences amont au lieu de les corriger.

Critères de **conformité runtime** (uniquement **après** validation du contrat **et** autorisation d’implémenter) — indicatifs, non exécutés :

- une lecture d’eau gameplay ne provient pas de UDW / M4 ;  
- une modification réelle de relief peut entraîner une invalidation / un recalcul hydrologique **local** ;  
- un objet rivière / lac / retenue du modèle expose zone, état ou niveau, et connexions ;  
- le stub actuel n’est plus présenté comme simulation.

---

## 12. Points explicitement ouverts

| # | Sujet | Pourquoi ce n’est pas tranché ici |
| --- | --- | --- |
| O1 | Quadruplet valide / absence d’eau / inconnu / invalide sur `QueryWater` | E : `{ DepthCm, bValid }` insuffisant ; pas de décision confirmée |
| O2 | Catalogue des transitions hydrauliques | Dépend C-14, C-01 et décisions non prises |
| O3 | Seuils simples W3 (eau → sol / écosystèmes) | Propriété future C-16 / C-17 ; pas de chiffres confirmés |
| O4 | Topologie C++ du propriétaire d’état hydrologique | Même prudence que C-14 B1 : respecter l’architecture réelle |
| O5 | Persistance de l’état eau | C-19 VALIDÉ conception ; O5 demeure ouvert (politique de persistance ≠ définition de l’état eau persisté) |
| O6 | Fréquences / budgets numériques | X1 pose le principe ; les valeurs relèvent d’un arbitrage futur / C-21 |
| O7 | Alignement éventuel de formulations W3 / W4 / X1 / X2 après clarification W1 | Historique : dette documentaire **hors** ce brouillon ; W1 seul a été clarifié |
| O8 | Qui a le droit d’émettre le canal Dirty `Water` | C-02 B3 : les contrats propriétaires définissent les émetteurs. C-01 E4 constate aujourd’hui un dirty Water côté relief — **divergence signalée §14**, non résolue ici |
| O9 | Mapping exact ouvrage C-14 ↔ objet hydraulique C-15 | Aucune décision de fiche unique confirmée |

---

## 13. État réel de l’implémentation (lecture seule — ≠ règles cibles)

Qualification : **vérifié dans le dépôt** lors de la rédaction.

| Mécanisme | Qualification |
| --- | --- |
| `FGardenFervorWaterSample` (`DepthCm`, `bValid`) | **Présent** — stub |
| `QueryWater` | **Présent** — hors périmètre → `bValid=false` ; sinon `bValid=true` + profondeur tableau |
| `WaterDepthCm` initialisé à `0` | **Présent** — pas une hydrologie connectée |
| Canal Dirty `Water` | **Présent** (enum C-02) |
| Rivières / lacs / retenues comme objets gameplay | **Absents** |
| Connectivité, ruissellement, accumulation | **Absents** |
| Vérité distincte UDW | Commentaire code seulement ; **pas** de sim C-15 |
| Preuve runtime hydrologique | **Aucune** |

Les règles §2–§11 sont **normatives cibles**. Le runtime actuel est une **dette**, pas une preuve.

---

## 14. Vérification documentaire — divergences signalées (non corrigées)

Ces écarts existent **avant** C-15. Ce contrat **ne les résout pas** en corrigeant C-01, C-02 ou le runtime.

1. **C-01 E4 vs D4/D5.** L’implémentation notifie un dirty `Soil \| Water` lors d’un brush relief. C-01 dit ne gérer que le relief et seulement **signaler**. La sémantique eau de ce dirty n’est **pas** une autorité C-01. C-15 reprend : C-01 signale le relief ; C-15 décide le recalcul hydraulique. Le droit d’émission du canal `Water` reste **O8**.

2. **C-02 stub vs C-02 C1/C5.** `QueryWater` retourne `bValid=true` dans le périmètre alors qu’aucune sim n’existe. C-02 l’interdit déjà de présenter comme garantie. C-15 confirme : **pas de vérité fonctionnelle** tant que le contrat n’est pas VALIDÉ et implémenté.

3. **Registre vs voisinage.** L’amont officiel C-15 = **C-02 · C-01**. C-14 / C-16 / C-17 sont des **frontières**, pas des dépendances de rédaction manquantes. L’ordre et les autorités amont ne sont pas recalculés ici.

4. **Suivi.** La clôture documentaire met à jour `00_SUIVI_CONTRATS.md` (C-15 = **VALIDÉ**, compteur **10 / 16**). Cela ne démarre pas C-16 et n’autorise aucune implémentation.

5. **W3 vs G.** W3 affirme une influence fondatrice simple eau → sol / écosystèmes. G interdit de déclarer ces effets **opérationnels** sans C-16 / C-17. Ce contrat les tient ensemble : influence **conçue**, propriété **future**, pas d’effet runtime déclaré.

6. **Compteur 10/16.** Ce fichier est **VALIDÉ** documentairement. Il n’est **pas** une preuve runtime.

---

## 15. Invariants

1. Une seule vérité eau gameplay : C-15 (W2).  
2. Fondateur = logique connectée + ruissellement / accumulation simplifiés ; fluide détaillé hors fondateur (W1).  
3. Long terme ouvert, non pré-approuvé (W1).  
4. L’état hydrologique n’est pas un seul nombre (B).  
5. Connectivité hybride, sans algorithme unique (C).  
6. C-01 / C-02 / C-14 / C-16 / C-17 / présentation restent dans leurs autorités (D).  
7. Zéro valide ≠ invalide (E).  
8. Pas de tick / Hertz / solveur imposés ici (F).  
9. Stub `QueryWater` ≠ simulation C-15.  
10. Ce document n’autorise aucune implémentation.

---

## 16. Hors autorisation

Ce contrat **VALIDÉ** **n’autorise pas** :

- l’implémentation d’une hydrologie réelle ;  
- le remplacement du stub par un solveur ;  
- le démarrage de C-16, C-17, C-21 ou ODC-F9 ;  
- la modification du Design Gate ou des contrats amont ;  
- la réouverture de Case B.

**Arrêt après clôture :** aucune implémentation, aucun démarrage de C-16.

---

*Fin C-15 — VALIDÉ. C-16 et C-17 demeurent non commencés. Case B demeure suspendu. Points ouverts O1–O9 conservés. Aucune implémentation hydrologique ni contrat suivant démarrés par cette clôture.*
