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

typedef Rational (*ArithOp)(Rational, Rational);
typedef bool (*CmpOp)(Rational, Rational);

static void test_simplify(Rational rational, Rational expected) {
  Rational actual = rational_simplify(rational);
  printf(
      "SIMPLIFY OK = %d -- simplify(%d / %d), expected (%d / %d), got "
      "(%d, %d)\n",
      (actual.numerator == expected.numerator &&
       actual.denominator == expected.denominator),
      rational.numerator, rational.denominator, expected.numerator,
      expected.denominator, actual.numerator, actual.denominator);
}

static void test_fraction(Rational a,
                          ArithOp op,
                          Rational b,
                          Rational expected) {
  char op_char = (op == rational_add)   ? '+'
                 : (op == rational_sub) ? '-'
                 : (op == rational_mul) ? '*'
                 : (op == rational_div) ? '/'
                                        : '?';
  Rational actual = op(a, b);
  double actual_flt = (double)actual.numerator / (double)actual.denominator;
  double expected_flt =
      (double)expected.numerator / (double)expected.denominator;
  printf(
      "OPS OK = %d -- (%d / %d) %c (%d / %d), expected %d / %d (%f), got  "
      "%d / %d (%f)\n",
      ((actual_flt - expected_flt) < 1E-3), a.numerator, a.denominator, op_char,
      b.numerator, b.denominator, expected.numerator, expected.denominator,
      expected_flt, actual.numerator, actual.denominator, actual_flt);
}

static void test_comparison(Rational a, CmpOp cmp, Rational b, bool expected) {
  const char* op_string = (cmp == rational_equal)                   ? "="
                          : (cmp == rational_less_than)             ? "<"
                          : (cmp == rational_less_than_or_equal)    ? "<="
                          : (cmp == rational_greater_than)          ? ">"
                          : (cmp == rational_greater_than_or_equal) ? ">="
                                                                    : "?";
  static const char* const bool2str[2] = {"false", "true"};
  bool actual = cmp(a, b);
  printf("COMPARE OK = %d -- (%d / %d) %s (%d / %d) expected %s, got %s\n",
         actual == expected, a.numerator, a.denominator, op_string, b.numerator,
         b.denominator, bool2str[expected], bool2str[actual]);
}

int main(void) {
  int numerator = -15, denominator = 42;
  Rational rational = rational_create(numerator, denominator);
  const char* expected = "-15 / 42";
  char* actual = rational_to_string(rational);
  printf("Rational to String: %s, expected: %s\n", actual, expected);
  free(actual);
  test_simplify((Rational){1, 3}, (Rational){1, 3});
  test_simplify((Rational){4, 12}, (Rational){1, 3});
  test_simplify((Rational){-4, 12}, (Rational){-1, 3});
  test_simplify((Rational){4, -12}, (Rational){-1, 3});
  test_simplify((Rational){-4, -12}, (Rational){1, 3});
  test_simplify((Rational){0, -42}, (Rational){0, 1});
  test_simplify((Rational){12, 4}, (Rational){3, 1});
  test_simplify((Rational){-12, 4}, (Rational){-3, 1});
  test_simplify((Rational){12, -4}, (Rational){-3, 1});
  test_simplify((Rational){-12, -4}, (Rational){3, 1});
  test_fraction((Rational){2, 3}, rational_add, (Rational){1, 4},
                (Rational){11, 12});
  test_fraction((Rational){-2, 15}, rational_add, (Rational){7, 2},
                (Rational){101, 30});
  test_fraction((Rational){593, -666}, rational_add, (Rational){701, 558},
                (Rational){-135972, -371628});
  test_fraction((Rational){2, 3}, rational_sub, (Rational){1, 4},
                (Rational){5, 12});
  test_fraction((Rational){-2, 15}, rational_sub, (Rational){7, 2},
                (Rational){-109, 30});
  test_fraction((Rational){2, 3}, rational_mul, (Rational){1, 4},
                (Rational){2, 12});
  test_fraction((Rational){-2, 15}, rational_mul, (Rational){7, 2},
                (Rational){-14, 30});
  test_fraction((Rational){2, 3}, rational_div, (Rational){1, 4},
                (Rational){8, 3});
  test_fraction((Rational){-2, 15}, rational_div, (Rational){7, 2},
                (Rational){-4, 105});
  test_comparison((Rational){8, 12}, rational_equal, (Rational){2, 3}, true);
  test_comparison((Rational){-1, 3}, rational_equal, (Rational){1, -3}, true);
  test_comparison((Rational){-1, 3}, rational_equal, (Rational){1, 3}, false);
  test_comparison((Rational){1, 3}, rational_equal, (Rational){1, 3}, true);
  test_comparison((Rational){1, 3}, rational_equal, (Rational){1, 4}, false);
  test_comparison((Rational){8, 12}, rational_less_than, (Rational){2, 3},
                  false);
  test_comparison((Rational){1, 4}, rational_less_than, (Rational){1, 3}, true);
  test_comparison((Rational){10, 11}, rational_less_than, (Rational){9, 10},
                  false);
  test_comparison((Rational){8, 12}, rational_less_than_or_equal,
                  (Rational){2, 3}, true);
  test_comparison((Rational){1, 4}, rational_less_than_or_equal,
                  (Rational){1, 3}, true);
  test_comparison((Rational){10, 11}, rational_less_than_or_equal,
                  (Rational){9, 10}, false);
  test_comparison((Rational){8, 12}, rational_greater_than, (Rational){2, 3},
                  false);
  test_comparison((Rational){1, 4}, rational_greater_than, (Rational){1, 3},
                  false);
  test_comparison((Rational){10, 11}, rational_greater_than, (Rational){9, 10},
                  true);
  test_comparison((Rational){8, 12}, rational_greater_than_or_equal,
                  (Rational){2, 3}, true);
  test_comparison((Rational){1, 4}, rational_greater_than_or_equal,
                  (Rational){1, 3}, false);
  test_comparison((Rational){10, 11}, rational_greater_than_or_equal,
                  (Rational){9, 10}, true);
  return 0;
}
