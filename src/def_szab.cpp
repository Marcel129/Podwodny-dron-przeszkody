#include "Wektor.cpp"
#include "Macierz.cpp"
#include "rozmiar.h"

template class Wektor<double, ROZ>;
template class Macierz<double, ROZ>;
template std::istream &operator>>(std::istream &strWej, Wektor<double, ROZ> &W);
template std::ostream &operator<<(std::ostream &strWyj, const Wektor<double, ROZ> &W);
template std::istream &operator>>(std::istream &strWej, Macierz<double, ROZ> &W);
template std::ostream &operator<<(std::ostream &strWyj, const Macierz<double, ROZ> &W);

/*  SPECJALIZACJE  */
template <>
double Wektor<double, ROZ>::dlugosc() const
{
    for (int i = 0; i < ROZ; ++i)//jeśli choć 1 element wektora jest niezerowy można obliczyć jego długość
    {
        if (std::abs(tablica[i]) > 0.00000001)
        {
            double dl = 0;
            for (int a = 0; a < ROZ; ++a)
                dl += tablica[a] * tablica[a];
            dl = sqrt(dl);
            return dl;
        }
    }
    return 0;//mamy do czynienia z wektorem zerowym
}


