/* -------------------- */
/* --- filtr1_SSE.c --- */
/* -------------------- */

#include <stdio.h>
#include <stdlib.h>

// --- NRC Framework --- //
#include "def.h"
#include "nrutil.h"
//#include "timers_b.h"
// --- vNRC Framework --- //
#include "vdef.h"
#include "vnrutil.h"

#include "mutil.h"


#include "filtre2_SSE.h"

void vec_diff(vuint8 x1, vuint8 x2, vuint8 *y)
{
	*y = _mm_sub_epi8(_mm_max_epi(x1, x2),_mm_min_epi(x1, x2));
}

void vec_cmp_threshold(vuint8 threshold_128, vuint8 o_128, vuint8 *e)
{
	*e = _mm_cmptlt_epi8(threshold_128, o_128);
}

void vec_cmp_inc_dec()
{

}

void test_cmp_mul(vuint8 N, vuint8 * resultat, vuint8 vinput)
{
	switch(N)
	{
		case 1:
	}
}

void vec_left1()
{

}









/* ------------------------------------------------------------------------- */
void add_vf32vector(vfloat32 *vX1, vfloat32 *vX2, int i0, int i1, vfloat32 *vY)
/* ------------------------------------------------------------------------- */
{
    int i;
    vfloat32 x1, x2, y;

    for(i=i0; i<=i1; i++) {
        
        x1 = _mm_load_ps((float32*) &vX1[i]);
        x2 = _mm_load_ps((float32*) &vX2[i]);
        
        y = _mm_add_ps(x1, x2);
        
        display_vfloat32(x1, "%4.0f", "x1 ="); puts("");
        display_vfloat32(x2, "%4.0f", "x2 ="); puts("");
        display_vfloat32(y,  "%4.0f", "y  ="); puts("");

        _mm_store_ps((float*) &vY[i], y);
        puts("-------------------");
    }
}
/* --------------------------------------------------------------- */
vfloat32 dot_vf32vector(vfloat32 *vX1, vfloat32 *vX2, int i0, int i1)
/* --------------------------------------------------------------- */
{
	int i;
    vfloat32 z, z0, z1, z2, zTemp;
    vfloat32 x1, x2, y;

    z = _mm_set_ps(0,0,0,0);
    
    for(i=i0; i<=i1; i++) {
		
		x1 = _mm_load_ps((float32*) &vX1[i]);
        x2 = _mm_load_ps((float32*) &vX2[i]);
        
        y = _mm_mul_ps(x1, x2);
        
        z = _mm_add_ps(z, y);
        
        puts("-------------------");        
	}
	
	/* Avec deux shuffle (SSE)
	z = _mm_shuffle_ps(z,z,_MM_SHUFFLE(1,0,3,2));
	z0 = _mm_add_ps(z,zTemp);
	z1 = _mm_shuffle_ps(z0,z0,_MM_SHUFFLE(0,3,2,1));
	z2 = _mm_add_ps(z0,z1);
	*/
	
	/* Avec un seul shuffle (SSE) */
	zTemp = z;
	z2 = z;
	zTemp = _mm_shuffle_ps(zTemp,zTemp,_MM_SHUFFLE(0,3,2,1));
	z2 = _mm_add_ps(z2,zTemp);
	zTemp = _mm_shuffle_ps(zTemp,zTemp,_MM_SHUFFLE(0,3,2,1));
	z2 = _mm_add_ps(z2,zTemp);
	zTemp = _mm_shuffle_ps(zTemp,zTemp,_MM_SHUFFLE(0,3,2,1));
	z2 = _mm_add_ps(z2,zTemp);
    
    
    return z2;
}
/*
 * Partie 3.1 :
 * Question 3.1.1
 * Y de taille n
 * Quelle doit etre la taille de X ?
 * La taille de X doit etre n+2 pour somme à trois ou n+4 pour somme à 5
 */ 
