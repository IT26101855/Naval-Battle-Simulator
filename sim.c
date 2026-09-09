#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "sim.h"
#include "battlefield.h"
#include "combat.h"

// Part 1 A simulation function
    void part_1_A() {
     system("clear");
     printf("                                         Start\n\n\n");
     printf("                                 Part-1-A Simulation\n\n");

    struct Battleship b;

    //getting the details of the battleship
    printf("--Battleship Name--                       --Notation--                       --Gun Name--\n\n\n\n");
    printf(" USS Iowa(BB-61)                              U                           50-caliber Mark 7 gun\n");
    printf(" MS King George V                             M                           (356 mm) Mark VII gun\n");
    printf(" Richelieu                                    R                           (15 inch) Mle 1935 gun\n");
    printf(" Sovetsky Soyuz-class                         S                           (16 inch) B-37 gun\n\n\n\n");
    printf("Enter Battleship Type (U M R S): "); 
    scanf(" %c", &b.type);

    printf("Enter Battleship's X Position: ");
    scanf("%f", &b.x);

    printf("Enter Battleship's Y Position: ");
    scanf("%f", &b.y);

    printf("Enter Battleship's Max Velocity: ");
    scanf("%f", &b.maxVelocity);

    //displaying the details of the battleship
    printf("\n----- Battle Ship Information -----\n");
    printf("Type: %c\n", b.type);
    printf("Position: (%.2f, %.2f)\n", b.x, b.y);
    printf("Max Velocity: %.2f\n", b.maxVelocity);
    
    getchar();
    getchar();
    system("clear");

    //battlefield dimensions and escort ships count inputs
    float D;
    int N;
    battlefield(&D, &N);
    getchar();
    getchar();
    system("clear");

    struct Escortship e[N];
    char types[] = {'A', 'B', 'C', 'D', 'E'};

    //random number seed generator
    srand(time(NULL));

    //generating escort ships
    for (int i = 0; i < N; i++) {
        e[i].id = i + 1;

        // Randomly pick ship type from A to E
        e[i].type = types[rand() % 5];

        //randomly generate (x, y) coordinates within Canvas (0 to D)
        e[i].x = ((float)rand() / RAND_MAX) * D;
        e[i].y = ((float)rand() / RAND_MAX) * D;

        //assign specific values based on escort ship type
        switch(e[i].type) {
            case 'A':
                e[i].minAngle = ((float)rand() / RAND_MAX) * 70.0f;
                e[i].maxAngle = e[i].minAngle + 20.0f;
                e[i].minVelocity = ((float)rand() / RAND_MAX) * 10.0f;
                e[i].maxVelocity = 1.2f * b.maxVelocity;
                break;

            case 'B':
                e[i].minAngle = ((float)rand() / RAND_MAX) * 60.0f;
                e[i].maxAngle = e[i].minAngle + 30.0f;
                e[i].minVelocity = ((float)rand() / RAND_MAX) * 10.0f;
                e[i].maxVelocity = ((float)rand() / RAND_MAX) * b.maxVelocity;
                break;

            case 'C':
                e[i].minAngle = ((float)rand() / RAND_MAX) * 65.0f;
                e[i].maxAngle = e[i].minAngle + 25.0f;
                e[i].minVelocity = ((float)rand() / RAND_MAX) * 10.0f;
                e[i].maxVelocity = ((float)rand() / RAND_MAX) * b.maxVelocity;
                break;

            case 'D':
                e[i].minAngle = ((float)rand() / RAND_MAX) * 40.0f;
                e[i].maxAngle = e[i].minAngle + 50.0f;
                e[i].minVelocity = ((float)rand() / RAND_MAX) * 10.0f;
                e[i].maxVelocity = ((float)rand() / RAND_MAX) * b.maxVelocity;
                break;

            case 'E':
                e[i].minAngle = ((float)rand() / RAND_MAX) * 20.0f;
                e[i].maxAngle = e[i].minAngle + 70.0f;
                e[i].minVelocity = ((float)rand() / RAND_MAX) * 10.0f;
                e[i].maxVelocity = ((float)rand() / RAND_MAX) * b.maxVelocity;
                break;
        }
        e[i].isDestroyed = 0;
    }

    // display generated escort ships information
    printf("\n----- Generated Escort Ships -----\n");
    for (int i = 0; i < N; i++) {
        printf("ID: %d | Type: E_%c | Position: (%.2f, %.2f) | Max Vel: %.2f\n",
               e[i].id, e[i].type, e[i].x, e[i].y, e[i].maxVelocity);

    } 

    getchar();
    system("clear");

    battle_calculations(b, e, N);
}

