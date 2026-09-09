#ifndef COMBAT_H
#define COMBAT_H
#include "sim.h"

//part 1 A function
void battle_calculations(struct Battleship, struct Escortship e[], int N);

//part 1 B functions
int battle_calculations_B1(struct Battleship b, struct Escortship e[], int N, int iteration); //part 1 B sim 1
int battle_calculations_B2(struct Battleship b, struct Escortship e[], int N, int iteration,int jammed,float thetaMin); //part 1 B sim 2

//part 1 C functions
int battle_calculations_C_A(struct Battleship b,struct Escortship e[],int N); //part 1 C (part 1 A)
int battle_calculations_C_B1(struct Battleship b,struct Escortship e[],int N,int iteration,float *cumulativeImpact); //part 1 C (part 1 B sim 1)
int battle_calculations_C_B2(struct Battleship b,struct Escortship e[],int N,int iteration,int jammed,float thetaMin,float *cumulativeImpact); //part 1 C (part 1 B sim 2)

//part 2 A functions

void part_2_A_battle(struct Battleship b,struct Escortship e[],int N,
    float TB,
    int useImpactPower
);

void part_2_A_battle_B(struct Battleship b,struct Escortship e[],int N,int k,
    float pathX[],
    float pathY[],
    float TB,
    int simulationType,
    int t,
    float thetaMin,
    int useImpactPower
);

#endif
