#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

void main_menu(){
	int select;
	printf("                                                    |Main Menu|\n\n\n\n\n\n");
	printf("                                                1. Start Simulation\n\n");
	printf("                                                2. Instructions\n\n");
	printf("                                                3. Options\n\n");
	printf("                                                4. Extras\n\n");
	printf("                                                5. Exit\n\n\n\n\n");
	
	printf("Enter Your Choice: ");
	scanf("%d", &select);

	switch(select){
		case 1:
		system("clear");	
		break;

		case 2:
		system("clear");
		break;

		case 3:
		system("clear");
		break;

		case 4:
		system("clear");
		break;

		default:
		system("clear");
	}

		
}


