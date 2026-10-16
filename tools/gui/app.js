/**
 * Dragon Quest IX Decomp Studio - Client Application Logic
 */

document.addEventListener("DOMContentLoaded", () => {
  // State
  let currentModules = [];
  let currentFunctions = [];
  let selectedFunction = null;
  let activeModule = null;
  let eventSource = null;

  // DOM Elements
  const tabButtons = document.querySelectorAll(".nav-tab");
  const tabPanels = document.querySelectorAll(".tab-panel");
  const globalIndicator = document.getElementById("global-process-indicator");
  const globalIndicatorDot = globalIndicator.querySelector(".status-dot");
  const globalIndicatorLabel = document.getElementById("global-process-label");
  const terminalOutput = document.getElementById("terminal-output");
  const terminalTitle = document.getElementById("terminal-process-title");
  const btnKillProcess = document.getElementById("btn-kill-process");
  const btnClearTerminal = document.getElementById("btn-clear-terminal");

  // --- 1. Tab Navigation ---
  function switchTab(tabId) {
    tabButtons.forEach(btn => {
      btn.classList.toggle("active", btn.dataset.tab === tabId);
    });
    tabPanels.forEach(panel => {
      panel.classList.toggle("active", panel.id === `panel-${tabId}`);
    });

    if (tabId === "dashboard") loadDashboardData();
    if (tabId === "studio" && !activeModule) loadStudioModules();
    if (tabId === "vtables") loadVTablesData();
    if (tabId === "settings") {
      loadDoctorData();
      loadConcurrencySettings();
    }
  }

  tabButtons.forEach(btn => {
    btn.addEventListener("click", () => switchTab(btn.dataset.tab));
  });

  // --- 2. Live Process Streaming (SSE) ---
  function setupSSE() {
    if (eventSource) {
      eventSource.close();
    }
    eventSource = new EventSource("/api/process/stream");

    eventSource.onmessage = (event) => {
      try {
        const data = JSON.parse(event.data);
        if (data.text) {
          appendTerminal(data.text);
        }
        if (data.type === "autopilot_log" || data.type === "autopilot_finished") {
          refreshAutoPilotStatus();
        }
        if (data.done) {
          setProcessRunning(false);
          loadDashboardData(); // Refresh metrics after build/tools finish
        }
      } catch (e) {
        // Heartbeat or raw text
      }
    };

    eventSource.onerror = () => {
      // Reconnect after brief pause
      setTimeout(setupSSE, 3000);
    };
  }

  function appendTerminal(text) {
    // Strip terminal prompt placeholder on first real output
    if (terminalOutput.textContent.startsWith("Inicie un comando")) {
      terminalOutput.textContent = "";
    }
    terminalOutput.textContent += text;
    terminalOutput.scrollTop = terminalOutput.scrollHeight;
  }

  function setProcessRunning(running, label = "En reposo") {
    if (running) {
      globalIndicatorDot.className = "status-dot running";
      globalIndicatorLabel.textContent = `Ejecutando: ${label}`;
      btnKillProcess.style.display = "inline-flex";
      terminalTitle.textContent = `Proceso Activo: ${label}`;
    } else {
      globalIndicatorDot.className = "status-dot idle";
      globalIndicatorLabel.textContent = "En reposo";
      btnKillProcess.style.display = "none";
      terminalTitle.textContent = "Consola de Salida";
    }
  }

  async function runCommand(action, label) {
    terminalOutput.textContent += `\n>>> Ejecutando: ${label}...\n`;
    setProcessRunning(true, label);
    switchTab("control");

    try {
      const res = await fetch("/api/run", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ action, label }),
      });
      const data = await res.json();
      if (!res.ok) {
        appendTerminal(`[ERROR] ${data.error || "No se pudo iniciar el comando"}\n`);
        setProcessRunning(false);
      }
    } catch (err) {
      appendTerminal(`[ERROR de red]: ${err.message}\n`);
      setProcessRunning(false);
    }
  }

  // Bind Control Center Action Buttons
  document.querySelectorAll(".btn-action").forEach(btn => {
    btn.addEventListener("click", () => {
      const action = btn.dataset.action;
      const label = btn.querySelector("strong")?.textContent || action;
      runCommand(action, label);
    });
  });

  // Quick Start Handler: One-click module auto-selection and function draft loading
  const btnQuickStart = document.getElementById("btn-quick-start");
  if (btnQuickStart) {
    btnQuickStart.addEventListener("click", async () => {
      btnQuickStart.classList.add("loading");
      const origHtml = btnQuickStart.innerHTML;
      btnQuickStart.innerHTML = `<span class="btn-icon">⏳</span> Seleccionando módulo...`;

      try {
        const res = await fetch("/api/quick-start", { method: "POST" });
        const data = await res.json();

        if (data.success) {
          switchTab("studio");
          await loadStudioModules();
          await selectStudioModule(data.module);

          // Find or synthesize target function
          const targetAddr = data.function_address;
          let fn = currentFunctions.find(f => f.address === targetAddr);
          if (!fn) {
            fn = {
              name: data.function_name,
              address: data.function_address,
              address_hex: data.function_address_hex,
              size: 0,
              decompiled: false,
            };
          }
          selectFunction(fn);

          // Inject draft code directly
          const codeViewer = document.getElementById("wb-code-viewer");
          codeViewer.textContent = data.draft_code || "// Borrador no generado.";
          switchWbTab("code");
        } else {
          alert(data.message || "No se encontró ningún módulo con funciones pendientes.");
        }
      } catch (err) {
        alert(`Error en Arranque Rápido: ${err.message}`);
      } finally {
        btnQuickStart.classList.remove("loading");
        btnQuickStart.innerHTML = origHtml;
      }
    });
  }

  document.getElementById("btn-quick-check").addEventListener("click", () => {
    runCommand("ninja_check", "Ninja Check");
  });

  document.getElementById("btn-quick-build").addEventListener("click", () => {
    runCommand("ninja", "Ninja Build");
  });

  btnKillProcess.addEventListener("click", async () => {
    await fetch("/api/process/kill", { method: "POST" });
  });

  btnClearTerminal.addEventListener("click", () => {
    terminalOutput.textContent = "";
  });

  // --- 3. Dashboard View ---
  async function loadDashboardData() {
    try {
      const [resStatus, resModules] = await Promise.all([
        fetch("/api/status"),
        fetch("/api/modules"),
      ]);
      const statusData = await resStatus.json();
      const modulesData = await resModules.json();

      // Update KPIs
      if (statusData.code_percentage !== undefined) {
        document.getElementById("kpi-code-pct").textContent = `${statusData.code_percentage.toFixed(2)} %`;
        document.getElementById("kpi-code-bar").style.width = `${statusData.code_percentage}%`;
        document.getElementById("kpi-code-bytes").textContent =
          `${statusData.decompiled_bytes.toLocaleString()} / ${statusData.total_bytes.toLocaleString()} bytes`;

        document.getElementById("kpi-funcs-pct").textContent = `${statusData.functions_percentage.toFixed(2)} %`;
        document.getElementById("kpi-funcs-bar").style.width = `${statusData.functions_percentage}%`;
        document.getElementById("kpi-funcs-count").textContent =
          `${statusData.decompiled_functions.toLocaleString()} / ${statusData.total_functions.toLocaleString()} funciones`;
      }

      // Modules
      if (modulesData.modules) {
        currentModules = modulesData.modules;
        const completed = currentModules.filter(m => m.complete);
        document.getElementById("kpi-modules-completed").textContent = `${completed.length} / ${currentModules.length}`;

        const pillsContainer = document.getElementById("kpi-completed-pills");
        pillsContainer.innerHTML = completed.map(m => `<span class="badge badge-success">${m.name}</span>`).join(" ");

        renderModulesTable(currentModules);
      }
    } catch (err) {
      console.error("Error loading dashboard data:", err);
    }
  }

  function renderModulesTable(modules) {
    const tbody = document.getElementById("modules-table-body");
    const searchVal = document.getElementById("module-search").value.toLowerCase();
    const activeFilter = document.querySelector("[data-mod-filter].active")?.dataset.modFilter || "all";

    const filtered = modules.filter(m => {
      const matchesSearch = m.name.toLowerCase().includes(searchVal);
      if (!matchesSearch) return false;
      if (activeFilter === "progress") return !m.complete;
      if (activeFilter === "complete") return m.complete;
      return true;
    });

    if (filtered.length === 0) {
      tbody.innerHTML = `<tr><td colspan="6" class="loading-cell">No se encontraron módulos coincidentes.</td></tr>`;
      return;
    }

    tbody.innerHTML = filtered.map(m => `
      <tr>
        <td><strong>${m.name}</strong></td>
        <td>
          <div style="display: flex; align-items: center; gap: 8px;">
            <div class="progress-bar-container" style="width: 80px;">
              <div class="progress-bar-fill funcs-fill" style="width: ${m.percentage}%"></div>
            </div>
            <span>${m.percentage.toFixed(1)}%</span>
          </div>
        </td>
        <td>${m.decompiled_functions} / ${m.total_functions}</td>
        <td>${m.decompiled_bytes.toLocaleString()} B</td>
        <td>${m.complete ? '<span class="badge badge-success">Completo</span>' : '<span class="badge badge-warning">En progreso</span>'}</td>
        <td>
          <button class="btn btn-xs btn-outline btn-open-module-studio" data-mod="${m.name}">
            Abrir en Studio
          </button>
        </td>
      </tr>
    `).join("");

    document.querySelectorAll(".btn-open-module-studio").forEach(b => {
      b.addEventListener("click", () => {
        const mod = b.dataset.mod;
        switchTab("studio");
        selectStudioModule(mod);
      });
    });
  }

  document.getElementById("module-search").addEventListener("input", () => renderModulesTable(currentModules));
  document.querySelectorAll("[data-mod-filter]").forEach(btn => {
    btn.addEventListener("click", () => {
      document.querySelectorAll("[data-mod-filter]").forEach(b => b.classList.remove("active"));
      btn.classList.add("active");
      renderModulesTable(currentModules);
    });
  });

  // --- 4. Decomp Studio View ---
  async function loadStudioModules() {
    try {
      const res = await fetch("/api/modules");
      const data = await res.json();
      if (data.modules) {
        currentModules = data.modules;
        const select = document.getElementById("studio-module-select");
        select.innerHTML = currentModules.map(m =>
          `<option value="${m.name}">${m.name} (${m.percentage.toFixed(1)}% - ${m.remaining_functions} pendientes)</option>`
        ).join("");

        if (currentModules.length > 0 && !activeModule) {
          selectStudioModule(currentModules[0].name);
        }
      }
    } catch (err) {
      console.error("Error loading studio modules:", err);
    }
  }

  async function selectStudioModule(modName) {
    activeModule = modName;
    document.getElementById("studio-module-select").value = modName;
    const listContainer = document.getElementById("studio-functions-list");
    listContainer.innerHTML = `<div class="empty-hint">Cargando funciones de ${modName}...</div>`;

    try {
      const res = await fetch(`/api/module/${modName}`);
      const data = await res.json();
      if (data.functions) {
        currentFunctions = data.functions;
        renderFunctionsList();
      }
    } catch (err) {
      listContainer.innerHTML = `<div class="empty-hint">Error al cargar funciones.</div>`;
    }
  }

  document.getElementById("studio-module-select").addEventListener("change", (e) => {
    selectStudioModule(e.target.value);
  });

  function renderFunctionsList() {
    const container = document.getElementById("studio-functions-list");
    const searchVal = document.getElementById("studio-func-search").value.toLowerCase();
    const activeFilter = document.querySelector("[data-func-filter].active")?.dataset.funcFilter || "all";

    const filtered = currentFunctions.filter(fn => {
      const matchesSearch = fn.name.toLowerCase().includes(searchVal) || fn.address_hex.toLowerCase().includes(searchVal);
      if (!matchesSearch) return false;
      if (activeFilter === "pending") return !fn.decompiled;
      if (activeFilter === "done") return fn.decompiled;
      return true;
    });

    if (filtered.length === 0) {
      container.innerHTML = `<div class="empty-hint">No hay funciones con los filtros actuales.</div>`;
      return;
    }

    container.innerHTML = filtered.map(fn => {
      let badge = fn.decompiled ? '<span class="badge badge-success">OK</span>' : '<span class="badge badge-neutral">TODO</span>';
      if (fn.nonmatching) badge = '<span class="badge badge-warning">ASM</span>';
      return `
        <div class="func-list-item ${selectedFunction?.name === fn.name ? 'selected' : ''}" data-addr="${fn.address}">
          <div>
            <div class="func-item-name">${fn.name}</div>
            <div class="func-item-sub">${fn.address_hex} &bull; ${fn.size} B</div>
          </div>
          <div>${badge}</div>
        </div>
      `;
    }).join("");

    container.querySelectorAll(".func-list-item").forEach(item => {
      item.addEventListener("click", () => {
        const addr = parseInt(item.dataset.addr);
        const fn = currentFunctions.find(f => f.address === addr);
        if (fn) selectFunction(fn);
      });
    });
  }

  document.getElementById("studio-func-search").addEventListener("input", renderFunctionsList);
  document.querySelectorAll("[data-func-filter]").forEach(btn => {
    btn.addEventListener("click", () => {
      document.querySelectorAll("[data-func-filter]").forEach(b => b.classList.remove("active"));
      btn.classList.add("active");
      renderFunctionsList();
    });
  });

  function selectFunction(fn) {
    selectedFunction = fn;
    document.querySelectorAll(".func-list-item").forEach(item => {
      item.classList.toggle("selected", parseInt(item.dataset.addr) === fn.address);
    });

    document.getElementById("wb-func-name").textContent = fn.name;
    document.getElementById("wb-func-meta").textContent =
      `Módulo: ${activeModule} | Dirección: ${fn.address_hex} | Tamaño: ${fn.size} bytes | Estado: ${fn.decompiled ? "Decompilada" : "Pendiente"}`;
    document.getElementById("wb-action-buttons").style.display = "flex";

    loadFunctionNotes(activeModule, fn.name);
  }

  // Decomp Studio Action Buttons
  document.getElementById("btn-draft-func").addEventListener("click", async () => {
    if (!selectedFunction || !activeModule) return;
    const codeViewer = document.getElementById("wb-code-viewer");
    codeViewer.textContent = "// Generando borrador C++ con tools/draft.py y m2c...";
    switchWbTab("code");

    try {
      const res = await fetch("/api/decomp/draft", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ module: activeModule, address: selectedFunction.address }),
      });
      const data = await res.json();
      codeViewer.textContent = data.code || data.output || "// No se pudo generar el borrador.";
    } catch (err) {
      codeViewer.textContent = `// Error: ${err.message}`;
    }
  });

  document.getElementById("btn-diff-func").addEventListener("click", async () => {
    if (!selectedFunction || !activeModule) return;
    const diffViewer = document.getElementById("wb-diff-viewer");
    diffViewer.textContent = "// Ejecutando tools/diff_function.py con objdiff...";
    switchWbTab("diff");

    try {
      const res = await fetch("/api/decomp/diff", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ file: `src/...`, function: selectedFunction.name }),
      });
      const data = await res.json();
      diffViewer.textContent = data.diff || data.stderr || "// Diferencias no disponibles.";
    } catch (err) {
      diffViewer.textContent = `// Error: ${err.message}`;
    }
  });

  document.getElementById("btn-export-scratch").addEventListener("click", async () => {
    if (!selectedFunction || !activeModule) return;
    const btn = document.getElementById("btn-export-scratch");
    const origText = btn.innerHTML;
    btn.innerHTML = `<span class="btn-icon">⏳</span> Exportando...`;

    try {
      const res = await fetch("/api/decomp/export-scratch", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ module: activeModule, function: selectedFunction.address_hex }),
      });
      const data = await res.json();
      if (data.url) {
        alert(`Scratch creado con éxito:\n${data.url}\n(Copiado al portapapeles)`);
        window.open(data.url, "_blank");
      } else {
        alert(`Resultado de exportación:\n${data.output}`);
      }
    } catch (err) {
      alert(`Error al exportar: ${err.message}`);
    } finally {
      btn.innerHTML = origText;
    }
  });

  function switchWbTab(tabName) {
    document.querySelectorAll(".wb-tab").forEach(t => t.classList.toggle("active", t.dataset.wbTab === tabName));
    document.querySelectorAll(".wb-panel").forEach(p => p.classList.toggle("active", p.id === `wb-panel-${tabName}`));
  }

  document.querySelectorAll(".wb-tab").forEach(t => {
    t.addEventListener("click", () => switchWbTab(t.dataset.wbTab));
  });

  // --- 5. VTable Studio View ---
  async function loadVTablesData() {
    const tbody = document.getElementById("vtables-table-body");
    try {
      const res = await fetch("/api/vtables");
      const data = await res.json();
      if (data.vtables) {
        tbody.innerHTML = data.vtables.map(vt => `
          <tr>
            <td><strong>${vt.class_name}</strong></td>
            <td><span class="badge badge-neutral">${vt.module}</span></td>
            <td><code>${vt.address}</code></td>
            <td><code>${vt.mangled_symbol}</code></td>
            <td>${vt.meta}</td>
            <td>
              <button class="btn btn-xs btn-primary btn-inspect-vtable" data-cls="${vt.class_name}">
                Generar Cabecera .h
              </button>
            </td>
          </tr>
        `).join("");

        document.querySelectorAll(".btn-inspect-vtable").forEach(b => {
          b.addEventListener("click", () => openVTableModal(b.dataset.cls));
        });
      }
    } catch (err) {
      tbody.innerHTML = `<tr><td colspan="6" class="loading-cell">Error al cargar VTables.</td></tr>`;
    }
  }

  document.getElementById("btn-refresh-vtables").addEventListener("click", loadVTablesData);

  async function openVTableModal(className) {
    const modal = document.getElementById("vtable-modal");
    const title = document.getElementById("modal-class-title");
    const viewer = document.getElementById("modal-code-viewer");
    const savePath = document.getElementById("modal-save-path");

    title.textContent = `Clase C++: ${className}`;
    viewer.textContent = "// Generando esqueleto de cabecera con tools/vtable_helper.py...";
    savePath.value = `include/Scene/${className}.h`;
    modal.style.display = "flex";

    try {
      const res = await fetch("/api/vtable/header", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ class_name: className }),
      });
      const data = await res.json();
      viewer.textContent = data.header || "// No se generó código.";
    } catch (err) {
      viewer.textContent = `// Error: ${err.message}`;
    }
  }

  document.getElementById("btn-close-vtable-modal").addEventListener("click", () => {
    document.getElementById("vtable-modal").style.display = "none";
  });

  document.getElementById("btn-save-header").addEventListener("click", async () => {
    const className = document.getElementById("modal-class-title").textContent.replace("Clase C++: ", "");
    const savePath = document.getElementById("modal-save-path").value;
    try {
      const res = await fetch("/api/vtable/header", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ class_name: className, save_path: savePath }),
      });
      const data = await res.json();
      if (data.saved) {
        alert(`Cabecera guardada con éxito en ${savePath}`);
        document.getElementById("vtable-modal").style.display = "none";
      }
    } catch (err) {
      alert(`Error al guardar: ${err.message}`);
    }
  });

  // --- 6. Doctor & Settings View ---
  async function loadDoctorData() {
    const pre = document.getElementById("doctor-output-pre");
    pre.textContent = "Ejecutando diagnóstico de salud del entorno (tools/doctor.py)...";

    try {
      const res = await fetch("/api/doctor");
      const data = await res.json();
      pre.textContent = data.output || "Diagnóstico completado.";

      // Update ROM badges
      const romBadge = document.getElementById("badge-rom-eur");
      if (data.output.includes("European Base ROM (baserom_dqix_eur.nds): SHA-1 verified")) {
        romBadge.className = "badge badge-success";
        romBadge.textContent = "Presente y Verificada";
      } else {
        romBadge.className = "badge badge-warning";
        romBadge.textContent = "Falta en extract/";
      }
    } catch (err) {
      pre.textContent = `Error al ejecutar doctor: ${err.message}`;
    }
  }

  document.getElementById("btn-run-doctor-now").addEventListener("click", loadDoctorData);

  // --- 7. Notes & Tags System ---
  let noteSaveTimeout = null;

  async function loadFunctionNotes(moduleName, funcName) {
    const notesContainer = document.getElementById("studio-notes-container");
    const notesInput = document.getElementById("func-notes-input");
    const savedStatus = document.getElementById("notes-status-saved");
    const historyStats = document.getElementById("func-history-stats");
    const tagPills = document.querySelectorAll(".tag-pill");

    if (!notesContainer || !funcName) return;
    notesContainer.style.display = "flex";
    notesInput.value = "";
    savedStatus.textContent = "Sincronizando...";

    try {
      const [resNote, resHist] = await Promise.all([
        fetch(`/api/store/notes/${moduleName}/${encodeURIComponent(funcName)}`),
        fetch(`/api/store/history/${moduleName}`)
      ]);
      const noteData = await resNote.json();
      const histData = await resHist.json();

      notesInput.value = noteData.notes || "";
      const activeTags = new Set(noteData.tags || []);
      tagPills.forEach(pill => {
        pill.classList.toggle("active", activeTags.has(pill.dataset.tag));
      });

      if (noteData.updated_at) {
        const timePart = noteData.updated_at.split("T")[1]?.slice(0, 5) || "";
        savedStatus.textContent = `Guardado (${timePart})`;
      } else {
        savedStatus.textContent = "Guardado ✓";
      }

      if (Array.isArray(histData) && histData.length > 0) {
        const latest = histData[histData.length - 1];
        historyStats.textContent = `${latest.decompiled_funcs}/${latest.total_funcs} funciones coincidentes (${latest.percent_code.toFixed(1)}% bytes)`;
      } else {
        historyStats.textContent = "Sin historial previo";
      }
    } catch (err) {
      savedStatus.textContent = "Sin sincronizar";
    }
  }

  function saveCurrentFunctionNotes() {
    if (!selectedFunction || !activeModule) return;
    const notesInput = document.getElementById("func-notes-input");
    const savedStatus = document.getElementById("notes-status-saved");
    savedStatus.textContent = "Guardando...";

    const activeTags = Array.from(document.querySelectorAll(".tag-pill.active")).map(p => p.dataset.tag);
    fetch("/api/store/notes", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({
        module: activeModule,
        function: selectedFunction.name,
        notes: notesInput.value,
        tags: activeTags,
      })
    }).then(res => res.json()).then(data => {
      savedStatus.textContent = "Guardado ✓";
    }).catch(() => {
      savedStatus.textContent = "Error al guardar";
    });
  }

  document.querySelectorAll(".tag-pill").forEach(pill => {
    pill.addEventListener("click", () => {
      pill.classList.toggle("active");
      saveCurrentFunctionNotes();
    });
  });

  const funcNotesInput = document.getElementById("func-notes-input");
  if (funcNotesInput) {
    funcNotesInput.addEventListener("input", () => {
      const savedStatus = document.getElementById("notes-status-saved");
      if (savedStatus) savedStatus.textContent = "Escribiendo...";
      clearTimeout(noteSaveTimeout);
      noteSaveTimeout = setTimeout(saveCurrentFunctionNotes, 600);
    });
  }

  // --- 8. Parallel Task Manager & Queue UI ---
  const taskDrawer = document.getElementById("task-queue-drawer");
  const btnToggleQueue = document.getElementById("btn-toggle-queue");
  const btnCloseDrawer = document.getElementById("btn-close-queue-drawer");
  const queueBadge = document.getElementById("queue-badge-active");
  const drawerWorkers = document.getElementById("drawer-workers-status");
  const drawerQueueState = document.getElementById("drawer-queue-state");
  const queueTasksTbody = document.getElementById("queue-tasks-tbody");
  const btnQueuePause = document.getElementById("btn-queue-pause");
  const btnQueueStopCurrent = document.getElementById("btn-queue-stop-current");
  const btnQueueCancelAll = document.getElementById("btn-queue-cancel-all");

  let queueSummary = { tasks: [], is_paused: false, stop_after_current: false };

  function toggleQueueDrawer() {
    if (taskDrawer) taskDrawer.classList.toggle("collapsed");
  }

  if (btnToggleQueue) btnToggleQueue.addEventListener("click", toggleQueueDrawer);
  if (btnCloseDrawer) btnCloseDrawer.addEventListener("click", () => taskDrawer?.classList.add("collapsed"));

  const drawerHeader = document.querySelector(".queue-drawer-header");
  if (drawerHeader) {
    drawerHeader.addEventListener("click", (e) => {
      if (e.target.closest(".drawer-controls")) return;
      toggleQueueDrawer();
    });
  }

  async function refreshTaskQueue() {
    try {
      const res = await fetch("/api/tasks");
      const data = await res.json();
      queueSummary = data;

      if (queueBadge) queueBadge.textContent = data.active_workers || 0;
      if (drawerWorkers) drawerWorkers.textContent = `Workers: ${data.active_workers || 0}/${data.max_workers || 4}`;

      if (drawerQueueState) {
        if (data.is_paused) {
          drawerQueueState.className = "badge badge-warning";
          drawerQueueState.textContent = "Pausada";
          if (btnQueuePause) btnQueuePause.textContent = "▶️ Reanudar";
        } else if (data.active_workers > 0) {
          drawerQueueState.className = "badge badge-info";
          drawerQueueState.textContent = "Procesando";
          if (btnQueuePause) btnQueuePause.textContent = "⏸️ Pausar";
        } else {
          drawerQueueState.className = "badge badge-neutral";
          drawerQueueState.textContent = "En reposo";
          if (btnQueuePause) btnQueuePause.textContent = "⏸️ Pausar";
        }
      }

      if (btnQueueStopCurrent) {
        if (data.stop_after_current) {
          btnQueueStopCurrent.classList.add("btn-danger");
          btnQueueStopCurrent.textContent = "⏹️ Parar tras actual (ACTIVO)";
        } else {
          btnQueueStopCurrent.classList.remove("btn-danger");
          btnQueueStopCurrent.textContent = "⏹️ Parar tras actual";
        }
      }

      renderQueueTable(data.tasks || []);
    } catch (err) {
      // Ignore transient fetch drop
    }
  }

  function renderQueueTable(tasks) {
    if (!queueTasksTbody) return;
    if (!tasks || tasks.length === 0) {
      queueTasksTbody.innerHTML = `<tr><td colspan="7" class="loading-cell">No hay tareas en curso ni en cola.</td></tr>`;
      return;
    }

    queueTasksTbody.innerHTML = tasks.slice().reverse().map(t => {
      let badgeCls = `badge-task-${t.status}`;
      let statusLabel = t.status;
      if (t.status === "running") statusLabel = "En curso";
      if (t.status === "queued") statusLabel = "En cola";
      if (t.status === "completed") statusLabel = "Completado";
      if (t.status === "failed") statusLabel = "Fallido";
      if (t.status === "cancelled") statusLabel = "Cancelado";

      const dur = t.duration !== undefined ? `${t.duration.toFixed(1)}s` : "--";
      const out = (t.output || t.error || "").slice(-80);

      return `
        <tr>
          <td><code>${t.id.slice(0, 6)}</code></td>
          <td><strong>${t.label}</strong></td>
          <td><code>${t.action_type}</code></td>
          <td>${t.module || "-"}</td>
          <td><span class="badge ${badgeCls}">${statusLabel}</span></td>
          <td>${dur}</td>
          <td class="mono-text" style="font-size: 11px; max-width: 250px; overflow: hidden; text-overflow: ellipsis; white-space: nowrap;">
            ${out || "-"}
          </td>
        </tr>
      `;
    }).join("");
  }

  if (btnQueuePause) {
    btnQueuePause.addEventListener("click", async () => {
      const action = queueSummary.is_paused ? "resume" : "pause";
      await fetch("/api/tasks/control", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ action })
      });
      refreshTaskQueue();
    });
  }

  if (btnQueueStopCurrent) {
    btnQueueStopCurrent.addEventListener("click", async () => {
      await fetch("/api/tasks/control", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ action: "stop_after_current", enabled: !queueSummary.stop_after_current })
      });
      refreshTaskQueue();
    });
  }

  if (btnQueueCancelAll) {
    btnQueueCancelAll.addEventListener("click", async () => {
      await fetch("/api/tasks/control", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ action: "cancel_all" })
      });
      refreshTaskQueue();
    });
  }

  // --- 9. Concurrency & Hardware Settings ---
  async function loadConcurrencySettings() {
    try {
      const res = await fetch("/api/store/config");
      const cfg = await res.json();
      const slider = document.getElementById("cfg-max-workers");
      const valLabel = document.getElementById("cfg-max-workers-val");
      const stopOnError = document.getElementById("cfg-stop-on-error");
      const cpuBadge = document.getElementById("detected-cpu-badge");
      const coresHint = document.getElementById("cfg-cores-hint");

      if (cfg.detected_cores) {
        if (slider) slider.max = Math.max(16, cfg.detected_cores * 2);
        if (cpuBadge) cpuBadge.textContent = `${cfg.detected_cores} núcleos CPU detectados`;
        if (coresHint) coresHint.textContent = `Detectados ${cfg.detected_cores} núcleos lógicos en este equipo. Recomendado: ${Math.max(1, cfg.detected_cores - 1)}.`;
      }

      if (cfg.max_workers !== undefined) {
        if (slider) slider.value = cfg.max_workers;
        if (valLabel) valLabel.textContent = `${cfg.max_workers} workers`;
      }
      if (cfg.stop_on_error !== undefined && stopOnError) {
        stopOnError.checked = Boolean(cfg.stop_on_error);
      }
    } catch (err) {
      console.error("Error loading config:", err);
    }
  }

  const sliderMaxWorkers = document.getElementById("cfg-max-workers");
  if (sliderMaxWorkers) {
    sliderMaxWorkers.addEventListener("input", (e) => {
      const valLabel = document.getElementById("cfg-max-workers-val");
      if (valLabel) valLabel.textContent = `${e.target.value} workers`;
    });
  }

  const btnSaveConcurrency = document.getElementById("btn-save-concurrency-cfg");
  if (btnSaveConcurrency) {
    btnSaveConcurrency.addEventListener("click", async () => {
      const maxWorkers = parseInt(document.getElementById("cfg-max-workers").value);
      const stopOnError = document.getElementById("cfg-stop-on-error").checked;
      const feedback = document.getElementById("cfg-save-feedback");

      try {
        await fetch("/api/store/config", {
          method: "POST",
          headers: { "Content-Type": "application/json" },
          body: JSON.stringify({ max_workers: maxWorkers, stop_on_error: stopOnError })
        });
        if (feedback) {
          feedback.style.display = "inline";
          setTimeout(() => feedback.style.display = "none", 2500);
        }
        refreshTaskQueue();
      } catch (err) {
        alert(`Error al guardar configuración: ${err.message}`);
      }
    });
  }

  // --- 10. Auto-Pilot (Modo Automático) Controller ---
  let apState = { is_running: false, stop_requested: false, paused: false };
  let apDefaults = null;
  let apConfigLoaded = false;
  let apConfigDirty = false;
  let apResultsTimer = 0;

  const AP_STATUS_LABELS = {
    matched: "100%",
    near: "Casi-match",
    no_match: "No coincide",
    compile_error: "No compila",
    m2c_failed: "m2c falló",
    error: "Error",
  };
  const AP_BOOL_FIELDS = ["retry_failed", "integrate", "record_progress", "auto_commit", "keep_awake", "low_priority", "auto_start"];
  const AP_NUMBER_FIELDS = ["min_size", "max_size", "batch_size", "max_functions", "max_hours", "batch_pause_seconds",
    "max_consecutive_errors", "jobs", "permute_seconds", "permute_threshold"];

  const apEl = (id) => document.getElementById(id);
  const apForm = () => apEl("ap-config-form");

  function formatDuration(sec) {
    sec = Math.max(0, Math.floor(sec || 0));
    const h = Math.floor(sec / 3600);
    const m = Math.floor((sec % 3600) / 60);
    const s = sec % 60;
    return h > 0
      ? `${h}:${String(m).padStart(2, "0")}:${String(s).padStart(2, "0")}`
      : `${String(m).padStart(2, "0")}:${String(s).padStart(2, "0")}`;
  }

  function escapeHtml(text) {
    return String(text ?? "").replace(/[&<>"']/g, (c) => ({ "&": "&amp;", "<": "&lt;", ">": "&gt;", '"': "&quot;", "'": "&#39;" }[c]));
  }

  // Configuration form
  function fillConfigForm(config) {
    const form = apForm();
    if (!form) return;
    form.scope.value = config.scope;
    const wanted = new Set(config.modules || []);
    Array.from(form.modules.options).forEach((opt) => { opt.selected = wanted.has(opt.value); });
    // Modules saved earlier that the list doesn't have (complete since) stay selected
    wanted.forEach((name) => {
      if (!Array.from(form.modules.options).some((opt) => opt.value === name)) {
        form.modules.add(new Option(name, name, true, true));
      }
    });
    form.exclude_modules.value = (config.exclude_modules || []).join(", ");
    form.order.value = config.order;
    form.stop_at.value = config.stop_at || "";
    AP_NUMBER_FIELDS.forEach((name) => { form[name].value = config[name]; });
    AP_BOOL_FIELDS.forEach((name) => { form[name].checked = !!config[name]; });
    updateModulesFieldState();
    apConfigDirty = false;
  }

  function readConfigForm() {
    const form = apForm();
    const config = {
      scope: form.scope.value,
      modules: Array.from(form.modules.selectedOptions).map((opt) => opt.value),
      exclude_modules: form.exclude_modules.value,
      order: form.order.value,
      stop_at: form.stop_at.value,
    };
    AP_NUMBER_FIELDS.forEach((name) => { config[name] = form[name].value === "" ? null : Number(form[name].value); });
    AP_BOOL_FIELDS.forEach((name) => { config[name] = form[name].checked; });
    return config;
  }

  function updateModulesFieldState() {
    const form = apForm();
    if (!form) return;
    const field = form.querySelector(".ap-modules-field");
    if (field) field.classList.toggle("disabled", form.scope.value !== "modules");
  }

  function setConfigStatus(text, isError = false) {
    const status = apEl("ap-config-status");
    if (!status) return;
    status.textContent = text;
    status.classList.toggle("text-warning", isError);
  }

  async function loadAutoPilotModules() {
    try {
      const res = await fetch("/api/modules");
      const data = await res.json();
      const modules = (data.modules || []).slice().sort((a, b) => a.name.localeCompare(b.name));
      const form = apForm();
      const resultsModule = apEl("ap-results-module");
      if (form) {
        form.modules.innerHTML = "";
        modules.filter((m) => m.remaining_functions > 0).forEach((m) => {
          form.modules.add(new Option(`${m.name} · ${m.remaining_functions} pendientes · ${m.percentage}%`, m.name));
        });
      }
      if (resultsModule) {
        resultsModule.innerHTML = `<option value="">Todos los módulos</option>`;
        modules.forEach((m) => resultsModule.add(new Option(m.name, m.name)));
      }
    } catch (err) {
      // The list stays empty; the saved modules are still added by fillConfigForm
    }
  }

  async function loadAutoPilotConfig() {
    try {
      await loadAutoPilotModules();
      const res = await fetch("/api/autopilot/config");
      const data = await res.json();
      apDefaults = data.defaults;
      fillConfigForm(data.config);
      apConfigLoaded = true;
    } catch (err) {
      setConfigStatus(`No se pudo cargar la configuración: ${err.message}`, true);
    }
  }

  async function saveAutoPilotConfig() {
    const res = await fetch("/api/autopilot/config", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ config: readConfigForm() }),
    });
    const data = await res.json();
    if (data.config) fillConfigForm(data.config);
    setConfigStatus(`Guardada a las ${new Date().toLocaleTimeString()}`);
    return data.config;
  }

  // Status
  async function refreshAutoPilotStatus() {
    let data;
    try {
      const res = await fetch("/api/autopilot/status");
      data = await res.json();
    } catch (err) {
      return; // Ignore background network transient
    }
    apState = data;
    const st = data.stats || {};
    const stage = st.stage || data.stage || "idle";

    const banner = apEl("ap-integration-banner");
    if (banner) {
      const blocked = data.integration_blocked;
      banner.style.display = blocked ? "block" : "none";
      if (blocked) {
        banner.textContent = `⚠️ No se puede integrar en el build: dsd no puede ejecutarse (${blocked}). ` +
          `Los matches se guardan en build/autopilot/matched/ y se integrarán con “Integrar pendientes” cuando dsd funcione.`;
      }
    }

    apEl("ap-metric-time").textContent = formatDuration(st.elapsed_seconds);
    apEl("ap-metric-time-sub").textContent = data.is_running && st.remaining_seconds != null
      ? `Quedan ${formatDuration(st.remaining_seconds)}`
      : (data.is_running ? "Sin límite de tiempo" : "Duración de la sesión");
    apEl("ap-metric-matches").textContent = st.matches_100 || 0;
    apEl("ap-metric-processed-sub").textContent =
      `${st.integrated || 0} integradas · ${st.pending_integration || 0} pendientes`;
    apEl("ap-metric-processed").textContent = st.processed || 0;
    apEl("ap-metric-breakdown").textContent =
      `${st.near || 0} casi · ${st.no_match || 0} no · ${st.compile_errors || 0} no compilan · ${st.tool_errors || 0} errores`;
    apEl("ap-metric-drafts").textContent = `${st.batch_drafts || 0} / ${st.batch_total || st.draft_limit || 0}`;
    apEl("ap-metric-drafts-sub").textContent = `Lote #${st.current_batch || 1} · ${st.batches_completed || 0} completados`;

    const btnToggle = apEl("btn-autopilot-toggle");
    const statusBadge = apEl("ap-status-badge");
    const metricPhase = apEl("ap-metric-phase");
    const metricTarget = apEl("ap-metric-target");
    const btnStart = apEl("btn-ap-card-start");
    const btnStop = apEl("btn-ap-card-stop");
    const btnPause = apEl("btn-ap-pause");
    const btnKill = apEl("btn-ap-kill");
    const btnIntegrate = apEl("btn-ap-integrate");
    const liveLogBox = apEl("ap-live-log");
    const logPhaseMsg = apEl("ap-log-phase-msg");
    const logPreview = apEl("ap-log-preview");

    const stageText = { preflight: "Verificando entorno", drafting: "m2c + compilación", matching: "permute + integración" }[stage] || "En curso";
    const batch = st.current_batch || 1;

    if (data.is_running) {
      let badgeClass = "badge badge-info";
      let badgeText = `Lote #${batch} • ${stageText}`;
      let toggleClass = "btn btn-autopilot running";
      let toggleText = "Parar tras actual";
      if (data.stop_requested) {
        badgeClass = "badge badge-warning";
        badgeText = data.immediate_stop ? "Deteniendo ya..." : "Deteniendo tras actual...";
        toggleClass = "btn btn-autopilot stopping";
        toggleText = badgeText;
      } else if (data.paused) {
        badgeClass = "badge badge-warning";
        badgeText = "En pausa";
      }
      if (btnToggle) {
        btnToggle.className = toggleClass;
        btnToggle.innerHTML = `<span class="btn-icon">${data.stop_requested ? "⏳" : "⏹️"}</span> <span id="autopilot-btn-text">${toggleText}</span>`;
        btnToggle.title = "Detener limpiamente tras finalizar las funciones en curso";
      }
      if (statusBadge) { statusBadge.className = badgeClass; statusBadge.textContent = badgeText; }
      if (metricPhase) metricPhase.textContent = data.paused ? "En pausa" : `Lote #${batch} • ${stageText}`;
      if (metricTarget) {
        metricTarget.textContent = data.current_module
          ? `${data.current_module}::${data.current_function?.name || ""}`
          : (data.phase_message || "Procesando...");
      }
      btnStart.style.display = "none";
      btnStop.style.display = "inline-flex";
      btnStop.disabled = !!data.stop_requested;
      btnKill.style.display = data.immediate_stop ? "none" : "inline-flex";
      btnPause.style.display = data.stop_requested ? "none" : "inline-flex";
      btnPause.innerHTML = data.paused ? `<span class="btn-icon">▶️</span> Reanudar` : `<span class="btn-icon">⏸️</span> Pausar`;
      btnIntegrate.disabled = true;
    } else {
      if (btnToggle) {
        btnToggle.className = "btn btn-autopilot";
        btnToggle.innerHTML = `<span class="btn-icon">🚀</span> <span id="autopilot-btn-text">Modo Automático</span>`;
        btnToggle.title = "Modo Automático: decompilación continua desatendida con la configuración guardada";
      }
      if (statusBadge) {
        statusBadge.className = stage === "completed" ? "badge badge-success" : "badge badge-neutral";
        statusBadge.textContent = data.busy_integrating ? "Integrando..." : (stage === "completed" ? "Sesión completada ✓" : "En reposo");
      }
      if (metricPhase) metricPhase.textContent = stage === "completed" ? "Sesión completada ✓" : "En reposo";
      if (metricTarget) metricTarget.textContent = data.last_session?.stop_reason || "Sin tarea activa";
      btnStart.style.display = "inline-flex";
      btnStop.style.display = "none";
      btnPause.style.display = "none";
      btnKill.style.display = "none";
      btnIntegrate.disabled = !!data.busy_integrating;
    }

    const hasLog = (data.log_preview || []).length > 0;
    if (liveLogBox) liveLogBox.style.display = hasLog ? "flex" : "none";
    if (logPhaseMsg) logPhaseMsg.textContent = data.is_running ? (data.phase_message || "Modo automático activo") : "Última sesión";
    if (logPreview && hasLog) {
      const atBottom = logPreview.scrollTop + logPreview.clientHeight >= logPreview.scrollHeight - 20;
      logPreview.textContent = data.log_preview.join("");
      if (atBottom) logPreview.scrollTop = logPreview.scrollHeight;
    }

    const last = apEl("ap-last-session");
    if (last && data.last_session?.ended_at) {
      const ls = data.last_session;
      last.textContent = `Última: ${ls.ended_at} · ${formatDuration(ls.duration_seconds)} · ${ls.processed} intentadas · ` +
        `${ls.matches_100} al 100% · ${ls.integrated} integradas · ${ls.stop_reason || "completada"}`;
    }

    // While it runs, the results table follows it (at most every 10 s)
    const resultsOpen = apEl("ap-results-section")?.open;
    if (data.is_running && resultsOpen && Date.now() - apResultsTimer > 10000) loadAutoPilotResults();
  }

  // Results
  async function loadAutoPilotResults() {
    apResultsTimer = Date.now();
    const status = apEl("ap-results-status")?.value || "";
    const module = apEl("ap-results-module")?.value || "";
    const params = new URLSearchParams({ limit: "300" });
    if (status) params.set("status", status);
    if (module) params.set("module", module);
    try {
      const res = await fetch(`/api/autopilot/results?${params}`);
      const data = await res.json();
      const summary = data.summary || { total: {}, integrated: 0, tried: 0 };
      const chips = apEl("ap-results-chips");
      const total = summary.total || {};
      chips.innerHTML = [`<span class="badge badge-neutral">${summary.tried} intentadas</span>`,
        `<span class="badge badge-success">${summary.integrated} integradas</span>`]
        .concat(Object.keys(AP_STATUS_LABELS).filter((k) => total[k])
          .map((k) => `<span class="badge ap-status-${k}">${AP_STATUS_LABELS[k]}: ${total[k]}</span>`)).join(" ");
      apEl("ap-results-inline").textContent =
        `· ${total.matched || 0} al 100% · ${summary.integrated} integradas · ${summary.tried} intentadas`;
      const body = apEl("ap-results-body");
      const entries = data.entries || [];
      body.innerHTML = entries.length === 0
        ? `<tr><td colspan="7">Sin resultados para este filtro.</td></tr>`
        : entries.map((e) => `<tr>
            <td>${escapeHtml(e.module)}</td>
            <td class="mono" title="${escapeHtml(e.function)}">${escapeHtml(e.function)}</td>
            <td class="mono">${e.size}</td>
            <td><span class="badge ap-status-${escapeHtml(e.status)}">${AP_STATUS_LABELS[e.status] || escapeHtml(e.status)}${e.integrated ? " ✓ build" : ""}${e.permuted ? " · permute" : ""}</span></td>
            <td class="mono">${Number(e.percent || 0).toFixed(1)}</td>
            <td class="ap-note" title="${escapeHtml(e.note)}">${escapeHtml((e.note || "").split("\n")[0])}</td>
            <td class="mono">${escapeHtml(e.timestamp)}</td>
          </tr>`).join("");
    } catch (err) {
      apEl("ap-results-body").innerHTML = `<tr><td colspan="7">Error al cargar resultados: ${escapeHtml(err.message)}</td></tr>`;
    }
  }

  async function resetAutoPilotResults() {
    const status = apEl("ap-results-status")?.value || "";
    const module = apEl("ap-results-module")?.value || "";
    if (status === "matched" || status === "integrated") {
      alert("Los matches no se reintentan: ya coinciden al 100%.");
      return;
    }
    const what = `${status ? AP_STATUS_LABELS[status] : "todas las que no coincidieron"}${module ? ` de ${module}` : ""}`;
    if (!confirm(`¿Olvidar los resultados (${what}) para que el modo automático las intente otra vez?`)) return;
    const res = await fetch("/api/autopilot/results/reset", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ statuses: status ? [status] : null, module: module || null }),
    });
    const data = await res.json();
    alert(`${data.reset} funciones se intentarán otra vez.`);
    loadAutoPilotResults();
  }

  // Sessions
  async function loadAutoPilotSessions() {
    const select = apEl("ap-session-select");
    try {
      const res = await fetch("/api/autopilot/sessions");
      const sessions = await res.json();
      const previous = select.value;
      select.innerHTML = sessions.length ? "" : `<option value="">Sin sesiones todavía</option>`;
      sessions.forEach((s) => select.add(new Option(`${s.name} (${Math.ceil(s.size / 1024)} KB)`, s.name)));
      if (previous && sessions.some((s) => s.name === previous)) select.value = previous;
      if (select.value) loadAutoPilotSession(select.value);
    } catch (err) {
      select.innerHTML = `<option value="">Error al cargar</option>`;
    }
  }

  async function loadAutoPilotSession(name) {
    const pre = apEl("ap-session-log");
    try {
      const res = await fetch(`/api/autopilot/session?name=${encodeURIComponent(name)}`);
      const data = await res.json();
      pre.textContent = data.text || data.error || "";
      pre.scrollTop = pre.scrollHeight;
    } catch (err) {
      pre.textContent = `Error: ${err.message}`;
    }
  }

  // Controls
  async function startAutoPilot() {
    try {
      if (!apConfigLoaded) await loadAutoPilotConfig();
      const config = readConfigForm();
      if (config.scope === "modules" && config.modules.length === 0) {
        alert("Elige al menos un módulo, o cambia el ámbito a “Todos los módulos”.");
        return;
      }
      const res = await fetch("/api/autopilot/start", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ config }),
      });
      const data = await res.json();
      if (data.started) {
        setConfigStatus("Guardada e iniciada");
        apConfigDirty = false;
        refreshAutoPilotStatus();
      } else {
        alert("El Modo Automático ya se encuentra en ejecución o no se pudo iniciar.");
      }
    } catch (err) {
      alert(`Error al iniciar Modo Automático: ${err.message}`);
    }
  }

  async function postAutoPilot(path, body = {}) {
    try {
      await fetch(path, { method: "POST", headers: { "Content-Type": "application/json" }, body: JSON.stringify(body) });
    } catch (err) {
      alert(`Error: ${err.message}`);
    }
    refreshAutoPilotStatus();
  }

  const stopAutoPilot = (graceful = true) => postAutoPilot("/api/autopilot/stop", { graceful });

  async function ensureDoctorTools() {
    const btn = apEl("btn-ap-ensure-tools");
    const origHtml = btn.innerHTML;
    btn.innerHTML = `<span class="btn-icon">⏳</span> Verificando...`;
    btn.disabled = true;

    try {
      const res = await fetch("/api/doctor/ensure", { method: "POST" });
      const data = await res.json();
      if (data.ok) {
        alert("¡Verificación de herramientas exitosa!\nTodas las herramientas (Ninja, dsd, objdiff, mwccarm, m2c) están listas para operar en este PC.");
      } else {
        alert("Aviso al verificar herramientas:\n" + (data.logs || []).join("\n"));
      }
    } catch (err) {
      alert(`Error al verificar herramientas: ${err.message}`);
    } finally {
      btn.innerHTML = origHtml;
      btn.disabled = false;
    }
  }

  // Bind Auto-Pilot Buttons
  apEl("btn-autopilot-toggle")?.addEventListener("click", () => {
    if (apState.is_running) {
      stopAutoPilot(true);
    } else {
      startAutoPilot();
    }
  });
  apEl("btn-ap-card-start")?.addEventListener("click", startAutoPilot);
  apEl("btn-ap-card-stop")?.addEventListener("click", () => stopAutoPilot(true));
  apEl("btn-ap-kill")?.addEventListener("click", () => {
    if (confirm("¿Parar ya? Las herramientas en curso se terminan; una integración a medias restaura la configuración.")) {
      stopAutoPilot(false);
    }
  });
  apEl("btn-ap-pause")?.addEventListener("click", () =>
    postAutoPilot(apState.paused ? "/api/autopilot/resume" : "/api/autopilot/pause"));
  apEl("btn-ap-integrate")?.addEventListener("click", () => postAutoPilot("/api/autopilot/integrate"));
  apEl("btn-ap-ensure-tools")?.addEventListener("click", ensureDoctorTools);
  apEl("btn-ap-save-config")?.addEventListener("click", () =>
    saveAutoPilotConfig().catch((err) => setConfigStatus(`Error al guardar: ${err.message}`, true)));
  apEl("btn-ap-default-config")?.addEventListener("click", () => {
    if (apDefaults) {
      fillConfigForm(apDefaults);
      apConfigDirty = true;
      setConfigStatus("Valores por defecto (sin guardar)");
    }
  });
  apForm()?.addEventListener("input", () => {
    apConfigDirty = true;
    setConfigStatus("Cambios sin guardar");
    updateModulesFieldState();
  });
  apEl("ap-results-section")?.addEventListener("toggle", (event) => { if (event.target.open) loadAutoPilotResults(); });
  apEl("ap-sessions-section")?.addEventListener("toggle", (event) => { if (event.target.open) loadAutoPilotSessions(); });
  apEl("ap-results-status")?.addEventListener("change", loadAutoPilotResults);
  apEl("ap-results-module")?.addEventListener("change", loadAutoPilotResults);
  apEl("btn-ap-results-refresh")?.addEventListener("click", loadAutoPilotResults);
  apEl("btn-ap-reset-failed")?.addEventListener("click", resetAutoPilotResults);
  apEl("btn-ap-session-refresh")?.addEventListener("click", loadAutoPilotSessions);
  apEl("ap-session-select")?.addEventListener("change", (event) => { if (event.target.value) loadAutoPilotSession(event.target.value); });
  window.addEventListener("beforeunload", (event) => {
    if (apConfigDirty) event.preventDefault();
  });
  loadAutoPilotConfig();

  // Initial Load
  setupSSE();
  loadDashboardData();
  loadConcurrencySettings();
  refreshTaskQueue();
  refreshAutoPilotStatus();
  setInterval(refreshTaskQueue, 2500);
  setInterval(refreshAutoPilotStatus, 2000);
});
