/*
6 kyu
Sentence Calculator
https://www.codewars.com/kata/5970fce80ed776b94000008b
*/

#include <stdio.h>

int letters_to_numbers(const char* str);

static void do_test(const char* str, const int expected) {
  int actual = letters_to_numbers(str);
  printf("input was: \"%s\", expected: %d, got: %d\n", str, expected, actual);
}

int main(void) {
  do_test("I Love You", 170);
  do_test("ILoveYou", 170);
  do_test("ARE YOU HUNGRY?", 356);
  do_test("oops, i did it again!", 152);
  do_test("Give me 5!", 73);
  do_test("Give me five!", 110);
  return 0;
}
