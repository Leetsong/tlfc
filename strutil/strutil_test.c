#include "strutil.h"
#include <assert.h>

int main() {
  char* s = " \t\nyou have to learn Chinese, Math, English well\n";
  char* l = "you have to learn Chinese, Math, English well\n";
  char* r = " \t\nyou have to learn Chinese, Math, English well";
  char* a = "you have to learn Chinese, Math, English well";
  char* b = "Chinese, Math, English,, ,Physics,";
  char c[11] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '\0' };
  char* d = "12\n";

  assert(-1 == stridx(s, NULL));
  assert(-1 == stridx(NULL, NULL));
  assert(-1 == stridx(NULL, ""));
  assert(-1 == stridx(s, "1"));
  assert(-1 == stridx(s, "123"));
  // printf("learn: %d\n", stridx(s, "learn"));
  assert(15 == stridx(s, "learn"));
  assert(30 == stridx(s, "Math"));
  assert(0 == stridx(s, " "));
  assert(1 == stridx(s, "\t\n"));
  assert(-1 == stridx(s, "Well"));
  assert(-1 == stridx(s, "Well\n"));
  assert(44 == stridx(s, "well"));
  assert(44 == stridx(s, "well\n"));

  char* dup_s  = strdup(s);
  char* dup_a  = strdup(a);
  char* dup_sl = strdup(s);
  char* dup_sr = strdup(s);
  assert(strcmp(s, dup_s) == 0);
  assert(strcmp(a, dup_a) == 0);

  char* ndup_s = strndup(s, 7);
  char* ndup_a = strndup(a, 7);
  assert(strncmp(s, ndup_s, 7) == 0);
  assert(strncmp(a, ndup_a, 7) == 0);

  char* rpt_d1 = strrpt(d, 1);
  assert(strcmp(rpt_d1, "12\n") == 0);
  char* rpt_d2 = strrpt(d, 2);
  assert(strcmp(rpt_d2, "12\n12\n") == 0);
  char* rpt_d5 = strrpt(d, 5);
  assert(strcmp(rpt_d5, "12\n12\n12\n12\n12\n") == 0);

  assert(strsts("123", "1234") == 0);
  assert(strsts("123", "1") == 1);
  assert(strsts("123", "12") == 1);
  assert(strsts("123", "123") == 1);
  assert(strsts("123", "234") == 0);
  assert(strsts(s, "\t\n") == 0);
  assert(strsts(s, " \t\n") == 1);

  assert(streds("123", "1234") == 0);
  assert(streds("123", "3") == 1);
  assert(streds("123", "23") == 1);
  assert(streds("123", "123") == 1);
  assert(streds("123", "234") == 0);
  assert(streds(s, "\t\n") == 0);
  assert(streds(s, "\n") == 1);
  assert(streds(s, "well\n") == 1);

  strtrim(dup_s);
  assert(strcmp(dup_s, a) == 0);

  strtrim(dup_a);
  assert(strcmp(dup_a, a) == 0);

  strtriml(dup_sl);
  assert(strcmp(dup_sl, l) == 0);

  strtrimr(dup_sr);
  assert(strcmp(dup_sr, r) == 0);

  strrvs(c);
  assert(strcmp(c, "9876543210") == 0);

  assert(strsplit(NULL, "x") == NULL);

  char** tokens_ax = strsplit(a, "x");
  char*  joined_ax = strjoin(tokens_ax, "x");
  assert(strcmp(tokens_ax[0], a) == 0);
  assert(tokens_ax[1] == NULL);
  assert(strcmp(joined_ax, a) == 0);

  char** tokens_a = strsplit(a, ",");
  char*  joined_a = strjoin(tokens_a, ",");
  assert(strcmp(tokens_a[0], "you have to learn Chinese") == 0);
  assert(strcmp(tokens_a[1], " Math") == 0);
  assert(strcmp(tokens_a[2], " English well") == 0);
  assert(tokens_a[3] == NULL);
  assert(strcmp(joined_a, a) == 0);

  char** tokens_b = strsplit(b, ", ");
  assert(strcmp(tokens_b[0], "Chinese") == 0);
  assert(strcmp(tokens_b[1], "Math") == 0);
  assert(strcmp(tokens_b[2], "English") == 0);
  assert(strcmp(tokens_b[3], "Physics") == 0);
  assert(tokens_b[4] == NULL);

  size_t n_tokens_nax;
  char** tokens_nax = strnsplit(a, "x", &n_tokens_nax);
  char*  joined_nax = strnjoin(tokens_nax, n_tokens_nax, "x");
  assert(n_tokens_nax == 1);
  assert(strcmp(tokens_nax[0], a) == 0);
  assert(strcmp(joined_nax, a) == 0);

  size_t n_tokens_na;
  char** tokens_na = strnsplit(a, ",", &n_tokens_na);
  char*  joined_na = strnjoin(tokens_na, n_tokens_na, ",");
  assert(n_tokens_na == 3);
  assert(strcmp(tokens_na[0], "you have to learn Chinese") == 0);
  assert(strcmp(tokens_na[1], " Math") == 0);
  assert(strcmp(tokens_na[2], " English well") == 0);
  assert(strcmp(joined_na, a) == 0);

  size_t n_tokens_nb;
  char** tokens_nb = strnsplit(b, ", ", &n_tokens_nb);
  assert(n_tokens_nb == 4);
  assert(strcmp(tokens_nb[0], "Chinese") == 0);
  assert(strcmp(tokens_nb[1], "Math") == 0);
  assert(strcmp(tokens_nb[2], "English") == 0);
  assert(strcmp(tokens_nb[3], "Physics") == 0);

  for (int i = 0; tokens_ax[i]; i ++) { free(tokens_ax[i]); }
  for (int i = 0; tokens_a[i]; i ++) { free(tokens_a[i]); }
  for (int i = 0; tokens_b[i]; i ++) { free(tokens_b[i]); }
  for (int i = 0; i < n_tokens_nax; i ++) { free(tokens_nax[i]); }
  for (int i = 0; i < n_tokens_na; i ++) { free(tokens_na[i]); }
  for (int i = 0; i < n_tokens_nb; i ++) { free(tokens_nb[i]); }

  free(dup_s);      free(dup_a);
  free(dup_sl);     free(dup_sr);
  free(ndup_s);     free(ndup_a);
  free(rpt_d1);     free(rpt_d2);    free(rpt_d5);
  free(tokens_ax);  free(tokens_a);  free(tokens_b);
  free(joined_ax);  free(joined_a);
  free(tokens_nax); free(tokens_na); free(tokens_nb);
  free(joined_nax); free(joined_na);

  return 0;
}