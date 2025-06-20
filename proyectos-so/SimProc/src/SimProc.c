/**
 * Compilar: gcc -o build/SimProc src/SimProc.c -Wall `pkg-config --cflags --libs gtk+-3.0 gstreamer-1.0` -lm -lpthread -export-dynamic
 * */
 
#define ESTADO_LISTO 1
#define ESTADO_EJECUTANDO 2
#define ESTADO_BLOQUEADO 3
#define ESTADO_TERMINADO 4

#define MULTIPLO 5
 
#define NUM_PROCESOS 8

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>  // Para getcwd()
#include <gst/gst.h>  // Para efectos de sonido

/*Declaración de estructuras*/

typedef struct proc{
    int id;
    int tiempoRestante;
    int estado;
    int x;
    int y;
    struct proc *siguiente;
}PROCESO;

typedef struct colaproc{
    PROCESO *primero;
    PROCESO *ultimo;
}COLA;

/*Variables globales para el manejo de hilos*/
pthread_t hiloSimulacion;
gboolean simulacionActiva = FALSE;
GMutex mutexCola;

/*Variables para el proceso en ejecución*/
int idProcesoEnEjecucion = -1;
int tiempoProcesoEnEjecucion = 0;
int posXEjecucion = 300;
int posYEjecucion = 200;
gboolean procesoBloqueado = FALSE;

/*Variables para el personaje controlable*/
int personajeX = 400;
int personajeY = 300;
int personajeTamano = 20;

/*Variables para efectos de sonido*/
GstElement *pipelineEjecucion = NULL;
GstElement *pipelineBloqueo = NULL;
GstElement *pipelineTerminado = NULL;
gboolean sonidosHabilitados = TRUE;

/*Declaración de variables*/

GtkWidget *window;
GtkWidget *draw;
GtkWidget *btnEjecutar;
GtkWidget *btnSalir;
COLA cola;
gboolean refrescar(gpointer);

/*Prototipos de funciones*/

void on_window_destroy();
void on_btnSalir_clicked();
gboolean refrescar(gpointer);
void on_btnEjecutar_clicked();
gboolean on_draw_draw(GtkDrawingArea *, cairo_t *);
gboolean on_draw_key_press_event(GtkDrawingArea *, GdkEventKey *);
void iniciarSimulacion();
void dibujarProcesos(cairo_t *);

void encolar(PROCESO *);
PROCESO *desencolar();
PROCESO *obtenerPrimeroEnCola();

void crearProceso(PROCESO *, int, int, int, int, int);
int obtenerTiempoRestante(PROCESO *);
int obtenerEstado(PROCESO *);
int generarTiempoRestante();

gboolean detectarColision(int personajeX, int personajeY, int personajeTamano, 
                         int procesoX, int procesoY, int procesoRadio);

void *funcionSimulacion(void *arg);

gboolean reactivarBotonEjecutar(gpointer data);

// Función para reactivar el botón de ejecutar (se ejecuta en el hilo principal)
gboolean reactivarBotonEjecutar(gpointer data) {
    gtk_widget_show(btnEjecutar);
    simulacionActiva = FALSE;
    
    // Limpiar estado de la simulación
    idProcesoEnEjecucion = -1;
    procesoBloqueado = FALSE;
    posXEjecucion = 300;
    posYEjecucion = 200;
    
    // Limpiar pipelines de GStreamer
    if(pipelineEjecucion != NULL) {
        gst_element_set_state(pipelineEjecucion, GST_STATE_NULL);
        gst_object_unref(pipelineEjecucion);
        pipelineEjecucion = NULL;
    }
    if(pipelineBloqueo != NULL) {
        gst_element_set_state(pipelineBloqueo, GST_STATE_NULL);
        gst_object_unref(pipelineBloqueo);
        pipelineBloqueo = NULL;
    }
    if(pipelineTerminado != NULL) {
        gst_element_set_state(pipelineTerminado, GST_STATE_NULL);
        gst_object_unref(pipelineTerminado);
        pipelineTerminado = NULL;
    }
    
    printf("Botón de ejecutar reactivado - Listo para nueva simulación\n");
    return FALSE;  // No repetir
}

