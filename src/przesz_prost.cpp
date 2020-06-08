#include "przesz_prost.hh"

bool przesz_prost::czy_kolizja(const Wektor3D &srodek_drona, double promien) const
{
    std::cout << "srodek_drona[0] < przesuniecie[0] - promien - dlugosc / 2: " << srodek_drona[0] << " - " << przesuniecie[0] << " - " << promien << " - " << szerokosc << std::endl;
    Wektor3D pow_prostopadloscian(szerokosc + 2 * promien, dlugosc + 2 * promien, wysokosc + 2 * promien);
    Wektor3D polowa_pow_prost = pow_prostopadloscian*0.5;
    return (((srodek_drona[0] > przesuniecie[0] - polowa_pow_prost[0]) && (srodek_drona[0] < przesuniecie[0] + polowa_pow_prost[0])) &&
            ((srodek_drona[1] > przesuniecie[1] - polowa_pow_prost[1]) && (srodek_drona[1] < przesuniecie[1] + polowa_pow_prost[1])) &&
            ((srodek_drona[2] > przesuniecie[2] - polowa_pow_prost[2]) && (srodek_drona[0] < przesuniecie[2] + polowa_pow_prost[2])));
}