#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//function simulates loterry with random n lottery tickets
int main() {
    int n, i, j, k, c;
    int result[6], ticket[6], zlicz[7];
    srand((unsigned) time(NULL));

    scanf("%d", &n);

    for (i = 0; i < 7; i++)
        zlicz[i] = 0;

    for (i = 0; i < 6; i++) {
        j = 0;
        result[i] = (rand() % 49 + 1);
        while (j < i) {
            if (result[i] == result[j])
                result[i] = (rand() % 49 + 1);
            else j++;
        }
    }

    for (i = 0; i < 6; i++)
        printf("%d ", result[i]);

    for (k = 0; k < n; k++) {
        c = 0;
        for (i = 0; i < 6; i++) {
            j = 0;
            ticket[i] = (rand() % 49 + 1);
            while (j < i) {
                if (ticket[i] == ticket[j])
                    ticket[i] = (rand() % 49 + 1);
                else j++;
            }
            j = 0;
            while (j < 6) {
                if (ticket[i] == result[j])c++;
                j++;
            }
        }
        zlicz[c]++;
    }

    for (i = 0; i < 7; i++)
        printf("\n%d  :%d", i, zlicz[i]);
    return 0;
}
