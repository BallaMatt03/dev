/* ----------------- */
/* --- vnrutil.c --- */
/* ----------------- */


/*
 * Copyright (c) 2004-2006 Lionel Lacassagne
 */

#include <stdio.h>
#include <stdlib.h>

#include <xmmintrin.h>
#include <emmintrin.h>
#include <mmintrin.h>

#include "def.h"
#include "vdef.h"
#include "vnrutil.h"

#define LINEAR_ALLOCATION
/* -------------------------- */
void vnrerror(char error_text[])
/* -------------------------- */
/* Numerical Recipes standard error handler */
{
    fprintf(stderr,"Numerical Recipes run-time error...\n");
    fprintf(stderr,"%s\n",error_text);
    fprintf(stderr,"...now exiting to system...\n");
    exit(1);
}
/* ------------------------------------------------- */
vuint8 **vui8matrix(int nrl, int nrh, int ncl, int nch)
/* ------------------------------------------------- */
/* allocate a vuint8 matrix with subscript range m[nrl..nrh][ncl..nch] */
{
    int i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
    vuint8 **m;

    /* allocate pointers to rows */
    m=(vuint8 **) _mm_malloc ((size_t)((nrow)*sizeof(vuint8*)), 16);
    if (!m) vnrerror("allocation failure 1 in vui8matrix()");
    m -= nrl;

    /* allocate rows and set pointers to them */
#ifdef LINEAR_ALLOCATION
    m[nrl]=(vuint8 *) _mm_malloc ((size_t)((nrow*ncol)*sizeof(vuint8)), 16);
    if (!m[nrl]) vnrerror("allocation failure 2 in vui8matrix()");
    m[nrl] -= ncl;
    for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;
#else    
    for(i=nrl; i<=nrh; i++) {
        m[i] = (vuint8 *) _mm_malloc (ncol*sizeof(vuint8), 16);
        if (!m[i]) vnrerror("allocation failure 2 in vui8matrix()");
        m[i] -= ncl;
    }
#endif
    /* return pointer to array of pointers to rows */
    return m;
}
/* ------------------------------------------------- */
vsint8 **vsi8matrix(int nrl, int nrh, int ncl, int nch)
/* ------------------------------------------------- */
/* allocate a vsint8 matrix with subscript range m[nrl..nrh][ncl..nch] */
{
    int i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
    vsint8 **m;
    
    /* allocate pointers to rows */
    m=(vsint8 **) _mm_malloc ((size_t)((nrow)*sizeof(vsint8*)), 16);
    if (!m) vnrerror("allocation failure 1 in vsi8matrix()");
    m -= nrl;
    
    /* allocate rows and set pointers to them */
#ifdef LINEAR_ALLOCATION
    m[nrl]=(vsint8 *) _mm_malloc ((size_t)((nrow*ncol)*sizeof(vsint8)), 16);
    if (!m[nrl]) vnrerror("allocation failure 2 in vui8matrix()");
    m[nrl] -= ncl;
    for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;
#else    
    for(i=nrl; i<=nrh; i++) {
        m[i] = (vsint8 *) _mm_malloc (ncol*sizeof(vsint8), 16);
        if (!m[i]) vnrerror("allocation failure 2 in vsi8matrix()");
        m[i] -= ncl;
    }
#endif
    /* return pointer to array of pointers to rows */
    return m;
}
/* --------------------------------------------------- */
vuint16 **vui16matrix(int nrl, int nrh, int ncl, int nch)
/* --------------------------------------------------- */
/* allocate a vuint16 matrix with subscript range m[nrl..nrh][ncl..nch] */
{
    int i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
    vuint16 **m;

    /* allocate pointers to rows */
    m=(vuint16 **) _mm_malloc ((size_t)((nrow)*sizeof(vuint16*)), 16);
    if (!m) vnrerror("allocation failure 1 in vui16matrix()");
    m -= nrl;

    /* allocate rows and set pointers to them */
#ifdef LINEAR_ALLOCATION    
    m[nrl]=(vuint16 *) _mm_malloc ((size_t)((nrow*ncol)*sizeof(vuint16)), 16);
    if (!m[nrl]) vnrerror("allocation failure 2 in vui16matrix()");
    m[nrl] -= ncl;
    for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;
#else    
    for(i=nrl; i<=nrh; i++) {
        m[i] = (vuint16 *) _mm_malloc (ncol*sizeof(vuint16), 16);
        if (!m[i]) vnrerror("allocation failure 2 in vui16matrix()");
        m[i] -= ncl;
    }
#endif
    /* return pointer to array of pointers to rows */
    return m;
}
/* --------------------------------------------------- */
vsint16 **vsi16matrix(int nrl, int nrh, int ncl, int nch)
/* --------------------------------------------------- */
/* allocate a vsint16 matrix with subscript range m[nrl..nrh][ncl..nch] */
{
    int i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
    vsint16 **m;
    
    /* allocate pointers to rows */
    m=(vsint16 **) _mm_malloc ((size_t)((nrow)*sizeof(vsint16*)), 16);
    if (!m) vnrerror("allocation failure 1 in vsi16matrix()");
    m -= nrl;
    
    /* allocate rows and set pointers to them */
#ifdef LINEAR_ALLOCATION
    m[nrl]=(vsint16 *) _mm_malloc ((size_t)((nrow*ncol)*sizeof(vsint16)), 16);
    if (!m[nrl]) vnrerror("allocation failure 2 in vsi16matrix()");
    m[nrl] -= ncl;
    for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;
#else    
    for(i=nrl; i<=nrh; i++) {
        m[i] = (vsint16 *) _mm_malloc (ncol*sizeof(vsint16), 16);
        if (!m[i]) vnrerror("allocation failure 2 in vsi16matrix()");
        m[i] -= ncl;
    }
#endif    
    /* return pointer to array of pointers to rows */
    return m;
}
/* --------------------------------------------------- */
vuint32 **vui32matrix(int nrl, int nrh, int ncl, int nch)
/* --------------------------------------------------- */
/* allocate a vuint32 matrix with subscript range m[nrl..nrh][ncl..nch] */
{
    int i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
    vuint32 **m;
    
    /* allocate pointers to rows */
    m=(vuint32 **) _mm_malloc ((size_t)((nrow)*sizeof(vuint32*)), 16);
    if (!m) vnrerror("allocation failure 1 in vui32matrix()");
    m -= nrl;
    
    /* allocate rows and set pointers to them */
#ifdef LINEAR_ALLOCATION
    m[nrl]=(vuint32 *) _mm_malloc ((size_t)((nrow*ncol)*sizeof(vuint32)), 16);
    if (!m[nrl]) vnrerror("allocation failure 2 in vui32matrix()");
    m[nrl] -= ncl;
    for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;
#else    
    for(i=nrl; i<=nrh; i++) {
        m[i] = (vuint32 *) _mm_malloc (ncol*sizeof(vuint32), 16);
        if (!m[i]) vnrerror("allocation failure 2 in vui32matrix()");
        m[i] -= ncl;
    }
#endif
    /* return pointer to array of pointers to rows */
    return m;
}
/* --------------------------------------------------- */
vsint32 **vsi32matrix(int nrl, int nrh, int ncl, int nch)
/* --------------------------------------------------- */
/* allocate a vsint32 matrix with subscript range m[nrl..nrh][ncl..nch] */
{
    int i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
    vsint32 **m;
    
    /* allocate pointers to rows */
    m=(vsint32 **) _mm_malloc ((size_t)((nrow)*sizeof(vsint32*)), 16);
    if (!m) vnrerror("allocation failure 1 in vsi32matrix()");
    m -= nrl;
    
    /* allocate rows and set pointers to them */
#ifdef LINEAR_ALLOCATION
    m[nrl]=(vsint32 *) _mm_malloc ((size_t)((nrow*ncol)*sizeof(vsint32)), 16);
    if (!m[nrl]) vnrerror("allocation failure 2 in vsi32matrix()");
    m[nrl] -= ncl;
    for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;
#else
    for(i=nrl; i<=nrh; i++) {
        m[i] = (vsint32 *) _mm_malloc (ncol*sizeof(vsint32), 16);
        if (!m[i]) vnrerror("allocation failure 2 in vsi32matrix()");
        m[i] -= ncl;
    }
#endif
    /* return pointer to array of pointers to rows */
    return m;
}
/* ----------------------------------------------- */
vfloat **vfmatrix(int nrl, int nrh, int ncl, int nch)
/* ----------------------------------------------- */
/* allocate a vfloat matrix with subscript range m[nrl..nrh][ncl..nch] */
{
    int i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
    vfloat **m;

    /* allocate pointers to rows */
    m=(vfloat **) _mm_malloc ((size_t)((nrow)*sizeof(vfloat*)), 16);
    if (!m) vnrerror("allocation failure 1 in vfmatrix()");
    m -= nrl;

    /* allocate rows and set pointers to them */
#ifdef LINEAR_ALLOCATION    
    m[nrl]=(vfloat *) _mm_malloc ((size_t)((nrow*ncol)*sizeof(vfloat)), 16);
    if (!m[nrl]) vnrerror("allocation failure 2 in vfmatrix()");
    m[nrl] -= ncl;
    for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;
#else        
    for(i=nrl; i<=nrh; i++) {
        m[i]=(vfloat *) _mm_malloc (ncol*sizeof(vfloat), 16);
        if (!m[i]) vnrerror("allocation failure 2 in vfmatrix()");
        m[i] -= ncl;
    }
#endif    
    /* return pointer to array of pointers to rows */
    return m;
}
/* --------------------------------------------------- */
vfloat32 **vf32matrix(int nrl, int nrh, int ncl, int nch)
/* --------------------------------------------------- */
/* allocate a vfloat matrix with subscript range m[nrl..nrh][ncl..nch] */
{
    int i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
    vfloat32 **m;
    
    /* allocate pointers to rows */
    m=(vfloat32 **) _mm_malloc ((size_t)((nrow)*sizeof(vfloat32*)), 16);
    if (!m) vnrerror("allocation failure 1 in vf32matrix()");
    m -= nrl;
    
    /* allocate rows and set pointers to them */
#ifdef LINEAR_ALLOCATION
    m[nrl]=(vfloat32 *) _mm_malloc ((size_t)((nrow*ncol)*sizeof(vfloat32)), 16);
    if (!m[nrl]) vnrerror("allocation failure 2 in vf32matrix()");
    m[nrl] -= ncl;
    for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;
#else    
    for(i=nrl; i<=nrh; i++) {
        m[i]=(vfloat32 *) _mm_malloc (ncol*sizeof(vfloat32));
        if (!m[i]) vnrerror("allocation failure 2 in vf32mmatrix()");
        m[i] -= ncl;
    }
#endif
    /* return pointer to array of pointers to rows */
    return m;
}
/* --------------------------------------------------- */
vfloat32 **vf32matrixL(int nrl, int nrh, int ncl, int nch)
/* --------------------------------------------------- */
/* allocate a vfloat matrix with subscript range m[nrl..nrh][ncl..nch] */
/* Linear allocation */
{
    int i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
    vfloat32 **m;
    
    /* allocate pointers to rows */
    m=(vfloat32 **) _mm_malloc ((size_t)((nrow)*sizeof(vfloat32*)), 16);
    if (!m) vnrerror("allocation failure 1 in vf32matrix()");
    m -= nrl;
    
    /* allocate rows and set pointers to them */
    m[nrl]=(vfloat32 *) _mm_malloc ((size_t)((nrow*ncol)*sizeof(vfloat32)), 16);
    if (!m[nrl]) vnrerror("allocation failure 2 in vf32matrixL()");
    m[nrl] -= ncl;
    for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;
    
    //for(i=nrl; i<=nrh; i++) {
    //    m[i]=(vfloat32 *) _mm_malloc (ncol*sizeof(vfloat32));
    //    if (!m[i]) vnrerror("allocation failure 2 in vf32mmatrix()");
    //    m[i] -= ncl;
    //}
    /* return pointer to array of pointers to rows */
    return m;
}
/* -------------------------------------------------------------- */
void free_vui8matrix(vuint8 **m, int nrl, int nrh, int ncl, int nch)
/* -------------------------------------------------------------- */
{
    _mm_free(m[nrl]+ncl);
    _mm_free(m+nrl);
}
/* -------------------------------------------------------------- */
void free_vsi8matrix(vsint8 **m, int nrl, int nrh, int ncl, int nch)
/* -------------------------------------------------------------- */
{
    _mm_free(m[nrl]+ncl);
    _mm_free(m+nrl);
}
/* ---------------------------------------------------------------- */
void free_vui16matrix(vuint16 **m, int nrl, int nrh, int ncl, int nch)
/* ---------------------------------------------------------------- */
{
    _mm_free(m[nrl]+ncl);
    _mm_free(m+nrl);
}
/* ---------------------------------------------------------------- */
void free_vsi16matrix(vsint16 **m, int nrl, int nrh, int ncl, int nch)
/* ---------------------------------------------------------------- */
{
    _mm_free(m[nrl]+ncl);
    _mm_free(m+nrl);
}
/* ---------------------------------------------------------------- */
void free_vui32matrix(vuint32 **m, int nrl, int nrh, int ncl, int nch)
/* ---------------------------------------------------------------- */
{
    _mm_free(m[nrl]+ncl);
    _mm_free(m+nrl);
}
/* --------------------------------------------------------------- */
void free_vsi32matrix(vsint32 **m, int nrl, int nrh, int ncl, int nch)
/* --------------------------------------------------------------- */
{
    _mm_free(m[nrl]+ncl);
    _mm_free(m+nrl);
}
/* ---------------------------------------------------------------- */
void free_vf32matrix(vfloat32 **m, int nrl, int nrh, int ncl, int nch)
/* ---------------------------------------------------------------- */
{
    _mm_free(m[nrl]+ncl);
    _mm_free(m+nrl);
}
/* ---------------------------------------------------- */
vuint8**vui8matrix_map(int nrl, int nrh, int ncl, int nch)
/* ---------------------------------------------------- */
{
    int nrow=nrh-nrl+1;
    vuint8 **m;
    
    /* allocate pointers to rows */
    m=(vuint8**) _mm_malloc ((size_t)(nrow*sizeof(vuint8*)), 16);
    if (!m) vnrerror("allocation failure 1 in vui8matrix_map()");
    m -= nrl;
    
    /* return pointer to array of pointers to rows */
    return m;
}
/* ---------------------------------------------------- */
vsint8**vsi8matrix_map(int nrl, int nrh, int ncl, int nch)
/* ---------------------------------------------------- */
{
    int nrow=nrh-nrl+1;
    vsint8 **m;
    
    /* allocate pointers to rows */
    m=(vsint8**) _mm_malloc ((size_t)(nrow*sizeof(vsint8*)), 16);
    if (!m) vnrerror("allocation failure 1 in vsi8matrix_map()");
    m -= nrl;
    
    /* return pointer to array of pointers to rows */
    return m;
}
/* ------------------------------------------------------ */
vuint16**vui16matrix_map(int nrl, int nrh, int ncl, int nch)
/* ------------------------------------------------------ */
{
    int nrow=nrh-nrl+1;
    vuint16 **m;
    
    /* allocate pointers to rows */
    m=(vuint16**) _mm_malloc ((size_t)(nrow*sizeof(vuint16*)), 16);
    if (!m) vnrerror("allocation failure 1 in vui16matrix_map()");
    m -= nrl;
    
    /* return pointer to array of pointers to rows */
    return m;
}
/* ------------------------------------------------------ */
vsint16**vsi16matrix_map(int nrl, int nrh, int ncl, int nch)
/* ------------------------------------------------------ */
{
    int nrow=nrh-nrl+1;
    vsint16 **m;
    
    /* allocate pointers to rows */
    m=(vsint16**) _mm_malloc ((size_t)(nrow*sizeof(vsint16*)), 16);
    if (!m) vnrerror("allocation failure 1 in vsi16matrix_map()");
    m -= nrl;
    
    /* return pointer to array of pointers to rows */
    return m;
}
/* ------------------------------------------------------ */
vuint32**vui32matrix_map(int nrl, int nrh, int ncl, int nch)
/* ------------------------------------------------------ */
{
    int nrow=nrh-nrl+1;
    vuint32 **m;
    
    /* allocate pointers to rows */
    m=(vuint32**) _mm_malloc ((size_t)(nrow*sizeof(vuint32*)), 16);
    if (!m) vnrerror("allocation failure 1 in vui32matrix_map()");
    m -= nrl;
    
    /* return pointer to array of pointers to rows */
    return m;
}
/* ------------------------------------------------------- */
vsint32** vsi32matrix_map(int nrl, int nrh, int ncl, int nch)
/* ------------------------------------------------------- */
{
    int nrow=nrh-nrl+1;
    vsint32 **m;
    
    /* allocate pointers to rows */
    m=(vsint32**) _mm_malloc ((size_t)(nrow*sizeof(vsint32*)), 16);
    if (!m) vnrerror("allocation failure 1 in vsi32matrix_map()");
    m -= nrl;
    
    /* return pointer to array of pointers to rows */
    return m;
}
/* --------------------------------------------------- */
vfloat** vfmatrix_map(int nrl, int nrh, int ncl, int nch)
/* --------------------------------------------------- */
{
    int nrow=nrh-nrl+1;
    vfloat **m;
    
    /* allocate pointers to rows */
    m=(vfloat**) _mm_malloc ((size_t)(nrow*sizeof(vfloat*)), 16);
    if (!m) vnrerror("allocation failure 1 in vfmatrix_map()");
    m -= nrl;
    
    /* return pointer to array of pointers to rows */
    return m;
}
/* -------------------------------------------------------- */
vfloat32** vf32matrix_map (int nrl, int nrh, int ncl, int nch)
/* -------------------------------------------------------- */
{
    int nrow=nrh-nrl+1;
    vfloat32 **m;
    
    /* allocate pointers to rows */
    m=(vfloat32**) _mm_malloc ((size_t)(nrow*sizeof(vfloat32*)), 16);
    if (!m) vnrerror("allocation failure 1 in vf32matrix_map()");
    m -= nrl;
    
    /* return pointer to array of pointers to rows */
    return m;
}
/* ---------------------------------------------------------------------------------------------------- */
vuint8** vui8matrix_map_1D_pitch(vuint8 **m, int nrl, int nrh, int ncl, int nch, void *data_1D, int pitch)
/* ---------------------------------------------------------------------------------------------------- */
{
    int i;
    vuint8 *p;
    
    /* map rows and set pointers to them */
    m[nrl]= (vuint8*) data_1D;
    m[nrl] -= ncl;
    
    //for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1] + pitch;
    p = (vuint8*) m[nrl];
    for(i=nrl+1;i<=nrh;i++) {
        p += pitch;
        m[i] = (vuint8*) p;
    }
    /* return pointer to array of pointers to rows */
    return m;
}
//croiseur = bataille
//destroyer = heros
/* ---------------------------------------------------------------------------------------------------- */
vsint8** vsi8matrix_map_1D_pitch(vsint8 **m, int nrl, int nrh, int ncl, int nch, void *data_1D, int pitch)
/* ---------------------------------------------------------------------------------------------------- */
{
    int i;
    vsint8 *p;
    
    /* map rows and set pointers to them */
    m[nrl]= (vsint8*) data_1D;
    m[nrl] -= ncl;
    
    //for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1] + pitch;
    p = (vsint8*) m[nrl];
    for(i=nrl+1;i<=nrh;i++) {
        p += pitch;
        m[i] = (vsint8*) p;
    }
    /* return pointer to array of pointers to rows */
    return m;
}
/* --------------------------------------------------------------------------------------------- */
vuint16** vui16matrix_map_1D_pitch(vuint16 **m, int nrl, int nrh, int ncl, int nch, void *data_1D, int pitch)
/* --------------------------------------------------------------------------------------------- */
{
    int i;
    vuint16 *p;
    
    /* map rows and set pointers to them */
    m[nrl]= (vuint16*) data_1D;
    m[nrl] -= ncl;
    
    //for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1] + pitch;
    p = (vuint16*) m[nrl];
    for(i=nrl+1;i<=nrh;i++) {
        p += pitch;
        m[i] = (vuint16*) p;
    }
    /* return pointer to array of pointers to rows */
    return m;
}
/* ------------------------------------------------------------------------------------------------------ */
vsint16** vsi16matrix_map_1D_pitch(vsint16 **m, int nrl, int nrh, int ncl, int nch, void *data_1D, int pitch)
/* ------------------------------------------------------------------------------------------------------ */
{
    int i;
    vsint16 *p;
    
    /* map rows and set pointers to them */
    m[nrl]= (vsint16*) data_1D;
    m[nrl] -= ncl;
    
    //for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1] + pitch;
    p = (vsint16*) m[nrl];
    for(i=nrl+1;i<=nrh;i++) {
        p += pitch;
        m[i] = (vsint16*) p;
    }
    /* return pointer to array of pointers to rows */
    return m;
}
/* ------------------------------------------------------------------------------------------------------ */
vuint32** vui32matrix_map_1D_pitch(vuint32 **m, int nrl, int nrh, int ncl, int nch, void *data_1D, int pitch)
/* ------------------------------------------------------------------------------------------------------ */
{
    int i;
    vuint32 *p;
    
    /* map rows and set pointers to them */
    m[nrl]= (vuint32*) data_1D;
    m[nrl] -= ncl;
    
    //for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1] + pitch;
    p = (vuint32*) m[nrl];
    for(i=nrl+1;i<=nrh;i++) {
        p += pitch;
        m[i] = (vuint32*) p;
    }
    /* return pointer to array of pointers to rows */
    return m;
}
/* ------------------------------------------------------------------------------------------------------ */
vsint32** vsi32matrix_map_1D_pitch(vsint32 **m, int nrl, int nrh, int ncl, int nch, void *data_1D, int pitch)
/* ------------------------------------------------------------------------------------------------------ */
{
    int i;
    vsint32 *p;
    
    /* map rows and set pointers to them */
    m[nrl]= (vsint32*) data_1D;
    m[nrl] -= ncl;
    
    //for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1] + pitch;
    p = (vsint32*) m[nrl];
    for(i=nrl+1;i<=nrh;i++) {
        p += pitch;
        m[i] = (vsint32*) p;
    }
    /* return pointer to array of pointers to rows */
    return m;
}
/* ------------------------------------------------------------------------------------------------------ */
vfloat** vfmatrix_map_1D_pitch(vfloat **m, int nrl, int nrh, int ncl, int nch, void *data_1D, int pitch)
/* ------------------------------------------------------------------------------------------------------ */
{
    int i;
    vfloat *p;
    
    /* map rows and set pointers to them */
    m[nrl]= (vfloat*) data_1D;
    m[nrl] -= ncl;
    
    //for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1] + pitch;
    p = (vfloat*) m[nrl];
    for(i=nrl+1;i<=nrh;i++) {
        p += pitch;
        m[i] = (vfloat*) p;
    }
    /* return pointer to array of pointers to rows */
    return m;
}
/* -------------------------------------------------------------------------------------------------------- */
vfloat32** vf32matrix_map_1D_pitch(vfloat32 **m, int nrl, int nrh, int ncl, int nch, void *data_1D, int pitch)
/* -------------------------------------------------------------------------------------------------------- */
{
    int i;
    vfloat32 *p;
    
    /* map rows and set pointers to them */
    m[nrl]= (vfloat32*) data_1D;
    m[nrl] -= ncl;
    
    //for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1] + pitch;
    p = (vfloat32*) m[nrl];
    for(i=nrl+1;i<=nrh;i++) {
        p += pitch;
        m[i] = (vfloat32*) p;
    }
    /* return pointer to array of pointers to rows */
    return m;
}
/* ------------------------------------------------------------------ */
void free_vui8matrix_map(vuint8 **m, int nrl, int nrh, int ncl, int nch)
/* ------------------------------------------------------------------ */
{
    _mm_free(m+nrl);
}
/* ------------------------------------------------------------------ */
void free_vsi8matrix_map(vsint8 **m, int nrl, int nrh, int ncl, int nch)
/* ------------------------------------------------------------------ */
{
    _mm_free(m+nrl);
}
/* -------------------------------------------------------------------- */
void free_vui16matrix_map(vuint16 **m, int nrl, int nrh, int ncl, int nch)
/* -------------------------------------------------------------------- */
{
    _mm_free(m+nrl);
}
/* -------------------------------------------------------------------- */
void free_vsi16matrix_map(vsint16 **m, int nrl, int nrh, int ncl, int nch)
/* -------------------------------------------------------------------- */
{
    _mm_free(m+nrl);
}
/* -------------------------------------------------------------------- */
void free_vui32matrix_map(vuint32 **m, int nrl, int nrh, int ncl, int nch)
/* -------------------------------------------------------------------- */
{
    _mm_free(m+nrl);
}
/* -------------------------------------------------------------------- */
void free_vsi32matrix_map(vsint32 **m, int nrl, int nrh, int ncl, int nch)
/* -------------------------------------------------------------------- */
{
    _mm_free(m+nrl);
}
/* ---------------------------------------------------------------- */
void free_vfmatrix_map(vfloat **m, int nrl, int nrh, int ncl, int nch)
/* ---------------------------------------------------------------- */
{
    _mm_free(m+nrl);
}
/* ------------------------------------------------------------------- */
void free_vf32matrix_map(vfloat32 **m, int nrl, int nrh, int ncl, int nch)
/* ------------------------------------------------------------------- */
{
    _mm_free(m+nrl);
}
/* ------------------------------------------------------------ */
void resize_vui8matrix(vuint8 **m, int i0, int i1, int j0, int j1)
/* ------------------------------------------------------------ */
{
    int i, ncol=j1-j0+1;
    
    for(i=i0+1; i<=i1; i++) m[i]=m[i-1]+ncol;
}
/* ------------------------------------------------------------ */
void resize_vsi8matrix(vsint8 **m, int i0, int i1, int j0, int j1)
/* ------------------------------------------------------------ */
{
    int i, ncol=j1-j0+1;
    
    for(i=i0+1; i<=i1; i++) m[i]=m[i-1]+ncol;
}
/* -------------------------------------------------------------- */
void resize_vui16matrix(vuint16 **m, int i0, int i1, int j0, int j1)
/* -------------------------------------------------------------- */
{
    int i, ncol=j1-j0+1;
    
    for(i=i0+1; i<=i1; i++) m[i]=m[i-1]+ncol;
}
/* -------------------------------------------------------------- */
void resize_vsi16matrix(vsint16 **m, int i0, int i1, int j0, int j1)
/* -------------------------------------------------------------- */
{
    int i, ncol=j1-j0+1;
    
    for(i=i0+1; i<=i1; i++) m[i]=m[i-1]+ncol;
}
/* -------------------------------------------------------------- */
void resize_vui32matrix(vuint32 **m, int i0, int i1, int j0, int j1)
/* -------------------------------------------------------------- */
{
    int i, ncol=j1-j0+1;
    
    for(i=i0+1; i<=i1; i++) m[i]=m[i-1]+ncol;
}
/* -------------------------------------------------------------- */
void resize_vsi32matrix(vsint32 **m, int i0, int i1, int j0, int j1)
/* -------------------------------------------------------------- */
{
    int i, ncol=j1-j0+1;
    
    for(i=i0+1; i<=i1; i++) m[i]=m[i-1]+ncol;
}
/* -------------------------------------------------------------- */
void resize_vf32matrix(vfloat32 **m, int i0, int i1, int j0, int j1)
/* -------------------------------------------------------------- */
{
    int i, ncol=j1-j0+1;
    
    for(i=i0+1; i<=i1; i++) m[i]=m[i-1]+ncol;
}
/* ------------------ */
/* --- 0D Altivec --- */
/* ------------------ */

