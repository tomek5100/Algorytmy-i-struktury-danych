#include <iostream>

using namespace std;

const int maxlength = 4;
typedef int elementtype;
typedef int position;

class Kolejka
{
protected:
    elementtype Queue[maxlength];
    position Front; // Indeks elementu czołowego
    position Rear;  // Indeks ostatniego elementu
public:
    Kolejka();
    int AddOne(int i);
    void Enqueue(elementtype x);
    void Dequeue();
    elementtype FrontElem();
    void Makenull();
    bool Empty();
};

Kolejka::Kolejka()
{
    Front = 0;
    Rear = maxlength - 1;
}

int Kolejka::AddOne(int i)
{ //zwieksza o jeden zgodnie z relacja modulo
    return ((i + 1) % maxlength);
}

bool Kolejka::Empty()
{ //zwraca wartość true, gdy kolejka jest pusta, zwraca wartość false, gdy nie jest pusta
    return (AddOne(Rear) == Front);
}

void Kolejka::Enqueue(elementtype x)
{ //wstawia element do kolejki (wstawia na koniec !)
    if (AddOne(AddOne(Rear)) != Front) // Kolejka nie jest pełna
    {
        Rear = AddOne(Rear);
        Queue[Rear] = x;
    }
}

void Kolejka::Dequeue()
{   //usuń elementu z kolejki. Usuwamy element z początku kolejki
    if (!Empty())

    {
        Front = AddOne(Front);
    }
}

elementtype Kolejka::FrontElem()
{   //zwraca pierwszy element z kolejki

    if (!Empty())
    return Queue[Front];
}

void Kolejka::Makenull()
{ //czyni kolejke pusta

    Front=0;
    Rear= maxlength-1;

}


int main(){
    Kolejka k;
    cout << k.Empty() << endl;
    k.Enqueue(5);
    cout << k.Empty() << endl;
    cout << k.FrontElem() << endl;
    k.Dequeue();
    cout << k.Empty() << endl;
    k.Enqueue(4);
    k.Enqueue(3);
    k.Enqueue(2);
    k.Enqueue(20);
    cout << k.FrontElem() << endl;
    k.Dequeue();
    cout << k.FrontElem() << endl;
    k.Dequeue();
    cout << k.FrontElem() << endl;
    k.Dequeue();
    cout << k.FrontElem() << endl;


}
