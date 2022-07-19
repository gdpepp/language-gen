#include "ortho.h"

const int LINELEN = 1024;


char* getFilepath(char* dir, char* name);

t_utf8 getCharFromAllOrtho(t_lang_orth *orth, t_utf8 c) {
    t_utf8 ch = c;

    ch = getcharfromOrth(orth->cortho, ch) ||
         getcharfromOrth(orth->vortho, ch) ||
         getcharfromOrth(defOrthList, ch);

    return ch;
}

t_utf8 getcharfromOrth(t_list *orth, t_utf8 c) {
    int len = list_size(orth);
    int i;
    t_orth *aux = NULL;
    t_utf8 result = 0;


    for (i = 0; i < len; i++) {
        aux = list_get(orth, i);
        if (aux->letter == (wchar_t *) &c) {
            result = c;
        }
    }

    return result;
}

t_list *chooseOrthFromList(t_list *orthlist, int exp) {
    t_orthset *aux  = chooseFromList(orthlist, exp);
    return aux->orthset;
}

void fillOrthoList(t_list *list, char *fname) {
    FILE *file = NULL;
    char line[LINELEN];
    char **keyvalue;
    int i;
    int lines = getFileLines(fname);
    t_orth *os = NULL;

    if ((file = fopen(fname, "r")) == NULL) {
        printf("Error opening %s: %s\n", fname, strerror(errno));
        exit(1);
    }

    for (i = 0; i < lines; i++) {
        memset(line, '\0', LINELEN);
        if (fgets(line, LINELEN, file) != line) {
            printf("Error fgets");
        }

        keyvalue = string_split(line, "=");

        os = malloc(sizeof(t_orth));
        os->sound = malloc(sizeof(char) * strlen(keyvalue[1]));
        os->letter = (wchar_t *) keyvalue[0];
        strcpy(os->sound, keyvalue[1]);
        list_add(list, os);
    }
    freeSplit(keyvalue);
    fclose(file);
}

void fillOrthoListFromDirectory(t_list *orthList, char *folder) {
    int i;
    char* filename = NULL;
    t_orthset* os = NULL;
    t_list* auxlist = NULL;
    char* dir = NULL;
    char** files = NULL;

    //form complete path with given folder
    dir = string_new();
    string_append(&dir, "config/ortho/");
    string_append(&dir, folder);

    files = getAllFilesFromDirectory(dir);

    for (i = 0; files[i] != NULL; i++) {
        filename = getFilepath(dir, files[i]);
	//fill orthset
	os = malloc(sizeof(t_orthset));
        os->name = malloc(strlen(files[i]) * sizeof(char));
        strcpy(os->name, files[i]);
	
	auxlist = list_create();        
	os->orthset = auxlist;
	fillOrthoList(auxlist, filename);
        list_add(orthList, os);

        free(filename);
    }

    free(dir);
    freeSplit(files);
}

char* getFilepath(char* dir, char* name) {
    char* filepath;
    filepath = strdup(dir);
    string_append(&filepath, "/");
    string_append(&filepath, name);

    return filepath;
}

t_orthset *chooseFromList(t_list *list, int exp) {
    int listlen = list_size(list);
    int index = getRandByRange(0, listlen);
    return list_get(list, index);
}
