/*
6 kyu
Run-length encoding
https://www.codewars.com/kata/546dba39fa8da224e8000467
*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct Character {
  unsigned count;
  unsigned char value;
};

struct Character* run_length_encoding(const char* string, size_t* length_out);

static void do_test(const char* string,
                    size_t exp_len,
                    const struct Character expected[exp_len]) {
  size_t act_len = 666;
  struct Character* actual = run_length_encoding(string, &act_len);
  printf("input was:\n\"%s\"\nexp (%ld):\n", string, exp_len);
  for (size_t i = 0; i < exp_len; i++)
    printf("%u=%c ", expected[i].count, expected[i].value);
  printf("\ngot (%ld):\n", act_len);
  for (size_t i = 0; i < act_len; i++)
    printf("%u=%c ", actual[i].count, actual[i].value);
  printf("\n\n");
  free(actual);
}

int main(void) {
  do_test("", 0, NULL);
  do_test("abc", 3, ((struct Character[]){{1, 'a'}, {1, 'b'}, {1, 'c'}}));
  do_test("aab", 2, ((struct Character[]){{2, 'a'}, {1, 'b'}}));
  do_test("hello world!", 11,
          ((struct Character[]){{1, 'h'},
                                {1, 'e'},
                                {2, 'l'},
                                {1, 'o'},
                                {1, ' '},
                                {1, 'w'},
                                {1, 'o'},
                                {1, 'r'},
                                {1, 'l'},
                                {1, 'd'},
                                {1, '!'}}));
  do_test("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbb", 2,
          ((struct Character[]){{34, 'a'}, {3, 'b'}}));
  do_test("WWWWWWWWWWWWBWWWWWWWWWWWWBBBWWWWWWWWWWWWWWWWWWWWWWWWBWWWWWWWWWWWWWW",
          7,
          ((struct Character[]){{12, 'W'},
                                {1, 'B'},
                                {12, 'W'},
                                {3, 'B'},
                                {24, 'W'},
                                {1, 'B'},
                                {14, 'W'}}));
  return 0;
}
