#include "ortho.h"

//
// Created by utnso on 24/07/18.
//
t_utf8 getCharFromAllOrtho(t_lang_orth* orth , t_utf8 c) {
    t_utf8 ch = c;

    ch = getcharfromOrth(orth->cortho, ch) ||
         getcharfromOrth(orth->vortho, ch) ||
         getcharfromOrth(defOrthList, ch);

    return ch;
}

t_utf8 getcharfromOrth(t_list* orth, t_utf8 c) {
    int len = list_size(orth);
    int i;
    t_orth* aux =  NULL;
    t_utf8 result = 0;

    for (i = 0; i < len; i++) {
        aux = list_get(orth, i);
        if(aux->letter == c) {
            result = c;
        }
    }

    return result;
}