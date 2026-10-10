# GardenFervor — Registre de maintenance documentaire

**Fichier :** `REGISTRE_MAINTENANCE_DOCUMENTAIRE.md` (racine)  
**Statut :** actif  
**Rôle :** inventaire opérationnel des documents et artefacts à maintenir, de leurs dépendances, déclencheurs et procédures réelles.  
**Public :** humains et agents Cursor.  
**Création initiale :** 2026-10-09 (post clôture C-14).  
**Dernière révision inventaire :** 2026-10-09 — réconciliation avec l’audit exhaustif du patrimoine documentaire ; clôture A2 (GitHub Pages) puis clôture A1 (libellés Contrats) le même jour.  
**HEAD Git contrôlé lors de cette révision :** `cf3c1ff` (`cf3c1ff5dadf79d0822a095d026021504b6571ca`) = `origin/main`.  
*(La révision initiale citait `e4e6bd6` ; ce hash n’est plus le HEAD courant.)*

---

## 0. Comment utiliser ce registre

1. Avant une opération documentaire significative : lire ce fichier + `REGLES_PROJET.md` §1bis + `ETAT_PROJET.md`.
2. Identifier l’événement (matrice §3, **une seule** matrice E1–E13) → sources à modifier → vues à régénérer → validations.
3. **Sources canoniques d’abord**, miroirs manuels ensuite, génération ensuite, validation en dernier.
4. Après l’opération : appliquer la **règle d’auto-maintenance** (§5) avant de déclarer la tâche terminée.
5. Ne jamais traiter une vue générée comme source de vérité.
6. Ne pas exécuter `syncPages` ni un build documentaire sans autorisation adaptée à la tâche.
7. Les **propositions** (§8) ne sont pas des règles tant qu’elles n’ont pas été tranchées.

Ce registre **n’est pas** une source de vérité de gameplay ni de conception.  
Il ne remplace ni le Design Gate, ni les contrats, ni `ETAT_PROJET.md`.

---

## 1. Principes

| Principe | Règle |
| --- | --- |
| Autorité | Le Markdown / JS / données de source prime sur le HTML publié |
| Fréquence | **Événementielle** (clôture, décision, sync, changement d’architecture) — **aucune** cadence quotidienne, hebdomadaire ou mensuelle |
| VALIDÉ | Documentaire ≠ runtime ; ne jamais inventer un statut VALIDÉ |
| Génération | Utiliser uniquement les commandes listées ici (vérifiées dans le dépôt) |
| Hub | Après modification documentaire **destinée à Pages** et **autorisée** : `node docs/syncPages.mjs` |
| Préservation Git | Ne jamais `git add .` / `git add -A` ; commits dédiés ; push sur autorisation |
| Auto-maintenance | Si le patrimoine documentaire change, mettre à jour **ce registre** dans le périmètre autorisé (§5) |

**Proposition non officielle (à décider) :** revue périodique optionnelle de ce registre (ex. après chaque vague de contrats). Ce n’est **pas** une règle tant qu’elle n’est pas tranchée explicitement.

### 1.1 Nature des artefacts

| Nature | Signification |
| --- | --- |
| **CANONIQUE** | Source qui fait autorité. On l’édite ; on ne la régénère pas depuis une vue. |
| **MIROIR MANUEL** | Copie qu’une procédure humaine doit aligner explicitement. Pas de générateur vérifié. |
| **GÉNÉRÉ** | Résultat produit par un script. Ne pas l’éditer à la main. |
| **SCRIPT** | Outil de génération, synchronisation ou validation. |
| **RÉFÉRENCE** | Utile, mais pas à modifier à chaque événement. |
| **PREUVE** / **ARCHIVE** | Justificatif, gate, ou document historique. |
| **OUTIL** | Interface ou fichier de développement local, hors chaîne Pages. |
| **À CLARIFIER** | Autorité, dépendance ou statut **non établi**. Ne pas arbitrer ici. |

---

## 2. Inventaire vérifié

Légende **Nature** : voir §1.1.

**Compteurs — constat daté 2026-10-09 (réconciliation), pas un total éternel :**

| Constat | Nombre | Qualification |
| --- | --- | --- |
| Canvas d’audit (vue filtrée) | 104 | Hors 38 JPEG et 4 doublons `Saved/` ; **ne pas** citer comme total disque |
| JPEG source `lot1/` | 0 | Galerie lot1 **retirée** (2026-10-10) ; remplacée par 8 WebP nommés §2.8 |
| Copies `docs/images/lot1/` | 0 | Dossier lot1 publié **supprimé** |
| Doublons Saved `*RuntimeGate.txt` | 4 | Autorité **non tranchée** §2.9 / §8 |
| Entrées nominatives de ce registre | voir bas de §2 | Recalculées à cette révision |
| `node_modules/` | non inventorié | Exclusion justifiée |

Distinction : **inventaire opérationnel** (maintenance événementielle) vs **hors opérationnel** (référence, archive, outil local, runtime).

### 2.1 Pilotage projet

| ID | Document / artefact | Catégorie | Rôle | Nature | Source de vérité | Déclencheurs | Fréquence | Dépendances | Procédure | Validation | Risque si oubli | État |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| DOC-REGLES | `REGLES_PROJET.md` | Règles | Process opérationnel, §1bis, Hub, Design Gate | CANONIQUE | elle-même | nouvelle règle process ; nouvel outil documentaire | à chaque événement process | ETAT, HISTORIQUE, Hub | éditer MD | relecture humaine | agents hors process | Actif |
| DOC-ETAT | `ETAT_PROJET.md` | Suivi | Snapshot court courant | CANONIQUE | elle-même (baseline) | gate, clôture, fix validé, doc majeure | à chaque modification validée (§1bis) | HISTORIQUE, REGLES | éditer MD | cohérence avec dernière entrée HISTORIQUE | faux « état courant » | Actif |
| DOC-HIST | `HISTORIQUE_MODIFICATIONS.md` | Suivi | Mémoire longue ; §4 = chronologie des modifications validées | CANONIQUE | elle-même | toute modification validée | à chaque livrable validé | ETAT, REGLES | ajouter entrée §4 (`### date — ID — titre`) | ordre récent→ancien ; IDs uniques | perte de mémoire agent | Actif ; miroir Hub = §4 seulement |
| DOC-MAINT | `REGISTRE_MAINTENANCE_DOCUMENTAIRE.md` | Suivi | Inventaire maintenance + matrice | CANONIQUE | elle-même | création/déplacement/suppression doc, script, page Hub ou dépendance | à chaque changement de périmètre doc | REGLES, scripts Hub | éditer MD + contrôle chemins §6 | chemins existent ; natures non confondues | docs orphelines / sync oubliée | Actif |
| DOC-ODC-DOCX | `GardenFervor_ODC_v1.0.docx` | Référence | ODC produit | RÉFÉRENCE | elle-même | révision produit rare | rare | — | hors Hub | n/a Pages | dérive vs extrait | **Non suivi Git** (`??`) ; hors opérationnel courant |
| DOC-ODC-TXT | `Saved/GardenFervor_ODC_v1.0_extracted.txt` | Référence | Extrait texte ODC | RÉFÉRENCE | DOC-ODC-DOCX | réexport | rare | docx | extraction manuelle | comparaison visuelle | extrait stale | Référence |

### 2.2 Contrats

Fichiers `C-03`, `C-06`, `C-09`, `C-10`, `C-13` : **absents volontairement** (addenda hors compteur 16). Ce n’est pas un lien cassé.

`contractsSuivi.js` est un **MIROIR MANUEL**. Toute clôture impose de vérifier sa cohérence avec `00_SUIVI_CONTRATS.md`, `00_REGISTRE_CONTRATS.md` et les contrats dédiés, puis les pages qui le consomment (`docs/contracts.html`, bandeau `docs/index.html`, compteurs live de `docs/etat-global.html`). Aucun générateur MD→JS n’est présent dans le dépôt.

