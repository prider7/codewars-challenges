/*
4 kyu
4 By 4 Skyscrapers
https://www.codewars.com/kata/5671d975d81d6c1c87000022
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 4
#define CLUESIZE 16
#define SOLUTIONSIZE 24
#define MAXITER 10 * CLUESIZE
#define INITSTRING "1234"
#define DEBUG 0

static int clues_rows_index[CLUESIZE][SIZE][2] = {
    {{0, 0}, {1, 0}, {2, 0}, {3, 0}}, {{0, 1}, {1, 1}, {2, 1}, {3, 1}},
    {{0, 2}, {1, 2}, {2, 2}, {3, 2}}, {{0, 3}, {1, 3}, {2, 3}, {3, 3}},
    {{0, 3}, {0, 2}, {0, 1}, {0, 0}}, {{1, 3}, {1, 2}, {1, 1}, {1, 0}},
    {{2, 3}, {2, 2}, {2, 1}, {2, 0}}, {{3, 3}, {3, 2}, {3, 1}, {3, 0}},
    {{3, 3}, {2, 3}, {1, 3}, {0, 3}}, {{3, 2}, {2, 2}, {1, 2}, {0, 2}},
    {{3, 1}, {2, 1}, {1, 1}, {0, 1}}, {{3, 0}, {2, 0}, {1, 0}, {0, 0}},
    {{3, 0}, {3, 1}, {3, 2}, {3, 3}}, {{2, 0}, {2, 1}, {2, 2}, {2, 3}},
    {{1, 0}, {1, 1}, {1, 2}, {1, 3}}, {{0, 0}, {0, 1}, {0, 2}, {0, 3}}};

static int solutions[SOLUTIONSIZE][SIZE + 1] = {
    {1, 2, 3, 4, 4}, {1, 2, 4, 3, 3}, {1, 3, 2, 4, 3}, {1, 3, 4, 2, 3},
    {2, 1, 3, 4, 3}, {2, 3, 1, 4, 3}, {2, 3, 4, 1, 3}, {1, 4, 2, 3, 2},
    {1, 4, 3, 2, 2}, {2, 1, 4, 3, 2}, {2, 4, 1, 3, 2}, {2, 4, 3, 1, 2},
    {3, 1, 2, 4, 2}, {3, 1, 4, 2, 2}, {3, 2, 1, 4, 2}, {3, 2, 4, 1, 2},
    {3, 4, 1, 2, 2}, {3, 4, 2, 1, 2}, {4, 1, 2, 3, 1}, {4, 1, 3, 2, 1},
    {4, 2, 1, 3, 1}, {4, 2, 3, 1, 1}, {4, 3, 1, 2, 1}, {4, 3, 2, 1, 1}};

static char result[SIZE][SIZE][SIZE + 1];

static void do_row(const int cluerow, const int clue) {
  char* rowdata[SIZE];
  int foundcount[SOLUTIONSIZE];
  for (int i = 0; i < SIZE; i++) {
    int row = clues_rows_index[cluerow][i][0];
    int col = clues_rows_index[cluerow][i][1];
    rowdata[i] = &(result[row][col][0]);
  }
  for (int j = 0; j < SOLUTIONSIZE; j++) {
    foundcount[j] = 0;
    for (int i = 0; i < SIZE; i++) {
      if (clue == 0 || (clue > 0 && clue == solutions[j][SIZE])) {
        if (strchr(rowdata[i], (char)(solutions[j][i] + '0')) != NULL)
          foundcount[j]++;
      }
    }
  }
  for (int i = 0; i < SIZE; i++) {
    rowdata[i][0] = '\0';
  }
  for (int j = 0; j < SOLUTIONSIZE; j++) {
    if (foundcount[j] == SIZE) {
      for (int i = 0; i < SIZE; i++) {
        if (strchr(rowdata[i], solutions[j][i] + '0') == NULL) {
          int l = strlen(rowdata[i]);
          rowdata[i][l] = (char)(solutions[j][i] + '0');
          rowdata[i][l + 1] = '\0';
        }
      }
    }
  }
}

static int solution_found(void) {
  int count = 0;
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      if (strlen(result[i][j]) == 1)
        count++;
    }
  }
  return (count == SIZE * SIZE ? 1 : 0);
}

static void print_matrix(const int cluerow, const int iter) {
  printf("Iter. #%d, after doing clue row %d\n", iter, cluerow + 1);
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      printf("%*s ", SIZE, result[i][j]);
    }
    printf("\n");
  }
  printf("----------\n");
}

int** SolvePuzzle(int* clues) {
  int** matrix = malloc(SIZE * sizeof(int*));
  for (int i = 0; i < SIZE; i++)
    matrix[i] = calloc(SIZE, sizeof(int));
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      strcpy(result[i][j], INITSTRING);
    }
  }
  int i = 0, iter = 0;
  while (1) {
    iter++;
    do_row(i, clues[i]);
    if (DEBUG)
      print_matrix(i, iter);
    if (solution_found())
      break;
    i++;
    if (i == CLUESIZE)
      i = 0;
    if (iter > MAXITER)
      break; /* No solution */
  }
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      matrix[i][j] = (int)(result[i][j][0] - '0');
    }
  }
  return matrix;
}
