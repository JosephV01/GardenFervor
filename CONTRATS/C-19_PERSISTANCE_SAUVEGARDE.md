# C-19 — Persistance / sauvegarde

| Champ | Valeur |
| --- | --- |
| **ID** | C-19 |
| **Nom** | Persistance / sauvegarde |
| **Statut documentaire** | **VALIDÉ** — validation humaine explicite ; audit final PASS ; contrat de conception uniquement ; points ouverts O5, P8, Q7, R5 et R1–R8 / R11 conservés |
| **Profondeur** | Fondamentale (registre) |
| **Ordre de rédaction** | 19 |
| **Nécessité** | Requise |
| **Bloquant** | Oui — avant shipping / F1 redo **durable** (registre · S9). C-19 **n’est pas** la reprise F1 |
| **Dépendances amont (registre)** | **C-01** · **C-09** · **C-03** — C-01 est **VALIDÉ** ; C-09\* et C-03\* demeurent addenda **fermés** (S6) |
| **Voisinage opérationnel** | **C-02** (Dirty hors save, B5) · **C-08** (états de reprise, K2) · **C-11** (invariant réservations, F1) · **C-12** (chargements / transit, G2) · **C-14** (lifecycle, mécanisme) · **C-15** / **C-16** / **C-17** (O5 / P8 / Q7 ouverts) · **C-18** (R5 ouvert) · **C-20** (UX, **VALIDÉ** conception) · **C-21** (fréquences, non commencé) |
| **Références** | Registre C-19 · `REGLES_PROJET` session-only / persist OFF / F1 INVALIDÉ · C-01 D12 / D14 / E6 · C-02 B5 · C-08 K2 · C-11 F1 · C-12 G2 · C-14 · C-15 O5 · C-16 J1 / P8 · C-17 Q7 · C-18 R5 / Q30 · cadrage C-19 S1–S14 · L1–L3 |

Ce document formalise le **cadrage persistance / sauvegarde déjà accepté** (décisions humaines S1–S14 et L1–L3).  
Il n’invente aucune règle supplémentaire.  
Il constitue la **règle officielle de conception** C-19 après validation humaine explicite.  
La clôture est **documentaire**. Elle **n’autorise pas** l’implémentation runtime (flags, SaveGame, chargement, F1), ni le démarrage de C-20 ou C-21.

Trois plans sont **distingués** partout dans ce contrat :

1. **Politique cible** — ce que GardenFervor doit concevoir comme sauvegarde du monde.  
2. **Comportement actuel vérifié** — ce que le dépôt fait aujourd’hui.  
3. **Travaux d’implémentation futurs** — non autorisés par ce `VALIDÉ` documentaire (S2).

**Case B** demeure **suspendu**.  
**ODC-F9** n’est **pas** démarré.  
**C-20** est **VALIDÉ** comme contrat de **conception** (UX save non implémentée). **C-21** demeure **non commencé** (S14).  
**C-15**, **C-16**, **C-17** et **C-18** demeurent **VALIDÉ** comme contrats de **conception**. Leurs points **O5**, **P8**, **Q7**, **R5** et **R1–R8 / R11** restent **ouverts** et **inchangés**.  
Les addenda C-03\* · C-06\* · C-09\* · C-10\* · C-13\* restent **fermés**.  
S3 / Investor Demo restent **hors** exigence de sauvegarde monde (S13).

---

## 1. Identité et finalité

C-19 est le contrat de la **politique de persistance / sauvegarde** de GardenFervor (S1).

Le titre canonique est **Persistance / sauvegarde**.  
Le rôle, repris du registre, est :

```text
ce qui est persisté · migration · session-only
```

C-19 dit **quelles familles** peuvent entrer dans une sauvegarde, **quel régime** s’applique (session-only / durable), **quels principes** de migration et **quelles familles de déclenchement** existent.  
Il **ne possède pas** les règles métier des familles. Les propriétaires restent les contrats qui les définissent (S3).

