#include "dron.hh"

dron::dron(std::shared_ptr<drawNS::Draw3DAPI> wskazane_api, double d, double s, double w, double x, double y, double z, std::string zadany_kolor)
{
    prostopadloscian prost_inic(wskazane_api, d, s, w, x, y, z, zadany_kolor);
    kolor = zadany_kolor;
    korpus = prost_inic;
    Wirnik Wir(wskazane_api, D_WIRNIKA, S_WIRNIKA, W_WIRNIKA, 0, 0, 0, zadany_kolor);
    Wir_lewy = Wir;
    Wir_prawy = Wir;
    Wektor3D WL(x, y, z);
    Wektor3D OD_L((S_DRONA + S_WIRNIKA) / 4, (D_DRONA + D_WIRNIKA) / 2, 0), OD_P(-(S_DRONA + S_WIRNIKA) / 4, (D_DRONA + D_WIRNIKA) / 2, 0); //wektory inicjalizacyjne dla wirnikow
    Wir_prawy.set_od(OD_L);
    Wir_lewy.set_od(OD_P);
    Wir_lewy.przesun(WL);
    Wir_prawy.przesun(WL);
    Wektor3D max_odleglosc((D_DRONA / 2) + D_WIRNIKA, S_DRONA / 2, W_DRONA / 2); //najdalszy punkt to czubek wirnika
    promien_banki_bezpieczenstwa = max_odleglosc.dlugosc();
    przesuniecie = korpus.get_przes();
}

void dron::draw()
{
    Wir_prawy.draw();
    Wir_lewy.draw();
    korpus.draw();
}

void dron::move(double zadana_odleglosc, double kat_wznoszenia, const Wektor3D &W, vector<std::shared_ptr<przeszkoda>> przeszkody)
{ /*
    bool czy_kolizja = false; 
    int ilosc_krokow = 0;
    kat_wznoszenia = kat_wznoszenia*3.14/180;//na radiany
    double x2=0.1,y2, z2;
    Wektor3D wektor_orientacji = korpus.get_sr_czola() - korpus.get_przes();
    wektor_orientacji[0] != 0 ? y2 = x2 * wektor_orientacji[1] / wektor_orientacji[0] : y2 = 0;
    z2 = tan(kat_wznoszenia)*sqrt(x2*x2+y2*y2);
    Wektor3D wek(x2, y2, z2), wektor_wyj = korpus.get_przes();
    for (; (korpus.get_przes() - wektor_wyj).dlugosc() < zadana_odleglosc; ++ilosc_krokow)
        przesun(wek); 
    Wektor3D o_ile_sie_przesunal;
    if (std::abs(W[0]) > 0.000000001 || std::abs(W[1]) > 0.000000001 || std::abs(W[2]) > 0.000000001) //sprawdzenie czy wektor przesuniecia jest niezerowy
    {
        Wektor3D wektor_orientacji = korpus.get_sr_czola() - korpus.get_przes(), zadany_wektor_orientacji = W, wek_zer_x(1, 0, 0);
        double kat_roboczy, kat_orientacji_drona, kat_zadanej_orientacji;

        Wektor3D rzut_w_orien(wektor_orientacji[0], wektor_orientacji[1], 0), rzut_zad_w_orien(zadany_wektor_orientacji[0], zadany_wektor_orientacji[1], 0);
        if (rzut_w_orien.iloczyn_skalarny(rzut_zad_w_orien) / (rzut_w_orien.dlugosc() * rzut_zad_w_orien.dlugosc() >= 0))
            kat_roboczy = acos(rzut_w_orien.iloczyn_skalarny(rzut_zad_w_orien) / (rzut_w_orien.dlugosc() * rzut_zad_w_orien.dlugosc())) * 180 / 3.14;
        else
            kat_roboczy = -acos(rzut_w_orien.iloczyn_skalarny(rzut_zad_w_orien) / (rzut_w_orien.dlugosc() * rzut_zad_w_orien.dlugosc())) * 180 / 3.14;
        //obliczam kąt obrotu w płaszczyźnie XY, stad z=0
        rotate('z', kat_roboczy);
*/
    bool czy_kolizja = false;
    int ilosc_krokow = 0;
    kat_wznoszenia = kat_wznoszenia * 3.14 / 180; //na radiany
    double x2 = MIN_DYST, y2, z2;
    Wektor3D wektor_orientacji = korpus.get_sr_czola() - korpus.get_przes();
    wektor_orientacji[0] != 0 ? y2 = x2 * wektor_orientacji[1] / wektor_orientacji[0] : y2 = 0;
    if (std::abs(std::abs(kat_wznoszenia) - 1.57) > 0.00001)
        z2 = tan(kat_wznoszenia) * sqrt(x2 * x2 + y2 * y2);
    else
    {
        z2 = zadana_odleglosc;
        x2 = 0;
        y2 = 0;
    }

    //int ilosc_krokow = W.dlugosc() / MIN_DYST;
    Wektor3D krok(x2, y2, z2); //oblicz wektor cząstkowy
    Wektor3D przes_wyjsciowe = przesuniecie, wektor_wyj = korpus.get_przes();
    Wektor3D zapamietaj_przesuniecie_k = korpus.get_przes(); //zapamietaj aktualne polozenie
    Wektor3D zapamietaj_przesuniecie_wp = Wir_prawy.get_przes();
    Wektor3D zapamietaj_przesuniecie_wl = Wir_lewy.get_przes();

    for (; (korpus.get_przes() - wektor_wyj).dlugosc() < zadana_odleglosc && !czy_kolizja; ++ilosc_krokow) //animuj ruch
    {
        Macierz_Obrotu M('y', 30 * (ilosc_krokow % 3));
        Wir_lewy.set_own_orientation(M);
        Wir_prawy.set_own_orientation(M);
        this->set_przes(korpus.get_przes()); //utożsamiam przesuwanie drona z przesuwaniem korpusu
        przesun(krok);
        for (auto elem : przeszkody)
            if (!czy_kolizja)
                czy_kolizja = elem->czy_kolizja(przesuniecie, get_radius());
        if (czy_kolizja)
        {
            std::cout << "Wykryto kolizję\n";
            przesun(krok * (-2)); //cofnij krok wykonany w stronę przeszkody
            draw();
            ilosc_krokow -= 2; //bo cofnąłem drona
            break;
        }
        draw();
    }
    korpus.set_przes(zapamietaj_przesuniecie_k); //unikam bledu numerycznego powstałego przy animacji wykonujac pojedyncze przesuniecie
    Wir_prawy.set_przes(zapamietaj_przesuniecie_wp);
    Wir_lewy.set_przes(zapamietaj_przesuniecie_wl);
    przesuniecie = przes_wyjsciowe; /*
    cout << " kat_roboczy: " << kat_roboczy << endl;
    cout << " kat_zadanej_orientacji: " << kat_zadanej_orientacji << endl;
    cout << " kat_orientacji_drona: " << kat_orientacji_drona << endl;
    cout << "wektory:\n"
         << "korpus.get_sr_czola(): " << korpus.get_sr_czola() << "\nkorpus.get_przes(): " << korpus.get_przes() << "\nwektor_orientacji" << wektor_orientacji << endl
         << "zadany_wektor_orientacji: " << zadany_wektor_orientacji << endl
         << "korpus.get_przes()-W" << korpus.get_przes() - W << endl
         << "rzut_w_orien.iloczyn_skalarny(rzut_zad_w_orien): " << rzut_w_orien.iloczyn_skalarny(rzut_zad_w_orien) << endl;
}*/

    //if (!czy_kolizja)
    przesun(krok * ilosc_krokow);
    //else
    //przesun(o_ile_sie_przesunal);
}

