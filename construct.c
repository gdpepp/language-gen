//
// Created by gdpepp on 01/09/2018
//

#include "construct.h"

void addConstructToList(t_list *list, char *construct, char *key) {
    int added = 0;
    int i;
    int len = list_size(list);
    t_lang_construct *elem = NULL;

    for (i = 0; i < len; i++) {
        elem = list_get(list, i);
        if (!strcmp(key, elem->key)) {
            list_add(elem->elements, construct);
            added = 1;
        }
    }

    if (!added) {
        addNewConstructElement(list, construct, key);
    }
}

void addNewConstructElement(t_list *list, char *construct, char *key) {
    t_lang_construct new = {.key = key, .elements = list_create()};
    list_add(new.elements, construct);

    list_add(list, &new);
}

int constructIncludedInList(t_list *list, char *m) {
    int included = 0;
    int i, j;
    int len = list_size(list);
    int clen;
    t_lang_construct *construct = NULL;
    char *aux = NULL;

    for (i = 0; i < len; i++) {
        construct = list_get(list, i);
        clen = list_size(construct->elements);
        for (j = 0; j < clen; j++) {
            aux = list_get(construct->elements, j);
            if (!strcmp(aux, m)) {
                //construct found
                included = 1;
                break;
            }
        }
    }
    return included;
}

t_list *getConstructListFromList(t_list *clist, char *key) {
    int i;
    int len = list_size(clist);
    t_list *res = NULL;
    t_lang_construct *aux = NULL;

    for (i = 0; i < len; i++) {
        aux = list_get(clist, i);
        if (aux->key == key) {
            res = aux->elements;
            break;
        }
    }
    return res;
}
