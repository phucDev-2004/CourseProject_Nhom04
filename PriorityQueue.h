#pragma once
#include "Request.h"
#include <iostream>

class PriorityQueue
{
private:
    Request *heap;   // Mảng lưu danh sách khách chờ
    int capacity;    // Sức chứa tối đa của sảnh
    int currentSize; // Số khách đang chờ

    void swap(Request &a, Request &b);
    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    PriorityQueue(int cap);
    ~PriorityQueue();

    void push(Request req);
    Request pop();
    bool isEmpty();
    void display();   // Hien thi danh sach cho thang
    int size();       // So khach dang cho
};