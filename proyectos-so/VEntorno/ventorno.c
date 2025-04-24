/*
 * gcc -o ventorno ventorno.c -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
 * */
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

GtkWidget *window;
GtkWidget *btnSalir;
GtkWidget *btnAplicar;
GtkWidget *listbox;

extern char **environ;

int main(int argc, char *argv[])
{
	GtkBuilder *builder;
	
	gtk_init(&argc, &argv);
	
	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "ventorno.glade", NULL);
	
	window = GTK_WIDGET(gtk_builder_get_object(builder,"window"));
	btnSalir = GTK_WIDGET(gtk_builder_get_object(builder,"btnSalir"));
	btnAplicar = GTK_WIDGET(gtk_builder_get_object(builder,"btnAplicar"));
	listbox = GTK_WIDGET(gtk_builder_get_object(builder,"listbox"));
	
	
	gtk_builder_connect_signals(builder, NULL);
	
	gtk_widget_show(window);
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

void on_btnAplicar_clicked()
{
	GtkWidget *child;
    GtkWidget *label;
    GtkWidget *box;
    int i;

    while ((child = GTK_WIDGET(gtk_container_get_children(GTK_CONTAINER(listbox)))) != NULL) {
        gtk_widget_destroy(child);
    }

    for (i = 0; environ[i] != NULL; i++) {
        box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
        label = gtk_label_new(environ[i]);
        gtk_label_set_xalign(GTK_LABEL(label), 0.0);
        gtk_box_pack_start(GTK_BOX(box), label, TRUE, TRUE, 0);
        gtk_list_box_insert(GTK_LIST_BOX(listbox), box, -1);
    }

    gtk_widget_show_all(window);
    gtk_widget_hide(btnAplicar);
}
