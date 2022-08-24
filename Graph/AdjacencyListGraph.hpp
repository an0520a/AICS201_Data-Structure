#ifndef AdjacencyListGraph_H
#define AdjacencyListGraph_H

#include <string>
#include <exception>
#include "../vector/vector.hpp"
#include "../vector/vector.cpp"

class AL_Graph_error : public std::exception
{
public:
    AL_Graph_error(const std::string &_errorMessage) : errorMessage("AL_Graph error : " + _errorMessage) {}
    const char *what() const throw() override { return errorMessage.c_str(); }

private:
    std::string errorMessage;
};

// Direct Graph
template <typename Tv, typename Te>
class AL_Graph
{
public:
    AL_Graph();
    ~AL_Graph();
    class Vertex
    {
        friend AL_Graph;

    public:
        Vertex();
        Tv &operator*() const;
        bool isAdjacentTo(const Vertex &u) const;

    private:
        Vertex(const AL_Graph *_graph, int _index);
        const AL_Graph *graph;
        int index;
    };

    class Edge
    {
        friend AL_Graph;

    private:
        Edge(int _org = -1, int _des = -1, const Te &_wegiht = (Te)NULL);
        int org;
        int des;
        Te weight;
    };

    bool empty() const;
    void insertVertex(const Tv &val);
    void insertEdge(const Vertex &origin, const Vertex &destination, const Te &val);
    void eraseVertex(Vertex &u);
    void eraseEdge(const Edge &e);
    Edge getEdge(Vertex const &origin, Vertex const &destination) const;
    Vector<Vertex> getVertices() const;
    Vector<Vertex> DFS(const Vertex &u) const;
    Vector<Vertex> BFS(const Vertex &u) const;
    void Dijkstra(const Vertex &u) const;

private:
    class Node
    {
        friend AL_Graph;

    private:
        Node(int _index, Te _weight);
        int index;
        Te weight;
        Node *next;
    };

    class Header
    {
        friend AL_Graph;

    private:
        Header(Tv _v);
        Tv v;
        Node *next;
    };

    Vector<Header> vertices;
};
#endif