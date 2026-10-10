# C-18 — Technologie / progression

**Sous-titre :** Ages = legacy, non-authority

| Champ | Valeur |
| --- | --- |
| **ID** | C-18 |
| **Nom** | Technologie / progression |
| **Statut documentaire** | **VALIDÉ** — validation humaine explicite ; audit final PASS ; contrat de conception uniquement ; points ouverts R1–R8, R11 ; O1–O9, P1–P10 et Q1–Q12 conservés |
| **Profondeur** | Détaillée (registre) |
| **Ordre de rédaction** | 18 |
| **Nécessité** | Requise (Q2) |
| **Bloquant** | Oui — avant les véritables déblocages DG-07 (registre · Q2) |
| **Dépendances amont (registre)** | **C-00** · **C-03** — C-00 n’a pas de fichier dédié (DG-00 = autorité) ; C-03 demeure addendum **fermé** (Q15, Q16) |
| **Voisinage opérationnel** | **C-14** (lifecycle / mise en service) · **C-04** (tâches) · **C-15** / **C-16** / **C-17** (lectures environnementales, conception) · **C-19** (persistance) · **C-20** (présentation) · **C-21** (fréquences) |
| **Références** | DG-07 (07.1–07.7, état constaté VALIDÉ) · `00.4` · `00.5.T2` · `00.5.U6` · `01.5` · `02.3` · `02.10` · `05.4` · `13.1` · `13.4` · C-14 A3/B2 · C-04 J3 · C-15 O1–O9 · C-16 P1–P10 · C-17 Q1–Q12 · cadrage C-18 Q1–Q31 |

Ce document formalise le **cadrage technologie / progression déjà accepté** (décisions humaines Q1–Q31) et les **décisions Design Gate déjà VALIDÉES** de DG-07.  
Il n’invente aucune règle supplémentaire.  
Il constitue la **règle officielle de conception** C-18 après validation humaine explicite.  
La clôture est **documentaire**. Elle **n’autorise pas** l’implémentation runtime DG-07, ni le démarrage de C-19, C-20 ou C-21, ni la migration Ages / `RequiredAge` / HUD FWSG.

**Case B** demeure **suspendu**.  
**ODC-F9** n’est **pas** démarré par cette clôture.  
**C-19** est **VALIDÉ** conception uniquement. **C-20** est **VALIDÉ** conception uniquement (UX non implémentée). **C-21** demeure **non commencé**.  
**C-15**, **C-16** et **C-17** demeurent **VALIDÉ** comme contrats de **conception** uniquement. Leurs points **O1–O9**, **P1–P10** et **Q1–Q12** restent **ouverts** et **inchangés**.  
Les addenda C-03 · C-06 · C-09 · C-10 · C-13 restent **fermés**.  
S3 / Investor Demo restent **hors** dépendance à Ages, à la recherche et aux déblocages DG-07 (Q7).

---

## 1. Identité et finalité

C-18 est le contrat de la **vérité de conception** de la progression GardenFervor : recherche, technologies, schémas, autorisations durables, familles de déblocages, et sémantique des conditions de progression (Q1, Q3).

Il rend **DG-07 exploitable** au niveau des règles de conception.  
Il **n’est pas** une spécification d’implémentation C++ ou Blueprint.

Le titre canonique est **Technologie / progression**.  
Le sous-titre **Ages = legacy, non-authority** porte la politique Ages ; il ne fait pas partie du nom d’identité (Q1).  
Le titre registre §5 « Progression / tech (hors Ages legacy) » décrit la même politique ; C-18 ne le substitue pas comme nom officiel (Q4, Q31).

`PARTIEL`, dans le registre et le suivi, décrit la **couverture actuelle** de la progression cible (DG-07 formalisé, runtime Ages isolé).  
`PARTIEL` **ne signifie pas** que le contrat est facultatif.  
C-18 est **requis** et **bloquant** avant les déblocages réels DG-07 (Q2).

Niveau de garantie de ce contrat :

- formaliser le **périmètre** et les **frontières** ;  
- rendre auditable ce que C-18 **possède, lit, signale et n’absorbe pas** ;  
- conserver **ouverts** les points non arbitrés ;  
- **ne pas** figer catalogue nommé, durée, coût numérique, Hertz, persistance, ResourceKey, ni API C++.

Les identifiants **Q1–Q31** ci-dessous sont le **cadrage accepté**, pas un second Design Gate.

---

## 2. Référentiel des décisions utilisées

### 2.1 Conception VALIDÉE (Design Gate — non modifié ici)

**07.1** (VALIDÉ) — reprise intégrale :

> « Le bâtiment principal est le hub de départ : stock, capacité de base, extraction élémentaire et ancrage de progression. Il n’est pas le bâtiment de recherche ; la recherche est portée par un bâtiment dédié (07.2). Évolution hybride : modules/extensions prioritaires, complétés lorsque pertinent par niveaux et/ou remplacement par un schéma supérieur. Le principal débloque uniquement les premiers schémas et capacités de base, sans large panier automatique. »

**07.2** (VALIDÉ) — reprise intégrale :

> « La recherche doit être portée par un véritable bâtiment et fonctionner comme une activité du monde avec coûts, capacités et dépendances ; elle ne doit pas être uniquement un menu. »

**07.3** (VALIDÉ) — reprise intégrale :

> « Un schéma est une autorisation durable de construire, transformer ou utiliser une possibilité correspondante. Obtention possible par : Recherche ; Acquisition / déblocage territorial ; fourniture au départ ; variante d’évolution. Les schémas ne sont pas consommés au fondateur. La Recherche peut produire des technologies et/ou des schémas. Il n’existe pas de chaîne unique obligatoire Recherche → Technologie → Schéma. »

**07.4** (VALIDÉ) — reprise intégrale :

> « Une technologie représente une capacité ou un système nouveau : domaine, milieu, réseau, chaîne, opération ou autre possibilité structurante. Organisation par domaines/paliers, sans arbre technologique unique obligatoire. Prérequis possibles : technologie(s), bâtiment vivant et/ou condition territoriale, selon le cas. »

**07.5** (VALIDÉ) — reprise intégrale :

> « Une progression peut débloquer de nouveaux bâtiments, ressources, unités, équipements, infrastructures et transformations. »

