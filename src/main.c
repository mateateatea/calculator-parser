#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include "calc.h"
#include "parser.h"

int main(){
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif
    float first_number;
    float second_number;
    int choose;
    float result;
    printf("Type first number: \n");
    scanf("%f", &first_number);
    printf("Type second number: \n");
    scanf("%f", &second_number);
    printf("Choose, which operation do you want to use: \n");
    printf("1. Add\n2. Sub\n3. Mul\n4. Div\n5. Parser\n");
    scanf("%d", &choose);
    switch (choose)
    {
    case 1:
        result = add(first_number, second_number);
        printf("Your addition result is: %.2f", result);
        break;
    case 2:
        result = sub(first_number, second_number);
        printf("Your subtracion is: %.2f", result);
        break;
    case 3:
        result = mul(first_number, second_number);
        printf("Your multiplication result is: %.2f", result);
        break;
    case 4:
        if (second_number == 0){
            printf("You cant divide by 0! ");
            return 1;
        }else{
            result = divide(first_number, second_number);
            printf("Your division result is: %.2f", result);
        }
        break;
    case 5:
        result = parser();
        printf("%.2f", result);
        break;
    default:
        break;
    }
#ifndef _WIN32
    printf("\n");
#endif
    return 0;
}