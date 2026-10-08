# ROADMAP — Roadmap globale GardenFervor

Pilotage permanent : **où en est le projet, que faire ensuite, jusqu’au jeu final**.

## Source de vérité

```text
ROADMAP/GardenFervor_ROADMAP.md
```

Toute modification de contenu commence par ce fichier Markdown.  
Le HTML est **uniquement** une vue générée.

```text
GardenFervor_ROADMAP.md  →  build  →  GardenFervor_ROADMAP.html
```

## Différence avec les autres outils

| Outil | Rôle |
| --- | --- |
| **Cette Roadmap** | Ordre global et horizons jusqu’au produit |
| **Plan de production / Roadmap** | Suivi des tranches T1–T9 (cohorte S3) |
| **Design Gate** | Décisions de conception validées |
| **Contrats** | Règles opérationnelles par système |
| **Project Graph** | Interconnexions systèmes / preuves |

## Générer

```bash
node ROADMAP/scripts/buildRoadmap.mjs
node ROADMAP/scripts/validateRoadmap.mjs
```

## Modifier

1. Éditer `GardenFervor_ROADMAP.md`
2. `node ROADMAP/scripts/buildRoadmap.mjs`
3. `node ROADMAP/scripts/validateRoadmap.mjs`
4. Vérifier `GardenFervor_ROADMAP.html`
5. Commit dédié (Markdown **et** HTML généré)
6. Push sur la branche courante

**Jamais** éditer le HTML pour changer le fond.

## Hub / GitHub Pages

- Hub : `docs/index.html` → raccourci **Roadmap GardenFervor**
- Page publiée : `docs/roadmap-globale.html` (copie synchronisée)
- URL : `https://josephv01.github.io/GardenFervor/roadmap-globale.html`

Sync :

```bash
node docs/syncPages.mjs
```

## Structure des balises (dans le .md)

Les commentaires `<!--RM:…-->` permettent le parsing machine.  
Ne pas les supprimer lors d’une édition.
