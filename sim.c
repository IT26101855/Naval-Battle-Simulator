#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sim.h"
#include "battlefield.h"

// Data structure of battleship
struct Battleship {
    char type;
    float x;
    float y;
    float maxVelocity;
};

// Data structure of escort ships
struct Escortship {
    int id;
    char type;
    float x;
    float y;
    float minVelocity;
    float maxVelocity;
    float minAngle;
    float maxAngle;
    float impactPower;
    int isDestroyed;
};

// Part 1 A simulation function
void part_1_A() {
    system("clear");
    printf("                                         Start\n\n\n");
    printf("                                 Part-1-A Simulation\n\n");

    struct Battleship b;

    // Getting the details of the battleship
    printf("Enter Battleship Type (U M R S): ");
    scanf(" %c", &b.type);

    printf("Enter Battleship's X Position: ");
    scanf("%f", &b.x);

    printf("Enter Battleship's Y Position: ");
    scanf("%f", &b.y);

    printf("Enter Battleship's Max Velocity: ");
    scanf("%f", &b.maxVelocity);

    // Displaying the details of the battleship
    printf("\n----- Battle Ship Information -----\n");
    printf("Type: %c\n", b.type);
    printf("Position: (%.2f, %.2f)\n", b.x, b.y);
    printf("Max Velocity: %.2f\n", b.maxVelocity);
    
    getchar();
    getchar();
    system("clear");

    // Battlefield dimensions and Escort ships count inputs
    float D;
    int N;
    printf("Enter Battlefield dimensions (D): ");
    scanf("%f", &D);
    printf("Enter Number of Escort Ships (N): ");
    scanf("%d", &N);

    struct Escortship e[N];
    char types[] = {'A', 'B', 'C', 'D', 'E'};

    // Random Number Seed Generator
    srand(time(NULL));

    // Generating Escort Ships
    for (int i = 0; i < N; i++) {
        e[i].id = i + 1;

        // Randomly pick ship type from A to E
        e[i].type = types[rand() % 5];

        // Randomly generate (x, y) coordinates within Canvas (0 to D)
        e[i].x = ((float)rand() / RAND_MAX) * D;
        e[i].y = ((float)rand() / RAND_MAX) * D;

        // Assign specific values based on Escort Ship Type
        switch(e[i].type) {
            case 'A':
                e[i].impactPower = 0.08f;
                e[i].minAngle = ((float)rand() / RAND_MAX) * 70.0f;
                e[i].maxAngle = e[i].minAngle + 20.0f;
                e[i].minVelocity = ((float)rand() / RAND_MAX) * 10.0f;
                e[i].maxVelocity = 1.2f * b.maxVelocity;
                break;

            case 'B':
                e[i].impactPower = 0.06f;
                e[i].minAngle = ((float)rand() / RAND_MAX) * 60.0f;
                e[i].maxAngle = e[i].minAngle + 30.0f;
                e[i].minVelocity = ((float)rand() / RAND_MAX) * 10.0f;
                e[i].maxVelocity = ((float)rand() / RAND_MAX) * b.maxVelocity;
                break;

            case 'C':
                e[i].impactPower = 0.07f;
                e[i].minAngle = ((float)rand() / RAND_MAX) * 65.0f;
                e[i].maxAngle = e[i].minAngle + 25.0f;
                e[i].minVelocity = ((float)rand() / RAND_MAX) * 10.0f;
                e[i].maxVelocity = ((float)rand() / RAND_MAX) * b.maxVelocity;
                break;

            case 'D':
                e[i].impactPower = 0.05f;
                e[i].minAngle = ((float)rand() / RAND_MAX) * 40.0f;
                e[i].maxAngle = e[i].minAngle + 50.0f;
                e[i].minVelocity = ((float)rand() / RAND_MAX) * 10.0f;
                e[i].maxVelocity = ((float)rand() / RAND_MAX) * b.maxVelocity;
                break;

            case 'E':
                e[i].impactPower = 0.04f;
                e[i].minAngle = ((float)rand() / RAND_MAX) * 20.0f;
                e[i].maxAngle = e[i].minAngle + 70.0f;
                e[i].minVelocity = ((float)rand() / RAND_MAX) * 10.0f;
                e[i].maxVelocity = ((float)rand() / RAND_MAX) * b.maxVelocity;
                break;
        }
        e[i].isDestroyed = 0;
    }

    // Display Generated Escort Ships Information
    printf("\n----- Generated Escort Ships -----\n");
    for (int i = 0; i < N; i++) {
        printf("ID: %d | Type: E_%c | Position: (%.2f, %.2f) | Max Vel: %.2f\n",
               e[i].id, e[i].type, e[i].x, e[i].y, e[i].maxVelocity);

    } 

    getchar();
    getchar();
    system("clear");
}
