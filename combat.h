#ifndef COMBAT_H
#define COMBAT_H

struct Battleship {
    char type;
    float x;
    float y;
    float maxVelocity;
};

struct Escortship {
    int id;
    char type;
    float x;
    float y;
    float minAngle;
    float maxAngle;
    float minVelocity;
    float maxVelocity;
    int isDestroyed; // 1 = Destroyed, 0 = Active
};

void battle_calculations(struct Battleship b, struct Escortship e[], int N);

#endif