void simulation_part_B_1(){
	system("clear");

    printf("====================================================\n");
    printf("             PART 1-B - SIMULATION 1\n");
    printf("====================================================\n\n\n\n\n");


    //getting the details of the battleship

    struct Battleship b;


    printf("--Battleship Name--                       --Notation--                       --Gun Name--\n\n");

    printf(" USS Iowa(BB-61)                              U                           50-caliber Mark 7 gun\n");
    printf(" MS King George V                             M                           (356 mm) Mark VII gun\n");
    printf(" Richelieu                                    R                           (15 inch) Mle 1935 gun\n");
    printf(" Sovetsky Soyuz-class                         S                           (16 inch) B-37 gun\n\n");


    printf("Enter Battleship Type (U M R S): ");
    scanf(" %c", &b.type);

    printf("Enter Battleship's Max Velocity: ");
    scanf("%f", &b.maxVelocity);


    //battlefield dimensions

    float D;
    int N;

    battlefield(&D, &N);


    //escort ship types

    struct Escortship e[N];

    char types[] = {'A', 'B', 'C', 'D', 'E'};


    srand(time(NULL));


  
         //generate escort ships

    for (int i = 0; i < N; i++)
    {
        e[i].id = i + 1;


        //random escort ship type

        e[i].type = types[rand() % 5];


        //random position inside battlefield

        e[i].x =
            ((float)rand() / RAND_MAX) * D;

        e[i].y =
            ((float)rand() / RAND_MAX) * D;


        //escort ships specific values

        switch(e[i].type)
        {
            case 'A':

                e[i].minAngle =
                    ((float)rand() / RAND_MAX) * 70.0f;

                e[i].maxAngle =
                    e[i].minAngle + 20.0f;

                e[i].minVelocity =
                    ((float)rand() / RAND_MAX) * 10.0f;

                e[i].maxVelocity =
                    1.2f * b.maxVelocity;

                break;


            case 'B':

                e[i].minAngle =
                    ((float)rand() / RAND_MAX) * 60.0f;

                e[i].maxAngle =
                    e[i].minAngle + 30.0f;

                e[i].minVelocity =
                    ((float)rand() / RAND_MAX) * 10.0f;

                e[i].maxVelocity =
                    ((float)rand() / RAND_MAX) * b.maxVelocity;

                break;


            case 'C':

                e[i].minAngle =
                    ((float)rand() / RAND_MAX) * 65.0f;

                e[i].maxAngle =
                    e[i].minAngle + 25.0f;

                e[i].minVelocity =
                    ((float)rand() / RAND_MAX) * 10.0f;

                e[i].maxVelocity =
                    ((float)rand() / RAND_MAX) * b.maxVelocity;

                break;


            case 'D':

                e[i].minAngle =
                    ((float)rand() / RAND_MAX) * 40.0f;

                e[i].maxAngle =
                    e[i].minAngle + 50.0f;

                e[i].minVelocity =
                    ((float)rand() / RAND_MAX) * 10.0f;

                e[i].maxVelocity =
                    ((float)rand() / RAND_MAX) * b.maxVelocity;

                break;


            case 'E':

                e[i].minAngle =
                    ((float)rand() / RAND_MAX) * 20.0f;

                e[i].maxAngle =
                    e[i].minAngle + 70.0f;

                e[i].minVelocity =
                    ((float)rand() / RAND_MAX) * 10.0f;

                e[i].maxVelocity =
                    ((float)rand() / RAND_MAX) * b.maxVelocity;

                break;
        }


        //initially all escort ships are alive

        e[i].isDestroyed = 0;
    }



    //display details of escort ships

    printf("\n----- Generated Escort Ships -----\n\n");

    for (int i = 0; i < N; i++)
    {
        printf("ID: %d | Type: E_%c | Position: (%.2f, %.2f) | Max Vel: %.2f\n",
               e[i].id,
               e[i].type,
               e[i].x,
               e[i].y,
               e[i].maxVelocity);
    }


    //get input for value k

    int k;

    printf("\n\nEnter number of path points (k): ");
    scanf("%d", &k);



    while (k <= 0)
    {
        printf("Invalid value! k must be greater than 0.\n");
        printf("Enter number of path points (k): ");
        scanf("%d", &k);
    }


 
    //arrays for path points

    float pathX[k];
    float pathY[k];


    //generate k random points inside battlefield

    printf("\n\n----- GENERATED PATH -----\n\n");

    for (int i = 0; i < k; i++)
    {
        pathX[i] =
            ((float)rand() / RAND_MAX) * D;

        pathY[i] =
            ((float)rand() / RAND_MAX) * D;


        printf("Point %d : (%.2f, %.2f)\n",
               i + 1,
               pathX[i],
               pathY[i]);
    }


    printf("\nPath generated successfully.\n");

    getchar();
    getchar();

    system("clear");


 
       //simulate each path point of the battleship

    for (int i = 0; i < k; i++)
    {

        // move battleship to current path point

        b.x = pathX[i];
        b.y = pathY[i];


        printf("\n====================================================\n");
        printf("                 ITERATION %d\n", i + 1);
        printf("====================================================\n");

        printf("Battleship Position: (%.2f, %.2f)\n",
               b.x,
               b.y);


       
        // show current escort ship status

        printf("\nCurrent Escort Ships:\n");

        for (int j = 0; j < N; j++)
        {
            if (e[j].isDestroyed)
            {
                printf("E_%c (ID %d) -> DESTROYED\n",
                       e[j].type,
                       e[j].id);
            }
            else
            {
                printf("E_%c (ID %d) -> ACTIVE\n",
                       e[j].type,
                       e[j].id);
            }
        }


        /* --------------------------------------------------
           Run Part 1-A type battle at this point
        
           battle_calculations() returns:
        
           1 -> B is destroyed
           0 -> B survives
         --------------------------------------------------*/

        int bSunk;

        bSunk = battle_calculations_B1(b, e, N, i+1);


        //if battleship is destroyed, stop all remaining iterations

        if (bSunk == 1)
        {
            printf("\n");
            printf("---------------------------------------------------\n");
            printf(" Battleship SANK at iteration %d!\n", i + 1);
            printf(" Path simulation stopped.\n");
            printf("----------------------------------------------------\n");

            break;
        }


        
        //if battleship survived, continue to next point

        if (i < k - 1)
        {
            printf("\nBattleship survived iteration %d.\n",
                   i + 1);

            printf("Moving to next path point...\n");
        }
        else
        {
            printf("\nAll %d path points completed.\n", k);
        }
    }


    printf("\n\n====================================================\n");
    printf("       PART 1-B SIMULATION 1 COMPLETED\n");
    printf("====================================================\n");

    printf("\nResults have been saved to the results file.\n");

    getchar();
    getchar();

    system("clear");
}

