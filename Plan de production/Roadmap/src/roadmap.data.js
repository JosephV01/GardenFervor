/**
 * GardenFervor — Roadmap de production
 * SOURCE DE VÉRITÉ UNIQUE — éditer uniquement ce fichier, puis :
 *   node Plan de production/Roadmap/scripts/syncRoadmap.mjs
 *
 * Distinct de :
 *   Design Gate = conception
 *   PLAN_PRODUCTION_COHORTE_S3.md = comment produire
 *   ETAT_PROJET.md = snapshot projet
 *   HISTORIQUE_MODIFICATIONS.md = traçabilité longue
 */

export const ROADMAP_META = {
  project: 'GardenFervor',
  version: '1.0',
  title: 'Roadmap de production',
  updated: '2026-10-06',
  planRef: 'Plan de production/PLAN_PRODUCTION_COHORTE_S3.md',
  controlRef: 'Audit de readiness pré-implémentation/CONTROLE_FINAL_PRE_IMPLEMENTATION_COHORTE.md',
  globalState: 'Prêt — en attente ordre T1',
  currentSliceId: null,
  nextSliceId: 'T1',
  blockNote: null,
};

/** Statuts autorisés */
export const STATUS = {
  TODO: 'À FAIRE',
  DOING: 'EN COURS',
  REVIEW: 'VALIDATION',
  DONE: 'VALIDÉ',
  BLOCKED: 'BLOQUÉ',
};

export const PHASES = [
  {
    id: 'phase-s3',
    code: 'P1',
    title: 'Preuve cohorte forestière S3',
    summary: 'Cas A — terrain déjà prêt. Première preuve jouable de la boucle RTS.',
    status: STATUS.TODO,
    slices: [
      {
        id: 'T1',
        name: 'C7 Timber',
        objective: 'Enregistrer la ResourceKey officielle Timber dans PhysicalEconomy.',
        status: STATUS.TODO,
        dependsOn: ['F03 C7'],
        expected: 'GardenFervorPhysicalResourceKey(Timber) == "Timber"',
        validation: 'Compile ; helper Timber ; Wood legacy intact',
        block: null,
        validatedAt: null,
        planSection: 'Plan §E T1',
      },
      {
        id: 'T2',
        name: 'C1 ResourceKey',
        objective: 'Extract/Haul génériques paramétrés (OperationalResourceKey).',
        status: STATUS.TODO,
        dependsOn: ['T1'],
        expected: 'Même agent : Spoil ou Timber selon la tâche',
        validation: 'Spoil non régressé ; Deposit Timber possible',
        block: null,
        validatedAt: null,
        planSection: 'Plan §E T2',
      },
      {
        id: 'T3',
        name: 'C2 U1/U2/U3',
        objective: 'Caps Extraction / Transport / Construction (données).',
        status: STATUS.TODO,
        dependsOn: ['T2'],
        expected: 'Trois rôles sans Worker fourre-tout',
        validation: 'Claims séparés U1/U2/U3',
        block: null,
        validatedAt: null,
        planSection: 'Plan §E T3',
      },
      {
        id: 'T4',
        name: 'Stocks A/B',
        objective: 'Deux stocks PE distincts liés au Project.',
        status: STATUS.TODO,
        dependsOn: ['T1'],
        expected: 'A ≠ B ; GetAvailable distincts',
        validation: 'Ids différents ; Deposit A visible',
        block: null,
        validatedAt: null,
        planSection: 'Plan §E T4',
      },
      {
        id: 'T5',
        name: 'Expand Cas A',
        objective: 'Expand Project générique : Analyze→Extract→Transport→Build→Verify.',
        status: STATUS.TODO,
        dependsOn: ['T2', 'T3', 'T4'],
        expected: 'Graphe sans ExpandForest / sans LevelPad copié',
        validation: 'Tâches + caps + Timber corrects',
        block: null,
        validatedAt: null,
        planSection: 'Plan §E T5',
      },
      {
        id: 'T6',
        name: 'Intention smoke',
        objective: 'Entrée dédiée Intention → Project (sans BeginPlace/TrySpend).',
        status: STATUS.TODO,
        dependsOn: ['T5'],
        expected: 'Smoke crée Project Running + unités',
        validation: 'Sans spend ; HUD Wood FWSG inchangé',
        block: null,
        validatedAt: null,
        planSection: 'Plan §E T6',
      },
      {
        id: 'T7',
        name: 'En service S3',
        objective: 'Achevé ≠ En service ; critère Achevé ∧ Stock B Timber > 0.',
        status: STATUS.TODO,
        dependsOn: ['T5', 'T4'],
        expected: 'Deux jalons visibles ; pas de coût inventé',
        validation: 'Pas En service si B vide',
        block: null,
        validatedAt: null,
        planSection: 'Plan §E T7',
      },
      {
        id: 'T8',
        name: 'Observabilité PE',
        objective: 'Smoke/overlay lisible ancré PhysicalEconomy.',
        status: STATUS.TODO,
        dependsOn: ['T6', 'T7'],
        expected: 'Chaîne + A/B Timber + En service lisibles',
        validation: 'Sans HUD FWSG comme vérité',
        block: null,
        validatedAt: null,
        planSection: 'Plan §E T8',
      },
      {
        id: 'T9',
        name: 'Preuve bout-en-bout',
        objective: 'Chaîne S3 Cas A complète et observable en PIE.',
        status: STATUS.TODO,
        dependsOn: ['T1', 'T2', 'T3', 'T4', 'T5', 'T6', 'T7', 'T8'],
        expected: 'Intention→…→En service + Timber B > 0',
        validation: 'Checklist Plan §G (humain)',
        block: null,
        validatedAt: null,
        planSection: 'Plan §E T9',
      },
    ],
  },
];

export function getAllSlices() {
  return PHASES.flatMap((p) => p.slices.map((s) => ({ ...s, phaseId: p.id, phaseTitle: p.title })));
}

export function getProgress() {
  const slices = getAllSlices();
  const total = slices.length;
  const done = slices.filter((s) => s.status === STATUS.DONE).length;
  const blocked = slices.filter((s) => s.status === STATUS.BLOCKED).length;
  const doing = slices.filter((s) => s.status === STATUS.DOING).length;
  const review = slices.filter((s) => s.status === STATUS.REVIEW).length;
  const todo = slices.filter((s) => s.status === STATUS.TODO).length;
  return {
    total,
    done,
    blocked,
    doing,
    review,
    todo,
    percent: total === 0 ? 0 : Math.round((done / total) * 100),
  };
}

export function serializeRoadmap() {
  return {
    meta: ROADMAP_META,
    statusLabels: STATUS,
    phases: PHASES,
    progress: getProgress(),
  };
}
