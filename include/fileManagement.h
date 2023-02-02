/**
 * File containing all the functions to simulate a championship.
 * 
 * @authors Alice MABILLE, Benjamin PAUMARD
 * @version 1.0.0
 * @since February, 01 2023
*/
#ifndef __FILE_MANAGEMENT__
#define __FILE_MANAGEMENT__

#include "libs.h"

#define BUFFER_SIZE 2048

char* readFile(char* path);

void writeFile(char* path, char* data);

#endif