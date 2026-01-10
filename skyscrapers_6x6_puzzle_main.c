/*
2 kyu
6 By 6 Skyscrapers
https://www.codewars.com/kata/5679d5a3f2272011d700000d
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int** SolvePuzzle(int* clues);

static int clues[][24] = {
    {3, 2, 2, 3, 2, 1, 1, 2, 3, 3, 2, 2, 5, 1, 2, 2, 4, 3, 3, 2, 1, 2, 2, 4},
    {0, 0, 0, 2, 2, 0, 0, 0, 0, 6, 3, 0, 0, 4, 0, 0, 0, 0, 4, 4, 0, 3, 0, 0}};

int outcomes[][6][6] = {{{2, 1, 4, 3, 5, 6},
                         {1, 6, 3, 2, 4, 5},
                         {4, 3, 6, 5, 1, 2},
                         {6, 5, 2, 1, 3, 4},
                         {5, 4, 1, 6, 2, 3},
                         {3, 2, 5, 4, 6, 1}},
                        {{5, 6, 1, 4, 3, 2},
                         {4, 1, 3, 2, 6, 5},
                         {2, 3, 6, 1, 5, 4},
                         {6, 5, 4, 3, 2, 1},
                         {1, 2, 5, 6, 4, 3},
                         {3, 4, 2, 5, 1, 6}}};

static void do_test(int testno, int clues[24], int expected[6][6]) {
  int** puzzle = SolvePuzzle(clues);
  int count = 0;
  for (int i = 0; i < 6; i++) {
    if (memcmp(puzzle[i], expected[i], 6 * sizeof(int)))
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
