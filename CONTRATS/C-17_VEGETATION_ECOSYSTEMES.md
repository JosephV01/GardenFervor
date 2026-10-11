# C-17 — Végétation / écosystèmes

| Champ | Valeur |
| --- | --- |
| **ID** | C-17 |
| **Nom** | Végétation / écosystèmes |
| **Statut documentaire** | **VALIDÉ** — validation humaine explicite ; audit final PASS ; contrat de conception uniquement ; points ouverts Q1–Q12, O1–O9 C-15 et P1–P10 C-16 conservés |
| **Profondeur** | Détaillée (registre) |
| **Ordre de rédaction** | 17 |
| **Bloquant** | Oui (avant simulation écologique réelle — registre) |
| **Dépendances amont (registre)** | **C-15** · **C-16** · **C-01** |
| **Voisinage opérationnel** | **C-02** (accueil spatial) · **C-08** (travaux) · **C-14** (emprise) · **C-15** (eau) · **C-16** (sol) |
| **Références** | Registre C-17 · `00.5.E1`–`00.5.E4` · `00.5.W3` · `00.5.X1` · `00.5.X2` · `00.6.F1` · `00.6.F2` · `00.6.F3` · `00.6.M2` · `00.6.A1` · `00.6.A2` · `08.3` · `08.5` · `09.1`–`09.6` · `10.5` · `12.4` · C-01 D4/D5/D14 · C-02 B2/B3/C1/C5 · C-14 C1 · C-15 G / O1–O9 · C-16 cadrage A1–K1 / P1–P10 · cadrage C-17 A1–K1 (voir §2.2 note) |

Ce document formalise le **cadrage végétation / écosystèmes déjà accepté** (décisions humaines de conception) et les **décisions Design Gate déjà VALIDÉES**.  
Il n’invente aucune règle supplémentaire.  
Il constitue la **règle officielle de conception** C-17 après validation humaine et inscription **VALIDÉ** dans le suivi.  
La clôture est **documentaire**. Elle **n’autorise pas** l’implémentation d’une simulation écologique, ni le démarrage de C-18, ni une preuve runtime de végétation / état écologique, ni l’implémentation hydrologique ou de sol.

**Case B** demeure **suspendu**.  
**C-18** demeure **non commencé**.  
**C-15** et **C-16** demeurent **VALIDÉ** comme contrats de **conception** uniquement. Leurs points **O1–O9** et **P1–P10** restent **ouverts** et **inchangés**.  
**ODC-F9** n’est **pas** démarré par cette clôture.  
Les addenda C-03 · C-06 · C-09 · C-10 · C-13 restent **fermés**.

---

## 1. Identité et finalité

C-17 est le contrat de la **vérité gameplay de la végétation et des états écologiques**.

Il porte deux vérités complémentaires :

1. la **végétation** et sa **composition agrégée** ;  
2. l’**état écologique courant** et l’**état écologique cible**.

Les états écologiques terrestres fondateurs sont **prairie**, **forêt** et **zone humide** (`00.5.E1`, `09.2`).

Il s’appuie sur **00.5.E1–E4** et **DG-09** (VALIDÉS) sans les remplacer.

Niveau de garantie de ce contrat :

- formaliser le **périmètre fondateur** et les **frontières** ;  
- rendre auditable ce que C-17 **lit, possède, expose et signale** ;  
- conserver **ouverts** les points non arbitrés ;  
- **ne pas** figer seuil, couverture chiffrée, maille, fréquence, formule, canal Dirty dédié, algorithme ni API C++.

C-17 définit des **responsabilités métier**. Il **n’est pas** une architecture C++ ni une spécification d’implémentation exécutable.

Les identifiants **A1–K1** ci-dessous sont le **cadrage accepté**, pas un second Design Gate.

---

## 2. Référentiel des décisions utilisées

### 2.1 Conception VALIDÉE (Design Gate — non modifié ici)

**00.5.E1** (VALIDÉ) — reprise intégrale :

> « États écologiques terrestres fondateurs : prairie, forêt, zone humide. Les lacs/rivières restent d’abord des états/structures hydrologiques relevant de W1–W4, auxquels un état écologique aquatique pourra être associé. Autres types écologiques différés. »

**00.5.E2** (VALIDÉ) — reprise intégrale :

> « Simuler dès le fondateur : conditions écologiques, état actuel, évolution (progression, stabilisation, dégradation, restauration) et composition agrégée. Mise à jour basse fréquence + événements importants. Pas de simulation biologique individuelle plante par plante. »

**00.5.E3** (VALIDÉ) — reprise intégrale :

> « Dépendances obligatoires dès le fondateur : territoire → eau/sol → végétation → état écologique, avec rétroactions pertinentes vers le territoire. Les interactions biologiques détaillées (espèces individuelles, chaînes alimentaires complexes, reproduction détaillée, etc.) restent différées. »

**00.5.E4** (VALIDÉ) — reprise intégrale :

