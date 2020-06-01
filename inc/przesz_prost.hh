#ifndef PRZESZ_PROST_HH
#define PRZESZ_PROST_HH

#include <iostream>
#include "przeszkoda.hh"
#include "bryla.hh"
#include "dron.hh"
#include "Dr3D_gnuplot_api.hh"
#include "int_rysowania.hh"
#include "parametry_drona.hh"

using drawNS::APIGnuPlot3D;
using drawNS::Point3D;
using std::vector;

class przesz_prost : public przeszkoda, public prostopadloscian
{
public:
    przesz_prost() : prostopadloscian(){};
    przesz_prost(std::shared_ptr<drawNS::Draw3DAPI> api, double d, double s, double w, double x, double y, double z) : 
    prostopadloscian(api,d, s, w, x, y, z){};

    bool czy_kolizja(const Wektor3D &,double)const override;
};

#endif