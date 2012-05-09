//
//  glutils.h
//  TrivialGLUT
//
//  Created by research on 5/8/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef utils_glutils_h
#define utils_glutils_h

extern int windowWidth;
extern int windowHeight;

void RenderBitmapFontString(float x, float y, void *font,
                            const unsigned char *string) {
  
  int height = 0;
  if (font == GLUT_BITMAP_HELVETICA_10) { height = 10; }
  else if (font == GLUT_BITMAP_HELVETICA_12) { height = 12; }
  else if (font == GLUT_BITMAP_HELVETICA_18) { height = 18; }
  
  glDisable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0.0, windowWidth, 0, windowHeight);
  
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  
  glRasterPos2d(x, y - height);
  for (const unsigned char *c = string; *c; c++)
    glutBitmapCharacter(font, *c);
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
  glEnable(GL_DEPTH_TEST);
}

void drawCube() {
	glBegin(GL_QUADS);                  // Draw A Quad
  glVertex3f( 1.0f, 1.0f,-1.0f);			// Top Right Of The Quad (Top)
  glVertex3f(-1.0f, 1.0f,-1.0f);			// Top Left Of The Quad (Top)
  glVertex3f(-1.0f, 1.0f, 1.0f);			// Bottom Left Of The Quad (Top)
  glVertex3f( 1.0f, 1.0f, 1.0f);			// Bottom Right Of The Quad (Top)
  glVertex3f( 1.0f,-1.0f, 1.0f);			// Top Right Of The Quad (Bottom)
  glVertex3f(-1.0f,-1.0f, 1.0f);			// Top Left Of The Quad (Bottom)
  glVertex3f(-1.0f,-1.0f,-1.0f);			// Bottom Left Of The Quad (Bottom)
  glVertex3f( 1.0f,-1.0f,-1.0f);			// Bottom Right Of The Quad (Bottom)
  glVertex3f( 1.0f, 1.0f, 1.0f);			// Top Right Of The Quad (Front)
  glVertex3f(-1.0f, 1.0f, 1.0f);			// Top Left Of The Quad (Front)
  glVertex3f(-1.0f,-1.0f, 1.0f);			// Bottom Left Of The Quad (Front)
  glVertex3f( 1.0f,-1.0f, 1.0f);			// Bottom Right Of The Quad (Front)
  glVertex3f( 1.0f,-1.0f,-1.0f);			// Bottom Left Of The Quad (Back)
  glVertex3f(-1.0f,-1.0f,-1.0f);			// Bottom Right Of The Quad (Back)
  glVertex3f(-1.0f, 1.0f,-1.0f);			// Top Right Of The Quad (Back)
  glVertex3f( 1.0f, 1.0f,-1.0f);			// Top Left Of The Quad (Back)
  glVertex3f(-1.0f, 1.0f, 1.0f);			// Top Right Of The Quad (Left)
  glVertex3f(-1.0f, 1.0f,-1.0f);			// Top Left Of The Quad (Left)
  glVertex3f(-1.0f,-1.0f,-1.0f);			// Bottom Left Of The Quad (Left)
  glVertex3f(-1.0f,-1.0f, 1.0f);			// Bottom Right Of The Quad (Left)
  glVertex3f( 1.0f, 1.0f,-1.0f);			// Top Right Of The Quad (Right)
  glVertex3f( 1.0f, 1.0f, 1.0f);			// Top Left Of The Quad (Right)
  glVertex3f( 1.0f,-1.0f, 1.0f);			// Bottom Left Of The Quad (Right)
  glVertex3f( 1.0f,-1.0f,-1.0f);			// Bottom Right Of The Quad (Right)
	glEnd();                            // Done Drawing The Quad

}