**07.6** (VALIDÉ) — reprise intégrale :

> « Priorité de progression : Nouveaux domaines → Environnements/accès → Réseaux/modes → Chaînes de ressources → Opérations/transformations. La progression horizontale est prioritaire ; les améliorations d’efficacité sont secondaires et rares. Formes de progression autorisées : nouveau schéma de bâtiment ; module de mobilité ; nouveau mode de transport ; nouvelle ressource. »

**07.7** (VALIDÉ) — reprise intégrale :

> « Ordre de progression confirmé (02.10) : Aménagements forestiers → Zones humides → Retenues → Lacs → Rivières / grands aménagements hydrologiques. Portes de progression : Recherche + bâtiments dédiés. Les effets et comportements écologiques sont définis dans DG-09, pas dans DG-07. »

| ID | Portée reprise |
| --- | --- |
| **00.4** | Recherche / Technologie / Schéma = **trois notions distinctes**, sans chaîne unique imposée. |
| **00.5.T2** | Trois ordres de durée : court (tâches), moyen (opérations/chantiers), long (recherche / progression / évolution écologique). **Valeurs chiffrées À DÉFINIR.** |
| **00.5.U6** | Équipement modulaire interne dès le fondateur ; configurations de contenu limitées. **Contenu exact ouvert.** |
| **01.5** | Une construction devient « vivante » à la mise en service si une fonction est réellement utilisable. Des déblocages en cascade **peuvent** se déclencher alors **si** DG-07 les autorise. La mise en service **n’est pas** à elle seule une autorisation C-18. |
| **02.3** | Catalogue de boucle minimale déjà VALIDÉ côté DG-02 (principal, exploitation forestière, stockage, logistique/atelier, recherche). Ce n’est **pas** un catalogue technologique C-18. |
| **02.10** | Deux couches d’impact ; grandes transformations intentionnelles plus tard ; déblocage = recherche + bâtiments dédiés. Ordre repris par **07.7**. |
| **05.4** | Vecteurs d’apparition de ressources : recherche / technologie ; bâtiments vivants / déblocages ; état du territoire / écosystèmes. C-18 ne crée **aucune** ResourceKey. |
| **13.1** | Le joueur doit comprendre disponible / verrouillé / cause. C-18 fournit la **règle exprimable**. C-20 porte la **présentation**. |
| **13.4** | Progression = ouverture du monde, pas accumulation de bonus. Aligné sur **07.6**. |

### 2.2 Cadrage accepté (questionnaire C-18 Q1–Q31 — pas de nouvelle conception)

| # | Contenu accepté |
| --- | --- |
| **Q1** | Titre canonique **Technologie / progression**. Politique Ages = sous-titre / corps, pas le nom. |
| **Q2** | C-18 est **requis** et **bloquant** avant déblocages réels DG-07. `PARTIEL` = couverture actuelle, pas facultativité. |
| **Q3** | C-18 possède les règles de conception : recherche-monde, technologies, schémas, autorisations durables, familles de déblocages, sémantique des conditions, distinction autorisé / effectivement possible. L’exécution reste chez les propriétaires. |
| **Q4** | Les écarts documentaires sont **signalés** ici. Ils ne sont **pas** corrigés par cette rédaction. |
| **Q5** | **DG-07** est la seule vérité de conception de la progression. Ages I–III = isolé, **non-autorité**. **Aucun** mapping Age ↔ domaine, technologie ou palier. |
| **Q6** | `TechComponent`, définitions d’âge, HUD FWSG = legacy / présentation isolée. Pas de source de vérité métier cible. |
| **Q7** | S3 et Investor Demo restent **hors** C-18, hors Ages, hors recherche et hors déblocages DG-07. Leurs décisions ne sont pas rouvertes. |
| **Q8** | 07.1 = principe : principal ≠ recherche ; premiers schémas / capacités de base seulement. Pas de large panier. Pas de liste nommée. |
| **Q9** | 07.2 = existence et familles de conditions (bâtiment, ressources, temps, capacité, dépendances). Pas de fiche, timer, barème, ni cycle de tâches. |
| **Q10** | C-18 possède la **sémantique** du schéma : autorisation durable, non consommée au fondateur. L’exécution concrète = propriétaires. |
| **Q11** | Organisation par domaines / paliers **en principe**. **Aucun** catalogue technologique exhaustif ni liste arbitraire de technologies nommées. |
| **Q12** | Six familles de déblocage 07.5 : bâtiments, ressources, unités, équipements, infrastructures, transformations. Cadre de conception, pas preuve runtime. |
| **Q13** | Progression **horizontale** prioritaire (07.6, 13.4). Un déblocage « efficacité seule » serait non conforme en conception. Pas de calendrier de paliers. |
| **Q14** | Portes environnementales = **autorisations** de progression (recherche + bâtiments dédiés). Effets = DG-09 / C-15 / C-16 / C-17. |
| **Q15** | C-00 **NON REQUIS**. DG-00 reste l’autorité identifiée. Pas de contrat C-00 créé ici. |
| **Q16** | C-03\* reste **fermé**. C-18 n’invente **aucune** règle Intention → Project. |
| **Q17** | C-14 reste propriétaire du cycle de vie et de la mise en service. En service ≠ débloqué. |
| **Q18** | C-17 reste propriétaire des états et transitions écologiques. C-18 ne clôture **aucune** question Q1–Q12 / O1–O9 / P1–P10. Type « transformation » seulement, sous lecture propriétaire utilisable. |
| **Q19** | C-18 = règles d’autorisation exprimables. C-20 = présentation UI. Pas de wording HUD imposé. |
| **Q20** | Addenda C-03\* · C-06\* · C-09\* · C-10\* · C-13\* **non rouverts**. C-18 peut renvoyer à une ressource, capacité ou service **déjà** définie ; il n’en crée pas. |
| **Q21** | **Aucune** ResourceKey créée. **Aucune** nouvelle règle de propriété de stocks, plafond ou critère universel de service. |
| **Q22** | Food / Wood / Stone / Gold = ressources **historiques Ages**, non-autorité économique cible. **Aucun** mapping Wood ↔ Timber. |
| **Q23** | Coûts cadrés par **familles** seulement. Aucun montant, durée ni cadence inventés. |
| **Q24** | Cinq couches distinctes (§6). **Pas** une chaîne unique obligatoire pour tous les cas. |
| **Q25** | `RequiredAge` ≠ autorisation DG-07. Écart documenté. **Ni** suppression **ni** remplacement de code par ce contrat. |
| **Q26** | Autorisation technologique / bâtimentaire possible dans son périmètre. **Aucun** verrou runtime sur stub `QueryWater` / `QuerySoil`, Paint / M4, apparence, nom de biome ou état écologique non fourni par une lecture métier valide et exploitable. |
| **Q27** | Scission : décisions **indépendantes** (concevables maintenant) vs **conditionnelles** (R1–R8, R11, §13.2). R9 / R10 = hors périmètre ; mappings Ages / Wood = interdictions validées (§13.3). |
| **Q28** | T2 et U6 restent **ouverts**. Recherche = ordre de durée **long** en principe. Pas de secondes, pas de loadout nommé. |
| **Q29** | Critères d’audit du **texte** (§12). Pas d’exigence runtime. |
| **Q30** | Même un futur `VALIDÉ` resterait **documentaire**. Il n’autoriserait pas, à lui seul, l’implémentation. |
| **Q31** | Écarts documentaires classés (§14) : descriptibles ici / correction séparée / hors périmètre. |

