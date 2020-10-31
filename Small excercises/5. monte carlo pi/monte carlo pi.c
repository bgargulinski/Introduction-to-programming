#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//program approximates pi with monte carlo method
int main() {
    srand((unsigned) time(NULL));
    int n, k;
    float random1, random2, pi;

    k = 0;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        random1 = ((float) rand()) / RAND_MAX;
        random2 = ((float) rand()) / RAND_MAX;
        if (random1 * random1 + random2 * random2 <= 1)
            k++;
    }

    pi = 4 * (k / n);

    printf("%lf", pi);
    return 0;
}