> « Le résultat écologique est mesuré par un état actuel et un état cible, accompagnés d’indicateurs compréhensibles (conditions, couverture/composition agrégée, stabilité) et d’explications des facteurs bloquants. Pas de simple score abstrait d’« écologie ». Le joueur crée les conditions ; il ne sélectionne pas directement ni ne peint le résultat écologique final. »

| ID | Portée reprise |
| --- | --- |
| **00.5.W3** | L’eau influence réellement sols et écosystèmes dès la boucle minimale, via états / seuils **simples**. **Pas** de simulation détaillée des échanges eau-sol. Influence conçue ; chiffres = **O3 C-15**, non tranchés ici. |
| **00.5.X1** | Écosystèmes : simulé réellement + fréquence réduite + agrégé ; états, conditions, transitions et composition agrégée. |
| **00.5.X2** | Hors fondateur notamment : biologie individuelle plante par plante ; chaînes alimentaires complexes ; reproduction détaillée ; toute simulation sans conséquence démontrée. |
| **00.6.F1** | Couches eau / sol / végétation actives seulement si un bâtiment ou une transformation a un impact déclaré pertinent. Sinon : pas d’effet gameplay obligatoire ; visuel possible. |
| **00.6.F2** | « Simulé réellement » = vérité capable de conséquences, pas un calcul chaque frame. |
| **00.6.F3** | Une couche active doit avoir au moins une conséquence gameplay, environnementale, ou une dépendance fonctionnelle réelle. |
| **00.6.M2** | Agrégation par défaut (éco agrégée) ; instances fines seulement si identité gameplay. |
| **00.6.A1** | Paint / termes moteur = techniques. Discours gameplay : surface, sol, végétation, état du terrain. |
| **00.6.A2** | Données GardenFervor = vérité ; M4 / UDS / UDW = représentation. |
| **08.3** | Nettoyage et Défrichage sont des **travaux**. Ils n’absorbent pas la vérité écologique. |
| **08.5** | Un dirty de relief n’est **pas** une peinture écologique. Eau / sols / végétation : invalidation / mise à jour locale, pas transition forcée. |
| **09.1** | Végétation et État écologique = vérités gameplay DG-09, distinctes de Sol et Eau. États + seuils + dirty ; basse fréquence et événements. Activation **00.6.F1**. |
| **09.2** | Cibles fondatrices : Prairie ; Forêt ; Zone humide. Lac / Rivière = hydrologie W. Sol fertile / zones sèches = conditions de sol. Observable : actuel + cible + indicateurs ; pas de score abstrait. |
| **09.3** | Moteur hybride conditions + interventions. Dirty = invalidation / mise à jour locale, **jamais** transition forcée. Restauration ordinaire vs majeure = conception DG-09 ; catalogue = hors C-17. |
| **09.4** | Effets d’emprise / activité : règles environnementales DG-09 ; catalogue / types = DG-10 ; exécution = DG-11. C-17 porte la **vérité écologique**, pas le catalogue de fiches. |
| **09.5** | Le joueur vise des états ou transformations ; il ne peint pas le résultat écologique. |
| **09.6** | Grands ouvrages : portes et catalogue hors C-17 (DG-07 / DG-10 / C-14). Zones humides = états écologiques territoriaux, pas un type hydraulique C-15. |
| **10.5** | C-14 déclare emprise, accès, candidats d’impact. Comportements Sol / Eau / Végétation / État écologique = DG-09 / contrats propriétaires. |

### 2.2 Cadrage accepté (questionnaire C-17 — pas de nouvelle conception)