void simulation_part_B_2()
{
    struct Battleship b;

    float D;
    int N;

    int k;
    int t;

    float thetaMin;


    system("clear");

    printf("====================================================\n");
    printf("          PART 1-B - SIMULATION 2\n");
    printf("====================================================\n\n");


  
      //battleship input 


    printf("Enter Battleship Type: ");
    scanf(" %c", &b.type);

    printf("Enter Battleship Maximum Velocity: ");
    scanf("%f", &b.maxVelocity);


 
      //battlefield

    battlefield(&D, &N);


      //generate escort ships

    struct Escortship e[N];

    for (int i = 0; i < N; i++)
    {
        e[i].id = i + 1;

        e[i].x =
            ((float)rand() / RAND_MAX) * D;

        e[i].y =
            ((float)rand() / RAND_MAX) * D;

        e[i].isDestroyed = 0;


        int typeNumber =
            rand() % 5;


        switch (typeNumber)
        {
            case 0:
                e[i].type = 'A';
                e[i].minVelocity = 10;
                e[i].maxVelocity = 20;
                e[i].minAngle = 10;
                e[i].maxAngle = 30;
                break;

            case 1:
                e[i].type = 'B';
                e[i].minVelocity = 15;
                e[i].maxVelocity = 25;
                e[i].minAngle = 15;
                e[i].maxAngle = 35;
                break;

            case 2:
                e[i].type = 'C';
                e[i].minVelocity = 20;
                e[i].maxVelocity = 30;
                e[i].minAngle = 20;
                e[i].maxAngle = 40;
                break;

            case 3:
                e[i].type = 'D';
                e[i].minVelocity = 25;
                e[i].maxVelocity = 35;
                e[i].minAngle = 25;
                e[i].maxAngle = 45;
                break;

            case 4:
                e[i].type = 'E';
                e[i].minVelocity = 30;
                e[i].maxVelocity = 40;
                e[i].minAngle = 30;
                e[i].maxAngle = 50;
                break;
        }
    }


   
       //get input k value
       

    do
    {
        printf("\nEnter number of path points k: ");
        scanf("%d", &k);

        if (k <= 0)
        {
            printf("k must be greater than 0!\n");
        }

    } while (k <= 0);


   
      //get input t value  (t < k)

    do
    {
        printf("Enter t (number of normal-gun iterations, t < k): ");
        scanf("%d", &t);

        if (t <= 0 || t >= k)
        {
            printf("Invalid t! It must satisfy 0 < t < k.\n");
        }

    } while (t <= 0 || t >= k);


    /* 
       THETA MIN INPUT
       0 < thetaMin < 30
                          */

    do
    {
        printf("Enter thetaMin (0 < thetaMin < 30): ");
        scanf("%f", &thetaMin);

        if (thetaMin <= 0 || thetaMin >= 30)
        {
            printf("Invalid thetaMin! "
                   "It must be between 0 and 30 degrees.\n");
        }

    } while (thetaMin <= 0 || thetaMin >= 30);

     //generate path points

    float pathX[k];
    float pathY[k];

    for (int i = 0; i < k; i++)
    {
        pathX[i] =
            ((float)rand() / RAND_MAX) * D;

        pathY[i] =
            ((float)rand() / RAND_MAX) * D;
    }


 
      //run the simulaton

    for (int i = 0; i < k; i++)
    {
        b.x = pathX[i];
        b.y = pathY[i];


        int jammed;

        if (i < t)
        {
            jammed = 0;
        }
        else
        {
            jammed = 1;
        }


        printf("\n========================================\n");
        printf("Iteration %d / %d\n", i + 1, k);
        printf("B Position: (%.2f, %.2f)\n",b.x,b.y);


        if (jammed)
        {
            printf("B Gun Status: JAMMED\n");
            printf("Allowed Angle: %.2f - 90 degrees\n",thetaMin);
        }
        else
        {
            printf("B Gun Status: NORMAL\n");
            printf("Allowed Angle: 0 - 90 degrees\n");
        }


        printf("========================================\n");


        int bSunk = battle_calculations_B2(b,e,N,i + 1,jammed,thetaMin);


        if (bSunk)
        {
            printf("\nBattleship was destroyed!\n");
            printf("Simulation 2 stopped at iteration %d.\n",
                   i + 1);

            break;
        }
    }


    printf("\n====================================================\n");
    printf("       PART 1-B SIMULATION 2 COMPLETED\n");
    printf("====================================================\n");

    printf("\nResults saved to:\n");
    printf("part_1_B_simulation_2.txt\n");

    printf("\nPress Enter to return...");

    while (getchar() != '\n');
    getchar();
    getchar();
    system("clear");
}

