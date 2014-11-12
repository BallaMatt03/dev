////////////////////////////////
// 2007			      //
// TD Informatique Graphique  //
// Université Paris 11	      //  
// Mehdi AMMI - ammi@limsi.fr //
////////////////////////////////
/*gcc TD_GL_3.c -o TD_GL_3 -lGL -lGLU -lglut -lm*/
#include <GL/glut.h>    // Header pour GLUT 
#include <GL/gl.h>	// Header pour OpenGL
#include <GL/glu.h>	// Header pour GLu
#include <stdlib.h>     // Header  Utilitaire général
#include <math.h>       // Header fonctions mathématiques
#include "LOADER.c"     // Header pour les fonctions de chargement **

/* Postion de la source de lumière */

GLfloat light_position[] = {5.0f,30.0f,0.0f, 1.0f};
GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};



/* Identifiants des objets LIST */
#define OBJET_1 1 
#define OBJET_2 2
#define OBJET_3 3
#define OBJET_4 4



/* Profile de la base */
GLfloat base_2d[] =
{0,0,
8,0,
7,3,
5,5,
2,5.5,
2,0,
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
/* Paramètres des articulations DDL*/

float base_x = 0,base_z = 0, base_rot = 0;
float first_x = 0,first_z = 20;
float second_x = 0,second_z = 20;
float third_x = 0,third_z = 20;
float finger_x = 45.0;

/* Paramètres caméra de navigation */
float up_down = 0.0, left_right = -1.57;
float cam_pos_x = 0.0;
float cam_pos_z = 30.0;
float cam_look_x = 0.0;
float cam_look_z = 0.0;
float vect_x = 0.0;
float vect_z = 0.0;


/* code ASCII pour la touche escape*/
#define ESCAPE 27
#define SPACE 32
/* Idantifiant de la fenêtre GLUT */
int window; 


/* Headers */

void Special_key(int key, int x, int y);
void Keyboard_key(unsigned char key, int x, int y);
void ground();
void revolution(int nbr_vertices, GLfloat profile[], float angle, int nbr_sections);
void extrude(int nbr_vertices, GLfloat profile[], GLfloat vector[]);
void Make_CallListes();
void tronc_robot();
void bras_robot();
void move_camera(double speed);
void rotate_camera(double speed);

/* Fonction d'initialisation */
void InitGL(int Width, int Height)	        
{
// Couleur d'effacement du buffer de couleur
  glClearColor(0.1f, 0.1f, 0.3f, 0.0f);		

// paramètrage du Z-buffer
  glClearDepth(1.0);	
  glDepthFunc(GL_LESS);	
  glEnable(GL_DEPTH_TEST);	


// Activation de l'éclairage
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0); 	


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

// Paramètrage de l'éclairage
  glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse);
  glLightfv(GL_LIGHT0,GL_POSITION,light_position);


//////////////////////////////////////////////////
// camera

//  gluLookAt(0.0,5.0,30.0,0.0,5.0,0.0,0.0,1.0,0.0); // premère partie : robot seul

  gluLookAt(cam_pos_x,10.0,cam_pos_z,cam_look_x,5.0,cam_look_z,0.0,1.0,0.0); 

//////////////////////////////////////////////////
// Compilation des listes

  Make_CallListes();

//////////////////////////////////////////////////
// sol  

  glPushMatrix();
  ground();
  glPopMatrix();


