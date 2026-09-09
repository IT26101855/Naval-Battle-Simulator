#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "combat.h"

#define GRAVITY 9.81

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

float calculateFlightTime(float velocity, float angle)
{
    float angleRad = angle * M_PI / 180.0;

    return (2.0 * velocity * sin(angleRad)) / GRAVITY;
}


void battle_calculations(struct Battleship b, struct Escortship e[], int N)
{

    FILE *fp = fopen("part_1_A.txt", "a");

    if (fp == NULL)
    {
        printf("Error opening file for writing!\n");
        return;
    }


    int simulationNumber = 1;
    char line[256];

    FILE *countFile = fopen("part_1_A.txt", "r");

    if (countFile != NULL)
   {
           int tempNumber;

        while (fgets(line, sizeof(line), countFile) != NULL)
{
    char *simulationText;

    simulationText = strstr(line, "SIMULATION ");

    if (simulationText != NULL)
    {
        if (sscanf(simulationText, "SIMULATION %d", &tempNumber) == 1)
        {
            simulationNumber = tempNumber + 1;
        }
    }
}

        fclose(countFile);
    }

    fprintf(fp, "\n\n");
    fprintf(fp, "                             ========================================\n");
    fprintf(fp, "                                             SIMULATION %d\n", simulationNumber);
    fprintf(fp, "                             ========================================\n\n");

       //initial conditions

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
        fprintf(fp, "Position: (%.2f, %.2f)\n",
                e[i].x, e[i].y);

        fprintf(fp, "Minimum Velocity: %.2f\n",
                e[i].minVelocity);

        fprintf(fp, "Maximum Velocity: %.2f\n",
                e[i].maxVelocity);

        fprintf(fp, "Minimum Angle: %.2f degrees\n",
                e[i].minAngle);

        fprintf(fp, "Maximum Angle: %.2f degrees\n",
                e[i].maxAngle);
    }



    //  ---SIMULATION---

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


          //battleship attacks escort Ship

        float B_range =
            (b.maxVelocity * b.maxVelocity) / GRAVITY;

        if (distance <= B_range)
        {
            e[i].isDestroyed = 1;
            hit_e_count++;

            float hit_time =
           calculateFlightTime(b.maxVelocity, 45.0);

           if (hit_time > battle_duration)
              {
                   battle_duration = hit_time;
              }
        }

          //escort Ship attacks battleship

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

             battle_duration =
             calculateFlightTime(e[i].maxVelocity,e[i].maxAngle);

            break;
        }
    }


    fprintf(fp, "\n\n==== SIMULATION RESULTS ====\n\n");

    if (b_sunk)
    {
        fprintf(fp, "STATUS: Battleship SANK!\n");
        fprintf(fp, "Sunk by Escort Ship ID: %d\n",
                sunk_by_id);
        fprintf(fp, "Battle Duration: %.2f seconds\n",
            battle_duration);
    }
    else
    {
        fprintf(fp, "STATUS: Battleship SURVIVED!\n");

        fprintf(fp, "Total Escort Ships Hit: %d\n",
                hit_e_count);

        fprintf(fp, "Battle Duration: %.2f seconds\n",
                battle_duration);
    }



      //final battle condition

    fprintf(fp, "\n\n==== FINAL BATTLEFIELD CONDITIONS ====\n\n");

    fprintf(fp, "Battleship:\n");
    fprintf(fp, "Type: %c\n", b.type);
    fprintf(fp, "Position: (%.2f, %.2f)\n",
            b.x, b.y);
    fprintf(fp, "Max Velocity: %.2f\n",
            b.maxVelocity);


    fprintf(fp, "\nEscort Ships:\n");

    for (int i = 0; i < N; i++)
    {
        fprintf(fp, "\nEscort Ship ID: %d\n",
                e[i].id);

        fprintf(fp, "Type: E_%c\n",
                e[i].type);

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

    printf("\nSimulation %d results saved successfully!\n",
           simulationNumber);
}

