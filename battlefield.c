#include <stdio.h>
#include <stdlib.h>
#include "battlefield.h"

void battlefield(float *D, int *N) {
    // Valid Canvas Dimension (D) Input
    while (1) {
        printf("Enter Battlefield dimensions (D > 0): ");
        if (scanf("%f", D) == 1 && *D > 0) {
            break;
        }
        printf("Invalid input! Please enter a positive number for dimension.\n");
        while (getchar() != '\n'); // Clear buffer
    }

    // Valid Escort Ships Count (N) Input
    while (1) {
        printf("Enter Number of Escort Ships (N > 0): ");
        if (scanf("%d", N) == 1 && *N > 0) {
            break;
        }
        printf("Invalid input! Please enter a positive integer for ship count.\n");
        while (getchar() != '\n'); // Clear buffer
    }

    printf("\n\nBattlefield: (0.00, 0.00) to (%.2f, %.2f)\n", *D, *D);
    printf("Number of Escort Ships (N): %d\n", *N);
}
