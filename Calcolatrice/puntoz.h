#ifndef COMPLEX_H
#define COMPLEX_H
#include <cstdlib>
#include <iostream>
#include <istream>
#include <math.h>
#include "frazioni.h"

class punto:public razionale{
    friend std::istream& operator>>(std::istream&,punto&);
    friend std::ostream& operator<<(std::ostream&,const punto&);
private:
    razionale x,y;
public:
    punto();
    punto(razionale,razionale);
    punto(int, int);
    bool operator ==(const punto &);
    razionale get_ascisse() const;
    razionale get_ordinate() const;
    punto operator +(const punto&) const;
    void stampa() const;
    punto& operator=(const punto&);
    static double distanza(const punto&,const punto&);
    static double distanza(const punto*&, const punto*&);
    static punto mediana(const punto&, const punto&);
};

#endif // COMPLEX_H



