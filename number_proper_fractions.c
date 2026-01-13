/*
4 kyu
Number of Proper Fractions with Denominator d
https://www.codewars.com/kata/55b7bb74a0256d4467000070
*/

#include <math.h>

typedef long long bigint;

/* Euler's totient function, see
 * https://en.wikipedia.org/wiki/Euler%27s_totient_function */

bigint properFractions(bigint n) {
  if (n <= 1LL)
    return 0LL;
  bigint num = n;
  bigint result = n;
  for (bigint p = 2LL; p * p <= num; p++) {
    if (num % p == 0LL) {
      while (num % p == 0LL) {
        num /= p;
      }
      result -= result / p;
    }
  }
  if (num > 1LL)
    result -= result / num;
  return result;
}
