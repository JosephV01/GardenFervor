# Scenes

## Scène dédiée — étape 2 VALIDÉE · P0 runtime VALIDÉ

| Champ | Valeur |
| --- | --- |
| Nom | `L_InvestorDemo_S3` |
| Chemin Unreal | `/Game/GardenFervor/InvestorDemo/L_InvestorDemo_S3` |
| Fichier | `Content/GardenFervor/InvestorDemo/L_InvestorDemo_S3.umap` |
| Validation visuelle | **Confirmée** (humain) |
| P0 isolement runtime | **VALIDÉ** (humain) — aucun boot AoE legacy |
| Versionnement Git | **Oui** — `Content/GardenFervor/InvestorDemo/` (étape 2B) |
| Git LFS | Non requis (assets ≈ 165 Ko) |
| GameMode PIE | `GardenFervorInvestorDemoGameMode` (prefix `L_InvestorDemo`) |
| Gameplay T1→T9 | Non branché · étape 3 non démarrée |

**Ne pas modifier** `GardenFervorIsland` pour cette démo (`AGardenFervorGameMode` inchangé).

### Ouverture

1. Ouvrir `GardenFervorEditor`.
2. Content Browser → `GardenFervor/InvestorDemo/L_InvestorDemo_S3`.
3. PIE : `GardenFervorInvestorDemoGameMode` → `AGardenFervorStrategyPawn` depuis `Demo_PlayerStart_Overview`.

### Chaîne visuelle validée

`Intention → Project → WorkSite → U1 → Stock A → U2 → Stock B → U3 → En service`

### Polish futur (non bloquant)

Certains labels `TextRender` apparaissent inversés selon l’angle de vue — à corriger plus tard (billboard / orientation).

### Générateur temporaire

Le script `Content/Python/create_investor_demo_level.py` a été **supprimé** après validation : il n’était pas un outil permanent. La scène et ses matériaux restent en place.
