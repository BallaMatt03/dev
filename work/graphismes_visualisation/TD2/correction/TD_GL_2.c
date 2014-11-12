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
0,0,2
};



// Header des fonctions
void revolution(int nbr_vertices, GLfloat profile[], float angle, int nbr_sections);
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
  gluLookAt(0.0,15.0,20.0,0.0,8.0,0.0,0.0,1.0,0.0); 



// 1er Partie du TD
/*

  // Objet par extrusion : segement/pince
  glPushMatrix();
  glColor3f(0.6,0.6,0.6);
  glRotatef(45,1.0,0.0,0.0);
  glTranslatef(0,0,0);
  glScalef(0.5,0.5,0.5);
  extrude(9, Segment_2d, extrusion_vector);
  glPopMatrix();
*/

/*
  // Objet par révolution : base/lampadaire
  glPushMatrix();
  glColor3f(0.6,0.6,0.6);
  glTranslatef(-0,0.0,0);
  glRotatef(0,1.0,0.0,0.0);
  glScalef(0.3,0.3,0.3);
  revolution(7, pied_2d, 360, 16);
  glPopMatrix();				
*/

/*
  // Chargement d'un objet : articluation 
  DessinModele();
*/




  // Objets par listes d'affichage
/*
  Make_CallListes();

  glCallList(OBJET_1); 

  glCallList(OBJET_2); 

  glCallList(OBJET_3); 

  glCallList(OBJET_4); 

  glCallList(OBJET_5); 
*/



//2eme Partie du TD

  // Terain
  glBegin(GL_POLYGON);
  glNormal3f(0,1,0); 
  glVertex3f(-10.0f,0.0f,-10.0f);
  glVertex3f(10.0f,0.0f,-10.0f);
  glVertex3f(10.0f,0.0f,10.0f);
  glVertex3f(-10.0f,0.0f,10.0f);
  glEnd();	


  // Compilation des listes
  Make_CallListes();

  //pied 1
  glPushMatrix();
  glTranslatef(5.0f,0.0f,-8.0f);
  glCallList(OBJET_4);
  glPopMatrix();

  //pied 2
  glPushMatrix();
  glTranslatef(-5.0f,0.0f,-8.0f);
  glCallList(OBJET_4);
  glPopMatrix();

  //pied 3
  glPushMatrix();
  glTranslatef(5.0f,0.0f,0.0f);
  glCallList(OBJET_4);
  glPopMatrix();

  //pied 4
  glPushMatrix();
  glTranslatef(-5.0f,0.0f,0.0f);
  glCallList(OBJET_4);
  glPopMatrix();

  //etablie
  glPushMatrix();
  glTranslatef(0.0f,7.0f,-5.0f);
  glScalef(15.0,0.2,15.0);
  glutSolidCube(1.0);
  glPopMatrix();

  //base robot
  glPushMatrix();
  glTranslatef(5.0f,7.0f,-9.0f);
  glCallList(OBJET_3);
  glPopMatrix();


  //segement 1
  glPushMatrix();
  glTranslatef(-6.0f,7.5f,-10.0f);
  glRotatef(90.0,1.0,0.0,0.0);
  glRotatef(-15.0,0.0,0.0,1.0);
  glCallList(OBJET_1);
  glPopMatrix();

  //segement 2
  glPushMatrix();
  glTranslatef(-3.0f,7.5f,-10.0f);
  glRotatef(90.0,1.0,0.0,0.0);
  glRotatef(-15.0,0.0,0.0,1.0);
  glCallList(OBJET_1);
  glPopMatrix();

  //segement 1
  glPushMatrix();
  glTranslatef(0.0f,7.5f,-10.0f);
  glRotatef(90.0,1.0,0.0,0.0);
  glRotatef(-15.0,0.0,0.0,1.0);
  glCallList(OBJET_1);
  glPopMatrix();


  //pince 1
  glPushMatrix();
  glTranslatef(-5.0f,7.2f,-2.0f);
  glRotatef(90.0,1.0,0.0,0.0);
  glRotatef(45.0,0.0,0.0,1.0);
  glCallList(OBJET_2);
  glPopMatrix();

  //pince 2
  glPushMatrix();
  glTranslatef(-3.0f,7.2f,-2.0f);
  glRotatef(90.0,1.0,0.0,0.0);
  glRotatef(45.0,0.0,0.0,1.0);
  glCallList(OBJET_2);
  glPopMatrix();


  //pince 3
  glPushMatrix();
  glTranslatef(-1.0f,7.2f,-2.0f);
  glRotatef(90.0,1.0,0.0,0.0);
  glRotatef(45.0,0.0,0.0,1.0);
  glCallList(OBJET_2);
  glPopMatrix();


  //pince 4
  glPushMatrix();
  glTranslatef(1.0f,7.2f,-2.0f);
  glRotatef(90.0,1.0,0.0,0.0);
  glRotatef(45.0,0.0,0.0,1.0);
  glCallList(OBJET_2);
  glPopMatrix();


  //articulation 1
  glPushMatrix();
  glTranslatef(6.0f,8.0f,-2.0f);
  glCallList(OBJET_5);
  glPopMatrix();

  //articulation 2
  glPushMatrix();
  glTranslatef(3.0f,8.0f,-2.0f);
  glCallList(OBJET_5);
  glPopMatrix();


  //articulation 3
  glPushMatrix();
  glTranslatef(4.5f,8.0f,0.0f);
  glCallList(OBJET_5);
  glPopMatrix();



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
void revolution(int nbr_vertices, GLfloat profile[], float angle, int nbr_sections) {

int s, v;
float theta1, theta2, x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;

for(s=0; s<nbr_sections; s++) {

// incréments en rotation autour de y
theta1 = (s*1.0)*angle/nbr_sections*3.14/180;
theta2 = (s+1.0)*angle/nbr_sections*3.14/180;

// incréments lorsqu'on parcours le profil de bas en haut

for(v=0; v<nbr_vertices-1; v++) {
x1 = profile[v*2]*cos(theta1);
y1 = profile[v*2+1];
z1 = profile[v*2]*sin(theta1);

x2 = profile[v*2+2]*cos(theta1);
y2 = profile[v*2+3];
z2 = profile[v*2+2]*sin(theta1);

x3 = profile[v*2+2]*cos(theta2);
y3 = profile[v*2+3];
z3 = profile[v*2+2]*sin(theta2);

x4 = profile[v*2]*cos(theta2);
y4 = profile[v*2+1];
z4 = profile[v*2]*sin(theta2);

// calcul de la normale au plan par produit vectoriel

float v1x,v1y,v1z, // V1
      v2x,v2y,v2z, // V2
      nx,ny,nz;    // normale à la face

v1x = x2 - x1;
v1y = y2 - y1;
v1z = z2 - z1;

v2x = x3 - x2;
v2y = y3 - y2;
v2z = z3 - z2;

nx = (v1y * v2z) - (v1z * v2y);
ny = (v1z * v2x) - (v1x * v2z);
nz = (v1x * v2y) - (v1y * v2x);


nx /= sqrt(pow(nx,2)+pow(ny,2)+pow(nz,2));
ny /= sqrt(pow(nx,2)+pow(ny,2)+pow(nz,2));
nz /= sqrt(pow(nx,2)+pow(ny,2)+pow(nz,2));

// Affichage de la face avec les normales associées à chaque sommet
glBegin(GL_POLYGON);
glNormal3f(nx,ny,nz); 
glVertex3f(x1,y1,z1);
glNormal3f(nx,ny,nz); 
glVertex3f(x2,y2,z2);
glNormal3f(nx,ny,nz); 
glVertex3f(x3,y3,z3);
glNormal3f(nx,ny,nz); 
glVertex3f(x4,y4,z4);
glEnd();

}
}
}