Niveau de garantie de ce contrat :

- formaliser le **périmètre** et les **frontières** ;  
- rendre auditable ce que C-19 **porte**, ne possède pas, et n’active pas ;  
- conserver **ouverts** les points non arbitrés ;  
- **ne pas** figer schéma de slot, code SaveGame, Hertz, écran, catalogue Ages, ResourceKey, ni API C++.

Les identifiants **S1–S14** et **L1–L3** ci-dessous sont le **cadrage accepté**, pas un second Design Gate.

---

## 2. Référentiel des décisions utilisées

### 2.1 Cadrage accepté (questionnaire C-19 — pas de nouvelle conception)

| # | Contenu accepté |
| --- | --- |
| **S1=A** | Titre et rôle du registre, tels quels. |
| **S2=A** | Un futur `VALIDÉ` = **conception documentaire seulement**. Flags, SaveGame, chargement, F1 : **autorisation distincte**. |
| **S3=B** | Politique **monde** organisée par **familles**. Pas de transfert de propriété des règles métier. |
| **S4** | **T, R, L, I** retenus dans la politique cible. **E** et **X** **conditionnels** à la définition et à la validation par leurs contrats propriétaires. **P** et **K** **exclus**. |
| **S5=A** | Dirty C-02 = session, **hors** sauvegarde monde. C-19 n’y déroge pas. |
| **S6=A** | Citer C-03\* et C-09\* **sans** rouvrir. C-10\* et C-13\* restent fermés. |
| **S7=C** | **Hybride** : session-only **aujourd’hui** ; persistance durable = **cible de conception** shipping ; **sans** activation technique. |
| **S8=A** | Familles de déclenchement seulement. **Aucune** cadence, temporisation ou UX. |
| **S9=A** | Persistance durable **bloquante** pour le shipping / F1 durable. Reprise F1 = travail **distinct**. |
| **S10=A** | Une persistance **future** de recherche / tech / schéma relèverait de C-19 **uniquement** dans le cadre autorisé par C-18. **R5 reste ouvert**. Pas de catalogue, Ages, DG-07, ni remplacement de `RequiredAge`. |
| **S11=B** | Principe : versionner ; refuser une sauvegarde incompatible. **Pas** de schéma concret ni de code. |
| **S12=B** | Interdit de présenter le chemin actuel comme une sauvegarde monde **opérationnelle** tant que le flag est désactivé et que le chargement est désactivé. |
| **S13=A** | S3 / Investor Demo **hors** exigence de sauvegarde monde. |
| **S14=A** | UX sauvegarde = **C-20**. Fréquences / temporisations = **C-21**. C-19 ne les ouvre pas. |
| **L1** | Exclusions §19. |
| **L2** | « Sauvegarde du monde » = snapshot autoritatif des familles **admises** et **effectivement définies** par leurs propriétaires (§4.2). |
| **L3** | Écarts documentaires et techniques recensés §20 — signalés, non corrigés ici. |

### 2.2 Contrats amont et voisins déjà VALIDÉS (lus, non réécrits)

