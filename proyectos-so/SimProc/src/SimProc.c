/**
 * Simulador de Procesos Round Robin con Interacción de Usuario
 * Compilar: gcc -o build/SimProc src/SimProc.c -Wall `pkg-config --cflags --libs gtk+-3.0 gstreamer-1.0` -lm -lpthread -export-dynamic
 */

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <gst/gst.h>

// Constantes
#define ESTADO_LISTO 1
#define ESTADO_EJECUTANDO 2
#define ESTADO_BLOQUEADO 3
#define ESTADO_TERMINADO 4
#define ESTADO_SUSPENDIDO 5

#define MULTIPLO 15
#define NUM_PROCESOS 8

// Estructuras
typedef struct proc {
    int id;
    int tiempoRestante;
    int estado;
    int x;
    int y;
    int tiempoSuspension;
    int quantumRestante;
    struct proc *siguiente;
} PROCESO;

typedef struct colaproc {
    PROCESO *primero;
    PROCESO *ultimo;
} COLA;

// Variables globales
pthread_t hiloSimulacion;
gboolean simulacionActiva = FALSE;
GMutex mutexCola;

// Proceso en ejecución
int idProcesoEnEjecucion = -1;
int tiempoProcesoEnEjecucion = 0;
int posXEjecucion = 300;
int posYEjecucion = 200;
gboolean procesoBloqueado = FALSE;
PROCESO *procesoEnEjecucion = NULL;

// Personaje controlable
int personajeX = 400;
int personajeY = 300;
int personajeTamano = 20;

// Efectos de sonido
GstElement *pipelineEjecucion = NULL;
GstElement *pipelineBloqueo = NULL;
GstElement *pipelineTerminado = NULL;
gboolean sonidosHabilitados = TRUE;

// Interfaz gráfica
GtkWidget *window;
GtkWidget *draw;
GtkWidget *btnEjecutar;
GtkWidget *btnSalir;

// Colas de procesos
COLA colaListos;
COLA colaSuspendidos;

// Control de tiempo
int cuantoActual = 0;

// Estadísticas
int procesosTerminados = 0;
gboolean victoriaSonando = FALSE;

// Prototipos de funciones
void on_window_destroy();
void on_btnSalir_clicked();
gboolean refrescar(gpointer);
void on_btnEjecutar_clicked();
gboolean on_draw_draw(GtkDrawingArea *, cairo_t *);
gboolean on_draw_key_press_event(GtkDrawingArea *, GdkEventKey *);
void dibujarProcesos(cairo_t *);

// Funciones de cola
void encolarListos(PROCESO *);
PROCESO *desencolarListos();
PROCESO *obtenerPrimeroEnColaListos();
void encolarSuspendidos(PROCESO *);
PROCESO *desencolarSuspendidos();
PROCESO *obtenerPrimeroEnColaSuspendidos();

// Funciones de procesos
void crearProceso(PROCESO *, int, int, int, int, int);
int generarTiempoRestante();
gboolean detectarColision(int, int, int, int, int, int);

// Funciones de simulación
void *funcionSimulacion(void *arg);
gboolean reactivarBotonEjecutar(gpointer data);

// Funciones de sonido
void reproducirSonido(const char* archivo, GstElement **pipeline);
void reproducirSonidoEjecucion();
void reproducirSonidoBloqueado();
void reproducirSonidoTerminado();