int battle_calculations_B1(struct Battleship b,
                           struct Escortship e[],
                           int N,
                           int iteration)
{
    FILE *fp = fopen("part_1_B_simulation_1.txt", "a");

    if (fp == NULL)
    {
        printf("Error opening Part 1-B Simulation 1 file!\n");
        return 0;
    }

    int b_sunk = 0;
    int sunk_by_id = -1;
    int hit_e_count = 0;

    float battle_duration = 0.0;

    float time_to_hit[N];

    for (int i = 0; i < N; i++)
    {
        time_to_hit[i] = 0.0;
    }


    fprintf(fp, "\n\n");
    fprintf(fp, "====================================================\n");
    fprintf(fp, "             PART 1-B SIMULATION 1\n");
    fprintf(fp, "                   ITERATION %d\n", iteration);
    fprintf(fp, "====================================================\n\n");



      // initial conditions for this iteration

    fprintf(fp, "=== INITIAL BATTLEFIELD CONDITIONS ===\n\n");

    fprintf(fp, "Battleship:\n");
    fprintf(fp, "Type: %c\n", b.type);
    fprintf(fp, "Position: (%.2f, %.2f)\n", b.x, b.y);
    fprintf(fp, "Max Velocity: %.2f\n\n", b.maxVelocity);

    fprintf(fp, "Total Escort Ships (N): %d\n\n", N);

    fprintf(fp, "----- ESCORT SHIP DETAILS -----\n");

    for (int i = 0; i < N; i++)
    {
        // Destroyed ships are not present
// in later iterations.

        if (e[i].isDestroyed)
        {
            continue;
        }

        fprintf(fp, "\nEscort Ship ID: %d\n", e[i].id);
        fprintf(fp, "Type: E_%c\n", e[i].type);

        fprintf(fp, "Position: (%.2f, %.2f)\n",
                e[i].x,
                e[i].y);

        fprintf(fp, "Minimum Velocity: %.2f\n",
                e[i].minVelocity);

        fprintf(fp, "Maximum Velocity: %.2f\n",
                e[i].maxVelocity);

        fprintf(fp, "Minimum Angle: %.2f degrees\n",
                e[i].minAngle);

        fprintf(fp, "Maximum Angle: %.2f degrees\n",
                e[i].maxAngle);
    }



       //battle calculations

    for (int i = 0; i < N; i++)
    {
        // If this E ship was destroyed in a previous
// iteration, it cannot participate again.

        if (e[i].isDestroyed)
        {
            continue;
        }


        //distance between B and E

        float dx = b.x - e[i].x;
        float dy = b.y - e[i].y;

        float distance = sqrt(dx * dx + dy * dy);


        //battleship attacks escort ship

        float B_range =
            (b.maxVelocity * b.maxVelocity) / GRAVITY;

        if (distance <= B_range)
        {
            e[i].isDestroyed = 1;

            hit_e_count++;

            float hit_time = calculateFlightTime(b.maxVelocity, 45.0);

            time_to_hit[i] = hit_time;

            if (hit_time > battle_duration)
            {
                battle_duration = hit_time;
            }
        }


        // escort ship attacks battleship
// Only an E ship which survived B's attack
// can attack B.

        if (e[i].isDestroyed)
        {
            continue;
        }


        float minAngleRad =
            e[i].minAngle * M_PI / 180.0;

        float maxAngleRad =
            e[i].maxAngle * M_PI / 180.0;


        float E_range_min =
            (e[i].minVelocity *
             e[i].minVelocity *
             sin(2 * minAngleRad)) / GRAVITY;


        float E_range_max =
            (e[i].maxVelocity *
             e[i].maxVelocity *
             sin(2 * maxAngleRad)) / GRAVITY;


        if (distance >= E_range_min &&
            distance <= E_range_max)
        {
            b_sunk = 1;

            sunk_by_id = e[i].id;

            battle_duration =
                calculateFlightTime(
                    e[i].maxVelocity,
                    e[i].maxAngle
                );

            break;
        }
    }



       //battle results

    fprintf(fp, "\n\n");
    fprintf(fp, "==== ITERATION %d RESULTS ====\n\n", iteration);


    if (b_sunk)
    {
        fprintf(fp, "STATUS: Battleship SANK!\n");

        fprintf(fp,"Sunk by Escort Ship ID: %d\n",sunk_by_id);

        fprintf(fp,"Battle Duration: %.2f seconds\n",battle_duration);

        fprintf(fp,"\nSimulation stopped because Battleship was destroyed.\n");
    }
    else
    {
        fprintf(fp, "STATUS: Battleship SURVIVED!\n");

        fprintf(fp,"Total Escort Ships Hit: %d\n",hit_e_count);

        fprintf(fp,"Battle Duration: %.2f seconds\n",battle_duration);


        if (hit_e_count > 0)
        {
            fprintf(fp,
                    "\n----- ESCORT SHIPS HIT BY B -----\n");

            for (int i = 0; i < N; i++)
            {
                if (time_to_hit[i] > 0.0)
                {
                    fprintf(fp,"\nEscort Ship ID: %d\n",e[i].id);

                    fprintf(fp,"Type: E_%c\n",e[i].type);

                    fprintf(fp,"Time to Hit: %.2f seconds\n",time_to_hit[i]);
                }
            }
        }
    }



      //final battlefield conditions

    fprintf(fp,
            "\n\n==== FINAL BATTLEFIELD CONDITIONS ====\n\n");

    fprintf(fp, "Battleship:\n");

    fprintf(fp,"Type: %c\n", b.type);

    fprintf(fp,"Position: (%.2f, %.2f)\n", b.x, b.y);

    fprintf(fp,"Max Velocity: %.2f\n",b.maxVelocity);


    fprintf(fp, "\nEscort Ships:\n");

    for (int i = 0; i < N; i++)
    {
        fprintf(fp,"\nEscort Ship ID: %d\n",e[i].id);
        fprintf(fp,"Type: E_%c\n",e[i].type);
        fprintf(fp,"Position: (%.2f, %.2f)\n", e[i].x, e[i].y);

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

    printf("\nIteration %d results saved to part_1_B_simulation_1.txt\n",
           iteration);

    return b_sunk;
}

int battle_calculations_B2(struct Battleship b,
                           struct Escortship e[],
                           int N,
                           int iteration,
                           int jammed,
                           float thetaMin)
{
    FILE *fp = fopen("part_1_B_simulation_2.txt", "a");

    if (fp == NULL)
    {
        printf("Error opening Part 1-B Simulation 2 file!\n");
        return 0;
    }

    int b_sunk = 0;
    int sunk_by_id = -1;
    int hit_e_count = 0;

    float battle_duration = 0.0;
    float time_to_hit[N];

    for (int i = 0; i < N; i++)
    {
        time_to_hit[i] = 0.0;
    }


    fprintf(fp, "\n\n");
    fprintf(fp, "====================================================\n");
    fprintf(fp, "             PART 1-B SIMULATION 2\n");
    fprintf(fp, "                   ITERATION %d\n", iteration);
    fprintf(fp, "====================================================\n\n");


      //initial conditions

    fprintf(fp, "=== INITIAL BATTLEFIELD CONDITIONS ===\n\n");

    fprintf(fp, "Battleship:\n");
    fprintf(fp, "Type: %c\n", b.type);
    fprintf(fp, "Position: (%.2f, %.2f)\n", b.x, b.y);
    fprintf(fp, "Max Velocity: %.2f\n", b.maxVelocity);

    if (jammed)
    {
        fprintf(fp, "Gun Status: JAMMED\n");
        fprintf(fp,"Allowed Vertical Angle: %.2f - 90.00 degrees\n",thetaMin);
    }
    else
    {
        fprintf(fp, "Gun Status: NORMAL\n");
        fprintf(fp,"Allowed Vertical Angle: 0.00 - 90.00 degrees\n");
    }

    fprintf(fp, "\nTotal Escort Ships (N): %d\n\n", N);

    fprintf(fp, "----- ESCORT SHIP DETAILS -----\n");

    for (int i = 0; i < N; i++)
    {
        if (e[i].isDestroyed)
        {
            continue;
        }

        fprintf(fp, "\nEscort Ship ID: %d\n", e[i].id);
        fprintf(fp, "Type: E_%c\n", e[i].type);

        fprintf(fp,"Position: (%.2f, %.2f)\n",e[i].x,e[i].y);

        fprintf(fp,"Minimum Velocity: %.2f\n",e[i].minVelocity);

        fprintf(fp,"Maximum Velocity: %.2f\n",e[i].maxVelocity);

        fprintf(fp,"Minimum Angle: %.2f degrees\n",e[i].minAngle);

        fprintf(fp,"Maximum Angle: %.2f degrees\n",e[i].maxAngle);
    }


       //battle

    for (int i = 0; i < N; i++)
    {
        // destroyed E ships cannot participate
// in later iterations.

        if (e[i].isDestroyed)
        {
            continue;
        }


        float dx = b.x - e[i].x;
        float dy = b.y - e[i].y;

        float distance = sqrt(dx * dx + dy * dy);



         // battleship attacks escort ship

        // Select a vertical firing angle.
// before jamming:
// 0 - 90 degrees
// After jamming:
// thetaMin - 90 degrees

        float firingAngle;

        if (jammed)
        {
            firingAngle = thetaMin +((float)rand() / RAND_MAX) *(90.0 - thetaMin);
        }
        else
        {
            firingAngle =((float)rand() / RAND_MAX) * 90.0;
        }


        float angleRad =
            firingAngle * M_PI / 180.0;


        // Projectile horizontal range.

        float B_range = (b.maxVelocity * b.maxVelocity *sin(2.0 * angleRad)) / GRAVITY;


        fprintf(fp,"\nB firing angle against E_%c: %.2f degrees\n",e[i].type,firingAngle);

        fprintf(fp,"Distance to E: %.2f\n",distance);

        fprintf(fp,"B Attack Range: %.2f\n",B_range);


        if (distance <= B_range)
        {
            e[i].isDestroyed = 1;

            hit_e_count++;

            float hit_time =
                calculateFlightTime(b.maxVelocity,firingAngle);

            time_to_hit[i] = hit_time;

            if (hit_time > battle_duration)
            {
                battle_duration = hit_time;
            }
        }


          //escort ship attaacks battleship

        if (e[i].isDestroyed)
        {
            continue;
        }


        float minAngleRad =
            e[i].minAngle * M_PI / 180.0;

        float maxAngleRad =
            e[i].maxAngle * M_PI / 180.0;


        float E_range_min =
            (e[i].minVelocity *
             e[i].minVelocity *
             sin(2.0 * minAngleRad)) / GRAVITY;


        float E_range_max =
            (e[i].maxVelocity *
             e[i].maxVelocity *
             sin(2.0 * maxAngleRad)) / GRAVITY;


        if (distance >= E_range_min &&
            distance <= E_range_max)
        {
            b_sunk = 1;

            sunk_by_id = e[i].id;

            battle_duration =
                calculateFlightTime(
                    e[i].maxVelocity,
                    e[i].maxAngle
                );

            break;
        }
    }



      //results

    fprintf(fp, "\n\n");
    fprintf(fp,
            "==== ITERATION %d RESULTS ====\n\n",
            iteration);


    if (b_sunk)
    {
        fprintf(fp,
                "STATUS: Battleship SANK!\n");

        fprintf(fp,
                "Sunk by Escort Ship ID: %d\n",
                sunk_by_id);

        fprintf(fp,
                "Battle Duration: %.2f seconds\n",
                battle_duration);

        fprintf(fp,
                "\nSimulation stopped because Battleship was destroyed.\n");
    }
    else
    {
        fprintf(fp,
                "STATUS: Battleship SURVIVED!\n");

        fprintf(fp,
                "Total Escort Ships Hit: %d\n",
                hit_e_count);

        if (hit_e_count > 0)
        {
            fprintf(fp,
                    "\n----- ESCORT SHIPS HIT BY B -----\n");

            for (int i = 0; i < N; i++)
            {
                if (time_to_hit[i] > 0.0)
                {
                    fprintf(fp,
                            "\nEscort Ship ID: %d\n",
                            e[i].id);

                    fprintf(fp,
                            "Type: E_%c\n",
                            e[i].type);

                    fprintf(fp,
                            "Time to Hit: %.2f seconds\n",
                            time_to_hit[i]);
                }
            }
        }

        fprintf(fp,
                "\nBattle Duration: %.2f seconds\n",
                battle_duration);
    }


      //final conditions

    fprintf(fp,
            "\n\n==== FINAL BATTLEFIELD CONDITIONS ====\n\n");

    fprintf(fp, "Battleship:\n");

    fprintf(fp,
            "Type: %c\n",
            b.type);

    fprintf(fp,
            "Position: (%.2f, %.2f)\n",
            b.x,
            b.y);

    fprintf(fp,
            "Max Velocity: %.2f\n",
            b.maxVelocity);


    fprintf(fp, "\nEscort Ships:\n");

    for (int i = 0; i < N; i++)
    {
        fprintf(fp,
                "\nEscort Ship ID: %d\n",
                e[i].id);

        fprintf(fp,
                "Type: E_%c\n",
                e[i].type);

        fprintf(fp,
                "Position: (%.2f, %.2f)\n",
                e[i].x,
                e[i].y);

        if (e[i].isDestroyed)
        {
            fprintf(fp,
                    "Status: DESTROYED\n");
        }
        else
        {
            fprintf(fp,
                    "Status: SURVIVED\n");
        }
    }


    fclose(fp);

    printf("\nIteration %d results saved to "
           "part_1_B_simulation_2.txt\n",
           iteration);

    return b_sunk;
}

int battle_calculations_C_A(struct Battleship b,
                            struct Escortship e[],
                            int N)
{
    FILE *fp = fopen("part_1_C_A.txt", "a");

    if (fp == NULL)
    {
        printf("Error opening Part 1-C A results file!\n");
        return 0;
    }

    int b_sunk = 0;
    int sunk_by_id = -1;
    int hit_e_count = 0;

    float cumulativeImpact = 0.0f;
    float battle_duration = 0.0f;

    fprintf(fp, "\n\n");
    fprintf(fp, "====================================================\n");
    fprintf(fp, "             PART 1-C - SIMULATION A\n");
    fprintf(fp, "====================================================\n\n");

     //initial battlefield conditions

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

        fprintf(fp, "Position: (%.2f, %.2f)\n",e[i].x, e[i].y);

        fprintf(fp, "Minimum Velocity: %.2f\n",e[i].minVelocity);

        fprintf(fp, "Maximum Velocity: %.2f\n",e[i].maxVelocity);

        fprintf(fp, "Minimum Angle: %.2f degrees\n",e[i].minAngle);

        fprintf(fp, "Maximum Angle: %.2f degrees\n",e[i].maxAngle);

        fprintf(fp, "Impact Power: %.2f\n",e[i].impactPower);

        fprintf(fp, "Attack Used: NO\n");
    }



      //battle conditions

    for (int i = 0; i < N; i++)
    {
        // Distance between B and E

        float dx = b.x - e[i].x;
        float dy = b.y - e[i].y;

        float distance = sqrt(dx * dx + dy * dy);



         //battleship attack escort ship

        // ==================================================
// E ATTACKS B FIRST
// ==================================================

if (!e[i].isDestroyed &&
    e[i].hasAttacked == 0)
{
    float minAngleRad =
        e[i].minAngle * M_PI / 180.0;

    float maxAngleRad =
        e[i].maxAngle * M_PI / 180.0;

    float E_range_min =
        (e[i].minVelocity *
         e[i].minVelocity *
         sin(2.0 * minAngleRad)) /
        GRAVITY;

    float E_range_max =
        (e[i].maxVelocity *
         e[i].maxVelocity *
         sin(2.0 * maxAngleRad)) /
        GRAVITY;

    if (distance >= E_range_min &&
        distance <= E_range_max)
    {
        e[i].hasAttacked = 1;

        cumulativeImpact +=
            e[i].impactPower;

        fprintf(fp,
                "\nEscort Ship ID: %d attacked B\n",
                e[i].id);

        fprintf(fp,
                "Type: E_%c\n",
                e[i].type);

        fprintf(fp,
                "Impact Power: %.2f\n",
                e[i].impactPower);

        fprintf(fp,
                "Cumulative Impact: %.2f\n",
                cumulativeImpact);

        fprintf(fp,
                "Cumulative Damage: %.2f%%\n",
                cumulativeImpact * 100.0f);

        if (cumulativeImpact >= 1.0f)
        {
            b_sunk = 1;
            sunk_by_id = e[i].id;

            break;
        }
    }
}

// ==================================================
// B ATTACKS E
// ==================================================

if (!e[i].isDestroyed)
{
    float B_range =
        (b.maxVelocity * b.maxVelocity) /
        GRAVITY;

    if (distance <= B_range)
    {
        e[i].isDestroyed = 1;
        hit_e_count++;

        float hit_time =
            calculateFlightTime(
                b.maxVelocity,
                45.0f);

        if (hit_time > battle_duration)
        {
            battle_duration = hit_time;
        }

        fprintf(fp,
                "\nB destroyed Escort Ship ID: %d\n",
                e[i].id);

        fprintf(fp,
                "Time to Hit: %.2f seconds\n",
                hit_time);
    }
}

}

      //simulation results

    fprintf(fp, "\n\n==== SIMULATION RESULTS ====\n\n");

    if (b_sunk)
    {
        fprintf(fp, "STATUS: Battleship SANK!\n");

        fprintf(fp,
                "Sunk by Escort Ship ID: %d\n",
                sunk_by_id);

        fprintf(fp,
                "Cumulative Impact: %.2f\n",
                cumulativeImpact);

        fprintf(fp,
                "Cumulative Damage: %.2f%%\n",
                cumulativeImpact * 100.0f);

        fprintf(fp,
                "Battle Duration: %.2f seconds\n",
                battle_duration);
    }
    else
    {
        fprintf(fp, "STATUS: Battleship SURVIVED!\n");

        fprintf(fp,
                "Total Escort Ships Hit: %d\n",
                hit_e_count);

        fprintf(fp,
                "Cumulative Impact: %.2f\n",
                cumulativeImpact);

        fprintf(fp,
                "Cumulative Damage: %.2f%%\n",
                cumulativeImpact * 100.0f);

        fprintf(fp,
                "Battle Duration: %.2f seconds\n",
                battle_duration);
    }


     //final conditions

    fprintf(fp,
            "\n\n==== FINAL BATTLEFIELD CONDITIONS ====\n\n");

    fprintf(fp, "Battleship:\n");
    fprintf(fp, "Type: %c\n", b.type);

    fprintf(fp,
            "Position: (%.2f, %.2f)\n",
            b.x, b.y);

    fprintf(fp,
            "Max Velocity: %.2f\n",
            b.maxVelocity);

    fprintf(fp,
            "Cumulative Impact: %.2f\n",
            cumulativeImpact);
    fprintf(fp,
            "Cumulative Damage: %.2f%%\n",
            cumulativeImpact * 100.0f);


    fprintf(fp, "\nEscort Ships:\n");

    for (int i = 0; i < N; i++)
    {
        fprintf(fp,
                "\nEscort Ship ID: %d\n",
                e[i].id);

        fprintf(fp,
                "Type: E_%c\n",
                e[i].type);

        fprintf(fp,
                "Position: (%.2f, %.2f)\n",
                e[i].x,
                e[i].y);

        fprintf(fp,
                "Impact Power: %.2f\n",
                e[i].impactPower);

        if (e[i].isDestroyed)
        {
            fprintf(fp, "Status: DESTROYED\n");
        }
        else
        {
            fprintf(fp, "Status: SURVIVED\n");
        }

        if (e[i].hasAttacked)
        {
            fprintf(fp, "Attack Used: YES\n");
        }
        else
        {
            fprintf(fp, "Attack Used: NO\n");
        }
    }


    fclose(fp);

    printf("\nPart 1-C A results saved to part_1_C_A.txt\n");
    printf("Cumulative Impact: %.2f\n", cumulativeImpact);
    printf("Cumulative Damage: %.2f%%\n", cumulativeImpact * 100.0f);


    return b_sunk;
}