Note de traçabilité — les codes **Q1–Q31** de ce §2.2 sont le **cadrage C-18**, pas des items Design Gate. `07.*` / `00.4` / `01.5` / `02.10` / `13.*` restent les seuls identifiants Design Gate de progression.

### 2.3 Contrats amont et voisins déjà VALIDÉS (lus, non réécrits)

| Source | Reprise pour C-18 |
| --- | --- |
| **C-00 / DG-00** | Autorité de cadre et de vocabulaire. Pas de fichier contrat dédié (Q15). |
| **C-03\*** | Addendum **fermé**. C-04 J3 : partir de l’existant ; **pas** de nouvelle règle Intention→Project (Q16). |
| **C-04 J3** | C-03 reste fermé. C-18 n’ouvre pas un graphe de tâches de recherche. |
| **C-06\*** | Capacités / roster **fermés**. C-18 peut autoriser une famille « unité / équipement » ; il n’ajoute aucune cap. |
| **C-09\*** / **C-10\*** | Économie physique / stocks **fermés**. Clé officielle S3 = `Timber`. C-18 n’en crée pas (Q20, Q21). |
| **C-13\*** | Critère cohorte Achevé / En service **fermé**. Distinct du lifecycle C-14 et de l’autorisation C-18. |
| **C-14 A3 / B2** | Cycle de vie, Achevé ≠ En service. DG-02 reste propriétaire des définitions de bâtiments. |
| **C-15 G / O1–O9** | Vérité hydrologique. Stub `QueryWater` ≠ vérité. **O1–O9 restent ouverts.** |
| **C-16 A1 / P1–P10** | Vérité sol. Stub `QuerySoil` ≠ vérité. **P1–P10 restent ouverts.** |
| **C-17 A2 / E1 / E2 / Q1–Q12** | Vérité végétation / écosystème. Paint `Forest` ≠ forêt. **Q1–Q12 restent ouverts.** |

---

## 3. Responsabilités et frontières

### 3.1 Ce que C-18 possède

1. Les **règles de conception** de la recherche comme **activité du monde** (07.2, Q9).  
2. Les **règles de conception** des technologies : domaines / paliers, prérequis possibles, **sans** arbre unique (07.4, Q11).  
3. La **sémantique des schémas** : autorisation durable, sources d’obtention, non-consommation au fondateur (07.3, Q10).  
4. Les **autorisations durables** et leur distinction d’avec l’accès effectif (Q3, Q24).  
5. Les **six familles de déblocages** (07.5, Q12).  
6. La **sémantique des conditions de progression**, y compris les portes environnementales **comme autorisations** (07.7, Q14).  
7. La **distinction** entre capacité autorisée et action effectivement possible (Q3, Q24 couche 5).  
8. Le **signal d’autorisation** aux systèmes consommateurs (couche 4) — existence et sens, **pas** leur réaction.

### 3.2 Ce que C-18 ne possède pas

| Domaine | Autorité |
| --- | --- |
| Cadre / vocabulaire fondateur | **DG-00** (C-00 NON REQUIS) |
| Intention → Project | **C-03\*** fermé — non rouvert |
| Graphe de tâches, dépendances opérationnelles | **C-04** |
| Capacités / roster | **C-06\*** fermé |
| Autonomie d’unité | **C-07** |
| Travaux / défrichement | **C-08** |
| ResourceKey, stocks, ownership | **C-09\*** / **C-10\*** fermés |
| Réservations | **C-11** |
| Transport / réseaux (exécution) | **C-12** / **DG-06** |
| Critère cohorte Achevé / En service | **C-13\*** fermé |
| Cycle de vie, mise en service, emprise | **C-14** |
| Vérité hydrologique, `QueryWater`, O1–O9 | **C-15** |
| Vérité sol, `QuerySoil`, P1–P10 | **C-16** |
| Végétation, états écologiques, Q1–Q12 | **C-17** |
| Persistance / sauvegarde | **C-19** |
| Présentation UI, wording, HUD | **C-20** |
| Fréquences, budgets, Hertz | **C-21** |
| Définitions de bâtiments (fiches) | **DG-02** |
| Effets et comportements écologiques | **DG-09** / contrats propriétaires |
| S3 / Investor Demo | Preuves et docs existants — **hors C-18** |

### 3.3 Ce que C-18 lit

| Lecture | Autorité | Usage C-18 |
| --- | --- | --- |
| Existence / mise en service / « vivant » d’un bâtiment | **C-14** / **01.5** | Prérequis « bâtiment vivant » (07.4) — C-18 n’écrit pas l’état lifecycle |
| Tâches / graphe d’une activité de recherche | **C-04** | C-18 n’ouvre **pas** ce graphe ; il ne prescrit pas le cycle opérationnel |
| Ressource / stock déjà défini | **C-09\*** / **C-10\*** fermés | Famille de coût seulement, si une clé **déjà** autorisée existe |
| Lecture hydrologique **valide et utilisable** | **C-15** | Condition d’autorisation **future**, jamais via stub |
| Lecture sol **valide et utilisable** | **C-16** | Idem |
| État écologique **valide et utilisable** | **C-17** | Idem ; Q1–Q12 ouverts |
| Vocabulaire Recherche / Technologie / Schéma | **00.4** | Distinguer les trois notions |

