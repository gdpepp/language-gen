//
// Created by utnso on 23/07/18.
//

#ifndef LANGUAGE_GEN_LANG_GEN_H
#define LANGUAGE_GEN_LANG_GEN_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "langstructs.h"
#include "utils/list.h"
#include "utils/string.h"
#include "utlis/random.h"
#include "random.h"
#include "initList.h"
#include "ortho.h"

int getRandByRange(int lo, int hi);

int getRandByRange(int lo, int hi);

int getRandInt();

int constructIncludedInList(t_list* list, char *m);

void addConstructToList(t_list *list, char *morph, char *key);

void addNewConstructElement(t_list *list, char *morph, char *key);

void shuffleList(t_list *list);

void *chooseFromList(t_list *list, int exp);

char chooseFromString(char *str, int exp);

char *append(t_list *list, char sep);

char *spell(t_lang_orth *orth, bool isOrtho, char *syll);

char *makeSyllable(t_language *lang);

char *getPhonType(t_lang_phon *phon, char ptype);

t_list* getConstructListFromList(t_list* clist, char* key);

#endif //LANGUAGE_GEN_LANG_GEN_H