int battle_calculations_C_B1(struct Battleship b,struct Escortship e[],int N,int iteration,float *cumulativeImpact)
{
    FILE *fp = fopen("part_1_C_B_simulation_1.txt", "a");

    if (fp == NULL)
    {
        printf("Error opening Part 1-C Simulation 1 file!\n");
        return 0;
    }

    int b_sunk = 0;
    int sunk_by_id = -1;
    int hit_e_count = 0;

    float battle_duration = 0.0f;

    fprintf(fp, "\n\n");
    fprintf(fp, "====================================================\n");
    fprintf(fp, "       PART 1-C - PART B SIMULATION 1 - ITERATION %d\n",
            iteration);
    fprintf(fp, "====================================================\n\n");

     //initial conditions

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
        fprintf(fp, "Position: (%.2f, %.2f)\n",e[i].x, e[i].y);
        fprintf(fp, "Minimum Velocity: %.2f\n",e[i].minVelocity);
        fprintf(fp, "Maximum Velocity: %.2f\n",e[i].maxVelocity);
        fprintf(fp, "Minimum Angle: %.2f degrees\n",e[i].minAngle);
        fprintf(fp, "Maximum Angle: %.2f degrees\n",e[i].maxAngle);
        fprintf(fp, "Impact Power: %.2f\n",e[i].impactPower);

        if (e[i].isDestroyed)
            fprintf(fp, "Status: DESTROYED\n");
        else
            fprintf(fp, "Status: ACTIVE\n");

        if (e[i].hasAttacked)
            fprintf(fp, "Attack Used: YES\n");
        else
            fprintf(fp, "Attack Used: NO\n");
    }

    // Battle calculations

    for (int i = 0; i < N; i++)
    {
        // already destroyed escort ships cannot participate
// in later iterations.
        if (e[i].isDestroyed)
        {
            continue;
        }

        float dx = b.x - e[i].x;
        float dy = b.y - e[i].y;

        float distance =
            sqrt(dx * dx + dy * dy);

        float firingAngle =
            ((float)rand() / RAND_MAX) * 90.0f;

        float angleRad =
            firingAngle * M_PI / 180.0f;

        float B_range =
            (b.maxVelocity *
             b.maxVelocity *
             sin(2.0f * angleRad)) / GRAVITY;

        fprintf(fp, "\n----------------------------------------\n");
        fprintf(fp, "Escort Ship ID: %d\n", e[i].id);
        fprintf(fp, "Distance: %.2f\n", distance);
        fprintf(fp, "B Firing Angle: %.2f degrees\n",
                firingAngle);
        fprintf(fp, "B Attack Range: %.2f\n",
                B_range);

        // battlesip attacks escortship

        if (distance <= B_range)
        {
            e[i].isDestroyed = 1;
            hit_e_count++;

            float hit_time = calculateFlightTime(b.maxVelocity,firingAngle);

            if (hit_time > battle_duration)
            {
                battle_duration = hit_time;
            }

            fprintf(fp,"B destroyed Escort Ship ID: %d\n",e[i].id);

            fprintf(fp,"Time to Hit: %.2f seconds\n",hit_time);
        }

        // escort ship attacks battleship.
// each escortship can attack only once.

        if (e[i].hasAttacked)
        {
            fprintf(fp,"E attack skipped - attack already used.\n");
            continue;
        }

        float minAngleRad =
            e[i].minAngle * M_PI / 180.0f;

        float maxAngleRad =
            e[i].maxAngle * M_PI / 180.0f;

        float E_range_min = (e[i].minVelocity * e[i].minVelocity * sin(2.0f * minAngleRad)) / GRAVITY;

        float E_range_max = (e[i].maxVelocity * e[i].maxVelocity * sin(2.0f * maxAngleRad)) / GRAVITY;

        fprintf(fp,"E Attack Range: %.2f - %.2f\n",E_range_min,E_range_max);

        if (distance >= E_range_min &&
            distance <= E_range_max)
        {
            e[i].hasAttacked = 1;

            *cumulativeImpact +=
                e[i].impactPower;

            float hit_time = calculateFlightTime(e[i].maxVelocity,e[i].maxAngle);

            if (hit_time > battle_duration)
            {
                battle_duration = hit_time;
            }

            fprintf(fp,"\nEscort Ship ID %d attacked B\n",e[i].id);

            fprintf(fp,"Type: E_%c\n",e[i].type);

            fprintf(fp,"Impact Power: %.2f\n",e[i].impactPower);

            fprintf(fp,"Time to Hit: %.2f seconds\n",hit_time);

            fprintf(fp, "Cumulative Impact: %.2f\n",*cumulativeImpact);

            // battleship is destroyed when cumulative
// impact reaches 100%.
            if (*cumulativeImpact >= 1.0f)
            {
                b_sunk = 1;
                sunk_by_id = e[i].id;

                fprintf(fp,"\nCumulative impact reached 100%%.\n");

                break;
            }
        }
    }

    //results

    fprintf(fp, "\n\n==== ITERATION %d RESULTS ====\n\n",
            iteration);

    if (b_sunk)
    {
        fprintf(fp, "STATUS: Battleship SANK!\n");
        fprintf(fp,"Sunk by Escort Ship ID: %d\n",sunk_by_id);

        fprintf(fp,"Cumulative Impact: %.2f\n", *cumulativeImpact);

        fprintf(fp,"Cumulative Damage: %.2f%%\n", (*cumulativeImpact) * 100.0f);

        fprintf(fp,"Battle Duration: %.2f seconds\n", battle_duration);
    }
    else
    {
        fprintf(fp,"STATUS: Battleship SURVIVED!\n");

        fprintf(fp,"Escort Ships Hit This Iteration: %d\n", hit_e_count);

        fprintf(fp,"Cumulative Impact: %.2f\n", *cumulativeImpact);

        fprintf(fp,"Cumulative Damage: %.2f%%\n",(*cumulativeImpact) * 100.0f);

        fprintf(fp,"Battle Duration: %.2f seconds\n",battle_duration);
    }

    //final battlefield conditions

    fprintf(fp,
            "\n\n==== FINAL BATTLEFIELD CONDITIONS ====\n\n");

    fprintf(fp, "Battleship:\n");
    fprintf(fp, "Type: %c\n", b.type);
    fprintf(fp,"Position: (%.2f, %.2f)\n",b.x, b.y);

    fprintf(fp,"Max Velocity: %.2f\n",b.maxVelocity);

    fprintf(fp,"Cumulative Impact: %.2f\n",*cumulativeImpact);

    fprintf(fp, "\nEscort Ships:\n");

    for (int i = 0; i < N; i++)
    {
        fprintf(fp,"\nEscort Ship ID: %d\n",e[i].id);

        fprintf(fp,"Type: E_%c\n",e[i].type);

        fprintf(fp,"Position: (%.2f, %.2f)\n",e[i].x,e[i].y);

        fprintf(fp,"Impact Power: %.2f\n",e[i].impactPower);

        if (e[i].isDestroyed)
            fprintf(fp, "Status: DESTROYED\n");
        else
            fprintf(fp, "Status: SURVIVED\n");

        if (e[i].hasAttacked)
            fprintf(fp, "Attack Used: YES\n");
        else
            fprintf(fp, "Attack Used: NO\n");
    }

    fclose(fp);

    printf("\nIteration %d results saved to "
           "part_1_C_B_simulation_1.txt\n",
           iteration);

    return b_sunk;
}

