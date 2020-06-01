#include <iostream>
#include <unistd.h>
#include "Macierz.hh"
#include "Dr3D_gnuplot_api.hh"
#include "dron.hh"
#include "powierzchnia.hh"
#include "parametry_drona.hh"
#include "przesz_prost.hh"

using drawNS::APIGnuPlot3D;
using drawNS::Point3D;
using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main()
{
  Wektor3D WT, W0; //zmienna na przechowanie parametrów translacji wprowadzonych przez użytkownika
  std::shared_ptr<drawNS::Draw3DAPI> api(new APIGnuPlot3D(-SZEROKOSC_BASENU, DLUGOSC_BASENU, -WYSOKOSC_BASENU, SZEROKOSC_BASENU, -DLUGOSC_BASENU, WYSOKOSC_BASENU, -1));
  //włacza gnuplota, pojawia się scena, odswiezanie po każdym pojawieniu sie nowego konturu

  vector<std::shared_ptr<przeszkoda>> przeszkody;

  std::shared_ptr<przesz_prost> bloczek(new przesz_prost(api, 4, 1, 4, 1, 3, -4));
  std::shared_ptr<powierzchnia> dno(new powierzchnia(api, -9.5));
  std::shared_ptr<dron> drugi_dron(new dron(api, D_DRONA, S_DRONA, W_DRONA, 5, 5, -5));
  std::shared_ptr<dron> pierwszy_dron(new dron(api, D_DRONA, S_DRONA, W_DRONA, -5, -5, -5));
  std::shared_ptr<dron> dron_przechowawczy(new dron(api, D_DRONA, S_DRONA, W_DRONA, -5, -5, -5));
  std::shared_ptr<powierzchnia> lustro_wody(new powierzchnia(api, 8.5));
  //przeszkody.push_back(bloczek);
  przeszkody.push_back(lustro_wody);
  przeszkody.push_back(dno);
  przeszkody.push_back(drugi_dron);

  bloczek->draw("yellow");
  dno->draw();
  lustro_wody->draw("blue");
  drugi_dron->draw("blue");
  pierwszy_dron->draw("green");

  std::shared_ptr<dron> dronisko(new dron(api, D_DRONA, S_DRONA, W_DRONA, 0, 0, 0));

  char x; //zmienna pomocnicza do sterowania switchem
  double kat;
  char z = 'z';
  cout << "Wybierz drona, którym chcesz sterować:\ng - zielony\nb - niebieski\n"
       << endl;
  cin >> z;
  do
  {
    switch (z)
    {
    case 'g':
      dronisko = drugi_dron;
      przeszkody.push_back(pierwszy_dron);
      break;
    case 'b':
      dronisko = pierwszy_dron;
      przeszkody.push_back(drugi_dron);
      break;
    default:
      cout << "Nie ma takiego drona.\n"
           << endl;
      break;
    }
    break;
  } while (z != 'q' || !cin.fail());

  do
  {
    if (cin.fail() == false)
    {
      cout << "Co chcesz zrobić z dronem?\nt - Przesuń\nr - Obróć\nc- Wybierz drona\nq- Zakończ\n";
      cin >> x;
      switch (x)
      {
      case 't':
        cout << "Podaj wektor przesuniecia: " << endl;
        cin >> WT;
        dronisko->move(WT, przeszkody);
        dronisko->draw();
        cout << "Aktualne polozenie drona: " << dronisko->get_przes() << endl;
        break;
      case 'r':
        cout << "Podaj kat obrotu:  " << endl;
        cin >> kat;
        dronisko->rotate('z', kat);
        dronisko->draw();
        break;
      case 'c':
        cout << "Wybierz drona, którym chcesz sterować:\ng - zielony\nb - niebieski\n"
             << endl;
        char znak;
        cin >> znak;
        switch (znak)
        {
        case 'g':
          przeszkody.pop_back();
          przeszkody.push_back(dronisko);
          dronisko = pierwszy_dron;
          break;
        case 'b':
          przeszkody.pop_back();
          przeszkody.push_back(dronisko);
          dronisko = drugi_dron;
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
