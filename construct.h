//
// Created by gdpepp on 01/09/2018
//

#ifndef LANGUAGE_GEN_CONSTRUCT_H
#define LANGUAGE_GEN_CONSTRUCT_H

#include "langstructs.h"
#include "utils/list.h"
#include "utils/string.h"
#include "utils/random.h"
#include <string.h>

char* makeWord(t_language* lang, char* key);

char* getWord(t_language* lang, char* key);

void addConstructToList(t_list *list, char *construct, char *key);

void addNewConstructElement(t_list *list, char *construct, char *key);

int constructIncludedInList(t_list *list, char *m);

t_list* getConstructListFromList(t_list* clist, char* key);

#endif //LANGUAGE_GEN_WORD_H