int battle_calculations_C_B2(struct Battleship b,struct Escortship e[],int N, int iteration, int jammed, float thetaMin, float *cumulativeImpact)
{
    FILE *fp = fopen("part_1_C_B_simulation_2.txt", "a");

    if (fp == NULL)
    {
        printf("Error opening Part 1-C Simulation 2 file!\n");
        return 0;
    }

    int b_sunk = 0;
    int sunk_by_id = -1;
    int hit_e_count = 0;

    float battle_duration = 0.0f;

    fprintf(fp, "\n\n");
    fprintf(fp, "====================================================\n");
    fprintf(fp, "       PART 1-C - PART B SIMULATION 2 - ITERATION %d\n",
            iteration);
    fprintf(fp, "====================================================\n\n");

    // Initial conditions

    fprintf(fp,
            "=== INITIAL BATTLEFIELD CONDITIONS ===\n\n");

    fprintf(fp, "Battleship:\n");
    fprintf(fp, "Type: %c\n", b.type);
    fprintf(fp,"Position: (%.2f, %.2f)\n",b.x, b.y);

    fprintf(fp,"Max Velocity: %.2f\n",b.maxVelocity);

    if (jammed)
    {
        fprintf(fp,"Gun Status: JAMMED\n");

        fprintf(fp,"Allowed Vertical Angle: %.2f - 90.00 degrees\n",thetaMin);
    }
    else
    {
        fprintf(fp,"Gun Status: NORMAL\n");

        fprintf(fp,"Allowed Vertical Angle: 0.00 - 90.00 degrees\n");
    }

    fprintf(fp,"\nTotal Escort Ships (N): %d\n\n",N);

    fprintf(fp,"----- ESCORT SHIP DETAILS -----\n");

    for (int i = 0; i < N; i++)
    {
        fprintf(fp,"\nEscort Ship ID: %d\n",e[i].id);

        fprintf(fp,"Type: E_%c\n",e[i].type);

        fprintf(fp,"Position: (%.2f, %.2f)\n",e[i].x,e[i].y);

        fprintf(fp,"Minimum Velocity: %.2f\n",e[i].minVelocity);

        fprintf(fp,"Maximum Velocity: %.2f\n",e[i].maxVelocity);

        fprintf(fp,"Minimum Angle: %.2f degrees\n",e[i].minAngle);

        fprintf(fp,"Maximum Angle: %.2f degrees\n",e[i].maxAngle);

        fprintf(fp,"Impact Power: %.2f\n",e[i].impactPower);

        if (e[i].isDestroyed)
            fprintf(fp, "Status: DESTROYED\n");
        else
            fprintf(fp, "Status: ACTIVE\n");

        if (e[i].hasAttacked)
            fprintf(fp, "Attack Used: YES\n");
        else
            fprintf(fp, "Attack Used: NO\n");
    }

    //battle calculations

    for (int i = 0; i < N; i++)
    {
        if (e[i].isDestroyed)
        {
            continue;
        }

        float dx = b.x - e[i].x;
        float dy = b.y - e[i].y;

        float distance =
            sqrt(dx * dx + dy * dy);

        // Select battleship firing angle.
// normal:
// 0 - 90 degrees
// jammed:
// thetaMin - 90 degrees

        float firingAngle;

        if (jammed)
        {
            firingAngle = thetaMin + ((float)rand() / RAND_MAX) * (90.0f - thetaMin);
        }
        else
        {
            firingAngle =
                ((float)rand() / RAND_MAX) *
                90.0f;
        }

        float angleRad =
            firingAngle * M_PI / 180.0f;

        float B_range =
            (b.maxVelocity *
             b.maxVelocity *
             sin(2.0f * angleRad)) /
            GRAVITY;

        fprintf(fp,
                "\n----------------------------------------\n");

        fprintf(fp,
                "Escort Ship ID: %d\n",
                e[i].id);

        fprintf(fp,
                "Distance: %.2f\n",
                distance);

        fprintf(fp,
                "B Firing Angle: %.2f degrees\n",
                firingAngle);

        fprintf(fp,
                "B Attack Range: %.2f\n",
                B_range);

        // B attacks E.

        if (distance <= B_range)
        {
            e[i].isDestroyed = 1;
            hit_e_count++;

            float hit_time =
                calculateFlightTime(
                    b.maxVelocity,
                    firingAngle);

            if (hit_time > battle_duration)
            {
                battle_duration = hit_time;
            }

            fprintf(fp,
                    "B destroyed Escort Ship ID: %d\n",
                    e[i].id);

            fprintf(fp,
                    "Time to Hit: %.2f seconds\n",
                    hit_time);
        }

        // E can attack only once.

        if (e[i].hasAttacked)
        {
            fprintf(fp,
                    "E attack skipped - attack already used.\n");

            continue;
        }

        float minAngleRad =
            e[i].minAngle * M_PI / 180.0f;

        float maxAngleRad =
            e[i].maxAngle * M_PI / 180.0f;

        float E_range_min =
            (e[i].minVelocity *
             e[i].minVelocity *
             sin(2.0f * minAngleRad)) /
            GRAVITY;

        float E_range_max =
            (e[i].maxVelocity *
             e[i].maxVelocity *
             sin(2.0f * maxAngleRad)) /
            GRAVITY;

        fprintf(fp,
                "E Attack Range: %.2f - %.2f\n",
                E_range_min,
                E_range_max);
        printf("E%d | Distance = %.2f | E Range = %.2f - %.2f | Impact = %.2f\n", e[i].id,distance, E_range_min, E_range_max, e[i].impactPower);

        // E attacks B if B is inside
// E's attack range.

        if (distance >= E_range_min &&
            distance <= E_range_max)
        {
            e[i].hasAttacked = 1;

            *cumulativeImpact += e[i].impactPower;

            printf(">>> E%d ATTACKED B! Impact = %.2f\n",e[i].id,e[i].impactPower);

    printf(">>> Cumulative Impact = %.2f\n", *cumulativeImpact);

            float hit_time =
                calculateFlightTime(
                    e[i].maxVelocity,
                    e[i].maxAngle);

            if (hit_time > battle_duration)
            {
                battle_duration = hit_time;
            }

            fprintf(fp,
                    "\nEscort Ship ID %d attacked B\n",
                    e[i].id);

            fprintf(fp,
                    "Type: E_%c\n",
                    e[i].type);

            fprintf(fp,
                    "Impact Power: %.2f\n",
                    e[i].impactPower);

            fprintf(fp,
                    "Time to Hit: %.2f seconds\n",
                    hit_time);

            fprintf(fp,
                    "Cumulative Impact: %.2f\n",
                    *cumulativeImpact);

            // B destroyed when cumulative
// impact reaches 100%.

            if (*cumulativeImpact >= 1.0f)
            {
                b_sunk = 1;
                sunk_by_id = e[i].id;

                fprintf(fp,
                        "\nCumulative impact reached 100%%.\n");

                break;
            }
        }
    }

    // Results

    fprintf(fp,
            "\n\n==== ITERATION %d RESULTS ====\n\n",
            iteration);

    if (b_sunk)
    {
        fprintf(fp,
                "STATUS: Battleship SANK!\n");

        fprintf(fp,
                "Sunk by Escort Ship ID: %d\n",
                sunk_by_id);

        fprintf(fp,
                "Cumulative Impact: %.2f\n",
                *cumulativeImpact);

        fprintf(fp,
                "Cumulative Damage: %.2f%%\n",
                (*cumulativeImpact) * 100.0f);

        fprintf(fp,
                "Battle Duration: %.2f seconds\n",
                battle_duration);

        fprintf(fp,
                "\nSimulation stopped because "
                "Battleship was destroyed.\n");
    }
    else
    {
        fprintf(fp,
                "STATUS: Battleship SURVIVED!\n");

        fprintf(fp,
                "Escort Ships Hit This Iteration: %d\n",
                hit_e_count);

        fprintf(fp,
                "Cumulative Impact: %.2f\n",
                *cumulativeImpact);

        fprintf(fp,
                "Cumulative Damage: %.2f%%\n",
                (*cumulativeImpact) * 100.0f);

        fprintf(fp,
                "Battle Duration: %.2f seconds\n",
                battle_duration);
    }

    // Final battlefield

    fprintf(fp,
            "\n\n==== FINAL BATTLEFIELD CONDITIONS ====\n\n");

    fprintf(fp, "Battleship:\n");

    fprintf(fp,
            "Type: %c\n",
            b.type);

    fprintf(fp,
            "Position: (%.2f, %.2f)\n",
            b.x,
            b.y);

    fprintf(fp,
            "Max Velocity: %.2f\n",
            b.maxVelocity);

    fprintf(fp,
            "Cumulative Impact: %.2f\n",
            *cumulativeImpact);

    fprintf(fp, "\nEscort Ships:\n");

    for (int i = 0; i < N; i++)
    {
        fprintf(fp,
                "\nEscort Ship ID: %d\n",
                e[i].id);

        fprintf(fp,
                "Type: E_%c\n",
                e[i].type);

        fprintf(fp,
                "Position: (%.2f, %.2f)\n",
                e[i].x,
                e[i].y);

        fprintf(fp,
                "Impact Power: %.2f\n",
                e[i].impactPower);

        if (e[i].isDestroyed)
            fprintf(fp,
                    "Status: DESTROYED\n");
        else
            fprintf(fp,
                    "Status: SURVIVED\n");

        if (e[i].hasAttacked)
            fprintf(fp,
                    "Attack Used: YES\n");
        else
            fprintf(fp,
                    "Attack Used: NO\n");
    }

    fclose(fp);

    printf("\nIteration %d results saved to "
           "part_1_C_B_simulation_2.txt\n",
           iteration);

    return b_sunk;
}