| # | Contenu accepté |
| --- | --- |
| **A1** | **Deux vérités complémentaires** sous C-17 : (1) végétation et composition agrégée ; (2) état écologique **courant** et état écologique **cible**. Ce n’est **pas** un score abstrait. |
| **A2** | **Une seule** vérité gameplay végétation / écosystème : C-17. M4, Paint, UDS, UDW et la couche technique `Forest` **ne sont pas** cette vérité. |
| **B1** | États terrestres fondateurs **uniquement** : prairie, forêt, zone humide. Aucun type ajouté ici. |
| **B2** | Lac, rivière, retenue = **structures hydrologiques C-15**. Un état écologique **aquatique** associé reste **différé**. |
| **B3** | « Sol fertile » et « zones sèches » restent des conditions **C-16**. C-17 peut les **lire** lorsqu’elles sont disponibles et utilisables. Il ne les redéfinit pas. |
| **C1** | C-17 **pourra exposer**, lorsque le contrat sera VALIDÉ **et** qu’une implémentation aura été autorisée distinctement : indicateurs compréhensibles ; signal de changement écologique aux futurs consommateurs. **Pas** d’API C++ imposée. |
| **D1** | Transitions déterminées par les **conditions environnementales** et les **interventions pertinentes**. Aucun seuil chiffré. |
| **D2** | Familles qualitatives fondatrices : **création**, **dégradation**, **restauration**, **stabilisation**. **Pas** de catalogue opérationnel exhaustif. |
| **D3** | Une invalidation locale est une **demande de réévaluation**. Elle n’est **jamais** un ordre imposant une transition. |
| **E1** | C-17 **portera** les conséquences écologiques des lectures hydrologiques **valides et utilisables au sens C-15**. Il ne redéfinit pas `QueryWater`. Les chiffres restent **O3**. Une lecture absente, inconnue, invalide ou non utilisable **n’est jamais** une valeur métier valide par défaut. |
| **E2** | C-17 **lira** le sol **lorsque** C-16 rend l’information disponible et utilisable. Il n’écrit ni humidité métier, ni fertilité, ni compaction. Une lecture sol absente, inconnue, invalide ou non utilisable **n’est jamais** une valeur métier valide par défaut. |
| **F1** | Après un signal pertinent, **C-17 décide** s’il réévalue. |
| **F2** | Les cellules / mécanismes C-02 **localisent et invalident**. Ils **n’imposent pas** la granularité écologique. Pas de maille chiffrée. |
| **G1** | **C-08** exécute le **défrichement**. **C-17** porte les **conséquences écologiques** de ce défrichement. Un événement de chantier **n’est pas** la vérité écologique. C-17 n’exécute aucun travail C-08. |
| **G2** | **C-14** déclare emprise et impacts de structure. C-17 applique une conséquence écologique **seulement** si un impact déclaré le justifie (**00.6.F1**, `09.4`). |
| **H1** | Zone humide = **état écologique terrestre** C-17. Elle **lit** des conditions hydrologiques C-15 lorsqu’elles sont utilisables. Elle n’est **pas** un type hydraulique C-15. |
| **I1** | Chaîne conceptuelle **territoire → eau/sol → végétation → état écologique** (`00.5.E3`) reprise comme **principe**. Pas de matrices chiffrées. |
| **I2** | Rétroactions **pertinentes** vers le territoire : **principe** seulement. C-17 peut **signaler** un besoin de réévaluation. Il n’écrit pas la vérité C-01 / C-15 / C-16. Aucune règle quantitative ajoutée. |
| **J1** | Contrat de **conception** : responsabilités métier. **Pas** d’architecture C++ , d’API de lecture, ni d’implémentation exécutable imposées ici. |
| **K1** | Exclusions §10. |

Note de traçabilité — les codes **A1–K1** de ce §2.2 sont le **cadrage C-17**, pas des items Design Gate. Ils condensent les réponses retenues du questionnaire (A1–L2) ; ils ne le remplacent pas item par item. `00.5.*` / `00.6.*` / `08.*` / `09.*` restent les seuls identifiants Design Gate. Les items questionnaire restés ouverts (B2 → Q12 ; C2 → Q2 ; canal Dirty questionnaire → Q1 ; API → Q2/Q3 ; G3/H2/K* → Q6–Q10 ; L2 → §12) figurent en **Q1–Q12**, pas comme décisions de cette table.

### 2.3 Contrats amont déjà VALIDÉS (lus, non réécrits)

| Source | Reprise pour C-17 |
| --- | --- |
| **C-01 D4** | C-01 gère uniquement le relief. Végétation et écologie ne sont pas son autorité. |
| **C-01 D5** | Toute modification réelle du relief est **signalée**. C-01 ne décide pas la réaction écologique. |
| **C-01 D14** | Paint technique ≠ biome / végétation / état écologique gameplay. La couche `Forest` n’est pas la forêt C-17. |
| **C-02 C1 / C5** | Stubs Soil / Water ≠ simulation garantie. Validité fonctionnelle éco = contrat propriétaire (C-17). |
| **C-02 B2 / B3** | Canaux Dirty **extensibles**. C-02 fournit le mécanisme. Les propriétaires définissent les émetteurs. **Aucun** canal végétation / écosystème n’est créé ni autorisé ici. |
| **C-02 D3 / F3** | C-02 n’est pas propriétaire de l’écologie. Il localise, invalide et expose des lectures spatiales. |
| **C-08** | Exécute le **défrichement** (cadrage G1). N’absorbe pas la vérité C-17. |
| **C-14 C1 / 10.5** | Déclare emprise et candidats d’impact. Ne possède pas les comportements écologiques. |
| **C-15 G / §3.5** | C-15 n’est pas propriétaire de la végétation, de la composition écologique ni de leurs transitions. Il fournit des lectures / signaux eau. |
| **C-15 O1–O9** | **Restent ouverts.** Ce contrat **ne les ferme pas**. |
| **C-16 A1 / D1 / F1 / P1–P10** | C-16 porte la vérité sol. C-17 est consommateur futur. **P1–P10 restent ouverts.** |
| **C-16 cadrage F1 / C-15 O3** | Réaction sol à l’eau = cadre C-16. Chiffres et part écosystèmes = **O3 ouvert**. C-17 ne les invente pas. |

---

## 3. Responsabilités et données sous autorité

### 3.1 Ce que C-17 possède