| Source | Reprise pour C-19 |
| --- | --- |
| **C-01 D12** | Le relief doit pouvoir être sauvegardé. Save / load / migrer = **C-19**. C-01 porte la **capacité** persistable, pas la politique. |
| **C-01 D14** | Paint technique C-01 ≠ sol / fertilité / biome. |
| **C-01 E6** | Persist terrain désactivée ; `LoadRuntimeTerraform` skip. C-01 constate encore capacité / politique ouvertes. C-19 est `VALIDÉ` comme **règle de conception** ; ce n’est **pas** une activation du code. |
| **C-02 B5** | Dirty = runtime / session ; **hors** sauvegarde monde. |
| **C-08 K2** | C-08 définit les **états d’opération** nécessaires à une reprise cohérente. La persistance reste au système compétent (**C-19** notamment). **Pas** une famille S4 supplémentaire. |
| **C-11 F1** | Avant reprise des effets : réservations **restaurées ou réacquises**, puis **vérifiées**. Invariant = C-11. Mécanisme = C-19. |
| **C-12 G2** | Données logistiques à préserver (chargements, transit). Mécanisme = C-19. Ni duplication ni perte fictive. Aucune sauvegarde complète opérationnelle **sans preuve**. |
| **C-14** | Mécanisme de sauvegarde = C-19. C-14 n’est pas absorbé. |
| **C-15 O5** | Persistance de l’état eau = politique C-19. **O5 reste ouvert.** |
| **C-16 J1 / P8** | Capacité persistable à préserver. Politique = C-19. **P8 reste ouvert.** |
| **C-17 Q7** | Persistance de l’état écologique = politique C-19. **Q7 reste ouvert.** |
| **C-18 R5 / Q30** | Persistance recherche / tech / schéma = C-19. **R5 reste ouvert.** Un `VALIDÉ` C-18 reste documentaire. |

C-04 et C-05 **n’ont pas** de flèche C-19. Ce contrat **n’invente pas** de famille tâches / SitePrep.

---

## 3. Portée d’un `VALIDÉ` (S2)

Ce contrat est **`VALIDÉ`**. Il reste un **contrat de conception**.

Un `VALIDÉ` C-19 **n’autorise pas**, à lui seul :

- d’activer `bEnableRuntimeTerraformPersistence` ;  
- de rendre `SaveRuntimeTerraform` / `LoadRuntimeTerraform` opérationnels ;  
- de reprendre ODC-F1 ;  
- d’implémenter une sauvegarde monde ;  
- d’ouvrir C-20 ou C-21 ;  
- de fermer O5, P8, Q7, R5 ou R1–R8 / R11 ;  
- de modifier le Design Gate, `designGate.js`, DG-07, Ages, `RequiredAge` ou `08.2`.

Toute implémentation exigerait une **autorisation distincte**.

---

## 4. Politique cible — ce qui est persisté

### 4.1 Largeur (S3)

C-19 définit une **politique monde par familles**.

Il nomme les familles **admissibles** dans une sauvegarde du monde.  
Il **n’acquiert pas** leurs règles métier, leurs schémas internes, ni leurs catalogues.

### 4.2 Définition — sauvegarde du monde (L2)

Une **sauvegarde du monde**, au sens C-19, est un snapshot **autoritatif** des familles **admises** par ce contrat **et effectivement définies** par leurs propriétaires, rechargeable **sans perte ni duplication fictive** de ces données (C-12 G2, C-11 F1).

Ce n’est **pas** :

- le Dirty C-02 ;  
- le Landscape / M4 session-only ;  
- l’overlay PMC ;  
- une couche E ou X encore ouverte chez son propriétaire ;  
- les Ages ;  
- une preuve S3 / Investor Demo.

### 4.3 Familles retenues (S4)

| Code | Famille | Rôle C-19 | Propriétaire métier | Limite |
| --- | --- | --- | --- | --- |
| **T** | Relief / paint technique | Politique save / load / migration | **C-01** (capacité D12 / D14) | Paint ≠ sol / biome |
| **R** | Réservations (reprise) | Mécanisme seulement | **C-11** (F1) | Invariant métier inchangé |
| **L** | Chargements / transit | Mécanisme seulement | **C-12** (G2) | Pas de preuve opérationnelle aujourd’hui |
| **I** | Lifecycle infrastructures | Mécanisme seulement | **C-14** | C-14 non absorbé |

Ces quatre familles font partie de la **politique cible**. Leur **implémentation** n’est pas autorisée ici.

### 4.4 Familles conditionnelles (S4, S10)

| Code | Famille | Condition | État actuel |
| --- | --- | --- | --- |
| **E** | Eau / sol / éco | Le propriétaire **définit et valide** un état persistable | **O5, P8, Q7 ouverts** |
| **X** | Recherche / tech / schéma | Cadre **autorisé par C-18** | **R5 ouvert** ; pas de catalogue, Ages, DG-07, `RequiredAge` |

