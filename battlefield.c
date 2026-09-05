#include <stdio.h>
#include <stdlib.h>

void battlefield(){
	float D;
	int N;
	printf("Enter Battlefield dimensions: ");
	scanf("%f", &D);
	printf("Enter Number of Escort Ships (N): ");
        scanf("%d", &N);

	printf("Battlefield: (0,0) to (%.2f,%.2f)\n",D,D);
}
