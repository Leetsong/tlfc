#include "strutil.h"

/**
 * strdup duplicates a string from s
 * @param  s string you want to be duplicated
 * @return   a duplicate of s, remember to free it
 */
char* strdup(const char* s) {
  if (NULL == s) { return NULL; }
  size_t l = strlen(s);
  char *ds = (char*)malloc((l + 1) * sizeof(char));
  strcpy(ds, s); ds[l] = '\0';
  return ds;
}

/**
 * strndup duplicates a first n characters from s
 * @param  s string you want to be duplicated
 * @param  n number of characters you want to be duplicated
 * @return   a duplicate of s, remember to free it
 */
char* strndup(const char* s, size_t n) {
  if (NULL == s) { return NULL; }
  char* ds = (char*)malloc((n + 1) * sizeof(char));
  strncpy(ds, s, n); ds[n] = '\0';
  return ds;
}

/**
 * strrpt returns a string who repeats s for n times
 * @param  s string you want to be repeated
 * @param  n times to repeat
 * @return   a repeated string of s, remember to free it
 */
char* strrpt(const char* s, int n) {
  if (NULL == s) { return NULL; }
  size_t ls = strlen(s), lrs = n * ls;
  char* rs = (char*)malloc((lrs + 1) * sizeof(char));
  for (int i = 0; i < n; i ++) { memcpy(rs + i * ls, s, ls); }
  rs[lrs] = '\0';
  return rs;
}

/**
 * strsts checks whether s starts with ss
 * @param  s  string
 * @param  ss starts to be checked
 * @return    1 if true else 0
 */
int strsts(const char* s, const char* ss) {
  if (NULL == s || NULL == ss) { return 0; }
  size_t ls = strlen(s), lss = strlen(ss);
  return ls < lss ? 0 : ((strncmp(s, ss, lss) == 0) ? 1 : 0);
}

/**
 * streds checks whether s ends with ss
 * @param  s  string
 * @param  ss ends to be checked
 * @return    1 if true else 0
 */
int streds(const char* s, const char* ss) {
  if (NULL == s || NULL == ss) { return 0; }
  size_t ls = strlen(s), lss = strlen(ss);
  return ls < lss ? 0 : (strncmp(s + ls - lss, ss, lss) == 0 ? 1 : 0);
}

/**
 * strtriml trims left spaces of a string, using isspace(defined in ctype.h)
 * @param  s string to be trimed left, s will be rewritten to trimed s
 * @return   trimed string
 */
char* strtriml(char* s) {
  if (NULL == s) { return NULL; }

  int ls = strlen(s), st = 0;
  int cnt = 0;

  while (st < ls && isspace(s[st])) { st ++; }
  
  cnt = ls - st;
  if (cnt == ls) { /* do nothing */ }
  else if (cnt > 0) { memmove(s, s + st, cnt); s[cnt] = '\0'; }
  else { s[0] = '\0'; }

  return s;
}

/**
 * strtrim trims right spaces of a string, using isspace(defined in ctype.h)
 * @param  s string to be trimed rignt, s will be rewritten to trimed s
 * @return   trimed string
 */
char* strtrimr(char* s) {
  if (NULL == s) { return NULL; }

  int ls = strlen(s), ed = ls - 1;
  int cnt = 0;

  while (ed >= 0 && isspace(s[ed])) { ed --; }
  
  cnt = ed + 1;
  if (cnt == ls) { /* do nothing */ }
  else { s[cnt] = '\0'; }

  return s;
}

/**
 * strtrim trims spaces of a string, using isspace(defined in ctype.h)
 * @param  s string to be trimed, s will be rewritten to trimed s
 * @return   trimed string
 */
char* strtrim(char* s) {
  if (NULL == s) { return NULL; }

  int isspace_st, isspace_ed;
  int ls = strlen(s), st = 0, ed = ls - 1;
  int cnt = 0;

  while (st <= ed) {
    isspace_st = isspace(s[st]);
    isspace_ed = isspace(s[ed]);
    if(!isspace_st && !isspace_ed) { break; }
    if(isspace_st) { st ++; }
    if(isspace_ed) { ed --; }
  }
  
  cnt = (ed - st + 1);
  if (cnt == ls) { /* do nothing */ }
  else if (cnt > 0) { memmove(s, s + st, cnt); s[cnt] = '\0'; }
  else { s[0] = '\0'; }

  return s;
}

/**
 * strrvs revers a string
 * @param  s string to be reversed
 * @return   0 if succeeded else -1
 */
int strrvs(char* s) {
  if (NULL == s) { return -1; }
  if (s[0] == '\0' || s[1] == '\0') { return 1; }

  int h = 0, t = strlen(s) - 1, tmp;
  while (h < t) { tmp = s[h]; s[h] = s[t]; s[t] = tmp; h ++; t --; }

  return 1;
}

/**
 * strsplit splits a string according to characters in delim
 * @param  s     string to be split
 * @param  delim split character set
 * @return       tokens after splitting, terminated by NULL, 
 *               remember to free them all one by one
 */
char** strsplit(const char* s, const char* delim) {
  if(NULL == s) { return NULL; }

  char **tokens;

  if (NULL == delim) {
    tokens = (char**)malloc(2 * sizeof(char*));
    tokens[0] = strdup(s);
    tokens[1] = NULL;
    return tokens;
  }

  char *ss, *nxtp, *p;
  size_t size = 0;

  p = ss = strdup(s);
  nxtp = strtok(ss, delim);
  while (nxtp) { size += 1; nxtp = strtok(NULL, delim); }

  // we use size(at most) to allocate memories
  tokens = (char**)malloc((size + 1) * sizeof(char*));
  memset(tokens, 0, (size + 1) * sizeof(char*));

  for (int i = 0; i < size; ) {
    // this is a workaround to solve the bug generated by strtok
    // e.g. split "123,,456" by comma "," will return ["123", ",456"]
    p += strspn(p, delim);
    if (p && *p) {
      tokens[i] = strdup(p);
      p += (strlen(p) + 1);
      i ++;
    } else {
      p = p + 1; // strtok only considers one character
    }
  }

  free(ss);

  return tokens;
}

