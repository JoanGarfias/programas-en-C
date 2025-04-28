/**
 * Compilar: gcc -o filosofos filosofos.c -Wall `pkg-config --cflags --libs gtk+-3.0` -lm -lpthread -export-dynamic
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

struct stfilosofo{
	int num;
	int px, py;
	cairo_surface_t *img;
};
typedef struct stfilosofo STFILOSOFO;

STFILOSOFO filosofos[5];
int bejecutar = FALSE;
pthread_mutex_t tenedor[5];
pthread_t hilof[5];
sem_t semcomedor;
gboolean bsem = FALSE;

GtkWidget *window;
GtkWidget *draw1;
GtkWidget *btnEjecutar;
cairo_surface_t *img1, *img2;

void ini_filosofos(void); /*Estas son void porque debe ser así para el uso de hilos. */
void *ffilosofo(void *);
gboolean refrescar(gpointer); //Esto es parecido a void *, solo que es para compatibilidad

int main(int argc, char *argv[])
{
    GtkBuilder *builder;

    gtk_init(&argc, &argv);

    img1 = cairo_image_surface_create_from_png("dormir.png");
    img2 = cairo_image_surface_create_from_png("comer.png");

    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "Filosofos.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    draw1 = GTK_WIDGET(gtk_builder_get_object(builder, "draw1"));
    btnEjecutar = GTK_WIDGET(gtk_builder_get_object(builder, "btnEjecutar"));
    gtk_builder_connect_signals(builder, NULL);

    gtk_widget_show_all(window);

    gtk_main();

    cairo_surface_destroy(img1);
    cairo_surface_destroy(img2);
    if(bsem){
		sem_destroy(&semcomedor);
	}

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

gboolean refrescar(gpointer data)
{
    gtk_widget_queue_draw(GTK_WIDGET(draw1));
    return FALSE;
}

void on_btnEjecutar_clicked()
{
	int i;
	pthread_attr_t attr;

	ini_filosofos();
	bejecutar = TRUE;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	for(i = 0; i < 5; i++){
		pthread_create(&hilof[i], &attr, ffilosofo, (void *)&filosofos[i]);
		//gtk_widget_queue_draw(draw1);
		g_idle_add(refrescar, NULL); //Esto manda a ejecutar la función refrescar cuando se desocupe.
	}
	gtk_widget_hide(btnEjecutar);
}


gboolean on_draw1_draw(GtkDrawingArea *widget, cairo_t *cr)
{
	int i;

	if(bejecutar){
		for(i = 0; i < 5; i++){
			cairo_set_source_surface(cr, filosofos[i].img,
									 filosofos[i].px, filosofos[i].py);
			cairo_paint(cr);
		}
	}

	return FALSE;
}

void ini_filosofos(void)
{
	int i;

	srand(time(NULL)); //Semilla de aleatoriedad
	if(sem_init(&semcomedor, 0, 4) == 0){ //Creamos un semaforo, inicia en 0 y maximo llega hasta 4
		bsem = TRUE;
	}else{
		perror("Error en la inicialización del semáforo\n");
	}
	for(i = 0; i < 5; i++){
		filosofos[i].num = i;
		filosofos[i].px = 120 + 80 * sin((72*i)/(180/M_PI));
		filosofos[i].py = 110 + 80 * cos((72*i)/(180/M_PI));
		filosofos[i].img = img1;
		pthread_mutex_init(&tenedor[i], NULL); //Mutex para los tenedores
	}
}

void *ffilosofo(void *pf)
{
	STFILOSOFO *f = (STFILOSOFO *)pf;

	while(TRUE)
	{
		usleep(1000000+(int)(2000000*rand()/(RAND_MAX+1.0)));//Dormido
		sem_wait(&semcomedor); //Intenta tomar un lugar en el comedor
		if (f->num % 2 == 0) {
			pthread_mutex_lock(&tenedor[f->num]);
			pthread_mutex_lock(&tenedor[(f->num+1)%5]);
		} else {
			pthread_mutex_lock(&tenedor[(f->num+1)%5]);
			pthread_mutex_lock(&tenedor[f->num]);
		}
		f->img = img2; //Se pone a comer
		//gtk_widget_queue_draw(draw1);//Se le ve comiendo
		g_idle_add(refrescar, NULL);
		usleep(2000000+(int)(2000000*rand()/(RAND_MAX+1.0)));//Come
		pthread_mutex_unlock(&tenedor[f->num]);//Libera el izquierdo
		pthread_mutex_unlock(&tenedor[(f->num+1)%5]);//Libera el derecho
		f->img = img1;//Se pone a dormir
		//gtk_widget_queue_draw(draw1);//Se le ve dormido
		g_idle_add(refrescar, NULL);
		sem_post(&semcomedor); //Sale del comedor
	}
	return NULL;
}
