#ifndef TRIANGOLI_H
#define TRIANGOLI_H
#include <poligoni.h>
#include <iostream>
#include <QVector>
#include <QArrayData>

class triangolo: public poligono{

private:
    QList<punto*> k;
public:
    triangolo(const QList<punto*>);
    virtual double area() const;
    virtual double  perimetro() const;
    virtual double  raggioCircInscritta() const;
    virtual double  raggioCircCircoscritta() const;
    virtual double  areaCircInscritta() const;
    virtual double  areaCircCircoscritta() const;
};
#endif // TRIANGOLI_H