// Función principal
int main(int argc, char *argv[]) {
    srand(time(NULL));
    GtkBuilder *builder;

    gtk_init(&argc, &argv);
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

// Funciones de interfaz
void on_window_destroy() {
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
}

void on_btnSalir_clicked() {
    on_window_destroy();
}

gboolean refrescar(gpointer data) {
    gtk_widget_queue_draw(GTK_WIDGET(draw));
    return TRUE;
}

void on_btnEjecutar_clicked() {
    gtk_widget_hide(btnEjecutar);
    
    if(simulacionActiva) {
        simulacionActiva = FALSE;
        if(pthread_join(hiloSimulacion, NULL) != 0) {
            fprintf(stderr, "Error al esperar el hilo de simulación anterior\n");
        }
    }
    
    // Limpiar colas existentes
    g_mutex_lock(&mutexCola);
    while(colaListos.primero != NULL) {
        PROCESO *p = desencolarListos();
        if(p != NULL) free(p);
    }
    while(colaSuspendidos.primero != NULL) {
        PROCESO *p = desencolarSuspendidos();
        if(p != NULL) free(p);
    }
    g_mutex_unlock(&mutexCola);
    
    g_mutex_clear(&mutexCola);
    g_mutex_init(&mutexCola);
    
    simulacionActiva = TRUE;
    procesosTerminados = 0;
    victoriaSonando = FALSE;
    
    // Crear procesos iniciales
    for(int i = 0; i < NUM_PROCESOS; i++) {
        PROCESO *proceso = (PROCESO *)malloc(sizeof(PROCESO));
        crearProceso(proceso, i, generarTiempoRestante(), ESTADO_LISTO, 10, 10);
        proceso->tiempoSuspension = 0;
        encolarListos(proceso);
    }

    if(pthread_create(&hiloSimulacion, NULL, funcionSimulacion, NULL) != 0) {
        fprintf(stderr, "Error al crear el hilo de simulación\n");
        return;
    }
    
    g_timeout_add(1000, refrescar, NULL);
    printf("Nueva simulación iniciada con %d procesos\n", NUM_PROCESOS);
}

gboolean on_draw_draw(GtkDrawingArea *widget, cairo_t *cr) {
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);
    dibujarProcesos(cr);
    return FALSE;
}

gboolean on_draw_key_press_event(GtkDrawingArea *widget, GdkEventKey *event) {
    gboolean bCambio = FALSE;
    int velocidad = 10;
    int nuevaX = personajeX;
    int nuevaY = personajeY;
    int anchoPantalla = 640;
    int altoPantalla = 480;
    
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
    
    // Wrap-around
    if(nuevaX < 0) nuevaX = anchoPantalla - personajeTamano/2;
    if(nuevaX > anchoPantalla - personajeTamano/2) nuevaX = 0;
    if(nuevaY < 0) nuevaY = altoPantalla - personajeTamano/2;
    if(nuevaY > altoPantalla - personajeTamano/2) nuevaY = 0;
    
    g_mutex_lock(&mutexCola);
    if(idProcesoEnEjecucion >= 0) {
        if(!procesoBloqueado && detectarColision(nuevaX, nuevaY, personajeTamano, posXEjecucion, posYEjecucion, 18)) {
            printf("¡COLISIÓN! Proceso %d suspendido\n", idProcesoEnEjecucion);
            procesoBloqueado = TRUE;
            if(procesoEnEjecucion != NULL) {
                procesoEnEjecucion->estado = ESTADO_SUSPENDIDO;
            }
            reproducirSonidoBloqueado();
            bCambio = TRUE;
        } else {
            personajeX = nuevaX;
            personajeY = nuevaY;
            bCambio = TRUE;
        }
    } else {
        personajeX = nuevaX;
        personajeY = nuevaY;
        bCambio = TRUE;
    }
    g_mutex_unlock(&mutexCola);
    
    if(bCambio) {
        printf("Personaje en (%d, %d)\n", personajeX, personajeY);
        gtk_widget_queue_draw(GTK_WIDGET(draw));
    }
    return bCambio;
}

// Funciones de cola
void encolarListos(PROCESO *nuevo) {
    if(nuevo == NULL) return;
    nuevo->siguiente = NULL;
    if(colaListos.primero == NULL && colaListos.ultimo == NULL) {
        colaListos.primero = nuevo;
        colaListos.ultimo = nuevo;
    } else {
        colaListos.ultimo->siguiente = nuevo;
        colaListos.ultimo = nuevo;
    }
}

PROCESO *desencolarListos() {
    if(colaListos.primero == NULL) return NULL;
    PROCESO *desencolado = colaListos.primero;
    colaListos.primero = desencolado->siguiente;
    desencolado->siguiente = NULL;
    if(colaListos.primero == NULL) colaListos.ultimo = NULL;
    return desencolado;
}

