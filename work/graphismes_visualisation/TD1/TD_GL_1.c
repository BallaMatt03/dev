////////////////////////////////
// 2008						  //
// TD Informatique Graphique  //
// Université Paris 11	      //  
// Mehdi AMMI - ammi@limsi.fr //
////////////////////////////////

#include <GL/glut.h>    // Header pour GLUT 
#include <GL/gl.h>	// Header pour OpenGL
#include <GL/glu.h>	// Header pour GLu
#include <stdlib.h>     // Heard  Utilitaire général

/* Position de la source de lumière */

GLfloat light_position[] = { 1.0F,0.0F,1.0F,0.0F };
GLfloat lightambiant[] = { 1.0f,1.0f,1.0f,0.0};

/* code ASCII pour la touche escape*/
#define ESCAPE 27

/* Identifiant de la fenêtre GLUT */
int window; 

/* .. */
void InitGL(int Width, int Height)	        
{
// ..
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		

// ..
  glClearDepth(1.0);	
  glDepthFunc(GL_LESS);	
  glEnable(GL_DEPTH_TEST);	

// Gesion d'éclairage
  glEnable(GL_LIGHTING);//
  glEnable(GL_LIGHT0); 	

  glLightfv(GL_LIGHT0,GL_POSITION,light_position);	
  glLightfv(GL_LIGHT0,GL_AMBIENT,lightambiant);


// ..
  glShadeModel(GL_SMOOTH);			

// ..
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();				
  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);	

// Projection orthogonale sans aspect ratio
//..

// Projection orthogonale avec aspect ratio
//..

  glMatrixMode(GL_MODELVIEW);

}

/* .. */
void ReSizeGLScene(int Width, int Height)
{
  if (Height==0)				
    Height=1;

  glViewport(0, 0, Width, Height);		

// ..
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();				
  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);	

// Projection orthogonale sans aspect ratio
//..

// Projection orthogonale avec aspect ratio
//..

  glMatrixMode(GL_MODELVIEW);

}

