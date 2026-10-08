# PROJECT_GRAPH — Cartographie globale GardenFervor

Projection documentaire **vivante** de l’architecture du projet : systèmes, règles, contrats, données, preuves, intégrations et frontières.

> **Ce graphe n’est pas une source de vérité.**  
> En cas de conflit : **dépôt réel → règles/contrats/Design Gate → preuves → documentation descriptive.**

## Contenu

```text
PROJECT_GRAPH/
├── README.md
├── CURRENT_STATE.md          ← inventaire + anomalies de la dernière génération
├── CHANGELOG.md
├── GardenFervor_ProjectGraph.html
├── data/
│   └── projectGraph.data.json
├── graph/
│   ├── GardenFervor_ProjectGraph.mmd      (MASTER)
│   ├── GardenFervor_SystemsGraph.mmd
│   ├── GardenFervor_RulesGraph.mmd
│   ├── GardenFervor_DataFlowGraph.mmd
│   ├── GardenFervor_ExecutionGraph.mmd
│   ├── GardenFervor_ValidationGraph.mmd
│   └── GardenFervor_ExternalGraph.mmd
└── scripts/
    ├── curatedGraph.mjs      ← nœuds/relations curatés (sources vérifiées)
    ├── buildProjectGraph.mjs
    └── validateProjectGraph.mjs
```

## Régénérer

Depuis la **racine du dépôt** :

```bash
node PROJECT_GRAPH/scripts/buildProjectGraph.mjs
node PROJECT_GRAPH/scripts/validateProjectGraph.mjs
```

Aucune dépendance npm supplémentaire. Aucune modification hors `PROJECT_GRAPH/`.

## Ouvrir la vue interactive

Ouvrir localement :

```text
PROJECT_GRAPH/GardenFervor_ProjectGraph.html
```

Fonctions : zoom, pan, recherche, filtres catégorie/statut/vue, détail des sources et relations.

## Comment sont déterminés les statuts

Chaque nœud important porte trois champs distincts :

| Champ | Signification |
| --- | --- |
| `designStatus` | Conception / document (ex. VALIDÉ, PLANNED) |
| `implementationStatus` | Code réel (IMPLEMENTED, PARTIAL, STUB, LEGACY, SUSPENDED…) |
| `validationStatus` | Preuve (PASS, INVALIDÉ, PARTIAL, n/a) |

Exemple : **C-01** peut être `designStatus=VALIDÉ` avec `implementationStatus=PARTIAL` et dettes F1.

## Comment ajouter une relation

1. Vérifier la relation dans le **code**, un **contrat VALIDÉ**, une **règle**, ou une **preuve**.
2. L’ajouter dans `scripts/curatedGraph.mjs` avec :
   - `type` parmi la liste officielle (`DEPENDS_ON`, `GOVERNS`, `SIGNALS`…) ;
   - `confidence` (`HIGH` / `MEDIUM` / `LOW`) ;
   - `source` (chemin fichier) ;
   - `relationKind` : `ACTIVE` (défaut), `FUTURE`, ou `UNVERIFIED`.
3. Relancer le build + validate.

**Ne jamais** inventer une connexion « logique » sans source. Si incertaine → `UNVERIFIED` ou ne pas l’ajouter.

## Relation incertaine

- `confidence: LOW` et/ou `relationKind: UNVERIFIED`
- conserver `source` + `notes` expliquant le doute
- le HTML affiche ces liens en style distinct (pointillé)

## Vérifier que le graphe reflète le dépôt

1. Relancer `buildProjectGraph.mjs`
2. Lire `CURRENT_STATE.md` (anomalies, headers non mappés, divergences doc)
3. Lancer `validateProjectGraph.mjs`
4. Comparer HEAD / dirty tree dans `generationInfo`

## Sources inspectées à chaque build

- `REGLES_PROJET.md`, `ETAT_PROJET.md`, `HISTORIQUE_MODIFICATIONS.md`
- `CONTRATS/` (registre, suivi, contrats présents)
- Design Gate React (`designGate.js`)
- `Source/GardenFervor/` (scan headers subsystems / gates / components)
- `Saved/ODC_*Gate.txt`
- `GardenFervor.uproject`, `Content/`, `docs/`

## Maintenance

Lorsqu’un système, contrat, frontière, flux ou preuve change : **régénérer** le graphe.  
Il n’existe pas aujourd’hui de hook git automatique — la régénération est manuelle via les commandes ci-dessus.

## Périmètre des modifications

La cartographie ne doit modifier **que** `PROJECT_GRAPH/`.  
Elle ne corrige pas les dettes, ne valide pas de contrats, et ne change pas le Design Gate.