// ==========================================================
// PART 2-A
// ==========================================================

// Get distance between B and an E ship
float p2a_distance(struct Battleship b, struct Escortship e)
{
    return sqrt(
        pow(b.x - e.x, 2) +
        pow(b.y - e.y, 2)
    );
}

// Get the maximum attack range of B
float p2a_b_range(struct Battleship b)
{
    return (b.maxVelocity * b.maxVelocity) / GRAVITY;
}

// Sort E ships using our custom attack strategy
void p2a_create_attack_order(
    struct Battleship b,
    struct Escortship e[],
    int N,
    int order[],
    int useImpactPower
)
{
    int count = 0;

    // Find E ships that are inside B range
    for (int i = 0; i < N; i++)
    {
        if (!e[i].isDestroyed)
        {
            float dist = p2a_distance(b, e[i]);
            float range = p2a_b_range(b);

            if (dist <= range)
            {
                order[count] = i;
                count++;
            }
        }
    }

    // Sort the attack order
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            int first = order[i];
            int second = order[j];

            float d1 = p2a_distance(b, e[first]);
            float d2 = p2a_distance(b, e[second]);

            int swapNeeded = 0;

            if (useImpactPower)
            {
                // Higher impact ship gets priority
                if (e[first].impactPower < e[second].impactPower)
                {
                    swapNeeded = 1;
                }
                else if (
                    e[first].impactPower ==
                    e[second].impactPower
                )
                {
                    // If same impact, attack closer ship first
                    if (d1 > d2)
                    {
                        swapNeeded = 1;
                    }
                }
            }
            else
            {
                // Attack closer ship first
                if (d1 > d2)
                {
                    swapNeeded = 1;
                }
            }

            if (swapNeeded)
            {
                int temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }
}


// ==========================================================
// PART 2-A - PART 1-A / PART 1-C A
// ==========================================================

