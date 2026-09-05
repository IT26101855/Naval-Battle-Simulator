#include <stdio.h>
#include <stdlib.h>
#include "sim.h"

//data structure of battleship
struct Battleship{
	char type;
	float x;
	float y;
	float maxVelocity;
};
//data structure of escort ships
struct Escortship{
	int id;
	char type;
	float x;
	float y;
	float minVelocity;
	float maxVelocity;
	float minAngele;
	float maxAngle;
};
//part 1 A simulation function
void part_1_A(){
	system("clear");
	printf("                                     Start\n\n\n");
	printf("                                Part-1-A Simulation\n\n");
	struct Battleship b;
//getting the details of the battleship

	printf("Enter Battleship Type(U M R S): ");
	scanf(" %c", &b.type);

	printf("Enter Battleship's X Position: ");
	scanf("%f", &b.x);

	printf("Enter Battleship's Y Position: ");
	scanf("%f", &b.y);

	printf("Enter Battleship's Max Velocity: ");
	scanf("%f", &b.maxVelocity);

//displaing the details of the battleship
	
	printf("\n-----Battle Ship Information-----\n");
	printf("Type: %c\n", b.type);
	printf("Position:(%.2f,%.2f)\n", b.x, b.y);
	printf("Max Velocity: %.2f\n", b.maxVelocity);
	getchar();
	getchar();
	system("clear");
	printf("                                                        To Be Continued...\n\n\n\n\n");
	getchar();
	system("clear");
	

}
