# C-01 — Terrain runtime (vérité hauteur / shipping)

| Champ | Valeur |
| --- | --- |
| **ID** | C-01 |
| **Nom** | Terrain runtime (vérité hauteur / shipping) |
| **Statut documentaire** | Rédigé — **en attente d’audit et de validation** (non VALIDÉ) |
| **Profondeur** | Fondamentale (registre) |
| **Ordre de rédaction** | 1 |
| **Bloquant** | Oui (F1 shipping · vérité terrain · Cas B durable) |
| **Références** | Registre C-01 · DG-08 / 00.5.G* / 00.5.S4 / 00.6.A2 · REGLES §4 · ODC-F1 / F8 |

Ce document formalise les **décisions C-01 validées**.  
Il n’invente aucune règle de gameplay supplémentaire.  
Il ne constitue pas encore une règle officielle tant qu’il n’est pas **VALIDÉ** dans le suivi.

---

## 1. Objet

C-01 définit le contrat opérationnel du **relief du terrain** en runtime :

- quelle donnée fait autorité pour la hauteur ;
- ce qu’une modification réussie garantit ;
- la relation entre vérité terrain et affichage ;
- les frontières avec les systèmes consommateurs et voisins.

C-01 ne définit pas l’autonomie des unités, la préparation de site, ni la sémantique écologique.

---

## 2. Décisions validées (source de vérité)

Les quatorze décisions suivantes sont reprises **sans modification** :

| # | Décision |
| --- | --- |
| D1 | `RuntimeTerraformStore` est l’autorité de la hauteur du terrain. Les autres systèmes gameplay lisent cette vérité. Le Landscape / affichage ne constitue pas une seconde vérité. |
| D2 | `ApplyBrushAt()` retourne `true` uniquement si la modification réelle du terrain dans le Store a été effectuée. Les traitements ultérieurs ne conditionnent pas ce retour. |
| D3 | Shipping : le résultat attendu est un terrain modifié de manière fiable **et visible** en jeu. Le contrat n’impose **aucune** solution technique de présentation particulière. |
| D4 | C-01 gère uniquement le **relief** du terrain. Eau, sol, végétation, écologie et autres conséquences appartiennent à leurs propres systèmes. |
| D5 | Toute modification réelle du relief doit être **signalée** aux systèmes concernés. C-01 ne décide pas de leur réaction. |
| D6 | Si le terrain réel est correctement modifié mais que l’affichage tarde à suivre, la modification reste réelle. L’affichage doit ensuite revenir en conformité. |
| D7 | C-01 ne décide pas si une opération est autorisée par le gameplay. Cette décision appartient aux systèmes demandeurs. |
| D8 | Il doit être possible de vérifier qu’une modification a eu lieu, où, et de quelle manière elle a modifié le terrain. Pas de système complet d’historique dans C-01. |
| D9 | C-01 impose uniquement ses limites techniques de sécurité. Les limites et règles de gameplay sont définies ailleurs. |
| D10 | Une modification est considérée comme réalisée lorsque la vérité terrain est correctement enregistrée. L’affichage peut être synchronisé ensuite. |
| D11 | C-01 ne gère pas actuellement les déblais/remblais comme ressources. Le contrat préserve seulement la possibilité d’une gestion future. |
| D12 | Le terrain doit pouvoir être sauvegardé. La responsabilité sauvegarde/chargement appartient à **C-19**, pas à C-01. |
| D13 | Opérations métier distinguées : **Creuser**, **Remblayer**, **Aplanir**. C-01 ne définit pas leurs règles métier détaillées. |
| D14 | C-01 peut conserver des informations techniques de peinture du terrain. C-01 ne définit pas leur signification gameplay (sol, fertilité, biome, etc.). |

---

## 3. Responsabilités

### 3.1 Ce que C-01 garantit

1. **Autorité hauteur (D1)**  
   La hauteur gameplay du terrain est celle du `RuntimeTerraformStore` (base + delta, selon le modèle de stockage).  
   Tout système gameplay qui a besoin de la hauteur lit cette autorité (directement ou via une API qui l’expose sans la remplacer).

