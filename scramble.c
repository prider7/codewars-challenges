/*
5 kyu
Scramblies
https://www.codewars.com/kata/55c04b4cc56a697bb0000048
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static char* xstrdup(const char* s) {
  size_t len = strlen(s) + 1;
  char* p = malloc(len);
  if (p)
    memcpy(p, s, len);
  return p;
}

bool scramble(const char* str1, const char* str2) {
  char* cstr1 = xstrdup(str1);
  unsigned int l_str2 = strlen(str2);
  bool result = true;
  for (unsigned int i = 0; i < l_str2; i++) {
    char* found = strchr(cstr1, str2[i]);
    if (found == NULL) {
      result = false;
      break;
    }
    *found = '.';
  }
  free(cstr1);
  return result;
}
