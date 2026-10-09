# CONTRATS — SUIVI DE PRODUCTION

**Fichier :** `CONTRATS/00_SUIVI_CONTRATS.md`  
**Statut :** actif  
**Référence ordre / nécessité :** `CONTRATS/00_REGISTRE_CONTRATS.md` (non modifié ici)  
**Date d’initialisation :** 2026-10-08

---

## 1. Rôle du document

Ce document pilote **l’avancement documentaire** des contrats :

- quels contrats sont terminés / en cours / à faire ;
- quelles étapes (audit, décisions, rédaction, revue, validation) sont franchies ;
- quel contrat est autorisé maintenant ;
- quels contrats sont bloqués ou suspendus.

Il **n’est pas** une source de vérité de gameplay.  
Les règles restent dans les contrats individuels (lorsqu’ils existent) et dans le Design Gate / ODC.  
Le **registre** reste la référence pour la liste, la nécessité, les dépendances et l’**ordre officiel**.

Distinction obligatoire :

```text
Couverture documentaire existante (DG, ODC, formalisations, T1–T9)
≠
Contrat dédié validé
```

---

## 2. Règles de progression

1. Respecter l’**ordre officiel** du registre ; ne pas le recalculer ici.
2. Un seul contrat peut être **en cours** à la fois (sauf décision humaine contraire explicite).
3. Un fichier contrat peut exister en **RÉDACTION** ou **REVUE** sans être **VALIDÉ**.
4. **VALIDÉ** uniquement après décision + revue explicites humaines.
5. Un contrat à couverture « suffisante » ailleurs n’est **pas** un contrat dédié VALIDÉ.
6. Les addenda `*` (C-03, C-06, C-09, C-10, C-13) ne démarrent que si le périmètre S3 ne suffit plus (registre §5).
7. Case B reste **suspendu** ; sa reprise dépend des contrats bloquants (registre), pas de ce suivi seul.
8. Un contrat **VALIDÉ** reste la règle opérationnelle même si l’implémentation présente encore des écarts documentés (dettes ultérieures).

---

## 3. Statuts

| Statut | Signification |
| --- | --- |
| **NON COMMENCÉ** | Aucun travail de production de contrat dédié engagé. |
| **AUDIT PRÉPARATOIRE** | État des lieux en cours avant décisions. |
| **DÉCISIONS EN COURS** | Audit terminé ; arbitrages humains en cours ; rédaction non ouverte. |
| **RÉDACTION** | Décisions suffisantes ; rédaction du document contrat en cours. |
| **REVUE** | Brouillon rédigé ; revue humaine / croisement registre en cours. |
| **VALIDÉ** | Contrat dédié accepté explicitement comme règle opérationnelle. |
| **BLOQUÉ** | Progression impossible faute de dépendance ou de décision externe. |
| **SUSPENDU** | Progression volontairement arrêtée (ex. Case B lié). |

Règle : un contrat rédigé ≠ VALIDÉ ≠ règle officielle.

---

## 4. Tableau global

### Indicateur de création / validation

Périmètre compté = contrats pour lesquels le registre exige un **contrat autonome à créer/valider**  
(`REQUIS` ou `PARTIEL` / `PARTIEL→REQUIS` — hors `NON REQUIS` et hors `SUFFISANT*` tant que l’addendum n’est pas ouvert) :

| ID concernés | C-01 · C-02 · C-04 · C-05 · C-07 · C-08 · C-11 · C-12 · C-14 · C-15 · C-16 · C-17 · C-18 · C-19 · C-20 · C-21 |
| --- | --- |
| Total à créer/valider | **16** |
| Contrats dédiés VALIDÉS | **6** |
| Progression validation | **6 / 16** |

*(Les `SUFFISANT*` et `NON REQUIS` sont suivis dans le tableau mais exclus du dénominateur tant qu’aucun addendum / contrat dédié n’est ouvert.)*

### Tableau

Légende progression : `—` = non commencé · `OK` = terminé · `EN COURS` · `n/a` = hors production de contrat dédié.