// Función para reproducir sonido de proceso en ejecución
void reproducirSonidoEjecucion() {
    if(!sonidosHabilitados) return;
    
    if(pipelineEjecucion != NULL) {
        gst_element_set_state(pipelineEjecucion, GST_STATE_NULL);
        gst_object_unref(pipelineEjecucion);
    }
    
    // Obtener el directorio actual de trabajo y subir un nivel si estamos en build/
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        char uri[2048];
        // Si estamos en la carpeta build, subir un nivel
        if (strstr(cwd, "/build") != NULL) {
            // Encontrar la posición de /build y cortar ahí
            char *build_pos = strstr(cwd, "/build");
            if (build_pos != NULL) {
                *build_pos = '\0';  // Cortar en /build
            }
        }
        snprintf(uri, sizeof(uri), "playbin uri=file://%s/src/ejecucion.wav", cwd);
        printf("Intentando reproducir: %s\n", uri);
        
        pipelineEjecucion = gst_parse_launch(uri, NULL);
        if(pipelineEjecucion != NULL) {
            gst_element_set_state(pipelineEjecucion, GST_STATE_PLAYING);
            printf("Sonido de ejecución iniciado\n");
            g_usleep(100000);  // Pequeño delay para asegurar reproducción
        } else {
            printf("Error al crear pipeline para sonido de ejecución\n");
        }
    } else {
        printf("Error al obtener directorio actual\n");
    }
}

// Función para reproducir sonido de proceso bloqueado
void reproducirSonidoBloqueado() {
    if(!sonidosHabilitados) return;
    
    if(pipelineBloqueo != NULL) {
        gst_element_set_state(pipelineBloqueo, GST_STATE_NULL);
        gst_object_unref(pipelineBloqueo);
    }
    
    // Obtener el directorio actual de trabajo y subir un nivel si estamos en build/
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        char uri[2048];
        // Si estamos en la carpeta build, subir un nivel
        if (strstr(cwd, "/build") != NULL) {
            // Encontrar la posición de /build y cortar ahí
            char *build_pos = strstr(cwd, "/build");
            if (build_pos != NULL) {
                *build_pos = '\0';  // Cortar en /build
            }
        }
        snprintf(uri, sizeof(uri), "playbin uri=file://%s/src/bloqueado.wav", cwd);
        printf("Intentando reproducir: %s\n", uri);
        
        pipelineBloqueo = gst_parse_launch(uri, NULL);
        if(pipelineBloqueo != NULL) {
            gst_element_set_state(pipelineBloqueo, GST_STATE_PLAYING);
            printf("Sonido de bloqueo iniciado\n");
            g_usleep(100000);  // Pequeño delay para asegurar reproducción
        } else {
            printf("Error al crear pipeline para sonido de bloqueo\n");
        }
    } else {
        printf("Error al obtener directorio actual\n");
    }
}

// Función para reproducir sonido de proceso terminado
void reproducirSonidoTerminado() {
    if(!sonidosHabilitados) return;
    
    if(pipelineTerminado != NULL) {
        gst_element_set_state(pipelineTerminado, GST_STATE_NULL);
        gst_object_unref(pipelineTerminado);
    }
    
    // Obtener el directorio actual de trabajo y subir un nivel si estamos en build/
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        char uri[2048];
        // Si estamos en la carpeta build, subir un nivel
        if (strstr(cwd, "/build") != NULL) {
            // Encontrar la posición de /build y cortar ahí
            char *build_pos = strstr(cwd, "/build");
            if (build_pos != NULL) {
                *build_pos = '\0';  // Cortar en /build
            }
        }
        snprintf(uri, sizeof(uri), "playbin uri=file://%s/src/terminado.wav", cwd);
        printf("Intentando reproducir: %s\n", uri);
        
        pipelineTerminado = gst_parse_launch(uri, NULL);
        if(pipelineTerminado != NULL) {
            gst_element_set_state(pipelineTerminado, GST_STATE_PLAYING);
            printf("Sonido de terminado iniciado\n");
            g_usleep(100000);  // Pequeño delay para asegurar reproducción
        } else {
            printf("Error al crear pipeline para sonido de terminado\n");
        }
    } else {
        printf("Error al obtener directorio actual\n");
    }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    GtkBuilder *builder;

    gtk_init(&argc, &argv);
    
    // Inicializar GStreamer
    gst_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "../assets/SimProc.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    draw = GTK_WIDGET(gtk_builder_get_object(builder, "draw"));
    btnEjecutar = GTK_WIDGET(gtk_builder_get_object(builder, "btnEjecutar"));
    btnSalir = GTK_WIDGET(gtk_builder_get_object(builder, "btnSalir"));
    gtk_builder_connect_signals(builder, NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}

