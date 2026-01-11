/*
4 kyu
Adding Big Numbers
https://www.codewars.com/kata/525f4206b73515bffb000b21
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* add(const char* a, const char* b);

static void do_test(const char* a, const char* b, const char* expected) {
  char* actual = add(a, b);
  printf("a = \"%s\"\nb = \"%s\"\na + b = \"%s\"\ngot   = \"%s\"\n%s\n-----\n",
         a, b, expected, actual,
         strcmp(expected, actual) == 0 ? "ok" : "error");
  free(actual);
}

int main(void) {
  do_test("1", "1", "2");
  do_test("123", "456", "579");  // 123 + 456 == 579
  do_test("888", "222", "1110");
  do_test("1372", "69", "1441");
  do_test("12", "456", "468");
  do_test("101", "100", "201");
  do_test("63829983432984289347293874", "90938498237058927340892374089",
          "91002328220491911630239667963");
  return 0;
}