/* ---------------------------------------------------------- */
void sum3_vf32vector(vfloat32 *vX, int i0, int i1, vfloat32 *vY)
/* ---------------------------------------------------------- */
{
	int i;
	vfloat32 x0, x1, x2, xu, xp, y;
	for(i=i0; i<=i1; i++) {
		/*Recuperer les trois vecteurs*/
		x0 = _mm_load_ps((float32*) &vX[i-1]);
		x1 = _mm_load_ps((float32*) &vX[i]);
		x2 = _mm_load_ps((float32*) &vX[i+1]);
		
		/*Premier decalage : a droite*/
		xp = vec_right1_ps(x0, x1);
		
		/*Deuxieme decalage : a gauche*/
		xu = vec_left1_ps(x1, x2);
		
		/*Additionner les vecteurs*/
		y = _mm_add_ps(xp,x1);
		y = _mm_add_ps(y,xu);
		
		_mm_store_ps((float*) &vY[i], y);
	}
}
/* ---------------------------------------------------------- */
void sum5_vf32vector(vfloat32 *vX, int i0, int i1, vfloat32 *vY)
/* ---------------------------------------------------------- */
{
	int i;
	vfloat32 x0, x1, x2, x3, x4, x5, x6, y;
	for(i=i0; i<=i1; i++) {
		/*Recuperer les trois vecteurs*/
		x0 = _mm_load_ps((float32*) &vX[i-1]);
		x1 = _mm_load_ps((float32*) &vX[i]);
		x2 = _mm_load_ps((float32*) &vX[i+1]);
		
		/*Premier decalage : a droite*/
		x3 = vec_right2_ps(x0,x1);
		x4 = vec_right1_ps(x0,x1);
		
		/*Deuxieme decalage : a gauche*/
		x5 = vec_left2_ps(x1,x2);
		x6 = vec_left1_ps(x1,x2);
		
		/*Additionner les vecteurs*/
		y = _mm_add_ps(x1,x3);
		y = _mm_add_ps(y,x4);
		y = _mm_add_ps(y,x5);
		y = _mm_add_ps(y,x6);
		
		_mm_store_ps((float*) &vY[i], y);
	}
}
/* ---------------------------------------------------------- */
void min3_vf32vector(vfloat32 *vX, int i0, int i1, vfloat32 *vY)
/* ---------------------------------------------------------- */
{
	int i;
	vfloat32 x0, x1, x2, xu, xp, y;
	for(i=i0; i<=i1; i++) {
		/*Recuperer les trois vecteurs*/
		x0 = _mm_load_ps((float32*) &vX[i-1]);
		x1 = _mm_load_ps((float32*) &vX[i]);
		x2 = _mm_load_ps((float32*) &vX[i+1]);
		
		/*Premier decalage : a droite*/
		xp = vec_right1_ps(x0, x1);
		
		/*Deuxieme decalage : a gauche*/
		xu = vec_left1_ps(x1, x2);
		
		/*Recuperer les minimums*/
		y = _mm_min_ps(xp,x1);
		y = _mm_min_ps(y,xu);
		
		_mm_store_ps((float*) &vY[i], y);
	}
}
/* ---------------------------------------------------------- */
void min5_vf32vector(vfloat32 *vX, int i0, int i1, vfloat32 *vY)
/* ---------------------------------------------------------- */
{
	int i;
	vfloat32 x0, x1, x2, x3, x4, x5, x6, y;
	for(i=i0; i<=i1; i++){
		/*Recuperer les trois vecteurs*/
		x0 = _mm_load_ps((float32*) &vX[i-1]);
		x1 = _mm_load_ps((float32*) &vX[i]);
		x2 = _mm_load_ps((float32*) &vX[i+1]);
		
		/*Premier decalage : a droite*/
		x3 = vec_right2_ps(x0,x1);
		x4 = vec_right1_ps(x0,x1);
		
		/*Deuxieme decalage : a gauche*/
		x5 = vec_left2_ps(x1,x2);
		x6 = vec_left1_ps(x1,x2);
		
		/*Recuperer les minimums*/
		y = _mm_min_ps(x1,x3);
		y = _mm_min_ps(y,x4);
		y = _mm_min_ps(y,x5);
		y = _mm_min_ps(y,x6);
		
		_mm_store_ps((float*) &vY[i], y);
	}
	
}
// -------------------------------------------------------------
void positive_add3_vf32vector(vfloat32 *vX, int n, vfloat32 *vY)
// -------------------------------------------------------------
{
	int i, j = 0;
	vfloat32 x0, x0_tmp, x1, x1_tmp, x2, x2_tmp, x3, x3_tmp, xu, xp, y, z;
	
	/*Vecteur z pour detecter les valeurs inferieures a zero*/
	z = _mm_set_ps(0,0,0,0);
	
	for(i=0; i<n; i++) {
		/*Recuperer vecteur i-1*/
		x0 = _mm_load_ps((float32*) &vX[i-1]);
		/*Le comparer a un vecteur de zeros*/
		x0_tmp = _mm_cmplt_ps(z,x0);
		/*Si il y a des negatifs, mettre 0*/
		x0=_mm_or_ps(_mm_and_ps(x0_tmp,x0),_mm_andnot_ps(x0_tmp,x0_tmp));
		
		/*Recuperer vecteur i*/
		x1 = _mm_load_ps((float32*) &vX[i]);
		/*Le comparer a un vecteur de zeros*/
		x1_tmp = _mm_cmplt_ps(z,x1);
		/*Si il y a des negatifs, mettre 0*/
		x1=_mm_or_ps(_mm_and_ps(x1_tmp,x1),_mm_andnot_ps(x1_tmp,x1_tmp));
		
		/*Recuperer vecteur i+1*/
        x2 = _mm_load_ps((float32*) &vX[i+1]);
        /*Le comparer a un vecteur de zeros*/
		x2_tmp = _mm_cmplt_ps(z,x2);
		/*Si il y a des negatifs, mettre 0*/
		x2=_mm_or_ps(_mm_and_ps(x2_tmp,x2),_mm_andnot_ps(x2_tmp,x2_tmp));

		/*Calcul de la somme pour 3 avec que des nombres positifs*/
			/*Premier decalage : a droite*/
			xp = vec_right1_ps(x0, x1);

			/*Deuxieme decalage : a gauche*/
			xu = vec_left1_ps(x1, x2);

			/*Additionner les vecteurs*/
			y = _mm_add_ps(xp,x1);
			y = _mm_add_ps(y,xu);

		_mm_store_ps((float*) &vY[i], y);
	}
}
// -------------------------------------------------------------
void positive_avg3_vf32vector(vfloat32 *vX, int n, vfloat32 *vY)
// -------------------------------------------------------------
{
	int i, j = 0;
	vfloat32 x0, x1, x2, x0_tmp, x1_tmp, x2_tmp, xu, xp, y, x, z, uns, x_final, res;

    z = _mm_set_ps(0,0,0,0);
    uns = _mm_set_ps(1,1,1,1);

	for(i=0; i<n; i++){
		/*Recuperer vecteur i-1*/
		x0 = _mm_load_ps((float32*) &vX[i-1]);
		/*Le comparer a un vecteur de zeros*/
		x0_tmp = _mm_cmplt_ps(z,x0);
		/*Si il y a des negatifs, mettre 0*/
		x0=_mm_or_ps(_mm_and_ps(x0_tmp,x0),_mm_andnot_ps(x0_tmp,x0_tmp));
		
		/*Recuperer vecteur i*/
		x1 = _mm_load_ps((float32*) &vX[i]);
		/*Le comparer a un vecteur de zeros*/
		x1_tmp = _mm_cmplt_ps(z,x1);
		/*Si il y a des negatifs, mettre 0*/
		x1=_mm_or_ps(_mm_and_ps(x1_tmp,x1),_mm_andnot_ps(x1_tmp,x1_tmp));
		
		/*Recuperer vecteur i+1*/
        x2 = _mm_load_ps((float32*) &vX[i+1]);
        /*Le comparer a un vecteur de zeros*/
		x2_tmp = _mm_cmplt_ps(z,x2);
		/*Si il y a des negatifs, mettre 0*/
		x2=_mm_or_ps(_mm_and_ps(x2_tmp,x2),_mm_andnot_ps(x2_tmp,x2_tmp));
		
		/*Calcul de la somme y avec les nombres positifs gardes (numerateur)*/
			/*Premier decalage : a droite*/
			xp = vec_right1_ps(x0, x1);
			
			/*Deuxieme decalage : a gauche*/
			xu = vec_left1_ps(x1, x2);
			
			/*Additionner les vecteurs*/
			y = _mm_add_ps(xp,x1);
			y = _mm_add_ps(y,xu);
		
		/*Calcul la somme x sur le nombre de nombres positifs (denominateur)*/
			x0_tmp = _mm_and_ps(x0_tmp,uns);
			x1_tmp = _mm_and_ps(x1_tmp,uns);
			x2_tmp = _mm_and_ps(x2_tmp,uns);
			
			/*Premier decalage : a droite*/
			xp = vec_right1_ps(x0_tmp, x1_tmp);
			
			/*Deuxieme decalage : a gauche*/
			xu = vec_left1_ps(x1_tmp, x2_tmp);
			
			/*Additionner les vecteurs*/
			x = _mm_add_ps(xp,x1_tmp);
			x = _mm_add_ps(x,xu);
		
		/*Mettre des 1 la ou il y a des zeros*/
			x_final = _mm_cmplt_ps(z,x);
			x=_mm_or_ps(_mm_and_ps(x_final,x),_mm_andnot_ps(x_final,uns));
		
		/*Calculer la moyenne en divisant ces deux vecteurs*/
		    res = _mm_div_ps(y,x);
		    
		_mm_store_ps((float*) &vY[i], res);
	}
}
// ---------------------------
void testu_positive_add3(void)
// ---------------------------
{
    int i;
    vfloat32 x0, x1, x2;
        
    vfloat32 zero = _mm_set1_ps(0);
    vfloat32 one  = _mm_set1_ps(1);
    
    x0 = _mm_setr_ps(-1,  1,  2, 3);
    x1 = _mm_setr_ps(-1, -1,  4, 5);
    x2 = _mm_setr_ps(-1,  6, -1, 7);
    
    display_vfloat32(x0, "%4.0f", "x0 ="); puts("");
    display_vfloat32(x1, "%4.0f", "x1 ="); puts("");
    display_vfloat32(x2, "%4.0f", "x2 ="); puts("\n");    
}
/* ========================== */
/* === Fonctions de tests === */
/* ========================== */