Une lecture **absente**, **inconnue**, **invalide** ou **non utilisable** **n’est jamais** une condition environnementale satisfaite (Q18, Q26).

### 3.4 Ce que C-18 expose (conception ; ≠ runtime)

Lorsque C-18 sera `VALIDÉ` **et** qu’une implémentation aura été **autorisée distinctement** :

- l’état d’**acquisition** d’une technologie (couche 1) ;  
- l’état d’**obtention** d’un schéma (couche 2) ;  
- l’**autorisation durable** correspondante (couche 3) ;  
- un **signal** aux consommateurs (couche 4).

Tant que C-18 n’est pas `VALIDÉ` et implémenté, **aucune** lecture runtime Ages / `RequiredAge` / HUD FWSG n’est cette exposition.

### 3.5 Ce que C-18 signale

C-18, en conception, définit qu’un changement **réel** d’autorisation — technologie acquise, schéma obtenu, autorisation durable née au sens 07.3 — **doit pouvoir** être signalé aux consommateurs.

Un schéma obtenu est une **autorisation durable**, **non consommée** au moment de son obtention (07.3, Q10).  
Ce contrat **ne définit pas** et **n’autorise pas** un mécanisme de révocation.

Il **ne prescrit pas** leur réaction (même principe que C-17 §3.4).  
Il **n’exécute pas** la construction, la mise en service, la dépense, ni l’effet écologique.

---

## 4. Modèle de progression

### 4.1 Autorité de conception (Q5)

**DG-07** est la référence conceptuelle cible.  
Ages I–III n’est **pas** un second modèle de progression.  
Les deux stacks **coexistent aujourd’hui** dans le dépôt (constat §11) ; seule DG-07 a autorité sur les règles métier **cibles**.

Aucun mapping n’est autorisé par ce contrat entre :

- un Age et un domaine ;  
- un Age et une technologie ;  
- un Age et un palier ;  
- `RequiredAge` et une autorisation C-18 ;  
- Wood et Timber.

### 4.2 Trois notions distinctes (`00.4`, 07.3)

| Notion | Sens C-18 | N’est pas |
| --- | --- | --- |
| **Recherche** | Activité du monde portée par un bâtiment dédié (07.2) | Un menu seul ; un Age ; une tâche C-04 |
| **Technologie** | Capacité ou système nouveau, organisé par domaines / paliers (07.4) | Un schéma ; un Age ; un ResourceKey |
| **Schéma** | Autorisation durable de construire, transformer ou utiliser (07.3) | Une consommation ; une mise en service ; une fiche C-14 |

La Recherche **peut** produire des technologies et/ou des schémas.  
Il **n’existe pas** de chaîne unique obligatoire Recherche → Technologie → Schéma.

### 4.3 Chemin principal distinct de la recherche (07.1, Q8)

Le bâtiment principal est le **hub de départ**.  
Il **n’est pas** le bâtiment de recherche.  
Il débloque uniquement les **premiers** schémas et capacités de base, **sans** large panier automatique.

L’évolution physique du principal (modules, niveaux, remplacement par un schéma supérieur) relève de **C-14** / **DG-02** pour l’exécution et les fiches.  
C-18 porte seulement le **principe d’autorisation** de ces premiers schémas.

Aucun roster nommé n’est ajouté ici (Q11).  
`02.3` reste une décision **DG-02**, citée, non absorbée.

### 4.4 Technologies par domaines et paliers (07.4, Q11)

Une technologie est une **possibilité structurante** (domaine, milieu, réseau, chaîne, opération ou équivalent déjà prévu par 07.4).

Organisation **autorisée** : domaines et paliers.  
Organisation **interdite comme obligation** : un arbre technologique unique.

Prérequis **possibles**, selon le cas, déjà prévus par 07.4 :

- une ou plusieurs technologies ;  
- un bâtiment **vivant** (sens `01.5` / C-14) ;  
- une condition territoriale **lorsque** la donnée propriétaire est valide et exploitable.

Aucun catalogue nommé. Aucun palier chiffré. Aucune correspondance Age.

### 4.5 Progression horizontale (07.6, 13.4, Q13)

Priorité de conception, dans cet ordre de préférence :

1. nouveaux domaines ;  
2. environnements / accès ;  
3. réseaux / modes ;  
4. chaînes de ressources ;  
5. opérations / transformations.

La progression horizontale est **prioritaire**.  
Les améliorations d’efficacité sont **secondaires et rares**.

Formes déjà autorisées par 07.6 : nouveau schéma de bâtiment ; module de mobilité ; nouveau mode de transport ; nouvelle ressource.

Un déblocage conçu **uniquement** comme hausse numérique d’efficacité, sans ouverture de possibilité, serait **non conforme** à C-18 **en conception**.  
Aucun calendrier, aucun barème d’efficacité n’est fixé ici.

---

## 5. Recherche

### 5.1 Nature (07.2, Q9)

La recherche est une **activité du monde**.  
Elle n’est pas une progression abstraite déclenchée par un menu seul.

Elle doit être portée par un **véritable bâtiment** distinct du principal (07.1, 07.2).

### 5.2 Familles de conditions pertinentes (Q9, Q23)

C-18 autorise les familles suivantes comme **cadre** :

| Famille | Sens | Non fixé ici |
| --- | --- | --- |
| **Bâtiment** | Un bâtiment de recherche **vivant** au sens `01.5` | Fiche, emprise, lifecycle (C-14 / DG-02) |
| **Ressources** | Un coût d’une ressource **déjà** définie ailleurs | ResourceKey nouvelle ; montant ; Wood/FWSG |
| **Temps** | Ordre de durée **long** (`00.5.T2`) | Secondes, ticks, barème |
| **Capacité** | Une capacité d’accueil / de file pertinente | Chiffre ; roster C-06\* |
| **Dépendances** | Prérequis technologiques, bâtimentaires ou territoriaux **déjà prévus** par 07.4 | Graphe C-04 ; Intention→Project |

