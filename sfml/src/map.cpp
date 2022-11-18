#include "map.h"

int mapW[] = // The map array. Edit to change level but keep the outer walls
{
	1, 1, 1, 1, 1, 1, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	4, 0, 0, 0, 0, 0, 0, 2,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 0, 1,
};

int mapF[]= // Floors
{
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 2, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 
};

int mapC[]= // Ceiling
{
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 
};




void drawMap2D(sf::RenderWindow& window) { // Get window as parameter to draw from inside function
	int x, y, xo, yo;
	sf::Color color; // SFML declare color variable

	for(y=0; y<mapY; y++) {
		for(x=0; x<mapX; x++) {
			if(mapW[y*mapX+x]>0) { // If current map's item
				color=sf::Color::White; // White
			} else { color=sf::Color::Black; }

			xo=x*mapS; yo=y*mapS;
			
			sf::RectangleShape rectangle(sf::Vector2f(mapS-1, mapS-1));
			rectangle.setFillColor(color); // Set color depending of the index
			rectangle.setPosition(xo, yo); // Move to px and py location
			
			window.draw(rectangle); // Draw
		}
	}
}