#include "przesz_prost.hh"

bool przesz_prost::czy_kolizja(const Wektor3D &srodek_drona, double promien) const
{ //std::cout<<"srodek_drona[0] < przesuniecie[0] - promien - dlugosc / 2: "<<srodek_drona[0] <<"  "<< przesuniecie[2]<<"  " << promien<<"  "<< dlugosc / 2<<std::endl;
    return (((srodek_drona[0] > przesuniecie[0] - promien - dlugosc / 2) && (srodek_drona[0] < przesuniecie[0] + promien + dlugosc / 2)) &&
        ((srodek_drona[1] > przesuniecie[1] - promien - szerokosc / 2) && (srodek_drona[1] < przesuniecie[1] + promien + szerokosc / 2))&&
        ((srodek_drona[2] > przesuniecie[2] - promien - wysokosc / 2) && (srodek_drona[0] < przesuniecie[2] + promien + wysokosc / 2)));
}