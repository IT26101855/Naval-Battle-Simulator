#ifndef COMBAT_H
#define COMBAT_H
#include "sim.h"

void battle_calculations(struct Battleship, struct Escortship e[], int N);
int battle_calculations_B1(struct Battleship b, struct Escortship e[], int N, int iteration);
int battle_calculations_B2(struct Battleship b, struct Escortship e[], int N, int iteration,int jammed,float thetaMin);


#endif
