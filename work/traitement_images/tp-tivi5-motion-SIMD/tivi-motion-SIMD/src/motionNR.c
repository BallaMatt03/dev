/* ------------------ */
/* --- motionNR.c --- */
/* ------------------ */

/*
 * Copyright (c) 2011-2012 Lionel Lacassagne, all rights reserved
 * University Paris Sud 11
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "def.h"
#include "nrutil.h"
#include "mutil.h"
#include "morphoNR.h"

// ---------------------------------------------------------------------------------------------------------
void FrameDifference_FirstStep(uint8 **I0, uint8 **I1, int i0, int i1, int j0, int j1, uint8 **D, uint8 **S)
// ---------------------------------------------------------------------------------------------------------
{
    int i, j;
    uint8 x0;
    
    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {
            
            x0 = I0[i][j];
            
            I1[i][j] =x0;
            D[i][j]  = 0;
            S[i][j]  = 0;
        }
    }
}
// ----------------------------------------------------------------------------------------------------------------------
void FrameDifference_1Step(uint8 **I0, uint8 **I1, int i0, int i1, int j0, int j1, uint8 **D, uint8 **S, uint8 threshold)
// ----------------------------------------------------------------------------------------------------------------------
{
    int i, j;
    uint8 x0, x1, d, e;
    
    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {
            x0 = I0[i][j];
            x1 = I1[i][j];
            
            // A COMPLETER
            d = abs(x1-x0);
            if(d < threshold){
                e=1;
            }
            else{
                e=0;
            }
            
            D[i][j] = d;
            S[i][j] = e;
        }
    }
}
// -------------------------------------------------------------------------------------------------------------
void SigmaDelta_FirstStep(uint8 **I, int i0, int i1, int j0, int j1, uint8 **M, uint8 **O, uint8 **V, uint8 **E)
// -------------------------------------------------------------------------------------------------------------
{
    int i, j;
    
    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {
            M[i][j] = I[i][j];
            O[i][j] = 0;
            V[i][j] = 2;
            E[i][j] = 0;
        }
    }
}
// ----------------------------------------------------------------------------------------------------------------
void SigmaDelta_1Step(uint8 **I, int i0, int i1, int j0, int j1, uint8 **M, uint8 **O, uint8 **V, uint8 **E, int k)
// ----------------------------------------------------------------------------------------------------------------
{
    int i, j;
    uint32 x, m, d, v, kd, e;
    
    
    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {
            
            x = I[i][j];
            m = M[i][j];
            v = V[i][j];
            
            // A COMPLETER
            
            if(m < x)
            {
                m = m + 1;
            }
            else if(m > x)
            {
                m = m - 1;
            }
            
            d = abs(m - x);

            if(v < k * d)
            {
                v = v + 1;
            }
            else if(v > k * d)
            {
                v = v - 1;
            }

            if(d < v)
            {
                e = 0;
            }
            else
            {
                e = 1;
            }
            
            M[i][j] = m;
            O[i][j] = d;
            V[i][j] = v;
            E[i][j] = e;
        }
    }
}
