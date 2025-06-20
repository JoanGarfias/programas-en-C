# ✅ Proyecto: Simulador Round Robin en C con GTK y Glade

## 🧱 Fase 1: Preparación del entorno
- [x] Instalar las librerías necesarias:
  - `sudo apt install libgtk-3-dev`
  - `sudo apt install glade`
- [x] Crear estructura de carpetas del proyecto:
  - `src/` para código fuente.
  - `assets/` para archivo `.glade`.
  - `build/` para binarios.
- [x] Crear archivo `.glade` con Glade:
  - [x] Botón “Ejecutar”
  - [x] Botón “Salir”
  - [x] `GtkDrawingArea` para visualizar la simulación

## 🧠 Fase 2: Modelado y lógica de simulación
- [x] Definir `struct Proceso` con:
  - ID, tiempo restante, estado, posición x/y
- [x] Crear estructuras para:
  - Cola de listos
  - Lista de bloqueados
- [x] Generar hasta 8 procesos:
  - ID 0 a 7
  - Tiempo aleatorio entre 30 y 90 (múltiplos de 15)
- [ ] Implementar algoritmo Round Robin:
  - [ ] Ejecutar por 15 unidades de tiempo
  - [ ] Si termina → eliminar
  - [ ] Si no → volver a encolar

## 🧩 Fase 3: Interfaz y visualización
- [ ] Conectar señales desde Glade:
  - Botón Ejecutar
  - Botón Salir
- [ ] Dibujar procesos en `GtkDrawingArea`
- [ ] Mostrar ID y tiempo restante
- [ ] Usar `g_timeout_add()` para simular el paso del tiempo
- [ ] Redibujar cada vez que cambie el estado

## 🎮 Fase 4: Interacción con el "killer"
- [ ] Dibujar killer (cuadro o ícono)
- [ ] Mover killer con flechas del teclado
- [ ] Detectar colisión con proceso ejecutando
  - [ ] Mover proceso a bloqueados
  - [ ] Reducir tiempo por segundo hasta 15
  - [ ] Reencolar o terminar

## ⚠️ Fase 5: Concurrencia y condiciones de carrera
- [ ] Evitar acceso simultáneo a listas
- [ ] Asegurar que no se encolen 2 procesos al mismo tiempo
- [ ] Asegurar que no se actualice área de dibujo mientras se modifica

## 🧪 Fase 6: Finalización y reinicio
- [ ] Detectar cuando todos los procesos terminan
- [ ] Mostrar nuevamente botón “Ejecutar”
- [ ] Permitir reiniciar simulación

## 🎥 Fase 7: Grabación del video
- [ ] Grabar simulación explicando:
  - Round Robin
  - Estados de procesos
  - Killer en acción
  - Código fuente
- [ ] Participación equitativa de ambos miembros
- [ ] Subir a YouTube (modo público o no listado)