Tant que la condition n’est pas remplie, E et X **n’entrent pas** dans une sauvegarde du monde.  
C-19 peut seulement dire : *si* le propriétaire clôt un état persistable dans son cadre, la **politique** C-19 s’appliquerait.  
Cela **ne ferme pas** O5, P8, Q7 ni R5.

### 4.5 Familles exclues (S4, S6)

| Code | Famille | Motif |
| --- | --- | --- |
| **P** | Projets / intentions | Amont C-03\* **fermé**. C-19 n’invente pas Intention → Project. |
| **K** | Stocks / économie | Amont C-09\* **fermé**. C-19 n’invente pas ResourceKey / stocks. |

P et K restent **exclus** tant que ces dépendances fermées n’ont pas été **régulièrement réexaminées** (autorisation distincte, hors C-19).

C-08 K2 n’ajoute **pas** de lettre S4. C-08 reste propriétaire des états de reprise d’opération ; C-19 resterait le mécanisme, sans catalogue C-08 inventé ici.

---

## 5. Régime temporel (S7)

**Politique cible (hybride) :**

- **Aujourd’hui (conception de l’interim) :** session-only. Les éditions Landscape se restaurent à Stop Play. Ce n’est pas une sauvegarde du monde.  
- **Cible shipping :** persistance **durable** des familles alors admises et définies.  
- **Activation technique :** **aucune** par ce contrat.

Aucun choix S7 ne réactive `SaveRuntimeTerraform` / `LoadRuntimeTerraform`.

---

## 6. Déclenchement (S8)

C-19 retient seulement des **familles de déclenchement** :

- fin de session ;  
- jalon monde ;  
- demande joueur.

Il **ne fixe pas** :

- de secondes, debounce ou Hertz (y compris la valeur technique `2.f` constatée en settings) ;  
- de slot imposé comme règle produit ;  
- d’écran, wording ou flux (C-20) ;  
- de cadence de simulation (C-21).

Ces trois familles ne sont **pas** un catalogue produit exhaustif. C-19 n’en ajoute pas d’autres ici.

---

## 7. Dirty spatial (S5)

C-02 B5 reste la règle : Dirty = état runtime / session ; **hors** sauvegarde du monde.

C-19 **n’y déroge pas**. Persister le Dirty exigerait de **rouvrir C-02**, hors ce contrat.

---

## 8. Addenda fermés (S6)

Amont officiel du registre : **C-01 · C-09 · C-03**.

- **C-01** `VALIDÉ` : cité et utilisé (capacité T).  
- **C-03\*** et **C-09\*** : **cités sans ouvrir**. C-19 peut renvoyer à une donnée *déjà* définie ailleurs ; il n’invente ni Intention → Project ni ResourceKey / stocks.  
- **C-10\*** et **C-13\*** : restent **fermés**.  
- **C-06\*** : reste fermé (voisinage, pas amont C-19).

Réviser l’amont du registre, ou rouvrir un addendum, = **autorisation distincte**.

---

## 9. Shipping et F1 (S9)

La persistance **durable** est **bloquante** pour le shipping (S9).

C-19 **n’est pas** la reprise F1. F1 demeure un travail **distinct**.

Ce `VALIDÉ` C-19 reste **documentaire** et **n’autorise pas** l’implémentation runtime (S2). Ces deux décisions restent **séparées** : S9 ne définit pas une condition de levée du blocage.

F1 demeure **À REFAIRE / INVALIDÉ** (C-01 D3 / E5, `REGLES_PROJET`, `Saved/ODC_F1_RuntimeTerrainGate.txt`).  
Architecture de présentation (PMC, RT, matériau, M4) = **C-01 / F1 redo**, hors C-19.

---

## 10. Recherche / technologie (S10)