void part_2_A_battle(
    struct Battleship b,
    struct Escortship e[],
    int N,
    float TB,
    int useImpactPower
)
{
    FILE *fp;

    if (useImpactPower)
    {
        fp = fopen("part_2_A_C.txt", "w");
    }
    else
    {
        fp = fopen("part_2_A.txt", "w");
    }

    if (fp == NULL)
    {
        printf("Error opening Part 2-A result file!\n");
        return;
    }

    int order[N];
    int attackCount = 0;
    int b_sunk = 0;
    int hit_e_count = 0;

    float cumulativeImpact = 0.0f;
    float currentTime = 0.0f;

    // Create attack order
    p2a_create_attack_order(
        b,
        e,
        N,
        order,
        useImpactPower
    );

    for (int i = 0; i < N; i++)
    {
        if (!e[i].isDestroyed)
        {
            float dist = p2a_distance(b, e[i]);

            if (dist <= p2a_b_range(b))
            {
                attackCount++;
            }
        }
    }

    // Save initial conditions
    fprintf(fp, "====================================================\n");

    if (useImpactPower)
    {
        fprintf(fp, "             PART 2-A - PART 1-C A\n");
    }
    else
    {
        fprintf(fp, "             PART 2-A - PART 1-A\n");
    }

    fprintf(fp, "====================================================\n\n");

    fprintf(fp, "=== INITIAL BATTLEFIELD CONDITIONS ===\n\n");

    fprintf(
        fp,
        "Battleship Type: %c\n",
        b.type
    );

    fprintf(
        fp,
        "Battleship Position: (%.2f, %.2f)\n",
        b.x,
        b.y
    );

    fprintf(
        fp,
        "Battleship Max Velocity: %.2f\n",
        b.maxVelocity
    );

    fprintf(
        fp,
        "Total Escort Ships: %d\n",
        N
    );

    fprintf(
        fp,
        "Time Between B Firings: %.2f seconds\n\n",
        TB
    );

    fprintf(fp, "----- ESCORT SHIPS -----\n");

    for (int i = 0; i < N; i++)
    {
        fprintf(
            fp,
            "ID: %d | Type: E_%c | Position: (%.2f, %.2f)\n",
            e[i].id,
            e[i].type,
            e[i].x,
            e[i].y
        );
    }

    fprintf(fp, "\n----- B ATTACK ORDER -----\n");

    if (attackCount == 0)
    {
        fprintf(
            fp,
            "No E ships are inside B attack range.\n"
        );
    }

    for (int i = 0; i < attackCount; i++)
    {
        int index = order[i];

        fprintf(
            fp,
            "%d. E Ship ID %d (Type E_%c)\n",
            i + 1,
            e[index].id,
            e[index].type
        );
    }

    fprintf(fp, "\n----- ATTACK RESULTS -----\n");

    // B attacks E ships in the selected order
    for (int i = 0; i < attackCount; i++)
    {
        int index = order[i];

        if (e[index].isDestroyed)
        {
            continue;
        }

        currentTime += TB;

        fprintf(
            fp,
            "\nTime: %.2f seconds\n",
            currentTime
        );

        fprintf(
            fp,
            "B attacks E Ship ID %d\n",
            e[index].id
        );

        // B destroys E with one attack
        e[index].isDestroyed = 1;
        hit_e_count++;

        fprintf(
            fp,
            "E Ship ID %d DESTROYED\n",
            e[index].id
        );
    }

    // E ships attack B
    for (int i = 0; i < N; i++)
    {
        if (e[i].isDestroyed)
        {
            continue;
        }

        float dist = p2a_distance(b, e[i]);

        float R_E_min =
            (
                e[i].minVelocity *
                e[i].minVelocity *
                sin(
                    2 *
                    e[i].minAngle *
                    M_PI / 180.0
                )
            ) / GRAVITY;

        float R_E_max =
            (
                e[i].maxVelocity *
                e[i].maxVelocity *
                sin(
                    2 *
                    e[i].maxAngle *
                    M_PI / 180.0
                )
            ) / GRAVITY;

        if (
            dist >= R_E_min &&
            dist <= R_E_max
        )
        {
            if (useImpactPower)
            {
                cumulativeImpact += e[i].impactPower;

                fprintf(
                    fp,
                    "E Ship ID %d hits B\n",
                    e[i].id
                );

                fprintf(
                    fp,
                    "Impact Power: %.2f\n",
                    e[i].impactPower
                );

                fprintf(
                    fp,
                    "Cumulative Impact: %.2f\n",
                    cumulativeImpact
                );

                if (cumulativeImpact >= 1.0f)
                {
                    b_sunk = 1;

                    fprintf(
                        fp,
                        "BATTLESHIP DESTROYED\n"
                    );

                    break;
                }
            }
            else
            {
                b_sunk = 1;

                fprintf(
                    fp,
                    "E Ship ID %d hits B\n",
                    e[i].id
                );

                fprintf(
                    fp,
                    "BATTLESHIP DESTROYED\n"
                );

                break;
            }
        }
    }

    // Save final result
    fprintf(
        fp,
        "\n\n==== FINAL RESULTS ====\n"
    );

    if (b_sunk)
    {
        fprintf(
            fp,
            "Battleship Status: DESTROYED\n"
        );
    }
    else
    {
        fprintf(
            fp,
            "Battleship Status: SURVIVED\n"
        );
    }

    fprintf(
        fp,
        "Total E Ships Destroyed: %d\n",
        hit_e_count
    );

    if (useImpactPower)
    {
        fprintf(
            fp,
            "Cumulative Impact on B: %.2f\n",
            cumulativeImpact
        );
    }

    fprintf(
        fp,
        "\n----- FINAL ESCORT SHIP STATUS -----\n"
    );

    for (int i = 0; i < N; i++)
    {
        fprintf(
            fp,
            "E Ship ID %d: %s\n",
            e[i].id,
            e[i].isDestroyed ?
            "DESTROYED" :
            "SURVIVED"
        );
    }

    fclose(fp);

    if (useImpactPower)
    {
        printf(
            "\nPart 2-A C results saved to "
            "'part_2_A_C.txt'\n"
        );
    }
    else
    {
        printf(
            "\nPart 2-A results saved to "
            "'part_2_A.txt'\n"
        );
    }
}


// ==========================================================
// PART 2-A - PART 1-B
// ==========================================================

void part_2_A_battle_B(
    struct Battleship b,
    struct Escortship e[],
    int N,
    int k,
    float pathX[],
    float pathY[],
    float TB,
    int simulationType,
    int t,
    float thetaMin,
    int useImpactPower
)
{
    FILE *fp;

    if (useImpactPower)
    {
        if (simulationType == 1)
        {
            fp = fopen(
                "part_2_A_C_B1.txt",
                "w"
            );
        }
        else
        {
            fp = fopen(
                "part_2_A_C_B2.txt",
                "w"
            );
        }
    }
    else
    {
        if (simulationType == 1)
        {
            fp = fopen(
                "part_2_A_B1.txt",
                "w"
            );
        }
        else
        {
            fp = fopen(
                "part_2_A_B2.txt",
                "w"
            );
        }
    }

    if (fp == NULL)
    {
        printf("Error opening Part 2-A file!\n");
        return;
    }

    int b_sunk = 0;

    float cumulativeImpact = 0.0f;
    float currentTime = 0.0f;

    fprintf(
        fp,
        "====================================================\n"
    );

    if (useImpactPower)
    {
        if (simulationType == 1)
        {
            fprintf(
                fp,
                "          PART 2-A - PART 1-C B1\n"
            );
        }
        else
        {
            fprintf(
                fp,
                "          PART 2-A - PART 1-C B2\n"
            );
        }
    }
    else
    {
        if (simulationType == 1)
        {
            fprintf(
                fp,
                "          PART 2-A - PART 1-B B1\n"
            );
        }
        else
        {
            fprintf(
                fp,
                "          PART 2-A - PART 1-B B2\n"
            );
        }
    }

    fprintf(
        fp,
        "====================================================\n\n"
    );

    fprintf(
        fp,
        "Time Between B Firings: %.2f seconds\n",
        TB
    );

    if (simulationType == 2)
    {
        fprintf(
            fp,
            "Jam Starts After Iteration: %d\n",
            t
        );

        fprintf(
            fp,
            "Minimum Angle: %.2f degrees\n",
            thetaMin
        );
    }

    // Run each B movement point
    for (int iteration = 0; iteration < k; iteration++)
    {
        b.x = pathX[iteration];
        b.y = pathY[iteration];

        fprintf(
            fp,
            "\n\n====================================================\n"
        );

        fprintf(
            fp,
            "ITERATION %d\n",
            iteration + 1
        );

        fprintf(
            fp,
            "B Position: (%.2f, %.2f)\n",
            b.x,
            b.y
        );

        fprintf(
            fp,
            "====================================================\n"
        );

        int order[N];
        int attackCount = 0;

        // Find attack order for this position
        p2a_create_attack_order(b,e,N,order,useImpactPower);

        for (int i = 0; i < N; i++)
        {
            if (!e[i].isDestroyed)
            {
                float dist = p2a_distance(b, e[i]);

                float range;

                if (simulationType == 2 &&
                    iteration + 1 > t)
                {
                    float angle = thetaMin + (rand() / (float)RAND_MAX) * (90.0f - thetaMin);

                    range = (b.maxVelocity * b.maxVelocity * sin(2 * angle * M_PI / 180.0)) / GRAVITY;
                }
                else
                {
                    range = p2a_b_range(b);
                }

                if (dist <= range)
                {
                    attackCount++;
                }
            }
        }

        fprintf(fp,"\n----- B ATTACK ORDER -----\n");

        for (int i = 0; i < attackCount; i++)
        {
            int index = order[i];

            fprintf(fp,"%d. E Ship ID %d (Type E_%c)\n",i + 1,e[index].id, e[index].type);
        }

        if (attackCount == 0)
        {
            fprintf(fp,"No E ships are inside B attack range.\n");
        }

        // B attacks in the selected order
        for (int i = 0; i < attackCount; i++)
        {
            int index = order[i];

            if (e[index].isDestroyed)
            {
                continue;
            }

            currentTime += TB;

            fprintf(fp,"\nTime: %.2f seconds\n",currentTime);

            fprintf(fp,"B attacks E Ship ID %d\n",e[index].id);

            e[index].isDestroyed = 1;

            fprintf(fp,"E Ship ID %d DESTROYED\n",e[index].id);
        }

        // Remaining E ships can attack B
        for (int i = 0; i < N; i++)
        {
            if (e[i].isDestroyed)
            {
                continue;
            }

            if (e[i].hasAttacked)
            {
                continue;
            }

            float dist = p2a_distance(b, e[i]);

            float R_E_min = (e[i].minVelocity * e[i].minVelocity * sin(2 * e[i].minAngle * M_PI / 180.0)) / GRAVITY;

            float R_E_max = (e[i].maxVelocity * e[i].maxVelocity * sin( 2 * e[i].maxAngle * M_PI / 180.0)) / GRAVITY;

            if (dist >= R_E_min &&
                dist <= R_E_max
            )
            {
                e[i].hasAttacked = 1;

                fprintf(fp,"E Ship ID %d attacks B\n",e[i].id);

                if (useImpactPower)
                {
                    cumulativeImpact +=
                        e[i].impactPower;

                    fprintf(fp,"Impact Power: %.2f\n", e[i].impactPower);

                    fprintf(fp,"Cumulative Impact: %.2f\n",cumulativeImpact);

                    if (cumulativeImpact >= 1.0f)
                    {
                        b_sunk = 1;

                        fprintf(fp,"BATTLESHIP DESTROYED\n");

                        break;
                    }
                }
                else
                {
                    b_sunk = 1;

                    fprintf(fp,"BATTLESHIP DESTROYED\n");

                    break;
                }
            }
        }

        if (b_sunk)
        {
            break;
        }
    }

    fprintf(fp,"\n\n================ FINAL RESULTS ================\n");

    if (b_sunk)
    {
        fprintf(fp,"Battleship Status: DESTROYED\n");
    }
    else
    {
        fprintf(fp,"Battleship Status: SURVIVED\n");
    }

    if (useImpactPower)
    {
        fprintf(fp,"Cumulative Impact: %.2f\n",cumulativeImpact);
    }

    fprintf(fp,"\n----- FINAL ESCORT STATUS -----\n");

    for (int i = 0; i < N; i++)
    {
        fprintf(fp,"E Ship ID %d: %s\n",e[i].id,e[i].isDestroyed ? "DESTROYED" :"SURVIVED");
    }

    fclose(fp);

    printf("\nPart 2-A simulation results saved.\n");
}


