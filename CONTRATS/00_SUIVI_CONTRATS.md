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
| Contrats dédiés VALIDÉS | **15** |
| Progression validation | **15 / 16** |

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
| C-11 | Réservations | 11 | oui | partielle | OK | OK | OK | OK | OK | **VALIDÉ** | oui | Validé humainement ; 23/23 A1–G1 ; audit final PASS ; C-09·C-10 addenda fermés ; Case B reste suspendu ; dettes d’implémentation / preuves manquantes conservées |
| C-12 | Transport / logistique | 12 | oui | partielle | OK | OK | OK | OK | OK | **VALIDÉ** | oui | Validé humainement ; 25/25 A1–G3 ; audit final PASS ; C-10 addendum fermé ; Case B reste suspendu ; dettes d’implémentation / preuves partielles (§17) conservées |
| C-13 | Construction / En service | 13* | addendum* | suffisante | — | — | — | — | — | NON COMMENCÉ | non* | Critère cohorte ; pas VALIDÉ dédié |
| C-14 | Infrastructures | 14 | oui | absente | OK | OK | OK | OK | OK | **VALIDÉ** | oui | Validé humainement ; 15/15 A1–F1 ; audit final PASS ; C-10·C-13\* addenda fermés ; Case B reste suspendu ; points ouverts §18 et dettes F9 / implémentation conservés |
| C-15 | Hydrologie | 15 | oui | absente | OK | OK | OK | OK | OK | **VALIDÉ** | oui | Validé humainement ; cadrage A–G ; audit après correction PASS ; W1 cité intégralement ; O1–O9 et dettes stub / Dirty Water conservés ; Case B reste suspendu ; aucune implémentation |
| C-16 | Sol | 16 | oui | absente | OK | OK | OK | OK | OK | **VALIDÉ** | oui | Validé humainement ; cadrage A1–K1 ; audit final PASS ; contrat de conception uniquement ; P1–P10 et O1–O9 C-15 conservés ; dettes stub / Dirty Soil conservées ; Case B reste suspendu ; aucune implémentation |
| C-17 | Végétation / écosystèmes | 17 | oui | partielle | OK | OK | OK | OK | OK | **VALIDÉ** | oui | Validé humainement ; cadrage A1–K1 ; audit final PASS ; contrat de conception uniquement ; Q1–Q12, O1–O9 C-15 et P1–P10 C-16 conservés ; Case B reste suspendu ; aucune implémentation écologique |
| C-18 | Technologie / progression | 18 | oui | partielle | OK | OK | OK | OK | OK | **VALIDÉ** | oui | Validé humainement ; cadrage Q1–Q31 ; audit final PASS ; contrat de conception uniquement ; R1–R8, R11 ouverts ; O1–O9, P1–P10 et Q1–Q12 C-17 conservés ; Ages = legacy ; ≠ runtime DG-07 |
| C-19 | Persistance / sauvegarde | 19 | oui | partielle | OK | OK | OK | OK | OK | **VALIDÉ** | oui | Validé humainement ; cadrage S1–S14 · L1–L3 ; audit final PASS ; contrat de conception uniquement ; O5, P8, Q7, R5 et R1–R8 / R11 conservés ; ≠ runtime persist / F1 |
| C-20 | Observabilité / UX lisibilité | 20 | oui | partielle | OK | OK | OK | OK | OK | **VALIDÉ** | oui (produit) | Validé humainement ; cadrage X1–X10 · L1–L3 ; audit final PASS ; contrat de conception uniquement ; R7 C-18 et O1–O9 / P1–P10 / Q1–Q12 conservés ; ≠ UX produit / HUD DG-13 |
| C-21 | Simulation / fréquences / perf | 21 | oui | partielle | — | — | — | — | — | NON COMMENCÉ | oui | Avant scale |
| C-22 | Investor Demo | — | non | suffisante | n/a | n/a | n/a | n/a | n/a | NON COMMENCÉ | non | Docs présentation ; pas contrat gameplay |
| C-23 | Présentation M4 / UDS | — | non | suffisante | n/a | n/a | n/a | n/a | n/a | NON COMMENCÉ | non | Rendu ; pas contrat gameplay |

\* Addendum conditionnel — registre §5 / §7.

---

## 5. Contrat actuellement en cours

```text
Contrat actuel : aucun
Dernier validé : C-20
```

**C-20 — VALIDÉ** (clôture formelle — contrat de conception uniquement)

| Étape | État |
| --- | --- |
| Audit préparatoire / inspection code | **terminé** |
| Décisions | **prises** — cadrage **X1–X10 · L1–L3** |
| Rédaction | **terminée** — `CONTRATS/C-20_OBSERVABILITE_UX_LISIBILITE.md` |
| Revue / audit contrat | **terminé** (étape 6 · corrections étape 7 · audit final PASS) |
| Validation | **acquise** — validation humaine explicite |

**C-01**, **C-02**, **C-04**, **C-05**, **C-07**, **C-08**, **C-11**, **C-12**, **C-14**, **C-15**, **C-16**, **C-17**, **C-18**, **C-19** et **C-20** restent **VALIDÉ**.  
**C-03** reste addendum fermé (NON COMMENCÉ / hors compteur).  
**C-06\***, **C-09\***, **C-10\*** et **C-13\*** restent addenda fermés (SUFFISANT\* / hors compteur).  
C-21 reste **NON COMMENCÉ**. Case B reste **suspendu**. ODC-F9 **non démarré**. Aucune implémentation écologique, sol, hydrologique, progression DG-07, persistance runtime ni UX produit. R1–R8, R11, Q1–Q12 C-17, C-15 O1–O9 et C-16 P1–P10 restent ouverts.

