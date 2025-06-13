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

gboolean refrescar(gpointer); //Esto es parecido a void *, solo que es para compatibilidad

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

gboolean refrescar(gpointer data)
{
    gtk_widget_queue_draw(GTK_WIDGET(draw));
    return FALSE;
}

void on_btnEjecutar_clicked()
{
	gtk_widget_hide(btnEjecutar);
}


gboolean on_draw_draw(GtkDrawingArea *widget, cairo_t *cr)
{
	//int i;

    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);

	return FALSE;
}

gboolean on_draw_key_press_event(GtkDrawingArea *widget, GdkEventKey *event)
{
    gboolean bCambio = FALSE;

    switch(event->keyval){
        case GDK_KEY_Left:
            //bCambio = TRUE;
            printf("Izquierda");
            break;
    }

    return bCambio;
}