// ==========================================================
// PART 2-B
// ==========================================================

// Get TE value for an escort ship type.
// The assignment specifies four escort type intervals.
// The current project also has type E, so E uses the fourth interval.
float p2b_get_TE(char type, float TE_A, float TE_B, float TE_C, float TE_D)
{
    switch (type)
    {
        case 'A': return TE_A;
        case 'B': return TE_B;
        case 'C': return TE_C;
        case 'D': return TE_D;
        case 'E': return TE_D;
        default: return TE_D;
    }
}

// Create attack order using the ships currently inside B range.
int p2b_create_attack_order(
    struct Battleship b,
    struct Escortship e[],
    int N,
    int order[],
    float range,
    int useImpactPower
)
{
    int count = 0;

    for (int i = 0; i < N; i++)
    {
        if (!e[i].isDestroyed && p2a_distance(b, e[i]) <= range)
        {
            order[count] = i;
            count++;
        }
    }

    // Custom strategy: protect B by attacking the closest E first.
    // For Part 1-C, higher impact ships are given priority.
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            int first = order[i];
            int second = order[j];
            int swapNeeded = 0;

            float d1 = p2a_distance(b, e[first]);
            float d2 = p2a_distance(b, e[second]);

            if (useImpactPower)
            {
                if (e[first].impactPower < e[second].impactPower)
                {
                    swapNeeded = 1;
                }
                else if (e[first].impactPower == e[second].impactPower && d1 > d2)
                {
                    swapNeeded = 1;
                }
            }
            else if (d1 > d2)
            {
                swapNeeded = 1;
            }

            if (swapNeeded)
            {
                int temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }

    return count;
}

// Check whether an E ship can attack B.
int p2b_can_E_attack(struct Battleship b, struct Escortship e)
{
    float distance = p2a_distance(b, e);

    float minAngleRad = e.minAngle * M_PI / 180.0;
    float maxAngleRad = e.maxAngle * M_PI / 180.0;

    float R_E_min =
        (e.minVelocity * e.minVelocity * sin(2.0 * minAngleRad)) / GRAVITY;

    float R_E_max =
        (e.maxVelocity * e.maxVelocity * sin(2.0 * maxAngleRad)) / GRAVITY;

    return distance >= R_E_min && distance <= R_E_max;
}

// Part 2-B: Part 1-A / Part 1-C A
void part_2_B_battle(
    struct Battleship b,
    struct Escortship e[],
    int N,
    float TB,
    float TE_A,
    float TE_B,
    float TE_C,
    float TE_D,
    int useImpactPower
)
{
    FILE *fp;

    if (useImpactPower)
        fp = fopen("part_2_B_C.txt", "w");
    else
        fp = fopen("part_2_B.txt", "w");

    if (fp == NULL)
    {
        printf("Error opening Part 2-B result file!\n");
        return;
    }

    float nextE[N];
    int order[N];
    float cumulativeImpact = 0.0f;
    float currentTime = 0.0f;
    float nextB = TB;
    int b_sunk = 0;
    int targetPosition = 0;

    for (int i = 0; i < N; i++)
        nextE[i] = p2b_get_TE(e[i].type, TE_A, TE_B, TE_C, TE_D);

    int attackCount = p2b_create_attack_order(
        b, e, N, order, p2a_b_range(b), useImpactPower);

    fprintf(fp, "====================================================\n");
    fprintf(fp, useImpactPower ?
        "             PART 2-B - PART 1-C A\n" :
        "             PART 2-B - PART 1-A\n");
    fprintf(fp, "====================================================\n\n");

    fprintf(fp, "=== INITIAL BATTLEFIELD CONDITIONS ===\n\n");
    fprintf(fp, "Battleship Type: %c\n", b.type);
    fprintf(fp, "Battleship Position: (%.2f, %.2f)\n", b.x, b.y);
    fprintf(fp, "Battleship Max Velocity: %.2f\n", b.maxVelocity);
    fprintf(fp, "Total Escort Ships: %d\n", N);
    fprintf(fp, "Time Between B Firings: %.2f seconds\n", TB);
    fprintf(fp, "TE_A: %.2f seconds\n", TE_A);
    fprintf(fp, "TE_B: %.2f seconds\n", TE_B);
    fprintf(fp, "TE_C: %.2f seconds\n", TE_C);
    fprintf(fp, "TE_D: %.2f seconds\n\n", TE_D);

    fprintf(fp, "----- ESCORT SHIPS -----\n");
    for (int i = 0; i < N; i++)
    {
        fprintf(fp, "ID: %d | Type: E_%c | Position: (%.2f, %.2f) | TE: %.2f\n",
            e[i].id, e[i].type, e[i].x, e[i].y,
            p2b_get_TE(e[i].type, TE_A, TE_B, TE_C, TE_D));
    }

    fprintf(fp, "\n----- B ATTACK ORDER -----\n");
    if (attackCount == 0)
        fprintf(fp, "No E ships are inside B attack range.\n");
    for (int i = 0; i < attackCount; i++)
    {
        int index = order[i];
        fprintf(fp, "%d. E Ship ID %d (Type E_%c)\n",
            i + 1, e[index].id, e[index].type);
    }

    fprintf(fp, "\n----- CONTINUOUS FIRE RESULTS -----\n");

    // B and E ships fire continuously according to their intervals.
    // B follows the selected attack order.
    while (!b_sunk && (targetPosition < attackCount))
    {
        // Find the next E firing event before the next B firing.
        int eventE = -1;
        float earliestE = 1.0e30f;

        for (int i = 0; i < N; i++)
        {
            if (!e[i].isDestroyed && p2b_can_E_attack(b, e[i]) &&
                nextE[i] < earliestE)
            {
                earliestE = nextE[i];
                eventE = i;
            }
        }

        if (eventE != -1 && earliestE < nextB)
        {
            currentTime = earliestE;
            fprintf(fp, "\nTime: %.2f seconds\n", currentTime);
            fprintf(fp, "E Ship ID %d (Type E_%c) fires at B\n",
                e[eventE].id, e[eventE].type);

            if (useImpactPower)
            {
                cumulativeImpact += e[eventE].impactPower;
                fprintf(fp, "Impact Power: %.2f\n", e[eventE].impactPower);
                fprintf(fp, "Cumulative Impact: %.2f\n", cumulativeImpact);

                if (cumulativeImpact >= 1.0f)
                {
                    b_sunk = 1;
                    fprintf(fp, "BATTLESHIP DESTROYED\n");
                    break;
                }
            }
            else
            {
                b_sunk = 1;
                fprintf(fp, "BATTLESHIP DESTROYED\n");
                break;
            }

            nextE[eventE] += p2b_get_TE(
                e[eventE].type, TE_A, TE_B, TE_C, TE_D);
        }
        else
        {
            int index = order[targetPosition];
            currentTime = nextB;

            if (!e[index].isDestroyed)
            {
                fprintf(fp, "\nTime: %.2f seconds\n", currentTime);
                fprintf(fp, "B attacks E Ship ID %d\n", e[index].id);
                e[index].isDestroyed = 1;
                fprintf(fp, "E Ship ID %d DESTROYED\n", e[index].id);
            }

            targetPosition++;
            nextB += TB;
        }
    }

    // If all B targets were destroyed, E ships can still fire continuously.
    // Continue until the next E event causes B to be destroyed.
    if (!b_sunk)
    {
        int safety = 0;
        while (safety < 100000)
        {
            int eventE = -1;
            float earliestE = 1.0e30f;

            for (int i = 0; i < N; i++)
            {
                if (!e[i].isDestroyed && p2b_can_E_attack(b, e[i]) &&
                    nextE[i] < earliestE)
                {
                    earliestE = nextE[i];
                    eventE = i;
                }
            }

            if (eventE == -1)
                break;

            currentTime = earliestE;
            fprintf(fp, "\nTime: %.2f seconds\n", currentTime);
            fprintf(fp, "E Ship ID %d (Type E_%c) fires at B\n",
                e[eventE].id, e[eventE].type);

            if (useImpactPower)
            {
                cumulativeImpact += e[eventE].impactPower;
                fprintf(fp, "Impact Power: %.2f\n", e[eventE].impactPower);
                fprintf(fp, "Cumulative Impact: %.2f\n", cumulativeImpact);

                if (cumulativeImpact >= 1.0f)
                {
                    b_sunk = 1;
                    fprintf(fp, "BATTLESHIP DESTROYED\n");
                    break;
                }
            }
            else
            {
                b_sunk = 1;
                fprintf(fp, "BATTLESHIP DESTROYED\n");
                break;
            }

            nextE[eventE] += p2b_get_TE(
                e[eventE].type, TE_A, TE_B, TE_C, TE_D);
            safety++;
        }
    }

    fprintf(fp, "\n\n================ FINAL RESULTS ================\n");
    fprintf(fp, "Battleship Status: %s\n", b_sunk ? "DESTROYED" : "SURVIVED");
    fprintf(fp, "Total E Ships Destroyed: ");

    int destroyedCount = 0;
    for (int i = 0; i < N; i++)
        if (e[i].isDestroyed) destroyedCount++;
    fprintf(fp, "%d\n", destroyedCount);

    if (useImpactPower)
        fprintf(fp, "Cumulative Impact on B: %.2f\n", cumulativeImpact);

    fprintf(fp, "\n----- FINAL ESCORT SHIP STATUS -----\n");
    for (int i = 0; i < N; i++)
    {
        fprintf(fp, "E Ship ID %d: %s\n", e[i].id,
            e[i].isDestroyed ? "DESTROYED" : "SURVIVED");
    }

    fclose(fp);
    printf("\nPart 2-B results saved successfully.\n");
}

