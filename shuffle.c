//
// Created by gdi on 18/9/2018.
//

#include "shuffle.h"

void *chooseFromSet(char** set, int exp) {
    int setlen = setSize(set);
    int index = getRandByRange(0, setlen);
    return set[index];
}

int setSize(char** set) {
    int i;
    for(i = 0; set[i] != NULL; i++) ;
    return i;
}

char *getLettersFromSet(char** set) {
    char* str = chooseFromSet(set, 2);
    char *letters = shuffleLetters(str);

    return letters;
}

char *shuffleLetters(char *letters) {
    int i;
    int rand;
    int len = strlen(letters);
    int len2 = 0;
    char *original = malloc((sizeof(char) * len) + 1);
    memset(original, '\0', len + 1);
    char *shuffled = malloc((sizeof(char) * len) + 1);
    memset(shuffled, '\0', len + 1);
    char rl;

    strcat(original, letters);
    //TODO ERROR CHECKING

    for (i = 0; i < len; i++) {
        len2 = strlen(original);
        rand = getRandByRange(0, len2);
        rl = original[rand];
        shuffled[i] = rl;

        //delete char from original
        memmove(&original[rand], &original[rand + 1], len - rand);
    }

    free(original);
    return shuffled;
}

void shuffleSet(char** set) {
    int i;
    int rand;
    int setlen = setSize(set);
    char* tmp = NULL;
    char *relem = NULL;

    for (i = 0; i < setlen; i++) {
        rand = getRandByRange(i, setlen);
        relem = set[rand];

        tmp = set[i];
        set[i] = relem;
        set[rand] = tmp;

    }
}

char choosecharFromString(char *str) {
    int len = strlen(str);
    int idx = 0;
    char *shuffled = shuffleLetters(str);
    idx = getRandByRange(0, len);

    return shuffled[idx];
}