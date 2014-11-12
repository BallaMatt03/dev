////////////////////////////////		   
// TD Informatique Graphique  //
// Université Paris 11	      //  
// Mehdi AMMI - ammi@limsi.fr //
////////////////////////////////

#include <GL/glut.h>    // Header pour GLUT 
#include <GL/gl.h>	// Header pour OpenGL
#include <GL/glu.h>	// Header pour GLu
#include <stdlib.h>     // Heard  Utilitaire général
#include <math.h>       // Header pour les fonctions mathèmatiques
#include "LOADER.c"     // Header pour les fonctions de chargement **

// Identifiants des objets LIST
#define OBJET_1 1 
#define OBJET_2 2
#define OBJET_3 3
#define OBJET_4 4
#define OBJET_5 5
#define OBJET_6 6
#define OBJET_7 7

/* Postion et composante ambiante de la source de lumière */

GLfloat light_position[] = {-20.0F,10.0F,20.0F,1.0F };
GLfloat lightambiant[] = { 1.0f,1.0f,1.0f,0.0};

/* code ASCII pour la touche escape*/
#define ESCAPE 27

/* Idantifiant de la fenêtre GLUT */
int window; 


/* Profile de la base */
GLfloat base_2d[] =
{0,0,
8,0,
7,3,
5,5,
2,5.5,
2,0,
};

/* Profile du pied de table */
GLfloat pied_2d[] =
{
1.5,0.0,
1.7,0.5,
1.6,1.0,
1,2,
1,17,
2,17,
2,17.3
};


/* Profile du segment */
GLfloat segment_2d[] =
{
1,0,
0,3,
0,5,
1,8,
3,8,
4,5,
4,3,
3,0,
1,0
};


/* Profile de la pince */
GLfloat pince_2d[] =
{0,0,
0.5,0.15,
0.75,0.5,
1,1,
1,5,
0.75,5.5,
0.5,5.85,
0,6,
-0.5,5.85,
-0.75,5.5,
-1,5,
-1,1,
-0.75,0.5,
-0.5,0.15,
0,0
};


GLfloat extrusion_vector[] =
{
0,0,0.5
};



// Header des fonctions
void revolution(int nbr_vertices, GLfloat profile[], float angle, int nbr_sections /*Nbre de segments pour une sphere par exemple*/);
void extrude(int nbr_vertices, GLfloat profile[], GLfloat vector[]);
void  Make_CallListes();

/* Fonction d'initialisation */
void InitGL(int Width, int Height)	        
{
// Couleur d'effacement du buffer de couleur
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		

// paramètrage du Z-buffer
  glClearDepth(1.0);	
  glDepthFunc(GL_LESS);	
  glEnable(GL_DEPTH_TEST);	

// Activation de l'éclairage **
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0); 	

  glLightfv(GL_LIGHT0,GL_POSITION,light_position);	
  glLightfv(GL_LIGHT0,GL_AMBIENT,lightambiant);

  glEnable(GL_NORMALIZE);

// Activation du lissage
  glShadeModel(GL_SMOOTH);			

// Projection perceptive
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();				
  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);	


// Normalisation des normales
  glEnable(GL_NORMALIZE);


  glMatrixMode(GL_MODELVIEW);

}

/* Fonction de redimensionnement de la fenêtre */
void ReSizeGLScene(int Width, int Height)
{
  if (Height==0)				
    Height=1;

  glViewport(0, 0, Width, Height);		

// Projection perceptive
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();				
  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);	

  glMatrixMode(GL_MODELVIEW);

}

