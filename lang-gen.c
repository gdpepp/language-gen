#include <string.h>
#include "lang-gen.h"

int main() {
    listInit();
    printf("Hello, World!\n");
    return 0;
}

void* chooseFromList(t_list *list, int exp) {
    int randint = getRandInt();
    int listlen = list_size(list);

    exp ? exp : 1;

    double index = floor(pow(randint, exp) * listlen);
    return list_get(list, (int) index);
}

char chooseFromString(char* str, int exp) {
    int randint = getRandInt();
    size_t len = strlen(str);

    exp ? exp : 1;

    int index = (int) floor(pow(randint, exp) * len);
    return str[index];
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

int getRandInt() {
    srand( (unsigned int) time(NULL));
    return rand();
}


int getRandByRange(int lo, int hi) {
    int randint = getRandInt();

    if (hi == 0) {
        hi = lo;
        lo = 0;
    }

    return (int) floor(randint  * (hi - lo)) + lo;
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

char* spell(t_lang_orth* orth, bool isOrtho, char* syll) {
    char* s = NULL;
    size_t len = strlen(syll);
    t_utf8 c;

    int i;
    if (isOrtho) {
        for (i = 0; i < len; i++) {
            c = (t_utf8) syll[i];
            s += getCharFromAllOrtho(orth, c);
        }
    }
    return s;
}

char* makeSyllable(t_language *lang) {
    int i;
    size_t sylllen = strlen(lang->syllStructure);
    char *syll = string_new();
    char *phon;
    char ptype;
    char toAppend;
    bool rectified = false;

    while (!rectified) {
        for (i = 0; i < sylllen; i++) {
            ptype = lang->syllStructure[i];
            if (lang->syllStructure[i + 1] == '?') {
                i++;
                if (getRandInt() < 0.5) {
                    continue;
                }
            }


            phon = getPhonType(lang->phon, ptype);
            toAppend = chooseFromString(phon, lang->exponent);
            string_append(&syll, &toAppend);
        }

        /*TODO ver como evaluar regex -
         * ver si "lang.restricts[i].test(syll)" devuelve TRUE en error
         * for (i = 0; i < lang.restricts.length; i++) {
            if (lang.restricts[i].test(syll)) {

 |            rectified = true;
                break;
            }
        }
         */
        rectified = true;
    }

    return spell(lang->orth, lang->ortho, syll);
}

/*TODO hasta aca llegue. Seguir por la proxima funcion
 */
char* getMorpheme(t_language* lang, char* key) {
    int extras = 10;
    int n;
    int included = 0;
    char* morph = NULL;
    t_list* list = getConstructListFromList(lang->morphemes, key);
    int len = list_size(list);

    if (!lang->morph) {
        return makeSyllable(lang);
    }

    if (key != NULL) {
        extras = 1;
    }

    while (!included) {
        n = getRandByRange(len + extras, 0);
        morph = list_get(list,n);
        if (morph == NULL) {
            morph = makeSyllable(lang);

            included = constructIncludedInList(list, morph);

            if (!included) {
                addConstructToList(list, morph, key);
            }
        }
    }

    return morph;
}

void addConstructToList(t_list *list, char *construct, char *key) {
    int added = 0;
    int i;
    int len = list_size(list);
    t_lang_construct *elem = NULL;

    for (i = 0; i < len; i++) {
        elem = list_get(list, i);
        if(!strcmp(key, elem->key)) {
            list_add(elem->elements, construct);
            added = 1;
        }
    }

    if(!added) {
        addNewConstructElement(list, construct, key);
    }
}

void addNewConstructElement(t_list *list, char *construct, char *key) {
    t_lang_construct new = { .key = key, .elements = list_create()};
    list_add(new.elements, construct);

    list_add(list, &new);
}

int constructIncludedInList(t_list *list, char *m) {
    int included = 0;
    int i, j;
    int len = list_size(list);
    int clen;
    t_lang_construct *construct = NULL;
    char *aux = NULL;

    for (i = 0; i < len; i++) {
        construct = list_get(list, i);
        clen = list_size(construct->elements);
        for (j = 0; j < clen; j++) {
            aux = list_get(construct->elements, j);
            if (!strcmp(aux, m)) {
                //construct found
                included = 1;
                break;
            }
        }
    }
    return included;
}

t_list* getConstructListFromList(t_list* clist, char* key) {
    int i;
    int len = list_size(clist);
    t_list* res = NULL;
    t_lang_construct* aux = NULL;

    for(i = 0; i < len; i++) {
        aux = list_get(clist, i);
        if(aux->key == key) {
            res = aux->elements;
            break;
        }
    }
    return res;
}

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

//TODO
char* makeName(t_language* lang, char* key) {
    char* name = NULL;

    return name;
}

char* getPhonType(t_lang_phon* phon, char ptype) {
    char* result = NULL;

    switch (ptype) {
        case 'C':
            result = phon->C;
            break;
        case 'V':
            result = phon->V;
            break;
        case 'L':
            result = phon->L;
            break;
        case 'S':
            result = phon->S;
            break;
        case 'F':
            result = phon->F;
            break;
        default:
            result = &ptype;
            break;
    }

    return result;
}
