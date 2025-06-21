# SimProc - Simulador de Procesos Round Robin con Interacción de Usuario

## 📋 Descripción General

SimProc es un simulador educativo de procesos que implementa el algoritmo de planificación **Round Robin** con características interactivas. El proyecto está desarrollado en **C** utilizando **GTK+3** para la interfaz gráfica y **GStreamer** para efectos de sonido.

### 🎯 Objetivos del Proyecto

- Demostrar el funcionamiento del algoritmo Round Robin
- Visualizar el manejo de colas de procesos (listos y suspendidos)
- Implementar interacción de usuario mediante colisiones
- Simular suspensión de procesos por eventos externos
- Proporcionar una experiencia educativa interactiva

## 🏗️ Arquitectura del Sistema

### Conceptos de Sistemas Operativos Implementados

#### 1. **Concurrencia y Paralelismo**
- **Hilos (Threads)**: Utilizamos `pthread` para separar la lógica de simulación de la interfaz gráfica
- **Ejecución Concurrente**: El hilo de simulación ejecuta procesos mientras la GUI se actualiza independientemente
- **Sincronización**: Uso de mutexes para proteger las estructuras de datos compartidas

#### 2. **Planificación de Procesos**
- **Algoritmo Round Robin**: Cada proceso recibe un quantum fijo de 15 unidades de tiempo
- **Colas de Procesos**: Implementación de colas FIFO para procesos listos y suspendidos
- **Estados de Proceso**: 
  - `ESTADO_LISTO` (1): Proceso esperando CPU
  - `ESTADO_EJECUTANDO` (2): Proceso en CPU
  - `ESTADO_SUSPENDIDO` (5): Proceso suspendido por colisión
  - `ESTADO_TERMINADO` (4): Proceso completado

#### 3. **Sincronización y Exclusión Mutua**
- **Mutex**: `GMutex mutexCola` protege el acceso a las colas de procesos
- **Race Conditions**: Evitadas mediante bloqueo de secciones críticas
- **Consistencia de Datos**: Garantizada en operaciones de encolado/desencolado

#### 4. **Gestión de Memoria**
- **Asignación Dinámica**: Uso de `malloc()` y `free()` para estructuras de proceso
- **Prevención de Memory Leaks**: Liberación explícita de memoria al terminar procesos

## 📊 Estructuras de Datos

### 1. **Estructura PROCESO**
```c
typedef struct proc {
    int id;                    // Identificador único del proceso
    int tiempoRestante;        // Tiempo total restante para completar
    int estado;               // Estado actual del proceso
    int x, y;                 // Posición en la interfaz gráfica
    int tiempoSuspension;     // Tiempo restante en suspensión
    int quantumRestante;      // Quantum restante para este proceso
    struct proc *siguiente;   // Puntero al siguiente proceso en la cola
} PROCESO;
```

### 2. **Estructura COLA**
```c
typedef struct colaproc {
    PROCESO *primero;         // Puntero al primer proceso en la cola
    PROCESO *ultimo;          // Puntero al último proceso en la cola
} COLA;
```

### 3. **Variables Globales Clave**
```c
// Control de simulación
pthread_t hiloSimulacion;
gboolean simulacionActiva = FALSE;
GMutex mutexCola;

// Proceso en ejecución
int idProcesoEnEjecucion = -1;
int tiempoProcesoEnEjecucion = 0;
int posXEjecucion, posYEjecucion;
PROCESO *procesoEnEjecucion = NULL;

// Colas de procesos
COLA colaListos;
COLA colaSuspendidos;
```

## 🔄 Algoritmos Implementados

### 1. **Algoritmo Round Robin**

```c
// Bucle principal de simulación
while(simulacionActiva) {
    // Obtener proceso de la cola de listos
    PROCESO *proceso = desencolarListos();
    
    // Ejecutar por quantum fijo (15 unidades)
    for(int i = 0; i < proceso->quantumRestante && !procesoTerminado; i++) {
        proceso->tiempoRestante--;
        proceso->quantumRestante = cuanto - (i+1);
        
        // Verificar si se suspendió por colisión
        if(proceso->estado == ESTADO_SUSPENDIDO) {
            proceso->tiempoSuspension = proceso->quantumRestante;
            encolarSuspendidos(proceso);
            break;
        }
        
        g_usleep(1000000); // 1 segundo por unidad
    }
    
    // Si no terminó, volver a cola de listos con quantum completo
    if(!procesoTerminado && proceso->estado != ESTADO_SUSPENDIDO) {
        proceso->quantumRestante = 15;
        encolarListos(proceso);
    }
}
```

