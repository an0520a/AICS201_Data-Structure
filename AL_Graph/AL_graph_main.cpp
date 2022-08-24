#include <iostream>
#include "AL_graph.hpp"
#include "AL_graph.cpp"

int main()
{
    AL_Graph<unsigned int, unsigned int> graph;

    unsigned int n, m;
    scanf(" %u", &n);

    graph.insertVertex(0);

    for (unsigned int i = 1; i <= n; i++) graph.insertVertex(i);

    Vector<AL_Direct_Graph<unsigned int, unsigned int>::Vertex> vertices = graph.getVertices();

    scanf(" %u", &m);

    while(m--)
    {
        unsigned int u, v;
        scanf(" %u %u", &u, &v);

        graph.insertEdge(vertices[u], 0, vertices[v]);
    }

    Vector<AL_Direct_Graph<unsigned int, unsigned int>::Vertex> BFS_Verteics = graph.BFS(vertices[0]);

    if (m == 0) printf("0\n");
    else        printf("%u\n", n - BFS_Verteics.size() - 2);
}