void part_1_C_A()
{
    system("clear");

    printf("====================================================\n");
    printf("        PART 1-C - PART 1-A WITH IMPACT POWER\n");
    printf("====================================================\n\n");

    struct Battleship b;

    /* Battleship details */
    printf("Enter Battleship Type (U M R S): ");
    scanf(" %c", &b.type);

    printf("Enter Battleship's X Position: ");
    scanf("%f", &b.x);

    printf("Enter Battleship's Y Position: ");
    scanf("%f", &b.y);

    printf("Enter Battleship's Max Velocity: ");
    scanf("%f", &b.maxVelocity);

    /* Battlefield details */
    float D;
    int N;

    battlefield(&D, &N);

    /* Create escort ships */
    struct Escortship e[N];

    char types[] = {'A', 'B', 'C', 'D', 'E'};

    srand(time(NULL));

    for (int i = 0; i < N; i++)
    {
        e[i].id = i + 1;

        /* Random type */
        e[i].type = types[rand() % 5];

        /* Random position */
        e[i].x = ((float)rand() / RAND_MAX) * D;
        e[i].y = ((float)rand() / RAND_MAX) * D;

        /* Type-specific values */
        switch (e[i].type)
        {
            case 'A':
                e[i].minAngle =
                    ((float)rand() / RAND_MAX) * 70.0f;

                e[i].maxAngle =
                    e[i].minAngle + 20.0f;

                e[i].minVelocity =
                    ((float)rand() / RAND_MAX) * 10.0f;

                e[i].maxVelocity =
                    1.2f * b.maxVelocity;

                e[i].impactPower = 0.08f;
                break;

            case 'B':
                e[i].minAngle =
                    ((float)rand() / RAND_MAX) * 60.0f;

                e[i].maxAngle =
                    e[i].minAngle + 30.0f;

                e[i].minVelocity =
                    ((float)rand() / RAND_MAX) * 10.0f;

                e[i].maxVelocity =
                    ((float)rand() / RAND_MAX) * b.maxVelocity;

                e[i].impactPower = 0.06f;
                break;

            case 'C':
                e[i].minAngle =
                    ((float)rand() / RAND_MAX) * 65.0f;

                e[i].maxAngle =
                    e[i].minAngle + 25.0f;

                e[i].minVelocity =
                    ((float)rand() / RAND_MAX) * 10.0f;

                e[i].maxVelocity =
                    ((float)rand() / RAND_MAX) * b.maxVelocity;

                e[i].impactPower = 0.07f;
                break;

            case 'D':
                e[i].minAngle =
                    ((float)rand() / RAND_MAX) * 40.0f;

                e[i].maxAngle =
                    e[i].minAngle + 50.0f;

                e[i].minVelocity =
                    ((float)rand() / RAND_MAX) * 10.0f;

                e[i].maxVelocity =
                    ((float)rand() / RAND_MAX) * b.maxVelocity;

                e[i].impactPower = 0.05f;
                break;

            case 'E':
                e[i].minAngle =
                    ((float)rand() / RAND_MAX) * 20.0f;

                e[i].maxAngle =
                    e[i].minAngle + 70.0f;

                e[i].minVelocity =
                    ((float)rand() / RAND_MAX) * 10.0f;

                e[i].maxVelocity =
                    ((float)rand() / RAND_MAX) * b.maxVelocity;

                e[i].impactPower = 0.04f;
                break;
        }

        /* Initial states */
        e[i].isDestroyed = 0;
        e[i].hasAttacked = 0;
    }

    /* Display generated ships */
    printf("\n----- Generated Escort Ships -----\n\n");

    for (int i = 0; i < N; i++)
    {
        printf("ID: %d | Type: E_%c | Position: (%.2f, %.2f) | "
               "Max Vel: %.2f | Impact Power: %.2f\n",
               e[i].id,
               e[i].type,
               e[i].x,
               e[i].y,
               e[i].maxVelocity,
               e[i].impactPower);
    }

    printf("\nPart 1-C initial setup completed.\n");
    printf("Impact power has been assigned to all escort ships.\n");

    getchar();
    getchar();

    int bSunk = battle_calculations_C_A(b, e, N);

    if (bSunk)
       {
         printf("\nBattleship was destroyed!\n");
      }
    else
       {
          printf("\nBattleship survived!\n");
       }

    system("clear");
}

