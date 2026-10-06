# Scénario de démonstration — S3 Cas A (T1→T9)

Durée cible : **3 à 5 minutes**.  
Mode : démonstration guidée (humain) ; automatisation visuelle = étapes futures.  
Autorité : systèmes gameplay réels — **pas de simulation parallèle**.

## Scène visuelle (étape 2 — VALIDÉE)

| Champ | Valeur |
| --- | --- |
| Nom | `L_InvestorDemo_S3` |
| Chemin | `/Game/GardenFervor/InvestorDemo/L_InvestorDemo_S3` |
| Fichier | `Content/GardenFervor/InvestorDemo/L_InvestorDemo_S3.umap` |
| Disposition | `Investor Demo/Placeholders/LAYOUT.md` |
| Validation visuelle | **Confirmée** (humain) |

Organisation spatiale validée :

```text
[INTENTION]
        ↓
[PROJECT]
        ↓
[WORKSITE]
      ┌───────┐
      │       │
   [U1]     [U2]
      │       │
 [Stock A] → [Stock B]
                 ↓
                [U3]
                 ↓
          [EN SERVICE]
```

HUD / états futurs : plan réservé (coin NW).  
Placeholders présents · **T1→T9 non branchés**.  
Polish futur : certains `TextRender` inversés selon la vue (non bloquant).

---

## Fil narratif (ce que comprend l’investisseur)

> « Le joueur formule une intention. Le jeu crée un projet de chantier. Le site est déjà prêt (Cas A). Une unité extrait du bois physique (Timber), une autre le transporte vers un second stock, une troisième établit l’achèvement. Le chantier n’entre en service que lorsque le bois est réellement disponible au stock de destination — et tout cela se lit dans l’économie physique, pas dans un HUD fictif. »

---

## Séquence détaillée

### Beat 1 — Intention → Project (T6)

| | |
| --- | --- |
| **Investisseur voit** | Un signal d’intention + un projet « Draft » nommé / numéroté |
| **Démonstrateur fait** | Déclenche l’entrée Intention (futur UI démo ou commande déjà validée) |
| **Change visuellement** | Apparition du marqueur Projet + zone |
| **Système réel** | `CreateProjectFromIntention` · pas de TrySpend / BeginPlace |

### Beat 2 — Analyse (générique, chaîne T9)

| | |
| --- | --- |
| **Investisseur voit** | Un temps court d’analyse sur la zone |
| **Démonstrateur fait** | Laisse la tâche Analyze se résoudre (ou avance le smoke) |
| **Change visuellement** | Marqueur « Analyse » → terminé |
| **Système réel** | Tâche `Analyze` / `AnalyzeSite` (pas ForestAnalysis) |

### Beat 3 — WorkSite prêt (T5 · Cas A)

| | |
| --- | --- |
| **Investisseur voit** | Zone de travail marquée « prête » |
| **Démonstrateur fait** | Souligne : *aucun terrassement* |
| **Change visuellement** | Contour zone / label AlreadyReady |
| **Système réel** | SitePrep `AlreadyReady` · **pas** Raise/Lower/Paint |

### Beat 4 — Roster U1 / U2 / U3 (T3)

| | |
| --- | --- |
| **Investisseur voit** | Trois unités distinctes (placeholders) |
| **Démonstrateur fait** | Nomme les rôles : Extraction / Transport / Construction |
| **Change visuellement** | Labels U1 · U2 · U3 |
| **Système réel** | Caps `Extraction` / `Transport` / `Construction` |

### Beat 5 — Extraction Timber → Stock A (T1 · T2 · T4 · T9)

| | |
| --- | --- |
| **Investisseur voit** | U1 travaille près de Stock A ; quantité Timber A augmente |
| **Démonstrateur fait** | Montre que la ressource s’appelle **Timber** (PE), pas Wood legacy |
| **Change visuellement** | Remplissage Stock A |
| **Système réel** | Extract + `OperationalResourceKey=Timber` → `Deposit` Stock A (`LinkedPitStockId`) |

### Beat 6 — Transport A → B (T4 · T9)

| | |
| --- | --- |
| **Investisseur voit** | U2 charge à A, se déplace, dépose à B |
| **Démonstrateur fait** | Insiste sur le trajet physique (pas un transfert magique) |
| **Change visuellement** | A diminue · cargo · B augmente |
| **Système réel** | `Withdraw` A → cargo → `Deposit` B |

### Beat 7 — Construction → Complete (T7 · T9)

| | |
| --- | --- |
| **Investisseur voit** | U3 agit sur le chantier ; jalon « Complete » |
| **Démonstrateur fait** | Distingue **Achevé** ≠ **En service** |
| **Change visuellement** | Indicateur Complete allumé |
| **Système réel** | Build Construction → `MarkConstructionComplete` · pas de coût inventé |

### Beat 8 — En service (T7)

| | |
| --- | --- |
| **Investisseur voit** | Indicateur En service s’allume |
| **Démonstrateur fait** | Rappelle la règle : Complete **et** Stock B Timber > 0 |
| **Change visuellement** | Résultat / service visible ; Timber reste dans B |
| **Système réel** | `GardenFervorRefreshCohortServiceState` · pas de consommation auto |

### Beat 9 — Observabilité (T8) + preuve complète (T9)

| | |
| --- | --- |
| **Investisseur voit** | Lecture claire Stock A / Stock B / Complete / EnService |
| **Démonstrateur fait** | Affiche le snapshot PE (ou log C6) |
| **Change visuellement** | Overlay diagnostic (futur) ou console structurée |
| **Système réel** | Helpers C6 · `GetAvailable` live · smoke `gf.Project.SmokeCohortS3` |

---

## Mapping tranche → événement démo

| Tranche | Événement visible |
| --- | --- |
| T1 | Mot / clé **Timber** sur les stocks PE |
| T2 | Tâche Extract/Haul paramétrée (ResourceKey), pas branche « if bois » |
| T3 | Trois rôles U1/U2/U3 |
| T4 | Deux stocks distincts A et B |
| T5 | WorkSite prêt sans modifier le terrain |
| T6 | Intention → Project |
| T7 | Complete puis En service (deux états) |
| T8 | Lecture PE incontestable |
| T9 | Enchaînement bout-en-bout sans raccourci |

---

## Ce que la démo ne montre pas (volontairement)

- Terraform / Cas B
- Forêt complète / arbres finaux
- Économie legacy Wood / HUD FWSG comme vérité
- Multiplayer, save, écologie, UI produit finale
