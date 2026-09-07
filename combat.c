#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "combat.h"

#define GRAVITY 9.81

void battle_calculations(struct Battleship b, struct Escortship e[], int N) {
    FILE *fp = fopen("part1_A_results.txt", "w");
    if (fp == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

   /* ================= INITIAL CONDITIONS ================= */

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

    /* ================= SIMULATION ================= */

    int b_sunk = 0;
    int sunk_by_id = -1;
    int hit_e_count = 0;

    float battle_duration = 0.0;

    for (int i = 0; i < N; i++)
    {
       //distance between battleship and escort ship 
        float dx = b.x - e[i].x;
        float dy = b.y - e[i].y;

        float distance = sqrt(dx * dx + dy * dy);

        /* -------------------------------------------------
           Battleship attacks Escort Ship
           ------------------------------------------------- */

        float B_range =
            (b.maxVelocity * b.maxVelocity) / GRAVITY;

        if (distance <= B_range)
        {
            e[i].isDestroyed = 1;
            hit_e_count++;
        }

        /* -------------------------------------------------
           Escort Ship attacks Battleship
           ------------------------------------------------- */

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
             * the Battleship in Part 1-A,
             * we can stop after the first successful hit.
             */
            break;
        }
    }

    //display simulation results 

    fprintf(fp, "\n\n==== SIMULATION RESULTS ====\n\n");

    if (b_sunk)
    {
        fprintf(fp, "STATUS: Battleship SANK!\n");
        fprintf(fp, "Sunk by Escort Ship ID: %d\n", sunk_by_id);
    }
    else
    {
        fprintf(fp, "STATUS: Battleship SURVIVED!\n");
        fprintf(fp, "Total Escort Ships Hit: %d\n", hit_e_count);
        fprintf(fp, "Battle Duration: %.2f seconds\n", battle_duration);
    }

    /* ================= FINAL CONDITIONS ================= */

    fprintf(fp, "\n\n==== FINAL BATTLEFIELD CONDITIONS ====\n\n");

    fprintf(fp, "Battleship:\n");
    fprintf(fp, "Type: %c\n", b.type);
    fprintf(fp, "Position: (%.2f, %.2f)\n", b.x, b.y);
    fprintf(fp, "Max Velocity: %.2f\n", b.maxVelocity);

    fprintf(fp, "\nEscort Ships:\n");

    for (int i = 0; i < N; i++)
    {
        fprintf(fp, "\nEscort Ship ID: %d\n", e[i].id);
        fprintf(fp, "Type: E_%c\n", e[i].type);
        fprintf(fp, "Position: (%.2f, %.2f)\n",
                e[i].x, e[i].y);

        if (e[i].isDestroyed)
        {
            fprintf(fp, "Status: DESTROYED\n");
        }
        else
        {
            fprintf(fp, "Status: ALIVE\n");
        }
    }

    fclose(fp);

    printf("\n                           Combat results saved to 'part1A_results.txt' successfully!\n");
    getchar();
    system("clear");
}
