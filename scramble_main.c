/*
5 kyu
Scramblies
https://www.codewars.com/kata/55c04b4cc56a697bb0000048
*/

#include <stdbool.h>
#include <stdio.h>

bool scramble(const char* str1, const char* str2);

static void do_test(const char* s1, const char* s2, bool expected) {
  bool actual = scramble(s1, s2);
  printf("input was: \"%s\" and \"%s\"\nexpected: \"%s\"\ngot     : \"%s\"\n\n",
         s1, s2, expected ? "true" : "false", actual ? "true" : "false");
}

int main(void) {
  do_test("rkqodlw", "world", true);
  do_test("cedewaraaossoqqyt", "codewars", true);
  do_test("katas", "steak", false);
  do_test("scriptjavx", "javascript", false);
  do_test("scriptingjava", "javascript", true);
  do_test("scriptsjava", "javascript", true);
  do_test("javscripts", "javascript", false);
  do_test("aabbcamaomsccdd", "commas", true);
  do_test("commas", "commas", true);
  do_test("sammoc", "commas", true);
  return 0;
}
