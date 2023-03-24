#include "s21_SmartCalc.h"

int convert_to_struct(const char *input, double x_value, elements *parser_input,
                      int *size) {
  int count = 0, len = strlen(input), err = 0;
  for (int i = 0; i < len; i++) {
    if (input[i] != ' ') {
      if (i == 0 && input[0] == '+') i++;
      if (i == 0 && input[0] == '-') {
        input_unary(parser_input, &count);
        parser_input = parser_input + count;
        i++;
      }
      if (input[i] == 'x') {
        convert_x(x_value, &i, parser_input);
        parser_input++;
        count++;
      }
      if (input[i] >= '0' && input[i] <= '9') {
        convert_digit(&i, input, parser_input, &err);
        parser_input++;
        count++;
      }
      if (err == 0) {
        if (input[i] == '+' || input[i] == '-' || input[i] == '/' ||
            input[i] == '*' || input[i] == '^') {
          convert_sign(i, input, parser_input);
          count++;
        }
        if (input[i] == 'm' || input[i] == 's' || input[i] == 'c' ||
            input[i] == 's' || input[i] == 't' || input[i] == 'a' ||
            input[i] == 'l') {
          i = convert_word(i, input, parser_input, &err);
          count++;
        }
        if (input[i] == ')' || input[i] == '(') {
          convert_brackets(i, input, parser_input);
          count++;
          if ((input[i] == '(') && (input[i + 1] == '-')) {
            i++;
            convert_brackets_u(&parser_input);
            count = count + 2;
          }
          if ((input[i] == '(') && (input[i + 1] == '+')) i++;
        }
      }
    }
    parser_input++;
  }
  *size = count;
  return err;
}
void convert_x(double x_value, int *i, elements *parser_input) {
  parser_input->type = 1;
  parser_input->value = x_value;
  (*i)++;
}
void convert_digit(int *i, const char *input, elements *parser_input,
                   int *err) {
  int control = 0;
  char *start_digit = (char *)input + *i;
  parser_input->type = 1;
  while (input[*i] >= '0' && input[*i] <= '9') {
    (*i)++;
    if (input[*i] == '.') {
      (*i)++;
      control++;
    }
  }
  if (control <= 1) {
    double res = 0.0;
    sscanf(start_digit, "%lf", &res);
    parser_input->value = res;
  } else {
    *err = 1;
  }
}
void convert_sign(int i, const char *input, elements *parser_input) {
  if (input[i] == '+' || input[i] == '-') {
    parser_input->type = 2;
    parser_input->priority = 1;
    parser_input->operation[0] = input[i];
  } else if (input[i] == '/' || input[i] == '*') {
    parser_input->type = 2;
    parser_input->priority = 2;
    parser_input->operation[0] = input[i];
  } else if (input[i] == '^') {
    parser_input->type = 2;
    parser_input->priority = 3;
    parser_input->operation[0] = input[i];
  }
}
int convert_word(int i, const char *input, elements *parser_input, int *err) {
  if (input[i] == 'm' && input[i + 1] == 'o' && input[i + 2] == 'd') {
    parser_input->type = 2;
    parser_input->priority = 2;
    parser_input->operation[0] = 'm';
    parser_input->operation[1] = 'o';
    parser_input->operation[2] = 'd';
    i = i + 2;
  } else if (input[i] == 's' && input[i + 1] == 'q' && input[i + 2] == 'r' &&
             input[i + 3] == 't') {
    parser_input->type = 3;
    parser_input->priority = 3;
    parser_input->operation[0] = 's';
    parser_input->operation[1] = 'q';
    parser_input->operation[2] = 'r';
    parser_input->operation[3] = 't';
    i = i + 3;
  } else if (input[i] == 'c' && input[i + 1] == 'o' && input[i + 2] == 's') {
    parser_input->type = 3;
    parser_input->priority = 3;
    parser_input->operation[0] = 'c';
    parser_input->operation[1] = 'o';
    parser_input->operation[2] = 's';
    i = i + 2;
  } else if (input[i] == 's' && input[i + 1] == 'i' && input[i + 2] == 'n') {
    parser_input->type = 3;
    parser_input->priority = 3;
    parser_input->operation[0] = 's';
    parser_input->operation[1] = 'i';
    parser_input->operation[2] = 'n';
    i = i + 2;
  } else if (input[i] == 't' && input[i + 1] == 'a' && input[i + 2] == 'n') {
    parser_input->type = 3;
    parser_input->priority = 3;
    parser_input->operation[0] = 't';
    parser_input->operation[1] = 'a';
    parser_input->operation[2] = 'n';
    i = i + 2;
  } else if (input[i] == 'a') {
    parser_input->type = 3;
    parser_input->priority = 3;
    parser_input->operation[0] = 'a';
    if (input[i + 1] == 'c' && input[i + 2] == 'o' && input[i + 3] == 's') {
      parser_input->operation[1] = 'c';
      parser_input->operation[2] = 'o';
      parser_input->operation[3] = 's';
    } else if (input[i + 1] == 's' && input[i + 2] == 'i' &&
               input[i + 3] == 'n') {
      parser_input->operation[1] = 's';
      parser_input->operation[2] = 'i';
      parser_input->operation[3] = 'n';
    } else if (input[i + 1] == 't' && input[i + 2] == 'a' &&
               input[i + 3] == 'n') {
      parser_input->operation[1] = 't';
      parser_input->operation[2] = 'a';
      parser_input->operation[3] = 'n';
    }
    i = i + 3;
  } else if (input[i] == 'l') {
    parser_input->type = 3;
    parser_input->priority = 3;
    parser_input->operation[0] = 'l';
    if (input[i + 1] == 'o' && input[i + 2] == 'g') {
      parser_input->operation[1] = 'o';
      parser_input->operation[2] = 'g';
      i = i + 2;
    } else if (input[i + 1] == 'n') {
      parser_input->operation[1] = 'n';
      i++;
    }
  } else {
    *err = 1;
  }
  return i;
}
void convert_brackets(int i, const char *input, elements *parser_input) {
  parser_input->type = 4;
  parser_input->priority = 0;
  parser_input->operation[0] = input[i];
}
void convert_brackets_u(elements **parser_input) {
  (*parser_input)++;
  (*parser_input)->type = 1;
  (*parser_input)->value = -1.0;

  (*parser_input)++;
  (*parser_input)->type = 2;
  (*parser_input)->priority = 2;
  (*parser_input)->operation[0] = '*';
}
void sort_station(elements *parser_input, elements *parser_output, int *size) {
  int count_out = *size, size_in = *size, count_in = 0, i = 0;
  elements stack_tmp[MAX_STACK] = {0};
  elements *stack_ptr = stack_tmp;
  while (count_in++ < *size) {
    if (parser_input->type == 1) {
      fill_struct(parser_output, parser_input);
      parser_output++;
    }
    if (parser_input->type == 2 || parser_input->type == 3) {
      while (i > 0) {
        stack_ptr--;
        if (parser_input->priority <= stack_ptr->priority) {
          fill_struct(parser_output, stack_ptr);
          parser_output++;
          i--;
        } else {
          stack_ptr++;
          break;
        }
      }
      fill_struct(stack_ptr, parser_input);
      stack_ptr++;
      i++;
    }
    if (parser_input->type == 4) {
      sort_brackets(parser_input, &parser_output, &stack_ptr, &i, &count_out);
    }
    parser_input++;
  }
  while (i > 0) {
    stack_ptr--;
    fill_struct(parser_output, stack_ptr);
    parser_output++;
    i--;
  }
  *size = count_out;
  free_struct(parser_input - size_in, size_in);
}
void sort_brackets(elements *parser_input, elements **parser_output,
                   elements **stack_ptr, int *i, int *count_out) {
  if (parser_input->operation[0] == '(') {
    (*count_out)--;
    fill_struct(*stack_ptr, parser_input);
    (*stack_ptr)++;
    (*i)++;
  }
  if (parser_input->operation[0] == ')') {
    (*count_out)--;
    while (*i > 0) {
      (*stack_ptr)--;
      if ((*stack_ptr)->operation[0] == '(') {
        (*i)--;
        break;
      } else {
        fill_struct(*parser_output, *stack_ptr);
        (*parser_output)++;
        (*i)--;
      }
    }
  }
}
void fill_struct(elements *fill, elements *in) {
  fill->type = in->type;
  fill->operation[0] = in->operation[0];
  fill->operation[1] = in->operation[1];
  fill->operation[2] = in->operation[2];
  fill->operation[3] = in->operation[3];
  fill->operation[4] = in->operation[4];
  fill->priority = in->priority;
  fill->value = in->value;
}
void free_struct(elements *elements, int size) {
  for (int k = 0; k < size; k++) {
    elements[k].type = 0;
    elements[k].priority = 0;
    elements[k].operation[0] = '\0';
    elements[k].operation[1] = '\0';
    elements[k].operation[2] = '\0';
    elements[k].operation[3] = '\0';
    elements[k].operation[4] = '\0';
    elements[k].value = 0;
  }
}
void input_unary(elements *parser_input, int *count) {
  parser_input->type = 1;
  parser_input->value = -1.0;
  (*count)++;

  parser_input++;
  parser_input->type = 2;
  parser_input->priority = 2;
  parser_input->operation[0] = '*';
  (*count)++;
}
