//
// Created by gdi on 25/07/2018.
//

#ifndef LANGUAGE_GEN_ORTHO_H
#define LANGUAGE_GEN_ORTHO_H

#include "langstructs.h"
#include "shuffle.h"
#include <string.h>

t_utf8 getCharFromAllOrtho(t_lang_orth *orth, t_utf8 c);

t_utf8 getcharfromOrth(t_list *orth, t_utf8 c);

t_list *chooseOrthFromList(t_list *orthlist, int exp);

#endif //LANGUAGE_GEN_ORTHO_H
