/*
* Compilar con: gcc -o lectoresescritores lectoresescritores.c -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic 
*/

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <glib.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

gchar szRol[64] = "Iniciando...";
GtkWidget *window;
GtkWidget *draw1;

int main(int argc, char *argv[]){
    GtkBuilder *builder;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();

    gtk_builder_add_from_file(builder, "lectoresescritores.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    draw1 = GTK_WIDGET(gtk_builder_get_object(builder, "draw1"));

    gtk_builder_connect_signals(builder, NULL);

    gtk_widget_show(window);

    gtk_main();

    return 0;
}

void on_window_destroy(){
    gtk_main_quit();
}

void on_Salir_clicked(){
    on_window_destroy();
}

gboolean on_draw1_draw(GtkDrawingArea *widget, cairo_t *cr){
    cairo_set_source_rgb(cr, 0.5, 0.5, 1.0);
    cairo_select_font_face(cr, "Purisa", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 18);
    cairo_translate(cr, 10, 20);
    cairo_show_text(cr, szRol);

    return FALSE;
}