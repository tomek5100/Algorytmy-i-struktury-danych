#ifndef LISTATABLICOWA_HPP
#define LISTATABLICOWA_HPP
#include <iostream>
#include <cstdio>

typedef int elementtype, position;
const int maxlength = 10;
struct List
{
    elementtype elements[maxlength];
    int last; //indeks ostatniego elementu listy
};

position END(List l); //zwraca indeks za ostatnim elementem

position First(List l); //zwraca indeks pierwszego elementu

position Next(position p, List l); //zwraca indeks nastepnego elementu w stosunku do p

position Previous(position p, List l); //zwraca indeks poprzedniego elementu w stosunku do p

position Locate(elementtype x, List l); //zwraca pozycje x w l, gdy nie ma x w l zwraca end(l)

elementtype Retrieve(position p, List l); //zwraca element znajdujacy sie w liscie na pozycji p

bool Insert(int x, position p, List& l); //wstawia x do komorki o numerze p

bool Delete(position p, List& l); //usuwa element z komorki o numerze p

bool Insert_duplicate(List& l); //wstawiam na ostatnie miejsce duplikat elementu o numerze i

bool Delete_duplicate(List& l); //usuwam duplikaty z listy

#endif