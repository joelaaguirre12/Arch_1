#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
char *word_start(char* str,char delim)
{
	int *pchar;
	int i;
	pchar = &str[0];	
	if(strlen(str) == 0) {
		return 0;
	}
	else {
		while (delim_character(*(pchar+i), delim)) {
			i += 1;
		}
		return *(pchar+i);
	}
}

/* Returns a pointer to the first delimiter character of the zero
   terminated string*/
char *end_word(char* str,char delim)
{

}

/* Counts the number of words or tokens*/
int count_tokens(char* str,char delim)
{

}

/* Returns a freshly allocated new zero-terminated string
   containing <len> chars from <inStr> */
char *copy_str(char *inStr, short len, char delim)
{

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

}

void print_all_tokens(char** tokens)
{

}

int main(void) 
{
	char c = getchar();
	char delim = getchar();
	printf("c = %c, delim = %c, Is c a delimiter? %d\n", c, delim, delim_character(c, delim));
	printf("c = %c, delim = %c, Is c a non-delimiter? %d\n", c, delim, non_delim_character(c, delim));
}
