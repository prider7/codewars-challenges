/*
5 kyu
Rational Arithmetic
https://www.codewars.com/kata/5260074c9a0022f83e0009da
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Rational {
  int numerator, denominator;
} Rational;

static int greatest_common_divisor(int m, int n);
static int least_common_multiple(int m, int n);
static int rational_sgn(Rational rational);
static Rational rational_abs(Rational rational);
Rational rational_create(int numerator, int denominator);
char* rational_to_string(Rational rational);
Rational rational_simplify(Rational rational);
bool rational_equal(Rational a, Rational b);
bool rational_less_than(Rational a, Rational b);
bool rational_less_than_or_equal(Rational a, Rational b);
bool rational_greater_than(Rational a, Rational b);
bool rational_greater_than_or_equal(Rational a, Rational b);
Rational rational_add(Rational a, Rational b);
Rational rational_sub(Rational a, Rational b);
Rational rational_mul(Rational a, Rational b);
Rational rational_div(Rational a, Rational b);

static int greatest_common_divisor(int m, int n) {
  /* The greatest common divisor g is the largest natural number that divides
   * both a and b without leaving a remainder. */
  while (m > 0) {
    int tmp = n % m;
    n = m;
    m = tmp;
  }
  return n;
}

static int least_common_multiple(int m, int n) {
  /* When adding, subtracting, or comparing simple fractions,
   * the least common multiple of the denominators (often called the lowest
   * common denominator) is used, because each of the fractions can be expressed
   * as a fraction with this denominator.  */
  int x = m / greatest_common_divisor(m, n);
  return n * x;
}

static int rational_sgn(Rational rational) {
  int n = 1;
  int d = 1;
  if (rational.numerator < 0)
    n = -1;
  if (rational.denominator < 0)
    d = -1;
  return n * d * (rational.numerator == 0 ? 0 : 1);
}

static Rational rational_abs(Rational rational) {
  int n = rational.numerator;
  if (n < 0)
    n = -n;
  int d = rational.denominator;
  if (d < 0)
    d = -d;
  return (Rational){n, d};
}

Rational rational_create(int numerator, int denominator) {
  return (Rational){numerator, denominator};
}

char* rational_to_string(Rational rational) {
  char* result = calloc(30, sizeof(char));
  sprintf(result, "%d / %d", rational.numerator, rational.denominator);
  return result;
}

Rational rational_simplify(Rational rational) {
  int sign = rational_sgn(rational);
  Rational abs = rational_abs(rational);
  int div = greatest_common_divisor(abs.numerator, abs.denominator);
  return (Rational){sign * abs.numerator / div, abs.denominator / div};
}

bool rational_equal(Rational a, Rational b) {
  return rational_sgn(rational_sub(a, b)) == 0;
}

bool rational_less_than(Rational a, Rational b) {
  return rational_sgn(rational_sub(a, b)) < 0;
}

bool rational_less_than_or_equal(Rational a, Rational b) {
  return rational_sgn(rational_sub(a, b)) <= 0;
}

bool rational_greater_than(Rational a, Rational b) {
  return rational_sgn(rational_sub(a, b)) > 0;
}

bool rational_greater_than_or_equal(Rational a, Rational b) {
  return rational_sgn(rational_sub(a, b)) >= 0;
}

Rational rational_add(Rational a, Rational b) {
  int sign_a = rational_sgn(a);
  Rational abs_a = rational_abs(a);
  int sign_b = rational_sgn(b);
  Rational abs_b = rational_abs(b);
  int lcm = least_common_multiple(abs_a.denominator, abs_b.denominator);
  int fa = lcm / abs_a.denominator;
  int fb = lcm / abs_b.denominator;
  return (Rational){
      sign_a * fa * abs_a.numerator + sign_b * fb * abs_b.numerator, lcm};
}

Rational rational_sub(Rational a, Rational b) {
  return rational_add(a, (Rational){-b.numerator, b.denominator});
}

Rational rational_mul(Rational a, Rational b) {
  return (Rational){a.numerator * b.numerator, a.denominator * b.denominator};
}

Rational rational_div(Rational a, Rational b) {
  return (Rational){a.numerator * b.denominator, a.denominator * b.numerator};
}
