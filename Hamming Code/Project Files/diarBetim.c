#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

void char2bits(int c, int bits[8]) {
  int j = 7;
  for (int i = 0; i < 8; i++, j--) {
    if (c & (1 << i)) {
      bits[j] = 1;
    } else {
      bits[j] = 0;
    }
  }
}

int bits2char(int* arr) {
  int ch = 0;

  for (int i = 0; i < 8; i++) {
    ch *= 2;
    ch += arr[i];
  }
  return ch;
}

int main(int argc, char* argv[]){
  FILE *outfile, *infileP1, *infileP2, *infileD1, *infileP3, *infileD2, *infileD3, *infileD4;
  int hamming[7], hamming2[7], outputChar[8];
  int charP1[8], charP2[8], charD1[8], charP3[8], charD2[8], charD3[8], charD4[8];
  int P1get, P2get, D1get, P3get, D2get, D3get, D4get;

  int size;
  char *filename;
  char filename2[50], part0[50], part1[50], part2[50], part3[50], part4[50], part5[50], part6[50];

  int errorPlace1, errorPlace2, checkP1, checkP2, checkP4, checkP11, checkP12, checkP14;
  int c;
  bool foundError1, foundError2;
  
  while ((c = getopt(argc, argv, "f:s:")) != -1) {
    switch (c) {
    case 'f':
      filename = optarg;
      break;
    case 's':
      size = atoi(optarg);
      break;
    }
   }
   
  infileP1 = fopen(strcat(strcpy(part0, filename), ".part0"), "r");
  infileP2 = fopen(strcat(strcpy(part1, filename), ".part1"), "r");
  infileD1 = fopen(strcat(strcpy(part2, filename), ".part2"), "r");
  infileP3 = fopen(strcat(strcpy(part3, filename), ".part3"), "r");
  infileD2 = fopen(strcat(strcpy(part4, filename), ".part4"), "r");
  infileD3 = fopen(strcat(strcpy(part5, filename), ".part5"), "r");
  infileD4 = fopen(strcat(strcpy(part6, filename), ".part6"), "r");
  outfile  = fopen(strcat(strcpy(filename2, filename), ".2"), "w");
  
  for(int i = 0; i < (size/4); i++){

    P1get = fgetc(infileP1);
    P2get = fgetc(infileP2);
    D1get = fgetc(infileD1);
    P3get = fgetc(infileP3);
    D2get = fgetc(infileD2);
    D3get = fgetc(infileD3);
    D4get = fgetc(infileD4);
    
    char2bits(P1get, charP1);
    char2bits(P2get, charP2);
    char2bits(D1get, charD1);
    char2bits(P3get, charP3);
    char2bits(D2get, charD2);
    char2bits(D3get, charD3);
    char2bits(D4get, charD4);

    for(int k = 0; k < 8; k+=2){
      
      errorPlace1 = 0;
      foundError1 = false;
      hamming[0] = charP1[k];
      hamming[1] = charP2[k];
      hamming[2] = charD1[k];
      hamming[3] = charP3[k];
      hamming[4] = charD2[k];
      hamming[5] = charD3[k];
      hamming[6] = charD4[k];

      errorPlace2 = 0;
      foundError2 = false;
      hamming2[0] = charP1[k+1];
      hamming2[1] = charP2[k+1];
      hamming2[2] = charD1[k+1];
      hamming2[3] = charP3[k+1];
      hamming2[4] = charD2[k+1];
      hamming2[5] = charD3[k+1];
      hamming2[6] = charD4[k+1];
      
      checkP1 = (hamming[2] ^ hamming[4] ^ hamming[6]);
      checkP2 = (hamming[2] ^ hamming[5] ^ hamming[6]);
      checkP4 = (hamming[4] ^ hamming[5] ^ hamming[6]);
      if(checkP1 != hamming[0]) {errorPlace1 += 1; foundError1 = true;}
      if(checkP2 != hamming[1]) {errorPlace1 += 2; foundError1 = true;}
      if(checkP4 != hamming[3]) {errorPlace1 += 4; foundError1 = true;}
      if(errorPlace1) ((hamming[errorPlace1-1] == 0) ? (hamming[errorPlace1-1] = 1) : (hamming[errorPlace1-1] = 0));

      checkP11 = (hamming2[2] ^ hamming2[4] ^ hamming2[6]);
      checkP12 = (hamming2[2] ^ hamming2[5] ^ hamming2[6]);
      checkP14 = (hamming2[4] ^ hamming2[5] ^ hamming2[6]);
      if(checkP11 != hamming2[0]) {errorPlace2 += 1; foundError2 = true;}
      if(checkP12 != hamming2[1]) {errorPlace2 += 2; foundError2 = true;}
      if(checkP14 != hamming2[3]) {errorPlace2 += 4; foundError2 = true;}
      if(errorPlace2) ((hamming2[errorPlace2-1] == 0) ? (hamming2[errorPlace2-1] = 1) : (hamming2[errorPlace2-1] = 0));

      outputChar[0] = hamming[2];
      outputChar[1] = hamming[4];
      outputChar[2] = hamming[5];
      outputChar[3] = hamming[6];
      outputChar[4] = hamming2[2];
      outputChar[5] = hamming2[4];
      outputChar[6] = hamming2[5];
      outputChar[7] = hamming2[6];
      
      fputc(bits2char(outputChar), outfile);
    }
    
  }

  fclose(outfile);
  fclose(infileP1);
  fclose(infileP2);
  fclose(infileD1);
  fclose(infileP3);
  fclose(infileD2);
  fclose(infileD3);
  fclose(infileD4);
  
  return 0;
}
