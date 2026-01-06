/*
6 kyu
Replace With Alphabet Position
https://www.codewars.com/kata/546f922b54af40e1e90001da
*/

#include <stdio.h>
#include <stdlib.h>

char* alphabet_position(const char* text);

static void do_test(const char* str, const char* expected) {
  char* actual = alphabet_position(str);
  printf("input was: \"%s\"\nexpected: \"%s\"\ngot     : \"%s\"\n", str,
         expected, actual);
  free(actual);
}

int main(void) {
  do_test("The sunset sets at twelve o' clock.",
          "20 8 5 19 21 14 19 5 20 19 5 20 19 1 20 20 23 5 12 22 5 15 3 12 15 "
          "3 11");
  do_test("The narwhal bacons at midnight.",
          "20 8 5 14 1 18 23 8 1 12 2 1 3 15 14 19 1 20 13 9 4 14 9 7 8 20");
  do_test("0", "");
  do_test("123456789", "");
  do_test("12345A6789", "1");
  do_test("   ...a...   ", "1");
  return 0;
}
