# GardenFervor — Investor Demo

**Étape actuelle :** **5 — VALIDÉ** (démonstration racontable)  
**Statut :** P0 VALIDÉ · étapes 3–5 VALIDÉES · cinématique / assets finaux / Case B **non démarrés**  


**Preuve gameplay sous-jacente :** cohorte S3 Cas A · Roadmap **T1→T9 = 9/9 VALIDÉ (100 %)** · Design Gate / Roadmap T1→T9 **inchangés**  
**Dépôt :** `C:\Users\sahel\Documents\Unreal Projects\GardenFervor` · remote `https://github.com/JosephV01/GardenFervor.git`  
**Scène Unreal :** `/Game/GardenFervor/InvestorDemo/L_InvestorDemo_S3`  
**Runtime Demo :** `AGardenFervorInvestorDemoGameMode` + `AGardenFervorInvestorDemoPlayerController` (opérationnel)  
**Binding map :** `DefaultEngine.ini` → `GameModeMapPrefixes` Prefix=`L_InvestorDemo` · `AGardenFervorGameMode` (Island) **inchangé**

---

## 1. Objectif

Préparer une **démonstration interactive courte** destinée aux investisseurs, montrant visuellement la preuve fonctionnelle S3 Cas A déjà validée (`gf.Project.SmokeCohortS3` → `ok=1`).

La démo doit, à terme :

- s’appuyer sur les **vrais systèmes GardenFervor** (T1→T9) ;
- n’utiliser des **placeholders que pour le rendu** ;
- rester **indépendante** de la production gameplay quotidienne ;
- être **réutilisable**, **évolutive** et **remplaçable** par de vrais assets sans refaire la logique.

---

## 2. Public visé

| Public | Besoin |
| --- | --- |
| Investisseurs / partenaires | Comprendre la boucle RTS en quelques minutes, sans lire le C++ |
| Fondateur / démonstrateur | Enchaîner un scénario fiable et répétable |
| Équipe | Remplacer progressivement les placeholders sans casser la démo |

---

## 3. Principe architectural obligatoire

```text
Investor Demo
      ↓
présentation visuelle (placeholders → assets)
      ↓
vrais systèmes GardenFervor T1→T9
```

**Interdit :** simulation parallèle / seconde économie / miroir de Timber.

Les placeholders sont des **éléments visuels**.  
Ils ne deviennent jamais une autorité gameplay.

---

## 4. Séparation d’avec le gameplay

| Zone | Rôle |
| --- | --- |
| `Source/GardenFervor/…` · systèmes T1→T9 | **Autorité** gameplay |
| `Plan de production/Roadmap/` | **SoT** production · **9/9 VALIDÉ** |
| `GardenFervor_DesignGate_React/` | Conception — **non modifié** |
| `Investor Demo/` | Documentation / présentation |
| `Content/GardenFervor/InvestorDemo/` | Scène + matériaux placeholders (visuel) |

---

## 5. Structure

```text
Investor Demo/                          ← documentation (Git)
├── README.md
├── Documentation/
├── Presentation/
├── Scenes/
└── Placeholders/

Content/GardenFervor/InvestorDemo/      ← assets Unreal versionnés (Git)
├── L_InvestorDemo_S3.umap
└── Materials/
    ├── MI_DemoGround.uasset
    └── MI_PH_*.uasset
```

### Reproductibilité (étape 2B)

```text
GitHub → clone/checkout → ouvrir L_InvestorDemo_S3
```

Dépendances moteur uniquement : `/Engine/BasicShapes/*` + `BasicShapeMaterial` (fournis par UE).  
Aucun script Python, aucun asset hors `InvestorDemo/` requis pour ouvrir la scène visuelle.
---

## 6. Étape 2 — VALIDÉE

| Champ | État |
| --- | --- |
| Scène | `/Game/GardenFervor/InvestorDemo/L_InvestorDemo_S3` |
| Validation visuelle | **Confirmée** (humain) |
| Chaîne lisible | Intention → Project → WorkSite → U1 → Stock A → U2 → Stock B → U3 → En service |
| Placeholders | Présents (BasicShapes + labels) |
| Gameplay T1→T9 | **Non branché** |
| Script générateur temporaire | **Supprimé** (`create_investor_demo_level.py`) — scène conservée |

### Polish futur (non bloquant)

Certains `TextRender` apparaissent **inversés** selon la vue caméra actuelle.  
Enregistré pour une étape ultérieure — **non corrigé** à la clôture étape 2.

---

## 6bis. P0 — isolement runtime = VALIDÉ

| Champ | État |
| --- | --- |
| Statut | **VALIDÉ** |
| Validation humaine PIE | **Confirmée** — scène lisible · placeholders présents · boot legacy absent |
| GameMode Demo | `AGardenFervorInvestorDemoGameMode` opérationnel |
| PlayerController Demo | `AGardenFervorInvestorDemoPlayerController` |
| GameMode Island | `AGardenFervorGameMode` **inchangé** |
| Absents observés | TC · Worker · ResourceNodes · HUD FWSG · Ages · BuildMenu · LevelPad |
| T1→T9 / Design Gate / Roadmap | **Inchangés** |
| Étape 3 | **VALIDÉ** (voir §12) |
| Étape 4 | **VALIDÉ** (voir §14) |
| Étape 5 | **VALIDÉ** (voir §15) |

---

## 7. Scénario T1→T9 (résumé)

