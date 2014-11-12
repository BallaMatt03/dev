/* -------------- */
/* --- main.c --- */
/* -------------- */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "def.h"
#include "nrutil.h"
#include "timers_b.h"

#include "vdef.h"
#include "vnrutil.h"

#include "test_motionNR.h"
#include "test_motionNR_SSE.h"

#ifdef OPENMP
#include <omp.h>
#endif

/* ---------------- */
void init_openmp(void)
/* ---------------- */
{
    //printf("FREQ = %5.2f GHz\n", FREQ/1e9);
#ifdef OPENMP
	puts("--> OpenMP Actif\n");
#endif

}
/* -------------------------------- */
int main(int argc, const char *argv[])
/* -------------------------------- */
{
	printf("Hello, world !\n");
    init_openmp();
    
    //test_motionNR(argc, argv);
    test_motionNR_SSE(argc, argv);
    
    return 0;
}
