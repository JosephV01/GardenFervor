# État global du projet — source Hub

## Rôle

Page publique **État global du projet** (`docs/etat-global.html`) : bilan détaillé
systèmes / maturité / preuves / priorités, pour consultation régulière sans relancer un audit.

## Sources de vérité

| Contenu | Source | Mise à jour |
| --- | --- | --- |
| Compteurs contrats, statut C-*, Case B, prochain autorisé | `GardenFervor_DesignGate_React/src/data/contractsSuivi.js` (miroir de `CONTRATS/00_SUIVI_CONTRATS.md`) | Clôture de contrat → sync suivi → `node docs/syncPages.mjs` |
| Descriptions systèmes, scénarios, priorités, risques, recommandations | **`etatGlobal.data.js`** (éditorial) | Éditer ce fichier, puis rebuild |
| Preuves ODC | Textes dans `etatGlobal.data.js` (référencent `Saved/ODC_F*.txt`) | Mettre à jour après nouveau gate |

Les **statuts contractuels** ne doivent **pas** être dupliqués à la main dans `etatGlobal.data.js`
sauf notes runtime (`contractsNotes`). Le build injecte les statuts depuis `contractsSuivi.js`.

## Commandes

```bash
# Rebuild page seule
node docs/etat-global/buildEtatGlobal.mjs

# Sync Hub complet (inclut cette page)
node docs/syncPages.mjs
```

## Sortie

- `docs/etat-global.html` — vue publiée (GitHub Pages)
- Lien Hub : carte **État global du projet** dans `docs/index.html`

## Origine éditoriale

Contenu initial dérivé du Canvas Cursor `gardenfervor-etat-global.canvas.tsx`
(audit post C-12, 2026-10-09). Le Canvas n’est **pas** la source de maintenance.
