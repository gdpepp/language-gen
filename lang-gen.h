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
#include <locale.h>
#include "langstructs.h"
#include "utils/list.h"
#include "utils/string.h"
#include "utils/random.h"
#include "shuffle.h"
#include "utils/fileFunctions.h"
#include "initList.h"
#include "ortho.h"
#include "morpheme.h"
#include "word.h"

void setUp();

char *append(t_list *list, char sep);

t_language *makeBasicLanguage();

t_language *makeOrthoLanguage();

t_language *makeRandomLanguage();

t_lang_phon *getBasicPhon();

void printLanguage(t_language *lang);

void exitGracefully(t_language *lang);

char* shuffleLetters(char* letters);

char* getSyllStructure();

#endif //LANGUAGE_GEN_LANG_GEN_H
