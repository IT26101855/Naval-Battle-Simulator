#ifndef SIMULATION_H
#define SIMULATION_H

struct Battleship
{
    char type;
    float x;
    float y;
    float maxVelocity;
};

struct Escortship
{
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

void part_1_A();

#endif
