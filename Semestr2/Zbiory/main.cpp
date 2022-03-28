#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

template <typename T>
class Visitor
{
public:
    virtual void Visit(T &element) = 0;
    virtual bool IsDone() const
    {
        return false;
    }
};

template <typename T>
class AddingVisitor : public Visitor<T>
{
public:
    int sum; // w tym polu pamiętamy policzoną sumę
    AddingVisitor() : sum(0){};
    void Visit(int &i)
    {
        sum += i;
    }
    void MakeNull()
    {
        sum = 0;
    }
};

template <typename T>
class Container
{
public:
    Container(){};
    virtual int Count() const = 0;
    virtual bool IsEmpty() const { return Count() == 0; };
    virtual bool IsFull() const = 0;
    virtual void MakeNull() = 0;
    virtual void Accept(Visitor<T> &v) const = 0;
};

template <typename T>
class Iterator
{
public:
    virtual ~Iterator(){};
    Iterator(){};
    virtual bool IsDone() const = 0;
    virtual T &operator*() const = 0;
    virtual void operator++() = 0;
};

template <typename T>
class Set : public Container<T>
{
protected:
    int count;
    int universeSize;

public:
    // Set() : universeSize(5) {} // konstruktor domyślny, inaczej nie chciało się kompilować
    Set(int n) : universeSize(n) {}
    int UniverseSize() const { return universeSize; }
    int Count() const { return count; };
    virtual void Insert(T element) = 0;
    virtual bool IsMember(T element) const = 0;
    virtual void Withdraw(T element) = 0;
};

class SetAsArray : public Set<int>
{
    std::vector<bool> array;

public:
    // pobiera jeden argument N oznaczajacy rozmiar zbioru uniwersalnego
    //(tablicy bool) ustawiajac argumenty na zero
    SetAsArray(unsigned int n) : Set(n)
    {
        universeSize = n; // ustawiam rozmiar zbioru i tablicy boolowskiej
        array.resize(n);
        fill(array.begin(), array.end(), false); // wszystkie elementy false
        count = 0;
    }

    void MakeNull()
    {
        this->count = 0;
        this->universeSize = 0;
        this->array.clear(); // ustawia wszystko w array na false
    }

    bool IsFull() const
    {
        return (Count() == UniverseSize());
    };

    void Insert(int element)
    {
        if (element <= this->universeSize && element >= 0 && this->array[element] == false)
        {
            this->array[element] = true;
            count++;
        }
    }

    bool IsMember(int element) const
    {
        if (element >= this->universeSize || element < 0)
            return false;
        return this->array[element];
    };

    void Withdraw(int element)
    {
        // jesli element nalezy do zbioru to ustawiamy false
        if (element <= this->universeSize && element > 0 && (this->array[element] == true))
        {
            this->array[element] = false;
            count--;
        }
    }

    // friend - funkcja uzyska prawo dostepu do prywatnych elementów danej klasy.
    friend SetAsArray operator+(SetAsArray const &s, SetAsArray const &t)
    {
        if (s.universeSize != t.universeSize)
        {
            cout << "Zbiory uniwersalne nie są rowne" << endl;
            return -1;
        }
        SetAsArray result(s.universeSize);
        for (int i = 0; i < s.universeSize; ++i)
        {
            result.array[i] = s.array[i] || t.array[i];
            if (result.array[i] == true)
                result.count++;
        }
        return result;
    }

    friend SetAsArray operator-(SetAsArray const &s, SetAsArray const &t)
    {
        if (s.universeSize != t.universeSize)
        {
            cout << "Zbiory uniwersalne nie są rowne" << endl;
            return -1;
        }
        SetAsArray result(s.universeSize);
        for (int i = 0; i < s.universeSize; ++i)
        {
            result.array[i] = s.array[i] && !t.array[i];
            if (result.array[i] == true)
                result.count++;
        }
        return result;
    }

    friend SetAsArray operator*(SetAsArray const &s, SetAsArray const &t)
    {
        if (s.universeSize != t.universeSize)
        {
            cout << "Zbiory uniwersalne nie są rowne" << endl;
            return -1;
        }
        SetAsArray result(s.universeSize);
        for (int i = 0; i < s.universeSize; ++i)
        {
            result.array[i] = s.array[i] && t.array[i];
            if (result.array[i] == true)
                result.count++;
        }
        return result;
    }

