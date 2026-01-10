/*
4 kyu
4 By 4 Skyscrapers
https://www.codewars.com/kata/5671d975d81d6c1c87000022
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int** SolvePuzzle(int* clues);

static int clues[][16] = {{2, 2, 1, 3, 2, 2, 3, 1, 1, 2, 2, 3, 3, 2, 1, 3},
                          {0, 0, 1, 2, 0, 2, 0, 0, 0, 3, 0, 0, 0, 1, 0, 0}};

int outcomes[][4][4] = {
    {{1, 3, 4, 2}, {4, 2, 1, 3}, {3, 4, 2, 1}, {2, 1, 3, 4}},
    {{2, 1, 4, 3}, {3, 4, 1, 2}, {4, 2, 3, 1}, {1, 3, 2, 4}}};

static void do_test(int testno, int clues[16], int expected[4][4]) {
  int** puzzle = SolvePuzzle(clues);
  int count = 0;
  for (int i = 0; i < 4; i++) {
    if (memcmp(puzzle[i], expected[i], 4 * sizeof(int)))
      count++;
    free(puzzle[i]);
  }
  printf("Test #%d ok: %s\n", testno, count ? "false" : "true");
  free(puzzle);
}

int main(void) {
  do_test(1, clues[0], outcomes[0]);
  do_test(2, clues[1], outcomes[1]);
  return 0;
}
