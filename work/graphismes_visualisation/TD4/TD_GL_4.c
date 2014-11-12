////////////////////////////////
// 2008			      //
// TD Informatique Graphique  //
// Université Paris 11	      //  
// Mehdi AMMI - ammi@limsi.fr //
////////////////////////////////

#include <GL/glut.h>    // Header pour GLUT 
#include <GL/gl.h>	// Header pour OpenGL
#include <GL/glu.h>	// Header pour GLu
#include <stdlib.h>     // Header  Utilitaire général
#include <math.h>       // Header fonctions mathématiques
#include "LOADER.c"     // Header pour les fonctions de chargement **

/* Postion de la source de lumière */

GLfloat light_position[] = {5.0f,30.0f,0.0f, 1.0f};
GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};

// Spot 1 

  GLfloat spot1[] = { 2.5F,0.8F,0.8F,1.0F };

  GLfloat spot1_pos[] = { -10.0F,27.0F,-50.0F,1.0F  };
  GLfloat spot1_dir[] = {0.0F,-1.0F,0.0F,1.0F };
  GLfloat spot1_cone = 25.0f;

// Spot 2 

  GLfloat spot2[] = { 2.5F,0.8F,0.8F,1.0F };

  GLfloat spot2_pos[] = { 10.0F,27.0F,-50.0F,1.0F  };
  GLfloat spot2_dir[] = {0.0F,-1.0F,0.0F,1.0F };
  GLfloat spot2_cone = 25.0f;


/* Definition matériaux */

GLfloat mat_specularWHITE[] ={255.0,255.0,255.0,1.0};
GLfloat mat_ambientWHITE[] ={255.0,255.0,255.0,1.0};
GLfloat mat_diffuseWHITE[] ={255.0,255.0,255.0,1.0};
GLfloat mat_shininessWHITE[] ={12.0 * 0.4};

GLfloat mat_specularWHITE_2[] ={1.0,1.0,1.0,1.0};
GLfloat mat_ambientWHITE_2[] ={1.0,1.0,1.0,1.0};
GLfloat mat_diffuseWHITE_2[] ={1.0,1.0,1.0,1.0};
GLfloat mat_shininessWHITE_2[] ={128.0 * 0.4};

GLfloat mat_specularBLUE[] ={0.75,0.75,0.75,1.0};
GLfloat mat_ambientBLUE[] ={0,0,1,1.0};
GLfloat mat_diffuseBLUE[] ={0.50,0.50,0.50,1.0};
GLfloat mat_shininessBLUE[] ={128.0 };

GLfloat mat_specularLIGHT_BLUE[] ={0.75,0.75,0.75,1.0};
GLfloat mat_ambientLIGHT_BLUE[] ={0,0.0,0.9,1.0};
GLfloat mat_diffuseLIGHT_BLUE[] ={0.90,0.90,0.90,1.0};
GLfloat mat_shininessLIGHT_BLUE[] ={128.0};


GLfloat mat_specularYELLOW[] ={0.75,0.75,0.75,1.0};
GLfloat mat_ambientYELLOW[] ={1,1,0,1.0};
GLfloat mat_diffuseYELLOW[] ={0.50,0.50,0.50,1.0};
GLfloat mat_shininessYELLOW[] ={128.0};



/* Identifiants des objets LIST */
#define OBJET_1 1 
#define OBJET_2 2
#define OBJET_3 3
#define OBJET_4 4
#define OBJET_5 5



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

float base_x = 0,base_y = 0, base_rot = 20;
float first_x = 0,first_y = -10;
float second_x = 70,second_y = -20;
float third_x = 70,third_y = 30;
float finger_x = 45.0;

/* Paramètres caméra de navigation */


float up_down = 0.0, left_right = -1.57;
float cam_pos_x = 0.0;
float cam_pos_z = 40.0;
float cam_look_x = 0.0;
float cam_look_z = 0.0;
float vect_x = 0.0;
float vect_z = 0.0;


/* Stockage des identifiants des textures  */ 
int texture[5];  //**

/* Structure de l'image : height, width, et data */
struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
};
typedef struct Image Image;


