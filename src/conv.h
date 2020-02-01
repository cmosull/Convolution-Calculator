//Header File
#ifndef conv_h
#define conv_h

#include <stdio.h>
#include <stdlib.h>

struct TData
{ int MinIndex,MaxIndex,Points;
  float *pValue;
};

void checkarg(int argnum);
int checksize(FILE *fin);
struct TData parse(FILE *fin, struct TData In, int size);
struct TData convolve(struct TData In1, struct TData In2, struct TData Out);
struct TData writeout(FILE *fout, struct TData out);
void close(FILE *in1, FILE *in2, FILE *out);

#endif
