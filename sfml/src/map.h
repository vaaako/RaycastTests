#ifndef MAP_H // To make sure you don't declare the function more than once by including the header multiple times.
#define MAP_H

#include "../config.h"

#define mapX  8      // Map width
#define mapY  8      // Map height
#define mapS 64      // Map cube size

extern int mapW[], mapF[], mapC[];


void drawMap2D(sf::RenderWindow& window);

#endif