| ID | Document / artefact | Catégorie | Rôle | Nature | Source de vérité | Déclencheurs | Fréquence | Dépendances | Procédure | Validation | Risque si oubli | État |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| DOC-REG-C | `CONTRATS/00_REGISTRE_CONTRATS.md` | Contrats | Liste, nécessité, ordre, dépendances | CANONIQUE | elle-même | clôture / ouverture contrat | clôture & arbitrages registre | SUIVI, contrats dédiés | éditer MD | compteur / ordre cohérents | mauvais prochain contrat | Actif |
| DOC-SUIVI-C | `CONTRATS/00_SUIVI_CONTRATS.md` | Contrats | Avancement production documentaire | CANONIQUE | elle-même | clôture contrat | chaque clôture | REGISTRE, contrat dédié | éditer MD | progression N/16 | Hub contrats faux | Actif ; §5 : C-18 REVUE / dernier VALIDÉ C-17 |
| DOC-ROUT-C | `CONTRATS/ReglesRoutinesContrats.md` | Contrats | Routine étapes contrats | CANONIQUE | elle-même | évolution process contrats | événementielle | SUIVI | éditer MD | — | clôtures incohérentes | Actif **et non suivi Git** (`??`) — constat, pas une action d’indexation |
| DOC-C01 | `CONTRATS/C-01_TERRAIN_RUNTIME.md` | Contrats | Règle C-01 | CANONIQUE | elle-même | réouverture seulement | stable post-VALIDÉ | SUIVI, REGISTRE | routine DOC-ROUT-C | audit + validation humaine | règle terrain ambiguë | Actif |
| DOC-C02 | `CONTRATS/C-02_SUBSTRAT_SPATIAL.md` | Contrats | Règle C-02 | CANONIQUE | elle-même | réouverture seulement | stable post-VALIDÉ | SUIVI, REGISTRE | routine DOC-ROUT-C | idem | règle ambiguë | Actif |
| DOC-C04 | `CONTRATS/C-04_TACHES_GRAPHE_DEPENDANCES.md` | Contrats | Règle C-04 | CANONIQUE | elle-même | réouverture seulement | stable post-VALIDÉ | SUIVI, REGISTRE | routine DOC-ROUT-C | idem | règle ambiguë | Actif |
| DOC-C05 | `CONTRATS/C-05_WORKSITE_SITEPREP.md` | Contrats | Règle C-05 | CANONIQUE | elle-même | réouverture seulement | stable post-VALIDÉ | SUIVI, REGISTRE | routine DOC-ROUT-C | idem | Case B | Actif |
| DOC-C07 | `CONTRATS/C-07_AUTONOMIE_UNITE_AGENT_GENERIQUE.md` | Contrats | Règle C-07 | CANONIQUE | elle-même | réouverture seulement | stable post-VALIDÉ | SUIVI, REGISTRE | routine DOC-ROUT-C | idem | règle ambiguë | Actif |
| DOC-C08 | `CONTRATS/C-08_TERRAFORMER_OPERATIONNEL.md` | Contrats | Règle C-08 | CANONIQUE | elle-même | réouverture seulement | stable post-VALIDÉ | SUIVI, REGISTRE | routine DOC-ROUT-C | idem | règle ambiguë | Actif |
| DOC-C11 | `CONTRATS/C-11_RESERVATIONS.md` | Contrats | Règle C-11 | CANONIQUE | elle-même | réouverture seulement | stable post-VALIDÉ | SUIVI, REGISTRE | routine DOC-ROUT-C | idem | règle ambiguë | Actif |
| DOC-C12 | `CONTRATS/C-12_TRANSPORT_LOGISTIQUE.md` | Contrats | Règle C-12 | CANONIQUE | elle-même | réouverture seulement | stable post-VALIDÉ | SUIVI, REGISTRE | routine DOC-ROUT-C | idem | règle ambiguë | Actif |
| DOC-C14 | `CONTRATS/C-14_INFRASTRUCTURES_LIFECYCLE.md` | Contrats | Règle C-14 | CANONIQUE | elle-même | réouverture seulement | stable post-VALIDÉ | SUIVI, REGISTRE | routine DOC-ROUT-C | idem | lifecycle ambigu | Actif |
| DOC-C15 | `CONTRATS/C-15_HYDROLOGIE.md` | Contrats | Règle C-15 | CANONIQUE | elle-même | réouverture seulement | stable post-VALIDÉ | SUIVI, REGISTRE | routine DOC-ROUT-C | idem | hydrologie ambiguë | Actif ; conception uniquement ; ≠ implémentation |
| DOC-C16 | `CONTRATS/C-16_SOL.md` | Contrats | Règle C-16 | CANONIQUE | elle-même | réouverture seulement | stable post-VALIDÉ | SUIVI, REGISTRE | routine DOC-ROUT-C | idem | sol ambigu | Actif ; conception uniquement ; P1–P10 ouverts |
| DOC-C17 | `CONTRATS/C-17_VEGETATION_ECOSYSTEMES.md` | Contrats | Règle C-17 | CANONIQUE | elle-même | réouverture seulement | stable post-VALIDÉ | SUIVI, REGISTRE | routine DOC-ROUT-C | idem | éco ambiguë | Actif ; **non suivi Git** (`??`) ; conception uniquement ; Q1–Q12 ouverts |
| DOC-C18 | `CONTRATS/C-18_TECHNOLOGIE_PROGRESSION.md` | Contrats | Règle C-18 | CANONIQUE | elle-même | réouverture seulement | stable post-VALIDÉ | SUIVI, REGISTRE, DG-07 | routine DOC-ROUT-C | ne pas implémenter sans autorisation distincte | fausse progression | Actif ; **VALIDÉ** conception (`b04ec3b`) ; Ages = legacy ; ≠ runtime DG-07 |
| MIR-SUIVI-JS | `GardenFervor_DesignGate_React/src/data/contractsSuivi.js` | Contrats | Miroir UI / compteurs Hub | **MIROIR MANUEL** | `00_SUIVI` + `00_REGISTRE` + C-xx | clôture contrat | chaque clôture | syncPages, GEN-CONTRACTS, DOC-HUB, GEN-EG | éditer JS **puis** (si publication autorisée) sync | Hub affiche N/16 aligné sur le MD | pages contrats obsolètes | Actif ; A1 **RÉSOLUE** ; dernier VALIDÉ = C-18 ; C-19 = non commencé |
| GEN-CONTRACTS | `docs/contracts.html` | Hub | Page suivi contrats | GÉNÉRÉ | MIR-SUIVI-JS | sync Hub | via `syncPages` | MIR-SUIVI-JS | `node docs/syncPages.mjs` | bandeau + cartes | lecture publique fausse | Généré |

### 2.3 Conception (Design Gate) — deux interfaces distinctes

**Chaîne Pages (officielle pour GitHub Pages) :**  
`designGate.js` → `syncStandaloneFromJs.mjs` → `GardenFervor_DESIGN_GATE_v0.1.html` + `designGate.data.json` → copie `docs/design-gate.html`.

**Interface Vite locale :** `index.html` + `src/main.jsx` + `src/ContractsSuiviView.jsx` + `src/styles.css`. Consomme les mêmes JS de données. **Aucune synchronisation automatique** entre l’app Vite et les HTML Pages n’est présente dans le dépôt.

| ID | Document / artefact | Catégorie | Rôle | Nature | Source de vérité | Déclencheurs | Fréquence | Dépendances | Procédure | Validation | Risque si oubli | État |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| DOC-DG-JS | `GardenFervor_DesignGate_React/src/data/designGate.js` | Conception | SoT décisions DG | CANONIQUE | elle-même | décision DG confirmée | chaque décision | REGLES | éditer JS | sync standalone | conception ≠ UI | Actif |
| SCR-DG | `GardenFervor_DesignGate_React/scripts/syncStandaloneFromJs.mjs` | Script | Génère HTML+JSON DG | SCRIPT | DOC-DG-JS | modif DG | après source | DOC-DG-JS | via `syncPages` ou `node GardenFervor_DesignGate_React/scripts/syncStandaloneFromJs.mjs` | exit 0 | build DG cassé | Actif |
| GEN-DG-HTML | `GardenFervor_DesignGate_React/GardenFervor_DESIGN_GATE_v0.1.html` | Conception | Vue standalone | GÉNÉRÉ | DOC-DG-JS | sync DG | après source | SCR-DG | syncStandalone | ouvrir HTML | HTML stale | Généré |
| GEN-DG-JSON | `GardenFervor_DesignGate_React/designGate.data.json` | Conception | JSON DG | GÉNÉRÉ | DOC-DG-JS | sync DG | après source | SCR-DG | syncStandalone | JSON cohérent | JSON stale | Généré |
| GEN-DG-PAGES | `docs/design-gate.html` | Hub | Copie Pages (anciennement GEN-DG) | GÉNÉRÉ | GEN-DG-HTML | syncPages | après source | copie | `node docs/syncPages.mjs` | sections VALIDÉes | Hub DG obsolète | Généré |

