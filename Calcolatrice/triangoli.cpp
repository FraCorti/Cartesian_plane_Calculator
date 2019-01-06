#include "triangoli.h"


triangolo::triangolo(const QList<punto*>punti){
    for(auto i=punti.begin(); i != punti.end() ; ++i){
        k.push_back(*i);
    }
}

double triangolo::perimetro() const{
    QVector<punto*>t = k.toVector();
    double a = punto::distanza(*t[0],*t[1]);
    double b = punto::distanza(*t[1],*t[2]);
    double c = punto::distanza(*t[0],*t[2]);
    double perimetro =  a+b+c;
    return perimetro;
}

double triangolo::area() const{
    QVector<punto*> t = k.toVector();
    double semiPer = this->perimetro()/2;
    double a = punto::distanza(*t[0],*t[1]);
    double b = punto::distanza(*t[1],*t[2]);
    double c = punto::distanza(*t[0],*t[2]);
    double areaSenzaRadice = semiPer*(semiPer-a)*(semiPer-b)*(semiPer-c);
    return sqrt(areaSenzaRadice);
}

double triangolo::raggioCircInscritta() const{
    return (this->area()/(this->perimetro()/2));
}

double triangolo::raggioCircCircoscritta() const    {
    QVector<punto*> t = k.toVector();
    double a = punto::distanza(*t[0],*t[1]);
    double b = punto::distanza(*t[1],*t[2]);
    double c = punto::distanza(*t[0],*t[2]);
    double raggioCirc = (a*b*c) / (this->area()*4);
    return raggioCirc;
}

double triangolo::areaCircInscritta() const{
   return pow(this->raggioCircInscritta(),2) * poligono::pi;
}

double triangolo::areaCircCircoscritta() const{
   double raggio = this->raggioCircCircoscritta();
   double area = pow(raggio,2) * poligono::pi;
   return area;
}
