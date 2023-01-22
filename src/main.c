#include <gtk/gtk.h>
#include <unistd.h>

static void on_button_clicked(GtkWidget *button, gpointer data) {
    pid_t pid = fork();
    if (pid == 0) {
        // This is the child process
        // Insert code for the process to be forked here
    } else if (pid > 0) {
        // This is the parent process
        g_print("Child process with PID %d has been forked.\n", pid);
    } else {
        // Fork failed
        g_print("Fork failed.\n");
    }
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Fork Process Example");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    GtkWidget *button = gtk_button_new_with_label("Fork Process");
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);

    gtk_container_add(GTK_CONTAINER(window), button);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