/*Interfaz gráfica*/

void on_window_destroy()
{
    simulacionActiva = FALSE;
    if(pthread_join(hiloSimulacion, NULL) != 0) {
        fprintf(stderr, "Error al esperar el hilo de simulación\n");
    }
    g_mutex_clear(&mutexCola);
    
    // Limpiar pipelines de GStreamer
    if(pipelineEjecucion != NULL) {
        gst_element_set_state(pipelineEjecucion, GST_STATE_NULL);
        gst_object_unref(pipelineEjecucion);
    }
    if(pipelineBloqueo != NULL) {
        gst_element_set_state(pipelineBloqueo, GST_STATE_NULL);
        gst_object_unref(pipelineBloqueo);
    }
    if(pipelineTerminado != NULL) {
        gst_element_set_state(pipelineTerminado, GST_STATE_NULL);
        gst_object_unref(pipelineTerminado);
    }
    
    gtk_main_quit();
    int i;
    for(i = 0; i < NUM_PROCESOS; i++){
        PROCESO *proceso = desencolar();
        if(proceso != NULL)
            free(proceso);
    }
}

void on_btnSalir_clicked()
{
	on_window_destroy();
}

gboolean refrescar(gpointer data)
{
    gtk_widget_queue_draw(GTK_WIDGET(draw));
    return TRUE;  // Retornar TRUE para que el temporizador continúe ejecutándose
}

void on_btnEjecutar_clicked()
{
    gtk_widget_hide(btnEjecutar);
    
    // Si ya hay una simulación activa, esperar a que termine el hilo anterior
    if(simulacionActiva) {
        simulacionActiva = FALSE;
        if(pthread_join(hiloSimulacion, NULL) != 0) {
            fprintf(stderr, "Error al esperar el hilo de simulación anterior\n");
        }
    }
    
    // Limpiar la cola existente si hay procesos
    g_mutex_lock(&mutexCola);
    while(cola.primero != NULL) {
        PROCESO *p = desencolar();
        if(p != NULL) {
            free(p);
        }
    }
    g_mutex_unlock(&mutexCola);
    
    // Reinicializar mutex
    g_mutex_clear(&mutexCola);
    g_mutex_init(&mutexCola);
    
    simulacionActiva = TRUE;
    
    int i;
    for(i=0; i < NUM_PROCESOS; i++){
        PROCESO *proceso = (PROCESO *)malloc(sizeof(PROCESO));
        crearProceso(proceso, i, generarTiempoRestante(), ESTADO_LISTO, 10, 10);
        encolar(proceso);
    }

    if(pthread_create(&hiloSimulacion, NULL, funcionSimulacion, NULL) != 0) {
        fprintf(stderr, "Error al crear el hilo de simulación\n");
        return;
    }
    
    // Configurar un temporizador para actualizar la interfaz
    g_timeout_add(500, refrescar, NULL);
    
    printf("Nueva simulación iniciada con %d procesos\n", NUM_PROCESOS);
}

