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
	const int bit=9;
	const float db=12.0;

	char in_name[MAX_STR_LNGTH], out_name[MAX_STR_LNGTH];
	short *wave;
	short *new_wave;

	unsigned int freq_in, bits_in;
	unsigned int n_wave;
	unsigned int i;
	FILE *prt;

	float a, f_wave;

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

	// --------- 2.1 output curve to ascii file --------------
	
	/*prt = fopen ("prt.txt","wt"); 

	for(i=0 ; i<n_wave;i++){ 
		fprintf(prt,"%i \n",wave[i]); 
	} 
	fclose(prt); */

	// -------- 2.1 output curve to ascii file end ----------

	// -------------- 2.4 downsampling ----------------------
	
	/*for (i=0; i < n_wave / 2; i++){
		wave[i] = wave[i*2];
	}
	freq_in /= 2;
	n_wave /= 2;*/

	// -------------- 2.4 downsampling end ------------------

	// --------------3.2 bit reduction ----------------------

	/*for (i =0; i < n_wave; i++){
		wave[i] /= 512;
		wave[i] *= 512;
	}*/
	// -------------- 3.2 bit reduction end -----------------

	// -------------- 3.4 difference signal ------------------
	/*
	new_wave = (short*)malloc(n_wave*sizeof(short));

	for(i=0; i<n_wave; i++){
		new_wave[i] = wave[i];         // keep original
		wave[i] /= pow(2.0,bit);       // quantify
		wave[i] *= pow(2.0,bit);       // boost amplitude
		wave[i] -= new_wave[i];        // error calculation
		wave[i] *= pow(2.0, 16-bit-1); // boost error
	}
	*/
	// -------------- 3.4 difference signal end --------------
	
	// -------------- Ü3 / 3.1 Klirrfaktor -------------------

	a = pow(10.0,db/20.0);
	fprintf(stderr,"%f\n", db);
	fprintf(stderr,"%f\n",a);

	for(i=0; i <n_wave; i++) {
		f_wave = wave[i];
		f_wave *= a;
		wave[i] = f_wave;
		if(f_wave > 32767){
			wave[i] = 32767;
		}
		if(f_wave < -32768){
			wave[i] = -32768;
		}
		//fprintf(stderr, "%i", wave[i]);
	}

	// -------------- Ü3 / 3.1 Klirrfaktor end ---------------
	if (out)
		write_wave(wave, n_wave, freq_in, bits_in, out_name, &header);

	free(wave);

	return(1);
}

