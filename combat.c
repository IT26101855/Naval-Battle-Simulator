#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "combat.h"

#define GRAVITY 9.81

// Helper function to get full name of Escort Ship Type
const char* get_escort_name(char type) {
    switch (type) {
        case 'A': return "1936A-class Destroyer";
        case 'B': return "Gabbiano-class Corvette";
        case 'C': return "Matsu-class Destroyer";
        case 'D': return "F-class Escort Ship";
        case 'E': return "Japanese Kaibokan";
        default:  return "Unknown Escort Ship";
    }
}

void show_simulation_statistics() {
    FILE *fp = fopen("part1_A_results.txt", "r");

    if (fp == NULL) {
        printf("\n[!] No simulation history found (part1_A_results.txt does not exist).\n");
        printf("    Please run a simulation first!\n");
        printf("\nPress Enter to return...");
        while (getchar() != '\n');
        getchar();
        return;
    }

    system("clear");
    printf("                                        ----- PAST SIMULATION STATISTICS-----           \n");

    char ch;
    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);
    }

    fclose(fp);

    printf("\n=====================================================\n");
    printf("End of Statistics.\n\n"); 
    printf ("                                     Press Enter to return to Main Menu...");
    while (getchar() != '\n');
    getchar();
}

void battle_calculations(struct Battleship b, struct Escortship e[], int N) {
    FILE *fp = fopen("part1_A_results.txt", "a");
    if (fp == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    // Find the next simulation number 
    FILE *countFile = fopen("part1_A_results.txt", "r");

    int simulationNumber = 1;
    char line[200];

    if (countFile != NULL)
      {
        while (fgets(line, sizeof(line), countFile) != NULL)
          {
             if (strstr(line, "=== INITIAL BATTLEFIELD CONDITIONS ===") != NULL)
               {
                    simulationNumber++;
        }
    }

    fclose(countFile);
}

fprintf(fp, "\n\n========================================\n");
fprintf(fp, "              SIMULATION %d\n", simulationNumber);
fprintf(fp, "========================================\n\n");

     //--- INITIAL CONDITIONS--- 

    fprintf(fp, "=== INITIAL BATTLEFIELD CONDITIONS ===\n\n");

    fprintf(fp, "Battleship:\n");
    fprintf(fp, "Type: %c\n", b.type);
    fprintf(fp, "Position: (%.2f, %.2f)\n", b.x, b.y);
    fprintf(fp, "Max Velocity: %.2f\n\n", b.maxVelocity);

    fprintf(fp, "Total Escort Ships (N): %d\n\n", N);

    fprintf(fp, "----- ESCORT SHIP DETAILS -----\n");

    for (int i = 0; i < N; i++)
    {
        fprintf(fp, "\nEscort Ship ID: %d\n", e[i].id);
        fprintf(fp, "Type: E_%c\n", e[i].type);
        fprintf(fp, "Position: (%.2f, %.2f)\n", e[i].x, e[i].y);
        fprintf(fp, "Minimum Velocity: %.2f\n", e[i].minVelocity);
        fprintf(fp, "Maximum Velocity: %.2f\n", e[i].maxVelocity);
        fprintf(fp, "Minimum Angle: %.2f degrees\n", e[i].minAngle);
        fprintf(fp, "Maximum Angle: %.2f degrees\n", e[i].maxAngle);
        fprintf(fp, "Impact Power: %.2f\n", e[i].impactPower);
    }

    //---SIMULATION--- 

    int b_sunk = 0;
    int sunk_by_id = -1;
    int hit_e_count = 0;

    float battle_duration = 0.0;

    // Calculate maximum flight time of Battleship's shell (at optimal 45 degrees)
    float vy = b.maxVelocity * sin(45.0 * M_PI / 180.0);
    float time_to_hit_b = (2.0 * vy) / GRAVITY;

    for (int i = 0; i < N; i++)
    {
       //distance between battleship and escort ship 
        float dx = b.x - e[i].x;
        float dy = b.y - e[i].y;

        float distance = sqrt(dx * dx + dy * dy);

   
          // battleship attacks escort Ship

        float B_range =
            (b.maxVelocity * b.maxVelocity) / GRAVITY;

        if (distance <= B_range)
        {
            e[i].isDestroyed = 1;
            hit_e_count++;

	    if (time_to_hit_b > battle_duration) {
                battle_duration = time_to_hit_b;
            }
        }
          // escort ship attacks battleship
          

        float minAngleRad =
            e[i].minAngle * M_PI / 180.0;

        float maxAngleRad =
            e[i].maxAngle * M_PI / 180.0;

        float E_range_min =
            (e[i].minVelocity * e[i].minVelocity *
             sin(2 * minAngleRad)) / GRAVITY;

        float E_range_max =
            (e[i].maxVelocity * e[i].maxVelocity *
             sin(2 * maxAngleRad)) / GRAVITY;

        if (distance >= E_range_min &&
            distance <= E_range_max)
        {
            b_sunk = 1;
            sunk_by_id = e[i].id;

            /*
             * Since one shell impact can destroy
             * the Battleship.
             * we can stop after the first successful hit.
             */
            break;
        }
    }

    //display simulation results 

    fprintf(fp, "\n\n==== SIMULATION RESULTS ====\n\n");

    if (b_sunk && sunk_by_id != -1 )
    {
        fprintf(fp, "STATUS: Battleship SANK!\n");
        fprintf(fp, "Sunk by Escort Ship ID: %d (Type: E_%c - %s) \n", e[sunk_by_id].id, e[sunk_by_id].type, get_escort_name(e[sunk_by_id].type));
    }
    else
    {
        fprintf(fp, "STATUS: Battleship SURVIVED!\n");
        fprintf(fp, "Total Escort Ships Hit: %d\n", hit_e_count);
    }   
       	fprintf(fp, "Battle Duration (Max Time to Hit): %.2f seconds\n", battle_duration);
    

    // ---FINAL CONDITIONS---

    fprintf(fp, "\n\n==== FINAL BATTLEFIELD CONDITIONS ====\n\n");

    fprintf(fp, "Battleship:\n");
    fprintf(fp, "Type: %c\n", b.type);
    fprintf(fp, "Position: (%.2f, %.2f)\n", b.x, b.y);
    fprintf(fp, "Max Velocity: %.2f\n", b.maxVelocity);

    fprintf(fp, "\nEscort Ships:\n");

    for (int i = 0; i < N; i++)
    {
        fprintf(fp, "\nEscort Ship ID: %d\n", e[i].id);
        fprintf(fp, "Type: E_%c\n (%s)\n", e[i].type, get_escort_name(e[i].type) );
        fprintf(fp, "Position: (%.2f, %.2f)\n",
                e[i].x, e[i].y);

        if (e[i].isDestroyed)
        {
            fprintf(fp, "Status: DESTROYED\n");
        }
        else
        {
            fprintf(fp, "Status: SURVIVED\n");
        }
    }

    fclose(fp);

    printf("\n                           Combat results saved to 'part1A_results.txt' successfully!\n");
    getchar();
    system("clear");
}
