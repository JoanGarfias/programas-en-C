# Guión para Video: Simulador de Procesos Round Robin
## "SimProc: Una Aventura Interactiva en Sistemas Operativos"

---

## **PRESENTADOR 1 (Minutos 0-5): Introducción y Conceptos Teóricos**

### **0:00 - 0:30: Apertura**
¡Hola a todos! Bienvenidos a este video donde vamos a explorar uno de los algoritmos más importantes en sistemas operativos: el **Round Robin**. Pero no será una clase aburrida de teoría, sino que vamos a ver cómo funciona en la práctica con un simulador interactivo que desarrollamos en C usando GTK.

### **0:30 - 1:30: ¿Qué es Round Robin?**
Antes de meternos en el código, necesitamos entender qué hace este algoritmo. Imagina que tienes varios procesos esperando para ejecutarse en tu computadora. El Round Robin es como un chef que atiende a todos sus clientes de manera justa: le da a cada proceso un tiempo fijo llamado "quantum" para ejecutarse, y si no termina, lo pone al final de la fila para que espere su turno nuevamente.

En nuestro simulador, cada proceso tendrá un quantum de 15 unidades de tiempo. Si un proceso necesita más tiempo, se va al final de la cola de "listos" y el siguiente proceso toma el control.

### **1:30 - 2:30: Estados de los Procesos**
Los procesos en nuestro sistema pueden estar en diferentes estados:
- **Listo**: Esperando su turno para ejecutarse
- **Ejecutando**: Actualmente usando el CPU
- **Bloqueado/Suspendido**: Pausado temporalmente (¡aquí es donde viene la diversión!)
- **Terminado**: Ya completó su trabajo

### **2:30 - 3:30: La Interactividad - El Elemento Killer**
Aquí está la parte divertida: mientras los procesos se ejecutan, tú puedes controlar un personaje en pantalla usando las flechas del teclado. Si tu personaje toca un proceso que está ejecutándose, ¡lo bloqueas! Ese proceso se va a la cola de "suspendidos" y tiene que esperar 15 unidades de tiempo antes de poder volver a la cola de listos.

### **3:30 - 4:30: Estructura del Proyecto**
Nuestro simulador está construido con:
- **GTK+3**: Para la interfaz gráfica
- **Cairo**: Para dibujar los procesos y animaciones
- **GStreamer**: Para efectos de sonido
- **Pthreads**: Para manejar la simulación en paralelo

### **4:30 - 5:00: Transición**
Ahora voy a pasarle el micrófono a mi compañero, que nos va a mostrar cómo funciona todo esto en la práctica y nos explicará el código detalladamente.

---

## **PRESENTADOR 2 (Minutos 5-10): Implementación y Demostración**

### **5:00 - 5:30: Bienvenida y Transición**
¡Perfecto! Ahora vamos a ver cómo todo esto se traduce en código real. Vamos a explorar las partes más importantes del simulador y luego lo ejecutaremos para ver la magia en acción.

### **5:30 - 6:30: Análisis del Código Clave**
Primero, miremos la estructura de datos principal. Cada proceso se representa con una estructura que contiene:
```c
typedef struct proc {
    int id;                    // Identificador único
    int tiempoRestante;        // Tiempo que le queda
    int estado;               // En qué estado está
    struct proc *siguiente;   // Para la cola
} PROCESO;
```

Las colas son fundamentales aquí. Tenemos dos:
- **Cola de Listos**: Procesos esperando ejecutarse
- **Cola de Suspendidos**: Procesos bloqueados por el usuario

### **6:30 - 7:30: La Simulación en Acción**
Ahora vamos a ejecutar el simulador. Como pueden ver, tenemos 8 procesos inicialmente en estado "listo", cada uno con un tiempo aleatorio entre 30 y 90 unidades. El proceso en la cabeza de la cola pasa a ejecutarse y aparece en una posición aleatoria en pantalla.

Observen cómo el tiempo va disminuyendo segundo a segundo. Cuando llega a 15, el proceso vuelve a la cola de listos y el siguiente proceso toma el control.

### **7:30 - 8:30: La Interactividad en Funcionamiento**
Ahora viene la parte divertida. Voy a mover el personaje morado usando las flechas del teclado. ¡Miren! Cuando toco el proceso que está ejecutándose, se bloquea y se va a la cola de suspendidos. El sistema automáticamente toma el siguiente proceso de la cola de listos.

Los procesos suspendidos tienen un contador que va de 15 a 0. Cuando llega a 0, vuelven a la cola de listos con un quantum completo.

### **8:30 - 9:30: Sincronización y Prevención de Condiciones de Carrera**
Una parte crucial del código es la sincronización. Usamos mutexes para evitar que dos hilos modifiquen las colas al mismo tiempo:

```c
g_mutex_lock(&mutexCola);
// Operaciones con las colas
g_mutex_unlock(&mutexCola);
```

Esto garantiza que no tengamos condiciones de carrera cuando un proceso termina y otro sale de suspendidos al mismo tiempo.

### **9:30 - 10:00: Cierre y Aplicaciones Prácticas**
Como pueden ver, este simulador no solo es educativo, sino que también demuestra conceptos reales que se usan en sistemas operativos modernos. El Round Robin se utiliza en muchos sistemas, desde Linux hasta Windows, para garantizar que todos los procesos tengan una oportunidad justa de ejecutarse.

La interactividad añade una dimensión práctica que nos ayuda a entender cómo los procesos pueden ser interrumpidos y cómo el sistema maneja estas interrupciones.

¡Espero que hayan disfrutado esta demostración! No olviden suscribirse para más contenido sobre programación y sistemas operativos.

---

## **NOTAS TÉCNICAS PARA LA PRODUCCIÓN**

### **Comandos de Compilación:**
```bash
gcc -o build/SimProc src/SimProc.c -Wall `pkg-config --cflags --libs gtk+-3.0 gstreamer-1.0` -lm -lpthread -export-dynamic
```

### **Dependencias:**
- GTK+3
- GStreamer
- Cairo
- Pthreads

### **Estructura del Proyecto:**
```
SimProc/
├── src/
│   └── SimProc.c
├── assets/
│   ├── SimProc.glade
│   └── *.wav
└── build/
```

### **Elementos Visuales Sugeridos:**
- Capturas de pantalla del código con resaltado de sintaxis
- Demostración en vivo del simulador funcionando
- Diagramas de flujo de los estados de procesos
- Animaciones de las colas y transiciones

### **Puntos de Edición:**
- Transición suave entre presentadores en el minuto 5
- Zoom en secciones importantes del código
- Split-screen para mostrar código y ejecución simultáneamente
- Efectos de sonido para las colisiones y transiciones de estado 