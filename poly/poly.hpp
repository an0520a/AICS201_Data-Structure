#ifndef POLY_H
#define POLY_H

#include <iostream>

typedef struct _term
{
    double coef;
    int expon;
} term;

class Polynomial
{
public:
    Polynomial();
    ~Polynomial();
    bool isZero();
    double coef(int expon);
    int leadExp();
    void remove(int expon);
    void singleAdd(double coef, int expon);
    void singleMult(double coef, int expon);
    void add(Polynomial *poly);
    void mult(Polynomial *poly);

private:
    term *start;
    term *end;
    int capacity;
};

#endif