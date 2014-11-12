/* ---------------------- */
/* --- motionNR_SSE.c --- */
/* ---------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "def.h"
#include "nrutil.h"
#include "timers_b.h"

#include "vdef.h"
#include "vnrutil.h"

#include "morphoNR_SSE.h"
#include "motionNR_SSE.h"

#ifdef OPENMP
#include <omp.h>
#endif
/*
#include <ia32intrin.h>

double dtime()
{
    return (double) _rdtsc();
}
*/
/* ------------------------------------------------------------------------- */
void vec_diff(vuint8 x0, vuint8 x1, vuint8 *o)
/* ------------------------------------------------------------------------- */
{           
    *o = _mm_sub_epi16(_mm_max_epi16(x0, x1), _mm_min_epi16(x0, x1));
}

//2.2
/* ------------------------------------------------------------------------- */
void vec_cmp_threshold(vuint8 o_128, uint8 threshold_128, vuint8 *e)
/* ------------------------------------------------------------------------- */
{
    *e = _mm_cmplt_epi8(threshold_128, o_128);
}

//3.1
/* ------------------------------------------------------------------------- */
void vec_cmp_inc_dec(vuint8* m128, vuint8 x128)
/* ------------------------------------------------------------------------- */
{
    vuint8 complt = _mm_cmplt_epi16(*m128, x128);
    vuint8 compgt = _mm_cmpgt_epi16(*m128, x128);
    
    inc = _mm_and_si128(complt, one);
    dec = _mm_and_si128(compgt, one);
    
    *m128 = _mm_add_si128(*m128, inc);
    *m128 = _mm_add_si128(*m128, dec);
}

//3.2
/* ------------------------------------------------------------------------- */
void test_cmp_mul(vuint8* v128, vuint8 o128, vuint8 N)
/* ------------------------------------------------------------------------- */
{
    vuint8 res, total = o128;
    
    switch (N) {
        case 2:
            total = _mm_adds_epi16(o128, o128);
            break;
        case 3:
            total = _mm_adds_epi16(o128, _mm_adds_epi16(o128, o128));
            break;
        case 4:
            res = _mm_adds_epi16(o128, o128);
            total = _mm_adds_epi16(res, res);
            break;
        case 5:
            res = _mm_adds_epi16(o128, o128);
            total = _mm_adds_epi16(res, _mm_adds_epi16(o128, res));
            break;    
    }
    
    vec_cmp_inc_dec(*v128, total);
}

//4.1
#define vec_left1(v0, v1)  _mm_shuffle_epi8(v0, _mm_shuffle_epi8(v1, v0, _MM_SHUFFLE(3,2,1,0)), _MM_SHUFFLE(0,3,2,1))

//4.2
#define vec_right1(v1, v2) _mm_shuffle_epi8(_mm_shuffle_epi8(v1, v2, _MM_SHUFFLE(1,0,3,2)), v2, _MM_SHUFFLE(2,1,2,1))

