#include "global.h"

//-- Gloabal Variables --//
float px, py, pdx, pdy, pa, psd; // PlayerX, PlayerY, PlayerDelta-X, PlayerDelta-Y, PlayerAngle, PlayerSpeed
float fps;


//-- Init Function --//
sprite sp[4];
int depth[120]; // Hold wall line depth to compare for sprite depth
// void init() {//init all variables when game starts
// 	// Player default values
// 	// px=150; py=400; pa=90, psd=8;//psd=0.5;//0.2
// 	px=250; py=225; pa=180, psd=8;//psd=0.5;//0.2
// 	pdx=cos(degToRad(pa)); pdy=-sin(degToRad(pa));


// 	sp[0].type=1; sp[0].state=1; sp[0].map=0; sp[0].x=1.5*64; sp[0].y=5*64;   sp[0].z=20; // Key
// 	sp[1].type=2; sp[1].state=1; sp[1].map=1; sp[1].x=3*64;   sp[1].y=5.5*64; sp[1].z=20; // Light 1
// 	// sp[2].type=2; sp[2].state=1; sp[2].map=1; sp[2].x=3.5*64; sp[2].y=4.5*64; sp[2].z= 0; // Light 2
// 	// sp[3].type=3; sp[3].state=1; sp[3].map=2; sp[3].x=2.5*64; sp[3].y=2*64;   sp[3].z=20; // Enemy
// }

void init()//init all variables when game starts
{
	glClearColor(0.3,0.3,0.3,0);
	px=192; py=224; pa=180; psd=0.1;
	pdx=cos(degToRad(pa)); pdy=-sin(degToRad(pa)); // Init player
	// mapW[19]=4; mapW[26]=4; // Close doors

	// 	// Z = 20 -> Down // Z = 0 -> Up
	sp[0].type=1; sp[0].state=1; sp[0].map=0; sp[0].x=1.5*64; sp[0].y=5*64;   sp[0].z=20; // Key
	sp[1].type=2; sp[1].state=1; sp[1].map=1; sp[1].x=1.5*64; sp[1].y=4.5*64; sp[1].z= 0; // Light 1
	sp[2].type=2; sp[2].state=1; sp[2].map=1; sp[2].x=3.5*64; sp[2].y=4.5*64; sp[2].z= 0; // Light 2
	sp[3].type=3; sp[3].state=1; sp[3].map=2; sp[3].x=2.5*64; sp[3].y=2*64;   sp[3].z=20; // Enemy
}

//-- GLobal Functions --//
float degToRad(float a) { return a*M_PI/180.0; } // M_PI = 3.14159 (math.h)
float FixAng(float a) { if(a>359) { a-=360;} if(a<0){ a+=360;} return a; }
