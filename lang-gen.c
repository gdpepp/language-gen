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

char *makeSyllable(t_language *lang) {
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
    t_list* list = getMorphemeListFromList(lang->morphemes, key);
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

            included = morphIncludedInList(list, morph);

            if (!included) {
                addMorphToList(list, morph, key);
            }
        }
    }

    return morph;
}

void addMorphToList(t_list *list, char *morph, char *key) {
    int added = 0;
    int i;
    int len = list_size(list);
    t_lang_morph *morphElem = NULL;

    for (i = 0; i < len; i++) {
        morphElem = list_get(list, i);
        if(!strcmp(key, morphElem->key)) {
            list_add(morphElem->morphemes, morph);
            added = 1;
        }
    }

    if(!added) {
        addNewMorphElement(list, morph, key);
    }
}

void addNewMorphElement(t_list *list, char *morph, char *key) {
    t_lang_morph new = { .key = key, .morphemes = list_create()};
    list_add(new.morphemes, morph);

    list_add(list, &new);
}

int morphIncludedInList(t_list *list, char *m) {
    int included = 0;
    int i, j;
    int len = list_size(list);
    int mlen;
    t_lang_morph *morphElem = NULL;
    char *aux = NULL;

    for (i = 0; i < len; i++) {
        morphElem = list_get(list, i);
        mlen = list_size(morphElem->morphemes);
        for (j = 0; j < mlen; j++) {
            aux = list_get(morphElem->morphemes, j);
            if (!strcmp(aux, m)) {
                //morph found
                included = 1;
                break;
            }
        }
    }
    return included;
}

t_list* getMorphemeListFromList(t_list* morphemes, char* key) {
    int i;
    int len = list_size(morphemes);
    t_list* res = NULL;
    t_lang_morph* aux = NULL;

    for(i = 0; i < len; i++) {
        aux = list_get(morphemes, i);
        if(aux->key == key) {
            res = aux->morphemes;
            break;
        }
    }
    return res;
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