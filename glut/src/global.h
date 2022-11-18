#ifndef GLOBAL_H // To make sure you don't declare the function more than once by including the header multiple times.
#define GLOBAL_H

#include "../config.h"

typedef struct
{
	int w, a, d, s; // Button state on off
} ButtonKeys;


extern float px, py, pdx, pdy, pa, psd; // PlayerX, PlayerY, PlayerDelta-X, PlayerDelta-Y, PlayerAngle, PlayerSpeed
extern float fps;

void init(void); // Init all variables when game starts

// Calc
float degToRad(float a);
float FixAng(float a);

// Return distance between the player and rays end point
// That is the hypotenus
// So we can use Pythagorean Theorem
float dist(float ax, float ay, float bx, float by, float ang);

#endif
