#include <iostream>
#include <vector>

using namespace std;

class Vertex
{
    int number;

public:
    int weight;
    std::string label;
    Vertex(int n);
    int Number() const;
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
    Vertex *Mate(Vertex *v);
};

class GraphAsMatrix
{
    std::vector<Vertex *> vertices;
    std::vector<std::vector<Edge *>> adjacencyMatrix;
    bool isDirected;
    int numberOfVertices;
    int numberOfEdges = 0;

    //     class AllVerticesIter : public Iterator<Vertex>
    //     {
    //         GraphAsMatrix &owner;
    //         int current;

    //     public:
    //         AllVerticesIter(GraphAsMatrix &owner);
    //         bool IsDone();
    //         Vertex &operator*();
    //         void operator++();
    //     };
    //     class AllEdgesIter : public Iterator<Edge>
    //     {
    //         GraphAsMatrix &owner;
    //         int row;
    //         int col;

    //     public:
    //         void next();
    //         AllEdgesIter(GraphAsMatrix &owner);
    //         bool IsDone();
    //         Edge &operator*();
    //         void operator++() { next(); }
    //     };
    //     class EmanEdgesIter : public Iterator<Edge>
    //     {
    //         GraphAsMatrix &owner;
    //         int row;
    //         int col;

    //     public:
    //         void next();
    //         EmanEdgesIter(GraphAsMatrix &owner, int v);
    //         bool IsDone();
    //         Edge &operator*();
    //         void operator++() { next(); }
    //     };
    //     class InciEdgesIter : public Iterator<Edge>
    //     {
    //         GraphAsMatrix &owner;
    //         int row;
    //         int col;

    //     public:
    //         void next();
    //         InciEdgesIter(GraphAsMatrix &owner, int v);
    //         bool IsDone();
    //         Edge &operator*();
    //         void operator++() { next(); }
    //     };

    // public:
    //     GraphAsMatrix(int n, bool b);
    //     int NumberOfVertices();
    //     bool IsDirected();
    //     int NumberOfEdges();
    //     bool IsEdge(int u, int v);
    //     void MakeNull();
    //     void AddEdge(int u, int v);
    //     void AddEdge(Edge *edge);
    //     Edge *SelectEdge(int u, int v);
    //     Vertex *SelectVertex(int v);

    //     Iterator<Vertex> &VerticesIter();
    //     Iterator<Edge> &EdgesIter();
    //     Iterator<Edge> &EmanatingEdgesIter(int v);
    //     Iterator<Edge> &IncidentEdgesIter(int v);
};