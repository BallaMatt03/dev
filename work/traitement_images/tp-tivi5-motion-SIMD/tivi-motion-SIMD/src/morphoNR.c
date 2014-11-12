/* ------------------ */
/* --- morphoNR.c --- */
/* ------------------ */

/*
 * Copyright (c) 2011 Lionel Lacassagne, all rights reserved
 * University Paris Sud 11
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "def.h"
#include "nrutil.h"
#include "mutil.h"
#include "morphoNR.h"

/* ----------------------------------------------------------- */
uint8** alloc_structuring_element(int i0, int i1, int j0, int j1)
/* ----------------------------------------------------------- */
{
    uint8 **SE;
    SE = ui8matrix(i0, i1, j0, j1);
    return SE;
}
/* ------------------------------------------------------------------- */
void free_structuring_element(uint8 **SE, int i0, int i1, int j0, int j1)
/* ------------------------------------------------------------------- */
{
    free_ui8matrix(SE, i0, i1, j0, j1);
}
/* ------------------------------------------------------------------------------------------------ */
void display_structuring_element(uint8 **SE, int i0, int i1, int j0, int j1, char *format, char *name)
/* ------------------------------------------------------------------------------------------------ */
{
    display_ui8matrix(SE, i0, i1, j0, j1, format, name);
}
/* ----------------------------------------------------------------------------------------- */
void binary_erosion_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y)
/* ----------------------------------------------------------------------------------------- */
{
    // X should be in [0,1]
    int i, j;
    int ii, jj;
    
    uint8 **T;
    uint8 y; 
    
    T = ui8matrix(i0-radius, i1+radius, j0-radius, j1+radius); 
    zero_ui8matrix(T, i0-radius, i1+radius, j0-radius, j1+radius);
    dup_ui8matrix(X, i0, i1, j0, j1, T);
    extend_ui8matrix(T, i0, i1, j0, j1, radius);
    
    // A COMPLETER
    
    free_ui8matrix(T, i0-radius, i1+radius, j0-radius, j1+radius); 
}
/* ----------------------------------------------------------------------------------------- */
void binary_dilation_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y)
/* ----------------------------------------------------------------------------------------- */
{
    // X should be in [0,1]
    int i, j;
    int ii, jj;
    
    uint8 **T;
    uint8 y; 
    
    T = ui8matrix(i0-radius, i1+radius, j0-radius, j1+radius); 
    zero_ui8matrix(T, i0-radius, i1+radius, j0-radius, j1+radius);
    dup_ui8matrix(X, i0, i1, j0, j1, T);
    extend_ui8matrix(T, i0, i1, j0, j1, radius);
    
    // A COMPLETER

    free_ui8matrix(T, i0-radius, i1+radius, j0-radius, j1+radius); 
}
/* ------------------------------------------------------------------------------------------ */
void binary_closing_ui8matrix (uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y)
/* ------------------------------------------------------------------------------------------ */
{
    // X is copied into a tmp T => Y=f(Y) is possible
    binary_dilation_ui8matrix(X, i0, i1, j0, j1, radius, Y);
    binary_erosion_ui8matrix (Y, i0, i1, j0, j1, radius, Y);
}
/* ------------------------------------------------------------------------------------------ */
void binary_opening_ui8matrix (uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y)
/* ------------------------------------------------------------------------------------------ */
{
    // X is copied into a tmp T => Y=f(Y) is possible
    binary_erosion_ui8matrix (X, i0, i1, j0, j1, radius, Y);
    binary_dilation_ui8matrix(Y, i0, i1, j0, j1, radius, Y);
}
/* ---------------------------------------------------------------------------------- */
void erosion_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y)
/* ---------------------------------------------------------------------------------- */
{
    // X should be in [0,1]
    int i, j;
    int ii, jj;
    
    uint8 **T;
    uint8 y; 
    
    T = ui8matrix(i0-radius, i1+radius, j0-radius, j1+radius); 
    zero_ui8matrix(T, i0-radius, i1+radius, j0-radius, j1+radius);
    dup_ui8matrix(X, i0, i1, j0, j1, T);
    extend_ui8matrix(T, i0, i1, j0, j1, radius);
    
    // A COMPLETER

    free_ui8matrix(T, i0-radius, i1+radius, j0-radius, j1+radius); 
}
/* ----------------------------------------------------------------------------------- */
void dilation_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y)
/* ----------------------------------------------------------------------------------- */
{
    // X should be in [0,1]
    int i, j;
    int ii, jj;
    
    uint8 **T;
    uint8 y; 
    
    T = ui8matrix(i0-radius, i1+radius, j0-radius, j1+radius); 
    zero_ui8matrix(T, i0-radius, i1+radius, j0-radius, j1+radius);
    dup_ui8matrix(X, i0, i1, j0, j1, T);
    extend_ui8matrix(T, i0, i1, j0, j1, radius);
    
    // A COMPLETER

    free_ui8matrix(T, i0-radius, i1+radius, j0-radius, j1+radius); 
}
/* ---------------------------------------------------------------------------------- */
void closing_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y)
/* ---------------------------------------------------------------------------------- */
{
    // X is copied into a tmp T => Y=f(Y) is possible
    dilation_ui8matrix(X, i0, i1, j0, j1, radius, Y);
    erosion_ui8matrix (Y, i0, i1, j0, j1, radius, Y);
}
/* ---------------------------------------------------------------------------------- */
void opening_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y)
/* ---------------------------------------------------------------------------------- */
{
    // X is copied into a tmp T => Y=f(Y) is possible
    erosion_ui8matrix (X, i0, i1, j0, j1, radius, Y);
    dilation_ui8matrix(Y, i0, i1, j0, j1, radius, Y);
}
/* -------------------------------------------------------------------------------------------------------------- */
void alternate_sequential_filter_opening_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y)
/* -------------------------------------------------------------------------------------------------------------- */
{
    int r;
    
    for(r=1; r<=radius; r++) {
        if(r==1) {
            opening_ui8matrix(X, i0, i1, j0, j1, r, Y);
        } else {
            opening_ui8matrix(Y, i0, i1, j0, j1, r, Y);

        }
    }
}
/* -------------------------------------------------------------------------------------------------------------- */
void alternate_sequential_filter_closing_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y)
/* -------------------------------------------------------------------------------------------------------------- */
{
    int r;
    
    for(r=1; r<=radius; r++) {
        if(r==1) {
            closing_ui8matrix(X, i0, i1, j0, j1, r, Y);
        } else {
            closing_ui8matrix(Y, i0, i1, j0, j1, r, Y);
            
        }
    }
}