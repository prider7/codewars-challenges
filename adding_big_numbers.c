/*
4 kyu
Adding Big Numbers
https://www.codewars.com/kata/525f4206b73515bffb000b21
*/

#include <stdlib.h>
#include <string.h>

char* add(const char* a, const char* b) {
  unsigned la = strlen(a), lb = strlen(b);
  unsigned l = ((la > lb) ? la : lb) + 1;
  char* result = calloc(l + 1, sizeof(char));
  char* prlast;
  char* pr;
  if (la == 0 || lb == 0) {
    if (la)
      strcpy(result, a);
    else
      strcpy(result, b);
    prlast = result + strlen(result) - 1;
    pr = result;
  } else {
    for (unsigned i = 0; i < l; i++)
      result[i] = '0';
    prlast = result + l - 1;
    pr = prlast;
    const char* pa = a + la - 1;
    const char* pb = b + lb - 1;
    unsigned summand1 = 0, summand2 = 0, carryover = 0;
    while ((pa >= a) || (pb >= b)) {
      summand1 = (pa >= a) ? (*pa - '0') : 0;
      summand2 = (pb >= b) ? (*pb - '0') : 0;
      unsigned sum = summand1 + summand2 + carryover;
      carryover = sum / 10;
      sum = sum % 10;
      *pr = sum + '0';
      pa--;
      pb--;
      pr--;
    }
    if (carryover > 0)
      *pr = carryover + '0';
  }
  while (*pr == '0' && pr < prlast)
    pr++;
  if (result < pr)
    memmove(result, pr, strlen(pr) + 1);
  return result;
}
