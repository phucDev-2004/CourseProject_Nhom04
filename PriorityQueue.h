#pragma once
#include "Request.h"
#include <iostream>

class PriorityQueue
{
private:
    Request *heap;   // Mảng lưu danh sách khách chờ
    int capacity;    // Sức chứa tối đa của sảnh
    int currentSize; // Số khách đang chờ
    bool isMinHeap;  // true: Min-Heap (UpQueue), false: Max-Heap (DownQueue)

    void swap(Request &a, Request &b);
    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    PriorityQueue(int cap, bool isMin = true);
    ~PriorityQueue();

    void push(Request req);
    Request pop();
    Request top();    // Xem phan tu uu tien nhat (Khong xoa)
    bool isEmpty();
    void display();   // Hien thi danh sach cho thang
    int size();       // So khach dang cho
};