// ---------------------------------------------------------------------------
void PreProcessing_SSE(vuint8 **X, vuint8 **Y, int i0, int i1, int j0, int j1)
// ---------------------------------------------------------------------------
{
    // simple copie pour assurer le fonctionnement du programme principal
    dup_vui8matrix(X, i0, i1, j0, j1, Y);
    // A COMPLETER

}
// ----------------------------------------------------------------------------
void PostProcessing_SSE(vuint8 **X, vuint8 **Y, int i0, int i1, int j0, int j1)
// ----------------------------------------------------------------------------
{
    vuint8 **T;
    T = NULL;
    
    // simple copie pour assurer le fonctionnement du programme principal
    dup_vui8matrix(X, i0, i1, j0, j1, Y);
    // A COMPLETER

}
// ----------------------------------------------------------------------------------------------------------------------------------
void FrameDifference_FirstStep_SSE(vuint8 **I0, vuint8 **I1, vuint8 **D, vuint8 **S, uint8 threshold, int i0, int i1, int j0, int j1)
// ----------------------------------------------------------------------------------------------------------------------------------
{
    int i,j;   
    vuint8 zero;
    
    zero = _mm_set1_epi8(0);
    
    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {
            _mm_store_si128(&D[i][j], zero);
            _mm_store_si128(&S[i][j], zero);
        }
    }
}
// ------------------------------------------------------------------------------------------------------------------------------
void FrameDifference_1Step_SSE(vuint8 **I0, vuint8 **I1, vuint8 **D, vuint8 **S, uint8 threshold, int i0, int i1, int j0, int j1)
// ------------------------------------------------------------------------------------------------------------------------------
{
    int i,j;
    
    vuint8 x0, x1, o, e;
    vuint8 vmax, vmin, gt;
    vuint8 vthreshold;
    vuint8 k128;
    vuint8 one;
    
    vuint8 o_128, vthreshold_128;
   
    vthreshold     = _mm_set1_epi8(threshold-1);
    k128           = _mm_set1_epi8(128);
    one            = _mm_set1_epi8(1);
    vthreshold_128 = _mm_sub_epi8(vthreshold, k128);

#ifdef OPENMP
#pragma omp parallel for private(j)
#endif
    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {
            
            // load
            x0 = _mm_load_si128(&I0[i][j]);
            x1 = _mm_load_si128(&I1[i][j]);
            
            // A COMPLETER
            vec_diff(x0, x1, o);
            //vec_cmp_threshold(x0, x1, &e);//, vthreshold);

            // store
            _mm_store_si128(&D[i][j], o);
            _mm_store_si128(&S[i][j], e);
        }
    }
}
// ------------------------------------------------------------------------------------------------------------------------------
void SigmaDelta_FirstStep_SSE(vuint8 **I, vuint8 **M, vuint8 **O, vuint8 **V, vuint8 **E, int k, int i0, int i1, int j0, int j1)
// ------------------------------------------------------------------------------------------------------------------------------
{
    int i,j;
    
    vuint8 x;
    vuint8 zero;
    vuint8 one;
    
    zero = _mm_set1_epi8(0);
    one  = _mm_set1_epi8(1);

    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {
            
            // load
            x = _mm_load_si128(&I[i][j]);
                       
            // store
            _mm_store_si128(&M[i][j], x);
            _mm_store_si128(&O[i][j], zero);
            _mm_store_si128(&V[i][j], one);
            _mm_store_si128(&E[i][j], zero);
        }
    }
}
// -------------------------------------------------------------------------------------------------------------------------
void SigmaDelta_1Step_SSE(vuint8 **I, vuint8 **M, vuint8 **O, vuint8 **V, vuint8 **E, int k, int i0, int i1, int j0, int j1)
// -------------------------------------------------------------------------------------------------------------------------
{
    /*#ifdef OPENMP
    //#pragma omp parallel default(none) shared(I, M, O, V, E, i0,i1,j0,j1,k)
    #pragma omp parallel shared(I, M, O, V, E, i0,i1,j0,j1,k)
	{
    #endif*/


    int i,j;
    
    vuint8 x, m, o, v, e;
    vuint8 x128, m128, o128, v128, k128, ko128;
    vuint8 zero;
    vuint8 one;
    vuint8 lt, gt;
    vuint8 ko;
    vuint8 inc, z; // zero flag
  
    zero = _mm_set1_epi8(0);
    one  = _mm_set1_epi8(1);

    k128 = _mm_set1_epi8(128);

#ifdef OPENMP
//#pragma omp parallel for private(j)
    #pragma omp parallel for private(i, j, x, m, o, v, e, x128, m128, o128, v128, k128, ko128, zero, one, lt, gt, ko, inc, z)
#endif
    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {
            
            // load
            x = _mm_load_si128(&I[i][j]);
            m = _mm_load_si128(&M[i][j]);
            v = _mm_load_si128(&V[i][j]);

            
            // A COMPLETER
                                   
            // store
            _mm_store_si128(&M[i][j], m);
            _mm_store_si128(&O[i][j], o);
            _mm_store_si128(&V[i][j], v);
            _mm_store_si128(&E[i][j], e);

        }
    }

    //#ifdef OPENMP
	//}
    //#endif
}
