#include "ElevatorSystem.h"
#include <cstdlib> // abs()
#include <iostream>

using namespace std;

// ---- Tien ich in duong ke ----
static void esLine(char c = '-', int len = 60)
{
    for (int i = 0; i < len; i++)
        cout << c;
    cout << "\n";
}

ElevatorSystem::ElevatorSystem(int maxCapacity, int initFloor)
    : elevator(maxCapacity, initFloor), requestQueue(100)
{
}

void ElevatorSystem::addRequest(Request req)
{
    requestQueue.push(req);
    string huongStr = (req.huong == LEN) ? "LEN [^]" : "XUONG [v]";
    cout << "  [+] Da them: Khach #" << req.id
         << " | Tang goi: " << req.tangGoi
         << " -> Tang den: " << req.tangDen
         << " | Can nang: " << req.canNang << " kg"
         << " | Huong: " << huongStr << "\n";
}

void ElevatorSystem::displayQueue()
{
    cout << "  DANH SACH CHO THANG MAY:\n";
    requestQueue.display();
    cout << "  Tong so khach dang cho: " << requestQueue.size() << "\n";
}

void ElevatorSystem::processRequests()
{
    // 1. Lấy tất cả yêu cầu từ hàng đợi ra mảng de de dang duyet
    Request pending[100];
    int pCount = 0;
    while (!requestQueue.isEmpty())
    {
        pending[pCount++] = requestQueue.pop();
    }

    elevator.currentDir = LEN; // Mac dinh ban dau di len
    cout << "\n  --- BAT DAU LO TRINH THANG MAY (Uu tien Priority Queue + Thuật toán LOOK) ---\n";
    cout << string(60, '-') << "\n";

    while (true)
    {
        bool actionTaken = false;

        // 1. CHẾ ĐỘ FETCH: Nếu thang rỗng, đi thẳng tới đón khách ưu tiên cao nhất (tangGoi nhỏ nhất)
        if (elevator.cabinPassengers.isEmpty()) {
            int nextReq = -1;
            for (int i = 0; i < pCount; i++) {
                if (pending[i].id != -1) {
                    nextReq = i;
                    break;
                }
            }
            
            if (nextReq == -1) break; // Hoan tat tat ca!

            if (elevator.currentFloor > pending[nextReq].tangGoi) {
                elevator.currentDir = XUONG;
                if (!actionTaken) cout << "     (Di qua tang " << elevator.currentFloor << ")\n";
                elevator.move();
                continue; // Đi thẳng, không đón ai dọc đường để đảm bảo tính Priority Queue
            } else if (elevator.currentFloor < pending[nextReq].tangGoi) {
                elevator.currentDir = LEN;
                if (!actionTaken) cout << "     (Di qua tang " << elevator.currentFloor << ")\n";
                elevator.move();
                continue; // Đi thẳng, không đón ai dọc đường
            } else {
                elevator.currentDir = pending[nextReq].huong;
            }
        }

        // 2. Trả khách
        int weightLost = elevator.cabinPassengers.remove(elevator.currentFloor);
        if (weightLost > 0)
        {
            elevator.currentWeight -= weightLost;
            cout << "\n  [-] Thang dung tai tang " << elevator.currentFloor
                 << " de TRA KHACH | Giam: " << weightLost
                 << " kg | Con lai: " << elevator.currentWeight << "/" << elevator.maxCapacity << " kg\n";
            actionTaken = true;
        }

        // 3. Đón khách
        bool picked = false;
        for (int i = 0; i < pCount; i++)
        {
            if (pending[i].id != -1 && pending[i].tangGoi == elevator.currentFloor)
            {
                // CHỈ đón nếu khách CÙNG HƯỚNG với thang máy
                if (pending[i].huong == elevator.currentDir)
                {
                    if (elevator.checkWeight(pending[i].canNang))
                    {
                        elevator.addPassenger(pending[i]);
                        pending[i].id = -1; // Danh dau da don
                        picked = true;
                        actionTaken = true;
                    }
                }
            }
        }

        if (picked)
        {
            cout << "     Danh sach trong thang hien tai:\n";
            elevator.cabinPassengers.display();
        }

        // 4. Tính toán hướng đi tiếp theo (Chỉ áp dụng khi thang có người - Thuật toán SCAN/LOOK)
        if (!elevator.cabinPassengers.isEmpty()) {
            bool needToGoUp = elevator.cabinPassengers.hasTargetAbove(elevator.currentFloor);
            bool needToGoDown = elevator.cabinPassengers.hasTargetBelow(elevator.currentFloor);
            
            // Nhìn phía trước xem có khách gọi CÙNG HƯỚNG không
            for (int i = 0; i < pCount; i++) {
                if (pending[i].id != -1 && pending[i].huong == elevator.currentDir) {
                    if (elevator.currentDir == LEN && pending[i].tangGoi > elevator.currentFloor) needToGoUp = true;
                    if (elevator.currentDir == XUONG && pending[i].tangGoi < elevator.currentFloor) needToGoDown = true;
                }
            }

            if (elevator.currentDir == LEN && !needToGoUp) {
                elevator.currentDir = XUONG; // Quay dau xuong
                cout << "\n  ============================================================";
                cout << "\n  [!] THANG MAY DOI HUONG: [ XUONG v ] (Do khong con ai phia tren)";
                cout << "\n  ============================================================\n";
            } else if (elevator.currentDir == XUONG && !needToGoDown) {
                elevator.currentDir = LEN; // Quay dau len
                cout << "\n  ============================================================";
                cout << "\n  [!] THANG MAY DOI HUONG: [ LEN ^ ] (Do khong con ai phia duoi)";
                cout << "\n  ============================================================\n";
            }
        } else {
            // Thang vừa trả khách xong và rỗng -> vòng lặp sau sẽ tự động fetch khách ưu tiên nhất.
            continue; 
        }

        // 5. Di chuyen
        if (!actionTaken) cout << "     (Di qua tang " << elevator.currentFloor << ")\n";
        elevator.move();
    }

    elevator.currentDir = DUNG_YEN;
    cout << "\n  *** Da xu ly xong TAT CA yeu cau bang thuat toan SCAN/LOOK! ***\n";
}

void ElevatorSystem::displayStatus()
{
    elevator.displayStatus();
}

int ElevatorSystem::calculatePriority(Elevator &e, Request req)
{
    int score = 0;
    if (e.currentDir == LEN && req.tangGoi >= e.currentFloor)
        score += 1000;
    else if (e.currentDir == XUONG && req.tangGoi <= e.currentFloor)
        score += 1000;
    score -= abs(e.currentFloor - req.tangGoi);
    return score;
}