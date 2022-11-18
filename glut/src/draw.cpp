#include "draw.h"
#include "../assets/textures/sky.ppm"

void DrawPoint(int x, int y, int thickness, int image[], int pixel, int shade) {
	glPointSize(thickness); glColor3ub(image[pixel+0]*shade, image[pixel+1]*shade, image[pixel+2]*shade); glBegin(GL_POINTS); glVertex2i(x, y); glEnd();
}

// -- Draw Things -- //
// Draw sky and rotate based on player rotation
void drawSky() {
	int x,y;
	for(y=0;y<40;y++) 	{
		for(x=0;x<120;x++) {
			int xo=(int)pa*2-x; if(xo<0){ xo+=120;} xo=xo % 120; // Return 0-120 based on player angle
			int pixel=(y*120+xo)*3;

			glPointSize(8); glColor3ub(sky[pixel+0],sky[pixel+1],sky[pixel+2]); glBegin(GL_POINTS); glVertex2i(x*8,y*8); glEnd();
		}
	}
}


// void drawCords(sf::RenderWindow& window, sf::Font font) {

// 	// Cords
// 	sf::Text text(
// 	"X: "   + std::to_string(px)+ 
// 	"\nY: " + std::to_string(py)+ 
// 	"\nA: " + std::to_string(pa), 
// 	font, 20);

// 	text.setPosition(SCREEN_WIDTH-150, SCREEN_HEIGHT-110);
// 	text.setStyle(sf::Text::Bold);
// 	text.setFillColor(sf::Color::Red);

// 	window.draw(text);
// }

// -- Utility -- //
// Color getColor(int image[], int pixel, int shade) {
// 	return { image[pixel+0]*shade, image[pixel+1]*shade, image[pixel+2]*shade }; // Red, Green, Blue
// }