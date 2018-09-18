//
// Created by gdpepp on 23/07/18.
//

#ifndef LANGUAGE_GEN_LANGSTRUCTS_H
#define LANGUAGE_GEN_LANGSTRUCTS_H

#include "utils/list.h"
#include <wchar.h>

typedef wchar_t t_utf8;

/*
 * LISTS STRUCTURES
 */

typedef struct orth {
    wchar_t letter;
    char *sound;
} t_orth;

typedef struct set {
    char *setName;
    char *letters;
} t_set;

typedef struct rectifier {
    char *rectName;
    char *re;
} t_rectifier;

typedef struct orthset {
    char* name;
    t_list *orthset;
} t_orthset;


/*
 * LANG STRUCTURES
 */

typedef struct lang_phonemes {
    char* C;
    char* V;
    char* L;
    char* S;
    char* F;
} t_lang_phon;

typedef struct lang_orth {
    t_list* vortho;
    t_list* cortho;
} t_lang_orth;

typedef struct lang_con struct {
    char* key;
    t_list* elements;
} t_lang_construct;

typedef struct language {
    char* syllStructure;
    char* genitive;
    char* definite;
    bool ortho;
    bool morph;
    bool wordpool;
    char joiner;
    int exponent;
    int minSyll;
    int maxSyll;
    int minchar;
    int maxchar;
    t_list* words; // list of t_lang_construct
    t_list* names; // list of char*
    t_list* morphemes; // list of t_lang_construct
    t_lang_phon* phon;
    t_lang_orth* orth;
} t_language;

t_list *defOrthList;
t_list *cOrthList;
t_list *vOrthList;
t_list *conset;
t_list *sset;
t_list *lset;
t_list *fset;
t_list *vowset;
t_list *resset;

#endif //LANGUAGE_GEN_LANGSTRUCTS_H
