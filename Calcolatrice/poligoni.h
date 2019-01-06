#ifndef POLIGONI_H
#define POLIGONI_H

#include <iostream>
#include "puntoz.h"
#include <math.h>
#include <vector>
#include <array>


class poligono: public punto{
public:
    static double pi;
    virtual ~poligono() = default;
    virtual double perimetro() const = 0;
    virtual double area() const =0;
    virtual double raggioCircInscritta() const =0;
    virtual double raggioCircCircoscritta() const =0 ;
    virtual double areaCircInscritta() const =0;
    virtual double areaCircCircoscritta() const =0;
};
#endif // POLIGONI_H
