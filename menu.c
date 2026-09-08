#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "sim.h"
#include "combat.h"

void main_menu() {
    int select;
    int exitoption;

    do {
        system("clear");
        printf("                                                    |Main Menu|\n\n\n\n\n\n");
        printf("                                                1. Start Simulation\n\n");
        printf("                                                2. Instructions\n\n");
        printf("                                                3. Simulator Statistics\n\n");
        printf("                                                4. Exit\n\n\n\n\n");

        printf("                                                Enter Your Choice: ");
        
        if (scanf("%d", &select) != 1) {
            while (getchar() != '\n'); // Clear buffer on invalid input
            continue;
        }

        switch (select) {
            case 1:
                system("clear");
                part_1_A();
                break;

            case 2:
                system("clear");
                printf("                           -----------INSTRUCTIONS-------                             \n\n\n\n");
                printf(" 1. Mode 1 (Part 1-A): Standard 1-v-N Naval Battle Calculation.\n");
                printf(" 2. Mode 2 (Part 1-B): Path-based Navigation over 'k' points with\n");
                printf("    cumulative Health Point (HP) degradation.\n");
                printf(" 3. Input battleship coordinates, max speed, and battlefield dimensions.\n");
                printf(" 4. Escort ships will auto-generate based on probabilistic parameters.\n\n");
                printf("=====================================================================\n");
                printf("\nPress Enter to return to Main Menu...");
                while (getchar() != '\n');
                getchar();
                break;

            case 3:
                  system("clear");
		  FILE *fp;
                  char line[256];

                 fp = fopen("part1_A_results.txt", "r");

                 printf("========================================\n");
                 printf("              STATISTICS\n");
                 printf("========================================\n\n");

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

    printf("\n\n========================================\n");
    printf("Press Enter to return to Main Menu...");
    getchar();
    getchar();

    system("clear");
    break;
 
           

            case 4:
                do {
                    system("clear");
                    printf("                                          Are you sure?\n\n\n\n\n\n");
                    printf("                              1. Yes, That's enough for today!\n\n");
                    printf("                              2. No, I changed my mind!\n\n\n\n\n\n\n");

                    printf("                                       Enter your choice: ");
                    if (scanf("%d", &exitoption) != 1) {
                        while (getchar() != '\n');
                        continue;
                    }

                } while (exitoption != 1 && exitoption != 2);

                if (exitoption == 1) {
                    system("clear");
                    printf("                                          Goodbye! See you later.\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                    printf("                                           Press Enter To Exit...             ");
                    while (getchar() != '\n');
                    getchar();
                    system("clear");
                    return;
                }
                
                system("clear");
                break;

            default:
                system("clear");
                printf("Invalid choice! Press Enter to try again...");
                while (getchar() != '\n');
                getchar();
                break;
        }

    } while (1);
}
