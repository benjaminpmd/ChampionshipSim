/**
 * File containing all the functions to simulate a championship.
 * 
 * @authors Alice MABILLE, Benjamin PAUMARD
 * @version 1.0.0
 * @since February, 01 2023
*/
#ifndef __FILE_MANAGEMENT__
#define __FILE_MANAGEMENT__

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#define BUFFER_SIZE 2048

/**
 * Function that read a file and returns the buffer.
 * 
 * @param path path of the file to read.
 * @return the buffer of the file, the content.
*/
void readFile(char* path, char* buffer);

/**
 * TODO: documentation
*/
void writeFile(char* path, char* data);
#endif