### 2. **Gestión de Colas FIFO**

#### Encolado
```c
void encolarListos(PROCESO *nuevo) {
    nuevo->siguiente = NULL;
    if(colaListos.primero == NULL) {
        colaListos.primero = colaListos.ultimo = nuevo;
    } else {
        colaListos.ultimo->siguiente = nuevo;
        colaListos.ultimo = nuevo;
    }
}
```

#### Desencolado
```c
PROCESO *desencolarListos() {
    if(colaListos.primero == NULL) return NULL;
    
    PROCESO *desencolado = colaListos.primero;
    colaListos.primero = desencolado->siguiente;
    desencolado->siguiente = NULL;
    
    if(colaListos.primero == NULL) {
        colaListos.ultimo = NULL;
    }
    return desencolado;
}
```

### 3. **Detección de Colisiones**
```c
gboolean detectarColision(int personajeX, int personajeY, int personajeTamano, 
                         int procesoX, int procesoY, int procesoRadio) {
    int distanciaX = abs(personajeX - procesoX);
    int distanciaY = abs(personajeY - procesoY);
    
    int minDistanciaX = personajeTamano/2 + procesoRadio;
    int minDistanciaY = personajeTamano/2 + procesoRadio;
    
    return (distanciaX < minDistanciaX && distanciaY < minDistanciaY);
}
```

## 🎨 Sistema de Renderizado

### 1. **Renderizado de Cola de Listos**

```c
// Dibujar cola de listos
PROCESO *p = obtenerPrimeroEnColaListos();
int contador = 0;
int radio = 20;
int espaciado = 60;
int inicioX = 50;
int inicioY = 50;

while(p != NULL && contador < NUM_PROCESOS) {
    int x = inicioX + (contador * espaciado);
    int y = inicioY + 10;
    
    // Color según estado
    switch(p->estado) {
        case ESTADO_LISTO:
            cairo_set_source_rgb(cr, 0.2, 0.8, 0.2); // Verde
            break;
        case ESTADO_EJECUTANDO:
            cairo_set_source_rgb(cr, 0.8, 0.8, 0.2); // Amarillo
            break;
        // ... otros estados
    }
    
    // Dibujar círculo del proceso
    cairo_arc(cr, x, y, radio, 0, 2 * M_PI);
    cairo_fill_preserve(cr);
    cairo_stroke(cr);
    
    // Dibujar ID del proceso
    snprintf(texto, sizeof(texto), "P%d", p->id);
    cairo_show_text(cr, texto);
    
    // Dibujar tiempo restante
    snprintf(texto, sizeof(texto), "%d", p->tiempoRestante);
    cairo_show_text(cr, texto);
    
    p = p->siguiente;
    contador++;
}
```

### 2. **Renderizado de Cola de Suspendidos**

Similar al de listos, pero:
- Posición: `inicioYSusp = 350`
- Color: Rojo apagado `(0.7, 0.3, 0.3)`
- Muestra tiempo de suspensión restante

### 3. **Renderizado de Proceso en Ejecución**

```c
if(idProcesoEnEjecucion >= 0) {
    int radio = 18;
    
    // Color según estado (bloqueado o ejecutando)
    if(procesoBloqueado) {
        cairo_set_source_rgb(cr, 0.6, 0.6, 0.6); // Gris
    } else {
        cairo_set_source_rgb(cr, 1.0, 0.6, 0.0); // Naranja
    }
    
    // Dibujar círculo de ejecución
    cairo_arc(cr, posXEjecucion, posYEjecucion, radio, 0, 2 * M_PI);
    cairo_fill_preserve(cr);
    cairo_stroke(cr);
    
    // Etiqueta de estado
    if(procesoBloqueado) {
        cairo_show_text(cr, "BLOQUEADO");
    } else {
        cairo_show_text(cr, "EJECUTANDO");
    }
}
```

### 4. **Renderizado del Personaje**

```c
// Personaje controlable (cuadrado morado)
cairo_set_source_rgb(cr, 0.5, 0.0, 0.8);  // Color morado
cairo_rectangle(cr, personajeX - personajeTamano/2, 
               personajeY - personajeTamano/2, 
               personajeTamano, personajeTamano);
cairo_fill_preserve(cr);
cairo_stroke(cr);
```