//////////////////////////////////////////////////
// Bras articulé

	
/*Mettre les degré de liberté au fur et a mesure des objets*/
/*
// base
glTranslatef(base_x,0.0,base_z);
glRotatef(base_rot,0.0,1.0,0.0);
glCallList(OBJET_3);




// segment 1
float first_y = 0.25*5.5;
glTranslatef(0.0,first_y,0.0);
glRotatef(first_x,1.0,0.0,0.0);
glRotatef(first_z,0.0,0.0,1.0);
glCallList(OBJET_4);
glCallList(OBJET_1);

// segment2
float second_y = 0.6*8.0;
glTranslatef(0.0,second_y,0.0);
glRotatef(second_x,1.0,0.0,0.0);
glRotatef(second_z,0.0,0.0,1.0);
glCallList(OBJET_4);
glCallList(OBJET_1);


// segment 3	
glTranslatef(0.0,second_y,0.0);
glRotatef(third_x,1.0,0.0,0.0);
glRotatef(third_z,0.0,0.0,1.0);
glCallList(OBJET_4);
glCallList(OBJET_1);


// pinces 1 & 2
//float finger_x = 45.0;

glTranslatef(0.0,second_y,0.0);
glCallList(OBJET_4);

glPushMatrix();

glRotatef(finger_x,0.0,0.0,1.0);
glCallList(OBJET_2);
glTranslatef(0.0,5.85*0.3,0.0);
glRotatef(-45.0,0.0,0.0,1.0);
glCallList(OBJET_2);

glPopMatrix();


glRotatef(-finger_x,0.0,0.0,1.0);
glCallList(OBJET_2);

glTranslatef(0.0,5.85*0.3,0.0);
glRotatef(45.0,0.0,0.0,1.0);
glCallList(OBJET_2);
*/
//////////////////////////////////////////////////

//////////////////////////////////////////////////
// Robot complet

/////////////////////////////////
// Base
glTranslatef(base_x,0.0,base_z);
glPushMatrix();
glScalef(2.0,2.0,2.0);
glCallList(OBJET_3);
glPopMatrix();


/////////////////////////////////
// Tronc

glTranslatef(0.0,4.0+(2.0*1.375),0.0);
glRotatef(base_rot,0.0,1.0,0.0);
glPushMatrix();
glScalef(3.0,4.0,3.0);
tronc_robot();
glPopMatrix();
//////////////////////////////////////////////////
// bras 1
glPushMatrix();
glTranslatef(-3.0,2.0,0.0);
glRotatef(90.0,0.0,0.0,1.0);
bras_robot();
glPopMatrix();

//////////////////////////////////////////////////

//////////////////////////////////////////////////
// bras 2
glPushMatrix();
glTranslatef(3.0,2.0,0.0);
glRotatef(-90.0,0.0,0.0,1.0);
glScalef(-1.0,1.0,1.0);
bras_robot();
glPopMatrix();
//////////////////////////////////////////////////
//Tête du robot
glTranslatef(0.0,5.0,0.0);
glutSolidSphere(2.5,20,20);

  // Permutation des buffers
   glutSwapBuffers();
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
    }// Identifiants des objets LIST
}


int main(int argc, char **argv) 
{
  // Pointeurs vers l'application
  glutInit(&argc, argv);

  /*  Activation des buffers :   
     Double buffer 
     RGBA color
     Alpha
     Depth buffer */  
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  

  /* Création de la fenêtre */
  glutInitWindowSize(1024, 765);  

  /* Positionnement de la fenêtre */
  glutInitWindowPosition(200, 200);  

  /* Ouverture de la fenêtre */  
  window = glutCreateWindow("TD Informatique Graphique");  

  /* Spécification de la fontion de dessin */
  glutDisplayFunc(&DrawGLScene);  

  /* Spécification de la fontion de redimensionnement */
  glutReshapeFunc(&ReSizeGLScene);

  /* Spécification de la fontion de de gestion du clavier */
  glutKeyboardFunc(Keyboard_key);

  /* Spécification de la fontion special de gestion du clavier */

  glutSpecialFunc(Special_key);

  /* Intitialisation des paramètres de l'affichage et de la fenêtre */
  InitGL(640, 480);
  
  /* Lancement de la boucle OpenGL */  
  glutMainLoop();  

  return 1;
}



void Special_key(int key, int x, int y) 
{

  switch (key) 
  {


// Déblacement du robot

	case GLUT_KEY_RIGHT:  		
		base_x+= 0.5;
		break; 

	case GLUT_KEY_LEFT:  		
		base_x-= 0.5;
		break; 
	
	case GLUT_KEY_UP:  		
		base_z-=0.5;
		break; 
        
 	case GLUT_KEY_DOWN:  		  
		base_z+=0.5;
		break;
		
	case GLUT_KEY_PAGE_UP:
	  base_rot+=5.0;
	  break;
	
	case GLUT_KEY_PAGE_DOWN:
	  base_rot-=5.0;
	  break;

/*
// Interaction avec la camèra

	case GLUT_KEY_RIGHT:  		
		left_right+= 0.03;
		rotate_camera(left_right);
		break; 

	case GLUT_KEY_LEFT:  		
		left_right-= 0.03;
		rotate_camera(left_right);
		break; 
	
	case GLUT_KEY_UP:  		
		move_camera(0.02);
		break; 
        
 	case GLUT_KEY_DOWN:  		
		move_camera(-0.02);
		break;    


        default:
        break;
*/
  }    



   glutSwapBuffers();
   glutPostRedisplay();
}



