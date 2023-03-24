#ifndef s21_SmartCalc_h
#define s21_SmartCalc_h

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "s21_check_input.h"

#define MAX_INPUT 255
#define MAX_STACK 265

typedef struct {
  int type;
  char operation[5];
  int priority;
  double value;
} elements;
/*
type:
1 - число
2 - арифметика + mod  + ^(pow)
3 - sqrt + тригонометрия
4 - скобки
-----------------------------
priority (priority operation):
1 - + -
2 - / * mod
3 - ^ sin cos... log ln
*/
int s21_check_input(const char *s);
void s21_calculator(elements *parser_output, int size, double *result);
int qt_calculator(const char *input, double x_value, double *result);
// help
int convert_to_struct(const char *input, double x_value, elements *result,
                      int *size);
void convert_x(double x_value, int *i, elements *parser_input);
void convert_digit(int *i, const char *input, elements *parser_input, int *err);
void convert_sign(int i, const char *input, elements *parser_input);
int convert_word(int i, const char *input, elements *result, int *err);
void convert_brackets(int i, const char *input, elements *parser_input);
void convert_brackets_u(elements **parser_input);
void sort_station(elements *parser_input, elements *parser_output, int *size);
void sort_brackets(elements *parser_input, elements **parser_output,
                   elements **stack_ptr, int *i, int *count_out);
void fill_struct(elements *fill, elements *in);
void free_struct(elements *elements, int size);
void input_unary(elements *parser_input, int *count);
double calculate(double val1, double val2, char *operation);

#endif /* s21_SmartCalc_h */

/* err
1 на ввод посупили некорректные данные
2 пустые скобки
3 несовпадает кол-во скобок
4 неверная длина выражения
5 деление на 0 или корень отрицательного числа
6 обработка nan, замена на Error
*/
