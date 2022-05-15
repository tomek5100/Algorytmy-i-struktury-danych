#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
class Iterator
{
public:
    Iterator(){};
    virtual ~Iterator(){};
    virtual bool IsDone() = 0;
    virtual T &operator*() = 0;
    virtual void operator++() = 0;
};

// wizytator zliczajacy ile wierzcholkow odwiedzilismy algorytmem DFS
class Visitor
{
public:
    virtual void Visit() = 0;
    virtual bool IsDone() const
    {
        return false;
    }
};

class CountingVisitor : public Visitor
{
public:
    int amount; // w tym polu pamiętamy ilosc odwiedzonych wierzcholkow
    CountingVisitor()
    {
        amount = 0;
    };
    void Visit()
    {
        amount++;
    }
    void MakeNull()
    {
        amount = 0;
    }
};

// wierzcholki
class Vertex
{
    // unikalny numer wierzcholka
    int number;

public:
    int weight;
    std::string label;
    Vertex(int n) : number(n){};
    int Number() const { return number; };
};

// krawedzie
class Edge
{
protected:
    Vertex *v0;
    Vertex *v1;

public:
    int weight;
    std::string label;
    Edge(Vertex *V0, Vertex *V1) : v0(V0), v1(V1){};
    Vertex *V0() { return v0; };
    Vertex *V1() { return v1; };

    // zwraca drugi wierzcholek krawedzi
    Vertex *Mate(Vertex *v)
    {
        if (v->Number() == v0->Number())
        {
            return v1;
        }
        else if (v->Number() == v1->Number())
        {
            return v0;
        }
        else
        {
            cout << "Blad! Krawedz nie ma drugiego wierzcholka!" << endl;
            return NULL;
        }
    };
};

class GraphAsMatrix
{
    std::vector<Vertex *> vertices;                   // vector wierzcholkow grafu
    std::vector<std::vector<Edge *>> adjacencyMatrix; // macierz sasiedztwa
    bool isDirected;                                  // czy graf skierowany
    int numberOfVertices;                             // liczba wierzcholkow
    int numberOfEdges = 0;                            // liczba krawedzi
    std::vector<bool> visited;                        // czy wierzcholek byl odwiedzony

public:
    // iterator po wszystkich wierzcholkach, czyli czytam caly wektor
    class AllVerticesIter : public Iterator<Vertex>
    {
        GraphAsMatrix &owner;
        int current;

    public:
        AllVerticesIter(GraphAsMatrix &o) : owner(o), current(0){};

        bool IsDone()
        {
            if (current < owner.NumberOfVertices())
                return false;
            else
                return true;
        };

        Vertex &operator*()
        {
            return *owner.vertices[current];
        };

        void operator++()
        {
            if (current < owner.NumberOfVertices())
            {
                current++;
            }
        };
    };

    // iterator po wszystkich krawedziach, czyli czytam cala macierz
    class AllEdgesIter : public Iterator<Edge>
    {
        GraphAsMatrix &owner;
        int row;
        int col;

    public:
        AllEdgesIter(GraphAsMatrix &o) : owner(o), row(0), col(0)
        {
            next();
        };

        void next()
        {
            if (row != 0 || col != 0)
            {
                col++;
            }
            if (row == (owner.NumberOfVertices() - 1) && (col >= owner.NumberOfVertices() - 1))
            {
                // jesli wsystkie wiersze i kolumny zostaly przejrzane
                // daje informacje metodzie isDone aby zakonczyc iterowanie
                row = owner.NumberOfVertices();
                col = owner.NumberOfVertices();
            }
            for (int i = row; i < owner.NumberOfVertices(); i++)
            {
                for (int j = col; j < owner.NumberOfVertices(); j++)
                {
                    if (owner.adjacencyMatrix[i][j] != NULL)
                    {
                        // znalezlismy kolejna krawedz
                        row = i;
                        col = j;
                        return;
                    }
                    if (j == owner.NumberOfVertices() - 1)
                    {
                        // aby przegladac kolumny nowego wiersza od nowa
                        col = 0;
                    }
                }
            }
        };

