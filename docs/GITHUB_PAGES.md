# GitHub Pages — Hub documentation GardenFervor

## URL

`https://josephv01.github.io/GardenFervor/`

## Fichiers publiés (`docs/`)

| Fichier | Rôle |
| --- | --- |
| **`index.html`** | **Hub d’accueil** — état projet + liens |
| `roadmap.html` | Roadmap de production |
| `design-gate.html` | Design Gate autonome |
| `contracts.html` | Suivi des contrats |
| `syncPages.mjs` | Synchronisation complète des pages |

## Historique

Jusqu’en 2026-10-08, `docs/index.html` contenait uniquement la Roadmap.  
Ce contenu a été **dupliqué** vers `docs/roadmap.html` avant que `index.html` ne devienne le hub.

## Tenir le hub à jour (obligatoire après modification documentaire)

Dès qu’un de ces éléments change :

- roadmap (`roadmap.data.js` / statut de tranche) ;
- Design Gate (`designGate.js`) ;
- contrats (`CONTRATS/*.md` + `contractsSuivi.js`) ;
- ajout d’un nouveau document HTML à publier ;

exécuter **depuis la racine du dépôt** :

```bash
node docs/syncPages.mjs
```

Puis commit + push `main` pour rafraîchir GitHub Pages.

Cette commande :

1. synchronise `docs/roadmap.html` ;
2. synchronise `docs/design-gate.html` ;
3. régénère `docs/contracts.html` depuis `contractsSuivi.js` ;
4. met à jour le bandeau d’état et les résumés de cartes dans `docs/index.html`.

**Ne pas** écraser manuellement le bandeau entre `<!-- SYNC:STATUS:START -->` et `<!-- SYNC:STATUS:END -->` — il est généré.

## Sources de vérité

| Page | Source |
| --- | --- |
| Roadmap | `Plan de production/Roadmap/src/roadmap.data.js` |
| Design Gate | `GardenFervor_DesignGate_React/src/data/designGate.js` |
| Contrats | `CONTRATS/*.md` (miroir UI : `contractsSuivi.js`) |
| Hub navigation | `docs/index.html` (structure) + sync pour l’état |

## Activation manuelle (GitHub)

1. **Settings → Pages**
2. **Source** : Deploy from a branch
3. **Branch** : `main` / folder **`/docs`**
4. Enregistrer

Délai possible de quelques minutes après push.