void *funcionSimulacion(void *arg) {
    int i;
    while(simulacionActiva) {
        g_mutex_lock(&mutexCola);
        
        // Si hay un proceso bloqueado, no permitir que otros procesos se ejecuten
        if(procesoBloqueado && idProcesoEnEjecucion >= 0) {
            g_mutex_unlock(&mutexCola);
            g_usleep(500000);  // Esperar 0.5 segundos
            continue;
        }
        
        if(cola.primero == NULL){
            printf("Cola vacía - Simulación terminada\n");
            g_mutex_unlock(&mutexCola);
            
            // Reactivar el botón de ejecutar en el hilo principal
            g_idle_add((GSourceFunc)reactivarBotonEjecutar, NULL);
            break;
        }

        PROCESO *proceso = desencolar();
        if(proceso == NULL) {
            g_mutex_unlock(&mutexCola);
            continue;
        }
        proceso->estado = ESTADO_EJECUTANDO;
        
        // Actualizar información del proceso en ejecución
        idProcesoEnEjecucion = proceso->id;
        tiempoProcesoEnEjecucion = proceso->tiempoRestante;
        posXEjecucion = 50 + (rand() % 600);  // Posición X aleatoria entre 50 y 650
        posYEjecucion = 50 + (rand() % 400);  // Posición Y aleatoria entre 50 y 450
        
        // Reproducir sonido de proceso en ejecución
        reproducirSonidoEjecucion();
        
        g_mutex_unlock(&mutexCola);

        gboolean procesoTerminado = FALSE;
        for(i = 0; i < 15 && simulacionActiva && !procesoTerminado; i++){
            proceso->tiempoRestante--;
            tiempoProcesoEnEjecucion = proceso->tiempoRestante;  // Actualizar tiempo en ejecución
            if(proceso->tiempoRestante <= 0){
                proceso->estado = ESTADO_TERMINADO;
                printf("Proceso %d terminado\n", proceso->id);
                
                // Reproducir sonido de proceso terminado
                reproducirSonidoTerminado();
                
                procesoTerminado = TRUE;
            }
            g_usleep(500000);  // 0.5 segundos en microsegundos
        }

        g_mutex_lock(&mutexCola);
        if(procesoTerminado) {
            free(proceso);
            idProcesoEnEjecucion = -1;  // No hay proceso en ejecución
            procesoBloqueado = FALSE;   // Limpiar estado bloqueado
        } else if(simulacionActiva) {
            proceso->estado = ESTADO_LISTO;
            encolar(proceso);
            idProcesoEnEjecucion = -1;  // No hay proceso en ejecución
            procesoBloqueado = FALSE;   // Limpiar estado bloqueado
        }

        // Imprimir estado de la cola
        printf("\nCola de procesos:\n");
        PROCESO *p = obtenerPrimeroEnCola();
        while(p != NULL){
            printf("Proceso %d : \n\tDirección %p\n\tEstado %d\n\tTiempo restante %d\n", 
                   p->id, (void*)p, p->estado, p->tiempoRestante);
            p = p->siguiente;
        }
        g_mutex_unlock(&mutexCola);
    }

    // Limpieza final de la cola si la simulación termina
    g_mutex_lock(&mutexCola);
    while(cola.primero != NULL) {
        PROCESO *p = desencolar();
        if(p != NULL) {
            free(p);
        }
    }
    g_mutex_unlock(&mutexCola);
    
    return NULL;
}

gboolean on_draw_draw(GtkDrawingArea *widget, cairo_t *cr)
{
    // Fondo blanco
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);

    // Dibujar los procesos
    dibujarProcesos(cr);

    return FALSE;
}

gboolean on_draw_key_press_event(GtkDrawingArea *widget, GdkEventKey *event)
{
    gboolean bCambio = FALSE;
    int velocidad = 10;  // Píxeles por movimiento
    int nuevaX = personajeX;
    int nuevaY = personajeY;

    switch(event->keyval){
        case GDK_KEY_Left:  case GDK_KEY_A: case GDK_KEY_a:
            nuevaX -= velocidad;
            break;

        case GDK_KEY_Right: case GDK_KEY_D: case GDK_KEY_d:
            nuevaX += velocidad;
            break;

        case GDK_KEY_Up:    case GDK_KEY_W: case GDK_KEY_w:
            nuevaY -= velocidad;
            break;

        case GDK_KEY_Down:  case GDK_KEY_S: case GDK_KEY_s:
            nuevaY += velocidad;
            break;
    }

    // Verificar colisión solo si hay un proceso en ejecución y no está bloqueado
    if(idProcesoEnEjecucion >= 0 && !procesoBloqueado) {
        if(detectarColision(nuevaX, nuevaY, personajeTamano, posXEjecucion, posYEjecucion, 18)) {
            printf("¡COLISIÓN! Proceso %d bloqueado\n", idProcesoEnEjecucion);
            procesoBloqueado = TRUE;
            
            // Reproducir sonido de proceso bloqueado
            reproducirSonidoBloqueado();
            
            bCambio = TRUE;
        } else {
            // Solo mover si no hay colisión
            personajeX = nuevaX;
            personajeY = nuevaY;
            bCambio = TRUE;
        }
    } else {
        // Si no hay proceso en ejecución o ya está bloqueado, mover normalmente
        personajeX = nuevaX;
        personajeY = nuevaY;
        bCambio = TRUE;
    }

    if(bCambio) {
        printf("Personaje en (%d, %d)\n", personajeX, personajeY);
        gtk_widget_queue_draw(GTK_WIDGET(draw));
    }

    return bCambio;
}