---

## 6. Prochain contrat autorisé

```text
Contrat en cours : aucun
Prochain contrat autorisé : C-21
```

C-20 est **VALIDÉ** (conception uniquement). **Ne pas** démarrer C-21 sans ordre explicite.  
C-03, C-06, C-09, C-10 et C-13 restent des addenda `SUFFISANT*` fermés (registre §5) — **ne pas les ouvrir** automatiquement. Case B reste **suspendu** (réactivation = autorisation explicite distincte). ODC-F9 reste **non démarré** automatiquement. Aucune implémentation écologique, sol, hydrologique, déblocage DG-07, persistance runtime ni UX produit.

---

## 7. Contrats bloqués / suspendus

| Sujet | Statut suivi | Motif |
| --- | --- | --- |
| **Case B** (gameplay / Demo) | **SUSPENDU** | Contrats documentaires C-05·C-07·C-08·C-11·C-12·C-14 VALIDÉS ; réactivation / implémentation / validation produit **interdites** sans autorisation explicite distincte ; dettes runtime conservées |
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
| 2026-10-09 | C-11 | NON COMMENCÉ | **REVUE** | Contrat `C-11_RESERVATIONS.md` rédigé ; audit 23/23 PASS ; compteur reste 6/16 |
| 2026-10-09 | C-11 | REVUE | **VALIDÉ** | Validation humaine explicite ; 23/23 A1–G1 ; audit final PASS ; compteur **7 / 16** |
| 2026-10-09 | C-12 | NON COMMENCÉ | **REVUE** | Contrat `C-12_TRANSPORT_LOGISTIQUE.md` rédigé ; audit 25/25 PASS ; compteur reste 7/16 |
| 2026-10-09 | C-12 | REVUE | **VALIDÉ** | Validation humaine explicite ; 25/25 A1–G3 ; audit final PASS ; compteur **8 / 16** |
| 2026-10-09 | C-14 | NON COMMENCÉ | **REVUE** | Contrat `C-14_INFRASTRUCTURES_LIFECYCLE.md` rédigé ; audit 15/15 PASS FINAL ; compteur reste 8/16 |
| 2026-10-09 | C-14 | REVUE | **VALIDÉ** | Validation humaine explicite ; 15/15 A1–F1 ; audit final PASS FINAL ; compteur **9 / 16** |
| 2026-10-10 | C-15 | NON COMMENCÉ | **REVUE** | Contrat `C-15_HYDROLOGIE.md` rédigé puis corrigé (W1 intégral + §3.2 emprise) ; audit après correction PASS ; compteur reste 9/16 |
| 2026-10-10 | C-15 | REVUE | **VALIDÉ** | Validation humaine explicite ; cadrage A–G ; audit après correction PASS ; O1–O9 conservés ; compteur **10 / 16** |
| 2026-10-10 | C-16 | NON COMMENCÉ | **VALIDÉ** | Validation humaine explicite ; cadrage A1–K1 ; audit final PASS ; contrat de conception uniquement ; P1–P10 et O1–O9 C-15 conservés ; compteur **11 / 16** |
| 2026-10-10 | C-17 | NON COMMENCÉ | **VALIDÉ** | Validation humaine explicite ; cadrage A1–K1 ; audit final PASS ; contrat de conception uniquement ; Q1–Q12, O1–O9 C-15 et P1–P10 C-16 conservés ; compteur **12 / 16** |
| 2026-10-10 | C-18 | NON COMMENCÉ | **REVUE** | Brouillon publié (`C-18_TECHNOLOGIE_PROGRESSION.md`, `632b6ee`) ; Q1–Q31 formalisés ; audit étape 6 + corrections étape 7 ; **DRAFT / BROUILLON — non validé** ; compteur reste **12 / 16** |
| 2026-10-10 | C-18 | REVUE | **VALIDÉ** | Validation humaine explicite ; cadrage Q1–Q31 ; audit final PASS ; contrat de conception uniquement ; R1–R8, R11 ouverts ; O1–O9, P1–P10 et Q1–Q12 C-17 conservés ; compteur **13 / 16** |
| 2026-10-10 | C-19 | NON COMMENCÉ | **VALIDÉ** | Validation humaine explicite ; cadrage S1–S14 · L1–L3 ; audit final PASS ; contrat de conception uniquement ; O5, P8, Q7, R5 et R1–R8 / R11 conservés ; compteur **14 / 16** |
| 2026-10-10 | C-20 | NON COMMENCÉ | **VALIDÉ** | Validation humaine explicite ; cadrage X1–X10 · L1–L3 ; audit final PASS ; contrat de conception uniquement ; R7 C-18 et O1–O9 / P1–P10 / Q1–Q12 conservés ; compteur **15 / 16** |

---

*Fin du suivi — C-01·C-02·C-04·C-05·C-07·C-08·C-11·C-12·C-14·C-15·C-16·C-17·C-18·C-19·C-20 VALIDÉS ; compteur 15/16 ; C-21 non commencé ; Case B suspendu ; C-03·C-06·C-09·C-10·C-13 addenda fermés ; aucune implémentation écologique, DG-07, persist runtime ni UX produit.*
