/*
3 kyu
Divide integers as strings
https://www.codewars.com/kata/58dea43ff98a7e2124000169
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** divide_strings(char* a, char* b);

static void do_test(char* a, char* b, char* exp_q, char* exp_r) {
  char** actual = divide_strings(a, b);
  printf("Divide %s / %s\n", a, b);
  printf("Quotient  expected: %s / actual: %s / %s\n", exp_q, *actual,
         strcmp(exp_q, *actual) == 0 ? "OK" : "ERROR");
  printf("Remainder expected: %s / actual: %s / %s\n\n", exp_r, *(actual + 1),
         strcmp(exp_r, *(actual + 1)) == 0 ? "OK" : "ERROR");
  free(*actual);
  free(*(actual + 1));
  free(actual);
}

int main(void) {
  do_test("0", "5", "0", "0");
  do_test("1", "0", "0", "0");
  do_test("5", "5", "1", "0");
  do_test("27", "555", "0", "27");
  do_test("4", "5", "0", "4");
  do_test("10", "2", "5", "0");
  do_test("20", "3", "6", "2");
  do_test("60", "5", "12", "0");
  do_test("219", "11", "19", "10");
  do_test("729", "9", "81", "0");
  do_test("1000", "10", "100", "0");
  do_test("600001", "100", "6000", "1");
  do_test("11107135725677065448", "489719917", "22680588107", "405838329");
  do_test("111071357256770654482830238975", "489719917898394834343434",
          "226805", "431277825214079567690605");
  do_test(
      "184790733561196925308873515484315984060536656440200009552010764454852016"
      "791567587789654057143789196699289535283253138865592960091851879945473991"
      "40648414335967175603604070",
      "329835921963528214944714296793796971483802154107692065694383654242412992"
      "3207307111306010595140414048",
      "5602504798783871102678704536871710996691923057347664340484182355083454",
      "280950917494734174107103604538232463103186179535217794398201314393645261"
      "204046796978324604449642278");
  return 0;
}
