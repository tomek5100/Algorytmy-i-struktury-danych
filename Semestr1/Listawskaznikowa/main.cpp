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
protected:
    position l; // wskaźnik do głowy listy

public:
    Lista() //konstruktor
    {
        l = new celltype;
        l->next = NULL;
    }

    ~Lista()
    { //destruktor czyni listę pustą i zwraca pozycję END(L). //makenull
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
    l.Insert(5, l.First());                //wstawiam 5 na poczatek listy
    cout << l.Retrieve(l.First()) << endl; //wyswietlam 5 - pierwszy element listy

    l.Insert(2, l.First());                        //wstawiam 2 na poczatek listy
    cout << l.Retrieve(l.First()) << " ";          //wyswietlam 2 - pierwszy element listy
    cout << l.Retrieve(l.Next(l.First())) << endl; //wyswietlam 5 - drugi element listy

    l.Insert(1, l.Next(l.First()));                        //wstawiam 1 na drugie miejsce
    cout << l.Retrieve(l.First()) << " ";                  //wyswietlam 2 - pierwszy element listy
    cout << l.Retrieve(l.Next(l.First())) << " ";          //wyswietlam 1 - drugi element listy
    cout << l.Retrieve(l.Next(l.Next(l.First()))) << endl; //wyswietlam 5 - trzeci element listy

    l.Delete(l.Locate(1));

    cout << "Cala lista: " << endl;
    l.wyswietlListe(); //wypisuje cala liste
    return 0;
}