Hors opérationnel Pages (outil local) :

| ID | Document / artefact | Nature | Note |
| --- | --- | --- | --- |
| DEV-DG-IDX | `GardenFervor_DesignGate_React/index.html` | OUTIL | Shell Vite local |
| DEV-DG-MAIN | `GardenFervor_DesignGate_React/src/main.jsx` | OUTIL | Entrée React locale |
| DEV-DG-VIEW | `GardenFervor_DesignGate_React/src/ContractsSuiviView.jsx` | OUTIL | Vue contrats locale ≠ `docs/contracts.html` |
| DEV-DG-CSS | `GardenFervor_DesignGate_React/src/styles.css` | OUTIL | Styles locaux ; n’affecte pas Pages |
| DEV-DG-README | `GardenFervor_DesignGate_React/README.md` | RÉFÉRENCE | Mode d’emploi ; à tenir si les scripts changent |
| DEV-DG-PKG | `GardenFervor_DesignGate_React/package.json` | OUTIL | Deps Vite |
| DEV-DG-LOCK | `GardenFervor_DesignGate_React/package-lock.json` | OUTIL | Lockfile ; `node_modules/` non inventorié |

### 2.4 Roadmap globale

Chaîne distincte de la Roadmap S3 (§2.5).

| ID | Document / artefact | Catégorie | Rôle | Nature | Source de vérité | Déclencheurs | Fréquence | Dépendances | Procédure | Validation | Risque si oubli | État |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| DOC-RM-MD | `ROADMAP/GardenFervor_ROADMAP.md` | Roadmap | SoT roadmap globale | CANONIQUE | elle-même | clôture contrat / changement priorité | événementielle | SUIVI, ETAT | éditer MD | build+validate | prochain travail faux | Actif |
| DOC-RM-CL | `ROADMAP/CHANGELOG.md` | Roadmap | Journal versions roadmap | CANONIQUE | elle-même | version roadmap | avec MD | DOC-RM-MD | éditer MD | — | historique roadmap flou | Actif |
| GEN-RM-HTML | `ROADMAP/GardenFervor_ROADMAP.html` | Roadmap | Vue HTML | GÉNÉRÉ | DOC-RM-MD | build | après MD | SCR-RM-BUILD | `node ROADMAP/scripts/buildRoadmap.mjs` | `validateRoadmap.mjs` | HTML ≠ MD | Généré |
| GEN-RM-JSON | `ROADMAP/data/roadmap.data.json` | Roadmap | Données machine | GÉNÉRÉ | DOC-RM-MD | build | après MD | SCR-RM-BUILD | idem | hash MD | désync machine | Généré |
| GEN-RM-PAGES | `docs/roadmap-globale.html` | Hub | Copie Pages | GÉNÉRÉ | GEN-RM-HTML | sync | via syncPages | copie | `node docs/syncPages.mjs` | lien Hub | Pages stale | Généré ; listé dans GITHUB_PAGES (A2 **RÉSOLUE**) |
| SCR-RM-BUILD | `ROADMAP/scripts/buildRoadmap.mjs` | Script | Génère HTML/JSON | SCRIPT | — | évolution schéma RM | événementielle | DOC-RM-MD | node script | validate | build cassé | Actif |
| SCR-RM-VAL | `ROADMAP/scripts/validateRoadmap.mjs` | Script | Valide cohérence MD↔JSON | SCRIPT | — | après build | après build | GEN-RM-* | `node ROADMAP/scripts/validateRoadmap.mjs` | exit 0 | faux OK | Actif |
| DOC-RM-README | `ROADMAP/README.md` | Roadmap | Mode d’emploi | RÉFÉRENCE | scripts | changement script | événementielle | SCR-RM-* | éditer MD | — | doc fausse | Actif si scripts changent |
| DOC-RM-REACT | `ROADMAP/react/README.md` | Roadmap | Précise l’absence de stack React dédiée | RÉFÉRENCE | SCR-RM-BUILD | rare | rare | — | éditer MD | — | confusion de stack | Hors opérationnel |

### 2.5 Roadmap production S3

Chaîne distincte de la Roadmap globale. Ne pas synchroniser l’une depuis l’autre.

| ID | Document / artefact | Catégorie | Rôle | Nature | Source de vérité | Déclencheurs | Fréquence | Dépendances | Procédure | Validation | Risque si oubli | État |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| DOC-S3-PLAN | `Plan de production/PLAN_PRODUCTION_COHORTE_S3.md` | Roadmap S3 | Plan opérationnel T1–T9 | CANONIQUE / RÉFÉRENCE | elle-même | clôture tranche | stable post-T9 | — | éditer MD | — | plan vs preuve | Référence ; pas de sync Hub automatique |
| DOC-S3-DATA | `Plan de production/Roadmap/src/roadmap.data.js` | Roadmap S3 | SoT tranches T1–T9 | CANONIQUE | elle-même | statut tranche | événementielle (stable post-T9) | Plan S3 | éditer JS | syncRoadmap | Hub S3 faux | Actif |
| SCR-S3 | `Plan de production/Roadmap/scripts/syncRoadmap.mjs` | Script | Injecte JSON dans HTML S3 + copie Pages | SCRIPT | DOC-S3-DATA | modif S3 | après source | DOC-S3-DATA | via `syncPages` | exit 0 | sync S3 cassée | Actif |
| GEN-S3-WORK | `Plan de production/Roadmap/index.html` | Roadmap S3 | Coquille HTML + payload injecté | GÉNÉRÉ (injection) | DOC-S3-DATA | syncRoadmap | après source | SCR-S3 | syncRoadmap | ouvrir local | vue locale stale | Généré |
| GEN-S3-JSON | `Plan de production/Roadmap/roadmap.data.json` | Roadmap S3 | JSON S3 | GÉNÉRÉ | DOC-S3-DATA | syncRoadmap | après source | SCR-S3 | syncRoadmap | — | JSON stale | Généré |
| GEN-S3 | `docs/roadmap.html` | Hub | Vue S3 Pages | GÉNÉRÉ | GEN-S3-WORK | sync | via syncPages | copie | `node docs/syncPages.mjs` | blurb Hub `data-sync=s3-card` | Pages S3 stale | Généré |
| DOC-S3-README | `Plan de production/Roadmap/README.md` | Roadmap S3 | Mode d’emploi | RÉFÉRENCE | scripts | changement script | événementielle | SCR-S3 | éditer MD | — | doc fausse | Actif si scripts changent |

### 2.6 Project Graph

`PROJECT_GRAPH/CURRENT_STATE.md` est **GÉNÉRÉ**. Ce n’est pas l’état projet (`ETAT_PROJET.md`).

