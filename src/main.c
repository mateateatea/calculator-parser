#include <stdio.h>
#include "calc.h"

int main(){
    float first_number;
    float second_number;
    int choose;
    float result;
    printf("Type first number: \n");
    scanf("%f", &first_number);
    printf("Type second number: \n");
    scanf("%f", &second_number);
    printf("Choose, which operation do you want to use: \n");
    printf("1. Add\n 2. Sub\n 3. Mul\n 4. Div\n");
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
            result = div(first_number, second_number);
            printf("Your division result is: %.2f", result);
        }
        break;
    default:
        break;
    }
    return 0;
}