/* code ASCII pour la touche escape*/
#define ESCAPE 27
#define SPACE 32
/* Idantifiant de la fenêtre GLUT */
int window; 


/* Headers */

void Special_key(int key, int x, int y);
void Keyboard_key(unsigned char key, int x, int y);
void plan();
void revolution(int nbr_vertices, GLfloat profile[], float angle, int nbr_sections);
void extrude(int nbr_vertices, GLfloat profile[], GLfloat vector[]);
void  Make_CallListes();
void tronc_robot();
void Robot();
void move_camera(double speed);
void rotate_camera(double speed);
void SetMaterial(GLfloat spec[], GLfloat amb[], GLfloat diff[], GLfloat shin[]);
int ImageLoad(char *filename, Image *image);
void LoadGLTextures();
void Tableau();
void Chrome();
/* Fonction d'initialisation */
void InitGL(int Width, int Height)	        
{
// Couleur d'effacement du buffer de couleur
  glClearColor(0.1f, 0.1f, 0.3f, 0.0f);		

// paramètrage du Z-buffer
  glClearDepth(1.0);	
  glDepthFunc(GL_LESS);	
  glEnable(GL_DEPTH_TEST);	

// Activation et chargement des textures
    LoadGLTextures();				// Chargement des textures
    glEnable(GL_TEXTURE_2D);			// activation du texture mapping

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
  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,1000.0f);	



  glMatrixMode(GL_MODELVIEW);

}

/* Focntion de dessin */
void DrawGLScene()
{ 
// Effacement du buffer de couleur et de profondeur
  glClear(GL_DEPTH_BUFFER_BIT);		
  glLoadIdentity();		


// Paramètrage de l'éclairage
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  //glEnable(GL_LIGHTING);
  //glEnable(GL_LIGHT0);


//////////////////////////////////////////////////
// camera

  gluLookAt(cam_pos_x,80.0,cam_pos_z,cam_look_x,5.0,cam_look_z,0.0,1.0,0.0); 


///////////////////////////////////////////////////////
//// arrière plan

glPushMatrix();
glTranslatef(cam_pos_x,10.0,cam_pos_z);
glRotatef(-90.0,1.0,0.0,0.0);
glRotatef(180.0,1.0,0.0,0.0);
SetMaterial(mat_specularWHITE, mat_ambientWHITE, mat_diffuseWHITE, mat_shininessWHITE);
glBindTexture( GL_TEXTURE_2D, texture[4] );
GLUquadric* params_globe = gluNewQuadric();
gluQuadricTexture(params_globe,GL_TRUE);
gluSphere(params_globe,800.0,40,40);
gluDeleteQuadric(params_globe);
glPopMatrix();
glBindTexture( GL_TEXTURE_2D, 0 );
SetMaterial(mat_specularWHITE_2, mat_ambientWHITE_2, mat_diffuseWHITE_2, mat_shininessWHITE_2);

//////////////////////////////////////////////////
// Compilation des listes

  Make_CallListes();

// Materiaux
/*glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambientYELLOW);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuseYELLOW);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specularYELLOW);
glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininessYELLOW);*/

SetMaterial(mat_specularYELLOW, mat_ambientYELLOW, mat_diffuseYELLOW, mat_shininessYELLOW);

//////////////////////////////////////////////////
// sol  
  glPushMatrix();
  
  plan();
  glPopMatrix();


//////////////////////////////////////////////////
// mur
glPushMatrix();
glTranslatef(0.0, 0.0, -50.0);
glRotatef(90.0, 1.0,0.0,0.0);
glScalef(0.4,0.4,0.4);
plan();
glPopMatrix();
//////////////////////////////////////////////////
// Robot
/*glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambientWHITE_2);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuseWHITE_2);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specularWHITE_2);
glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininessWHITE_2);*/

SetMaterial(mat_specularWHITE_2, mat_ambientWHITE_2, mat_diffuseWHITE_2, mat_shininessWHITE_2);
Robot();

//////////////////////////////////////////////////
// Tableau
Tableau();

//////////////////////////////////////////////////
// Objets Chrome
//SetMaterial(mat_specularWHITE_2, mat_ambientWHITE_2, mat_diffuseWHITE_2, mat_shininessWHITE_2);
Chrome();

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

/*
// Interaction avec le robot

	case GLUT_KEY_RIGHT:  		
		base_x+= 0.5;
		break; 

	case GLUT_KEY_LEFT:  		
		base_x-= 0.5;
		break; 
	
	case GLUT_KEY_UP:  		
		base_y-=0.5;
		break; 
        
 	case GLUT_KEY_DOWN:  		  
		base_y+=0.5;
		break;    
*/

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
		if(first_y < 45.0)
		first_y += 1.0;
		break; 
	
	case 's':  		  
		if(first_y > -45.0)
		first_y -= 1.0;
		break; 

	case 'e':  		
		if(second_x > -45.0)
		second_x -= 1.0;
		break; 

	case 'd':  		 
		if(second_x < 45.0)
		second_x += 1.0;
		break; 

	case 'r':  		  
		if(second_y > -45.0)
		second_y -= 1.0;
		break; 
  
	case 'f':  		 
		if(second_y < 45.0)
		second_y += 1.0;
		break; 

	case 't':  		
		if(third_x < 90.0)
		third_x += 1.0;
		break; 

	case 'g':  
		if(third_x > -90.0)
		third_x -= 1.0;
		break; 

	case 'y':  
		if(third_y < 90.0)
		third_y += 1.0;
		break; 
        
	case 'h':  	  
		if(third_y > -90.0)
		third_y -= 1.0;
		break; 

	case 'p':  
		base_rot += 1.0;
		break; 
        
	case 'm':  	  
		base_rot -= 1.0;
		break; 


        case ESCAPE :
               { 
	       glutDestroyWindow(window); 
	       exit(0);                   
               }


	case SPACE :  		

		if(finger_x == 45.0)
			finger_x = 28.0;
		else
			finger_x = 45.0;

		break;  

		


        default: 
        break;
  }    

   glutPostRedisplay();
   glutSwapBuffers();

}


