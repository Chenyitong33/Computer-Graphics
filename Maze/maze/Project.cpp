/*
 *  Project: An Interactive 3D Maze Game 
 *  Project.cpp
 * 
 * -----------------------------------------------------------------------------
 *  Student Information
 * -----------------------------------------------------------------------------
 *  Student Name:
 *  Student ID:
 *  E-mail:
 *  Major: Computer Technology / Electronic Information / Software Technology
 *  Year: 3
 * ------------------------------------------------------------------------------
 */
#include <c:\glut\glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "Bitmap.h"

#define M_PI 3.141592654

// ============ Global variables =======================
// Maze information
#define MAX_MAZESIZE 20
static int _mapx, _mapz; // Size of the maze	
static int _map[MAX_MAZESIZE][MAX_MAZESIZE];
int _initpos[2];         // Initial position of the player
static int floorWidth, floorHeight, wallWidth, wallHeight, doorWidth, doorHeight;
GLubyte *floorimage, *wallimage, *doorimage;
static GLuint FLOOR, WALL, DOOR;

static GLfloat _wallHeight = 1.0; // Height of the wall
static GLfloat _wallScale = 2.0;  // Scale of the width of the wall
//static int i, j;

// Camera setting
GLfloat _viewangle = 45.0; // Angle of view
GLfloat _viewdepth = 20.0; // View depth

bool camera = TRUE;

// Define the player information structure
typedef struct _playerInfo {
   GLfloat degree;  // Object orientation
   GLfloat forward, spin;
   GLfloat pos[3];	// User position
   GLfloat mySize;	// User radial size
   GLfloat forwardStepSize;	// Step size
   GLfloat spinStepSize;	// Rotate step size
} playerInfo;

playerInfo _player;

int _drawmode = 0;
bool isWin = false;
void init();
void initplayer();

// Capture the BMP file
GLubyte* TextureLoadBitmap(char *filename, int *w, int *h) // Bitmap file to load
{
   BITMAPINFO *info; // Bitmap information
   void       *bits; // Bitmap pixel bits
   GLubyte    *rgb;  // Bitmap RGB pixels

   // Try loading the bitmap and converting it to RGB...
   bits = LoadDIBitmap(filename, &info);
   
   if (bits==NULL) 
	  return (NULL);
   
   rgb = ConvertRGB(info, bits);
   
   if (rgb == NULL) {
      free(info);
      free(bits);
   }

   *w = info->bmiHeader.biWidth;
   *h = info->bmiHeader.biHeight;

   // Free the bitmap and RGB images, then return 0 (no errors).
   
   free(info);
   free(bits);
   return (rgb);
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(_viewangle, (GLfloat) w / (GLfloat) h, 0.8, _viewdepth);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

//====== Drawing functions ===============
void DrawGround()
{
   // Draw the ground here
   // 拆分成一块一块地板
   int i, j;
   glPushMatrix();

   for (j = 0; j < _mapz; j++) {
	   for (i = 0; i < _mapx; i++) {
		   glPushMatrix();
		   glTranslatef((2 * i + 1) * _wallScale / 2.0, 0.0, (2 * j + 1) * _wallScale / 2.0);
		   glScalef(_wallScale, 1.0, _wallScale);
		   //if (_map[i][j] == 0)
		   {
			   glBindTexture(GL_TEXTURE_2D, FLOOR);

			   glBegin(GL_QUADS);
			   glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.0, 0.5);
			   glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.0, 0.5);
			   glTexCoord2f(1.0, 0.0); glVertex3f(0.5, 0.0, -0.5);
			   glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, 0.0, -0.5);
			   glEnd();
		   }
		   glPopMatrix();
	   }
   }

   glPopMatrix();
}

