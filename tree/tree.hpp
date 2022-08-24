#ifndef TREE_H
#define TREE_H

#include <exception>
#include <string>
#include "../vector/vector.hpp"
#include "../vector/vector.cpp"

class Tree_error : public std::exception
{
public:
    Tree_error(const std::string &_errorMessage) : errorMessage("Tree error : " + _errorMessage) {}
    const char *what() const throw() override { return errorMessage.c_str(); }

private:
    std::string errorMessage;
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
    Vector<NodeTree<T>*> chi;

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
    bool isEmpty() const;
    int isSize() const;
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
    NodeTree<T>* root;
    int size;
};

#endif