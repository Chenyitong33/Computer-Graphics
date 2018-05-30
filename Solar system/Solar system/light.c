/*
 *   Tutorial 6 Lighting and Texture Mapping in OpenGL
 *   A Lit Sphere
 *   light.c
 *   (Taken from OpenGL Programming Guide, 3rd Edition, 1999)
 *
 *   This program demonstrates the use of the OpenGL lighting
 *   model.  A sphere is drawn using a grey material characteristic.
 *   A single light source illuminates the object.
 */
#include "c:\glut\glut.h"
#include <stdlib.h>
#include "bitmap.h"

GLUquadricObj *mySphere, *Earth;
static int teximageWidth, teximageHeight, earthimageWidth, earthimageHeight;
GLubyte *teximage, *earthimage;
static GLuint texName, earth;

///////////////////////////////////////////////////////////////////////////
// capture the BMP file
///////////////////////////////////////////////////////////////////////////
// filename specifies the BMP file to read
// After executed, w & h will contain
// the image width & height while the raw RGB byte is returned
///////////////////////////////////////////////////////////////////////////
GLubyte* TextureLoadBitmap(char *filename, int *w, int *h)		
{
   BITMAPINFO *info; // Bitmap information
   void	      *bits; // Bitmap pixel bits
   GLubyte    *rgb;	 // Bitmap RGB pixels

   // Try loading the bitmap and converting it to RGB...
   bits = LoadDIBitmap(filename, &info);
  
   if (bits == NULL) 
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

/*   Initialize material property, light source, lighting model,
 *   and depth buffer.
 */
void init(void) 
{
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
   
   glGenTextures(1, &texName);
   glBindTexture(GL_TEXTURE_2D, texName);
   
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
   teximage = TextureLoadBitmap("test.bmp", &teximageWidth, &teximageHeight);
   gluBuild2DMipmaps(GL_TEXTURE_2D, 3, teximageWidth, teximageHeight, 
                GL_RGB, GL_UNSIGNED_BYTE, teximage);

   glGenTextures(2, &earth);
   glBindTexture(GL_TEXTURE_2D, earth);
   
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
   earthimage = TextureLoadBitmap("earth.bmp", &earthimageWidth, &earthimageHeight);
   gluBuild2DMipmaps(GL_TEXTURE_2D, 3, earthimageWidth, earthimageHeight, 
                GL_RGB, GL_UNSIGNED_BYTE, earthimage);  

   // Read the texture image and store the RGB byte to teximage
   

   mySphere = gluNewQuadric();
   gluQuadricDrawStyle(mySphere, GLU_FILL);
   gluQuadricTexture(mySphere,GL_TRUE);

   Earth = gluNewQuadric();
   gluQuadricDrawStyle(Earth, GLU_FILL);
   gluQuadricTexture(Earth,GL_TRUE);
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   //glutWireSphere(1.0, 20, 16);
   glBindTexture(GL_TEXTURE_2D, texName);
   gluSphere(mySphere, 0.5, 12, 12);

   glBindTexture(GL_TEXTURE_2D, earth);
   glTranslatef(1.0, 0.0, 0.0);
   gluSphere(Earth, 0.5, 12, 12);
   glFlush();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      glOrtho( - 1.5, 1.5, - 1.5 * (GLfloat) h / (GLfloat) w,
               1.5 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
   else
      glOrtho( - 1.5 * (GLfloat) w / (GLfloat) h,
               1.5 * (GLfloat) w / (GLfloat) h, -1.5, 1.5, -10.0, 10.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void mykey(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);  
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(500, 500); 
   glutInitWindowPosition(100, 100);
   glutCreateWindow("A Lit Sphere");
   init();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(mykey);
   glutMainLoop();
   return 0;
}
