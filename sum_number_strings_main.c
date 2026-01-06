/*
4 kyu
Sum Strings as Numbers
https://www.codewars.com/kata/5324945e2ece5e1f32000370
*/

#include <stdio.h>
#include <stdlib.h>

char* strsum(const char* a, const char* b);

static void do_test(const char* s1, const char* s2, const char* expected) {
  char* actual = strsum(s1, s2);
  printf("input was:\n\"%s\"\n\"%s\"\nexpected: \"%s\"\ngot     : \"%s\"\n\n",
         s1, s2, expected, actual);
  free(actual);
}

int main(void) {
  do_test("123", "456", "579");
  do_test("00001", "9", "10");
  do_test("00000", "0", "0");
  do_test("", "0090", "90");
  do_test("00007", "", "7");
  do_test("", "", "");
  do_test("12345678901234567890", "87654321098765432109",
          "99999999999999999999");
  do_test("12345678901234567891", "87654321098765432109",
          "100000000000000000000");
  return 0;
}
