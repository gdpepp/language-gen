//
// Created by gdpepp on 01/09/2018
//

#ifndef LANGUAGE_GEN_WORD_H
#define LANGUAGE_GEN_WORD_H

#include "langstructs.h"
#include "utils/list.h"
#include "utils/string.h"
#include "utils/random.h"
#include "morpheme.h"
#include <string.h>
#include <stdarg.h>

char *makeWord(t_language *lang, char *key);

char *getWord(t_language *lang, char *key);

void joinByJoiner(char* joined, char* w2, char joiner);

char * getJoinedWordsByJoiner(char joiner, int count, ...);

#endif //LANGUAGE_GEN_WORD_H