        bool IsDone()
        {
            if (row < owner.NumberOfVertices() && col < owner.NumberOfVertices())
            {
                return false;
            }
            else
                return true;
        };

        Edge &operator*()
        {
            return *owner.adjacencyMatrix[row][col];
        };

        void operator++() { next(); }
    };

    // iterator po krawedziach danego wierzcholka, czyli czytam wiersz
    class EmanEdgesIter : public Iterator<Edge>
    {
        GraphAsMatrix &owner;
        int row;
        int col;
        bool iter;

    public:
        EmanEdgesIter(GraphAsMatrix &o, int v) : owner(o), row(v), col(0)
        {
            iter = true;
            next();
        };

        void next()
        {
            if (iter)
            {
                iter = false;
                // aby przegladac pierwsza kolumne
                if (owner.adjacencyMatrix[row][col] != NULL)
                {
                    return;
                }
            }
            for (int j = col; j < owner.NumberOfVertices() - 1; j++)
            {
                if (owner.adjacencyMatrix[row][j + 1] != NULL)
                {
                    col = j + 1;
                    return;
                }
            }
            // ustawiam to zeby dac informacje metodzie isDone ze przejrzalem wszystko
            col = owner.NumberOfVertices();
        };

        bool IsDone()
        {
            if (col < owner.NumberOfVertices())
                return false;
            else
                return true;
        };
        Edge &operator*()
        {
            return *owner.adjacencyMatrix[row][col];
        };
        void operator++() { next(); }
    };

    // iterator po krawedziach dochodzacych do danego wierzcholka, czyli czytam kolumne
    class InciEdgesIter : public Iterator<Edge>
    {
        GraphAsMatrix &owner;
        int row;
        int col;
        bool iter;

    public:
        void next()
        {
            if ((row == 0) && (iter == true))
            {
                iter = false;
                // aby przegladac pierwszy wiersz
                if (owner.adjacencyMatrix[row][col] != NULL)
                {
                    return;
                }
            }
            for (int i = row; i < owner.NumberOfVertices() - 1; i++)
            {
                if (owner.adjacencyMatrix[i + 1][col] != NULL)
                {
                    row = i + 1;
                    return;
                }
            }
            // ustawiam to zeby dac informacje metodzie isDone ze przejrzalem wszystko
            row = owner.NumberOfVertices();
        };

        InciEdgesIter(GraphAsMatrix &o, int v) : owner(o), row(0), col(v)
        {
            next();
            iter = true;
        };

        bool IsDone()
        {
            if (row < owner.NumberOfVertices())
            {
                return false;
            }
            else
            {
                return true;
            }
        };

        Edge &operator*()
        {
            return *owner.adjacencyMatrix[row][col];
        };

        void operator++() { next(); }
    };

public:
    // liczba wierzcholkow, czy skierowany
    GraphAsMatrix(int n, bool b) : numberOfVertices(n), isDirected(b)
    {
        vertices.resize(n);

        for (int i = 0; i < numberOfVertices; i++)
        {
            vertices[i] = new Vertex(i);
        }

        // oczyszczam macierz sasiedztwa
        std::vector<std::vector<Edge *>> tmp_matrix(numberOfVertices, std::vector<Edge *>(numberOfVertices, NULL));
        adjacencyMatrix = tmp_matrix;

        // ustawiam tablice odwiedzonych wierzcholkow na false
        visited.resize(n);
        fill(visited.begin(), visited.end(), false);
    };

    int NumberOfVertices() { return numberOfVertices; };
    bool IsDirected() { return isDirected; };
    int NumberOfEdges() { return numberOfEdges; };

    bool IsEdge(int u, int v)
    {
        if (u < numberOfVertices && v < numberOfVertices)
        {
            if (adjacencyMatrix[u][v] != NULL)
            {
                return true;
            }
        }
        return false;
    };

    void MakeNull()
    {
        // ustawiamy liczbe krawedzi na zero i czyscimy macierz sasiedztwa
        numberOfEdges = 0;

        for (int i = 0; i < numberOfVertices; i++)
        {
            for (int j = 0; j < numberOfVertices; j++)
            {
                adjacencyMatrix[i][j] == NULL;
            }
        }
    };

