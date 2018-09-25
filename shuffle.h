//
// Created by gdi on 18/9/2018.
//

#ifndef LANGUAGE_GEN_SHUFFLE_H
#define LANGUAGE_GEN_SHUFFLE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils/list.h"
#include "utils/random.h"
#include "langstructs.h"

char *getLettersFromSet(char** set);

int setSize(char** set);

char *shuffleLetters(char *letters);

void shuffleSet(char** set);

void *chooseFromSet(char** set, int exp);

char choosecharFromString(char *str);

#endif //LANGUAGE_GEN_SHUFFLE_H
