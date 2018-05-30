/*
 *  Project2: Animation of the Solor System 
 *  Project2.cpp
 * 
 * -------------------------------------------------------------
 *  Student Information
 * -------------------------------------------------------------
 *  Student Name: Chen Yitong
 *  Student ID: 1209853z-i011-0012
 *  E-mail: 349479060@qq.com
 * -------------------------------------------------------------
 *  Supplement: The running program is just a version without bonus part
 *  cause if the bonus part added, there is a mapping problem with venus,
 *  I just marked the bonus part in green and it can always be checked.
 */
#include <c:\glut\glut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "Bitmap.h"

#define M_PI    3.1415926
#define M_2PI   2 * M_PI
#define M_PI_2  M_PI / 2

#define SOLAR_YEAR	     200	// Rotation Period of the solar system
#define MERCURY_YEAR     360	// Rotation Period of the Moon
#define EARTH_YEAR 	     4320   // Rotation Period of the Earth
#define VENUS_YEAR 	     2880   // Rotation Period of the Venus
#define MARS_YEAR 	     8640   // Rotation Period of the Mars
#define MOON_YEAR 	     360	// Rotation Period of the Moon	
#define JUPITER_YEAR     40000	// Rotation Period of the Jupiter
#define SATURN_YEAR      120000 // Rotation Period of the Saturn
#define URANUS_YEAR      360000 // Rotation Period of the Uranus
#define NEPTUNE_YEAR     720000 // Rotation Period of the Neptune
#define PLUTO_YEAR 	     360	// Rotation Period of the Pluto

#define MERCURY_DAY      66		// Self-rotation Period of the Mercury
#define EARTH_DAY 	     11		// Self-rotation Period of the Earth	
#define VENUS_DAY 	     66		// Self-rotation Period of the Venus	
#define MARS_DAY 	     11 	// Self-rotation Period of the Mars	
#define JUPITER_DAY      4		// Self-rotation Period of the Jupiter
#define SATURN_DAY 	     5	    // Self-rotation Period of the Saturn	
#define URANUS_DAY 	     8	    // Self-rotation Period of the Uranus
#define NEPTUNE_DAY      8		// Self-rotation Period of the Neptune
#define PLUTO_DAY 	     66	    // Self-rotation Period of the Pluto

#define	SUN_RADIUS		 0.10	// Radius of the Sun
#define	MERCURY_RADIUS   0.06	// Radius of the Mecury
#define	VENUS_RADIUS	 0.25	// Radius of the Venus
#define	EARTH_RADIUS	 0.25	// Radius of the Earth
#define	MOON_RADIUS		 0.08	// Radius of the Moon
#define	MARS_RADIUS		 0.15	// Radius of the Mars
#define	JUPITER_RADIUS	 0.75	// Radius of the Jupiter
#define	SATURN_RADIUS	 0.65	// Radius of the Saturn
#define	URANUS_RADIUS	 0.40	// Radius of the Uranus
#define	NEPTUNE_RADIUS	 0.30	// Radius of the Neptune
#define	PLUTO_RADIUS	 0.04	// Radius of the Pluto

#define	MERCURY_ORBIT	 0.25	// Orbit Radius of the Venus
#define	VENUS_ORBIT		 0.75	// Orbit Radius of the Venus
#define	EARTH_ORBIT		 1.75	// Orbit Radius of the Earth
#define	MOON_ORBIT		 0.35	// Orbit Radius of the Moon
#define	MARS_ORBIT		 2.5	// Orbit Radius of the Mars
#define	JUPITER_ORBIT	 3.8	// Orbit Radius of the Jupiter
#define	SATURN_ORBIT	 6.5	// Orbit Radius of the Saturn
#define	URANUS_ORBIT	 8.5	// Orbit Radius of the Uranus
#define	NEPTUNE_ORBIT	 10.5	// Orbit Radius of the Neptune
#define	PLUTO_ORBIT		 12.0	// Orbit Radius of the Pluto

#define PRECESSION_YEAR  20 	// Self-rotation Period of the Earth Precession
#define PRECESSION_ANGLE 30
#define MAX_STAR 1000

#define TRUE  1
#define FALSE 0

class Star {
public:
	float x, y, z;
};

Star star[MAX_STAR];