void plan()
{
        float inc_i = 0.5, inc_j=0.5;
        float i,j;
	for( i = -50; i <= 50; i += inc_i)
	{
		for( j = -50; j <= 50; j += inc_j)
		{
		glBegin(GL_QUADS);
			glNormal3f(0.0,1.0,0.0); 
			glVertex3f(i, 0, j);
			glVertex3f(i+inc_i, 0, j);

			glVertex3f(i+inc_i, 0, j+inc_j);
			glVertex3f(i, 0, j+inc_j);

		glEnd();
		}
	}
}

// Fonction permettant de creer les sphères Chromées
void Chrome()
{
	glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);
	glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);
	glBindTexture(GL_TEXTURE_2D,texture[4]);
	glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glPushMatrix();
    glTranslatef(-40.0,4.0,-30.0);
	glutSolidSphere(4,40.0,40.0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-40.0,4.0,-10.0);
	glutSolidSphere(4,40.0,40.0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-40.0,4.0,10.0);
	glutSolidSphere(4,40.0,40.0);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D,0);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
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

v2x = x2 - x1;
v2y = y2 - y1;
v2z = z2 - z1;

v1x = x3 - x2;
v1y = y3 - y2;
v1z = z3 - z2;

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


// Choix de la texture.
if(nbr_vertices == 9)
  glBindTexture(GL_TEXTURE_2D,texture[1]);

// face 1
int w;
glBegin(GL_POLYGON);

for(w=0; w<nbr_vertices-1; w++)
{
glNormal3f(0.0,0.0,-1.0);

// Coordonnées texture
glTexCoord2f(profile[w*2]*10/256,profile[w*2+1]*10/256);


glVertex3f(profile[w*2],profile[w*2+1],0.0);
}

glEnd();

// face 2
glBegin(GL_POLYGON);

for(w=0; w<nbr_vertices-1; w++)
{
glNormal3f(0.0,0.0,1.0);

// Coordonnées texture
glTexCoord2f((profile[w*2]+vector[0])*10/256,(profile[w*2+1]+vector[1])*10/256);

glVertex3f(profile[w*2]+vector[0],profile[w*2+1]+vector[1],+vector[2]);
}

