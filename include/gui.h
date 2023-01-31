/**
 * File containing the GUI.
 * 
 * @authors Alice MABILLE, Benjamin PAUMARD
 * @version 1.0.0
 * @since January 25, 2023
*/
#ifndef __GUI__
#define __GUI__
#include "./libs.h"

void on_button_clicked(GtkWidget *button, gpointer data);

/**
 * Procedure that runs the GUI
*/
void runGui(int argc, char **argv);

#endif