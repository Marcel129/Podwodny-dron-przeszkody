#ifndef WIRNIK_HH
#define WIRNIK_HH

#include "bryla.hh"
#include "Macierz.hh"
#include "Wektor.hh"
#include "parametry_drona.hh"

class Wirnik : public prostopadloscian
{
protected:

public:
    Wirnik():prostopadloscian(){};
    Wirnik(std::shared_ptr<drawNS::Draw3DAPI> wskazane_api, double d, double s, double w, double x, double y, double z):prostopadloscian(wskazane_api,d,s,w,x,y,z){};
};

#endif