/* .. */
void DrawGLScene()
{
// Effacer arrière plan et Z buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		
  glLoadIdentity();		
  //gluLookAt(8.0,6.0,4.0,0.0,0.0,0.0,0.0,1.0,0.0); 
  gluLookAt(8.0,8.0,8.0,0.0,0.0,0.0,0.0,1.0,0.0); 

  // Dessin des poins et segments
  /*
  glPointSize(5.0); // change la taille des poins dessinés
  //glColor3f(1.0,1.0,1.0);
  glBegin(GL_POINTS);
  glVertex3f(0.0,0.0,0.0);
  glEnd();
  glFlush();
  */
/*
  //glColor3f(1.0,1.0,1.0);
  glBegin(GL_LINES);
  glColor3f(0.0,255.0,0.0);
  glVertex3f(0.0,0.0,0.0);
  glVertex3f(1.0,0.0,0.0);
  glColor3f(0.0,0.0,255.0);
  glVertex3f(0.0,0.0,0.0);
  glVertex3f(0.0,1.0,0.0);
  glColor3f(255.0,0.0,0.0);
  glVertex3f(0.0,0.0,0.0);
  glVertex3f(0.0,0.0,1.0);
  glEnd();
  glFlush();
*/


  // Dessin d'un triangle

  //..


  // Dessin d'un triangle coloré uniformément

  //..


  // Dessin d'un triangle coloré par interpolation

  //..				




  // Cube sans couleur

  //Translation de l'objet
/*
  //Face 1
  glBegin(GL_QUADS);
  glColor3f(0.0,1.0,0.0);
  glVertex3f(0.0,0.0,0.0);
  glVertex3f(1.0,0.0,0.0);
  glVertex3f(1.0,1.0,0.0);
  glVertex3f(0.0,1.0,0.0);
  glEnd();


  // Face 2

  glBegin(GL_QUADS);
  glColor3f(1.0,0.0,1.0);
  glVertex3f(0.0,0.0,1.0);
  glVertex3f(1.0,0.0,1.0);
  glVertex3f(1.0,1.0,1.0);
  glVertex3f(0.0,1.0,1.0);
  glEnd();

  // Face 3

  glBegin(GL_QUADS);
  glColor3f(1.0,0.0,0.0);
  glVertex3f(0.0,0.0,0.0);
  glVertex3f(0.0,0.0,1.0);
  glVertex3f(1.0,0.0,1.0);
  glVertex3f(1.0,0.0,0.0);
  glEnd();

  // Face 4

  glBegin(GL_QUADS);
  glColor3f(1.0,1.0,0.0);
  glVertex3f(0.0,1.0,0.0);
  glVertex3f(0.0,1.0,1.0);
  glVertex3f(1.0,1.0,1.0);
  glVertex3f(1.0,1.0,0.0);
  glEnd();

  // Face 5

  glBegin(GL_QUADS);
  glColor3f(0.0,0.0,1.0);
  glVertex3f(0.0,0.0,0.0);
  glVertex3f(0.0,0.0,1.0);
  glVertex3f(0.0,1.0,1.0);
  glVertex3f(0.0,1.0,0.0);
  glEnd();

  // Face 4
  
  glBegin(GL_QUADS);
  glColor3f(0.0,1.0,1.0);
  glVertex3f(1.0,0.0,0.0);
  glVertex3f(1.0,0.0,1.0);
  glVertex3f(1.0,1.0,1.0);
  glVertex3f(1.0,1.0,0.0);
  glEnd();

  glFlush();
*/

  // Cube avec normales

  //Translation de l'objet
  //..		
/*
  //Face 1
  glBegin(GL_QUADS);
  //glColor3f(0.0,1.0,0.0);
  glNormal3f(0.0,0.0,-1.0);
  glVertex3f(0.0,0.0,0.0);
  glVertex3f(1.0,0.0,0.0);
  glVertex3f(1.0,1.0,0.0);
  glVertex3f(0.0,1.0,0.0);
  
  glEnd();

  // Face 2

  glBegin(GL_QUADS);
  //glColor3f(1.0,0.0,1.0);
  glNormal3f(0.0,0.0,1.0);
  glVertex3f(0.0,0.0,1.0);
  glVertex3f(1.0,0.0,1.0);
  glVertex3f(1.0,1.0,1.0);
  glVertex3f(0.0,1.0,1.0);
  glEnd();

  // Face 3

  glBegin(GL_QUADS);
  //glColor3f(1.0,0.0,0.0);
  glNormal3f(0.0,-1.0,0.0);
  glVertex3f(0.0,0.0,0.0);
  glVertex3f(0.0,0.0,1.0);
  glVertex3f(1.0,0.0,1.0);
  glVertex3f(1.0,0.0,0.0);
  glEnd();

  // Face 4

  glBegin(GL_QUADS);
  //glColor3f(1.0,1.0,0.0);
  glNormal3f(0.0,1.0,0.0);
  glVertex3f(0.0,1.0,0.0);
  glVertex3f(0.0,1.0,1.0);
  glVertex3f(1.0,1.0,1.0);
  glVertex3f(1.0,1.0,0.0);
  glEnd();

  // Face 5

  glBegin(GL_QUADS);
  //glColor3f(0.0,0.0,1.0);
  glNormal3f(-1.0,0.0,0.0);
  glVertex3f(0.0,0.0,0.0);
  glVertex3f(0.0,0.0,1.0);
  glVertex3f(0.0,1.0,1.0);
  glVertex3f(0.0,1.0,0.0);
  glEnd();

  // Face 4
  
  glBegin(GL_QUADS);
  //glColor3f(0.0,1.0,1.0);
  glNormal3f(1.0,0.0,0.0);
  glVertex3f(1.0,0.0,0.0);
  glVertex3f(1.0,0.0,1.0);
  glVertex3f(1.0,1.0,1.0);
  glVertex3f(1.0,1.0,0.0);
  glEnd();

  glFlush();
*/
  // Cube avec noramles
  GLfloat no_mat[] = { 0.0F,0.0F,0.0F,1.0F };
  GLfloat mat_diffuse[] = { 0.1F,0.5F,0.8F,1.0F };
  GLfloat mat_ambient[] = { 0.5F,0.5F,0.5F,1.0F };
  GLfloat mat_specular[] = { 0.5F,0.5F,0.5F,1.0F };
  GLfloat high_shininess[] = { 100.0F };
  
  glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
  glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
  glutSolidCube(1.0);
  
  glTranslatef(5.0,0.0,0.0);
  glRotatef(45,1.0,1.0,1.0);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
  glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
  //glutSolidSphere(1.0,20,20);
  glutSolidCube(1.0);
  //glutSolidTorus(1.0, 2.0, 100, 1);
  
  glFlush();

  //Face 1
  //..


  // Face 2
  //..

  // Face 3
  //..

  // Face 4
  //..

  // Face 5
  //..

  // Face 6
  //..

  // Permutation des buffers
  glutSwapBuffers();
}

/* .. */
void keyPressed(unsigned char key, int x, int y) 
{

    if (key == ESCAPE) 
    { 
	/* .. */
	glutDestroyWindow(window); 

	/* .. */
	exit(0);                   
    }
}

/* .. */  
int main(int argc, char **argv) 
{
  /* .. */  
  glutInit(&argc, argv);

  /* .. */  
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  

  /* .. */
  glutInitWindowSize(640, 480);  

  /* .. */
  glutInitWindowPosition(0, 0);  

  /* .. */  
  window = glutCreateWindow("TD Informatique Graphique");  

  /* .. */
  glutDisplayFunc(&DrawGLScene);  

  /* .. */
  glutReshapeFunc(&ReSizeGLScene);

  /* .. */
  glutKeyboardFunc(&keyPressed);

  /* .. */
  InitGL(640, 480);
  
  /* Fonction qui lance la boucle */  
  glutMainLoop();  

  return 1;
}
