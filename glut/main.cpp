// 2022-07-23

#include "config.h"

ButtonKeys Keys;
float frame1, frame2;
void display() {  
	// Frames per second
	frame2=glutGet(GLUT_ELAPSED_TIME); fps=(frame2-frame1); frame1=glutGet(GLUT_ELAPSED_TIME); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	// Movement
	if(Keys.a==1) {
		pa+=psd*fps; pa=FixAng(pa); pdx=cos(degToRad(pa)); pdy=-sin(degToRad(pa));
	} else if(Keys.d==1) { pa-=psd*fps; pa=FixAng(pa); pdx=cos(degToRad(pa)); pdy=-sin(degToRad(pa)); }



	// - Collision - //
	/**
	 * Find a dot position in front of the player and check the map if that square is empty
	 * If is empty then move the player in the X or Y position
	 */
	int xo=0; int yo=0; // Offset
	// 20 units in front of the player depending of the player direction
	if(pdx<0) { xo=-20; } else{ xo=20; } // X offset to check map
	if(pdy<0) { yo=-20; } else{ yo=20; } // Y offset to check map

	int ipx=px/64.0, // Player grid positin
		ipx_add_xo=(px+xo)/64.0, // Position plus the X offset
		ipx_sub_xo=(px-xo)/64.0; // Position minus the X offset

	// Same for Y position
	int ipy=py/64.0,
		ipy_add_yo=(py+yo)/64.0,
		ipy_sub_yo=(py-yo)/64.0;


	if(Keys.w==1) { // Move forward
		// Front & Back Colision
		if(mapW[ipy*mapX        + ipx_add_xo]==0) { px+=pdx*psd*fps; } // Horizontal Foward
		if(mapW[ipy_add_yo*mapX + ipx       ]==0) { py+=pdy*psd*fps; } // Vertical Foward
	} else if(Keys.s==1) { // Move backward
		// Front & Back Colision
		if(mapW[ipy*mapX        + ipx_sub_xo]==0) { px-=pdx*psd*fps; } // Horizontal Foward
		if(mapW[ipy_sub_yo*mapX + ipx       ]==0) { py-=pdy*psd*fps; } // Vertical Foward
	} 

	// Draw Things
	// drawSky();
	drawRay();
	drawSprite();

	// Glut buffers
	glutPostRedisplay();
	glutSwapBuffers();
}


void ButtonDown(unsigned char key, int x, int y) { // Keyboard button pressed down
	if(key=='a') Keys.a=1;
	if(key=='d') Keys.d=1;
	if(key=='w') Keys.w=1;
	if(key=='s') Keys.s=1;


	/**
	 * If the player's offset is in a square of a value of 4
	 * Change that value to 0
	 *  Turning the wall in a empty space
	 */
	if(key=='e' && sp[0].state==0) { // Open door if sprite is off
		int xo=0; if(pdx<0) { xo=-25; } else { xo=25; }
		int yo=0; if(pdy<0) { yo=-25; } else { yo=25; } 
		int ipx=px/64.0, ipx_add_xo=(px+xo)/64.0;
		int ipy=py/64.0, ipy_add_yo=(py+yo)/64.0;

		// If the player's X and Y position plus offset in the map is four, set the same value to 0
		if(mapW[ipy_add_yo*mapX+ipx_add_xo]==4){ mapW[ipy_add_yo*mapX+ipx_add_xo]=0;}
	}

	glutPostRedisplay();
}

void ButtonUp(unsigned char key,int x,int y) { // Keyboard button pressed up
	if(key=='a') Keys.a=0;
	if(key=='d') Keys.d=0;
	if(key=='w') Keys.w=0;
	if(key=='s') Keys.s=0;
	glutPostRedisplay();
}

void resize(int w,int h) { // Screen window rescaled, snap back
	glutReshapeWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
}


int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition( glutGet(GLUT_SCREEN_WIDTH)/2-SCREEN_WIDTH/2, glutGet(GLUT_SCREEN_HEIGHT)/2-SCREEN_HEIGHT/2 ); // Start window at the center of screen
	glutCreateWindow(SCREEN_TITLE);
	init();
	gluOrtho2D(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	// window.setFramerateLimit(SCREEN_FPS); // Framerate

	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(ButtonDown);
	glutKeyboardUpFunc(ButtonUp);
	glutMainLoop();
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