1. La **vérité végétation** et la **composition agrégée** (A1), **sans** seuil de couverture ni barème.  
2. La **vérité d’état écologique** : état **courant** et état **cible** (A1, `00.5.E4`, `09.2`).  
3. Les trois états terrestres fondateurs : **prairie**, **forêt**, **zone humide** (B1).  
4. Les **familles qualitatives de transitions** selon conditions environnementales et interventions pertinentes (D1) : **création / dégradation / restauration / stabilisation** (D2). Pas de catalogue opérationnel.  
5. La décision de **réévaluer** après un signal pertinent (F1, D3).  
6. La **possibilité** d’exposer des indicateurs compréhensibles et un signal de changement (C1) — **lorsque** VALIDÉ et implémentation autorisée distinctement.  
7. Les **conséquences écologiques du défrichement** (G1) et des emprises / impacts **déclarés** (G2) — pas l’exécution du défrichement, pas le catalogue de fiches. C-17 n’acquiert pas une responsabilité générale sur le nettoyage ou le terrassement.

### 3.2 Ce que C-17 lit

| Lecture | Autorité | Usage C-17 |
| --- | --- | --- |
| Hauteur, pente, surface de relief | **C-01** (via C-02 pour le relais spatial) | Situer une évolution liée aux transformations du territoire (I1) |
| Cellules, hors-périmètre, Dirty *mécanisme* | **C-02** | Localiser, invalider (F2) — pas imposer la maille éco |
| Lectures / signaux hydrologiques | **C-15** | Conséquences éco **si** la lecture est **valide et utilisable** au sens C-15 (E1) |
| Humidité métier, fertilité, compaction, conditions dérivées | **C-16** | Lecture **si** disponible et utilisable (E2, B3) |
| Existence / emprise / impact déclaré | **C-14** / fiches (`09.4`) | Activer une conséquence seulement si **00.6.F1** le justifie (G2) |
| Signal de **défrichement** | **C-08** | C-08 **exécute** ; C-17 peut en porter la **conséquence écologique** (G1). C-17 n’exécute pas. |
| Signal de nettoyage ou de terrassement | Travaux `08.3` / chantiers | **Signal éventuel de réévaluation** seulement (`08.5`, D3). C-17 n’exécute pas ces travaux et **n’en porte pas** une conséquence écologique générale. |

Une lecture **absente**, **inconnue**, **invalide** ou **non utilisable** (eau ou sol) **n’est jamais** substituée par une valeur métier par défaut (E1, E2).

### 3.3 Ce que C-17 expose

Lorsque le contrat sera VALIDÉ **et** qu’une implémentation aura été **autorisée distinctement** :

- l’état écologique **courant** et l’état **cible**, exprimés **dans le trio** prairie / forêt / zone humide — **sans** imposer un état exclusif par lieu (Q12 **ouvert**) ;  
- la **composition agrégée** pertinente ;  
- des **indicateurs compréhensibles** (`00.5.E4`, C1) ;  
- un **signal** de changement écologique aux futurs consommateurs ;  
- **aucune** vérité de relief, d’eau, de sol ou de rendu.

Tant que C-17 n’est pas VALIDÉ et implémenté, **aucune** lecture runtime existante n’est cette exposition. Il n’existe **pas** aujourd’hui de `QueryVegetation` ni d’échantillon écologique.

### 3.4 Ce que C-17 signale

Après un changement **réel** de l’état métier écologique (réévaluation C-17 effectuée), C-17 signale les zones concernées.  
Il ne prescrit pas la réaction des consommateurs (même principe que C-01 D5, C-15 §3.4, C-16 §3.4).

Un Dirty ou une invalidation **seule** **n’est pas** une preuve de simulation et **n’impose pas** de transition (D3).

Le **canal** Dirty éventuel (nom, existence, émetteurs) reste **ouvert** (Q1). Ce contrat **ne crée pas** de canal `Vegetation` / `Ecosystem` et **ne réutilise pas** Dirty `Soil` ou Dirty `Water` comme vérité C-17.

### 3.5 Non-responsabilités

| Domaine | Autorité |
| --- | --- |
| Hauteur / déformation / shipping du relief | **C-01** |
| Grille, Dirty *mécanisme*, `WorldToCell`, queries terrain | **C-02** |
| Vérité hydrologique, `QueryWater`, lac / rivière / retenue, O1–O9 | **C-15** |
| Humidité métier, fertilité, compaction, « sol fertile » / « zones sèches », P1–P10 | **C-16** |
| Lifecycle infrastructures, déclaration d’emprise | **C-14** |
| Exécution du **défrichement** | **C-08** |
| Catalogue et progression des grands ouvrages | DG-10 / DG-07 / **C-14** |
| Exécution procédurale des chantiers | DG-11 / C-04 / C-05 / C-07 |
| Apparence, M4, Paint, UDS, UDW, couche technique `Forest` | Présentation — cadrage A2, `00.6.A1`, `00.6.A2` |
| Tick spatial global, budgets / Hertz | Technique / **C-21** |
| Politique de sauvegarde | **C-19** |
| UX produit, déblocages, ResourceKey | **C-20** / **C-18** / économie (addenda fermés) |
| État écologique aquatique associé | **Différé** (`09.2`, B2) |

