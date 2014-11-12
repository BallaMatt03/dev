/* ---------------- */
/* --- parser.c --- */
/* ---------------- */

/*
 * Basic Command Line Parser
 */

/*
 * Copyright (c) 1999-2009 Lionel Lacassagne, EIA, LISIF, IEF
 *
 * 1999-04-12
 * 2002-02-13 : ajout du type BOOL
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdarg.h> // va_list
#include <string.h>

#include "def.h"
#include "nrutil.h"

#include "parser.h"

/* ----------------------- */
void Error(char *format, ...)
/* ----------------------- */
/* global error handler */
{
    va_list args;
    FILE *file;
    
    va_start(args, format);
    
    file = fopen("error.txt", "wb");
    if(file == NULL) {
        fprintf (stderr,"Error : can't write error to disk\n");
    } else {
        fprintf (file,"Error\n");
        vfprintf(file, format, args);
        fprintf (file, "\n");
        fclose  (file);
    }
    fprintf (stderr, "Erreur : ");
    vfprintf(stderr, format, args);
    fprintf (stderr, "\n");
    
    va_end(args);
    
    //getchar();

  exit(-1);
}

/* ---------------------------------------------------- */
void Parser_ScanLine(FILE *file, char *line)
/* ---------------------------------------------------- */
{
  fscanf(file, scanLINE, line);
}
/* ----------------------------------------------------- */
void Parser_ScanLine2(FILE *file, char *line)
/* ----------------------------------------------------- */
{
  do {
    fscanf(file, scanLINE, line);
  } while(line[0] == '#');
}

/* ------------------------------------------------------------- */
void Parser_ScanChar(char *line, char *word, char *c)
/* ------------------------------------------------------ */
{
  //sscanf(line, scanCHAR, &c);
  sscanf("%c", c);
  Parser_WriteChar(word, *c);
}
/* -------------------------------------------------------------- */
void Parser_ScanStr(char *line, char *word, char *str)
/* -------------------------------------------------------------- */
{
  static char string[1024];
  static char c;

  /*sscanf(line, scanSTR2, string);
  sscanf(line, scanCHAR, &c);*/
  sscanf(line, "%s %c %s", string, &c, str);
  if( (strcmp(string, word) != 0) ||  (c != '=') ) {
    Error("Parser_ScanStr : %s != %s \n", string, word);
  }
  Parser_WriteStr(word, str);
}
/* ----------------------------------------------------------------- */
void Parser_ScanInt(char *line, char *word, int *integer)
/* ----------------------------------------------------------------- */
{
  static char string[1024];
  static char c;

  /*sscanf(line, scanSTR,   string);
  sscanf(line, scanCHAR, &c);
  sscanf(line, scanINT,   integer);*/

  sscanf(line, "%s %c %d", string, &c, integer);

  if( (strcmp(string, word) != 0) ||  (c != '=') ) {
    Error("Parser_ScanInt : %s %s %d\n", word, string, *integer);
  }
  Parser_WriteInt(word, *integer);
}
/* ------------------------------------------------------------------ */
void Parser_ScanFloat(char *line, char *word, float *real)
/* ------------------------------------------------------------------ */
{
  static char string[1024];
  static char c;

  /*sscanf(line, scanSTR,   string);
  sscanf(line, scanCHAR, &c);
  sscanf(line, scanINT,   integer);*/

  sscanf(line, "%s %c %f", string, &c, real);

  if( (strcmp(string, word) != 0) ||  (c != '=') ) {
    Error("Parser_ScanInt : %s %s %d\n", word, string, *real);
  }
  Parser_WriteFloat(word, *real);
}
/* ------------------------------------------------------------- */
void Parser_ScanBOOL(char *line, char *word, BOOL *b)
/* ------------------------------------------------------------- */
{
  
  static char str[1024];
  
  Parser_ScanStr(line, word, str);

  if( strcmp(str, "FALSE") == 0 ) {
    *b = FALSE;
  } else {
    if( strcmp(str, "TRUE" ) == 0 ) {
      *b = TRUE;
    } else {
      Error("Parser_ScanBOOL %s %s \n", word, str);
    }
  }
  Parser_WriteBOOL(word, *b);
}
/* ------------------------------- */
void Parser_Reset(void)
/* ------------------------------- */
{
  FILE *f = fopen("parser.txt", "wb");
  fclose(f);
}
/* ------------------------------------------------- */
void Parser_WriteChar(char *word, char c)
/* ------------------------------------------------- */
{
  FILE *f = fopen("parser.txt", "ab");

  fprintf(f, "%s = %c\n", word, c);
  fclose(f);
}
/* --------------------------------------------------- */
void Parser_WriteStr(char *word, char *str)
/* --------------------------------------------------- */
{
  FILE *f = fopen("parser.txt", "ab");

  fprintf(f, "%s = %s\n", word, str);
  fclose(f);
}
/* ----------------------------------------------------- */
void Parser_WriteInt(char *word, int integer)
/* ----------------------------------------------------- */
{
  FILE *f = fopen("parser.txt", "ab");

  fprintf(f, "%s = %d\n", word, integer);
  fclose(f);
}
/* ------------------------------------------------------ */
void Parser_WriteFloat(char *word, float real)
/* ------------------------------------------------------ */
{
  FILE *f = fopen("parser.txt", "ab");

  fprintf(f, "%s = %f\n", word, real);
  fclose(f);
}
/* ------------------------------------------------- */
void Parser_WriteBOOL(char *word, BOOL b)
/* ------------------------------------------------- */
{
  FILE *f = fopen("parser.txt", "ab");

  if(b==TRUE)  fprintf(f, "%s = TRUE\n", word);
  if(b==FALSE) fprintf(f, "%s = FALSE\n", word);
  
  fclose(f);
}
