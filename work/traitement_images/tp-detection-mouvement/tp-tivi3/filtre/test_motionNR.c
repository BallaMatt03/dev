/* ----------------------- */
/* --- test_motionNR.c --- */
/* ----------------------- */

/*
 * Copyright (c) 2011-2012 Lionel Lacassagne, all rights reserved
 * University Paris Sud 11
 */

#include <stdio.h>
#include <math.h>

#include "def.h"
#include "nrutil.h"
#include "morphoNR.h"

#include "parser.h"
#include "sequence.h"

#include "motionNR.h"

#include "my_paths.h"

// ---------------------------------------
void test_basic_FD(int argc, char* argv[])
// ---------------------------------------
{   
    char *src_path;
    char *dst_path;
    char *sequence_filename;
    
    char cfilenameD[1024];
    char cfilenameS[1024];
    
    BOOL save, save_debug;
    
    int i0, i1, j0, j1;
    int width, height;
    int ndigit;
    
    uint8 **I0, **I1, **D, **S, **swap;
    uint8 threshold = 10; // valeur de seuil: parametre a optimiser
    int t, tstart, tstop, tstep;
    
    //char complete_filename[1024];
    char *filename;
    char *complete_filename;
    tsSequence *sequence;
    
    puts("==================================");
    puts("=== test_basic_FrameDifference ===");
    puts("==================================");
    
    // ------------------------------------- //    
    // -- Configuration et initialisation -- //
    // ------------------------------------- //
    
    if(argc<=1) {
        // sequence par defaut
        puts("il faut indiquer ici le path pour lire le fichier de configuration de la sequence ...");
        puts("il faut aussi indiquer *dans* le fichier les src_path et dst_path ...");
        sequence_filename = "d:/code/config/car3_win.txt";   
        sequence_filename = "/Volumes/Delta1/Users/lacas/Code/TP/image/filtre/car3_mac.txt";   
    } else {
        // sequence passee en ligne de commande
        sequence_filename = argv[1];
    }
    
    sequence = Sequence_pConstructor();
    Sequence_Parse_File(sequence_filename, sequence);
    
    src_path = Sequence_Get_SrcPath(sequence); // check if exist
    filename = Sequence_Get_Filename(sequence);
    dst_path = Sequence_Get_DstPath(sequence);  // check if exist
    ndigit   = Sequence_Get_NDigit(sequence);
    
    width  = Sequence_Get_Width(sequence);
    height = Sequence_Get_Height(sequence);
    
    save       = Sequence_Get_Save(sequence);
    save_debug = Sequence_Get_SaveDebug(sequence); // not used in that version
    
    printf("src_path = %s\n", src_path);
    printf("filename = %s\n", filename);
    printf("dst_path = %s\n", dst_path);
    
    i0 = 0; i1 = height-1;
    j0 = 0; j1 = width-1;
    
    // ---------------- //    
    // -- Allocation -- //
    // ---------------- //
    
    I0 = ui8matrix(i0, i1, j0, j1);
    I1 = ui8matrix(i0, i1, j0, j1);
    D  = ui8matrix(i0, i1, j0, j1);
    S  = ui8matrix(i0, i1, j0, j1);
    
    // -------------------- //    
    // -- Initialisation -- //
    // -------------------- //
    
    tstart = Sequence_Get_TStart(sequence);
    tstop  = Sequence_Get_TStop(sequence);
    tstep  = Sequence_Get_TStep(sequence);
    
    complete_filename = Sequence_Get_CompleteFilename(sequence);
    Sequence_Next(sequence);
    
    MLoadPGM_ui8matrix(complete_filename, i0, i1, j0, j1, I0);
    
    FrameDifference_FirstStep(I0, I1, i0, i1, j0, j1, D, S);
    
    if(save_debug) {
        generate_path_filename_k_ndigit_extension(dst_path, "D_", tstart, ndigit, "pgm", cfilenameD); SavePGM_ui8matrix(D, i0, i1, j0, j1, cfilenameD);
    }
    if(save) {
        generate_path_filename_k_ndigit_extension(dst_path, "S_", tstart, ndigit, "pgm", cfilenameS); SavePGM_ui8matrix(S, i0, i1, j0, j1, cfilenameS);
    }
    swap = I1; I1 = I0; I0 = swap;
    
    // -------------------------- //    
    // -- Boucle de traitement -- //
    // -------------------------- //
    
    for(t=tstart+1; t<=tstop; t+= tstep) {
        
        printf("--- %d ---\n", t);
        FrameDifference_1Step(I0, I1, i0, i1, j0, j1, D, S, threshold);
        
        if(save_debug) {
            generate_path_filename_k_ndigit_extension(dst_path, "D_", t, ndigit, "pgm", cfilenameD); SavePGM_ui8matrix(D, i0, i1, j0, j1, cfilenameD);
        }
        if(save) {
            generate_path_filename_k_ndigit_extension(dst_path, "S_", t, ndigit, "pgm", cfilenameS); SavePGM_ui8matrix(S, i0, i1, j0, j1, cfilenameS);
        }
        swap = I1; I1 = I0; I0 = swap;
        complete_filename = Sequence_Get_CompleteFilename(sequence); MLoadPGM_ui8matrix(complete_filename, i0, i1, j0, j1, I0);
        
        Sequence_Next(sequence);
    }
    
    // ------------------- //    
    // -- Desallocation -- //
    // ------------------- //
    
    free_ui8matrix(I0, i0, i1, j0, j1);
    free_ui8matrix(I1, i0, i1, j0, j1);
    free_ui8matrix(D,  i0, i1, j0, j1);
    free_ui8matrix(S,  i0, i1, j0, j1);
    
    Sequence_pDestructor(sequence);
    
    return;
}
// ----------------------------------------
void test_robust_FD(int argc, char* argv[])
// ----------------------------------------
{
    // A COMPLETER
    // en s'inspirant du precedent
}
// ---------------------------------------
void test_basic_SD(int argc, char* argv[])
// ---------------------------------------
{
    char *src_path;
    char *dst_path;
    char *sequence_filename;
    
    char cfilenameM[1024];
    char cfilenameO[1024];
    char cfilenameV[1024];
    char cfilenameE[1024];
    
    BOOL save, save_debug;
    
    int i0, i1, j0, j1;
    int width, height;
    int ndigit;
    
    uint8 **I, **M, **O, **V, **E;
    int k = 3; // nombre d'ecar-type pour le test de SD
    int t, tstart, tstop, tstep;
    
    //char complete_filename[1024];
    char *filename;
    char *complete_filename;
    tsSequence *sequence;
    
    puts("============================");
    puts("=== test_basic_SigmaDeta ===");
    puts("============================");
    
    // ------------------------------------- //    
    // -- Configuration et initialisation -- //
    // ------------------------------------- //
    
    if(argc<=1) {
        // sequence par defaut
        puts("il faut indiquer ici le path pour lire le fichier de configuration de la sequence ...");
        puts("il faut aussi indiquer *dans* le fichier les src_path et dst_path ...");
        sequence_filename = "d:/code/config/car3_win.txt";   
        sequence_filename = "/Volumes/Delta1/Users/lacas/Code/TP/image/filtre/car3_mac.txt";   
    } else {
        // sequence passee en ligne de commande
        sequence_filename = argv[1];
    }
    
    sequence = Sequence_pConstructor();
    Sequence_Parse_File(sequence_filename, sequence);
    
    src_path = Sequence_Get_SrcPath(sequence); // check if exist
    filename = Sequence_Get_Filename(sequence);
    dst_path = Sequence_Get_DstPath(sequence);  // check if exist
    ndigit   = Sequence_Get_NDigit(sequence);
    
    width  = Sequence_Get_Width(sequence);
    height = Sequence_Get_Height(sequence);
    
    save       = Sequence_Get_Save(sequence);
    save_debug = Sequence_Get_SaveDebug(sequence); // not used in that version
    
    printf("src_path = %s\n", src_path);
    printf("filename = %s\n", filename);
    printf("dst_path = %s\n", dst_path);
    
    i0 = 0; i1 = height-1;
    j0 = 0; j1 = width-1;
    
    // ---------------- //    
    // -- Allocation -- //
    // ---------------- //
    
    I = ui8matrix(i0, i1, j0, j1);
    M = ui8matrix(i0, i1, j0, j1);
    O = ui8matrix(i0, i1, j0, j1);
    V = ui8matrix(i0, i1, j0, j1);
    E = ui8matrix(i0, i1, j0, j1);
    
    // -------------------- //    
    // -- Initialisation -- //
    // -------------------- //
    
    tstart = Sequence_Get_TStart(sequence);
    tstop  = Sequence_Get_TStop(sequence);
    tstep  = Sequence_Get_TStep(sequence);
    
    complete_filename = Sequence_Get_CompleteFilename(sequence);
    Sequence_Next(sequence);
    
    MLoadPGM_ui8matrix(complete_filename, i0, i1, j0, j1, I);
    
    SigmaDelta_FirstStep(I, i0, i1, j0, j1, M, O, V, E); // V=1 instead of 0
    
    if(save_debug) {
        generate_path_filename_k_ndigit_extension(dst_path, "M_", tstart, ndigit, "pgm", cfilenameM); SavePGM_ui8matrix(M, i0, i1, j0, j1, cfilenameM);
        generate_path_filename_k_ndigit_extension(dst_path, "O_", tstart, ndigit, "pgm", cfilenameO); SavePGM_ui8matrix(O, i0, i1, j0, j1, cfilenameO);
        generate_path_filename_k_ndigit_extension(dst_path, "V_", tstart, ndigit, "pgm", cfilenameV); SavePGM_ui8matrix(E, i0, i1, j0, j1, cfilenameV);
    }
    if(save) {
        generate_path_filename_k_ndigit_extension(dst_path, "E_", tstart, ndigit, "pgm", cfilenameE); SavePGM_ui8matrix(V, i0, i1, j0, j1, cfilenameE);
    }
  
    // -------------------------- //    
    // -- Boucle de traitement -- //
    // -------------------------- //
    
    for(t=tstart+1; t<=tstop; t+= tstep) {
        
        printf("--- %d ---\n", t);
        SigmaDelta_1Step(I, i0, i1, j0, j1, M, O, V, E, k);
        
        if(save_debug) {
            generate_path_filename_k_ndigit_extension(dst_path, "M_", t, ndigit, "pgm", cfilenameM); SavePGM_ui8matrix(M, i0, i1, j0, j1, cfilenameM);
            generate_path_filename_k_ndigit_extension(dst_path, "O_", t, ndigit, "pgm", cfilenameO); SavePGM_ui8matrix(O, i0, i1, j0, j1, cfilenameO);
            generate_path_filename_k_ndigit_extension(dst_path, "V_", t, ndigit, "pgm", cfilenameV); SavePGM_ui8matrix(E, i0, i1, j0, j1, cfilenameE);
        }
        if(save) {
            generate_path_filename_k_ndigit_extension(dst_path, "E_", t, ndigit, "pgm", cfilenameE); SavePGM_ui8matrix(V, i0, i1, j0, j1, cfilenameV);
        }
        
        complete_filename = Sequence_Get_CompleteFilename(sequence); MLoadPGM_ui8matrix(complete_filename, i0, i1, j0, j1, I);
        
        Sequence_Next(sequence);
    }
    
    // ------------------- //    
    // -- Desallocation -- //
    // ------------------- //
    
    free_ui8matrix(I, i0, i1, j0, j1);
    free_ui8matrix(M, i0, i1, j0, j1);
    free_ui8matrix(O, i0, i1, j0, j1);
    free_ui8matrix(V, i0, i1, j0, j1);
    free_ui8matrix(E, i0, i1, j0, j1);
    
    Sequence_pDestructor(sequence);
    
    return;
}
// ----------------------------------------
void test_robust_SD(int argc, char* argv[])
// ----------------------------------------
{  
    // A COMPLETER
    // en s'inspirant du precedent
}
// --------------------------------------
int test_motionNR(int argc, char* argv[])
// --------------------------------------
{
    puts("=====================");
    puts("=== test_motionNR ===");
    puts("=====================");
    
    puts("decommenter au fur et a mesure ...");
    test_basic_FD(argc, argv); // Frame Difference en stand alone
    //test_robust_FD(argc, argv); // version robuste 1) avec post-traitement, 2) avec pre-traitement
    
    //test_basic_SD(argc, argv); // Sigma-Delta en stand alone
    //test_robust_SD(argc, argv); //version robuste 1) avec post-traitement, 2) avec pre-traitement
    
    return 0;
}
