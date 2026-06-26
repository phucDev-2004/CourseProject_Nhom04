#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

struct Request
{
    string maYC;
    int tangGoi;
    int tangDen;
    int priority;
};

struct Node
{
    Request data;
    Node* next;
};

struct PriorityQueue
{
    Node* front;
};

void initQueue(PriorityQueue& q);

bool isEmpty(PriorityQueue q);

void enqueue(PriorityQueue& q,
             string maYC,
             int tangGoi,
             int tangDen,
             int currentFloor);

bool dequeue(PriorityQueue& q,
             Request& x);

void display(PriorityQueue q);

void loadFromFile(PriorityQueue& q,
                  string filename,
                  int currentFloor);

void processNextRequest(PriorityQueue& q,
                        int& currentFloor);

void processAll(PriorityQueue& q,
                int& currentFloor);

#endif
