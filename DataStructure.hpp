#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <iostream>
#include <exception>        // 오류 클래스를 위해 추가
#include <string>           // 오류 클래스를 위해 추가
#include <initializer_list> // 벡터의 이니셜라이저_리스트를 통한 생성자를 위해 추가
#include <memory.h>         // 벡터 insert, erase 함수 속도를 위해 추가
#include <limits>           // 그래프를 위해 위해

// 존재하는 자료구조 목록 :
// 스택, 원형큐, 원형덱, 노드, 이중연결리스트, 이중연결리스트 기반 큐, 벡터, 포화이진트리
// 트리, 힙, 인접리스트기반 유향 가중 그래프, 정렬알고리즘

#define VECTOR_MAX_SIZE 4294767295ULL

/*
 *
 *
 *
 *
 *
 *
 *
 * 
 * ============================== 클래스 선언부 ==============================
 *
 *
 *
 *
 *
 *
 *
 *
 * 
 */

template <typename T>
class Stack
{
public:
    Stack(int capacity = 0);
    Stack(const Stack &stack);
    void operator=(const Stack &stack);
    ~Stack();
    bool empty() const;
    bool full() const;
    unsigned int size() const;
    unsigned int capacity() const;
    T top() const;
    void push(const T &_val);
    T pop();
    void reserve(unsigned int _capacity);

private:
    unsigned int stackSize;
    unsigned int stackCapacity;
    T *basePointer;
    T *stackPointer;
};

// stability test passed through acmicpcs : https://www.acmicpc.net/problem/2164
// 제출번호 : 29791891
template <typename T>
class Queue
{
public:
    Queue(unsigned int _capacity = 0);
    Queue(const Queue &queue);
    void operator=(const Queue &queue);
    ~Queue();
    void push(const T &input);
    T pop();
    bool full() const;
    bool empty() const;
    unsigned int size() const;
    unsigned int capacity() const;
    void reserve(unsigned int _capacity);

private:
    T *start;
    T *end;
    T *Q_p;
    unsigned int queueSize;
    unsigned int queueCapacity;
};

// stability test passed through acmicpcs : https://www.acmicpc.net/problem/2164
// 제출번호 : 29791891
template <typename T>
class Deque
{
public:
    Deque(unsigned int _capacity = 0);
    Deque(const Deque &deque);
    void operator=(const Deque &deque);
    ~Deque();
    void push_front(const T &_val);
    void push_back(const T &_val);
    T pop_front();
    T pop_back();
    bool full() const;
    bool empty() const;
    unsigned int size() const;
    unsigned int capacity() const;
    void reserve(unsigned int _capacity);

private:
    T *start;
    T *end;
    T *D_p;
    unsigned int dequeSize;
    unsigned int dequeCapacity;
};

template <typename T>
class DLL;

template <typename T>
class BinaryTree;

template <typename T> // private 일부러 X
class Node
{
public:
    Node(T input = (T)NULL);
    ~Node();

private:
    T value;
    Node<T> *left;
    Node<T> *right;
    Node<T> *par;

    friend class DLL<T>;
    friend class BinaryTree<T>;
};

template <typename T>
class DLL
{
public:
    DLL();
    ~DLL();
    DLL(const DLL &__DLL);
    void operator=(const DLL &__DLL);
    bool empty() const;
    int size() const;
    void push_front(const T &val);
    void push_back(const T &val);
    void insert(unsigned int index, const T &val);
    void erase(unsigned int index);
    T &front() const;
    T &back() const;
    T &at(unsigned int index) const;
    void clear();

    class Iterator
    {
    public:
        Iterator(Node<T> *input = nullptr);
        Iterator &operator++();
        Iterator operator++(int);
        Iterator &operator--();
        Iterator operator--(int);
        T &operator*() const; // 이건 const를 붙여야되나?
        bool operator==(const Iterator &_iter) const;
        bool operator!=(const Iterator &_iter) const;

    private:
        Node<T> *iter;
    };

    typedef const Iterator const_Iterator;

    Iterator begin() const;
    Iterator end() const;

private:
    Node<T> *head;
    unsigned int dllSize;
};

template <typename T> //DLL기반 Queue인데, Queue error을 던질 방법은?
class Queue_DLL
{
public:
    Queue_DLL();
    ~Queue_DLL();
    bool empty() const;
    int size() const;
    void push(T input);
    T pop();

private:
    DLL<T> *dll;
};

// 임의 클래스도 담겨지는데, 왜 스트링만 못담지??
// https://www.acmicpc.net/problem/10814
// 제출번호 : 29791891
template <typename T>
class Vector
{
public:
    class Iterator
    {
    public:
        Iterator();
        T &operator*() const;
        T &operator[](int _index) const;
        Iterator operator+(unsigned int _num) const;
        Iterator operator-(unsigned int _num) const;
        Iterator &operator+=(unsigned int _num);
        Iterator &operator-=(unsigned int _num);
        long long operator-(const Iterator &_it) const;
        Iterator &operator=(const Iterator &_it);
        friend typename Vector<T>::Iterator operator+(unsigned int num, const typename Vector<T>::Iterator &_it) { return _it + num; }
        Iterator &operator++();
        Iterator operator++(int);
        Iterator &operator--();
        Iterator operator--(int);
        bool operator==(const Iterator &_it) const;
        bool operator!=(const Iterator &_it) const;
        bool operator>(const Iterator &_it) const;
        bool operator>=(const Iterator &_it) const;
        bool operator<(const Iterator &_it) const;
        bool operator<=(const Iterator &_it) const;

    private:
        Iterator(const Vector *_vector, unsigned int _index);
        const Vector *vector;
        unsigned int index;
        friend class Vector;
    };

    typedef const Iterator const_Iterator;

    Vector(unsigned int _size = 0);
    Vector(unsigned int _numberOfValue, const T &_value);
    Vector(const Iterator &_first, const Iterator &_last);
    Vector(std::initializer_list<T> _list);
    Vector(const Vector &_vector);
    Vector &operator=(const Vector &_vector);
    ~Vector();

    Iterator begin() const;
    Iterator end() const;
    bool empty() const;
    int size() const;
    int capacity() const;
    unsigned long long max_size() const;
    void resize(unsigned int _size, const T &val = 0);
    void reserve(unsigned int _capacity);
    void swap(Vector &_target);
    void assign(const Iterator &_start, const Iterator &_end);
    void assign(unsigned int _size, const T &val);
    void insert(unsigned int _index, const T &val);
    void insert(const Iterator &_position, const T &val);
    void insert(const Iterator &_position, const Iterator &_first, const Iterator &_last);
    void insert(unsigned int index, const Iterator &first, const Iterator &last);
    void push_back(const T &val);
    T pop_back();
    T &at(unsigned int _index) const;
    T &operator[](unsigned int _index) const;
    T *operator+(unsigned int _index) const;
    T &front() const;
    T &back() const;
    void erase(unsigned int _index);
    void erase(unsigned int _first, unsigned int _last);
    void erase(const Iterator &_first, const Iterator &_last);
    void clear();

private:
    T *vec;
    unsigned int vecSize;
    unsigned int vecCapacity;
};

template <typename T>
class Tree;

template <typename T>
class NodeTree
{
public:
    NodeTree(T input = (T)NULL);
    ~NodeTree();

private:
    T val;
    NodeTree<T> *par;
    Vector<NodeTree<T> *> chi;

    friend class Tree<T>;
};

template <typename T>
class Tree
{
public:
    class Position
    {
        friend Tree;

    public:
        Position(NodeTree<T> *input = nullptr);
        T &operator*();
        Position &setParent();
        Position &setChild(int num);
        Position &setValue(T input);
        Position getParent() const;
        Position getChild(int num) const;
        bool isRoot() const;

    private:
        NodeTree<T> *node;
    };

    Tree();
    ~Tree();
    bool empty() const;
    int size() const;
    void createRoot(T val = (T)NULL);
    void createChild(Position &where, T val = (T)NULL);
    int getChildNumber(const Position &where) const;
    const Vector<typename Tree::Position> &getChildVector(const Position &where) const;
    //void getChildVector(const Position &where, Vector<Position> &vec); // 벡터 자체를 반환하는 방법은?
    void erase(Position &where);
    void preorder(const Position &where, Vector<Position> &vec) const;
    void inorder(const Position &where, Vector<Position> &vec) const;
    void postorder(const Position &where, Vector<Position> &vec) const;
    Position getRoot() const;

private:
    NodeTree<T> *root;
    int treeSize;
};

template <typename T>
class BinaryTree // 포화이진트리
{
public:
    class Position
    {
        friend BinaryTree;

