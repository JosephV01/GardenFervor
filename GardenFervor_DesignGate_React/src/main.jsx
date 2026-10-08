import React, { useMemo, useState } from 'react';
import { createRoot } from 'react-dom/client';
import {
  CheckCircle2,
  ChevronDown,
  ChevronRight,
  CircleHelp,
  ClipboardCheck,
  Download,
  GitBranch,
  Layers3,
  LockKeyhole,
  Menu,
  Search,
  Sparkles,
  Target,
  X
} from 'lucide-react';
import './styles.css';
import { DESIGN_GATE, STATUS_META, getSectionStats, toMarkdown } from './data/designGate.js';
import ContractsSuiviView from './ContractsSuiviView.jsx';

const VALID_STATUS = new Set(['VALIDÉ', 'À DÉFINIR', 'À TESTER', 'DÉPENDANT', 'HORS PÉRIMÈTRE', 'À RÉÉVALUER']);

function App() {
  const [workspace, setWorkspace] = useState('gate');
  const [activeId, setActiveId] = useState(DESIGN_GATE.sections[0].id);
  const [query, setQuery] = useState('');
  const [statusFilter, setStatusFilter] = useState('TOUS');
  const [sidebarOpen, setSidebarOpen] = useState(true);
  const [expanded, setExpanded] = useState(() => new Set(DESIGN_GATE.sections.map((s) => s.id)));
  const [showQuestionnaireOnly, setShowQuestionnaireOnly] = useState(false);

  const active = DESIGN_GATE.sections.find((s) => s.id === activeId) ?? DESIGN_GATE.sections[0];

  const globalStats = useMemo(() => {
    const flat = DESIGN_GATE.sections.flatMap((section) => section.items);
    const counts = { total: flat.length, validated: 0, open: 0, test: 0, dependent: 0, out: 0, reevaluate: 0 };
    flat.forEach((item) => {
      if (item.status === 'VALIDÉ') counts.validated++;
      else if (item.status === 'À DÉFINIR') counts.open++;
      else if (item.status === 'À TESTER') counts.test++;
      else if (item.status === 'DÉPENDANT') counts.dependent++;
      else if (item.status === 'HORS PÉRIMÈTRE') counts.out++;
      else if (item.status === 'À RÉÉVALUER') counts.reevaluate++;
    });
    return counts;
  }, []);

  const completion = Math.round((globalStats.validated / Math.max(1, globalStats.total - globalStats.out)) * 100);

  const filteredSections = useMemo(() => {
    const q = query.trim().toLowerCase();
    return DESIGN_GATE.sections.map((section) => {
      const sectionText = [section.title, section.goal, ...section.tags].join(' ').toLowerCase();
      const sectionMatch = !q || sectionText.includes(q);
      const items = section.items.filter((item) => {
        const text = [item.title, item.decision ?? '', item.question ?? '', item.rationale ?? '', ...(item.subpoints ?? [])].join(' ').toLowerCase();
        const qMatch = !q || text.includes(q) || sectionMatch;
        const statusMatch = statusFilter === 'TOUS' || item.status === statusFilter;
        const questionMatch = !showQuestionnaireOnly || Boolean(item.question);
        return qMatch && statusMatch && questionMatch;
      });
      return { ...section, visibleItems: items };
    }).filter((section) => section.visibleItems.length > 0 || (!q && statusFilter === 'TOUS' && !showQuestionnaireOnly));
  }, [query, statusFilter, showQuestionnaireOnly]);

  function toggle(id) {
    setExpanded((current) => {
      const next = new Set(current);
      if (next.has(id)) next.delete(id); else next.add(id);
      return next;
    });
  }

  function scrollTo(sectionId) {
    setActiveId(sectionId);
    setExpanded((current) => new Set(current).add(sectionId));
    document.getElementById(sectionId)?.scrollIntoView({ behavior: 'smooth', block: 'start' });
  }

  function exportMarkdown() {
    const blob = new Blob([toMarkdown(DESIGN_GATE)], { type: 'text/markdown;charset=utf-8' });
    const url = URL.createObjectURL(blob);
    const a = document.createElement('a');
    a.href = url;
    a.download = 'GardenFervor_DESIGN_GATE_v0.1.md';
    a.click();
    URL.revokeObjectURL(url);
  }

  return (
    <div className="appShell">
      <header className="topbar">
        <div className="brandBlock">
          {workspace === 'gate' && (
            <button className="iconButton mobileOnly" onClick={() => setSidebarOpen((v) => !v)} aria-label="Afficher le menu"><Menu size={19} /></button>
          )}
          <div className="brandMark"><SproutIcon /></div>
          <div>
            <div className="eyebrow">GARDENFERVOR</div>
            <div className="topTitle">
              {workspace === 'gate' ? <>DESIGN GATE <span>v0.1</span></> : <>SUIVI DES CONTRATS</>}
            </div>
          </div>
        </div>
        <nav className="workspaceTabs" aria-label="Espaces de travail">
          <button
            type="button"
            className={`workspaceTab ${workspace === 'gate' ? 'active' : ''}`}
            onClick={() => setWorkspace('gate')}
          >
            Design Gate
          </button>
          <button
            type="button"
            className={`workspaceTab ${workspace === 'contracts' ? 'active' : ''}`}
            onClick={() => setWorkspace('contracts')}
          >
            Suivi des contrats
          </button>
        </nav>
        <div className="topActions">
          <div className="statusChip"><span className="dot"></span> {workspace === 'gate' ? 'Document actif' : 'Pilot pilotage'}</div>
          {workspace === 'gate' && (
            <button className="button secondary" onClick={exportMarkdown}><Download size={16} /> Exporter Markdown</button>
          )}
        </div>
      </header>

      {workspace === 'contracts' ? (
        <ContractsSuiviView />
      ) : (
      <div className="layout">
        <aside className={`sidebar ${sidebarOpen ? 'open' : ''}`}>
          <div className="sideTop">
            <div className="sideHeading">Navigation</div>
            <button className="iconButton desktopOnly" onClick={() => setSidebarOpen(false)} aria-label="Fermer le menu"><X size={16}/></button>
          </div>
          <div className="searchBox">
            <Search size={16} />
            <input value={query} onChange={(e) => setQuery(e.target.value)} placeholder="Rechercher dans le Gate…" />
            {query && <button onClick={() => setQuery('')} aria-label="Effacer"><X size={14}/></button>}
          </div>
          <div className="filterGrid">
            <select value={statusFilter} onChange={(e) => setStatusFilter(e.target.value)}>
              <option value="TOUS">Tous les statuts</option>
              {[...VALID_STATUS].map((s) => <option key={s} value={s}>{s}</option>)}
            </select>
            <button className={`filterToggle ${showQuestionnaireOnly ? 'active' : ''}`} onClick={() => setShowQuestionnaireOnly((v) => !v)}><CircleHelp size={14}/> Questions</button>
          </div>
          <nav className="navList">
            {filteredSections.length === 0 && <div className="emptyState small">Aucun résultat.</div>}
            {filteredSections.map((section) => {
              const stats = getSectionStats(section);
              const isActive = activeId === section.id;
              const open = expanded.has(section.id);
              return (
                <div key={section.id} className={`navGroup ${isActive ? 'active' : ''}`}>
                  <button className="navSection" onClick={() => { toggle(section.id); scrollTo(section.id); }}>
                    {open ? <ChevronDown size={14}/> : <ChevronRight size={14}/>} 
                    <span className="navCode">{section.code}</span>
                    <span className="navTitle">{section.title}</span>
                    <span className="navCount">{stats.open + stats.dependent}</span>
                  </button>
                  {open && <div className="navSub">
                    {section.items.map((item) => (
                      <button key={item.id} onClick={() => {
                        setActiveId(section.id);
                        document.getElementById(item.id)?.scrollIntoView({ behavior: 'smooth', block: 'start' });
                      }}>
                        <span>{item.code}</span>{item.title}
                      </button>
                    ))}
                  </div>}
                </div>
              );
            })}
          </nav>
        </aside>

        <main className="content">
          <section className="heroCard">
            <div className="heroContent">
              <div className="heroKicker"><ClipboardCheck size={15}/> Contrat de conception</div>
              <h1>Construire le jeu avant de construire le système.</h1>
              <p className="heroLead">Ce Design Gate définit les décisions de gameplay à prendre avant l’implémentation. Il décrit l’intention du joueur, les bâtiments, les unités, la progression, la logistique, le terrain et l’évolution des écosystèmes sans inventer les règles encore inconnues.</p>
              <div className="heroRule"><Sparkles size={18}/><span><strong>Principe central :</strong> le joueur décide ce qu’il veut obtenir ; le monde détermine comment y parvenir.</span></div>
            </div>
            <div className="heroProgress">
              <div className="progressLabel"><span>Avancement de conception</span><strong>{completion}%</strong></div>
              <div className="progressTrack"><div className="progressFill" style={{ width: `${Math.min(completion,100)}%` }} /></div>
              <div className="progressMeta">{globalStats.validated} décisions validées · {globalStats.open + globalStats.dependent} ouvertes · {globalStats.test} à tester</div>
            </div>
          </section>

          <section className="dashboardGrid">
            <StatCard icon={<CheckCircle2/>} label="Validé" value={globalStats.validated} tone="validated" />
            <StatCard icon={<CircleHelp/>} label="À définir" value={globalStats.open} tone="open" />
            <StatCard icon={<LockKeyhole/>} label="Dépendant" value={globalStats.dependent} tone="dependent" />
            <StatCard icon={<ClipboardCheck/>} label="À tester" value={globalStats.test} tone="test" />
          </section>

          <section className="principlesCard">
            <div className="sectionMiniTitle"><Target size={17}/> Fondations déjà retenues</div>
            <div className="principleGrid">
              {DESIGN_GATE.principles.map((p) => <div className="principle" key={p.id}><div className="principleTag">{p.tag}</div><p>{p.text}</p></div>)}
            </div>
          </section>

          <div className="sectionHeadingRow" id="gateTop">
            <div>
              <div className="eyebrow">WORKSPACE DE CONCEPTION</div>
              <h2>Questionnaire structuré</h2>
              <p>Chaque grande section indique ce qu’il faut décider exactement. Les éléments sans décision définitive restent explicitement ouverts.</p>
            </div>
            <div className="keyLegend">
              {Object.entries(STATUS_META).map(([s,m]) => <span key={s} className={`statusBadge ${m.className}`}>{m.short}</span>)}
            </div>
          </div>

          <div className="gateSections">
            {filteredSections.map((section) => (
              <SectionCard key={section.id} section={section} isExpanded={expanded.has(section.id)} onToggle={() => toggle(section.id)} />
            ))}
          </div>

          <section className="bottomGrid">
            <div className="panel">
              <div className="panelTitle"><GitBranch size={17}/> Règles de validation</div>
              <ul>{DESIGN_GATE.validationRules.map((r) => <li key={r}>{r}</li>)}</ul>
            </div>
            <div className="panel">
              <div className="panelTitle"><Layers3 size={17}/> Hors périmètre actuel</div>
              <ul>{DESIGN_GATE.outOfScope.map((r) => <li key={r}>{r}</li>)}</ul>
            </div>
          </section>

          <footer className="footer"><span>GardenFervor · Design Gate v0.1</span><span>Document vivant · aucune décision ouverte n’est présumée validée.</span></footer>
        </main>
      </div>
      )}
    </div>
  );
}

