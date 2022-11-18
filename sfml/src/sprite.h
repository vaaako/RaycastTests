#ifndef SPRITE_H // To make sure you don't declare the function more than once by including the header multiple times.
#define SPRITE_H

#include "../config.h"

struct sprite// All veriables per sprite
{
	int type;    // Static, key, enemy
	int state;   // On, off
	int map;     // Texture to show
	float x,y,z; // Position
};

extern sprite sp[];
extern int depth[]; // Hold wall line depth to compare for sprite depth


void drawSprite(void);

#endif