## 🎮 Sistema de Interacción

### 1. **Control del Personaje**

```c
gboolean on_draw_key_press_event(GtkDrawingArea *widget, GdkEventKey *event) {
    int velocidad = 10;
    int nuevaX = personajeX;
    int nuevaY = personajeY;
    
    switch(event->keyval) {
        case GDK_KEY_Left:  case GDK_KEY_A: case GDK_KEY_a:
            nuevaX -= velocidad; break;
        case GDK_KEY_Right: case GDK_KEY_D: case GDK_KEY_d:
            nuevaX += velocidad; break;
        case GDK_KEY_Up:    case GDK_KEY_W: case GDK_KEY_w:
            nuevaY -= velocidad; break;
        case GDK_KEY_Down:  case GDK_KEY_S: case GDK_KEY_s:
            nuevaY += velocidad; break;
    }
    
    // Wrap-around en bordes de pantalla
    if(nuevaX < 0) nuevaX = anchoPantalla - personajeTamano/2;
    if(nuevaX > anchoPantalla - personajeTamano/2) nuevaX = 0;
    if(nuevaY < 0) nuevaY = altoPantalla - personajeTamano/2;
    if(nuevaY > altoPantalla - personajeTamano/2) nuevaY = 0;
    
    // Verificar colisión con proceso en ejecución
    if(idProcesoEnEjecucion >= 0 && !procesoBloqueado && 
       detectarColision(nuevaX, nuevaY, personajeTamano, 
                       posXEjecucion, posYEjecucion, 18)) {
        procesoBloqueado = TRUE;
        procesoEnEjecucion->estado = ESTADO_SUSPENDIDO;
        reproducirSonidoBloqueado();
    } else {
        personajeX = nuevaX;
        personajeY = nuevaY;
    }
}
```

### 2. **Sistema de Colisiones**

- **Detección**: Algoritmo de distancia euclidiana simplificado
- **Efecto**: Suspensión inmediata del proceso en ejecución
- **Tiempo de Suspensión**: Igual al quantum restante del proceso
- **Sonido**: Efecto de sonido al colisionar

## 🔊 Sistema de Audio

### Implementación con GStreamer

```c
void reproducirSonido(const char* archivo, GstElement **pipeline) {
    if(!sonidosHabilitados) return;
    
    // Limpiar pipeline anterior
    if(*pipeline != NULL) {
        gst_element_set_state(*pipeline, GST_STATE_NULL);
        gst_object_unref(*pipeline);
    }
    
    // Construir URI del archivo de sonido
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        char uri[2048];
        snprintf(uri, sizeof(uri), "playbin uri=file://%s/src/%s", cwd, archivo);
        
        *pipeline = gst_parse_launch(uri, NULL);
        if(*pipeline != NULL) {
            gst_element_set_state(*pipeline, GST_STATE_PLAYING);
            g_usleep(100000); // Pequeño delay para reproducción
        }
    }
}
```

### Tipos de Sonidos
- **Ejecución**: `ejecucion.wav` - Cuando un proceso inicia ejecución
- **Bloqueo**: `bloqueado.wav` - Cuando ocurre una colisión
- **Terminación**: `terminado.wav` - Cuando un proceso termina

## ⏱️ Control de Tiempo

### 1. **Temporización de Simulación**

```c
// Refresco de GUI cada 1 segundo
g_timeout_add(1000, refrescar, NULL);

// Pausa entre iteraciones de simulación
g_usleep(1000000); // 1 segundo = 1 unidad de tiempo
```

### 2. **Generación de Tiempos de Proceso**

```c
int generarTiempoRestante() {
    int escalador = rand() % 5; // 0 a 4
    return 30 + (escalador * MULTIPLO); // 30 a 90 unidades
}
```

### 3. **Gestión de Quantum**

- **Quantum Fijo**: 15 unidades de tiempo por proceso
- **Quantum Restante**: Se decrementa durante la ejecución
- **Renovación**: Quantum completo al volver a cola de listos

## 📈 Estadísticas y Monitoreo

### 1. **Contadores en Tiempo Real**

