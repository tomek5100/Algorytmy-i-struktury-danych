#include <iostream>
#include <vector>

using namespace std;

class Container
{
protected:
    Container(){};

public:
    virtual unsigned int Count() const = 0;
    virtual bool IsEmpty() const
    {
        return Count() == 0;
    }
    virtual bool IsFull() const = 0;
    virtual void MakeNull() = 0;
};

template <typename T>
class PriorityQueue : public Container
{
public:
    virtual void Enqueue(T element) = 0;
    virtual T FindMin() const = 0;
    virtual T DequeueMin() = 0;
};

template <typename T>
class BinaryHeap : public PriorityQueue<T>
{
protected:
    int count;
    std::vector<T> data;

public:
    BinaryHeap(unsigned int n);
    BinaryHeap();
    ~BinaryHeap() { ; };
    void MakeNull();
    void Enqueue(T element);
    T FindMin() const;
    T DequeueMin();
    bool IsEmpty() const;
    bool IsFull() const;
    void Wypisz() const;
    unsigned int Count() const
    {
        return count;
    }
};

template <typename T>
BinaryHeap<T>::BinaryHeap(unsigned int n) : count(0), data(n){};

template <typename T>
BinaryHeap<T>::BinaryHeap() : count(0), data(10){};

template <typename T>
bool BinaryHeap<T>::IsEmpty() const
{
    return (count == 0);
}

template <typename T>
bool BinaryHeap<T>::IsFull() const
{
    return false;
}

template <typename T>
void BinaryHeap<T>::MakeNull()
{
    count = 0;
}

template <typename T>
T BinaryHeap<T>::FindMin() const
{
    if (count > 0)
        return data[0];
    else
    {
        cout << "Error! Kolejka jest pusta!" << endl;
        return -999;
    }
}

template <typename T>
void BinaryHeap<T>::Enqueue(T element)
{
    if (count >= data.size())
        data.resize(count + 1);
    ++count;

    int i = count - 1;
    while ((i > 0) && (data[(i - 1) / 2] > element))
    {
        data[i] = data[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    data[i] = element;
}

template <typename T>
T BinaryHeap<T>::DequeueMin()
{
    if (count > 0)
    {
        T result = data[0];
        T last = data[count - 1];
        --count;
        int i = 0;
        while (2 * i + 1 < count)
        {
            int child = 2 * i + 1;
            if ((child + 1 < count) && (data[child + 1] < data[child]))
                child = child + 1;
            if (last <= data[child])
                break;
            data[i] = data[child];
            i = child;
        }
        data[i] = last;
        return result;
    }
    else
    {
        cout << "Error! Kolejka jest pusta!" << endl;
        return -999;
    }
}

// metoda wypisuje kopiec poziom po poziomie poczynajac od korzenia
template <typename T>
void BinaryHeap<T>::Wypisz() const
{
    int i = count;
    cout << "Kolejka: ";
    for (int k = 0; k < i; k++)
    {
        cout << data[k] << " ";
    }
    cout << endl;
}

int main()
{
    BinaryHeap<int> Kolejka(10);
    cout << "IsEmpty? : " << Kolejka.IsEmpty() << endl;
    Kolejka.Enqueue(5);
    cout << "IsEmpty? : " << Kolejka.IsEmpty() << endl;
    Kolejka.Wypisz();
    cout << "Minimum : " << Kolejka.FindMin() << endl;
    Kolejka.Enqueue(6);
    Kolejka.Wypisz();
    cout << "Minimum : " << Kolejka.FindMin() << endl;
    Kolejka.Enqueue(8);
    Kolejka.Wypisz();
    cout << "Minimum : " << Kolejka.FindMin() << endl;
    Kolejka.Enqueue(3);
    Kolejka.Wypisz();
    cout << "Minimum : " << Kolejka.FindMin() << endl;
    Kolejka.Enqueue(9);
    Kolejka.Wypisz();
    cout << "Minimum : " << Kolejka.FindMin() << endl;
    Kolejka.Enqueue(2);
    Kolejka.Wypisz();
    cout << "Minimum : " << Kolejka.FindMin() << endl;
    Kolejka.Enqueue(1);
    Kolejka.Wypisz();
    cout << "Minimum : " << Kolejka.FindMin() << endl;
    Kolejka.DequeueMin();
    Kolejka.Wypisz();
    cout << "Minimum : " << Kolejka.FindMin() << endl;
    Kolejka.DequeueMin();
    Kolejka.Wypisz();
    cout << "Minimum : " << Kolejka.FindMin() << endl;
    Kolejka.MakeNull();
    cout << "IsEmpty? : " << Kolejka.IsEmpty() << endl;

    return 0;
}