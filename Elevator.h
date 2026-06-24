#pragma once
#include "Request.h"
#include "LinkedList.h"
#include <iostream>

using namespace std;

class Elevator
{
public:
    int currentFloor;
    int maxCapacity;
    float currentWeight;
    Huong currentDir;

    LinkedList cabinPassengers;

    Elevator();
    Elevator(int maxCapacity, int initFloor);

    bool checkWeight(int weight);
    void addPassenger(Request request);
    void removePassenger(int tangDen);
    void move();
    void displayStatus();
};