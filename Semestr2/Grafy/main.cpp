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

public:
    class AllVerticesIter : public Iterator<Vertex>
    {
        GraphAsMatrix &owner;
        int current;

    public:
        AllVerticesIter(GraphAsMatrix &o) : owner(o), current(0){};

        bool IsDone()
        {
            if (current < owner.NumberOfVertices())
            {
                return false;
            }
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

    class AllEdgesIter : public Iterator<Edge>
    {
        GraphAsMatrix &owner;
        int row;
        int col;

    public:
        void next()
        {

            for (int i = row; i < owner.NumberOfVertices(); i++)
            {
                for (int j = col; j < owner.NumberOfVertices(); j++)
                {
                    if (owner.adjacencyMatrix[i][j] != NULL)
                    {
                        row = i;
                        col = j;
                        break;
                    }
                }
            }
        };
        AllEdgesIter(GraphAsMatrix &o) : owner(o), row(0), col(0)
        {
            this->next();
        };

        bool IsDone()
        {
            if (row >= owner.NumberOfVertices() && col >= owner.NumberOfVertices())
            {
                return true;
            }
            else
                return false;
        };

        Edge &operator*()
        {
            return *owner.adjacencyMatrix[row][col];
        };

        void operator++()
        {
            next();
        }
    };

    class EmanEdgesIter : public Iterator<Edge>
    {
        GraphAsMatrix &owner;
        int row;
        int col;

    public:
        void next(){

            // napisac

        };
        EmanEdgesIter(GraphAsMatrix &o, int v) : owner(o), row(v), col(0)
        {
            this->next();
        };
        bool IsDone()
        {
            if (col >= owner.NumberOfVertices())
            {
                return true;
            }
            else
                return false;
        };
        Edge &operator*()
        {
            return *owner.adjacencyMatrix[row][col];
        };
        void operator++() { next(); }
    };

    class InciEdgesIter : public Iterator<Edge>
    {
        GraphAsMatrix &owner;
        int row;
        int col;

    public:
        void next(){

            // napisac

        };
        InciEdgesIter(GraphAsMatrix &o, int v) : owner(o), row(0), col(v){};
        bool IsDone()
        {
            if (row >= owner.NumberOfVertices())
            {
                return true;
            }
            else
            {
                return false;
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
        adjacencyMatrix.resize(n);

        for (int i = 0; i < numberOfVertices; i++)
        {
            vertices[i] = new Vertex(i);
        }

        for (int i = 0; i < numberOfVertices; i++)
        {
            adjacencyMatrix[i].resize(numberOfVertices);

            for (int j = 0; j < numberOfVertices; j++)
            {
                adjacencyMatrix[i][j] == NULL;
            }
        }
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
                    adjacencyMatrix[v][u] = edge;
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

    Iterator<Vertex> &VerticesIter();
    Iterator<Edge> &EdgesIter();
    Iterator<Edge> &EmanatingEdgesIter(int v);
    Iterator<Edge> &IncidentEdgesIter(int v);
};

int main()
{
    cout << "\nGraf skierowany" << endl;
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

    return 0;
}