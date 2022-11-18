#include "raycast.h"
#include "../assets/textures/All_Textures.ppm"


void drawRay(sf::RenderWindow& window) {
	sf::Color color;

	int r,mx,my,mp,dof,side; // Rays, MapX, MapY, MapItem, ?, ?
	float vx,vy,rx,ry,ra,xo,yo,disV,disH; // VerticalRay-X, VerticalRay-Y, RayX, RayY, RayAngle, ?, ?, Vertical Distance, Horizontal Distance
	
	// If we initialize a Ray angle back one degree from our player angle wich should add our limits to the next angle
	// Move back 30º degrees (Divide by 30 Rays for each side)
	ra=FixAng(pa+30); // Ray set back 30 degrees
	
	for(r=0;r<120;r++) { //60
		int vmt=0, hmt=0; // Vertical and Horizontal map texture number
		//---Vertical---//
		// Find first vertical line

		dof=0; side=0;
		// We are looking for the shortest distance, so the default value is high
		disV=100000; // Vertical Distance

		float Tan=tan(degToRad(ra)); // Tanghent of the value of the Ray Angle

		// Since is vertical lines, we need to know know if the Ray is facing left or right or up and down
		// Looking left
		if(cos(degToRad(ra))> 0.001) {
			rx=(((int)px>>6)<<6)+64;
			ry=(px-rx)*Tan+py; xo= 64; yo=-xo*Tan;
		// Looking right
		} else if(cos(degToRad(ra))<-0.001) {
			rx=(((int)px>>6)<<6)-0.0001;
			ry=(px-rx)*Tan+py; xo=-64; yo=-xo*Tan;
		// Looking up or down. no hit  
		} else {
			rx=px; ry=py; dof=8;
		} 


		while(dof<8) // To not loop forever, check to 8
		{ 
			// We know the large coordinates where the Ray will hit the wall
			// But wee need to know where that is in the map array
			mx=(int)(rx)>>6; my=(int)(ry)>>6;
			mp=my*mapX+mx;

			// If the map positionis less than the array size we can check it inside the map
			if(mp>0 && mp<mapX*mapY && mapW[mp]>0) {
				vmt=mapW[mp]-1;
				dof=8; // End Loop
				disV=cos(degToRad(ra))*(rx-px)-sin(degToRad(ra))*(ry-py); // Hit
			}

			// Next line
			// If dont hit the wall, to check the next horiziontal line is add the X&Y offset
			// Then will check all lines until hit a wall, wich stop the loop and the line check
			else{ rx+=xo; ry+=yo; dof+=1;} // Check next horizontal 
		}
		vx=rx; vy=ry; // Vertical Ray X&V

		//---Horizontal---//
		dof=0;
		disH=100000; // Horizontal Distance
		Tan=1.0/Tan; // Tangent of the value of the Ray Angle
		
		if(sin(degToRad(ra))> 0.001) { // Looking up
			ry=(((int)py>>6)<<6)-0.0001;
			rx=(py-ry)*Tan+px; yo=-64; xo=-yo*Tan;
		} else if(sin(degToRad(ra))<-0.001) { // Looking down
			ry=(((int)py>>6)<<6)+64;
			rx=(py-ry)*Tan+px; yo= 64; xo=-yo*Tan;
		} else{ rx=px; ry=py; dof=8; } // Looking straight left or right
	

		while(dof<8) 
		{ 
			mx=(int)(rx)>>6; my=(int)(ry)>>6;
			mp=my*mapX+mx;

			if(mp>0 && mp<mapX*mapY && mapW[mp]>0) {
				hmt=mapW[mp]-1;
				dof=8; disH=cos(degToRad(ra))*(rx-px)-sin(degToRad(ra))*(ry-py); // Hit
			} else { rx+=xo; ry+=yo; dof+=1; } // Check next horizontal
		} 


		// Vertical vall hit
		// We want the sortest distance
		// So if the vertical or horizontal is sorter then we set the Ray to that variable
		float shade=1;
		color = sf::Color(0, 255, 0); // Default Color
		if(disV<disH) { // Horizontal hit first
			hmt=vmt;
			shade=0.5; // Shading
			rx=vx; ry=vy; disH=disV;
			color = sf::Color(0, 200, 0); // Far color ("Light")
		}

		// Ray
		// sf::Vertex ray[] = {{{px, py}, color}, {{rx, ry}, color}};
		// window.draw(ray, 2, sf::Lines);

		// --- Draw 3D Walls --- //
		// Fix fisheyes (The center is heigher)
		// This occurs because the further rays are a longer distance than the center rays
		int ca=FixAng(pa-ra); // Distance between the player angle and the Ray angle
		disH=disH*cos(degToRad(ca)); // Fix fisheye
		
		// Line height and limit
		/**
		 *  Window is 320x160
		 * So the formula for each line height will be the cube size times
		 * the new screen height divided by that Ray distance
		 * So he further away the larger the distance the shorter the final line
		 * height will be
		 * 
		 * 
		 * r*8+530
		 *   8 - Distance between the lines
		 * 	 530 - Where the left screen start (after the map)
		 */

		int lineH=(mapS*SCREEN_HEIGHT)/(disH);

		float ty_step=32.0/(float)lineH;

		// Offset bariable to be half the difference between the screen height and line height
		// This prevent a visual effect that we don't want
		float ty_off=0;
		if(lineH>SCREEN_HEIGHT){ ty_off=(lineH-SCREEN_HEIGHT)/2.0; lineH=SCREEN_HEIGHT; }
		int lineOff = SCREEN_HEIGHT/2 - (lineH>>1); // Set the lines to the screen center
		depth[r]=disH; // Save this line's depth


		// --- Draw Walls --- //
		// Draw individual pixels (instead of lines) of textures
		int y;
		// Add 32 to go to the next texture
		float ty=ty_off*ty_step;//+hmt*32; // Texture's Y value
		
		// Fix textures X and Y (Put texture in all walls)
		float tx;
		if(shade==1) {
			// Divide by two since textures are half the size and finde remainder of an integer division of 32
			tx=(int)(rx/2.0)%32;

			if(ra>180) { tx=31-tx; } // Flip texture
		} else {
			tx=(int)(ry/2.0)%32;
			if(ra>90 && ra<270) { tx=31-tx; } // Flip texture
		} 


		// --- Draw Walls --- //
		int pixel, red, green, blue;
		for(y=0; y<lineH; y++) {
			// Using ppm
			pixel=((int)ty*32+(int)tx)*3+(hmt*32*32*3);
			red   =All_Textures[pixel+0]*shade;
			green =All_Textures[pixel+1]*shade;
			blue  =All_Textures[pixel+2]*shade;
			DrawPoint(sf::Vector2i(r*8, y+lineOff), 8, sf::Color(red, green, blue));//getColor(All_Textures, pixel, shade));

			ty+=ty_step;
		}
		// Draw Line every 8 pixel and shift the window over the right side
		// DrawLine(window, sf::Vector2f(r*8+530, lineOff), sf::Vector2f(r*8+530, lineH+lineOff), 8, color);


		// --- Draw Floors --- //
		// Start drawing at the bottom of the wall (lineOff+lineH) and go to the screen's edge (320)

		/**
		 * We can find the point where the ray hits the floor in the world space by using trigonometry
		 * And project that point onto the screen space
		 * */

		for(y=lineOff+lineH; y<SCREEN_HEIGHT; y++) {
			float dy=y-(SCREEN_HEIGHT/2.0), deg=degToRad(ra), raFix=cos(degToRad(FixAng(pa-ra)));

			// Find texture's X value with the formula and same for the texture's Y position
			tx=px/2 + cos(deg)*158*2*32/dy/raFix;
			ty=py/2 - sin(deg)*158*2*32/dy/raFix;

			// We can loop up the tx and ty within the texture array
			// To find the exact texture map let's use the and operator an 31 since out textures are 32 pixels wide
			
			// Using ppm
			int mp=mapF[(int)(ty/32.0)*mapX+(int)(tx/32.0)]*32*32;
			pixel=(((int)(ty)&31)*32 + ((int)(tx)&31))*3+mp*3;
			red   =All_Textures[pixel+0]*0.7;
			green =All_Textures[pixel+1]*0.7;
			blue  =All_Textures[pixel+2]*0.7;
			DrawPoint(sf::Vector2i(r*8, y), 8, sf::Color(red, green, blue));

			// --- Draw Ceiling ---//
			mp=mapC[(int)(ty/32.0)*mapX+(int)(tx/32.0)]*32*32;
			pixel=(((int)(ty)&31)*32 + ((int)(tx)&31))*3+mp*3;

			// Subtract screen height from y to draw it above the walls
			// Just draw ceiliing if mp is above 0
			if(mp>0) { DrawPoint(sf::Vector2i(r*8, SCREEN_HEIGHT-y), 8, getColor(All_Textures, pixel)); };
		}


		// ra=FixAng(ra-1); // When done, go to next ray 1º degree away
		ra=FixAng(ra-0.5);
	}
}