Une **éventuelle** persistance future de l’état de recherche / tech / schéma **relèverait** de la politique C-19, **uniquement** dans le cadre que C-18 autorisera.

**R5 reste ouvert.**  
C-19 ne ferme pas R1–R8 ni R11.  
Interdit ici : catalogue nommé, mapping Ages, runtime DG-07, remplacement de `RequiredAge`, mapping Wood ↔ Timber.

---

## 11. Migration (S11)

**Principe seulement :**

- une sauvegarde est **versionnée** ;  
- une sauvegarde **incompatible** est **refusée**.

C-19 **ne définit pas** :

- le schéma de `UGardenFervorTerraformSaveGame` ;  
- le nom de slot `GardenFervorTerraform_Island` comme format cible ;  
- une table de migration v1 → futur ;  
- un code de chargement.

L’existant v1 est une **dette technique** (§13), pas le format officiel.

---

## 12. Chemin actuel — non opérationnel (S12)

Tant que `bEnableRuntimeTerraformPersistence` est **false** et que `LoadRuntimeTerraform` **retourne toujours false**, le chemin C++ **ne doit pas** être présenté comme une sauvegarde monde opérationnelle.

C’est une **règle de présentation / qualification** C-19.  
Elle **ne corrige pas** le C++.

---

## 13. Comportement actuel vérifié

Qualification : **lu dans le dépôt** lors de la rédaction. **≠** politique cible.

| Mécanisme | Qualification |
| --- | --- |
| `UGardenFervorTerraformSaveGame` (version 1, delta hauteur + paint) | **Présent** — seul `USaveGame` constaté |
| `bEnableRuntimeTerraformPersistence` | **false** (défaut C++ ; `REGLES_PROJET` CONVENTION) |
| `SaveRuntimeTerraform` | **Coupé** par le flag |
| `LoadRuntimeTerraform` | **Toujours false** (« persistence OFF » post-reset ODC) |
| Slot `GardenFervorTerraform_Island` | **Présent** en settings — **non** règle C-19 |
| `TerraformSaveDebounceSeconds = 2.f` | **Présent** en settings — constat technique, **pas** une cadence C-19 |
| `bSessionOnlyLandscapeEdits` | **true** — snapshot / restore Stop Play (`REGLES_PROJET` VERROUILLÉ) |
| Overlay PMC `bUseRuntimeTerraformOverlay` | **false** |
| ODC-F1 | **INVALIDÉ / À REFAIRE** |
| SaveGame projets, tâches, économie, réservations, tech, eau / sol / éco | **Absents** |
| Dirty C-02 | Session — **hors** save (B5) |
| Preuve S3 / Demo | **Session** — hors save monde |

Les règles §3–§12 sont **normatives cibles**. Le runtime actuel est une **dette**, pas une preuve.

---

## 14. Travaux d’implémentation futurs (non autorisés)

Hors périmètre de ce document, même après ce `VALIDÉ` :

- allumer les flags ou le SaveGame ;  
- rendre le load symétrique au save ;  
- implémenter T / R / L / I en runtime ;  
- clore E / X par du code ;  
- reprendre F1 ;  
- rédiger un schéma de migration ;  
- UX sauvegarde (C-20) ;  
- Hertz / debounce produit (C-21).

---

## 15. S3 / Investor Demo (S13)

Les preuves S3 et l’Investor Demo **restent hors** exigence de sauvegarde monde.  
C-19 ne les rouvre pas. Aligné C-18 Q7 (hors Ages / DG-07).

---

## 16. C-20 / C-21 (S14)

| Sujet | Autorité | État |
| --- | --- | --- |
| Écran, wording, flux joueur, observabilité produit de la save | **C-20** | **VALIDÉ** — conception uniquement ; présentation de la sauvegarde non implémentée |
| Fréquences, temporisations, budgets, Hertz | **C-21** | **Non commencé** |

C-19 ne les démarre pas et n’emprunte pas leurs champs.

---

## 17. Responsabilités et frontières

