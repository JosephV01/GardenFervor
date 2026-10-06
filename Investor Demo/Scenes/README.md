# Scenes

## Scène dédiée — étape 2 VALIDÉE

| Champ | Valeur |
| --- | --- |
| Nom | `L_InvestorDemo_S3` |
| Chemin Unreal | `/Game/GardenFervor/InvestorDemo/L_InvestorDemo_S3` |
| Fichier | `Content/GardenFervor/InvestorDemo/L_InvestorDemo_S3.umap` |
| Validation visuelle | **Confirmée** (humain) |
| Versionnement Git | **Oui** — `Content/GardenFervor/InvestorDemo/` (étape 2B) |
| Git LFS | Non requis (assets ≈ 165 Ko) |
| Gameplay T1→T9 | Non branché |

**Ne pas modifier** `GardenFervorIsland` pour cette démo.

### Ouverture

1. Ouvrir `GardenFervorEditor`.
2. Content Browser → `GardenFervor/InvestorDemo/L_InvestorDemo_S3`.
3. PIE : `GardenFervorGameMode` → `AGardenFervorStrategyPawn` depuis `Demo_PlayerStart_Overview`.

### Chaîne visuelle validée

`Intention → Project → WorkSite → U1 → Stock A → U2 → Stock B → U3 → En service`

### Polish futur (non bloquant)

Certains labels `TextRender` apparaissent inversés selon l’angle de vue — à corriger plus tard (billboard / orientation).

### Générateur temporaire

Le script `Content/Python/create_investor_demo_level.py` a été **supprimé** après validation : il n’était pas un outil permanent. La scène et ses matériaux restent en place.