    void AddEdge(int u, int v)
    {
        if (u < numberOfVertices && v < numberOfVertices)
        {
            if (adjacencyMatrix[u][v] == NULL)
            {
                Edge *edge = new Edge(vertices[u], vertices[v]);
                numberOfEdges++;
                adjacencyMatrix[u][v] = edge;
                // jesli jest nieskierowany to odbijamy symetrycznie wzgledem diagonali
                if (!isDirected)
                {
                    Edge *edge_nieskierowana = new Edge(vertices[v], vertices[u]);
                    adjacencyMatrix[v][u] = edge_nieskierowana;
                }
            }
        }
        else
        {
            cout << "Blad AddEdge" << endl;
            exit;
        }
    };

    void AddEdge(Edge *edge)
    {
        Vertex *u = edge->V0();
        Vertex *v = edge->V1();
        int u_number = v->Number();
        int v_number = u->Number();

        if (u_number < numberOfVertices && v_number < numberOfVertices)
        {
            if (adjacencyMatrix[u_number][v_number] == NULL)
            {

                numberOfEdges++;
                adjacencyMatrix[u_number][v_number] = edge;

                // jesli jest nieskierowany to odbijamy symetrycznie wzgledem diagonali
                if (!isDirected)
                {
                    adjacencyMatrix[v_number][u_number] = edge;
                }
            }
        }
        else
        {
            cout << "Blad AddEdge" << endl;
            exit;
        }
    };

    // zwraca wskaznik do krawedzi laczacej podane wierzcholki
    Edge *SelectEdge(int u, int v)
    {
        if (u < numberOfVertices && v < numberOfVertices)
        {
            return adjacencyMatrix[u][v];
        }
        else
        {
            cout << "Blad SelectEdge" << endl;
            return NULL;
        }
    };

    // zwraca wskaznik do i-tego wierzcholka grafu
    Vertex *SelectVertex(int i)
    {
        if (i >= 0 && i < numberOfVertices)
        {
            return vertices[i];
        }
        else
        {
            cout << "Blad SelectVertex" << endl;
            return NULL;
        }
    };

    // iterator po wszystkich wierzcholkach, czyli czytam caly wektor
    Iterator<Vertex> &VerticesIter()
    {
        return *new AllVerticesIter(*this);
    }

    // iterator po wszystkich krawedziach, czyli czytam cala macierz
    Iterator<Edge> &EdgesIter()
    {
        return *new AllEdgesIter(*this);
    }

    // iterator po krawedziach danego wierzcholka, czyli czytam wiersz
    Iterator<Edge> &EmanatingEdgesIter(int v)
    {
        return *new EmanEdgesIter(*this, v);
    }

    // iterator po krawedziach dochodzacych do danego wierzcholka, czyli czytam kolumne
    Iterator<Edge> &IncidentEdgesIter(int v)
    {
        return *new InciEdgesIter(*this, v);
    }

    // oznacza wszystkie wierzcholki jako nieodwiedzone i wywoluje metode DFS1
    void DFS(Vertex *v)
    {
        fill(visited.begin(), visited.end(), false);
        DFS1(v, visited);

        // jesli nie przejrzelismy wszystkich wierzcholkow to wywoluje ponownie DFS1
        for (int i = 0; i < numberOfVertices; ++i)
        {
            if (visited.at(i) == false)
            {
                DFS1(vertices.at(i), visited);
            }
        }
    }

    // rekursywne przegladanie sasiadow danego wierzcholka
    void DFS1(Vertex *v, std::vector<bool> &visited)
    {
        // wypisuje wierzcholek i ustawiam jako odwiedzony
        cout << v->Number() << endl;
        visited.at(v->Number()) = true;

        // iterator po krawedziach wychodzacych z v->Number()
        Iterator<Edge> &wychodzace = this->EmanatingEdgesIter(v->Number());

        while (!wychodzace.IsDone())
        {
            Vertex *wierzcholek = (*wychodzace).V1();
            if (visited.at(wierzcholek->Number()) == false)
            {
                DFS1(wierzcholek, visited);
            }
            ++wychodzace;
        }
        delete &wychodzace;
    }

