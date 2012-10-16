#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#include "wave_io.h"

#define MAX_STR_LNGTH 256

#define PI 3.141592653

int main(int argc, char *argv[])
  {
  int	out;
      
  char in_name[MAX_STR_LNGTH], out_name[MAX_STR_LNGTH];
  short *wave;

  unsigned int freq_in, bits_in;
  unsigned int n_wave;
   
  struct Waveheader header;


  if ( (argc != 3) && (argc != 5) )
    {
    fprintf(stderr, "Usage: %s -i infile [-o outfile]\n", argv[0]);
    exit(1);
    }
  else
    {
    strcpy(in_name, argv[2]);
    out=0;
    out_name[0]='\0';

    if (argc == 5)
      {
      strcpy(out_name, argv[4]);
      out=1;
      }
    }
  
  fprintf(stderr,"infile: %s outfile: %s\n", in_name, out_name);

  read_wave(&wave, &n_wave, &freq_in, &bits_in, in_name, &header);
  if (out)
    write_wave(wave, n_wave, freq_in, bits_in, out_name, &header);

  free(wave);
  
  return(1);
  }

