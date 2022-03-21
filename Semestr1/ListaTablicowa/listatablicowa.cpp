#include <iostream>
#include <cstdio>
#include "listatablicowa.hpp"

using namespace std;

/* typedef int elementtype, position;
const int maxlength;
struct List
{
	elementtype elements[maxlength];
	int last; //indeks ostatniego elementu listy
}; */

position END(List l)
{ //zwraca indeks za ostatnim elementem
	return l.last + 1;
}

position First(List l)
{ //zwraca indeks pierwszego elementu
	return 0;
}

position Next(position p, List l)
{ //zwraca indeks nastepnego elementu w stosunku do p
	if (p < END(l))
	{
		return p + 1;
	}
	else
	{
		cout << "Operacja nieokreslona" << endl;
		return -1;
	}
}

position Previous(position p, List l)
{ //zwraca indeks poprzedniego elementu w stosunku do p
	if ((p <= First(l) || (p > END(l))))
	{
		cout << "Operacja nieokreslona" << endl;
		return -1;
	}
	else
	{
		return p - 1;
	}
}

position Locate(elementtype x, List l)
{ //zwraca pozycje x w l, gdy nie ma x w l zwraca end(l)
	for (int i = 0; i < END(l); i++)
	{
		if (l.elements[i] == x)
		{
			return i;
		}
	}
	return END(l);
}

elementtype Retrieve(position p, List l)
{ //zwraca element znajdujacy sie w liscie na pozycji p
	if ((p >= 0) || (p <= END(l)))
	{
		return l.elements[p];
	}
	else
	{
		return -1000000000;
	}
}

bool Insert(int x, position p, List& l)
{ //wstawia x do komorki o numerze p
	if ((p < 0) || (p > END(l)))
		return false;
	if (p == END(l))
	{
		l.elements[p] = x;
		l.last = l.last + 1;
		return true;
	}

	if (p < END(l))
	{
		for (position k = END(l); k > p; k--)
		{
			l.elements[k] = l.elements[k - 1];
		}
		l.elements[p] = x;
		l.last = l.last + 1;
		return true;
	}
	return false;
}

bool Delete(position p, List& l)
{ //usuwa element z komorki o numerze p
	while (p < END(l) - 1)
	{
		l.elements[p] = l.elements[p + 1];
		p++;
	}
	l.last--;
	return true;
}

bool Insert_duplicate(List& l) {
	//wstawiam na ostatnie miejsce duplikat elementu o numerze i
	int last_element = l.last;
	for (int i = 0; i <= last_element; i++) {
		Insert(Retrieve(i, l), END(l), l);
		//automatycznie zwiekszam wielkosc listy
	}
	return true;

}

bool Delete_duplicate(List& l) {
	//usuwam duplikaty z listy
	for (int i = 0; i <= l.last; i++) {
		for (int j = 0; j <= l.last; j++) {
			if (l.elements[i] == l.elements[j] && i != j){
			Delete(j, l);
			}
		}
	}
	return true;
}
