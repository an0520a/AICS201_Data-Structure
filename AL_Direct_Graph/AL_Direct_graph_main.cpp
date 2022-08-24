#include <iostream>
#include "AL_Direct_graph.hpp"
#include "AL_Direct_graph.cpp"

using namespace std;

int main()
{
    AL_Direct_Graph<unsigned int, unsigned int> graph;

    for (unsigned int i = 0; i < 5; i++)
        graph.insertVertex(i);

    Vector<AL_Direct_Graph<unsigned int, unsigned int>::Vertex> vertices = graph.getVertices();

    for (unsigned int i = 0; i < vertices.size(); i++)
    {
        cout << vertices[i].getKey() << endl;
    }

    graph.insertEdge(vertices[0], 0, vertices[1]);
    graph.insertEdge(vertices[1], 0, vertices[0]); // 0 - 1
    graph.insertEdge(vertices[1], 0, vertices[2]);
    graph.insertEdge(vertices[2], 0, vertices[1]); // 1 - 2
    graph.insertEdge(vertices[2], 0, vertices[3]);
    graph.insertEdge(vertices[3], 0, vertices[2]); // 2 - 3
    graph.insertEdge(vertices[0], 0, vertices[2]);
    graph.insertEdge(vertices[2], 0, vertices[0]); // 0 - 2
    graph.insertEdge(vertices[2], 0, vertices[4]);
    graph.insertEdge(vertices[4], 0, vertices[2]); // 2 - 4
    graph.insertEdge(vertices[0], 0, vertices[4]);
    graph.insertEdge(vertices[4], 0, vertices[0]); // 0 - 1

    //cout << vertices[0].isAdjacentTo(vertices[3]) << endl;

    Vector<AL_Direct_Graph<unsigned int, unsigned int>::Vertex> BFS_Verteics = graph.BFS(vertices[0]);

    for (unsigned int i = 0; i < BFS_Verteics.size(); i++)
    {
        cout << *BFS_Verteics[i] << endl;
    }

    graph.eraseVertex(vertices[0]);
}