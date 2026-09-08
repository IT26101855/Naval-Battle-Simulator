#ifndef SIM_H
#define SIM_H

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
    int isDestroyed;
};

void part_1_A();

void simulation_part_B_1();
void simulation_part_B_2();

#endif
