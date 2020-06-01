#include "dron.hh"

dron::dron(std::shared_ptr<drawNS::Draw3DAPI> wskazane_api, double d, double s, double w, double x, double y, double z)
{
    prostopadloscian prost_inic(wskazane_api, d, s, w, x, y, z);
    korpus = prost_inic;
    Wirnik Wir(wskazane_api, D_WIRNIKA, S_WIRNIKA, W_WIRNIKA, 0, 0, 0);
    Wir_lewy = Wir;
    Wir_prawy = Wir;
    Wektor3D WL(x, y, z);
    Wektor3D OD_L((S_DRONA + S_WIRNIKA) / 4, (D_DRONA + D_WIRNIKA) / 2, 0), OD_P(-(S_DRONA + S_WIRNIKA) / 4, (D_DRONA + D_WIRNIKA) / 2, 0); //wektory inicjalizacyjne dla wirnikow
    Wir_prawy.set_od(OD_L);
    Wir_lewy.set_od(OD_P);
    Wir_lewy.przesun(WL);
    Wir_prawy.przesun(WL);
    Wektor3D max_odleglosc((D_DRONA / 2) + D_WIRNIKA, S_DRONA/2, W_DRONA/2); //najdalszy punkt to czubek wirnika
    promien_banki_bezpieczenstwa = max_odleglosc.dlugosc();
    przesuniecie = korpus.get_przes();
}

void dron::draw(string kolor)
{
    Wir_prawy.draw(kolor);
    Wir_lewy.draw(kolor);
    korpus.draw(kolor);
}

void dron::move(const Wektor3D &W, vector<std::shared_ptr<przeszkoda>> przeszkody)
{
    bool czy_kolizja = false;
    Wektor3D o_ile_sie_przesunal;
    if (std::abs(W[0]) > 0.000000001 || std::abs(W[1]) > 0.000000001 || std::abs(W[2]) > 0.000000001) //sprawdzenie czy wektor przesuniecia jest niezerowy
    {                                                                                                 /*
        double kat_roboczy;
        if (korpus.get_przes().dlugosc() < 0.00000000001)
        {
            Wektor3D W_pom(W[0], W[1], 0);
            kat_roboczy = acos((W[1]) / (W_pom.dlugosc()));
        }
        else{
            Wektor3D rzut_przesuniecia(korpus.get_przes()[0],korpus.get_przes()[1],0), rzut_translacji(W[0], W[1], 0);
            kat_roboczy =acos(rzut_przesuniecia.iloczyn_skalarny(rzut_translacji)/(rzut_przesuniecia.dlugosc()*rzut_translacji.dlugosc()));
        }Macierz_Obrotu mix = korpus.get_orientation();
        cout<<"orientacja\n"<<korpus.get_orientation()<<"odwrotnosc\n"<<mix.macierz_odwrotna();
        
        cout << " kat_roboczy: " << kat_roboczy << endl;
        Macierz_Obrotu zadana_orientacja('z',kat_roboczy*180);
        rotate('z',(kat_roboczy*180)/3.14);
        Macierz_Obrotu zwrot_na_kurs;
        //kat_roboczy = przesuniecie.iloczyn_skalarny(W)/(przesuniecie.dlugosc()*W.dlugosc());
        
        //cout << " przesuniecie.iloczyn_skalarny(W): " << przesuniecie.iloczyn_skalarny(W) << endl;
        cout << " korpus.przesuniecie: " << korpus.get_przes() << endl;
        cout << " przesuniecie.dlugosc(): " << korpus.get_przes().dlugosc() << endl;
        cout << " W.dlugosc(): " << W.dlugosc() << endl;
        cout << " W " << W << endl;*/
        int ilosc_krokow = W.dlugosc() / MIN_DYST;
        Wektor3D krok = W / ilosc_krokow; //oblicz wektor cząstkowy
        Wektor3D przes_wyjsciowe = przesuniecie;
        Wektor3D zapamietaj_przesuniecie_k = korpus.get_przes(); //zapamietaj aktualne polozenie
        Wektor3D zapamietaj_przesuniecie_wp = Wir_prawy.get_przes();
        Wektor3D zapamietaj_przesuniecie_wl = Wir_lewy.get_przes(); /*
        korpus.set_przes(korpus.get_przes() + W); //sprawdzam w którą stronę chce się przemieścic dron
        for (auto elem : przeszkody)
            czy_kolizja = elem->czy_kolizja(przesuniecie, get_radius())

                              korpus.set_przes(korpus.get_przes() - W);*/
        for (int i = 0; i < ilosc_krokow + 1 && !czy_kolizja; ++i)  //animuj ruch
        {
            Macierz_Obrotu M('y', 30 * (i % 3));
            Wir_lewy.set_own_orientation(M);
            Wir_prawy.set_own_orientation(M);
            przesuniecie = korpus.get_przes(); //utożsamiam przesuwanie drona z przesuwaniem korpusu
            przesun(krok);
            o_ile_sie_przesunal = o_ile_sie_przesunal + krok;
            for (auto elem : przeszkody)
                if (!czy_kolizja)
                    czy_kolizja = elem->czy_kolizja(przesuniecie, get_radius());
            if (czy_kolizja)
            {
                std::cout << "Wykryto kolizję\n";
                przesun(krok * (-1)); //cofnij wykonany krok w stronę przeszkody
                break;
            }
            draw();
        }
        korpus.set_przes(zapamietaj_przesuniecie_k); //unikam bledu numerycznego powstałego przy animacji wykonujac pojedyncze przesuniecie
        Wir_prawy.set_przes(zapamietaj_przesuniecie_wp);
        Wir_lewy.set_przes(zapamietaj_przesuniecie_wl);
        przesuniecie = przes_wyjsciowe;
    }

    if (!czy_kolizja)
        przesun(W); //przesuwam dron
    else
        przesun(o_ile_sie_przesunal);
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

bool dron::czy_kolizja(const Wektor3D &srodek_drugiego_drona, double promien) const
{
    //std::cout << "Udalo sie!" << std::endl;cout<<"srodek_drugiego_drona "<<srodek_drugiego_drona<<"  przesuniecie: "<<przesuniecie<<endl<<"srodek_drugiego_drona - przesuniecie "<<srodek_drugiego_drona - przesuniecie<<endl;
    if ((srodek_drugiego_drona - przesuniecie).dlugosc() < (2 * promien))
        return true;
    return false;
}