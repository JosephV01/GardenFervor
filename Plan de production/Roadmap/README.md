# Roadmap de production — GardenFervor

## Rôle

Vue de **pilotage** de l’avancement réel de la production.

| Document | Rôle |
| --- | --- |
| Design Gate | Décisions de conception |
| `PLAN_PRODUCTION_COHORTE_S3.md` | Comment produire |
| `ETAT_PROJET.md` | Snapshot projet |
| `HISTORIQUE_MODIFICATIONS.md` | Traçabilité longue |
| **Cette roadmap** | Où en est la production |

## Source de vérité

**Unique :** `src/roadmap.data.js`

Ne pas éditer à la main le JSON ni les HTML générés.

## Synchronisation

```bash
node "Plan de production/Roadmap/scripts/syncRoadmap.mjs"
```

Génère / met à jour :

- `roadmap.data.json`
- `Plan de production/Roadmap/index.html` (vue de travail)
- **`docs/index.html`** (entrée GitHub Pages — page autonome)

Ouvrir en local : `docs/index.html` ou `Plan de production/Roadmap/index.html`  
Publication : voir `docs/GITHUB_PAGES.md`

## Quand mettre à jour

- Une tranche **commence** → `EN COURS` + `meta.currentSliceId`
- Passage en **validation humaine** → `VALIDATION`
- Validation humaine **OK** → `VALIDÉ` + `validatedAt` ; avancer `nextSliceId`
- **Blocage** → `BLOQUÉ` + `block` / `meta.blockNote`
- Reformulation / abandon → statut + note ; sync

### Règle fondamentale

**Code terminé ≠ VALIDÉ.**  
`VALIDÉ` exige la validation prévue dans le Plan de production.

## Progression

Calculée uniquement depuis le nombre de tranches en statut `VALIDÉ` / total.

## Design Gate

La roadmap peut afficher un blocage et référencer un DG.  
Elle ne modifie jamais le Design Gate.
