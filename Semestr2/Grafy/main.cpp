#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

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

class Edge
{
protected:
    Vertex *v0;
    Vertex *v1;

public:
    int weight;
    std::string label;
    Edge(Vertex *V0, Vertex *V1);
    Vertex *V0() { return v0; };
    Vertex *V1() { return v1; };

    // zwraca drugi wierzcholek krawedzi
    Vertex *Mate(Vertex *v){

    };
};

class GraphAsMatrix
{
    std::vector<Vertex *> vertices;                   // vector wierzcholkow grafu
    std::vector<std::vector<Edge *>> adjacencyMatrix; // macierz sasiedztwa
    bool isDirected;
    int numberOfVertices;
    int numberOfEdges = 0;

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
        // tworzymy vector wierzcholkow, unikalne numery od 0 do n
        // tworzymy macierz sasiedztwa ustawiajac ja na null, potem metoda
        // addedges bedziemy dodawac krawedzie
        for (int i = 0; i < numberOfVertices; i++)
        {
            vertices.push_back();
        }

        //ustawiamy macierz sasiedztwa na zera
        fill(adjacencyMatrix.begin(), adjacencyMatrix.end(), 0);
    };

    int NumberOfVertices() { return numberOfVertices; };
    bool IsDirected() { return isDirected; };
    int NumberOfEdges() { return numberOfEdges; };

    bool IsEdge(int u, int v);
    void MakeNull();
    void AddEdge(int u, int v);
    void AddEdge(Edge *edge);
    Edge *SelectEdge(int u, int v){

    };

    // zwraca wskaznik do v-tego wierzcholka grafu
    Vertex *SelectVertex(int v)
    {
        if (v >= 0 && v < numberOfVertices)
        {
            return vertices[v];
        }
        else
        {
            cout << "Blad" << endl;
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