/* --------------------- */
vuint8 init_vuint8(uint8 x)
/* --------------------- */
{
    vuint8 T[1];
    uint8 *p = (uint8*) T;
    
    p[0]  = p[1]  = p[2]  = p[3]  = x;
    p[4]  = p[5]  = p[6]  = p[7]  = x;
    p[8]  = p[9]  = p[10] = p[11] = x;
    p[12] = p[13] = p[14] = p[15] = x;
    
    return T[0];
}
/* --------------------- */
vsint8 init_vsint8(sint8 x)
/* --------------------- */
{
    vsint8 T[1];
    sint8 *p = (sint8*) T;
    
    p[0]  = p[1]  = p[2]  = p[3]  = x;
    p[4]  = p[5]  = p[6]  = p[7]  = x;
    p[8]  = p[9]  = p[10] = p[11] = x;
    p[12] = p[13] = p[14] = p[15] = x;
    
    return T[0];
}
/* ------------------------ */
vuint16 init_vuint16(uint16 x)
/* ------------------------ */
{
    vuint16 T[1];
    uint16 *p = (uint16*) T;
    
    p[0] = p[1] = p[2] = p[3] = x;
    p[4] = p[5] = p[6] = p[7] = x;
    
    return T[0];
}
/* ------------------------ */
vsint16 init_vsint16(sint16 x)
/* ------------------------ */
{
    vsint16 T[1];
    sint16 *p = (sint16*) T;
    
    p[0] = p[1] = p[2] = p[3] = x;
    p[4] = p[5] = p[6] = p[7] = x;
    
    return T[0];
}
/* ------------------------ */
vuint32 init_vuint32(uint32 x)
/* ------------------------ */
{
    vuint32 T[1];
    uint32 *p = (uint32*) T;
    
    p[0] = p[1] = p[2] = p[3] = x;
    
    return T[0];
}
/* ------------------------ */
vsint32 init_vsint32(sint32 x)
/* ------------------------ */
{
    vsint32 T[1];
    sint32 *p = (sint32*) T;
    
    p[0] = p[1] = p[2] = p[3] = x;
    
    return T[0];
}
/* --------------------------- */
vfloat32 init_vfloat32(float32 x)
/* --------------------------- */
{
    vfloat32 T[1];
    float32 *p = (float32*) T;
    
    p[0] = p[1] = p[2] = p[3] = x;
    
    return T[0];
}
/* ---------------------------------------- */
vuint8 init_vuint8_param(uint8 x0, uint8 step)
/* ---------------------------------------- */
{
    int i;
    vuint8 T[1];
    uint8 *p = (uint8*) T;
    
    for(i=0; i<16; i++) {
        p[i] = x0;
        x0 += step;
    }
    return T[0];
}
/* ---------------------------------------- */
vsint8 init_vsint8_param(sint8 x0, sint8 step)
/* ---------------------------------------- */
{
    int i;
    vsint8 T[1];
    sint8 *p = (sint8*) T;
    
    for(i=0; i<16; i++) {
        p[i] = x0;
        x0 += step;
    }
    return T[0];
}
/* -------------------------------------------- */
vuint16 init_vuint16_param(uint16 x0, uint16 step)
/* -------------------------------------------- */
{
    int i;
    vuint16 T[1];
    uint16 *p = (uint16*) T;
    
    for(i=0; i<8; i++) {
        p[i] = x0;
        x0 += step;
    }
    return T[0];
}
/* -------------------------------------------- */
vsint16 init_vsint16_param(sint16 x0, sint16 step)
/* -------------------------------------------- */
{
    int i;
    vsint16 T[1];
    sint16 *p = (sint16*) T;
    
    for(i=0; i<8; i++) {
        p[i] = x0;
        x0 += step;
    }
    return T[0];
}
/* -------------------------------------------- */
vuint32 init_vuint32_param(uint32 x0, uint32 step)
/* -------------------------------------------- */
{
    int i;
    vuint32 T[1];
    uint32 *p = (uint32*) T;
    
    for(i=0; i<4; i++) {
        p[i] = x0;
        x0 += step;
    }
    return T[0];
}
/* -------------------------------------------- */
vsint32 init_vsint32_param(sint32 x0, sint32 step)
/* -------------------------------------------- */
{
    int i;
    vsint32 T[1];
    sint32 *p = (sint32*) T;
    
    for(i=0; i<4; i++) {
        p[i] = x0;
        x0 += step;
    }
    return T[0];
}
/* ------------------------------------------------ */
vfloat32 init_vfloat32_param(float32 x0, float32 step)
/* ------------------------------------------------ */
{
    int i;
    vfloat32 T[1];
    float32 *p = (float32*) T;
    
    for(i=0; i<4; i++) {
        p[i] = x0;
        x0 += step;
    }
    return T[0];
}
/* -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
vuint8 init_vuint8_all(uint8 x0, uint8 x1, uint8 x2, uint8 x3, uint8 x4, uint8 x5, uint8 x6, uint8 x7, uint8 x8, uint8 x9, uint8 x10, uint8 x11, uint8 x12, uint8 x13, uint8 x14, uint8 x15)
/* -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
{
    vuint8 T[1];
    uint8 *p = (uint8*) T;
    
    p[0] = x0;
    p[1] = x1;
    p[2] = x2;
    p[3] = x3;
    p[4] = x4;
    p[5] = x5;
    p[6] = x6;
    p[7] = x7;
    p[8] = x8;
    p[9] = x9;
    p[10] = x10;
    p[11] = x11;
    p[12] = x12;
    p[13] = x13;
    p[14] = x14;
    p[15] = x15;
    
    return T[0];
}
/* -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
vsint8 init_vsint8_all(sint8 x0, sint8 x1, sint8 x2, sint8 x3, sint8 x4, sint8 x5, sint8 x6, sint8 x7, sint8 x8, sint8 x9, sint8 x10, sint8 x11, sint8 x12, sint8 x13, sint8 x14, sint8 x15)
/* -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
{
    vsint8 T[1];
    sint8 *p = (sint8*) T;
    
    p[0] = x0;
    p[1] = x1;
    p[2] = x2;
    p[3] = x3;
    p[4] = x4;
    p[5] = x5;
    p[6] = x6;
    p[7] = x7;
    p[8] = x8;
    p[9] = x9;
    p[10] = x10;
    p[11] = x11;
    p[12] = x12;
    p[13] = x13;
    p[14] = x14;
    p[15] = x15;
    
    return T[0];
}
/* ---------------------------------------------------------------------------------------------------------- */
vuint16 init_vuint16_all(uint16 x0, uint16 x1, uint16 x2, uint16 x3, uint16 x4, uint16 x5, uint16 x6, uint16 x7)
/* ---------------------------------------------------------------------------------------------------------- */
{
    vuint16 T[1];
    uint16 *p = (uint16*) T;
    
    p[0] = x0;
    p[1] = x1;
    p[2] = x2;
    p[3] = x3;
    p[4] = x4;
    p[5] = x5;
    p[6] = x6;
    p[7] = x7;
    
    return T[0];
}
/* ---------------------------------------------------------------------------------------------------------- */
vsint16 init_vsint16_all(sint16 x0, sint16 x1, sint16 x2, sint16 x3, sint16 x4, sint16 x5, sint16 x6, sint16 x7)
/* ---------------------------------------------------------------------------------------------------------- */
{
    vsint16 T[1];
    sint16 *p = (sint16*) T;
    
    p[0] = x0;
    p[1] = x1;
    p[2] = x2;
    p[3] = x3;
    p[4] = x4;
    p[5] = x5;
    p[6] = x6;
    p[7] = x7;
    
    return T[0];
}
/* -------------------------------------------------------------- */
vuint32 init_vuint32_all(uint32 x0, uint32 x1, uint32 x2, uint32 x3)
/* -------------------------------------------------------------- */
{
    vuint32 T[1];
    uint32 *p = (uint32*) T;
    
    p[0] = x0;
    p[1] = x1;
    p[2] = x2;
    p[3] = x3;
    
    return T[0];
}
/* -------------------------------------------------------------- */
vsint32 init_vsint32_all(sint32 x0, sint32 x1, sint32 x2, sint32 x3)
/* -------------------------------------------------------------- */
{
    vsint32 T[1];
    sint32 *p = (sint32*) T;
    
    p[0] = x0;
    p[1] = x1;
    p[2] = x2;
    p[3] = x3;
    
    return T[0];
}
/* -------------------------------------------------------------------- */
vfloat32 init_vfloat32_all(float32 x0, float32 x1, float32 x2, float32 x3)
/* -------------------------------------------------------------------- */
{
    vfloat32 T[1];
    float32 *p = (float32*) T;
    
    p[0] = x0;
    p[1] = x1;
    p[2] = x2;
    p[3] = x3;
    
    return T[0];
}
/* ------------------ */
/* --- 1D Altivec --- */
/* ------------------ */

