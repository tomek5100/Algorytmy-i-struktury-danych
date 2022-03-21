#include <iostream>
#include <cstdio>
#include "listatablicowa.hpp"

using namespace std;

void print(List l)
{
	position i = First(l);
	while (i != END(l) && (i != -1))
	{
		printf("  %d,", Retrieve(i, l));
		i = Next(i, l);
	}
	printf("\n");
}

int main()
{

	List l;
	l.last = -1;
	
	Insert(100, First(l), l);
	print(l);
	
	for (int i = 0; i < 3; i++) {
		Insert(i, First(l), l);
	}
	print(l);

	Insert(20, Previous(END(l), l), l);
	print(l);
	Delete(Locate(20, l), l);
	print(l);

	Insert_duplicate(l);
	print(l);

	Insert(100, 0, l);
	print(l);

	Delete_duplicate(l);
	print(l);
	
	return 0;
}