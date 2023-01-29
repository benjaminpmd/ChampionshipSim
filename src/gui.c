#include "../include/libs.h"
#include "../include/gui.h"
#include "../include/config.h"

void runGui(int argc, char **argv) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Fork Process Example");
    gtk_window_set_default_size(GTK_WINDOW(window), WIDTH, HEIGHT);

    GtkWidget *button = gtk_button_new_with_label("Fork Process");
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);

    gtk_container_add(GTK_CONTAINER(window), button);

    gtk_widget_show_all(window);

    gtk_main();
}