#include "Wektor.hh"

int Wektor3D::liczba_istniejacych(0);
int Wektor3D::liczba_stworzonych(0);

template <typename TYP, int ROZMIAR>
std::istream &operator>>(std::istream &strWej, Wektor<TYP, ROZMIAR> &W)
{
  for (int i = 0; i < ROZMIAR; i++)
    strWej >> W[i];
  return strWej;
}

template <typename TYP, int ROZMIAR>
std::ostream &operator<<(std::ostream &strWyj, const Wektor<TYP, ROZMIAR> &W)
{
  for (int i = 0; i < ROZMIAR; i++)
  {
    strWyj << std::setw(MIEJSCE) << std::setprecision(PRECYZJA) << W[i];
    if (i + 1 < ROZMIAR)
      strWyj << "\t";
  }
  std::cout << std::endl;
  return strWyj;
}

template <typename TYP, int ROZMIAR>
Wektor<TYP, ROZMIAR>::Wektor() //konstruktor bezparametryczny
{
  int i = 0;
  for (TYP &tab : tablica)
  {
    tab = 0;
    ++i;
  }
}

template <typename TYP, int ROZMIAR>
Wektor<TYP, ROZMIAR>::Wektor(TYP a) //konstruktor bezparametryczny
{
  int i = 0;
  for (TYP &tab : tablica)
  {
    tab = a;
    ++i;
  }
}

template <typename TYP, int ROZMIAR>
bool Wektor<TYP, ROZMIAR>::operator!=(const Wektor<TYP, ROZMIAR> &W2) const
{
  for (int i = 0; i < ROZMIAR; ++i)
  {
    if (tablica[i] != W2[i])
      return true;
  }
  return false;
}

template <typename TYP, int ROZMIAR>
Wektor<TYP, ROZMIAR>::Wektor(TYP moja_tab[]) //konstruktor parametryczny
{
  int i = 0;
  for (TYP &tab : tablica)
  {
    tab = moja_tab[i];
    ++i;
  }
}

template <typename TYP, int ROZMIAR>
const TYP &Wektor<TYP, ROZMIAR>::operator[](int ind) const //get
{
  if (ind < 0 || ind > ROZMIAR)
  {
    std::cerr << "Przekroczenie zakresu" << std::endl;
    exit(1);
  }
  return tablica[ind];
}

template <typename TYP, int ROZMIAR>
TYP &Wektor<TYP, ROZMIAR>::operator[](int ind) //set
{
  if (ind < 0 || ind > ROZMIAR)
  {
    std::cerr << "Przekroczenie zakresu" << std::endl;
    exit(1);
  }
  return tablica[ind];
}

template <typename TYP, int ROZMIAR>
Wektor<TYP, ROZMIAR> Wektor<TYP, ROZMIAR>::operator*(const TYP &mnoznik) const //mnozenie wektora przez liczbe
{
  Wektor<TYP, ROZMIAR> W;

  for (int i = 0; i < ROZMIAR; ++i)
    W.tablica[i] = mnoznik * this->tablica[i];

  return W;
}

template <typename TYP, int ROZMIAR>
Wektor<TYP, ROZMIAR> Wektor<TYP, ROZMIAR>::operator*(const Wektor<TYP, ROZMIAR> &W) const //iloczyn wektorowy
{
  if (ROZMIAR != 3)
  {
    std::cout << "Błąd: nie można obliczyć iloczynu wektorowego." << std::endl;
    exit(1);
  }

  Wektor<TYP, ROZMIAR> wynik;
  for (int i = 0; i < 3; ++i) //oblicz elementy wektora błędu używając Sarrusa
    wynik[i] = tablica[(i + 2) % 3] * W[(i + 1) % 3] - tablica[(i + 1) % 3] * W[(i + 2) % 3];

  return wynik;
}

template <typename TYP, int ROZMIAR>
Wektor<TYP, ROZMIAR> Wektor<TYP, ROZMIAR>::operator/(const TYP &dzielnik) const //dzielenie wektora przez liczbe
{
  Wektor<TYP, ROZMIAR> W;
  if (dzielnik != 0)
  {
    for (int i = 0; i < ROZMIAR; ++i)
      W.tablica[i] = this->tablica[i] / dzielnik;
  }
  else
  {
    std::cout << "Błąd:dzielenie przez 0" << std::endl;
    exit(1);
  }
  return W;
}

template <typename TYP, int ROZMIAR>
Wektor<TYP, ROZMIAR> Wektor<TYP, ROZMIAR>::operator+(const Wektor &W2) const //dodawanie dwoch wektorow
{
  Wektor<TYP, ROZMIAR> W;

  for (int i = 0; i < ROZMIAR; ++i)
    W.tablica[i] = this->tablica[i] + W2.tablica[i];

  return W;
}

template <typename TYP, int ROZMIAR>
TYP Wektor<TYP, ROZMIAR>::iloczyn_skalarny(const Wektor &W) const
{
  TYP wynik(0);
  for (int i = 0; i < ROZMIAR; ++i)
  {
    wynik = wynik + tablica[i] * W[i];
  }
  return wynik;
}

template <typename TYP, int ROZMIAR>
Wektor<TYP, ROZMIAR> Wektor<TYP, ROZMIAR>::operator-(const Wektor &W2) const //odejmowanie dwoch wektorow
{
  Wektor<TYP, ROZMIAR> W;
  for (int i = 0; i < ROZMIAR; ++i)
    W.tablica[i] = this->tablica[i] - W2.tablica[i];

  return W;
}

Wektor3D::Wektor3D(double x, double y, double z)
{
  tablica[0] = x;
  tablica[1] = y;
  tablica[2] = z;
  ++liczba_istniejacych;
  ++liczba_stworzonych;
}

Wektor3D::Wektor3D(const Wektor3D &W)
{
  tablica[0] = W[0];
  tablica[1] = W[1];
  tablica[2] = W[2];
  ++liczba_istniejacych;
  ++liczba_stworzonych;
}