| ID | Document / artefact | Catégorie | Rôle | Nature | Source de vérité | Déclencheurs | Fréquence | Dépendances | Procédure | Validation | Risque si oubli | État |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| DOC-PG-CUR | `PROJECT_GRAPH/scripts/curatedGraph.mjs` | Graphe | Nœuds/relations curatés | CANONIQUE (projection) | registre+suivi+repo | clôture contrat / nouveau système | événementielle | SUIVI | éditer curated | build+validate | graphe faux | Actif |
| SCR-PG-BUILD | `PROJECT_GRAPH/scripts/buildProjectGraph.mjs` | Script | Génère graphe | SCRIPT | DOC-PG-CUR | après curated | après source | DOC-PG-CUR | `node PROJECT_GRAPH/scripts/buildProjectGraph.mjs` | validate | build cassé | Actif |
| SCR-PG-VAL | `PROJECT_GRAPH/scripts/validateProjectGraph.mjs` | Script | Valide graphe | SCRIPT | JSON généré | après build | après build | GEN-PG-* | `node PROJECT_GRAPH/scripts/validateProjectGraph.mjs` | exit 0 | faux OK | Actif |
| GEN-PG-HTML | `PROJECT_GRAPH/GardenFervor_ProjectGraph.html` | Graphe | Vue HTML | GÉNÉRÉ | DOC-PG-CUR | build | après source | SCR-PG-BUILD | build | validate | projection stale | Généré |
| GEN-PG-JSON | `PROJECT_GRAPH/data/projectGraph.data.json` | Graphe | JSON graphe | GÉNÉRÉ | DOC-PG-CUR | build | après source | SCR-PG-BUILD | build | validate | JSON stale | Généré |
| GEN-PG-MMD1 | `PROJECT_GRAPH/graph/GardenFervor_ProjectGraph.mmd` | Graphe | Mermaid master | GÉNÉRÉ | DOC-PG-CUR | build | après source | SCR-PG-BUILD | build | — | mmd stale | Généré |
| GEN-PG-MMD2 | `PROJECT_GRAPH/graph/GardenFervor_SystemsGraph.mmd` | Graphe | Mermaid systèmes | GÉNÉRÉ | DOC-PG-CUR | build | après source | SCR-PG-BUILD | build | — | mmd stale | Généré |
| GEN-PG-MMD3 | `PROJECT_GRAPH/graph/GardenFervor_RulesGraph.mmd` | Graphe | Mermaid règles | GÉNÉRÉ | DOC-PG-CUR | build | après source | SCR-PG-BUILD | build | — | mmd stale | Généré |
| GEN-PG-MMD4 | `PROJECT_GRAPH/graph/GardenFervor_DataFlowGraph.mmd` | Graphe | Mermaid data | GÉNÉRÉ | DOC-PG-CUR | build | après source | SCR-PG-BUILD | build | — | mmd stale | Généré |
| GEN-PG-MMD5 | `PROJECT_GRAPH/graph/GardenFervor_ExecutionGraph.mmd` | Graphe | Mermaid exécution | GÉNÉRÉ | DOC-PG-CUR | build | après source | SCR-PG-BUILD | build | — | mmd stale | Généré |
| GEN-PG-MMD6 | `PROJECT_GRAPH/graph/GardenFervor_ValidationGraph.mmd` | Graphe | Mermaid validation | GÉNÉRÉ | DOC-PG-CUR | build | après source | SCR-PG-BUILD | build | — | mmd stale | Généré |
| GEN-PG-MMD7 | `PROJECT_GRAPH/graph/GardenFervor_ExternalGraph.mmd` | Graphe | Mermaid externe | GÉNÉRÉ | DOC-PG-CUR | build | après source | SCR-PG-BUILD | build | — | mmd stale | Généré |
| GEN-PG-STATE | `PROJECT_GRAPH/CURRENT_STATE.md` | Graphe | Inventaire de la **dernière génération** | GÉNÉRÉ | build | build | après source | SCR-PG-BUILD | build | anomalies listées dans le fichier | le prendre pour ETAT_PROJET | Généré |
| GEN-PG-PAGES | `docs/project-graph.html` | Hub | Copie Pages | GÉNÉRÉ | GEN-PG-HTML | sync | via syncPages | copie | `node docs/syncPages.mjs` | lien Hub | Pages stale | Généré ; listé dans GITHUB_PAGES (A2 **RÉSOLUE**) |
| DOC-PG-README | `PROJECT_GRAPH/README.md` | Graphe | Mode d’emploi | RÉFÉRENCE | scripts | changement script | événementielle | SCR-PG-* | éditer MD | — | doc fausse | Actif si scripts changent |
| DOC-PG-CL | `PROJECT_GRAPH/CHANGELOG.md` | Graphe | Journal graphe | RÉFÉRENCE | elle-même | changement graphe notable | **À confirmer** (non formalisée) | — | édition MD manuelle | — | changelog oublié | Actif ; fréquence non définie |

### 2.7 Hub, état global, historique

**Pages Hub réellement liées depuis `docs/index.html` :**  
`etat-global.html` · `roadmap-globale.html` · `historique.html` · `design-gate.html` · `contracts.html` · `project-graph.html` · `presentation-client.html` · `roadmap.html`.

**Historique :** source canonique `HISTORIQUE_MODIFICATIONS.md`. Miroir `docs/historique.html` = **§4 uniquement**, via `docs/historique/buildHistorique.mjs`. Les catégories affichées (contrats, conception, technique, roadmap, documentation, hub) sont **inférées par le script**, ce ne sont pas un champ structuré de la source. Contrôle d’obsolescence : champ `sourceHash` (SHA-256 du Markdown) dans le HTML généré. Régénérer après toute modification de §4 (directement ou via `syncPages` si publication autorisée). Les §1–3 du Markdown n’ont pas de miroir Hub.

`ETAT_PROJET.md` et `etatGlobal.data.js` sont des récits **distincts**. Ne pas les fusionner. `gitHeadAtAudit` = référence historique de l’audit éditorial, pas le HEAD courant (A3 **RÉSOLUE**).

| ID | Document / artefact | Catégorie | Rôle | Nature | Source de vérité | Déclencheurs | Fréquence | Dépendances | Procédure | Validation | Risque si oubli | État |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| DOC-HUB | `docs/index.html` | Hub | Portail navigation + zones `SYNC:STATUS` / `data-sync` | CANONIQUE (structure) + fragments générés | structure manuelle ; statut via sync | nouvelle page / redesign | événementielle | syncPages | éditer structure ; sync pour bandeau | liens relatifs existent | page orpheline | Actif |
| DOC-GPAGES | `docs/GITHUB_PAGES.md` | Hub | Mode d’emploi Pages | CANONIQUE | elle-même | nouvelle page Hub | événementielle | syncPages | éditer MD | liste pages = réel | doc Pages fausse | Actif ; A2 **RÉSOLUE** (table alignée : S3, globale, graphe) |
| DOC-EG-DATA | `docs/etat-global/etatGlobal.data.js` | Hub | Éditorial état global | CANONIQUE (éditorial) | elle-même + compteurs via MIR-SUIVI-JS | clôture / audit global | événementielle | contractsSuivi | éditer JS | buildEtatGlobal | récit faux / ≠ ETAT | Actif ; `gitHeadAtAudit` figé = clôture C-14 `e4e6bd6e203f0a06a64677539f7405f6f60f8f24` (A3 **RÉSOLUE**) |
| SCR-EG | `docs/etat-global/buildEtatGlobal.mjs` | Script | Build état global | SCRIPT | DOC-EG-DATA + MIR-SUIVI-JS | après sources | via syncPages | DOC-EG-DATA | `node docs/etat-global/buildEtatGlobal.mjs` | page générée | page stale | Actif |
| GEN-EG | `docs/etat-global.html` | Hub | Vue état global | GÉNÉRÉ | DOC-EG-DATA + MIR-SUIVI-JS | sync / build | via syncPages | SCR-EG | buildEtatGlobal | compteurs live | Hub état faux | Généré |
| DOC-EG-README | `docs/etat-global/README.md` | Hub | Mode d’emploi | RÉFÉRENCE | scripts | changement script | événementielle | SCR-EG | éditer MD | — | doc fausse | Actif si scripts changent |
| GEN-HIST | `docs/historique.html` | Hub | Chronologie historique | GÉNÉRÉ | DOC-HIST §4 | sync / build | via syncPages | SCR-HIST | `node docs/historique/buildHistorique.mjs` | `entryCount` + `sourceHash` | Hub historique stale | Généré (**déjà créé** ; ne pas recréer) |
| SCR-SYNC | `docs/syncPages.mjs` | Script | Sync complète Pages | SCRIPT | — | toute pub doc **autorisée** | après sources | sous-scripts | `node docs/syncPages.mjs` | JSON `ok: true` + liens | Pages désynchronisées | Actif |
| SCR-HIST | `docs/historique/buildHistorique.mjs` | Script | Parse HISTORIQUE §4 → HTML | SCRIPT | DOC-HIST | évolution format §4 / nouvelle entrée | après HIST | DOC-HIST | node script | exit 0 + count | chronologie cassée | Actif |
| DOC-HIST-README | `docs/historique/README.md` | Hub | Mode d’emploi historique Hub | RÉFÉRENCE | SCR-HIST | changement script | événementielle | SCR-HIST | éditer MD | — | doc fausse | Actif si scripts changent |
| GEN-PRES | `docs/presentation-client.html` | Hub | Copie Pages pitch | GÉNÉRÉ | CAN-PRES | sync | via syncPages | `fs.copyFileSync` | `node docs/syncPages.mjs` | ouvrir page | pitch stale | Généré |

### 2.8 Présentation client — HTML et 38 images

**HTML source :**

| ID | Document / artefact | Catégorie | Rôle | Nature | Source de vérité | Déclencheurs | Fréquence | Dépendances | Procédure | Validation | Risque si oubli | État |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| CAN-PRES | `Investor Demo/PrésentationClientHtml/PrésentationClient.html` | Présentation | Pitch client | CANONIQUE | elle-même | évolution pitch | événementielle | IMG-SRC-* | éditer HTML ; sync si publication | page + galerie | Pages pitch stale | Actif |

