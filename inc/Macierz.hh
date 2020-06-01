#ifndef MACIERZ_HH
#define MACIERZ_HH
#include <iostream>
#include <cmath>
#include "rozmiar.h"
#include "Wektor.hh"

/*
Plik zawiera deklaracje ogólnej klasy modelującej macierz, jak i jej bardziej szczególną postać - macierz obrotu.
*/

template <typename TYP, int ROZMIAR>
class Macierz
{
protected:
  Wektor<TYP, ROZMIAR> tablica[ROZMIAR];

public:
  Macierz();
  Macierz(Wektor<TYP, ROZMIAR> tab[])
  {
    for (int i = 0; i < ROZMIAR; i++)
      tablica[i] = tab[i];
  };
  Macierz(const Macierz<TYP, ROZMIAR> &M)
  {
    for (int i = 0; i < ROZMIAR; i++)
      tablica[i] = M[i];
  };
  Wektor<TYP, ROZMIAR> &operator[](int ind);             //set
  const Wektor<TYP, ROZMIAR> &operator[](int ind) const; //get

  Wektor<TYP, ROZMIAR> operator*(const Wektor<TYP, ROZMIAR> W) const;   //mnożenie macierzy przez wektor
  Macierz<TYP, ROZMIAR> operator*(const Macierz<TYP, ROZMIAR> M) const; //mnożenie macierzy przez macierz
  bool operator == (const Macierz<TYP, ROZMIAR> M)const;
  Macierz<TYP,ROZMIAR> inicjuj_jednostkowa();
  Macierz<TYP,ROZMIAR> macierz_odwrotna();//obliczenie macierzy odwrotnej
  
  void transponuj_macierz(void);
  TYP wyz_gauss();
};

template <typename TYP, int ROZMIAR>
std::istream &operator>>(std::istream &Strm, Macierz<TYP, ROZMIAR> &Mac);
template <typename TYP, int ROZMIAR>
std::ostream &operator<<(std::ostream &Strm, const Macierz<TYP, ROZMIAR> &Mac);

class Macierz_Obrotu : public Macierz<double, ROZ>
{
public:
  Macierz_Obrotu();
  Macierz_Obrotu(const Macierz<double, ROZ> &M) : Macierz<double, ROZ>(M){}
  Macierz_Obrotu(char os, double kat);
};

#endif
