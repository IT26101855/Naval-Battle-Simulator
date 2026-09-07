#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "sim.h"
#include "combat.h"

void main_menu(){
	int select;
	int exitoption;
	//display the main menu options in a loop
	do
	  {
	   printf("                                                     |Main Menu|\n\n\n\n\n\n");
	   printf("                                                1. Start Simulation\n\n");
	   printf("                                                2. Instructions\n\n");
	   printf("                                                3. Simulator Statistics\n\n");
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

		FILE *fp;
                char line[256];

                fp = fopen("part1_A_results.txt", "r");

              printf("                                        --------------- Simulator Statistics---------------\n\n\n\n\n");

              if (fp == NULL)
                {
                    printf("No simulation results found!\n");
        }
              else
                {
                     while (fgets(line, sizeof(line), fp) != NULL)
                          {  
                              printf("%s", line);
                          }

                     fclose(fp);
         }

           
           printf("\n\n\n\n\n\n\n\n\n                                                Press Enter to return to Main Menu...");
           getchar();
           getchar();

           system("clear");
           break;

            case 4:
               //function of the exit option in the main menu in a loop

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