GLUquadricObj *sun, *mercury, *venus, *earth, *moon, *mars, *earthaxis;
GLUquadricObj *jupiter, *saturn, *uranus, *neptune, *pluto;
static int sunimageWidth, sunimageHeight, earthimageWidth, earthimageHeight, moonimageWidth, moonimageHeight, marsimageWidth,
	marsimageHeight, venusimageWidth, venusimageHeight, mercuryimageWidth, mercuryimageHeight, jupiterimageWidth, jupiterimageHeight,
	saturnimageWidth, saturnimageHeight, uranusimageWidth, uranusimageHeight, neptuneimageWidth, neptuneimageHeight, plutoimageWidth, plutoimageHeight;
GLubyte *sunimage, *earthimage, *moonimage, *marsimage, *venusimage, *mercuryimage, *jupiterimage, *saturnimage, *uranusimage, *neptuneimage, *plutoimage;
static GLuint SUN, EARTH, MOON, MARS, VENUS, MERCURY, JUPITER, SATURN, URANUS, NEPTUNE, PLUTO;

float angle_global = 0;
float year_mercury, year_earth = 0, year_venus = 0, year_mars = 0, year_moon = 0;
float year_jupiter = 0, year_saturn = 0, year_uranus = 0, year_neptune = 0, year_pluto = 0;
float day_mercury = 0, day_earth = 0, day_venus = 0, day_mars = 0;
float day_jupiter = 0, day_saturn = 0, day_uranus = 0, day_neptune = 0, day_pluto = 0;

float precession = 0;

GLfloat Rotate_x = 0, Rotate_y = 60;
GLfloat Translate_x = 0.0, Translate_y = 0.0;
GLfloat Zoom = 0.0, Scale = 1.0;
GLfloat dx, dy, old_x = 0.0, old_y = 0.0;
GLfloat old_dx = 0, old_dy = 0;
GLfloat dr, theta = 0;
GLfloat new_x, new_y;
GLuint	texture[6];											// 纹理数组，保存纹理名字

static GLfloat earthr_Angle;												    // 地球公转的角度
static GLfloat earths_Angle;													// 地球自转的角度
static GLfloat moonr_Angle;														// 月亮公转的角度
static GLfloat marsr_Angle;														// 火星公转的角度
static GLfloat marss_Angle;														// 火星自转的角度
static GLfloat venusr_Angle;													// 金星公转的角度
static GLfloat venuss_Angle;													// 金星自转的角度
static GLfloat mercuryr_Angle;													
static GLfloat mercurys_Angle;
static GLfloat jupiterr_Angle;													
static GLfloat jupiters_Angle;
static GLfloat saturnr_Angle;													
static GLfloat saturns_Angle;
static GLfloat uranusr_Angle;													
static GLfloat uranuss_Angle;
static GLfloat neptuner_Angle;													
static GLfloat neptunes_Angle;
static GLfloat plutor_Angle;													
static GLfloat plutos_Angle;
static GLfloat star_Angle;														// 星体
static GLfloat earthaxis_Angle;													// 地轴

int operation = 0;				//operation of behavior. Default is 0.
GLboolean g = GL_TRUE;
GLboolean t = GL_TRUE;
GLboolean r = GL_FALSE;

int G_mousedown_L = FALSE, G_mousedown_R = FALSE;

float winwidth, winheight;
int _ScreenMode = 3;
int j=0; //index of star

void TransformXY(int ix, int iy, float *x, float *y)
{
   *x = 2.0 * (float) ix / (float) winwidth - 1.0;
   *y = -2.0 * (float) iy / (float) winheight + 1.0;
}

// Capture the BMP file
GLubyte* TextureLoadBitmap(char *filename, int *w, int *h) // I - Bitmap file to load
{
   BITMAPINFO *info; // Bitmap information
   void		  *bits; // Bitmap pixel bits
   GLubyte	  *rgb;	 // Bitmap RGB pixels
   GLubyte    err = '0';

   // Try to load the bitmap and converting it to RGB...
   bits = LoadDIBitmap(filename, &info);
   if (bits == NULL) 
	  return (NULL);
   
   rgb = ConvertRGB(info, bits);
   
   if (rgb == NULL) {
      free(info);
      free(bits);
   };

   printf("%s: %d %d\n", filename, info->bmiHeader.biWidth, info->bmiHeader.biHeight);
   printf("read %s successfully\n", filename);
   *w = info->bmiHeader.biWidth;
   *h = info->bmiHeader.biHeight;

   // Free the bitmap and RGB images, then return 0 (no errors).
   free(info);
   free(bits);
   
   return (rgb);
}