/* Focntion de dessin */
void DrawGLScene()
{
// Effacement du buffer de couleur et de profondeur
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		

  glLoadIdentity();
  //gluLookAt(0.0,15.0,20.0,0.0,8.0,0.0,0.0,1.0,0.0); 
  gluLookAt(50.0,50.0,50.0,0.0,0.0,0.0,0.0,1.0,0.0); 
  //gluLookAt(-20.0,-20.0,-20.0,0.0,0.0,0.0,0.0,1.0,0.0); 



// 1er Partie du TD


  // Objet par extrusion : segment/pince
  //extrude(9,segment_2d,extrusion_vector);
  //glTranslatef(20.0,0.0, 0.0);
  
  //extrude(15,pince_2d,extrusion_vector);
  //glTranslatef(10.0,0.0, 0.0);

  // Objet par révolution : base/lampadaire
  //revolution(6,base_2d,360,42);


  // Chargement d'un objet : articulation 
  DessinModele_2();



  // Objets par listes d'affichage
  //..



//2eme Partie du TD

  // Terain
  //..


  // Compilation des listes
  //..




  //pied 1
  //..

  //pied 2
  //..

  //pied 3
  //..

  //pied 4
  //..

  //etablie
  //..







  //base robot
  //..


  //segement 1
  //..


  //segement 2
  //..


  //segement 1
  //..

  //pince 1
  //..

  //pince 2
  //..
  //pince 3
  //..

  //pince 4
  //..


  //articulation 1
  //..


  //articulation 2
  //..


  //articulation 3
  //..




  // Permutation des buffers
  glutSwapBuffers();
  //Raffrechissement de l'image
  glutPostRedisplay();
}

/* Fonction de gestion du clavier */
void keyPressed(unsigned char key, int x, int y) 
{

    if (key == ESCAPE) 
    { 
	/* Eteindre la fenêtre */
	glutDestroyWindow(window); 

	/* Sortire du programme */
	exit(0);                   
    }
    switch (key)
   {
      case GLUT_KEY_UP:
         //rotation_x_increment = rotation_x_increment +0.005;
      break;
      case GLUT_KEY_DOWN:
         //rotation_x_increment = rotation_x_increment -0.005;
      break;
      case GLUT_KEY_LEFT:
         //rotation_y_increment = rotation_y_increment +0.005;
      break;
      case GLUT_KEY_RIGHT:
         //rotation_y_increment = rotation_y_increment -0.005;
      break;
   }
}


int main(int argc, char **argv) 
{
  /* Initialize GLUT state - glut will take any command line arguments that pertain to it or 
     X Windows - look at its documentation at http://reality.sgi.com/mjk/spec3/spec3.html */  
  glutInit(&argc, argv);

  /*  Activation des buffers :   
     Double buffer 
     RGBA color
     Alpha
     Depth buffer */  
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  

  /* Création de la fenêtre */
  glutInitWindowSize(640, 480);  

  /* Positionnement de la fenêtre */
  glutInitWindowPosition(0, 0);  

  /* Ouverture de la fenêtre */  
  window = glutCreateWindow("TD Informatique Graphique");  

  /* Spécification de la fontion de dessin */
  glutDisplayFunc(&DrawGLScene);  

  /* Spécification de la fontion de redimensionnement */
  glutReshapeFunc(&ReSizeGLScene);

  /* Spécification de la fontion de de gestion du clavier */
  glutKeyboardFunc(&keyPressed);

  /* Intitialisation des paramètres de l'affichage et de la fenêtre */
  InitGL(640, 480);
  
  /* Lancement de la boucle OpenGL */  
  glutMainLoop();  

  return 1;
}