/*Lógica de la simulación*/

void iniciarSimulacion(){
    int i;
    while(1){
        if(cola.primero == NULL){
            printf("Cola vacía\n");
            break;
        }

        PROCESO *proceso = desencolar();
        if(proceso != NULL){
            proceso->estado = ESTADO_EJECUTANDO;
            for(i = 0; i < 15; i++){
                proceso->tiempoRestante--;
                if(proceso->tiempoRestante == 0){
                    proceso->estado = ESTADO_TERMINADO;
                    printf("Proceso %d terminado\n", proceso->id);
                    free(proceso);
                    break;
                }
                sleep(1);
            }
            if(proceso->estado != ESTADO_TERMINADO){
                encolar(proceso);
            }
        }

        printf("\nCola de procesos:\n");
        PROCESO *p = obtenerPrimeroEnCola();
        while(p != NULL){
            printf("Proceso %d con dirección %p\n", p->id, p);
            p = p->siguiente;
        }
    }
}

/*Lógica de la cola*/

void encolar(PROCESO *nuevo) {
    if(nuevo == NULL) return;
    
    nuevo->siguiente = NULL;
    if(cola.primero == NULL && cola.ultimo == NULL){ //Es el primero en insertarse
        cola.primero = nuevo;
        cola.ultimo = nuevo;
    } 
    else{
        cola.ultimo->siguiente = nuevo;
        cola.ultimo = nuevo;
    }
}

PROCESO *desencolar() {
    if(cola.primero == NULL){
        return NULL;
    }
    PROCESO *desencolado = cola.primero;
    cola.primero = desencolado->siguiente;
    desencolado->siguiente = NULL; // Importante: desvinculamos el proceso de la cola
    if(cola.primero == NULL){ //Si el nodo que desencolaremos era el ultimo en la cola, actualizamos el ultimo
        cola.ultimo = NULL;
    }
    return desencolado;
}

PROCESO *obtenerPrimeroEnCola(){
    return cola.primero;
}

/*Lógica de los procesos*/

int generarTiempoRestante(){
    int escalador = rand() % 5; //Escalador de 0 a 4 para multiplicar el tiempo restante
    return 5 + (escalador * MULTIPLO);
}

void crearProceso(PROCESO *proceso, int id, int tiempoRestante, int estado, int x, int y){
    if(proceso == NULL) return;
    
    proceso->id = id;
    proceso->tiempoRestante = tiempoRestante;
    proceso->estado = estado;
    proceso->x = x;
    proceso->y = y;
    proceso->siguiente = NULL;
}

int obtenerTiempoRestante(PROCESO *proceso){
    return proceso->tiempoRestante;
}

int obtenerEstado(PROCESO *proceso){
    return proceso->estado;
}