void DrawWalls()
{	
   // Draw the maze's walls here
	int i, j;
	glPushMatrix();
	//glColor3f(0.0, 1.0, 1.0);

	for (j = 0; j < _mapz; j++) {
		for (i = 0; i < _mapx; i++) {
			glPushMatrix();
			glTranslatef((2*i+1) * _wallScale / 2.0, 0.0 , (2*j+1) * _wallScale / 2.0);
			glScalef(_wallScale, 1.0, _wallScale);
			if (_map[i][j] == 1)
			{
				glBindTexture(GL_TEXTURE_2D, WALL);
				
				glBegin(GL_QUADS);
				glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, 0.0, 0.5);
				glTexCoord2f(1.0, 1.0); glVertex3f(-0.5, 1.0, 0.5);
				glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 1.0, -0.5);
				glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, 0.0, -0.5);
				glEnd();

				glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, 0.0, 0.5);
				glTexCoord2f(1.0, 0.0); glVertex3f(0.5, 0.0, 0.5);
				glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 1.0, 0.5);
				glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 1.0, 0.5);
				glEnd();

				glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0); glVertex3f(0.5, 0.0, 0.5);
				glTexCoord2f(1.0, 0.0); glVertex3f(0.5, 0.0, -0.5);
				glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 1.0, -0.5);
				glTexCoord2f(0.0, 1.0); glVertex3f(0.5, 1.0, 0.5);
				glEnd();

				glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0); glVertex3f(0.5, 0.0, -0.5);
				glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, 0.0, -0.5);
				glTexCoord2f(1.0, 1.0); glVertex3f(-0.5, 1.0, -0.5);
				glTexCoord2f(0.0, 1.0); glVertex3f(0.5, 1.0, -0.5);
				glEnd();

				glBegin(GL_QUADS);
				glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 1.0, 0.5);
				glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 1.0, 0.5);
				glTexCoord2f(1.0, 0.0); glVertex3f(0.5, 1.0, -0.5);
				glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, 1.0, -0.5);
				glEnd();
			}
			glPopMatrix();
		}
	}
	
	glPopMatrix();
}

void DrawDoor()
{
	int i, j;
	glPushMatrix();
	//glColor3f(1.0, 0.0, 0.0);

	for (j = 0; j < _mapz; j++) {
		for (i = 0; i < _mapx; i++) {
			glPushMatrix();
			glTranslatef((2 * i + 1) * _wallScale / 2.0, 0.0, (2 * j + 1) * _wallScale / 2.0);
			glScalef(_wallScale, 1.0, _wallScale);
			if (_map[i][j] == 3)
			{
				glBindTexture(GL_TEXTURE_2D, DOOR);
				
				glBegin(GL_QUADS);
				glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, 0.0, 0.5);
				glTexCoord2f(1.0, 1.0); glVertex3f(-0.5, 1.0, 0.5);
				glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 1.0, -0.5);
				glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, 0.0, -0.5);
				glEnd();

				glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, 0.0, 0.5);
				glTexCoord2f(1.0, 0.0); glVertex3f(0.5, 0.0, 0.5);
				glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 1.0, 0.5);
				glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 1.0, 0.5);
				glEnd();

				glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0); glVertex3f(0.5, 0.0, 0.5);
				glTexCoord2f(1.0, 0.0); glVertex3f(0.5, 0.0, -0.5);
				glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 1.0, -0.5);
				glTexCoord2f(0.0, 1.0); glVertex3f(0.5, 1.0, 0.5);
				glEnd();

				glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0); glVertex3f(0.5, 0.0, -0.5);
				glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, 0.0, -0.5);
				glTexCoord2f(1.0, 1.0); glVertex3f(-0.5, 1.0, -0.5);
				glTexCoord2f(0.0, 1.0); glVertex3f(0.5, 1.0, -0.5);
				glEnd();

			}
			glPopMatrix();
		}
	}
	glPopMatrix();
}

void DrawPlayer()
{
   // Draw your player here
	glPushMatrix();
		glTranslatef(_player.pos[0], _player.pos[1], _player.pos[2]);
		glColor3f(1.0, 1.0, 1.0);
		glutSolidSphere(_player.mySize, 15, 15);
		
		glPushMatrix();
		glTranslatef(-0.15, 0.15, 0.0);
		glutSolidSphere(0.05, 15, 15);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.15, 0.15, 0.0);
		glutSolidSphere(0.05, 15, 15);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, -0.1, 0.0);
		glRotatef(180, 1, 0, 0);
		glutSolidCone(0.03, 0.5, 15, 15);
		glPopMatrix();
	glPopMatrix();
}