glEnd();
glBindTexture(GL_TEXTURE_2D,0);


}

void  Make_CallListes(){



// Objet par extrusion : segment
glNewList(OBJET_1,GL_COMPILE);
SetMaterial(mat_specularWHITE_2, mat_ambientWHITE_2, mat_diffuseWHITE_2, mat_shininessWHITE_2);
glPushMatrix();
glScalef(0.5f,0.6f,0.5f);
glTranslatef(-2.0f,0.0f,-1.0f);
extrude(9, segment_2d, extrusion_vector);
glPopMatrix();
glEndList();



// Objet par extrusion : pince
glNewList(OBJET_2,GL_COMPILE);
SetMaterial(mat_specularLIGHT_BLUE, mat_ambientLIGHT_BLUE, mat_diffuseLIGHT_BLUE, mat_shininessLIGHT_BLUE);
glPushMatrix();
glScalef(0.2f,0.3f,0.2f);
glTranslatef(0.0f,0.0f,-1.0f);
extrude(15, pince_2d, extrusion_vector);
glPopMatrix();
glEndList();


// Objet par revoltion : base
glNewList(OBJET_3,GL_COMPILE);
SetMaterial(mat_specularLIGHT_BLUE, mat_ambientLIGHT_BLUE, mat_diffuseLIGHT_BLUE, mat_shininessLIGHT_BLUE);
glPushMatrix();
glScalef(0.25f,0.25f,0.25f);
revolution(6, base_2d, 360, 16);
glPopMatrix();
glEndList();


// Objet chargé : articulation (sphère)
glNewList(OBJET_4,GL_COMPILE);
SetMaterial(mat_specularLIGHT_BLUE, mat_ambientLIGHT_BLUE, mat_diffuseLIGHT_BLUE, mat_shininessLIGHT_BLUE);
glPushMatrix();
glScalef(0.8f,0.8f,0.8f);
DessinModele();
glPopMatrix();
glEndList();

// Objet chrome :  (sphère)
glNewList(OBJET_5,GL_COMPILE);
//SetMaterial(mat_specularWHITE_2, mat_ambientWHITE_2, mat_diffuseWHITE_2, mat_shininessWHITE_2);
glPushMatrix();

//Texture
//Sphere

glEndList();

}


