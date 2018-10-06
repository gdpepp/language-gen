/*
 * fileFunctions.c
 *
 *  Created on: 30/9/2017
 *      Author: utnso
 */

#include "fileFunctions.h"

int MAX_LINE_LEN = 1024;

#define MB_SIZE	(1024*1024)

off_t fsize(const char *filename) {
	struct stat st;
	if (stat(filename, &st) == 0)
		return st.st_size;
	printf("No se pudo determinar el tamanio del archivo: %s", strerror(errno));
	return -1;
}

off_t getFileLines(const char *filename) {
	FILE *file;
	off_t fileSize = 0;
	off_t lines = 0;
    int ch;
	file = fopen(filename, "r");

	if (!file) {
		printf("No se pudo abrir el archivo: %s\n", strerror(errno));
		return -1;
	}
	fileSize = fsize(filename);

	if (fileSize == 0) {
		fclose(file);
		return -1;
	}

	while(!feof(file))
	{
		ch = fgetc(file);
		if(ch == '\n')
		{
			lines++;
		}
	}

	if (ferror(file)) {
		fclose(file);
		printf("Error al leer el archivo : %s\n", strerror(errno));
		return -1;
	}
	fclose(file);

	return lines;

}

//int checkIfPathExists(char *path){
//	char **dir = string_split(path, "/");
//	char *currentDir = string_new();
//	struct stat st;
//	int i, ret;
//	for(i=0; dir[i+1] != NULL ;i++){
//		printf("Parte del dir a analizar: %s", dir[i]);
//		string_append(&currentDir, "/");
//		string_append(&currentDir, dir[i]);
//		printf("Chequeando si el dir existe: %s", currentDir);
//		stat(currentDir, &st);
//		if(!(stat(currentDir, &st)==0 && S_ISDIR(st.st_mode))){
//			if(mkdir(currentDir, 0777)){
//				printf("Error en MKDIR de %s. %s\n",currentDir, strerror(errno));
//				ret = EXIT_FAILURE;
//				break;
//			}
//			printf("Cree dir: %s", currentDir);
//		}
//	}
//	free(currentDir);
//	freeSplit(dir);
//	ret = EXIT_SUCCESS;
//	return ret;
//}

char* readAllFile(char *filename) {
	FILE *file;
	off_t fileSize;
	char *fileContent;

	file = fopen(filename, "r");

	if (!file) {
		printf("No se pudo abrir el archivo: %s", strerror(errno));
		return NULL;
	}
	fileSize = fsize(filename);

	if (fileSize == 0) {
		fclose(file);
		return NULL;
	}
	fileContent = malloc(fileSize + 1);
	if (fileContent == NULL) {
		fclose(file);
		printf("No se pudo alocar memoria para leer el archivo : %s",
				strerror(errno));
		return NULL;
	}
	fread(fileContent, sizeof(char), fileSize, file);
	//fileContent[fileSize] = '\0';

	if (ferror(file)) {
		fclose(file);
		printf("Error al leer el archivo : %s", strerror(errno));
		return NULL;
	}
	fclose(file);

	return fileContent;
}

char* readFileLine(char *filename, int line) {
    FILE *file;
    int ch;
    int linenum = 0;
    char* buff = NULL;
    file = fopen(filename, "r");

    if (!file) {
        printf("No se pudo abrir el archivo: %s", strerror(errno));
        return NULL;
    }

    buff = malloc(sizeof(char) * MAX_LINE_LEN);
    if(fgets(buff, line, file) != buff) {
        printf("Error en fgets");
    }

    if (ferror(file)) {
        fclose(file);
        printf("Error al leer el archivo : %s", strerror(errno));
        return NULL;
    }
    fclose(file);

    return buff;
}

FILE* createFileWithData(char*filename, char* buffer) {
	FILE *file;
	file = fopen(filename, "w");
	if (!file) {
		printf("No se pudo abrir el archivo: %s", strerror(errno));
		return NULL;
	}
	fwrite(buffer, strlen(buffer), sizeof(buffer), file);
	if (ferror(file)) {
		fclose(file);
		printf("Se produjo un error en el archivo");
		return NULL;
	}

	fclose(file);
	return file;
}

//char* getNameFromFile(FILE* file) {
//	char path[1024];
//	char result[1024];
//	int fd = fileno(file);
//
//	sprintf(path, "/proc/self/fd/%d", fd);
//	memset(result, 0, sizeof(result));
//	readlink(path, result, sizeof(result) - 1);
//
//	int fileLength = strlen(result);
//	char* fileName = malloc(fileLength + 1);
//	memcpy(fileName, result, fileLength);
//
//	return fileName;
//}

int appendFile(char* fileName, char* buffer) {
	FILE* file = fopen(fileName, "a");

	if (!file) {
		printf("No se pudo abrir el archivo: %s", strerror(errno));
		return EXIT_FAILURE;
	}

    fwrite(buffer, strlen(buffer), sizeof(buffer), file);
	if (ferror(file)) {
		fclose(file);
		printf("Se produjo un error en el archivo");
		return EXIT_FAILURE;
	}
	fclose(file);
	return EXIT_SUCCESS;
}

void deleteDirectory(char* path) {
	char *archivosPath = string_new();
	char *aux;
	string_append(&archivosPath, path);
	DIR  *d = opendir(archivosPath);
	struct dirent *dir;

	if(d){
		while((dir = readdir(d))){
			aux = strdup(archivosPath);
			string_append(&aux, "/");
			string_append(&aux, dir->d_name);
			remove(aux);
			free(aux);
		}
	}
	remove(archivosPath);
	free(archivosPath);
	closedir(d);
}

char* getFileName(char* path) {
	char** split = string_split(path, "/");
	int i = 0;
	for (i = 0; split[i]; i++);
	char* aux = strdup(split[i - 1]);

	freeSplit(split);

	return aux;
}

void getAllFilesFromDirectory(char** files, char *dname) {
    char *aux;
    DIR *d = opendir(dname);
    struct dirent *fd;
    int i = 0;
    if (d) {
        while ((fd = readdir(d))) {
            if (strcmp(fd->d_name, ".") && strcmp(fd->d_name, "..")) {
                aux = string_new();
                string_append(&aux, fd->d_name);

                files = realloc(files, sizeof(char*) * i);
		files[i] = aux;
                i++;
            }
        }
        //add NULL to last position for checking purposes
        files[i] = NULL;
    }
    closedir(d);
}

void getAllLinesFromFile(char **set, char *fname) {
    FILE *file = NULL;
    char line[MAX_LINE_LEN];
    int i;
    int lines = getFileLines(fname);
    char** content = NULL;

    if ((file = fopen(fname, "r")) == NULL) {
        printf("Error opening %s: %s\n", fname, strerror(errno));
        exit(1);
    }

    for (i = 0; i < lines; i++) {
        memset(line, '\0', MAX_LINE_LEN);
        if (fgets(line, MAX_LINE_LEN, file) != line) {
            printf("Error fgets");
        }

        //add line to set
        content[i] = line;
    }
    fclose(file);
    content[++i] = NULL;
}

