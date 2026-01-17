/*
2 kyu
Evaluate mathematical expression
https://www.codewars.com/kata/52a78825cdfc2cfc87000005
*/

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define RPN_DATA_MAX_SIZE 500
#define RPN_EXEC_STACK_SIZE 100
#define RPN_OP_STACK_SIZE 100
#define ERROR_RESULT (NAN)
#define DEBUG false

typedef enum { ERR, VAL, ADD, SUB, MUL, DIV, NEG } RPN_Type;

typedef struct {
  RPN_Type type;
  double value;
} RPN_Entry;

typedef struct {
  RPN_Entry entries[RPN_DATA_MAX_SIZE];
  int count;
} RPN_Entries;

typedef struct {
  char data[RPN_OP_STACK_SIZE];
  int count;
} RPN_Op_Stack;

typedef struct {
  double data[RPN_EXEC_STACK_SIZE];
  int count;
} RPN_Execution_Stack;

static RPN_Entries rpn_entries;
static RPN_Op_Stack rpn_op_stack;
static RPN_Execution_Stack rpn_ex_stack;

static RPN_Type convert_op(char c) {
  switch (c) {
    case '+':
      return ADD;
      break;
    case '-':
      return SUB;
      break;
    case '*':
      return MUL;
      break;
    case '/':
      return DIV;
      break;
    case 'N':
      return NEG;
      break;
  }
  return ERR;
}

static char reconvert_op(RPN_Type c) {
  switch (c) {
    case ADD:
      return '+';
      break;
    case SUB:
      return '-';
      break;
    case MUL:
      return '*';
      break;
    case DIV:
      return '/';
      break;
    case NEG:
      return 'N';
      break;
    case VAL:
      return '#';
      break;
    default:
      return '?';
  }
}

static char lookahead(const char* p) {
  const char* q = p;
  while (*q == ' ')
    q++;
  return *q;
}

static char lookback(const char* p) {
  const char* q = p;
  while (*q == ' ')
    q--;
  return *q;
}

static void print_op_stack(void) {
  if (DEBUG) {
    printf("entries(%d): ", rpn_entries.count);
    for (int i = 0; i < rpn_entries.count; i++) {
      if (rpn_entries.entries[i].type == VAL) {
        printf("%f ", rpn_entries.entries[i].value);
      } else {
        printf("%c ", reconvert_op(rpn_entries.entries[i].type));
      }
    }
    printf(" *** op_stack(%d): ", rpn_op_stack.count);
    for (int i = rpn_op_stack.count - 1; i >= 0; i--) {
      printf("%c ", rpn_op_stack.data[i]);
    }
    printf("\n");
  }
}

