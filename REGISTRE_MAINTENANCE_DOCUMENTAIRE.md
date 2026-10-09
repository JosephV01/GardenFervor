# GardenFervor — Registre de maintenance documentaire

**Fichier :** `REGISTRE_MAINTENANCE_DOCUMENTAIRE.md` (racine)  
**Statut :** actif  
**Rôle :** inventaire opérationnel des documents et artefacts à maintenir, de leurs dépendances, déclencheurs et procédures réelles.  
**Public :** humains et agents Cursor.  
**Dernière révision inventaire :** 2026-10-09 (création initiale post clôture C-14 / HEAD `e4e6bd6`).

---

## 0. Comment utiliser ce registre

1. Avant une opération documentaire significative : lire ce fichier + `REGLES_PROJET.md` §1bis + `ETAT_PROJET.md`.
2. Identifier l’événement (matrice §3) → sources à modifier → vues à régénérer → validations.
3. **Sources canoniques d’abord**, génération ensuite, validation en dernier.
4. Après l’opération : mettre à jour ce registre **si** un document, chemin, script ou dépendance a changé (§5).
5. Ne jamais traiter une vue générée comme source de vérité.

Ce registre **n’est pas** une source de vérité de gameplay ni de conception.  
Il ne remplace ni le Design Gate, ni les contrats, ni `ETAT_PROJET.md`.

---

## 1. Principes

| Principe | Règle |
| --- | --- |
| Autorité | Le Markdown / JS / données de source prime sur le HTML publié |
| Fréquence | **Événementielle** (clôture, décision, sync, changement d’architecture) — pas de cadence inventée |
| VALIDÉ | Documentaire ≠ runtime ; ne jamais inventer un statut VALIDÉ |
| Génération | Utiliser uniquement les commandes listées ici (vérifiées dans le dépôt) |
| Hub | Après modification documentaire destinée à Pages : `node docs/syncPages.mjs` |
| Préservation Git | Ne jamais `git add .` / `git add -A` ; commits dédiés ; push sur autorisation |

**Proposition non officielle (à décider) :** revue périodique optionnelle de ce registre (ex. après chaque vague de contrats). Ce n’est **pas** une règle tant qu’elle n’est pas tranchée explicitement.

---

## 2. Inventaire vérifié

Légende **Nature** : `CANONIQUE` · `MIROIR` · `GÉNÉRÉ` · `RÉFÉRENCE` · `PREUVE` · `SCRIPT`

### 2.1 Pilotage projet

| ID | Document / artefact | Catégorie | Rôle | Nature | Source de vérité | Déclencheurs | Fréquence | Dépendances | Procédure | Validation | Risque si oubli | État |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| DOC-REGLES | `REGLES_PROJET.md` | Règles | Process opérationnel, §1bis, Hub, Design Gate | CANONIQUE | elle-même | nouvelle règle process ; nouvel outil documentaire | à chaque événement process | ETAT, HISTORIQUE, Hub | éditer MD | relecture humaine | agents hors process | Actif |
| DOC-ETAT | `ETAT_PROJET.md` | Suivi | Snapshot court courant | CANONIQUE | elle-même (baseline) | gate, clôture, fix validé, doc majeure | à chaque modification validée (§1bis) | HISTORIQUE, REGLES | éditer MD | cohérence avec dernière entrée HISTORIQUE | faux « état courant » | Actif |
| DOC-HIST | `HISTORIQUE_MODIFICATIONS.md` | Suivi | Mémoire longue §4 chronologique | CANONIQUE | elle-même | toute modification validée | à chaque livrable validé | ETAT, REGLES | ajouter entrée §4 | ordre récent→ancien ; IDs uniques | perte de mémoire agent | Actif |
| DOC-MAINT | `REGISTRE_MAINTENANCE_DOCUMENTAIRE.md` | Suivi | Inventaire maintenance + matrice | CANONIQUE | elle-même | création/déplacement/suppression doc ou script | à chaque changement de périmètre doc | REGLES, scripts Hub | éditer MD + contrôle chemins §6 | `node docs/historique/buildHistorique.mjs` + sync OK si Hub touché | docs orphelines / sync oubliée | Actif |
| DOC-ODC | `GardenFervor_ODC_v1.0` / extrait `Saved/…` | Référence | Direction produit / phases | RÉFÉRENCE | ODC | rare (révision produit) | événementielle | — | hors sync Hub automatique | non applicable Pages | dérive produit | Référence |