//nbr_vertices: nombre de vertex du profile
//profile[]: tableau 2d contenant les vertex du profile relativement à l'axe de révolution
//angle: angle d'extension (360 correspond à un tour complet)
//nbr_sections: nombre de sections pour le mesh
void revolution(int nbr_vertices, GLfloat profile[], float angle/*angle de la revolution (45°, 90°)*/, int nbr_sections/*nombre de section sur l'angle*/) {

int s, v;
float theta1/*premier sommet*/, theta2/*deuxieme sommet*/, x, xx, x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;

	for(s=0; s<nbr_sections; s++) {

	// incréments en rotation autour de y
	theta1 = (s*1.0)*angle/nbr_sections*3.14/180;
	theta2 = (s+1.0)*angle/nbr_sections*3.14/180;

	// incréments lorsqu'on parcours le profil de bas en haut

		for(v=0; v<nbr_vertices-1; v++) {
			x = profile[2*v];
			xx = profile[2*v+2];
			
			x1 = x * cos(theta1);
			y1 = profile[2*v+1];
			z1 = x * sin(theta1);
			x2 = xx * cos(theta1);
			y2 = profile[2*v+3];
			z2 = xx * sin(theta1);
			
			x4 = x * cos(theta2);
			y4 = y1;
			z4 = x * sin(theta2);
			x3 = xx * cos(theta2);
			y3 = y2;
			z3 = xx * sin(theta2);
			
			// calcul de la normale au plan par produit vectoriel

			float v1x,v1y,v1z, // V1
				  v2x,v2y,v2z, // V2
				  nx,ny,nz;    // normale à la face
			v1x = x1-x2;
			v1y = y1-y2;
			v1z = z1-z2;
			v2x = x4-x2;
			v2y = y4-y2;
			v2z = z4-z2;
			nx = (v1y*v2z)-(v1z*v2y);
			ny = -1 * ((v1x*v2z)-(v1z*v2x)); /*v1z*v2x-v1x*v2z*/
			nz = (v1x*v2y)-(v2x*v1y);


			// Affichage de la face avec les normales associées à chaque sommet
			glBegin(GL_QUADS);
			glNormal3f(-nx,-ny,-nz);
			glVertex3f(x1,y1,z1);
			glVertex3f(x2,y2,z2);
			glVertex3f(x3,y3,z3);
			glVertex3f(x4,y4,z4);
			glEnd();

		}
	}
	glFlush();
}

//nbr_vertices: nombre de vertex du profile
//profile[]: tableau 2d contenant les vertex du profile
//vector[] : vecteur d'extrusion
void extrude(int nbr_vertices, GLfloat profile[], GLfloat vector[]) {

int v;

float x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;

	for(v=0; v<nbr_vertices-1; v++) {
		
		x1 = profile[2*v];
		y1 = profile[2*v+1];
		z1 = 0.0;
		x2 = profile[2*v+2];
		y2 = profile[2*v+3];
		z2 = 0.0;
		
		x3 = x1 + vector[0];
		y3 = y1 + vector[1];
		z3 = z1 + vector[2];
		x4 = x2 + vector[0];
		y4 = y2 + vector[1];
		z4 = z2 + vector[2];
		
		
		// calcul de la normale au plan par produit vectoriel

		float v1x,v1y,v1z, // V1
			  v2x,v2y,v2z, // V2
			  nx,ny,nz;    // normale à la face

		v1x = x1-x2;
		v1y = y1-y2;
		v1z = z1-z2;
		v2x = x4-x2;
		v2y = y4-y2;
		v2z = z4-z2;
		
		nx = (v1y*v2z)-(v1z*v2y);
		ny = -1 * ((v1x*v2z)-(v1z*v2x)); /*v1z*v2x-v1x*v2z*/
		nz = (v1x*v2y)-(v2x*v1y);
		
		// Affichage de la face avec les normales associées à chaque sommet
		glBegin(GL_QUADS);
		glNormal3f(nx,ny,nz);
		glVertex3f(x1,y1,z1);
		glVertex3f(x2,y2,z2);
		glVertex3f(x4,y4,z4);
		glVertex3f(x3,y3,z3);
		glEnd();
	}


// Calcul des faces principales

// face 1

glBegin(GL_POLYGON);
glNormal3f(0.0,0.0,-1.0);
for(v=0; v<nbr_vertices-1; v++) {
	glVertex3f(profile[2*v],profile[2*v+1],0.0);
}
glEnd();


// face 2
glBegin(GL_POLYGON);
glNormal3f(0.0,0.0,1.0);
for(v=0; v<nbr_vertices-1; v++) {
	glVertex3f(profile[2*v]+vector[0],profile[2*v+1]+vector[1],vector[2]);
}
glEnd();
glFlush();
}

void  Make_CallListes(){

// Objet par extrusion : segment
glNewList(OBJET_1,GL_COMPILE);
glPushMatrix();
//glScalef(xx);
//glTranslatef(xxx);
//extrude(xxx);
glPopMatrix();
glEndList();

// Objet par extrusion : pince
//..


// Objet par revoltion : base
//..


// Objet par revoltion : pied de table
//..


// Objet chargé : articulation (sphère)
//..




}