**Procédure de copie images (script réel `docs/syncPages.mjs`) :**  
`fs.cpSync('Investor Demo/PrésentationClientHtml/images', 'docs/images', { recursive: true })`.  
Déclencheur : ajout, remplacement ou suppression d’un WebP source, ou publication Hub autorisée.  
Contrôle : le basename existe des deux côtés. Risque : image 404 sur la page publiée.

#### 2.8.1 Sources (11 WebP publiés + 10 originaux) — CANONIQUE asset

Dossier : `Investor Demo/PrésentationClientHtml/images/`  
Galerie `lot1/` retirée le 2026-10-10. HTML statique, plus de Base64.  
Originaux `01-…png` à `10-…png` : **ne pas modifier** ; ce sont des WebP avec extension `.png`.  
Les WebP servis par la page sont des copies 1600×900. Ne pas recopier les originaux vers `docs/`.

| ID | Chemin exact | Nature | Copie | Rôle |
| --- | --- | --- | --- | --- |
| IMG-SRC-HERO | `…/images/hero-territoire.webp` | CANONIQUE | IMG-CPY-HERO | Hero — depuis 01 |
| IMG-SRC-S3 | `…/images/gameplay-s3-overview.webp` | CANONIQUE | IMG-CPY-S3 | Prototype S3 — placeholders 192×192 |
| IMG-SRC-TS | `…/images/vision-territoire-strategique.webp` | CANONIQUE | IMG-CPY-TS | Concept — depuis 02 |
| IMG-SRC-U | `…/images/vision-unites-chantier.webp` | CANONIQUE | IMG-CPY-U | Unités — depuis 03 |
| IMG-SRC-L | `…/images/vision-logistique-bois.webp` | CANONIQUE | IMG-CPY-L | Logistique — depuis 04 |
| IMG-SRC-ST | `…/images/vision-stocks-localises.webp` | CANONIQUE | IMG-CPY-ST | Stocks localisés — depuis 05 |
| IMG-SRC-H | `…/images/vision-hydrologie.webp` | CANONIQUE | IMG-CPY-H | Hydrologie — **contenu de 09** |
| IMG-SRC-E | `…/images/vision-ecosysteme-zone-humide.webp` | CANONIQUE | IMG-CPY-E | Zone humide — **contenu de 08** |
| IMG-SRC-SO | `…/images/vision-sol.webp` | CANONIQUE | IMG-CPY-SO | Sol / nivellement — **contenu de 06** |
| IMG-SRC-C | `…/images/vision-construction-riviere.webp` | CANONIQUE | IMG-CPY-C | Pont / rivière — **contenu de 07** |
| IMG-SRC-M | `…/images/vision-mosaique-ecologique.webp` | CANONIQUE | IMG-CPY-M | Ambition — depuis 10 |

#### 2.8.2 Copies Hub (11) — GÉNÉRÉ

Dossier : `docs/images/` (plus de `lot1/`). Reconstruire depuis la source, pas à la main.

#### 2.8.3 Autres documents Investor Demo (hors Hub)

| ID | Document / artefact | Nature | Note |
| --- | --- | --- | --- |
| DOC-INV-R | `Investor Demo/README.md` | RÉFÉRENCE | Intro ; hors Hub |
| DOC-INV-A | `Investor Demo/Documentation/ARCHITECTURE.md` | RÉFÉRENCE | Archi démo ; hors Hub |
| DOC-INV-S | `Investor Demo/Documentation/SCENARIO_T1_T9.md` | RÉFÉRENCE | Scénario T1–T9 ; hors Hub |
| DOC-INV-SC | `Investor Demo/Scenes/README.md` | RÉFÉRENCE | Scènes ; hors Hub |
| DOC-INV-PH | `Investor Demo/Placeholders/README.md` | RÉFÉRENCE | Placeholders ; hors Hub |
| DOC-INV-LY | `Investor Demo/Placeholders/LAYOUT.md` | RÉFÉRENCE | Layout ; hors Hub |
| DOC-INV-PR | `Investor Demo/Presentation/README.md` | **À CLARIFIER** | Rôle vs `PrésentationClientHtml/` **non établi**. Ne pas fusionner ni supprimer. |

### 2.9 Preuves ODC (`Saved/`)

Les fichiers `Saved/ODC_F*.txt` sont ceux **cités** par `ETAT_PROJET.md` et `HISTORIQUE_MODIFICATIONS.md`.  
Quatre fichiers homonymes génériques coexistent. **L’autorité entre `ODC_F*` et `*RuntimeGate.txt` n’est pas tranchée.** Ne pas fusionner, ne pas supprimer, ne pas choisir un SoT dans cette révision.

| ID | Document / artefact | Catégorie | Rôle | Nature | Source de vérité | Déclencheurs | Fréquence | Relation observée | Procédure | Validation | Risque si oubli | État |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| PRF-F1 | `Saved/ODC_F1_RuntimeTerrainGate.txt` | Preuves | Gate F1 | PREUVE | runtime / gate | redo F1 | par gate | cité ETAT/HIST (INVALIDÉ) | commande gate | PASS/FAIL dans fichier | preuve introuvable | Actif |
| PRF-F2 | `Saved/ODC_F2_VisualTerrainGate.txt` | Preuves | Gate F2 | PREUVE | runtime / gate | re-run | par gate | cité ETAT/HIST (PASS) | commande gate | idem | idem | Actif |
| PRF-F3 | `Saved/ODC_F3_SimulationSubstrateGate.txt` | Preuves | Gate F3 | PREUVE | runtime / gate | re-run | par gate | cité ETAT/HIST (PASS) | commande gate | idem | idem | Actif |
| PRF-F4 | `Saved/ODC_F4_TaskGraphGate.txt` | Preuves | Gate F4 | PREUVE | runtime / gate | re-run | par gate | cité ETAT/HIST (PASS) | commande gate | idem | idem | Actif |
| PRF-F5 | `Saved/ODC_F5_AutonomyGate.txt` | Preuves | Gate F5 | PREUVE | runtime + PIE | re-run | par gate | cité ETAT/HIST ; doublon nom PRF-DUP-AUT | commande gate | idem | idem | Actif |
| PRF-F6 | `Saved/ODC_F6_EconomyGate.txt` | Preuves | Gate F6 | PREUVE | runtime / gate | re-run | par gate | cité ETAT/HIST ; doublon nom PRF-DUP-ECO | commande gate | idem | idem | Actif |
| PRF-F7 | `Saved/ODC_F7_LogisticsGate.txt` | Preuves | Gate F7 | PREUVE | runtime + PIE | re-run | par gate | cité ETAT/HIST ; doublon nom PRF-DUP-LOG | commande gate | idem | idem | Actif |
| PRF-F8 | `Saved/ODC_F8_TerraformOperationGate.txt` | Preuves | Gate F8 | PREUVE | runtime / gate | re-run | par gate | cité ETAT/HIST ; doublon nom PRF-DUP-TER | commande gate | idem | idem | Actif |
| PRF-AF5 | `Saved/ODC_AUDIT_PRE_F5.txt` | Preuves | Audit pré-F5 | PREUVE / ARCHIVE | audit | historique | archive | — | n/a | présence | contexte perdu | Hors opérationnel courant |
| PRF-DUP-AUT | `Saved/AutonomyRuntimeGate.txt` | Preuves | Doublon de nom vs F5 | PREUVE / **À CLARIFIER** | **non établi** | — | — | coexiste avec PRF-F5 ; relation fichier **non arbitrée** | ne pas supprimer | — | citer le mauvais fichier | Ambiguïté |
| PRF-DUP-ECO | `Saved/EconomyRuntimeGate.txt` | Preuves | Doublon de nom vs F6 | PREUVE / **À CLARIFIER** | **non établi** | — | — | coexiste avec PRF-F6 ; **non arbitrée** | ne pas supprimer | — | idem | Ambiguïté |
| PRF-DUP-LOG | `Saved/LogisticsRuntimeGate.txt` | Preuves | Doublon de nom vs F7 | PREUVE / **À CLARIFIER** | **non établi** | — | — | coexiste avec PRF-F7 ; **non arbitrée** | ne pas supprimer | — | idem | Ambiguïté |
| PRF-DUP-TER | `Saved/TerraformOperationGate.txt` | Preuves | Doublon de nom vs F8 | PREUVE / **À CLARIFIER** | **non établi** | — | — | coexiste avec PRF-F8 ; **non arbitrée** | ne pas supprimer | — | idem | Ambiguïté |

