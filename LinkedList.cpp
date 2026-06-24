#include "LinkedList.h"

Node::Node(Request request)
{
    data = request;
    next = nullptr;
}

LinkedList::LinkedList()
{
    head = nullptr;
    currentSize = 0;
}

LinkedList::~LinkedList()
{
    Node *current = head;
    while (current != nullptr)
    {
        Node *nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

bool LinkedList::hasTargetAbove(int currentFloor)
{
    Node *temp = head;
    while (temp != nullptr)
    {
        if (temp->data.tangDen > currentFloor)
            return true;
        temp = temp->next;
    }
    return false;
}

bool LinkedList::hasTargetBelow(int currentFloor)
{
    Node *temp = head;
    while (temp != nullptr)
    {
        if (temp->data.tangDen < currentFloor)
            return true;
        temp = temp->next;
    }
    return false;
}

void LinkedList::insert(Request request)
{
    Node *newNode = new Node(request);
    newNode->next = head;
    head = newNode;
    currentSize++;
}

int LinkedList::remove(int tangDen)
{
    int weightLost = 0;

    // 1. Node cần xóa là node đầu tiên
    while (head != nullptr && head->data.tangDen == tangDen)
    {
        Node *temp = head;
        weightLost += temp->data.canNang;
        head = head->next;
        delete temp;
        currentSize--;
    }

    // 1. Node cần xóa là node ở giữa hoặc cuối danh sách
    if (head != nullptr)
    {
        Node *current = head;
        while (current->next != nullptr)
        {
            if (current->next->data.tangDen == tangDen)
            {
                Node *temp = current->next;
                weightLost += temp->data.canNang;

                current->next = temp->next;
                delete temp;
                currentSize--;
            }
            else
            {
                current = current->next;
            }
        }
    }
    return weightLost;
}

// Kiểm tra danh sách liên kết có rỗng hay không
bool LinkedList::isEmpty()
{
    return head == nullptr;
}

void LinkedList::display()
{
    Node *temp = head;
    if (temp == nullptr)
    {
        cout << "[Thang may dang trong]" << endl;
        return;
    }

    while (temp != nullptr)
    {
        cout << "Khach ID " << temp->data.id
             << " | Goi tang " << temp->data.tangGoi
             << " -> Den tang " << temp->data.tangDen
             << " | Can nang: " << temp->data.canNang << " kg" << endl;
        temp = temp->next;
    }
    cout << endl;
}