---

## 4. Modèle écologique fondateur

### 4.1 Nature du modèle (`00.5.E1`–`00.5.E4`, `00.5.X1`, `00.5.X2`, cadrage A1)

Le fondateur conçoit une **vérité écologique réelle**, à **fréquence réduite**, sous forme **agrégée**.

Inclus dès le fondateur (conception) :

- végétation et composition agrégée ;  
- état écologique courant et état cible ;  
- prairie, forêt, zone humide ;  
- transitions par conditions + interventions, familles D2.

Hors fondateur (E2, X2, K1) :

- biologie individuelle plante par plante ;  
- chaînes alimentaires complexes ; reproduction détaillée ;  
- score écologique abstrait ;  
- état écologique aquatique ;  
- tout seuil, formule, solveur ou catalogue opérationnel non décidé explicitement.

### 4.2 Les deux vérités (A1, `09.1`)

| Vérité | Contenu fondateur | Non fixé ici |
| --- | --- | --- |
| Végétation / composition agrégée | Couverture / mix agrégé, sans espèces individuelles | Seuils de couverture ; représentation C++ ; grain chiffré |
| État écologique | Courant et cible **inscrits dans le trio** prairie / forêt / zone humide | Q12 (un état exclusif par lieu vs multi-états) ; maille ; mapping technique |

C-17 **ne fusionne pas** ces deux vérités en un score unique.  
C-17 **ne crée pas** de quatrième écosystème cible fondateur.  
C-17 **n’impose** ni un état exclusif par lieu, ni un modèle multi-états. Aucune règle de dominance, de mélange, de couverture ou de seuil n’est ajoutée (Q12 **ouvert**).

### 4.3 Invariants fondateurs (uniquement dérivés)

1. **Une seule vérité gameplay** végétation / écosystème : C-17 (A2). Le rendu / Paint n’en est pas une copie concurrente.  
2. **Trio terrestre** : prairie, forêt, zone humide (B1, `00.5.E1`).  
3. **Lac / rivière ≠ écosystème cible** (B2, `09.2`).  
4. **Sol fertile / zones sèches ≠ écosystèmes** (B3, `09.2`, C-16 A1).  
5. **Pas de peinture** (`09.5`, `08.5`, D3) : un brush, un visuel ou un Dirty ne produit pas à lui seul un état écologique « fini ».  
6. **Activation `00.6.F1`** : effet gameplay obligatoire seulement si un impact déclaré le justifie. Couche active ⇒ conséquence réelle (`00.6.F3`).  
7. **Le joueur crée les conditions** ; il ne sélectionne pas ni ne peint le résultat (`00.5.E4`, `09.5`).  
8. **Non-substitution** : lecture eau / sol non utilisable ≠ valeur métier par défaut (E1, E2).

Aucun seuil d’humidité, de couverture, de temps ou de dominance n’est fixé ici.

---

## 5. États, lectures et incertitude (sémantique seulement)

### 5.1 Contenu minimal d’un état écologique (A1, B1, C1)

| Famille | Contenu attendu | Non fixé ici |
| --- | --- | --- |
| Localisation | Zone concernée (via C-02) | Taille de maille ; égalité cellule = état |
| Végétation | Composition agrégée | Barème de couverture |
| État | Courant et cible **inscrits dans le trio** prairie / forêt / zone humide ; Q12 ouvert | Coexistence détaillée avec une structure C-15 (Q6) ; un état exclusif vs multi-états (Q12) |
| Indicateurs | Compréhensibles au sens `00.5.E4` | Liste exhaustive ; UX C-20 |
| Évolution | Changement **observable** après réévaluation réelle | Catalogue opérationnel (Q5) |

### 5.2 Lectures amont non utilisables (E1, E2)

Les consommateurs de C-17, **et C-17 lui-même**, doivent traiter ainsi les lectures C-15 / C-16 :

| Situation | Règle C-17 |
| --- | --- |
| Lecture **valide et utilisable** au sens du contrat propriétaire | Peut fonder une réévaluation / une conséquence |
| **Absence**, **inconnu**, **invalide**, **non utilisable** | **Ne pas** inventer une valeur métier ; **ne pas** déclencher une transition sur cette seule base |
| Stub `QueryWater` / `QuerySoil` (`bValid`, `DepthCm`, `Moisture=0.5`) | **Pas** une simulation ; **pas** une entrée métier C-17 |

Le **mapping technique** d’un quadruplet de validité écologique (valide / absence / inconnu / invalide) **reste ouvert** (Q2). Ce n’est **ni** O1 C-15 **ni** C2 / P4 C-16.

---

## 6. API existante (constat, non redéfinie)

Inspectée dans `GardenFervorSpatialTypes.h`, `GardenFervorSpatialSubsystem.cpp`, `NotifySpatialLandscapeBrush` :

