#include "equazione.h"

equazione::equazione(const razionale&t =0,const razionale&z =0): y(1), x(t), q(z){}

equazione::equazione(const razionale&y1 =0,const razionale&x1 =0,const razionale&z1 =0): y(y1), x(x1), q(z1) {}

razionale equazione::getY() const{
    return y;
}

razionale equazione::getX() const{
    return x;
}

razionale equazione::getQ() const{
    return q;
}

equazione* equazione::punti(const punto* primo, const punto* secondo){
    if(primo == secondo){  //punti uguali
        return nullptr;
    }
    if(primo->get_ascisse() == secondo->get_ascisse()){
       return new equazione(0,1,primo->get_ascisse());
    }
    if(primo->get_ordinate() == secondo->get_ordinate()){
       return new equazione(1,0,primo->get_ordinate());
    }
    else{
        //razionale mEqu=((primo.gety()-secondo.gety() )/(primo.getx()-secondo.getx()));  // calcolo m
        //razionale qEqu= primo.gety() - (m_tmp*primo.getx());  //calcolo q
        return new equazione(1,(primo->get_ordinate()-secondo->get_ordinate())/(primo->get_ascisse()-secondo->get_ascisse()),primo->get_ordinate()-((primo->get_ordinate()-secondo->get_ordinate())/(primo->get_ascisse()-secondo->get_ascisse())*primo->get_ascisse()));
    }
}

equazione equazione::esplicita() const{
    if(y.getNum() == 0){
        razionale coeff = x.inverso();
        return equazione(0,1,q*coeff);
    }
    if(x.getNum() == 0){
        razionale coeff = y.inverso();
        return equazione(1, 0, q*coeff);
    }    
    razionale coeff = y.inverso();
    return equazione(y, x*coeff, q*coeff);
}

bool equazione::appartenenza(const punto&p) const{
    if(getY().getNum() == 0){ //caso x = q
        if(x*p.get_ascisse() == q)
            return true;
        else
            return false;
    }
    if(getX().getNum() == 0){  //caso y = q
        if(y*p.get_ordinate() == q)
            return true;
        else
            return false;
    }
    razionale y1= p.get_ordinate()*y;
    razionale x1 = x *p.get_ascisse()+q;
    if(x1==y1){
        return true;
    }
    else{
        return false;
    }
}
//POST: true sse punto appartiene alla retta

punto* equazione::incontro(const equazione&t, const equazione&m){
    if(t.x == m.x){
        return nullptr;
    }
    else{       
        if(t.y == 0 && m.x == 0){
            return new punto(t.q,m.q);
        }
        if(t.x == 0 && m.y ==0){
            return new punto(m.q, t.q);
        }
        if(t.q == 0 && m.q == 0 ){
            return new punto(0,0);
        }
        if(t.q ==0 || m.q ==0)
            if(t.q == 0 ){
                razionale x = m.q/(t.x - m.x);
                razionale y = t.x * x;
                return new punto(x,y);
            }
            if(m.q ==0){
               razionale x = t.q/ (t.y-m.x);
               razionale y = m.x* x;
               return new punto(x,y);
            }
        }
        if(t.y == 0 || t.x == 0){
            if(t.y == 0)
                return new punto(t.q, t.q*m.x + m.q);

            if(t.x == 0)
                return new punto(t.y/m.x-m.q/t.x,t.q);
        }
        if(m.y == 0 || m.x == 0){
            if(m.y == 0)
                return new punto(m.q, m.q*t.x + t.q);
            if(m.x == 0 )
                return new punto(m.x/t.x - t.q/t.x, m.q);
        }
        razionale x((m.x-t.x)*(t.q-m.q));  //calcolo coordinate x
        //razionale y((m1.x*x)+m1.q);  //calcolo coordinate y
        return new punto(x,(m.x*x)+m.q);
}


double equazione::distanza(const equazione* e, const punto& p){
        equazione eEsplicita = e->esplicita();
        double numeratoreSenzaModulo = razionale::conversione(p.get_ordinate()-(eEsplicita.getX()*p.get_ascisse()+eEsplicita.getQ()));
        razionale EPow = eEsplicita.getX()^2;
        razionale uno(1,1);
        double denominatore = razionale::conversione(uno+EPow);
        double distanza = fabs(numeratoreSenzaModulo) / sqrt(denominatore);
        return distanza;
}
//POST: torna distanza punto dalla retta sse punto non appartiene alla retta

equazione* equazione::perpendicolare(const equazione&e, const punto&p){
    if(e.y == 0)
        return new equazione(1, 0, p.get_ordinate());
    if(e.x == 0)
        return new equazione(0, 1, p.get_ascisse());
    else
        return new equazione(e.y,razionale(-1)*(e.x.inverso()),razionale(-1)*(e.x.inverso())*(p.get_ascisse()+p.get_ordinate()));
}
    

equazione* equazione::parallela(const equazione& e, const punto& p){
    razionale segno(-1,1);
    if(e.x == 0)
        return new equazione(1, 0 , p.get_ordinate());
    if(e.y == 0)
        return new equazione(0, 1 , p.get_ascisse());
    else
        return new equazione(e.y, e.x, segno*e.x * p.get_ascisse() + p.get_ordinate());
}

bool equazione::condParallelismo(const equazione&a, const equazione&b){
    if((a.x==0 && b.x==0) || (a.y==0 && b.y==0))
        return true;
    if((a.y==0 && b.x==0) || (a.x==0 && b.y==0))
        return false;
    if(a.y == b.y && a.x == b.x)
        return true;
    return a.x*b.x ==1;
}
//POST: torna true sse rette sono parallele

bool equazione::condPerpendicolari(const equazione&a,const equazione&b){
    if((a.x==0 && b.x==0) || (a.y==0 && b.y==0))
        return false;
    if((a.y==0 && b.x== 0) || (a.x==0 && b.y==0))
        return true;
    if(a.y == b.y && a.x == b.x)
        return false;
    return a.x*b.x == -1;
}
//POST: torna true sse rette sono perpendicolari

void equazione::stampa(const equazione &e, std::ostream &os){
   if(e.y.getNum() == 0){
      razionale tmp= e.x.razionale::inverso();
      os<<"x=";
      razionale q1 = e.q*tmp;
      std::cout<<q1;
      return;
   }
   if(e.x.getNum()==0){
      razionale tmp= e.y.razionale::inverso();
      os<<"y=";
      razionale q1 = e.q*tmp;
      std::cout<<q1;
      return;
   }
   equazione tmp = e.esplicita();
   os<<"y=";
   if(razionale::conversione(tmp.x)!=1){
       std::cout<<tmp.x;
   }
   os<<"x";
   if(razionale::conversione(tmp.q)>0){
       os<<"+";
   }
   if(tmp.q.getNum() !=0){
      std::cout<<tmp.q;
   }
   std::cout<<std::endl;
}

std::ostream& operator <<(std::ostream& os,const equazione&e){
   e.stampa(e,os);
   return os;
}