Ces familles **ne deviennent pas** un cycle opérationnel de tâches.  
C-04 reste propriétaire des tâches si une activité de recherche est un jour exécutée.  
C-18 **n’ouvre pas** ce graphe.

### 5.3 Ce que la recherche n’est pas

- un Age ;  
- `TryAdvanceAge` / `AdvanceCost` ;  
- un menu HUD FWSG ;  
- une Intention→Project (C-03\* fermé) ;  
- une durée chiffrée T2 ;  
- une preuve S3 / Demo.

---

## 6. Schémas, autorisations et cinq couches

### 6.1 Schéma (07.3, Q10)

Un schéma est une **autorisation durable** de construire, transformer ou utiliser une possibilité correspondante.

Sources d’obtention **déjà prévues** par 07.3 :

- recherche ;  
- acquisition / déblocage territorial ;  
- fourniture au départ ;  
- variante d’évolution.

Au fondateur, les schémas **ne sont pas consommés** par l’usage.

C-18 possède l’**acquisition** et la **sémantique**.  
L’exécution concrète (construire, transformer, utiliser) appartient aux contrats propriétaires (C-14, C-04, C-08, économie fermée, etc.).

### 6.2 Les cinq couches (Q24)

Les couches suivantes sont **distinctes**. Elles ne forment **pas** une chaîne unique obligatoire pour tous les cas (`00.4`, 07.3).

| # | Couche | Sens | Autorité |
| --- | --- | --- | --- |
| **1** | Acquisition technologique | Une technologie est acquise | **C-18** (règle) |
| **2** | Obtention du schéma | Un schéma est obtenu | **C-18** (règle) |
| **3** | Autorisation durable | La possibilité correspondante est autorisée de façon persistante au fondateur | **C-18** (sémantique) |
| **4** | Signal aux consommateurs | Les systèmes concernés peuvent être informés du changement d’autorisation | **C-18** définit le signal ; le consommateur reste maître de sa réaction |
| **5** | Accès effectif | L’action est réellement possible ici et maintenant | **Propriétaires** : C-14 (vivant / en service), C-04 (tâches), économie / caps déjà définies, lectures environnementales utilisables, etc. |

Règles d’emploi :

1. Une couche 1 **n’implique pas** automatiquement une couche 2.  
2. Une couche 2 **n’implique pas** automatiquement une couche 1.  
3. Les couches 1 à 3 **ne se fusionnent pas**.  
4. La couche 4 **n’exécute rien**.  
5. La couche 5 **peut échouer** alors que les couches 1–3 sont satisfaites (bâtiment non en service, stock insuffisant, lecture environnementale non utilisable, tâche bloquée).  
6. `01.5` : une mise en service **peut** déclencher des déblocages en cascade **seulement si** les couches C-18 les autorisent. C-14 ne s’arroge pas cette autorisation.

### 6.3 Capacité autorisée vs action possible (Q3, Q17)

| État | Signification |
| --- | --- |
| **Autorisé** (couches 1–3) | La conception permet cette possibilité. |
| **Signalé** (couche 4) | Un consommateur peut en tenir compte. |
| **Effectivement possible** (couche 5) | Les préconditions opérationnelles du propriétaire sont aussi réunies. |

**En service** (C-14) n’est **pas** synonyme de **débloqué** (C-18).  
**Débloqué** n’est **pas** synonyme de **constructible / utilisable maintenant**.

---

## 7. Familles de déblocages

### 7.1 Les six familles (07.5, Q12)

Une progression **peut** autoriser, dans le cadre de conception :

1. **Bâtiments**  
2. **Ressources**  
3. **Unités**  
4. **Équipements**  
5. **Infrastructures**  
6. **Transformations**

Ces familles sont un **cadre**.  
Elles **ne prouvent pas** que les fonctionnalités correspondantes existent déjà dans le runtime.  
Elles **n’autorisent pas** C-18 à créer le contenu de ces familles.

### 7.2 Frontière par famille

| Famille | C-18 peut | C-18 ne peut pas |
| --- | --- | --- |
| Bâtiments | Autoriser un schéma / une tech de bâtiment | Posséder le lifecycle, la fiche DG-02, la mise en service |
| Ressources | Autoriser l’apparition d’une ressource **déjà** définie (`05.4`) | Créer une ResourceKey, un stock, un mapping Wood↔Timber |
| Unités | Autoriser une famille d’unité | Ajouter une capacité C-06\* ou un roster |
| Équipements | Autoriser une famille d’équipement | Trancher U6 (contenu exact ouvert) |
| Infrastructures | Autoriser un schéma d’infrastructure | Posséder C-14 / C-12 / C-13\* |
| Transformations | Autoriser une ambition de transformation (07.7 / 02.10) | Posséder l’effet C-15 / C-16 / C-17 ni fermer leurs questions |

### 7.3 Transformations et portes 07.7 (Q14, Q18)

Ordre de conception **déjà VALIDÉ** (07.7 / 02.10), comme **ambition d’autorisation**, non comme preuve runtime :

Aménagements forestiers → Zones humides → Retenues → Lacs → Rivières / grands aménagements hydrologiques.

Portes de progression : **recherche + bâtiments dédiés**.  
Effets et comportements = **DG-09** et contrats propriétaires.

C-18 **peut viser** cet ordre comme principe d’autorisation.  
C-18 **n’exécute** aucune transformation.  
C-18 **ne clôture** aucune question C-15 / C-16 / C-17.

Les limites actuelles (lectures non utilisables, stubs, contrats de conception) **ne sont pas** une interdiction permanente d’une simulation environnementale plus approfondie.  
Elles **interdisent seulement** de fonder **aujourd’hui** un verrou d’exécution sur une donnée invalide.

---

## 8. Conditions environnementales

### 8.1 Sémantique (Q14, Q26)

C-18 définit la sémantique des **autorisations de progression** qui **peuvent** dépendre de l’environnement.

Il **ne possède pas** :

- la vérité hydrologique (**C-15**) ;  
- les règles métier des sols (**C-16**) ;  
- l’état écologique (**C-17**).

