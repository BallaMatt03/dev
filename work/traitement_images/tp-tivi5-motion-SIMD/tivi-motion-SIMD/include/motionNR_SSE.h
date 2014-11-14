/* ---------------------- */
/* --- motionNR_SSE.h --- */
/* ---------------------- */

/*
 * Copyright (c) 2011-2013 Lionel Lacassagne, all rights reserved
 * University Paris Sud 11
 */

#ifndef __MOTION_NR_SSE_H__
#define __MOTION_NR_SSE_H__

#ifdef __cplusplus
extern "C" {
#endif

void vec_diff(vuint8 x0, vuint8 x1, vuint8 *o);
void vec_cmp_threshold(vuint8 o_128, vuint8 threshold_128, vuint8 *e);
void vec_cmp_inc_dec(vuint8* m128, vuint8 x128);
void test_cmp_mul(vuint8* v128, vuint8 o128, vuint8 N);

// Frame Difference
void FrameDifference_FirstStep_SSE(vuint8 **I0, vuint8 **I1, vuint8 **D, vuint8 **S, uint8 threshold, int i0, int i1, int j0, int j1);
void FrameDifference_1Step_SSE    (vuint8 **I0, vuint8 **I1, vuint8 **D, vuint8 **S, uint8 threshold, int i0, int i1, int j0, int j1);

// Sigma-Delta
void SigmaDelta_FirstStep_SSE(vuint8 **I, vuint8 **M, vuint8 **O, vuint8 **V, vuint8 **E, int k, int i0, int i1, int j0, int j1);
void SigmaDelta_1Step_SSE    (vuint8 **I, vuint8 **M, vuint8 **O, vuint8 **V, vuint8 **E, int k, int i0, int i1, int j0, int j1);

// Pre et Post Processing
void PreProcessing_SSE(vuint8 **X, vuint8 **Y, int i0, int i1, int j0, int j1);
void PostProcessing_SSE(vuint8 **X, vuint8 **Y, int i0, int i1, int j0, int j1);

#ifdef __cplusplus
}
#endif

#endif // __MOTION_NR_SSE_H__
