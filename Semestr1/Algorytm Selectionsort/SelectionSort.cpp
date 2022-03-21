#include <iostream>
#include <algorithm>

using namespace std;

void prostewybieranie(int a[], int n)
{
    int k, x; //k-indeks minimalnego elementu; x-obiekt minimalny
    int licznik = 0;
    {
        for (int i = 0; i < n; i++)
        {
            k = i;
            x = a[i]; //szukamy elementu minimalnego w ciągu a[i]...a[n]
            for (int j = i + 1; j < n; j++)
            {
                licznik++; //zliczam operacje porównania
                if (a[j] < x)
                {
                    k = j;
                    x = a[j];
                }
            }

            a[k] = a[i];
            //a[i] : = x; //zamieniamy element i-ty z min
            swap(a[i], x);
        }
    }
    cout << "Operacje dominujace: " << licznik << endl; //wyswietlam ilość operacji dominujacych(porównania)
}

int main()
{
    const int n = 10; //rozmiar
    int a[n] = {1, 2, 5, 1, 15, 99, 23, 55, 16, 10};
    prostewybieranie(a, n);
    for (int x : a)
    {
        cout << x << endl; //wyswietlam posortowana tablice
    }
}