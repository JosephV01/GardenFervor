# Scenes

## Scène dédiée — étape 2 · P0 · étape 3 · étape 4 = VALIDÉES

| Champ | Valeur |
| --- | --- |
| Nom | `L_InvestorDemo_S3` |
| Chemin Unreal | `/Game/GardenFervor/InvestorDemo/L_InvestorDemo_S3` |
| Fichier | `Content/GardenFervor/InvestorDemo/L_InvestorDemo_S3.umap` |
| Validation visuelle | **Confirmée** (humain) |
| P0 isolement runtime | **VALIDÉ** (humain) — aucun boot AoE legacy |
| Étape 3 S3 | **VALIDÉ** (humain) — parcours + présentation Cas A |
| Étape 4 présentation | **VALIDÉ** (humain) — caméra · 10 beats · overlay compact haut-gauche |
| Versionnement Git | **Oui** — `Content/GardenFervor/InvestorDemo/` |
| Git LFS | `L_InvestorDemo_S3.umap` (règle fichier spécifique) |
| GameMode PIE | `GardenFervorInvestorDemoGameMode` (prefix `L_InvestorDemo`) |
| Gameplay T1→T9 | Branché — F8 / `gf.InvestorDemo.RunS3` · Case A **sans Terraform** |

**Ne pas modifier** `GardenFervorIsland` pour cette démo (`AGardenFervorGameMode` inchangé).

### Ouverture

1. Ouvrir `GardenFervorEditor`.
2. Content Browser → `GardenFervor/InvestorDemo/L_InvestorDemo_S3`.
3. PIE : `GardenFervorInvestorDemoGameMode` → `AGardenFervorStrategyPawn` depuis `Demo_PlayerStart_Overview`.
4. Déclencher le parcours : **F8** (ou console `gf.InvestorDemo.RunS3`).
5. Observer : caméra guidée · overlay haut-gauche · unités colorées · parcours async.
6. Log attendu : `ok=1 · PeakA=1.0 · B=1.0 · Complete=1 EnService=1` · Case A sans Terraform.

### Chaîne visuelle validée

`Intention → Project → Analyse → WorkSite → U1 → Stock A → U2 → Stock B → U3 → Achevé → En service`

### Polish futur (non bloquant)

Certains labels `TextRender` apparaissent inversés selon l’angle de vue — à corriger plus tard (billboard / orientation).

### Générateur temporaire

Le script `Content/Python/create_investor_demo_level.py` a été **supprimé** après validation : il n’était pas un outil permanent. La scène et ses matériaux restent en place.
