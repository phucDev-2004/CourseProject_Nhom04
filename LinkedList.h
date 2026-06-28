#pragma once
#include "Request.h"
#include <iostream>

using namespace std;

class Node
{
public:
    Request data;
    Node *next;

    Node(Request request);
};

class LinkedList
{
private:
    Node *head;
    int currentSize;

public:
    LinkedList();
    ~LinkedList();

    void insert(Request request);
    void remove(int tangDen);
    bool isEmpty();
    void display();
};