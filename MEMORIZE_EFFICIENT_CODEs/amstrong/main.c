#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main() {
    char input[100];
    printf("Enter a number: ");
    scanf("%s", input);

    int num = atoi(input);
    int len = strlen(input);

    int sum = 0;
    for (int i = 0; i < len; i++) {
        int digit = input[i] - '0';
        sum += pow(digit, len);
    }

    if (sum == num)
        printf("%d is an Armstrong number.\n", num);
    else
        printf("%d is not an Armstrong number.\n", num);

    return 0;
}
