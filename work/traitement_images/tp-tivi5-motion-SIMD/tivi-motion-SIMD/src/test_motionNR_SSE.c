/* --------------------------- */
/* --- test_motionNR_SSE.c --- */
/* --------------------------- */

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

//#include "mvt.h"
//#include "mvt_sse.h"

#ifdef OPENMP
#include <omp.h>
#endif

/* ------------------------------------------------ */
void main_FrameDifference_SSE2(int argc, char *argv[])
/* ------------------------------------------------ */
{
    char *src_path;
    char *dst_path;
    
    char *filename;
    
    char cfilenameI[1024];
    char cfilenameO[1024];
    char cfilenameE[1024];
    
    int  i0,  i1,  j0,  j1; // indices scalaires
    int vi0, vi1, vj0, vj1; // indices vectoriels
    
    int width, height;
    //int pitch;
    
    int ndigit;
    
    vuint8 **vI0, **vI1, **vO, **vE, **vSwap; // SIMD matrix
    uint8  **wI0, **wI1, **wO, **wE, **wSwap; // scalar wrappers
    
    vuint8 **vII0, **vII1, **vEE;
    uint8  **wII0, **wII1, **wEE;

    int t, tstart, tstop, tstep;
    
    int seuil;
    
    /// exemple pour PC
    src_path = "d:/Sequences/car3/"; 
    filename = "car_3";
    dst_path = "../SD_SSE2/";
    
    // exemple pour Mac/Linux
    src_path = "/home/matthias/car3/"; 
    filename = "car_3";
    dst_path = "/home/matthias/car3/";
    
    ndigit   = 3;
    width    = 320;
    height   = 240;
    
    tstart = 0;
    tstop  = 100;
    tstep  = 1;
    
    printf("src_path = %s\n", src_path);
    printf("filename = %s\n", filename);
    printf("dst_path = %s\n", dst_path);
    
    
    // attention la borne j1 est 16 fois plus petite
    // car indices pour variables SIMD et non variable scalaire
    
    i0 = 0; i1 = height-1;
    j0 = 0; j1 = width-1;
    
    
    vi0 = 0; vi1 = height-1;
    vj0 = 0; vj1 = width/16-1;
    
    // SIMD allocation
    vI0 = vui8matrix (vi0, vi1, vj0, vj1);
    vI1 = vui8matrix (vi0, vi1, vj0, vj1);
    vO  = vui8matrix (vi0, vi1, vj0, vj1);
    vE  = vui8matrix (vi0, vi1, vj0, vj1);
    
    vII0 = vui8matrix (vi0, vi1, vj0, vj1);
    vII1 = vui8matrix (vi0, vi1, vj0, vj1);
    vEE  = vui8matrix (vi0, vi1, vj0, vj1);

    wI0 = (uint8**) vI0;
    wI1 = (uint8**) vI1;
    wO  = (uint8**) vO;
    wE  = (uint8**) vE;
    
    wII0 = (uint8**) vII0;
    wII1 = (uint8**) vII1;
    wEE  = (uint8**) vEE;

    seuil = 25;
    
    generate_path_filename_k_ndigit_extension(src_path, filename, tstart, ndigit, "pgm", cfilenameI);
    puts(cfilenameI);
    MLoadPGM_ui8matrix (cfilenameI, i0, i1, j0, j1, wI1); // Multiple-Load without allocating matrix
    
    PreProcessing_SSE(vI1, vII1,  vi0, vi1, vj0, vj1);
    FrameDifference_FirstStep_SSE(vII0, vII1, vO, vE, seuil, vi0, vi1, vj0, vj1);
    
    for(t=tstart+1; t<=tstop; t+=tstep) {
        // generate filename of current image
        generate_path_filename_k_ndigit_extension(src_path, filename, t, ndigit, "pgm", cfilenameI); puts(cfilenameI);
        
        // load current image
        MLoadPGM_ui8matrix (cfilenameI, i0, i1, j0, j1, wI0);
        
        PreProcessing_SSE(vI0, vII0,  vi0, vi1, vj0, vj1);
        FrameDifference_1Step_SSE(vII0, vII1, vO, vE, seuil, vi0, vi1, vj0, vj1);
        PostProcessing_SSE(vE, vEE,  vi0, vi1, vj0, vj1);

        //generate filename for output
        generate_path_filename_k_ndigit_extension(dst_path, "J_", t, ndigit, "pgm", cfilenameO); SavePGM_ui8matrix(wII0, i0, i1, j0, j1, cfilenameO);
        generate_path_filename_k_ndigit_extension(dst_path, "O_", t, ndigit, "pgm", cfilenameO); SavePGM_ui8matrix(wO,   i0, i1, j0, j1, cfilenameO);
        generate_path_filename_k_ndigit_extension(dst_path, "E_", t, ndigit, "pgm", cfilenameE); SavePGM_ui8matrix(wE,   i0, i1, j0, j1, cfilenameE);
        generate_path_filename_k_ndigit_extension(dst_path, "F_", t, ndigit, "pgm", cfilenameE); SavePGM_ui8matrix(wEE,  i0, i1, j0, j1, cfilenameE);

        printf("%s -> %s %s\n", cfilenameI, cfilenameO, cfilenameE);
        
                        
        // pointeur rotation (avoid images copies)
        vSwap = vI1; vI1 = vI0; vI0 = vSwap;
        wSwap = wI1; wI1 = wI0; wI0 = wSwap;
        
        vSwap = vII1; vII1 = vII0; vII0 = vSwap;
        wSwap = wII1; wII1 = wII0; wII0 = wSwap;

    }
    
    free_vui8matrix(vI0, vi0, vi1, vj0, vj1);
    free_vui8matrix(vI1, vi0, vi1, vj0, vj1);
    free_vui8matrix(vO,  vi0, vi1, vj0, vj1);
    free_vui8matrix(vE,  vi0, vi1, vj0, vj1);
    
    free_vui8matrix(vII0, vi0, vi1, vj0, vj1);
    free_vui8matrix(vII1, vi0, vi1, vj0, vj1);
    free_vui8matrix(vEE,  vi0, vi1, vj0, vj1);

    return;
}
/* ------------------------------------------- */
void main_SigmaDelta_SSE2(int argc, char *argv[])
/* ------------------------------------------- */
{
    char *src_path;
    char *dst_path;
    char *filename;
    
    char cfilenameI  [1024];
    char cfilenameM  [1024];
    char cfilenameO  [1024];
    char cfilenameV  [1024];
    char cfilenameE  [1024];
    //char cfilenameEr [1024];
    //char cfilenameEd [1024];
    //char cfilenameEe [1024];
    
    int i0, i1, j0, j1;
    //int b=1; // border
    //int c8 = card_vuint8(); // cardinal
    //int pitch;
    
    int k; // nombre d'ecart type
    
    // -- indices sans bord -- //
    int si0, si1, sj0, sj1; // scalar indices
    int vi0, vi1, vj0, vj1; // vector indices
    //int mi0, mi1, mj0, mj1; // memory (bounded) indices
    
    
    int width, height;
    int ndigit;
    
    vuint8 **vI, **vII, **vM, **vO, **vV, **vE, **vEE;
    uint8  **wI, **wII, **wM, **wO, **wV, **wE, **wEE;
    
    int t, tstart, tstop, tstep;
    
    //double t0, t1, dt=0, cpp;
    
    int save = 1;
    
    // ------------ //
    // --- car3 --- //
    // ------------ //
    
    // exemple pour PC
    src_path = "d:/Sequences/car3/"; 
    filename = "car_3";
    dst_path = "../SD_SSE2/";
    
    // exemple pour Mac/Linux
    src_path = "/home/matthias/car3/"; 
    filename = "car_3";
    dst_path = "/home/matthias/car3/";
    
    ndigit   = 3;
    
    width  = 320;
    height = 240;
    
    tstart = 0;
    tstop  = 199;
    tstep  = 1;
    
    //tstop  = 30; // pour debug
    printf("src_path = %s\n", src_path);
    printf("filename = %s\n", filename);
    printf("dst_path = %s\n", dst_path);
    
    // ------------------ //
    // -- Calcul index -- //
    // ------------------ //
    
    i0 = 0; i1 = height-1;
    j0 = 0; j1 = width-1;
    
    vi0 = 0; vi1 = height-1;
    vj0 = 0; vj1 = width/16-1;
    
    // SIMD allocation
    vI   = vui8matrix(vi0,  vi1,  vj0,  vj1);
    vII  = vui8matrix(vi0,  vi1,  vj0,  vj1);
    vM   = vui8matrix(vi0,  vi1,  vj0,  vj1);
    vO   = vui8matrix(vi0,  vi1,  vj0,  vj1);
    vV   = vui8matrix(vi0,  vi1,  vj0,  vj1);
    vE   = vui8matrix(vi0,  vi1,  vj0,  vj1);
    vEE  = vui8matrix(vi0,  vi1,  vj0,  vj1);
    
    wI = (uint8**) vI;
    wII = (uint8**) vII;
    wM = (uint8**) vM;
    wO = (uint8**) vO;
    wV = (uint8**) vV;
    wE = (uint8**) vE;
    wEE = (uint8**) vEE;

    // -------------------- //
    // -- Initialisation -- //
    // -------------------- //
    
    k = 4; // nombre d'ecart type

    generate_path_filename_k_ndigit_extension  (src_path, filename, tstart, ndigit, "pgm", cfilenameI);
    MLoadPGM_ui8matrix(cfilenameI, i0, i1, j0, j1, wI);
    
    SigmaDelta_FirstStep_SSE(vI, vM, vO, vV, vE, k, vi0, vi1, vj0, vj1);
    
    if(save) {
        generate_path_filename_k_ndigit_extension(dst_path, "I_", tstart, ndigit, "pgm", cfilenameI); SavePGM_ui8matrix(wI,  i0, i1, j0, j1, cfilenameI);
        generate_path_filename_k_ndigit_extension(dst_path, "J_", tstart, ndigit, "pgm", cfilenameI); SavePGM_ui8matrix(wII, i0, i1, j0, j1, cfilenameI);
        generate_path_filename_k_ndigit_extension(dst_path, "M_", tstart, ndigit, "pgm", cfilenameM); SavePGM_ui8matrix(wM,  i0, i1, j0, j1, cfilenameM);
        generate_path_filename_k_ndigit_extension(dst_path, "O_", tstart, ndigit, "pgm", cfilenameO); SavePGM_ui8matrix(wO,  i0, i1, j0, j1, cfilenameO);
        generate_path_filename_k_ndigit_extension(dst_path, "V_", tstart, ndigit, "pgm", cfilenameV); SavePGM_ui8matrix(wV,  i0, i1, j0, j1, cfilenameV);
        generate_path_filename_k_ndigit_extension(dst_path, "E_", tstart, ndigit, "pgm", cfilenameE); SavePGM_ui8matrix(wE,  i0, i1, j0, j1, cfilenameE);
        generate_path_filename_k_ndigit_extension(dst_path, "F_", tstart, ndigit, "pgm", cfilenameE); SavePGM_ui8matrix(wEE, i0, i1, j0, j1, cfilenameE);
    }
    
    // ------------ //
    // -- boucle -- //
    // ------------ //
    
    for(t=tstart+1; t<=tstop; t+= tstep) {
        
        printf("-- %d / %d --\n", t, tstop);
        
        generate_path_filename_k_ndigit_extension  (src_path, filename, t, ndigit, "pgm", cfilenameI);
        MLoadPGM_ui8matrix(cfilenameI, si0, si1, sj0, sj1, wI);
        
        PreProcessing_SSE(vI, vII,  vi0, vi1, vj0, vj1);
        SigmaDelta_1Step_SSE(vI, vM, vO, vV, vE, k, vi0, vi1, vj0, vj1); 
        PostProcessing_SSE(vE, vEE,  vi0, vi1, vj0, vj1);
        
        if(save) {
            generate_path_filename_k_ndigit_extension(dst_path, "I_", t, ndigit, "pgm", cfilenameI); SavePGM_ui8matrix(wI,  i0, i1, j0, j1, cfilenameI);
            generate_path_filename_k_ndigit_extension(dst_path, "J_", t, ndigit, "pgm", cfilenameI); SavePGM_ui8matrix(wII, i0, i1, j0, j1, cfilenameI);
            generate_path_filename_k_ndigit_extension(dst_path, "M_", t, ndigit, "pgm", cfilenameM); SavePGM_ui8matrix(wM,  i0, i1, j0, j1, cfilenameM);
            generate_path_filename_k_ndigit_extension(dst_path, "O_", t, ndigit, "pgm", cfilenameO); SavePGM_ui8matrix(wO,  i0, i1, j0, j1, cfilenameO);
            generate_path_filename_k_ndigit_extension(dst_path, "V_", t, ndigit, "pgm", cfilenameE); SavePGM_ui8matrix(wV,  i0, i1, j0, j1, cfilenameE);
            generate_path_filename_k_ndigit_extension(dst_path, "E_", t, ndigit, "pgm", cfilenameE); SavePGM_ui8matrix(wE,  i0, i1, j0, j1, cfilenameE);
            generate_path_filename_k_ndigit_extension(dst_path, "F_", t, ndigit, "pgm", cfilenameE); SavePGM_ui8matrix(wEE, i0, i1, j0, j1, cfilenameE);
        }
    }
    
    // SIMD allocation
    free_vui8matrix(vI,  vi0,  vi1,  vj0,  vj1);
    free_vui8matrix(vII, vi0,  vi1,  vj0,  vj1);
    free_vui8matrix(vM,  vi0,  vi1,  vj0,  vj1);
    free_vui8matrix(vO,  vi0,  vi1,  vj0,  vj1);
    free_vui8matrix(vV,  vi0,  vi1,  vj0,  vj1);
    free_vui8matrix(vE,  vi0,  vi1,  vj0,  vj1);
    free_vui8matrix(vEE, vi0,  vi1,  vj0,  vj1);
    
    
    return;
}
// -------------------------------------------
void test_motionNR_SSE(int argc, char *argv[])
// -------------------------------------------
{
    printf("test_motionNR_SSE\n");
    main_FrameDifference_SSE2(argc, argv);
    main_SigmaDelta_SSE2(argc, argv);
}
