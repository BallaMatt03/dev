////////////////////////////////
// 2007			      //
// TD Informatique Graphique  //
// Université Paris 11	      //  
// Mehdi AMMI - ammi@limsi.fr //
////////////////////////////////

#include <GL/gl.h>	// Header pour OpenGL
#include <stdlib.h>     // Heard  Utilitaire général
#include <math.h>       // Header pour les fonctions mathèmatiques
#include <stdio.h>      // Fonctions d'entrée/sortie

#define MaxVertices     300
#define MaxPolygones    600

struct Faces{
        GLfloat V1[3];
        GLfloat V2[3];
        GLfloat V3[3];
        GLfloat N[3];
       };

struct  Faces Tri[MaxPolygones];
GLfloat Vertice[MaxVertices][3];
GLint   Poly[MaxPolygones][3];
GLint   NumPolygones;
GLint   NumVertices;


void Chargement(char *nombre)
{
 int i;

 FILE *in = fopen(nombre, "r");
 if (!in)
	return;
 fscanf(in, "%d\n", &NumVertices);
 for (i = 0; i<NumVertices; i++)
    fscanf(in, "%f %f %f\n", &Vertice[i][0], &Vertice[i][1], &Vertice[i][2]);
 fscanf(in, "%d\n", &NumPolygones);
 for (i = 0; i<NumPolygones; i++)
    fscanf(in, "%d %d %d\n", &Poly[i][0], &Poly[i][1], &Poly[i][2]);
 fclose(in);
}

//Calcul du module d'un vecteur
GLfloat Modulo(GLfloat x, GLfloat y, GLfloat z)
{
 GLfloat len;

 len = x*x + y*y + z*z;
 return (sqrt(len));
}



//Normalisation d'un vecteur
GLvoid Normalisation(GLfloat *x, GLfloat *y, GLfloat *z)
{
 GLfloat len;

 len = Modulo(*x, *y, *z);
 len = 1.0/len;
 (*x) *= len;
 (*y) *= len;
 (*z) *= len;
}

//Calcul du produit vectoriel de deux vecteurs
GLvoid ProduitVectoriel(GLfloat V1[], GLfloat V2[], GLfloat V3[],
                             GLfloat *NormalX, GLfloat *NormalY, GLfloat *NormalZ)
{
 GLfloat Qx, Qy, Qz, Px, Py, Pz;

 Px = V2[0]-V1[0];
 Py = V2[1]-V1[1];
 Pz = V2[2]-V1[2];
 Qx = V3[0]-V1[0];
 Qy = V3[1]-V1[1];
 Qz = V3[2]-V1[2];
 *NormalX = Py*Qz - Pz*Qy;
 *NormalY = Pz*Qx - Px*Qz;
 *NormalZ = Px*Qy - Py*Qx;
}

//Calcul de la normale d'un polygone (3 sommets)
void NormaleFace(void)
{
 GLfloat NormalX, NormalY, NormalZ;
 GLint i,j;

 for (i=0; i<NumPolygones; i++)
     {
      //Vertice 1
      j=Poly[i][0];
      Tri[i].V1[0] = Vertice[j][0];
      Tri[i].V1[1] = Vertice[j][1];
      Tri[i].V1[2] = Vertice[j][2];
      //Verice 2
      j=Poly[i][1];
      Tri[i].V2[0] = Vertice[j][0];
      Tri[i].V2[1] = Vertice[j][1];
      Tri[i].V2[2] = Vertice[j][2];
      //Vertice 3
      j=Poly[i][2];
      Tri[i].V3[0] = Vertice[j][0];
      Tri[i].V3[1] = Vertice[j][1];
      Tri[i].V3[2] = Vertice[j][2];

      //Calcul du vecteur Normal
      ProduitVectoriel(Tri[i].V1, Tri[i].V2, Tri[i].V3, &NormalX, &NormalY, &NormalZ);

      //Normalisaion du vecteur
      Normalisation(&NormalX, &NormalY, &NormalZ);

      //Sauvegarde des résultats
      Tri[i].N[0] = NormalX;
      Tri[i].N[1] = NormalY;
      Tri[i].N[2] = NormalZ;
    };
}

// Fonction de dessin du modèle
void DessinModele(void)
{


 Chargement("SPHERE.TXT");

 NormaleFace();

 int i;

 glBegin(GL_TRIANGLES);
 for (i=0; i<MaxPolygones; i++)
        {
        glNormal3fv(Tri[i].N);
        glVertex3fv(Tri[i].V1);
        glVertex3fv(Tri[i].V2);
        glVertex3fv(Tri[i].V3);
        }
 glEnd();
 

}



// Fonction de dessin du modèle
void DessinModele_2(void)
{


 Chargement("HEAD.TXT");

 NormaleFace();

 int i;

 glBegin(GL_TRIANGLES);
 for (i=0; i<MaxPolygones; i++)
        {
        glNormal3fv(Tri[i].N);
        glVertex3fv(Tri[i].V1);
        glVertex3fv(Tri[i].V2);
        glVertex3fv(Tri[i].V3);
        }
 glEnd();
 

}