Voir `Documentation/SCENARIO_T1_T9.md`. Disposition : `Placeholders/LAYOUT.md`.

| Temps | Visible | Tranche |
| --- | --- | --- |
| Intention → Project | Marqueurs Draft | T6 |
| Analyse / WorkSite prêt | Zone AlreadyReady | T5 |
| U1 / U2 / U3 | Caps Extraction / Transport / Construction | T3 |
| Timber A → B | Stocks PE | T1 · T2 · T4 · T9 |
| Complete → En service | Deux états | T7 |
| Lecture PE | Overlay futur | T8 · T9 |

---

## 8. Placeholders

Intention · Project · WorkSite · U1 · U2 · U3 · Stock A · Stock B · En service · HUD réservé

Couleurs = **visuel seul**, jamais vérité gameplay.

---

## 9. Remplacement progressif

```text
Placeholder → Mesh démo → Asset temporaire → Asset final
```

Sans changer l’autorité PhysicalEconomy ni les contrats T1→T9.

---

## 10. Relation avec la Roadmap

Roadmap gameplay = SoT · **reste 9/9 VALIDÉ**.  
Investor Demo ≠ seconde Roadmap.  
Statuts T1→T9 **non modifiés** par cette démo.

---

## 11. Règles de maintenance

1. Logique = systèmes gameplay + validation humaine.
2. Visuel = ce dossier + `Content/GardenFervor/InvestorDemo/`.
3. `LinkedPitStockId` = Stock A PE · ne pas renommer.
4. Preuve fonctionnelle S3 : PIE `gf.Project.SmokeCohortS3` → `ok=1`.
5. Design Gate : aucune modification via Investor Demo hors ordre explicite.

---

## 12. Étape 3 — VALIDÉE

| Champ | État |
| --- | --- |
| Statut | **VALIDÉ** |
| Objectif | Brancher `L_InvestorDemo_S3` sur le vrai parcours S3 Cas A |
| Déclenchement | Bouton **LANCER LA DÉMONSTRATION** · **F8** · `gf.InvestorDemo.RunS3` |
| Parcours | Intention→Project→Analyze→WorkSite AlreadyReady→U1 Extract Timber→A→U2 Haul→B→U3 Complete→En service |
| Présentation | Async (`AGardenFervorInvestorDemoS3Director`) · PH_* sur Landscape · labels face caméra · U1/U2/U3 différenciés · déplacements réels |
| Autorité | Project / Task / UnitTaskAgent / PhysicalEconomy (**pas de miroir**) |
| Terraform | **Aucun** — Case A site déjà prêt |
| Mobilité PH_/LBL_ | Warnings Movable corrigés (présentation ciblée) |
| Validation technique | `ok=1 · PeakA=1.0 · A=0.0 · B=1.0 · Complete=1 · EnService=1 · PE live` |
| Validation humaine PIE | **PASS** |

Pont code : `FGardenFervorInvestorDemoS3Bridge` + `AGardenFervorInvestorDemoS3Director` (`Source/GardenFervor/Game/`).

## 13. Prochaines étapes

Étape 5 clôturée.  
Étapes ultérieures (cinématique / assets finaux / Terraform Case B) : **non démarrées**.

## 14. Étape 4 — VALIDÉE

| Champ | État |
| --- | --- |
| Statut | **VALIDÉ** |
| Objectif | Présentation investisseur lisible sans changer le parcours T1→T9 |
| Caméra | Guidée (focus interpolé sur les beats / unités / stocks) |
| Beats 1–10 | Intention · Projet · Analyse · WorkSite · Extraction · Transport · Stock B · Construction · Achevé · En service |
| UI | Overlay léger `UGardenFervorInvestorDemoPresentationWidget` — carte **haut-gauche** compacte (~320 px) |
| Overlay final | Scène dominante · N/10 + pastilles + PE `A/B/C/S` + statut / `EN SERVICE` |
| Rythme | Pauses Intention / Projet / Analyse / WorkSite / spawn + hold conclusion |
| Conclusion | Vue d’ensemble + indicateur En service |
| Autorité | Inchangée — APIs T1→T9 réelles · **pas de simulation** |
| Terraform | **Aucun** — Case A |
| Validation humaine | **PASS** (après correctif overlay) |

Gameplay S3 / T1→T9 / Design Gate / Roadmap / `GardenFervorIsland` : **inchangés**.

## 15. Étape 5 — VALIDÉE

| Champ | État |
| --- | --- |
| Statut | **VALIDÉ** |
| Objectif | Démonstration racontable pour non-technicien (sans changer T1→T9) |
| Narration | Intention → projet → analyse → chantier prêt → unités autonomes → ressources → Achevé → En service |
| Cause / action / résultat | Statuts overlay + labels monde orientés résultat (sans jargon API) |
| Autonomie | Mise en évidence U1/U2/U3 · « pas de pilotage manuel » |
| Déclenchement | Bouton **LANCER LA DÉMONSTRATION** → `RunS3CasA` (identique F8 / console) |
| Bouton | Visible au démarrage · bas-centre · masqué après lancement · **one-shot** · pas de replay |
| Overlay | Compact haut-gauche conservé (étape 4) |
| Autorité | APIs T1→T9 réelles · **pas de simulation** |
| Terraform | **Aucun** — Case A |
| Validation humaine | **PASS** |

Gameplay S3 / T1→T9 / Design Gate / Roadmap / `GardenFervorIsland` : **inchangés**.