void dibujarProcesos(cairo_t *cr)
{
    g_mutex_lock(&mutexCola);
    
    // Limpiar cualquier trayectoria anterior
    cairo_new_path(cr);
    
    PROCESO *p = obtenerPrimeroEnCola();
    int contador = 0;
    int radio = 20;  // Radio más pequeño
    int espaciado = 60;  // Espaciado reducido
    int inicioX = 50;
    int inicioY = 50;  // Centrado verticalmente
    cairo_text_extents_t extents;  // Declarar extents al inicio de la función
    
    while(p != NULL && contador < NUM_PROCESOS) {
        int x = inicioX + (contador * espaciado);
        int y = inicioY;
        
        // Color del círculo según el estado
        switch(p->estado) {
            case ESTADO_LISTO:
                cairo_set_source_rgb(cr, 0.2, 0.8, 0.2); // Verde
                break;
            case ESTADO_EJECUTANDO:
                cairo_set_source_rgb(cr, 0.8, 0.8, 0.2); // Amarillo
                break;
            case ESTADO_BLOQUEADO:
                cairo_set_source_rgb(cr, 0.8, 0.2, 0.2); // Rojo
                break;
            case ESTADO_TERMINADO:
                cairo_set_source_rgb(cr, 0.5, 0.5, 0.5); // Gris
                break;
            default:
                cairo_set_source_rgb(cr, 0.7, 0.7, 0.7); // Gris claro
                break;
        }
        
        // Dibujar el círculo
        cairo_arc(cr, x, y, radio, 0, 2 * M_PI);
        cairo_fill_preserve(cr);
        
        // Borde negro
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_set_line_width(cr, 2);
        cairo_stroke(cr);
        cairo_new_path(cr);
        
        // Si es el primer proceso (próximo a ejecutarse), dibujar una flecha
        if(contador == 0) {
            // Flecha apuntando hacia abajo
            cairo_set_source_rgb(cr, 1, 0, 0); // Rojo
            cairo_set_line_width(cr, 3);
            cairo_move_to(cr, x, y + radio + 20);
            cairo_line_to(cr, x, y + radio + 35);
            cairo_stroke(cr);
            cairo_new_path(cr);
            
            // Punta de la flecha
            cairo_move_to(cr, x - 5, y + radio + 30);
            cairo_line_to(cr, x, y + radio + 35);
            cairo_line_to(cr, x + 5, y + radio + 30);
            cairo_stroke(cr);
            cairo_new_path(cr);
            
            // Texto "NEXT"
            cairo_set_source_rgb(cr, 1, 0, 0);
            cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
            cairo_set_font_size(cr, 10);
            cairo_text_extents(cr, "NEXT", &extents);
            cairo_move_to(cr, x - extents.width/2, y + radio + 50);
            cairo_show_text(cr, "NEXT");
            cairo_new_path(cr);
        }
        
        // Texto del ID del proceso
        char texto[50];
        snprintf(texto, sizeof(texto), "P%d", p->id);
        
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size(cr, 12);
        
        cairo_text_extents(cr, texto, &extents);
        cairo_move_to(cr, x - extents.width/2, y + extents.height/2);
        cairo_show_text(cr, texto);
        cairo_new_path(cr);
        
        // Texto del tiempo restante
        snprintf(texto, sizeof(texto), "%d", p->tiempoRestante);
        cairo_set_font_size(cr, 10);
        cairo_text_extents(cr, texto, &extents);
        cairo_move_to(cr, x - extents.width/2, y + radio + 15);
        cairo_show_text(cr, texto);
        cairo_new_path(cr);
        
        p = p->siguiente;
        contador++;
    }
    
    // Dibujar el proceso en ejecución si existe
    if(idProcesoEnEjecucion >= 0) {
        int radio = 18;  // Más pequeño que antes
        
        // Color según si está bloqueado o no
        if(procesoBloqueado) {
            cairo_set_source_rgb(cr, 0.6, 0.6, 0.6); // Gris para bloqueado
        } else {
            cairo_set_source_rgb(cr, 1.0, 0.6, 0.0); // Naranja para ejecutando
        }
        
        // Dibujar el círculo
        cairo_arc(cr, posXEjecucion, posYEjecucion, radio, 0, 2 * M_PI);
        cairo_fill_preserve(cr);
        
        // Borde negro más grueso
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_set_line_width(cr, 3);
        cairo_stroke(cr);
        cairo_new_path(cr);
        
        // Texto según el estado
        if(procesoBloqueado) {
            cairo_set_source_rgb(cr, 0.4, 0.4, 0.4);
            cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
            cairo_set_font_size(cr, 10);
            cairo_text_extents(cr, "BLOQUEADO", &extents);
            cairo_move_to(cr, posXEjecucion - extents.width/2, posYEjecucion - radio - 10);
            cairo_show_text(cr, "BLOQUEADO");
            cairo_new_path(cr);
        } else {
            cairo_set_source_rgb(cr, 1, 0, 0);
            cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
            cairo_set_font_size(cr, 10);
            cairo_text_extents(cr, "EJECUTANDO", &extents);
            cairo_move_to(cr, posXEjecucion - extents.width/2, posYEjecucion - radio - 10);
            cairo_show_text(cr, "EJECUTANDO");
            cairo_new_path(cr);
        }
        
        // Texto del ID del proceso
        char texto[50];
        snprintf(texto, sizeof(texto), "P%d", idProcesoEnEjecucion);
        
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size(cr, 14);
        
        cairo_text_extents(cr, texto, &extents);
        cairo_move_to(cr, posXEjecucion - extents.width/2, posYEjecucion + extents.height/2);
        cairo_show_text(cr, texto);
        cairo_new_path(cr);
        
        // Texto del tiempo restante
        snprintf(texto, sizeof(texto), "%d", tiempoProcesoEnEjecucion);
        cairo_set_font_size(cr, 12);
        cairo_text_extents(cr, texto, &extents);
        cairo_move_to(cr, posXEjecucion - extents.width/2, posYEjecucion + radio + 15);
        cairo_show_text(cr, texto);
        cairo_new_path(cr);
    }
    
    // Dibujar sección de procesos bloqueados (diseño agradable con tonos grises)
    if(procesoBloqueado && idProcesoEnEjecucion >= 0) {
        // Fondo de la sección bloqueados
        cairo_set_source_rgb(cr, 0.95, 0.95, 0.95); // Gris muy claro
        cairo_rectangle(cr, 50, 500, 600, 100);
        cairo_fill_preserve(cr);
        
        // Borde de la sección
        cairo_set_source_rgb(cr, 0.7, 0.7, 0.7);
        cairo_set_line_width(cr, 2);
        cairo_stroke(cr);
        cairo_new_path(cr);
        
        // Título de la sección
        cairo_set_source_rgb(cr, 0.3, 0.3, 0.3);
        cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size(cr, 16);
        cairo_text_extents(cr, "PROCESO BLOQUEADO", &extents);
        cairo_move_to(cr, 350 - extents.width/2, 520);
        cairo_show_text(cr, "PROCESO BLOQUEADO");
        cairo_new_path(cr);
        
        // Información del proceso bloqueado
        char texto[100];
        snprintf(texto, sizeof(texto), "Proceso P%d - Tiempo restante: %d - Posición: (%d, %d)", 
                idProcesoEnEjecucion, tiempoProcesoEnEjecucion, posXEjecucion, posYEjecucion);
        
        cairo_set_source_rgb(cr, 0.5, 0.5, 0.5);
        cairo_set_font_size(cr, 12);
        cairo_text_extents(cr, texto, &extents);
        cairo_move_to(cr, 350 - extents.width/2, 540);
        cairo_show_text(cr, texto);
        cairo_new_path(cr);
        
        // Mensaje informativo
        cairo_set_source_rgb(cr, 0.6, 0.6, 0.6);
        cairo_set_font_size(cr, 10);
        cairo_text_extents(cr, "El proceso continuará ejecutándose hasta completar su tiempo", &extents);
        cairo_move_to(cr, 350 - extents.width/2, 560);
        cairo_show_text(cr, "El proceso continuará ejecutándose hasta completar su tiempo");
        cairo_new_path(cr);
        
        cairo_text_extents(cr, "Ningún otro proceso podrá ejecutarse hasta que termine", &extents);
        cairo_move_to(cr, 350 - extents.width/2, 575);
        cairo_show_text(cr, "Ningún otro proceso podrá ejecutarse hasta que termine");
        cairo_new_path(cr);
    }
    
    // Dibujar el personaje controlable (cuadrado morado)
    cairo_set_source_rgb(cr, 0.5, 0.0, 0.8);  // Color morado
    cairo_rectangle(cr, personajeX - personajeTamano/2, personajeY - personajeTamano/2, 
                   personajeTamano, personajeTamano);
    cairo_fill_preserve(cr);
    
    // Borde negro
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, 2);
    cairo_stroke(cr);
    cairo_new_path(cr);
    
    g_mutex_unlock(&mutexCola);
}

// Función para detectar colisión entre el personaje y el proceso en ejecución
gboolean detectarColision(int personajeX, int personajeY, int personajeTamano, 
                         int procesoX, int procesoY, int procesoRadio) {
    int distanciaX = abs(personajeX - procesoX);
    int distanciaY = abs(personajeY - procesoY);
    
    // Distancia mínima para que no haya colisión
    int minDistanciaX = personajeTamano/2 + procesoRadio;
    int minDistanciaY = personajeTamano/2 + procesoRadio;
    
    return (distanciaX < minDistanciaX && distanciaY < minDistanciaY);
}