// Mouse callback for handling mouse click
void Mouse(int button, int state, int ix, int iy)
{
   float x, y;

   // Transform mouse position from screen coordinate to world 2D coordinate
   TransformXY(ix, iy, &x, &y);

   // Save old cursor location when mouse is clicked
   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
	  G_mousedown_L = TRUE;
	  old_x = x;
	  old_y = y;
   }
   else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
	  G_mousedown_L = FALSE;
	  old_dx = dx;
	  old_dy = dy;
	  dx = 0;
	  dy = 0;
   }
   if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
	  G_mousedown_R = TRUE;
	  old_x = x;
	  old_y = y;
   }
   else if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
	  G_mousedown_R = FALSE;
   }
   glutPostRedisplay();
}

void Drag(int ix, int iy)
{  
   // Transform mouse position from screen coordinate to world 2D coordinate
   TransformXY(ix, iy, &new_x, &new_y);

   // Increment rotation angle for right mouse dragging
   if (G_mousedown_L) {
	  Rotate_y += (new_y - old_y) * 30;
	  old_x = new_x;
	  old_y = new_y;
   }

   // Increment scale for left mouse dragging
   if (G_mousedown_R) {
	  Scale += new_y - old_y;
	  if (Scale < 0.2) Scale = (float) 0.2;
	  if (Scale > 3.0) Scale = (float) 3.0;
	  old_x = new_x;
	  old_y = new_y;
   }
   glutPostRedisplay();
}

// Keyboard callback for handling keyboard event
void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
		case 'g':
			operation = 1;
			{if (g == GL_TRUE)
				{
				g = GL_FALSE;
				}
			 else if (g == GL_FALSE)
				g = GL_TRUE;
			}
			break;
		case 't':
			{if (t == GL_TRUE)
				t = GL_FALSE;
			 else if (t == GL_FALSE)
				t = GL_TRUE;
			}
			break;
		case 'r':
			earthr_Angle = 0;														
			earths_Angle = 0;														
			moonr_Angle = 0;														
			marsr_Angle = 0;														
			marss_Angle = 0;														
			venusr_Angle = 0;														
			venuss_Angle = 0;
			mercuryr_Angle = 0;														
			mercurys_Angle = 0;														
			jupiterr_Angle = 0;														
			jupiters_Angle = 0;														
			saturnr_Angle = 0;														
			saturns_Angle = 0;														
			uranusr_Angle = 0;
			uranuss_Angle = 0;
			neptuner_Angle = 0;
			neptunes_Angle = 0;
			plutor_Angle = 0;
			plutos_Angle = 0;
			star_Angle = 0;															
            earthaxis_Angle = 0;	
			break;
		
		case 'q':
			exit(0);
	}
   // Add code here to control the animation interactively
}

// Special key-stroke callback function
void Special(int key, int x, int y)
{
   if (key == GLUT_KEY_F1) {
	  _ScreenMode ++;
	  if (_ScreenMode > 3) _ScreenMode = 0;
	  if (_ScreenMode == 0)
		 glutReshapeWindow(350, 200);
	  else if(_ScreenMode == 1)
		 glutReshapeWindow(700, 400);
	  else if(_ScreenMode == 2)
	 	 glutReshapeWindow(900, 600);
	  else if(_ScreenMode == 3)
	 	 glutReshapeWindow(150, 75);
   }
}

// Reshape callback
void Reshape(int w, int h)
{
   winwidth  = w;
   winheight = h;
   glViewport(0, 0, w, h);      // Viewport transformation
   glMatrixMode(GL_PROJECTION);	// Projection transformation
   glLoadIdentity(); 
   gluPerspective(45, (GLfloat) w / (GLfloat) h, 1.0, 40.0); 
   glutPostRedisplay();
}

