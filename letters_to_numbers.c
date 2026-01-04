/*
6 kyu
Sentence Calculator
https://www.codewars.com/kata/5970fce80ed776b94000008b
*/

#include <ctype.h>

int letters_to_numbers(const char* str) {
  const char* p = str;
  int result = 0;
  while (*p) {
    if (isdigit(*p))
      result += ((int)*p - '0');
    else if (isalpha(*p)) {
      if (isupper(*p))
        result += ((int)*p - 'A' + 1) * 2;
      else
        result += ((int)*p - 'a' + 1);
    }
    p++;
  }
  return result;
}
