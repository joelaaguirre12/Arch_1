#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* Return true (non-zero) if c is the delimiter character
   previously chosen by the user.
   Zero terminators are not printable (therefore false) */
bool delim_character(char c, char delim)
{
	if(c == '\0' || c != delim) {
		/* If c is null-terminator or is not delim, return false */
		return false;
	}
	else {
		/* Otherwise c is not a null-terminator and is the delim */
		return true;
	}
}

/* Return true (non-zero) if c is a non-delimiter
   character.
   Zero terminators are not printable (therefore false) */
bool non_delim_character(char c, char delim)
{
	if(c == '\0' || c == delim) {
		/* If c is the null-terminator or is the delim */
		return false;
	}
	else {
		/* Otherwise c is not a null-terminator and is not the delim */
		return true;
	}
}

/* Returns a pointer to the first character of the next
   word starting with a non-delimiter character. Return a zero pointer if
   str does not contain any words.*/
char *word_start(char *str, char delim)
{
	char *pchar;
	pchar = str;
	// if string is empty, return 0
	if(strlen(str) == 0) {
		return 0;
	}
	else {
		// printf("Before increment: *pchar = '%c' pchar = %d\n", *pchar, pchar);
		while (delim_character(*pchar, delim)) {
			// printf("'%c' is not a delim, continuing loop...\n", *pchar);
			pchar++;
			// printf("Address: %d\n", pchar);
			// printf("After increment: *pchar = '%c' pchar = %d\n", *pchar, pchar);
		}
		return pchar;
	}
}

/* Returns a pointer to the first delimiter character of the zero
   terminated string*/
char *end_word(char *str,char delim)
{
	char *pchar;
	pchar = str;
	if(strlen(str) == 0) {
		return 0;
	}
	else {
		// printf("Before increment: *pchar = '%c' pchar = %d\n", *pchar, pchar);
		while (non_delim_character(*pchar, delim)) {
			// printf("'%c' is not a delim, continuing loop...\n", *pchar);
			pchar++;
			// printf("Address: %d\n", pchar);
			// printf("After increment: *pchar = '%c' pchar = %d\n", *pchar, pchar);
		}
		return pchar;
	}
}

/* Counts the number of words or tokens*/
int count_tokens(char* str,char delim)
{
	int num_tok = 0;
	char *pchar;
	pchar = str;
	if (strlen(str) == 0) {
		return num_tok;
	}
	else {
		while (*pchar != '\0') {
			if (delim_character(*pchar, delim)) {
				num_tok++;
			}
			pchar++;
		}
		num_tok++;
		return num_tok;
	}
}

/* Returns a freshly allocated new zero-terminated string
   containing <len> chars from <inStr> */
char *copy_str(char *inStr, short len, char delim)
{
	/* if user is asking for a string longer than the original string's length, return the length of the string */
	if (len > strlen(inStr)) {
		len = strlen(inStr);
	}
	char* string = (char*) malloc(len * sizeof(char));
	char *pchar;
	pchar = inStr;
	int i;	
	if (len == 0) {
		return '\0';
	}
	else {
		for (i = 0; i < len; i++) {
			string[i] = *pchar;
			//printf("String: %c *pchar: %c\n", string[i], *pchar);
			pchar++;	
		}
		string[i] = '\0';
		return string;
	}
}

/* Returns a freshly allocated zero-terminated vector of freshly allocated
   delimiter-separated tokens from zero-terminated str.
   For example, tokenize("hello world string"), with a character delimiter
   of a space " " would result in:
     tokens[0] = "hello"
     tokens[1] = "world"
     tokens[2] = "string"
     tokens[3] = 0
*/
char** tokenize(char* str, char delim)
{
	int length = count_tokens(str, delim);
	int i;
	char start;
	char end;
	char** tokens = (char**) malloc((strlen(str) * sizeof(char)));
	char *start = word_start(str, delim);
	char *end = end_word(str, delim);
	for (i = 0; i < length; i++) {
		int wordLength = end-start;
		tokens[i] = copy_str(str, wordLength, delim);
		printf("Token %d: %s\n", i, tokens[i]);
		*start = word_start(*end, delim);
		*end = end_word(*start, delim);
	}
	tokens[i] = '\0';
	return tokens;
}

void print_all_tokens(char** tokens, int size)
{	
	int i;
	for (i = 0; i < size+1; i++) {
		printf("Token %d: %s\n", i, tokens[i]);
	}
}

int main(void) 
{
	char input[] = "Hello,World,Joel,not";
	char *pinput = input;
	char deli = ',';

	printf("Input: %s\n", input);
	char *x = word_start(pinput, deli);
	printf("The first letter is: %c\n", *x);
	x = end_word(pinput, deli);
	printf("The delimiter is: %c\n", *x);
	int totToks = count_tokens(pinput, deli);
	printf("Number of tokens: %d\n", totToks);
	printf("Tokenizing...\n");
	char** tokens = tokenize(pinput, deli);
	printf("Printing tokens...\n");
	print_all_tokens(tokens, totToks);
	return 0;
}