    public:
        Position(Node<T> *input = nullptr);
        T &operator*();
        Position &setParent();
        Position &setLeft();
        Position &setRight();
        Position getParent() const;
        Position getLeft() const;
        Position getRight() const;
        bool isRoot() const;

    private:
        Node<T> *iter;
    };

    BinaryTree();
    ~BinaryTree();
    bool empty() const;
    int size() const;
    void createRoot();
    void createChild(Position &where);
    void erase(Position &where);
    void preorder(const Position &where, Vector<BinaryTree::Position> &vec);
    void inorder(const Position &where, Vector<BinaryTree::Position> &vec);
    void postorder(const Position &where, Vector<BinaryTree::Position> &vec);
    Position root() const;

private:
    Node<T> *head;
    int treeSize;
};

// 최소힙. 배열기반. val이 key값 그 자체라는 가정하에 설계.
template <typename T>
class Heap
{
public:
    Heap();
    ~Heap();
    class Position
    {
    public:
        Position();
        const T &getVal() const;
        Position &setParent();
        Position &setLeftChild();
        Position &setRightChild();
        Position getParent() const;
        Position getLeftChild() const;
        Position getRightChild() const;
        int depth() const;
        bool isLeftChild() const;
        bool isRightChild() const;
        bool isRoot() const;

    private:
        Position(const Heap *_heap = nullptr, int _index = 0);
        const Heap *hp;
        unsigned int index;

        friend class Heap;
    };
    bool empty() const;
    unsigned int height() const;
    unsigned int size() const;
    void insert(const T &val);
    void reserve(); // capacity = capacity * 2 + 1
    void reserve(unsigned int _capacity);
    void erase();                // erase root
    void erase(Position &where); // erase where
    void clear();
    Position getRoot() const;
    Position getLast() const;

private:
    unsigned int heapSize;
    unsigned int heapCapacity;
    T *heap;
    T *last; // (last의 index) + 1 == size

