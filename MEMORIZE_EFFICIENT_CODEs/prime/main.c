#include <stdio.h>

int main() {
    int num, is_prime = 1;
    printf("Enter a number: ");
    scanf("%d", &num);

    if (num <= 1) {
        is_prime = 0;
    } else {
        for (int i = 2; i < num / 2 + 1; i++) {
            if (num % i == 0) {
                is_prime = 0;
                break;
            }
        }
    }

    if (is_prime)
        printf("%d is a prime number.\n", num);
    else
        printf("%d is not a prime number.\n", num);

    return 0;
}
