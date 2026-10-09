# GitHub Pages — Hub documentation GardenFervor

## URL

`https://josephv01.github.io/GardenFervor/`

## Fichiers publiés (`docs/`)

| Fichier | Rôle |
| --- | --- |
| **`index.html`** | **Hub d’accueil** — état projet + liens |
| `etat-global.html` | État global du projet (systèmes, maturité, preuves, priorités) |
| `historique.html` | Historique des modifications (miroir de `HISTORIQUE_MODIFICATIONS.md` §4) |
| `roadmap.html` | Roadmap de production S3 (tranches T1–T9) |
| `roadmap-globale.html` | Roadmap globale |
| `design-gate.html` | Design Gate autonome |
| `contracts.html` | Suivi des contrats |
| `project-graph.html` | Project Graph |
| `presentation-client.html` | Présentation client GardenFervor (copie publiée ; hors démo) |
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
4. met à jour le bandeau d’état et les résumés de cartes dans `docs/index.html` ;
5. copie `Investor Demo/PrésentationClientHtml/PrésentationClient.html` → `docs/presentation-client.html` ;
6. copie `Investor Demo/PrésentationClientHtml/images/` → `docs/images/` (galerie lot1) ;
7. copie Project Graph et Roadmap globale ;
8. régénère `docs/etat-global.html` depuis `docs/etat-global/etatGlobal.data.js` + `contractsSuivi.js` ;
9. régénère `docs/historique.html` depuis `HISTORIQUE_MODIFICATIONS.md` (§4).

**Ne pas** écraser manuellement le bandeau entre `<!-- SYNC:STATUS:START -->` et `<!-- SYNC:STATUS:END -->` — il est généré.

Inventaire des documents à maintenir : **`REGISTRE_MAINTENANCE_DOCUMENTAIRE.md`** (racine).

## Sources de vérité

| Page | Source |
| --- | --- |
| Roadmap S3 (`roadmap.html`) | `Plan de production/Roadmap/src/roadmap.data.js` |
| Roadmap globale (`roadmap-globale.html`) | `ROADMAP/GardenFervor_ROADMAP.md` (vue HTML générée, puis copiée) |
| Project Graph (`project-graph.html`) | `PROJECT_GRAPH/scripts/curatedGraph.mjs` (vue HTML générée, puis copiée) |
| Design Gate | `GardenFervor_DesignGate_React/src/data/designGate.js` |
| Contrats | `CONTRATS/*.md` (miroir UI : `contractsSuivi.js`) |
| État global | `docs/etat-global/etatGlobal.data.js` (éditorial) + compteurs via `contractsSuivi.js` — voir `docs/etat-global/README.md` |
| Historique | `HISTORIQUE_MODIFICATIONS.md` (§4) — build `docs/historique/buildHistorique.mjs` |
| Présentation client | `Investor Demo/PrésentationClientHtml/PrésentationClient.html` |
| Hub navigation | `docs/index.html` (structure) + sync pour l’état |

## Activation manuelle (GitHub)

1. **Settings → Pages**
2. **Source** : Deploy from a branch
3. **Branch** : `main` / folder **`/docs`**
4. Enregistrer

Délai possible de quelques minutes après push.