    bool isFull() const;
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

/*
 *
 *
 *
 *
 *
 *
 *
 * 
 * ============================== 예외 클래스 선언, 정의부 ==============================
 *
 *
 *
 *
 *
 *
 *
 *
 * 
 */

class Stack_error : public std::exception
{
public:
    Stack_error(const std::string &_errorMessage) : errorMessage("Stack error : " + _errorMessage) {}
    const char *what() const throw() override { return errorMessage.c_str(); }

private:
    std::string errorMessage;
};

class Queue_error : public std::exception
{
public:
    Queue_error(const std::string &_errorMessage) : errorMessage("Queue error : " + _errorMessage) {}
    const char *what() const throw() override { return errorMessage.c_str(); }

private:
    std::string errorMessage;
};

class Deque_error : public std::exception
{
public:
    Deque_error(const std::string &_errorMessage) : errorMessage("Deque error : " + _errorMessage) {}
    const char *what() const throw() override { return errorMessage.c_str(); }

private:
    std::string errorMessage;
};

class DLL_error : public std::exception
{
public:
    DLL_error(const std::string &_errorMessage) : errorMessage("DLL error : " + _errorMessage) {}
    const char *what() const throw() override { return errorMessage.c_str(); }

private:
    std::string errorMessage;
};

class Vector_error : public std::exception
{
public:
    Vector_error(const std::string &_errorMessage) : errorMessage("Vector error : " + _errorMessage) {}
    const char *what() const throw() override { return errorMessage.c_str(); }

private:
    std::string errorMessage;
};

class BinaryTree_error : public std::exception
{
public:
    BinaryTree_error(const std::string &_errorMessage) : errorMessage("BinaryTree error : " + _errorMessage) {}
    const char *what() const throw() override { return errorMessage.c_str(); }

private:
    std::string errorMessage;
};

class Tree_error : public std::exception
{
public:
    Tree_error(const std::string &_errorMessage) : errorMessage("Tree error : " + _errorMessage) {}
    const char *what() const throw() override { return errorMessage.c_str(); }

private:
    std::string errorMessage;
};

class Heap_error : public std::exception
{
public:
    Heap_error(const std::string &_errorMessage) : errorMessage("Heap error : " + _errorMessage) {}
    const char *what() const throw() override { return errorMessage.c_str(); }

private:
    std::string errorMessage;
};

class AL_Graph_error : public std::exception
{
public:
    AL_Graph_error(const std::string &_errorMessage) : errorMessage("AL_Graph error : " + _errorMessage) {}
    const char *what() const throw() override { return errorMessage.c_str(); }

private:
    std::string errorMessage;
};

/*
 *
 *
 *
 *
 *
 *
 *
 * 
 * ============================== 클래스 멤버 함수 정의부 ==============================
 *
 *
 *
 *
 *
 *
 *
 *
 * 
 * 
 */

template <typename T>
Stack<T>::Stack(int stackCapacity) : basePointer((T *)calloc(stackCapacity, sizeof(T))), stackCapacity(stackCapacity), stackSize(0)
{
    if (stackCapacity < 0)
        throw Stack_error("Objects with negative stackCapacity cannot be created.");

    stackPointer = basePointer - 1;
}

template <typename T>
Stack<T>::Stack(const Stack &stack)
{
    stackCapacity = stack.stackCapacity;
    stackSize = stack.stackSize;
    basePointer = (T *)calloc(stackCapacity, sizeof(T));
    memcpy(basePointer, stack.basePointer, sizeof(T) * stackSize);
}

template <typename T>
void Stack<T>::operator=(const Stack &stack)
{
    if (basePointer != stack.basePointer)
    {
        if (stackSize == 0)
            free(basePointer);

        stackCapacity = stack.stackCapacity;
        stackSize = stack.stackSize;
        basePointer = (T *)calloc(stackCapacity, sizeof(T));
        memcpy(basePointer, stack.basePointer, sizeof(T) * stackSize);
    }
}

template <typename T>
Stack<T>::~Stack()
{
    free(basePointer);
    basePointer = nullptr;
    stackPointer = nullptr;
}

template <typename T>
bool Stack<T>::empty() const
{
    return stackSize == 0;
}

template <typename T>
bool Stack<T>::full() const
{
    return stackSize == stackCapacity;
}

template <typename T>
unsigned int Stack<T>::size() const
{
    return stackSize;
}

template <typename T>
unsigned int Stack<T>::capacity() const
{
    return stackCapacity;
}

template <typename T>
T Stack<T>::top() const
{
    if (empty())
        throw Stack_error("stack is empty!");

    return *stackPointer;
}

template <typename T>
void Stack<T>::push(const T &val)
{
    if (full())
        reserve(stackCapacity * 2);

    stackSize++;
    *++stackPointer = val;
}

template <typename T>
T Stack<T>::pop()
{
    if (empty())
        throw Stack_error("Stack is empty!");

    stackSize--;
    return *stackPointer--;
}

template <typename T>
void Stack<T>::reserve(unsigned int _reserve)
{
    if (_reserve < stackCapacity)
        throw Stack_error("stackCapacity of reassign is leen than the original stackCapacity");
    if (_reserve == 0)
    {
        if (!(basePointer = (T *)malloc(sizeof(T))))
            throw Stack_error("Out of memory");
        stackPointer = basePointer - 1;
        stackCapacity = 1;
        return;
    }

    T *tmp;
    if (!(tmp = (T *)realloc(basePointer, _reserve * sizeof(T))))
        throw Stack_error("Out of memory");
    else if (tmp != basePointer)
    {
        basePointer = tmp;
        stackPointer = tmp + stackSize - 1;
    }

    stackCapacity = _reserve;
}

template <typename T>
Queue<T>::Queue(unsigned int _queueCapacity) : queueCapacity(_queueCapacity), queueSize(0), Q_p((T *)calloc(_queueCapacity, sizeof(T)))
{
    if (_queueCapacity < 0)
        throw Queue_error("Objects with negative queueCapacity cannot be created.");

    end = Q_p - 1;
    start = Q_p;
}

template <typename T>
Queue<T>::Queue(const Queue &queue)
{
    queueCapacity = queue.queueCapacity;
    queueSize = queue.queueSize;
    Q_p = (T *)calloc(queueCapacity, sizeof(T));
    start = Q_p + queue.start - queue.Q_p;
    end = Q_p + queue.end - queue.Q_p;
    memcpy(Q_p, queue.Q_p, sizeof(T) * queueCapacity);
}

template <typename T>
void Queue<T>::operator=(const Queue &queue)
{
    if (Q_p != queue.Q_p)
    {
        if (queueSize == 0)
            free(Q_p);

        queueCapacity = queue.queueCapacity;
        queueSize = queue.queueSize;
        Q_p = (T *)calloc(queueCapacity, sizeof(T));
        start = Q_p + queue.start - queue.Q_p;
        end = Q_p + queue.end - queue.Q_p;
        memcpy(Q_p, queue.Q_p, sizeof(T) * queueCapacity);
    }
}

template <typename T>
Queue<T>::~Queue()
{
    free(Q_p);
}

template <typename T>
void Queue<T>::push(const T &input)
{
    if (queueSize >= queueCapacity)
        Queue<T>::reserve(queueCapacity * 2);

    queueSize++;
    end = Q_p + (end - Q_p + 1) % queueCapacity;
    *end = input;
}

template <typename T>
T Queue<T>::pop()
{
    if (!queueSize)
        throw Queue_error("Queue is empty!");

    T temp = *start;

    start = Q_p + (start + 1 - Q_p) % queueCapacity;
    queueSize--;

    return temp;
}

template <typename T>
bool Queue<T>::full() const
{
    if (queueSize == queueCapacity)
        return 1;
    else
        return 0;
}

template <typename T>
bool Queue<T>::empty() const
{
    if (queueSize == 0)
        return 1;
    else
        return 0;
}

template <typename T>
unsigned int Queue<T>::size() const
{
    return queueSize;
}

template <typename T>
unsigned int Queue<T>::capacity() const
{
    return queueCapacity;
}

template <typename T>
void Queue<T>::reserve(unsigned int _queueCapacity)
{
    if (_queueCapacity == 0 && queueCapacity == 0)
    {
        if (!(Q_p = (T *)calloc(1, sizeof(T))))
            throw Queue_error("Out of memory");
        start = Q_p;
        end = Q_p - 1;
        queueCapacity = 1;
        return;
    }

    if (_queueCapacity > 60000)
        throw Queue_error("over the max reserve queueCapacity");

    if (_queueCapacity > queueCapacity)
    {

        T *temp;

        if (!(temp = (T *)realloc(Q_p, sizeof(T) * _queueCapacity)))
            throw Queue_error("Out of memory");

        if (Q_p != temp)
        {
            start = temp + (start - Q_p);
            end = temp + (end - Q_p);
            Q_p = temp;
        }

        if (start > end)
        {
            T *p2 = Q_p + queueCapacity;
            for (T *p = Q_p; p <= end;)
                *(p2++) = *(p++);

            end = start + queueSize - 1;
        }
        queueCapacity = _queueCapacity;

        return;
    }
    else // 사이즈 감소에 대해서는 테스트 해보지 못했음.
    {
        return;
        throw Queue_error("reserve capacity must be greater than origin capacity");
    }
}

template <typename T>
Deque<T>::Deque(unsigned int _dequeCapacity) : dequeCapacity(_dequeCapacity), dequeSize(0), D_p((T *)malloc(sizeof(T) * _dequeCapacity))
{
    if (_dequeCapacity < 0)
        throw Deque_error("Objects with negative max_dequeSize cannot be created.");

    start = D_p,
    end = D_p + _dequeCapacity - 1;
}

template <typename T>
Deque<T>::Deque(const Deque &deque)
{
    dequeCapacity = deque.dequeCapacity;
    dequeSize = deque.dequeSize;
    D_p = (T *)calloc(dequeCapacity, sizeof(T));
    start = D_p + deque.start - deque.D_p;
    end = D_p + deque.end - deque.D_p;
    memcpy(D_p, deque.D_p, sizeof(T) * dequeCapacity);
}

template <typename T>
void Deque<T>::operator=(const Deque &deque)
{
    if (D_p != deque.D_p)
    {
        if (dequeSize == 0)
            free(D_p);

        dequeCapacity = deque.dequeCapacity;
        dequeSize = deque.dequeSize;
        D_p = (T *)calloc(dequeCapacity, sizeof(T));
        start = D_p + deque.start - deque.D_p;
        end = D_p + deque.end - deque.D_p;
        memcpy(D_p, deque.D_p, sizeof(T) * dequeCapacity);
    }
}

template <typename T>
Deque<T>::~Deque()
{
    free(D_p);
    D_p = nullptr;
}

template <typename T>
void Deque<T>::push_front(const T &input)
{
    if (dequeSize >= dequeCapacity)
        Deque<T>::reserve(dequeCapacity * 2);

    dequeSize++;
    start = D_p + ((start - 1 - D_p + dequeCapacity) % dequeCapacity); // c언어에서 음수에 대한 나머지연산은, 음수값으로 나오기 때문에, 꼭 dequeCapacity를 한번 더해줘야함
    *start = input;
}

template <typename T>
void Deque<T>::push_back(const T &input)
{
    if (dequeSize >= dequeCapacity)
        Deque<T>::reserve(dequeCapacity * 2);

    dequeSize++;
    end = D_p + (end + 1 - D_p) % dequeCapacity;
    *end = input;
}

template <typename T>
T Deque<T>::pop_front()
{
    if (!dequeSize)
        throw Deque_error("Deque is empty!");

    T temp = *start;

    start = D_p + (start + 1 - D_p) % dequeCapacity;
    dequeSize--;

    return temp;
}

template <typename T>
T Deque<T>::pop_back()
{
    if (!dequeSize)
        throw Deque_error("Deque is empty!");

    T temp = *end;

    end = D_p + (end - 1 - D_p + dequeCapacity) % dequeCapacity;
    dequeSize--;

    return temp;
}

template <typename T>
bool Deque<T>::full() const
{
    if (dequeSize == dequeCapacity)
        return 1;
    else
        return 0;
}

template <typename T>
bool Deque<T>::empty() const
{
    if (dequeSize == 0)
        return 1;
    else
        return 0;
}

template <typename T>
unsigned int Deque<T>::size() const
{
    return dequeSize;
}

template <typename T>
unsigned int Deque<T>::capacity() const
{
    return dequeCapacity;
}

template <typename T>
void Deque<T>::reserve(unsigned int _dequeCapacity)
{
    if (_dequeCapacity == 0 && dequeCapacity == 0)
    {
        if (!(D_p = (T *)calloc(1, sizeof(T))))
            throw Deque_error("Out of memory");
        start = D_p;
        end = D_p - 1;
        dequeCapacity = 1;
        return;
    }

    if (_dequeCapacity > 60000)
        throw Deque_error("over the max reserve dequeCapacity");

    if (_dequeCapacity > dequeCapacity)
    {

        T *temp;

        if (!(temp = (T *)realloc(D_p, sizeof(T) * _dequeCapacity)))
            throw Deque_error("Out of memory");

        if (D_p != temp)
        {
            start = temp + (start - D_p);
            end = temp + (end - D_p);
            D_p = temp;
        }

        if (start > end)
        {
            T *p2 = D_p + dequeCapacity;
            for (T *p = D_p; p <= end;)
                *(p2++) = *(p++);

            end = start + dequeSize - 1;
        }
        dequeCapacity = _dequeCapacity;

        return;
    }
    else // 사이즈 감소에 대해서는 테스트 해보지 못했음.
    {
        throw Deque_error("reserve capacity must be greater than origin capacity");
    }
}

template <typename T>
Node<T>::Node(T val) : left(NULL), value(val), right(NULL) {}

template <typename T>
Node<T>::~Node()
{
    value = (T)NULL;
    left = nullptr;
    right = nullptr;
}

template <typename T>
DLL<T>::DLL() : head(nullptr), dllSize(0) {}

template <typename T>
DLL<T>::DLL(const DLL &__DLL) : head(nullptr), dllSize(0)
{
    for (unsigned int i = 0; i < __DLL.size(); i++)
        push_back(__DLL.at(i));
}

template <typename T>
DLL<T>::~DLL()
{
    if (!empty())
    {
        Node<T> *tmp = (*head).right;

        do
        {
            tmp = (*tmp).right;
            delete (*tmp).left;
        } while (tmp != head);

        delete tmp;

        head = nullptr;
    }
}

template <typename T>
void DLL<T>::operator=(const DLL &__DLL)
{
    clear();

    for (unsigned int i = 0; i < __DLL.size(); i++)
        push_back(__DLL.at(i));
}

template <typename T>
bool DLL<T>::empty() const { return !dllSize; }

template <typename T>
int DLL<T>::size() const { return dllSize; }

template <typename T>
void DLL<T>::push_front(const T &val)
{
    if (empty())
    {
        head = new Node<T>{val};
        (*head).left = head;
        (*head).right = head;
        dllSize++;
        return;
    }

    Node<T> *node = new Node<T>{val};
    (*(*head).left).right = node; // 원형 DLL 이므로, (*head).left는 DLL의 꼬리를 의미함.
    (*node).left = (*head).left;
    (*node).right = head;
    (*head).left = node;
    head = node;

    dllSize++;
}

template <typename T>
void DLL<T>::push_back(const T &val)
{
    if (empty())
    {
        head = new Node<T>{val};
        (*head).left = head;
        (*head).right = head;
        dllSize++;
        return;
    }

    Node<T> *node = new Node<T>{val};
    (*(*head).left).right = node;
    (*node).left = (*head).left;
    (*node).right = head;
    (*head).left = node;

    dllSize++;
}

template <typename T>
void DLL<T>::insert(unsigned int index, const T &val)
{
    if (index >= dllSize) // dllSize가 0인경우, 모든 경우에 대해서 거름.
    {
        if (index == 0 && dllSize == 0)
        {
            push_front(val);
            return;
        }

        std::string error_str;
        error_str = "Reference to (" + std::to_string(index) + ") that does not exist";
        throw DLL_error(error_str);
    }

    if (index == 0) // 이 처리를 해주지 않으면 맨 앞이 아니라, 맨 마지막에 값을 삽입한거랑 똑같은 일이 발생함
    {
        push_front(val);
        return;
    }

    Node<T> *node = new Node<T>{val};

    Node<T> *tmp = head;
    for (unsigned int i = 0; i < index; i++)
        tmp = (*tmp).right;

    (*(*tmp).left).right = node;
    (*node).left = (*tmp).left;
    (*node).right = tmp;
    (*tmp).left = node;

    dllSize++;
}

template <typename T>
T &DLL<T>::front() const
{
    if (empty())
    {
        throw DLL_error("DLL is empty!");
    }

    return (*head).value;
}

template <typename T>
T &DLL<T>::back() const
{
    if (empty())
    {
        throw DLL_error("DLL is empty!");
    }

    return (*(*head).left).value;
}

template <typename T>
T &DLL<T>::at(unsigned int index) const
{
    if (index >= dllSize || index < 0) // 0인경우 자동으로 걸러줌
    {
        std::string error_str;
        error_str = "Reference to (" + std::to_string(index) + ") that does not exist";
        throw DLL_error(error_str);
    }

    Node<T> *tmp = head;
    for (unsigned int i = 0; i < index; i++)
        tmp = (*tmp).right;

    return (*tmp).value;
}

template <typename T>
void DLL<T>::erase(unsigned int index)
{
    if (index >= dllSize || index < 0)
    {
        std::string error_str;
        error_str = "Reference to (" + std::to_string(index) + ") that does not exist";
        throw DLL_error(error_str);
        return;
    }

    Node<T> *tmp = head;
    for (unsigned int i = 0; i < index; i++)
        tmp = (*tmp).right;

    (*(*tmp).left).right = (*tmp).right;
    (*(*tmp).right).left = (*tmp).left;

    if (index == 0)
        head = (*head).right; // 0번째를 삭제할경우 head 변경됨. dllSize가 1인 DLL을 erase해도, ~Node 소멸자 덕분에 null으 들어감.

    dllSize--;
    delete tmp;
}

template <typename T>
void DLL<T>::clear()
{
    if (empty())
        return;
    Node<T> *tmp = (*head).right;

    do
    {
        tmp = (*tmp).right;
        delete (*tmp).left;
    } while (tmp != head);

    delete tmp;

    dllSize = 0;
    head = nullptr;
}

template <typename T>
DLL<T>::Iterator::Iterator(Node<T> *val) : iter(val) {}

template <typename T>
typename DLL<T>::Iterator &DLL<T>::Iterator::operator++()
{
    iter = (*iter).right;
    return *this;
}

template <typename T>
typename DLL<T>::Iterator DLL<T>::Iterator::operator++(int)
{
    Iterator tmp = *this;
    iter = (*iter).right;
    return tmp;
}

template <typename T>
typename DLL<T>::Iterator &DLL<T>::Iterator::operator--()
{
    iter = (*iter).left;
    return *this;
}

template <typename T>
typename DLL<T>::Iterator DLL<T>::Iterator::operator--(int)
{
    Iterator tmp = *this;
    iter = (*iter).left;
    return tmp;
}

template <typename T>
T &DLL<T>::Iterator::operator*() const
{
    return (*(*this).iter).value;
}

template <typename T>
bool DLL<T>::Iterator::operator==(const Iterator &_iter) const
{
    return iter == _iter.iter;
}

template <typename T>
bool DLL<T>::Iterator::operator!=(const Iterator &_iter) const
{
    return iter != _iter.iter;
}

template <typename T>
typename DLL<T>::Iterator DLL<T>::begin() const
{
    // 비어 있으면, head가 nullptr 이므로 nullptr 반환
    return Iterator(head);
}

template <typename T>
typename DLL<T>::Iterator DLL<T>::end() const
{
    // 비어 있으면, (*head).left가 nullptr 이므로 nullptr 반환
    return Iterator((*head).left);
}

template <typename T>
Queue_DLL<T>::Queue_DLL() : dll(new DLL<T>) {}

template <typename T>
Queue_DLL<T>::~Queue_DLL() { delete dll; }

template <typename T>
bool Queue_DLL<T>::empty() const { return (*dll).empty(); }

template <typename T>
int Queue_DLL<T>::size() const { return (*dll).size(); }

template <typename T>
void Queue_DLL<T>::push(T input)
{
    (*dll).push_back(input);
}

template <typename T>
T Queue_DLL<T>::pop()
{
    T tmp = (*dll).front();
    (*dll).erase(0);
    return tmp;
}

template <typename T>
Vector<T>::Vector(unsigned int _size) : vec((T *)calloc(_size, sizeof(T))), vecCapacity(_size), vecSize(_size) {}

template <typename T>
Vector<T>::Vector(unsigned int numberOfValue, const T &value)
    : vec((T *)calloc(numberOfValue, sizeof(T))), vecCapacity(numberOfValue), vecSize(numberOfValue)
{
    if (sizeof(T) == 1)
        memset(vec, value, vecSize);
    else
        for (unsigned int i = 0; i < vecSize; i++)
            vec[i] = value;
}

template <typename T>
Vector<T>::Vector(const Iterator &first, const Iterator &last)
    : vec((T *)calloc(last - first, sizeof(T))), vecCapacity(last - first), vecSize(last - first)
{
    if (first.index > last.index)
        throw Vector_error("first Iterator is after the last");
    else if (first.vector != last.vector)
        throw Vector_error("The first iterator and the last iterator point to different vector");

    if (first.index == last.index)
        return;

    memmove(vec, (*first.vector).vec + first.index, (last.index - first.index) * sizeof(T));
}

template <typename T>
Vector<T>::Vector(const Vector &_vector)
    : vec((T *)calloc(_vector.vecCapacity, sizeof(T))), vecCapacity(_vector.vecCapacity), vecSize(_vector.vecSize)
{
    memcpy(vec, _vector.vec, sizeof(T) * vecSize);
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> _list)
    : vec((T *)calloc(_list.size(), sizeof(T))), vecCapacity(_list.size()), vecSize(_list.size())
{
    memcpy(vec, _list.begin(), sizeof(T) * vecSize);
}

template <typename T>
Vector<T> &Vector<T>::operator=(const Vector &input)
{
    if (vec != input.vec)
    {
        clear();

        vecCapacity = input.vecCapacity;
        vecSize = input.vecSize;
        vec = (T *)calloc(vecCapacity, sizeof(T));

        memcpy(vec, input.vec, sizeof(T) * vecSize);
    }

    return *this;
}

template <typename T>
Vector<T>::~Vector() { free(vec); }

template <typename T>
inline int Vector<T>::size() const { return vecSize; }

template <typename T>
inline int Vector<T>::capacity() const { return vecCapacity; }

template <typename T>
inline bool Vector<T>::empty() const { return vecSize == 0; }

template <typename T>
inline unsigned long long Vector<T>::max_size() const { return VECTOR_MAX_SIZE; }

template <typename T>
inline void Vector<T>::resize(unsigned int _size, const T &val)
{
    if (_size > vecCapacity)
        reserve(_size);
    if (_size > vecSize)
    {
        if (sizeof(T) == 1)
            memset(vec + vecSize, val, _size - vecSize);
        else
        {
            for (unsigned int i = vecSize; i < _size; i++)
                vec[i] = val;
        }
    }

    vecSize = _size;
}

template <typename T>
inline void Vector<T>::reserve(unsigned int _capacity)
{

    if (_capacity < vecCapacity)
        throw Vector_error("capacity to reserve is leen than the original capacity");
    if (_capacity == 0)
    {
        vec = (T *)calloc(1, sizeof(T));
        vecCapacity = 1;
        return;
    }

    T *tmp;

    if (!(tmp = (T *)realloc(vec, sizeof(T) * _capacity)))
        throw Vector_error("Out of Memory");
    else if (tmp != vec)
        vec = tmp;

    vecCapacity = _capacity;
}

template <typename T>
inline void Vector<T>::swap(Vector &target)
{
    T *vec_tmp;
    T vecSize_tmp;
    T vecCapacity_tmp;

    vec = target.vec;
    vecSize = target.vecSize;
    vecCapacity = target.vecCapacity;

    target.vec = vec_tmp;
    target.vecSize = vecSize_tmp;
    target.vecCapacity = vecCapacity_tmp;
}

template <typename T>
void Vector<T>::assign(const Iterator &first, const Iterator &last)
{
    if (first.vector != last.vector)
        throw Vector_error("The first iterator or the last iterator point to different vector");
    else if (first > last)
        throw Vector_error("first Iterator is after the last");

    unsigned int _size = last - first;

    if (_size > vecCapacity)
        reserve(_size);

    int i = 0;
    for (Iterator it = first; it < last; it++, i++)
        vec[i] = *it;

    vecSize = _size;
}

template <typename T>
void Vector<T>::assign(unsigned int _size, const T &val)
{
    if (_size > vecCapacity)
        reserve(_size);

    if (sizeof(T) == 1)
        memset(vec, val, _size);
    else
        for (unsigned int i = 0; i < _size; i++)
            vec[i] = val;

    vecSize = _size;
}

template <typename T>
void Vector<T>::insert(unsigned int index, const T &val)
{
    if (index > vecSize)
        throw Vector_error("An access to an invalid index has occured");
    else if (vecSize == vecCapacity)
        reserve(vecCapacity * 2);

    memmove(vec + index + 1, vec + index, (vecSize - index) * sizeof(T));

    *(vec + index) = val;
    vecSize++;
}

template <typename T>
void Vector<T>::insert(const Iterator &position, const T &val)
{
    if (position.vector != this)
        throw Vector_error("iterator point to different vector");
    else if (position.index > vecSize)
        throw Vector_error("An access to an invalid Iterator has occured");
    else if (vecSize == vecCapacity)
        reserve(vecCapacity * 2);

    memmove(vec + position.index + 1, vec + position.index, (vecSize - position.index) * sizeof(T));

    *(vec + position.index) = val;
    vecSize++;
}

template <typename T>
void Vector<T>::insert(const Iterator &position, const Iterator &first, const Iterator &last)
{
    unsigned int index = position.index;
    if (position.vector != this)
        throw Vector_error("Invaild Iterator");
    else if (index > vecSize)
        throw Vector_error("An access to an invalid index has occured");
    else if (first.index > last.index)
        throw Vector_error("first Iterator is after the last");
    else if (first.vector != last.vector)
        throw Vector_error("The first iterator or the last iterator point to different vector");

    if (first.index == last.index)
        return;
    else if (vecCapacity < vecSize + last.index - first.index)
        reserve((vecSize + last.index - first.index) * 2);

    memmove(vec + index + last.index - first.index, vec + index, (vecSize - index) * sizeof(T));
    memmove(vec + index, (*first.vector).vec + first.index, (last.index - first.index) * sizeof(T));

    vecSize += last.index - first.index;
}

template <typename T>
void Vector<T>::insert(unsigned int index, const Iterator &first, const Iterator &last)
{
    if (index > vecSize)
        throw Vector_error("An access to an invalid index has occured");
    else if (first.index > last.index)
        throw Vector_error("first Iterator is after the last");
    else if (first.vector != last.vector)
        throw Vector_error("The first iterator or the last iterator point to different vector");
    else if (first.index == last.index)
        return;

    if (vecCapacity < vecSize + last.index - first.index)
        reserve((vecSize + last.index - first.index) * 2);

    memmove(vec + index + last.index - first.index, vec + index, (vecSize - index) * sizeof(T));
    memmove(vec + index, (*first.vector).vec + first.index, (last.index - first.index) * sizeof(T));

    vecSize += last.index - first.index;
}

template <typename T>
inline void Vector<T>::push_back(const T &val)
{
    if (vecSize == vecCapacity)
        reserve(vecCapacity * 2);

    *(vec + vecSize) = val;
    vecSize++;
}

template <typename T>
inline T Vector<T>::pop_back()
{
    if (vecSize == 0)
        throw Vector_error("vector is empty");

    T tmp = *(vec + vecSize - 1);
    vecSize--;
    return tmp;
}

template <typename T>
inline T &Vector<T>::at(unsigned int index) const
{
    if (index >= vecSize || index < 0)
        throw Vector_error("An access to an invalid index has occured");

    return *(vec + index);
}

template <typename T>
inline T &Vector<T>::operator[](unsigned int index) const { return *(vec + index); }

template <typename T>
T *Vector<T>::operator+(unsigned int _index) const
{
    return vec + _index;
}

template <typename T>
inline T &Vector<T>::front() const { return *vec; }

template <typename T>
inline T &Vector<T>::back() const
{
    if (vecSize == 0)
        throw Vector_error("vector is empty");

    return *(vec + vecSize - 1);
}

template <typename T>
inline void Vector<T>::erase(unsigned int index)
{
    if (index >= vecSize)
        throw Vector_error("An access to an invalid index has occured");

    memmove(vec + index, vec + index + 1, (vecSize - index - 1) * sizeof(T));

    vecSize--;
}

template <typename T>
inline void Vector<T>::erase(unsigned int first, unsigned int last)
{
    if (first >= vecSize || last >= vecSize)
        throw Vector_error("An access to an invalid index has occured");
    else if (first > last)
        throw Vector_error("first is after the last");

    memmove(vec + first, vec + last, (vecSize - last) * sizeof(T));

    vecSize -= last - first;
}

template <typename T>
inline void Vector<T>::erase(const Iterator &first, const Iterator &last)
{
    if (first.vector != this || last.vector != this)
        throw Vector_error("The first iterator or the last iterator point to different vector");
    else if (first.index >= vecSize || last.index >= vecSize)
        throw Vector_error("An access to an invalid index has occured");
    else if (first.index > last.index)
        throw Vector_error("first is after the last");

    memmove(vec + first.index, vec + last.index, (vecSize - last.index) * sizeof(T));

    vecSize -= last.index - first.index;
}

template <typename T>
inline void Vector<T>::clear() { vecSize = 0; }

template <typename T>
inline typename Vector<T>::Iterator Vector<T>::begin() const { return Iterator(this, 0); }

template <typename T>
inline typename Vector<T>::Iterator Vector<T>::end() const { return Iterator(this, vecSize); }

template <typename T>
inline Vector<T>::Iterator::Iterator() : vector(nullptr), index(T(NULL)) {}

template <typename T>
inline Vector<T>::Iterator::Iterator(const Vector *_vector, unsigned int _index) : vector(_vector), index(_index) {}

template <typename T>
inline T &Vector<T>::Iterator::operator*() const { return (*vector)[index]; }

template <typename T>
inline T &Vector<T>::Iterator::operator[](int _num) const { return (*vector)[index + _num]; }

template <typename T>
inline typename Vector<T>::Iterator Vector<T>::Iterator::operator+(unsigned int num) const { return Iterator(vector, index + num); }

template <typename T>
inline typename Vector<T>::Iterator Vector<T>::Iterator::operator-(unsigned int num) const { return Iterator(vector, index - num); }

template <typename T>
inline typename Vector<T>::Iterator &Vector<T>::Iterator::operator+=(unsigned int num)
{
    index += num;
    return *this;
}

template <typename T>
inline typename Vector<T>::Iterator &Vector<T>::Iterator::operator-=(unsigned int num)
{
    index -= num;
    return *this;
}

template <typename T>
inline long long Vector<T>::Iterator::operator-(const Iterator &it) const { return index - it.index; }

template <typename T>
inline typename Vector<T>::Iterator &Vector<T>::Iterator::operator=(const Iterator &it)
{
    vector = it.vector, index = it.index;
    return *this;
}

template <typename T>
inline typename Vector<T>::Iterator &Vector<T>::Iterator::operator++()
{
    index++;
    return *this;
}

template <typename T>
inline typename Vector<T>::Iterator Vector<T>::Iterator::operator++(int)
{
    Iterator tmp(vector, index);
    index++;
    return tmp;
}

template <typename T>
inline typename Vector<T>::Iterator &Vector<T>::Iterator::operator--()
{
    index--;
    return *this;
}

template <typename T>
inline typename Vector<T>::Iterator Vector<T>::Iterator::operator--(int)
{
    Iterator tmp(vector, index);
    index--;
    return tmp;
}

template <typename T>
inline bool Vector<T>::Iterator::operator==(const Iterator &it) const { return vector == it.vector && index == it.index; }

template <typename T>
inline bool Vector<T>::Iterator::operator!=(const Iterator &it) const { return vector != it.vector || index != it.index; }

template <typename T>
inline bool Vector<T>::Iterator::operator>(const Iterator &it) const { return index > it.index; }

template <typename T>
inline bool Vector<T>::Iterator::operator>=(const Iterator &it) const { return index >= it.index; }

template <typename T>
inline bool Vector<T>::Iterator::operator<(const Iterator &it) const { return index < it.index; }

template <typename T>
inline bool Vector<T>::Iterator::operator<=(const Iterator &it) const { return index <= it.index; }

template <typename T>
NodeTree<T>::NodeTree(T input) : val(input), par(nullptr) {}

template <typename T>
NodeTree<T>::~NodeTree() { par = nullptr; }

template <typename T>
Tree<T>::Tree() : root(nullptr), treeSize(0) {}

template <typename T>
Tree<T>::~Tree()
{
    if (treeSize != 0)
    {
        Vector<Position> vec;

        (*this).postorder(getRoot(), vec);
        for (typename Vector<Position>::Iterator it = vec.begin(); it != vec.end(); it++)
            delete (*it).node;

        vec.clear();
    }
}

template <typename T>
Tree<T>::Position::Position(NodeTree<T> *input) : node(input) {}

template <typename T>
T &Tree<T>::Position::operator*() { return (*node).val; }

template <typename T>
typename Tree<T>::Position &Tree<T>::Position::setParent()
{
    node = (*node).par;
    return *this;
}

template <typename T>
typename Tree<T>::Position &Tree<T>::Position::setChild(int num)
{
    node = (*node).chi.at(num);
    return *this;
}

template <typename T>
inline typename Tree<T>::Position &Tree<T>::Position::setValue(T input)
{
    (*node).val = input;
    return *this;
}

template <typename T>
inline typename Tree<T>::Position Tree<T>::Position::getParent() const { return Tree<T>::Position((*node).par); }

template <typename T>
inline typename Tree<T>::Position Tree<T>::Position::getChild(int num) const { return Tree<T>::Position((*node).chi.at(num)); }

template <typename T>
inline bool Tree<T>::Position::isRoot() const { return node->par == nullptr; }

template <typename T>
inline bool Tree<T>::empty() const { return treeSize == 0; }

template <typename T>
inline int Tree<T>::size() const { return treeSize; }

template <typename T>
void Tree<T>::createRoot(T val)
{
    if (!empty())
    {
        throw Tree_error("Tree is not emtpy");
        return;
    }

    root = new NodeTree<T>{val};
    treeSize++;
}

template <typename T>
inline void Tree<T>::createChild(Position &where, T val) { (*where.node).chi.push_back(new NodeTree<T>{val}), treeSize++; }

template <typename T>
inline int Tree<T>::getChildNumber(const Position &where) const { return (*where.node).chi.treeSize(); }

template <typename T>
inline const Vector<typename Tree<T>::Position> &Tree<T>::getChildVector(const Position &where) const { return (*where.node).chi; }

template <typename T>
void Tree<T>::erase(Position &where)
{
    for (int i = 0; i < (*(*where.node).par).chi.treeSize(); i++)
    {
        if (where.node == (*(*where.node).par).chi[i])
        {
            (*(*where.node).par).chi.erase(i);
            break;
        }
    }

    Vector<Position> vec;
    preorder(where, vec);

    for (typename Vector<Position>::Iterator it = vec.begin(); it != vec.end(); it++)
    {
        delete (*it).node;
    }

    where.node = nullptr;
}

template <typename T>
void Tree<T>::preorder(const Position &where, Vector<Tree::Position> &vec) const
{
    if (where.node == nullptr)
        return;

    vec.push_back(where);

    for (int i = 0; i < (*where.node).chi.size(); i++)
        preorder(Position((*where.node).chi[i]), vec);
}

template <typename T>
void Tree<T>::postorder(const Position &where, Vector<Tree::Position> &vec) const
{
    if (where.node == nullptr)
        return;

    for (int i = 0; i < (*where.node).chi.size(); i++)
        preorder(Position((*where.node).chi[i]), vec);

    vec.push_back(where);
}

template <typename T>
typename Tree<T>::Position Tree<T>::getRoot() const
{
    if (empty())
        throw Tree_error("Tree is emtpy. Does not exist root");

    return Position(root);
}

template <typename T>
BinaryTree<T>::BinaryTree() : treeSize(0), head(nullptr) {}

template <typename T>
BinaryTree<T>::~BinaryTree()
{
    BinaryTree<T>::Position tmp(head);

    Vector<Position> vec;

    (*this).postorder(tmp, vec);
    for (typename Vector<Position>::Iterator it = vec.begin(); it != vec.end(); it++)
    {
        delete (*it).iter;
    }

    vec.clear();

    head = nullptr;
}

template <typename T>
bool BinaryTree<T>::empty() const { return head == nullptr; }

template <typename T>
int BinaryTree<T>::size() const { return treeSize; }

template <typename T>
void BinaryTree<T>::createRoot()
{
    if (!empty())
    {
        throw BinaryTree_error("Tree is not emtpy");
        return;
    }

    head = new Node<T>;

    treeSize += 1;
}

template <typename T>
void BinaryTree<T>::createChild(Position &where)
{
    if ((*where.iter).left != nullptr || (*where.iter).right != nullptr)
    {
        throw BinaryTree_error("input value is not leaf");
        return;
    }

    (*where.iter).left = new Node<T>;
    (*(*where.iter).left).par = where.iter;
    (*where.iter).right = new Node<T>;
    (*(*where.iter).right).par = where.iter;

    treeSize += 2;
}

template <typename T>
void BinaryTree<T>::erase(Position &where)
{
    Node<T> *parWhere = (*where.iter).par;
    Node<T> *tmp = (where.iter == (*where.iter).left) ? (*parWhere).right : (*parWhere).left;

    if ((*where.iter).left != NULL || (*where.iter).right != NULL)
    {
        throw BinaryTree_error("input value is not leaf");
        return;
    }

    if (parWhere == head)
        head = tmp, (*tmp).par = NULL;
    else
    {
        if ((*(*parWhere).par).left == parWhere)
            (*(*parWhere).par).left = tmp;
        else
            (*(*parWhere).par).right = tmp;
        //postorder을 통한 메모리 해제 추가.
    }

    delete where.iter;
    delete parWhere;

    treeSize -= 2;
}

template <typename T>
void BinaryTree<T>::preorder(const Position &where, Vector<BinaryTree::Position> &vec)
{
    if (where.iter == nullptr)
        return;

    vec.push_back(where);

    if ((*where.iter).left != nullptr)
        preorder(Position((*where.iter).left), vec);
    if ((*where.iter).right != nullptr)
        preorder(Position((*where.iter).right), vec);
}

template <typename T>
void BinaryTree<T>::inorder(const Position &where, Vector<BinaryTree::Position> &vec)
{
    if (where.iter == nullptr)
        return;

    if ((*where.iter).left != nullptr)
        inorder(Position((*where.iter).left), vec);

    vec.push_back(where);

    if ((*where.iter).right != nullptr)
        inorder(Position((*where.iter).right), vec);
}

template <typename T>
void BinaryTree<T>::postorder(const Position &where, Vector<BinaryTree::Position> &vec)
{
    if (where.iter == nullptr)
        return;

    if ((*where.iter).left != nullptr)
        postorder(Position((*where.iter).left), vec);

    if ((*where.iter).right != nullptr)
        postorder(Position((*where.iter).right), vec);

    vec.push_back(where);
}

template <typename T>
BinaryTree<T>::Position::Position(Node<T> *input) : iter(input) {}

template <typename T>
T &BinaryTree<T>::Position::operator*() { return iter->value; }

template <typename T>
typename BinaryTree<T>::Position &BinaryTree<T>::Position::setParent()
{
    iter = (*iter).par;
    return *this;
}

template <typename T>
typename BinaryTree<T>::Position &BinaryTree<T>::Position::setLeft()
{
    iter = (*iter).left;
    return *this;
}

template <typename T>
typename BinaryTree<T>::Position &BinaryTree<T>::Position::setRight()
{
    iter = (*iter).right;
    return *this;
}

template <typename T>
typename BinaryTree<T>::Position BinaryTree<T>::Position::getParent() const
{
    return BinaryTree<T>::Position((*iter).par);
}

template <typename T>
typename BinaryTree<T>::Position BinaryTree<T>::Position::getLeft() const
{
    return BinaryTree<T>::Position((*iter).left);
}

template <typename T>
typename BinaryTree<T>::Position BinaryTree<T>::Position::getRight() const
{
    return BinaryTree<T>::Position((*iter).right);
}

template <typename T>
bool BinaryTree<T>::Position::isRoot() const { return iter->par == nullptr; }

template <typename T>
typename BinaryTree<T>::Position BinaryTree<T>::root() const
{
    return Position(head);
}

template <typename T>
Heap<T>::Heap() : heapSize(0), heapCapacity(1), heap((T *)calloc(1, sizeof(T))) { last = heap - 1; }

template <typename T>
Heap<T>::~Heap() { free(heap); }

template <typename T>
inline bool Heap<T>::empty() const { return heapSize == 0; }

template <typename T>
inline unsigned int Heap<T>::height() const
{
    int height = 0;
    int tmp = heapSize;

    while (tmp)
    {
        tmp >>= 1, height++;
    }

    return height;
}

template <typename T>
inline unsigned int Heap<T>::size() const { return heapSize; }

template <typename T>
void Heap<T>::insert(const T &val)
{
    if (empty())
    {
        last = heap, *last = val, heapSize++;
        return;
    }

    if (isFull())
        reserve();

    *(++last) = val, heapSize++; // nex last nodet = val, last node = next last node, heapSize++;

    unsigned int tmp_index = heapSize - 1;
    unsigned int tmp_par_index = (heapSize >> 1) - 1; // tmp = last의 부모의 인덱스 값

    while (tmp_index != 0 && *(heap + tmp_index) < *(heap + tmp_par_index))
    {

        T tmp_val = *(heap + tmp_par_index);
        *(heap + tmp_par_index) = *(heap + tmp_index);
        *(heap + tmp_index) = tmp_val;
        T debug_par = *(heap + tmp_par_index);
        T debug_tmp = *(heap + tmp_index);

        tmp_index = tmp_par_index;
        tmp_par_index = ((tmp_index - 1) >> 1);
    }
}

template <typename T>
void Heap<T>::erase(Position &where)
{
    unsigned int tmp_index = where.index;
    unsigned int tmp_leftChild_index = (tmp_index << 1) ^ 1;
    unsigned int tmp_rightChild_index = ((tmp_index + 1) << 1);

    if (tmp_index >= heapSize)
        throw Heap_error("invalid locate");

    *(heap + tmp_index) = *last;
    heapSize--, last--;

    while (1)
    {
        if ((tmp_leftChild_index) >= heapSize && (tmp_rightChild_index >= heapSize))
            break;
        else if (tmp_leftChild_index >= heapSize)
        {
            if (*(heap + tmp_index) <= *(heap + tmp_rightChild_index))
                break;

            T tmp_next_val = *(heap + tmp_rightChild_index);
            *(heap + tmp_rightChild_index) = *(heap + tmp_index);
            *(heap + tmp_index) = tmp_next_val;

            break;
        }
        else if (tmp_rightChild_index >= heapSize)
        {
            if (*(heap + tmp_index) <= *(heap + tmp_leftChild_index))
                break;

            T tmp_next_val = *(heap + tmp_leftChild_index);
            *(heap + tmp_leftChild_index) = *(heap + tmp_index);
            *(heap + tmp_index) = tmp_next_val;

            break;
        }

        if (!(*(heap + tmp_index) > *(heap + tmp_leftChild_index) || *(heap + tmp_index) > *(heap + tmp_rightChild_index)))
            return;

        int tmp_next_index =
            (*(heap + tmp_leftChild_index) < *(heap + tmp_rightChild_index)) ? tmp_leftChild_index : tmp_rightChild_index;

        T tmp_next_val = *(heap + tmp_next_index);
        *(heap + tmp_next_index) = *(heap + tmp_index);
        *(heap + tmp_index) = tmp_next_val;

        tmp_index = tmp_next_index;
        tmp_leftChild_index = ((tmp_index + 1) << 1) - 1;
        tmp_rightChild_index = ((tmp_index + 1) << 1);
    }
}

template <typename T>
void Heap<T>::erase()
{
    unsigned int tmp_index = 0;
    unsigned int tmp_leftChild_index = 1;
    unsigned int tmp_rightChild_index = 2;

    if (tmp_index >= heapSize)
        throw Heap_error("invalid locate");

    *(heap + tmp_index) = *last;
    heapSize--, last--;

    while (1)
    {
        if ((tmp_leftChild_index) >= heapSize && (tmp_rightChild_index >= heapSize))
            break;
        else if (tmp_leftChild_index >= heapSize)
        {
            if (*(heap + tmp_index) <= *(heap + tmp_rightChild_index))
                break;

            T tmp_next_val = *(heap + tmp_rightChild_index);
            *(heap + tmp_rightChild_index) = *(heap + tmp_index);
            *(heap + tmp_index) = tmp_next_val;

            break;
        }
        else if (tmp_rightChild_index >= heapSize)
        {
            if (*(heap + tmp_index) <= *(heap + tmp_leftChild_index))
                break;

            T tmp_next_val = *(heap + tmp_leftChild_index);
            *(heap + tmp_leftChild_index) = *(heap + tmp_index);
            *(heap + tmp_index) = tmp_next_val;

            break;
        }

        if (!(*(heap + tmp_index) > *(heap + tmp_leftChild_index) || *(heap + tmp_index) > *(heap + tmp_rightChild_index)))
            return;

        int tmp_next_index =
            (*(heap + tmp_leftChild_index) < *(heap + tmp_rightChild_index)) ? tmp_leftChild_index : tmp_rightChild_index;

        T tmp_next_val = *(heap + tmp_next_index);
        *(heap + tmp_next_index) = *(heap + tmp_index);
        *(heap + tmp_index) = tmp_next_val;

        tmp_index = tmp_next_index;
        tmp_leftChild_index = ((tmp_index + 1) << 1) - 1;
        tmp_rightChild_index = ((tmp_index + 1) << 1);
    }
}

template <typename T>
void Heap<T>::clear() { heapSize = 0; }

template <typename T>
Heap<T>::Position::Position() : hp(nullptr), index(0) {}

template <typename T>
Heap<T>::Position::Position(const Heap *_heap, int _index) : hp(_heap), index(_index) {}

template <typename T>
inline const T &Heap<T>::Position::getVal() const { return *((*hp).heap + index); }

template <typename T>
inline typename Heap<T>::Position &Heap<T>::Position::setParent()
{
    if (isRoot())
        throw Heap_error("this is Root");
    index = (index - 1) >> 1;

    return *this;
}

template <typename T>
inline typename Heap<T>::Position &Heap<T>::Position::setLeftChild()
{
    int tmp = (index << 1) ^ 1;
    index = tmp;

    return *this;
}

template <typename T>
inline typename Heap<T>::Position &Heap<T>::Position::setRightChild()
{
    int tmp = ((index + 1) << 1);
    index = tmp;

    return *this;
}

template <typename T>
inline typename Heap<T>::Position Heap<T>::Position::getParent() const
{
    return Position(hp, (index - 1) >> 1);
}

template <typename T>
inline typename Heap<T>::Position Heap<T>::Position::getLeftChild() const
{
    int tmp = (index << 1) ^ 1;
    return Position(hp, tmp);
}

template <typename T>
inline typename Heap<T>::Position Heap<T>::Position::getRightChild() const
{
    int tmp = ((index + 1) << 1);
    return Position(hp, tmp);
}

template <typename T>
int Heap<T>::Position::depth() const
{
    int depth = 0;
    int tmp = index + 1;

    while (tmp)
    {
        tmp >>= 1, depth++;
    }

    return depth;
}

template <typename T>
inline bool Heap<T>::Position::isLeftChild() const
{
    if (isRoot())
        return false;
    else
        return index & 1; // 홀수라면 왼쪽 자식이므로 1을 반환
}

template <typename T>
inline bool Heap<T>::Position::isRightChild() const
{
    if (isRoot())
        return false;
    else
        return !(index & 1); // 짝수라면 오른쪽 자식이므로 1을 반환
}

template <typename T>
inline bool Heap<T>::Position::isRoot() const { return (index == 0) ? true : false; }

template <typename T>
inline bool Heap<T>::isFull() const { return heapSize == heapCapacity; }

template <typename T>
inline void Heap<T>::reserve(unsigned int _heapCapacity)
{
    T *tmp;
    if (_heapCapacity <= heapSize)
        throw Heap_error("input heapCapacity less then heapSize");
    if (!(tmp = (T *)realloc(heap, sizeof(T) * (_heapCapacity))))
        throw Heap_error("Out of Memory");
    else if (tmp != heap)
        heap = tmp, last = tmp + heapSize - 1;

    heapCapacity = _heapCapacity;
}

template <typename T>
inline void Heap<T>::reserve()
{
    T *tmp;
    if (!(tmp = (T *)realloc(heap, sizeof(T) * ((heapCapacity << 1) ^ 1))))
        throw Heap_error("Out of Memory");
    else if (tmp != heap)
        heap = tmp, last = tmp + heapSize - 1;

    heapCapacity = (heapCapacity << 1) ^ 1;
}

template <typename T>
inline typename Heap<T>::Position Heap<T>::getRoot() const
{
    if (empty())
        throw Heap_error("Heap is emtpy");

    return Position(this, 0);
}

template <typename T>
inline typename Heap<T>::Position Heap<T>::getLast() const
{
    if (empty())
        throw Heap_error("Heap is emtpy");

    return Position(this, last - heap);
}

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
    for (unsigned int i = 0; i < vertices.size(); i++)
        T[i] = std::numeric_limits<unsigned int>::max();

