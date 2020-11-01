#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

//function takes two numbers then looks for the lowest number between them that
//has a number bigger than MAX_INT in its Collatz sequence or if there is no such number
//it prints the number which has first number 1 in its Collatz sequence with the highest index
int main() {
    int number1, number2, currentNumber, flag, rememberIndex,
    highscore, collatzIndex, highscoreIndex;
    scanf("%d%d", &number1, &number2);
    currentNumber = 2;
    highscore = 0;
    flag = 1;
    collatzIndex = 0;
    for (int i = number1; (i <= number2) && (flag != 0); i++) {
        currentNumber = i;
        rememberIndex = i;
        collatzIndex = 0;
        while ((flag == 1) && (currentNumber != 1)) {
            if (currentNumber % 2 == 1) {
                if (currentNumber > (INT_MAX - 1) / 3)
                    flag = 0;
                else
                    currentNumber = 3 * currentNumber + 1;
            } else
                currentNumber = currentNumber / 2;
            collatzIndex++;
        }
        if (collatzIndex > highscore) {
            highscoreIndex = i;
            highscore = collatzIndex;
        }
    }
    if (flag == 0)
        printf("%d?", rememberIndex);
    else
        printf("%d %d", highscoreIndex, highscore);
    return 0;
}