### 2.2 Contrats

| ID | Document / artefact | Catégorie | Rôle | Nature | Source de vérité | Déclencheurs | Fréquence | Dépendances | Procédure | Validation | Risque si oubli | État |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| DOC-REG-C | `CONTRATS/00_REGISTRE_CONTRATS.md` | Contrats | Liste, nécessité, ordre, dépendances | CANONIQUE | elle-même | clôture / ouverture contrat | clôture & arbitrages registre | SUIVI, contrats dédiés | éditer MD | compteur / ordre cohérents | mauvais prochain contrat | Actif |
| DOC-SUIVI-C | `CONTRATS/00_SUIVI_CONTRATS.md` | Contrats | Avancement production documentaire | CANONIQUE | elle-même | clôture contrat | chaque clôture | REGISTRE, contrat dédié | éditer MD | progression N/16 | Hub contrats faux | Actif |
| DOC-Cxx | `CONTRATS/C-*.md` (ex. C-14) | Contrats | Règle opérationnelle dédiée | CANONIQUE | fichier contrat | rédaction → VALIDÉ | clôture | SUIVI, REGISTRE | routine `CONTRATS/ReglesRoutinesContrats.md` | audit + validation humaine | règle ambigüe | Actif (par ID) |
| DOC-ROUT-C | `CONTRATS/ReglesRoutinesContrats.md` | Contrats | Routine étapes contrats | CANONIQUE | elle-même | évolution process contrats | événementielle | SUIVI | éditer MD | — | clôtures incohérentes | Actif (présence à vérifier si non versionné) |
| MIR-SUIVI-JS | `GardenFervor_DesignGate_React/src/data/contractsSuivi.js` | Contrats | Miroir UI / sync Hub | MIROIR | `00_SUIVI` + `00_REGISTRE` + contrats | clôture contrat | chaque clôture | syncPages | éditer JS puis sync | Hub affiche N/16 | pages contrats obsolètes | Actif |
| GEN-CONTRACTS | `docs/contracts.html` | Hub | Page suivi contrats | GÉNÉRÉ | `contractsSuivi.js` | sync Hub | via `syncPages` | MIR-SUIVI-JS | `node docs/syncPages.mjs` | bandeau + cartes | lecture publique fausse | Généré |

### 2.3 Conception (Design Gate)

| ID | Document / artefact | Catégorie | Rôle | Nature | Source de vérité | Déclencheurs | Fréquence | Dépendances | Procédure | Validation | Risque si oubli | État |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| DOC-DG-JS | `GardenFervor_DesignGate_React/src/data/designGate.js` | Conception | SoT décisions DG | CANONIQUE | elle-même | décision DG confirmée | chaque décision | REGLES §7octies | éditer JS | sync standalone | conception ≠ UI | Actif |
| GEN-DG | `docs/design-gate.html` | Hub | Vue Design Gate | GÉNÉRÉ | `designGate.js` | sync | via syncPages | script `syncStandaloneFromJs.mjs` | `node docs/syncPages.mjs` | sections VALIDÉes | Hub DG obsolète | Généré |

### 2.4 Roadmap globale

| ID | Document / artefact | Catégorie | Rôle | Nature | Source de vérité | Déclencheurs | Fréquence | Dépendances | Procédure | Validation | Risque si oubli | État |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| DOC-RM-MD | `ROADMAP/GardenFervor_ROADMAP.md` | Roadmap | SoT roadmap globale | CANONIQUE | elle-même | clôture contrat / changement priorité | événementielle | SUIVI, ETAT | éditer MD | build+validate | prochain travail faux | Actif |
| DOC-RM-CL | `ROADMAP/CHANGELOG.md` | Roadmap | Journal versions roadmap | CANONIQUE | elle-même | version roadmap | avec MD | DOC-RM-MD | éditer MD | — | historique roadmap flou | Actif |
| GEN-RM-HTML | `ROADMAP/GardenFervor_ROADMAP.html` | Roadmap | Vue HTML | GÉNÉRÉ | DOC-RM-MD | build | après MD | `buildRoadmap.mjs` | `node ROADMAP/scripts/buildRoadmap.mjs` | `validateRoadmap.mjs` | HTML ≠ MD | Généré |
| GEN-RM-JSON | `ROADMAP/data/roadmap.data.json` | Roadmap | Données machine | GÉNÉRÉ | DOC-RM-MD | build | après MD | buildRoadmap | idem | hash MD | désync machine | Généré |
| GEN-RM-PAGES | `docs/roadmap-globale.html` | Hub | Copie Pages | GÉNÉRÉ | GEN-RM-HTML | sync | via syncPages | copie | `node docs/syncPages.mjs` | lien Hub | Pages stale | Généré |
| SCR-RM-BUILD | `ROADMAP/scripts/buildRoadmap.mjs` | Script | Génère HTML/JSON | SCRIPT | — | évolution schéma RM | événementielle | DOC-RM-MD | node script | validate | build cassé | Actif |
| SCR-RM-VAL | `ROADMAP/scripts/validateRoadmap.mjs` | Script | Valide cohérence | SCRIPT | — | après build | après build | GEN-RM-* | node script | exit 0 | faux OK | Actif |

