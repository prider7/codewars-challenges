/*
5 kyu
Human Readable Time
https://www.codewars.com/kata/52685f7382004e774f0001f7
*/

#include <stdio.h>
#include <string.h>

char* human_readable_time(unsigned seconds, char* time_string);

static void do_test(unsigned seconds, const char* expected) {
  char time_string[sizeof "00:00:00"];
  memset(time_string, '@', sizeof time_string);
  char* actual = human_readable_time(seconds, time_string);
  printf("input was:\n\"%u\"\nexpected:\n\"%s\"\ngot:\n\"%s\"\n\n", seconds,
         expected, actual);
}

int main(void) {
  do_test(0, "00:00:00");
  do_test(59, "00:00:59");
  do_test(60, "00:01:00");
  do_test(90, "00:01:30");
  do_test(3599, "00:59:59");
  do_test(3600, "01:00:00");
  do_test(45296, "12:34:56");
  do_test(86399, "23:59:59");
  do_test(86400, "24:00:00");
  do_test(359999, "99:59:59");
  return 0;
}
