#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "sim.h"

void main_menu(){
	int select;
	int exitoption;
	do
	  {
	   printf("                                                     |Main Menu|\n\n\n\n\n\n");
	   printf("                                                1. Start Simulation\n\n");
	   printf("                                                2. Instructions\n\n");
	   printf("                                                3. Options\n\n");
	   printf("                                                4. Exit\n\n\n\n\n");
	
	   printf("                                                Enter Your Choice: ");
	   scanf("%d", &select);

	   switch(select)
        {
            case 1:
                part_1_A();
                break;

            case 2:
                system("clear");
                printf("Instructions\n");
                break;

            case 3:
                system("clear");
                printf("Statistics\n");
                break;

            case 4:

                do
                {
                    system("clear");

                    printf("                                         Are you sure?\n\n\n\n\n\n");
                    printf("                              1. Yes, That's enough for today!\n\n");
                    printf("                              2. No, I changed my mind!\n\n\n\n\n\n\n");

                    printf("                                       Enter your choice: ");
                    scanf("%d", &exitoption);

                } while(exitoption != 1 && exitoption != 2);

                if(exitoption == 1)
                {
                    system("clear");
                    printf("                                         Goodbye! See you later.\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		    printf("                                          Press Enter To Exit...             ");
		    getchar();
		    getchar();
		    system("clear");
                    return;
                }

                // If exitoption == 2,
                // nothing happens here.
                // The main menu loop continues.
                system("clear");
		break;

            default:
                system("clear");
                printf("Invalid choice!\n");
                break;
        }

    } while(1);
}

