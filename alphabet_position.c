/*
6 kyu
Replace With Alphabet Position
https://www.codewars.com/kata/546f922b54af40e1e90001da
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* alphabet_position(const char* text) {
  char* result = calloc(strlen(text) * 3 + 1, sizeof(char));
  unsigned int num;
  char buf[3];
  const char* p = text;
  while (*p) {
    if (isalpha(*p)) {
      if (isupper(*p))
        num = *p - 'A' + 1;
      else
        num = *p - 'a' + 1;
      sprintf(buf, "%u ", num);
      strcat(result, buf);
    }
    p++;
  }
  unsigned int lresult = strlen(result);
  if (lresult > 1)
    if (result[lresult - 1] == ' ')
      result[lresult - 1] = '\0';
  return result;
}
