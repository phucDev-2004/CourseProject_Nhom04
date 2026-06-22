#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "Structs.h"

void addPassenger(Elevator& e, Passenger p);
void removePassenger(Elevator& e, int floor);
bool checkWeight(Elevator& e, Passenger p);

#endif
