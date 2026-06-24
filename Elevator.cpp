#include "Elevator.h"

// Hàm kiểm tra xem nếu thêm hành khách này vào thì có bị quá tải không
bool checkWeight(Elevator& e, Passenger p) {
    if (e.currentWeight + p.weight > e.maxWeight) {
        std::cout << "Canh bao: Qua tai! Khong the don hanh khach co ID: " << p.id << ".\n";
        return false;
    }
    return true;
}

// Hàm đón khách vào thang máy (Thêm vào cuối danh sách liên kết passengerList)
void addPassenger(Elevator& e, Passenger p) {
    // Kiểm tra cân nặng trước
    if (!checkWeight(e, p)) {
        return; 
    }

    // Tạo một Node mới 
    Node* newNode = new Node;
    newNode->data = p;
    newNode->next = nullptr;

    // Nếu thang máy đang trống khách
    if (e.passengerList == nullptr) {
        e.passengerList = newNode;
    } else {
        // Duyệt xuống cuối danh sách liên kết passengerList để nối vào đuôi
        Node* temp = e.passengerList;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    // Cập nhật lại trọng tải hiện tại của thang máy
    e.currentWeight += p.weight;
    std::cout << "Da don hanh khach ID " << p.id << " vao thang may.\n";
}

// Hàm trả khách ra khi thang máy đến đúng tầng (Xóa Node khỏi passengerList)
void removePassenger(Elevator& e, int floor) {
    if (e.passengerList == nullptr) return; // Thang máy trống thì không làm gì cả

    Node* temp = e.passengerList;
    Node* prev = nullptr;

    // Duyệt qua danh sách để tìm và trả những khách muốn xuống tầng này (destinationFloor)
    while (temp != nullptr) {
        if (temp->data.destinationFloor == floor) {
            std::cout << "Hanh khach ID " << temp->data.id << " da roi thang may tai tang " << floor << ".\n";
            
            // Cập nhật lại trọng lượng thang máy
            e.currentWeight -= temp->data.weight;

            // Xử lý xóa Node trong Linked List
            Node* nodeToDelete = temp;
            if (prev == nullptr) {
                // Nếu khách cần xóa nằm ngay đầu danh sách
                e.passengerList = temp->next;
                temp = e.passengerList;
            } else {
                // Nếu khách nằm ở giữa hoặc cuối danh sách
                prev->next = temp->next;
                temp = temp->next;
            }
            delete nodeToDelete; // Giải phóng bộ nhớ
        } else {
            prev = temp;
            temp = temp->next;
        }
    }
}