void part_1_C_B1()
{
    system("clear");

    printf("====================================================\n");
    printf("        PART 1-C - PART 1 B SIMULATION 1\n");
    printf("====================================================\n\n");

    struct Battleship b;

    /* Battleship */

    printf("Enter Battleship Type: ");
    scanf(" %c", &b.type);

    printf("Enter Battleship Maximum Velocity: ");
    scanf("%f", &b.maxVelocity);

    /* Battlefield */

    float D;
    int N;

    battlefield(&D, &N);

    /* Escort ships */

    struct Escortship e[N];

    for (int i = 0; i < N; i++)
    {
        e[i].id = i + 1;

        e[i].x =
            ((float)rand() / RAND_MAX) * D;

        e[i].y =
            ((float)rand() / RAND_MAX) * D;

        e[i].isDestroyed = 0;
        e[i].hasAttacked = 0;

        int typeNumber =
            rand() % 5;

        switch (typeNumber)
        {
            case 0:
                e[i].type = 'A';
                e[i].minVelocity = 10;
                e[i].maxVelocity = 20;
                e[i].minAngle = 10;
                e[i].maxAngle = 30;
                e[i].impactPower = 0.08f;
                break;

            case 1:
                e[i].type = 'B';
                e[i].minVelocity = 15;
                e[i].maxVelocity = 25;
                e[i].minAngle = 15;
                e[i].maxAngle = 35;
                e[i].impactPower = 0.06f;
                break;

            case 2:
                e[i].type = 'C';
                e[i].minVelocity = 20;
                e[i].maxVelocity = 30;
                e[i].minAngle = 20;
                e[i].maxAngle = 40;
                e[i].impactPower = 0.07f;
                break;

            case 3:
                e[i].type = 'D';
                e[i].minVelocity = 25;
                e[i].maxVelocity = 35;
                e[i].minAngle = 25;
                e[i].maxAngle = 45;
                e[i].impactPower = 0.05f;
                break;

            case 4:
                e[i].type = 'E';
                e[i].minVelocity = 30;
                e[i].maxVelocity = 40;
                e[i].minAngle = 30;
                e[i].maxAngle = 50;
                e[i].impactPower = 0.04f;
                break;
        }
    }

    /* k input */

    int k;

    do
    {
        printf("\nEnter number of path points k: ");
        scanf("%d", &k);

        if (k <= 0)
        {
            printf("k must be greater than 0!\n");
        }

    } while (k <= 0);

    /* Generate path */

    float pathX[k];
    float pathY[k];

    for (int i = 0; i < k; i++)
    {
        pathX[i] =
            ((float)rand() / RAND_MAX) * D;

        pathY[i] =
            ((float)rand() / RAND_MAX) * D;
    }

    /*
     * IMPORTANT:
     * cumulative impact must survive
     * between iterations.
     */

    float cumulativeImpact = 0.0f;

    /* Run simulation */

    for (int i = 0; i < k; i++)
    {
        b.x = pathX[i];
        b.y = pathY[i];

        printf("\n========================================\n");
        printf("Iteration %d / %d\n", i + 1, k);

        printf("B Position: (%.2f, %.2f)\n",
               b.x,
               b.y);

        printf("Cumulative Impact: %.2f\n",
               cumulativeImpact);

        printf("Cumulative Damage: %.2f%%\n",
               cumulativeImpact * 100.0f);

        printf("========================================\n");

        int bSunk =
            battle_calculations_C_B1(
                b,
                e,
                N,
                i + 1,
                &cumulativeImpact);

        if (bSunk)
        {
            printf("\nBattleship was destroyed!\n");

            printf("Simulation 1 stopped at iteration %d.\n",
                   i + 1);

            break;
        }
    }

    printf("\n====================================================\n");
    printf("       PART 1-C PART B SIMULATION 1 COMPLETED\n");
    printf("====================================================\n");

    printf("\nFinal Cumulative Impact: %.2f\n",
           cumulativeImpact);

    printf("Final Cumulative Damage: %.2f%%\n",
           cumulativeImpact * 100.0f);

    printf("\nResults saved to:\n");
    printf("part_1_C_B_simulation_1.txt\n");

    printf("\nPress Enter to return...");

    while (getchar() != '\n');
    getchar();

    system("clear");
}