void getPoint(GLfloat radius,GLfloat a,GLfloat b)
{
 
 star[j].x=radius*sin(a* M_PI/180.0)*cos(b* M_PI/180.0);
 star[j].y=radius*sin(a* M_PI/180.0)*sin(b* M_PI/180.0);
 star[j].z=radius*cos(a* M_PI/180.0);
 
}
// Function to draw a point.
static float pointSize = 1.0;
void drawPoint(Star currentPt)
{
	glPointSize(pointSize);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	glVertex3f(currentPt.x, currentPt.y, currentPt.z);
	glEnd();
}
void Sun()
{  GLfloat mat_emission[] = {0.3, 0.2, 0.2, 0.0};
   glPushMatrix();
   //glTranslatef(0.0, 0.5 * HEAD_HEIGHT, 0.0);
   glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);//emissive
   //glColor3f(1.0, 0.0, 0.0);
   glScalef(SUN_RADIUS, SUN_RADIUS, SUN_RADIUS);
   gluSphere(sun, 0.3, 30, 30);
   glPopMatrix();
}
void Mars()
{
   glPushMatrix();
   //glTranslatef(0.0, 0.5 * HEAD_HEIGHT, 0.0);
   glColor3f(0.0, 0.0, 1.0);
   glScalef(MARS_RADIUS, MARS_RADIUS, MARS_RADIUS);
   glBindTexture(GL_TEXTURE_2D, MARS);
   gluSphere(mars, 0.3, 30, 30);
   glPopMatrix();
}
void Venus()
{
   glPushMatrix();
   //glTranslatef(0.0, 0.5 * HEAD_HEIGHT, 0.0);
   glColor3f(0.0, 0.0, 1.0);
   glScalef(VENUS_RADIUS, VENUS_RADIUS, VENUS_RADIUS);
   glBindTexture(GL_TEXTURE_2D, VENUS);
   gluSphere(venus, 0.3, 30, 30);
   glPopMatrix();
}
void Earthaxis()
{
   glPushMatrix();
   glColor3f(1.0, 0.0, 0.0);
   glRotatef(-90.0, 1.0, 0.0, 0.0);
   gluCylinder(earthaxis, 0.001, 0.001, 0.15, 32, 32);
   glPopMatrix();
}
void Earth()
{
   glPushMatrix();
   //glTranslatef(0.0, 0.5 * HEAD_HEIGHT, 0.0);
   glColor3f(0.0, 0.0, 1.0);
   glScalef(EARTH_RADIUS, EARTH_RADIUS, EARTH_RADIUS);
   glBindTexture(GL_TEXTURE_2D, EARTH);
   gluSphere(earth, 0.3, 30, 30);
   
   glPopMatrix();
}
void Moon()
{
   glPushMatrix();
   //glTranslatef(0.0, 0.5 * HEAD_HEIGHT, 0.0);
   glColor3f(1.0, 1.0, 0.0);
   glScalef(MOON_RADIUS, MOON_RADIUS, MOON_RADIUS);
   glBindTexture(GL_TEXTURE_2D, MOON);
   gluSphere(moon, 0.3, 30, 30);
   glPopMatrix();
}
void Mercury()
{
   glPushMatrix();
   //glTranslatef(0.0, 0.5 * HEAD_HEIGHT, 0.0);
   glColor3f(0.0, 0.0, 1.0);
   glScalef(MERCURY_RADIUS, MERCURY_RADIUS, MERCURY_RADIUS);
   glBindTexture(GL_TEXTURE_2D, MERCURY);
   gluSphere(mercury, 0.3, 30, 30);
   glPopMatrix();
}
void Jupiter()
{
   glPushMatrix();
   //glTranslatef(0.0, 0.5 * HEAD_HEIGHT, 0.0);
   glColor3f(0.0, 0.0, 1.0);
   glScalef(JUPITER_RADIUS, JUPITER_RADIUS, JUPITER_RADIUS);
   glBindTexture(GL_TEXTURE_2D, JUPITER);
   gluSphere(jupiter, 0.3, 30, 30);
   glPopMatrix();
}
void Saturn()
{
   glPushMatrix();
   //glTranslatef(0.0, 0.5 * HEAD_HEIGHT, 0.0);
   glColor3f(0.0, 0.0, 1.0);
   glScalef(SATURN_RADIUS, SATURN_RADIUS, SATURN_RADIUS);
   glBindTexture(GL_TEXTURE_2D, SATURN);
   gluSphere(saturn, 0.3, 30, 30);
   glPopMatrix();
}
void Uranus()
{
   glPushMatrix();
   //glTranslatef(0.0, 0.5 * HEAD_HEIGHT, 0.0);
   glColor3f(0.0, 0.0, 1.0);
   glScalef(URANUS_RADIUS, URANUS_RADIUS, URANUS_RADIUS);
   glBindTexture(GL_TEXTURE_2D, URANUS);
   gluSphere(uranus, 0.3, 30, 30);
   glPopMatrix();
}
void Neptune()
{
   glPushMatrix();
   //glTranslatef(0.0, 0.5 * HEAD_HEIGHT, 0.0);
   glColor3f(0.0, 0.0, 1.0);
   glScalef(NEPTUNE_RADIUS, NEPTUNE_RADIUS, NEPTUNE_RADIUS);
   glBindTexture(GL_TEXTURE_2D, NEPTUNE);
   gluSphere(neptune, 0.3, 30, 30);
   glPopMatrix();
}
void Pluto()
{
   glPushMatrix();
   //glTranslatef(0.0, 0.5 * HEAD_HEIGHT, 0.0);
   glColor3f(0.0, 0.0, 1.0);
   glScalef(PLUTO_RADIUS, PLUTO_RADIUS, PLUTO_RADIUS);
   glBindTexture(GL_TEXTURE_2D, PLUTO);
   gluSphere(pluto, 0.3, 30, 30);
   glPopMatrix();
}
void Building()
{
	glBegin(GL_QUADS);

	glNormal3f( 0.0f, 0.0f, 1.0f);
	glVertex3f( 0.2f, 0.05f, 0.05f);
	glVertex3f(-0.2f, 0.05f, 0.05f);
	glVertex3f(-0.2f, -0.05f, 0.05f);
	glVertex3f( 0.2f, -0.05f, 0.05f);
	//1---------------------------
	glNormal3f( 0.0f, 0.0f, -1.0f);
	glVertex3f(-0.2f, -0.05f, -0.05f);
	glVertex3f(-0.2f, 0.05f, -0.05f);
	glVertex3f( 0.2f, 0.05f, -0.05f);
	glVertex3f( 0.2f, -0.05f, -0.05f);
	//2---------------------------
	glNormal3f( 0.0f, 1.0f, 0.0f);
	glVertex3f( 0.2f, 0.05f, 0.05f);
	glVertex3f( 0.2f, 0.05f, -0.05f);
	glVertex3f(-0.2f, 0.05f, -0.05f);
	glVertex3f(-0.2f, 0.05f, 0.05f);
	//3---------------------------
	glNormal3f( 0.0f, -1.0f, 0.0f);
	glVertex3f(-0.2f, -0.05f, -0.05f);
	glVertex3f( 0.2f, -0.05f, -0.05f);
	glVertex3f( 0.2f, -0.05f, 0.05f);
	glVertex3f(-0.2f, 0.05f, 0.05f);
	//4---------------------------
	glNormal3f( 1.0f, 0.0f, 0.0f);
	glVertex3f( 0.2f, 0.05f, 0.05f);
	glVertex3f( 0.2f, -0.05f, 0.05f);
	glVertex3f( 0.2f, -0.05f, -0.05f);
	glVertex3f( 0.2f, 0.05f, -0.05f);
	//5---------------------------
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-0.2f, -0.05f, -0.05f);
	glVertex3f(-0.2f, -0.05f, 0.05f);
	glVertex3f(-0.2f, 0.05f, 0.05f);
	glVertex3f(-0.2f, 0.05f, -0.05f);
	//6---------------------------
	glEnd();

}

