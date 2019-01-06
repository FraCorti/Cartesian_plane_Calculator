#include "puntoz.h"

punto::punto(): x(), y(){}

punto::punto(razionale x1=0, razionale y1=0): x(x1), y(y1) {}

punto::punto(int x1 = 0, int y1 = 0): x(x1), y(y1){}

bool punto::operator==(const punto&p){
   if((x == p.x) && ( y == p.x))
        return true;
   else
       return false;
}

punto& punto::operator=(const punto& genericPoint){
    if(this != &genericPoint){
        x = genericPoint.x;  //std::move(genericPoint.x)
        y = genericPoint.y;  //std::move(genericPoint.y);
    }
    return *this;
}

razionale punto::get_ascisse() const{
    return x;
}

razionale punto::get_ordinate() const{
    return y;
}

punto punto::operator+(const punto&t) const{
    return punto(t.x + x,t.y + y);
}

double punto::distanza(const punto& primo, const punto& secondo){
    punto conto(secondo.x-primo.x, secondo.y-primo.y);  // x2 - x1 ee y2 - y1
    double contoX = razionale::conversione(conto.x);
    double contoY = razionale::conversione(conto.y);
    double dist = sqrt(pow(contoX,2) + pow(contoY,2));
    return dist;
}



punto punto::mediana(const punto& primo,const punto& secondo){
     return punto((secondo.x + primo.x)/2,(secondo.y + primo.y)/2);
}

void punto::stampa() const{
    std::cout<<"("<<x<<";"<<y<<")";
}

std::ostream& operator<<(std::ostream&os,const punto&t){
    t.stampa();
    return os;
}
