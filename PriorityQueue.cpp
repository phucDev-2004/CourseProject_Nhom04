#include "PriorityQueue.h"

PriorityQueue::PriorityQueue(int cap)
{
    capacity = cap;
    currentSize = 0;
    heap = new Request[capacity];
}

PriorityQueue::~PriorityQueue()
{
    delete[] heap;
}

void PriorityQueue::swap(Request &a, Request &b)
{
    Request temp = a;
    a = b;
    b = temp;
}

// đẩy khách lên vị trí ưu tiên cao hơn
void PriorityQueue::heapifyUp(int index)
{
    if (index == 0)
        return;
    int parent = (index - 1) / 2;
    if (heap[index].tangGoi < heap[parent].tangGoi)
    {
        swap(heap[index], heap[parent]);
        heapifyUp(parent);
    }
}

// đẩy khách xuống khi đã lấy người ưu tiên ra
void PriorityQueue::heapifyDown(int index)
{
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < currentSize && heap[left].tangGoi < heap[smallest].tangGoi)
        smallest = left;
    if (right < currentSize && heap[right].tangGoi < heap[smallest].tangGoi)
        smallest = right;

    if (smallest != index)
    {
        swap(heap[index], heap[smallest]);
        heapifyDown(smallest);
    }
}

void PriorityQueue::push(Request req)
{
    if (currentSize == capacity)
        return;
    heap[currentSize] = req;
    heapifyUp(currentSize);
    currentSize++;
}

Request PriorityQueue::pop()
{
    if (isEmpty())
        return Request();
    Request root = heap[0];
    heap[0] = heap[currentSize - 1];
    currentSize--;
    heapifyDown(0);
    return root;
}

bool PriorityQueue::isEmpty()
{
    return currentSize == 0;
}

int PriorityQueue::size()
{
    return currentSize;
}

void PriorityQueue::display()
{
    if (currentSize == 0)
    {
        std::cout << "  [Hang doi trong - khong co khach cho]\n";
        return;
    }
    std::cout << "  Thu tu | ID  | Tang goi | Tang den | Can nang | Huong\n";
    std::cout << "  -------+-----+----------+----------+----------+----------\n";
    Request temp[100];
    for (int i = 0; i < currentSize; i++)
        temp[i] = heap[i];
    for (int i = 0; i < currentSize - 1; i++)
        for (int j = i + 1; j < currentSize; j++)
            if (temp[j].tangGoi < temp[i].tangGoi)
            {
                Request t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
    for (int i = 0; i < currentSize; i++)
    {
        std::string huongStr = (temp[i].huong == LEN) ? "LEN [^]" : "XUONG [v]";
        std::cout << "  " << (i + 1)
                  << "       | #" << temp[i].id
                  << "  |    " << temp[i].tangGoi
                  << "      |    " << temp[i].tangDen
                  << "      |  " << temp[i].canNang << " kg"
                  << "  | " << huongStr << "\n";
    }
}