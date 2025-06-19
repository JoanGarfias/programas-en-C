/**
 * Compilar: gcc -o SimProc SimProc.c -Wall `pkg-config --cflags --libs gtk+-3.0` -lm -lpthread -export-dynamic
 * */
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

GtkWidget *window;
GtkWidget *draw;
GtkWidget *btnEjecutar;
GtkWidget *btnSalir;

#define NUM_PROCESSES 8
#define EXECUTION_QUANTUM 15
#define USER_SIZE 20
#define PROCESS_SIZE 20
#define MOVE_STEP 10

// Constantes para las secciones de la pantalla
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define QUEUE_Y 80
#define EXECUTION_Y 240
#define BLOCKED_Y 400
#define PROCESS_SPACING 80

#define EXECUTION_TIME 5

typedef struct {
    int id;
    int remaining_time;
    int is_running;
    int is_blocked;
    int x, y;           // Posición del proceso
    pthread_mutex_t mutex;
} Process;

typedef struct {
    int x, y;           // Posición del usuario
} User;

Process processes[NUM_PROCESSES];
User user = {100, 100};  // Posición inicial del usuario
sem_t execution_semaphore;
pthread_mutex_t process_mutex;
int current_process = -1;
int queue_position = 0;  // Posición actual en la cola

int ready_queue[NUM_PROCESSES];
int ready_front = 0, ready_rear = 0, ready_count = 0;

int blocked_queue[NUM_PROCESSES];
int blocked_front = 0, blocked_rear = 0, blocked_count = 0;

void initialize_processes() {
    srand(time(NULL));
    for (int i = 0; i < NUM_PROCESSES; i++) {
        processes[i].id = i;
        processes[i].remaining_time = (rand() % 5 + 2) * 15; // 30, 45, 60, 75, 90
        processes[i].is_running = FALSE;
        processes[i].is_blocked = FALSE;
        // Posicionar en la cola inicialmente, centrado horizontalmente
        processes[i].x = (WINDOW_WIDTH - (NUM_PROCESSES * PROCESS_SPACING)) / 2 + (i * PROCESS_SPACING);
        processes[i].y = QUEUE_Y;
        pthread_mutex_init(&processes[i].mutex, NULL);
    }
    sem_init(&execution_semaphore, 0, 1);  // Solo un proceso puede ejecutar a la vez
    pthread_mutex_init(&process_mutex, NULL);
}

void* process_execution(void* arg) {
    int process_id = *(int*)arg;
    free(arg);

    while (1) {
        // Esperar hasta que sea el turno de este proceso
        while (queue_position != process_id) {
            usleep(100000);  // Esperar 100ms antes de verificar de nuevo
        }

        sem_wait(&execution_semaphore);

        pthread_mutex_lock(&process_mutex);
        current_process = process_id;
        processes[process_id].is_running = TRUE;
        // Mover a la sección de ejecución, manteniendo la posición horizontal
        processes[process_id].x = (WINDOW_WIDTH - (NUM_PROCESSES * PROCESS_SPACING)) / 2 + (process_id * PROCESS_SPACING);
        processes[process_id].y = EXECUTION_Y;
        pthread_mutex_unlock(&process_mutex);

        // Ejecutar por 5 segundos
        for (int i = 0; i < EXECUTION_TIME; i++) {
            if (processes[process_id].remaining_time > 0) {
                pthread_mutex_lock(&processes[process_id].mutex);
                processes[process_id].remaining_time--;
                pthread_mutex_unlock(&processes[process_id].mutex);
            }
            sleep(1);
        }

        pthread_mutex_lock(&process_mutex);
        processes[process_id].is_running = FALSE;
        current_process = -1;

        // Verificar si el proceso está bloqueado
        if (processes[process_id].is_blocked) {
            // Si aún tiene tiempo restante, volver a la cola de espera
            if (processes[process_id].remaining_time > 0) {
                processes[process_id].is_blocked = FALSE;
                processes[process_id].y = QUEUE_Y;
                // Avanzar en la cola para permitir que el siguiente proceso entre en ejecución
                queue_position = (queue_position + 1) % NUM_PROCESSES;
            }
            // Si no tiene tiempo restante, el proceso termina
        } else {
            // Si no está bloqueado, volver a la cola
            processes[process_id].y = QUEUE_Y;
            // Avanzar en la cola
            queue_position = (queue_position + 1) % NUM_PROCESSES;
        }

        pthread_mutex_unlock(&process_mutex);
        sem_post(&execution_semaphore);
    }

    return NULL;
}

gboolean refrescar(gpointer data)
{
    gtk_widget_queue_draw(GTK_WIDGET(draw));
    return TRUE;  // Mantener el temporizador activo
}