### 17.1 Ce que C-19 garantit (politique)

1. Nommer les familles **admises**, **conditionnelles** et **exclues**.  
2. Distinguer capacité persistable (propriétaire) et **politique** save / load / migration (C-19).  
3. Maintenir Dirty **hors** save (B5).  
4. Qualifier le chemin actuel comme **non opérationnel** (S12).  
5. Porter le caractère **bloquant** de la persistance durable pour le shipping ; F1 reste distinct (S9). Ce `VALIDÉ` reste documentaire et n’autorise pas l’implémentation (S2) — décisions **séparées**.  
6. Laisser ouverts O5, P8, Q7, R5 et R1–R8 / R11.

### 17.2 Ce que C-19 ne possède pas

| Domaine | Autorité |
| --- | --- |
| Vérité hauteur / paint technique | **C-01** |
| Dirty / grille / queries | **C-02** |
| Intention → Project | **C-03\*** (fermé) |
| Graphe de tâches | **C-04** |
| WorkSite / SitePrep | **C-05** |
| ResourceKey / stocks | **C-09\*** / **C-10\*** (fermés) |
| Invariant réservations | **C-11** |
| Données logistiques | **C-12** |
| Construction / En service | **C-13\*** (fermé) |
| Lifecycle infrastructures | **C-14** |
| Eau / sol / éco | **C-15** / **C-16** / **C-17** |
| Recherche / tech / schéma | **C-18** |
| UX | **C-20** |
| Fréquences | **C-21** |
| Architecture F1 / présentation Landscape | **C-01** + F1 redo |
| Rendu M4 | **C-23** / vendor |

---

## 18. Points explicitement ouverts

| # | Sujet | Pourquoi ce n’est pas tranché ici |
| --- | --- | --- |
| **O5 C-15** | Persistance de l’état eau | Politique = C-19 ; donnée = C-15, **ouverte** |
| **P8 C-16** | Persistance de l’état sol | J1 : capacité oui ; donnée = C-16, **ouverte** |
| **Q7 C-17** | Persistance de l’état écologique | Politique = C-19 ; donnée = C-17, **ouverte** |
| **R5 C-18** | Persistance recherche / tech / schéma | Cadre C-18 **ouvert** |
| **R1–R8, R11 C-18** | Catalogue, coûts, Hertz recherche, HUD, etc. | **Inchangés** |
| **O1–O9, P1–P10, Q1–Q12** hors O5 / P8 / Q7 | Questions amont | **Inchangées** |
| Schéma / slot / table de migration | S11 = principe seulement | Pas de schéma inventé |
| Familles P / K | Addenda fermés | Exclusion jusqu’à réexamen distinct |
| Tâches / SitePrep persistés | Pas de flèche C-04 / C-05 | Pas inventé |

---

## 19. Exclusions (L1)

- reprise ou architecture F1 (PMC, RT, matériau, M4 shipping) ;  
- activation des flags, SaveGame, load runtime ;  
- runtime DG-07, Ages, `RequiredAge`, mapping Wood ↔ Timber ;  
- fermeture de O1–O9, P1–P10, Q1–Q12, R1–R8, R11 ;  
- réouverture des addenda C-03\* · C-06\* · C-09\* · C-10\* · C-13\* ;  
- Case B ;  
- Investor Demo / S3 comme save monde ;  
- Dirty persisté ;  
- Hertz, debounce produit, écran, wording HUD ;  
- modification de `designGate.js` / `08.2` ;  
- invention d’invariants métier, schémas de données ou migrations appartenant à d’autres contrats ;  
- famille persistable tâches / SitePrep.

---

## 20. Vérification documentaire — divergences signalées (non corrigées)

Ces écarts existent **avant** ou **autour** de C-19. Ce fichier **ne les corrige pas**.

1. **Amont registre C-03\* / C-09\*.** Officiellement amont de C-19, addenda **fermés**. Traités par S6=A (citer sans ouvrir). Une révision d’amont = correction documentaire séparée.

