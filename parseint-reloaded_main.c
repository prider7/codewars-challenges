/*
4 kyu
parseInt() reloaded
https://www.codewars.com/kata/525c7c5ab6aecef16e0001a5
*/

#include <stdio.h>

long parse_int(const char* number);

void do_test(const char* number, long expected) {
  long result = parse_int(number);
  printf("While parsing '%s', expected %ld, got %ld, %s\n", number, expected,
         result, (expected == result ? "OK" : "ERROR"));
}

int main(void) {
  do_test("zero", 0);
  do_test("one", 1);
  do_test("twenty", 20);
  do_test("one hundred", 100);
  do_test("two hundred and forty-six", 246);
  do_test("one thousand", 1000);
  do_test("one thousand one hundred and eleven", 1111);
  do_test("one hundred eleven thousand one hundred eleven", 111111);
  do_test("one hundred fifteen thousand one hundred twelve", 115112);
  do_test("nine hundred ninety-nine thousand nine hundred and ninety-nine",
          999999);
  do_test("one million", 1000000);
  return 0;
}