//nbr_vertices: nombre de vertex du profile
//profile[]: tableau 2d contenant les vertex du profile
//vector[] : vecteur d'extrusion
void extrude(int nbr_vertices, GLfloat profile[], GLfloat vector[]) {

int v;

float x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;

for(v=0; v<nbr_vertices-1; v++) {

x1 = profile[v*2];
y1 = profile[v*2+1];
z1 = 0;

x2 = profile[v*2+2];
y2 = profile[v*2+3];
z2 = 0;

x3 = profile[v*2+2]+vector[0];
y3 = profile[v*2+3]+vector[1];
z3 = vector[2];

x4 = profile[v*2]+vector[0];
y4 = profile[v*2+1]+vector[1];
z4 = vector[2];

// calcul de la normale au plan par produit vectoriel

float v1x,v1y,v1z, // V1
      v2x,v2y,v2z, // V2
      nx,ny,nz;    // normale à la face

v1x = x2 - x1;
v1y = y2 - y1;
v1z = z2 - z1;

v2x = x3 - x2;
v2y = y3 - y2;
v2z = z3 - z2;

nx = (v1y * v2z) - (v1z * v2y);
ny = (v1z * v2x) - (v1x * v2z);
nz = (v1x * v2y) - (v1y * v2x);

// Affichage de la face avec les normales associées à chaque sommet
glBegin(GL_POLYGON);
glNormal3f(nx,ny,nz); 
glVertex3f(x1,y1,z1);
glNormal3f(nx,ny,nz); 
glVertex3f(x2,y2,z2);
glNormal3f(nx,ny,nz); 
glVertex3f(x3,y3,z3);
glNormal3f(nx,ny,nz); 
glVertex3f(x4,y4,z4);
glEnd();

}

// Calcul des faces laterales

// face 1
int w;
glBegin(GL_POLYGON);

for(w=0; w<nbr_vertices-1; w++)
{
glNormal3f(0.0,0.0,-1.0);
glVertex3f(profile[w*2],profile[w*2+1],0.0);
}

glEnd();

// face 2
glBegin(GL_POLYGON);

for(w=0; w<nbr_vertices-1; w++)
{
glNormal3f(0.0,0.0,-1.0);
glVertex3f(profile[w*2]+vector[0],profile[w*2+1]+vector[1],+vector[2]);
}

glEnd();



}

void  Make_CallListes(){

// Objet par extrusion : segment
glNewList(OBJET_1,GL_COMPILE);
glPushMatrix();
glScalef(0.5f,0.8f,0.5f);
glTranslatef(-2.0f,0.0f,-1.0f);
extrude(9, segment_2d, extrusion_vector);
glPopMatrix();
glEndList();

// Objet par extrusion : pince
glNewList(OBJET_2,GL_COMPILE);
glPushMatrix();
glScalef(0.2f,0.3f,0.2f);
glTranslatef(0.0f,0.0f,-1.0f);
extrude(15, pince_2d, extrusion_vector);
glPopMatrix();
glEndList();


// Objet par revoltion : base
glNewList(OBJET_3,GL_COMPILE);
glPushMatrix();
glScalef(0.25f,0.25f,0.25f);
revolution(6, base_2d, 360, 16);
glPopMatrix();
glEndList();


// Objet par revoltion : pied de table
glNewList(OBJET_4,GL_COMPILE);
glPushMatrix();
glScalef(0.3f,0.4f,0.3f);
revolution(7, pied_2d, 360, 16);
glPopMatrix();
glEndList();


// Objet chargé : articulation (sphère)
glNewList(OBJET_5,GL_COMPILE);
DessinModele();
glEndList();




}