| Mécanisme | Constat actuel | Rôle contractuel C-17 |
| --- | --- | --- |
| `QueryVegetation` / sample écologique | **Absent** | Pas d’API à réinterpréter |
| Canal Dirty végétation / écosystème | **Absent** | Non créé ici (Q1) |
| `QuerySoil` / `QueryWater` | Stubs | Dettes C-16 / C-15 — **pas** des lectures C-17 |
| Canaux Dirty | `Terrain \| Slope \| Soil \| Water` | Mécanisme C-02 ; `Soil` = P7 ; `Water` = O8 ; **≠** C-17 |
| Brush relief | Dirty `Terrain\|Slope\|Soil\|Water` | Signal de relief (C-01 E4) — dette amont, non corrigée ici |
| Couche Paint / setting `Forest` | Présentation / technique | **Pas** l’état forêt C-17 (A2, D14) |
| `RTS/Environment/` | Gate visuel | **Pas** une sim écologique |

C-17 **n’impose pas** une nouvelle API par préférence (J1). Toute lecture future devra être décidée **après** ce contrat, sans traiter l’absence actuelle comme une vérité nulle métier.

---

## 7. Échanges avec les systèmes voisins

```text
C-01  vérité relief  ──signale──►  C-17  (peut réévaluer ; n’écrit pas le Store)
C-02  cellules/dirty/queries  ◄──►  C-17  (accueil spatial ; pas propriétaire éco)
C-15  vérité eau  ──expose lectures/signaux──►  C-17  (si utilisables ; O3 ouvert)
C-16  vérité sol  ──expose lectures/signaux──►  C-17  (si utilisables ; P* ouverts)
C-14  lifecycle  ──expose emprise/impact──►  C-17
C-08  travaux     ──expose événement──►  C-17  (conséquence éco ; pas l’exécution)
C-17  vérité éco  ──expose lectures / signaux──►  UX · tâches · C-18 (futurs)
M4 / Paint / UDS / UDW  ◄──représentent──  C-17   (jamais l’inverse)
```

| Contrat | C-17 lit | C-17 n’absorbe pas |
| --- | --- | --- |
| **C-01** | Signal de modification de relief | Écriture Store, Paint gameplay |
| **C-02** | Cellules, hors-périmètre, Dirty mécanisme | Propriété de la grille ; création de canal |
| **C-15** | Lectures / signaux eau **utilisables au sens C-15** | O1–O9, `QueryWater`, lac / rivière / retenue |
| **C-16** | Lectures / signaux sol **utilisables au sens C-16** | P1–P10, humidité / fertilité / compaction |
| **C-14** | Existence / emprise / impact déclaré | Cycle construction / démontage |
| **C-08** | Signal de **défrichement** (conséquence éco G1) | Exécution du défrichement ; nettoyage / terrassement |
| **C-19** | — | Politique de sauvegarde |
| **C-20 / C-18 / C-21** | — | UX, déblocages, Hertz |
| **C-09\*** | — | ResourceKey / Timber ; addendum **fermé** |

**O3 C-15 :** dépendance **ouverte**. E1 porte le *cadre* des conséquences éco à l’eau utilisable ; il **n’invente pas** les chiffres.

**O8 C-15** et **P7 C-16** : canaux `Water` et `Soil` **distincts**. Non fusionnés avec un futur dirty C-17.

---

## 8. Réactions aux changements et temporalité

### 8.1 Comportement contractuel (D1, D3, F1, `00.5.E2`, `00.5.X1`)

- La vérité écologique fondatrice est **réellement effectuée** seulement lorsque C-17 sera VALIDÉ **et** implémenté (pas un décor M4, pas Paint `Forest`).  
- Causes déjà VALIDÉES conceptuellement : conditions territoriales + interventions humaines (`09.3`, D1).  
- C-17 **décide** la réévaluation après un signal pertinent (F1).  
- Une invalidation **seule** n’équivaut pas à un nouvel état déjà calculé (D3).  
- Traitement **localisé et événementiel** privilégié ; basse fréquence possible en **principe** (`00.5.X1`, `00.6.F2`).  
- **Pas** de tick écologique mondial permanent, **pas** de période en Hertz (valeurs = C-21, Q8).

### 8.2 Familles de transitions (D2)

Familles qualitatives **seulement** :

- **création** ;  
- **dégradation** ;  
- **restauration** ;  
- **stabilisation**.

Ce n’est **pas** un catalogue opérationnel (qui passe de quoi à quoi, en combien de temps, sous quels chiffres).  
`09.3` (restauration ordinaire vs majeure) reste une **reprise Design Gate** ; C-17 n’ajoute pas de catalogue de moyens.

### 8.3 Ce qui n’est pas imposé

- seuils eau → éco (O3) ;  
- barèmes sol (P1–P6) ;  
- maille égale à la cellule C-02 ;  
- solveur, schéma numérique ;  
- scan global à chaque frame ;  
- canal Dirty dédié.

---

## 9. Interactions eau–sol–écosystèmes (cadrage E1, E2, I1, I2 ; `00.5.W3`)

