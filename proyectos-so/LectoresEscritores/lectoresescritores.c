/**
 * Compilar: gcc -o lectoresescritores lectoresescritores.c -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
 * */
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

#define	ESCRITOR 	1
#define LECTOR		2

gchar szRol[64] = "Iniciando ..."; /*gchar viene de g.lib, 
es para ser compatible con otras distribuciones de Linux*/
int numproc = 5;
int rol = LECTOR;
int tesc = 0; //Tiempo de escritura
int tuberia[2];
char c; //dato testigo

GtkWidget *window;
GtkWidget *draw1;

cairo_surface_t *imgesc, *imglec, *imgesp, *imgact;
/*cairo puede escribir texto, trazar rayas, imagenes*/

int cambioderol(void *);

int main(int argc, char *argv[])
{
	pid_t pid;
	int i, ale;
	//i es para iterar en los procesos (5)
	//ale es un numero aleatorio
	GtkBuilder *builder;
	
	if(pipe(tuberia) == -1){
		perror("Error: [Tubería]\n");
		return -1;
	}
	
	write(tuberia[1], &c, 1);
	
	for(i = 0; i < numproc; i++){
		pid = fork();
		if(pid == -1){
			perror("Error al creal el hijo\n");
			break;
		}else if(pid != 0){ //si te clonas y el pid es diferente de cero
			break;
		}
		//pid == 0 es el hijo
		//pid != 0 (numero positivo) es el PID de un proceso
		//pid == -1 ya se acabó la memoria
	}
	srand((unsigned int) pid * 2);
	ale = 1 + (int) (10.0 * rand() / (RAND_MAX + 1.0));
	if(ale <= 9){
		rol = LECTOR;
		sprintf(szRol, "Lector activo %d", ale);
	}else{
		rol = ESCRITOR;
		sprintf(szRol, "Se va a solicitar escritura %d", ale);
	}
	
	gtk_init(&argc, &argv);
	
	imgesc = cairo_image_surface_create_from_png("esc.png");
	imglec = cairo_image_surface_create_from_png("lec.png");
	imgesp = cairo_image_surface_create_from_png("esp.png");
	imgact = imgesp;
	
	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "lectoresescritores.glade", NULL);
	
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
	draw1 = GTK_WIDGET(gtk_builder_get_object(builder, "draw1"));
	gtk_builder_connect_signals(builder, NULL);
	
	gtk_widget_show(window);
	
	gdk_threads_add_timeout(1000, cambioderol, NULL);
	gtk_main();
	
	cairo_surface_destroy(imgesc);
	cairo_surface_destroy(imglec);
	cairo_surface_destroy(imgesp);
	
	close(tuberia[0]);
	close(tuberia[1]);
	
	return 0;
}

void on_window_destroy()
{
	if(rol == ESCRITOR && tesc <= 4){
		write(tuberia[1], &c, 1);
		tesc = 0;
	}
	gtk_main_quit();
}

void on_btnSalir_clicked()
{
		on_window_destroy();
}

gboolean on_draw1_draw(GtkDrawingArea *widget, cairo_t *cr)
{
	cairo_set_source_rgb(cr, 0.5, 0.5, 1.0);
	cairo_select_font_face(cr, "Purisa",
							CAIRO_FONT_SLANT_NORMAL,
							CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size(cr, 18);
	if(rol == ESCRITOR){
		if(tesc > 0){
			imgact = imgesc;
		}else{
			imgact = imgesp;
		}
	}else{
		imgact = imglec;
	}
	cairo_translate(cr, 10, 20);
	cairo_show_text(cr, szRol);
	
	cairo_set_source_surface(cr, imgact, 20, 50);
	cairo_paint(cr);
	
	return FALSE;
}

int cambioderol(void *p)
{
	int ale;
	
	gtk_widget_queue_draw(draw1);
	if(rol == ESCRITOR){
		if(tesc == 0){
			read(tuberia[0], &c, 1);
		}
		sprintf(szRol, "Escritor Activo %d", tesc);
		gtk_widget_queue_draw(draw1);
		tesc++;
		if(tesc <= 4){
			return TRUE;
		}else{
			write(tuberia[1], &c, 1);
			tesc = 0;
		}
	}
	
	ale = 1 + (int) (10.0 * rand() / (RAND_MAX + 1.0));
	if(ale <= 9){
		rol = LECTOR;
		sprintf(szRol, "Lector activo %d", ale);
	}else{
		rol = ESCRITOR;
		sprintf(szRol, "Se va a solicitar escritura %d", ale);
	}
	
	gtk_widget_queue_draw(draw1);
	
	return TRUE;
}
