#include "DLL.hpp"

template <typename T>
Node<T>::Node(T input) : left(NULL), value(input), right(NULL) {}

template <typename T>
Node<T>::~Node()
{
    value = (T)NULL;
    left = nullptr;
    right = nullptr;
}

template <typename T>
DLL<T>::DLL() : head(nullptr), size(0) {}

template <typename T>
DLL<T>::~DLL()
{
    if (!isEmpty())
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
bool DLL<T>::isEmpty() const { return !size; }

template <typename T>
int DLL<T>::isSize() const { return size; }

template <typename T>
void DLL<T>::insertFront(T input)
{
    if (isEmpty())
    {
        head = new Node<T>{input};
        (*head).left = head;
        (*head).right = head;
        size++;
        return;
    }

    Node<T> *node = new Node<T>{input};
    (*(*head).left).right = node; // 원형 DLL 이므로, (*head).left는 DLL의 꼬리를 의미함.
    (*node).left = (*head).left;
    (*node).right = head;
    (*head).left = node;
    head = node;

    size++;
}

template <typename T>
void DLL<T>::insertBack(T input)
{
    if (isEmpty())
    {
        head = new Node<T>{input};
        (*head).left = head;
        (*head).right = head;
        size++;
        return;
    }

    Node<T> *node = new Node<T>{input};
    (*(*head).left).right = node;
    (*node).left = (*head).left;
    (*node).right = head;
    (*head).left = node;

    size++;
}

template <typename T>
void DLL<T>::insertMiddle(int index, T input)
{
    if (index >= size || index < 0) // size가 0인경우, 모든 경우에 대해서 거름.
    {
        if (index == 0 && size == 0)
        {
            insertFront(input);
            return;
        }

        std::string error_str;
        error_str = "Reference to (" + std::to_string(index) + ") that does not exist";
        throw DLL_error(error_str);
    }

    if (index == 0) // 이 처리를 해주지 않으면 맨 앞이 아니라, 맨 마지막에 값을 삽입한거랑 똑같은 일이 발생함
    {
        insertFront(input);
        return;
    }

    Node<T> *node = new Node<T>{input};

    Node<T> *tmp = head;
    for (int i = 0; i < index; i++)
        tmp = (*tmp).right;

    (*(*tmp).left).right = node;
    (*node).left = (*tmp).left;
    (*node).right = tmp;
    (*tmp).left = node;

    size++;
}

template <typename T>
void DLL<T>::replace(int index, T input)
{
    if (index >= size || index < 0)
    {
        std::string error_str;
        error_str = "Reference to (" + std::to_string(index) + ") that does not exist";
        throw DLL_error(error_str);
        return;
    }

    Node<T> *tmp = head;
    for (int i = 0; i < index; i++)
        tmp = (*tmp).right;

    (*tmp).value = input;
}

template <typename T>
T DLL<T>::getFront() const
{
    if (isEmpty())
    {
        throw DLL_error("DLL is empty!");
        return (T)NULL;
    }

    return (*head).value;
}

template <typename T>
T DLL<T>::getBack() const
{
    if (isEmpty())
    {
        throw DLL_error("DLL is empty!");
        return (T)NULL;
    }

    return (*(*head).left).value;
}

template <typename T>
T DLL<T>::getMiddle(int index) const
{
    if (index >= size || index < 0) // 0인경우 자동으로 걸러줌
    {
        std::string error_str;
        error_str = "Reference to (" + std::to_string(index) + ") that does not exist";
        throw DLL_error(error_str);
        return (T)NULL;
    }

    Node<T> *tmp = head;
    for (int i = 0; i < index; i++)
        tmp = (*tmp).right;

    return (*tmp).value;
}

template <typename T>
void DLL<T>::erase(int index)
{
    if (index >= size || index < 0)
    {
        std::string error_str;
        error_str = "Reference to (" + std::to_string(index) + ") that does not exist";
        throw DLL_error(error_str);
        return;
    }

    Node<T> *tmp = head;
    for (int i = 0; i < index; i++)
        tmp = (*tmp).right;

    (*(*tmp).left).right = (*tmp).right;
    (*(*tmp).right).left = (*tmp).left;

    if (index == 0)
        head = (*head).right; // 0번째를 삭제할경우 head 변경됨. size가 1인 DLL을 erase해도, ~Node 소멸자 덕분에 null으 들어감.

    size--;
    delete tmp;
}

template <typename T>
void DLL<T>::clear()
{
    if (isEmpty())
        return;
    Node<T> *tmp = (*head).right;

    do
    {
        tmp = (*tmp).right;
        delete (*tmp).left;
    } while (tmp != head);

    delete tmp;

    size = 0;
    head = nullptr;
}

template <typename T>
DLL<T>::Iterator::Iterator(Node<T> *input) : iter(input) {}

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
T &DLL<T>::Iterator::operator*()
{
    return (*(*this).iter).value;
}

template <typename T>
bool DLL<T>::Iterator::operator==(const Iterator &input) const
{
    return iter == input.iter;
}

template <typename T>
bool DLL<T>::Iterator::operator!=(const Iterator &input) const
{
    return iter != input.iter;
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
typename DLL<T>::Iterator DLL<T>::getIterator(int index) const
{
    if (index >= size || index < 0) // 0인 경우 자동으로 걸러줌
    {
        std::string error_str;
        error_str = "Reference to (" + std::to_string(index) + ") that does not exist";
        throw DLL_error(error_str);
        return Iterator(nullptr);
    }

    Node<T> *tmp = head;
    for (int i = 0; i < index; i++)
        tmp = (*tmp).right;

    return Iterator(tmp);
}