#include "word.h"

char* makeWord(t_language* lang, char* key) {
    int nsylls =  getRandByRange(lang->minSyll, lang->maxSyll + 1);
    int randompos = getRandByRange(nsylls, 0);
    int i;
    char* keys[nsylls];
    keys[randompos] = key;
    char* word = string_new();
    char* morphemeToAppend = NULL;
    
    for(i = 0; i < nsylls; i++) {
    	morphemeToAppend = getMorpheme(lang, keys[i]);
	string_append(&word, morphemeToAppend);
	
	free(keys[i]);
}

    free(keys);
return word;
}

char* getWord(t_language* lang, char* key) {
    int extras;
    int n;
    int included = 0;
    char* word = NULL;

    if(key != NULL) {
        extras = 2;
    } else {
        extras = 3;
    }
    
    while (!included) {
        n = getRandByRange(list_size(lang->words) + extras, 0);
        word = list_get(lang->words, n);

        if (!word) {
            word = makeWord(lang, key);
            included = constructIncludedInList(lang->words, word);

            if (!included) {
                addConstructToList(lang->words, word, key);
            }
        
	}
    }

    return word; 
}

