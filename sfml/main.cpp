/**
	* Render map only when press key
	* Modify to a method where dont need the map to render walls
	* */


// 2022-07-23

#include "config.h"

//------------------------------PLAYER-----------------------------------------//
void drawPlayer2D(sf::RenderWindow& window)
{
	sf::Color color = sf::Color::Yellow;

	// Player
	sf::RectangleShape rectangle(sf::Vector2f(8, 8));
	rectangle.setFillColor(color);
	rectangle.setPosition(px, py); // Move to px and py location

	// Player's Line
	sf::Vertex line[] = {{{px, py}, color}, {{px+pdx*20,py+pdy*20}, color}};

	window.draw(rectangle);
	window.draw(line, 2, sf::Lines);
}

int main() {
	// Anti aliasing
	// sf::ContextSettings settings;
	// settings.antialiasingLevel = 8;

	// Window (1020, 510)
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), SCREEN_TITLE);
	window.setFramerateLimit(SCREEN_FPS); // Framerate


	// Importing font
	sf::Font font;
	font.loadFromFile("assets/fonts/arial.ttf"); // Find font file
	

	// Fps
	sf::Clock clock;
	sf::Text FPS(" ", font, 26);
	FPS.setStyle(sf::Text::Bold);
	FPS.setFillColor(sf::Color::Green);

	init();

	while(window.isOpen()) {
		// To not list keys when window don't has focus
		if(!window.hasFocus()) continue;

		sf::Event event;
		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed) window.close();
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close(); // Close window with ESC
		}

		// FPS
		float currentTime = clock.restart().asSeconds();
		fps = 1/currentTime;
		FPS.setString(std::to_string(fps));


		// Movement
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			pa+=psd/* *fps*/; pa=FixAng(pa); pdx=cos(degToRad(pa)); pdy=-sin(degToRad(pa));
		} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			pa-=psd/* *fps*/; pa=FixAng(pa); pdx=cos(degToRad(pa)); pdy=-sin(degToRad(pa));
		}


		// - Collision - //
		/**
		 * Find a dot position in front of the player and check the map if that square is empty
		 * If is empty then move the player in the X or Y position
		 * */

		int xo, yo; // Offset
		// 20 units in front of the player depending of the player direction
		if(pdx<0) { xo=-20; } else { xo=20; }
		if(pdy<0) { yo=-20; } else { yo=20; }

		int ipx=px/64.0, // Player grid positin
			ipx_add_xo=(px+xo)/64.0, // Position plus the X offset
			ipx_sub_xo=(px-xo)/64.0; // Position minus the X offset

		// Same for Y position
		int ipy=py/64.0,
			ipy_add_yo=(py+yo)/64.0,
			ipy_sub_yo=(py-yo)/64.0;


		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			// Front & Back Colision
			if(mapW[ipy*mapX+ipx_add_xo]==0) { px+=pdx*psd/* *fps*/; } // Horizontal Foward
			if(mapW[ipy_add_yo*mapX+ipx]==0) { py+=pdy*psd/* *fps*/; } // Vertical Foward
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			// Front & Back Colision
			if(mapW[ipy*mapX+ipx_sub_xo]==0) { px-=pdx*psd/* *fps*/; } // Horizontal Foward
			if(mapW[ipy_sub_yo*mapX+ipx]==0) { py-=pdy*psd/* *fps*/; } // Vertical Foward
		}

		/**
		 * If the player's offset is in a square of a value of 4
		 * Change that value to 0
		 *  Turning the wall in a empty space
		 * */
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::E) && sp[0].state==0) { // Open door if sprite is off
			if(pdx<0) { xo=-25; } else { xo=25; }
			if(pdy<0) { yo=-25; } else { yo=25; }

			// If the player's X and Y position plus offset in the map is four, set the same value to 0
			if(mapW[ipy_add_yo*mapX+ipx_add_xo]==4) { mapW[ipy_add_yo*mapX+ipx_add_xo]=0; }
		}


		
		// window.clear(sf::Color::White);
		window.clear();
			// drawSky();

			drawRay(window);
			drawSprite();
			drawCords(window, font);
			window.draw(FPS);
		window.display();
	}
}













/**
 * 
 * --- Almost everything about angles explained of the dumbest way possible ---
 * --- All you need to know to undestand what is going on ---
 * - Programming langues use SIN and COS use Radians values intead of degrees values
 * 	- Degrees - 0 (Start), 90 (Top), 180 (Left), 270 (Bottom), 360 (One turn)
 * 	- Radians - 0 (Start), PI/2 (Top), PI (Left), 3*PI/2 (Bottom), 2/PI
 * - A circumference goes anti-clockwise
 * - Recommended to search images of this terms
 * 
 * (X is horizontall and Y is vertical)
 * PI is the base to calculate circumference, with a is a full angle
 * 
 * --- Circumference ---
 * Circumference = Circle or a Spheare
 * (D)iameter -> From left to right of a circle
 * (R)adius -> Straight line from the center to te cirumference of a circle
 * 
 * Circumference is = PixD or 2xPixR
 * Area is = PixR²
 * 
 * --- Angles ---
 * 0 is 0º angle
 * 1xPI (Just PI) Is a 180º angle
 * So 2xPi is a 360º angle
 * If this is the case so PI/2 is a 90º angle
 * And 3*PI/2 is a 270º
 * 
 * 
 * --- SIN and COS ---
 * - COS -
 * Cos is basically a horizontal line from the middle of a circumference
 * Unlike the radius, the COS dont necessarily goes till the end of a circumference
 * 
 * - SIN -
 * If the COS is the horizontal line, the SIN is te vertical
 * 
 * - Example - 
 * 			   O <- COS, SIN
 * 		      /|
 * 		     / |
 * 		    /  | 
 * 		   /   |
 * 	 	  /    |
 * 	 	 /     |
 * 	 	/      | a
 *   c /       | 
 *    /        |
 *   /         | <- SIN
 *  /)α    90º_|
 * /_)_______|_|
 * 	^  b
 * 	|
 * 	COS
 * 
 * a -> Height
 * b -> Base
 * c  -> hypotenuse
 * 
 * To get the hypotenuse we use the Pythagorean Theorem
 * c = √(a²+b²) or c²=a²+b²
 * 
 * SIN(α) = a/c
 * COS(α) = b/c
 * TAN(α) = a/b
*/