| ID | Nom | Ordre | Contrat requis | Couverture existante | Audit | Décisions | Rédaction | Revue | Validation | Statut | Bloquant | Notes |
| -- | --- | ----: | -------------- | -------------------- | ----- | --------- | --------- | ----- | ---------- | ------ | -------- | ----- |
| C-00 | Cadre / invariants fondateurs | — | non | suffisante | n/a | n/a | n/a | n/a | n/a | NON COMMENCÉ | non | Pas de contrat dédié (DG-00) |
| C-01 | Terrain runtime | 1 | oui | partielle | OK | OK | OK | OK | OK | **VALIDÉ** | oui | Validé humainement ; écarts d’implémentation restent dettes (ApplyBrushAt, GroundUtils, F1, persist, dirty Soil\|Water, lexique) |
| C-02 | Substrat spatial | 2 | oui | partielle | OK | OK | OK | OK | OK | **VALIDÉ** | oui | Validé humainement ; 31/31 décisions A1–F3 ; `C-02_SUBSTRAT_SPATIAL.md` ; audit final PASS |
| C-03 | Projet / Intention | 3* | addendum* | suffisante | — | — | — | — | — | NON COMMENCÉ | non* | S3 suffisant ; pas VALIDÉ dédié |
| C-04 | Tâches / graphe / dépendances | 4 | oui | partielle | OK | OK | OK | OK | OK | **VALIDÉ** | oui | Validé humainement ; 48/48 A1–K6 ; audit final PASS ; dettes d’implémentation conservées |
| C-05 | WorkSite / SitePrep | 5 | oui | partielle | OK | OK | OK | OK | OK | **VALIDÉ** | oui | Validé humainement ; 62/62 A1–N3 ; audit final PASS ; Case B reste suspendu ; dettes d’implémentation conservées |
| C-06 | Capacités / roster | 6* | addendum* | suffisante | — | — | — | — | — | NON COMMENCÉ | non* | S3 suffisant ; pas VALIDÉ dédié |
| C-07 | Autonomie unité | 7 | oui | partielle | OK | OK | OK | OK | OK | **VALIDÉ** | oui | Validé humainement ; 47/47 A1–J4 ; audit final PASS ; Case B reste suspendu ; dettes d’implémentation conservées |
| C-08 | Terraformer opérationnel | 8 | oui | partielle | OK | OK | OK | OK | OK | **VALIDÉ** | oui | Validé humainement ; 58/58 A1–L4 ; audit final PASS ; Case B reste suspendu ; dettes d’implémentation conservées |
| C-09 | Économie physique | 9* | addendum* | suffisante | — | — | — | — | — | NON COMMENCÉ | non* | S3 Timber ; pas VALIDÉ dédié |
| C-10 | Stocks A/B | 10* | addendum* | suffisante | — | — | — | — | — | NON COMMENCÉ | non* | S3 ; pas VALIDÉ dédié |
| C-11 | Réservations | 11 | oui | partielle | — | — | — | — | — | NON COMMENCÉ | oui | Avant multi-chantier |
| C-12 | Transport / logistique | 12 | oui | partielle | — | — | — | — | — | NON COMMENCÉ | oui | Au-delà S3 |
| C-13 | Construction / En service | 13* | addendum* | suffisante | — | — | — | — | — | NON COMMENCÉ | non* | Critère cohorte ; pas VALIDÉ dédié |
| C-14 | Infrastructures | 14 | oui | absente | — | — | — | — | — | NON COMMENCÉ | oui | Avant ODC-F9 |
| C-15 | Hydrologie | 15 | oui | absente | — | — | — | — | — | NON COMMENCÉ | oui | |
| C-16 | Sol | 16 | oui | absente | — | — | — | — | — | NON COMMENCÉ | oui | |
| C-17 | Végétation / écosystèmes | 17 | oui | partielle | — | — | — | — | — | NON COMMENCÉ | oui | |
| C-18 | Technologie / progression | 18 | oui | partielle | — | — | — | — | — | NON COMMENCÉ | oui | |
| C-19 | Persistance / sauvegarde | 19 | oui | partielle | — | — | — | — | — | NON COMMENCÉ | oui | Avant shipping |
| C-20 | Observabilité / UX | 20 | oui | partielle | — | — | — | — | — | NON COMMENCÉ | conditionnel | Preuve vs produit |
| C-21 | Simulation / fréquences / perf | 21 | oui | partielle | — | — | — | — | — | NON COMMENCÉ | oui | Avant scale |
| C-22 | Investor Demo | — | non | suffisante | n/a | n/a | n/a | n/a | n/a | NON COMMENCÉ | non | Docs présentation ; pas contrat gameplay |
| C-23 | Présentation M4 / UDS | — | non | suffisante | n/a | n/a | n/a | n/a | n/a | NON COMMENCÉ | non | Rendu ; pas contrat gameplay |

\* Addendum conditionnel — registre §5 / §7.

---

## 5. Contrat actuellement en cours

```text
Contrat actuel : aucun
Dernier validé : C-08
```

**C-08 — VALIDÉ** (clôture formelle)

| Étape | État |
| --- | --- |
| Audit préparatoire / inspection code | **terminé** |
| Décisions | **prises** — **58/58** (A1–L4) |
| Rédaction | **terminée** — `CONTRATS/C-08_TERRAFORMER_OPERATIONNEL.md` |
| Revue / audit contrat | **terminé** (AUDIT FINAL — PASS ; 58/58) |
| Validation | **acquise** — validation humaine explicite |

