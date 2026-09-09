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
            while (getchar() != '\n');
            continue;
        }

        switch (select) {

            // start simulation
            case 1:
            {
                int simChoice;

                do {
                    system("clear");

                    printf("                                                    |Start Simulation|\n\n\n\n");
                    printf("                                                1. Part 1-A\n\n");
                    printf("                                                2. Part 1-B\n\n");
                    printf("                                                3. Part 1-C\n\n");
                    printf("                                                4. Back to Main Menu\n\n\n");

                    printf("                                                Enter Your Choice: ");

                    if (scanf("%d", &simChoice) != 1) {
                        while (getchar() != '\n');
                        continue;
                    }

                    switch (simChoice) {

                        // part 1 A
                        case 1:
                            system("clear");
                            part_1_A();
                            break;

                        // part 1 B
                        case 2:
                        {
                            int bChoice;

                            do {
                                system("clear");

                                printf("                                                |Part 1-B|\n\n\n\n");
                                printf("                                                1. Simulation 1\n\n");
                                printf("                                                2. Simulation 2\n\n");
                                printf("                                                3. Back\n\n\n");

                                printf("                                                Enter Your Choice: ");

                                if (scanf("%d", &bChoice) != 1) {
                                    while (getchar() != '\n');
                                    continue;
                                }

                                switch (bChoice) {

                                    case 1:
                                        system("clear");
                                        simulation_part_B_1();
                                        break;

                                    case 2:
                                        system("clear");
                                        simulation_part_B_2();
                                        break;

                                    case 3:
                                        break;

                                    default:
                                        printf("\nInvalid choice!");
                                        while (getchar() != '\n');
                                        getchar();
                                        break;
                                }

                            } while (bChoice != 3);

                            break;
                        }

                        // part 1 C
                        case 3:
                        {
                            int cChoice;

                            do {
                                system("clear");

                                printf("                                                |Part 1-C|\n\n\n\n");
                                printf("                                                1. Part 1-A\n\n");
                                printf("                                                2. Part 1-B - Simulation 1\n\n");
                                printf("                                                3. Part 1-B - Simulation 2\n\n");
                                printf("                                                4. Back\n\n\n");

                                printf("                                                Enter Your Choice: ");

                                if (scanf("%d", &cChoice) != 1) {
                                    while (getchar() != '\n');
                                    continue;
                                }

                                switch (cChoice) {

                                    case 1:
                                        system("clear");
                                        part_1_C_A();
                                        break;

                                    case 2:
                                        system("clear");
                                        part_1_C_B1();
                                        break;

                                    case 3:
                                        system("clear");
                                        part_1_C_B2();
                                        break;

                                    case 4:
                                        break;

                                    default:
                                        printf("\nInvalid choice!");
                                        while (getchar() != '\n');
                                        getchar();
                                        break;
                                }

                            } while (cChoice != 4);

                            break;
                        }

                        case 4:
                            break;

                        default:
                            printf("\nInvalid choice!");
                            while (getchar() != '\n');
                            getchar();
                            break;
                    }

                } while (simChoice != 4);

                break;
            }

            // instructions
            case 2:
                system("clear");

                printf("                           -----------INSTRUCTIONS-------                             \n\n\n\n");
                printf(" 1. Mode 1 (Part 1-A): Standard 1-v-N Naval Battle Calculation.\n");
                printf(" 2. Mode 2 (Part 1-B): Path-based Navigation over 'k' points and Battleship gun jamming\n");
                printf(" 3. Mode 3 (Part 1-C): Part 1 A & B Simulations with impact power\n");
                printf(" 4. Input battleship coordinates, max speed, and battlefield dimensions.\n");
                printf(" 5. Escort ships will auto-generate based on probabilistic parameters.\n\n");
                printf("=====================================================================\n");
                printf("\nPress Enter to return to Main Menu...");

                while (getchar() != '\n');
                getchar();

                break;

            // simulator statistics
            case 3:
            {
                int statChoice;
                FILE *fp;
                char line[256];

                do {
                    system("clear");

                    printf("                                                    |Simulator Statistics|\n\n\n\n");
                    printf("                                                1. Part 1-A Simulation\n\n");
                    printf("                                                2. Part 1-B Simulation 1\n\n");
                    printf("                                                3. Part 1-B Simulation 2\n\n");
                    printf("                                                4. Part 1-C Simulation\n\n");
                    printf("                                                5. Back to Main Menu\n\n\n");

                    printf("                                                Enter Your Choice: ");

                    if (scanf("%d", &statChoice) != 1) {
                        while (getchar() != '\n');
                        continue;
                    }

                    switch (statChoice) {

                        // part 1 A results
                        case 1:
                            system("clear");

                            fp = fopen("part_1_A.txt", "r");

                            printf("========================================\n");
                            printf("          PART 1-A STATISTICS\n");
                            printf("========================================\n\n");

                            if (fp == NULL) {
                                printf("No Part 1-A simulation results found!\n");
                            }
                            else {
                                while (fgets(line, sizeof(line), fp) != NULL) {
                                    printf("%s", line);
                                }

                                fclose(fp);
                            }

                            printf("\n\n========================================\n");
                            printf("Press Enter to return...");

                            while (getchar() != '\n');
                            getchar();

                            break;

                        // part 1 B simulation 1 results
                        case 2:
                            system("clear");

                            fp = fopen("part_1_B_simulation_1.txt", "r");

                            printf("========================================\n");
                            printf("       PART 1-B SIMULATION 1\n");
                            printf("              STATISTICS\n");
                            printf("========================================\n\n");

                            if (fp == NULL) {
                                printf("No Part 1-B Simulation 1 results found!\n");
                            }
                            else {
                                while (fgets(line, sizeof(line), fp) != NULL) {
                                    printf("%s", line);
                                }

                                fclose(fp);
                            }

                            printf("\n\n========================================\n");
                            printf("Press Enter to return...");

                            while (getchar() != '\n');
                            getchar();

                            break;

                        // part 1 B simulation 2 results
                        case 3:
                            system("clear");

                            fp = fopen("part_1_B_simulation_2.txt", "r");

                            printf("========================================\n");
                            printf("       PART 1-B SIMULATION 2\n");
                            printf("              STATISTICS\n");
                            printf("========================================\n\n");

                            if (fp == NULL) {
                                printf("No Part 1-B Simulation 2 results found!\n");
                            }
                            else {
                                while (fgets(line, sizeof(line), fp) != NULL) {
                                    printf("%s", line);
                                }

                                fclose(fp);
                            }

                            printf("\n\n========================================\n");
                            printf("Press Enter to return...");

                            while (getchar() != '\n');
                            getchar();

                            break;

                        // part 1 C results
                        case 4:
                        {
                            int cStatChoice;

                            do {
                                system("clear");

                                printf("                                                |Part 1-C Simulation|\n\n\n\n");
                                printf("                                                1. Part 1-C - Part 1-A\n\n");
                                printf("                                                2. Part 1-C - Simulation 1\n\n");
                                printf("                                                3. Part 1-C - Simulation 2\n\n");
                                printf("                                                4. Back\n\n\n");

                                printf("                                                Enter Your Choice: ");

                                if (scanf("%d", &cStatChoice) != 1) {
                                    while (getchar() != '\n');
                                    continue;
                                }

                                switch (cStatChoice) {

                                    case 1:
                                        system("clear");

                                        fp = fopen("part_1_C_A.txt", "r");

                                        printf("========================================\n");
                                        printf("       PART 1-C - (PART 1-A)\n");
                                        printf("              STATISTICS\n");
                                        printf("========================================\n\n");

                                        if (fp == NULL) {
                                            printf("No Part 1-C Part 1-A results found!\n");
                                        }
                                        else {
                                            while (fgets(line, sizeof(line), fp) != NULL) {
                                                printf("%s", line);
                                            }

                                            fclose(fp);
                                        }

                                        printf("\n\n========================================\n");
                                        printf("Press Enter to return...");

                                        while (getchar() != '\n');
                                        getchar();

                                        break;

                                    case 2:
                                        system("clear");

                                        fp = fopen("part_1_C_B_simulation_1.txt", "r");

                                        printf("========================================\n");
                                        printf("       PART 1-C - (PART B SIMULATION 1)\n");
                                        printf("              STATISTICS\n");
                                        printf("========================================\n\n");

                                        if (fp == NULL) {
                                            printf("No Part 1-C Simulation 1 results found!\n");
                                        }
                                        else {
                                            while (fgets(line, sizeof(line), fp) != NULL) {
                                                printf("%s", line);
                                            }

                                            fclose(fp);
                                        }

                                        printf("\n\n========================================\n");
                                        printf("Press Enter to return...");

                                        while (getchar() != '\n');
                                        getchar();

                                        break;

                                    case 3:
                                        system("clear");

                                        fp = fopen("part_1_C_B_simulation_2.txt", "r");

                                        printf("========================================\n");
                                        printf("       PART 1-C - (PART BSIMULATION 2)\n");
                                        printf("              STATISTICS\n");
                                        printf("========================================\n\n");

                                        if (fp == NULL) {
                                            printf("No Part 1-C Simulation 2 results found!\n");
                                        }
                                        else {
                                            while (fgets(line, sizeof(line), fp) != NULL) {
                                                printf("%s", line);
                                            }

                                            fclose(fp);
                                        }

                                        printf("\n\n========================================\n");
                                        printf("Press Enter to return...");

                                        while (getchar() != '\n');
                                        getchar();

                                        break;

                                    case 4:
                                        break;

                                    default:
                                        printf("\nInvalid choice!");
                                        while (getchar() != '\n');
                                        getchar();
                                        break;
                                }

                            } while (cStatChoice != 4);

                            break;
                        }

                        // go back to main menu
                        case 5:
                            break;

                        default:
                            printf("\nInvalid choice!");
                            while (getchar() != '\n');
                            getchar();
                            break;
                    }

                } while (statChoice != 5);

                break;
            }

            // exit
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

