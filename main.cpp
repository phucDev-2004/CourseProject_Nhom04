#include <iostream>
#include <fstream>
#include <string>
#include "Request.h"
#include "PriorityQueue.h"
#include "Elevator.h"
#include "ElevatorSystem.h"

using namespace std;

// ============================================================
//   TIEN ICH IN DUONG KE
// ============================================================
void printLine(char c = '=', int len = 60)
{
    for (int i = 0; i < len; i++)
        cout << c;
    cout << "\n";
}

void printTitle(const string &title, int len = 60)
{
    printLine('=', len);
    int pad = (len - (int)title.size()) / 2;
    if (pad < 0)
        pad = 0;
    cout << string(pad, ' ') << title << "\n";
    printLine('=', len);
}

// ============================================================
//   DOC FILE DU LIEU
//   Dinh dang file:
//     Dong 1 : tai trong toi da (kg)
//     Dong 2 : tang ban dau cua thang may
//     Dong 3 : so luong yeu cau
//     Dong 4 : id  tangGoi  tangDen  canNang
//   (Huong cua yeu cau tu dong xac dinh tu tangGoi va tangDen)
// ============================================================
bool loadFile(const string &filename,
              int &maxCapacity,
              int &initFloor,
              Request requests[],
              int &count)
{
    ifstream fin(filename);
    if (!fin.is_open())
    {
        cout << "\n  [LOI] Khong mo duoc file: " << filename << "\n";
        return false;
    }

    fin >> maxCapacity >> initFloor >> count;

    for (int i = 0; i < count; i++)
    {
        int id, tangGoi, tangDen, canNang;
        fin >> id >> tangGoi >> tangDen >> canNang;
        requests[i] = Request(id, tangGoi, tangDen, canNang);
    }

    fin.close();
    return true;
}


void runInteractive()
{
    ElevatorSystem* sys = new ElevatorSystem(1000, 1);
    int maxCapacity = 1000;
    int initFloor = 1;

    while (true)
    {
        cout << "\n";
        printTitle("HE THONG QUAN LY THANG MAY - MENU TUY CHON");
        cout << "  [1] Khoi tao lai thang may (Tai trong, tang hien tai)\n";
        cout << "  [2] Doc du lieu tu file\n";
        cout << "  [3] Them yeu cau thu cong\n";
        cout << "  [4] Xem danh sach yeu cau (Hang doi)\n";
        cout << "  [5] Xem trang thai thang may hien tai\n";
        cout << "  [6] Xu ly tat ca cac yeu cau\n";
        cout << "  [7] Xem danh sach khach da duoc tra\n";
        cout << "  [0] Thoat chuong trinh\n";
        printLine('-', 60);
        cout << "  Nhap lua chon cua ban: ";
        
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice)
        {
        case 1:
            cout << "  Nhap tai trong toi da (kg): ";
            cin >> maxCapacity;
            cout << "  Nhap tang ban dau: ";
            cin >> initFloor;
            delete sys;
            sys = new ElevatorSystem(maxCapacity, initFloor);
            cout << "  => Khoi tao thang may thanh cong!\n";
            break;
        case 2:
        {
            cout << "  CHON FILE DU LIEU:\n";
            cout << "    [1] TestData_04.txt\n";
            cout << "    [2] DemoData_04.txt\n";
            cout << "    [3] Nhap ten file khac\n";
            cout << "  Lua chon: ";
            int fChoice;
            cin >> fChoice;
            string filename = "";
            if (fChoice == 1) filename = "TestData_04.txt";
            else if (fChoice == 2) filename = "DemoData_04.txt";
            else if (fChoice == 3) {
                cout << "  Nhap ten file: ";
                cin >> filename;
            } else {
                cout << "  Lua chon khong hop le.\n";
                break;
            }

            const int MAX_REQ = 100;
            Request requests[MAX_REQ];
            int count = 0;
            
            if (loadFile(filename, maxCapacity, initFloor, requests, count)) {
                delete sys;
                sys = new ElevatorSystem(maxCapacity, initFloor);
                
                for (int i = 0; i < count; i++) {
                    sys->addRequest(requests[i]);
                }
                cout << "  => Doc file thanh cong! Da them " << count << " yeu cau vao hang doi.\n";
            }
            break;
        }
        case 3:
        {
            int id, tangGoi, tangDen, canNang;
            cout << "  Nhap ID khach: "; cin >> id;
            cout << "  Nhap tang goi: "; cin >> tangGoi;
            cout << "  Nhap tang den: "; cin >> tangDen;
            cout << "  Nhap can nang: "; cin >> canNang;
            
            sys->addRequest(Request(id, tangGoi, tangDen, canNang));
            cout << "  => Da them yeu cau vao hang doi.\n";
            break;
        }
        case 4:
            cout << "\n";
            sys->displayQueue();
            break;
        case 5:
            cout << "\n";
            sys->displayStatus();
            break;
        case 6:
            cout << "\n";
            sys->processRequests();
            break;
        case 7:
            cout << "\n";
            sys->displayDropOffList();
            break;
        case 0:
            cout << "\n  Da thoat chuong trinh.\n";
            delete sys;
            return;
        default:
            cout << "  Lua chon khong hop le!\n";
        }
    }
}

int main()
{
    runInteractive();
    return 0;
}
