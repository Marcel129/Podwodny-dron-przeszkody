#ifndef PRZESZKODA_HH
#define PRZESZKODA_HH

#include <iostream>
#include "Wektor.hh"

class przeszkoda {
    public:
    virtual bool czy_kolizja(const Wektor3D &,double)const=0;
};

#endif