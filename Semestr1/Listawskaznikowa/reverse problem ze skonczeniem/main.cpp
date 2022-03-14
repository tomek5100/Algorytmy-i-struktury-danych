#include <iostream>

using namespace std;

typedef int elementtype;

struct celltype
{
    elementtype element;
    celltype *next; //wskaznik do nastepnego elementu
};
typedef celltype *position;

class Lista
{
    //protected:
public:
    position l; // wskaźnik do głowy listy

public:
    Lista() //konstruktor
    {
        l = new celltype;
        l->next = NULL;
    }

    ~Lista()
    { //destruktor czyni listę pustą i zwraca pozycję END(L).
        position tmp;
        if ((l != NULL) && (l->next != NULL))
            while (l->next != NULL)
            {
                tmp = l->next;
                l->next = tmp->next;
                delete tmp;
            }
    }
    void Insert(elementtype x, position p)
    { //wstaw x na pozycję p na liście L
        position tmp;
        tmp = p->next;
        p->next = new celltype;
        p->next->element = x;
        p->next->next = tmp;
    }
    void Delete(position p)
    { //usuwa element na pozycji p z listy
        position tmp;
        tmp = p->next;
        p->next = p->next->next;
        delete tmp;
    }

    elementtype Retrieve(position p)
    { // zwraca element występujący w L na pozycji p
        if (p->next != NULL)
            return p->next->element;
        else
        {
            cout << "Taka pozycja nie wystepuje w liscie!" << endl;
            exit(-1);
        }
    }

    position Locate(elementtype x)
    {
        //zwraca pozycję elementu x w liście, czyli taką pozycję p, że p->next->element= =x
        position tmp;
        tmp = l;
        while (tmp->next != NULL) //dopóki tmp nie wskazuje na ostatni rekord listy
        {
            if (tmp->next->element == x)
                return tmp;

            tmp = tmp->next;
        }
        return tmp;
    }
    position First() //First - zwraca pozycję pierwszego elementu w L. Jeśli L pusta, to zwraca END(L)
    {
        return l;
    }
    position Next(position p) //zwraca pozycję następną w stosunku do p w L
    {
        return p->next;
    }
    position Previous(position p)
    { //zwraca pozycję poprzednia w stosunku do p w L
        position tmp;
        tmp = l;
        if (p == l)
        {
            cout << "Operacja niezdefiniowana!" << endl;
            exit(-1);
        }
        while (tmp->next != p)
        {
            tmp = tmp->next;
        }
        return tmp;
    }

    position END()
    { //zwraca wskaźnik do ostatniego elementu
        position tmp = l;
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        return tmp;
    }

    void reverse()
    {
        l = l->next;
        position current = l; //aktualny
        position nextc = NULL; //nastepny
        position prev = NULL; //poprzedni

        while (current != NULL)
        {
            nextc = current->next;
            current->next = prev;
            prev = current;
            current = nextc;
        }
        l = prev;
        cout << "Reverse echo head element: " << l->element << endl;
    }

    void wyswietlListe()
    {
        //wypisuje cala liste
        position x = l->next;
        int i = 1;

        while (x != NULL)
        {
            cout << "[i: " << i << "] Wartosc " << x->element << endl;
            i++;
            x = x->next;
        }
    }
};
int main()
{
    Lista l;

    //test
    cout << "Po utworzeniu obiektu l: " << l.l << " l->next: " << l.l->next << endl;

    l.Insert(5, l.First());
    
    //test wskaznikow
    cout << l.Retrieve(l.First()) << endl;
    
    cout << "Retrieve glowa: " << l.l->element << endl;
    cout << "Retieve(first): " << l.Retrieve(l.l) << " = Retrieve(first next): " << l.l->next->element << endl;

    l.Insert(2, l.First());
    cout << l.Retrieve(l.First()) << " ";
    cout << l.Retrieve(l.Next(l.First())) << endl;

    l.Insert(1, l.Next(l.First()));
    cout << l.Retrieve(l.First()) << " ";
    cout << l.Retrieve(l.Next(l.First())) << " ";
    cout << l.Retrieve(l.Next(l.Next(l.First()))) << endl;
    
    cout << "test wskaznikow" << endl;
    cout << "\n0. " << l.l->element << "\n1. " << l.l->next->element << "\n2. " << 
    l.l->next->next->element << "\n3. " << l.l->next->next->next->element << endl;
    cout << "1 " << l.l << " 2 " << l.l->next << " 3 " << l.l->next->next << " 4 " << l.l->next->next->next
    << " 5 " << l.l->next->next->next->next << endl;
    
    cout << "\nCala lista: " << endl;
    l.wyswietlListe();

    //odwracamy
    l.reverse();
    cout << "Cala lista: " << endl;
    l.wyswietlListe();
    cout << l.Retrieve(l.Next(l.Next(l.First()))) << endl;
    cout << l.Retrieve(l.First()) << endl;
    cout << "Retrieve(first a powinna byc glowa): " << l.l->element << endl;

    cout << "\n0. " << l.l->element << "\n1. " << l.l->next->element << "\n2. " << 
    l.l->next->next->element << "\n3. " << l.l->next->next->next->element << endl;
    cout << "1 " << l.l << " 2 " << l.l->next << " 3 " << l.l->next->next << " 4 " << l.l->next->next->next
    << " 5 " << l.l->next->next->next->next << endl;

    return 0;
}