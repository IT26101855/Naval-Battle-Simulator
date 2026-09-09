#ifndef COMBAT_H
#define COMBAT_H
#include "sim.h"

void battle_calculations(struct Battleship, struct Escortship e[], int N);
int battle_calculations_B1(struct Battleship b, struct Escortship e[], int N, int iteration);
int battle_calculations_B2(struct Battleship b, struct Escortship e[], int N, int iteration,int jammed,float thetaMin);

//part 1 C functions
int battle_calculations_C_A(struct Battleship b,struct Escortship e[],int N);
int battle_calculations_C_B1(struct Battleship b,struct Escortship e[],int N,int iteration,float *cumulativeImpact);

int battle_calculations_C_B2(struct Battleship b,struct Escortship e[],int N,int iteration,int jammed,float thetaMin,float *cumulativeImpact);

#endif
