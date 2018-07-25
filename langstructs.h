//
// Created by utnso on 23/07/18.
//

#ifndef LANGUAGE_GEN_LANGSTRUCTS_H
#define LANGUAGE_GEN_LANGSTRUCTS_H

#include "utils/list.h"

typedef unsigned char utf8_t;

typedef struct orth {
    utf8_t letter;
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


typedef struct language {
    char* syllStructure;
    bool ortho;
    bool morph;
    bool wordpool;
    char joiner;
    int exponent;
    int minSyll;
    int maxSyll;
    int minchar;
    int maxchar;
    t_list* morphemes;
    t_list* phonemes;
    t_list* words;
    t_list* names;

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