void Keyboard_key(unsigned char key, int x, int y)
{

  switch (key) 
  {    

	case 'a':  		 
		if(first_x < 45.0)
		first_x += 1.0;
		break; 

	case 'q':  		
		if(first_x > -45.0)
		first_x -= 1.0;
		break; 
		
  case 'z':  		 
		if(first_z < 45.0)
		first_z += 1.0;
		break; 

	case 's':  		
		if(first_z > -45.0)
		first_z -= 1.0;
		break;
		
	case 'e':  		 
		if(second_x < 45.0)
		second_x += 1.0;
		break; 

	case 'd':  		
		if(second_x > -45.0)
		second_x -= 1.0;
		break;
		
	case 'r':  		 
		if(second_z < 45.0)
		second_z += 1.0;
		break; 

	case 'f':  		
		if(second_z > -45.0)
		second_z -= 1.0;
		break;
		
	case 't':  		 
		if(third_x < 45.0)
		third_x += 1.0;
		break; 

	case 'g':  		
		if(third_x > -45.0)
		third_x -= 1.0;
		break;
		
	case 'y':  		 
		if(third_z < 45.0)
		third_z += 1.0;
		break; 

	case 'h':  		
		if(third_z > -45.0)
		third_z -= 1.0;
		break;
		
	case 32:  		
		if(finger_x == 45.0)
		finger_x = 25.0;
		else finger_x = 45.0;
		break;

// Autres degrés de libertes
//..

        case ESCAPE :
               { 
	       glutDestroyWindow(window); 
	       exit(0);                   
               }

        default: 
        break;
  }    

   glutPostRedisplay();
   glutSwapBuffers();

}


void ground()
{

	// Draw a 1x1 grid along the X and Z axis'
        float i;
	for( i = -50; i <= 50; i += 5)
	{
		// Start drawing some lines
		glBegin(GL_LINES);

			// Do the horizontal lines (along the X)
			glVertex3f(-50, 0, i);
			glVertex3f(50, 0, i);

			// Do the vertical lines (along the Z)
			glVertex3f(i, 0, -50);
			glVertex3f(i, 0, 50);

		// Stop drawing lines
		glEnd();
	}
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
glNormal3f(0.0,0.0,1.0);
glVertex3f(profile[w*2]+vector[0],profile[w*2+1]+vector[1],+vector[2]);
}

glEnd();



}

void  Make_CallListes(){

// Objet par extrusion : segment
glNewList(OBJET_1,GL_COMPILE);
glPushMatrix();
glScalef(0.5f,0.6f,0.5f);
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


// Objet chargé : articulation (sphère)
glNewList(OBJET_4,GL_COMPILE);
glPushMatrix();
glScalef(0.8f,0.8f,0.8f);
DessinModele();
glPopMatrix();
glEndList();


}


