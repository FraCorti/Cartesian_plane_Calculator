#ifndef QUADRATI_H
#define QUADRATI_H

#include "poligoni.h"
#include <iostream>
#include <math.h>


class quadrato: public poligono{
private:  
    QList<punto*> q;

public:   
    quadrato(const QList<punto*>);
    virtual double perimetro() const;
    virtual double area() const;
    virtual double raggioCircInscritta() const;
    virtual double raggioCircCircoscritta() const;
    virtual double areaCircInscritta() const;
    virtual double areaCircCircoscritta() const;
    static void puntiOpposti(punto&, punto&, QList<punto*>);
    static void puntiLatoSinistro(punto&,punto&,QList<punto*>);
    static void puntiLatoDestro(punto&,punto&,QList<punto*>);
    static bool controlloReg(const QList<punto*>);
    QList<punto*> getPoints() const;
};
#endif // QUADRATI_H
