#include<iostream>
#include "poly.hpp"

using namespace std;

Polynomial::Polynomial() : start((term *)calloc(10, sizeof(term))), capacity(10) { end = start; }

Polynomial::~Polynomial() { free(start), start = nullptr, end = nullptr; }

bool Polynomial::isZero() { return (start == end) ? 1 : 0; }

double Polynomial::coef(int expon)
{
    term *tmp = end - 1;
    do
    {
        if(expon == (*tmp).expon)
            return (*tmp).coef;
    } while ((tmp--) - start);

    return 0.0;
}

int Polynomial::leadExp()
{
    term *tmp = end - 1;
    int exponTmp = 0;
    do
    {
        exponTmp = (exponTmp > (*tmp).expon) ? exponTmp : (*tmp).expon;
    } while ((tmp--) - start);

    return exponTmp;
}

void Polynomial::remove(int expon)
{
    term *tmp = end - 1;
    do
    {
        if (expon == (*tmp).expon)
        {
            end--;
            for (; tmp < end; tmp++)
            {
                (*tmp).coef = (*(tmp + 1)).coef;
                (*tmp).expon = (*(tmp + 1)).expon;
            }
            return;
        }
    } while ((tmp--) - start);

    cerr << "Does not exist expon : " << expon << endl;
    return;
}

void Polynomial::singleAdd(double coef, int expon)
{
    term *tmp = end - 1;
    do
    {
        if (expon == (*tmp).expon)
        {
            (*tmp).coef += coef;
            return;
        }
    } while ((tmp--) - start);

    if (end - start == capacity)
    {
        if (!(tmp = (term *)realloc(start, sizeof(term) * (capacity += 10))))
            cerr << "Memory allocation failure" << endl, exit(-1);
        if (start != tmp)
            end = tmp + (end - start), start = tmp;
    }

    (*end).coef = coef;
    (*end++).expon = expon;
}

void Polynomial::singleMult(double coef, int expon)
{
    term *tmp = end - 1;
    do
    {
        (*tmp).coef *= coef;
        (*tmp).expon += expon;
    } while ((tmp--) - start);
}

void Polynomial::add(Polynomial* Poly)
{
    term *tmp = (*Poly).end - 1;
    do
    {
        singleAdd((*tmp).coef, (*tmp).expon);
    } while ((tmp--) - (*Poly).start);
}

void Polynomial::mult(Polynomial *Poly)
{
    term *tmp = (*Poly).end - 1;
    do
    {
        singleMult((*tmp).coef, (*tmp).expon);
    } while ((tmp--) - (*Poly).start);
}