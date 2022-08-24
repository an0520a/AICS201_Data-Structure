#ifndef DLL_H
#define DLL_H

#include <exception>

class DLL_error : public std::exception
{
public:
    DLL_error(const std::string &_errorMessage) : errorMessage("DLL error : " + _errorMessage) {}
    const char *what() const throw() override { return errorMessage.c_str(); }

private:
    std::string errorMessage;
};

template <typename T>
class DLL;

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

    friend class DLL<T>;
};

// None trailer node
template <typename T>
class DLL
{
public:
    DLL();
    ~DLL();
    bool isEmpty() const;
    int isSize() const;
    void insertFront(T input);
    void insertBack(T input);
    void insertMiddle(int index, T input);
    void replace(int index, T input);
    T getFront() const;
    T getBack() const;
    T getMiddle(int index) const;
    void erase(int index);
    void clear();

    class Iterator
    {
    public:
        Iterator(Node<T>* input = nullptr);
        Iterator &operator++();
        Iterator operator++(int);
        Iterator &operator--();
        Iterator operator--(int);
        T& operator*(); // 이건 const를 붙여야되나?
        bool operator==(const Iterator&) const;
        bool operator!=(const Iterator&) const;
    private:
        Node<T> *iter;
    };

    Iterator begin() const;
    Iterator end() const;
    Iterator getIterator(int index) const;

private:
    Node<T> *head;
    unsigned int size; // 없어도 구현은 가능하나, 시간 복잡도가 너무 커질듯 함.
};

#endif