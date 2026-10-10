<!--
GardenFervor — ROADMAP GLOBALE — SOURCE DE VÉRITÉ ABSOLUE
Modifier uniquement ce fichier, puis build + validate.
Balises machine : RM:META, RM:NOW, RM:NEXT, RM:PHASE, RM:JALON, RM:WORK
(ne pas imbriquer d'exemples de balises HTML dans ce bandeau)
-->

<!--RM:META
version: 1.0.11
updated: 2026-10-10
title: GardenFervor — Roadmap globale
git_head_at_audit: b0c3367
notes: C-19 VALIDÉ conception · compteur 14/16 · C-20 non commencé. Distincte de Plan de production/Roadmap (cohorte S3).
-->

# GardenFervor — Roadmap globale

> **Où allons-nous, dans quel ordre, et pourquoi ?**  
> Ce document est la **source de vérité** de la Roadmap.  
> La page HTML est une présentation dérivée — jamais l’inverse.

## Comment lire ce document

| Outil | Question à laquelle il répond |
| --- | --- |
| **Cette Roadmap** | Où en est le projet, que faire ensuite, jusqu’au jeu final ? |
| **Design Gate** | Quelles décisions de conception sont validées ? |
| **Contrats** | Quelles règles précises gouvernent chaque système ? |
| **Project Graph** | Comment les systèmes, règles et preuves sont-ils reliés ? |
| **Roadmap S3** (`Plan de production/Roadmap`) | Suivi des tranches T1–T9 de la cohorte forestière (preuve contrôlée) |

---

## Où en est GardenFervor ?

<!--RM:NOW
summary: Conception fondatrice VALIDÉE · première preuve S3 Cas A TERMINÉE · contrats opérationnels 14/16 (C-01·C-02·C-04·C-05·C-07·C-08·C-11·C-12·C-14·C-15·C-16·C-17·C-18·C-19 VALIDÉS) · C-20 non commencé · C-03·C-06·C-09·C-10·C-13 addenda fermés · Case B SUSPENDU · ODC-F9 non démarré · aucune implémentation éco / sol / eau / DG-07 / persist runtime
conception: VALIDÉ
realisation: PARTIELLE
validation: PARTIELLE
contracts_validated: 14
contracts_required: 16
s3_case_a: VALIDÉ
case_b: SUSPENDU
design_gate: VALIDÉ (DG-00→DG-14)
odc_f1: À REFAIRE
-->

**En une phrase :** le *quoi* du jeu est largement décidé ; une première chaîne de chantier simple est prouvée ; les contrats jusqu’à C-19 sont VALIDÉS (C-15…C-19 = conception uniquement) ; C-19 n’autorise aucun flag persist / SaveGame / F1 ; C-20 n’est pas commencé.

### Acquis confirmés

- **Design Gate DG-00 → DG-14** : sections clôturées VALIDÉ (source : `ETAT_PROJET.md`).
- **Cohorte S3 Cas A** : tranches T1–T9 **VALIDÉ** — chantier forestier sur terrain déjà prêt, jusqu’à « En service » (source : `ETAT_PROJET.md`, suivi production).
- **Contrats opérationnels VALIDÉS :**
  - **C-01** — vérité du terrain (hauteur runtime) ;
  - **C-02** — grille spatiale / zones modifiées / consultations ;
  - **C-04** — tâches / graphe / dépendances (**48/48** décisions) ;
  - **C-05** — WorkSite / SitePrep (**62/62** décisions) ;
  - **C-07** — autonomie unité / agent générique (**47/47** décisions) ;
  - **C-08** — Terraformer opérationnel (**58/58** décisions) — métier formalisé ; **pas** encore implémenté en jeu ;
  - **C-11** — Réservations (**23/23** décisions) — concurrence formalisée ; **pas** validation runtime multi-chantier ;
  - **C-12** — Transport / logistique (**25/25** décisions) — règles métier formalisées ; haul A→B / F7 **partiel** ≠ réseaux / multi-flux complets.
  - **C-14** — Infrastructures lifecycle (**15/15** décisions) — règles métier formalisées ; ODC-F9 **non démarré** ; points ouverts §18 conservés.
  - **C-15** — Hydrologie (cadrage **A–G**) — règles formalisées ; stub `QueryWater` conservé ; **aucune implémentation** ; O1–O9 conservés.
  - **C-16** — Sol (cadrage **A1–K1**) — conception uniquement ; stub `QuerySoil` ; P1–P10 ouverts.
  - **C-17** — Végétation / écosystèmes (cadrage **A1–K1**) — conception uniquement ; Q1–Q12 ouverts. Fichier local encore **non suivi Git**.
  - **C-18** — Technologie / progression (cadrage **Q1–Q31**) — conception uniquement ; Ages = legacy ; **aucune implémentation DG-07**.
  - **C-19** — Persistance / sauvegarde (cadrage **S1–S14** · **L1–L3**) — conception uniquement ; persist OFF ; **≠ flags / SaveGame / F1**.
- **Preuves techniques majeures (ODC) :** F2 présentation · F3 spatial · F4 tâches · F5 autonomie · F6 économie physique · F7 logistique · F8 opérations terrain — **PASS** (F5/F7 avec validation humaine).
- **Investor Demo** : présentation et démonstration S3 présentes.
- **Cartographie** : `PROJECT_GRAPH/` disponible (projection, pas SoT).

### En construction / partiel

- Runtime terrain **shipping** (ODC-F1 **À REFAIRE** — preuve précédente INVALIDÉE).
- Chaîne chantiers / préparation : code S3 opérationnel ; **C-04**, **C-05**, **C-07**, **C-08**, **C-11**, **C-12** et **C-14 VALIDÉS** (règles métier) ; dettes runtime SitePrep / tâches / agent / Terraform / réservations / logistique / infra documentées — **Creuser / Remblayer / Aplanir non validés en jeu** · **F9 non démarré**.
- Eau / sol spatiaux : **stubs** (C-15 · C-16 = règles seulement). Végétation gameplay **absente** (C-17 = règles seulement).
- Persistance terrain : **désactivée** (C-19 = politique documentaire seulement).

### Suspendu

- **Case B** — chantier qui exige d’abord de préparer / transformer le terrain : **SUSPENDU** malgré C-05·C-07·C-08·C-11·C-12·C-14 VALIDÉS documentairement ; réactivation = autorisation explicite distincte.

### Notes d’ordre

- **C-03**, **C-06**, **C-09**, **C-10** et **C-13** restent des **addenda fermés** (suffisants pour S3) : **ne pas les ouvrir** sans besoin réel.
- **Dernier VALIDÉ du compteur 16 = C-19** (ordre 19) — conception uniquement.
- **C-15 / C-16 / C-17 / C-18 VALIDÉ ≠** simulation environnementale ni déblocages DG-07 runtime.
- **C-18 VALIDÉ ≠** implémentation recherche / Ages. Ages = legacy.
- **C-19 VALIDÉ ≠** activation persist / SaveGame / F1.
- **ODC-F9** reste **non démarré** (C-14 VALIDÉ ≠ preuve F9).

---

## Prochain travail autorisé

<!--RM:NEXT
id: next-c20
title: C-20 — Observabilité / UX
status: À FAIRE
horizon: Non commencé
note: C-19 VALIDÉ conception (b0c3367). Ne pas démarrer C-20 sans ordre explicite. Pas d’implémentation persist / F1 / DG-07. Addenda fermés. Case B suspendu. ODC-F9 non démarré.
depends: C-19 VALIDÉ
unlocks: UX / lisibilité (après C-20)
-->

### Prochain autorisé — C-20 : observabilité / UX

**Statut :** NON COMMENCÉ  
**Horizon :** Non commencé  
**En langage simple :** C-19 est la règle de conception de la persistance. C-20 est le prochain contrat requis. Il n’est pas ouvert.

| | |
| --- | --- |
| Prérequis | C-19 VALIDÉ (conception) · addenda C-03/C-06/C-09/C-10/C-13 fermés |
| Débloque | rien tant que C-20 n’est pas ouvert |
| Ne pas faire maintenant | démarrer C-20 · activer persist / SaveGame / F1 · implémenter DG-07 · ouvrir les addenda · Case B · ODC-F9 |

### Travaux ultérieurs (non autorisés comme « en cours »)

1. **C-20** — seulement sur ordre explicite.
2. **Ensuite** : dettes F1, ODC-F9 (sur ordre), C-21, persist runtime — et **seulement sur ordre** reprise Case B.

---

## Vision produit (destination)

GardenFervor est un **RTS de gestion de territoire** où le joueur donne des intentions, et où des **unités autonomes** transforment réellement le monde : relief, ressources, infrastructures, écosystèmes.

Le joueur doit comprendre :

- ce qui est possible ;
- ce qui se passe ;
- ce qui bloque ;
- ce qui demande son attention ;

…sans micro-gérer chaque action.

La Roadmap mène de la **preuve contrôlée actuelle** jusqu’à un **jeu jouable, lisible, stable et abouti** — pas seulement jusqu’à la fin des contrats.

---

# Phases

Les horizons utilisés : `Acquis` · `Actuel` · `Prochain` · `Après validation` · `À planifier` · `Phase ultérieure`.  
Pas de dates calendaires inventées.

---

<!--RM:PHASE
id: P0
title: Fondations et gouvernance
status: TERMINÉ
horizon: Acquis
depends:
unlocks: P1,P2
sources: REGLES_PROJET.md | ETAT_PROJET.md | GardenFervor_DesignGate_React/src/data/designGate.js
-->

## Phase P0 — Fondations et gouvernance

**Statut :** TERMINÉ · **Horizon :** Acquis  

Décider ce qu’est GardenFervor, comment on décide, et comment on prouve. Sans cette base, aucune production contrôlée n’est légitime.

### Pourquoi c’est nécessaire

Éviter de coder des mécaniques inventées, et garder une mémoire claire des règles du projet.

<!--RM:JALON
id: P0.J1
phase: P0
title: Design Gate clôturé
status: VALIDÉ
conception: VALIDÉE
realisation: n/a
validation: PASS
depends:
unlocks: P1
sources: ETAT_PROJET.md · designGate.js
-->

### Jalon P0.J1 — Design Gate clôturé

**Statut :** VALIDÉ  

DG-00 → DG-14 validés. La conception fondatrice du jeu est en place.

<!--RM:WORK
id: P0.W1
jalon: P0.J1
title: Cadre RTS et boucle joueur
status: VALIDÉ
sources: DG-00 · DG-01
-->

#### Travail P0.W1 — Cadre RTS et boucle joueur

Identité du jeu, intention → monde, autonomie, lisibilité. **VALIDÉ.**

<!--RM:JALON
id: P0.J2
phase: P0
title: Readiness pré-implémentation
status: VALIDÉ
conception: VALIDÉE
realisation: n/a
validation: PASS
depends: P0.J1
unlocks: P1
sources: Audit de readiness pré-implémentation/CONTROLE_FINAL_PRE_IMPLEMENTATION_COHORTE.md
-->

### Jalon P0.J2 — Readiness pré-implémentation

**Statut :** VALIDÉ  

Contrôle final **PASS** — prêt pour une implémentation contrôlée (cohorte), pas pour un développement libre.

<!--/RM:PHASE-->

---

<!--RM:PHASE
id: P1
title: Première preuve jouable (cohorte S3)
status: TERMINÉ
horizon: Acquis
depends: P0
unlocks: P2,P3
sources: ETAT_PROJET.md · Plan de production/PLAN_PRODUCTION_COHORTE_S3.md · Plan de production/Roadmap
-->

## Phase P1 — Première preuve jouable (cohorte S3)

**Statut :** TERMINÉ · **Horizon :** Acquis  

Montrer une chaîne complète, simple et honnête : intention → chantier → unités → matière → construction → mise en service — **sur un terrain déjà prêt (Cas A)**.

<!--RM:JALON
id: P1.J1
phase: P1
title: Cohorte S3 Cas A (T1–T9)
status: VALIDÉ
conception: VALIDÉE
realisation: TERMINÉE
validation: PASS
depends: P0
unlocks: P2
sources: ETAT_PROJET.md · HISTORIQUE_MODIFICATIONS.md
-->

### Jalon P1.J1 — Cohorte S3 Cas A

**Statut :** VALIDÉ (9/9)  

Preuve contrôlée forestière : bois, stocks, transport, construction, critère « En service ».

<!--RM:WORK
id: P1.W1
jalon: P1.J1
title: Chaîne units + stocks + chantier Cas A
status: VALIDÉ
sources: smokes cohorte · Investor Demo S3
-->

#### Travail P1.W1 — Chaîne Cas A

Roster exploitation / transport / construction · Timber · stocks A/B · pas de terrassement obligatoire.

<!--RM:JALON
id: P1.J2
phase: P1
title: Case B (terrain à préparer d’abord)
status: SUSPENDU
conception: PARTIELLE
realisation: PARTIELLE
validation: NON TERMINÉE
depends: P4,P5,P6
unlocks: Demo Case B
sources: CONTRATS/00_REGISTRE_CONTRATS.md · CONTRATS/00_SUIVI_CONTRATS.md
-->

### Jalon P1.J2 — Case B (préparation de terrain obligatoire)

**Statut :** SUSPENDU  

Existe partiellement en code, mais **volontairement gelé** jusqu’aux contrats de chantier / tâches / terrassement.

<!--/RM:PHASE-->

---

<!--RM:PHASE
id: P2
title: Contrats opérationnels (règles d’exécution)
status: EN COURS
horizon: Actuel
depends: P0,P1
unlocks: P3,P4,P5,P6,P7
sources: CONTRATS/00_REGISTRE_CONTRATS.md · CONTRATS/00_SUIVI_CONTRATS.md
-->

## Phase P2 — Contrats opérationnels

**Statut :** EN COURS · **Horizon :** Actuel · Progression documentaire **3 / 16**

Transformer les décisions de conception en **règles d’exécution** assez précises pour construire la suite sans inventer.

<!--RM:JALON
id: P2.J1
phase: P2
title: C-01 Terrain runtime
status: VALIDÉ
conception: VALIDÉE
realisation: PARTIELLE
validation: PASS
depends: P0
unlocks: P2.J2,P3
sources: CONTRATS/C-01_TERRAIN_RUNTIME.md
-->

### Jalon P2.J1 — C-01 Terrain runtime

**Statut :** VALIDÉ (contrat) · réalisation encore **partielle** (dettes F1, persistance, dirty eau/sol…).

<!--RM:JALON
id: P2.J2
phase: P2
title: C-02 Substrat spatial
status: VALIDÉ
conception: VALIDÉE
realisation: PARTIELLE
validation: PASS
depends: P2.J1
unlocks: P2.J3
sources: CONTRATS/C-02_SUBSTRAT_SPATIAL.md
-->

### Jalon P2.J2 — C-02 Substrat spatial

**Statut :** VALIDÉ · 31 décisions. Grille, zones modifiées, consultations.

<!--RM:JALON
id: P2.J3
phase: P2
title: C-04 Tâches / graphe / dépendances
status: VALIDÉ
conception: VALIDÉE
realisation: PARTIELLE
validation: PASS
depends: P2.J2
unlocks: P2.J4,P4,P5
sources: CONTRATS/C-04_TACHES_GRAPHE_DEPENDANCES.md
note: 48/48 A1–K6 ; audit PASS ; C-03 addendum fermé ; dettes d’implémentation conservées.
-->

### Jalon P2.J3 — C-04 Tâches / graphe / dépendances

**Statut :** VALIDÉ (contrat) · réalisation encore **partielle** (dettes Progress/effets, invalidation monde, etc.).

Organiser le travail : étapes, dépendances, progression, blocages, réévaluation, hiérarchie.  
Contrat dédié : `CONTRATS/C-04_TACHES_GRAPHE_DEPENDANCES.md`.

<!--RM:JALON
id: P2.J4
phase: P2
title: Contrats chantiers / unités / terraform (C-05 · C-07 · C-08)
status: VALIDÉ
conception: VALIDÉ
realisation: PARTIELLE
validation: VALIDÉ
depends: P2.J3
unlocks: P1.J2,P4,P5,P6
sources: CONTRATS/C-05_WORKSITE_SITEPREP.md · CONTRATS/C-07_AUTONOMIE_UNITE_AGENT_GENERIQUE.md · CONTRATS/C-08_TERRAFORMER_OPERATIONNEL.md · CONTRATS/00_REGISTRE_CONTRATS.md
note: C-05·C-07·C-08 VALIDÉS documentairement ; métier Terraform formalisé ≠ implémenté en jeu ; Case B suspendu.
-->

### Jalon P2.J4 — C-05 · C-07 · C-08

**Statut :** TERMINÉ côté contrats (**C-05 · C-07 · C-08 VALIDÉS**) — implémentation métier Terraform et Case B **hors** ce jalon documentaire

- **C-05** — **VALIDÉ** — savoir si / quand préparer un site (`CONTRATS/C-05_WORKSITE_SITEPREP.md`) ;  
- **C-07** — **VALIDÉ** — autonomie générique des unités (`CONTRATS/C-07_AUTONOMIE_UNITE_AGENT_GENERIQUE.md`) ;  
- **C-08** — **VALIDÉ** — métier Terraform (`CONTRATS/C-08_TERRAFORMER_OPERATIONNEL.md`) — **règles formalisées**, pas validation produit Creuser/Remblayer/Aplanir.  

**Case B** reste **suspendu** ; réactivation = autorisation explicite distincte.

<!--RM:JALON
id: P2.J5
phase: P2
title: Contrats reste du compteur (C-16…C-21)
status: À FAIRE
conception: À CONCEVOIR
realisation: PARTIELLE
validation: NON TERMINÉE
depends: P2.J3,P2.J4
unlocks: P7,P8,P9,P10,P11,P13
sources: CONTRATS/00_REGISTRE_CONTRATS.md · CONTRATS/C-15_HYDROLOGIE.md
note: C-16·C-17·C-18·C-19 VALIDÉS conception ; C-20 non commencé.
-->

### Jalon P2.J5 — Autres contrats obligatoires

**C-11** — **VALIDÉ** — réservations / concurrence (`CONTRATS/C-11_RESERVATIONS.md`).  
**C-12** — **VALIDÉ** — transport / logistique (`CONTRATS/C-12_TRANSPORT_LOGISTIQUE.md`) — règles formalisées ; runtime réseaux / multi-flux **partiel**.  
**C-14** — **VALIDÉ** — infrastructures lifecycle (`CONTRATS/C-14_INFRASTRUCTURES_LIFECYCLE.md`) — règles formalisées ; ODC-F9 **non démarré**.  
**C-15** — **VALIDÉ** — hydrologie (`CONTRATS/C-15_HYDROLOGIE.md`) — règles formalisées ; **aucune implémentation** ; O1–O9 conservés.  
**C-16** — **VALIDÉ** — sol (conception) ; P1–P10 ouverts.  
**C-17** — **VALIDÉ** — végétation / écosystèmes (conception) ; Q1–Q12 ouverts.  
**C-18** — **VALIDÉ** — conception uniquement — `C-18_TECHNOLOGIE_PROGRESSION.md` — Ages = legacy ; ≠ runtime DG-07.  
**C-19** — **VALIDÉ** — conception uniquement — `C-19_PERSISTANCE_SAUVEGARDE.md` — persist OFF ; ≠ flags / SaveGame / F1.

UX, simulation/perf, persist runtime — **dans l’ordre du registre**, sans démarrer C-20 automatiquement.

<!--/RM:PHASE-->

---

<!--RM:PHASE
id: P3
title: Monde et terrain (vérité + présentation)
status: EN COURS
horizon: Actuel
depends: P2.J1,P1
unlocks: P6,P9,P13
sources: CONTRATS/C-01_TERRAIN_RUNTIME.md · Saved/ODC_F1_RuntimeTerrainGate.txt · Saved/ODC_F2_VisualTerrainGate.txt · Saved/ODC_F8_TerraformOperationGate.txt
-->

## Phase P3 — Monde et terrain

**Statut :** EN COURS · **Horizon :** Actuel  

Le relief doit être une **vérité de jeu** fiable, présentée joliment (M4 / ciel), sans que le rendu décide du gameplay.

<!--RM:JALON
id: P3.J1
phase: P3
title: Présentation terrain (M4 / ciel)
status: VALIDÉ
conception: VALIDÉE
realisation: TERMINÉE
validation: PASS
depends: P0
sources: ODC-F2
-->

### Jalon P3.J1 — Présentation (M4 / UDS)

**Statut :** VALIDÉ (preuve F2). Le rendu n’est pas la vérité hauteur.

<!--RM:JALON
id: P3.J2
phase: P3
title: Terrain shipping Base+Delta (F1)
status: À FAIRE
conception: VALIDÉE
realisation: À FAIRE
validation: INVALIDÉ (ancienne preuve)
depends: P2.J1
unlocks: P13
sources: ODC-F1 INVALIDÉ · C-01
-->

### Jalon P3.J2 — Terrain emballé (shipping)

**Statut :** À FAIRE · ODC-F1 **À REFAIRE**  

Aujourd’hui : brushes Landscape en session ; store CPU pour l’espace. La cible shipping Base+Delta n’est pas revalidée.

<!--RM:JALON
id: P3.J3
phase: P3
title: Grille spatiale opérationnelle
status: PARTIEL
conception: VALIDÉE
realisation: PARTIELLE
validation: PASS
depends: P2.J2
sources: C-02 · ODC-F3
-->

### Jalon P3.J3 — Grille spatiale

**Statut :** preuve F3 PASS · contrat C-02 VALIDÉ · stubs eau/sol · invalidation tâches **pas encore branchée**.

<!--/RM:PHASE-->

---

<!--RM:PHASE
id: P4
title: Chantiers et transformation du monde
status: À CONCEVOIR
horizon: Prochain
depends: P2.J3,P2.J4,P3
unlocks: P1.J2,P8
sources: DG-11 · registre C-04 C-05 C-08
-->

## Phase P4 — Chantiers et transformation du monde

**Statut :** À CONCEVOIR · **Horizon :** Prochain  

Le joueur pose une intention ; le monde se transforme par étapes visibles et compréhensibles (préparer, terrasser, construire) — pas en un « flash » opaque.

<!--RM:JALON
id: P4.J1
phase: P4
title: Graphe de travail des chantiers
status: À CONCEVOIR
depends: P2.J3
unlocks: P4.J2
sources: C-04
-->

### Jalon P4.J1 — Graphe de travail

Étapes, sous-étapes, progression, blocages, reprise après changement du monde.

<!--RM:JALON
id: P4.J2
phase: P4
title: Préparation de site
status: À FAIRE
depends: P4.J1,P2.J4
unlocks: P4.J3
sources: C-05
-->

### Jalon P4.J2 — Préparation de site

Savoir si une zone est prête ; sinon, quelles étapes de préparation lancer.

<!--RM:JALON
id: P4.J3
phase: P4
title: Terrassement progressif réel
status: À FAIRE
depends: P4.J2,P5,P6
unlocks: P1.J2
sources: C-08 · DG-08
-->

### Jalon P4.J3 — Terrassement progressif

**Contrat C-08 VALIDÉ** (règles métier). Statut d’implémentation / preuve produit : **À FAIRE** — passes, zones, matière, critères de fin hors simple « tâche terminée » ; Case B **suspendu**.

<!--/RM:PHASE-->

---

<!--RM:PHASE
id: P5
title: Unités et autonomie
status: PARTIEL
horizon: Après validation
depends: P2.J3,P1
unlocks: P4.J3,P7
sources: DG-04 · ODC-F5 · registre C-07
-->

## Phase P5 — Unités et autonomie

**Statut :** PARTIEL · **Horizon :** Après validation (après C-04)  

Des unités capables de choisir un travail compatible, s’y rendre, l’exécuter, signaler un blocage — une seule tâche active à la fois.

<!--RM:JALON
id: P5.J1
phase: P5
title: Agent générique d’exécution
status: PARTIEL
depends: P2.J3
sources: UnitTaskAgent · ODC-F5 · CONTRATS/C-07_AUTONOMIE_UNITE_AGENT_GENERIQUE.md
-->

### Jalon P5.J1 — Agent générique

**Preuve F5 PASS** · contrat **C-07 VALIDÉ** (47/47) — règles figées ; dettes d’implémentation (effets, InstantMode, Progress) conservées.


<!--RM:JALON
id: P5.J2
phase: P5
title: Capacités et roster élargis
status: PARTIEL
depends: P5.J1
sources: C-06 addendum* · DG-03
-->

### Jalon P5.J2 — Capacités / roster

Suffisant pour S3 ; à élargir quand le jeu sort du kit forestier minimal.

<!--/RM:PHASE-->

---

<!--RM:PHASE
id: P6
title: Ressources, logistique et économie
status: PARTIEL
horizon: Après validation
depends: P1,P5
unlocks: P8,P10
sources: DG-05 · DG-06 · ODC-F6 · ODC-F7 · C-09…C-12
-->

## Phase P6 — Ressources, logistique et économie

**Statut :** PARTIEL · **Horizon :** Après validation  

Matières localisées, transport réel, réservations claires — au-delà du mini-scénario Timber A→B.

<!--RM:JALON
id: P6.J1
phase: P6
title: Économie physique minimale
status: VALIDÉ
validation: PASS
sources: ODC-F6 · S3 Timber
-->

### Jalon P6.J1 — Économie physique minimale

**PASS** pour le périmètre Timber / stocks. Addendum C-09/C-10 fermés tant que S3 suffit.

<!--RM:JALON
id: P6.J2
phase: P6
title: Réservations et multi-chantier
status: À FAIRE
depends: P2.J3
sources: C-11
-->

### Jalon P6.J2 — Réservations

Avant plusieurs chantiers concurrents sans chaos.

<!--RM:JALON
id: P6.J3
phase: P6
title: Logistique au-delà du haul A→B
status: À FAIRE
depends: P5,P6.J1
sources: C-12 · DG-06
note: C-12 VALIDÉ (25/25) — règles métier ; runtime réseaux / N4 / multi-flux encore partiel.
-->

### Jalon P6.J3 — Logistique élargie

Réseaux, accès, replanification de transport — conception DG-06 VALIDÉE ; **C-12 VALIDÉ** (règles métier) ; runtime au-delà du haul A→B / F7 encore **partiel**.

<!--/RM:PHASE-->

---

<!--RM:PHASE
id: P7
title: Infrastructures et territoire
status: EN COURS
horizon: Actuel
depends: P4,P6
unlocks: P9,P10
sources: DG-10 · CONTRATS/C-14_INFRASTRUCTURES_LIFECYCLE.md · ODC-F9 (non démarré)
-->

## Phase P7 — Infrastructures et territoire

**Statut :** EN COURS · **Horizon :** Actuel  

Routes, supports, infrastructures temporaires/permanentes qui changent l’accès et le possible — **C-14 VALIDÉ** (règles) ; preuve ODC-F9 encore **à faire** sur ordre.

<!--RM:JALON
id: P7.J1
phase: P7
title: Cycle de vie des infrastructures
status: PARTIEL
depends: P2.J5,P4
sources: C-14 · ODC-F9
note: C-14 VALIDÉ (15/15) ; ODC-F9 non démarré.
-->

### Jalon P7.J1 — Cycle de vie infrastructures

**C-14 VALIDÉ** (15/15) — règles lifecycle formalisées. Preuve **ODC-F9** — **non démarrée**.

<!--/RM:PHASE-->

---

<!--RM:PHASE
id: P8
title: Écosystèmes et simulations du vivant
status: À FAIRE
horizon: À planifier
depends: P3,P7
unlocks: P10,P11
sources: DG-09 · C-15 · C-16 · C-17 · Spatial stubs
-->

## Phase P8 — Écosystèmes et simulations du vivant

**Statut :** À FAIRE · **Horizon :** À planifier  

Eau, sol, végétation : états de jeu réels (pas seulement décor), mis à jour localement quand le terrain ou les ouvrages changent.

<!--RM:JALON
id: P8.J1
phase: P8
title: Hydrologie et sol
status: À FAIRE
sources: C-15 · C-16 · stubs spatiaux
-->

### Jalon P8.J1 — Eau et sol

Conception DG-09 VALIDÉE · runtime encore stub.

<!--RM:JALON
id: P8.J2
phase: P8
title: Végétation et écosystèmes
status: À FAIRE
depends: P8.J1
sources: C-17 · DG-09
-->

### Jalon P8.J2 — Végétation / écosystèmes

Transitions, impacts humains, objectifs écologiques — après eau/sol.

<!--/RM:PHASE-->

---

<!--RM:PHASE
id: P9
title: Progression, recherche et déblocages
status: À FAIRE
horizon: À planifier
depends: P2,P6
unlocks: P10
sources: DG-07 · C-18
-->

## Phase P9 — Progression et déblocages

**Statut :** À FAIRE · **Horizon :** À planifier  

Le joueur élargit ses possibilités (schémas, technologies, horizontal) sans casser la lisibilité ni inventer une économie d’entretien trop tôt.

<!--RM:JALON
id: P9.J1
phase: P9
title: Système de progression jouable
status: À FAIRE
sources: C-18 · TechComponent legacy
-->

### Jalon P9.J1 — Progression jouable

Conception DG-07 VALIDÉE · C-18 VALIDÉ conception · implémentation legacy Ages isolée · aucun déblocage DG-07 runtime.

<!--/RM:PHASE-->

---

<!--RM:PHASE
id: P10
title: Expérience joueur, lisibilité et pédagogie
status: PARTIEL
horizon: À planifier
depends: P4,P5,P8
unlocks: P11,P12
sources: DG-13 · C-20 · Investor Demo
-->

## Phase P10 — Expérience joueur, lisibilité et pédagogie

**Statut :** PARTIEL · **Horizon :** À planifier  

Le joueur comprend l’état du territoire et des unités. Dimension éducative / encyclopédie : expliquer le monde sans feuille de calcul.

<!--RM:JALON
id: P10.J1
phase: P10
title: Lisibilité produit
status: À FAIRE
sources: C-20 · DG-13
-->

### Jalon P10.J1 — Lisibilité produit

Au-delà des smokes : HUD et signaux utiles (disponibilité, blocage, progression).

<!--RM:JALON
id: P10.J2
phase: P10
title: Encyclopédie et pédagogie
status: À CONCEVOIR
sources: vision produit DG · présentation client
-->

### Jalon P10.J2 — Encyclopédie / pédagogie

Contenu explicatif du monde (écosystèmes, chaînes, ouvrages) — **à concevoir** ; pas de backlog détaillé inventé ici.

<!--RM:JALON
id: P10.J3
phase: P10
title: Présentation et démonstration
status: PARTIEL
sources: Investor Demo · docs/presentation-client.html
-->

### Jalon P10.J3 — Présentation

Démo S3 et pitch client existants ; à enrichir quand Case B et systèmes suivants seront prêts.

<!--/RM:PHASE-->

---

<!--RM:PHASE
id: P11
title: Contenu, équilibrage et polish
status: À FAIRE
horizon: Phase ultérieure
depends: P7,P8,P9,P10
unlocks: P12
sources: DG-02 catalogue · vision produit
-->

## Phase P11 — Contenu, équilibrage et polish

**Statut :** À FAIRE · **Horizon :** Phase ultérieure  

Élargir le catalogue (bâtiments, unités, biomes), équilibrer durées et coûts **quand les valeurs seront décidées**, polir l’expérience.

<!--RM:JALON
id: P11.J1
phase: P11
title: Catalogue de contenu jouable
status: À FAIRE
sources: DG-02 · DataAssets RTS
-->

### Jalon P11.J1 — Catalogue

Au-delà du kit forestier minimal.

<!--RM:JALON
id: P11.J2
phase: P11
title: Équilibrage et ressenti
status: NON DÉFINI
sources: valeurs chiffrées encore À DÉFINIR (DG)
-->

### Jalon P11.J2 — Équilibrage

Pas de chiffres inventés dans cette Roadmap.

<!--/RM:PHASE-->

---

<!--RM:PHASE
id: P12
title: Stabilité, performance, sauvegarde, release
status: À FAIRE
horizon: Phase ultérieure
depends: P3.J2,P2.J5,P11
unlocks:
sources: C-19 · C-21 · ODC-F1 · REGLES_PROJET.md
-->

## Phase P12 — Stabilité, performance, sauvegarde, release

**Statut :** À FAIRE · **Horizon :** Phase ultérieure  

Le jeu doit pouvoir être sauvegardé, tenu en performance, et livré sans tricher sur la vérité terrain.

<!--RM:JALON
id: P12.J1
phase: P12
title: Persistance / sauvegarde
status: À FAIRE
depends: P3.J2
sources: C-19 · TerraformSave désactivé
-->

### Jalon P12.J1 — Sauvegarde

Persistance terrain actuellement off — contrat C-19 avant shipping.

<!--RM:JALON
id: P12.J2
phase: P12
title: Simulation / fréquences / perf
status: À FAIRE
sources: C-21 · DG-00.5
-->

### Jalon P12.J2 — Performance de simulation

Avant montée en échelle du territoire.

<!--RM:JALON
id: P12.J3
phase: P12
title: Validation finale et release
status: À FAIRE
depends: P12.J1,P12.J2,P11
sources: DG-14 principes de validation
-->

### Jalon P12.J3 — Release

Validation humaine des boucles critiques, stabilité, build shipping — **sans date inventée**.

<!--/RM:PHASE-->

---

## Chaîne de dépendances (vue synthétique)

```text
P0 Fondations (TERMINÉ)
 └─► P1 Preuve S3 Cas A (TERMINÉ) · Case B (SUSPENDU)
      └─► P2 Contrats (EN COURS : 14/16 VALIDÉS · C-19 VALIDÉ conception · C-20 non commencé)
           ├─► P3 Monde / terrain (F1 À REFAIRE)
           ├─► P4 Chantiers (C-05·C-07·C-08 VALIDÉS doc · implémentation métier À FAIRE)
           ├─► P5 Unités (C-07 VALIDÉ)
           └─► P6 Ressources / logistique (C-11·C-12 VALIDÉS doc · runtime logistique partiel)
                └─► P7 Infrastructures (C-14 VALIDÉ doc · F9 non démarré)
                     └─► P8 Écosystèmes (C-15·C-16·C-17 VALIDÉS doc · pas de sim éco)
                          └─► P9 Progression
                               └─► P10 UX / pédagogie
                                    └─► P11 Contenu / polish
                                         └─► P12 Stabilité / release
```

---

## Blocages et suspensions (tableau)

| Sujet | Statut | Pourquoi | Débloqué par |
| --- | --- | --- | --- |
| Case B | SUSPENDU | Contrats C-05·C-07·C-08·C-11·C-12·C-14 VALIDÉS ; réactivation ≠ automatique | Autorisation explicite distincte (+ dettes C-01 utiles) |
| C-03 | Fermé (addendum) | S3 suffit | Ouverture humaine seulement si besoin |
| C-06 | Fermé (addendum) | S3 suffit | Ouverture humaine seulement si besoin |
| C-09 / C-10 | Fermés (addenda) | S3 suffit | Ouverture humaine seulement si besoin |
| C-13 | Fermé (addendum) | Critère cohorte | Ouverture humaine seulement si besoin |
| ODC-F1 | À REFAIRE | Preuve shipping INVALIDÉE | Travaux terrain shipping |
| ODC-F9 | NON DÉMARRÉ | C-14 VALIDÉ ≠ preuve F9 | Ordre explicite distinct |
| C-05 | VALIDÉ | Contrat opérationnel 62/62 | — |
| C-07 | VALIDÉ | Contrat opérationnel 47/47 | — |
| C-08 | VALIDÉ | Contrat opérationnel 58/58 (métier formalisé ≠ produit) | — |
| C-11 | VALIDÉ | Contrat opérationnel 23/23 (concurrence formalisée ≠ runtime complet) | — |
| C-12 | VALIDÉ | Contrat opérationnel 25/25 (logistique formalisée ≠ réseaux / multi-flux complets) | — |
| C-14 | VALIDÉ | Contrat opérationnel 15/15 (lifecycle formalisé ≠ F9 runtime) | — |
| C-15 | VALIDÉ | Contrat opérationnel cadrage A–G (règles ≠ simulation runtime) | — |
| C-16 | À FAIRE | Prochain requis (non commencé) | Ordre explicite de rédaction |

---

## Liens utiles

| Ressource | Emplacement |
| --- | --- |
| État projet | `ETAT_PROJET.md` |
| Règles | `REGLES_PROJET.md` |
| Registre contrats | `CONTRATS/00_REGISTRE_CONTRATS.md` |
| Suivi contrats | `CONTRATS/00_SUIVI_CONTRATS.md` |
| Design Gate | `GardenFervor_DesignGate_React/` |
| Project Graph | `PROJECT_GRAPH/` |
| Roadmap cohorte S3 | `Plan de production/Roadmap/` |
| Hub Pages | `docs/index.html` |

---

## Historique de cette Roadmap

| Date | Version | Changement |
| --- | --- | --- |
| 2026-10-10 | 1.0.11 | C-19 VALIDÉ conception · compteur 14/16 · C-20 non commencé · persist OFF · ≠ flags / SaveGame / F1 · Case B reste suspendu |
| 2026-10-10 | 1.0.10 | C-18 VALIDÉ conception · compteur 13/16 · C-19 non commencé · aucune implémentation DG-07 · Case B reste suspendu |
| 2026-10-10 | 1.0.9 | C-18 DRAFT / REVUE (non validé) · compteur 12/16 · C-16·C-17 VALIDÉS conception · aucune implémentation DG-07 · Case B reste suspendu |
| 2026-10-10 | 1.0.8 | Clôture C-15 VALIDÉ · compteur 10/16 · prochain = C-16 · aucune implémentation hydrologique · Case B reste suspendu |
| 2026-10-09 | 1.0.7 | Clôture C-14 VALIDÉ · compteur 9/16 · prochain = C-15 · ODC-F9 non démarré · Case B reste suspendu |
| 2026-10-09 | 1.0.6 | Clôture C-12 VALIDÉ · compteur 8/16 · prochain = C-14 · Case B reste suspendu |
| 2026-10-09 | 1.0.5 | Clôture C-11 VALIDÉ · compteur 7/16 · prochain = C-12 · Case B reste suspendu |
| 2026-10-09 | 1.0.4 | Clôture C-08 VALIDÉ · compteur 6/16 · prochain = C-11 · Case B reste suspendu |
| 2026-10-09 | 1.0.3 | Clôture C-07 VALIDÉ · compteur 5/16 · prochain = C-08 |
| 2026-10-08 | 1.0.2 | Clôture C-05 VALIDÉ · compteur 4/16 · prochain = C-07 |
| 2026-10-08 | 1.0.1 | Clôture C-04 VALIDÉ · compteur 3/16 · prochain = C-05 |
| 2026-10-08 | 1.0.0 | Création initiale après audit dépôt |

*Les mises à jour détaillées : `ROADMAP/CHANGELOG.md`.*
