#include <iostream>

using namespace std;

const int maxlegth = 3;
typedef int elementtype;
typedef int position;

class Stos
{
protected:
    elementtype S[maxlegth];
    position Top; //szczyt stosu
public:
    Stos();
    void Push(elementtype x);
    void Pop();
    bool Empty();
    elementtype TopElem();
    void Makenull();
};

Stos::Stos(void)
{
    Top = -1;
}

void Stos::Push(elementtype x)
{
    if (Top < maxlegth - 1)
    {
        Top++;
        S[Top] = x;
    }
}

void Stos::Pop()
{
    if (Top >= 0)
        Top--;
}

elementtype Stos::TopElem()
{
    if (Top >= 0)
        return S[Top];
    throw  "Top < 0";
}

void Stos::Makenull()
{
    Top = -1;
}

bool Stos::Empty()
{
    return (Top == -1);
}

int main()
{
    Stos S;
    cout << S.Empty() << endl;
    S.Push(5);
    cout << S.TopElem() << endl;
    cout << S.Empty() << endl;
    S.Pop();
    cout << S.Empty() << endl;
    S.Push(2);
    S.Push(3);
    cout << S.TopElem() << endl;
    S.Push(6);
    S.Push(3);
    //S.Makenull();
    cout << S.TopElem() << endl;
    cout << S.Empty() << endl;

    return 0;
}
