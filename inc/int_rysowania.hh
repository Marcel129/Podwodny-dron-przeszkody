#ifndef INT_RYSOWANIA
#define INT_RYSOWANIA
#define BAZOWE_ID -20

#include <iostream>
#include "Dr3D_gnuplot_api.hh"

class int_rysowania
{
protected:
    int ID, pomocnicze_id=-20;
    std::string kolor;
    std::shared_ptr<drawNS::Draw3DAPI> api;

public:
    void usun() { if(ID != pomocnicze_id)  api->erase_shape(ID);else { ++pomocnicze_id;api->erase_shape(ID); }}
    //void draw();
};

#endif
