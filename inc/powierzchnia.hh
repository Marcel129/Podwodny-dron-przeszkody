#ifndef POWIERZCHNIA_HH
#define POWIERZCHNIA_HH

#include "int_rysowania.hh"
#include "Dr3D_gnuplot_api.hh"
#include "bryla.hh"
#include "przeszkoda.hh"

using drawNS::APIGnuPlot3D;
using drawNS::Point3D;
using std::vector;

#define MIN_ROZ_WYS 0.5 //wywoluje nierownosci powierzchni

class powierzchnia : public int_rysowania, public przeszkoda
{
    double wysokosc_polozenia;

public:
    powierzchnia(std::shared_ptr<drawNS::Draw3DAPI> wskazane_api, double wys,std::string zadany_kolor = "grey")
    {
        wysokosc_polozenia = wys;
        kolor=zadany_kolor;
        api = wskazane_api;
        ID = -20;
    };
    void draw();
    bool czy_kolizja(const Wektor3D & srodek,double promien_drona) const override
    {
        if (wysokosc_polozenia > 0) //jeśli rozptrujemy tafle wody
        {
            if (srodek[2] > wysokosc_polozenia) //zwróć true jeśli środek drona wypłynie nad powierzchnie
                return true;
            else
                return false;
        }
        else //jeśli rozpatrujemy dno
        {
            if (srodek[2] < (wysokosc_polozenia + promien_drona/2)) //zwróć true jeśli środek drona wypłynie nad powierzchnie
                return true;
            else
                return false;
        }
    }
};

#endif