// Display callback
void Display(void)
{
    // Clear the window color before drawing is performed
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
   
   	//GLfloat light0_pos[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat ambient[] = { 0.4, 0.4, 0.4, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glEnable(GL_LIGHT0);

	//Building();

    //draw the star-sphere
    for(int a=1; a < 180; a+=10)
    {
	    for(int b=1;b < 360;b+=10)
	    {
		    getPoint(1.0, a, b);
		    drawPoint(star[j]);
		    //j++;
	    }
    }

   glLoadIdentity();
   glRotatef(star_Angle, 0.0, 1.0, 0.0);
   //glRotatef(theta[0], 0.0, 1.0, 0.0);
   Sun();															//sun
   
   glPushMatrix();
   glRotatef(earthr_Angle, 0.0, 1.0, 0.0);                           //orbit-rotate of earth
   glTranslatef(0.0, -0.1, EARTH_ORBIT/10);
   glPushMatrix();

   glPushMatrix();
   glRotatef(30, 0.0, 0.0, 1.0);   
   glRotatef(moonr_Angle, 0.0, 1.0, 0.0);                            //orbit-rotate of moon
   glTranslatef(0.0, 0.0, MOON_ORBIT/10 + 0.3*EARTH_RADIUS);

   //glPushMatrix();
   Moon();											//moon
   glPopMatrix();
   //glPopMatrix();

   glPushMatrix();
   glRotatef(30, 0.0, 0.0, 1.0);                   //PRECESSION
   glRotatef(earthaxis_Angle, 0.0, 1.0, 0.0);                          //self-rotate of precession
   Earthaxis();
   glPopMatrix();

                    
   glRotatef(earths_Angle, 0.0, 1.0, 0.0);                             //self-rotate of earth
   //glTranslatef(0.0, -0.5 * HEAD_HEIGHT, 0.0); 
   Earth();
   glPopMatrix();
   glPopMatrix();

   glPushMatrix();
   glRotatef(marsr_Angle, 0.0, 1.0, 0.0);                             //orbit-rotate of mars
   glTranslatef(0.0, 0.0, MARS_ORBIT/10);
   glPushMatrix();
   glRotatef(marss_Angle, 0.0, 1.0, 0.0);                             //self-rotate of mars
   Mars();
   glPopMatrix();
   glPopMatrix();
      
   glPushMatrix();
   glRotatef(neptuner_Angle, 0.0, 1.0, 0.0);                           
   glTranslatef(0.0, 0.0, NEPTUNE_ORBIT/10);
   glPushMatrix();
   glRotatef(neptunes_Angle, 0.0, 1.0, 0.0);                           
   Neptune();
   glPopMatrix();   
   glPopMatrix();

   glPushMatrix();
   glRotatef(venusr_Angle, 0.0, 1.0, 0.0);                           //orbit-rotate of venus
   glTranslatef(0.0, 0.2, VENUS_ORBIT/10);
   glPushMatrix();
   glRotatef(venuss_Angle, 0.0, 1.0, 0.0);                           //self-rotate of venus
   Venus();
   glPopMatrix();
   glPopMatrix();
  /* 
   glPushMatrix();
   glRotatef(mercuryr_Angle, 0.0, 1.0, 0.0);                           
   glTranslatef(0.0, 0.3, MERCURY_ORBIT/10);
   glPushMatrix();
   glRotatef(mercurys_Angle, 0.0, 1.0, 0.0);                           
   Mercury();
   glPopMatrix();
   glPopMatrix();
   
   glPushMatrix();
   glRotatef(jupiterr_Angle, 0.0, 1.0, 0.0);                           
   glTranslatef(0.0, 0.0, JUPITER_ORBIT/10);
   glPushMatrix();
   glRotatef(jupiters_Angle, 0.0, 1.0, 0.0);                           
   Jupiter();
   glPopMatrix();
   glPopMatrix();
  
   glPushMatrix();
   glRotatef(saturnr_Angle, 0.0, 1.0, 0.0);                           
   glTranslatef(0.0, -0.2, SATURN_ORBIT/10);
   glPushMatrix();
   glRotatef(saturns_Angle, 0.0, 1.0, 0.0);                           
   Saturn();
   glPopMatrix();
   glPopMatrix();
   
   glPushMatrix();
   glRotatef(uranusr_Angle, 0.0, 1.0, 0.0);                           
   glTranslatef(0.0, 0.03, URANUS_ORBIT/10);
   glPushMatrix();
   glRotatef(uranuss_Angle, 0.0, 1.0, 0.0);                           
   Uranus();
   glPopMatrix();
   glPopMatrix();
  
   glPushMatrix();
   glRotatef(plutor_Angle, 0.0, 1.0, 0.0);                           
   glTranslatef(0.0, -0.3, PLUTO_ORBIT/10);
   glPushMatrix();
   glRotatef(plutos_Angle, 0.0, 1.0, 0.0);                           
   Pluto();
   glPopMatrix();
   glPopMatrix();
   */

   // Add code here to
   // 1. Transform the planets and draw them, 
   // 2. Draw the star-sphere by points, 
   // 3. Set correctly material properties of the Sun & planets.
   // You may use glTranslate*(), glRotate*(), glLoadIdentity(), glPushMatrix(), 
   // glPopMatrix(), glMaterial*(), glBegin(), gluSphere(), etc.
   //
   // 4. Provide texture mapping for each planets except the Sun
   // Learn to use glTexImage2D().
	
   if(g == GL_TRUE)
   {earthr_Angle -= 0.083f;
    star_Angle -= 0.01f;
	marsr_Angle -= 0.042f;
	venusr_Angle -= 0.125f;

	mercuryr_Angle -= 1.0f;
	jupiterr_Angle -= 0.009f;
	saturnr_Angle -= 0.003f;
	uranusr_Angle -= 0.001f;
	neptuner_Angle -= 0.005f;
	plutor_Angle -= 1.0f;
   }

   if(t == GL_TRUE)
   {   
	earths_Angle += 3.272f;		//be divided by 10
	earthaxis_Angle += 18.0f;
	moonr_Angle -= 1.0f;
	marss_Angle += 3.272f;		//be divided by 10
	venuss_Angle += 0.545f;		//be divided by 10

	mercurys_Angle += 0.545f;
	jupiters_Angle +=9.0f;
	saturns_Angle += 7.2f;
	uranuss_Angle += 4.5f;
	neptunes_Angle += 4.5f;
	plutos_Angle += 0.545f;
   }

   if(g == GL_FALSE) //press g
	{
	 earthr_Angle -= 0.0f;
	 star_Angle -= 0.0f;
	 marsr_Angle -= 0.0f;
	 venusr_Angle -= 0.0f;
	 	
	mercuryr_Angle -= 0.0f;
	jupiterr_Angle -= 0.0f;
	saturnr_Angle -= 0.0f;
	uranusr_Angle -= 0.0f;
	neptuner_Angle -= 0.0f;
	plutor_Angle -= 0.0f;

	}
	
   if(t == GL_FALSE) //press t
	{
	 earths_Angle += 0.0f;
	 earthaxis_Angle += 0.0f;
	 moonr_Angle -= 0.0f;
	 marss_Angle += 0.0f;
	 venuss_Angle += 0.0f;
	 	
	 mercurys_Angle += 0.0f;
	 jupiters_Angle += 0.0f;
	 saturns_Angle += 0.0f;
	 uranuss_Angle += 0.0f;
	 neptunes_Angle += 0.0f;
	 plutos_Angle += 0.0f;
	}
   

   glutSwapBuffers();
}

