/*
4 kyu
Number of Proper Fractions with Denominator d
https://www.codewars.com/kata/55b7bb74a0256d4467000070
*/

#include <stdio.h>

typedef unsigned long long bigint;

bigint properFractions(bigint n);

static void doTest(bigint input, bigint expected) {
  bigint actual = properFractions(input);
  printf("For input = %lld, expected %lld, but got %lld -> %s\n", input,
         expected, actual, (expected == actual ? "ok" : "wrong"));
}

int main(void) {
  doTest(1LL, 0LL);
  doTest(2LL, 1LL);
  doTest(3LL, 2LL);
  doTest(5LL, 4LL);
  doTest(6LL, 2LL);
  doTest(10LL, 4LL);
  doTest(12LL, 4LL);
  doTest(15LL, 8LL);
  doTest(30LL, 8LL);
  doTest(60LL, 16LL);
  doTest(25LL, 20LL);
  doTest(9999LL, 6000LL);
  doTest(9999999LL, 6637344LL);
  doTest(3235532013097327LL, 3180815834572800LL);
  return 0;
}
