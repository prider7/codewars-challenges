/*
2 kyu
6 By 6 Skyscrapers
https://www.codewars.com/kata/5679d5a3f2272011d700000d
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 6
#define CLUESIZE 24
#define SOLUTIONSIZE 720
#define MAXITER 10 * CLUESIZE
#define INITSTRING "123456"
#define DIGITS \
  { 1, 2, 3, 4, 5, 6 }
#define DEBUG 0

static int clues_rows_index[CLUESIZE][SIZE][2];
static int solutions[SOLUTIONSIZE][SIZE + 1];
static char result[SIZE][SIZE][SIZE + 1];
static int solution_counter = 0;

static int max_of_n(const int arr[], int n);
static int viewcount(const int arr[], int n);
static void swap(int* a, int* b);
static void permute(int arr[], int start, int end);
static void init_data(void);
static void do_row(const int cluerow, const int clue);
static int solution_found(void);
static void print_matrix(const int cluerow, const int iter);
static void print_init_data(void);

int** SolvePuzzle(int* clues);

static int max_of_n(const int arr[], int n) {
  int max = arr[0];
  for (int i = 1; i < n; i++) {
    if (arr[i] > max)
      max = arr[i];
  }
  return max;
}

static int viewcount(const int arr[], int n) {
  int c = 1;
  for (int i = 1; i < n; i++)
    if (arr[i] > max_of_n(arr, i))
      c++;
  return c;
}

static void swap(int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

static void permute(int arr[], int start, int end) {
  if (start == end) {
    for (int i = 0; i <= end; i++) {
      solutions[solution_counter][i] = arr[i];
    }
    solutions[solution_counter][end + 1] =
        viewcount(solutions[solution_counter], end + 1);
    solution_counter++;
    return;
  }
  for (int i = start; i <= end; i++) {
    swap(&arr[start], &arr[i]);
    permute(arr, start + 1, end);
    swap(&arr[start], &arr[i]);
  }
}

static void init_data(void) {
  int k = 2 * SIZE;
  for (int j = 0; j < SIZE; j++) {
    for (int i = 0; i < SIZE; i++) {
      clues_rows_index[j][i][0] = i;
      clues_rows_index[j][i][1] = j;
      clues_rows_index[j + k][i][0] = SIZE - i - 1;
      clues_rows_index[j + k][i][1] = SIZE - j - 1;
    }
  }
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      clues_rows_index[i + SIZE][j][0] = i;
      clues_rows_index[i + SIZE][j][1] = SIZE - j - 1;
      clues_rows_index[i + SIZE + k][j][0] = SIZE - i - 1;
      clues_rows_index[i + SIZE + k][j][1] = j;
    }
  }
  int digits[] = DIGITS;
  solution_counter = 0;
  permute(digits, 0, SIZE - 1);
}

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

static void print_init_data(void) {
  for (int i = 0; i < CLUESIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      printf("clues_rows_index[%d][%d][0..1] = %d %d\n", i, j,
             clues_rows_index[i][j][0], clues_rows_index[i][j][1]);
    }
  }
  for (int i = 0; i < SOLUTIONSIZE; i++) {
    printf("solutions[%d][0..%d] = ", i, SIZE);
    for (int j = 0; j <= SIZE; j++) {
      printf("%d ", solutions[i][j]);
    }
    printf("\n");
  }
}

int** SolvePuzzle(int* clues) {
  init_data();
  if (DEBUG)
    print_init_data();
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
