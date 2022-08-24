#include "AdjacencyListGraph.hpp"
#include "../stack/stack.hpp"
#include "../stack/stack.cpp"
#include "../queue/queue.hpp"
#include "../queue/queue.cpp"
#include <limits>
#include <iostream>

template <typename Tv, typename Te>
AL_Graph<Tv, Te>::AL_Graph() {}

template <typename Tv, typename Te>
AL_Graph<Tv, Te>::~AL_Graph()
{
    for (int i = 0; i < vertices.size(); i++)
    {
        Node *tmp = (vertices[i]).next;

        if (tmp == nullptr)
            continue;

        while ((*tmp).next != nullptr)
        {
            Node *tmp_next = tmp->next;
            delete tmp;
            tmp = tmp_next;
        }

        delete tmp;
    }
}

template <typename Tv, typename Te>
AL_Graph<Tv, Te>::Vertex::Vertex() : graph(nullptr), index(-1) {}

template <typename Tv, typename Te>
AL_Graph<Tv, Te>::Vertex::Vertex(const AL_Graph *_graph, int _index) : graph(_graph), index(_index) {}

template <typename Tv, typename Te>
inline Tv &AL_Graph<Tv, Te>::Vertex::operator*() const
{
    return (*graph).vertices[index].v;
}

template <typename Tv, typename Te>
inline bool AL_Graph<Tv, Te>::Vertex::isAdjacentTo(const Vertex &u) const
{
    if (index == -1)
        return 0;

    Node *tmp = (vertices.at(index)).next;

    while (tmp != nullptr)
    {
        if ((*tmp).index == u.index)
            return 1;
        tmp = (*tmp).next;
    }

    return 0;
}

template <typename Tv, typename Te>
AL_Graph<Tv, Te>::Edge::Edge(int _org, int _des, const Te &_weight) : org(_org), des(_des), weight(_weight) {}

template <typename Tv, typename Te>
typename AL_Graph<Tv, Te>::Edge AL_Graph<Tv, Te>::getEdge(Vertex const &origin, Vertex const &destination) const
{
    if (origin.index >= vertices.size() || origin.index >= vertices.size())
        throw AL_Graph_error("invaild vertex");

    Node *tmp = (vertices[origin.index]).next;

    while (tmp != nullptr)
    {
        if ((*tmp).index == destination.index)
        {
            return Edge(origin.index, destination.index, (*tmp).weight);
        }

        tmp = (*tmp).next;
    }

    throw AL_Graph_error("invaild vertex");
}

template <typename Tv, typename Te>
AL_Graph<Tv, Te>::Node::Node(int _index, Te _weight) : index(_index), weight(_weight), next(nullptr) {}

template <typename Tv, typename Te>
AL_Graph<Tv, Te>::Header::Header(Tv _v) : v(_v), next(nullptr) {}

template <typename Tv, typename Te>
bool AL_Graph<Tv, Te>::empty() const { return vertices.empty(); }

template <typename Tv, typename Te>
inline void AL_Graph<Tv, Te>::insertVertex(const Tv &val)
{
    vertices.push_back(Header(val));
}

template <typename Tv, typename Te>
inline void AL_Graph<Tv, Te>::insertEdge(const Vertex &u, const Vertex &w, const Te &val)
{
    if (u.index >= vertices.size() || w.index >= vertices.size())
        throw AL_Graph_error("invalid vertex");
    if (u.index == w.index)
        throw AL_Graph_error("not allow self-loop");

    Node *tmp = (vertices.at(u.index)).next;

    if (tmp == nullptr)
    {
        (vertices.at(u.index)).next = new Node{w.index, val};
        return;
    }

    while (true)
    {
        if ((*tmp).index == w.index)
            throw AL_Graph_error("exist edge");

        if ((*tmp).next == nullptr)
        {
            (*tmp).next = new Node{w.index, val};
            return;
        }
        else
        {
            tmp = (*tmp).next;
        }
    }
}

template <typename Tv, typename Te>
inline void AL_Graph<Tv, Te>::eraseVertex(Vertex &u)
{
    if (u.index >= vertices.size() || u.index < 0)
        throw AL_Graph_error("invaild vertex");

    vertices.erase(u.index);

    for (int i = 0; i < vertices.size(); i++)
    {
        Node *tmp = (vertices[i]).next;
        if (tmp == nullptr)
            continue;
        else if ((*tmp).next == nullptr && (*tmp).index == u.index)
        {
            (vertices[i]).next = nullptr;
            delete tmp;
            continue;
        }

        while ((*tmp).next != nullptr)
        {
            if (tmp->next->index == u.index)
            {
                Node *tmp_next_next = tmp->next->next;
                delete tmp->next;
                tmp->next = tmp_next_next;
            }
            else
            {
                tmp = tmp->next;
            }
        }
    }

    u.index = -1;
    u.graph = nullptr;

    //u.~Vertex(); 이게 왜 안돼지?
}

