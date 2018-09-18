#include "word.h"

char *makeWord(t_language *lang, char *key) {
    int nsylls = getRandByRange(lang->minSyll, lang->maxSyll + 1);
    int randompos = getRandByRange(nsylls, 0);
    int i;
    char *keys[nsylls];
    keys[randompos] = key;
    char *word = string_new();
    char *morphemeToAppend = NULL;

    for (i = 0; i < nsylls; i++) {
        morphemeToAppend = getMorpheme(lang, keys[i]);
        string_append(&word, morphemeToAppend);

        free(keys[i]);
    }

    free(keys);
    return word;
}

char *getWord(t_language *lang, char *key) {
    int extras;
    int n;
    int included = 0;
    char *word = NULL;

    if (key != NULL) {
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

char *append(t_list *list, char sep) {
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

char * getJoinedWordsByJoiner(char joiner, int count, ...) {
    char* joined = string_new();
    char* w = NULL;
    int i;
    va_list args;
    va_start(args, count); // tell it the stack starts with "count"

    // get first argument
    w = va_arg(args, char*);
    string_append(&joined, w);

    // inside the while(), pull int args off the stack:
    for(i = 1; i < count; i++) {
        w = va_arg(args, char*); // get next argument
        joinByJoiner(joined, w, joiner);
    }

    va_end(args);  // clean up

    return joined;
}

void joinByJoiner(char* joined, char* w2, char joiner) {
    string_append(&joined, &joiner);
    string_append(&joined, w2);
}