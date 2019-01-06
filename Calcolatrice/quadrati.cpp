#include "quadrati.h"


void quadrato::puntiLatoSinistro(punto& alto, punto& basso, QList<punto*> points){
    punto TmpAlto = *points.first();
    punto TmpBasso = *points.first();
    for(auto i = points.begin(); i != points.end(); ++i){
        if((*i)->get_ascisse() <= TmpAlto.get_ascisse() && (*i)->get_ordinate() >= TmpAlto.get_ordinate())
                TmpAlto=**i;  //punto alto sinistra
        if((*i)->get_ascisse() <= TmpBasso.get_ascisse() && (*i)->get_ordinate() <= TmpBasso.get_ordinate())
                TmpBasso=**i; //punto basso sinistra
    }
    alto=TmpAlto;
    basso=TmpBasso;
}
//POST: assegna i due punti appartenenti al lato sinistro del mio quadrato

void quadrato::puntiLatoDestro(punto& alto, punto& basso, QList<punto*> points){
    punto TmpAlto = *points.first();
    punto TmpBasso = *points.first();
    for(auto i = points.begin(); i != points.end(); ++i){
        if((*i)->get_ascisse() >= TmpAlto.get_ascisse() && (*i)->get_ordinate() >= TmpAlto.get_ordinate())
             TmpAlto=**i;  //punto alto destra

        if((*i)->get_ascisse() >= TmpBasso.get_ascisse() && (*i)->get_ordinate() <= TmpBasso.get_ordinate())
               TmpBasso=**i; //punto basso destra
    }
    alto=TmpAlto;
    basso=TmpBasso;
}
//POST:torno i punti del lato destro

//PRE:
void quadrato::puntiOpposti(punto& sx, punto& dx , QList<punto*> points){

    punto TmpSx = *points.first();
    punto TmpDx = *points.first();
    for(auto i = points.begin(); i != points.end(); ++i){
        if((*i)->get_ascisse() <= TmpSx.get_ascisse() && (*i)->get_ordinate() > TmpSx.get_ordinate())
                TmpSx=**i; //punto alto sinistra
        if((*i)->get_ascisse() > TmpDx.get_ascisse() && (*i)->get_ordinate() <= TmpDx.get_ordinate())
                TmpDx=**i; //punto basso a destra
    }
    sx=TmpSx;
    dx=TmpDx;
}
//POST: assegna punto in alto a sinistra e in basso a destra

double quadrato::perimetro() const{
    punto alto, basso;
    quadrato::puntiLatoSinistro(alto, basso, this->getPoints());
    double perimetro = punto::distanza(alto , basso) * 4;
    return perimetro;
}

quadrato::quadrato(const QList<punto*> punti){
    for(auto i = punti.begin(); i != punti.end(); ++i){
        q.push_back(*i);
    }
}

bool quadrato::controlloReg(const QList<punto*> points){
    punto altoSx,bassoSx;
    punto altoDx, bassoDx;
    quadrato::puntiLatoSinistro(altoSx,bassoSx, points);
    quadrato::puntiLatoDestro(altoDx,bassoDx,points);

    double latoSx = punto::distanza(altoSx,bassoSx);
    double latoDx = punto::distanza(altoDx,bassoDx);
    double latoSopra = punto::distanza(altoSx, altoDx);
    double latoSotto = punto::distanza(bassoSx,bassoDx);
    if(latoSx==latoDx && latoSx==latoSopra && latoSx==latoSotto){
        return true;
    }
    return false;
}

QList<punto*> quadrato::getPoints() const{
    return q;
}
//POST: torno punti del mio quadrato

double quadrato::area()const{
   punto alto, basso;
   quadrato::puntiLatoSinistro(alto, basso, this->getPoints());
   double dist =  pow(punto::distanza(alto, basso),2);
   return dist;
}
//POST: calcolo area

double quadrato::raggioCircCircoscritta()const{
    punto altoSx;
    punto bassoDx;
    quadrato::puntiOpposti(altoSx, bassoDx, getPoints());
    double raggio = punto::distanza(altoSx, bassoDx) * 1.41;  //diventa 0
    return raggio;
}
//POST: calcola raggio circ circoscritta

double quadrato::raggioCircInscritta()const{
    punto alto, basso;
    quadrato::puntiLatoSinistro(alto, basso, getPoints());
    double raggio = punto::distanza(alto,basso)/2;
    return raggio;
}
//POST: calcolo raggio Circ inscritta

double quadrato::areaCircInscritta()const{
   double ACI = pow(this->raggioCircInscritta(),2) *poligono::pi;
   return ACI;
}
//POST: calcolo area Circ inscritta

double quadrato::areaCircCircoscritta()const{
    double ACC = pow(this->raggioCircCircoscritta(),2) * poligono::pi;
    return ACC;
}
//POST: calcolo area Circ Circoscritta
