//
//  main.cpp
//  TrivialGLUT
//
//  Created by research on 5/8/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <sstream>
#include <iostream>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include "fpsclock.h"
#include "arcball.h"
#include "glutils.h"

using namespace std;

// Glut window ids
int mainWindow;

float	rtri;						// Angle For The Triangle
float	rquad;						// Angle For The Quad
Clock wallClock;
FPSClock fpsClock;
int windowWidth = 640;
int windowHeight = 480;
const vec eye( 0.0f, 0.0f, 20.0f );
const vec centre( 0.0f, 0.0f, 6.0f );
const vec up( 0.0f, 1.0f, 0.0f );
const float SPHERE_RADIUS = 5.0f;

int mousex = 0;
int mousey = 0;


//--------------------------
// Initialize rendering ctxt
//--------------------------
void initGL ( void )     // Create Some Everyday Functions
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glEnable ( GL_COLOR_MATERIAL );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glEnable(GL_CULL_FACE);
}


//--------------------------
// Update Frames Per Second
//--------------------------
void updateFPS(void) {
  double fps = fpsClock.update();
  char message[50];
  sprintf(message, "fps: %3.2f", fps);
  RenderBitmapFontString(0, windowHeight - 0,
                         GLUT_BITMAP_HELVETICA_18, 
                         reinterpret_cast<const unsigned char*>(message));
}

//--------------------------
// Draw objects
//--------------------------
void drawScene(void) {
  glPushMatrix();  
  glTranslatef(0,0.0f,0.0f);				// Move Right 1.5 Units And Into The Screen 6.0
  drawColoredCube();
  glPopMatrix();
}

//--------------------------
// Draw function every frame
//--------------------------
void display ( void )   // Create The Display Function
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
  glLoadIdentity();									// Reset The Current Modelview Matrix
  
  arcball_rotate();
  drawScene();
  updateFPS();
  usleep(1000000 / 66);
  
  glutSwapBuffers ( );
  // Swap The Buffers To Not Be Left With A Clear Screen
}

//--------------------------
// Reshape window handler
//--------------------------
void reshape ( int width , int height )
{
  windowWidth = width;
  windowHeight = height;

  if (height==0)                                // Prevent A Divide By Zero By
	{
		height=1;                                   // Making Height Equal One
	}
  
	glViewport(0,0,width,height);                 // Reset The Current Viewport
  
  
	glMatrixMode(GL_PROJECTION);                  // Select The Projection Matrix
	glLoadIdentity();                             // Reset The Projection Matrix
  
	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
  
  gluLookAt(
            eye.x, eye.y, eye.z,
            centre.x, centre.y, centre.z,
            up.x, up.y, up.z );
  
	arcball_setzoom( SPHERE_RADIUS, eye, up );
  
	glMatrixMode(GL_MODELVIEW);                   // Select The Modelview Matrix
	glLoadIdentity();									
}

//----------------------------------------------------------------------------//
// USER INTERFACE CONTROLS
//----------------------------------------------------------------------------//

//--------------------------
// Keydown handler Function
//--------------------------
void keyboard ( unsigned char key, int x, int y )  
{
  switch ( key ) {
    case 27:        // When Escape Is Pressed...
      exit ( 0 );   // Exit The Program
      break;        // Ready For Next Case
    default:        // Now Wrap It Up
      break;
  }
}

//--------------------------
// Special KeyDown handler
//--------------------------
void onSpecialKeyPressed ( int special, int x, int y )  // Create Special Function (required for arrow keys)
{
  switch ( special ) {
    case GLUT_KEY_UP:     // When Up Arrow Is Pressed...
      glutFullScreen ( ); // Go Into Full Screen Mode
      break;
    case GLUT_KEY_DOWN:               // When Down Arrow Is Pressed...
      glutReshapeWindow ( 500, 500 ); // Go Into A 500 By 500 Window
      break;
    default:
      break;
  }
}

//--------------------------
// MouseDown handler
//--------------------------
void onMouse(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON)
  {
    int invert_y = (windowHeight - y) - 1; // GL viewport coordinates are Cartesian
    arcball_start(x,invert_y);
  }
  else if (button == GLUT_RIGHT_BUTTON)
  {
  }
  mousex = x;
  mousey = y;
}

//--------------------------
// MouseDrag Handler
//--------------------------
void onMouseDrag(int x, int y) {
  mousex = x;
  mousey = y;
  int invert_y = (windowHeight - y) - 1;
	arcball_move(x,invert_y);
}

//--------------------------
// MouseMove Handler
//--------------------------
void onMouseMove(int x, int y) {
  mousex = x;
  mousey = y;
}

//--------------------------
// Main program entry
//--------------------------
int main ( int argc, char** argv )
{
  glutInit            ( &argc, argv ); // Erm Just Write It =)
  glutInitDisplayMode ( GLUT_RGBA | GLUT_DOUBLE ); // Display Mode
  glutInitWindowSize  ( windowWidth, windowHeight ); // If glutFullScreen wasn't called this is the window size
  glutInitWindowPosition(10, 10);
  glutCreateWindow    ( "Window Name Goes Here" ); // Window Title (argv[0] for current directory as title)
  //glutFullScreen      ( );          // Put Into Full Screen
  initGL ();
  glutDisplayFunc     ( display );  // Matching Earlier Functions To Their Counterparts
  glutReshapeFunc     ( reshape );
  glutKeyboardFunc    ( keyboard );
  glutMouseFunc       ( onMouse );
  glutMotionFunc      ( onMouseDrag );
  glutPassiveMotionFunc(onMouseMove );
  glutSpecialFunc     ( onSpecialKeyPressed );
  glutIdleFunc        ( display );
  
  wallClock.tic();  
  arcball_reset();

  glutMainLoop        ( );          // Initialize The Main Loop
  
  return 0;
};
