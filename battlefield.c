#include <stdio.h>
#include <stdlib.h>
#include "battlefield.h"

void battlefield(float *D, int *N) {
    //valid canvas dimension (D) input
    while (1) {
        printf("Enter Battlefield dimensions (D > 0): ");
        if (scanf("%f", D) == 1 && *D > 0) {
            break;
        }
        printf("Invalid input! Please enter a positive number for dimension.\n");
        while (getchar() != '\n'); // clear buffer
    }

    //valid escort ships count (N) input
    while (1) {
        printf("Enter Number of Escort Ships (N > 0): ");
        if (scanf("%d", N) == 1 && *N > 0) {
            break;
        }
        printf("Invalid input! Please enter a positive integer for ship count.\n");
        while (getchar() != '\n'); 
    }

    printf("\n\nBattlefield: (0.00, 0.00) to (%.2f, %.2f)\n", *D, *D);
    printf("Number of Escort Ships (N): %d\n", *N);
}
