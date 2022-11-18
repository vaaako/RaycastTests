#ifndef DRAW_H // To make sure you don't declare the function more than once by including the header multiple times.
#define DRAW_H

#include "../config.h"


// Draw
void DrawLine(sf::RenderWindow& window, sf::Vector2f start, sf::Vector2f end, float thickness, sf::Color color);
void DrawPoint(sf::Vector2i cord, int thickness, sf::Color color);

void drawCords(sf::RenderWindow& window, sf::Font font);
void drawSky();

sf::Color getColor(int image[], int pixel, int shade=1);


#endif
