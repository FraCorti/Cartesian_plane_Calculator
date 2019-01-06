#ifndef EQUAZIONE_1_H
#define EQUAZIONE_1_H

#include <iostream>
#include "puntoz.h"
#include <math.h>
#include "frazioni.h"

class equazione:public punto{
    friend std::istream& operator>>(std::istream&,const equazione&);
    friend std::ostream& operator<<(std::ostream&,const equazione&);
private:
    razionale y,x,q;
public:
    equazione(const razionale&,const razionale&);
    equazione(const razionale&,const razionale&,const razionale&);
    static equazione* punti(const punto*,const punto*);
    razionale getY() const;
    razionale getX() const;
    razionale getQ() const;
    equazione esplicita() const;
    bool appartenenza(const punto&) const;
    static punto* incontro(const equazione&, const equazione&);
    static double distanza(const equazione*,const punto&);
    static equazione* perpendicolare(const equazione&, const punto&);
    static equazione* parallela(const equazione&,const punto&); 
    static bool condParallelismo(const equazione&,const equazione&);
    static bool condPerpendicolari(const equazione&,const equazione&);
    static void stampa(const equazione&,std::ostream&);
};
#endif // EQUAZIONE_1_H