    Te MAX = std::numeric_limits<Te>::max(); // Te 자료형의 최대값을 반환하는 numeric_limits
    if (MAX == 0)
    {
        throw AL_Graph_error("can't find MAX of weight");
    }

    unsigned int start = u.index;
    for (unsigned int i = 0; i < vertices.size(); i++)
        arr[i] = MAX;
    arr[start] = 0;

    Node *next = vertices[start].next;
    if (next == NULL)
        return;

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

        for (unsigned int i = sel + 1; i < vertices.size(); i++)
            sel = (arr[sel] < arr[i]) ? sel : (label[i]) ? sel
                                                         : i;
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

    for (unsigned int i = 0; i < vertices.size(); i++)
    {
        std::cout << vertices[i].v << " : " << arr[i];
        std::cout << "\t\t|\t";

        Stack<Tv> path;
        unsigned int tmp = i;
        while (T[tmp] != std::numeric_limits<unsigned int>::max())
        {
            path.push(vertices[tmp].v);
            tmp = T[tmp];
        }

        path.push(vertices[start].v);

        while (!path.empty())
            std::cout << path.pop() << ' ';

        std::cout << '\n';
    }
}

/*
template <typename Tv, typename Te>
Vector<typename AL_Graph<Tv, Te>::Vertex> AL_Graph<Tv, Te>::Dijkstra(const Vertex &u, const Vertex &v)
{
    Te *S = new Te[vertices.size()], fill_n(S, vertices.size(), -1);
    unsigned int *T = new unsigned int[vertices.size()]{0};
    // HEAP에 대한 테스트 완료 후 작성
}
*/

