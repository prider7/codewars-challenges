/*
4 kyu
Range Extraction
https://www.codewars.com/kata/51ba717bb08c1cd60f00002f
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void numstrcat(char* dest, const int n, const char* add) {
  char buf[15];
  sprintf(buf, "%d", n);
  strcat(dest, buf);
  if (add[0])
    strcat(dest, add);
}

char* range_extraction(const int* args, size_t n) {
  char* result = (char*)calloc((n + 1) * 12, sizeof(char));
  int* diffs = (int*)calloc(n - 1, sizeof(int));
  for (size_t i = 0; i < n - 1; i++)
    diffs[i] = args[i + 1] - args[i];
  size_t pos = 0;
  while (pos < (n - 1)) {
    while (pos < (n - 1) && diffs[pos] > 1) {
      numstrcat(result, args[pos], ",");
      pos++;
    }
    size_t count = 0;
    while (pos < (n - 1) && diffs[pos] == 1) {
      count++;
      if (count == 1)
        numstrcat(result, args[pos], "");
      if (count == 2)
        strcat(result, "-");
      pos++;
    }
    if (count == 1)
      strcat(result, ",");
  }
  numstrcat(result, args[n - 1], "");
  free(diffs);
  return result;
}
