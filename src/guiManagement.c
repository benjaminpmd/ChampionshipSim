#include "../include/guiManagement.h"
#include "../include/config.h"

#include <gtk/gtk.h>

// Callback function for the "Get Input" button
void get_input(GtkWidget *widget, gpointer data) {
  const gchar *input;

  // Retrieve the user input from the entry box
  input = gtk_entry_get_text(GTK_ENTRY(data));

  // Display the user input
  display_input(gtk_label_new(""), input, NULL);
}

// Function to display the user input in the label
void display_input(GtkWidget *label, const gchar *str, gpointer data) {
  gchar buffer[256];

  // Update the label with the user input
  sprintf(buffer, "Number entered: %s", str);
  gtk_label_set_text(GTK_LABEL(label), buffer);

  // Replace the old label with the new one
  gtk_container_remove(GTK_CONTAINER(gtk_widget_get_parent(label)), label);
  gtk_box_pack_start(GTK_BOX(gtk_widget_get_parent(label)), label, FALSE, FALSE, 0);

  // Show the updated label
  gtk_widget_show_all(gtk_widget_get_parent(label));
}

void on_button_clicked(GtkWidget *button, gpointer data) {
    pid_t pid = fork();
    if (pid == 0) {
        // This is the child process
        // Insert code for the process to be forked here
        printf("Hey, I'm the fork!\n");
        _exit(0);
    } else if (pid > 0) {
        // This is the parent process
        g_print("Child process with PID %d has been forked.\n", pid);
    } else {
        // Fork failed
        g_print("Fork failed.\n");
    }
}

void runGui(int argc, char **argv) {
    /*
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Fork Process Example");
    gtk_window_set_default_size(GTK_WINDOW(window), WIDTH, HEIGHT);

    GtkWidget *button = gtk_button_new_with_label("Fork Process");
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);

    gtk_container_add(GTK_CONTAINER(window), button);

    gtk_widget_show_all(window);

    gtk_main();
    */
GtkWidget *window, *label, *entry, *button, *vbox;
  gchar *str = "Enter a number:";

  gtk_init(&argc, &argv);

  // Create the main window
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Input Number");
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  // Create the label for displaying the number
  label = gtk_label_new(str);
  vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);

  // Create the entry box for user input
  entry = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);

  // Create the button for retrieving user input
  button = gtk_button_new_with_label("Get Input");
  g_signal_connect(button, "clicked", G_CALLBACK(get_input), entry);
  gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

  gtk_container_add(GTK_CONTAINER(window), vbox);

  // Show the main window
  gtk_widget_show_all(window);

  // Run the GTK main loop
  gtk_main();
}
