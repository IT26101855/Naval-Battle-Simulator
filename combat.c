#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "combat.h"

#define GRAVITY 9.81

float calculateFlightTime(float velocity, float angle)
{
    float angleRad = angle * M_PI / 180.0;

    return (2.0 * velocity * sin(angleRad)) / GRAVITY;
}


void battle_calculations(struct Battleship b, struct Escortship e[], int N)
{

    FILE *fp = fopen("part1_A_results.txt", "a");

    if (fp == NULL)
    {
        printf("Error opening file for writing!\n");
        return;
    }


    int simulationNumber = 1;
    char line[256];

    FILE *countFile = fopen("part1_A_results.txt", "r");

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
        /*
          Destroyed ships are not present
           in later iterations.
         */

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
        /*
           If this E ship was destroyed in a previous
           iteration, it cannot participate again.
         */

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

            float hit_time =
                calculateFlightTime(b.maxVelocity, 45.0);

            time_to_hit[i] = hit_time;

            if (hit_time > battle_duration)
            {
                battle_duration = hit_time;
            }
        }


        /* 
           escort ship attacks battleship

           Only an E ship which survived B's attack
           can attack B.*/

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
        fprintf(fp, "STATUS: Battleship SURVIVED!\n");

        fprintf(fp,
                "Total Escort Ships Hit: %d\n",
                hit_e_count);

        fprintf(fp,
                "Battle Duration: %.2f seconds\n",
                battle_duration);


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
    }


    
      //final battlefield conditions

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
