#include "bryla.hh"

int bryla::liczba_istniejacych(0);
int bryla::liczba_stworzonych(0);

bryla::bryla(const bryla &B)
{
    srodek = B.srodek;
    przesuniecie = B.przesuniecie;
    orientacja = B.orientacja;
    odsuniecie = B.odsuniecie;
    orientacja_wlasna = B.orientacja_wlasna;

    ++liczba_stworzonych;
    ++liczba_istniejacych;
};

bryla::bryla()
{
    kolor = "green";
    ++liczba_stworzonych;
    ++liczba_istniejacych;
};

prostopadloscian::prostopadloscian(std::shared_ptr<drawNS::Draw3DAPI> w_api, double d, double s, double w, double x, double y, double z, std::string zadany_kolor)
{
    ++liczba_stworzonych;
    ++liczba_istniejacych;

    ID = -20;
    kolor = zadany_kolor;
    Macierz_Obrotu M_jednostkowa;
    orientacja = orientacja_wlasna = M_jednostkowa;
    api = w_api;
    dlugosc = d;
    szerokosc = s;
    wysokosc = w;
    Wektor3D WT(x, y, z), wz;
    przesuniecie = wz;
    Wektor3D W(szerokosc, dlugosc, wysokosc);
    W = W * 0.5;
    srodek_czola[0] = srodek[0];
    srodek_czola[1] = srodek[1] - dlugosc / 2;
    srodek_czola[2] = srodek[2];
    wierzcholki[0][0] = srodek[0] + W[0];
    wierzcholki[0][1] = srodek[1] - W[1];
    wierzcholki[0][2] = srodek[2] - W[2];
    wierzcholki[1][0] = srodek[0] + W[0];
    wierzcholki[1][1] = srodek[1] + W[1];
    wierzcholki[1][2] = srodek[2] - W[2];
    wierzcholki[2][0] = srodek[0] - W[0];
    wierzcholki[2][1] = srodek[1] + W[1];
    wierzcholki[2][2] = srodek[2] - W[2];
    wierzcholki[3][0] = srodek[0] - W[0];
    wierzcholki[3][1] = srodek[1] - W[1];
    wierzcholki[3][2] = srodek[2] - W[2];
    wierzcholki[4][0] = srodek[0] + W[0];
    wierzcholki[4][1] = srodek[1] - W[1];
    wierzcholki[4][2] = srodek[2] + W[2];
    wierzcholki[5][0] = srodek[0] + W[0];
    wierzcholki[5][1] = srodek[1] + W[1];
    wierzcholki[5][2] = srodek[2] + W[2];
    wierzcholki[6][0] = srodek[0] - W[0];
    wierzcholki[6][1] = srodek[1] + W[1];
    wierzcholki[6][2] = srodek[2] + W[2];
    wierzcholki[7][0] = srodek[0] - W[0];
    wierzcholki[7][1] = srodek[1] - W[1];
    wierzcholki[7][2] = srodek[2] + W[2];
    przesun(WT);
}

void prostopadloscian::draw()
{
    usun(); //usunięcie poprzedniego widoku drona
    //rysowanie drona o zadanych wymiarach
    ID = api->draw_polyhedron(vector<vector<Point3D>>{{drawNS::Point3D(wierzcholki[0][0], wierzcholki[0][1], wierzcholki[0][2]),
                                                       drawNS::Point3D(wierzcholki[1][0], wierzcholki[1][1], wierzcholki[1][2]),
                                                       drawNS::Point3D(wierzcholki[2][0], wierzcholki[2][1], wierzcholki[2][2]),
                                                       drawNS::Point3D(wierzcholki[3][0], wierzcholki[3][1], wierzcholki[3][2]),
                                                       drawNS::Point3D(wierzcholki[0][0], wierzcholki[0][1], wierzcholki[0][2])},
                                                      {drawNS::Point3D(wierzcholki[4][0], wierzcholki[4][1], wierzcholki[4][2]),
                                                       drawNS::Point3D(wierzcholki[5][0], wierzcholki[5][1], wierzcholki[5][2]),
                                                       drawNS::Point3D(wierzcholki[6][0], wierzcholki[6][1], wierzcholki[6][2]),
                                                       drawNS::Point3D(wierzcholki[7][0], wierzcholki[7][1], wierzcholki[7][2]),
                                                       drawNS::Point3D(wierzcholki[4][0], wierzcholki[4][1], wierzcholki[4][2])}},
                              kolor);
    api->redraw();
}

void prostopadloscian::aktualizuj_wierzcholki(const Wektor3D &W2, const Macierz_Obrotu &M) //domyslnie nie obracaj i nie przesuwaj
{
    orientacja = M * orientacja;
    przesuniecie = W2 + przesuniecie;
    Wektor3D W(szerokosc, dlugosc, wysokosc);
    W = W * 0.5;
    srodek_czola[0] = srodek[0];
    srodek_czola[1] = srodek[1] - dlugosc / 2;
    srodek_czola[2] = srodek[2];
    wierzcholki[0][0] = srodek[0] + W[0];
    wierzcholki[0][1] = srodek[1] - W[1];
    wierzcholki[0][2] = srodek[2] - W[2];
    wierzcholki[1][0] = srodek[0] + W[0];
    wierzcholki[1][1] = srodek[1] + W[1];
    wierzcholki[1][2] = srodek[2] - W[2];
    wierzcholki[2][0] = srodek[0] - W[0];
    wierzcholki[2][1] = srodek[1] + W[1];
    wierzcholki[2][2] = srodek[2] - W[2];
    wierzcholki[3][0] = srodek[0] - W[0];
    wierzcholki[3][1] = srodek[1] - W[1];
    wierzcholki[3][2] = srodek[2] - W[2];
    wierzcholki[4][0] = srodek[0] + W[0];
    wierzcholki[4][1] = srodek[1] - W[1];
    wierzcholki[4][2] = srodek[2] + W[2];
    wierzcholki[5][0] = srodek[0] + W[0];
    wierzcholki[5][1] = srodek[1] + W[1];
    wierzcholki[5][2] = srodek[2] + W[2];
    wierzcholki[6][0] = srodek[0] - W[0];
    wierzcholki[6][1] = srodek[1] + W[1];
    wierzcholki[6][2] = srodek[2] + W[2];
    wierzcholki[7][0] = srodek[0] - W[0];
    wierzcholki[7][1] = srodek[1] - W[1];
    wierzcholki[7][2] = srodek[2] + W[2];

    for (int i = 0; i < 8; ++i)
        wierzcholki[i] = orientacja * (orientacja_wlasna * wierzcholki[i] + get_od()) + przesuniecie;
    srodek_czola = orientacja * (orientacja_wlasna * srodek_czola + get_od()) + przesuniecie;
}