```c
// Variables de estadísticas
int procesosTerminados = 0;
int countListos = 0;
int countSuspendidos = 0;

// Renderizado de estadísticas
char stats1[64], stats2[64], stats3[64];
snprintf(stats1, sizeof(stats1), "Terminados: %d", procesosTerminados);
snprintf(stats2, sizeof(stats2), "Listos: %d", countListos);
snprintf(stats3, sizeof(stats3), "Suspendidos: %d", countSuspendidos);
```

### 2. **Pantalla de Victoria**

```c
if (procesosTerminados == NUM_PROCESOS) {
    if (!victoriaSonando) {
        reproducirSonidoTerminado();
        victoriaSonando = TRUE;
    }
    
    // Mostrar mensaje de victoria
    cairo_set_source_rgb(cr, 0.1, 0.6, 0.1);
    cairo_set_font_size(cr, 48);
    cairo_show_text(cr, "¡VICTORIA!");
}
```

## 🔧 Funciones Clave del Sistema

### 1. **Gestión de Procesos**

```c
void crearProceso(PROCESO *proceso, int id, int tiempoRestante, 
                 int estado, int x, int y) {
    proceso->id = id;
    proceso->tiempoRestante = tiempoRestante;
    proceso->estado = estado;
    proceso->x = x;
    proceso->y = y;
    proceso->tiempoSuspension = 0;
    proceso->quantumRestante = MULTIPLO; // 15 unidades
    proceso->siguiente = NULL;
}
```

### 2. **Función Principal de Simulación**

```c
void *funcionSimulacion(void *arg) {
    while(simulacionActiva) {
        // Lógica de Round Robin
        // Gestión de colas
        // Control de tiempo
        // Manejo de colisiones
    }
    return NULL;
}
```

### 3. **Gestión de Memoria**

```c
// Limpieza al terminar simulación
while(colaListos.primero != NULL) {
    PROCESO *p = desencolarListos();
    if(p != NULL) free(p);
}
while(colaSuspendidos.primero != NULL) {
    PROCESO *p = desencolarSuspendidos();
    if(p != NULL) free(p);
}
```

## 🚀 Compilación y Ejecución

### Comando de Compilación
```bash
gcc -o build/SimProc src/SimProc.c -Wall \
    `pkg-config --cflags --libs gtk+-3.0 gstreamer-1.0` \
    -lm -lpthread -export-dynamic
```

### Dependencias
- **GTK+3**: Interfaz gráfica
- **GStreamer**: Efectos de sonido
- **Pthread**: Concurrencia
- **Cairo**: Renderizado gráfico

### Archivos Requeridos
- `src/SimProc.c`: Código fuente principal
- `assets/SimProc.glade`: Diseño de interfaz
- `src/*.wav`: Archivos de sonido

## 🎓 Aspectos Educativos

### 1. **Conceptos Demostrados**
- **Planificación de Procesos**: Round Robin en acción
- **Estados de Proceso**: Transiciones entre estados
- **Colas de Procesos**: FIFO y gestión de prioridades
- **Concurrencia**: Hilos y sincronización
- **Interrupciones**: Simuladas mediante colisiones

### 2. **Aprendizaje Interactivo**
- **Visualización**: Estados de procesos en tiempo real
- **Interacción**: Control directo del personaje
- **Feedback**: Efectos de sonido y visuales
- **Estadísticas**: Monitoreo en tiempo real

## 🔍 Características Técnicas Avanzadas

### 1. **Thread Safety**
- Uso de mutexes para proteger estructuras compartidas
- Separación de hilos para GUI y simulación
- Manejo seguro de memoria dinámica

### 2. **Optimización de Rendimiento**
- Refresco eficiente de GUI
- Gestión optimizada de colas
- Liberación oportuna de memoria

### 3. **Robustez del Sistema**
- Manejo de errores en operaciones de archivo
- Validación de estados de proceso
- Prevención de condiciones de carrera

## 📝 Conclusión

SimProc es un proyecto educativo completo que demuestra conceptos fundamentales de sistemas operativos de manera interactiva y visual. Combina teoría de planificación de procesos con implementación práctica, proporcionando una herramienta valiosa para el aprendizaje de conceptos de concurrencia, sincronización y gestión de procesos.

El proyecto utiliza tecnologías modernas como GTK+3 y GStreamer, demostrando cómo implementar sistemas complejos en C con interfaces gráficas profesionales y efectos multimedia. 