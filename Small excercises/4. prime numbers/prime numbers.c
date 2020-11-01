#include <stdio.h>

// factorization of number
int main() {
    int n;

    scanf("%d", &n);

    if (n < 2)
        printf("invalid input");
    else {

        int i = 2;
        while (n > 1) {
            if (n % i == 0) {
                n /= i;
                printf("%d", i);

                if (n != 1)
                    printf(" * ");
            }
            else
                i++;
        }
    }

    return 0;
}