double calculate(const char* expression) {
  if (DEBUG)
    printf("Expression: %s\n", expression);
  // Convert expression to RPN into rpn_entries
  // Shunting yard algorithm
  // See: https://en.wikipedia.org/wiki/Shunting_yard_algorithm
  rpn_entries.count = 0;
  rpn_op_stack.count = 0;
  bool nonum = false;
  bool nminus = false;
  const char* p = expression;
  while (*p) {
    // look for number
    if (!nonum) {
      char* end;
      double value = strtod(p, &end);
      if (end > p) {
        rpn_entries.entries[rpn_entries.count].value = value;
        rpn_entries.entries[rpn_entries.count].type = VAL;
        rpn_entries.count++;
        if (DEBUG)
          printf("Number: %f\n", value);
        p = end;
      }
    }
    if (DEBUG && nonum)
      printf("nonum!\n");
    nonum = false;
    while (*p == ' ')
      p++;
    if (*p != '\0') {
      if (DEBUG)
        printf("Oper. : %c\n", *p);
      // look for ops and ()
      switch (*p) {
        case '+':
        case '-':
          while (rpn_op_stack.count > 0 &&
                 rpn_op_stack.data[rpn_op_stack.count - 1] != '(') {
            if (rpn_op_stack.data[rpn_op_stack.count - 1] == '*' ||
                rpn_op_stack.data[rpn_op_stack.count - 1] == '/') {
              char r = lookback(p - 1);
              if ((r == '/' || r == '*') && *p == '-' &&
                  lookahead(p + 1) == '(') {
                if (DEBUG)
                  printf("- should be N\n");
                nminus = true;
                break;
              } else {
                rpn_entries.entries[rpn_entries.count].type =
                    convert_op(rpn_op_stack.data[rpn_op_stack.count - 1]);
                rpn_entries.count++;
                rpn_op_stack.count--;
                print_op_stack();
              }
            } else
              break;
          }
          while (rpn_op_stack.count > 0 &&
                 rpn_op_stack.data[rpn_op_stack.count - 1] != '(') {
            if ((rpn_op_stack.data[rpn_op_stack.count - 1] == '+' ||
                 rpn_op_stack.data[rpn_op_stack.count - 1] == '-')) {
              char r = lookback(p - 1);
              if ((r == '-' || r == '+') && *p == '-' &&
                  lookahead(p + 1) == '(') {
                if (DEBUG)
                  printf("- should be N\n");
                nminus = true;
                break;
              } else {
                rpn_entries.entries[rpn_entries.count].type =
                    convert_op(rpn_op_stack.data[rpn_op_stack.count - 1]);
                rpn_entries.count++;
                rpn_op_stack.count--;
                print_op_stack();
              }
            } else
              break;
          }
          char r = lookback(p - 1);
          if (r == '(' && *p == '-' && lookahead(p + 1) == '(') {
            if (DEBUG)
              printf("- should be N\n");
            nminus = true;
          }
          rpn_op_stack.data[rpn_op_stack.count++] = nminus ? 'N' : *p;
          nminus = false;
          print_op_stack();
          p++;
          break;
        case '*':
        case '/':
          while (rpn_op_stack.count > 0 &&
                 rpn_op_stack.data[rpn_op_stack.count - 1] != '(') {
            if (rpn_op_stack.data[rpn_op_stack.count - 1] == '*' ||
                rpn_op_stack.data[rpn_op_stack.count - 1] == '/') {
              rpn_entries.entries[rpn_entries.count].type =
                  convert_op(rpn_op_stack.data[rpn_op_stack.count - 1]);
              rpn_entries.count++;
              rpn_op_stack.count--;
              print_op_stack();
            } else
              break;
          }
          rpn_op_stack.data[rpn_op_stack.count++] = *p;
          print_op_stack();
          p++;
          break;
        case '(':
          rpn_op_stack.data[rpn_op_stack.count++] = *p;
          print_op_stack();
          p++;
          break;
        case ')':
          while (rpn_op_stack.data[rpn_op_stack.count - 1] != '(') {
            rpn_entries.entries[rpn_entries.count].type =
                convert_op(rpn_op_stack.data[rpn_op_stack.count - 1]);
            rpn_entries.count++;
            rpn_op_stack.count--;
            print_op_stack();
            if (rpn_op_stack.count == 0)
              return ERROR_RESULT;
          }
          if (rpn_op_stack.data[rpn_op_stack.count - 1] != '(')
            return ERROR_RESULT;
          rpn_op_stack.count--;
          p++;
          nonum = true;
          break;
        default:
          return ERROR_RESULT;
      }
    }
  }
  while (rpn_op_stack.count > 0) {
    rpn_entries.entries[rpn_entries.count].type =
        convert_op(rpn_op_stack.data[rpn_op_stack.count - 1]);
    rpn_entries.count++;
    rpn_op_stack.count--;
    print_op_stack();
  }
  if (DEBUG) {
    printf("End of Parsing\n");
  }
  // Execute rpn_entries in rpn_stack in Reverse Polish notation
  // and calculate result
  // See: https://en.wikipedia.org/wiki/Reverse_Polish_notation
  if (DEBUG) {
    for (int i = 0; i < rpn_entries.count; i++) {
      if (rpn_entries.entries[i].type == VAL)
        printf("%d = %c = %f\n", i, reconvert_op(rpn_entries.entries[i].type),
               rpn_entries.entries[i].value);
      else
        printf("%d = %c\n", i, reconvert_op(rpn_entries.entries[i].type));
    }
  }
  rpn_ex_stack.count = 0;
  for (int i = 0; i < rpn_entries.count; i++) {
    switch (rpn_entries.entries[i].type) {
      case VAL:
        if (rpn_ex_stack.count + 1 >= RPN_EXEC_STACK_SIZE)
          return ERROR_RESULT;
        rpn_ex_stack.data[rpn_ex_stack.count++] = rpn_entries.entries[i].value;
        break;
      case ADD:
        if (rpn_ex_stack.count < 1)
          return ERROR_RESULT;
        rpn_ex_stack.data[rpn_ex_stack.count - 2] +=
            rpn_ex_stack.data[rpn_ex_stack.count - 1];
        rpn_ex_stack.count--;
        break;
      case SUB:
        if (rpn_ex_stack.count < 1)
          return ERROR_RESULT;
        rpn_ex_stack.data[rpn_ex_stack.count - 2] -=
            rpn_ex_stack.data[rpn_ex_stack.count - 1];
        rpn_ex_stack.count--;
        break;
      case MUL:
        if (rpn_ex_stack.count < 1)
          return ERROR_RESULT;
        rpn_ex_stack.data[rpn_ex_stack.count - 2] *=
            rpn_ex_stack.data[rpn_ex_stack.count - 1];
        rpn_ex_stack.count--;
        break;
      case DIV:
        if (rpn_ex_stack.count < 1)
          return ERROR_RESULT;
        if (rpn_ex_stack.data[rpn_ex_stack.count - 1] == 0.0)
          return ERROR_RESULT;
        rpn_ex_stack.data[rpn_ex_stack.count - 2] /=
            rpn_ex_stack.data[rpn_ex_stack.count - 1];
        rpn_ex_stack.count--;
        break;
      case NEG:
        rpn_ex_stack.data[rpn_ex_stack.count - 1] =
            -rpn_ex_stack.data[rpn_ex_stack.count - 1];
        break;
      case ERR:
        return ERROR_RESULT;
    }
  }
  if (DEBUG)
    printf("Stack Count @ end = %d = %s\n%s\n", rpn_ex_stack.count,
           rpn_ex_stack.count == 1 ? "OK" : "ERROR", expression);
  return rpn_ex_stack.data[0];
}