void encolarSuspendidos(PROCESO *nuevo) {
    if(nuevo == NULL) return;
    nuevo->siguiente = NULL;
    if(colaSuspendidos.primero == NULL && colaSuspendidos.ultimo == NULL) {
        colaSuspendidos.primero = nuevo;
        colaSuspendidos.ultimo = nuevo;
    } else {
        colaSuspendidos.ultimo->siguiente = nuevo;
        colaSuspendidos.ultimo = nuevo;
    }
}

PROCESO *desencolarSuspendidos() {
    if(colaSuspendidos.primero == NULL) return NULL;
    PROCESO *desencolado = colaSuspendidos.primero;
    colaSuspendidos.primero = desencolado->siguiente;
    desencolado->siguiente = NULL;
    if(colaSuspendidos.primero == NULL) colaSuspendidos.ultimo = NULL;
    return desencolado;
}

PROCESO *obtenerPrimeroEnColaListos() {
    return colaListos.primero;
}

PROCESO *obtenerPrimeroEnColaSuspendidos() {
    return colaSuspendidos.primero;
}

// Funciones de procesos
int generarTiempoRestante() {
    int escalador = rand() % 5;
    return 30 + (escalador * MULTIPLO);
}

void crearProceso(PROCESO *proceso, int id, int tiempoRestante, int estado, int x, int y) {
    if(proceso == NULL) return;
    proceso->id = id;
    proceso->tiempoRestante = tiempoRestante;
    proceso->estado = estado;
    proceso->x = x;
    proceso->y = y;
    proceso->tiempoSuspension = 0;
    proceso->quantumRestante = MULTIPLO;
    proceso->siguiente = NULL;
}

gboolean detectarColision(int personajeX, int personajeY, int personajeTamano, 
                         int procesoX, int procesoY, int procesoRadio) {
    int distanciaX = abs(personajeX - procesoX);
    int distanciaY = abs(personajeY - procesoY);
    int minDistanciaX = personajeTamano/2 + procesoRadio;
    int minDistanciaY = personajeTamano/2 + procesoRadio;
    return (distanciaX < minDistanciaX && distanciaY < minDistanciaY);
}

// Funciones de simulación
gboolean reactivarBotonEjecutar(gpointer data) {
    gtk_widget_show(btnEjecutar);
    simulacionActiva = FALSE;
    
    idProcesoEnEjecucion = -1;
    procesoBloqueado = FALSE;
    posXEjecucion = 300;
    posYEjecucion = 200;
    
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
    return FALSE;
}