### 2.5 Roadmap production S3

| ID | Document / artefact | Catégorie | Rôle | Nature | Source de vérité | Déclencheurs | Fréquence | Dépendances | Procédure | Validation | Risque si oubli | État |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| DOC-S3-DATA | `Plan de production/Roadmap/src/roadmap.data.js` | Roadmap S3 | SoT tranches T1–T9 | CANONIQUE | elle-même | clôture tranche | événementielle | Plan S3 | éditer JS | syncRoadmap | Hub S3 faux | Actif (stable post-T9) |
| GEN-S3 | `docs/roadmap.html` | Hub | Vue S3 | GÉNÉRÉ | DOC-S3-DATA | sync | via syncPages | syncRoadmap.mjs | `node docs/syncPages.mjs` | blurb Hub | Pages S3 stale | Généré |

### 2.6 Project Graph

| ID | Document / artefact | Catégorie | Rôle | Nature | Source de vérité | Déclencheurs | Fréquence | Dépendances | Procédure | Validation | Risque si oubli | État |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| DOC-PG-CUR | `PROJECT_GRAPH/scripts/curatedGraph.mjs` | Graphe | Nœuds/relations curatés | CANONIQUE (projection) | registre+suivi+repo | clôture contrat / nouveau système | événementielle | SUIVI | éditer curated | build+validate | graphe faux | Actif |
| GEN-PG-* | `PROJECT_GRAPH/GardenFervor_ProjectGraph.html`, `data/`, `graph/*.mmd`, `CURRENT_STATE.md` | Graphe | Vues générées | GÉNÉRÉ | DOC-PG-CUR | build | après curated | buildProjectGraph | `node PROJECT_GRAPH/scripts/buildProjectGraph.mjs` | validateProjectGraph | projection obsolète | Généré |
| GEN-PG-PAGES | `docs/project-graph.html` | Hub | Copie Pages | GÉNÉRÉ | GEN-PG HTML | sync | via syncPages | copie | syncPages | lien Hub | Pages stale | Généré |

### 2.7 Hub & état global

| ID | Document / artefact | Catégorie | Rôle | Nature | Source de vérité | Déclencheurs | Fréquence | Dépendances | Procédure | Validation | Risque si oubli | État |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| DOC-HUB | `docs/index.html` | Hub | Portail navigation | CANONIQUE (structure) + zones SYNC | structure manuelle ; statut via sync | nouvelle page / redesign | événementielle | syncPages | éditer structure ; sync pour bandeau | liens existent | page orpheline | Actif |
| DOC-GPAGES | `docs/GITHUB_PAGES.md` | Hub | Mode d’emploi Pages | CANONIQUE | elle-même | nouvelle page Hub | événementielle | syncPages | éditer MD | liste pages = réel | doc Pages fausse | Actif |
| DOC-EG-DATA | `docs/etat-global/etatGlobal.data.js` | Hub | Éditorial état global | CANONIQUE (éditorial) | elle-même + compteurs via suivi | clôture / audit global | événementielle | contractsSuivi | éditer JS | buildEtatGlobal | récit faux | Actif |
| GEN-EG | `docs/etat-global.html` | Hub | Vue état global | GÉNÉRÉ | DOC-EG-DATA + MIR-SUIVI-JS | sync / build | via syncPages | buildEtatGlobal.mjs | `node docs/etat-global/buildEtatGlobal.mjs` | compteurs 9/16 | Hub état faux | Généré |
| GEN-HIST | `docs/historique.html` | Hub | Chronologie historique | GÉNÉRÉ | DOC-HIST §4 | sync / build | via syncPages | buildHistorique.mjs | `node docs/historique/buildHistorique.mjs` | entrées = §4 | Hub historique stale | Généré |
| SCR-SYNC | `docs/syncPages.mjs` | Script | Sync complète Pages | SCRIPT | — | toute pub doc | après sources | sous-scripts | `node docs/syncPages.mjs` | JSON ok + liens | Pages désynchronisées | Actif |
| SCR-HIST | `docs/historique/buildHistorique.mjs` | Script | Parse HISTORIQUE → HTML | SCRIPT | DOC-HIST | évolution format §4 | événementielle | DOC-HIST | node script | exit 0 + count | chronologie cassée | Actif |
| GEN-PRES | `docs/presentation-client.html` (+ `docs/images/`) | Hub | Présentation client | GÉNÉRÉ (copie) | `Investor Demo/PrésentationClientHtml/` | sync | via syncPages | copie | syncPages | — | pitch stale | Généré |