### 2.10 Archives — `Audit de readiness pré-implémentation/`

Dossier **non suivi Git** (`??`). Référence historique de readiness. **Pas** des contrats VALIDÉS. Pas dans `syncPages`. Risque : les relire comme vérité opérationnelle courante.

| ID | Chemin exact | Nature | État Git |
| --- | --- | --- | --- |
| ARC-01 | `Audit de readiness pré-implémentation/AUDIT_READINESS_PRE_IMPLEMENTATION.md` | ARCHIVE | `??` |
| ARC-02 | `Audit de readiness pré-implémentation/CLARIFICATION_01_ECONOMIE_PROGRESSION.md` | ARCHIVE | `??` |
| ARC-03 | `Audit de readiness pré-implémentation/CLARIFICATION_02_MODELE_RUNTIME_BOIS.md` | ARCHIVE | `??` |
| ARC-04 | `Audit de readiness pré-implémentation/CLARIFICATION_03_OWNERSHIP_STOCKS.md` | ARCHIVE | `??` |
| ARC-05 | `Audit de readiness pré-implémentation/CLARIFICATION_04_KIT_COHORTE.md` | ARCHIVE | `??` |
| ARC-06 | `Audit de readiness pré-implémentation/CLARIFICATION_05_UNITES_SERVICE.md` | ARCHIVE | `??` |
| ARC-07 | `Audit de readiness pré-implémentation/FORMALISATION_01_FONDATATION_ECONOMIE_BOIS_STOCKS.md` | ARCHIVE | `??` |
| ARC-08 | `Audit de readiness pré-implémentation/FORMALISATION_02_KIT_COHORTE_FORESTIERE.md` | ARCHIVE | `??` |
| ARC-09 | `Audit de readiness pré-implémentation/FORMALISATION_03_ARBITRAGES_C7_C4_C5_C6.md` | ARCHIVE | `??` |
| ARC-10 | `Audit de readiness pré-implémentation/ARBITRAGES_C7_C4_C5_C6.md` | ARCHIVE | `??` |
| ARC-11 | `Audit de readiness pré-implémentation/PREPARATION_CONTRATS_C7_C6.md` | ARCHIVE | `??` |
| ARC-12 | `Audit de readiness pré-implémentation/PREPARATION_IMPLEMENTATION_COHORTE.md` | ARCHIVE | `??` |
| ARC-13 | `Audit de readiness pré-implémentation/CONTROLE_FINAL_PRE_IMPLEMENTATION_COHORTE.md` | ARCHIVE | `??` |

Ne pas archiver davantage, déplacer, supprimer, indexer ou modifier ces fichiers au titre de ce registre.

### 2.11 Hors inventaire opérationnel (exclusions justifiées)

| ID | Élément | Nature | Note |
| --- | --- | --- | --- |
| EXCL-SRC | `Source/` | RUNTIME | Code C++ ; hors maintenance documentaire Hub |
| EXCL-CONTENT | `Content/`, `Config/`, `GardenFervor.uproject` | RUNTIME | Assets / projet UE non suivis ou partiellement suivis |
| EXCL-SITEPREP | SitePrep / ProjectSubsystem (working tree `M`) | CODE | Préservé hors docs ; ne pas mélanger aux commits doc |
| EXCL-NM | `GardenFervor_DesignGate_React/node_modules/` | OUTIL | Non inventorié fichier par fichier |
| EXCL-COOK | Cook, logs, dumps shaders, `Saved/` hors preuves ODC listées | TEMP | Hors patrimoine documentaire |
| EXCL-IDE | `.vsconfig`, `.cursor/mcp.json` | OUTIL | IDE ; hors état projet |

---

## 3. Matrice événements → actions (E1–E13)

**Une seule matrice.** Les identifiants E1–E10 de la création initiale sont **réalignés** ici sur l’audit 2026-10-09 (E1–E13). Ne pas tenir une seconde liste concurrente.

Ordre fixe : **(1) sources canoniques → (2) miroirs manuels → (3) builds → (4) `docs/syncPages.mjs` si publication autorisée → (5) validations → (6) contrôle humain si requis.**

Ne pas inverser. Ne pas éditer une vue GÉNÉRÉ pour « corriger » une source.

### E1 — Décision Design Gate confirmée / modifiée

| Étape | Action |
| --- | --- |
| Sources | DOC-DG-JS `designGate.js` |
| Dépendants | ETAT (si impact état), HISTORIQUE §4, éventuellement Roadmap globale |
| Vues | GEN-DG-HTML, GEN-DG-JSON, GEN-DG-PAGES |
| Validations | syncStandalone (via syncPages si pub) ; relecture section touchée |
| Succès | statut DG cohérent JS ↔ HTML Pages |
| Humain | validation conception si statut VALIDÉ |
| Ne pas toucher | contrats VALIDÉS, compteurs N/16, interface Vite sauf besoin UI locale, code gameplay |

### E2 — Clôture d’un contrat

| Étape | Action |
| --- | --- |
| Sources | `CONTRATS/C-xx_*.md` · DOC-SUIVI-C · DOC-REG-C |
| Miroirs / dépendants | **MIR-SUIVI-JS (manuel, obligatoire à vérifier)** · ETAT · HISTORIQUE · DOC-RM-MD · DOC-PG-CUR · DOC-EG-DATA (éditorial) · ce registre si le périmètre doc change |
| Vues | build Roadmap globale · build Project Graph · syncPages (contracts, hub, etat-global, roadmap-globale, project-graph, historique) si publication autorisée |
| Validations | validateRoadmap · validateProjectGraph · compteur N/16 MD = JS = Hub |
| Succès | Hub + suivi + contrat alignés ; prochain ID correct |
| Humain | validation finale contrat (déjà acquise avant clôture) |
| Ne pas toucher | C-16 contenu, Design Gate hors impact, code gameplay, working tree SitePrep |

### E3 — Preuve ou validation d’un jalon technique (ODC gate)

| Étape | Action |
| --- | --- |
| Sources | preuve `Saved/ODC_F*.txt` · ETAT · HISTORIQUE |
| Dépendants | DOC-EG-DATA si l’éditorial change |
| Vues | etat-global / historique si publication autorisée |
| Validations | fichier preuve présent ; ETAT cite le chemin |
| Succès | phase ODC reflétée |
| Humain | si gate « PASS (humain) » |
| Ne pas toucher | statuts contrats, DG ; ne pas arbitrer PRF-DUP-* |

### E4 — Modification d’une règle ou d’une architecture process

| Étape | Action |
| --- | --- |
| Sources | DOC-REGLES et/ou DOC-ROUT-C et/ou contrat / DG selon le sujet |
| Dépendants | **ce registre** (§5) ; DOC-GPAGES si commande change ; graphe si système |
| Vues | PG si curated change ; Hub si howto |
| Validations | chemins §6 |
| Succès | agents peuvent suivre le process |
| Ne pas toucher | compteurs contrats si hors clôture |

### E5 — Évolution de la Roadmap globale

| Étape | Action |
| --- | --- |
| Sources | DOC-RM-MD · DOC-RM-CL |
| Dépendants | ETAT si le prochain travail change |
| Vues | GEN-RM-HTML, GEN-RM-JSON, GEN-RM-PAGES |
| Validations | `node ROADMAP/scripts/validateRoadmap.mjs` |
| Succès | hash MD = JSON ; Hub roadmap-globale à jour après sync autorisée |
| Ne pas toucher | DOC-S3-DATA (chaîne S3 séparée) |

### E6 — Évolution de la Roadmap S3

| Étape | Action |
| --- | --- |
| Sources | DOC-S3-DATA (et DOC-S3-PLAN si le plan change) |
| Vues | GEN-S3-WORK, GEN-S3-JSON, GEN-S3 |
| Validations | syncRoadmap exit 0 ; blurb Hub S3 |
| Succès | `docs/roadmap.html` reflète le JS |
| Ne pas toucher | Roadmap globale MD/HTML |

### E7 — Modification du graphe projet

