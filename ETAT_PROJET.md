# GardenFervor — État projet (baseline)

Dernière mise à jour : **2026-10-10**  
Companions : `REGLES_PROJET.md` (§1bis) · `HISTORIQUE_MODIFICATIONS.md` (mémoire longue) · `REGISTRE_MAINTENANCE_DOCUMENTAIRE.md` (inventaire sync) · Design Gate React (`GardenFervor_DesignGate_React/src/data/designGate.js`) · Contrats (`CONTRATS/00_SUIVI_CONTRATS.md`).

**Contrats opérationnels :** C-01 · C-02 · C-04 · C-05 · C-07 · C-08 · C-11 · C-12 · C-14 = **VALIDÉ** · progression **9 / 16** · prochain requis = C-15 (non commencé) · C-03·C-06·C-09·C-10·C-13 addenda **fermés** · Case B **suspendu** · ODC-F9 **non démarré**.

---

## Phase ODC

| Phase | Statut | Preuve |
| --- | --- | --- |
| ODC-F1 Terrain runtime (Base+Delta shipping) | **À REFAIRE** | `Saved/ODC_F1_RuntimeTerrainGate.txt` (INVALIDÉ) |
| ODC-F2 M4 / RVT / UDS / UDW | **PASS** | `Saved/ODC_F2_VisualTerrainGate.txt` |
| ODC-F3 Spatial substrate | **PASS** | `Saved/ODC_F3_SimulationSubstrateGate.txt` |
| ODC-F4 Projet → tâche | **PASS** | `Saved/ODC_F4_TaskGraphGate.txt` |
| ODC-F5 Autonomie unité | **PASS (humain)** | `Saved/ODC_F5_AutonomyGate.txt` + PIE |
| ODC-F6 Économie physique minimale | **PASS** | `Saved/ODC_F6_EconomyGate.txt` |
| ODC-F7 Logistique | **PASS (humain)** | `Saved/ODC_F7_LogisticsGate.txt` + PIE |
| ODC-F8 Terraformer industriel | **PASS** | `Saved/ODC_F8_TerraformOperationGate.txt` |

---

## Ce qui fonctionne

- Autonomie + haul Pit→Pad + matière Spoil→Fill
- **Terraform ops** : Raise/Lower/Compact branchés agents → store (données) + LandscapeEdit en PIE (session-only)
- Spatial dirty après brush

---

## Risques / ouvert

- F1 shipping Base+Delta visual packaged encore à refaire (F8 prouve la **donnée**, pas le PMC)
- Compact/Grade = alias industriels basiques
- Sol / eau spatial = stubs
- **Readiness :** F01·F02·F03 · **contrôle final PASS** · Plan de production S3 créé — **pas d’implémentation** ; code **uniquement sur ordre explicite** (DG-14.4 · tranche T1+)
---

## Kit minimal de cohorte forestière — arbitré

**Statut :** défini pour la préparation de l’implémentation contrôlée — **implémentation non démarrée** · **non autorisée par la seule formalisation**.

| Élément | Contenu arbitrée |
| --- | --- |
| Réf. doc | `FORMALISATION_02_KIT_COHORTE_FORESTIERE.md` · `FORMALISATION_03_ARBITRAGES_C7_C4_C5_C6.md` |
| Ancre DG | DG-14.3 (preuve) · DG-14.4 (transition future) |
| Service | **S3** — Achevé + Stock B Timber > 0 → **En service** (critère cohorte) |
| Bois | Clé PE **`Timber`** (C7) · Option A Stock B · pas de coût inventé |
| Stocks | A ≠ B obligatoires ; indépendants ; pas d’Owner |
| Roster | U1 Exploitation · U2 Transport · U3 Construction/Service |
| Intention | Entrée dédiée minimale Intention→Project (C4) — pas BeginPlace/TrySpend |
| Observabilité | Smoke / PE (C6) — pas HUD FWSG |
| Analyse | `Analyze` générique — pas de ForestAnalysis |
| Terraform | Conditionnel ; 1ʳᵉ preuve = Cas A (terrain déjà prêt) |
| Chaîne | Intention → Project → Analyze → (prep si besoin) → U1→A → U2→B → U3 → En service → observable |

### Arbitrages C7 · C4 · C5 · C6 — formalisés

| Id | Décision |
| --- | --- |
| **C7** | ResourceKey officielle = **`Timber`** ; vérité `PhysicalResourceTypes.h` ; `Wood` = legacy seulement |
| **C4** | Intention→Project via mécanisme dédié minimal ; sans EconomyComponent / TrySpend / BeginPlace / Ages / coûts |
| **C5** | Achevé ≠ En service ; réussite S3 = Achevé + Timber en Stock B → En service (critère cohorte, pas universel jeu) |
| **C6** | Observabilité smoke/PE ; pas HUD FWSG ; pas UI DG-13 complète |

