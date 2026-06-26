#include "PriorityQueue.h"

void initQueue(PriorityQueue& q)
{
    q.front = NULL;
}

bool isEmpty(PriorityQueue q)
{
    return q.front == NULL;
}

void enqueue(PriorityQueue& q,
             string maYC,
             int tangGoi,
             int tangDen,
             int currentFloor)
{
    Node* p = new Node;

    p->data.maYC = maYC;
    p->data.tangGoi = tangGoi;
    p->data.tangDen = tangDen;

    p->data.priority =
        abs(currentFloor - tangGoi);

    p->next = NULL;

    if(q.front == NULL ||
       p->data.priority <
       q.front->data.priority)
    {
        p->next = q.front;
        q.front = p;
        return;
    }

    Node* cur = q.front;

    while(cur->next != NULL &&
          cur->next->data.priority <=
          p->data.priority)
    {
        cur = cur->next;
    }

    p->next = cur->next;
    cur->next = p;
}

bool dequeue(PriorityQueue& q,
             Request& x)
{
    if(isEmpty(q))
        return false;

    Node* p = q.front;

    x = p->data;

    q.front = q.front->next;

    delete p;

    return true;
}

void display(PriorityQueue q)
{
    if(isEmpty(q))
    {
        cout << "\nHang doi rong!\n";
        return;
    }

    Node* p = q.front;

    cout << "\n===== DANH SACH YEU CAU =====\n";

    while(p != NULL)
    {
        cout << p->data.maYC
             << " | Goi: "
             << p->data.tangGoi
             << " | Den: "
             << p->data.tangDen
             << " | Priority: "
             << p->data.priority
             << endl;

        p = p->next;
    }
}

void loadFromFile(PriorityQueue& q,
                  string filename,
                  int currentFloor)
{
    ifstream fin(filename);

    if(!fin)
    {
        cout << "\nKhong mo duoc file!\n";
        return;
    }

    int n;

    fin >> n;

    for(int i = 0; i < n; i++)
    {
        string ma;
        int goi;
        int den;

        fin >> ma >> goi >> den;

        enqueue(q,
                ma,
                goi,
                den,
                currentFloor);
    }

    fin.close();

    cout << "\nDoc file thanh cong!\n";
}

void processNextRequest(PriorityQueue& q,
                        int& currentFloor)
{
    Request x;

    if(!dequeue(q, x))
    {
        cout << "\nKhong co yeu cau nao!\n";
        return;
    }

    cout << "\n===== XU LY YEU CAU =====\n";

    cout << "Ma YC: "
         << x.maYC << endl;

    cout << "Tang hien tai: "
         << currentFloor << endl;

    cout << "Di den tang goi: "
         << x.tangGoi << endl;

    cout << "Dua khach den tang: "
         << x.tangDen << endl;

    currentFloor = x.tangDen;

    cout << "Vi tri moi: Tang "
         << currentFloor
         << endl;
}

void processAll(PriorityQueue& q,
                int& currentFloor)
{
    while(!isEmpty(q))
    {
        processNextRequest(q,
                           currentFloor);
    }
}
