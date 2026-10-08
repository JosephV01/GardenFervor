# CONTRATS — SUIVI DE PRODUCTION

**Fichier :** `CONTRATS/00_SUIVI_CONTRATS.md`  
**Statut :** initialisé  
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
| Contrats dédiés VALIDÉS | **0** |
| Progression validation | **0 / 16** |

*(Les `SUFFISANT*` et `NON REQUIS` sont suivis dans le tableau mais exclus du dénominateur tant qu’aucun addendum / contrat dédié n’est ouvert.)*

### Tableau

Légende progression : `—` = non commencé · `OK` = terminé · `EN COURS` · `n/a` = hors production de contrat dédié.

| ID | Nom | Ordre | Contrat requis | Couverture existante | Audit | Décisions | Rédaction | Revue | Validation | Statut | Bloquant | Notes |
| -- | --- | ----: | -------------- | -------------------- | ----- | --------- | --------- | ----- | ---------- | ------ | -------- | ----- |
| C-00 | Cadre / invariants fondateurs | — | non | suffisante | n/a | n/a | n/a | n/a | n/a | NON COMMENCÉ | non | Pas de contrat dédié (DG-00) |
| C-01 | Terrain runtime | 1 | oui | partielle | OK | OK | OK | EN COURS | — | **REVUE** | oui | Contrat rédigé — en attente d’audit et validation ; fichier `C-01_TERRAIN_RUNTIME.md` |
| C-02 | Substrat spatial | 2 | oui | partielle | — | — | — | — | — | NON COMMENCÉ | oui | Après C-01 |
| C-03 | Projet / Intention | 3* | addendum* | suffisante | — | — | — | — | — | NON COMMENCÉ | non* | S3 suffisant ; pas VALIDÉ dédié |
| C-04 | Tâches / graphe / dépendances | 4 | oui | partielle | — | — | — | — | — | NON COMMENCÉ | oui | |
| C-05 | WorkSite / SitePrep | 5 | oui | partielle | — | — | — | — | — | NON COMMENCÉ | oui | Lié Case B suspendu |
| C-06 | Capacités / roster | 6* | addendum* | suffisante | — | — | — | — | — | NON COMMENCÉ | non* | S3 suffisant ; pas VALIDÉ dédié |
| C-07 | Autonomie unité | 7 | oui | partielle | — | — | — | — | — | NON COMMENCÉ | oui | |
| C-08 | Terraformer opérationnel | 8 | oui | partielle | — | — | — | — | — | NON COMMENCÉ | oui | Bloque Demo Case B |
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
Contrat actuel : C-01
Étape : REVUE
```

**C-01 — contrat rédigé / en attente d’audit et validation**

| Étape | État |
| --- | --- |
| Audit préparatoire | **terminé** |
| Décisions | **prises** (14/14 reprises dans le contrat) |
| Rédaction | **terminée** — `CONTRATS/C-01_TERRAIN_RUNTIME.md` |
| Revue | **en cours** (audit / validation humaine en attente) |
| Validation | **non acquise** — statut ≠ VALIDÉ |

C-02 et suivants restent **NON COMMENCÉS**.

---

## 6. Prochain contrat autorisé

```text
Prochain contrat autorisé :
C-01
```

Tant que **C-01** n’est pas **VALIDÉ**, aucun contrat d’ordre supérieur (C-02, …) ne doit être considéré comme en cours.  
Les addenda `*` restent fermés tant que le besoin S3 n’est pas dépassé (registre).

---

## 7. Contrats bloqués / suspendus

| Sujet | Statut suivi | Motif |
| --- | --- | --- |
| **Case B** (gameplay / Demo) | **SUSPENDU** | Registre §9 — signal audit Terraformer ; pas de reprise sans contrats bloquants |
| C-05 / C-07 / C-08 (liés Case B) | NON COMMENCÉ | Non suspendus en tant que production documentaire ; Case B reste suspendu côté implémentation |
| Aucun contrat documentaire | BLOQUÉ | — |

---

## 8. Historique de progression

| Date | Contrat | Ancien statut | Nouveau statut | Motif |
| --- | --- | --- | --- | --- |
| 2026-10-08 | — | — | — | Création du suivi de production |
| 2026-10-08 | C-01 | NON COMMENCÉ | AUDIT PRÉPARATOIRE → **DÉCISIONS EN COURS** | Audit préparatoire terminé ; décisions humaines requises ; rédaction non ouverte |
| 2026-10-08 | C-01 | DÉCISIONS EN COURS | **REVUE** | Contrat `C-01_TERRAIN_RUNTIME.md` rédigé ; en attente d’audit et validation ; pas VALIDÉ |

---

*Fin du suivi — C-01 rédigé non validé ; aucun autre contrat individuel ouvert.*