function SproutIcon() {
  return <svg width="18" height="18" viewBox="0 0 24 24" fill="none" aria-hidden="true"><path d="M12 20V10" stroke="currentColor" strokeWidth="1.7" strokeLinecap="round"/><path d="M12 11C8 11 5 8.7 5 4c4.7 0 7 2.9 7 7Z" stroke="currentColor" strokeWidth="1.7" strokeLinejoin="round"/><path d="M12 14c0-4 2.6-6.5 7-6.5 0 4.5-2.8 6.5-7 6.5Z" stroke="currentColor" strokeWidth="1.7" strokeLinejoin="round"/></svg>;
}

function StatCard({ icon, label, value, tone }) {
  return <div className={`statCard ${tone}`}><div className="statIcon">{icon}</div><div><div className="statValue">{value}</div><div className="statLabel">{label}</div></div></div>;
}

function SectionCard({ section, isExpanded, onToggle }) {
  const stats = getSectionStats(section);
  return (
    <section className={`gateCard ${isExpanded ? 'expanded' : ''}`} id={section.id}>
      <button className="gateHeader" onClick={onToggle}>
        <div className="gateHeaderLeft">
          <div className="gateCode">{section.code}</div>
          <div><h3>{section.title}</h3><p>{section.goal}</p></div>
        </div>
        <div className="gateHeaderRight">
          <div className="miniStats"><span className="miniPill validated">{stats.validated}</span><span className="miniPill open">{stats.open}</span><span className="miniPill dependent">{stats.dependent}</span></div>
          {isExpanded ? <ChevronDown size={18}/> : <ChevronRight size={18}/>} 
        </div>
      </button>
      {isExpanded && (
        <div className="gateBody">
          <div className="sectionMeta">
            <div className="metaBlock"><span>Objectif</span><strong>{section.goal}</strong></div>
            <div className="metaBlock"><span>Dépend de</span><strong>{section.dependsOn.length ? section.dependsOn.join(' · ') : 'Aucune dépendance critique'}</strong></div>
            <div className="metaBlock"><span>Impacte</span><strong>{section.impacts.length ? section.impacts.join(' · ') : 'À déterminer'}</strong></div>
          </div>
          {section.items.map((item) => <DecisionItem key={item.id} item={item} />)}
        </div>
      )}
    </section>
  );
}