    // zmodyfikowana metoda DFS1, zamiast wypisywania wierzcholkow zlicza ilosc przejrzen
    int DFS_visitor(Vertex *v)
    {
        fill(visited.begin(), visited.end(), false);
        CountingVisitor *visitor = new CountingVisitor;
        DFS1_visitor(visitor, v, visited);
        // zwraca liczbe przejrzanych wierzcholkow
        return visitor->amount;
    }

    void DFS1_visitor(CountingVisitor *visitor, Vertex *v, std::vector<bool> &visited)
    {
        // wywoluje metode Visit i ustawiam jako odwiedzony
        visitor->Visit();

        visited.at(v->Number()) = true;

        // iterator po krawedziach wychodzacych z v->Number()
        Iterator<Edge> &wychodzace = this->EmanatingEdgesIter(v->Number());

        while (!wychodzace.IsDone())
        {
            Vertex *wierzcholek = (*wychodzace).V1();
            if (visited.at(wierzcholek->Number()) == false)
            {
                DFS1_visitor(visitor, wierzcholek, visited);
            }
            ++wychodzace;
        }
    }

    bool IsConnected()
    {
        int ilosc = 0;
        if (!isDirected)
        {
            // nieskierowany - sprawdzanie spojnosci grafu
            ilosc = DFS_visitor(vertices.at(0));
            if (ilosc == numberOfVertices)
            {
                // graf jest spojny
                return true;
            }
            else
            {
                // graf nie jest spojny
                return false;
            }
        }
        else
        { // sprawdzanie silnej spojnosci grafu skierowanego
            for (int i = 0; i < numberOfVertices; ++i)
            {
                if (DFS_visitor(vertices.at(i)) != numberOfVertices)
                {
                    return false;
                }
            }
            // jesli od kazdego wierzcholka doszlismy do kazdego to graf jest spojny
            return true;
        }
    }
};