// For debugging collision detection
void DrawSphere()
{
   glPushMatrix();
	  glTranslatef(_player.pos[0], _player.pos[1], _player.pos[2]);
	  glColor3f(1.0, 0.0, 1.0); 
	  glutWireSphere(_player.mySize, 15, 15);
   glPopMatrix();
}

void display(void)
{
   glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
   glColor3f(1.0, 1.0, 1.0);

   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   
   if (camera == TRUE)
   {
	   gluLookAt(_player.pos[0] - 2.0 * sin(_player.degree * M_PI / 180.0), // eye
		   _player.pos[1] + 0.25,
		   _player.pos[2] - 2.0 * cos(_player.degree* M_PI / 180.0),
		   _player.pos[0], // at
		   _player.pos[1],
		   _player.pos[2],
		   0.0, 1.0, 0.0); // up
   }
   //俯拍视角
   else if (camera == FALSE)
   {
	   gluLookAt(8.0, // eye
	   20.0,
	   8.0,
	   8.0, // at
	   0.0,
	   8.0,
	   0.0, 0.0, -1.0); //up
   }
	  
 	  DrawGround();
  	  DrawWalls();
	  DrawDoor();
	  
	  if (_drawmode == 0)
	  {
		  glPushMatrix();
		  // 此处的平移变化是难点!实现老鼠移动时头朝向变化
		  glTranslatef(_player.pos[0], 0.0, _player.pos[2]);
		  glRotatef(_player.degree, 0.0, _player.pos[1], 0.0);
		  glTranslatef(-_player.pos[0], 0.0, -_player.pos[2]);
		  DrawPlayer();
		  glPopMatrix();
	  }
		  
	  else
		  DrawSphere();
   glPopMatrix();

   if (isWin == TRUE)
   {//reset
	   Sleep(2000);
	   initplayer();
	   isWin = FALSE;
   }

   glutSwapBuffers();
}

void checkcollide()
{
   float dx, dz;
   int i = (int)(_player.pos[0] / _wallScale); //强制转换，获得当前区块x坐标
   int j = (int)(_player.pos[2] / _wallScale); //获得当前区块z坐标
   // Check collision of walls here

   // Update the current position
   dx = _player.forward * sin(_player.degree * M_PI / 180.0);
   dz = _player.forward * cos(_player.degree * M_PI / 180.0);

   float current_x = _player.pos[0] + dx;
   float current_z = _player.pos[2] + dz;

   float distance;
   // move forward in x direction
   if (dx > 0)
   {
	   if (i + 1 >= _mapx ||
		   _map[i + 1][j] == 1)
	   {
		   distance = _player.mySize - ((i + 1) * _wallScale - current_x); //玩家的半径与玩家中心距墙距离的比较

		   if (distance < 0)
		   {
			   _player.pos[0] += dx;
		   }
	   }
	   else
	   {
		   _player.pos[0] += dx;
	   }

   }
   else // move backward in x direction
   {
	   if (i <= 0 ||
		   _map[i - 1][j] == 1)
	   {
		   distance = _player.mySize - (current_x - i * _wallScale); //玩家的半径与玩家中心距墙距离的比较
		   if (distance < 0)
		   {
			   _player.pos[0] += dx;
		   }
	   }
	   else
	   {
		   _player.pos[0] += dx;
	   }
   }

   // move forward in z direction
   if (dz>0)
   {
	   if (j + 1 >= _mapz ||
		   _map[i][j + 1] == 1)
	   {
		   distance = _player.mySize - ((j + 1) * _wallScale - current_z); //玩家的半径与玩家中心距墙距离的比较

		   if (distance < 0)
		   {
			   _player.pos[2] += dz;
		   }
	   }
	   else
	   {
		   _player.pos[2] += dz;
	   }

   }
   // move backward in z direction
   else
   {
	   if (j <= 0 ||
		   _map[i][j - 1] == 1)
	   {
		   distance = _player.mySize - (current_z - j * _wallScale); //玩家的半径与玩家中心距墙距离的比较

		   if (distance < 0)
		   {
			   _player.pos[2] += dz;
		   }
	   }
	   else
	   {
		   _player.pos[2] += dz;
	   }
   }

   if (_map[i][j] == 3)
   {
	    isWin = true;
   }

   //_player.pos[0] += dx;
   //_player.pos[2] += dz;
}