// 정렬함수 : 병합정렬, 힙정렬

template <typename T>
class _basic_cmp
{
    int operator()(const T &a, const T &b) { return (a < b) ? -1 : ((a == b) ? 0 : 1); }
};

template <typename T>
using basic_cmp = _basic_cmp<T>;

template <typename T>
int basic_cmp_T(T a, T b)
{
    if (a < b)
        return -1;
    else if (a == b)
        return 0;
    else
        return 1;
}

/*
 * ==============
 * ===병합정렬====
 * ==============
*/

template <typename T>
void merge_sort(T *arr, unsigned int size)
{
    merge_sort(arr, size, [](const T &A, const T &B) -> bool
               { return (A <= B) ? 0 : 1; });
}

template <typename T>
void merge_sort(T *first, T *last)
{
    if (last <= first)
        return;
    merge_sort(first, last - first);
}

template <typename T>
void merge_sort(const typename Vector<T>::Iterator &first, const typename Vector<T>::Iterator &last)
{
    if (last <= first)
        return;
    merge_sort(&*first, last - first);
}

template <typename T>
void merge_sort(T *arr, unsigned long long first, unsigned long long last)
{
    if (last <= first)
        return;
    merge_sort(arr + first, last - first + 1);
}

template <typename T, typename cmp_f>
void merge_sort(T *arr, unsigned int size, cmp_f cmp)
{
    if (size == 1)
        return;

    merge_sort(arr, (size + 1) / 2, cmp);
    merge_sort(arr + (size + 1) / 2, size / 2, cmp);

    T *tmp = (T *)malloc(size * sizeof(T));
    memcpy(tmp, arr, size * sizeof(T));

    T *p1 = tmp;
    T *p2 = tmp + (size + 1) / 2;
    T *p1_last = p2;
    T *p2_last = tmp + size;

    for (unsigned int i = 0; i < size; i++)
    {
        if (p1 == p1_last)
        {
            memcpy(arr + i, p2, (size - i) * sizeof(T));
            break;
        }
        else if (p2 == p2_last)
        {
            memcpy(arr + i, p1, (size - i) * sizeof(T));
            break;
        }

        if (cmp(*p1, *p2) <= 0)
            arr[i] = *p1, p1++;
        else
            arr[i] = *p2, p2++;
    }

    free(tmp);
}

