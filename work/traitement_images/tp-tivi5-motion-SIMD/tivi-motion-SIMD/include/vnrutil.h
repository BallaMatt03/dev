/* ------------------ */
/* --- vnrutil.h --- */
/* ------------------ */

/*
 * Copyright (c) 2004-2013 Lionel Lacassagne
 */

#ifndef __VNRUTIL_H__
#define __VNRUTIL_H__

#ifdef __cplusplus
#pragma message ("C++")
extern "C" {
#endif

#include <xmmintrin.h>
#include <emmintrin.h>
#include <mmintrin.h>
    
#include "def.h"
#include "vdef.h"
        
void vnrerror(char error_text[]);

/* =================================== */
/* === 2D Altivec ==================== */
/* =================================== */

/* ----------- */
/* -- alloc -- */
/* ----------- */

vuint8   **vui8matrix (int nrl, int nrh, int ncl, int nch);
vsint8   **vsi8matrix (int nrl, int nrh, int ncl, int nch);
vuint16  **vui16matrix(int nrl, int nrh, int ncl, int nch);
vsint16  **vsi16matrix(int nrl, int nrh, int ncl, int nch);
vuint32  **vui32matrix(int nrl, int nrh, int ncl, int nch);
vsint32  **vsi32matrix(int nrl, int nrh, int ncl, int nch);
vfloat    **vfmatrix (int nrl, int nrh, int ncl, int nch);
vfloat32 **vf32matrix(int nrl, int nrh, int ncl, int nch);
vfloat32 **vf32matrixL(int nrl, int nrh, int ncl, int nch);

/* ---------- */
/* -- free -- */
/* ---------- */

void free_vui8matrix (vuint8 **m, int nrl, int nrh, int ncl, int nch);
void free_vsi8matrix (vsint8 **m, int nrl, int nrh, int ncl, int nch);
void free_vui16matrix(vuint16 **m, int nrl, int nrh, int ncl, int nch);
void free_vsi16matrix(vsint16 **m, int nrl, int nrh, int ncl, int nch);
void free_vui32matrix(vuint32 **m, int nrl, int nrh, int ncl, int nch);
void free_vsi32matrix(vsint32 **m, int nrl, int nrh, int ncl, int nch);
void free_vfmatrix (vfloat **m, int nrl, int nrh, int ncl, int nch);
void free_vf32matrix(vfloat32 **m, int nrl, int nrh, int ncl, int nch);

/* ------------- */
/* -- wrapper -- */
/* ------------- */

vuint8   **vui8matrix_map (int nrl, int nrh, int ncl, int nch);
vsint8   **vsi8matrix_map (int nrl, int nrh, int ncl, int nch);
vuint16  **vui16matrix_map(int nrl, int nrh, int ncl, int nch);
vsint16  **vsi16matrix_map(int nrl, int nrh, int ncl, int nch);
vuint32  **vui32matrix_map(int nrl, int nrh, int ncl, int nch);
vsint32  **vsi32matrix_map(int nrl, int nrh, int ncl, int nch);
vfloat   **vfmatrix_map   (int nrl, int nrh, int ncl, int nch);
vfloat32 **vf32matrix_map (int nrl, int nrh, int ncl, int nch);

vuint8**    vui8matrix_map_1D_pitch(vuint8   **m, int nrl, int nrh, int ncl, int nch, void *data_1D, int pitch);
vsint8**    vsi8matrix_map_1D_pitch(vsint8   **m, int nrl, int nrh, int ncl, int nch, void *data_1D, int pitch);
vuint16**  vui16matrix_map_1D_pitch(vuint16  **m, int nrl, int nrh, int ncl, int nch, void *data_1D, int pitch);
vsint16**  vsi16matrix_map_1D_pitch(vsint16  **m, int nrl, int nrh, int ncl, int nch, void *data_1D, int pitch);
vuint32**  vui32matrix_map_1D_pitch(vuint32  **m, int nrl, int nrh, int ncl, int nch, void *data_1D, int pitch);
vsint32**  vsi32matrix_map_1D_pitch(vsint32  **m, int nrl, int nrh, int ncl, int nch, void *data_1D, int pitch);
vfloat**      vfmatrix_map_1D_pitch(vfloat   **m, int nrl, int nrh, int ncl, int nch, void *data_1D, int pitch);
vfloat32 ** vf32matrix_map_1D_pitch(vfloat32 **m, int nrl, int nrh, int ncl, int nch, void *data_1D, int pitch);

void free_vui8matrix_map (vuint8   **m, int nrl, int nrh, int ncl, int nch);
void free_vsi8matrix_map (vsint8   **m, int nrl, int nrh, int ncl, int nch);
void free_vui16matrix_map(vuint16  **m, int nrl, int nrh, int ncl, int nch);
void free_vsi16matrix_map(vsint16  **m, int nrl, int nrh, int ncl, int nch);
void free_vui32matrix_map(vuint32  **m, int nrl, int nrh, int ncl, int nch);
void free_vsi32matrix_map(vsint32  **m, int nrl, int nrh, int ncl, int nch);
void free_vfmatrix_map   (vfloat   **m, int nrl, int nrh, int ncl, int nch);
void ree_vf32matrix_map  (vfloat32 **m, int nrl, int nrh, int ncl, int nch);

/* -------------- */
/* --- resize --- */
/* -------------- */

void resize_vui8matrix(vuint8 **m, int i0, int i1, int j0, int j1);
void resize_vsi8matrix(vsint8 **m, int i0, int i1, int j0, int j1);
void resize_vui16matrix(vuint16 **m, int i0, int i1, int j0, int j1);
void resize_vsi16matrix(vsint16 **m, int i0, int i1, int j0, int j1);
void resize_vui32matrix(vuint32 **m, int i0, int i1, int j0, int j1);
void resize_vsi32matrix(vsint32 **m, int i0, int i1, int j0, int j1);
void resize_vf32matrix(vfloat32 **m, int i0, int i1, int j0, int j1);

/* ====================================== */
/* === misc function ==================== */
/* ====================================== */

void display_vui8matrix (vuint8   **vX, int i0, int i1, int j0, int j1, char *format, char *name);
void display_vui32matrix(vuint32  **vX, int i0, int i1, int j0, int j1, char *format, char *name);
void display_vf32matrix (vfloat32 **vX, int i0, int i1, int j0, int j1, char *format, char *name);

/* ----------- */
/* --- 0D  --- */
/* ----------- */

vuint8   init_vuint8  (uint8   x);
vuint16  init_vuint16 (uint16  x);
vsint16  init_vsint16 (sint16  x);
vuint32  init_vuint32 (uint32  x);
vsint32  init_vsint32 (sint32  x);
vfloat32 init_vfloat32(float32 x);

vuint8   init_vuint8_param  (uint8   x0, uint8   step);
vsint8   init_vsint8_param  (sint8   x0, sint8   step);
vuint16  init_vuint16_param (uint16  x0, uint16  step);
vsint16  init_vsint16_param (sint16  x0, sint16  step);
vuint32  init_vuint32_param (uint32  x0, uint32  step);
vsint32  init_vsint32_param (sint32  x0, sint32  step);
vfloat32 init_vfloat32_param(float32 x0, float32 step);

vuint8   init_vuint8_all   (uint8   x0, uint8   x1, uint8   x2, uint8   x3, uint8  x4, uint8  x5, uint8  x6, uint8  x7, uint8 x8, uint8 x9, uint8 x10, uint8 x11, uint8 x12, uint8 x13, uint8 x14, uint8 x15);
vsint8   init_vsint8_all   (sint8   x0, sint8   x1, sint8   x2, sint8   x3, sint8  x4, sint8  x5, sint8  x6, sint8  x7, sint8 x8, sint8 x9, sint8 x10, sint8 x11, sint8 x12, sint8 x13, sint8 x14, sint8 x15);
vuint16  init_vuint16_all  (uint16  x0, uint16  x1, uint16  x2, uint16  x3, uint16 x4, uint16 x5, uint16 x6, uint16 x7);
vsint16  init_vsint16_all  (sint16  x0, sint16  x1, sint16  x2, sint16  x3, sint16 x4, sint16 x5, sint16 x6, sint16 x7);
vuint32  init_vuint32_all  (uint32  x0, uint32  x1, uint32  x2, uint32  x3);
vsint32  init_vsint32_all  (sint32  x0, sint32  x1, sint32  x2, sint32  x3);
vfloat32 init_vfloat32_all (float32 x0, float32 x1, float32 x2, float32 x3);

/* ---------- */
/* --- 1D --- */
/* ---------- */

void zero_vsi8vector(vsint8 *m, int j0, int j1);
void zero_vui8vector(vuint8 *m, int j0, int j1);
void zero_vsi16vector(vsint16 *m, int j0, int j1);
void zero_vui16vector(vuint16 *m, int j0, int j1);
void zero_vsi32vector (vsint32 *m, int j0, int j1);
void zero_vui32vectorx(vuint32 *m, int j0, int j1);
void zero_vf32vector(vfloat32 *m, int j0, int j1);

void dup_vui8vector (vuint8   *X, int j0, int j1, vuint8   *Y);
void dup_vsi8vector (vsint8   *X, int j0, int j1, vsint8   *Y);
void dup_vui16vector(vuint16  *X, int j0, int j1, vuint16  *Y);
void dup_vsi16vector(vsint16  *X, int j0, int j1, vsint16  *Y);
void dup_vui32vector(vuint32  *X, int j0, int j1, vuint32  *Y);
void dup_vsi32vector(vsint32  *X, int j0, int j1, vsint32  *Y);
void dup_vf32vector (vfloat32 *X, int j0, int j1, vfloat32 *Y);
    
/* ---------- */
/* --- 2D --- */
/* ---------- */
    
void init_vui8matrix_param (vuint8   **m, int i0, int i1, int j0, int j1, uint8   x0, uint8   xstep, uint8   ystep);
void init_vsi16matrix_param(vsint16  **m, int i0, int i1, int j0, int j1, sint16  x0, sint16  xstep, sint16  ystep);
void init_vui16matrix_param(vuint16  **m, int i0, int i1, int j0, int j1, uint16  x0, uint16  xstep, uint16  ystep);
void init_vsi32matrix_param(vsint32  **m, int i0, int i1, int j0, int j1, sint32  x0, sint32  xstep, sint32  ystep);
void init_vui32matrix_param(vuint32  **m, int i0, int i1, int j0, int j1, uint32  x0, uint32  xstep, uint32  ystep);
void init_vf32matrix_param (vfloat32 **m, int i0, int i1, int j0, int j1, float32 x0, float32 xstep, float32 ystep);

// zero m=0
void zero_vsi8matrix (vsint8   **m, int i0, int i1, int j0, int j1);
void zero_vui8matrix (vuint8   **m, int i0, int i1, int j0, int j1);
void zero_vsi16matrix(vsint16  **m, int i0, int i1, int j0, int j1);
void zero_vui16matrix(vuint16  **m, int i0, int i1, int j0, int j1);
void zero_vsi32matrix(vsint32  **m, int i0, int i1, int j0, int j1);
void zero_vui32matrix(vuint32  **m, int i0, int i1, int j0, int j1);
void zero_vf32matrix (vfloat32 **m, int i0, int i1, int j0, int j1);

void dup_vui8matrix  (vuint8   **X, int i0, int i1, int j0, int j1, vuint8   **Y);
void dup_vsi8matrix  (vsint8   **X, int i0, int i1, int j0, int j1, vsint8   **Y);
void dup_vui16matrix (vuint16  **X, int i0, int i1, int j0, int j1, vuint16  **Y);
void dup_vsi16matrix (vsint16  **X, int i0, int i1, int j0, int j1, vsint16  **Y);
void dup_vui32matrix (vuint32  **X, int i0, int i1, int j0, int j1, vuint32  **Y);
void dup_vsi32matrix (vsint32  **X, int i0, int i1, int j0, int j1, vsint32  **Y);
void dup_vf32matrix  (vfloat32 **X, int i0, int i1, int j0, int j1, vfloat32 **Y);
    

#ifdef __cplusplus
}
#endif

#endif // __VNRUTIL_H__