void tronc_robot()
{

SetMaterial(mat_specularWHITE_2, mat_ambientWHITE_2, mat_diffuseWHITE_2, mat_shininessWHITE_2);
// Choix de la texture.
  /**/
  glBindTexture(GL_TEXTURE_2D, texture[0]);
  //Appliquer coordonnees

  glBegin(GL_QUADS);	

  //Face 1
  glNormal3f(0.0f,0.0f,1.0f);
  glTexCoord2f(1,0);
  glVertex3f(1.0f,-1.0f,1.0f);	
  glNormal3f(0.0f,0.0f,1.0f);
  glTexCoord2f(1,1);
  glVertex3f(1.0f,1.0f,1.0f);		
  glNormal3f(0.0f,0.0f,1.0f);
  glTexCoord2f(0,1);  	
  glVertex3f(-1.0f,1.0f,1.0f);	
  glNormal3f(0.0f,0.0f,1.0f);
  glTexCoord2f(0,0); 
  glVertex3f(-1.0f,-1.0f,1.0f);

  


  // Face 2
  glNormal3f(0.0f,0.0f,-1.0f);
  glTexCoord2f(1,0);  
  glVertex3f(1.0f,-1.0f,-1.0f);	
  glNormal3f(0.0f,0.0f,-1.0f);
  glTexCoord2f(1,1);
  glVertex3f(1.0f,1.0f,-1.0f);		
  glNormal3f(0.0f,0.0f,-1.0f);
  glTexCoord2f(0,1);  
  glVertex3f(-1.0f,1.0f,-1.0f);	
  glNormal3f(0.0f,0.0f,-1.0f);
  glTexCoord2f(0,0); 
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

  // Face 6
  glNormal3f(0.0f,-1.0f,0.0f); 
  glVertex3f(1.0f,-1.0f,-1.0f);	
  glNormal3f(0.0f,-1.0f,0.0f); 
  glVertex3f(1.0f,-1.0f,1.0f);		
  glNormal3f(0.0f,-1.0f,0.0f); 
  glVertex3f(-1.0f,-1.0f,1.0f);	
  glNormal3f(0.0f,-1.0f,0.0f); 
  glVertex3f(-1.0f,-1.0f,-1.0f);

  glEnd();				
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Robot()
{
//////////////////////////////////////////////////
// robot 

glPushMatrix();

glTranslatef(base_x,0.0,base_y);

glPushMatrix();
glScalef(2.0,2.0,2.0);
glCallList(OBJET_3);
glPopMatrix();

glTranslatef(0.0,4.0+(2*1.375),0.0);
glRotatef(base_rot,0.0,1.0,0.0);


glPushMatrix();
glScalef(3.0,4.0,3.0);
tronc_robot();
glPopMatrix();

glTranslatef(0.0,2.0,0.0);

//////////////////////////////////////////////////
// bras 1
	glPushMatrix();
	
	glTranslatef(-3.0,0.0,0.0);

	glRotatef(90.0,0.0,0.0,1.0);

// base
        
	glCallList(OBJET_3);

// segment 1
		glTranslatef(0.0,1.375,0.0);

		glRotatef(first_x,1,0,0);
		glRotatef(first_y,0,0,1);

		glCallList(OBJET_4);
		glCallList(OBJET_1);

// segment2
			glTranslatef(0.0,4.8,0.0);

			glRotatef(second_x,1,0,0);
			glRotatef(second_y,0,0,1);

			glCallList(OBJET_4);
			glCallList(OBJET_1);

// segment 3	
				glTranslatef(0.0,4.8,0.0);

				glRotatef(third_x,1,0,0);
				glRotatef(third_y,0,0,1);

				glCallList(OBJET_4);
				glCallList(OBJET_1);

// pinces 1 & 2
					glTranslatef(0.0,4.8,0.0);

					glCallList(OBJET_4);


						glPushMatrix();

						glRotatef(finger_x,0,0,1);

						glCallList(OBJET_2);

						glTranslatef(0.0,1.755,0.0);
						glRotatef(-45,0,0,1);

						glCallList(OBJET_2);
		
						glPopMatrix();



						glPushMatrix();

						glRotatef(-finger_x,0,0,1);

						glCallList(OBJET_2);

						glTranslatef(0.0,1.755,0.0);
						glRotatef(45,0,0,1);

						glCallList(OBJET_2);

						glPopMatrix();


	glPopMatrix();

//////////////////////////////////////////////////

//////////////////////////////////////////////////
// bras 2
	glPushMatrix();

	glTranslatef(3.0,0.0,0.0);

	glRotatef(-90.0,0.0,0.0,1.0);

// base
        
	glCallList(OBJET_3);

// segment 1
		glTranslatef(0.0,1.375,0.0);

		glRotatef(first_x,1,0,0);
		glRotatef(-first_y,0,0,1);

		glCallList(OBJET_4);
		glCallList(OBJET_1);

// segment2
			glTranslatef(0.0,4.8,0.0);

			glRotatef(second_x,1,0,0);
			glRotatef(-second_y,0,0,1);

			glCallList(OBJET_4);
			glCallList(OBJET_1);

// segment 3	
				glTranslatef(0.0,4.8,0.0);

				glRotatef(third_x,1,0,0);
				glRotatef(-third_y,0,0,1);

				glCallList(OBJET_4);
				glCallList(OBJET_1);

// pinces 1 & 2
					glTranslatef(0.0,4.8,0.0);

					glCallList(OBJET_4);


						glPushMatrix();

						glRotatef(finger_x,0,0,1);

						glCallList(OBJET_2);

						glTranslatef(0.0,1.755,0.0);
						glRotatef(-45,0,0,1);

						glCallList(OBJET_2);
		
						glPopMatrix();



						glPushMatrix();

						glRotatef(-finger_x,0,0,1);

						glCallList(OBJET_2);

						glTranslatef(0.0,1.755,0.0);
						glRotatef(45,0,0,1);

						glCallList(OBJET_2);

						glPopMatrix();


	glPopMatrix();

//////////////////////////////////////////////////
//tête du robot
glBindTexture(GL_TEXTURE_2D, texture[3]);
glPushMatrix();
  // Choix de la texture.
  
  SetMaterial(mat_specularWHITE_2, mat_ambientWHITE_2, mat_diffuseWHITE_2, mat_shininessWHITE_2);
  glTranslatef(0.0,2.0,0.0);
  glRotatef(-90.0,1.0,0.0,0.0);
  GLUquadric* params_globe = gluNewQuadric();
  gluQuadricTexture(params_globe,GL_TRUE);
  gluSphere(params_globe,2.0,40,40);
  gluDeleteQuadric(params_globe);
  
glPopMatrix();
glPopMatrix();
glBindTexture(GL_TEXTURE_2D, 0);
//////////////////////////////////////////////////

}



void Tableau()
{

// Tableau
glPushMatrix();

// Choix de la texture.
glBindTexture(GL_TEXTURE_2D, texture[2]);

SetMaterial(mat_specularWHITE, mat_ambientWHITE, mat_diffuseWHITE, mat_shininessWHITE);
  
// Positionnement du tableau
glTranslatef(0.0, 10.0, -49.0);
glRotatef(90.0,1.0,0.0,0.0);
glScalef(2.0,1.0,2.0);

  // Image
  glPushMatrix();
  glNormal3f(0.0f,-1.0f,0.0f);
  glBegin(GL_POLYGON);
  glTexCoord2f(0.0,1.0);
  glVertex3f(-2.0f,0.0f,-3.0f);
  glTexCoord2f(0.8,1.0);
  glVertex3f(2.0f,0.0f,-3.0f);
  glTexCoord2f(0.8,0.0);
  glVertex3f(2.0f,0.0f,3.0f);
  glTexCoord2f(0.0,0.0);
  glVertex3f(-2.0f,0.0f,3.0f);
  glEnd();
  glPopMatrix();

  // Cadre_1 // celui du bas
  glPushMatrix();
  glTranslatef(0.0f,0.0f,3.5f);
  glRotatef(0.0,1.0,0.0,0.0);
  glBegin(GL_POLYGON);
  glNormal3f(0.0f,-1.0f,0.0f);
  glTexCoord2f(1.0,1.0);
  glVertex3f(-3.0f,0.0f,-0.5f);
  glTexCoord2f(1.0,0.0);
  glVertex3f(3.0f,0.0f,-0.5f);
  glTexCoord2f(0.8,0.0);
  glVertex3f(3.0f,0.0f,0.5f);
  glTexCoord2f(0.8,1.0);
  glVertex3f(-3.0f,0.0f,0.5f);
  glEnd();
  glPopMatrix();

  // Cadre_2
  glPushMatrix();
  glTranslatef(2.5f,0.0f,0.0f);
  glRotatef(90.0,0.0,1.0,0.0);
  glBegin(GL_POLYGON);
  glNormal3f(0.0f,-1.0f,0.0f);
  glTexCoord2f(1.0,0.0);
  glVertex3f(-3.0f,0.0f,-0.5f);
  glTexCoord2f(1.0,1.0);
  glVertex3f(3.0f,0.0f,-0.5f);
  glTexCoord2f(0.8,1.0);
  glVertex3f(3.0f,0.0f,0.5f);
  glTexCoord2f(0.8,0.0);
  glVertex3f(-3.0f,0.0f,0.5f);
  glEnd();
  glPopMatrix();

  // Cadre_3
  glPushMatrix();
  glTranslatef(-2.5f,0.0f,0.0f);
  glRotatef(-90.0,0.0,1.0,0.0);
  glBegin(GL_POLYGON);
  glNormal3f(0.0f,-1.0f,0.0f);
  glTexCoord2f(1.0,1.0);
  glVertex3f(-3.0f,0.0f,-0.5f);
  glTexCoord2f(1.0,0.0);
  glVertex3f(3.0f,0.0f,-0.5f);
  glTexCoord2f(0.8,0.0);
  glVertex3f(3.0f,0.0f,0.5f);
  glTexCoord2f(0.8,1.0);
  glVertex3f(-3.0f,0.0f,0.5f);
  glEnd();
  glPopMatrix();

  // Cadre_4
  glPushMatrix();
  glTranslatef(0.0f,0.0f,-3.5f);
  glRotatef(-180.0,0.0,1.0,0.0);
  glBegin(GL_POLYGON);
  glNormal3f(0.0f,-1.0f,0.0f);
  glTexCoord2f(1.0,1.0);
  glVertex3f(-3.0f,0.0f,-0.5f);
  glTexCoord2f(1.0,0.0);
  glVertex3f(3.0f,0.0f,-0.5f);
  glTexCoord2f(0.8,0.0);
  glVertex3f(3.0f,0.0f,0.5f);
  glTexCoord2f(0.8,1.0);
  glVertex3f(-3.0f,0.0f,0.5f);
  glEnd();
  glPopMatrix();

  glPopMatrix();
  glBindTexture(GL_TEXTURE_2D, 0);
}

void move_camera(double speed)
{
	vect_x = cam_look_x - cam_pos_x;
	vect_z = cam_look_z - cam_pos_z;

	cam_pos_x += vect_x * speed;
	cam_pos_z += vect_z * speed;

	cam_look_x += vect_x * speed;
	cam_look_z += vect_z * speed;
}


void rotate_camera(double speed)
{
	vect_x = cam_look_x - cam_pos_x;
	vect_z = cam_look_z - cam_pos_z;

	// Calculate the sine and cosine of the angle once
	float cosTheta = (float)cos(speed);
	float sinTheta = (float)sin(speed);
 
	double new_x = sqrt(pow(vect_x,2) + pow(vect_z,2)) * cosTheta;
	double new_z = sqrt(pow(vect_x,2) + pow(vect_z,2)) * sinTheta;

	cam_look_x = cam_pos_x + new_x;
	cam_look_z = cam_pos_z + new_z;
}




void SetMaterial(GLfloat spec[], GLfloat amb[], GLfloat diff[], GLfloat shin[])
{
  glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
  glMaterialfv(GL_FRONT, GL_SHININESS, shin);
  glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
}





// chargeur d'image BPM...pour des images 24 bit avec un seul plan.  
int ImageLoad(char *filename, Image *image) {
    FILE *file;
    unsigned long size;                 // Taille de l'image en Byte.
    unsigned long i;                    // Variable d'incrémentation.
    unsigned short int planes;          // Nombre de plans dans l'image (1 seul)
    unsigned short int bpp;             // Nomre de bits apr pixel  (24 bits)
    char temp;                          // Varialbe de stockage temporaire.

    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL)
    {
	printf("File Not Found : %s\n",filename);
	return 0;
    }

    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);

    // read the width
    if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
	printf("Error reading width from %s.\n", filename);
	return 0;
    }
    printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height 
    if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {
	printf("Error reading height from %s.\n", filename);
	return 0;
    }
    printf("Height of %s: %lu\n", filename, image->sizeY);
    
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = image->sizeX * image->sizeY * 3;

    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
	printf("Error reading planes from %s.\n", filename);
	return 0;
    }
    if (planes != 1) {
	printf("Planes from %s is not 1: %u\n", filename, planes);
	return 0;
    }

    // read the bpp
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
	printf("Error reading bpp from %s.\n", filename);
	return 0;
    }
    if (bpp != 24) {
	printf("Bpp from %s is not 24: %u\n", filename, bpp);
	return 0;
    }
	
    // seek past the rest of the bitmap header.
    fseek(file, 24, SEEK_CUR);

    // read the data. 
    image->data = (char *) malloc(size);
    if (image->data == NULL) {
	printf("Error allocating memory for color-corrected image data");
	return 0;	
    }

    if ((i = fread(image->data, size, 1, file)) != 1) {
	printf("Error reading image data from %s.\n", filename);
	return 0;
    }

    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
	temp = image->data[i];
	image->data[i] = image->data[i+2];
	image->data[i+2] = temp;
    }
    
    // we're done.
    return 1;
}



    
// Chargement du Bitmap et conversion en texture
void LoadGLTextures() {	

// Texture tronc robot

    // Chargement de la texutre
    Image *image1;

    // Allocation de l'espace de la texture
    image1 = (Image *) malloc(sizeof(Image));
    if (image1 == NULL) {
	printf("Error allocating space for image");
	exit(0);
    }

    if (!ImageLoad("robot_tronc.bmp", image1)) {
	exit(1);
    }

    // Création de texture	
    glGenTextures(1, &texture[0]);
    glBindTexture(GL_TEXTURE_2D, texture[0]);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // Paramétrage du grossissement
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // Paramétrage de la réduction

    // texture 2d, niveau de détail 0, 3 composantes (red, green, blue),taille suivant x, taille suivant y, 
    // bordure 0, données couleurs de type rgb, données de type unsigned byte, les données.
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->data);



