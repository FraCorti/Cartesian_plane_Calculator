#include "poligoni.h"

double poligono::pi = 3.14;

std::ostream& operator>>(std::ostream& os,QVector<punto>p){
    for(auto i=p.begin(); i != p.end(); ++i)
        os<<*i;
    return os;
}
