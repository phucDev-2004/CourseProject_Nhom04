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


void runFromFile(const string &filename)
{
    const int MAX_REQ = 100;
    Request requests[MAX_REQ];
    int maxCapacity = 0, initFloor = 1, count = 0;

    cout << "\n  Dang doc file: " << filename << "\n";

    if (!loadFile(filename, maxCapacity, initFloor, requests, count))
        return;

    cout << "  Doc file thanh cong!\n";

    printTitle("THONG TIN DU LIEU DAU VAO");
    cout << "  File          : " << filename << "\n";
    cout << "  Tai trong max : " << maxCapacity << " kg\n";
    cout << "  Tang ban dau  : " << initFloor << "\n";
    cout << "  So yeu cau    : " << count << "\n\n";

    cout << "  DANH SACH YEU CAU:\n";
    printLine('-', 60);
    cout << "  ID  | Tang goi | Tang den | Can nang | Huong\n";
    printLine('-', 60);
    for (int i = 0; i < count; i++)
    {
        string huongStr = (requests[i].huong == LEN) ? "LEN [^]" : "XUONG [v]";
        cout << "  " << requests[i].id
             << "   |    " << requests[i].tangGoi
             << "      |    " << requests[i].tangDen
             << "      |  " << requests[i].canNang << " kg"
             << "    | " << huongStr << "\n";
    }
    printLine('-', 60);

    ElevatorSystem sys(maxCapacity, initFloor);

    cout << "\n  [1] THEM YEU CAU VAO HANG DOI UU TIEN (UpQueue & DownQueue):\n";
    printLine('-', 60);
    for (int i = 0; i < count; i++)
    {
        sys.addRequest(requests[i]);
    }

    cout << "\n  [2] DANH SACH CHO THANG MAY (SAU KHI TINH UU TIEN):\n";
    printLine('-', 60);
    sys.displayQueue();

    cout << "\n  [3] TRANG THAI BAN DAU CUA THANG MAY:\n";
    sys.displayStatus();

    cout << "\n  [ Nhan ENTER de bat dau xu ly... ]";
    cin.ignore();
    cin.get();

    cout << "\n  [4] XU LY CAC YEU CAU THEO UU TIEN HANG DOI:\n";
    printLine('-', 60);
    sys.processRequests();

    cout << "\n  [5] DANH SACH DIEM TRA KHACH SAU KHI HOAN THANH:\n";
    printLine('-', 60);
    sys.displayDropOffList();

    cout << "\n  [6] TRANG THAI SAU KHI HOAN THANH:\n";
    sys.displayStatus();
}

int main()
{
    // ---- Man hinh chao ----
    printTitle("HE THONG QUAN LY THANG MAY - NHOM 04");
    cout << "\n  CAU TRUC DU LIEU SU DUNG:\n";
    cout << "    [1] LinkedList    - Luu hanh khach trong cabin thang may\n";
    cout << "    [2] PriorityQueue - UpQueue (Min-Heap) & DownQueue (Max-Heap)\n\n";

    // ---- Menu chon file ----
    cout << "  CHON FILE DU LIEU:\n";
    cout << "    [1] TestData_04.txt  (Du lieu kiem thu)\n";
    cout << "    [2] DemoData_04.txt  (Du lieu demo)\n";
    cout << "    [0] Thoat\n\n";

    int choice = 0;
    cout << "  Nhap lua chon (0/1/2): ";
    cin >> choice;

    string filename;
    switch (choice)
    {
    case 1:
        filename = "TestData_04.txt";
        break;
    case 2:
        filename = "DemoData_04.txt";
        break;
    case 0:
        cout << "\n  Da thoat chuong trinh.\n";
        return 0;
    default:
        cout << "\n  Lua chon khong hop le!\n";
        return 1;
    }

    runFromFile(filename);

    printLine('=');
    cout << "\n  Nhan ENTER de thoat...";
    cin.ignore();
    cin.get();
    return 0;
}