void *funcionSimulacion(void *arg) {
    while(simulacionActiva) {
        g_mutex_lock(&mutexCola);
        
        if(idProcesoEnEjecucion >= 0) {
            g_mutex_unlock(&mutexCola);
            g_usleep(1000000);
            continue;
        }
        
        if(colaListos.primero == NULL && colaSuspendidos.primero == NULL) {
            printf("Colas vacías - Simulación terminada\n");
            g_mutex_unlock(&mutexCola);
            g_idle_add((GSourceFunc)reactivarBotonEjecutar, NULL);
            break;
        }
        
        if(colaListos.primero == NULL && colaSuspendidos.primero != NULL) {
            PROCESO *prev = NULL;
            PROCESO *curr = colaSuspendidos.primero;
            while(curr != NULL) {
                curr->tiempoSuspension--;
                curr->tiempoRestante--;
                if(curr->tiempoRestante <= 0) {
                    PROCESO *aEliminar = curr;
                    if(prev == NULL) {
                        colaSuspendidos.primero = curr->siguiente;
                    } else {
                        prev->siguiente = curr->siguiente;
                    }
                    if(curr == colaSuspendidos.ultimo) {
                        colaSuspendidos.ultimo = prev;
                    }
                    curr = curr->siguiente;
                    aEliminar->estado = ESTADO_TERMINADO;
                    printf("Proceso %d terminado (desde suspendidos)\n", aEliminar->id);
                    reproducirSonidoTerminado();
                    procesosTerminados++;
                    free(aEliminar);
                    continue;
                }
                if(curr->tiempoSuspension <= 0) {
                    // Volver a listos con quantum completo
                    PROCESO *aMover = curr;
                    if(prev == NULL) {
                        colaSuspendidos.primero = curr->siguiente;
                    } else {
                        prev->siguiente = curr->siguiente;
                    }
                    if(curr == colaSuspendidos.ultimo) {
                        colaSuspendidos.ultimo = prev;
                    }
                    curr = curr->siguiente;
                    aMover->estado = ESTADO_LISTO;
                    aMover->tiempoSuspension = 0;
                    aMover->quantumRestante = 15; // Quantum completo
                    encolarListos(aMover);
                    continue;
                }
                prev = curr;
                curr = curr->siguiente;
            }
            g_mutex_unlock(&mutexCola);
            g_usleep(1000000);
            continue;
        }
        
        PROCESO *proceso = desencolarListos();
        if(proceso == NULL) {
            g_mutex_unlock(&mutexCola);
            continue;
        }
        
        proceso->estado = ESTADO_EJECUTANDO;
        idProcesoEnEjecucion = proceso->id;
        procesoEnEjecucion = proceso;
        tiempoProcesoEnEjecucion = proceso->tiempoRestante;
        posXEjecucion = 50 + (rand() % 600);
        posYEjecucion = 200;
        cuantoActual = 0;
        reproducirSonidoEjecucion();
        g_mutex_unlock(&mutexCola);
        
        gboolean procesoTerminado = FALSE;
        int cuanto = proceso->quantumRestante;
        
        for(int i = 0; i < cuanto && simulacionActiva && !procesoTerminado; i++) {
            g_mutex_lock(&mutexCola);
            
            proceso->tiempoRestante--;
            tiempoProcesoEnEjecucion = proceso->tiempoRestante;
            cuantoActual = i+1;
            proceso->quantumRestante = cuanto - (i+1); // Actualizar quantum restante
            
            if(proceso->tiempoRestante <= 0) {
                proceso->estado = ESTADO_TERMINADO;
                printf("Proceso %d terminado\n", proceso->id);
                reproducirSonidoTerminado();
                procesoTerminado = TRUE;
                procesosTerminados++;
            }
            
            PROCESO *prev = NULL;
            PROCESO *curr = colaSuspendidos.primero;
            while(curr != NULL) {
                curr->tiempoSuspension--;
                curr->tiempoRestante--;
                if(curr->tiempoRestante <= 0) {
                    PROCESO *aEliminar = curr;
                    if(prev == NULL) {
                        colaSuspendidos.primero = curr->siguiente;
                    } else {
                        prev->siguiente = curr->siguiente;
                    }
                    if(curr == colaSuspendidos.ultimo) {
                        colaSuspendidos.ultimo = prev;
                    }
                    curr = curr->siguiente;
                    aEliminar->estado = ESTADO_TERMINADO;
                    printf("Proceso %d terminado (desde suspendidos)\n", aEliminar->id);
                    reproducirSonidoTerminado();
                    procesosTerminados++;
                    free(aEliminar);
                    continue;
                }
                if(curr->tiempoSuspension <= 0) {
                    // Volver a listos con quantum completo
                    PROCESO *aMover = curr;
                    if(prev == NULL) {
                        colaSuspendidos.primero = curr->siguiente;
                    } else {
                        prev->siguiente = curr->siguiente;
                    }
                    if(curr == colaSuspendidos.ultimo) {
                        colaSuspendidos.ultimo = prev;
                    }
                    curr = curr->siguiente;
                    aMover->estado = ESTADO_LISTO;
                    aMover->tiempoSuspension = 0;
                    aMover->quantumRestante = 15; // Quantum completo
                    encolarListos(aMover);
                    continue;
                }
                prev = curr;
                curr = curr->siguiente;
            }
            
            if(proceso->estado == ESTADO_SUSPENDIDO) {
                // Guardar el quantum restante cuando se suspende
                proceso->tiempoSuspension = proceso->quantumRestante;
                int posSusp = 0;
                PROCESO *tmp = colaSuspendidos.primero;
                while(tmp != NULL) {
                    posSusp++;
                    tmp = tmp->siguiente;
                }
                proceso->x = 50 + (posSusp * 60);
                proceso->y = 350;
                encolarSuspendidos(proceso);
                idProcesoEnEjecucion = -1;
                procesoEnEjecucion = NULL;
                procesoBloqueado = FALSE;
                g_mutex_unlock(&mutexCola);
                break;
            }
            
            g_mutex_unlock(&mutexCola);
            g_usleep(1000000);
        }
        
        g_mutex_lock(&mutexCola);
        if(procesoTerminado) {
            free(proceso);
            idProcesoEnEjecucion = -1;
            procesoEnEjecucion = NULL;
            procesoBloqueado = FALSE;
        } else if(proceso->estado != ESTADO_SUSPENDIDO && simulacionActiva) {
            proceso->estado = ESTADO_LISTO;
            proceso->quantumRestante = 15; // Quantum completo
            encolarListos(proceso);
            idProcesoEnEjecucion = -1;
            procesoEnEjecucion = NULL;
            procesoBloqueado = FALSE;
        }
        g_mutex_unlock(&mutexCola);
    }
    
    g_mutex_lock(&mutexCola);
    while(colaListos.primero != NULL) {
        PROCESO *p = desencolarListos();
        if(p != NULL) free(p);
    }
    while(colaSuspendidos.primero != NULL) {
        PROCESO *p = desencolarSuspendidos();
        if(p != NULL) free(p);
    }
    g_mutex_unlock(&mutexCola);
    
    return NULL;
}