### 2.8 Preuves techniques

| ID | Document / artefact | Catégorie | Rôle | Nature | Source de vérité | Déclencheurs | Fréquence | Dépendances | Procédure | Validation | Risque si oubli | État |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| DOC-PROOF | `Saved/ODC_F*_*.txt` | Preuves | Sorties gates | PREUVE | runtime / gate | gate exécuté | par gate | ETAT, HISTORIQUE | générer via commande gate | PASS/FAIL dans fichier | preuve introuvable | Actif |

### 2.9 Hors maintenance active (signalés)

| ID | Élément | Nature | Note |
| --- | --- | --- | --- |
| ARCH-AUDIT | `Audit de readiness pré-implémentation/` | ARCHIVE | Référence readiness ; pas de sync Hub automatique |
| ARCH-CONTENT | `Content/`, configs UE non suivis | RUNTIME | Hors maintenance documentaire Hub |
| ARCH-SRC-DIRTY | SitePrep / ProjectSubsystem (working tree) | CODE | Préservé hors docs ; ne pas mélanger aux commits doc |

---

## 3. Matrice événements → actions

Ordre fixe : **(1) sources canoniques → (2) miroirs données → (3) builds → (4) `docs/syncPages.mjs` → (5) validations → (6) contrôle humain si requis.**

### E1 — Décision Design Gate confirmée / modifiée

| Étape | Action |
| --- | --- |
| Sources | `designGate.js` |
| Dépendants | ETAT (si impact état), HISTORIQUE §4, éventuellement Roadmap |
| Vues | `docs/design-gate.html` via sync |
| Validations | syncPages OK ; relecture section touchée |
| Succès | statut DG cohérent Hub ↔ JS |
| Humain | validation conception si statut VALIDÉ |

### E2 — Clôture d’un contrat

| Étape | Action |
| --- | --- |
| Sources | `CONTRATS/C-xx_*.md` · `00_SUIVI` · `00_REGISTRE` |
| Miroirs | `contractsSuivi.js` · ETAT · HISTORIQUE · ROADMAP MD · curatedGraph · etatGlobal.data (éditorial) |
| Vues | build Roadmap · build Project Graph · syncPages (contracts, hub, etat-global, roadmap-globale, project-graph, **historique**) |
| Validations | validateRoadmap · validateProjectGraph · sync JSON · compteur N/16 aligné |
| Succès | Hub + suivi + contrat = VALIDÉ ; prochain ID correct |
| Humain | validation finale contrat (déjà acquise avant clôture) |

### E3 — Clôture / preuve jalon technique (ODC gate, tranche S3)

| Étape | Action |
| --- | --- |
| Sources | preuve `Saved/` · ETAT · HISTORIQUE · éventuellement roadmap S3 data |
| Vues | sync si Hub touché ; build S3 si data changée |
| Validations | fichier preuve présent ; ETAT aligné |
| Succès | phase ODC / tranche reflétée |
| Humain | si gate « PASS (humain) » |

### E4 — Modification règle / architecture process

| Étape | Action |
| --- | --- |
| Sources | `REGLES_PROJET.md` et/ou `ReglesRoutinesContrats.md` |
| Dépendants | **ce registre** (§5) ; Hub howto si commande change |
| Vues | sync si GITHUB_PAGES / index |
| Validations | chemins §6 |
| Succès | agents peuvent suivre le process |

### E5 — Mise à jour objectif / priorité / Roadmap globale

