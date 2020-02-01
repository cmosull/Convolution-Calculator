//Main Driver
#include "conv.h"

int main(int argc, char *argv[]) {
   FILE *FIn1, *FIn2, *FOut;
   struct TData Input1,Input2,Output;
   int size1=0,size2=0;

   checkarg(argc);

   FIn1 = fopen(argv[1], "r");
   FIn2 = fopen(argv[2], "r");
   FOut = fopen(argv[3], "w");

   size1 = checksize(FIn1);
   size2 = checksize(FIn2);

   Input1 = parse(FIn1, Input1, size1);
   Input2 = parse(FIn2, Input2, size2);

   Output = convolve(Input1,Input2,Output);

   Output = writeout(FOut,Output);
   
   close(FIn1,FIn2,FOut);
   
   free(Input1.pValue);
   free(Input2.pValue);
   free(Output.pValue);
   
   return 0;
}
