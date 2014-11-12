/* ---------------------- */
/* --- morphoNR_SSE.c --- */
/* ---------------------- */

/*
 * Copyright (c) 2011 Lionel Lacassagne, all rights reserved
 * University Paris Sud 11
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "vdef.h"
#include "vnrutil.h"
#include "mutil.h"
#include "morphoNR_SSE.h"

// definir vec_left1 et vec_right1 ici

// A COMPLETER
#define vec_left1(v0, v1)  v0
#define vec_right1(v1, v2) v2
// -------------------------------------------------------------------------------------------
void binary_erosion_kernel3_vui8matrix(vuint8 **X, int i0, int i1, int j0, int j1, vuint8 **Y)
// -------------------------------------------------------------------------------------------
{
    // les matrices X et Y sont deja allouees
    // X possede des bords
    
    // A COMPLETER

}
// --------------------------------------------------------------------------------------------
void binary_dilation_kernel3_vui8matrix(vuint8 **X, int i0, int i1, int j0, int j1, vuint8 **Y)
// --------------------------------------------------------------------------------------------
{
    // les matrices X et Y sont deja allouees
    // X possede des bords
    
    // A COMPLETER

}
// ------------------------------------------------------------------------------------
void erosion_kernel3_vui8matrix(vuint8 **X, int i0, int i1, int j0, int j1, vuint8 **Y)
// ------------------------------------------------------------------------------------
{
    // les matrices X et Y sont deja allouees
    // X possede des bords
    
    // A COMPLETER

}
// -------------------------------------------------------------------------------------
void dilation_kernel3_vui8matrix(vuint8 **X, int i0, int i1, int j0, int j1, vuint8 **Y)
// -------------------------------------------------------------------------------------
{
    // les matrices X et Y sont deja allouees
    // X possede des bords

    // A COMPLETER

}
// ----------------------------------------------------------------
void extend1_vui8matrix(vuint8 **X, int i0, int i1, int j0, int j1)
// ----------------------------------------------------------------
{
    int i, j;
    int border = 1;
    
    // bord haut
    for(i=i0-border; i<=i0-1; i++) {
        for(j=j0; j<=j1; j++) {
            X[i][j] = X[i0][j];
        }
    }
    
    // bord bas
    for(i=i1+1; i<=i1+border; i++) {
        for(j=j0; j<=j1; j++) {
            X[i][j] = X[i1][j];
        }
    }
    
    // bord gauche et droit
    for(i=i0-border; i<=i1+border; i++) {
        
        for(j=j0-border; j<=j0-1; j++) {
            X[i][j] = X[i][j0];
        }
        for(j=j1+1; j<=j1+border; j++) {
            X[i][j] = X[i][j1];
        }
    }
}
// ------------------------------------------------------------------------------------
void binary_erosion3_vui8matrix(vuint8 **X, int i0, int i1, int j0, int j1, vuint8 **Y)
// ------------------------------------------------------------------------------------
{
    // X should be in [0,1]
    int radius = 1;
    vuint8 **T;
    
    T = vui8matrix(i0-radius, i1+radius, j0-radius, j1+radius); 
    zero_vui8matrix(T, i0-radius, i1+radius, j0-radius, j1+radius);
    
    dup_vui8matrix(X, i0, i1, j0, j1, T);
    extend1_vui8matrix(T, i0, i1, j0, j1);
    
    binary_erosion_kernel3_vui8matrix(T, i0, i1, j0, j1, Y);
    
    free_vui8matrix(T, i0-radius, i1+radius, j0-radius, j1+radius); 
}
// -------------------------------------------------------------------------------------
void binary_dilation3_vui8matrix(vuint8 **X, int i0, int i1, int j0, int j1, vuint8 **Y)
// -------------------------------------------------------------------------------------
{
    // X should be in [0,1]
    int radius = 1;
    vuint8 **T;
    
    T = vui8matrix(i0-radius, i1+radius, j0-radius, j1+radius); 
    zero_vui8matrix(T, i0-radius, i1+radius, j0-radius, j1+radius);
    
    dup_vui8matrix(X, i0, i1, j0, j1, T);
    extend1_vui8matrix(T, i0, i1, j0, j1);
    
    binary_dilation_kernel3_vui8matrix(T, i0, i1, j0, j1, Y);
    
    free_vui8matrix(T, i0-radius, i1+radius, j0-radius, j1+radius); 
}
// -----------------------------------------------------------------------------------------------
void binary_erosion_vui8matrix(vuint8 **X, int i0, int i1, int j0, int j1, int radius, vuint8 **Y)
// -----------------------------------------------------------------------------------------------
{
    int r;
    
    for(r=1; r<=radius; r++) {
        binary_erosion3_vui8matrix(X, i0, i1, j0, j1, Y);
        dup_vui8matrix(Y, i0, i1, j0, j1, X);
    }
}
// ------------------------------------------------------------------------------------------------
void binary_dilation_vui8matrix(vuint8 **X, int i0, int i1, int j0, int j1, int radius, vuint8 **Y)
// ------------------------------------------------------------------------------------------------
{
    int r;
    
    for(r=1; r<=radius; r++) {
        binary_dilation3_vui8matrix(X, i0, i1, j0, j1, Y);
        dup_vui8matrix(Y, i0, i1, j0, j1, X);
    }
}
// ------------------------------------------------------------------------------------------------
void binary_closing_vui8matrix (vuint8 **X, int i0, int i1, int j0, int j1, int radius, vuint8 **Y)
// ------------------------------------------------------------------------------------------------
{
    vuint8 **T = NULL;
    T = vui8matrix(i0, i1, j0, j1); 
    binary_dilation_vui8matrix(X, i0, i1, j0, j1, radius, T);
    binary_erosion_vui8matrix (T, i0, i1, j0, j1, radius, Y);
    free_vui8matrix(T, i0, i1, j0, j1); 
}
// ------------------------------------------------------------------------------------------------
void binary_opening_vui8matrix (vuint8 **X, int i0, int i1, int j0, int j1, int radius, vuint8 **Y)
// ------------------------------------------------------------------------------------------------
{
    vuint8 **T = NULL;
    T = vui8matrix(i0, i1, j0, j1); 
    binary_erosion_vui8matrix (T, i0, i1, j0, j1, radius, Y);
    binary_dilation_vui8matrix(X, i0, i1, j0, j1, radius, T);
    free_vui8matrix(T, i0, i1, j0, j1); 
}
// -----------------------------------------------------------------------------
void erosion3_vui8matrix(vuint8 **X, int i0, int i1, int j0, int j1, vuint8 **Y)
// -----------------------------------------------------------------------------
{
    // X should be in [0,1]
    int radius = 1;
    vuint8 **T;
    
    T = vui8matrix(i0-radius, i1+radius, j0-radius, j1+radius); 
    zero_vui8matrix(T, i0-radius, i1+radius, j0-radius, j1+radius);
    
    dup_vui8matrix(X, i0, i1, j0, j1, T);
    extend1_vui8matrix(T, i0, i1, j0, j1);
    
    erosion_kernel3_vui8matrix(T, i0, i1, j0, j1, Y);
    
    free_vui8matrix(T, i0-radius, i1+radius, j0-radius, j1+radius); 
}
// ------------------------------------------------------------------------------
void dilation3_vui8matrix(vuint8 **X, int i0, int i1, int j0, int j1, vuint8 **Y)
// ------------------------------------------------------------------------------
{
    // X should be in [0,1]
    int radius = 1;
    vuint8 **T;
    
    T = vui8matrix(i0-radius, i1+radius, j0-radius, j1+radius); 
    zero_vui8matrix(T, i0-radius, i1+radius, j0-radius, j1+radius);
    
    dup_vui8matrix(X, i0, i1, j0, j1, T);
    extend1_vui8matrix(T, i0, i1, j0, j1);
    
    dilation_kernel3_vui8matrix(T, i0, i1, j0, j1, Y);
    
    free_vui8matrix(T, i0-radius, i1+radius, j0-radius, j1+radius); 
}
// ----------------------------------------------------------------------------------------
void erosion_vui8matrix(vuint8 **X, int i0, int i1, int j0, int j1, int radius, vuint8 **Y)
// ----------------------------------------------------------------------------------------
{
    int r;
    vuint8 **T = NULL;
    T = vui8matrix(i0, i1, j0, j1); 
    
    for(r=1; r<=radius; r++) {
        erosion3_vui8matrix(X, i0, i1, j0, j1, Y);
        dup_vui8matrix(T, i0, i1, j0, j1, X);
    }
    dup_vui8matrix(T, i0, i1, j0, j1, Y);
    
    free_vui8matrix(T, i0, i1, j0, j1); 
}
// -----------------------------------------------------------------------------------------
void dilation_vui8matrix(vuint8 **X, int i0, int i1, int j0, int j1, int radius, vuint8 **Y)
// -----------------------------------------------------------------------------------------
{
    int r;
    vuint8 **T = NULL;
    T = vui8matrix(i0, i1, j0, j1); 

    for(r=1; r<=radius; r++) {
        dilation3_vui8matrix(X, i0, i1, j0, j1, T);
        dup_vui8matrix(T, i0, i1, j0, j1, X);
    }
    dup_vui8matrix(T, i0, i1, j0, j1, Y);

    free_vui8matrix(T, i0, i1, j0, j1); 
}
// ----------------------------------------------------------------------------------------
void closing_vui8matrix(vuint8 **X, int i0, int i1, int j0, int j1, int radius, vuint8 **Y)
// ----------------------------------------------------------------------------------------
{
    vuint8 **T = NULL;
    T = vui8matrix(i0, i1, j0, j1); 
    dilation_vui8matrix(X, i0, i1, j0, j1, radius, T);
    erosion_vui8matrix (T, i0, i1, j0, j1, radius, Y);
    free_vui8matrix(T, i0, i1, j0, j1); 
}
// ----------------------------------------------------------------------------------------
void opening_vui8matrix(vuint8 **X, int i0, int i1, int j0, int j1, int radius, vuint8 **Y)
// ----------------------------------------------------------------------------------------
{
    vuint8 **T = NULL;
    T = vui8matrix(i0, i1, j0, j1); 
    erosion_vui8matrix (X, i0, i1, j0, j1, radius, T);
    dilation_vui8matrix(T, i0, i1, j0, j1, radius, Y);
    free_vui8matrix(T, i0, i1, j0, j1); 
}
// ---------------------------------------------------------------------------------------------------------------------------
void alternate_sequential_filter_binary_opening_vui8matrix(vuint8 **X, int i0, int i1, int j0, int j1, int radius, vuint8 **Y)
// ---------------------------------------------------------------------------------------------------------------------------
{
    int r;
    vuint8 **src = NULL;
    vuint8 **dst = NULL;
    
    src = vui8matrix(i0, i1, j0, j1); 
    dst = vui8matrix(i0, i1, j0, j1); 
    
    dup_vui8matrix(X, i0, i1, j0, j1, src);
    
    for(r=1; r<=radius; r++) {
        binary_opening_vui8matrix(src, i0, i1, j0, j1, r, dst);
        dup_vui8matrix(dst, i0, i1, j0, j1, src);
    }
    
    dup_vui8matrix(dst, i0, i1, j0, j1, Y);
    
    free_vui8matrix(src, i0, i1, j0, j1); 
    free_vui8matrix(dst, i0, i1, j0, j1); 
}
// ---------------------------------------------------------------------------------------------------------------------------
void alternate_sequential_filter_binary_closing_vui8matrix(vuint8 **X, int i0, int i1, int j0, int j1, int radius, vuint8 **Y)
// ---------------------------------------------------------------------------------------------------------------------------
{
    int r;
    vuint8 **src = NULL;
    vuint8 **dst = NULL;
    
    src = vui8matrix(i0, i1, j0, j1); 
    dst = vui8matrix(i0, i1, j0, j1); 
    
    dup_vui8matrix(X, i0, i1, j0, j1, src);
    
    for(r=1; r<=radius; r++) {
        binary_closing_vui8matrix(src, i0, i1, j0, j1, r, dst);
        dup_vui8matrix(dst, i0, i1, j0, j1, src);
    }
    
    dup_vui8matrix(dst, i0, i1, j0, j1, Y);
    
    free_vui8matrix(src, i0, i1, j0, j1); 
    free_vui8matrix(dst, i0, i1, j0, j1); 
}
// -------------------------------------------------------------------------------------------------------------------
void alternate_sequential_filter_opening_vui8matrix(vuint8 **X, int i0, int i1, int j0, int j1, int radius, vuint8 **Y)
// -------------------------------------------------------------------------------------------------------------------
{
    int r;
    vuint8 **src = NULL;
    vuint8 **dst = NULL;
    
    src = vui8matrix(i0, i1, j0, j1); 
    dst = vui8matrix(i0, i1, j0, j1); 
    
    dup_vui8matrix(X, i0, i1, j0, j1, src);
    
    for(r=1; r<=radius; r++) {
        opening_vui8matrix(src, i0, i1, j0, j1, r, dst);
        dup_vui8matrix(dst, i0, i1, j0, j1, src);
    }
    dup_vui8matrix(dst, i0, i1, j0, j1, Y);
    
    free_vui8matrix(src, i0, i1, j0, j1); 
    free_vui8matrix(dst, i0, i1, j0, j1); 
}
// -------------------------------------------------------------------------------------------------------------------
void alternate_sequential_filter_closing_vui8matrix(vuint8 **X, int i0, int i1, int j0, int j1, int radius, vuint8 **Y)
// -------------------------------------------------------------------------------------------------------------------
{
    int r;
    vuint8 **src = NULL;
    vuint8 **dst = NULL;
    
    src = vui8matrix(i0, i1, j0, j1); 
    dst = vui8matrix(i0, i1, j0, j1); 
    
    dup_vui8matrix(X, i0, i1, j0, j1, src);
    
    for(r=1; r<=radius; r++) {
        closing_vui8matrix(src, i0, i1, j0, j1, r, dst);
        dup_vui8matrix(dst, i0, i1, j0, j1, src);
    }
    
    dup_vui8matrix(dst, i0, i1, j0, j1, Y);
    
    free_vui8matrix(src, i0, i1, j0, j1); 
    free_vui8matrix(dst, i0, i1, j0, j1); 
}
