#include "Request.h"

Request::Request()
{
    id = 0;
    tangGoi = 0;
    tangDen = 0;
    huong = DUNG_YEN;
    canNang = 0;
}

Request::Request(int id, int tangGoi, int tangDen, int canNang)
{
    this->id = id;
    this->tangGoi = tangGoi;
    this->tangDen = tangDen;
    this->canNang = canNang;

    if (tangGoi < tangDen)
        huong = LEN;
    else if (tangGoi > tangDen)
        huong = XUONG;
    else
        huong = DUNG_YEN;
}