int main(int argc, char *argv[])
{
    GtkBuilder *builder;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "SimProc.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    draw = GTK_WIDGET(gtk_builder_get_object(builder, "draw"));
    btnEjecutar = GTK_WIDGET(gtk_builder_get_object(builder, "btnEjecutar"));
    btnSalir = GTK_WIDGET(gtk_builder_get_object(builder, "btnSalir"));
    gtk_builder_connect_signals(builder, NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}

void on_window_destroy()
{
	gtk_main_quit();
}

void on_btnSalir_clicked()
{
	on_window_destroy();
}

void on_btnEjecutar_clicked()
{
    gtk_widget_hide(btnEjecutar);

    // Inicializar procesos
    initialize_processes();

    // Crear hilos para cada proceso
    for (int i = 0; i < NUM_PROCESSES; i++) {
        int* process_id = malloc(sizeof(int));
        *process_id = i;
        pthread_t thread;
        pthread_create(&thread, NULL, process_execution, process_id);
        pthread_detach(thread);
    }

    // Iniciar el temporizador de refresco
    g_timeout_add(100, refrescar, NULL);
}

gboolean on_draw_draw(GtkDrawingArea *widget, cairo_t *cr)
{
    // Fondo blanco
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);

    // Dibujar procesos
    for (int i = 0; i < NUM_PROCESSES; i++) {
        // Color de la bolita según su estado
        if (processes[i].is_blocked) {
            cairo_set_source_rgb(cr, 0.5, 0.5, 0.5);  // Gris para procesos bloqueados
        } else if (processes[i].is_running) {
            cairo_set_source_rgb(cr, 1, 0, 0);        // Rojo para proceso en ejecución
        } else {
            cairo_set_source_rgb(cr, 0, 0, 1);        // Azul para procesos en espera
        }

        // Dibujar círculo
        cairo_arc(cr, processes[i].x, processes[i].y, PROCESS_SIZE, 0, 2 * M_PI);
        cairo_fill(cr);

        // Dibujar el tiempo restante
        char time_str[10];
        snprintf(time_str, sizeof(time_str), "%d", processes[i].remaining_time);
        cairo_set_source_rgb(cr, 1, 1, 1);  // Texto en blanco
        cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size(cr, 12);
        cairo_text_extents_t extents;
        cairo_text_extents(cr, time_str, &extents);
        cairo_move_to(cr, processes[i].x - extents.width/2, processes[i].y + extents.height/2);
        cairo_show_text(cr, time_str);
    }

    // Dibujar usuario (cuadrado verde)
    cairo_set_source_rgb(cr, 0, 1, 0);
    cairo_rectangle(cr, user.x, user.y, USER_SIZE, USER_SIZE);
    cairo_fill(cr);

    // Dibujar etiquetas de secciones
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 14);

    // Etiqueta de cola
    cairo_move_to(cr, 10, QUEUE_Y - 10);
    cairo_show_text(cr, "Cola de Espera");

    // Etiqueta de ejecución
    cairo_move_to(cr, 10, EXECUTION_Y - 10);
    cairo_show_text(cr, "Proceso en Ejecución");

    // Etiqueta de bloqueados
    cairo_move_to(cr, 10, BLOCKED_Y - 10);
    cairo_show_text(cr, "Procesos Bloqueados");

    return FALSE;
}

gboolean on_draw_key_press_event(GtkDrawingArea *widget, GdkEventKey *event)
{
    gboolean bCambio = FALSE;
    int new_x = user.x;
    int new_y = user.y;

    switch(event->keyval){
        case GDK_KEY_Left:
            new_x -= MOVE_STEP;
            bCambio = TRUE;
            break;
        case GDK_KEY_Right:
            new_x += MOVE_STEP;
            bCambio = TRUE;
            break;
        case GDK_KEY_Up:
            new_y -= MOVE_STEP;
            bCambio = TRUE;
            break;
        case GDK_KEY_Down:
            new_y += MOVE_STEP;
            bCambio = TRUE;
            break;
    }

    // Verificar límites de la ventana
    if (new_x >= 0 && new_x <= WINDOW_WIDTH - USER_SIZE &&
        new_y >= 0 && new_y <= WINDOW_HEIGHT - USER_SIZE) {

        // Verificar colisiones con procesos en ejecución
        for (int i = 0; i < NUM_PROCESSES; i++) {
            if (processes[i].is_running && !processes[i].is_blocked) {
                if (abs(new_x - processes[i].x) < (USER_SIZE + PROCESS_SIZE) &&
                    abs(new_y - processes[i].y) < (USER_SIZE + PROCESS_SIZE)) {
                    // Colisión detectada
                    processes[i].is_blocked = TRUE;
                    // Mover el proceso a la sección de bloqueados
                    processes[i].y = BLOCKED_Y;
                    processes[i].x = (WINDOW_WIDTH - (NUM_PROCESSES * PROCESS_SPACING)) / 2 + (i * PROCESS_SPACING);
                    // No avanzamos en la cola, el proceso seguirá consumiendo tiempo
                }
            }
        }

        user.x = new_x;
        user.y = new_y;
    }

    return bCambio;
}


void actualizar_posiciones_cola() {
    int base_x = (WINDOW_WIDTH - (ready_count * PROCESS_SPACING)) / 2;
    for (int i = 0; i < ready_count; i++) {
        int pid = ready_queue[(ready_front + i) % NUM_PROCESSES];
        processes[pid].x = base_x + i * PROCESS_SPACING;
        processes[pid].y = QUEUE_Y;
    }
}

// Función para verificar si hay algún proceso bloqueado
gboolean hay_proceso_bloqueado() {
    for (int i = 0; i < NUM_PROCESSES; i++) {
        if (processes[i].is_blocked) {
            return TRUE;
        }
    }
    return FALSE;
}

void enqueue_ready(int pid) {
    ready_queue[ready_rear] = pid;
    ready_rear = (ready_rear + 1) % NUM_PROCESSES;
    ready_count++;
    actualizar_posiciones_cola();
}

int dequeue_ready() {
    if (ready_count == 0) return -1;
    int pid = ready_queue[ready_front];
    ready_front = (ready_front + 1) % NUM_PROCESSES;
    ready_count--;
    actualizar_posiciones_cola();
    return pid;
}

void enqueue_blocked(int pid) {
    blocked_queue[blocked_rear] = pid;
    blocked_rear = (blocked_rear + 1) % NUM_PROCESSES;
    blocked_count++;
}

int dequeue_blocked() {
    if (blocked_count == 0) return -1;
    int pid = blocked_queue[blocked_front];
    blocked_front = (blocked_front + 1) % NUM_PROCESSES;
    blocked_count--;
    return pid;
}
