#include <stdio.h>
#include <stdlib.h>

void battlefield(float *D, int *N){

	printf("Enter Battlefield dimensions: ");
	scanf("%f", D);
	printf("Enter Number of Escort Ships (N): ");
        scanf("%d", N);

	printf("\n\n\n\n\n\n\n\n\nBattlefield: (0,0) to (%.2f,%.2f)\n",*D,*D);
	printf("\n\nNumber of Escort Ships(N): %d",*N);
}
