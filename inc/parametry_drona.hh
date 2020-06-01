#ifndef PARAMETRY_DRONA_HH
#define PARAMETRY_DRONA_HH

#include <sys/types.h>

#define MIN_DYST 0.1 //minimalna odległość, o jaką zostanie przesunięty dron przy rysowaniu
#define MIN_KAT 1   //minimalna kąt, o jaką zostanie obrócony dron przy rysowaniu
#define SZEROKOSC_BASENU 10
#define DLUGOSC_BASENU 10
#define WYSOKOSC_BASENU 10
#define S_DRONA 3
#define D_DRONA 5
#define W_DRONA 3
#define D_WIRNIKA 1
#define S_WIRNIKA 2
#define W_WIRNIKA 2

const useconds_t czas_zwloki = 1;         //ze względu na typ stała globalna zamiast #define, reguluje czas odświeżania grafiki, czas w us(mikrosekundach)
const useconds_t czas_zwloki_rotacja = 100; //ze względu na typ stała globalna zamiast #define, reguluje czas odświeżania grafiki, czas w us(mikrosekundach)

#endif