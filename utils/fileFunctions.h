/*
 * fileFunctions.h
 *
 *  Created on: 30/9/2017
 *      Author: utnso
 */

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>
#include "utils/string.h"
#include "utils/list.h"

/*
 * Devuelve el tamanio del un archivo.
 */
off_t fsize(const char *filename);

/*
 * Chequea si existe el path y si no, lo crea.
 */

int checkIfPathExists(char *path);


/*---------------------------------------------------------------------------------------------------------------|
 *ATENCION: las siguiente funciones solo sirve en el caso que sea un archivo NO de texto(todo decorrido)         |
 *Ejemplo: un databin.                                                                                           |                      |  
 * Devuelve buffer del archivo en un char*.                                                                      |
 */
char* readAllFile(char *filename);
/*                                                                                                               |
 * Crea un archivo desde un buffer.                                                                              |
 */
FILE* createFileWithData(char*filename, char* buffer);
/*                                                                                                               |
 * Agrega data a un archivo ya creado.                                                                           |
 */
int appendFile(char* fileName, char* buffer);
//---------------------------------------------------------------------------------------------------------------|

/*                                                                                                               |
 * Obtiene el nombre de un FILE.                                                                           |
 */
char* getNameFromFile(FILE* file);
/*                                                                                                               |
 * Borra un directorio completo.                                                                           |
 */
void deleteDirectory(char* path);
/*                                                                                                               |
 * Obtiene el nombre desde un Path.                                                                           |
 */
char* getFileName(char* path);
/*                                                                                                               |
 * Obtiene cantidad de lineas del archivo.                                                                           |
 */
off_t getFileLines(const char *filename);
/*                                                                                                               |
 * Obtiene linea del archivo.                                                                           |
 */
char* readFileLine(char *filename, int line);