#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void rollDices(int tab[], int size, int n) {
    int dice1, dice2;
    srand((unsigned) time(NULL));

    for (int i = 0; i < 13; i++)
        tab[i] = 0;

    for (int i = 0; i < n; i++) {
        dice1 = rand() % 6 + 1;
        dice2 = rand() % 6 + 1;

        tab[dice1 + dice2]++;
    }
}

int findMax(int tab[], int size) {
    int result = 0;
    for (int i = 0; i < size; i++) {
        if (tab[i] > result)
            result = tab[i];
    }
    return result;
}

void scaleOut(int tab[], int size, int max) {
    for (int i = 2; i < size; i++) {
        tab[i] = (tab[i] * 20) / max;
    }
}

void printHistogram(int tab[], int size) {
    for (int i = 21; i >= 0; i--) {
        if (i != 0 && i != 21) {
            for (int j = 1; j < 14; j++) {
                if (j != 1 && j != 13) {
                    if (tab[j] - i >= 0)
                        printf("* ");
                    else
                        printf("  ");
                }
                else
                    printf("| ");
            }
        }
        else {
            for (int j = 0; j < 25; j++) {
                if (j == 0 || j == 24)
                    printf("+");
                else
                    printf("-");
            }
        }
        printf("\n");
    }
}

int main() {
    int n, score, max;
    int scores[13];

    scanf("%d", &n);

    rollDices(scores, 13, n);

    max = findMax(scores, 13);

    scaleOut(scores, 13, max);

    printHistogram(scores, 13);
}