| Étape | Action |
| --- | --- |
| Sources | `ROADMAP/GardenFervor_ROADMAP.md` (+ CHANGELOG) |
| Vues | buildRoadmap → syncPages (roadmap-globale + hub) |
| Validations | validateRoadmap |
| Succès | `next` Hub = RM:NEXT |

### E6 — Ajout / retrait / déplacement document

| Étape | Action |
| --- | --- |
| Sources | document concerné |
| Dépendants | **ce registre** · `docs/GITHUB_PAGES.md` · `docs/index.html` si page Hub · syncPages si nouvelle page |
| Validations | contrôle chemins §6 |
| Succès | inventaire à jour ; pas de lien mort |

### E7 — Changement schéma données / script génération

| Étape | Action |
| --- | --- |
| Sources | script + README associés |
| Dépendants | ce registre · GITHUB_PAGES |
| Vues | rebuild concernés + sync |
| Validations | validateurs du sous-système |
| Succès | chaîne Source→Vue OK |

### E8 — Ajout / modification page Hub

| Étape | Action |
| --- | --- |
| Sources | structure `docs/index.html` · script build page · syncPages |
| Dépendants | GITHUB_PAGES · ce registre |
| Validations | syncPages ; ouvrir lien relatif |
| Succès | carte Hub → page |

### E9 — Synchronisation / publication documentaire

| Étape | Action |
| --- | --- |
| Sources | déjà à jour |
| Commande | `node docs/syncPages.mjs` |
| Validations | sortie JSON `ok: true` ; pages listées |
| Succès | bandeau SYNC à jour |
| Git | commit dédié + push **sur autorisation** |

### E10 — Échec validateur / miroir obsolète

| Étape | Action |
| --- | --- |
| Sources | identifier SoT vs généré (hash / validate) |
| Action | rebuild depuis SoT ; ne pas éditer le HTML généré à la main |
| Succès | validate exit 0 |

---

## 4. Chaînes de commandes (vérifiées)

Depuis la **racine** du dépôt :

```bash
# Roadmap globale
node ROADMAP/scripts/buildRoadmap.mjs
node ROADMAP/scripts/validateRoadmap.mjs

# Project Graph
node PROJECT_GRAPH/scripts/buildProjectGraph.mjs
node PROJECT_GRAPH/scripts/validateProjectGraph.mjs

# Historique Hub (miroir HISTORIQUE §4)
node docs/historique/buildHistorique.mjs

# État global seul
node docs/etat-global/buildEtatGlobal.mjs

# Sync Hub complète (inclut historique + état global + contrats + copies)
node docs/syncPages.mjs
```

---

## 5. Maintenance de ce registre

Mettre à jour `REGISTRE_MAINTENANCE_DOCUMENTAIRE.md` lorsque :

- un document de suivi est créé, déplacé, renommé ou retiré ;
- une page Hub ou un script de sync/build est ajouté ou modifié ;
- une source de vérité change de chemin ;
- une procédure de génération change.

Contrôle minimal (§6) après édition.  
Pointer depuis `REGLES_PROJET.md` (table fichiers d’état) — les agents doivent **consulter et maintenir** ce registre lors des opérations documentaires concernées.

---

## 6. Contrôle de couverture (checklist)

À exécuter après toute évolution documentaire structurante :

- [ ] Chaque page listée dans `docs/GITHUB_PAGES.md` a une entrée ici
- [ ] Chaque commande de `docs/syncPages.mjs` est référencée
- [ ] Chemins cités existent sur disque
- [ ] Toute vue `GÉNÉRÉ` a une SoT identifiée
- [ ] Aucune SoT n’est éditée « via » son HTML généré
- [ ] `docs/historique.html` se régénère depuis `HISTORIQUE_MODIFICATIONS.md`
- [ ] Travaux locaux non liés (ex. SitePrep dirty) ne sont pas mélangés aux commits doc

**Incertitudes assumées :**

- Les dossiers `Audit de readiness…` ne sont pas dans la chaîne Hub (archive) — confirmé par absence dans syncPages.
- Contenu Unreal non suivi : hors périmètre maintenance documentaire.
- Cadence périodique du registre : proposition seulement (§1).

---

## 7. Rappel Git

Cette maintenance documentaire se versionne par **commits dédiés**, sans `git add .`, sans force push, avec préservation des working trees étrangers.  
Commit et push restent des étapes **explicitement autorisées**, distinctes de la rédaction.

---

*Fin du registre de maintenance documentaire.*
