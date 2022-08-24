#pragma once

#include <exception>
#include <string>
#include "../vector/vector.hpp"
#include "../vector/vector.cpp"
#include "../queue/queue.hpp"
#include "../queue/queue.cpp"

class AL_Direct_Graph_error : public std::exception
{
public:
    AL_Direct_Graph_error(const std::string &_errorMessage) : errorMessage("AL_Direct_Graph error : " + _errorMessage) {}
    const char *what() const throw() override { return errorMessage.c_str(); }

private:
    std::string errorMessage;
};

template <typename TV, typename TE>
class AL_Direct_Graph
{
    class Node;
    class Header;

public:
    class Vertex;
    class Edge;

    AL_Direct_Graph();
    ~AL_Direct_Graph();
    bool empty() const;
    void insertVertex(const TV &val); // val must be unique
    void insertEdge(const Vertex &org, const TE &wgt, const Vertex &dst);
    Edge getEdges(const Vertex &u, const Vertex &v);
    Vertex getVertex(const TV &val);
    void eraseVertex(const Vertex &v);
    void eraseVertex(const TV &v);
    void eraseEdge(const Edge &e);
    Vector<Vertex> getVertices();
    //Vector<Vertex> BFS(const Vertex &org) const;
    Vector<Vertex> BFS(const Vertex &org) const;

    class Vertex
    {
    public:
        Vertex();
        unsigned int inDegree();
        unsigned int outDegree();
        unsigned int Degree();
        unsigned int getKey() { return header->key; }
        const TV &operator*() const;
        bool isAdjacentTo(const Vertex &u) const;

    private:
        Vertex(Header *header);
        Header *header;
        friend class AL_Direct_Graph;
    };

    class Edge
    {
    private:
        Edge(Header *org, const TE &wgt, Header *dst);
        Header *org, dst;
        TE weight;
        friend class AL_Direct_Graph;
    };

private:
    class Node
    {
    private:
        Node(Header *toHeader, const TE &wgt);
        TE weight;
        Header *nextHeader;
        Node *nextNode;
        friend class AL_Direct_Graph;
    };

    class Header
    {
    private:
        Header(const unsigned int &key, const TV &val = (TV)NULL);
        bool operator==(const Header &header) const;
        unsigned int key;
        TV val;
        Node *next;
        friend class AL_Direct_Graph;
    };

    unsigned int getKey();
    unsigned int max_Key;
    Vector<Header *> headerVec;
    Queue<unsigned int> keyStorage;
};