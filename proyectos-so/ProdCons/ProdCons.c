/**
 * Compilar: gcc -o ProdCons ProdCons.c -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
 * */
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <stdio.h>
#include <stdlib.h>

#define PRODUCTOR	1
#define CONSUMIDOR	2

pid_t pid;
int fildes[2];
int rol;
int elem = 0;

GtkWidget *window;
GtkWidget *btnProductor;
GtkWidget *btnConsumidor;
GtkWidget *draw1;

int main(int argc, char *argv[])
{
    GtkBuilder *builder;
    
    pipe(fildes);
    pid = fork();

    gtk_init(&argc, &argv);  

    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "ProdCons.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    btnProductor = GTK_WIDGET(gtk_builder_get_object(builder, "btnProductor"));
    btnConsumidor = GTK_WIDGET(gtk_builder_get_object(builder, "btnConsumidor"));
    draw1 = GTK_WIDGET(gtk_builder_get_object(builder, "draw1"));
    gtk_builder_connect_signals(builder, NULL);
    
    gtk_widget_show_all(window);
    if(pid == 0){
		rol = PRODUCTOR;
		gtk_widget_hide(btnConsumidor);
	}else{
		rol = CONSUMIDOR;
		gtk_widget_hide(btnProductor);
	}

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

gboolean on_draw1_draw(GtkDrawingArea *widget, cairo_t *cr)
{
	char szMensaje[128];
	
	cairo_set_source_rgb(cr, 0.5, 0.5, 1.0);
	cairo_select_font_face(cr, "Purisa",
							CAIRO_FONT_SLANT_NORMAL,
							CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size(cr, 18);

	cairo_translate(cr, 10, 50);
	if(rol == PRODUCTOR){
		sprintf(szMensaje, "Elementos producidos %d", elem);
		cairo_show_text(cr, szMensaje);
	}else if(rol == CONSUMIDOR){
		sprintf(szMensaje, "Elementos consumidos %d", elem);
		cairo_show_text(cr, szMensaje);
	}
	
	return FALSE;
}

void on_btnProductor_clicked()
{
	char c='\0';
	elem++;
	write(fildes[1], &c, sizeof(char));
	gtk_widget_queue_draw(draw1);
}

void on_btnConsumidor_clicked()
{
	char c;
	elem++;
	read(fildes[0], &c, sizeof(char));
	gtk_widget_queue_draw(draw1);
}