int main()
{
    cout << "\n\tGraf skierowany" << endl;
    GraphAsMatrix graf_skierowany = GraphAsMatrix(10, true);
    cout << "Liczba wierzcholkow: " << graf_skierowany.NumberOfVertices() << endl;
    cout << "Liczba krawedzi: " << graf_skierowany.NumberOfEdges() << endl;

    Vertex *v = graf_skierowany.SelectVertex(2);
    cout << "\nUnikalny numer: " << v->Number() << endl;
    v->weight = v->Number() * v->Number();
    cout << "Waga wierzcholka: " << v->weight << endl;

    graf_skierowany.AddEdge(1, 2);
    graf_skierowany.AddEdge(1, 2);
    graf_skierowany.AddEdge(2, 3);
    graf_skierowany.AddEdge(3, 4);
    graf_skierowany.AddEdge(9, 9);

    cout << "\nLiczba wierzcholkow: " << graf_skierowany.NumberOfVertices() << endl;
    cout << "Liczba krawedzi: " << graf_skierowany.NumberOfEdges() << endl;
    cout << "Czy istnieje krawedz (1,1) ? " << graf_skierowany.IsEdge(1, 1) << endl;
    cout << "Czy istnieje krawedz (1,2) ? " << graf_skierowany.IsEdge(1, 2) << endl;
    cout << "Czy istnieje krawedz (2,1) ? " << graf_skierowany.IsEdge(2, 1) << endl;

    Edge *e = graf_skierowany.SelectEdge(1, 2);
    cout << "\nSelectEdge(1, 2): " << endl;
    cout << "V0: " << e->V0()->Number() << endl;
    cout << "V1: " << e->V1()->Number() << endl;
    cout << "Sasiad V0: " << e->Mate(e->V0())->Number() << endl;
    cout << "Sasiad V1: " << e->Mate(e->V1())->Number() << endl;
    e->weight = e->V0()->Number() * e->V1()->Number();
    cout << "Waga krawedzi: " << e->weight << endl;

    Edge *f = graf_skierowany.SelectEdge(2, 3);
    cout << "\nSelectEdge(2, 3): " << endl;
    cout << "V0: " << f->V0()->Number() << endl;
    cout << "V1: " << f->V1()->Number() << endl;
    cout << "Sasiad V0: " << f->Mate(f->V0())->Number() << endl;
    cout << "Sasiad V1: " << f->Mate(f->V1())->Number() << endl;
    f->weight = f->V0()->Number() * f->V1()->Number();
    cout << "Waga krawedzi: " << f->weight << endl;

    Edge *g = graf_skierowany.SelectEdge(3, 4);
    cout << "\nSelectEdge(3, 4): " << endl;
    cout << "V0: " << g->V0()->Number() << endl;
    cout << "V1: " << g->V1()->Number() << endl;
    cout << "Sasiad V0: " << g->Mate(g->V0())->Number() << endl;
    cout << "Sasiad V1: " << g->Mate(g->V1())->Number() << endl;
    g->weight = g->V0()->Number() * g->V1()->Number();
    cout << "Waga krawedzi: " << g->weight << endl;

    Edge *h = graf_skierowany.SelectEdge(9, 9);
    cout << "\nSelectEdge(9, 9): " << endl;
    cout << "V0: " << h->V0()->Number() << endl;
    cout << "V1: " << h->V1()->Number() << endl;
    cout << "Sasiad V0: " << h->Mate(h->V0())->Number() << endl;
    cout << "Sasiad V1: " << h->Mate(h->V1())->Number() << endl;
    h->weight = h->V0()->Number() * h->V1()->Number();
    cout << "Waga krawedzi: " << h->weight << endl;

    // graf nieskierowany

    cout << "\n\tGraf nieskierowany" << endl;
    GraphAsMatrix graf_nieskierowany = GraphAsMatrix(10, false);
    cout << "Liczba wierzcholkow: " << graf_nieskierowany.NumberOfVertices() << endl;
    cout << "Liczba krawedzi: " << graf_nieskierowany.NumberOfEdges() << endl;

    v = graf_nieskierowany.SelectVertex(2);
    cout << "\nUnikalny numer: " << v->Number() << endl;
    v->weight = v->Number() * v->Number();
    cout << "Waga wierzcholka: " << v->weight << endl;

    graf_nieskierowany.AddEdge(1, 2);
    graf_nieskierowany.AddEdge(1, 2);
    graf_nieskierowany.AddEdge(2, 3);
    graf_nieskierowany.AddEdge(3, 4);
    graf_nieskierowany.AddEdge(9, 9);

    cout << "\nLiczba wierzcholkow: " << graf_nieskierowany.NumberOfVertices() << endl;
    cout << "Liczba krawedzi: " << graf_nieskierowany.NumberOfEdges() << endl;
    cout << "Czy istnieje krawedz (1,1) ? " << graf_nieskierowany.IsEdge(1, 1) << endl;
    cout << "Czy istnieje krawedz (1,2) ? " << graf_nieskierowany.IsEdge(1, 2) << endl;
    cout << "Czy istnieje krawedz (2,1) ? " << graf_nieskierowany.IsEdge(2, 1) << endl;

    e = graf_nieskierowany.SelectEdge(1, 2);
    cout << "\nSelectEdge(1, 2): " << endl;
    cout << "V0: " << e->V0()->Number() << endl;
    cout << "V1: " << e->V1()->Number() << endl;
    cout << "Sasiad V0: " << e->Mate(e->V0())->Number() << endl;
    cout << "Sasiad V1: " << e->Mate(e->V1())->Number() << endl;
    e->weight = e->V0()->Number() * e->V1()->Number();
    cout << "Waga krawedzi: " << e->weight << endl;

    f = graf_nieskierowany.SelectEdge(2, 3);
    cout << "\nSelectEdge(2, 3): " << endl;
    cout << "V0: " << f->V0()->Number() << endl;
    cout << "V1: " << f->V1()->Number() << endl;
    cout << "Sasiad V0: " << f->Mate(f->V0())->Number() << endl;
    cout << "Sasiad V1: " << f->Mate(f->V1())->Number() << endl;
    f->weight = f->V0()->Number() * f->V1()->Number();
    cout << "Waga krawedzi: " << f->weight << endl;

    g = graf_nieskierowany.SelectEdge(3, 4);
    cout << "\nSelectEdge(3, 4): " << endl;
    cout << "V0: " << g->V0()->Number() << endl;
    cout << "V1: " << g->V1()->Number() << endl;
    cout << "Sasiad V0: " << g->Mate(g->V0())->Number() << endl;
    cout << "Sasiad V1: " << g->Mate(g->V1())->Number() << endl;
    g->weight = g->V0()->Number() * g->V1()->Number();
    cout << "Waga krawedzi: " << g->weight << endl;

    h = graf_nieskierowany.SelectEdge(9, 9);
    cout << "\nSelectEdge(9, 9): " << endl;
    cout << "V0: " << h->V0()->Number() << endl;
    cout << "V1: " << h->V1()->Number() << endl;
    cout << "Sasiad V0: " << h->Mate(h->V0())->Number() << endl;
    cout << "Sasiad V1: " << h->Mate(h->V1())->Number() << endl;
    h->weight = h->V0()->Number() * h->V1()->Number();
    cout << "Waga krawedzi: " << h->weight << endl;

    // nowe testy - Iteratory

    // najpierw dla grafu skierowanego
    cout << "\n\tGraf skierowany" << endl;
    cout << "\nIterator po wierzcholkach" << endl;
    Iterator<Vertex> &wierzcholki = graf_skierowany.VerticesIter();

    while (!wierzcholki.IsDone())
    {
        cout << "Numer: " << (*wierzcholki).Number() << " Waga: " << (*wierzcholki).weight << endl;
        ++wierzcholki;
    }
    delete &wierzcholki;

    graf_skierowany.AddEdge(3, 5);
    graf_skierowany.AddEdge(8, 3);
    graf_skierowany.AddEdge(5, 2);

    cout << "\nIterator po wszystkich krawedziach" << endl;
    Iterator<Edge> &wszystkie_krawedzie = graf_skierowany.EdgesIter();

    while (!wszystkie_krawedzie.IsDone())
    {
        cout << "V0: " << (*wszystkie_krawedzie).V0()->Number() << " V1: " << (*wszystkie_krawedzie).V1()->Number() << endl;
        ++wszystkie_krawedzie;
    }
    delete &wszystkie_krawedzie;

    cout << "\nIterator po krawedziach wychodzacych z wierzcholka nr 3" << endl;
    Iterator<Edge> &wychodzace = graf_skierowany.EmanatingEdgesIter(3);

    while (!wychodzace.IsDone())
    {
        cout << "V0: " << (*wychodzace).V0()->Number() << " V1: " << (*wychodzace).V1()->Number() << endl;
        ++wychodzace;
    }
    delete &wychodzace;

    cout << "\nIterator po krawedziach dochodzacych do wierzcholka nr 2" << endl;
    Iterator<Edge> &dochodzace = graf_skierowany.IncidentEdgesIter(2);

    while (!dochodzace.IsDone())
    {
        cout << "V0: " << (*dochodzace).V0()->Number() << " V1: " << (*dochodzace).V1()->Number() << endl;
        ++dochodzace;
    }
    delete &dochodzace;

    // graf nieskierowany
    cout << "\n\tGraf nieskierowany" << endl;
    cout << "\nIterator po wierzcholkach" << endl;
    wierzcholki = graf_nieskierowany.VerticesIter();

    while (!wierzcholki.IsDone())
    {
        cout << "Numer: " << (*wierzcholki).Number() << " Waga: " << (*wierzcholki).weight << endl;
        ++wierzcholki;
    }
    delete &wierzcholki;

    graf_nieskierowany.AddEdge(3, 5);
    graf_nieskierowany.AddEdge(8, 3);
    graf_nieskierowany.AddEdge(5, 2);

    cout << "\nIterator po wszystkich krawedziach" << endl;
    wszystkie_krawedzie = graf_nieskierowany.EdgesIter();

    while (!wszystkie_krawedzie.IsDone())
    {
        cout << "V0: " << (*wszystkie_krawedzie).V0()->Number() << " V1: " << (*wszystkie_krawedzie).V1()->Number() << endl;
        ++wszystkie_krawedzie;
    }
    delete &wszystkie_krawedzie;

    cout << "\nIterator po krawedziach wychodzacych z wierzcholka nr 3" << endl;
    Iterator<Edge> &wychodzacea = graf_nieskierowany.EmanatingEdgesIter(3);

    while (!wychodzacea.IsDone())
    {
        cout << "V0: " << (*wychodzacea).V0()->Number() << " V1: " << (*wychodzacea).V1()->Number() << endl;
        ++wychodzacea;
    }
    delete &wychodzacea;

    cout << "\nIterator po krawedziach dochodzacych do wierzcholka nr 2" << endl;
    Iterator<Edge> &dochodzacea = graf_nieskierowany.IncidentEdgesIter(2);

    while (!dochodzacea.IsDone())
    {
        cout << "V0: " << (*dochodzacea).V0()->Number() << " V1: " << (*dochodzacea).V1()->Number() << endl;
        ++dochodzacea;
    }
    delete &dochodzacea;

    // DFS (przegladanie w glab)
    cout << "\nDFS graf nieskierowany:" << endl;
    GraphAsMatrix graph = GraphAsMatrix(10, false);
    graph.AddEdge(0, 1);
    graph.AddEdge(1, 2);
    graph.AddEdge(2, 3);
    graph.AddEdge(3, 4);
    graph.AddEdge(3, 7);
    graph.AddEdge(4, 5);
    graph.AddEdge(5, 9);
    graph.AddEdge(9, 9);
    graph.AddEdge(6, 8);
    graph.AddEdge(8, 6);
    graph.AddEdge(0, 8);

    graph.DFS(graph.SelectVertex(0));

    cout << "\nDFS graf skierowany:" << endl;
    GraphAsMatrix graphDir = GraphAsMatrix(10, true);
    graphDir.AddEdge(0, 1);
    graphDir.AddEdge(1, 2);
    graphDir.AddEdge(2, 3);
    graphDir.AddEdge(3, 4);
    graphDir.AddEdge(3, 7);
    graphDir.AddEdge(4, 5);
    graphDir.AddEdge(5, 9);
    graphDir.AddEdge(9, 9);
    graphDir.AddEdge(6, 8);
    graphDir.AddEdge(8, 6);
    graphDir.AddEdge(0, 8);

    graphDir.DFS(graphDir.SelectVertex(0));

    // sprawdzenie spojnosci grafow
    cout << "\nSprawdzenie spojnosci grafu nieskierowanego: " << endl;
    cout << ((graph.IsConnected() == 1) ? "\tGraf jest spojny\n" : "\tGraf nie jest spojny\n");
    graph.AddEdge(0, 8);
    cout << "Dodano krawedz (0, 8): " << endl;
    cout << ((graph.IsConnected() == 1) ? "\tGraf jest spojny\n" : "\tGraf nie jest spojny\n");

    cout << "\nSprawdzenie spojnosci grafu skierowanego: " << endl;
    graphDir.AddEdge(0, 8);
    graphDir.AddEdge(6, 0);
    graphDir.AddEdge(9, 0);
    cout << ((graphDir.IsConnected() == 1) ? "\tGraf jest spojny\n" : "\tGraf nie jest spojny\n");
    graphDir.AddEdge(7, 0);
    cout << "Dodano krawedz (7, 0): " << endl;
    cout << ((graphDir.IsConnected() == 1) ? "\tGraf jest spojny\n" : "\tGraf nie jest spojny\n");
    // graphDir.DFS_visitor(graphDir.SelectVertex(7));

    // Iterator<Edge> &sra = graphDir.EmanatingEdgesIter(7);
    // while (!sra.IsDone())
    // {
    //     cout << "V0: " << (*sra).V0()->Number() << " V1: " << (*sra).V1()->Number() << endl;
    //     ++sra;
    // }
    // delete &sra;

    return 0;
}