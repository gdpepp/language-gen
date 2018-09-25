//
// Created by gdi on 25/07/2018.
//

#ifndef LANGUAGE_GEN_ORTHO_H
#define LANGUAGE_GEN_ORTHO_H

#include "langstructs.h"
#include "utils/fileFunctions.h"
#include "shuffle.h"
#include <string.h>

t_utf8 getCharFromAllOrtho(t_lang_orth *orth, t_utf8 c);

t_utf8 getcharfromOrth(t_list *orth, t_utf8 c);

t_list *chooseOrthFromList(t_list *orthlist, int exp);

void fillOrthoList(t_list* list, char* fname);

void fillOrthoListFromDirectory(t_list* orthList, char* dir);

t_orthset *chooseFromList(t_list *list, int exp);

#endif //LANGUAGE_GEN_ORTHO_H
