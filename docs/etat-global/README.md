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

## Quatre couches distinctes

| Couche | Où | Nature |
| --- | --- | --- |
| HEAD Git courant | Git (`git rev-parse HEAD`) | Live. Cette page **ne le calcule pas**. |
| Référence Git de l’audit éditorial | `meta.gitHeadAtAudit` + `meta.gitMessageAtAudit` | **Historique et figée.** Jalon choisi (clôture C-14), pas le HEAD. Ne pas bumper à chaque commit, génération ou `syncPages`. |
| Compteurs / statuts contrats | `contractsSuivi.js` injecté au build | Live au moment de la génération. |
| Récit éditorial | reste de `etatGlobal.data.js` | Baseline longue du Hub. Distincte de `ETAT_PROJET.md` (baseline courte). |

`gitHeadAtAudit` n’est **pas** une donnée live. Le rebuild recopie le champ tel quel.

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
(audit post C-12). Référence Git de l’audit éditorial = clôture C-14
(`gitHeadAtAudit`, 2026-10-09). Le Canvas n’est **pas** la source de maintenance.
