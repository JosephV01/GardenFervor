import React, { useMemo, useState } from 'react';
import {
  AlertTriangle,
  ArrowRight,
  CheckCircle2,
  ClipboardList,
  FileWarning,
  GitBranch,
  ShieldAlert,
} from 'lucide-react';
import {
  CATEGORY_META,
  CONTRACTS_SUIVI,
  PRODUCTION_STATUS_META,
  getDisplayStatus,
  getOrderedContracts,
} from './data/contractsSuivi.js';

function statusMeta(status) {
  return PRODUCTION_STATUS_META[status] ?? PRODUCTION_STATUS_META['À FAIRE'];
}

function categoryMeta(category) {
  return CATEGORY_META[category] ?? CATEGORY_META.REQUIS;
}

export default function ContractsSuiviView() {
  const ordered = useMemo(() => getOrderedContracts(), []);
  const active = CONTRACTS_SUIVI.contracts.find((c) => c.id === CONTRACTS_SUIVI.activeContractId);
  const [selectedId, setSelectedId] = useState(CONTRACTS_SUIVI.activeContractId);
  const selected = CONTRACTS_SUIVI.contracts.find((c) => c.id === selectedId) ?? active;

  const { validated, required } = CONTRACTS_SUIVI.progress;
  const pct = Math.round((validated / Math.max(1, required)) * 100);

  const counts = useMemo(() => {
    const c = { todo: 0, review: 0, validated: 0, suffisant: 0, nonrequis: 0 };
    for (const contract of CONTRACTS_SUIVI.contracts) {
      const d = getDisplayStatus(contract);
      if (d === 'VALIDÉ') c.validated += 1;
      else if (d === 'REVUE' || d === 'RÉDACTION' || d === 'DÉCISIONS EN COURS') c.review += 1;
      else if (d === 'SUFFISANT') c.suffisant += 1;
      else if (d === 'NON REQUIS') c.nonrequis += 1;
      else if (contract.category === 'REQUIS') c.todo += 1;
    }
    return c;
  }, []);

  return (
    <main className="content cs-page">
      <section className="heroCard cs-hero">
        <div className="heroContent">
          <div className="heroKicker"><ClipboardList size={15} /> Pilotage documentaire</div>
          <h1>{CONTRACTS_SUIVI.title}</h1>
          <p className="heroLead cs-subtitle">{CONTRACTS_SUIVI.subtitle}</p>
          <div className="heroRule">
            <ShieldAlert size={18} />
            <span>
              <strong>Règle :</strong> {CONTRACTS_SUIVI.rule}
            </span>
          </div>
        </div>
        <div className="heroProgress">
          <div className="progressLabel">
            <span>Contrats autonomes requis validés</span>
            <strong>{validated} / {required}</strong>
          </div>
          <div className="progressTrack">
            <div className="progressFill" style={{ width: `${Math.min(pct, 100)}%` }} />
          </div>
          <div className="progressMeta">
            Progression {pct}% · dernière synchronisation {CONTRACTS_SUIVI.lastSync}
          </div>
        </div>
      </section>

      <section className="cs-metaGrid">
        <div className="cs-metaCard">
          <span>État global</span>
          <strong>Pilotage documentaire</strong>
          <em>{validated} / {required} validés</em>
        </div>
        <div className="cs-metaCard active">
          <span>Dernier contrat validé</span>
          <strong>{active?.id} — {active?.name}</strong>
          <em>Statut production : {active?.productionStatus}</em>
        </div>
        <div className="cs-metaCard">
          <span>Case B</span>
          <strong className="cs-warn">{CONTRACTS_SUIVI.caseB.status}</strong>
          <em>{CONTRACTS_SUIVI.caseB.note}</em>
        </div>
        <div className="cs-metaCard">
          <span>Sources</span>
          <strong>Registre + Suivi + contrats</strong>
          <em>{CONTRACTS_SUIVI.sources.join(' · ')}</em>
        </div>
      </section>

      <section className="dashboardGrid cs-stats">
        <Stat tone="todo" label="À faire (requis)" value={counts.todo} />
        <Stat tone="review" label="En cours / revue" value={counts.review} />
        <Stat tone="validated" label="Validés dédiés" value={validated} />
        <Stat tone="suffisant" label="Suffisants S3*" value={counts.suffisant} />
      </section>

      {active && (
        <section className="cs-activeBanner" aria-label="Dernier contrat validé">
          <div className="cs-activeLeft">
            <div className="eyebrow">DERNIER CONTRAT VALIDÉ</div>
            <h2>{active.id} — {active.name}</h2>
            <p>{active.note}</p>
          </div>
          <div className="cs-activeRight">
            <span className={`cs-badge ${statusMeta(active.productionStatus).className}`}>
              {statusMeta(active.productionStatus).label}
            </span>
            {active.detail && (
              <div className="cs-activeDecisions">
                Décisions : <strong>{active.detail.decisionsTaken} / {active.detail.decisionsTotal}</strong>
              </div>
            )}
          </div>
        </section>
      )}

      <div className="sectionHeadingRow">
        <div>
          <div className="eyebrow">ORDRE OFFICIEL</div>
          <h2>Registre de production</h2>
          <p>C-01 → C-02 → … → C-21. Les addenda * (SUFFISANT) ne sont pas des contrats dédiés VALIDÉS.</p>
        </div>
        <div className="keyLegend cs-legend">
          <span className="cs-badge cs-todo">À FAIRE</span>
          <span className="cs-badge cs-decisions">DÉCISIONS</span>
          <span className="cs-badge cs-draft">RÉDACTION</span>
          <span className="cs-badge cs-review">REVUE</span>
          <span className="cs-badge cs-validated">VALIDÉ</span>
          <span className="cs-badge cs-cat-partiel">PARTIEL</span>
          <span className="cs-badge cs-cat-suffisant">SUFFISANT</span>
          <span className="cs-badge cs-cat-nonrequis">NON REQUIS</span>
        </div>
      </div>

      <div className="cs-pipeline" aria-label="Ordre des contrats">
        {ordered.filter((c) => c.id !== 'C-10').map((contract, index) => {
          const display = getDisplayStatus(contract);
          const isActive = contract.id === CONTRACTS_SUIVI.activeContractId
            || (contract.id === 'C-09' && CONTRACTS_SUIVI.activeContractId === 'C-10');
          const isSelected = contract.id === selectedId
            || (contract.id === 'C-09' && selectedId === 'C-10');
          const labelId = contract.id === 'C-09' ? 'C-09/10' : contract.id;
          return (
            <React.Fragment key={contract.id}>
              {index > 0 && <span className="cs-pipeArrow" aria-hidden="true"><ArrowRight size={12} /></span>}
              <button
                type="button"
                className={`cs-pipeNode ${isActive ? 'active' : ''} ${isSelected ? 'selected' : ''} ${statusMeta(display).className}`}
                onClick={() => setSelectedId(contract.id)}
                title={contract.id === 'C-09'
                  ? 'C-09 / C-10 — Économie / Stocks'
                  : `${contract.id} — ${contract.name}`}
              >
                <span className="cs-pipeId">{labelId}</span>
                <span className="cs-pipeStatus">{display === 'NON COMMENCÉ' ? 'À FAIRE' : display}</span>
              </button>
            </React.Fragment>
          );
        })}
      </div>

      <div className="cs-layout">
        <section className="cs-list">
          {ordered.map((contract) => {
            const display = getDisplayStatus(contract);
            const showProductionBadge = contract.category === 'REQUIS'
              || !['NON COMMENCÉ'].includes(contract.productionStatus);
            const prodLabel = contract.productionStatus === 'NON COMMENCÉ' ? 'À FAIRE' : contract.productionStatus;
            const prod = statusMeta(prodLabel);
            const cat = categoryMeta(contract.category);
            const isActive = contract.id === CONTRACTS_SUIVI.activeContractId;
            const isSelected = contract.id === selectedId;
            return (
              <button
                type="button"
                key={contract.id}
                className={`cs-row ${isActive ? 'active' : ''} ${isSelected ? 'selected' : ''}`}
                onClick={() => setSelectedId(contract.id)}
              >
                <div className="cs-rowTop">
                  <span className="cs-rowOrder">#{contract.order ?? '—'}</span>
                  <span className="cs-rowId">{contract.id}</span>
                  <span className="cs-rowName">{contract.name}</span>
                  {isActive && <span className="cs-rowActiveTag">DERNIER VALIDÉ</span>}
                </div>
                <div className="cs-rowBadges">
                  {showProductionBadge && (
                    <span className={`cs-badge ${prod.className}`}>{prod.label}</span>
                  )}
                  <span className={`cs-badge ${cat.className}`}>{cat.label}</span>
                  {contract.coverage === 'partielle' && contract.category === 'REQUIS' && (
                    <span className="cs-badge cs-cat-partiel">PARTIEL</span>
                  )}
                  {contract.productionStatus === 'REVUE' && (
                    <span className="cs-badge cs-not-validated">NON VALIDÉ</span>
                  )}
                  {contract.blocking && <span className="cs-badge cs-blocked">BLOQUANT</span>}
                </div>
              </button>
            );
          })}
        </section>

        <aside className="cs-detail">
          {selected && <ContractDetail contract={selected} />}
        </aside>
      </div>

      <section className="cs-nonreq">
        <div className="sectionMiniTitle"><FileWarning size={16} /> Hors ordre de rédaction (non requis)</div>
        <div className="cs-nonreqGrid">
          {CONTRACTS_SUIVI.contracts
            .filter((c) => c.displayInOrder === false || c.category === 'NON REQUIS')
            .filter((c) => c.id === 'C-00' || c.id === 'C-22' || c.id === 'C-23')
            .map((c) => (
              <div key={c.id} className="cs-nonreqCard">
                <strong>{c.id}</strong>
                <span>{c.name}</span>
                <em>{c.note}</em>
              </div>
            ))}
        </div>
      </section>

      <footer className="footer">
        <span>GardenFervor · Suivi des contrats</span>
        <span>Vue synchronisée — les Markdown CONTRATS/ restent la source de vérité</span>
      </footer>
    </main>
  );
}

