#include <stdio.h>

//calculating sum of arithmetic sequence
int main() {
    double s, k, sum;
    int n;

    scanf("%lf%lf%d", &s, &k, &n);

    sum = (2 * s + (n - 1) * k) * (n / 2);

    printf("%lf", sum);

    return 0;
}
