/*
6 kyu
Run-length encoding
https://www.codewars.com/kata/546dba39fa8da224e8000467
*/

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  unsigned count;
  unsigned char value;
} Character;

Character* run_length_encoding(const char* string, size_t* length_out) {
  *length_out = 0;
  Character* result = NULL;
  size_t len = strlen(string);
  if (len > 0) {
    result = calloc(strlen(string), sizeof(Character));
    const char* p = string;
    size_t rindex;
    unsigned char lastc = '\0';
    while (*p) {
      if (*p != lastc) {
        (*length_out)++;
        rindex = *length_out - 1;
        result[rindex].count = 1;
        result[rindex].value = *p;
        lastc = *p;
      } else {
        result[rindex].count += 1;
      }
      p++;
    }
  }
  return result;
}
