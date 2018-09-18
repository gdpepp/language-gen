#include <string.h>
#include "lang-gen.h"

int main() {
    setUp();
    listInit();
    printf("Hello, World!\n");
    
    int i;
    for(i = 0; i < 10;i++) {   
    //	printf("%d\n",getRandInt());
    	printf("%d\n", halfChance());
    }
    return EXIT_SUCCESS;
}

void setUp() {
    setlocale(LC_CTYPE, "");
    setSeed();
}

void shuffleList(t_list* list) {
    int i;
    int rand;
    int listlen = list_size(list);
    t_set* tmp = NULL;
    t_set* relem = NULL;
    t_set* left = NULL;

    for (i = 0; i < listlen; i++) {
        rand = getRandByRange(i, listlen);
        relem = list_get(list, rand);

        tmp = list_replace(list, i, relem);
        left = list_replace(list, i, tmp);

        free(left);
    }
}

char* append(t_list* list, char sep) {
    char *s = NULL;
    int i;
    int len = list_size(list);
    char *tmp;

    if (!len) {
        //get first word from list
        s = list_get(list, 0);
        s = malloc( strlen(s) + sizeof(char));


        for (i = 1; i < len; i++) {
            //concat to s
            tmp = list_get(list, i);
            string_append(&s, &sep);
            string_append(&s, tmp);
        }
    }
    return s;
}

char* makeName(t_language* lang, char* key) {
    char* name = NULL;
    char* w1 = NULL;
    char* w2 = NULL;   

    if(lang->definite == NULL) {
    	lang->definite = "the";
    }

    if(lang->genitive == NULL) {
    	lang->genitive = "of";
    }
    
    while(1) {
        if(halfChance()) {	
	    name = getWord(lang, key); 
	    string_capitalize(name);
	} else {
            w1 = getWord(lang,(likely() ? key : NULL));	    
            w2 = getWord(lang,(likely() ? key : NULL));	
	    string_capitalize(w1);    
	    string_capitalize(w2);  



	}    
    }

    return name;
}