| Étape | Action |
| --- | --- |
| Sources | DOC-PG-CUR |
| Dépendants | DOC-PG-CL (**À confirmer** si tenue à jour) |
| Vues | GEN-PG-HTML, GEN-PG-JSON, GEN-PG-MMD1–7, GEN-PG-STATE, GEN-PG-PAGES |
| Validations | `node PROJECT_GRAPH/scripts/validateProjectGraph.mjs` |
| Succès | projection cohérente |
| Ne pas toucher | contrats MD ; ETAT_PROJET (≠ CURRENT_STATE.md) |

### E8 — Création, déplacement, remplacement ou suppression d’un document

| Étape | Action |
| --- | --- |
| Sources | document concerné |
| Dépendants | **ce registre** · DOC-GPAGES · DOC-HUB si page Hub · SCR-SYNC si nouvelle page |
| Validations | contrôle chemins §6 |
| Succès | inventaire à jour ; pas de lien mort |
| Ne pas toucher | inventer un VALIDÉ |

### E9 — Ajout / modification d’une page Hub

| Étape | Action |
| --- | --- |
| Sources | structure DOC-HUB · script de la page · SCR-SYNC · ce registre |
| Dépendants | DOC-GPAGES |
| Validations | liens relatifs ; sync si publication autorisée |
| Succès | carte catalogue + nav → page |
| Ne pas toucher | contrats, DG hors sujet |

### E10 — Modification des données consommées par le Hub

| Étape | Action |
| --- | --- |
| Sources | SoT de la page (MIR-SUIVI-JS, DOC-EG-DATA, DOC-S3-DATA, DOC-DG-JS, DOC-HIST, CAN-PRES, …) |
| Dépendants | pages générées concernées ; **plusieurs représentations des compteurs / prochain contrat** (index, contracts, etat-global) à vérifier ensemble |
| Vues | page générée |
| Validations | bandeau / blurbs / live counters alignés |
| Succès | pas de chiffre Hub contradictoire |
| Ne pas toucher | assimiler ETAT_PROJET et etatGlobal.data sans vérification |

### E11 — Changement d’un script ou d’un schéma de génération

| Étape | Action |
| --- | --- |
| Sources | le `.mjs` + README du domaine |
| Dépendants | **ce registre** · DOC-GPAGES si la commande Hub change |
| Vues | toutes les sorties du script |
| Validations | validateur du sous-système |
| Succès | chaîne Source→Vue OK |
| Ne pas toucher | sources métier |

### E12 — Régénération / publication de vues

| Étape | Action |
| --- | --- |
| Sources | déjà à jour |
| Commande | `node docs/syncPages.mjs` **si autorisée** |
| Validations | JSON `ok: true` ; pages listées dont `project-graph` et `roadmapGlobale` dans la sortie script |
| Succès | bandeau SYNC à jour |
| Git | commit dédié + push **sur autorisation distincte** |
| Ne pas toucher | working tree SitePrep (`git add .` interdit) |

### E13 — Détection d’un miroir obsolète ou échec d’un validateur

| Étape | Action |
| --- | --- |
| Sources | identifier SoT vs généré (`sourceHash` historique, validate Roadmap/Graphe) |
| Action | rebuild depuis SoT ; **ne pas** éditer le HTML généré à la main |
| Succès | validate exit 0 / hash = MD |
| Ne pas toucher | « corriger » GEN-* |

---

## 4. Chaînes de commandes (vérifiées dans le dépôt)

Depuis la **racine** du dépôt. **Ne pas les exécuter** au seul titre de la tenue de ce registre.

```bash
# Roadmap globale
node ROADMAP/scripts/buildRoadmap.mjs
node ROADMAP/scripts/validateRoadmap.mjs

# Roadmap S3 (aussi invoquée par syncPages)
node "Plan de production/Roadmap/scripts/syncRoadmap.mjs"

# Design Gate standalone (aussi invoquée par syncPages)
node GardenFervor_DesignGate_React/scripts/syncStandaloneFromJs.mjs

# Project Graph
node PROJECT_GRAPH/scripts/buildProjectGraph.mjs
node PROJECT_GRAPH/scripts/validateProjectGraph.mjs

# Historique Hub (miroir HISTORIQUE §4)
node docs/historique/buildHistorique.mjs

# État global seul
node docs/etat-global/buildEtatGlobal.mjs

# Sync Hub complète (écrit des fichiers — autorisation requise)
node docs/syncPages.mjs
```

`syncPages.mjs` enchaîne : syncRoadmap → syncStandalone → contrats+hub → copie présentation+images → copie project-graph → copie roadmap-globale → buildEtatGlobal → buildHistorique.

---

## 5. Maintenance de ce registre (règle permanente)

Lorsqu’une tâche crée, déplace, supprime, remplace ou modifie substantiellement un document, une source de données documentaire, un script de génération, une page du Hub ou une dépendance documentaire, l’agent doit vérifier si le registre doit être actualisé **avant** de déclarer la tâche terminée. Si le patrimoine documentaire change, mettre à jour ce registre dans le périmètre autorisé de la tâche, puis contrôler que les chemins et relations déclarés correspondent au dépôt réel.

Les agents doivent également :

- consulter ce registre avant une opération documentaire significative ;
- distinguer source canonique, miroir manuel et sortie générée ;
- mettre à jour les dépendances associées lorsqu’un artefact change ;
- ne pas inventer de fréquence périodique ;
- marquer les décisions non tranchées comme telles (`À CLARIFIER`, proposition, anomalie) ;
- ne pas exécuter de synchronisation ou de publication sans autorisation adaptée.

Cette règle s’applique aux travaux **futurs**. Elle n’autorise pas, à elle seule, à modifier d’autres fichiers.

Mettre à jour `REGISTRE_MAINTENANCE_DOCUMENTAIRE.md` lorsque :

- un document de suivi est créé, déplacé, renommé ou retiré ;
- une page Hub ou un script de sync/build est ajouté ou modifié ;
- une source de vérité change de chemin ;
- une procédure de génération change ;
- une image source / copie, une preuve, une archive documentaire ou une dépendance est ajoutée au patrimoine.

Contrôle minimal (§6) après édition.  
Pointer depuis `REGLES_PROJET.md` (table fichiers d’état) — les agents doivent **consulter et maintenir** ce registre lors des opérations documentaires concernées.

---

## 6. Contrôle de couverture (checklist)

À exécuter après toute évolution documentaire structurante :

- [ ] Chaque page réellement liée par `docs/index.html` a une entrée ici
- [ ] Écarts GITHUB_PAGES vs Hub : A2 **RÉSOLUE** ; tout nouvel écart à lister en anomalies
- [ ] Chaque commande invoquée par `docs/syncPages.mjs` est référencée §4
- [ ] Chemins cités existent sur disque, ou leur absence est qualifiée (addenda C-03/06/09/10/13)
- [ ] Toute vue `GÉNÉRÉ` a une SoT identifiée
- [ ] Tout `MIROIR MANUEL` a une procédure de vérification
- [ ] Aucune SoT n’est éditée « via » son HTML généré
- [ ] `docs/historique.html` se régénère depuis `HISTORIQUE_MODIFICATIONS.md` §4 (`sourceHash`)
- [ ] 19 IMG-SRC + 19 IMG-CPY individuels, paires basename identiques
- [ ] 4 PRF-DUP-* documentés comme ambiguïté, sans arbitrage
- [ ] Travaux locaux non liés (ex. SitePrep dirty) ne sont pas mélangés aux commits doc

---

## 7. Rappel Git

Cette maintenance documentaire se versionne par **commits dédiés**, sans `git add .`, sans force push, avec préservation des working trees étrangers.  
Commit et push restent des étapes **explicitement autorisées**, distinctes de la rédaction.

Constat Git lors de la révision `cf3c1ff` : `main` = `origin/main` ; index vide ; 5 fichiers SitePrep `M` préservés ; `CONTRATS/ReglesRoutinesContrats.md` et `Audit de readiness pré-implémentation/` en `??`.

---

## 8. Anomalies et points de vigilance

A4–A12 restent **ouvertes** (documentées seulement).  
A1, A2 et A3 sont **RÉSOLUES** (preuves ci-dessous). Les entrées sont conservées pour l’historique.