Une autorisation environnementale **exécutable** exige une donnée métier :

1. définie par son contrat propriétaire ;  
2. validée dans ce contrat ;  
3. effectivement **exploitable** (pas seulement déclarée).

Tant que ces trois conditions ne sont pas réunies, C-18 peut encore définir :

- une autorisation **technologique** ;  
- une autorisation **bâtimentaire** (recherche + bâtiment dédié, 07.7) ;

mais **aucun verrou d’exécution** environnemental.

### 8.2 Interdictions d’entrée (Q26)

Aucune autorisation runtime, aucun test de porte, aucune condition de couche 5 **ne peut** reposer sur :

- `QueryWater` ou `QuerySoil` présentés comme vérités métier complètes ;  
- un stub, une constante technique (`Moisture = 0.5`) ou une donnée invalide ;  
- une couche Paint, un matériau, M4, UDS, UDW ;  
- une apparence visuelle de forêt, de marais, d’eau ou de sol ;  
- un nom de biome ;  
- un état écologique **non** fourni par une lecture C-17 **valide et exploitable**.

### 8.3 Questions amont conservées ouvertes

Ce contrat **ne ferme pas** :

- **O1–O9** de C-15 ;  
- **P1–P10** de C-16 ;  
- **Q1–Q12** de C-17.

Il **n’invente** aucun seuil environnemental.

---

## 9. Ressources, coûts et addenda fermés

### 9.1 Non-autorité économique (Q20–Q23)

C-18 **ne transforme pas** Food / Wood / Stone / Gold en vérité économique du modèle DG-07.  
C-18 **ne crée pas** de ResourceKey, de règle de stock, de plafond, ni de critère universel de service.  
C-18 **n’établit pas** de correspondance Wood ↔ Timber.

La clé `Timber` demeure une décision **S3 / C-09\*** déjà close. C-18 peut la **citer** comme ressource déjà définie ; il ne l’étend pas.

Les coûts de recherche ou d’acquisition restent des **familles** (ressources / temps / capacité).  
Les **valeurs numériques** restent ouvertes (R2, R3).

`AdvanceCost` et les dépenses Ages via `EconomyComponent` sont du **legacy**. Ils ne sont **pas** le modèle de coût C-18.

### 9.2 Addenda non rouverts (Q16, Q20)

| Addendum | Règle C-18 |
| --- | --- |
| **C-03\*** | Fermé. Pas de règle Intention → Project. |
| **C-06\*** | Fermé. Pas de nouvelle capacité. |
| **C-09\*** | Fermé. Pas de nouvelle économie / ResourceKey. |
| **C-10\*** | Fermé. Pas de nouvelle ownership de stock. |
| **C-13\*** | Fermé. Pas de critère universel de service. |

Rouvrir l’un de ces addenda exigerait une **autorisation humaine distincte**, hors C-18.

---

## 10. Legacy Ages et écarts constatés

### 10.1 Qualification (Q5, Q6, Q22, Q25)

Qualification : **vérifié dans le dépôt** lors de la rédaction.  
Ces mécanismes sont des **constats**. Ils **ne sont pas** les règles cibles.

| Mécanisme | Constat actuel | Rôle contractuel C-18 |
| --- | --- | --- |
| `EGardenFervorTechAge` (Age1–Age3) | **Présent** | Legacy. Non-autorité. Pas de mapping vers un palier DG-07 |
| `UGardenFervorTechComponent` / `TryAdvanceAge` | **Présent** | Legacy. Isolé. Ne pas étendre (HISTORIQUE) |
| `UGardenFervorTechAgeDefinition` | **Présent** | Legacy. Coûts / règles d’âge ≠ C-18 |
| `RequiredAge` (`BuildingDefinition`, `UnitDefinition`) | **Présent** | **≠** autorisation DG-07. Ni supprimé ni remplacé par ce contrat |
| HUD FWSG (`GardenFervorRTSHUDWidget`) | **Présent** | Présentation legacy isolée. Pas une SoT |
| Food / Wood / Stone / Gold | **Présents** (économie Ages) | Legacy. ≠ `Timber`. Pas de mapping |
| Recherche / schéma / tech DG-07 runtime | **Absent** | Dette / absence. Pas une preuve |
| S3 / Demo | Isolés : pas d’Ages, pas de recherche DG-07 | **Hors C-18** (Q7) |

Les règles §2–§8 sont **normatives cibles de conception**.  
Le runtime Ages est une **dette isolée**, pas une base à généraliser.

### 10.2 Politique d’isolement (Q5, Q6, Q7, Q25)

C-18 **ne demande pas**, et **n’autorise pas par lui-même** :

- la suppression du stack Ages ;  
- sa migration vers DG-07 ;  
- le remplacement de `RequiredAge` ;  
- l’extension d’Ages à S3 ou à la Demo ;  
- l’usage du HUD FWSG comme vérité de déblocage.

S3 et la Demo restent les preuves **déjà VALIDÉES** sans Ages.  
Ce contrat **ne les rouvre pas**.

---

## 11. Dépendances et échanges

```text
DG-00 / 00.4     vocabulaire  ──────────────►  C-18
DG-07            principes VALIDÉS  ────────►  C-18
C-14             vivant / en service  ──lit──►  C-18  (prérequis bâtiment)
C-18             autorisation  ──signale──►  C-14 / C-04 / consommateurs
C-15 / C-16 / C-17  lectures utilisables  ──►  C-18  (portes futures seulement)
C-18             n’écrit pas  ──────────────►  eau / sol / éco / lifecycle
C-19             persistance  ──────────────►  hors C-18
C-20             UI  ◄──règle exprimable──  C-18
C-21             Hertz  ────────────────────►  hors C-18
Ages / HUD FWSG  legacy isolé  ─────────────►  non-autorité
M4 / Paint       représentation  ───────────►  jamais une porte
```

