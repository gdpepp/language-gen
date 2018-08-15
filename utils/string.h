//
// Created by utnso on 23/07/18.
//

#ifndef STRING_UTILS_H_
#define STRING_UTILS_H_

#include <stdbool.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdarg.h>

/**
* @NAME: string_new
* @DESC: creates emptystring
*/
char*   string_new();

/**
* @NAME: string_repeat
* @DESC: creates a 'count'-length string with the same char.
*
* string_repeat('a', 5) = "aaaaa"
*
*/
char*   string_repeat(char ch, int count);

/**
* @NAME: string_append
* @DESC: appends the first string to the second
*
* ie:
* char *greet= string_new();
* string_append(&greet, "OH, HI ");
* string_append(&greet, "MARK");
*
* => greet = "OH, HI MARK"
*/
void 	string_append(char ** original, char * string_to_add);


/**
 * @NAME: string_contains
 * @DESC: returns a boolean value indicating
 * the presence of substring in text
 */
bool	string_contains(char* text, char *substring);

/**
	* @NAME: string_capitalize
	* @DESC: Capitalizes a string
	*/
void 	string_capitalize(char * text);

/**
* @NAME: string_to_lower
* @DESC: Pone en minuscula todos los caracteres de un string
*/
void 	string_to_lower(char * text);


#endif /* STRING_UTILS_H_ */
