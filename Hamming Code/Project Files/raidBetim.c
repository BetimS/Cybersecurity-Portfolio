#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void char2bits(char c, unsigned char bits[8]) {
  for (int i = 0; i < 8; i ++) {
    bits[i] = (c >> (7 - i)) & 1;
  }
 }

unsigned char bits2char(int* arr) {
  int ch = 0;

  for (int i = 0; i < 8; i++) {
    ch *= 2;
    ch += arr[i];
  }
  return (unsigned char) ch;
}

int main(int argc, char* argv[]){
  FILE *infile, *outfileP1, *outfileP2, *outfileD1, *outfileP3, *outfileD2, *outfileD3, *outfileD4;
  infile = fopen(argv[2], "r");
  char part0[50];
  char part1[50];
  char part2[50];
  char part3[50];
  char part4[50];
  char part5[50];
  char part6[50];
  outfileP1 = fopen(strcat(strcpy(part0, argv[2]), ".part0"), "w");
  outfileP2 = fopen(strcat(strcpy(part1, argv[2]), ".part1"), "w");
  outfileD1 = fopen(strcat(strcpy(part2, argv[2]), ".part2"), "w");
  outfileP3 = fopen(strcat(strcpy(part3, argv[2]), ".part3"), "w");
  outfileD2 = fopen(strcat(strcpy(part4, argv[2]), ".part4"), "w");
  outfileD3 = fopen(strcat(strcpy(part5, argv[2]), ".part5"), "w");
  outfileD4 = fopen(strcat(strcpy(part6, argv[2]), ".part6"), "w");
  char c;
  int count = 0;

  while(c != EOF){
    int P1[8];
    int P2[8];
    int D1[8];
    int P3[8];
    int D2[8];
    int D3[8];
    int D4[8];
    for(int i = 0; i < 8; i+=2){
      c = fgetc(infile);
      unsigned char bits[8];
      unsigned int intBits[8];

      char2bits(c, bits);

      for (int i = 0; i < 8; i++) {
        intBits[i] = (int)bits[i];
      }
      P1[i] = (intBits[0] ^ intBits[1] ^ intBits[3]);
      P1[i+1] = (intBits[4] ^ intBits[5] ^ intBits[7]);
      P2[i] = (intBits[0] ^ intBits[2] ^ intBits[3]);
      P2[i+1] = (intBits[4] ^ intBits[6] ^ intBits[7]);
      D1[i] = intBits[0];
      D1[i+1] = intBits[4];
      P3[i] = (intBits[1] ^ intBits[2] ^ intBits[3]);
      P3[i+1] = (intBits[5] ^ intBits[6] ^ intBits[7]);
      D2[i] = intBits[1];
      D2[i+1] = intBits[5];
      D3[i] = intBits[2];
      D3[i+1] = intBits[6];
      D4[i] = intBits[3];
      D4[i+1] = intBits[7];
      count++;
    }
    if(c == EOF) break;
    
    fputc(bits2char(P1), outfileP1);
    fputc(bits2char(P2), outfileP2);
    fputc(bits2char(D1), outfileD1);
    fputc(bits2char(P3), outfileP3);
    fputc(bits2char(D2), outfileD2);
    fputc(bits2char(D3), outfileD3);
    fputc(bits2char(D4), outfileD4);

  }
  fclose(infile);
  fclose(outfileP1);
  fclose(outfileP2);
  fclose(outfileD1);
  fclose(outfileP3);
  fclose(outfileD2);
  fclose(outfileD3);
  fclose(outfileD4);

  printf("%s : %d\n", argv[2], (count-4));
  return 0;
}