**C-01**, **C-02**, **C-04**, **C-05** et **C-07** restent **VALIDÉ**.  
**C-03** reste addendum fermé (NON COMMENCÉ / hors compteur).  
**C-06\***, **C-09\*** et **C-10\*** restent addenda fermés (SUFFISANT\* / hors compteur).  
C-11 et suivants restent **NON COMMENCÉS** (aucun travail engagé). Case B reste **suspendu**.

---

## 6. Prochain contrat autorisé

```text
Prochain contrat autorisé :
C-11
```

Prochain élément **requis** du compteur 16 / ordre officiel après C-08.  
**Ne pas démarrer** C-11 sans ordre explicite.  
C-03, C-06, C-09 et C-10 restent des addenda `SUFFISANT*` fermés (registre §5) — **ne pas les ouvrir** automatiquement. Case B reste **suspendu** (réactivation = autorisation explicite distincte).

---

## 7. Contrats bloqués / suspendus

| Sujet | Statut suivi | Motif |
| --- | --- | --- |
| **Case B** (gameplay / Demo) | **SUSPENDU** | Contrats documentaires C-05·C-07·C-08 VALIDÉS ; réactivation / implémentation / validation produit **interdites** sans autorisation explicite distincte ; dettes runtime conservées |
| Aucun contrat documentaire | BLOQUÉ | — |

---

## 8. Historique de progression

| Date | Contrat | Ancien statut | Nouveau statut | Motif |
| --- | --- | --- | --- | --- |
| 2026-10-08 | — | — | — | Création du suivi de production |
| 2026-10-08 | C-01 | NON COMMENCÉ | AUDIT PRÉPARATOIRE → **DÉCISIONS EN COURS** | Audit préparatoire terminé ; décisions humaines requises ; rédaction non ouverte |
| 2026-10-08 | C-01 | DÉCISIONS EN COURS | **REVUE** | Contrat `C-01_TERRAIN_RUNTIME.md` rédigé ; en attente d’audit et validation ; pas VALIDÉ |
| 2026-10-08 | C-01 | REVUE | **VALIDÉ** | Validation humaine explicite ; audit contrat PASS ; écarts d’implémentation conservés comme dettes |
| 2026-10-08 | C-02 | NON COMMENCÉ | **REVUE** | Contrat `C-02_SUBSTRAT_SPATIAL.md` rédigé ; en attente d’audit et validation ; compteur reste 1/16 |
| 2026-10-08 | C-02 | REVUE | **VALIDÉ** | Validation humaine explicite ; 31/31 A1–F3 ; audit final PASS ; compteur **2 / 16** |
| 2026-10-08 | C-04 | NON COMMENCÉ | **REVUE** | Contrat `C-04_TACHES_GRAPHE_DEPENDANCES.md` rédigé ; audit 48/48 PASS ; compteur reste 2/16 |
| 2026-10-08 | C-04 | REVUE | **VALIDÉ** | Validation humaine explicite ; 48/48 A1–K6 ; audit final PASS ; compteur **3 / 16** |
| 2026-10-08 | C-05 | NON COMMENCÉ | **REVUE** | Contrat `C-05_WORKSITE_SITEPREP.md` rédigé ; audit 62/62 PASS ; compteur reste 3/16 |
| 2026-10-08 | C-05 | REVUE | **VALIDÉ** | Validation humaine explicite ; 62/62 A1–N3 ; audit final PASS ; compteur **4 / 16** |
| 2026-10-09 | C-07 | NON COMMENCÉ | **REVUE** | Contrat `C-07_AUTONOMIE_UNITE_AGENT_GENERIQUE.md` rédigé ; audit 47/47 PASS ; compteur reste 4/16 |
| 2026-10-09 | C-07 | REVUE | **VALIDÉ** | Validation humaine explicite ; 47/47 A1–J4 ; audit final PASS ; compteur **5 / 16** |
| 2026-10-09 | C-08 | NON COMMENCÉ | **REVUE** | Contrat `C-08_TERRAFORMER_OPERATIONNEL.md` rédigé ; audit 58/58 PASS ; compteur reste 5/16 |
| 2026-10-09 | C-08 | REVUE | **VALIDÉ** | Validation humaine explicite ; 58/58 A1–L4 ; audit final PASS ; compteur **6 / 16** |

---

*Fin du suivi — C-01·C-02·C-04·C-05·C-07·C-08 VALIDÉS ; compteur 6/16 ; Case B suspendu ; C-03·C-06·C-09·C-10 addenda fermés ; prochain requis = C-11.*