void part_1_C_B2()
{
    system("clear");

    printf("====================================================\n");
    printf("        PART 1-C - PART 1 B SIMULATION 2\n");
    printf("====================================================\n\n");

    struct Battleship b;

     //battleship details

    printf("Enter Battleship Type: ");
    scanf(" %c", &b.type);

    printf("Enter Battleship Maximum Velocity: ");
    scanf("%f", &b.maxVelocity);

    /* Battlefield */

    float D;
    int N;

    battlefield(&D, &N);

    /* Escort ships */

    struct Escortship e[N];

    for (int i = 0; i < N; i++)
    {
        e[i].id = i + 1;

        e[i].x =
            ((float)rand() / RAND_MAX) * D;

        e[i].y =
            ((float)rand() / RAND_MAX) * D;

        e[i].isDestroyed = 0;
        e[i].hasAttacked = 0;

        int typeNumber =
            rand() % 5;

        switch (typeNumber)
        {
            case 0:
                e[i].type = 'A';
                e[i].minVelocity = 10;
                e[i].maxVelocity = 20;
                e[i].minAngle = 10;
                e[i].maxAngle = 30;
                e[i].impactPower = 0.08f;
                break;

            case 1:
                e[i].type = 'B';
                e[i].minVelocity = 15;
                e[i].maxVelocity = 25;
                e[i].minAngle = 15;
                e[i].maxAngle = 35;
                e[i].impactPower = 0.06f;
                break;

            case 2:
                e[i].type = 'C';
                e[i].minVelocity = 20;
                e[i].maxVelocity = 30;
                e[i].minAngle = 20;
                e[i].maxAngle = 40;
                e[i].impactPower = 0.07f;
                break;

            case 3:
                e[i].type = 'D';
                e[i].minVelocity = 25;
                e[i].maxVelocity = 35;
                e[i].minAngle = 25;
                e[i].maxAngle = 45;
                e[i].impactPower = 0.05f;
                break;

            case 4:
                e[i].type = 'E';
                e[i].minVelocity = 30;
                e[i].maxVelocity = 40;
                e[i].minAngle = 30;
                e[i].maxAngle = 50;
                e[i].impactPower = 0.04f;
                break;
        }
    }

    //getting the value of k

    int k;

    do
    {
        printf("\nEnter number of path points k: ");
        scanf("%d", &k);

        if (k <= 0)
        {
            printf("k must be greater than 0!\n");
        }

    } while (k <= 0);

    /* t */

    int t;

    do
    {
        printf("Enter t (number of normal-gun iterations, t < k): ");
        scanf("%d", &t);

        if (t <= 0 || t >= k)
        {
            printf("Invalid t! It must satisfy 0 < t < k.\n");
        }

    } while (t <= 0 || t >= k);

    /* thetaMin */

    float thetaMin;

    do
    {
        printf("Enter thetaMin (0 < thetaMin < 30): ");
        scanf("%f", &thetaMin);

        if (thetaMin <= 0 || thetaMin >= 30)
        {
            printf("Invalid thetaMin! "
                   "It must be between 0 and 30 degrees.\n");
        }

    } while (thetaMin <= 0 || thetaMin >= 30);

    /* Generate path */

    float pathX[k];
    float pathY[k];

    for (int i = 0; i < k; i++)
    {
        pathX[i] =
            ((float)rand() / RAND_MAX) * D;

        pathY[i] =
            ((float)rand() / RAND_MAX) * D;
    }

    /*
     * Cumulative impact is shared
     * between all iterations.
     */

    float cumulativeImpact = 0.0f;

    /* Run simulation */

    for (int i = 0; i < k; i++)
    {
        b.x = pathX[i];
        b.y = pathY[i];

        int jammed;

        if (i < t)
        {
            jammed = 0;
        }
        else
        {
            jammed = 1;
        }

        printf("\n========================================\n");

        printf("Iteration %d / %d\n",
               i + 1,
               k);

        printf("B Position: (%.2f, %.2f)\n",
               b.x,
               b.y);

        if (jammed)
        {
            printf("B Gun Status: JAMMED\n");

            printf("Allowed Angle: %.2f - 90 degrees\n",
                   thetaMin);
        }
        else
        {
            printf("B Gun Status: NORMAL\n");

            printf("Allowed Angle: 0 - 90 degrees\n");
        }

        printf("Cumulative Impact: %.2f\n",
               cumulativeImpact);

        printf("Cumulative Damage: %.2f%%\n",
               cumulativeImpact * 100.0f);

        printf("========================================\n");

        int bSunk =
            battle_calculations_C_B2(
                b,
                e,
                N,
                i + 1,
                jammed,
                thetaMin,
                &cumulativeImpact);

        if (bSunk)
        {
            printf("\nBattleship was destroyed!\n");

            printf("Simulation 2 stopped at iteration %d.\n",
                   i + 1);

            break;
        }
    }

    printf("\n====================================================\n");
    printf("       PART 1-C PART B SIMULATION 2 COMPLETED\n");
    printf("====================================================\n");

    printf("\nFinal Cumulative Impact: %.2f\n",
           cumulativeImpact);

    printf("Final Cumulative Damage: %.2f%%\n",
           cumulativeImpact * 100.0f);

    printf("\nResults saved to:\n");
    printf("part_1_C_B_simulation_2.txt\n");

    printf("\nPress Enter to return...");

    while (getchar() != '\n');
    getchar();

    system("clear");
}