| Contrat | C-18 lit | C-18 n’absorbe pas |
| --- | --- | --- |
| **C-14** | En service / vivant | Cycle de vie, emprise, démontage |
| **C-04** | — | Graphe, cycle de recherche opérationnel |
| **C-15** | Lecture eau **utilisable** (future) | O1–O9, `QueryWater`, structures hydrauliques |
| **C-16** | Lecture sol **utilisable** (future) | P1–P10, humidité / fertilité / compaction |
| **C-17** | Lecture éco **utilisable** (future) | Q1–Q12, états, transitions |
| **C-09\*** / **C-10\*** | Clé déjà définie, si citée | ResourceKey, stocks |
| **C-19** | — | Politique de sauvegarde |
| **C-20** | — | UX, wording, HUD |
| **C-21** | — | Fréquences / budgets |

---

## 12. Critères de conformité du contrat

Un audit indépendant pourra vérifier ce contrat **sans** exiger une implémentation, s’il constate que le document :

1. reprend 07.1–07.7 **intégralement** et sans les altérer ;  
2. formalise Q1–Q31 sans nouvelle conception ;  
3. titre **Technologie / progression** et traite Ages comme legacy non-autorité ;  
4. distingue `PARTIEL` (couverture) de **requis / bloquant** (nécessité) ;  
5. attribue à C-18 les règles de progression / autorisation, **pas** l’exécution propriétaire ;  
6. sépare les **cinq couches** et refuse une chaîne unique obligatoire ;  
7. traite le schéma comme autorisation durable non consommée au fondateur ;  
8. reprend les six familles 07.5 comme cadre, sans catalogue nommé ;  
9. privilégie la progression horizontale (07.6) ;  
10. n’impose **aucun** mapping Age → DG-07 ni Wood → Timber ;  
11. n’invente **aucun** seuil, durée, coût numérique, Hertz ni ResourceKey ;  
12. ne rouvre **aucun** addendum fermé et n’invente **aucune** règle Intention→Project ;  
13. laisse **ouverts** O1–O9, P1–P10, Q1–Q12 C-17 et R1–R8, R11 ; classe R9 / R10 hors périmètre ; maintient les interdictions de mapping (§13.3) ;  
14. refuse tout verrou runtime sur stub / Paint / visuel / biome non lu ;  
15. maintient S3 / Demo hors dépendance DG-07 ;  
16. se déclare **VALIDÉ** comme contrat de conception uniquement, sans preuve runtime ni autorisation d’implémentation (Q30).

Critères de **conformité runtime** — uniquement **après** validation du contrat **et** autorisation d’implémenter distincte — indicatifs, **non exécutés** :

- une porte environnementale ne lit ni stub, ni Paint, ni visuel ;  
- `RequiredAge` n’est pas présenté comme autorisation C-18 ;  
- Food/Wood/Stone/Gold n’est pas présenté comme économie DG-07 ;  
- une mise en service seule n’est pas présentée comme déblocage si C-18 ne l’autorise pas.

---

## 13. Points ouverts, hors périmètre et limites validées

Les identifiants **R1–R8** et **R11** sont les seuls encore **ouverts** pour C-18.  
Ils **ne remplacent pas** O1–O9, P1–P10 ni Q1–Q12 de C-17.  
R9, R10 et les mappings Ages / Wood relèvent du **§13.3** : hors périmètre ou interdictions déjà arbitrées.

### 13.1 Concevable maintenant (indépendant — déjà tranché en principe)

Les sections §1–§10 suffisent à rédiger les règles de conception **sans** attendre R1–R8 ni R11.

### 13.2 Conditionnel — dépend d’un autre contrat ou d’une valeur absente (Q27)

Identifiants encore **ouverts** pour C-18. Ce ne sont **pas** des interdictions déjà tranchées.

| # | Sujet | Pourquoi ce n’est pas tranché ici |
| --- | --- | --- |
| **R1** | Catalogue nommé de technologies / schémas | Q11 : aucun roster imposé |
| **R2** | Montants de coût | Q23 : familles seulement |
| **R3** | Valeurs chiffrées T2 (durée de recherche) | `00.5.T2` À DÉFINIR (Q28) |
| **R4** | Configurations d’équipement U6 | `00.5.U6` ouvert (Q28) |
| **R5** | Persistance de l’état de recherche / tech / schéma | **C-19** |
| **R6** | Fréquences, budgets, Hertz d’une activité de recherche | **C-21** |
| **R7** | Présentation, wording, HUD de disponibilité / verrou | **C-20** ; 13.1 = règle exprimable seulement |
| **R8** | Verrou environnemental **exécutable** | Lectures C-15 / C-16 / C-17 utilisables ; O\* / P\* / Q\* ouverts |
| **R11** | Cycle opérationnel de tâches d’une recherche | **C-04** ; C-18 n’ouvre pas le graphe |

| — | **O1–O9 C-15** | Inchangés |
| — | **P1–P10 C-16** | Inchangés |
| — | **Q1–Q12 C-17** | Inchangés |

### 13.3 Hors périmètre et limites validées (non arbitrables par C-18)

Ces éléments **ne sont pas** des questions ouvertes de C-18. Ils ne figurent plus comme décisions à trancher ici.

**R9 — ResourceKey, stocks, plafonds, critère universel de service (Q20, Q21).**  
Hors périmètre. Les addenda C-09\* / C-10\* / C-13\* restent **fermés**. C-18 n’invente aucune ResourceKey, aucune règle de propriété de stocks, aucun plafond ni critère universel de service. Une réouverture de ces sujets exige une **autorisation humaine distincte et explicite**, hors C-18. Aucune règle d’économie nouvelle n’est créée ici.

**R10 — Intention → Project (Q16).**  
Hors périmètre. L’addendum C-03\* reste **fermé**. C-18 n’invente **aucune** règle Intention → Project, y compris pour une recherche. Une réouverture exige une **autorisation humaine distincte et explicite**, hors C-18.

**Mappings Ages et Wood (Q5, Q22) — interdictions validées.**  
Ce contrat **interdit** tout mapping entre Ages I–III et un domaine, une technologie ou un palier DG-07, ainsi que tout mapping Wood → Timber. Ces limites sont déjà arbitrées (§4.1, §9.1, §15.10, §17). Elles **ne sont pas** une question ouverte que C-18 pourrait résoudre. Toute révision future relèverait d’une décision humaine **distincte**, hors le présent cadrage.

---

## 14. Vérification documentaire — divergences signalées (non corrigées)

