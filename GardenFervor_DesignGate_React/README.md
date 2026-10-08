# GardenFervor — Design Gate v0.1 (React)

Document interactif de conception du jeu, construit comme un petit workspace React/Vite.

## Lancer en local

Prérequis : Node.js récent.

```bash
npm install
npm run dev
```

Puis ouvrir l’URL indiquée par Vite.

## Construire une version statique

```bash
npm run build
```

La sortie est générée dans `dist/`.

## Organisation

- `src/data/designGate.js` : contenu du Design Gate + statuts + export Markdown.
- `src/data/contractsSuivi.js` : miroir UI du suivi des contrats (source de vérité = `CONTRATS/*.md`).
- `src/ContractsSuiviView.jsx` : page **Suivi des contrats**.
- `src/main.jsx` : interface React, onglets Design Gate / Suivi des contrats.
- `src/styles.css` : style visuel.
- `index.html` : point d’entrée.

### Suivi des contrats

Onglet **Suivi des contrats** dans la barre supérieure.  
Vue de pilotage uniquement — ne remplace pas `CONTRATS/00_REGISTRE_CONTRATS.md` ni `CONTRATS/00_SUIVI_CONTRATS.md`.  
Après mise à jour des Markdown CONTRATS, synchroniser `src/data/contractsSuivi.js`.

Le contenu est volontairement structuré comme un questionnaire : une décision explicitement validée peut devenir `VALIDÉ`, une question non tranchée reste `À DÉFINIR`, et une dépendance bloquante peut rester `DÉPENDANT`.

Le bouton **Exporter Markdown** produit `GardenFervor_DESIGN_GATE_v0.1.md` à partir des mêmes données structurées.

## Maintenance permanente

`src/data/designGate.js` est la **source de vérité de conception**. Le mettre à jour dès qu’une décision est prise, dès qu’une ambiguïté apparaît, et après chaque jalon qui impacte les règles. Ne jamais passer un item à `VALIDÉ` sans confirmation explicite. En cas d’écart avec le code Unreal : signaler `Design Gate ≠ implémentation` plutôt que d’aligner en silence. Règles projet détaillées : `REGLES_PROJET.md` §7octies.

### Synchroniser HTML autonome + miroir JSON

Après toute modification de `designGate.js` :

```bash
node scripts/syncStandaloneFromJs.mjs
```

Cela régénère `GardenFervor_DESIGN_GATE_v0.1.html` (bloc données) et `designGate.data.json` (snapshot hors runtime). Ni le HTML ni le JSON ne sont des sources de décision.
