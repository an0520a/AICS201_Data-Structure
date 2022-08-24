#include <iostream>
#include "DLL.hpp"
#include "DLL.cpp"

using namespace std;

template <typename T>
void DLL_out(const DLL<T>& dll)
{

    for (typename DLL<T>::Iterator it = dll.begin(); it != dll.end(); it++)
    {
        cout << ' ' << *it;
    }

    cout << endl;
}

int main()
{
    DLL<char> dll;

    cout << "isEmpty test (size == 0)" << endl;
    cout << dll.isEmpty() << endl;

    cout << "pushMiddle test (at size == 0 && index == 0) : dll.pushMiddle(0, 'e')" << endl;
    dll.insertMiddle(0, 'e');
    cout << endl;

    cout << "isEmpty test (size != 0)" << endl;
    cout << dll.isEmpty() << endl;
    cout << endl;

    cout << "pushBack test : " << endl;
    dll.insertBack('l');
    dll.insertBack('l');
    dll.insertBack('o');
    dll.insertBack(',');
    dll.insertBack(' ');
    dll.insertBack('W');
    dll.insertBack('o');
    dll.insertBack('r');
    dll.insertBack('l');
    dll.insertBack('d');
    dll.insertBack('!');
    cout << endl;

    DLL_out(dll);

    cout << "pushFront test : dll.pushFront('H')" << endl;
    dll.insertFront('H');
    cout << endl;

    cout << "pushMiddle test : dll.pushMiddle(5, '!')" << endl;
    dll.insertMiddle(5, '!');
    cout << endl;

    cout << "replace test : dll.pushMiddle(5, '@')" << endl;
    dll.replace(5, '@');
    cout << endl;

    cout << "isSize test : dll.isSize()" << endl;
    cout << dll.isSize() << endl;
    cout << endl;

    cout << "getFront test : dll.getFront()" << endl;
    cout << dll.getFront() << endl;
    cout << endl;

    cout << "getBack test : dll.getBack()" << endl;
    cout << dll.getBack() << endl;
    cout << endl;

    cout << "getMiddle test : dll.getMiddle(5)" << endl;
    cout << dll.getMiddle(5) << endl;
    cout << endl;

    cout << "getIterator test : tmp = dll.getIterator(5)" << endl;
    DLL<char>::Iterator tmp = dll.getIterator(5);
    cout << (*tmp) << endl;
    cout << endl;

    cout << "erase test : dll.erase(5);" << endl;
    dll.erase(5);
    cout << endl;

    cout << "getPointer delete test : p" << endl;
    //cout << (*tmp) << (*++tmp) << (*tmp++) << endl;
    //주석 제거시 segment fault, 잘 해제 되었음을 알 수 있음.
    cout << endl;
    tmp = (DLL<char>::Iterator)NULL; // tmp가 가리키는 주소값 자체는 자동으로 초기화 되지 않기 때문에, 직접 초기화 해야함

    cout << "erase test 2 : dll.erase(0);" << endl; // 0번째 인덱스에 해당하는걸 지워도 안전성을 보장할 수 있는가?
    dll.erase(0);
    cout << endl;

    cout << "isSize() test 2 : dll.isSize();" << endl;
    cout << dll.isSize() << endl;
    cout << endl;

    cout << "getPointer clean test : dll.clear()" << endl;
    dll.clear();
    cout << endl;

    cout << "getPointer clean - push test : dll.pushBack('+')" << endl;
    dll.insertBack('+');
    cout << endl;

    cout << "getPointer clean - push test : dll.pushBack('-')" << endl;
    dll.insertBack('-');
    cout << endl;

    cout << "getPointer clean - push test : dll.pushFront('c')" << endl;
    dll.insertFront('c');
    cout << endl;

    cout << "Iterator test - (*p++):" << endl;
    DLL<char>::Iterator p = dll.begin();
    cout << (*p++) << endl;
    cout << endl;

    cout << "Iterator test : *p" << endl;
    cout << (*p) << endl;
    cout << endl;

    cout << "Iterator test : (*++p)" << endl;
    cout << (*++p) << endl;
    cout << endl;

    cout << "Iterator test - (*p--):" << endl;
    cout << (*p--) << endl;
    cout << endl;

    cout << "Iterator test : *p" << endl;
    cout << (*p) << endl;
    cout << endl;

    cout << "Iterator test : (*--p)" << endl;
    cout << (*--p) << endl;
    cout << endl;

    try
    {
        dll.insertMiddle(-5, 0);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}