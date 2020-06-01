#ifndef BRYLA_HH
#define BRYLA_HH

#include "Macierz.hh"
#include "Wektor.hh"
#include "Dr3D_gnuplot_api.hh"
#include "int_rysowania.hh"
#include "parametry_drona.hh"

using drawNS::APIGnuPlot3D;
using drawNS::Point3D;
using std::vector;

class bryla : public int_rysowania
{
protected:
    Wektor3D srodek, przesuniecie;
    Macierz_Obrotu orientacja;
    
    Wektor3D odsuniecie;
    Macierz_Obrotu orientacja_wlasna;

public:
    bryla(){};
    const Wektor3D &get_s() { return srodek; }
    void move(const Wektor3D &W);
};


class prostopadloscian : public bryla
{
protected:
    Wektor3D wierzcholki[8];
    double dlugosc, szerokosc, wysokosc;

public:
    prostopadloscian(){};
    prostopadloscian(std::shared_ptr<drawNS::Draw3DAPI> api, double d, double s, double w, double x, double y, double z);

    void draw(std::string zadany_kolor = "green"); //można zmienić kolor, ale nie ma obowiązku, żeby go podać

    void aktualizuj_wierzcholki(const Wektor3D &W2, const Macierz_Obrotu &M);
    void przesun(const Wektor3D &W2)
    {
        Macierz_Obrotu Macierz_jednostkowa;
        aktualizuj_wierzcholki(W2, Macierz_jednostkowa);
    }
    void obroc(const Macierz_Obrotu &M)
    {
        Wektor3D wektor_zerowy;
        aktualizuj_wierzcholki(wektor_zerowy, M);
    }

    void set_od(const Wektor3D &W) { odsuniecie = W; }
    const Wektor3D &get_od() { return odsuniecie; }
    void set_przes(const Wektor3D &W) { przesuniecie = W; }
    const Wektor3D &get_przes() { return przesuniecie; }

    const Macierz_Obrotu &get_orientation() const { return orientacja; }
    void set_orientation(const Macierz_Obrotu &M) { orientacja = M; }
    const Macierz_Obrotu &get_own_orientation() const { return orientacja_wlasna; }
    void set_own_orientation(const Macierz_Obrotu &M) { orientacja_wlasna = M; }
};

#endif