template <typename T, typename cmp_f>
void merge_sort(T *first, T *last, cmp_f cmp)
{
    if (last <= first)
        return;
    merge_sort(first, last - first, cmp);
}

template <typename T, typename cmp_f>
void merge_sort(
    const typename Vector<T>::Iterator &first, const typename Vector<T>::Iterator &last, cmp_f cmp)
{
    if (last <= first)
        return;
    merge_sort(&*first, last - first, cmp);
}

template <typename T, typename cmp_f>
void merge_sort(T *arr, unsigned long long first, unsigned long long last, cmp_f cmp)
{
    if (last <= first)
        return;
    merge_sort(arr + first, last - first + 1, cmp);
}

/*
 * ==============
 * ====힙정렬====
 * ==============
*/

template <typename T>
void heap_sort(T *arr, unsigned long long size, int(fp)(T, T) = basic_cmp_T)
{
    if (size <= 1)
        return;

    for (unsigned long long i = 1; i < size; i++)
    {
        unsigned long long tmp = i;
        unsigned long long tmp_par = (tmp - 1) >> 1;
        T tmp_val;

        while (tmp != 0 && fp(arr[tmp], arr[tmp_par]) > 0)
        {
            tmp_val = arr[tmp_par];
            arr[tmp_par] = arr[tmp];
            arr[tmp] = tmp_val;

            tmp = tmp_par;
            tmp_par = (tmp_par - 1) >> 1;
        }
    }

    for (unsigned long long i = size - 1; i != 1; i--)
    {

        T val = *arr;
        *arr = arr[i];
        arr[i] = val;

        unsigned long long tmp = 0;
        unsigned long long tmp_left = 1;
        unsigned long long tmp_right = 2;

        while (1)
        {
            T tmp_val;

            if (tmp_right >= i)
            {
                if (tmp_left >= i)
                    break;

                if (fp(arr[tmp], arr[tmp_left]) < 0)
                {
                    tmp_val = arr[tmp];
                    arr[tmp] = arr[tmp_left];
                    arr[tmp_left] = tmp_val;
                }

                break;
            }

            if (!(fp(arr[tmp], arr[tmp_left]) < 0 || fp(arr[tmp], arr[tmp_right]) < 0))
                break;

            if (fp(arr[tmp_left], arr[tmp_right]) > 0)
            {
                tmp_val = arr[tmp];
                arr[tmp] = arr[tmp_left];
                arr[tmp_left] = tmp_val;

                tmp = tmp_left;
            }
            else
            {
                tmp_val = arr[tmp];
                arr[tmp] = arr[tmp_right];
                arr[tmp_right] = tmp_val;

                tmp = tmp_right;
            }

            tmp_left = (tmp << 1) ^ 1;
            tmp_right = (tmp + 1) << 1;
        }
    }

    T val = *arr;
    *arr = arr[1];
    arr[1] = val;
}

template <typename T>
void heap_sort(T *first, T *last, int(fp)(T, T) = basic_cmp_T)
{
    if (last <= first)
        return;
    heap_sort(first, last - first, fp);
}

template <typename T>
void heap_sort(const typename Vector<T>::Iterator &first, const typename Vector<T>::Iterator &last, int(fp)(T, T) = basic_cmp_T)
{
    if (last <= first)
        return;
    heap_sort(&*first, last - first, fp);
}

template <typename T>
void heap_sort(T *arr, unsigned long long first, unsigned long long last, int(fp)(T, T) = basic_cmp_T)
{
    if (last <= first)
        return;
    heap_sort(arr + first, last - first + 1, fp);
}

#endif