// Part 2-B: Part 1-B Simulation 1 / 2 and Part 1-C versions
void part_2_B_battle_B(
    struct Battleship b,
    struct Escortship e[],
    int N,
    int k,
    float pathX[],
    float pathY[],
    float TB,
    float TE_A,
    float TE_B,
    float TE_C,
    float TE_D,
    int simulationType,
    int t,
    float thetaMin,
    int useImpactPower
)
{
    FILE *fp;

    if (useImpactPower)
        fp = fopen(simulationType == 1 ? "part_2_B_C_B1.txt" : "part_2_B_C_B2.txt", "w");
    else
        fp = fopen(simulationType == 1 ? "part_2_B_B1.txt" : "part_2_B_B2.txt", "w");

    if (fp == NULL)
    {
        printf("Error opening Part 2-B result file!\n");
        return;
    }

    float nextE[N];
    float currentTime = 0.0f;
    float cumulativeImpact = 0.0f;
    int b_sunk = 0;

    for (int i = 0; i < N; i++)
        nextE[i] = p2b_get_TE(e[i].type, TE_A, TE_B, TE_C, TE_D);

    fprintf(fp, "====================================================\n");
    if (useImpactPower)
        fprintf(fp, simulationType == 1 ? "          PART 2-B - PART 1-C B1\n" : "          PART 2-B - PART 1-C B2\n");
    else
        fprintf(fp, simulationType == 1 ? "          PART 2-B - PART 1-B B1\n" : "          PART 2-B - PART 1-B B2\n");
    fprintf(fp, "====================================================\n\n");
    fprintf(fp, "Time Between B Firings: %.2f seconds\n", TB);
    fprintf(fp, "TE_A: %.2f seconds\n", TE_A);
    fprintf(fp, "TE_B: %.2f seconds\n", TE_B);
    fprintf(fp, "TE_C: %.2f seconds\n", TE_C);
    fprintf(fp, "TE_D: %.2f seconds\n", TE_D);

    if (simulationType == 2)
    {
        fprintf(fp, "Jam Starts After Iteration: %d\n", t);
        fprintf(fp, "Minimum Angle: %.2f degrees\n", thetaMin);
    }

    for (int iteration = 0; iteration < k && !b_sunk; iteration++)
    {
        b.x = pathX[iteration];
        b.y = pathY[iteration];

        float bRange;
        float firingAngle = 45.0f;

        if (simulationType == 2 && iteration + 1 > t)
        {
            firingAngle = thetaMin +
                ((float)rand() / RAND_MAX) * (90.0f - thetaMin);
            bRange = (b.maxVelocity * b.maxVelocity *
                sin(2.0f * firingAngle * M_PI / 180.0f)) / GRAVITY;
        }
        else
        {
            bRange = p2a_b_range(b);
        }

        int order[N];
        int attackCount = p2b_create_attack_order(
            b, e, N, order, bRange, useImpactPower);

        fprintf(fp, "\n\n====================================================\n");
        fprintf(fp, "ITERATION %d\n", iteration + 1);
        fprintf(fp, "B Position: (%.2f, %.2f)\n", b.x, b.y);
        fprintf(fp, "B Attack Range: %.2f\n", bRange);
        if (simulationType == 2 && iteration + 1 > t)
            fprintf(fp, "B Firing Angle: %.2f degrees\n", firingAngle);

        fprintf(fp, "\n----- B ATTACK ORDER -----\n");
        if (attackCount == 0)
            fprintf(fp, "No E ships are inside B attack range.\n");
        for (int i = 0; i < attackCount; i++)
        {
            int index = order[i];
            fprintf(fp, "%d. E Ship ID %d (Type E_%c)\n",
                i + 1, e[index].id, e[index].type);
        }

        // B fires once in this movement iteration.
        currentTime += TB;
        if (attackCount > 0)
        {
            int index = order[0];
            if (!e[index].isDestroyed)
            {
                fprintf(fp, "\nTime: %.2f seconds\n", currentTime);
                fprintf(fp, "B attacks E Ship ID %d\n", e[index].id);
                e[index].isDestroyed = 1;
                fprintf(fp, "E Ship ID %d DESTROYED\n", e[index].id);
            }
        }

        // Process all E firing events that have become due.
        int changed = 1;
        while (changed && !b_sunk)
        {
            changed = 0;
            int eventE = -1;
            float earliestE = 1.0e30f;

            for (int i = 0; i < N; i++)
            {
                if (!e[i].isDestroyed && p2b_can_E_attack(b, e[i]) &&
                    nextE[i] <= currentTime && nextE[i] < earliestE)
                {
                    earliestE = nextE[i];
                    eventE = i;
                }
            }

            if (eventE != -1)
            {
                changed = 1;
                currentTime = nextE[eventE];
                fprintf(fp, "\nTime: %.2f seconds\n", currentTime);
                fprintf(fp, "E Ship ID %d (Type E_%c) fires at B\n",
                    e[eventE].id, e[eventE].type);

                if (useImpactPower)
                {
                    cumulativeImpact += e[eventE].impactPower;
                    fprintf(fp, "Impact Power: %.2f\n", e[eventE].impactPower);
                    fprintf(fp, "Cumulative Impact: %.2f\n", cumulativeImpact);

                    if (cumulativeImpact >= 1.0f)
                    {
                        b_sunk = 1;
                        fprintf(fp, "BATTLESHIP DESTROYED\n");
                        break;
                    }
                }
                else
                {
                    b_sunk = 1;
                    fprintf(fp, "BATTLESHIP DESTROYED\n");
                    break;
                }

                nextE[eventE] += p2b_get_TE(
                    e[eventE].type, TE_A, TE_B, TE_C, TE_D);
            }
        }
    }

    fprintf(fp, "\n\n================ FINAL RESULTS ================\n");
    fprintf(fp, "Battleship Status: %s\n", b_sunk ? "DESTROYED" : "SURVIVED");
    if (useImpactPower)
        fprintf(fp, "Cumulative Impact on B: %.2f\n", cumulativeImpact);

    fprintf(fp, "\n----- FINAL ESCORT SHIP STATUS -----\n");
    for (int i = 0; i < N; i++)
    {
        fprintf(fp, "E Ship ID %d: %s\n", e[i].id,
            e[i].isDestroyed ? "DESTROYED" : "SURVIVED");
    }

    fclose(fp);
    printf("\nPart 2-B path simulation results saved successfully.\n");
}