**Conception (`00.5.W3`, `00.5.E3`) :** l’eau influence sols et écosystèmes dès la boucle minimale, par états / seuils simples. La chaîne territoire → eau/sol → végétation → état écologique est un **principe**.

**Opérationnel dans ce contrat (conception ; ≠ runtime) :**

- C-15 **établit** la vérité hydrologique et **fournit** les lectures / signaux ;  
- C-16 **établit** la vérité sol et **fournit** les lectures / signaux ;  
- C-17 **portera** les conséquences **écologiques** lorsque ces lectures sont **utilisables** ;  
- C-17 **n’impose pas** de sémantique à `QueryWater` / `QuerySoil` ;  
- C-17 **ne ferme pas** O1–O9 ni P1–P10 ;  
- les rétroactions vers le territoire restent un **principe de signal** (I2) ;  
- les échanges détaillés et les chiffres restent hors de cette rédaction ;  
- la coexistence fine zone humide ↔ structure hydraulique reste **ouverte** (Q6).

La possibilité d’une interaction future plus précise est **préservée**. Elle n’est pas une autorisation d’implémentation.

---

## 10. Exclusions (K1)

- biologie individuelle ; chaînes alimentaires complexes ; reproduction détaillée (`X2`) ;  
- score écologique abstrait (`00.5.E4`, `09.2`) ;  
- peinture d’écosystème ; M4 / Paint / UDS / UDW comme vérité (A2, `09.5`) ;  
- structures lac / rivière / retenue (C-15) ; état écologique aquatique (B2) ;  
- humidité métier, fertilité, compaction, « sol fertile », « zones sèches » (C-16) ;  
- relief (C-01) ; grille / mécanisme Dirty (C-02) ; exécution des travaux (C-08) ; lifecycle (C-14) ;  
- création ou autorisation d’un canal Dirty végétation / écosystème ;  
- fermeture de O1–O9 ou P1–P10 ;  
- seuils, formules, catalogues opérationnels, Hertz, API C++ ;  
- conséquences économiques précises ; déblocage de ressources ; addenda C-09\* / C-10\* ;  
- exigences détaillées des consommateurs (C-18 / C-20) ;  
- politique de sauvegarde (C-19) ;  
- Case B ; ODC-F9 ; addenda C-03 / C-06 / C-13 ;  
- implémentation écologique, hydrologique ou de sol.

---

## 11. Critères observables pour un audit ultérieur

Un audit indépendant pourra vérifier ce contrat **sans** exiger une implémentation, s’il constate que le document :

1. reprend E1–E4 **intégralement** ;  
2. formalise A1–K1 sans nouvelle conception ;  
3. maintient **deux** vérités complémentaires, sans score abstrait ;  
4. limite les cibles terrestres à prairie / forêt / zone humide ;  
5. ne transforme pas lac / rivière en écosystème C-17 ;  
6. ne transforme pas « sol fertile » / « zones sèches » en écosystèmes ;  
7. distingue événement de chantier (C-08) et vérité écologique (C-17) ;  
8. distingue emprise / impact déclaré (C-14) et conséquence C-17 sous **00.6.F1** ;  
9. traite l’invalidation comme demande de réévaluation, pas comme transition forcée ;  
10. refuse de traiter `QueryWater` / `QuerySoil` / Paint `Forest` comme vérité C-17 ;  
11. refuse de substituer une valeur métier par défaut aux lectures non utilisables ;  
12. laisse **ouverts** O1–O9, P1–P10, Q1–Q12 ;  
13. n’impose ni Hertz, ni maille, ni solveur, ni API C++, ni canal Dirty nouveau ;  
14. n’invente aucun seuil chiffré ;  
15. signale les divergences amont au lieu de les corriger ;  
16. se déclare **VALIDÉ** comme contrat de conception uniquement, sans preuve runtime ni autorisation d’implémentation.

Critères de **conformité runtime** (uniquement **après** validation du contrat **et** autorisation d’implémenter) — indicatifs, non exécutés :

- une lecture écologique gameplay ne provient pas de M4 / Paint / UDS / UDW ;  
- prairie / forêt / zone humide ne sont pas des labels Paint ;  
- un Dirty ou un défrichement seul n’est pas présenté comme état écologique fini ;  
- une lecture eau / sol non utilisable n’est pas présentée comme entrée métier valide.

---

## 12. Points explicitement ouverts

Identifiants **Q*** = ouverts **C-17**. Ils **ne remplacent pas** O1–O9 de C-15 ni P1–P10 de C-16.