/**
 * strnsplit splits a string according to characters in delim
 * @param  s     string to be split
 * @param  delim split character set
 * @param  n     size number of tokens
 * @return       tokens after splitting, n pointed out size of tokens, 
 *               remember to free them all one by one
 */
char** strnsplit(const char* s, const char* delim, size_t *n) {
  if(NULL == s) { *n = 0; return NULL; }

  char **tokens;

  if (NULL == delim) {
    tokens = (char**)malloc(1 * sizeof(char*));
    tokens[0] = strdup(s); *n = 1;
    return tokens;
  }

  char *ss, *nxtp, *p;
  size_t size = 0;

  p = ss = strdup(s);
  nxtp = strtok(ss, delim);
  while (nxtp) { size += 1; nxtp = strtok(NULL, delim); }

  // we use size(at most) to allocate memories
  tokens = (char**) malloc(size * sizeof(char*));
  memset(tokens, 0, size * sizeof(char*));
  *n = 0;

  for (int i = 0; i < size; ) {
    // this is trick to solve the bug generated by strtok
    // e.g. split "123,,456" by comma "," will return ["123", ",456"]
    p += strspn(p, delim);
    if (p && *p) {
      tokens[i] = strdup(p);
      p += (strlen(p) + 1);
      (*n) ++; i ++;
    } else {
      p = p + 1; // strtok only considers one character
    }
  }

  free(ss);

  return tokens;
}

/**
 * strjoin joins all strings in tokens using delim
 * @param  tokens strings to be joined, terminated by NULL
 * @param  delim  delimeter used
 * @return        a joined string, remember to free it
 */
char* strjoin(char** tokens, const char* delim) {
  if (NULL == tokens || NULL == tokens[0]) { return NULL; }
  if (NULL == tokens[1]) { return strdup(tokens[0]); }
  if (NULL == delim) { delim = ""; }

  size_t ld = strlen(delim), len = 0, sz = 0;
  size_t *tokens_len = NULL;
  char *joined_s = NULL;

  for (int i = 0; tokens[i]; i ++) { sz ++; }
  tokens_len = (size_t*)malloc(sz * sizeof(size_t));
  len = ld * (sz - 1);

  for (int i = 0; i < sz; i ++) { len += (tokens_len[i] = strlen(tokens[i])); }
  joined_s = (char*)malloc((len + 1) * sizeof(char));

  int offset = 0;
  for (int i = 0; i < sz - 1; i ++) {
    strcpy(joined_s + offset, tokens[i]);
    offset += tokens_len[i];
    strcpy(joined_s + offset, delim);
    offset += ld;
  }

  strcpy(joined_s + offset, tokens[sz - 1]);
  joined_s[len] = '\0';

  free(tokens_len);

  return joined_s;
}

/**
 * strnjoin joins all strings in tokens using delim
 * @param  tokens strings to be joined, n points out its size
 * @param  n      size of tokens
 * @param  delim  delimeter used
 * @return        a joined string, remember to free it
 */
char* strnjoin(char** tokens, size_t n, const char* delim) {
  if (NULL == tokens || 0 == n) { return NULL; }
  if (1 == n) { return strdup(tokens[0]); }
  if (NULL == delim) { delim = ""; }

  size_t ld = strlen(delim), len = ld * (n - 1);
  size_t *tokens_len = NULL;
  char *joined_s = NULL;

  tokens_len = (size_t*)malloc(n * sizeof(size_t));
  for (int i = 0; i < n; i ++) { len += (tokens_len[i] = strlen(tokens[i])); }
  joined_s = (char*)malloc((len + 1) * sizeof(char));

  int offset = 0;
  for (int i = 0; i < n - 1; i ++) {
    strcpy(joined_s + offset, tokens[i]);
    offset += tokens_len[i];
    strcpy(joined_s + offset, delim);
    offset += ld;
  }

  strcpy(joined_s + offset, tokens[n - 1]);
  joined_s[len] = '\0';

  free(tokens_len);

  return joined_s;
}

/**
 * stridx finds the first occurring index of p in t. It is implemented via KMP.
 * @param  t the main string
 * @param  p the pattern string
 * @return   the first occurring index of p in t, or -1
 */
int stridx(const char* t, const char* p) {
  if (NULL == t || NULL == p) { return -1; }

  const int lp = (const int)strlen(p);
  const int lt = (const int)strlen(t);
  if (lp > lt) {
    return -1;
  } else if (lp == lt) {
    return strncmp(p, t, lp) == 0 ? 0 : -1;
  }

  // define a next array, size of p
  int* next = (int*)malloc(lp * sizeof(int));
  if (NULL == next) {
    return -2;
  }

  // fill the next array
  int k = -1;
  int i, j = 0;
  next[j] = k;
  while (j < lp) {
    if (k == -1 || p[j] == p[k]) {
      if (p[++ j] == p[++ k]) {
        next[j] = next[k];
      } else {
        next[j] = k;
      }
    } else {
      k = next[k];
    }
  }

  // find the first index
  i = j = 0;
  while (i < lt && j < lp) {
    if (j == -1 || t[i] == p[j]) {
      i ++; j ++;
    } else {
      j = next[j];
    }
  }

  // free next
  free(next);

  if (j == lp) {
    // find it
    return i - j;
  } else {
    return -1;
  }
}