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
    int tangGoi;  // Tầng gọi (nơi khách đang đứng chờ)
    int tangDen;  // Tầng đến (nơi khách muốn tới)
    Huong huong;
    int canNang;

    Request();
    Request(int id, int tangGoi, int tangDen, int canNang);
};
