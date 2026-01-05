/*
5 kyu
Human Readable Time
https://www.codewars.com/kata/52685f7382004e774f0001f7
*/

#include <stdio.h>

char* human_readable_time(unsigned seconds, char* time_string) {
  unsigned t[3], rem;
  t[0] = seconds / 3600u;
  rem = seconds % 3600u;
  t[1] = rem / 60u;
  t[2] = rem % 60u;
  sprintf(time_string, "%02u:%02u:%02u", t[0], t[1], t[2]);
  time_string[8] = '\0';
  return time_string;
}
