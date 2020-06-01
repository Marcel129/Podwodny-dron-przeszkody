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
  bool operator!=(const Wektor &W2)const;      //porównanie 2 wektorów
  TYP iloczyn_skalarny(const Wektor &) const;
  double dlugosc() const;
};

template <typename TYP, int ROZMIAR>
std::istream &operator>>(std::istream &strWej, Wektor<TYP, ROZMIAR> &W);
template <typename TYP, int ROZMIAR>
std::ostream &operator<<(std::ostream &strWyj, const Wektor<TYP, ROZMIAR> &W);



class Wektor3D : public Wektor<double, ROZ>
{
public:
  Wektor3D():Wektor<double, ROZ>(){}
  Wektor3D(double x,double y,double z){
    tablica[0]=x;
    tablica[1]=y;
    tablica[2]=z;
  }
  Wektor3D(const Wektor<double, ROZ> &W) : Wektor<double, ROZ>(W){};
};

#endif
