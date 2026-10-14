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
    if (tabId === "settings") loadDoctorData();
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

  // Initial Load
  setupSSE();
  loadDashboardData();
});