void drawColoredCube() {
  glColor3f(0.5f,0.5f,1.0f);					// Set The Color To Blue One Time Only
	glBegin(GL_QUADS);                  // Draw A Quad
  glColor3f(0.0f,1.0f,0.0f);          // Set The Color To Blue
  glVertex3f( 1.0f, 1.0f,-1.0f);			// Top Right Of The Quad (Top)
  glVertex3f(-1.0f, 1.0f,-1.0f);			// Top Left Of The Quad (Top)
  glVertex3f(-1.0f, 1.0f, 1.0f);			// Bottom Left Of The Quad (Top)
  glVertex3f( 1.0f, 1.0f, 1.0f);			// Bottom Right Of The Quad (Top)
  glColor3f(1.0f,0.5f,0.0f);          // Set The Color To Orange
  glVertex3f( 1.0f,-1.0f, 1.0f);			// Top Right Of The Quad (Bottom)
  glVertex3f(-1.0f,-1.0f, 1.0f);			// Top Left Of The Quad (Bottom)
  glVertex3f(-1.0f,-1.0f,-1.0f);			// Bottom Left Of The Quad (Bottom)
  glVertex3f( 1.0f,-1.0f,-1.0f);			// Bottom Right Of The Quad (Bottom)
  glColor3f(1.0f,0.0f,0.0f);          // Set The Color To Red
  glVertex3f( 1.0f, 1.0f, 1.0f);			// Top Right Of The Quad (Front)
  glVertex3f(-1.0f, 1.0f, 1.0f);			// Top Left Of The Quad (Front)
  glVertex3f(-1.0f,-1.0f, 1.0f);			// Bottom Left Of The Quad (Front)
  glVertex3f( 1.0f,-1.0f, 1.0f);			// Bottom Right Of The Quad (Front)
  glColor3f(1.0f,1.0f,0.0f);          // Set The Color To Yellow
  glVertex3f( 1.0f,-1.0f,-1.0f);			// Bottom Left Of The Quad (Back)
  glVertex3f(-1.0f,-1.0f,-1.0f);			// Bottom Right Of The Quad (Back)
  glVertex3f(-1.0f, 1.0f,-1.0f);			// Top Right Of The Quad (Back)
  glVertex3f( 1.0f, 1.0f,-1.0f);			// Top Left Of The Quad (Back)
  glColor3f(0.0f,0.0f,1.0f);          // Set The Color To Blue
  glVertex3f(-1.0f, 1.0f, 1.0f);			// Top Right Of The Quad (Left)
  glVertex3f(-1.0f, 1.0f,-1.0f);			// Top Left Of The Quad (Left)
  glVertex3f(-1.0f,-1.0f,-1.0f);			// Bottom Left Of The Quad (Left)
  glVertex3f(-1.0f,-1.0f, 1.0f);			// Bottom Right Of The Quad (Left)
  glColor3f(1.0f,0.0f,1.0f);          // Set The Color To Violet
  glVertex3f( 1.0f, 1.0f,-1.0f);			// Top Right Of The Quad (Right)
  glVertex3f( 1.0f, 1.0f, 1.0f);			// Top Left Of The Quad (Right)
  glVertex3f( 1.0f,-1.0f, 1.0f);			// Bottom Left Of The Quad (Right)
  glVertex3f( 1.0f,-1.0f,-1.0f);			// Bottom Right Of The Quad (Right)
	glEnd();                            // Done Drawing The Quad
  
}


void drawPyrmaid() {
	glBegin(GL_TRIANGLES);							// Drawing Using Triangles
  glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Front)
  glVertex3f(-1.0f,-1.0f, 1.0f);			// Left Of Triangle (Front)
  glVertex3f( 1.0f,-1.0f, 1.0f);			// Right Of Triangle (Front)
  glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Right)
  glVertex3f( 1.0f,-1.0f, 1.0f);			// Left Of Triangle (Right)
  glVertex3f( 1.0f,-1.0f, -1.0f);			// Right Of Triangle (Right)
  glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Back)
  glVertex3f( 1.0f,-1.0f, -1.0f);			// Left Of Triangle (Back)
  glVertex3f(-1.0f,-1.0f, -1.0f);			// Right Of Triangle (Back)
  glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Left)
  glVertex3f(-1.0f,-1.0f,-1.0f);			// Left Of Triangle (Left)
  glVertex3f(-1.0f,-1.0f, 1.0f);			// Right Of Triangle (Left)
  glEnd();                            // Finished Drawing The Triangle
}

void drawPyrmaidColored() {
	glBegin(GL_TRIANGLES);							// Drawing Using Triangles
  glColor3f(1.0f,0.0f,0.0f);          // Red
  glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Front)
  glColor3f(0.0f,1.0f,0.0f);          // Green
  glVertex3f(-1.0f,-1.0f, 1.0f);			// Left Of Triangle (Front)
  glColor3f(0.0f,0.0f,1.0f);          // Blue
  glVertex3f( 1.0f,-1.0f, 1.0f);			// Right Of Triangle (Front)
  glColor3f(1.0f,0.0f,0.0f);          // Red
  glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Right)
  glColor3f(0.0f,0.0f,1.0f);          // Blue
  glVertex3f( 1.0f,-1.0f, 1.0f);			// Left Of Triangle (Right)
  glColor3f(0.0f,1.0f,0.0f);          // Green
  glVertex3f( 1.0f,-1.0f, -1.0f);			// Right Of Triangle (Right)
  glColor3f(1.0f,0.0f,0.0f);          // Red
  glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Back)
  glColor3f(0.0f,1.0f,0.0f);          // Green
  glVertex3f( 1.0f,-1.0f, -1.0f);			// Left Of Triangle (Back)
  glColor3f(0.0f,0.0f,1.0f);          // Blue
  glVertex3f(-1.0f,-1.0f, -1.0f);			// Right Of Triangle (Back)
  glColor3f(1.0f,0.0f,0.0f);          // Red
  glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Left)
  glColor3f(0.0f,0.0f,1.0f);          // Blue
  glVertex3f(-1.0f,-1.0f,-1.0f);			// Left Of Triangle (Left)
  glColor3f(0.0f,1.0f,0.0f);          // Green
  glVertex3f(-1.0f,-1.0f, 1.0f);			// Right Of Triangle (Left)
  glEnd();                            // Finished Drawing The Triangle
}




inline float randf()
{
	return ((1.0f / 127.f) * (((float)(rand() & 255)) - 128.0f)) ;
}


#endif