2. **Succès d’écriture (D2, D10)**  
   Une API d’application de modification de relief (`ApplyBrushAt` ou équivalent) retourne succès **si et seulement si** la vérité Store a été effectivement mise à jour.  
   La synchronisation d’affichage, le rafraîchissement de collision visuelle, ou d’autres traitements aval **ne conditionnent pas** ce succès.

3. **Signalement (D5)**  
   Après toute modification réelle du relief, C-01 émet un signal aux systèmes concernés (périmètre, nature géométrique).  
   C-01 ne prescrit pas le traitement de ce signal.

4. **Observabilité minimale (D8)**  
   Il est possible, sans historique complet, de constater :
   - qu’une modification a eu lieu ;
   - où (localisation / emprise) ;
   - de quelle manière le relief a changé (ex. delta de hauteur mesurable sur la zone).

5. **Support technique peinture (D14)**  
   C-01 peut stocker des données techniques de peinture associées au terrain.  
   Ces données n’ont **pas** de sémantique gameplay définie par C-01.

6. **Capacité à être persisté (D12)**  
   L’état du relief (et données techniques associées gérées par C-01) doit être **persistable**.  
   Qui déclenche save/load et quand = **C-19**.

7. **Préservation matière future (D11)**  
   C-01 n’introduit pas aujourd’hui de production de ressources déblai/remblai.  
   Rien dans C-01 n’interdit qu’un système ultérieur calcule de la matière à partir des modifications de relief.

### 3.2 Ce que C-01 ne garantit pas

| Non-garantie | Appartenance |
| --- | --- |
| Autorisation gameplay d’une opération (qui peut creuser, quand, pourquoi) | Demandeurs (C-05, C-07, C-08, outils joueur, etc.) — D7 |
| Règles métier Creuser / Remblayer / Aplanir (objectifs, fin, qualité, volume métier) | Contrats / systèmes demandeurs — D13 |
| Réaction au dirty (replanification, invalidation chantier, sim eco) | C-02, C-05, C-08, C-15… — D5 |
| Signification gameplay de la peinture (sol, fertilité, biome) | Hors C-01 — D14 |
| Eau, sol, végétation, écologie | C-15, C-16, C-17, … — D4 |
| Politique de sauvegarde / chargement de partie | C-19 — D12 |
| Gestion actuelle des déblais/remblais comme ressources | Hors C-01 (avenir possible) — D11 |
| Choix d’une technologie d’affichage particulière (PMC, LandscapeEdit, matériau, etc.) | Hors obligation C-01 — D3 |
| Instantanéité visuelle | Affichage peut suivre après coup — D6, D10 |
| Historique complet des opérations | Hors C-01 — D8 |
| Limites / coûts / hard gates gameplay de terrain | Ailleurs (DG / contrats demandeurs) — D9 |

---

## 4. Planes : vérité, affichage, consommateurs

```text
Demandeur (C-05 / C-07 / C-08 / outil…)
        │  demande une modification (déjà autorisée côté gameplay)
        ▼
┌───────────────────────────┐
│ C-01 — vérité relief      │  RuntimeTerraformStore = autorité hauteur
│ enregistrement Store      │  succès = Store mis à jour
│ signal aux concernés      │
└───────────┬───────────────┘
            │
            ├──────────────► Affichage / Landscape / M4 (C-23 / présentation)
            │                 doit converger ; n’est PAS une seconde vérité
            │
            └──────────────► Consommateurs gameplay
                              (C-02 Spatial, unités, SitePrep, etc.)
                              lisent le Store (ou API dérivée)
```

| Plane | Rôle | Vérité ? |
| --- | --- | --- |
| **Store (C-01)** | Hauteur (et données techniques paint) | **Oui — autorité** |
| **Affichage** | Rendre le relief (et paint technique) visible | Non — doit suivre D6/D10 |
| **Consommateurs** | Lire la hauteur / réagir aux signaux | Non — ne redéfinissent pas la hauteur |

**Shipping (D3) :** en jeu livré, le joueur doit pouvoir constater un terrain réellement modifié **et** visible.  
Le moyen technique d’obtenir cette visibilité n’est **pas** imposé par C-01.

---

## 5. Entrées / sorties

### 5.1 Entrées (vers C-01)

