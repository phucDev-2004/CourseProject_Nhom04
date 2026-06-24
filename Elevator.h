#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "Structs.h"
#include <iostream>

void addPassenger(Elevator& e, Passenger p);      // Đón khách vào (Thêm vào danh sách liên kết passengerList)
void removePassenger(Elevator& e, int floor);     // Trả khách ra (Xóa khỏi danh sách liên kết tại tầng chỉ định)
bool checkWeight(Elevator& e, Passenger p);       // Kiểm tra tải trọng trước khi cho khách vào

#endif // ELEVATOR_H