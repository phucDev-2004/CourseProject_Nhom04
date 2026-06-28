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
    : elevator(maxCapacity, initFloor), upQueue(100, true), downQueue(100, false)
{
}

void ElevatorSystem::addRequest(Request req)
{
    if (req.huong == LEN) upQueue.push(req);
    else downQueue.push(req);
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
    cout << "  [+] HANG DOI DI LEN (UpQueue):\n";
    upQueue.display();
    cout << "  [+] HANG DOI DI XUONG (DownQueue):\n";
    downQueue.display();
    cout << "  Tong so khach dang cho: " << (upQueue.size() + downQueue.size()) << "\n";
}

void ElevatorSystem::displayDropOffList()
{
    cout << "  DANH SACH DIEM TRA KHACH (Hanh khach trong cabin):\n";
    if (elevator.cabinPassengers.isEmpty()) {
        cout << "  [Thang may dang trong - khong co ai can tra]\n";
    } else {
        elevator.cabinPassengers.display();
    }
}

void ElevatorSystem::processRequests()
{
    elevator.currentDir = LEN; // Thuat toan LOOK: mac dinh bat dau di len
    cout << "\n  --- BAT DAU LO TRINH THANG MAY (Thuat toan LOOK - 2 QUEUE) ---\n";
    cout << string(60, '-') << "\n";

    PriorityQueue pendingUp(100, true);
    PriorityQueue pendingDown(100, false);
    PriorityQueue rejectedReqs(100, true); // De chung nhe, vi luc push lai se kiem tra huong

    while (true)
    {
        bool actionTaken = false;

        // 1. Kiểm tra trả khách
        int weightLost = elevator.cabinPassengers.remove(elevator.currentFloor);
        if (weightLost > 0)
        {
            elevator.currentWeight -= weightLost;
            cout << "\n  [-] Thang dung tai tang " << elevator.currentFloor
                 << " de TRA KHACH | Giam: " << weightLost
                 << " kg | Con lai: " << elevator.currentWeight << "/" << elevator.maxCapacity << " kg\n";
            actionTaken = true;
        }

        // 2. Day khach dang cho o tang khac vao Pending de lay khach dung tang
        if (elevator.currentDir == LEN) {
            while (!upQueue.isEmpty() && upQueue.top().tangGoi < elevator.currentFloor) {
                pendingUp.push(upQueue.pop());
            }
        } else {
            while (!downQueue.isEmpty() && downQueue.top().tangGoi > elevator.currentFloor) {
                pendingDown.push(downQueue.pop());
            }
        }

        // 3. Đón khách
        bool picked = false;
        if (elevator.currentDir == LEN) {
            while (!upQueue.isEmpty() && upQueue.top().tangGoi == elevator.currentFloor) {
                Request req = upQueue.pop();
                if (elevator.checkWeight(req.canNang)) {
                    elevator.addPassenger(req);
                    picked = true;
                    actionTaken = true;
                } else {
                    cout << "  [!!!] Thang may qua tai! Tam thoi chua don khach #" << req.id 
                         << ". Khach tiep tuc cho o tang " << req.tangGoi << ".\n";
                    rejectedReqs.push(req);
                }
            }
        } else {
            while (!downQueue.isEmpty() && downQueue.top().tangGoi == elevator.currentFloor) {
                Request req = downQueue.pop();
                if (elevator.checkWeight(req.canNang)) {
                    elevator.addPassenger(req);
                    picked = true;
                    actionTaken = true;
                } else {
                    cout << "  [!!!] Thang may qua tai! Tam thoi chua don khach #" << req.id 
                         << ". Khach tiep tuc cho o tang " << req.tangGoi << ".\n";
                    rejectedReqs.push(req);
                }
            }
        }

        // Tra khach bi tu choi do qua tai ve lai hang doi
        while (!rejectedReqs.isEmpty()) {
            Request r = rejectedReqs.pop();
            if (r.huong == LEN) upQueue.push(r);
            else downQueue.push(r);
        }

        if (picked)
        {
            cout << "     [+] Danh sach hanh khach trong thang:\n";
            elevator.cabinPassengers.display();
        }

        // 4. Kiem tra xem co the tiep tuc di tiep hay doi huong
        bool needToGoUp = elevator.cabinPassengers.hasTargetAbove(elevator.currentFloor) 
                       || !upQueue.isEmpty() 
                       || (!pendingDown.isEmpty() && pendingDown.top().tangGoi > elevator.currentFloor);
                       
        bool needToGoDown = elevator.cabinPassengers.hasTargetBelow(elevator.currentFloor) 
                         || !downQueue.isEmpty() 
                         || (!pendingUp.isEmpty() && pendingUp.top().tangGoi < elevator.currentFloor);

        // Kiem tra stop hoan toan
        if (!needToGoUp && !needToGoDown && pendingUp.isEmpty() && pendingDown.isEmpty() && elevator.cabinPassengers.isEmpty()) {
            break; // Hoan tat
        }

        if (elevator.currentDir == LEN && !needToGoUp) {
            elevator.currentDir = XUONG;
            cout << "\n  ============================================================";
            cout << "\n  [!] THANG MAY DOI HUONG: [ XUONG v ] tai TANG " << elevator.currentFloor << " (Do khong con ai phia tren)";
            cout << "\n  ============================================================\n";
            // Gop pendingDown vao downQueue
            while (!pendingDown.isEmpty()) downQueue.push(pendingDown.pop());
            continue; // Quay lai dau vong lap de xu ly tiep o huong moi
        } else if (elevator.currentDir == XUONG && !needToGoDown) {
            elevator.currentDir = LEN;
            cout << "\n  ============================================================";
            cout << "\n  [!] THANG MAY DOI HUONG: [ LEN ^ ] tai TANG " << elevator.currentFloor << " (Do khong con ai phia duoi)";
            cout << "\n  ============================================================\n";
            // Gop pendingUp vao upQueue
            while (!pendingUp.isEmpty()) upQueue.push(pendingUp.pop());
            continue; // Quay lai dau vong lap de xu ly tiep o huong moi
        }

        // 5. Di chuyen
        if (!actionTaken) cout << "     (Di qua tang " << elevator.currentFloor << ")\n";
        elevator.move();
    }

    elevator.currentDir = DUNG_YEN;
    cout << "\n  *** Da xu ly xong tat ca yeu cau bang thuat toan LOOK! ***\n";
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