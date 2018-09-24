//
// Created by gdi on 18/9/2018.
//

#include "shuffle.h"

void *chooseFromList(t_list *list, int exp) {
    int listlen = list_size(list);
    int index = getRandByRange(0, listlen);
    return list_get(list, index);
}

char *getLettersFromSet(t_list *list) {
    t_set *set = chooseFromList(list, 2);
    printf("%s\n", set->letters);
    char *letters = shuffleLetters(set->letters);

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

char choosecharFromString(char *str) {
    int len = strlen(str);
    int idx = 0;
    char *shuffled = malloc(sizeof(char) * len + 1);
    shuffled = shuffleLetters(str);
    idx = getRandByRange(0, len);

    return shuffled[idx];
}