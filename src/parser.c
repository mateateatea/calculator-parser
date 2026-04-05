#include <stdio.h>
#include <stdlib.h>
#include "calc.h"
#include "parser.h"

float parser(){
    char expression[100];
    while(getchar() != '\n');
    printf("Enter your expression: \n");
    fgets(expression,100,stdin);
    const char *pos = expression;
    float result = parser_additive(&pos);
    printf("Wynik: %.2f\n", result);
    return 0;    
}

void skip_spaces(const char **pos){
    while (**pos == ' '){
        (*pos)++;
    }
}

float parser_number(const char **pos){
    skip_spaces(pos);
    float number = strtof(*pos, (char **)pos);
    return number;
}

float parser_multiplicative(const char **pos){
    float result_mul =  parser_number(pos);
    skip_spaces(pos);
    while (**pos == '*' || **pos == '/'){
        char operator = **pos;
        (*pos)++;
        float next_number = parser_number(pos);
        if (operator == '*'){
            result_mul = result_mul * next_number;
        }else{
            result_mul = result_mul / next_number;
        }
    }
    return result_mul;
}

float parser_additive(const char **pos){
    float result_add = parser_multiplicative(pos);
    skip_spaces(pos);
    while (**pos == '+' || **pos == '-'){
        char operator = **pos;
        (*pos)++;
        float next_number = parser_multiplicative(pos);
        if (operator == '+'){
            result_add = result_add + next_number;
        }else{
            result_add = result_add - next_number;
        }
    }
    return result_add;
}