/* ------------------ */
/* --- motionNR.h --- */
/* ------------------ */

/*
 * Copyright (c) 2011-2012 Lionel Lacassagne, all rights reserved
 * University Paris Sud 11
 */

#ifndef __MOTION_NR_H__
#define __MOTION_NR_H__

#ifdef __cplusplus
extern "C" {
#endif

// Frame Difference
void FrameDifference_FirstStep(uint8 **I0, uint8 **I1, int i0, int i1, int j0, int j1, uint8 **D, uint8 **S);
void FrameDifference_1Step(    uint8 **I0, uint8 **I1, int i0, int i1, int j0, int j1, uint8 **D, uint8 **S, uint8 threshold);

// Sigma-Delta
void SigmaDelta_FirstStep(uint8 **I, int i0, int i1, int j0, int j1, uint8 **M, uint8 **O, uint8 **V, uint8 **E);
void SigmaDelta_1Step(    uint8 **I, int i0, int i1, int j0, int j1, uint8 **M, uint8 **O, uint8 **V, uint8 **E, int k);

#ifdef __cplusplus
}
#endif

#endif // __MOTION_NR_H__