| ID | Constat | Fichiers | Correctif futur suggéré (**proposition**) |
| --- | --- | --- | --- |
| A1 | **RÉSOLUE.** Origine : `activeContractId: 'C-14'` vs suivi « Contrat actuel : aucun / Dernier validé : C-14 » ; libellés UI « Contrat actif » / « ACTIF ». Audit : la **valeur** C-14 est le dernier VALIDÉ (JSDoc + Hub « dernier » + état-global) ; divergence de **vocabulaire** seulement. Correctif 2026-10-09 : libellés « Dernier contrat validé » / « DERNIER VALIDÉ » dans `docs/syncPages.mjs` et `GardenFervor_DesignGate_React/src/ContractsSuiviView.jsx` ; badge NON VALIDÉ retiré de la bannière React ; `docs/contracts.html` régénéré via `node docs/syncPages.mjs --contracts-only`. Contrôles V1–V4 PASS. Validation visuelle humaine : C-14 « Dernier contrat validé », statut VALIDÉ, 9/16. Valeurs métier inchangées (`activeContractId: 'C-14'`, `nextAuthorizedId: 'C-15'`). | MIR-SUIVI-JS, DOC-SUIVI-C, SCR-SYNC, GEN-CONTRACTS, DEV-DG-VIEW | Correctif appliqué (libellés + page générée). Validateur MD↔JS reste une **proposition** (A12), pas une condition de cette clôture. |
| A2 | **RÉSOLUE.** Origine : `docs/GITHUB_PAGES.md` §Fichiers publiés omettait `project-graph.html` et `roadmap-globale.html`, alors que le Hub et `syncPages` les publiaient. Correctif constaté dans `docs/GITHUB_PAGES.md` (working tree, compte rendu de correction 2026-10-09, non commité au moment de cette clôture) : `roadmap-globale.html` (Roadmap globale) et `project-graph.html` (Project Graph) ajoutés à la table publiée ; `roadmap.html` distinguée comme Roadmap de production S3 ; sources de vérité scindées S3 / globale / graphe. | DOC-GPAGES, DOC-HUB, GEN-PG-PAGES, GEN-RM-PAGES | Correctif déjà appliqué dans `docs/GITHUB_PAGES.md` (fichier **non modifié** dans cette révision du registre) |
| A3 | **RÉSOLUE.** Origine : `gitHeadAtAudit: '91723da'` (`docs(hub): redesign landing as cinematic production portal`) alors que `originNote` / README attribuaient une actualisation à la clôture C-14 ; HEAD contrôlé à l’ouverture = `cf3c1ff`, puis `0943e660f20a32e30b9a93e90d186355c8b17db6`. Audit : le champ est une **référence historique figée**, pas le HEAD live ; `ETAT_PROJET.md` (baseline courte) et l’éditorial Hub restent des récits distincts — ne pas les fusionner. Correctif 2026-10-09 : sémantique dans `etatGlobal.data.js` et `docs/etat-global/README.md` ; `gitHeadAtAudit` = `e4e6bd6e203f0a06a64677539f7405f6f60f8f24` ; `gitMessageAtAudit` = `docs(contracts): validate C-14 infrastructure lifecycle` (commit C-14 vérifié) ; `originNote` réconcilié ; libellé Hub « Référence Git de l’audit éditorial (historique, figée) » ; `docs/etat-global.html` régénéré **uniquement** (`node docs/etat-global/buildEtatGlobal.mjs`). HEAD courant **non** bumpé. Compteurs 9/16, C-14, C-15 non commencé, Case B SUSPENDU, F1 INVALIDÉ / F2–F8 PASS inchangés. Roadmap `git_head_at_audit` hors périmètre. | DOC-EG-DATA, DOC-EG-README, SCR-EG, GEN-EG | Correctif appliqué. Ne pas bumper automatiquement à chaque commit, génération ou sync. |
| A4 | Compteurs N/16 et prochain contrat représentés plusieurs fois (index, contracts, etat-global) | DOC-HUB, GEN-CONTRACTS, GEN-EG, MIR-SUIVI-JS | Vérifier les trois surfaces ensemble à chaque E2/E10 |
| A5 | Deux interfaces Design Gate (Vite locale ≠ HTML Pages) sans sync auto | DEV-DG-*, GEN-DG-* | Conserver la distinction ; Pages = chaîne standalone |
| A6 | Deux roadmaps (globale vs S3) | DOC-RM-*, DOC-S3-* | Conserver les deux chaînes ; ne pas copier l’une sur l’autre |
| A7 | Autorité ambiguë `Saved/ODC_F*.txt` vs `Saved/*RuntimeGate.txt` | PRF-F5…F8, PRF-DUP-* | Trancher quel nom citer ; **pas d’arbitrage ici** |
| A8 | `CONTRATS/ReglesRoutinesContrats.md` présent mais `??` non suivi | DOC-ROUT-C | Décider versionnement ; **ne pas indexer ici** |
| A9 | Dossier readiness non suivi, hors Hub | ARC-01…13 | Archiver explicitement ou gitignore ; ne pas confondre avec contrats VALIDÉS |
| A10 | `Investor Demo/Presentation/README.md` rôle incertain vs HTML canonique | DOC-INV-PR, CAN-PRES | Clarifier ; ne pas fusionner |
| A11 | `CURRENT_STATE.md` généré peut être lu comme état projet | GEN-PG-STATE vs DOC-ETAT | Rappeler : généré ≠ ETAT_PROJET |
| A12 | Pas de validateur automatique HIST `sourceHash` hors rebuild ; pas de validateur SUIVI MD↔JS | SCR-HIST, MIR-SUIVI-JS | **Proposition** : checks dédiés |

**Propositions** (non officielles) : revue périodique du registre (§1) ; correctif A4 (A1, A2 et A3 **RÉSOLUES**) ; validateur A12.  
C-15 est **VALIDÉ** (clôture 2026-10-10). C-16 n’est pas commencé. Aucune implémentation hydrologique.

---

## 9. Recensement des identifiants (constat de cette révision)

Les totaux ci-dessous comptent les **lignes d’inventaire nominatives** de §2. Ils remplacent, pour ce registre, le chiffre unique « 104 » du canvas (vue filtrée).

| Groupe | IDs |
| --- | --- |
| Pilotage | DOC-REGLES, DOC-ETAT, DOC-HIST, DOC-MAINT, DOC-ODC-DOCX, DOC-ODC-TXT |
| Contrats | DOC-REG-C, DOC-SUIVI-C, DOC-ROUT-C, DOC-C01, DOC-C02, DOC-C04, DOC-C05, DOC-C07, DOC-C08, DOC-C11, DOC-C12, DOC-C14, DOC-C15, MIR-SUIVI-JS, GEN-CONTRACTS |
| Design Gate Pages | DOC-DG-JS, SCR-DG, GEN-DG-HTML, GEN-DG-JSON, GEN-DG-PAGES |
| Design Gate outil | DEV-DG-IDX, DEV-DG-MAIN, DEV-DG-VIEW, DEV-DG-CSS, DEV-DG-README, DEV-DG-PKG, DEV-DG-LOCK |
| Roadmap globale | DOC-RM-MD, DOC-RM-CL, GEN-RM-HTML, GEN-RM-JSON, GEN-RM-PAGES, SCR-RM-BUILD, SCR-RM-VAL, DOC-RM-README, DOC-RM-REACT |
| Roadmap S3 | DOC-S3-PLAN, DOC-S3-DATA, SCR-S3, GEN-S3-WORK, GEN-S3-JSON, GEN-S3, DOC-S3-README |
| Graphe | DOC-PG-CUR, SCR-PG-BUILD, SCR-PG-VAL, GEN-PG-HTML, GEN-PG-JSON, GEN-PG-MMD1–7, GEN-PG-STATE, GEN-PG-PAGES, DOC-PG-README, DOC-PG-CL |
| Hub | DOC-HUB, DOC-GPAGES, DOC-EG-DATA, SCR-EG, GEN-EG, DOC-EG-README, GEN-HIST, SCR-SYNC, SCR-HIST, DOC-HIST-README, GEN-PRES |
| Présentation | CAN-PRES, IMG-SRC-01…19, IMG-CPY-01…19, DOC-INV-R, DOC-INV-A, DOC-INV-S, DOC-INV-SC, DOC-INV-PH, DOC-INV-LY, DOC-INV-PR |
| Preuves | PRF-F1…F8, PRF-AF5, PRF-DUP-AUT, PRF-DUP-ECO, PRF-DUP-LOG, PRF-DUP-TER |
| Archives | ARC-01…13 |
| Exclusions | EXCL-SRC, EXCL-CONTENT, EXCL-SITEPREP, EXCL-NM, EXCL-COOK, EXCL-IDE |

---

*Fin du registre de maintenance documentaire.*
