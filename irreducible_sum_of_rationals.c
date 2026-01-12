/*
6 kyu
Irreducible Sum of Rationals
https://www.codewars.com/kata/5517fcb0236c8826940003c9
*/

#include <stdlib.h>

typedef struct Rational {
  int numerator, denominator;
} Rational;

static int greatest_common_divisor(int m, int n);
static int least_common_multiple(int m, int n);
static int rational_sgn(Rational rational);
static Rational rational_abs(Rational rational);
Rational rational_create(int numerator, int denominator);
Rational rational_simplify(Rational rational);
Rational rational_add(Rational a, Rational b);

int* sumFracts(const int lst[][2], unsigned length);

static int greatest_common_divisor(int m, int n) {
  while (m > 0) {
    int tmp = n % m;
    n = m;
    m = tmp;
  }
  return n;
}

static int least_common_multiple(int m, int n) {
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

Rational rational_simplify(Rational rational) {
  int sign = rational_sgn(rational);
  Rational abs = rational_abs(rational);
  int div = greatest_common_divisor(abs.numerator, abs.denominator);
  return (Rational){sign * abs.numerator / div, abs.denominator / div};
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

int* sumFracts(const int lst[][2], unsigned length) {
  int* result = calloc(2, sizeof(int));
  result[1] = 1;
  if (lst != NULL && length > 0) {
    Rational a = rational_create(lst[0][0], lst[0][1]);
    a = rational_simplify(a);
    for (unsigned i = 1; i < length; i++) {
      Rational b = rational_create(lst[i][0], lst[i][1]);
      a = rational_add(a, b);
      a = rational_simplify(a);
    }
    result[0] = a.numerator;
    result[1] = a.denominator;
  }
  return result;
}
