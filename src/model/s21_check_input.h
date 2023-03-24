#ifndef s21_check_input_h
#define s21_check_input_h

#include "s21_SmartCalc.h"

void check_input_start(const char *s, int *err);
void check_input_arithmetic(const char *s, int *err, int i);
void check_input_brackets(const char *s, int *err, int i);
void sum_brackets(int *err, int open, int close);
void check_correct(const char *s, int *err, int *open, int *close, int *i);

#endif /* s21_check_input_h */
