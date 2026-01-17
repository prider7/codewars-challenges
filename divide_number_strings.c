/*
3 kyu
Divide integers as strings
https://www.codewars.com/kata/58dea43ff98a7e2124000169
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static void remove_trailing_zeros(char* r) {
  char* prlast = r;
  while (*prlast)
    prlast++;
  prlast--;
  char* pr = r;
  while (*pr == '0' && pr < prlast)
    pr++;
  if (r < pr)
    memmove(r, pr, strlen(pr) + 1);
}

static char* subtract(const char* a, const char* b) {
  char* result;
  int la = strlen(a);
  int lb = strlen(b);
  int l = ((la > lb) ? la : lb);
  char* aa = calloc(l + 1, sizeof(char));
  char* bb = calloc(l + 1, sizeof(char));
  for (int i = 0; i < l; i++) {
    aa[i] = '0';
    bb[i] = '0';
  }
  strcpy(aa + l - la, a);
  strcpy(bb + l - lb, b);
  int cmp = strcmp(aa, bb);
  if (cmp == 0) {
    result = calloc(2, sizeof(char));
    strcpy(result, "0");
  } else {
    int lr = l + 1;
    result = calloc(lr + 1, sizeof(char));
    bool neg = false;
    if (cmp < 0) {
      neg = true;
      char* temp = aa;
      aa = bb;
      bb = temp;
    }
    for (int i = 0; i < lr; i++)
      result[i] = '0';
    char* prlast = result + lr - 1;
    char* pr = prlast;
    char* pa = aa + l - 1;
    char* pb = bb + l - 1;
    int carryover = 0;
    while (pa >= aa) {
      int diff = *pa - *pb - carryover;
      if (diff < 0) {
        diff += 10;
        carryover = 1;
      } else
        carryover = 0;
      *pr = diff + '0';
      pa--;
      pb--;
      pr--;
    }
    if (carryover > 0)
      *pr = carryover + '0';
    while (*pr == '0' && pr < prlast)
      pr++;
    if (neg) {
      pr--;
      *pr = '-';
    }
    if (result < pr)
      memmove(result, pr, strlen(pr) + 1);
  }
  free(aa);
  free(bb);
  return result;
}

char** divide_strings(char* a, char* b) {
  int la = strlen(a);
  int lb = strlen(b);
  char** result = malloc(2 * sizeof(char*));
  result[0] = calloc(la + 1, sizeof(char));
  result[1] = calloc(la + 1, sizeof(char));
  result[0][0] = '0';
  result[1][0] = '0';
  if (strcmp(a, "0") == 0 || strcmp(b, "0") == 0)
    return result;
  if (lb > la) {
    strcpy(result[1], a);
    return result;
  }
  if (strcmp(a, b) == 0) {
    result[0][0] = '1';
    return result;
  }
  char* aa = calloc(lb + 2, sizeof(char));
  char* diff;
  int pos = 0;
  strncpy(aa, a, lb);
  for (int i = 0; i < la - lb + 1; i++) {
    int count = 0;
    while (true) {
      diff = subtract(aa, b);
      if (diff[0] == '-') {
        free(diff);
        break;
      }
      count++;
      strcpy(aa, diff);
      free(diff);
    }
    result[0][pos] = count + '0';
    int laa = strlen(aa);
    if (i + lb < la) {
      aa[laa] = a[i + lb];
      aa[laa + 1] = '\0';
    }
    pos++;
  }
  result[0][pos] = '\0';
  strcpy(result[1], aa);
  free(aa);
  remove_trailing_zeros(result[0]);
  remove_trailing_zeros(result[1]);
  return result;
}