void move(void)
{
   if (_player.spin != 0.0) {
	   _player.degree += _player.spin;
	  if (_player.degree > 360.0) {
		  _player.degree -= 360.0;
	  }
	  else if (_player.degree < -360.0) {
		 _player.degree += 360.0;
	  }
   }

   if (_player.forward != 0.0) {
	  checkcollide();
   }
   glutPostRedisplay();
}

void keyboard(unsigned char key,int x, int y)
{
   switch (key) {
	  case 's':
	  case 'S':
	     // Change to use sphere for the object
		 _drawmode++;
		 _drawmode %= 2;
		 break;

	  case 'f':
	  case 'F':
		  glEnable(GL_FOG);
		  break;

	  case 'a':
	  case 'A':
		  camera = FALSE;
		  break;

      case 27:
	     exit(0);
   }
}

// Please read this function carefully, you can learn how to 
// make use the mouse buttons to control the Test Object/Player
void mouse(int button, int state, int x, int y)
{
   static int buttonhold = 0;
   if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP)) {
	  if (buttonhold >= 2) {
	     // Stop forward and turn right
		 _player.forward = 0.0;
		 _player.spin = -_player.spinStepSize; // Turn right
	  }
	  else
		 _player.spin = 0.0; // Stop turn left
	  buttonhold--;
   }

   if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_UP)) {
	  if (buttonhold >= 2) {
		 // Stop forward and turn left
		 _player.forward = 0.0;
		 _player.spin = _player.spinStepSize; // Turn left
	  }
	  else
	 	 _player.spin = 0.0; // Stop turn right
	  buttonhold--;
   }

   if ((button == GLUT_MIDDLE_BUTTON) && (state == GLUT_UP)) {
	  _player.forward = 0.0;
   }

   if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
	  if (buttonhold > 0) {
		 _player.forward = _player.forwardStepSize;
		 _player.spin = 0.0;
	  }
	  else
		 _player.spin = _player.spinStepSize; // Turn left
	  buttonhold++;
   }

   if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN)) {
	  if (buttonhold > 0) {
	     _player.forward = _player.forwardStepSize;
		 _player.spin = 0.0;
	  }
	  else
		 _player.spin = -_player.spinStepSize; // Turn right
	  buttonhold++;
   }

   if ((button == GLUT_MIDDLE_BUTTON) && (state == GLUT_DOWN)) {
	   _player.forward = _player.forwardStepSize;
   }
}

void initplayer()
{
   // Initilaize the player
   // You may try change the values as you like
   _player.degree = 0.0; // User orientation
   _player.mySize = 0.2; // User radial size
   _player.forward = 0.0;
   _player.forwardStepSize = 0.003; // Step size
   _player.spin = 0.0;
   _player.spinStepSize = 0.1; // Rotate step size

   // Init the player's position based on the postion on the map
   _player.pos[0] = _initpos[0] * _wallScale + _wallScale / 2.0;
   _player.pos[1] = _player.mySize;
   _player.pos[2] = _initpos[1] * _wallScale + _wallScale / 2.0;
}

