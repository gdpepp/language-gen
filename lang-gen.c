#include <string.h>
#include "lang-gen.h"

int main(int argc, char **argv) {
    setUp();
    listInit();
    //printf("Hello, World!\n");

    int type;

    if (argv[1] != NULL) {
        type = toupper(argv[1][0]);
    } else {
        type = 'R';
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
    lang->orth = malloc(sizeof(t_lang_orth));
    lang->orth->cortho = list_create();
    lang->orth->vortho = list_create();

    return lang;
}

t_language *makeOrthoLanguage() {
    t_language *lang = makeBasicLanguage();
    lang->ortho = 1;
    return lang;
}

t_language *makeRandomLanguage() {

    t_language *lang = makeBasicLanguage();
    lang->ortho = 1;
    lang->morph = 1;
    lang->wordpool = 1;
    lang->phon->C = getLettersFromSet(conset);
    printf("%s\n", lang->phon->C);
    lang->phon->V = getLettersFromSet(vowset);
    printf("%s\n", lang->phon->V);
    lang->phon->S = getLettersFromSet(sset);
    printf("%s\n", lang->phon->S);
    lang->phon->F = getLettersFromSet(fset);
    printf("%s\n", lang->phon->F);
    lang->phon->L = getLettersFromSet(lset);
    printf("%s\n", lang->phon->L);
    lang->syllStructure = getSyllStructure();
    //TODO restricts?
    lang->orth->cortho = chooseOrthFromList(cOrthList, 2);
    lang->orth->vortho = chooseOrthFromList(vOrthList, 2);

    lang->minSyll = getRandByRange(1, 3);
    if (strlen(lang->syllStructure) < 3) lang->minSyll++;
    lang->maxSyll = getRandByRange(lang->minSyll + 1, 7);
    lang->joiner = choosecharFromString("   -");

    return lang;
}


void printLanguage(t_language *lang) {
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

void exitGracefully(t_language *lang) {
    //TODO
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
            string_capitalize(getWord(lang, key));
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


char *getSyllStructure() {
    int lines = 0;
    int pos = 0;
    char *ss = NULL;

   static char* path = "./config/syllstruct";

    if((lines = getFileLines(path)) == -1) {
    	//error
	exit(1);
    }

    pos = getRandByRange(0, lines);

    if ((ss = readFileLine(path, pos)) == NULL) {
        printf("error al leer estructura de silabas");
    }

    return ss;
}