Ces écarts existent **avant** ou **autour** de C-18. Ce contrat **ne les résout pas** en modifiant le registre, le suivi, le Design Gate, le Hub ou les contrats voisins (Q4, Q31).

### 14.1 Descriptibles dans C-18 (faits dans ce fichier)

1. Titre officiel **Technologie / progression** vs intitulé registre §5 « hors Ages legacy » : politique Ages = sous-titre, pas le nom (Q1).  
2. `PARTIEL` registre / suivi = couverture DG-07 actuelle, **pas** facultativité (Q2).  
3. Amont officiel C-00 · C-03 : C-00 sans fichier ; C-03 addendum fermé — cités, non rouverts (Q15, Q16).  
4. Tension Ages / FWSG vs DG-07 (registre §8.2) : DG-07 = vérité cible ; Ages = legacy isolé (Q5, Q6).

### 14.2 Corrections nécessitant une autorisation séparée

1. Ajouter C-18 à la table **bloquante** du registre §6 (absente aujourd’hui).  
2. Harmoniser le titre §5 du registre avec le titre canonique.  
3. Suivi : passer C-18 de `NON COMMENCÉ` à un statut de rédaction — **hors cette étape**.  
4. Suivi Git de `CONTRATS/C-17_VEGETATION_ECOSYSTEMES.md` s’il demeure non suivi.  
5. Sync Hub / `contractsSuivi.js` / pages `docs/` — **hors cette clôture de fichier**.  
6. **Suivi / compteur.** Ce fichier est **VALIDÉ** documentairement comme contrat de conception. Il n’est **pas** une preuve runtime. La mise à jour du suivi et du compteur n’est **pas** effectuée par cette clôture de fichier.

### 14.3 Hors périmètre C-18

1. `designGate.js` localement modifié (préexistant) — lu, **non édité**.  
2. Pieds de page C-15 / C-16 éventuellement en retard sur C-17.  
3. ROADMAP / graphe / éditorial Hub encore en narratif C-14 / C-15.  
4. Case B, ODC-F9, addenda fermés.

---

## 15. Invariants

1. Titre : **Technologie / progression**. Ages = legacy, non-authority (Q1, Q5).  
2. C-18 est **requis** et **bloquant** avant déblocages réels DG-07. `PARTIEL` ≠ facultatif (Q2).  
3. C-18 possède les **règles** ; les propriétaires possèdent l’**exécution** (Q3).  
4. Recherche ≠ Technologie ≠ Schéma (`00.4`). Pas de chaîne unique (07.3, Q24).  
5. Principal ≠ bâtiment de recherche (07.1).  
6. Schéma = autorisation durable, non consommée au fondateur (07.3).  
7. Six familles 07.5 = cadre, pas runtime (Q12).  
8. Horizontal > efficacité (07.6, Q13).  
9. En service ≠ débloqué (Q17). Autorisé ≠ effectivement possible (Q24).  
10. Aucun mapping Age → DG-07. Aucun mapping Wood → Timber (Q5, Q22).  
11. Aucune ResourceKey, aucun montant, aucune durée chiffrée inventés (Q21, Q23, Q28).  
12. Stub / Paint / visuel ≠ porte environnementale (Q26).  
13. O1–O9, P1–P10, Q1–Q12 C-17 inchangés (Q18).  
14. Addenda C-03\* · C-06\* · C-09\* · C-10\* · C-13\* fermés (Q16, Q20).  
15. S3 / Demo hors C-18 (Q7).  
16. Ce contrat **VALIDÉ** n’autorise aucune implémentation (Q30).

---

## 16. Limites de l’autorisation documentaire

Ce contrat est **`VALIDÉ`**.  
Cette validation est **documentaire** seulement (Q30).

Elle **n’autorise pas**, à elle seule :

- l’implémentation runtime de la recherche, des technologies, des schémas ou des déblocages ;  
- la refonte, la suppression ou la migration des Ages ;  
- le remplacement de `RequiredAge` ;  
- l’implémentation de portes écologiques ou environnementales ;  
- le démarrage ou la modification de **C-19**, **C-20** ou **C-21** ;  
- la réouverture des addenda fermés ;  
- la fermeture de O1–O9, P1–P10 ou Q1–Q12 C-17 ;  
- une preuve S3 / Demo nouvelle ;  
- Case B ou ODC-F9.

Toute implémentation exigerait une **autorisation distincte**, après ce contrat `VALIDÉ` et dans le respect des contrats propriétaires.

---

## 17. Exclusions

- catalogue technologique ou de schémas nommé ;  
- durées, coûts, Hertz, loadouts U6 ;  
- architecture C++ / Blueprint imposée ;  
- API de lecture de progression imposée ;  
- mapping Age ↔ palier ; mapping Wood ↔ Timber ;  
- création de ResourceKey, stocks, plafonds, service universel ;  
- règle Intention → Project ;  
- absorption du lifecycle C-14, des tâches C-04, de l’économie, des unités, des effets écologiques ou de l’UI ;  
- verrou runtime sur stub, Paint, M4 ou visuel ;  
- fermeture des questions amont ouvertes ;  
- extension d’Ages à S3 / Demo ;  
- implémentation de progression DG-07.

---

## 18. Hors autorisation

Ce contrat **VALIDÉ** **n’autorise pas** :

- l’implémentation runtime DG-07 ;  
- la migration, la suppression ou le remplacement des Ages, de `RequiredAge` ou du HUD FWSG ;  
- la modification du Design Gate, des registres, du suivi, de l’historique, du Hub ou des contrats voisins ;  
- le démarrage ou la modification de **C-19**, **C-20** ou **C-21** ;  
- la fermeture de R1–R8, R11, O1–O9, P1–P10 ou Q1–Q12 C-17 ;  
- la réouverture des addenda fermés, de Case B ou d’ODC-F9.

**Arrêt après clôture :** aucune implémentation, aucun démarrage de C-19.

---

*Fin C-18 — VALIDÉ. C-19 demeure non commencé. Case B demeure suspendu. Points ouverts R1–R8, R11, O1–O9, P1–P10 et Q1–Q12 C-17 conservés. Aucune implémentation DG-07 ni contrat suivant démarrés par cette clôture.*
