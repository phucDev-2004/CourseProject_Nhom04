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

void LinkedList::insert(Request request)
{
    Node *newNode = new Node(request);
    newNode->next = head;
    head = newNode;
    currentSize++;
}

void LinkedList::remove(int tangDen)
{
    // Nếu node cần xóa là node đầu tiên
    while (head != nullptr && head->data.tangDen == tangDen)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
        currentSize--;
        return;
    }

    if (head != nullptr)
    {
        Node *current = head;
        while (current->next != nullptr)
        {
            Node *nextNode = current->next;

            if (nextNode->data.tangDen == tangDen)
            {
                current->next = nextNode->next;
                delete nextNode;
                currentSize--;
                return;
            }
            else
            {
                current = current->next;
            }
        }
    }
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
        cout << "Khach den tang " << temp->data.tangDen
             << ", di tang " << temp->data.tangDoi
             << ", can nang " << temp->data.canNang << endl;
        temp = temp->next;
    }
    cout << endl;
}