---

## Design Gate (React)

- Source : `GardenFervor_DesignGate_React/src/data/designGate.js` — **document vivant**
- Maintenance permanente : consulter / mettre à jour à chaque décision ou jalon impactant la conception (`REGLES_PROJET.md` §7octies)
- Aucun item ne passe à `VALIDÉ` sans confirmation explicite
- **DG-00 CADRE : VALIDÉ** (clôture section ; 94/94 items VALIDÉ ; audit de cohérence PASS)
- **DG-01 BOUCLE FONDAMENTALE : VALIDÉ** (clôture section ; 6/6 items VALIDÉ ; audit de cohérence PASS)
- **DG-02 BÂTIMENTS ET CONSTRUCTIONS : VALIDÉ** (clôture section ; 13/13 items VALIDÉ ; audit de cohérence PASS)
- **DG-03 UNITÉS : VALIDÉ** (clôture section ; 8/8 items VALIDÉ ; audit de cohérence PASS)
- **DG-04 AUTONOMIE DES UNITÉS : VALIDÉ** (clôture section ; 7/7 items VALIDÉ ; audit de cohérence PASS)
- **DG-05 RESSOURCES ET ÉCONOMIE : VALIDÉ** (clôture section ; 4/4 items VALIDÉ ; audit de cohérence PASS)
- **DG-06 LOGISTIQUE ET TRANSPORT : VALIDÉ** (clôture section ; 5/5 items VALIDÉ ; audit de cohérence PASS ; saturation = N4)
- **DG-07 RECHERCHE ET PROGRESSION : VALIDÉ** (clôture section ; 7/7 items VALIDÉ ; audit de cohérence PASS)
- **DG-08 TERRAIN ET TERRAFORMATION : VALIDÉ** (clôture section ; 5/5 items VALIDÉ ; audit de cohérence PASS)
- **DG-09 ENVIRONNEMENT ET ÉCOSYSTÈMES : VALIDÉ** (clôture section ; 6/6 items VALIDÉ ; audit de cohérence PASS)
- **DG-10 INFRASTRUCTURES : VALIDÉ** (clôture section ; 5/5 items VALIDÉ ; audit de cohérence PASS)
- **DG-11 CHANTIERS ET EXÉCUTION PROCÉDURALE : VALIDÉ** (clôture section ; 8/8 items VALIDÉ ; audit de cohérence PASS)
- **DG-12 INTERACTION ENTRE LES SYSTÈMES : VALIDÉ** (clôture section ; 6/6 items VALIDÉ ; audit de cohérence PASS)
- **DG-13 UX ET LISIBILITÉ : VALIDÉ** (clôture section ; 5/5 items VALIDÉ ; audit de cohérence PASS)
- **DG-14 CONDITIONS DE VALIDATION ET PASSAGE À L’IMPLÉMENTATION : VALIDÉ** (clôture section ; 4/4 items VALIDÉ ; audit de cohérence PASS — CLÔTURABLE)
- 00.1–00.7 + sous-items 00.5 (S→X) + 00.6 (V→P) : tous VALIDÉ
- **00.5.W1** : formulation clarifiée (horizon fondateur + ambition hydrologique à long terme) — **confirmation humaine d’impact acquise** ; Hub local `docs/design-gate.html` aligné et vérifié ; clôture documentaire ; W2·W3·W4·X1·X2 inchangés
- **Présentation client :** 10 illustrations 2026-10-10 intégrées (WebP) ; capture S3 réelle conservée ; C-15 non commencé

