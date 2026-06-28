#include "Request.h"

Request::Request()
{
    id = 0;
    tangDen = 0;
    tangDoi = 0;
    huong = DUNG_YEN;
    canNang = 0;
}

Request::Request(int id, int tangDen, int tangDoi, int canNang)
{
    this->id = id;
    this->tangDen = tangDen;
    this->tangDoi = tangDoi;
    this->canNang = canNang;

    if (tangDen > tangDoi)
        huong = LEN;
    else if (tangDen < tangDoi)
        huong = XUONG;
    else
        huong = DUNG_YEN;
}