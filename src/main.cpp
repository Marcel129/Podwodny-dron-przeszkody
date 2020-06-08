#include <iostream>
#include <unistd.h>
#include "Macierz.hh"
#include "Dr3D_gnuplot_api.hh"
#include "dron.hh"
#include "powierzchnia.hh"
#include "parametry_drona.hh"
#include "przesz_prost.hh"
#include "int_rysowania.hh"

using drawNS::APIGnuPlot3D;
using drawNS::Point3D;
using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main()
{
  cout << "START\nLiczba stworzonych wektorów: " << Wektor3D::Liczba_Stworzonych() << endl
       << "Liczba istniejących wektorów: " << Wektor3D::Liczba_Istniejacych() << endl;
  cout << "Liczba stworzonych brył: " << bryla::Liczba_Stworzonych() << endl
       << "Liczba istniejących brył: " << bryla::Liczba_Istniejacych() << endl;
  Wektor3D WT, W0; //zmienna na przechowanie parametrów translacji wprowadzonych przez użytkownika
  std::shared_ptr<drawNS::Draw3DAPI> api(new APIGnuPlot3D(-SZEROKOSC_BASENU, DLUGOSC_BASENU, -WYSOKOSC_BASENU, SZEROKOSC_BASENU, -DLUGOSC_BASENU, WYSOKOSC_BASENU, -1));
  //włacza gnuplota, pojawia się scena, odswiezanie po każdym pojawieniu sie nowego konturu

  vector<std::shared_ptr<przeszkoda>> przeszkody;

  std::shared_ptr<przesz_prost> bloczek(new przesz_prost(api, 4, -2, 4, -6, 3, -4, "yellow"));
  std::shared_ptr<powierzchnia> dno(new powierzchnia(api, -9.5));
  std::shared_ptr<dron> drugi_dron(new dron(api, D_DRONA, S_DRONA, W_DRONA, 5, 5, -5, "blue"));
  std::shared_ptr<dron> pierwszy_dron(new dron(api, D_DRONA, S_DRONA, W_DRONA, -5, -5, 5));
  std::shared_ptr<dron> dron_sterowany(new dron(api, D_DRONA, S_DRONA, W_DRONA, -5, -5, -5));
  std::shared_ptr<powierzchnia> lustro_wody(new powierzchnia(api, 8.5, "blue"));
  przeszkody.push_back(bloczek);
  przeszkody.push_back(lustro_wody);
  przeszkody.push_back(dno);
  przeszkody.push_back(drugi_dron);
  przeszkody.push_back(pierwszy_dron);

  vector<std::shared_ptr<dron>> lista_dronow;
  lista_dronow.push_back(pierwszy_dron);
  lista_dronow.push_back(drugi_dron);

  bloczek->draw();
  dno->draw();
  lustro_wody->draw();
  drugi_dron->draw();
  pierwszy_dron->draw();

  char x; //zmienna pomocnicza do sterowania switchem
  double kat;
  char z = 'z';

  do
  {
    cout << "Wybierz drona, którym chcesz sterować:\ng - zielony\nb - niebieski\nq - wyjscie\n"
         << endl;
    cin >> z;
    switch (z)
    {
    case 'g':
      dron_sterowany = lista_dronow[0];
      break;
    case 'b':
      dron_sterowany = lista_dronow[1];
      break;
    default:
      cout << "Nie ma takiego drona.\n"
           << endl;
      break;
    }
  } while (z != 'q' && z != 'g' && z != 'b');

  do
  {
    if (cin.fail() == false)
    {
      cout << "Liczba stworzonych wektorów: " << Wektor3D::Liczba_Stworzonych() << endl
           << "Liczba istniejących wektorów: " << Wektor3D::Liczba_Istniejacych() << endl;
      cout << "Liczba stworzonych brył: " << bryla::Liczba_Stworzonych() << endl
           << "Liczba istniejących brył: " << bryla::Liczba_Istniejacych() << endl;
      cout << "Co chcesz zrobić z dronem?\nt - Przesuń\nr - Obróć\nc- Wybierz drona\nq- Zakończ\n";
      cin >> x;
      switch (x)
      {
      case 't':
        double odleg, kat_wznoszenia;
        cout << "Podaj odleglosci i kat wznoszenia: " << endl;
        cin >> odleg >> kat_wznoszenia;
        dron_sterowany->move(odleg, kat_wznoszenia, WT, przeszkody);
        dron_sterowany->draw();
        cout << "Aktualne polozenie drona: " << dron_sterowany->get_przes() << endl;
        break;
      case 'r':
        cout << "Podaj kat obrotu:  " << endl;
        cin >> kat;
        dron_sterowany->rotate('z', kat);
        dron_sterowany->draw();
        break;
      case 'c':
        cout << "Wybierz drona, którym chcesz sterować:\ng - zielony\nb - niebieski\n"
             << endl;
        char znak;
        cin >> znak;
        switch (znak)
        {
        case 'g':
          dron_sterowany = lista_dronow[0];
          break;
        case 'b':
          dron_sterowany = lista_dronow[1];
          break;
        default:
          cout << "Nie ma takiego drona.\n"
               << endl;
          break;
        }
        break;
      case 'q':
        cout << "Zakończono pracę." << endl;
        exit(1);
        break;
      default:
        cout << "Nie ma takiej opcji." << endl;
        break;
      }
    }
  } while (cin.fail() == false);
}
