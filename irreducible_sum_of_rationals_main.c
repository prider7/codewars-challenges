/*
6 kyu
Irreducible Sum of Rationals
https://www.codewars.com/kata/5517fcb0236c8826940003c9
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* sumFracts(const int lst[][2], unsigned length);

static void printRationals(size_t length, const int rationals[length][2]) {
  printf("{ ");
  for (size_t i = 0; i < length; i++) {
    printf("{%d, %d}%s", rationals[i][0], rationals[i][1],
           (i == length - 1) ? "" : ", ");
  }
  printf(" }");
}

static void do_test(size_t length,
                    const int rationals[length][2],
                    const int expected[2]) {
  const size_t mem_size = 2 * sizeof *expected;
  int* actual = sumFracts(rationals, length);
  printf("input = ");
  printRationals(length, rationals);
  printf("\n");
  printf("expected {%d, %d} but got {%d, %d}\n%s\n\n", expected[0], expected[1],
         actual[0], actual[1],
         memcmp(actual, expected, mem_size) == 0 ? "ok" : "not ok");
  free(actual);
}

int main(void) {
  {
    int data[2][2] = {{1, 2}, {1, 3}};
    do_test(2, data, (int[2]){5, 6});
  }
  {
    int data[5][2] = {{1, 2}, {2, 9}, {3, 18}, {4, 24}, {6, 48}};
    do_test(5, data, (int[2]){85, 72});
  }
  {
    int data[3][2] = {{1, 2}, {1, 3}, {1, 4}};
    do_test(3, data, (int[2]){13, 12});
  }
  {
    int data[2][2] = {{1, 3}, {5, 3}};
    do_test(2, data, (int[2]){2, 1});
  }
  {
    int(*data)[2] = NULL;
    do_test(0, data, (int[2]){0, 1});
  }
}
