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

