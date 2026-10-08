# GitHub Pages — Hub documentation GardenFervor

## URL

`https://josephv01.github.io/GardenFervor/`

## Fichiers publiés (`docs/`)

| Fichier | Rôle |
| --- | --- |
| **`index.html`** | **Hub d’accueil** — liens vers tous les documents HTML |
| `roadmap.html` | Roadmap de production (page autonome) |
| `design-gate.html` | Design Gate autonome |
| `contracts.html` | Suivi des contrats (vue publiée) |

## Historique

Jusqu’en 2026-10-08, `docs/index.html` contenait uniquement la Roadmap.  
Ce contenu a été **dupliqué** vers `docs/roadmap.html` avant que `index.html` ne devienne le hub.

## Synchronisation

### Roadmap

```bash
node "Plan de production/Roadmap/scripts/syncRoadmap.mjs"
```

Met à jour :

- `Plan de production/Roadmap/index.html`
- `docs/roadmap.html`

**Ne modifie plus** `docs/index.html`.

Source de vérité : `Plan de production/Roadmap/src/roadmap.data.js`

### Design Gate

```bash
node GardenFervor_DesignGate_React/scripts/syncStandaloneFromJs.mjs
```

Met à jour :

- `GardenFervor_DesignGate_React/GardenFervor_DESIGN_GATE_v0.1.html`
- `docs/design-gate.html`

Source de vérité : `GardenFervor_DesignGate_React/src/data/designGate.js`

### Contrats

Source de vérité : `CONTRATS/*.md`  
Miroir React : `GardenFervor_DesignGate_React/src/data/contractsSuivi.js`  
Vue Pages : `docs/contracts.html` (à resynchroniser manuellement si le suivi change).

### Hub

`docs/index.html` est édité pour la navigation Pages.  
Ne pas le faire écraser par un sync roadmap.

## Activation manuelle (GitHub)

Dans le dépôt `JosephV01/GardenFervor` :

1. **Settings → Pages**
2. **Build and deployment → Source** : *Deploy from a branch*
3. **Branch** : `main`
4. **Folder** : `/docs`
5. Enregistrer

Délai possible de quelques minutes après push.
