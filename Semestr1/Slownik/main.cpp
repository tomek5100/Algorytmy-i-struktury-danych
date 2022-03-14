#include <iostream>

using namespace std;

const int B = 65; //rozmiar tablicy
typedef char* elementtype;
struct celltype
{
    elementtype element;
    celltype *next;
};
typedef celltype *position;

class dictionary
{
protected:
    //nasza lista
    position D[B];

public:
    dictionary();
    ~dictionary();
    void Makenul();
    bool Member(elementtype x);
    void Insert(elementtype x);
    void Delete(elementtype x);
    int H(elementtype x);
};

//konstruktor czyni slownik pustym
dictionary::dictionary()
{
    for (int i = 0; i < B; i++)
        D[i] = NULL;
}

//sprawdza czy element nalezy do slownika
bool dictionary::Member(elementtype x)
{
    position current;
    current = D[H(x)];
    while (current != NULL)
    {
        if (current->element == x)
            return true;
        else
            current = current->next;
    }
    return false;
}

//wstawia element x do slownika
void dictionary::Insert(elementtype x)
{
    int bucket;
    position oldheader;
    if (!Member(x))
    {
        bucket = H(x);
        oldheader = D[bucket];
        D[bucket] = new celltype;
        D[bucket]->element = x;
        D[bucket]->next = oldheader;
    }
}

//usuwa element x ze slownika
void dictionary::Delete(elementtype x)
{
    position p, current;
    int bucket;
    bucket = H(x);
    if (D[bucket] != NULL)
    {
        if (D[bucket]->element == x) //czy x jest w pierwszej komorce
        {
            p = D[bucket];
            D[bucket] = D[bucket]->next;
            delete p;
        }
        else
        {
            current = D[bucket];
            while (current->next != NULL)
                if ((current->next->element) == x)
                {
                    p = current->next;
                    current->next = current->next->next;
                    delete p;
                    break;
                }
                else
                    current = current->next;
        }
    }
}

//destruktor usuwa wszystkie elementy listy
dictionary::~dictionary()
{
    position p;
    for (int i = 0; i < B; i++)
    {
        while (D[i] != NULL)
        {
            p = D[i];
            D[i] = D[i]->next;
            delete p;
        }
    }
}

//czyni slownik slownikiem pustym
void dictionary::Makenul()
{
    position p;
    for (int i = 0; i < B; i++)
    {
        while (D[i] != NULL)
        {
            p = D[i];
            D[i] = D[i]->next;
            delete p;
        }
    }
}

//oblicza wartosc funkcji haszujacej
int dictionary::H(elementtype x)
{
    return (int(x[0])) % B;
}

int main()
{
    dictionary d;
    d.Insert("Ala"); //wstawawiam slowo "Ala" do slownika
    cout << d.Member("Ala") << endl; //wypisuje 1 bo Ala jest w slowniku
    cout << d.H("Ala") << endl; //wypisuje 0 - wartosc funkcji haszujacej
    d.Insert("As"); //wstawiam slowo As
    cout << d.Member("As") << endl; //wypisuje 1 - As jest w slowniku
    cout << d.H("As") << endl;
    cout << d.Member("Ala") << endl;
    cout << d.H("Ala") << endl;
    d.Insert("Rozycki");
    cout << d.H("Rozycki") << endl; //wypisuje 17 - wartosc funkcji haszujacej
    cout << d.Member("Rozycki") << endl; //wypisuje 1 
    d.Delete("Ala");
    cout << d.Member("As") << endl;
    cout << d.Member("Ala") << endl; //wypisuje 0 - Ala zostala usunieta ze slownika
    d.Makenul(); //czynie liste pusta
    cout << d.Member("As") << endl; //wypisuje 0
    cout << d.Member("Rozycki") << endl; //wypisuje 0

    return 0;
}