**Points reportés aux DG suivants (depuis clôtures DG-00 / DG-01 / DG-02) :**
1. Extensions territoriales (nombre / forme / taille) — S6 → DG-14+
2. Valeurs chiffrées des ordres de durée — T2 → DG-04 / DG-07 / DG-11
3. Qualité des ressources — conditionnelle (05.1) ; détail par ressource encore progressif  
4. Pertes / maintenance détaillée / usure composant — encore différées (X2 / U8–U9)  
5. Vocabulaire joueur déblai / remblai — **tranché en 08.3** (Spoil/Fill restent internes)  
6. Fiches d’impact bâtiment → eau / sol / végétation — cadre F1/B7 + règles 09.4 ; contenu fin par fiche encore progressif
7. États écologiques aquatiques associés aux structures W — **reportés** (09.2 : hydrologie d’abord)
8. Configurations d’équipement (contenu exact) — U6 → DG-03 / DG-07
9. Économie d’entretien des réseaux — **restée différée** (10.4 = état simplifié seulement ; N1 ouvert)
10. Relation grille logique / grille de construction — S5 → DG-08 / DG-11
11. Appliquer K1–K4 avant toute nouvelle mécanique ; réutiliser V4, P1, Y2
12. **DG-02 clôturé** — fiches / familles / catalogue / interdépendances (`02.13`) VALIDÉ ; appliquer en conception détaillée aval
13. **DG-03 clôturé** — familles / mobilité / acquisition / canevas ; autonomie traitée en DG-04  
14. **DG-04 clôturé** — sélection / priorisation / déplacement / exécution / replanification / intervention / lisibilité VALIDÉ ; `11.6` articule recalcul chantier sans réécrire `04.5`
15. **DG-05 clôturé** — taxonomie / chaîne / stocks-réservations / progressives VALIDÉ ; ressources env. = vérité minimale (09.1) ; consommables si besoin réel
16. **DG-06 clôturé** — modes / accès réseaux / accès auto / réutilisation / chaîne VALIDÉ ; saturation = N4 ; économie d’entretien réseau encore ouverte  
17. **DG-07 clôturé** — principal / recherche / schémas / technologies / déblocages / progression horizontale / environnementale VALIDÉ ; effets écologiques → DG-09  
18. **DG-08 clôturé** — état terrain / Raise-Lower-Paint / travaux / accès / conséquences VALIDÉ ; Eau/Sols/Végétation dirty → comportements DG-09  
19. **DG-09 clôturé** — couches / écosystèmes / transitions / impacts / objectif / grands ouvrages VALIDÉ ; aquatique associé différé ; détail ouvrages différé
20. **DG-10 clôturé** — temporaires / cycle / permanentes / partage / impact VALIDÉ ; conversion temp→perm différée ; rails différés ; entretien = état simplifié
21. **DG-11 clôturé** — déclenchement / analyse / génération / solution cachée / procédural / réaction / fin / rejouabilité VALIDÉ ; recalcul chantier ≠ `04.5`
22. **DG-12 clôturé** — matrices bâtiment↔unité/ressources/infra · système↔environnement · preuve forestière · contradictions fondatrices OK
23. **DG-13 clôturé** — disponibilité / blocage / unité / progression / surcharge VALIDÉ ; lisibilité sans feuille de calcul ni microgestion
24. **DG-14 clôturé** — 14.1–14.4 VALIDÉ ; conditions de passage à l’implémentation contrôlée définies ; **implémentation / cohorte non démarrées**
25. Contenu exact du kit de départ (01.1 / 02.3 sous-ensemble ≤4) ; critères détaillés de compréhension de la boucle (01.6 / P1)

---

## Plan de production

| Élément | État |
| --- | --- |
| Contrôle final | **PASS — PRÊT POUR IMPLÉMENTATION CONTRÔLÉE** — `Audit de readiness pré-implémentation/CONTROLE_FINAL_PRE_IMPLEMENTATION_COHORTE.md` |
| Plan | `Plan de production/PLAN_PRODUCTION_COHORTE_S3.md` |
| Roadmap | SoT `Roadmap/src/roadmap.data.js` · Pages `docs/roadmap.html` · Hub `docs/index.html` · URL `https://josephv01.github.io/GardenFervor/` |
| Première preuve | Cohorte S3 **Cas A** (sans Terraform obligatoire) |
| Tranches | T1–T9 VALIDÉ · progression **9/9 VALIDÉ** (100 %) · cohorte S3 Cas A **clôturée** |
| Implémentation | T9 preuve S3 Cas A **VALIDÉ** (PIE `gf.Project.SmokeCohortS3` ok=1) — aucune tranche suivante |
| Note stocks | `LinkedPitStockId` = Stock A PE ; critère En service = **Stock B** · risque sémantique Pit/LevelPad · ne pas renommer |

---

## Prochain pas

1. Contrats : C-14 clôturé — **ne pas démarrer C-15** sans ordre explicite ; C-03·C-06·C-09·C-10·C-13 restent addenda* fermés ; Case B **suspendu** ; ODC-F9 **non démarré** automatiquement
2. Cohorte S3 Cas A terminée — **aucun travail gameplay supplémentaire** hors ordre explicite
3. **Validation humaine F8** : PIE → Start LevelPad → constater raise Landscape près du pad (session-only)
4. **ODC-F9** Infrastructure lifecycle (sur ordre explicite — sans contourner DG ; C-14 = règles ≠ preuve F9)
5. Interdit sans validation : carte / M4 / T01