| Entrée | Description | Qui décide |
| --- | --- | --- |
| Localisation / emprise | Où appliquer la modification | Demandeur |
| Intention de relief | Creuser / Remblayer / Aplanir (D13) ou paramètres techniques équivalents | Demandeur (règles métier hors C-01) |
| Paramètres techniques | Amplitude, rayon, etc., dans les limites de sécurité C-01 | Demandeur + limites D9 |
| Données paint techniques (optionnel) | Couches / poids techniques | Demandeur ; sémantique hors C-01 (D14) |

C-01 **ne valide pas** l’autorisation gameplay (D7).  
Si le demandeur appelle C-01, C-01 applique (sous réserve de limites techniques D9).

### 5.2 Sorties (depuis C-01)

| Sortie | Description |
| --- | --- |
| Succès / échec | `true` ↔ Store effectivement modifié (D2) |
| État Store mis à jour | Nouvelle vérité hauteur (± paint technique) |
| Signal de modification | Notification aux systèmes concernés (D5) |
| Observabilité | Preuve minimale : fait / lieu / nature du changement (D8) |

### 5.3 Échecs techniques (indicatif)

Échec (`false`) lorsque la vérité Store **n’a pas** pu être mise à jour, par exemple :

- store non initialisé / non prêt ;
- coordonnées hors domaine terrain ;
- limite technique de sécurité refusant l’écriture (D9).

L’échec d’un traitement d’affichage **ne convertit pas** un succès Store en échec (D2, D6, D10).

---

## 6. Opérations de relief (D13)

| Opération métier | Rôle dans C-01 |
| --- | --- |
| **Creuser** | Intention de baisse de relief — C-01 applique le changement de hauteur correspondant quand demandé |
| **Remblayer** | Intention de hausse de relief — idem |
| **Aplanir** | Intention de mise à niveau / aplanissement — C-01 peut appliquer les écritures de hauteur nécessaires ; les critères métier de « assez plat » sont hors C-01 |

C-01 **ne définit pas** :

- quand ces opérations sont requises ;
- les critères de fin métier ;
- la décomposition en plusieurs pulses ;
- la coopération d’unités.

Ces sujets appartiennent notamment à **C-05**, **C-07**, **C-08**.

---

## 7. Peinture technique (D14)

- C-01 **peut** conserver des buffers / poids / indices de couches techniques.
- C-01 **ne décide pas** qu’une peinture = type de sol, fertilité, biome, eau, etc.
- Toute sémantique gameplay de surface relève d’autres contrats (notamment C-02 / C-16 / C-17 selon leur périmètre).

---

## 8. Notification (D5)

Après modification réelle du Store :

1. C-01 signale qu’une zone de relief a changé (emprise / canaux géométriques pertinents).
2. Les destinataires (ex. substrat spatial C-02) décident seuls de leur réaction.
3. C-01 **ne dirty pas « à la place »** des couches eau/sol/végétation comme vérité écologique : ces couches ne sont pas sa responsabilité (D4).  
   *(Si un signal géométrique déclenche plus tard une invalidation eco, c’est le contrat du système eco / C-02 qui le définit.)*

---

## 9. Limites techniques (D9)

C-01 peut refuser une écriture pour des raisons **techniques de sécurité** uniquement, par exemple :

- domaine spatial invalide ;
- store non prêt ;
- paramètres numériquement dangereux pour l’intégrité du store.

C-01 **n’applique pas** :

- hard gates de mobilité ;
- coûts ;
- permissions d’âge / tech ;
- règles de chantier.

---

## 10. Persistance (D12)

| Responsabilité | Contrat |
| --- | --- |
| État relief (et paint technique C-01) **persistable** | C-01 (capacité des données) |
| Quand / quoi sauvegarder / charger / migrer | **C-19** |

C-01 ne définit pas la politique de save de partie.

---

## 11. Frontières

| Contrat | Frontière |
| --- | --- |
| **C-02** | Cellules, queries, sémantique dirty hors relief pur ; lit la hauteur via l’autorité C-01 |
| **C-05** | SitePrep / `bSiteReady` / Cas A·B — décide *si* le relief doit être modifié pour un site ; n’est pas l’autorité hauteur |
| **C-07** | Agent (InstantMode, Execute/Verify) — demandeur d’écriture ; rythme hors C-01 |
| **C-08** | Terraformer opérationnel — décomposition spatiale, fin de grade, coopération ; consomme C-01 |
| **C-15…C-17** | Eau / sol / végétation — conséquences hors relief |
| **C-19** | Sauvegarde / chargement |
| **C-23** | Présentation M4 / UDS — affichage ; jamais vérité hauteur |
| **C-00** | Cadre fondateur (amont conceptuel) |

