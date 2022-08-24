#include <iostream>
#include "vector.hpp"
#include "vector.cpp"

using namespace std;

int main()
{
    Vector<int> vec;
    cout << "vector capacity : " << vec.capacity() << "\n\n";

    cout << "acces where invaild index" << endl;
    try
    {
        vec.at(0);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << "\n\n";
    }

    cout << "vector push_back : 0, 1, 2, 3, 4, 5, 6, 7, 8, 9" << endl;
    for (int i = 0; i < 10; i++)
        vec.push_back(i);
    cout << endl;

    cout << "Vector out using Iterator :";
    for (Vector<int>::Iterator it = vec.begin(); it < vec.end(); it++)
    {
        cout << ' ' << *it;
    }
    cout << "\n\n";

    Vector<int>::Iterator vec_p = vec.begin();
    cout << "Iterator pointer access test *(vec_p + 3) : " << *(vec_p + 3) << endl;
    cout << "Iterator [] access test vec[3] : " << vec[3] << endl;
    cout << "Iterator at access test vec.at(3) : " << vec.at(3) << endl;
    cout << "Iterator at acces where invaild index" << endl;
    try
    {
        vec.at(15);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << "\n\n";
    }

    cout << "Vector insert(3, -1)"
         << "\n\n";
    vec.insert(3, -1);

    cout << "Vector out using Iterator :";
    for (Vector<int>::Iterator it = vec.begin(); it < vec.end(); it++)
    {
        cout << ' ' << *it;
    }
    cout << "\n\n";

    cout << "vector size test : " << vec.size() << "\n\n";

    cout << "Vector erase(3)"
         << "\n\n";
    vec.erase(3);

    cout << "Vector out using Iterator :";
    for (Vector<int>::Iterator it = vec.begin(); it < vec.end(); it++)
    {
        cout << ' ' << *it;
    }
    cout << "\n\n";

    cout << "vector size test : " << vec.size() << "\n\n";

    cout << "vector capacity test : " << vec.capacity() << "\n\n";

    vec.resize(16, 1);
    cout << "vector resize(16, 1)"
         << "\n\n";

    cout << "Vector out using Iterator :";
    for (Vector<int>::Iterator it = vec.begin(); it < vec.end(); it++)
    {
        cout << ' ' << *it;
    }
    cout << "\n\n";

    cout << "vector size test : " << vec.size() << "\n\n";

    cout << "vector capacity test : " << vec.capacity() << "\n\n";

    vec.resize(32, 1);
    cout << "vector resize(32, 1)"
         << "\n\n";
    cout << "Vector out using Iterator :";
    for (Vector<int>::Iterator it = vec.begin(); it < vec.end(); it++)
    {
        cout << ' ' << *it;
    }
    cout << "\n\n";

    cout << "vector size test : " << vec.size() << "\n\n";

    cout << "vector capacity test : " << vec.capacity() << "\n\n";

    vec.resize(1);
    cout << "vector resize(1)"
         << "\n\n";
    cout << "Vector out using Iterator :";
    for (Vector<int>::Iterator it = vec.begin(); it < vec.end(); it++)
    {
        cout << ' ' << *it;
    }
    cout << "\n\n";

    cout << "vector size test : " << vec.size() << "\n\n";

    cout << "vector capacity test : " << vec.capacity() << "\n\n";

    vec.clear();
    cout << "vector clear()"
         << "\n\n";

    cout << "vector push_back : 0 ~ 31" << endl;
    for (int i = 0; i < 32; i++)
        vec.push_back(i);
    cout << endl;

    cout << "Vector out using Iterator :";
    for (Vector<int>::Iterator it = vec.begin(); it < vec.end(); it++)
    {
        cout << ' ' << *it;
    }
    cout << "\n\n";

    vec.assign(5, 3);
    cout << "vector assign(5, 3)"
         << "\n\n";
    cout << "Vector out using Iterator :";
    for (Vector<int>::Iterator it = vec.begin(); it < vec.end(); it++)
    {
        cout << ' ' << *it;
    }
    cout << "\n\n";

    cout << "vector size test : " << vec.size() << "\n\n";

    cout << "vector capacity test : " << vec.capacity() << "\n\n";

    vec.clear();
    cout << "vector clear()"
         << "\n\n";

    cout << "vector push_back : 0 ~ 31" << endl;
    for (int i = 0; i < 32; i++)
        vec.push_back(i);
    cout << endl;

    cout << "Vector out using Iterator :";
    for (Vector<int>::Iterator it = vec.begin(); it < vec.end(); it++)
    {
        cout << ' ' << *it;
    }
    cout << "\n\n";

    cout << "assign(Vector<int>::Iterator(&vec[11]), vec.end())"
         << "\n\n";
    vec.assign(vec_p + 11, vec.end());

    cout << "Vector out using Iterator :";
    for (Vector<int>::Iterator it = vec.begin(); it < vec.end(); it++)
    {
        cout << ' ' << *it;
    }
    cout << "\n\n";

    cout << "vector size test : " << vec.size() << "\n\n";

    cout << "vector capacity test : " << vec.capacity() << "\n\n";

    cout << "vector copy Operator test : ";
    Vector<int> copytest;

    {
        Vector<int> tmp;

        for (int i = 0; i < 64; i++)
            tmp.push_back(i);

        copytest = tmp;
    }

    for (Vector<int>::Iterator it = copytest.begin(); it < copytest.end(); it++)
    {
        cout << ' ' << *it;
    }
    cout << "\n\n";

    cout << "vector coppy test : ";

    Vector<int> copytest2(copytest);
    copytest.clear();

    for (Vector<int>::Iterator it = copytest2.begin(); it < copytest2.end(); it++)
    {
        cout << ' ' << *it;
    }

    cout << "\n\n";

    cout << "vec out : ";
    for (Vector<int>::Iterator it = vec.begin(); it < vec.end(); it++)
    {
        cout << ' ' << *it;
    }

    cout << "\n\n";

    cout << "vec iterator + operator test\n";
    int tmp_i = 0;
    for (Vector<int>::Iterator it = vec.begin(); tmp_i < vec.size(); tmp_i++)
    {
        cout << ' ' << *(it + tmp_i);
    }

    cout << "\n\n";

    cout << "vec iterator - operator test\n";
    tmp_i = vec.size();
    for (Vector<int>::Iterator it = vec.end(); tmp_i > 0; tmp_i--)
    {
        cout << ' ' << *(it - tmp_i);
    }

    cout << "\n\n";

    cout << "vec iterator, vec_p += 3 : " << *(vec_p += 3) << "\n\n";
    cout << "vec iterator, vec_p -= 3 : " << *(vec_p -= 3) << "\n\n";

    Vector<int>::Iterator vec_p2;
    vec_p2 = vec_p + 3;

    cout << "vec Iterator test, vec_p2 - vec_p : " << vec_p2 - vec_p << "\n\n";

    //cout << *(-3 + vec_p2) << endl;

    Vector<int> vec2 = vec;
    cout << "set vec2, vec2 = vec;"
         << "\n\n";

    cout << "insert test, vec2.insert(vec2.begin() + 1, vec.begin(), vec.end() : " << endl;
    vec2.insert(vec2.begin() + 1, vec.begin(), vec.end());
    for (int i = 0; i < vec2.size(); i++)
        cout << vec2[i] << ' ';
    cout << "\n\n";

    Vector<int> vec3 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << "vec3, Constructor(Initializer_list) test ({0, 1, 2, 3, 4, 5, 6, 7, 8, 9})  : ";
    for (int i = 0; i < vec3.size(); i++)
        cout << vec3[i] << ' ';
    cout << "\n\n";

    cout << "vec3 erase(3, 6) test  : ";
    vec3.erase(3, 6);
    for (int i = 0; i < vec3.size(); i++)
        cout << vec3[i] << ' ';
    cout << "\n\n";
    cout << "vec3 size : " << vec3.size() << "\n\n";

    cout << "Iterator safety to reserve test : ";
    Vector<int>::Iterator vec3_p1 = vec3.begin();
    Vector<int>::Iterator vec3_p2 = vec3.end();
    vec3.insert(vec3.end(), vec2.begin(), vec2.end());
    vec3.insert(vec3.end(), vec.begin(), vec.end());

    for (Vector<int>::Iterator iter = vec3_p1; iter < vec3_p2; iter++)
        cout << *iter << ' ';
    cout << "\n\n";

    cout << "vec size = " << vec.size() << endl;
    cout << "vec2 size = " << vec2.size() << endl;
    cout << "vec3 size = " << vec3.size() << "\n\n";

    vec3.insert(vec3.end(), -5);

    cout << "insert to vec3 what -5"
         << "\n\n";
    cout << "insert out test : " << endl;

    for (int i = 0; i < vec3.size(); i++)
        cout << vec3[i] << ' ';
    cout << "\n\n";

    //주의!!!!! 아래 부분은 적어도 5기가 이상의 여유 메모리가 있는 상태에서 실행할것을 권고함
    {
        Vector<unsigned char> vec_max(4294967295ULL, 5);
        cout << (int)vec_max.at(1ULL) << "\n\n";
        cout << (int)vec_max.at(10ULL) << "\n\n";
        cout << (int)vec_max.at(100ULL) << "\n\n";
        cout << (int)vec_max.at(1000ULL) << "\n\n";
        cout << (int)vec_max.at(10000ULL) << "\n\n";
        cout << (int)vec_max.at(100000ULL) << "\n\n";
        cout << (int)vec_max.at(1000000ULL) << "\n\n";
        cout << (int)vec_max.at(10000000ULL) << "\n\n";
        cout << (int)vec_max.at(100000000ULL) << "\n\n";
        cout << (int)vec_max.at(1000000000ULL) << "\n\n";
        cout << (int)vec_max.at(2000000000ULL) << "\n\n";
        cout << (int)vec_max.at(3000000000ULL) << "\n\n";
        cout << (int)vec_max.at(4294967294ULL) << "\n\n";

        cout << "\n\nvector max size : " << vec_max.max_size() << "\n\n";
    }
}