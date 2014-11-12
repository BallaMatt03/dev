// ------------- //
// --- mvt.h --- //
// ------------- //

#ifndef _MVT_H_
#define _MVT_H_

#ifdef __cplusplus
extern "C" {
#endif
    
void FrameDifference(byte **I0, byte **I1, byte **O, int i0, int i1, int j0, int j1);
void Threshold(byte **X, byte seuil, byte valeur, byte **Y, int i0, int i1, int j0, int j1);
void Density(uint8 **X, int seuil, uint8 **Y, int i0, int i1, int j0, int j1);
    
void main_FrameDifference(int argc, char *argv[]);
void main_SigmaDelta(int argc, char *argv[]);
    
#ifdef __cplusplus
}
#endif

#endif // _MVT_H_

