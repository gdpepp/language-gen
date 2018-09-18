#include <string.h>
#include "lang-gen.h"

int main(int argc, char **argv) {
    setUp();
    listInit();
    printf("Hello, World!\n");

    int type;
    
    if (argv[1] !=NULL) {
        type = toupper(argv[1][0]);
    } else {
    	type = 'B';
    }
    
    t_language *lang = NULL;

    switch (type) {
        case ('B'):
            lang = makeBasicLanguage();
            break;
        case ('O'):
            lang = makeOrthoLanguage();
            break;
        case ('R'):
            lang = makeRandomLanguage();
            break;
        default:
            printf("argument not recognized\n");
            exit(1);
    }

    //print result
    printLanguage(lang);

    //free all
    exitGracefully(lang);

    return EXIT_SUCCESS;
}

t_language *makeBasicLanguage() {

    t_language *lang = malloc(sizeof(t_language));

    lang->syllStructure = "CVC";
    lang->genitive = NULL;
    lang->definite = NULL;
    lang->ortho = 0;
    lang->morph = 0;
    lang->wordpool = 0;
    lang->joiner = ' ';
    lang->exponent = 2;
    lang->minSyll = 1;
    lang->maxSyll = 1;
    lang->minchar = 5;
    lang->maxchar = 12;
    lang->names = list_create();
    lang->words = list_create();
    lang->morphemes = list_create();
    lang->phon = getBasicPhon();
    lang->ortho = NULL;

    return lang;
}

t_language *makeOrthoLanguage() {
    t_language *lang = makeBasicLanguage();
    //TODO
    return lang;
}

t_language *makeRandomLanguage() {
    t_language *lang = makeBasicLanguage();
    //TODO
    return lang;
}

void printLanguage(t_language* lang) {
//TODO
	
}

t_lang_phon *getBasicPhon() {
    t_lang_phon *phon = malloc(sizeof(t_lang_phon));
    phon->C = "ptkmnls";
    phon->V = "aeiou";
    phon->S = "s";
    phon->F = "mn";
    phon->L = "rl";

    return phon;
}

void setUp() {
    setlocale(LC_CTYPE, "");
    setSeed();
}

void exitGracefully(t_language* lang) {
   //TODO
}

void shuffleList(t_list *list) {
    int i;
    int rand;
    int listlen = list_size(list);
    t_set *tmp = NULL;
    t_set *relem = NULL;
    t_set *left = NULL;

    for (i = 0; i < listlen; i++) {
        rand = getRandByRange(i, listlen);
        relem = list_get(list, rand);

        tmp = list_replace(list, i, relem);
        left = list_replace(list, i, tmp);

        free(left);
    }
}

char *makeName(t_language *lang, char *key) {
    char *name = NULL;
    char *w1 = NULL;
    char *w2 = NULL;
    int used = 1;
    if (lang->definite == NULL) {
        lang->definite = "the";
    }
    if (lang->genitive == NULL) {
        lang->genitive = "of";
    }

    while (used) {
        if (halfChance()) {
            name = getWord(lang, key);
            string_capitalize(name);
        } else {
            w1 = getWord(lang, (likely() ? key : NULL));
            w2 = getWord(lang, (likely() ? key : NULL));
            string_capitalize(w1);
            string_capitalize(w2);

            if (halfChance()) {
                name = getJoinedWordsByJoiner(lang->joiner, 2, w1, w2);
            } else {
                //add genitive at beginning of name
                name = getJoinedWordsByJoiner(lang->joiner, 3, w1, lang->genitive, w2);
            }
        }

        //add definite at beginning of name
        if (rarely()) {
            name = getJoinedWordsByJoiner(lang->joiner, 2, lang->definite, name);
        }

        //verify requirements
        if ((strlen(name) > lang->minchar) || (strlen(name) < lang->maxchar)) {
            used = constructIncludedInList(lang->names, name);
            if (!used) {
                list_add(lang->names, name);
            }
        }
    }

    return name;
}