**Case B :** hors périmètre d’implémentation de ce document. Case B reste suspendu. C-01 fournit seulement les garanties monde nécessaires lorsque Case B sera repris.

---

## 12. Invariants

1. Une seule autorité hauteur gameplay : le Store (D1).  
2. Succès d’écriture ≡ Store modifié (D2).  
3. Affichage retardé ≠ annulation de la modification (D6, D10).  
4. C-01 ne porte pas la sémantique eco ni l’autorisation gameplay (D4, D7).  
5. Creuser / Remblayer / Aplanir sont les intentions métier de relief reconnues ; leurs règles détaillées sont ailleurs (D13).

---

## 13. Critère minimal de suffisance du contrat

Ce contrat est considéré **suffisant pour validation documentaire** lorsque :

- les planes Store / affichage / consommateurs sont sans ambiguïté ;
- le succès `ApplyBrushAt` (ou équivalent) est défini comme en D2 ;
- les non-responsabilités (eco, autorisation, save, métier Terraformer) sont explicites ;
- shipping exige relief fiable **et** visible sans figer une techno (D3) ;
- aucune règle gameplay nouvelle n’a été introduite hors des 14 décisions.

*(La validation formelle reste une étape séparée dans `00_SUIVI_CONTRATS.md`.)*

---

## 14. Écarts constatés avec l’implémentation actuelle

**Section informative uniquement.**  
Le contrat décrit la règle validée ; l’implémentation actuelle **n’est pas** une preuve de conformité.  
Aucune correction n’est effectuée ici.

| # | Écart | Preuve actuelle | Décision contractuelle |
| --- | --- | --- | --- |
| E1 | `ApplyBrushAt` retourne `bStoreOk \|\| bLandscapeOk` | `GardenFervorLandscapeTerraformSubsystem.cpp` | D2 : succès = Store seulement |
| E2 | `GroundUtils` lit le Store **seulement** si overlay runtime actif ; sinon traces Landscape | `GardenFervorGroundUtils.cpp` + `IsUsingRuntimeOverlay()==false` | D1 : gameplay doit lire le Store |
| E3 | Spatial `QueryTerrain` lit déjà le Store | `GardenFervorSpatialSubsystem.cpp` | Aligné D1 pour Spatial ; autres lecteurs non uniformes |
| E4 | Notification dirty inclut Soil \| Water en plus de Terrain \| Slope | `NotifySpatialLandscapeBrush` | D4/D5 : C-01 signale le relief ; sémantique eco hors C-01 — à traiter à l’implémentation / C-02 |
| E5 | Affichage packaged : store mesurable, visual Landscape surtout PIE (F1 INVALIDÉ) | ODC-F1 INVALIDÉ · ODC-F8 · ETAT | D3 : shipping doit être visible — écart ouvert (pas de techno imposée) |
| E6 | Persistance terrain désactivée ; `LoadRuntimeTerraform` skip | Settings + code | D12 : persistable + responsabilité C-19 — capacité/politique encore ouvertes |
| E7 | Enum technique `Raise` / `Lower` / `Paint` ; Compact = alias Lower côté agent | Types + `UnitTaskAgent` | D13 : Creuser / Remblayer / Aplanir = intentions métier ; mapping technique hors invention C-01 |
| E8 | Vocabulaire doc/code « Raise/Lower/Paint » vs décisions « Creuser/Remblayer/Aplanir » | DG-08 · code · décisions C-01 | **Contradiction lexicale signalée** — non arbitrée ici ; C-01 conserve les termes métier décidés (D13) ; le mapping technique reste à l’implémentation sans changer D13 |

---

## 15. Hors périmètre explicite

- Toute modification de Case B, Investor Demo, Design Gate, ou code.
- Rédaction de C-02 ou contrats aval.
- Choix d’architecture F1 (matériau, RT, etc.).
- Définition des règles Terraformer / SitePrep.

---

*Fin C-01 — document rédigé, non VALIDÉ.*
