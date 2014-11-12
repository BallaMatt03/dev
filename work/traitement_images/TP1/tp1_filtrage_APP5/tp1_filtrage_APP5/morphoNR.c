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
}
/* ----------------------------------------------------------------------------------------- */
void binary_dilation_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y)
/* ----------------------------------------------------------------------------------------- */
{
}
/* ------------------------------------------------------------------------------------------ */
void binary_closing_ui8matrix (uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y)
/* ------------------------------------------------------------------------------------------ */
{
}
/* ------------------------------------------------------------------------------------------ */
void binary_opening_ui8matrix (uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y)
/* ------------------------------------------------------------------------------------------ */
{
}
/* ---------------------------------------------------------------------------------- */
void erosion_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y)
/* ---------------------------------------------------------------------------------- */
{
}
/* ----------------------------------------------------------------------------------- */
void dilation_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y)
/* ----------------------------------------------------------------------------------- */
{
}
/* ---------------------------------------------------------------------------------- */
void closing_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y)
/* ---------------------------------------------------------------------------------- */
{
}
/* ---------------------------------------------------------------------------------- */
void opening_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y)
/* ---------------------------------------------------------------------------------- */
{
}
/* -------------------------------------------------------------------------------------------------------------- */
void alternate_sequential_filter_opening_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y)
/* -------------------------------------------------------------------------------------------------------------- */
{
}
/* -------------------------------------------------------------------------------------------------------------- */
void alternate_sequential_filter_closing_ui8matrix(uint8 **X, int i0, int i1, int j0, int j1, int radius, uint8 **Y)
/* -------------------------------------------------------------------------------------------------------------- */
{
}