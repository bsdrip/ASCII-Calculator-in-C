#include "stdio.h"
#include "stdlib.h"


typedef struct {
    char num[5][5];
} Number;

const Number zero = {
    " ___ ",
    "|   |",
    "|   |",
    "|   |",
    "|___|"
};
const Number one = {
    "     ",
    "    |",
    "    |",
    "    |",
    "    |"
};
const Number two = {
    " ___ ",
    "    |",
    " ___|",
    "|    ",
    "|___ "
};
const Number three = {
    " ___ ",
    "    |",
    " ___|",
    "    |",
    " ___|"
};
const Number four = {
    "     ",
    "|   |",
    "|___|",
    "    |",
    "    |"
};
const Number five = {
    " ___ ",
    "|    ",
    "|___ ",
    "    |",
    " ___|"
};
const Number six = {
    " ___ ",
    "|    ",
    "|___ ",
    "|   |",
    "|___|"
};
const Number seven = {
    " ___ ",
    "    |",
    "    |",
    "    |",
    "    |"
};
const Number eight = {
    " ___ ",
    "|   |",
    "|___|",
    "|   |",
    "|___|"
};
const Number nine = {
    " ___ ",
    "|   |",
    "|___|",
    "    |",
    " ___|"
};
const Number minus = {
    "     ",
    "     ",
    " ___ ",
    "     ",
    "     "
};

Number get_ascii_for_digit(char digit) {
    switch (digit) {
        case 0:
            return zero;
            break;
        case 1:
            return one;
            break;
        case 2:
            return two;
            break;
        case 3:
            return three;
            break;
        case 4:
            return four;
            break;
        case 5:
            return five;
            break;
        case 6:
            return six;
            break;
        case 7:
            return seven;
            break;
        case 8:
            return eight;
            break;
        case 9:
            return nine;
            break;
        default:
            return zero;
            break;
    }
}

int get_number_of_digits(int number) {
    int digits = 0;
    if (number < 0) {
        number *= -1;
    }
    while (number > 0) {
        number /= 10;
        digits++;
    }
    if (digits == 0) {
        digits = 1;
    }
    return digits;
}

int* get_digits(int number, int digits) {
    int* digits_array = malloc(digits * sizeof(int));
    for (int i = digits - 1; i >= 0; i--) {
        digits_array[i] = number % 10;
        number /= 10;
    }
    return digits_array;
}

Number* get_ascii_for_number(int number) {
    int digits = get_number_of_digits(number);
    int* digits_array;
    Number* ascii_array;
    if (number < 0) {
        digits_array = get_digits(number * -1, digits);
        ascii_array = malloc(digits * sizeof(Number) + 1);
        ascii_array[0] = minus;
        for (int i = 1; i < digits + 1; i++) {
            ascii_array[i] = get_ascii_for_digit(digits_array[i - 1]);
        }
    } else {
        digits_array = get_digits(number, digits);
        ascii_array = malloc(digits * sizeof(Number));
        for (int i = 0; i < digits; i++) {
            ascii_array[i] = get_ascii_for_digit(digits_array[i]);
        }
    }
    free(digits_array);
    return ascii_array;
}

void print_number(Number* number, int digits) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < digits; j++) {
            for (int k = 0; k < 5; k++) {
                printf("%c", number[j].num[i][k]);
            }
        }
        printf("\n");
    }
}

void calculate(int number1, char operand, int number2) {
    switch(operand) {
        case '+':
            {
                int result = number1 + number2;
                int digits;
                if (result < 0) {
                    digits = get_number_of_digits(result) + 1;
                } else {
                    digits = get_number_of_digits(result);
                }
                if (get_number_of_digits(number1 + number2) > 5) {
                    printf("Result is too big to display\n");
                } else {
                    print_number(get_ascii_for_number(number1 + number2), digits);
                }
                break;
            }
        case '-':
            {
                int result = number1 - number2;
                int digits;
                if (result < 0) {
                    digits = get_number_of_digits(result) + 1;
                } else {
                    digits = get_number_of_digits(result);
                }
                if (get_number_of_digits(number1 - number2) > 5) {
                    printf("Result is too big to display\n");
                } else {
                    print_number(get_ascii_for_number(number1 - number2), digits);
                }
                break;
            }
        case '*':
            {
                int result = number1 * number2;
                int digits;
                if (result < 0) {
                    digits = get_number_of_digits(result) + 1;
                } else {
                    digits = get_number_of_digits(result);
                }
                if (get_number_of_digits(number1 * number2) > 5) {
                    printf("Result is too big to display\n");
                } else {
                    print_number(get_ascii_for_number(number1 * number2), digits);
                }
                break;
            }
        case '/':
            {
                int result = number1 / number2;
                int digits;
                if (result < 0) {
                    digits = get_number_of_digits(result) + 1;
                } else {
                    digits = get_number_of_digits(result);
                }
                if (get_number_of_digits(number1 / number2) > 5) {
                    printf("Result is too big to display\n");
                } else {
                    print_number(get_ascii_for_number(number1 / number2), digits);
                }
                break;
            }
        default:
            printf("Invalid operand\n");
            break;
    }
}

int check_input(int number1, char operand, int number2) {
    return
        get_number_of_digits(number1) <= 5
        && get_number_of_digits(number2) <= 5
        && ((operand == '/' && number2 != 0) || operand != '/');
}

int main() {
    int number1, number2;
    char operand;
    printf("Enter a 2 numbers with an operand between them: ");
    scanf("%d %c %d", &number1, &operand, &number2);
    while (!check_input(number1, operand, number2)) {
        printf("Number too big or division by 0, try again\n");
        printf("Enter a 2 numbers with an operand between them: ");
        scanf("%d %c %d", &number1, &operand, &number2);
    }
    calculate(number1, operand, number2);
    return 0;
}