void init()
{
   initplayer();
   glClearColor(0.2, 0.2, 0.2, 1.0);
   glShadeModel(GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_CULL_FACE);
   // material
   GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 50.0 };
   glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   // lighting
   GLfloat positionLight[] = { 0.0f, 10.0f, 1.0f, 1.0f };
   GLfloat ambientLight[] = { 0.50f, 0.50f, 0.50f, 1.0f };
   GLfloat diffuseLight[] = { 0.45f, 0.15f, 0.75f, 1.0f };
   GLfloat specularLight[] = { 0.40f, 0.40f, 0.40f, 1.0f };

   glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
   glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
   glLightfv(GL_LIGHT0, GL_POSITION, positionLight);
   glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
   glEnable(GL_COLOR_MATERIAL);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
  
   // Fog
   GLfloat fog[4] = { 0.3f, 0.3f, 0.6f, 1.0f };
   glDisable(GL_FOG);
   glFogi(GL_FOG_MODE, GL_EXP);
   glFogfv(GL_FOG_COLOR, fog);
   glFogf(GL_FOG_DENSITY, 0.15);
   glHint(GL_FOG_HINT, GL_DONT_CARE);
   glFogf(GL_FOG_START, 1.0);
   glFogf(GL_FOG_END, 4.0);
   glEnable(GL_POLYGON_SMOOTH);
   glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
   
   glEnable(GL_TEXTURE_2D);
   glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

   glGenTextures(1, &FLOOR);
   glBindTexture(GL_TEXTURE_2D, FLOOR);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   floorimage = TextureLoadBitmap("FLOOR.BMP", &floorWidth, &floorHeight);
   gluBuild2DMipmaps(GL_TEXTURE_2D, 3, floorWidth, floorHeight,
	   GL_RGB, GL_UNSIGNED_BYTE, floorimage);

   glGenTextures(1, &WALL);
   glBindTexture(GL_TEXTURE_2D, WALL);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   wallimage = TextureLoadBitmap("WALL.BMP", &wallWidth, &wallHeight);
   gluBuild2DMipmaps(GL_TEXTURE_2D, 3, wallWidth, wallHeight,
	   GL_RGB, GL_UNSIGNED_BYTE, wallimage);

   glGenTextures(1, &DOOR);
   glBindTexture(GL_TEXTURE_2D, DOOR);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   doorimage = TextureLoadBitmap("DOOR.BMP", &doorWidth, &doorHeight);
   gluBuild2DMipmaps(GL_TEXTURE_2D, 3, doorWidth, doorHeight,
	   GL_RGB, GL_UNSIGNED_BYTE, doorimage);
   //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, floorWidth, floorHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, floorimage);
}

// Read in the maze map
int readmap(char* filename) 
{
   FILE* fp;
   int i, j;
   char tmp[MAX_MAZESIZE];

   fp = fopen(filename,"r");

   if (fp) {
      fscanf(fp, "%d", &_mapx);
	  fscanf(fp, "%d", &_mapz);
	  for (j = 0; j < _mapz; j++) {
 	     fscanf(fp, "%s", tmp);
	     for (i = 0; i < _mapx; i++) {
			_map[i][j] = tmp[i] - '0';
			if (_map[i][j] == 2) {
			   // Save the initial position
			   _initpos[0] = i;
			   _initpos[1] = j;
			}
			printf("%d", _map[i][j]);
		 }
 		 printf("\n");
	  }
	  fclose(fp);
   }
   else {
	  printf("Error Reading Map file!\n");
	  return 0;
   }
   return 1;
}

void main(int argc,char **argv)
{
   if (argc >= 2) {
	  srand(time(NULL));
	  if (readmap(argv[1]) == 0 )
	  	 exit(0);
	  
	  glutInit(&argc, argv);
	  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	  glutInitWindowSize(400, 300);
	  glutInitWindowPosition(250, 250);
	  if (glutCreateWindow("An Interactive 3D Maze Game (Skeleton)") == GL_FALSE)
	     exit(-1);
	  init();
	  glutDisplayFunc(display);
	  glutReshapeFunc(reshape);
	  glutKeyboardFunc(keyboard);
	  glutMouseFunc(mouse);
	  glutIdleFunc(move);
      glutMainLoop();
   } 
   else
 	  printf("Usage %s <mapfile>\n", argv[0]);
}

