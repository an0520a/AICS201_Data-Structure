#include "AL_Direct_graph.hpp"

template <typename TV, typename TE>
AL_Direct_Graph<TV, TE>::AL_Direct_Graph() : max_Key(0) {}

template <typename TV, typename TE>
AL_Direct_Graph<TV, TE>::~AL_Direct_Graph()
{
    unsigned int size = headerVec.size();

    for (unsigned i = 0; i < size; i++)
    {
        Node *next = (*headerVec[i]).next;
        Node *next_next;

        delete headerVec[i];

        if (next == nullptr)
            continue;

        while (next != nullptr)
        {
            next_next = (*next).nextNode;
            delete next;
            next = next_next;
        }
    }
}

template <typename TV, typename TE>
bool AL_Direct_Graph<TV, TE>::empty() const { return headerVec.size(); }

template <typename TV, typename TE>
void AL_Direct_Graph<TV, TE>::insertVertex(const TV &val)
{
    unsigned int tmp = getKey();
    if (tmp == max_Key + 1) max_Key++;
    headerVec.push_back(new Header(tmp, val));
}

template <typename TV, typename TE>
void AL_Direct_Graph<TV, TE>::insertEdge(const Vertex &org, const TE &wgt, const Vertex &dst)
{
    if (!org.header || !dst.header)
        throw AL_Direct_Graph_error("Does not exist org or dst");

    if ((*org.header).next == nullptr)
    {
        (*org.header).next = new Node(dst.header, wgt);
        return;
    }

    Node *next = (*org.header).next;

    while ((*next).nextNode != nullptr)
    {
        next = (*next).nextNode;
    }

    (*next).nextNode = new Node(dst.header, wgt);
}

template <typename TV, typename TE>
typename AL_Direct_Graph<TV, TE>::Edge AL_Direct_Graph<TV, TE>::getEdges(const Vertex &org, const Vertex &dst)
{
    if ((!org.header || !dst.header) || (*org.header).next == nullptr)
        throw AL_Direct_Graph_error("Does not exist edge what org to dst");

    Node *next = (*org.header).next;

    while (next != nullptr)
    {
        if ((*next).nextHeader == dst.header)
            return Edge(org.header, (*next).weight, dst.header);
        next = (*next).nextNode;
    }

    throw AL_Direct_Graph_error("Does not exist edge what org to dst");
}

template <typename TV, typename TE>
typename AL_Direct_Graph<TV, TE>::Vertex AL_Direct_Graph<TV, TE>::getVertex(const TV &val)
{
    unsigned int size = headerVec.size();

    for (unsigned int i = 0; i < size; i++)
        if ((*headerVec[i]).val == val)
            return Vertex((*headerVec[i]).header);

    throw AL_Direct_Graph_error("Does not exist vertex");
}

template <typename TV, typename TE>
void AL_Direct_Graph<TV, TE>::eraseVertex(const Vertex &v)
{
    if (v.header == nullptr)
        throw AL_Direct_Graph_error("Does not exist what to erase Vertex");

    unsigned int vecSize = headerVec.size();
    unsigned int n;

    bool flag = false;

    for (unsigned int i = 0; i < vecSize; i++)
    {
        if (headerVec[i] == v.header)
        {
            n = i;
            flag = true;
            headerVec.erase(i);
            break;
        }

        Node *tmp = (*headerVec[i]).next;

        if (tmp == nullptr)
            continue;

        while ((*tmp).nextNode != nullptr)
        {
            if (tmp->nextNode->nextHeader == v.header)
            {
                Node *tmpNextNext = tmp->nextNode->nextNode;
                delete (*tmp).nextNode;
                (*tmp).nextNode = tmpNextNext;

                if (tmpNextNext == nullptr)
                    break;
            }

            tmp = (*tmp).nextNode;
        }
    }

    if (!flag)
        throw AL_Direct_Graph_error("Does not exist what to erase Vertex");

    Node *next = v.header->next;
    Node *next_next;
    delete v.header;

    while (next != nullptr)
    {
        next_next = (*next).nextNode;
        delete next;
        next = next_next;
    }

    for (unsigned int i = n; i < vecSize; i++)
    {
        Node *tmp = (*headerVec[i]).next;

        if (tmp == nullptr)
            continue;

        while ((*tmp).nextNode != nullptr)
        {
            if (tmp->nextNode->nextHeader == v.header)
            {
                Node *tmpNextNext = tmp->nextNode->nextNode;
                delete (*tmp).nextNode;
                (*tmp).nextNode = tmpNextNext;

                if (tmpNextNext == nullptr)
                    break;
            }

            tmp = (*tmp).nextNode;
        }
    }

    keyStorage.push(v.header->key);
}

