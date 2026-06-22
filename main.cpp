#include <iostream>
#include "Structs.h"
#include "PriorityQueue.h"
#include "Elevator.h"
#include "Display.h"
#include "Performance.h"

using namespace std;

int main() {

    Elevator elevator;

    elevator.currentFloor = 1;
    elevator.direction = 1;
    elevator.currentWeight = 0;
    elevator.maxWeight = 500;
    elevator.passengerList = NULL;

    cout << "ELEVATOR MANAGEMENT SYSTEM\n";

    return 0;
}
