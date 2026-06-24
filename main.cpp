#include "ElevatorQueue.h"

int main()
{
    PriorityQueue q;

    initQueue(q);

    int currentFloor = 1;

    int choice;

    do
    {
        system("cls");

        cout << "\n========== QUAN LY THANG MAY ==========";

        cout << "\n1. Doc du lieu tu file";
        cout << "\n2. Them yeu cau moi";
        cout << "\n3. Hien thi hang doi";
        cout << "\n4. Xu ly yeu cau tiep theo";
        cout << "\n5. Xu ly tat ca yeu cau";
        cout << "\n6. Xem vi tri thang may";
        cout << "\n0. Thoat";

        cout << "\n\nNhap lua chon: ";
        cin >> choice;

        switch(choice)
        {
        case 1:
        {
            loadFromFile(q,
                         "input.txt",
                         currentFloor);
            break;
        }

        case 2:
        {
            string ma;
            int goi;
            int den;

            cout << "\nMa YC: ";
            cin >> ma;

            cout << "Tang goi: ";
            cin >> goi;

            cout << "Tang den: ";
            cin >> den;

            enqueue(q,
                    ma,
                    goi,
                    den,
                    currentFloor);

            cout << "\nThem thanh cong!";
            break;
        }

        case 3:
        {
            display(q);
            break;
        }

        case 4:
        {
            processNextRequest(q,
                               currentFloor);
            break;
        }

        case 5:
        {
            processAll(q,
                       currentFloor);
            break;
        }

        case 6:
        {
            cout << "\nThang may dang o tang: "
                 << currentFloor;
            break;
        }

        case 0:
            break;

        default:
            cout << "\nLua chon khong hop le!";
        }

        cout << "\n\n";
        system("pause");

    } while(choice != 0);

    return 0;
}
