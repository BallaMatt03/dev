/* ---------------------- */
/* --- morphoNR_SSE.h --- */
/* ---------------------- */

/*
 * Copyright (c) 2011-2013 Lionel Lacassagne, all rights reserved
 * University Paris Sud 11
 */

#ifndef __MORPHO_NR_SSE_H__
#define __MORPHO_NR_SSE_H__

#ifdef __cplusplus
extern "C" {
#endif

void binary_erosion3_vui8matrix(vuint8 **X, int i0, int i1, int j0, int j1, vuint8 **Y);
void binary_dilation3_vui8matrix(vuint8 **X, int i0, int i1, int j0, int j1, vuint8 **Y);
void erosion3_vui8matrix(vuint8 **X, int i0, int i1, int j0, int j1, vuint8 **Y);
void dilation3_vui8matrix(vuint8 **X, int i0, int i1, int j0, int j1, vuint8 **Y);
    
void binary_erosion_vui8matrix (vuint8 **X, int i0, int i1, int j0, int j1, int radius, vuint8 **Y);
void binary_dilation_vui8matrix(vuint8 **X, int i0, int i1, int j0, int j1, int radius, vuint8 **Y);
void binary_opening_vui8matrix (vuint8 **X, int i0, int i1, int j0, int j1, int radius, vuint8 **Y);
void binary_closing_vui8matrix (vuint8 **X, int i0, int i1, int j0, int j1, int radius, vuint8 **Y);
    
void erosion_vui8matrix (vuint8 **X, int i0, int i1, int j0, int j1, int radius, vuint8 **Y);
void dilation_vui8matrix(vuint8 **X, int i0, int i1, int j0, int j1, int radius, vuint8 **Y);
void opening_vui8matrix (vuint8 **X, int i0, int i1, int j0, int j1, int radius, vuint8 **Y);
void closing_vui8matrix (vuint8 **X, int i0, int i1, int j0, int j1, int radius, vuint8 **Y);

void alternate_sequential_filter_binary_opening_vui8matrix(vuint8 **X, int i0, int i1, int j0, int j1, int radius, vuint8 **Y);
void alternate_sequential_filter_binary_closing_vui8matrix(vuint8 **X, int i0, int i1, int j0, int j1, int radius, vuint8 **Y);

void alternate_sequential_filter_opening_vui8matrix(vuint8 **X, int i0, int i1, int j0, int j1, int radius, vuint8 **Y);
void alternate_sequential_filter_closing_vui8matrix(vuint8 **X, int i0, int i1, int j0, int j1, int radius, vuint8 **Y);

#ifdef __cplusplus
}
#endif

#endif // __MORPHO_NR_SSE_H__
