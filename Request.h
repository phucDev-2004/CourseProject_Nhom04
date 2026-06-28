#pragma once

enum Huong
{
    LEN,
    XUONG,
    DUNG_YEN
};

class Request
{
public:
    int id;
    int tangDen;
    int tangDoi;
    Huong huong;
    int canNang;

    Request();
    Request(int id, int tangDen, int tangDoi, int canNang);
};
