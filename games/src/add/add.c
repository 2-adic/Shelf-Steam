#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void print_help() {
    printf("An addition quiz that tests your addition skills! Run the program with the argument \"--seed #\" to replay the same quiz.\n");
}

int main(int argc, char *argv[]) {
    unsigned int seed;
    int seedProvided = 0;


    if (argc > 1) {
        // processes command line arguments
        if (strcmp(argv[1], "--help") == 0) {
            print_help();
            return 0;
        } else if (strcmp(argv[1], "--seed") == 0) {
            if (argc > 2) {
                seed = (unsigned int)atoi(argv[2]);
                seedProvided = 1;
            } else {
                fprintf(stderr, "Error: --seed requires a number argument.\n");
                return 1;
            }
        }
    }

    // random questions are seed based
    if (seedProvided) {
        srand(seed);
    } else {
        seed = (unsigned int)time(NULL);
        srand(seed);
    }

    // gets user input for the amount of question to display
    int numQuestions;
    printf("How many questions do you want? ");
    if (scanf("%d", &numQuestions) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    int correctCount = 0;
    for (int i = 0; i < numQuestions; i++) {
        // generates two random numbers between 1 and 999.
        int num1 = (rand() % 999) + 1;
        int num2 = (rand() % 999) + 1;
        int correctAnswer = num1 + num2;
        int userAnswer;

        printf("\n----------------------------------------\n\n");

        // asks user the addition question
        printf("Question: %d\n", i+1);
        printf("%d + %d = ", num1, num2);
        if (scanf("%d", &userAnswer) != 1) {
            fprintf(stderr, "Invalid input.\n");
            return 1;
        }

        // lets the user know if they were correct or incorrect
        if (userAnswer == correctAnswer) {
            printf("\nCorrect!\n");
            correctCount++;
        } else {
            printf("\nIncorrect: %d + %d = %d\n", num1, num2, correctAnswer);
        }
    }

    printf("\n----------------------------------------\n\n");

    // calculates and displays the percentage of correct answers
    int percentage = (int)(((double)correctCount / numQuestions) * 100);
    printf("Finished! %d%% of the questions were answered correctly!\n", percentage);
    printf("Seed #: %d\n", seed);

    return 0;
}
