#include "lang-gen.h"


int main() {
    listInit();
    printf("Hello, World!\n");
    return 0;
}




//TODO test
void* choose(t_list* list, int exp) {

    srand( (unsigned int) time(NULL));
    int randint = rand();
    int listlen = list_size(list);

    if(!exp) {
        exp = 1;
    }
    double index = floor(pow(randint, exp) * listlen);

    return list_get(list, (int) index);
}

//TODO test
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


//TODO test
int getRandByRange(int lo, int hi) {
    int randint = getRandInt();

    if (hi == 0) {
        hi = lo;
        lo = 0;
    }

    return (int) floor(randint  * (hi - lo)) + lo;
}


//TODO test - join renamed to "append"
char* append(t_list* list, char sep) {
    char *s = NULL;
    int i;
    int len = list_size(list);
    char *tmp;

    if (!len) {
        //get first word from list
        s = list_get(list, 0);
        s = malloc(strlen(s) + sizeof(char));

        for (i = 1; i < len; i++) {
            //concat to s
            tmp = list_get(list, i);
            string_append(&s, &sep);
            string_append(&s, tmp);
        }
    }
    return s;
}

//TODO esto lo deje por la mitad
char* spell(t_language lang, char* syll) {
    char* s = NULL;
    int i;
    int len = strlen(syll);
    char c;

    if (ortho) {
        for (i = 0; i < len; i++) {
            c = syll[i];
            s += getOrthoFromAll(lang, c);

                    lang.cortho[c] || lang.vortho[c] || defaultOrtho[c] || c;
        }
    }
    return s;
}

//TODO esto lo deje por la mitad
void makeSyllable(t_language* lang) {
    int i;
    char* syll = NULL;
    int sylllen = strlen(lang->syllStructure);
    char ptype;
    bool bad = false;

    while (1) {
        for (i = 0; i < sylllen; i++) {
            ptype = lang->syllStructure[i];
            if (lang->syllStructure[i + 1] == '?') {
                i++;
                if (getRandInt() < 0.5) {
                    continue;
                }
            }
            syll += choose(lang.phonemes[ptype], lang->exponent);
        }

        for (i = 0; i < lang.restricts.length; i++) {
            if (lang.restricts[i].test(syll)) {
                bad = true;
                break;
            }
        }
        if (bad) continue;
        return spell(lang, syll);
    }
}