/* ---------------------------- */
void test_add_dot_vf32vector(void)
/* ---------------------------- */
{
    int n = 4*4;
    int card; // cardinal of vector type

    int si0, si1; // scalar indices
    int vi0, vi1; // vector indices
    int mi0, mi1; // memory (bounded) indices

    vfloat32 *vX1, *vX2, *vY, d;

    puts("------------------------------");
    puts("-- test_add_dot_vf32vector ---");
    puts("------------------------------");

    // ------------------------- //
    // -- calculs des indices -- //
    // ------------------------- //

    card = card_vfloat32();

    si0 = 0;
    si1 = n-1;
    s2v1D(si0, si1, card, &vi0, &vi1);
    v2m1D(vi0, vi1, card, &mi0, &mi1);
    
    // ------------------------------------------- //
    // -- allocation des tableaux 1D vectoriels -- //
    // ------------------------------------------- //

    vX1 = vf32vector(vi0, vi1);
    vX2 = vf32vector(vi0, vi1);
    vY  = vf32vector(vi0, vi1);

    // ---------- //
    // -- init -- //
    // ---------- //

    init_vf32vector_param(vX1, vi0, vi1, 1, 1);
    init_vf32vector_param(vX2, vi0, vi1, 1, 2);
    zero_vf32vector(vY, vi0, vi1);

    // --------------- //
    // -- affichage -- //
    // --------------- //

    // affichage classique sur une ligne: appel de la fonction scalaire
    display_f32vector((float32*) vX1, si0, si1, "%4.0f", "sX1");

    // affichage par bloc SIMD: appel de la fonction SIMD
    display_vf32vector(vX1, vi0, vi1, "%4.0f", "vX1"); puts("");

    // affichage classique sur une ligne: appel de la fonction scalaire
    display_f32vector((float32*) vX2, si0, si1, "%4.0f", "sX2");

    // affichage par bloc SIMD: appel de la fonction SIMD
    display_vf32vector(vX2, vi0, vi1, "%4.0f", "vX2"); puts("");

    // ------------ //
    // -- calcul -- //
    // ------------ //

    add_vf32vector(vX1, vX2, vi0, vi1, vY);
    d = dot_vf32vector(vX1, vX2, vi0, vi1);

    // affichage classique sur une ligne: appel de la fonction scalaire
    display_f32vector((float32*) vY, si0, si1, "%4.0f", "sY");

    // affichage par bloc SIMD: appel de la fonction SIMD
    display_vf32vector(vY, vi0, vi1, "%4.0f", "vY"); puts("");

    display_vfloat32(d, "%6.0f ", "dot"); puts("");

    // ---------- //
    // -- free -- //
    // ---------- //

    free_vf32vector(vX1, vi0, vi1);
    free_vf32vector(vX2, vi0, vi1);
    free_vf32vector(vY,  vi0, vi1);
}
/* ------------------------ */
void test_sum_vf32vector(void)
/* ------------------------ */
{
    int n = 4*4;
    int card; // cardinal of vector type

    int si0, si1; // scalar indices
    int vi0, vi1; // vector indices
    int mi0, mi1; // memory (bounded) indices

    vfloat32 *vX, *vY3, *vY5;

    puts("--------------------------");
    puts("-- test_sum_vf32vector ---");
    puts("--------------------------");

    // ------------------------- //
    // -- calculs des indices -- //
    // ------------------------- //

    card = card_vfloat32();

    si0 = 0;
    si1 = n-1;
    s2v1D(si0, si1, card, &vi0, &vi1);
    v2m1D(vi0, vi1, card, &mi0, &mi1);
    
    // ------------------------------------------- //
    // -- allocation des tableaux 1D vectoriels -- //
    // ------------------------------------------- //

    vX  = vf32vector(vi0, vi1);
    vY3 = vf32vector(vi0, vi1);
    vY5 = vf32vector(vi0, vi1);

    // ---------- //
    // -- init -- //
    // ---------- //

    init_vf32vector_param(vX, vi0, vi1, 1, 1);
    zero_vf32vector(vY3, vi0, vi1);
    zero_vf32vector(vY5, vi0, vi1);

    // --------------- //
    // -- affichage -- //
    // --------------- //

    // affichage classique sur une ligne: appel de la fonction scalaire
    display_f32vector((float32*) vX, si0, si1, "%4.0f", "sX1");

    // affichage par bloc SIMD: appel de la fonction SIMD
    //display_vf32vector(vX, vi0, vi1, "%4.0f", "vX"); puts("");

    // ------------ //
    // -- calcul -- //
    // ------------ //

    sum3_vf32vector(vX, vi0, vi1, vY3);
    sum5_vf32vector(vX, vi0, vi1, vY5);

    // affichage classique sur une ligne: appel de la fonction scalaire
    display_f32vector((float32*) vY3, si0, si1, "%4.0f", "sY3");

    // affichage par bloc SIMD: appel de la fonction SIMD
    //display_vf32vector(vY3, vi0, vi1, "%4.0f", "vY3"); puts("");

    // affichage classique sur une ligne: appel de la fonction scalaire
    display_f32vector((float32*) vY5, si0, si1, "%4.0f", "sY5");

    // affichage par bloc SIMD: appel de la fonction SIMD
    //display_vf32vector(vY5, vi0, vi1, "%4.0f", "vY5"); puts("");

    // ---------- //
    // -- free -- //
    // ---------- //

    free_vf32vector(vX,  vi0, vi1);
    free_vf32vector(vY3, vi0, vi1);
    free_vf32vector(vY5, vi0, vi1);
}
/* ------------------------ */
void test_min_vf32vector(void)
/* ------------------------ */
{
    int n = 4*4;
    int card; // cardinal of vector type

    int si0, si1; // scalar indices
    int vi0, vi1; // vector indices
    int mi0, mi1; // memory (bounded) indices

    vfloat32 *vX, *vY3, *vY5;

    puts("--------------------------");
    puts("-- test_min_vf32vector ---");
    puts("--------------------------");

    // ------------------------- //
    // -- calculs des indices -- //
    // ------------------------- //

    card = card_vfloat32();

    si0 = 0;
    si1 = n-1;
    s2v1D(si0, si1, card, &vi0, &vi1);
    v2m1D(vi0, vi1, card, &mi0, &mi1);
    
    // ------------------------------------------- //
    // -- allocation des tableaux 1D vectoriels -- //
    // ------------------------------------------- //

    vX  = vf32vector(vi0, vi1);
    vY3 = vf32vector(vi0, vi1);
    vY5 = vf32vector(vi0, vi1);

    // ---------- //
    // -- init -- //
    // ---------- //

    init_vf32vector_param(vX, vi0, vi1, 1, 2);
    rand_f32vector((float32*) vX, si0, si1); // generateur de nombres aleatoires (congruence lineaire)
    zero_vf32vector(vY3, vi0, vi1);
    zero_vf32vector(vY5, vi0, vi1);

    // --------------- //
    // -- affichage -- //
    // --------------- //

    // affichage classique sur une ligne: appel de la fonction scalaire
    display_f32vector((float32*) vX, si0, si1, "%4.0f", "sX1");

    // affichage par bloc SIMD: appel de la fonction SIMD
    //display_vf32vector(vX, vi0, vi1, "%4.0f", "vX"); puts("");

    // ------------ //
    // -- calcul -- //
    // ------------ //

    min3_vf32vector(vX, vi0, vi1, vY3);
    min5_vf32vector(vX, vi0, vi1, vY5);

    // affichage classique sur une ligne: appel de la fonction scalaire
    display_f32vector((float32*) vY3, si0, si1, "%4.0f", "sY3");
    display_f32vector((float32*) vY5, si0, si1, "%4.0f", "sY5");

    // ---------- //
    // -- free -- //
    // ---------- //

    free_vf32vector(vX,  vi0, vi1);
    free_vf32vector(vY3, vi0, vi1);
    free_vf32vector(vY5, vi0, vi1);
}
// ----------------------------
void test_cond_vf32vector(void)
// ----------------------------
{
    int b = 1;
    int n;
    int card; // cardinal of vector type
    
    int si0, si1; // scalar indices
    int vi0, vi1; // vector indices
    int mi0, mi1; // memory (bounded) indices
    
    int si0b, si1b; // scalar indices with border
    int vi0b, vi1b; // vector indices with border
    int mi0b, mi1b; // memory (bounded) indices  with border
    
    
    vfloat32 *vX, *vY;
    vfloat32 d;
    
    char* format = "%6.2f ";
    
    // chronometrie
    int iter, niter = 4;
    int run, nrun = 5;
    double t0, t1, dt, tmin, t;
    double cycles;
    
    puts("====================");
    puts("=== test 1D Cond ===");
    puts("====================");
    
    // ------------------------- //
    // -- calculs des indices -- //
    // ------------------------- //
    
    n=16;
    
    printf("n = %d\n", n);
    
    card = card_vfloat32();
    
    si0 = 0;
    si1 = n-1;
    
    s2v1D(si0, si1, card, &vi0, &vi1);
    v2m1D(vi0, vi1, card, &mi0, &mi1);
    
    si0b = si0-b;
    si1b = si1+b;
    
    s2v1D(si0b, si1b, card, &vi0b, &vi1b);
    v2m1D(vi0b, vi1b, card, &mi0b, &mi1b);
    
    // ------------------------------------------- //
    // -- allocation des tableaux 1D vectoriels -- //
    // ------------------------------------------- //
    
    vX = vf32vector (vi0b, vi1b);   
    vY  = vf32vector(vi0,  vi1);
    
    // ---------- //
    // -- init -- //
    // ---------- //
    
    zero_vf32vector(vX, vi0b, vi1b);
    zero_vf32vector(vY, vi0,  vi1);
    rand_f32vector((float32*)vX, 0, n-1);
    
    // --------------- //
    // -- affichage -- //
    // --------------- //
    
    // affichage classique sur une ligne: appel de la fonction scalaire
    display_f32vector((float32*) vX, si0, si1, "%6.0f ", "sX1");
    
    // affichage par bloc SIMD: appel de la fonction SIMD
    display_vf32vector(vX, vi0, vi1, "%6.0f ", "vX1");
    puts("");
    
    puts("---------------------");
    puts("--- addition cond ---");
    puts("---------------------");
    
    positive_add3_vf32vector(vX, n/card, vY);
    // affichage classique sur une ligne: appel de la fonction scalaire
    display_f32vector((float32*) vY, si0, si1, "%6.1f", "sY");
    puts("");
    zero_vf32vector(vY, vi0,  vi1);
    
    puts("--------------------");
    puts("--- average cond ---");
    puts("--------------------");
    
    positive_avg3_vf32vector(vX, n/card, vY);
    display_f32vector((float32*) vY, si0, si1, "%6.1f", "sY");
    
    // ---------- //
    // -- free -- //
    // ---------- //
    
    free_vf32vector(vX, vi0b, vi1b);    
    free_vf32vector(vY,  vi0, vi1);
}