// Texture segments robot
    // Chargement de la texutre
    Image *image2;

    // Allocation de l'espace de la texture
    image2 = (Image *) malloc(512*512/*sizeof(Image)*/);
    if (image2 == NULL) {
  printf("Error allocating space for image");
  exit(0);
    }

    if (!ImageLoad("robot_segment.bmp", image2)) {
  exit(1);
    }

    // Création de texture  
    glGenTextures(1, &texture[1]);
    glBindTexture(GL_TEXTURE_2D, texture[1]);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // Paramétrage du grossissement
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // Paramétrage de la réduction

    // texture 2d, niveau de détail 0, 3 composantes (red, green, blue),taille suivant x, taille suivant y, 
    // bordure 0, données couleurs de type rgb, données de type unsigned byte, les données.
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image2->sizeX, image2->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image2->data);

// Texture Tableau
    // Chargement de la texutre
    Image *image3;

    // Allocation de l'espace de la texture
    image3 = (Image *) malloc(512*512);
    if (image3 == NULL) {
  printf("Error allocating space for image");
  exit(0);
    }

    if (!ImageLoad("robot_copine.bmp", image3)) {
  exit(1);
    }

    // Création de texture  
    glGenTextures(1, &texture[2]);
    glBindTexture(GL_TEXTURE_2D, texture[2]);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // Paramétrage du grossissement
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // Paramétrage de la réduction

    // texture 2d, niveau de détail 0, 3 composantes (red, green, blue),taille suivant x, taille suivant y, 
    // bordure 0, données couleurs de type rgb, données de type unsigned byte, les données.
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image3->sizeX, image3->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image3->data);

  // Texture Tableau
    // Chargement de la texutre
    Image *image4;

    // Allocation de l'espace de la texture
    image4 = (Image *) malloc(512*512);
    if (image4 == NULL) {
  printf("Error allocating space for image");
  exit(0);
    }

    if (!ImageLoad("robot_tete.bmp", image4)) {
  exit(1);
    }

    // Création de texture  
    glGenTextures(1, &texture[3]);
    glBindTexture(GL_TEXTURE_2D, texture[3]);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // Paramétrage du grossissement
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // Paramétrage de la réduction

    // texture 2d, niveau de détail 0, 3 composantes (red, green, blue),taille suivant x, taille suivant y, 
    // bordure 0, données couleurs de type rgb, données de type unsigned byte, les données.
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image4->sizeX, image4->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image4->data);



// Textures environnement
    // Chargement de la texutre
    Image *image5;

    // Allocation de l'espace de la texture
    image5 = (Image *) malloc(/*sizeof(Image)*/512*512);
    if (image5 == NULL) {
	printf("Error allocating space for image");
	exit(0);
    }

    if (!ImageLoad("Texture_environnement.bmp", image5)) {
	exit(1);
    }

    // Création de texture	
    glGenTextures(1, &texture[4]);
    glBindTexture(GL_TEXTURE_2D, texture[4]);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // Paramétrage du grossissement
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // Paramétrage de la réduction

    // texture 2d, niveau de détail 0, 3 composantes (red, green, blue),taille suivant x, taille suivant y, 
    // bordure 0, données couleurs de type rgb, données de type unsigned byte, les données.
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image5->sizeX, image5->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image5->data);


};
