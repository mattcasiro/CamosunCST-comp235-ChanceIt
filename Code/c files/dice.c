#include "../interfaces/random.h"
#include "../interfaces/dice.h"
#define MIN    1
#define MAX    6

int rollDie(){
    int rollNum = getRandomInt(MIN, MAX);
    return rollNum;
}
