#include <stdio.h>

// calculating median of 3 numbers
int main() {
    int number[3];
    int median, max, min;

    for (int i = 0; i < 3; i++){
        scanf("%d", &number[i]);
    }

    for(int i = 1; i < 3; i++){
        if (number[i] >= number[(i + 1) % 3]
        && number[i] <= number[(i + 2) % 3])
            median = number[i];
        else if (number[i] <= number[(i + 1) % 3]
                 && number[i] >= number[(i + 2) % 3])
            median = number[i];
    }

    printf("%d", median);

    return 0;
}
