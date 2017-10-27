#ifndef __STRING_H__
#define __STRING_H__

#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char*  strdup(const char* s);
char*  strndup(const char* s, size_t l);
int    strsts(const char* s, const char* ss);
int    streds(const char* s, const char* ss);
char*  strtrim(char* s);
char** strsplit(const char* s, const char* delim);
char** strnsplit(const char* s, const char* delim, size_t* const n);
char*  strjoin(char** tokens, const char* delim);
char*  strnjoin(char** tokens, size_t n, const char* delim);

#endif