function Stat({ tone, label, value }) {
  return (
    <div className={`statCard cs-stat-${tone}`}>
      <div className="statIcon">
        {tone === 'validated' ? <CheckCircle2 /> : tone === 'review' ? <ClipboardList /> : <AlertTriangle />}
      </div>
      <div>
        <div className="statValue">{value}</div>
        <div className="statLabel">{label}</div>
      </div>
    </div>
  );
}

function ContractDetail({ contract }) {
  const display = getDisplayStatus(contract);
  const prod = statusMeta(contract.productionStatus === 'NON COMMENCÉ' ? 'À FAIRE' : contract.productionStatus);
  const isReview = contract.productionStatus === 'REVUE';
  const isValidated = contract.productionStatus === 'VALIDÉ' && contract.dedicatedValidated !== false;

  return (
    <div className={`cs-detailCard ${contract.id === CONTRACTS_SUIVI.activeContractId ? 'active' : ''}`}>
      <div className="eyebrow">FICHE CONTRAT</div>
      <h3>{contract.id}</h3>
      <p className="cs-detailName">{contract.name}</p>

      <div className="cs-detailBadges">
        <span className={`cs-badge ${prod.className}`}>{prod.label}</span>
        <span className={`cs-badge ${categoryMeta(contract.category).className}`}>
          {categoryMeta(contract.category).label}
        </span>
        {isReview && <span className="cs-badge cs-not-validated">NON VALIDÉ</span>}
        {isValidated && <span className="cs-badge cs-validated">VALIDÉ</span>}
        {!isValidated && display !== 'VALIDÉ' && contract.category === 'REQUIS' && !isReview && (
          <span className="cs-badge cs-not-validated">NON VALIDÉ</span>
        )}
      </div>

      {contract.note && <p className="cs-detailNote">{contract.note}</p>}
      {contract.file && <p className="cs-detailFile">Fichier : {contract.file}</p>}

      {contract.detail && (
        <>
          <div className="cs-detailBlock">
            <div className="cs-detailLabel">Décisions</div>
            <div className="cs-decisionsCount">
              {contract.detail.decisionsTaken} / {contract.detail.decisionsTotal}
            </div>
          </div>

          <div className="cs-detailBlock">
            <div className="cs-detailLabel">Frontières</div>
            <ul className="cs-frontierList">
              {contract.detail.frontiers.map((f) => (
                <li key={f.id}><strong>{f.id}</strong> — {f.label}</li>
              ))}
            </ul>
          </div>

          <div className="cs-detailBlock cs-gaps">
            <div className="cs-detailLabel"><AlertTriangle size={13} /> Écarts constatés</div>
            <p className="cs-gapNote">{contract.detail.gapNote}</p>
            <ul>
              {contract.detail.gaps.map((g) => (
                <li key={g}>{g}</li>
              ))}
            </ul>
          </div>
        </>
      )}

      <div className="cs-detailBlock">
        <div className="cs-detailLabel"><GitBranch size={13} /> Dépendances (registre)</div>
        <div className="cs-deps">
          <div>
            <span>Dépend de</span>
            <strong>{contract.dependsOn.length ? contract.dependsOn.join(' · ') : '—'}</strong>
          </div>
          <div>
            <span>Fournit à</span>
            <strong>{contract.providesTo.length ? contract.providesTo.join(' · ') : '—'}</strong>
          </div>
        </div>
        {contract.providesTo.length > 0 && (
          <div className="cs-depFlow">
            {contract.providesTo.map((id) => (
              <span key={id} className="cs-depChip">{contract.id} → {id}</span>
            ))}
          </div>
        )}
      </div>

      <div className="cs-pipelineHint">
        Chaîne : Décidé → Rédigé → En revue → Validé
        {isReview && <em> · Actuellement : rédigé / en revue — pas encore Validé</em>}
      </div>
    </div>
  );
}