2. **Save gated / load hard-skip.** `SaveRuntimeTerraform` dépend du flag ; `LoadRuntimeTerraform` est inconditionnellement false. Asymétrie = écart d’implémentation. S12 interdit de la présenter comme save monde opérationnelle.

3. **C-01 E6.** C-01 constate encore capacité / politique ouvertes. C-19 est `VALIDÉ` comme **règle de conception** ; ce n’est **pas** une activation du runtime. L’en-tête de `C-01_TERRAIN_RUNTIME.md` dit encore « non VALIDÉ » alors que le suivi le dit **VALIDÉ** — écart **hors** C-19.

4. **`08.2`.** Sous-point local « Persistance » sous Raise / Lower / Paint, sans contrat C-19. `designGate.js` est **préexistantement modifié**. C-19 **ne le touche pas**.

5. **`Config/DefaultGame.ini`.** Flag False, fichier **non suivi**. Constat ; pas une règle produit.

6. **Suivi / compteur.** C-19 reste `NON COMMENCÉ` au suivi (13 / 16) jusqu’à une étape ultérieure autorisée. Ce fichier **ne met pas à jour** le suivi.

7. **C-12 G2.** « Sans preuve » : conservé. C-19 n’invente pas la preuve.

---

## 21. Invariants

1. Titre et rôle : **Persistance / sauvegarde** — *ce qui est persisté · migration · session-only* (S1).  
2. Ce `VALIDÉ` reste **documentaire** (S2).  
3. Politique **monde par familles** ; pas de transfert de propriété métier (S3).  
4. Familles cibles : **T, R, L, I**. **E** et **X** conditionnels. **P** et **K** exclus (S4).  
5. Dirty **hors** save monde (S5, B5).  
6. Addenda C-03\* · C-09\* · C-10\* · C-13\* **fermés** (S6).  
7. Session-only aujourd’hui ; durable = cible shipping ; **pas** d’activation (S7).  
8. Déclenchement = familles seulement (S8). UX = C-20. Cadence = C-21 (S14).  
9. Bloquant shipping / F1 durable ; **≠** reprise F1 (S9).  
10. Tech future sous C-18 ; **R5 ouvert** (S10).  
11. Migration = principe ; pas de schéma (S11).  
12. Chemin actuel **≠** save monde opérationnelle (S12).  
13. S3 / Demo hors exigence (S13).  
14. O5, P8, Q7, R5, R1–R8 / R11 **ouverts**.

---

## 22. Hors autorisation

Ce contrat **VALIDÉ** **n’autorise pas** :

- l’implémentation ou la réactivation de la persistance runtime ;  
- la reprise F1 ;  
- l’ouverture de C-20 ou C-21 ;  
- la fermeture des questions ouvertes amont ;  
- la réouverture des addenda, de Case B ou d’ODC-F9 ;  
- la modification du Design Gate, des registres, du suivi, de l’historique, du Hub ou des contrats voisins.

---

## 23. Correspondance cadrage

| Décision | Section |
| --- | --- |
| S1 | §1 |
| S2 | §3, §22 |
| S3 | §4.1 |
| S4 | §4.3–§4.5 |
| S5 | §7 |
| S6 | §8 |
| S7 | §5 |
| S8 | §6 |
| S9 | §9 |
| S10 | §10, §4.4 |
| S11 | §11 |
| S12 | §12, §13 |
| S13 | §15 |
| S14 | §16 |
| L1 | §19 |
| L2 | §4.2 |
| L3 | §20 |

---

*Fin C-19 — VALIDÉ. La clôture est documentaire. C-20 est VALIDÉ conception (UX save non implémentée). C-21 demeure non commencé. Case B demeure suspendu. Points ouverts O5, P8, Q7, R5 et R1–R8 / R11 conservés. Aucune implémentation runtime ni contrat suivant démarrés par cette clôture. Le suivi / compteur restent à l’étape 11.*
