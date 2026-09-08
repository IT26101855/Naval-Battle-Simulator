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


 
    // Arrays for path points

    float pathX[k];
    float pathY[k];


    // Generate k random points inside battlefield

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


 
    // simulate each path point of the battleship

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


        // If B is destroyed, stop all remaining iterations

        if (bSunk == 1)
        {
            printf("\n");
            printf("---------------------------------------------------\n");
            printf(" Battleship SANK at iteration %d!\n", i + 1);
            printf(" Path simulation stopped.\n");
            printf("----------------------------------------------------\n");

            break;
        }


        
        // if B survived, continue to next point

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



