#include "tree.hpp"

template <typename T>
NodeTree<T>::NodeTree(T input) : val(input), par(nullptr) {}

template <typename T>
NodeTree<T>::~NodeTree() { par = nullptr; }

template <typename T>
Tree<T>::Tree() : root(nullptr), size(0) {}

template <typename T>
Tree<T>::~Tree()
{
    if(size != 0)
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
inline bool Tree<T>::isEmpty() const { return size == 0; }

template <typename T>
inline int Tree<T>::isSize() const { return size; }

template <typename T>
void Tree<T>::createRoot(T val)
{
    if (!isEmpty())
    {
        throw Tree_error("Tree is not emtpy");
        return;
    }

    root = new NodeTree<T>{val};
    size++;
}

template <typename T>
inline void Tree<T>::createChild(Position &where, T val){ (*where.node).chi.push_back(new NodeTree<T>{val}), size++; }

template <typename T>
inline int Tree<T>::getChildNumber(const Position &where) const { return (*where.node).chi.size(); }

template <typename T>
inline const Vector<typename Tree<T>::Position> &Tree<T>::getChildVector(const Position &where) const { return (*where.node).chi; }

template <typename T>
void Tree<T>::erase(Position &where)
{
    for (int i = 0; i < (*(*where.node).par).chi.size(); i++)
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
    if(where.node == nullptr) return;

    vec.push_back(where);

    for (int i = 0; i < (*where.node).chi.size(); i++)
        preorder(Position((*where.node).chi[i]), vec);
}

template <typename T>
void Tree<T>::postorder(const Position &where, Vector<Tree::Position> &vec) const
{
    if(where.node == nullptr) return;

    for (int i = 0; i < (*where.node).chi.size(); i++)
        preorder(Position((*where.node).chi[i]), vec);

    vec.push_back(where);
}

template <typename T>
typename Tree<T>::Position Tree<T>::getRoot() const
{
    if(isEmpty()) throw Tree_error("Tree is emtpy. Does not exist root");
    
    return Position(root);
}