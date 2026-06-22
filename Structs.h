#ifndef STRUCTS_H
#define STRUCTS_H

struct Passenger {
    int id;
    int startFloor;
    int destinationFloor;
    int weight;
};

struct Node {
    Passenger data;
    Node* next;
};

struct Elevator {
    int currentFloor;
    int direction; // 1: lên, -1: x
    int currentWeight;
    int maxWeight;

    Node* passengerList;
};

#endif