function DecisionItem({ item }) {
  const [open, setOpen] = useState(true);
  const meta = STATUS_META[item.status] ?? STATUS_META['À DÉFINIR'];
  return (
    <article className="decisionItem" id={item.id}>
      <button className="decisionHead" onClick={() => setOpen((v) => !v)}>
        <div className="decisionMain">
          <div className="itemCode">{item.code}</div>
          <div><h4>{item.title}</h4><span className={`statusBadge ${meta.className}`}>{meta.label}</span></div>
        </div>
        {open ? <ChevronDown size={16}/> : <ChevronRight size={16}/>} 
      </button>
      {open && <div className="decisionBody">
        {item.decision && <div className="callout decision"><strong>Décision retenue</strong><p>{item.decision}</p></div>}
        {item.question && <div className="callout question"><strong><CircleHelp size={14}/> Question à trancher</strong><p>{item.question}</p></div>}
        {item.subpoints?.length > 0 && <div className="subpointBlock"><div className="subpointLabel">À définir / vérifier exactement</div><div className="chips">{item.subpoints.map((s) => <span key={s}>{s}</span>)}</div></div>}
        {item.rationale && <p className="rationale">{item.rationale}</p>}
        {item.example && <div className="exampleBox"><div className="exampleTitle"><Sparkles size={14}/> Exemple de référence</div><p>{item.example}</p></div>}
        {(item.dependsOn?.length || item.impacts?.length) && <div className="relations"><span><strong>Dépend :</strong> {item.dependsOn?.length ? item.dependsOn.join(' · ') : '—'}</span><span><strong>Impacte :</strong> {item.impacts?.length ? item.impacts.join(' · ') : '—'}</span></div>}
      </div>}
    </article>
  );
}

createRoot(document.getElementById('root')).render(<App />);
