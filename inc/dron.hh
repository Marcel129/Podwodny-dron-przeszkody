#ifndef DRON_HH
#define DRON_HH

#include <iostream>
#include <unistd.h>
#include "bryla.hh"
#include "Dr3D_gnuplot_api.hh"
#include "int_rysowania.hh"
#include "wirnik.hh"
#include "parametry_drona.hh"
#include "przeszkoda.hh"


using drawNS::APIGnuPlot3D;
using drawNS::Point3D;
using std::cout;
using std::endl;
using std::vector;
/*!
*\brief Modeluje pojęcie drona
*
*Klasa modeluje pojęcie drona, jej atrybutami są jego korpus oraz 2 wirniki. 
*/

class dron : public prostopadloscian, public przeszkoda
{
protected:
    Wirnik Wir_prawy, Wir_lewy;
    prostopadloscian korpus;
    double promien_banki_bezpieczenstwa;
    void przesun(const Wektor3D &W); //zwykłe przesuniecie drona
    void obroc(const Macierz_Obrotu&); //zwykły obrot drona

public:
    /*!
*\brief Inicjalizuje drona o środku w zadanym punkcie
*
*Inicjalizuje drona o zadanych wymiarach o środku w zadanym punkcie. 
*Wymusza wywołanie komstruktorów elementów składowych drona: prostopałoscianu oraz wirnika.
*\param [in] wskazane_api - wskaźnik na obszar rysowania gnuplota, w którym ma znaleźć się dron 
*\param [in] d - długość tworzonego drona
*\param [in] s - szerokość tworzonego drona
*\param [in] w - wysokość tworzonego drona
*\param [in] x - X-ksowa składowa punktu środka drona
*\param [in] y - Y-kowa składowa punktu środka drona
*\param [in] z - Z-towa składowa punktu środka drona
*
*/
    dron(std::shared_ptr<drawNS::Draw3DAPI> wskazane_api, double d, double s, double w, double x, double y, double z);
    /*!
*\brief Przemieszcza drona o wskazany wektor
*
*\param [in] W - wektor, o jaki ma zostać przemieszczony dron
*/
    void move(const Wektor3D &W, vector<std::shared_ptr<przeszkoda>>); //animowany ruch drona
/*!
*\brief Obraca drona wokół wskazanej osi o wskazany kąt
*
*\param [in] os - os, wokół której ma zostać obrócony dron
*\param [in] kat - kat, o jaki ma zostać obrócony dron
*/
    void rotate(char os, double kat); //animowany obrot
/*!
*\brief Rysuje drona w jego aktualnym położeniu
*/
    void draw(string kolor = "green");
/*!
*\brief Zwraca promien sfery rezprezentującej drona podczas detekcji kolizji
*/
    double get_radius()const{return promien_banki_bezpieczenstwa;}
    Wektor3D get_przes(){return korpus.get_przes();}
    bool czy_kolizja(const Wektor3D &, double ) const override;
};

#endif