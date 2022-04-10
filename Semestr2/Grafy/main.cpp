#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

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

    /*
            class AllVerticesIter : public Iterator<Vertex>
            {
                GraphAsMatrix &owner;
                int current;

            public:
                AllVerticesIter(GraphAsMatrix &owner);
                bool IsDone();
                Vertex &operator*();
                void operator++();
            };
            class AllEdgesIter : public Iterator<Edge>
            {
                GraphAsMatrix &owner;
                int row;
                int col;

            public:
                void next();
                AllEdgesIter(GraphAsMatrix &owner);
                bool IsDone();
                Edge &operator*();
                void operator++() { next(); }
            };
            class EmanEdgesIter : public Iterator<Edge>
            {
                GraphAsMatrix &owner;
                int row;
                int col;

            public:
                void next();
                EmanEdgesIter(GraphAsMatrix &owner, int v);
                bool IsDone();
                Edge &operator*();
                void operator++() { next(); }
            };
            class InciEdgesIter : public Iterator<Edge>
            {
                GraphAsMatrix &owner;
                int row;
                int col;

            public:
                void next();
                InciEdgesIter(GraphAsMatrix &owner, int v);
                bool IsDone();
                Edge &operator*();
                void operator++() { next(); }
            };
    */

public:
    // liczba wierzcholkow, czy skierowany
    GraphAsMatrix(int n, bool b) : numberOfVertices(n), isDirected(b)
    {
        vertices.resize(n);
        adjacencyMatrix.resize(n);

        for (int i = 0; i < numberOfVertices; i++)
        {
            vertices[i] = NULL;
            adjacencyMatrix.resize(numberOfVertices);

            for (int j = 0; j < numberOfVertices; j++)
            {
                adjacencyMatrix[i][j] == NULL;
            }
        }

        for (int i = 0; i < numberOfVertices; i++)
        {
            vertices[i] = new Vertex(i);
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
            exit;
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
            exit;
        }
    };

    /*
            Iterator<Vertex> &VerticesIter();
            Iterator<Edge> &EdgesIter();
            Iterator<Edge> &EmanatingEdgesIter(int v);
            Iterator<Edge> &IncidentEdgesIter(int v);
    */
};