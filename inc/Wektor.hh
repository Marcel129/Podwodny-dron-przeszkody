#ifndef WEKTOR_HH
#define WEKTOR_HH

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include "rozmiar.h"
using namespace std;

template <typename TYP, int ROZMIAR>
class Wektor
{
protected:
  TYP tablica[ROZMIAR];

public:
  Wektor();
  Wektor(TYP a);
  Wektor(TYP moja_tab[]);

  const TYP &operator[](int ind) const; //get
  TYP &operator[](int ind);             //set

  Wektor operator*(const TYP &mnoznik) const;  //mnożenie wektora przez liczbe
  Wektor operator*(const Wektor &)const;       //iloczyn wektorowy
  Wektor operator/(const TYP &dzielnik) const; //dzielenie wektora przez liczbe
  Wektor operator+(const Wektor &W2) const;    //dodawanie dwoch wektorow
  Wektor operator-(const Wektor &W2) const;    //odejmowanie dwoch wektorow
  bool operator!=(const Wektor &W2) const;     //porównanie 2 wektorów
  TYP iloczyn_skalarny(const Wektor &) const;
  double dlugosc() const;
};

template <typename TYP, int ROZMIAR>
std::istream &operator>>(std::istream &strWej, Wektor<TYP, ROZMIAR> &W);
template <typename TYP, int ROZMIAR>
std::ostream &operator<<(std::ostream &strWyj, const Wektor<TYP, ROZMIAR> &W);

class Wektor3D : public Wektor<double, ROZ>
{
protected:
  static int liczba_stworzonych;
  static int liczba_istniejacych;

public:
  Wektor3D(double x, double y, double z);
  Wektor3D(const Wektor3D &W);
  Wektor3D(const Wektor<double, ROZ> &W) : Wektor<double, ROZ>(W)
  {
    ++liczba_istniejacych;
    ++liczba_stworzonych;
  }
  Wektor3D() : Wektor<double, ROZ>()
  {
    ++liczba_istniejacych;
    ++liczba_stworzonych;
  }
  ~Wektor3D() { --liczba_istniejacych; }

  static int Liczba_Istniejacych() { return liczba_istniejacych; }
  static int Liczba_Stworzonych() { return liczba_stworzonych; }
};

#endif
