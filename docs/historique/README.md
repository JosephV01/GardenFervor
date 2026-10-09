# Historique des modifications — miroir Hub

## Source de vérité

```text
HISTORIQUE_MODIFICATIONS.md  (§4 — historique chronologique)
```

Ne pas maintenir un second historique parallèle.  
Toute évolution se fait dans le Markdown racine ; la page HTML est régénérée.

## Générer

Depuis la racine du dépôt :

```bash
node docs/historique/buildHistorique.mjs
```

Sortie : `docs/historique.html`

Également invoqué par :

```bash
node docs/syncPages.mjs
```

## Hub

Carte **Historique des modifications** → `historique.html` dans `docs/index.html`.
