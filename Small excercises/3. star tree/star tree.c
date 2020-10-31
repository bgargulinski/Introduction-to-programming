#include <stdio.h>

//program is drawing a tree made of stars
int main() {
    int n;

    scanf("%d", &n);

    if (n == 1)
        printf(" * \n***\n***");
    else {
        for (int j = 1; j <= n; j++) {
            for (int i = 1; i <= n - j; i++)
                printf(" ");

            for (int i = 1; i <= 2 * j - 1; i++)
                printf("*");

            printf("\n");
        }

        for (int i = 1; i <= 3; i++) {
            for (int j = 0; j < n - 2; j++)
                printf(" ");
            printf("***\n");
        }
    }
    return 0;
}