/* ----------------------------------------- */
void zero_vsi8vector(vsint8 *v, int j0, int j1)
/* ----------------------------------------- */
{
    int j;
    //vsint8 z = vec_splat_s8(0); // AV
    vsint8 z = init_vsint8(0);
    
    for(j=j0; j<=j1; j++) {
        //vec_st(z, 0, &v[j]);
        _mm_store_si128(&v[j], z);
    }
}
/* ----------------------------------------- */
void zero_vui8vector(vuint8 *v, int j0, int j1)
/* ----------------------------------------- */
{
    int j;
    //vuint8 z = vec_splat_u8(0); // AV
    vuint8 z = init_vuint8(0);
    
    for(j=j0; j<=j1; j++) {
        //vec_st(z, 0, &v[j]);
        _mm_store_si128(&v[j], z);
    }
}
/* ------------------------------------------- */
void zero_vsi16vector(vsint16 *v, int j0, int j1)
/* ------------------------------------------- */
{
    int j;
    //vsint16 z = vec_splat_s16(0); // AV
    vsint16 z = init_vsint16(0);
    
    for(j=j0; j<=j1; j++) {
        //vec_st(z, 0, &v[j]);
        _mm_store_si128(&v[j], z);
    }
}
/* ------------------------------------------- */
void zero_vui16vector(vuint16 *v, int j0, int j1)
/* ------------------------------------------- */
{
    int j;
    //vuint16 z = vec_splat_u16(0); //AV
    vuint16 z = init_vuint16(0);
    
    for(j=j0; j<=j1; j++) {
        //vec_st(z, 0, &v[j]);
        _mm_store_si128(&v[j], z);
    }
}
/* ------------------------------------------- */
void zero_vsi32vector(vsint32 *v, int j0, int j1)
/* ------------------------------------------- */
{
    int j;
    //vsint32 z = vec_splat_s32(0); // AV
    vsint32 z = init_vsint32(0);
    
    for(j=j0; j<=j1; j++) {
        //vec_st(z, 0, &v[j]);
        _mm_store_si128(&v[j], z);
    }
}
/* -------------------------------------------- */
void zero_vui32vectorx(vuint32 *v, int j0, int j1)
/* -------------------------------------------- */
{
    int j;
    //vuint32 z = vec_splat_u32(0); // AV
    vuint32 z = init_vuint32(0);
    
    for(j=j0; j<=j1; j++) {
        //vec_st(z, 0, &v[j]);
        _mm_store_si128(&v[j], z);
    }
}
/* ------------------------------------------- */
void zero_vf32vector(vfloat32 *v, int j0, int j1)
/* ------------------------------------------- */
{
    int j;
    //vfloat32 z = (vfloat32) (0,0,0,0); // AV
    vfloat32 z = init_vfloat32(0);
    
    for(j=j0; j<=j1; j++) {
        //vec_st(z, 0, &v[j]);
        _mm_store_ps((float*)&v[j], z);
    }
}
/* ---------------------------------------------------------------------------------------------------- */
void init_vui8matrix_param(vuint8 **m, int i0, int i1, int j0, int j1, uint8 x0, uint8 xstep, uint8 ystep)
/* ---------------------------------------------------------------------------------------------------- */
{
    int i, j;
    vuint8 vxstep = init_vuint8(16*xstep);
    vuint8 vystep = init_vuint8(ystep);
    //vuint8 vx, vx0 = init_vuint8_all(x0, x0+xstep, x0+2*xstep, x0+3*xstep, x0+4*xstep,  x0+5*xstep,  x0+6*xstep,  x0+7*xstep, x0+8*xstep, x0+9*xstep, x0+10*xstep, x0+11*xstep, x0+12*xstep, x0+13*xstep, x0+14*xstep, x0+15*xstep);
    vuint8 vx, vx0 = init_vuint8_param(x0, xstep);
    
    for(i=i0; i<=i1; i++) {
        vx = vx0;
        for(j=j0; j<=j1; j++) {
            //vec_st(vx, 0, &m[i][j]);
            //vx = vec_add(vx, vxstep);
            _mm_store_si128(&m[i][j], vx);
            vx = _mm_add_epi8(vx, vxstep);
        }
        //vx0 = vec_add(vx0, vystep);
        vx0 = _mm_add_epi8(vx0, vystep);
    }
}
/* --------------------------------------------------------------------------------------------------------- */
void init_vui16matrix_param(vuint16 **m, int i0, int i1, int j0, int j1, uint16 x0, uint16 xstep, uint16 ystep)
/* --------------------------------------------------------------------------------------------------------- */
{
    int i, j;
    vuint16 vx, vx0 = init_vuint16_param(x0, xstep);
    vuint16 vxstep = init_vuint16(8*xstep);
    vuint16 vystep = init_vuint16(ystep);
    
    for(i=i0; i<=i1; i++) {
        vx = vx0;
        for(j=j0; j<=j1; j++) {
            //vec_st(vx, 0, &m[i][j]);
            //vx = vec_add(vx, vxstep);
            _mm_store_si128(&m[i][j], vx);
            vx = _mm_add_epi16(vx, vxstep);
        }
        //vx0 = vec_add(vx0, vystep);
        vx0 = _mm_add_epi16(vx0, vystep);
    }
}
/* --------------------------------------------------------------------------------------------------------- */
void init_vsi16matrix_param(vsint16 **m, int i0, int i1, int j0, int j1, sint16 x0, sint16 xstep, sint16 ystep)
/* --------------------------------------------------------------------------------------------------------- */
{
    int i, j;
    vsint16 vx, vx0 = init_vsint16_param(x0, xstep);
    vsint16 vxstep  = init_vsint16(8*xstep);
    vsint16 vystep  = init_vsint16(ystep);
    
    for(i=i0; i<=i1; i++) {
        vx = vx0;
        for(j=j0; j<=j1; j++) {
            //vec_st(vx, 0, &m[i][j]);
            //vx = vec_add(vx, vxstep);
            _mm_store_si128(&m[i][j], vx);
            vx = _mm_add_epi16(vx, vxstep);
        }
        //vx0 = vec_add(vx0, vystep);
        vx0 = _mm_add_epi16(vx0, vystep);
    }
}
/* ------------------------------------------------------------------------------------------------------------ */
void init_vui32matrix_param(vuint32 **m, int i0, int i1, int j0, int j1, uint32  x0, uint32  xstep, uint32  ystep)
/* ------------------------------------------------------------------------------------------------------------ */
{
    int i, j;
    vuint32 vx, vx0 = init_vuint32_param(x0, xstep);
    vuint32 vxstep = init_vuint32(4*xstep);
    vuint32 vystep = init_vuint32(ystep);
    
    for(i=i0; i<=i1; i++) {
        vx = vx0;
        for(j=j0; j<=j1; j++) {
            //vec_st(vx, 0, &m[i][j]);
            //vx = vec_add(vx, vxstep);
            _mm_store_si128(&m[i][j], vx);
            vx = _mm_add_epi32(vx, vxstep);
        }
        //vx0 = vec_add(vx0, vystep);
        vx0 = _mm_add_epi32(vx0, vystep);
    }
}
/* ------------------------------------------------------------------------------------------------------------ */
void init_vsi32matrix_param(vsint32 **m, int i0, int i1, int j0, int j1, sint32  x0, sint32  xstep, sint32  ystep)
/* ------------------------------------------------------------------------------------------------------------ */
{
    int i, j;
    vsint32 vx, vx0 = init_vsint32_param(x0, xstep);
    vsint32 vxstep  = init_vsint32(4*xstep);
    vsint32 vystep  = init_vsint32(ystep);
    
    for(i=i0; i<=i1; i++) {
        vx = vx0;
        for(j=j0; j<=j1; j++) {
            //vec_st(vx, 0, &m[i][j]);
            //vx = vec_add(vx, vxstep);
            _mm_store_si128(&m[i][j], vx);
            vx = _mm_add_epi32(vx, vxstep);
        }
        //vx0 = vec_add(vx0, vystep);
        vx0 = _mm_add_epi32(vx0, vystep);
    }
}
/* ------------------------------------------------------------------------------------------------------------ */
void init_vf32matrix_param(vfloat32 **m, int i0, int i1, int j0, int j1, float32 x0, float32 xstep, float32 ystep)
/* ------------------------------------------------------------------------------------------------------------ */
{
    int i, j;
    vfloat32 vx, vx0 = init_vfloat32_param(x0, xstep);
    vfloat32 vxstep = init_vfloat32(4*xstep);
    vfloat32 vystep = init_vfloat32(ystep);
    
    for(i=i0; i<=i1; i++) {
        vx = vx0;
        for(j=j0; j<=j1; j++) {
            //vec_st(vx, 0, &m[i][j]);
            //vx = vec_add(vx, vxstep);
            _mm_store_ps((float*)&m[i][j], vx);
            vx = _mm_add_ps(vx, vxstep);
        }
        //vx0 = vec_add(vx0, vystep);
        vx0 = _mm_add_ps(vx0, vystep);
    }
}
/* ---------------------------------------------------------- */
void zero_vsi8matrix(vsint8 **m, int i0, int i1, int j0, int j1)
/* ---------------------------------------------------------- */
{
    int i, j;
    vsint8 z = init_vsint8(0);
    
    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {
            //vec_st(z, 0, &m[i][j]);
            _mm_store_si128(&m[i][j], z);
        }
    }
}
/* ---------------------------------------------------------- */
void zero_vui8matrix(vuint8 **m, int i0, int i1, int j0, int j1)
/* ---------------------------------------------------------- */
{
    int i, j;
    vuint8 z = init_vuint8(0);
    
    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {
            //vec_st(z, 0, &m[i][j]);
            _mm_store_si128(&m[i][j], z);
        }
    }
}
/* ------------------------------------------------------------ */
void zero_vsi16matrix(vsint16 **m, int i0, int i1, int j0, int j1)
/* ------------------------------------------------------------ */
{
    int i, j;
    vsint16 z = init_vsint16(0);
    
    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {
            //vec_st(z, 0, &m[i][j]);
            _mm_store_si128(&m[i][j], z);
        }
    }
}
/* ------------------------------------------------------------ */
void zero_vui16matrix(vuint16 **m, int i0, int i1, int j0, int j1)
/* ------------------------------------------------------------ */
{
    int i, j;
    vuint16 z = init_vuint16(0);
    
    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {
            //vec_st(z, 0, &m[i][j]);
            _mm_store_si128(&m[i][j], z);
        }
    }
}
/* ------------------------------------------------------------ */
void zero_vsi32matrix(vsint32 **m, int i0, int i1, int j0, int j1)
/* ------------------------------------------------------------ */
{
    int i, j;
    vsint32 z = init_vsint32(0);
    
    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {
            //vec_st(z, 0, &m[i][j]);
            _mm_store_si128(&m[i][j], z);
        }
    }
}
/* ------------------------------------------------------------ */
void zero_vui32matrix(vuint32 **m, int i0, int i1, int j0, int j1)
/* ------------------------------------------------------------ */
{
    int i, j;
    vuint32 z = init_vuint32(0);
    
    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {
            //vec_st(z, 0, &m[i][j]);
            _mm_store_si128(&m[i][j], z);
        }
    }
}
/* ------------------------------------------------------------- */
void zero_vf32matrix (vfloat32 **m, int i0, int i1, int j0, int j1)
/* ------------------------------------------------------------- */
{
    int i, j;
    vfloat32 z = init_vfloat32(0);
    
    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {
            //vec_st(z, 0, &m[i][j]);
            _mm_store_ps((float*) &m[i][j], z);
        }
    }
}
/* --------------------------------------------------- */
void dup_vui8vector(vuint8 *X, int j0, int j1, vuint8 *Y)
/* --------------------------------------------------- */
{
    int j;
    vuint8 x;
    
    for(j=j0; j<=j1; j++) {
        //x = vec_ld(0, &X[j]);
        //vec_st(x, 0, &Y[j]);
        x = _mm_load_si128(&X[j]);
        _mm_store_si128(&Y[j], x);
    }
}
/* --------------------------------------------------- */
void dup_vsi8vector(vsint8 *X, int j0, int j1, vsint8 *Y)
/* --------------------------------------------------- */
{
    int j;
    vsint8 x;
    
    for(j=j0; j<=j1; j++) {
        //x = vec_ld(0, &X[j]);
        //vec_st(x, 0, &Y[j]);
        x = _mm_load_si128(&X[j]);
        _mm_store_si128(&Y[j], x);
    }
}
/* ------------------------------------------------------ */
void dup_vui16vector(vuint16 *X, int j0, int j1, vuint16 *Y)
/* ------------------------------------------------------ */
{
    int j;
    vuint16 x;
    
    for(j=j0; j<=j1; j++) {
        //x = vec_ld(0, &X[j]);
        //vec_st(x, 0, &Y[j]);
        x = _mm_load_si128(&X[j]);
        _mm_store_si128(&Y[j], x);
    }
}
/* ------------------------------------------------------ */
void dup_vsi16vector(vsint16 *X, int j0, int j1, vsint16 *Y)
/* ------------------------------------------------------ */
{
    int j;
    vsint16 x;
    
    for(j=j0; j<=j1; j++) {
        //x = vec_ld(0, &X[j]);
        //vec_st(x, 0, &Y[j]);
        x = _mm_load_si128(&X[j]);
        _mm_store_si128(&Y[j], x);
    }
}
/* ------------------------------------------------------ */
void dup_vui32vector(vuint32 *X, int j0, int j1, vuint32 *Y)
/* ------------------------------------------------------ */
{
    int j;
    vuint32 x;
    
    for(j=j0; j<=j1; j++) {
        //x = vec_ld(0, &X[j]);
        //vec_st(x, 0, &Y[j]);
        x = _mm_load_si128(&X[j]);
        _mm_store_si128(&Y[j], x);
    }
}
/* ------------------------------------------------------ */
void dup_vsi32vector(vsint32 *X, int j0, int j1, vsint32 *Y)
/* ------------------------------------------------------ */
{
    int j;
    vsint32 x;
    
    for(j=j0; j<=j1; j++) {
        //x = vec_ld(0, &X[j]);
        //vec_st(x, 0, &Y[j]);
        x = _mm_load_si128(&X[j]);
        _mm_store_si128(&Y[j], x);
    }
}
/* ------------------------------------------------------- */
void dup_vf32vector(vfloat32 *X, int j0, int j1, vfloat32 *Y)
/* ------------------------------------------------------- */
{
    int j;
    vfloat32 x;
    
    for(j=j0; j<=j1; j++) {
        //x = vec_ld(0, &X[j]);
        //vec_st(x, 0, &Y[j]);
        x = _mm_load_ps((float*) &X[j]);
        _mm_store_ps((float*) &Y[j], x);
    }
}
/* ------------------ */
/* --- 2D Altivec --- */
/* ------------------ */
/* --------------------------------------------------------------------- */
void dup_vui8matrix(vuint8 **X, int i0, int i1, int j0, int j1, vuint8 **Y)
/* --------------------------------------------------------------------- */
{
    int i, j;
    
    vuint8 x;
    
    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {
            
            //x = vec_ld(0, &X[i][j]);
            //vec_st(x, 0, &Y[i][j]);
            x = _mm_load_si128(&X[i][j]);
            _mm_store_si128(&Y[i][j], x);
        }
    }
}
/* --------------------------------------------------------------------- */
void dup_vsi8matrix(vsint8 **X, int i0, int i1, int j0, int j1, vsint8 **Y)
/* --------------------------------------------------------------------- */
{
    int i, j;
    
    vsint8 x;
    
    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {
            
            //x = vec_ld(0, &X[i][j]);
            //vec_st(x, 0, &Y[i][j]);
            x = _mm_load_si128(&X[i][j]);
            _mm_store_si128(&Y[i][j], x);
        }
    }
}
/* ------------------------------------------------------------------------ */
void dup_vui16matrix(vuint16 **X, int i0, int i1, int j0, int j1, vuint16 **Y)
/* ------------------------------------------------------------------------ */
{
    int i, j;
    
    vuint16 x;
    
    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {
            
            //x = vec_ld(0, &X[i][j]);
            //vec_st(x, 0, &Y[i][j]);
            x = _mm_load_si128(&X[i][j]);
            _mm_store_si128(&Y[i][j], x);
        }
    }
}
/* ------------------------------------------------------------------------ */
void dup_vsi16matrix(vsint16 **X, int i0, int i1, int j0, int j1, vsint16 **Y)
/* ------------------------------------------------------------------------ */
{
    int i, j;
    
    vsint16 x;
    
    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {
            
            //x = vec_ld(0, &X[i][j]);
            //vec_st(x, 0, &Y[i][j]);
            x = _mm_load_si128(&X[i][j]);
            _mm_store_si128(&Y[i][j], x);
        }
    }
}
/* ------------------------------------------------------------------------ */
void dup_vui32matrix(vuint32 **X, int i0, int i1, int j0, int j1, vuint32 **Y)
/* ------------------------------------------------------------------------ */
{
    int i, j;
    
    vuint32 x;
    
    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {
            
            //x = vec_ld(0, &X[i][j]);
            //vec_st(x, 0, &Y[i][j]);
            x = _mm_load_si128(&X[i][j]);
            _mm_store_si128(&Y[i][j], x);
        }
    }
}
/* ------------------------------------------------------------------------ */
void dup_vsi32matrix(vsint32 **X, int i0, int i1, int j0, int j1, vsint32 **Y)
/* ------------------------------------------------------------------------ */
{
    int i, j;
    
    vsint32 x;
    
    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {
            
            //x = vec_ld(0, &X[i][j]);
            //vec_st(x, 0, &Y[i][j]);
            x = _mm_load_si128(&X[i][j]);
            _mm_store_si128(&Y[i][j], x);
        }
    }
}
/* ------------------------------------------------------------------------- */
void dup_vf32matrix(vfloat32 **X, int i0, int i1, int j0, int j1, vfloat32 **Y)
/* ------------------------------------------------------------------------- */
{
    int i, j;
    
    vfloat32 x;
    
    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {
            
            //x = vec_ld(0, &X[i][j]);
            //vec_st(x, 0, &Y[i][j]);
            x = _mm_load_ps((float*)&X[i][j]);
            _mm_store_ps((float*) &Y[i][j], x);
        }
    }
}