// PART 2-A

void part_2_A()
{
    int choice;

    do
    {
        printf("                                                                |Part 2-A|\n\n\n");
        printf("                                                         1. Part 1-A\n");
        printf("                                                         2. Part 1-B Simulation 1\n");
        printf("                                                         3. Part 1-B Simulation 2\n");
        printf("                                                         4. Part 1-C Part 1-A\n");
        printf("                                                         5. Part 1-C Simulation 1\n");
        printf("                                                         6. Part 1-C Simulation 2\n");
        printf("                                                         7. Back\n\n\n\n\n\n");
  

        printf("                                                           Enter your choice: ");
        scanf("%d", &choice);
	system("clear");

        if (choice == 7)
        {
            break;
        }

        if (choice < 1 || choice > 6)
        {
            printf("Invalid choice!\n");
            continue;
        }

        struct Battleship b;
        struct Escortship e[100];

        int N;
        float D;

        // Get battleship details
        printf("\nEnter Battleship Type(U M R S): ");
        scanf(" %c", &b.type);

        printf("Enter Battleship X position: ");
        scanf("%f", &b.x);

        printf("Enter Battleship Y position: ");
        scanf("%f", &b.y);

        printf("Enter Battleship Max Velocity: ");
        scanf("%f", &b.maxVelocity);

        // Create battlefield
        battlefield(&D, &N);

        if (N > 100)
        {
            N = 100;
        }

        // Create E ships
        for (int i = 0; i < N; i++)
        {
            e[i].id = i + 1;

            int typeNumber =
                rand() % 5;

            if (typeNumber == 0)
            {
                e[i].type = 'A';
                e[i].minVelocity =
                    (rand() % 11);
                e[i].maxVelocity =
                    b.maxVelocity * 1.2f;
                e[i].minAngle =
                    rand() % 71;
                e[i].maxAngle =
                    e[i].minAngle + 20;
                e[i].impactPower = 0.08f;
            }
            else if (typeNumber == 1)
            {
                e[i].type = 'B';
                e[i].minVelocity =
                    (rand() % 11);
                e[i].maxVelocity =
                    b.maxVelocity *
                    (
                        0.8f +
                        (
                            rand() /
                            (float)RAND_MAX
                        ) * 0.4f
                    );
                e[i].minAngle =
                    rand() % 61;
                e[i].maxAngle =
                    e[i].minAngle + 30;
                e[i].impactPower = 0.06f;
            }
            else if (typeNumber == 2)
            {
                e[i].type = 'C';
                e[i].minVelocity =
                    (rand() % 11);
                e[i].maxVelocity =
                    b.maxVelocity *
                    (
                        0.8f +
                        (
                            rand() /
                            (float)RAND_MAX
                        ) * 0.4f
                    );
                e[i].minAngle =
                    rand() % 66;
                e[i].maxAngle =
                    e[i].minAngle + 25;
                e[i].impactPower = 0.07f;
            }
            else if (typeNumber == 3)
            {
                e[i].type = 'D';
                e[i].minVelocity =
                    (rand() % 11);
                e[i].maxVelocity =
                    b.maxVelocity *
                    (
                        0.8f +
                        (
                            rand() /
                            (float)RAND_MAX
                        ) * 0.4f
                    );
                e[i].minAngle =
                    rand() % 61;
                e[i].maxAngle =
                    e[i].minAngle + 30;
                e[i].impactPower = 0.05f;
            }
            else
            {
                e[i].type = 'E';
                e[i].minVelocity =
                    (rand() % 11);
                e[i].maxVelocity =
                    b.maxVelocity *
                    (
                        0.8f +
                        (
                            rand() /
                            (float)RAND_MAX
                        ) * 0.4f
                    );
                e[i].minAngle =
                    rand() % 61;
                e[i].maxAngle =
                    e[i].minAngle + 30;
                e[i].impactPower = 0.04f;
            }

            e[i].x =
                (
                    rand() /
                    (float)RAND_MAX
                ) * D;

            e[i].y =
                (
                    rand() /
                    (float)RAND_MAX
                ) * D;

            e[i].isDestroyed = 0;
            e[i].hasAttacked = 0;
        }

        // Get time between B gun firings
        float TB;

        printf(
            "\nEnter time between B gun firings: "
        );

        scanf("%f", &TB);

        if (TB <= 0)
        {
            printf(
                "Time must be greater than 0.\n"
            );

            continue;
        }

        // Run Part 1-A
        if (choice == 1)
        {
            part_2_A_battle(
                b,
                e,
                N,
                TB,
                0
            );
        }

        // Run Part 1-B Simulation 1
        else if (choice == 2)
        {
            int k;

            printf(
                "Enter number of movement points k: "
            );

            scanf("%d", &k);

            if (k <= 0)
            {
                printf(
                    "k must be greater than 0.\n"
                );

                continue;
            }

            float pathX[k];
            float pathY[k];

            // Create B movement path
            for (int i = 0; i < k; i++)
            {
                pathX[i] =
                    (
                        rand() /
                        (float)RAND_MAX
                    ) * D;

                pathY[i] =
                    (
                        rand() /
                        (float)RAND_MAX
                    ) * D;
            }

            part_2_A_battle_B(
                b,
                e,
                N,
                k,
                pathX,
                pathY,
                TB,
                1,
                0,
                0,
                0
            );
        }

        // Run Part 1-B Simulation 2
        else if (choice == 3)
        {
            int k;
            int t;
            float thetaMin;

            printf(
                "Enter number of movement points k: "
            );

            scanf("%d", &k);

            printf(
                "Enter jam start iteration t (t<k): "
            );

            scanf("%d", &t);

            printf(
                "Enter minimum angle thetaMin (0 - 30): "
            );

            scanf("%f", &thetaMin);

            if (k <= 1)
            {
                printf(
                    "k must be greater than 1.\n"
                );

                continue;
            }

            if (t <= 0 || t >= k)
            {
                printf(
                    "t must be between 0 and k.\n"
                );

                continue;
            }

            if (
                thetaMin <= 0 ||
                thetaMin >= 30
            )
            {
                printf(
                    "thetaMin must be between 0 and 30.\n"
                );

                continue;
            }

            float pathX[k];
            float pathY[k];

            // Create B movement path
            for (int i = 0; i < k; i++)
            {
                pathX[i] = (rand() /(float)RAND_MAX) * D;

                pathY[i] =(rand() /(float)RAND_MAX) * D;
            }

            part_2_A_battle_B(b,e,N,k,pathX,pathY,TB,2,t,thetaMin,0);
        }

        // Run Part 1-C Simulation A
        else if (choice == 4)
        {
            part_2_A_battle(b,e,N,TB,1);
        }

        // Run Part 1-C Simulation 1
        else if (choice == 5)
        {
            int k;

            printf(
                "Enter number of movement points k: "
            );

            scanf("%d", &k);

            if (k <= 0)
            {
                printf(
                    "k must be greater than 0.\n"
                );

                continue;
            }

            float pathX[k];
            float pathY[k];

            // Create B movement path
            for (int i = 0; i < k; i++)
            {
                pathX[i] = (rand() / (float)RAND_MAX) * D;

                pathY[i] = (rand() /(float)RAND_MAX) * D;
            }

            part_2_A_battle_B(b,e,N,k,pathX,pathY,TB,1,0,0,1);
        }

        // Run Part 1-C Simulation 2
        else if (choice == 6)
        {
            int k;
            int t;
            float thetaMin;

            printf(
                "Enter number of movement points k: "
            );

            scanf("%d", &k);

            printf(
                "Enter jam start iteration t (t<k): "
            );

            scanf("%d", &t);

            printf(
                "Enter minimum angle thetaMin(0 - 30): "
            );

            scanf("%f", &thetaMin);

            if (k <= 1)
            {
                printf(
                    "k must be greater than 1.\n"
                );

                continue;
            }

            if (t <= 0 || t >= k)
            {
                printf(
                    "t must be between 0 and k.\n"
                );

                continue;
            }

            if (
                thetaMin <= 0 ||
                thetaMin >= 30
            )
            {
                printf(
                    "thetaMin must be between 0 and 30.\n"
                );

                continue;
            }

            float pathX[k];
            float pathY[k];

            // Create B movement path
            for (int i = 0; i < k; i++)
            {
                pathX[i] =
                    (
                        rand() /
                        (float)RAND_MAX
                    ) * D;

                pathY[i] =
                    (
                        rand() /
                        (float)RAND_MAX
                    ) * D;
            }

            part_2_A_battle_B(b,e,N,k,pathX,pathY,TB,2,t,thetaMin,1);
        }

        printf("\nPress Enter to continue...");
        getchar();
        getchar();
	system("clear");

    } while (choice != 7);
}
