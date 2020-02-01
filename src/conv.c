//Function Implementation File
#include "conv.h"

//Function that checks if there are enough command line arguments for convolution
void checkarg(int argnum) {
   if (argnum != 4) {
      fprintf(stderr,"\n\nNot enough or too many arguments! "); 
	  fprintf(stdout,"Please use the following command form:\n\n\t\t./conv [Input] [Input] [Output]\n\n");
      exit(1);
   }
}

int checksize(FILE *fin) {
   char buff[50];
   int size = 0;

   while (fgets(buff,50,fin)!=NULL) {
	  size++;
   }
   rewind(fin);
   return size;
}

//Function parses the input text files and sorts the data
struct TData parse(FILE *fin, struct TData In, int size) {
   char teststr[4];
   char data[50];
   int i,j,ind = 0, cnt = 1,tempi;
   float tempf;

   In.pValue = malloc(size * sizeof(float));

   fgets(data, 50, fin);
   sscanf(data,"%i %f", &In.MinIndex,&In.pValue[0]);

   for (i = 0; i < 4; i++) {
      teststr[i] = data[i];
   }

   while (ind == 0) {
      ind = 0;

      fgets(data, 50, fin);

      sscanf(data,"%i %f", &tempi, &In.pValue[cnt]);

      if (teststr[0] == data[0] && teststr[1] == data[1] && teststr[2] == data[2] && teststr[3] == data[3]) {
         ind = 1;
      }

      for (j = 0; j < 4; j++) {
         teststr[j] = data[j];
      }
      cnt++;
   }

   sscanf(data,"%i %f", &In.MaxIndex, &tempf);
   In.Points = (In.MaxIndex - In.MinIndex) + 1;

   return In;
}

//Function convolves the data and saves the caluclated data
struct TData convolve(struct TData In1, struct TData In2, struct TData Out) {
   int i,j,size,cnt;
   float temp;
   float *arr1;
   float *arr2;

   arr1 = In1.pValue;
   arr2 = In2.pValue;

   Out.MinIndex = In1.MinIndex + In2.MinIndex;
   Out.MaxIndex = In1.MaxIndex + In2.MaxIndex;

   size = In1.Points + In2.Points - 1;
   Out.Points = size;

   Out.pValue = malloc(size * sizeof(float));

   for (i=0; i < size; i++) {
      cnt = i;
      temp = 0.0;
      for (j = 0; j < In2.Points; j++) {
         if (cnt >= 0 && cnt < In1.Points) {
            temp = temp + (*(arr1 + cnt) * (*(arr2 + j)));
         }
         cnt--;
         *(Out.pValue + i) = temp;
      }
   }
   return Out;
}

//Function writes the calculated data to output file
struct TData writeout(FILE *fout, struct TData out) {
  int a;

  for (a = 0; a < out.Points; a++) {
     fprintf(fout,"%d\t%f\n",out.MinIndex + a,*(out.pValue + a));
  }
  fprintf(stdout,"\n\n\tOutput Generated Successfully\n\n");
  return out;
}

//Function closes the file pointers
void close(FILE *in1, FILE *in2, FILE *out) {
   fclose(in1);
   fclose(in2);
   fclose(out);
}
