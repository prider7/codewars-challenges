/*
4 kyu
parseInt() reloaded
https://www.codewars.com/kata/525c7c5ab6aecef16e0001a5
*/

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define TR_COUNT 31
#define DEBUG false

typedef struct {
  long value;
  char* name;
  size_t length;
  long factor;
} translation_t;

translation_t translations[TR_COUNT] = {
    {0, "zero", 4, 1},         {1, "one", 3, 1},       {2, "two", 3, 1},
    {3, "three", 5, 1},        {4, "four", 4, 1},      {5, "five", 4, 1},
    {6, "six", 3, 1},          {7, "seven", 5, 1},     {8, "eight", 5, 1},
    {9, "nine", 4, 1},         {10, "ten", 3, 1},      {11, "eleven", 6, 1},
    {12, "twelve", 6, 1},      {13, "thirteen", 8, 1}, {14, "fourteen", 8, 1},
    {15, "fifteen", 7, 1},     {16, "sixteen", 7, 1},  {17, "seventeen", 9, 1},
    {18, "eighteen", 8, 1},    {19, "nineteen", 8, 1}, {20, "twenty", 6, 1},
    {30, "thirty", 6, 1},      {40, "forty", 5, 1},    {50, "fifty", 5, 1},
    {60, "sixty", 5, 1},       {70, "seventy", 7, 1},  {80, "eighty", 6, 1},
    {90, "ninety", 6, 1},      {100, "hundred", 7, 1}, {0, "thousand", 8, 1000},
    {0, "million", 7, 1000000}};

long parse_int(const char* number) {
  long curr_factor = 1;
  bool hundred_corr = false;
  long result = 0;
  const char* pstart = number + strlen(number) - 1;
  const char* pend = pstart;
  while (pstart >= number) {
    while (pstart >= number && !isalpha(*pstart))
      pstart--;
    pend = pstart;
    while (pstart >= number && isalpha(*pstart))
      pstart--;
    pstart++;
    size_t len = pend - pstart + 1;
    if (DEBUG)
      printf("%.*s = ", (int)len, pstart);
    for (size_t i = 0; i < TR_COUNT; i++) {
      if (translations[i].length == len) {
        if (strncmp(pstart, translations[i].name, len) == 0) {
          if (translations[i].factor > curr_factor)
            curr_factor = translations[i].factor;
          if (hundred_corr && translations[i].value >= 1 &&
              translations[i].value < 10)
            result = result + (translations[i].value - 1) * 100 * curr_factor;
          else
            result = result + translations[i].value * curr_factor;
          hundred_corr = translations[i].value == 100;
          break;
        }
      }
    }
    pstart--;
    if (DEBUG)
      printf("%ld\n", result);
  }
  return result;
}