void tronc_robot()
{

  glBegin(GL_QUADS);				

  //Face 1
  glNormal3f(0.0f,0.0f,1.0f);
  glVertex3f(1.0f,-1.0f,1.0f);	
  glNormal3f(0.0f,0.0f,1.0f);
  glVertex3f(1.0f,1.0f,1.0f);		
  glNormal3f(0.0f,0.0f,1.0f);  	
  glVertex3f(-1.0f,1.0f,1.0f);	
  glNormal3f(0.0f,0.0f,1.0f); 
  glVertex3f(-1.0f,-1.0f,1.0f);


  // Face 2
  glNormal3f(0.0f,0.0f,-1.0f);  
  glVertex3f(1.0f,-1.0f,-1.0f);	
  glNormal3f(0.0f,0.0f,-1.0f);  
  glVertex3f(1.0f,1.0f,-1.0f);		
  glNormal3f(0.0f,0.0f,-1.0f);  
  glVertex3f(-1.0f,1.0f,-1.0f);	
  glNormal3f(0.0f,0.0f,-1.0f);  
  glVertex3f(-1.0f,-1.0f,-1.0f);


  // Face 3
  glNormal3f(1.0f,0.0f,0.0f); 
  glVertex3f(1.0f,1.0f,-1.0f);	
  glNormal3f(1.0f,0.0f,0.0f);   
  glVertex3f(1.0f,1.0f,1.0f);		
  glNormal3f(1.0f,0.0f,0.0f);   
  glVertex3f(1.0f,-1.0f,1.0f);	
  glNormal3f(1.0f,0.0f,0.0f);  
  glVertex3f(1.0f,-1.0f,-1.0f);


  // Face 4
  glNormal3f(-1.0f,0.0f,0.0f);   
  glVertex3f(-1.0f,1.0f,-1.0f);	
  glNormal3f(-1.0f,0.0f,0.0f);   
  glVertex3f(-1.0f,1.0f,1.0f);		
  glNormal3f(-1.0f,0.0f,0.0f);   
  glVertex3f(-1.0f,-1.0f,1.0f);	
  glNormal3f(-1.0f,0.0f,0.0f);   
  glVertex3f(-1.0f,-1.0f,-1.0f);

  // Face 5
  glNormal3f(0.0f,1.0f,0.0f);   
  glVertex3f(1.0f,1.0f,-1.0f);	
  glNormal3f(0.0f,1.0f,0.0f); 
  glVertex3f(1.0f,1.0f,1.0f);		
  glNormal3f(0.0f,1.0f,0.0f); 
  glVertex3f(-1.0f,1.0f,1.0f);	
  glNormal3f(0.0f,1.0f,0.0f); 
  glVertex3f(-1.0f,1.0f,-1.0f);

  // Face 4
  glNormal3f(0.0f,-1.0f,0.0f); 
  glVertex3f(1.0f,-1.0f,-1.0f);	
  glNormal3f(0.0f,-1.0f,0.0f); 
  glVertex3f(1.0f,-1.0f,1.0f);		
  glNormal3f(0.0f,-1.0f,0.0f); 
  glVertex3f(-1.0f,-1.0f,1.0f);	
  glNormal3f(0.0f,-1.0f,0.0f); 
  glVertex3f(-1.0f,-1.0f,-1.0f);

  glEnd();					
}

void bras_robot()
{
  // base
  //glTranslatef(base_x,0.0,base_z);
  //glRotatef(base_rot,0.0,1.0,0.0);
  glCallList(OBJET_3);

  // segment 1
  float first_y = 0.25*5.5;
  glTranslatef(0.0,first_y,0.0);
  glRotatef(first_x,1.0,0.0,0.0);
  glRotatef(first_z,0.0,0.0,1.0);
  glCallList(OBJET_4);
  glCallList(OBJET_1);

  // segment2
  float second_y = 0.6*8.0;
  glTranslatef(0.0,second_y,0.0);
  glRotatef(second_x,1.0,0.0,0.0);
  glRotatef(second_z,0.0,0.0,1.0);
  glCallList(OBJET_4);
  glCallList(OBJET_1);

  // segment 3	
  glTranslatef(0.0,second_y,0.0);
  glRotatef(third_x,1.0,0.0,0.0);
  glRotatef(third_z,0.0,0.0,1.0);
  glCallList(OBJET_4);
  glCallList(OBJET_1);


  // pinces 1 & 2
  //float finger_x = 45.0;

  glTranslatef(0.0,second_y,0.0);
  glCallList(OBJET_4);

  glPushMatrix();

  glRotatef(finger_x,0.0,0.0,1.0);
  glCallList(OBJET_2);
  glTranslatef(0.0,5.85*0.3,0.0);
  glRotatef(-45.0,0.0,0.0,1.0);
  glCallList(OBJET_2);

  glPopMatrix();

  glRotatef(-finger_x,0.0,0.0,1.0);
  glCallList(OBJET_2);

  glTranslatef(0.0,5.85*0.3,0.0);
  glRotatef(45.0,0.0,0.0,1.0);
  glCallList(OBJET_2);
}


void move_camera(double speed)
{
// Gestion de la translation


}


void rotate_camera(double speed)
{
// Gestion de la rotation




}