void dron::rotate(char os, double kat)
{
    Macierz_Obrotu obrot(os, kat);
    Macierz_Obrotu zapamietaj_orientacje_k = korpus.get_orientation();
    Macierz_Obrotu zapamietaj_orientacje_wl = Wir_lewy.get_orientation();
    Macierz_Obrotu zapamietaj_orientacje_wp = Wir_prawy.get_orientation();

    int k = 0;
    Macierz_Obrotu obrot_elementarny;
    if (kat < 0)
    {
        Macierz_Obrotu mac(os, -MIN_KAT);
        obrot_elementarny = mac;
    }
    else
    {
        Macierz_Obrotu mac(os, MIN_KAT);
        obrot_elementarny = mac;
    }

    for (double i = 0; i < abs((kat / MIN_KAT) + MIN_KAT); ++k, i += MIN_KAT) //animuj obrot
    {
        Macierz_Obrotu M('y', 30 * (k % 3));
        Wir_lewy.set_own_orientation(M);
        Wir_prawy.set_own_orientation(M);
        obroc(obrot_elementarny);
        draw();
    }
    korpus.set_orientation(zapamietaj_orientacje_k);
    Wir_prawy.set_orientation(zapamietaj_orientacje_wp);
    Wir_lewy.set_orientation(zapamietaj_orientacje_wl);
    obroc(obrot); //wykonanie właściwego obrotu
}

//operacje cząstkowe
void dron::przesun(const Wektor3D &W)
{
    korpus.przesun(W);
    Wir_prawy.przesun(W);
    Wir_lewy.przesun(W);
}

void dron::obroc(const Macierz_Obrotu &obrot)
{
    korpus.obroc(obrot);
    Wir_prawy.obroc(obrot);
    Wir_lewy.obroc(obrot);
}

bool dron::czy_kolizja(const Wektor3D &srodek_plynacego_drona, double promien) const
{
    //cout << "(this->przesuniecie - srodek_plynacego_drona).dlugosc() " << (this->przesuniecie - srodek_plynacego_drona).dlugosc() << endl;
    //cout << "this->przesuniecie " << this->przesuniecie << "srodek_plynacego_drona " << srodek_plynacego_drona << endl;
    if ((this->przesuniecie - srodek_plynacego_drona).dlugosc() > 0.000000000001) //jeśli środek drona sterowanego i drona 2 jest taki sam to znaczy, że to ten sam dron
    {
        //cout << "(this->przesuniecie - srodek_plynacego_drona).dlugosc() " << (this->przesuniecie - srodek_plynacego_drona).dlugosc() << endl;
        if ((this->przesuniecie - srodek_plynacego_drona).dlugosc() < (2 * promien))
            return true;
    }
    return false;
}