void init()
{
	/*
   int i;
   float theta, phi, r = 10;

   // Clear screen color
   glEnable(GL_COLOR_MATERIAL);
   glClearColor(0, 0, 0, 0);
   glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);

   // Texture mapping setting for Microsoft's OpenGL implementation
   glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
   glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
   glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
   glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);

   // Texture mapping parameters for filter and repeatance
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   */
	
   GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
   GLfloat mat_shininess[] = {50.0};
   GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};

   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_SMOOTH);

   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_TEXTURE_2D);

   glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
   
   glGenTextures(1, &EARTH);
   glBindTexture(GL_TEXTURE_2D, EARTH);
   
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
   earthimage = TextureLoadBitmap("earth.bmp", &earthimageWidth, &earthimageHeight);
   gluBuild2DMipmaps(GL_TEXTURE_2D, 3, earthimageWidth, earthimageHeight, 
                GL_RGB, GL_UNSIGNED_BYTE, earthimage);

   glGenTextures(2, &MOON);
   glBindTexture(GL_TEXTURE_2D, MOON);
   
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
   moonimage = TextureLoadBitmap("moon.bmp", &moonimageWidth, &moonimageHeight);
   gluBuild2DMipmaps(GL_TEXTURE_2D, 3, moonimageWidth, moonimageHeight, 
                GL_RGB, GL_UNSIGNED_BYTE, moonimage); 

   glGenTextures(3, &MARS);
   glBindTexture(GL_TEXTURE_2D, MARS);
   
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
   marsimage = TextureLoadBitmap("mars.bmp", &marsimageWidth, &marsimageHeight);
   gluBuild2DMipmaps(GL_TEXTURE_2D, 3, marsimageWidth, marsimageHeight, 
                GL_RGB, GL_UNSIGNED_BYTE, marsimage); 

   glGenTextures(4, &VENUS);
   glBindTexture(GL_TEXTURE_2D, VENUS);
   
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
   venusimage = TextureLoadBitmap("venus.bmp", &venusimageWidth, &venusimageHeight);
   gluBuild2DMipmaps(GL_TEXTURE_2D, 3, venusimageWidth, venusimageHeight, 
                GL_RGB, GL_UNSIGNED_BYTE, venusimage); 

   /*
   glGenTextures(5, &MERCURY);
   glBindTexture(GL_TEXTURE_2D, MERCURY);
   
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
   mercuryimage = TextureLoadBitmap("mercury.bmp", &mercuryimageWidth, &mercuryimageHeight);
   gluBuild2DMipmaps(GL_TEXTURE_2D, 3, mercuryimageWidth, mercuryimageHeight, 
                GL_RGB, GL_UNSIGNED_BYTE, mercuryimage); 
      
   glGenTextures(6, &JUPITER);
   glBindTexture(GL_TEXTURE_2D, JUPITER);
   
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
   jupiterimage = TextureLoadBitmap("jupiter.bmp", &jupiterimageWidth, &jupiterimageHeight);
   gluBuild2DMipmaps(GL_TEXTURE_2D, 3, jupiterimageWidth, jupiterimageHeight, 
                GL_RGB, GL_UNSIGNED_BYTE, jupiterimage);

   glGenTextures(7, &SATURN);
   glBindTexture(GL_TEXTURE_2D, SATURN);
   
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
   saturnimage = TextureLoadBitmap("saturn.bmp", &saturnimageWidth, &saturnimageHeight);
   gluBuild2DMipmaps(GL_TEXTURE_2D, 3, saturnimageWidth, saturnimageHeight, 
                GL_RGB, GL_UNSIGNED_BYTE, saturnimage);
				

   glGenTextures(8, &URANUS);
   glBindTexture(GL_TEXTURE_2D, URANUS);
   
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
   uranusimage = TextureLoadBitmap("uranus.bmp", &uranusimageWidth, &uranusimageHeight);
   gluBuild2DMipmaps(GL_TEXTURE_2D, 3, uranusimageWidth, uranusimageHeight, 
                GL_RGB, GL_UNSIGNED_BYTE, uranusimage);
   */
   glGenTextures(9, &NEPTUNE);
   glBindTexture(GL_TEXTURE_2D, NEPTUNE);
   
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
   neptuneimage = TextureLoadBitmap("neptune.bmp", &neptuneimageWidth, &neptuneimageHeight);
   gluBuild2DMipmaps(GL_TEXTURE_2D, 3, neptuneimageWidth, neptuneimageHeight, 
                GL_RGB, GL_UNSIGNED_BYTE, neptuneimage);
   /*
   
   glGenTextures(10, &PLUTO);
   glBindTexture(GL_TEXTURE_2D, PLUTO);
   
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
   plutoimage = TextureLoadBitmap("pluto.bmp", &plutoimageWidth, &plutoimageHeight);
   gluBuild2DMipmaps(GL_TEXTURE_2D, 3, plutoimageWidth, plutoimageHeight, 
                GL_RGB, GL_UNSIGNED_BYTE, plutoimage);
   */

   //construct the solar-system

   sun = gluNewQuadric();                 /* sun */
   gluQuadricDrawStyle(sun, GLU_FILL);
      
   earth = gluNewQuadric();                 /* earth */
   gluQuadricDrawStyle(earth, GLU_FILL);
   gluQuadricTexture(earth,GL_TRUE);

   earthaxis = gluNewQuadric();               
   gluQuadricDrawStyle(earthaxis, GLU_FILL);

   moon = gluNewQuadric();               
   gluQuadricDrawStyle(moon, GLU_FILL);
   gluQuadricTexture(moon,GL_TRUE);

   mars = gluNewQuadric();               
   gluQuadricDrawStyle(mars, GLU_FILL);
   gluQuadricTexture(mars,GL_TRUE);

   venus = gluNewQuadric();               
   gluQuadricDrawStyle(venus, GLU_FILL);
   gluQuadricTexture(venus,GL_TRUE);

   mercury = gluNewQuadric();               
   gluQuadricDrawStyle(mercury, GLU_FILL);
   gluQuadricTexture(mercury,GL_TRUE);

   jupiter = gluNewQuadric();               
   gluQuadricDrawStyle(jupiter, GLU_FILL);
   gluQuadricTexture(jupiter,GL_TRUE);

   saturn = gluNewQuadric();               
   gluQuadricDrawStyle(saturn, GLU_FILL);
   gluQuadricTexture(saturn,GL_TRUE);

   uranus = gluNewQuadric();               
   gluQuadricDrawStyle(uranus, GLU_FILL);
   gluQuadricTexture(uranus,GL_TRUE);

   neptune = gluNewQuadric();               
   gluQuadricDrawStyle(neptune, GLU_FILL);
   gluQuadricTexture(neptune,GL_TRUE);

   pluto = gluNewQuadric();               
   gluQuadricDrawStyle(pluto, GLU_FILL);
   gluQuadricTexture(pluto,GL_TRUE);
   // Add code here to 
   // 1. Initialize light-source settings, 
   // 2. Read bitmap images, 
   // 3. Initialize different GLU spheres and the position of the stars.
   // Use glLight*(), TextureLoadBitmap(), gluNewQuadric(), etc.
}

void Idle(void)
{	   
  
   // Add code here to 
   // 1. Update the rotation angles, 
   // 2. Force the system to display after the event
}

void main(int argc, char** argv)
{
   // Initialization of GLUT Library
   glutInitWindowSize(800, 450);
   glutInitWindowPosition(100, 100);
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

   // Create a window with title specified
   glutCreateWindow("Project2: Solor System Animation");

   // Register different callback functions for GLUT to response 
   // with different events, e.g. window sizing, mouse click or
   // keyboard stroke
   glutReshapeFunc(Reshape);
   glutDisplayFunc(Display);
   glutKeyboardFunc(Keyboard);
   glutSpecialFunc(Special);
   glutIdleFunc(Display);
   glutMouseFunc(Mouse);
   glutMotionFunc(Drag);
   init();	// not GLUT call, initialize several parameters
	
   // Enter the GLUT event processing loop which never returns.
   // It will call different registered callback according to different events.
   glutMainLoop();
}
