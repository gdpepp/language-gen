//
// Created by utnso on 23/07/18.
//

#include "string.h"

char *string_repeat(char character, int count) {
	char *text = calloc(count + 1, 1);
	int i = 0;
	for (i = 0; i < count; ++i) {
		text[i] = character;
	}
	return text;
}

char* string_duplicate(char* original) {
	return strdup(original);
}

void string_append(char** original, char* string_to_add) {
	*original = realloc(*original, strlen(*original) + strlen(string_to_add) + 1);
	strcat(*original, string_to_add);
}

char* string_new() {
	return string_duplicate("");
}

bool	string_contains(char* text, char *substring) {
	return strstr(text, substring) != NULL;
}

void string_capitalize(char *text) {
	if (strlen(text) != 0) {
		_string_upper_element(text);
		if (strlen(text) >= 2){
			string_to_lower(&text[1]);
		}
	}
}

void string_to_lower(char *text) {
	_string_do(text, &_string_lower_element);
}


/** PRIVATE FUNCTIONS **/

static void _string_upper_element(char* ch) {
	*ch = toupper(*ch);
}

static void _string_lower_element(char* ch) {
	*ch = tolower(*ch);
}

static void _string_do(char *text, void (*closure)(char* c)){
	int i = 0;
	while (text[i] != '\0') {
		closure(&text[i]);
		i++;
	}
}