    friend bool operator==(SetAsArray const &s, SetAsArray const &t)
    {
        if (s.universeSize != t.universeSize)
        {
            cout << "Zbiory uniwersalne nie są rowne" << endl;
            return false;
        }
        else
        {
            for (int i = 0; i < s.universeSize; ++i)
            {
                // jeśli jakikolwiek element jest różny to zwracamy false
                if (s.array[i] != t.array[i])
                {
                    return false;
                }
            }
            return true;
        }
    }

    friend bool operator<=(SetAsArray const &s, SetAsArray const &t)
    {
        // jeśli jakikolwiek element zbioru s nie zawiera się w t to zwracamy false
        for (int i = 0; i < s.universeSize; ++i)
        {
            // jesli element z tablicy s nie znajduje się w t to false
            if ((s.array[i] == true) && (t.array[i] == false))
            {
                return false;
            }
        }
        return true;
    }

    void Wypisz()
    {
        for (int i = 0; i < this->universeSize; i++)
        {
            if (this->array[i])
                cout << i << " ";
        }
        cout << endl;
    }

    void Accept(Visitor<int> &v) const
    {
        for (int i = 0; i < universeSize; i++)
        {
            if (this->array[i] == true)
                v.Visit(i);
        }
    }

    class Iter : public Iterator<int>
    {
        std::vector<bool> data;
        int universeSize;
        int index;

    public:
        Iter(std::vector<bool> array, int univerSize)
            : data(array), universeSize(univerSize)
        {
            for (auto &element : data)
            {
                if (element == true)
                {
                    // tu moze byc zle, zrob lepiej zwykla petle ktora ma i
                    index = element;
                    break;
                }
            }
        };
        ~Iter();
        const int &operator*(){
            return index;
        };
        void operator++();
        bool IsDone() const;
    };

    Iter &NewIterator()
    {
        return *new Iter(array, universeSize);
    }
};

int main()
{
    SetAsArray A(10), B(10), C(10), D(10);
    A.Insert(0);
    A.Insert(2);
    A.Insert(4);
    A.Insert(6);
    A.Insert(8);

    B.Insert(1);
    B.Insert(3);
    B.Insert(5);
    B.Insert(7);
    B.Insert(9);

    C = (A + B);

    D = (C - B);

    cout << "A: ";
    A.Wypisz();
    cout << "B: ";
    B.Wypisz();
    cout << "C: ";
    C.Wypisz();
    cout << "D: ";
    D.Wypisz();
    cout << D.Count() << endl;

    // cout << "Czy D==A ? " << operator==(D, A) << endl;
    //  inny sposób na użycie przeciążonego operatora:
    cout << "Czy D == A: " << ((D == A) ? "Tak" : "Nie") << endl;
    cout << "Czy D <= A: " << ((D <= A) ? "Tak" : "Nie") << endl;
    cout << "Czy C == B: " << ((C == B) ? "Tak" : "Nie") << endl;
    cout << "Czy B <= C: " << ((B <= C) ? "Tak" : "Nie") << endl;

    A.Insert(1);
    A.Wypisz();
    cout << "Czy D == A: " << ((D == A) ? "Tak" : "Nie") << endl;
    cout << "Czy D <= A: " << ((D <= A) ? "Tak" : "Nie") << endl;

    // nowe testy

    A.Insert(5);
    cout << "A: ";
    A.Wypisz();

    AddingVisitor<int> v_A;
    A.Accept(v_A);
    cout << "Obliczona suma A : " << v_A.sum << endl;

    SetAsArray E(10);
    // E = operator*(A, B);
    // inny sposob na uzycie przeciążonego operatora
    E = A * B;

    cout << "E: ";
    E.Wypisz();

    AddingVisitor<int> v_E;
    E.Accept(v_E);
    cout << "Obliczona suma E : " << v_E.sum << endl;
    v_E.MakeNull();

    E.Withdraw(1);
    cout << "E: ";
    E.Wypisz();

    E.Accept(v_E);
    cout << "Obliczona suma E: " << v_E.sum << endl;

    return 0;
}