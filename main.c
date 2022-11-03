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
        digits++;
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
    Number* ascii_array = malloc(digits * sizeof(Number));
    int index = 0;
    if (number < 0) {
        digits_array = get_digits(number * -1, digits);
        ascii_array[0] = minus;
        index = 1;
    } else {
        digits_array = get_digits(number, digits);
    }
    for (int i = index; i < 5 - digits + index; i++) {
        ascii_array[i] = zero;
    }
    for (int i = 0; i < digits; i++) {
        ascii_array[i + 5 - digits + index] = get_ascii_for_digit(digits_array[i]);
    }
    if (digits == 6) {
        ascii_array[0] = minus;
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
                    digits = 6;
                } else {
                    digits = 5;
                }
                if (get_number_of_digits(result) > digits) {
                    printf("Result is too big to display\n");
                } else {
                    print_number(get_ascii_for_number(result), digits);
                }
                break;
            }
        case '-':
            {
                int result = number1 - number2;
                int digits;
                if (result < 0) {
                    digits = 6;
                } else {
                    digits = 5;
                }
                if (get_number_of_digits(result) > digits) {
                    printf("Result is too big to display\n");
                } else {
                    print_number(get_ascii_for_number(result), digits);
                }
                break;
            }
        case '*':
            {
                int result = number1 * number2;
                int digits;
                if (result < 0) {
                    digits = 6;
                } else {
                    digits = 5;
                }
                if (get_number_of_digits(result) > digits) {
                    printf("Result is too big to display\n");
                } else {
                    print_number(get_ascii_for_number(result), digits);
                }
                break;
            }
        case '/':
            {
                int result = number1 / number2;
                int digits;
                if (result < 0) {
                    digits = 6;
                } else {
                    digits = 5;
                }
                if (get_number_of_digits(result) > digits) {
                    printf("Result is too big to display\n");
                } else {
                    print_number(get_ascii_for_number(result), digits);
                }
                break;
            }
        default:
            printf("Invalid operand\n");
            break;
    }
}

int check_valid_input(int number1, char operand, int number2) {
    return
        (number1 < 0 && get_number_of_digits(number1) <= 6) ||
        (number2 < 0 && get_number_of_digits(number2) <= 6) ||
        (get_number_of_digits(number1) <= 5 &&
        get_number_of_digits(number2 <= 5) &&
        ((operand == '/' && number2 != 0) || operand != '/'));
}

int main() {
    int number1, number2;
    char operand;
    printf("Enter a 2 numbers with an operand between them: ");
    scanf("%d %c %d", &number1, &operand, &number2);
    while (!check_valid_input(number1, operand, number2)) {
        printf("Number too big or division by 0, try again\n");
        printf("Enter a 2 numbers with an operand between them: ");
        scanf("%d %c %d", &number1, &operand, &number2);
    }
    calculate(number1, operand, number2);
    return 0;
}
