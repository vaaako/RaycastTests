#include "draw.h"
#include "../assets/textures/sky.ppm"

// Draw Line with thickness (SFML)
void DrawLine(sf::RenderWindow& window, sf::Vector2f start, sf::Vector2f end, float thickness, sf::Color color) {
	sf::Vector2f dv = end - start;
	float dl = (float)sqrt(dv.x * dv.x + dv.y * dv.y);

	sf::Vector2f uv = dv / dl;
	sf::Vector2f up = sf::Vector2f(-uv.y, uv.x);
	sf::Vector2f offset = up * (thickness / 2.0f);

	sf::Vertex vert[]=
	{
		sf::Vertex(start + offset, color),
		sf::Vertex(end   + offset, color),
		sf::Vertex(end   - offset, color),
		sf::Vertex(start - offset, color)
	};

	window.draw(vert, 4, sf::Quads);
}

void DrawPoint(sf::Vector2i cord, int thickness, sf::Color color) {
	glPointSize(thickness); glColor3ub(color.r, color.g, color.b); glBegin(GL_POINTS); glVertex2i(cord.x, cord.y); glEnd();
}


// -- Draw Things -- //
// Draw sky and rotate based on player rotation
void drawSky() {
	int x,y;
	for(y=0;y<40;y++) 	{
		for(x=0;x<120;x++) {
			int xo=(int)pa*2-x; if(xo<0){ xo+=120;} xo=xo % 120; // Return 0-120 based on player angle
			int pixel=(y*120+xo)*3;

			DrawPoint(sf::Vector2i(x*8, y*8), 8, getColor(sky, pixel));
		}
	}
}


void drawCords(sf::RenderWindow& window, sf::Font font) {
	// Cords
	sf::Text text(
	"X: "   + std::to_string(px)+ 
	"\nY: " + std::to_string(py)+ 
	"\nA: " + std::to_string(pa), 
	font, 20);

	text.setPosition(SCREEN_WIDTH-150, SCREEN_HEIGHT-110);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::Red);

	window.draw(text);
}

// -- Utility -- //
sf::Color getColor(int image[], int pixel, int shade) {
	return sf::Color(image[pixel+0]*shade, image[pixel+1]*shade, image[pixel+2]*shade); // Red, Green, Blue
}