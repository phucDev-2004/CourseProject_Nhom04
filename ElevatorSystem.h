#pragma once
#include "Elevator.h"
#include "PriorityQueue.h"

class ElevatorSystem
{
private:
    Elevator elevator;
    PriorityQueue upQueue;
    PriorityQueue downQueue;

public:
    ElevatorSystem(int maxCapacity, int initFloor = 1);
    void addRequest(Request request);
    void displayQueue();
    void displayDropOffList();
    void processRequests();
    void displayStatus();
    int calculatePriority(Elevator &e, Request req);
};