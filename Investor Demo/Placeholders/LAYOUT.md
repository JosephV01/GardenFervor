# Placeholders — disposition L_InvestorDemo_S3

**Scène Unreal :** `/Game/GardenFervor/InvestorDemo/L_InvestorDemo_S3`  
**Étape 2 :** **VALIDÉE** (validation visuelle humaine)  
**Nature :** visuel uniquement (pas d’autorité gameplay)

## Organisation Content

```text
Content/GardenFervor/InvestorDemo/
├── L_InvestorDemo_S3.umap
└── Materials/
    └── MI_PH_*.uasset
```

## Disposition (cm, origine monde)

| Placeholder | Label | Position approx. (X, Y, Z) | Forme |
| --- | --- | --- | --- |
| Intention | `INTENTION` | (0, -3200, 120) | Cube |
| Project | `PROJECT` | (0, -2400, 120) | Cube |
| WorkSite | `WORKSITE` | (0, -400, 5) | Plan large |
| U1 | `U1 — EXTRACTION` | (-2200, -200, 100) | Cylindre |
| Stock A | `STOCK A` | (-2200, 600, 100) | Cube |
| U2 | `U2 — TRANSPORT` | (0, 600, 100) | Cylindre |
| Stock B | `STOCK B` | (2200, 600, 100) | Cube |
| U3 | `U3 — CONSTRUCTION` | (2200, 1600, 100) | Cylindre |
| En service | `EN SERVICE` | (2200, 2600, 120) | Cube |
| HUD réservé | `HUD / ÉTATS (réservé)` | (-2800, -3200, 40) | Plan |

## Couleurs (visuel seul)

| Élément | Teinte |
| --- | --- |
| Intention | Cyan |
| Project | Violet |
| WorkSite | Vert sombre |
| U1 | Orange |
| Stock A | Brun |
| U2 | Jaune |
| Stock B | Bleu-vert |
| U3 | Magenta |
| En service | Vert vif |
| HUD slot | Gris |

## Polish futur (non bloquant)

Certains `TextRender` sont **inversés** selon la vue caméra. Ne bloque pas la lisibilité globale de la chaîne. Correction reportée (hors clôture étape 2).

## Remplacement futur

```text
PH_* (BasicShapes + MI_PH_*)
    ↓
Mesh démo dédié
    ↓
Asset temporaire art
    ↓
Asset GardenFervor final
```