template <typename Tv, typename Te>
inline void AL_Graph<Tv, Te>::eraseEdge(const Edge &e)
{
    if (e.org >= vertices.size() || e.des >= vertices.size())
        throw AL_Graph_error("invaild vertex");

    Node *tmp = (vertices[e.org]).next;
    if (tmp == nullptr)
        throw AL_Graph_error("invaild Edge");
    else if ((*tmp).next == nullptr && (*tmp).index == e.des)
    {
        (vertices[e.org]).next = nullptr;
        delete tmp;
        return;
    }

    while ((*tmp).next != nullptr)
    {
        if (tmp->next->index == e.des)
        {
            Node *tmp_next_next = tmp->next->next;
            delete tmp->next;
            tmp->next = tmp_next_next;
            return;
        }
        else
        {
            tmp = tmp->next;
        }
    }

    throw AL_Graph_error("invaild vertex");
}

template <typename Tv, typename Te>
Vector<typename AL_Graph<Tv, Te>::Vertex> AL_Graph<Tv, Te>::getVertices() const
{
    Vector<Vertex> tmp;
    tmp.reserve(vertices.size());
    for (int i = 0; i < vertices.size(); i++)
        tmp.push_back(Vertex(this, i));
    return tmp;
}

template <typename Tv, typename Te>
Vector<typename AL_Graph<Tv, Te>::Vertex> AL_Graph<Tv, Te>::DFS(const Vertex &u) const
{
    Vector<Vertex> vec;
    Stack<unsigned int> stack;
    bool *label = new bool[vertices.size()]{false};

    unsigned int next_index = u.index;

    do
    {
        if (!label[next_index]) // 방문하지 않았다면
        {
            vec.push_back((Vertex(this, next_index)));
            stack.push(next_index);
            label[next_index] = true;
        }
        else // 방문했다면
        {
            Node *tmp = vertices[next_index].next;
            if (!tmp)
            {
                stack.pop();
                if (stack.empty())
                {
                    delete[] label;
                    return vec;
                }
                next_index = stack.top();
                continue;
            }
            next_index = (*tmp).index;

            while (label[next_index])
            {
                if (!(tmp = (*tmp).next))
                {
                    stack.pop();
                    if (stack.empty())
                    {
                        delete[] label;
                        return vec;
                    }
                    next_index = stack.top();
                    break;
                }
                next_index = (*tmp).index;
            }
        }
    } while (true);
}

template <typename Tv, typename Te>
Vector<typename AL_Graph<Tv, Te>::Vertex> AL_Graph<Tv, Te>::BFS(const Vertex &u) const
{
    Vector<Vertex> vec;
    Queue<unsigned int> queue;
    bool *label = new bool[vertices.size()]{false};

    queue.push(u.index);
    unsigned int next_index;

    do
    {
        next_index = queue.pop();

        if (!label[next_index]) // 방문하지 않았다면
        {
            vec.push_back((Vertex(this, next_index)));
            Node *tmp = vertices[next_index].next;
            while (tmp)
            {
                queue.push((*tmp).index);
                tmp = (*tmp).next;
            }
            label[next_index] = true;
        }
    } while (!queue.empty());

    delete[] label;
    return vec;
}

template <typename Tv, typename Te>
void AL_Graph<Tv, Te>::Dijkstra(const Vertex &u) const
{
    Te *arr = (Te *)malloc(sizeof(Te) * vertices.size());
    bool *label = (bool *)calloc(vertices.size(), sizeof(bool));
    unsigned int *T = (unsigned int *)malloc(vertices.size() * sizeof(unsigned int));
    for(unsigned int i = 0; i < vertices.size(); i++) T[i] = std::numeric_limits<unsigned int>::max();

    Te MAX = std::numeric_limits<Te>::max(); // Te 자료형의 최대값을 반환하는 numeric_limits
    if (MAX == 0)
    {
        std::cerr << "Error : can't find MAX of weight";
        return;
    }

    unsigned int start = u.index;
    for (unsigned int i = 0; i < vertices.size(); i++) { arr[i] = MAX; }

    arr[start] = 0;

    Node *next = vertices[start].next;
    if (next == NULL) { return; }

    while (next)
    {
        arr[(*next).index] = (*next).weight;
        T[(*next).index] = start;
        next = (*next).next;
    }

    label[start] = true;

    unsigned int n = vertices.size() - 1;

    while (n--)
    {
        unsigned int sel;

        for (unsigned int i = 0; i < vertices.size(); i++)
        {
            if (label[i] == false)
            {
                sel = i;
                break;
            }
        }

        for (unsigned int i = sel + 1; i < vertices.size(); i++) { sel = (arr[sel] < arr[i]) ? sel : (label[i]) ? sel : i; }
        label[sel] = true;

        Node *next = vertices[sel].next;

        while (next)
        {
            if ((*next).weight + arr[sel] < arr[(*next).index])
            {
                arr[(*next).index] = (*next).weight + arr[sel];
                T[(*next).index] = sel;
            }

            next = (*next).next;
        }
    }

    Vector<Tv> path;
    for (unsigned int i = 0; i < vertices.size(); i++)
    {
        path.clear();

        std::cout << vertices[i].v << " : " << arr[i];
        std::cout << "\t\t|\t";

        unsigned int tmp = i;

        while (T[tmp] != std::numeric_limits<unsigned int>::max())
        {
            path.push_back(vertices[tmp].v);
            tmp = T[tmp];
        }

        path.push_back(vertices[start].v);

        for (unsigned int i = path.size() - 1; i != 0; i--)
            std::cout << path[i] << ' ';
        std::cout << path[0];
        std::cout << '\n';
    }
}