// Funciones de sonido
void reproducirSonido(const char* archivo, GstElement **pipeline) {
    if(!sonidosHabilitados) return;
    
    if(*pipeline != NULL) {
        gst_element_set_state(*pipeline, GST_STATE_NULL);
        gst_object_unref(*pipeline);
    }
    
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        char uri[2048];
        if (strstr(cwd, "/build") != NULL) {
            char *build_pos = strstr(cwd, "/build");
            if (build_pos != NULL) {
                *build_pos = '\0';
            }
        }
        snprintf(uri, sizeof(uri), "playbin uri=file://%s/src/%s", cwd, archivo);
        
        *pipeline = gst_parse_launch(uri, NULL);
        if(*pipeline != NULL) {
            gst_element_set_state(*pipeline, GST_STATE_PLAYING);
            g_usleep(100000);
        }
    }
}

void reproducirSonidoEjecucion() {
    reproducirSonido("ejecucion.wav", &pipelineEjecucion);
}

void reproducirSonidoBloqueado() {
    reproducirSonido("bloqueado.wav", &pipelineBloqueo);
}

void reproducirSonidoTerminado() {
    reproducirSonido("terminado.wav", &pipelineTerminado);
}

// Función de dibujo
void dibujarProcesos(cairo_t *cr) {
    g_mutex_lock(&mutexCola);
    
    if (procesosTerminados == NUM_PROCESOS) {
        if (!victoriaSonando) {
            reproducirSonidoTerminado();
            victoriaSonando = TRUE;
        }
        
        cairo_set_source_rgb(cr, 0.1, 0.6, 0.1);
        cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size(cr, 48);
        cairo_text_extents_t ext;
        const char *msg = "¡VICTORIA!";
        cairo_text_extents(cr, msg, &ext);
        int cx = 320 - ext.width/2;
        int cy = 240 + ext.height/2;
        cairo_move_to(cr, cx, cy);
        cairo_show_text(cr, msg);
        cairo_new_path(cr);
        
        g_mutex_unlock(&mutexCola);
        return;
    }
    
    cairo_new_path(cr);
    
    // Dibujar cola de listos
    PROCESO *p = obtenerPrimeroEnColaListos();
    int contador = 0;
    int radio = 20;
    int espaciado = 60;
    int inicioX = 50;
    int inicioY = 50;
    cairo_text_extents_t extents;
    
    cairo_set_source_rgb(cr, 0.1, 0.5, 0.1);
    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 14);
    cairo_text_extents(cr, "COLA DE LISTOS", &extents);
    cairo_move_to(cr, inicioX, inicioY - 20);
    cairo_show_text(cr, "COLA DE LISTOS");
    cairo_new_path(cr);

    while(p != NULL && contador < NUM_PROCESOS) {
        int x = inicioX + (contador * espaciado);
        int y = inicioY + 10;
        
        switch(p->estado) {
            case ESTADO_LISTO:
                cairo_set_source_rgb(cr, 0.2, 0.8, 0.2); break;
            case ESTADO_EJECUTANDO:
                cairo_set_source_rgb(cr, 0.8, 0.8, 0.2); break;
            case ESTADO_BLOQUEADO:
                cairo_set_source_rgb(cr, 0.8, 0.2, 0.2); break;
            case ESTADO_TERMINADO:
                cairo_set_source_rgb(cr, 0.5, 0.5, 0.5); break;
            default:
                cairo_set_source_rgb(cr, 0.7, 0.7, 0.7); break;
        }
        
        cairo_arc(cr, x, y, radio, 0, 2 * M_PI);
        cairo_fill_preserve(cr);
        
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_set_line_width(cr, 2);
        cairo_stroke(cr);
        cairo_new_path(cr);
        
        if(contador == 0) {
            cairo_set_source_rgb(cr, 1, 0, 0);
            cairo_set_line_width(cr, 3);
            cairo_move_to(cr, x, y + radio + 20);
            cairo_line_to(cr, x, y + radio + 35);
            cairo_stroke(cr);
            cairo_new_path(cr);
            
            cairo_move_to(cr, x - 5, y + radio + 30);
            cairo_line_to(cr, x, y + radio + 35);
            cairo_line_to(cr, x + 5, y + radio + 30);
            cairo_stroke(cr);
            cairo_new_path(cr);
            
            cairo_set_source_rgb(cr, 1, 0, 0);
            cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
            cairo_set_font_size(cr, 10);
            cairo_text_extents(cr, "NEXT", &extents);
            cairo_move_to(cr, x - extents.width/2, y + radio + 50);
            cairo_show_text(cr, "NEXT");
            cairo_new_path(cr);
        }
        
        char texto[50];
        snprintf(texto, sizeof(texto), "P%d", p->id);
        
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size(cr, 12);
        
        cairo_text_extents(cr, texto, &extents);
        cairo_move_to(cr, x - extents.width/2, y + extents.height/2);
        cairo_show_text(cr, texto);
        cairo_new_path(cr);
        
        snprintf(texto, sizeof(texto), "%d", p->tiempoRestante);
        cairo_set_font_size(cr, 10);
        cairo_text_extents(cr, texto, &extents);
        cairo_move_to(cr, x - extents.width/2, y + radio + 15);
        cairo_show_text(cr, texto);
        cairo_new_path(cr);
        
        p = p->siguiente;
        contador++;
    }
    
    // Dibujar cola de suspendidos
    p = obtenerPrimeroEnColaSuspendidos();
    contador = 0;
    int inicioYSusp = 350;
    
    cairo_set_source_rgb(cr, 0.5, 0.2, 0.2);
    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 14);
    cairo_text_extents(cr, "COLA DE SUSPENDIDOS", &extents);
    cairo_move_to(cr, inicioX, inicioYSusp - 20);
    cairo_show_text(cr, "COLA DE SUSPENDIDOS");
    cairo_new_path(cr);
    
    while(p != NULL && contador < NUM_PROCESOS) {
        int x = inicioX + (contador * espaciado);
        int y = inicioYSusp + 10;
        
        cairo_set_source_rgb(cr, 0.7, 0.3, 0.3);
        cairo_arc(cr, x, y, radio, 0, 2 * M_PI);
        cairo_fill_preserve(cr);
        
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_set_line_width(cr, 2);
        cairo_stroke(cr);
        cairo_new_path(cr);
        
        char texto[50];
        snprintf(texto, sizeof(texto), "P%d", p->id);
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size(cr, 12);
        cairo_text_extents(cr, texto, &extents);
        cairo_move_to(cr, x - extents.width/2, y + extents.height/2);
        cairo_show_text(cr, texto);
        cairo_new_path(cr);
        
        snprintf(texto, sizeof(texto), "%d", p->tiempoRestante);
        cairo_set_font_size(cr, 10);
        cairo_text_extents(cr, texto, &extents);
        cairo_move_to(cr, x - extents.width/2, y + radio + 15);
        cairo_show_text(cr, texto);
        cairo_new_path(cr);
        
        p->x = x;
        p->y = y;
        p = p->siguiente;
        contador++;
    }
    
    // Dibujar proceso en ejecución
    if(idProcesoEnEjecucion >= 0) {
        gboolean enSuspendidos = FALSE;
        PROCESO *ps = obtenerPrimeroEnColaSuspendidos();
        while(ps != NULL) {
            if(ps->id == idProcesoEnEjecucion) {
                enSuspendidos = TRUE;
                break;
            }
            ps = ps->siguiente;
        }
        
        if(!enSuspendidos) {
            int radio = 18;
            if(procesoBloqueado) {
                cairo_set_source_rgb(cr, 0.6, 0.6, 0.6);
            } else {
                cairo_set_source_rgb(cr, 1.0, 0.6, 0.0);
            }
            
            cairo_arc(cr, posXEjecucion, posYEjecucion, radio, 0, 2 * M_PI);
            cairo_fill_preserve(cr);
            cairo_set_source_rgb(cr, 0, 0, 0);
            cairo_set_line_width(cr, 3);
            cairo_stroke(cr);
            cairo_new_path(cr);
            
            if(procesoBloqueado) {
                cairo_set_source_rgb(cr, 0.4, 0.4, 0.4);
                cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
                cairo_set_font_size(cr, 10);
                cairo_text_extents(cr, "Suspendiendo...", &extents);
                cairo_move_to(cr, posXEjecucion - extents.width/2, posYEjecucion - radio - 10);
                cairo_show_text(cr, "Suspendiendo...");
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
            
            char texto[50];
            snprintf(texto, sizeof(texto), "P%d", idProcesoEnEjecucion);
            cairo_set_source_rgb(cr, 0, 0, 0);
            cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
            cairo_set_font_size(cr, 14);
            cairo_text_extents(cr, texto, &extents);
            cairo_move_to(cr, posXEjecucion - extents.width/2, posYEjecucion + extents.height/2);
            cairo_show_text(cr, texto);
            cairo_new_path(cr);
            
            snprintf(texto, sizeof(texto), "%d", tiempoProcesoEnEjecucion);
            cairo_set_font_size(cr, 12);
            cairo_text_extents(cr, texto, &extents);
            cairo_move_to(cr, posXEjecucion - extents.width/2, posYEjecucion + radio + 15);
            cairo_show_text(cr, texto);
            cairo_new_path(cr);
        }
    }
    
    // Dibujar personaje
    cairo_set_source_rgb(cr, 0.5, 0.0, 0.8);
    cairo_rectangle(cr, personajeX - personajeTamano/2, personajeY - personajeTamano/2, 
                   personajeTamano, personajeTamano);
    cairo_fill_preserve(cr);
    
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, 2);
    cairo_stroke(cr);
    cairo_new_path(cr);
    
    // Estadísticas
    int countListos = 0, countSuspendidos = 0;
    p = obtenerPrimeroEnColaListos();
    while(p != NULL) { countListos++; p = p->siguiente; }
    p = obtenerPrimeroEnColaSuspendidos();
    while(p != NULL) { countSuspendidos++; p = p->siguiente; }
    
    int statsX = 500;
    int statsY = 400;
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 13);
    char stats1[64], stats2[64], stats3[64];
    snprintf(stats1, sizeof(stats1), "Terminados: %d", procesosTerminados);
    snprintf(stats2, sizeof(stats2), "Listos: %d", countListos);
    snprintf(stats3, sizeof(stats3), "Suspendidos: %d", countSuspendidos);
    cairo_move_to(cr, statsX, statsY);
    cairo_show_text(cr, stats1);
    cairo_new_path(cr);
    cairo_move_to(cr, statsX, statsY + 20);
    cairo_show_text(cr, stats2);
    cairo_new_path(cr);
    cairo_move_to(cr, statsX, statsY + 40);
    cairo_show_text(cr, stats3);
    cairo_new_path(cr);
    
    g_mutex_unlock(&mutexCola);
}