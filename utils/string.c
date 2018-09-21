//
// Created by utnso on 23/07/18.
//

#include <string.h>
#include "string.h"

static void _string_do(char *text, void (*closure)(char *));

static void _string_lower_element(char *ch);

static void _string_upper_element(char *ch);

char** _string_split(char* text, char* separator, bool(*condition)(char*, int));

char *string_repeat(char character, int count) {
    char *text = calloc(count + 1, 1);
    int i = 0;
    for (i = 0; i < count; ++i) {
        text[i] = character;
    }
    return text;
}

char *string_duplicate(char *original) {
    return strdup(original);
}

void string_append(char **original, char *string_to_add) {
    *original = realloc(*original, strlen(*original) + strlen(string_to_add) + 1);
    strcat(*original, string_to_add);
}

char *string_new() {
    return string_duplicate("");
}

bool string_contains(char *text, char *substring) {
    return strstr(text, substring) != NULL;
}

void string_capitalize(char *text) {
    if (strlen(text) != 0) {
        _string_upper_element(text);
        if (strlen(text) >= 2) {
            string_to_lower(&text[1]);
        }
    }
}

void string_to_lower(char *text) {
    _string_do(text, &_string_lower_element);
}


/** PRIVATE FUNCTIONS **/

static void _string_upper_element(char *ch) {
    *ch = toupper(*ch);
}

static void _string_lower_element(char *ch) {
    *ch = tolower(*ch);
}

static void _string_do(char *text, void (*closure)(char *c)) {
    int i = 0;
    while (text[i] != '\0') {
        closure(&text[i]);
        i++;
    }
}

char* getString(char* origen, int size) {
    char* str = (char*) malloc(size + 1);
    memcpy(str, origen, size);
    str[size] = '\0';
    return str;
}

void freeSplit(char** split) {
    int i;
    for(i = 0; split[i] != NULL; i++){
        free(split[i]);
    }

    free(split[i]); //libero el espacio que tiene NULL
    free(split);
}


char **string_split(char *text, char *separator) {
    bool _is_last_token(char* next, int _) {
        return next[0] != '\0';
    }
    return _string_split(text, separator, _is_last_token);
}


char** _string_split(char* text, char* separator, bool(*condition)(char*, int)) {
    char **substrings = NULL;
    int size = 0;

    char *text_to_iterate = string_duplicate(text);

    char *next = text_to_iterate;
    char *str = text_to_iterate;

    while(condition(next, size)) {
        char* token = strtok_r(str, separator, &next);
        if(token == NULL) {
            break;
        }
        str = NULL;
        size++;
        substrings = realloc(substrings, sizeof(char*) * size);
        substrings[size - 1] = string_duplicate(token);
    };

    if (next[0] != '\0') {
        size++;
        substrings = realloc(substrings, sizeof(char*) * size);
        substrings[size - 1] = string_duplicate(next);
    }

    size++;
    substrings = realloc(substrings, sizeof(char*) * size);
    substrings[size - 1] = NULL;

    free(text_to_iterate);
    return substrings;
}