template <typename TV, typename TE>
void AL_Direct_Graph<TV, TE>::eraseEdge(const Edge &e)
{
    Node *tmp = (*e.org).next;
    bool flag = true;

    if (tmp == nullptr)
        throw AL_Direct_Graph_error("Does not exist what to erase edge");

    while ((*tmp).nextNode != nullptr)
    {
        if (tmp->nextNode->nextHeader == e.dst)
        {
            Node *tmpNextNext = tmp->nextNode->nextNode;
            delete (*tmp).nextNode;
            (*tmp).nextNode = tmpNextNext;
            flag = false;

            if (tmpNextNext == nullptr)
                break;
        }

        tmp = (*tmp).nextNode;
    }

    if (flag)
        throw AL_Direct_Graph_error("Does not exist what to erase edge");
}

template <typename TV, typename TE>
Vector<typename AL_Direct_Graph<TV, TE>::Vertex> AL_Direct_Graph<TV, TE>::getVertices()
{
    Vector<Vertex> tmp;
    unsigned int n = headerVec.size();

    for (unsigned int i = 0; i < n; i++)
        tmp.push_back(Vertex(headerVec[i]));

    return tmp;
}

template <typename TV, typename TE>
Vector<typename AL_Direct_Graph<TV, TE>::Vertex> AL_Direct_Graph<TV, TE>::BFS(const Vertex &org) const
{
    unsigned int size = headerVec.size();
    Vector<Vertex> vec;
    Queue<Header *> queue;

    bool *visited = new bool[max_Key + 1]{false};
    

    vec.push_back(org);
    queue.push(org.header);
    visited[(*org.header).key] = true;

    while (queue.empty() == false)
    {
        Header *header_tmp = queue.pop();
        Node *next = (*header_tmp).next;

        while (next)
        {
            header_tmp = (*next).nextHeader;
            unsigned int n = header_tmp->key;
            if (!visited[(*header_tmp).key])
            {
                visited[(*header_tmp).key] = true;
                queue.push(header_tmp);
                vec.push_back(Vertex(header_tmp));
            }

            next = (*next).nextNode;
        }
    }

    return vec;
}

template <typename TV, typename TE>
AL_Direct_Graph<TV, TE>::Vertex::Vertex() : header(nullptr) {}

template <typename TV, typename TE>
AL_Direct_Graph<TV, TE>::Vertex::Vertex(Header *_header) : header(_header) {}

template <typename TV, typename TE>
const TV &AL_Direct_Graph<TV, TE>::Vertex::operator*() const { return (*header).val; }

template <typename TV, typename TE>
bool AL_Direct_Graph<TV, TE>::Vertex::isAdjacentTo(const Vertex &u) const
{
    Node *tmp = (*header).next;

    while (tmp)
    {
        if ((*tmp).nextHeader == u.header)
            return 1;
        tmp = (*tmp).nextNode;
    }

    tmp = (*u.header).next;

    while (tmp)
    {
        if ((*tmp).nextHeader == header)
            return 1;
        tmp = (*tmp).nextNode;
    }

    return 0;
}

template <typename TV, typename TE>
AL_Direct_Graph<TV, TE>::Node::Node(Header *toHeader, const TE &wgt) : nextHeader(toHeader), nextNode(nullptr), weight(wgt) {}

template <typename TV, typename TE>
AL_Direct_Graph<TV, TE>::Edge::Edge(Header *_org, const TE &wgt, Header *_dst) : org(_org), weight(wgt), dst(_dst) {}

template <typename TV, typename TE>
AL_Direct_Graph<TV, TE>::Header::Header(const unsigned int &_key, const TV &_val) : val(_val), key(_key), next(nullptr) {}

template <typename TV, typename TE>
bool AL_Direct_Graph<TV, TE>::Header::operator==(const Header &header) const { return val == header.val; }

template <typename TV, typename TE>
unsigned int AL_Direct_Graph<TV, TE>::getKey()
{
    if (!keyStorage.empty()) return keyStorage.pop();
    else                     return max_Key + 1;
}