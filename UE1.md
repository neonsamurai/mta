Aufgabe 1.1
===========


    infile: [sprache.wav](..\sprache.wav )
    outfile: 
        filelength          329550
        samples             164587
        rate                22050
        bits                16
        bytes per sample    2
        channels            1
        Bitrate =           22050Hz * 16 bits * 1 Channel = 352 kbit/s

    infile: [musik2.wav](..\musik2.wav)
    outfile:
        filelength          3323492
        samples             1661558
        rate                44100
        bits                16
        bytes per sample    4
        channels            2
        Bitrate =           44100 * 16 bits * 2 Channels = 1,411 Mbit/s

Aufgabe 2.1
===========

Hinzugefügte Code ist:

```c++
unsigned int i;
     FILE *prt; 

// ...

prt = fopen ("prt.txt","wt"); 

for(i=0; i < n_wave; i++){ 
 fprintf(prt, "%i \n", wave[i]); 
} 
fclose(prt); 
```

||[sine\_lo.wav](../sine_lo.wav) Abtastung:                       || [sine\_hi.wav](../sine_hi.wav) Abtastung:|
|0                                                                |0|
|13858                                                            |10606|
|10606                                                            |-15000| 
|-5740                                                            |10606|
|-15000                                                           |0|
|-5740                                                            |-10606|
|10606                                                            |15000|
|13858                                                            |-10606|
|0                                                                | |
|-13858                                                           | |
|-10606                                                           | |
|5740                                                             | |
|15000                                                            | |
|5740                                                             | |
|-10606                                                           | |
|-13858                                                           | |
|Frequenz: 16 kHz Abtastrate / 16 Samples * 3 Schwingungen = 3kHz |Frequenz: 16 kHz Abtastrate / 8 Samples * 3 Schwingungen = 6kHz|

Aufgabe 2.2
===========

Abtasttheorem:
--------------
> Das Abtasttheorem besagt, dass ein kontinuierliches, bandbegrenztes Signal, mit einer Minimalfrequenz von 0 Hz und einer Maximalfrequenz ![f_max](../docfiles/fmax.png) , mit einer Frequenz größer als ![2*f_max](../docfiles/2fmax.png) gleichförmig abgetastet werden muss, damit man aus dem so erhaltenen zeitdiskreten Signal das Ursprungssignal ohne Informationsverlust, aber mit unendlich großem Aufwand (d.h. unendlich viele Abtastpunkte), exakt rekonstruieren oder – mit endlichem Aufwand – beliebig genau approximieren kann. 

_Quelle: Wikipedia

Grenzfall:
----------

![Schema des Grenzfalls](../docfiles/nyquist-grenzfall.gif)

_Quelle: http://public.beuth-hochschule.de/~mixdorff/mmt1/files/schwingungslehre.pdf

Aufgabe 2.3
===========

Zu hohe Frequenzen werden von der Soundkarte per Tiefpassfilter entfernt. Der Grenzwert liegt bei ca. 20kHz.

Aufgabe 2.4
===========

Hinzugefügter Code:

```c++
// -------------- 2.4 downsampling ----------------------
for (i=0; i < n_wave / 2; i++){
 wave[i] = wave[i*2];
}
freq_in /= 2;
n_wave /= 2;

// -------------- 2.4 downsampling end ------------------
```

[sine_hi.wav](../docfiles/sine_hi.wav) erleidet durch das Downsampling Faltungsverzerrungen, da das Abtasttheorem nicht mehr eingehalten werden kann. Die Frequenz reduziert sich auf ein Drittel auf 2kHz.

[sine_lo.wav](../docfiles/sine_lo.wav) behält seine Frequenz, da ihre Ausgangsfrequenz schon niedrig genug ist um auch nach dem Downsampling das Abtasttheorem einzuhalten.

Aufgabe 3.1
===========

8 Bit = 2^8 = 256 unterschiedlie Amplitudenwerte.
16 Bit = 2^16 = 65536 unterschiedlie Amplitudenwerte.

Aufgabe 3.2
===========

Hinzugefügter Code:

```c++
// --------------3.2 bit reduction ----------------------

for (i =0; i < n_wave; i++){
 wave[i] /= 512;
 wave[i] *= 512;
}
```

Aufgabe 3.3
===========

Sprache
-------

Bitreduzierte Sprachdatei: [sprache_bitreduced.wav](../docfiles/sprache_bitreduced.wav)

Merkliche Qualitätsverringerung tritt bei 8-bit Reduktion auf.
Das Quantisierungsgeräusch äußert sich in abgehackter Sprache, wobei jeweils Anfang und Ende von Worten verloren gehen.

Musik
-----
Bitreduzierte Musikdatei: [musik_bitreduced.wav](../docfiles/musik_bitreduced.wav)

Merkliche Qualitätsverringerung tritt bei 9-bit Reduktion auf.
Das Quantisierungsgeräusch äußert sich in einem permanenten Hintergrundrauschen.

Aufgabe 3.4
===========

Hinzugefügter Code:

```c++
// -------------- 3.4 difference signal ------------------
const int bit=9;
short *new_wave;

// [...]

new_wave = (short*)malloc(n_wave*sizeof(short));

for(i=0; i < n_wave; i++){
 new_wave[i] = wave[i];
 wave[i] /= pow(2.0,bit);
 wave[i] *= pow(2.0,bit);
 wave[i] -= new_wave[i];
 wave[i] *= pow(2.0, 16-bit-1);
}

// -------------- 3.4 difference signal end --------------
```

Sprache
-------

Plot der Bitreduktion (8 Bit):

![Plot der bitreduzierten Sprachdatei](../docfiles/sprache-bitred-8bit.jpg)

Plot des Differenzsignals:

![Plot der ber bitreduzierten Sprachdatei mit Differenzsignal](../docfiles/sprache_bitreduced-diff-8bit.wav)

Bitreduzierte Sprachdatei mit Differnezsignal: [sprache_bitreduced-diff-8bit.wav](../docfiles/sprache_bitreduced-diff-8bit.wav)

Musik
-----

Plot der Bitreduktion (9 Bit):

![Plot der bitreduzierten Musikdatei](../docfiles/musik-bitred-9bit.jpg)

Plot des Differenzsignals:

![Plot der bitreduzierten Musikdatei mit Differenzsignal](../docfiles/musik-bitred-9bit-diff.jpg)

Bitreduzierte Musikdatei mit Differenzsignal: [musik_bitreduced-diff-9bit.wav](../docfiles/musik_bitreduced-diff-9bit.wav)