| # | Sujet | Pourquoi ce n’est pas tranché ici |
| --- | --- | --- |
| Q1 | Canal Dirty végétation / écosystème : existence, nom, émetteurs | C-02 B2/B3 : extensible, non autorisé par défaut |
| Q2 | Sémantique / mapping d’une lecture écologique (valide / absence / inconnu / invalide) et API de lecture | J1 : pas d’API ; parallèle volontairement non fusionné avec O1 / P4 |
| Q3 | Topologie C++ du propriétaire d’état écologique | J1 : responsabilités métier seulement |
| Q4 | Seuils, formules, barèmes de composition / dominance / couverture | Aucun chiffre accepté ; O3 / P* non fermés |
| Q5 | Catalogue opérationnel des transitions | D2 = familles seulement |
| Q6 | Règles détaillées de coexistence zone humide ↔ structures hydrologiques C-15 | H1 = principe ; détail ouvert |
| Q7 | Persistance de l’état écologique | Politique = **C-19** |
| Q8 | Fréquences / budgets numériques | Principe X1 / F2 ; valeurs = **C-21** |
| Q9 | Conséquences économiques précises ; déblocage / ResourceKey | Addenda économiques fermés ; hors C-17 |
| Q10 | Exigences détaillées des consommateurs (UX, tâches, C-18) | C1 = signal possible, pas leurs règles |
| Q11 | État écologique aquatique associé à lac / rivière | `09.2` : ultérieur (B2) |
| Q12 | Règle d’état dominant vs multi-états de même rang | Non tranchée dans le cadrage accepté |
| — | **O1–O9 C-15** (dont O3, O8) | Inchangés |
| — | **P1–P10 C-16** (dont P7) | Inchangés |

---

## 13. État réel de l’implémentation (lecture seule — ≠ règles cibles)

Qualification : **vérifié dans le dépôt** lors de la rédaction.

| Mécanisme | Qualification |
| --- | --- |
| Lecture / sample végétation ou écosystème | **Absent** |
| Canal Dirty végétation / écosystème | **Absent** |
| `QuerySoil` / `QueryWater` | **Présents** — stubs C-16 / C-15, **pas** C-17 |
| Dirty `Soil` / `Water` au brush relief | **Présent** — écart C-01 E4 ; O8 / P7 ouverts |
| Couche / setting `Forest` | **Présent** — présentation / Paint |
| Preuve runtime C-17 | **Aucune** |

Les règles §2–§11 sont **normatives cibles de conception**. Le runtime actuel est une **absence / dette**, pas une preuve.

---

## 14. Vérification documentaire — divergences signalées (non corrigées)

Ces écarts existent **avant** ou **autour** de C-17. Ce contrat **ne les résout pas** en modifiant C-01, C-02, C-15, C-16, le registre ou le suivi.

1. **C-01 E4.** Le brush relief dirty `Soil \| Water`. Ce n’est ni un droit C-17, ni O8, ni P7 tranchés.  
2. **Stubs C-15 / C-16.** `bValid=true` dans la grille ≠ simulation eau / sol, encore moins C-17.  
3. **Paint `Forest`.** Label technique / visuel ≠ état forêt gameplay (D14, A2).  
4. **Pied de page C-15.** Le fichier C-15 dit encore que C-16 n’est pas commencé. C-16 est **VALIDÉ** (conception). Écart **hors** cette rédaction.  
5. **Registre vs voisinage.** Amont officiel C-17 = **C-15 · C-16 · C-01**. C-02 / C-08 / C-14 sont des **frontières**. Le registre n’est pas modifié par ce fichier.  
6. **Couverture suivi « partielle ».** Elle désigne DG-09, pas un runtime.  
7. **Suivi / compteur.** Ce fichier est **VALIDÉ** documentairement comme contrat de conception. Il n’est **pas** une preuve runtime. La mise à jour du suivi et du compteur n’est **pas** effectuée par cette clôture de fichier.

---

## 15. Invariants

1. Une seule vérité gameplay végétation / écosystème : C-17 (A2).  
2. Deux vérités complémentaires : végétation / composition agrégée ; état courant / cible (A1).  
3. Trio terrestre : prairie, forêt, zone humide (B1).  
4. Lac / rivière = C-15 ; aquatique associé différé (B2).  
5. Sol fertile / zones sèches = C-16 (B3).  
6. Invalidation ≠ transition (D3).  
7. Chantier / emprise ≠ vérité écologique (G1, G2).  
8. Lecture non utilisable ≠ valeur métier par défaut (E1, E2).  
9. Stub / Paint ≠ simulation C-17.  
10. O1–O9 et P1–P10 inchangés.  
11. Ce document n’autorise aucune implémentation.

---

## 16. Hors autorisation

Ce contrat **VALIDÉ** **n’autorise pas** :

- l’implémentation d’une simulation écologique ;  
- la création d’une API ou d’un canal Dirty ;  
- l’implémentation hydrologique ou de sol ;  
- la modification du Design Gate, de C-15, de C-16 ou des contrats amont ;  
- la fermeture de Q1–Q12, O1–O9 ou P1–P10 ;  
- la réouverture de Case B, d’ODC-F9 ou des addenda fermés ;  
- le démarrage de C-18.

**Arrêt après clôture :** aucune implémentation, aucun démarrage de C-18.

---

*Fin C-17 — VALIDÉ. C-18 demeure non commencé. Case B demeure suspendu. Points ouverts Q1–Q12, O1–O9 et P1–P10 conservés. Aucune implémentation écologique ni contrat suivant démarrés par cette clôture.*
