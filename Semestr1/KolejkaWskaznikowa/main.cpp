#include <iostream>

using namespace std;

typedef int elementtype;
struct celltype
{
    elementtype element;
    celltype *next;
};

typedef celltype *position;

class Queue
{
protected:
    position Front; // wskaźnik do głowy listy
    position Rear;  // wskaźnik do ostatniego elementu
public:
    Queue();
    ~Queue();
    void Enqueue(elementtype x);
    void Dequeue();
    elementtype FrontElem();
    bool Empty();
};

//inicjalizacja, kontruktor
Queue::Queue(void)
{
    Front = new celltype;
    Rear = Front;
    Front->next = NULL;
}

//wstawia element x na koniec kolejki
void Queue::Enqueue(elementtype x)
{
    position p = new celltype;
    p->element = x;
    p->next = NULL;
    Rear->next = p;
    Rear = p;
}

//usuwa element z poczatku kolejki
void Queue::Dequeue()
{
    if (!Empty())
    {
        position p = Front;
        Front = Front->next;
        delete p;
    }
}

//zwraca pierwszy element z kolejki
elementtype Queue::FrontElem()
{
    if (!Empty())
        return Front->next->element;
    else
    {
        cout << "Kolejka jest pusta" << endl;
        exit(-1);
    }
}

//sprawdza czy kolejka jest pusta
bool Queue::Empty()
{
    return (Front->next == NULL);
}

//destruktor, przegladamy cala kolejke, stopniowo zwalniamy pamiec przeznaczona na komorki
Queue::~Queue(void)
{
    position tmp;

    while (Front->next != NULL)
    {
        tmp = Front;
        Front = Front->next;
        delete tmp;
    }
    delete Front;
}

int main()
{

    Queue k;
    cout << k.Empty() << endl;     //zwraca 1 bo kolejka jest pusta
    k.Enqueue(5);                  //wstawiam 5 na koniec kolejki
    cout << k.Empty() << endl;     //zwraca 0 bo kolejka nie jest pusta
    cout << k.FrontElem() << endl; //zwraca 5 - element z poczatku kolejki
    k.Dequeue();                   //usuwa element z poczatku kolejki
    cout << k.Empty() << endl;     //zwraca 1 bo kolejka pusta
    k.Enqueue(4);                  //wstawiam 4 na koniec
    k.Enqueue(3);                  //wstawiam 3 na koniec
    k.Enqueue(2);                  //wstawiam 2 na koniec
    cout << k.FrontElem() << endl; //zwracam 4 - element z poczatku kolejki
    k.Enqueue(1);                  //wstawiam 1 na koniec
    cout << k.FrontElem() << endl; //zwracam 4 - element z poczatku kolejki
    k.Dequeue();                   //usuwam 4 - element z poczatku kolejki
    cout << k.FrontElem() << endl; //zwracam 3 - element z poczatku kolejki
    k.Enqueue(6);                  //wstawiam 6 na koniec kolejki
    cout << k.FrontElem() << endl; //zwracam 3 - element z poczatku kolejki
    k.Dequeue();                   //usuwam 3
    k.Dequeue();                   //usuwam 2
    cout << k.FrontElem() << endl; //zwracam 1
    cout << k.Empty() << endl;     //zwracam 0 - kolejka nie jest pusta, zostala jeszcze 6

    return 0;
}