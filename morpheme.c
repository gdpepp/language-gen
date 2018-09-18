//
// Created by gdpepp on 01/09/2018
//

#include "morpheme.h"

void *chooseFromList(t_list *list, int exp) {
    int randint = getRandInt();
    int listlen = list_size(list);

    exp ? exp : 1;

    double index = floor(pow(randint, exp) * listlen);
    return list_get(list, (int) index);
}

char chooseFromString(char *str, int exp) {
    int randint = getRandInt();
    size_t len = strlen(str);

    exp ? exp : 1;

    int index = (int) floor(pow(randint, exp) * len);
    return str[index];
}

char *spell(t_lang_orth *orth, bool isOrtho, char *syll) {
    char *s = NULL;
    size_t len = strlen(syll);
    t_utf8 c;

    int i;
    if (isOrtho) {
        for (i = 0; i < len; i++) {
            c = (t_utf8) syll[i];
            s += getCharFromAllOrtho(orth, c);
        }
    }
    return s;
}

char *getPhonType(t_lang_phon *phon, char ptype) {
    char *result = NULL;

    switch (ptype) {
        case 'C':
            result = phon->C;
            break;
        case 'V':
            result = phon->V;
            break;
        case 'L':
            result = phon->L;
            break;
        case 'S':
            result = phon->S;
            break;
        case 'F':
            result = phon->F;
            break;
        default:
            result = &ptype;
            break;
    }

    return result;
}

char *makeSyllable(t_language *lang) {
    int i;
    size_t sylllen = strlen(lang->syllStructure);
    char *syll = string_new();
    char *phon;
    char ptype;
    char toAppend;
    bool rectified = false;

    while (!rectified) {
        for (i = 0; i < sylllen; i++) {
            ptype = lang->syllStructure[i];
            if (lang->syllStructure[i + 1] == '?') {
                i++;
                if (getRandInt() < 0.5) {
                    continue;
                }
            }


            phon = getPhonType(lang->phon, ptype);
            toAppend = chooseFromString(phon, lang->exponent);
            string_append(&syll, &toAppend);
        }

        /*TODO ver como evaluar regex -
         * ver si "lang.restricts[i].test(syll)" devuelve TRUE en error
         * for (i = 0; i < lang.restricts.length; i++) {
            if (lang.restricts[i].test(syll)) {

 |            rectified = true;
                break;
            }
        }
         */
        rectified = true;
    }

    return spell(lang->orth, lang->ortho, syll);
}

char *getMorpheme(t_language *lang, char *key) {
    int extras = 10;
    int n;
    int included = 0;
    char *morph = NULL;
    t_list *list = getConstructListFromList(lang->morphemes, key);
    int len = list_size(list);

    if (!lang->morph) {
        return makeSyllable(lang);
    }

    if (key != NULL) {
        extras = 1;
    }

    while (!included) {
        n = getRandByRange(len + extras, 0);
        morph = list_get(list, n);
        if (morph == NULL) {
            morph = makeSyllable(lang);

            included = constructIncludedInList(list, morph);

            if (!included) {
                addConstructToList(list, morph, key);
            }
        }
    }

    return morph;
}


