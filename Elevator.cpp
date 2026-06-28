#include "Elevator.h"
#include "Request.h"
#include "LinkedList.h"
#include <iostream>
#include <cstdlib> // abs()

using namespace std;

Elevator::Elevator(int maxCap, int initFloor)
{
    currentFloor = initFloor;
    maxCapacity = maxCap;
    currentWeight = 0;
    currentDir = DUNG_YEN;
}

bool Elevator::checkWeight(int weight)
{
    if (this->currentWeight + weight > this->maxCapacity)
    {
        return false;
    }
    return true;
}

void Elevator::addPassenger(Request passenger)
{
    if (!checkWeight(passenger.canNang))
        return;

    this->cabinPassengers.insert(passenger);
    this->currentWeight += passenger.canNang;

    cout << "  [+] Da don Khach #" << passenger.id
         << " (" << passenger.canNang << " kg)"
         << " | Tai trong: " << currentWeight << "/" << maxCapacity << " kg\n";
}

void Elevator::removePassenger(int tangDen)
{
    float weightLost = this->cabinPassengers.remove(tangDen);
    if (weightLost > 0)
    {
        this->currentWeight -= weightLost;
        cout << "  [-] Da tra khach tai tang " << tangDen
             << " | Giam: " << weightLost << " kg"
             << " | Con lai: " << currentWeight << "/" << maxCapacity << " kg\n";
    }
}

void Elevator::move()
{
    if (currentDir == LEN)
        currentFloor++;
    else if (currentDir == XUONG)
        currentFloor--;
}

void Elevator::displayStatus()
{
    string dirStr;
    if (currentDir == LEN)
        dirStr = "LEN [^]";
    else if (currentDir == XUONG)
        dirStr = "XUONG [v]";
    else
        dirStr = "DUNG YEN";

    cout << "  +------------------------------------------+\n";
    cout << "  |         TRANG THAI THANG MAY             |\n";
    cout << "  +------------------------------------------+\n";
    cout << "  | Tang hien tai   : " << currentFloor << "\n";
    cout << "  | Huong di chuyen : " << dirStr << "\n";
    cout << "  | Tai trong       : " << currentWeight << "/" << maxCapacity << " kg\n";
    cout << "  | Hanh khach trong thang:\n";
    cabinPassengers.display();
    cout << "  +------------------------------------------+\n";
}
