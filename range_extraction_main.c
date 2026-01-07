/*
4 kyu
Range Extraction
https://www.codewars.com/kata/51ba717bb08c1cd60f00002f
*/

#include <stdio.h>
#include <stdlib.h>

char* range_extraction(const int* args, size_t n);

static void do_test(const int* args, size_t n, const char* expected) {
  char* actual = range_extraction(args, n);
  printf("input (%lu): [ ", n);
  for (size_t i = 0; i < n; i++) {
    printf("%d ", args[i]);
  }
  printf("]\nexpected: \"%s\"\ngot     : \"%s\"\n\n", expected, actual);
  free(actual);
}

int main(void) {
  do_test((const int[]){-6, -3, -2, -1, 0,  1,  3,  4,  5,  7,
                        8,  9,  10, 11, 14, 15, 17, 18, 19, 20},
          20ul, "-6,-3-1,3-5,7-11,14,15,17-20");
  do_test((const int[]){-3, -2, -1, 2, 10, 15, 16, 18, 19, 20}, 10ul,
          "-3--1,2,10,15,16,18-20");
  do_test((const int[]){-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5}, 11ul, "-5-5");
  do_test((const int[]){-5, -4, -2, -1, 1, 2, 4, 5}, 8ul,
          "-5,-4,-2,-1,1,2,4,5");
  do_test((const int[]){9}, 1ul, "9");
  return 0;
}
