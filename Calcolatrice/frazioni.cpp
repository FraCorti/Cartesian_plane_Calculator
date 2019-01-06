#include "frazioni.h"

razionale::razionale(): num(0){}

razionale::razionale(int n): num(n), den(1){}

//razionale::razionale(const razionale& raz): num(raz.num), den(raz.den){}

razionale::razionale(int n=0, int d=1): num(n), den(d) {
    if(den==0){
       num = 0;
    }
    else{
        if(num!=0){
            int i=mcd(n,d);
            if(i!=1){
                num=num/i;
                den=den/i;
            }
            if(n<0 && d<0){
                num *= -1;
                den *= -1;
            }
        }
    }
}

bool razionale::operator==(const int numero) const{
    if(den == 1){
        if(num == numero)
            return true;
        else
            return false;
    }
    else
        return numero*den==num;
}

int razionale::mcd(int a,int b) const{
   int c = fabs(a);     //fabs == valore assoluto
   int d = fabs(b);
   while (c!=d){
       if(c>d){
          c = c-d;
       }
       else{
          d = d-c;
       }
   }
   return c;
}

int razionale::getNum() const{
    return num;
}

int razionale::getDen() const{
    return den;
}

bool razionale::operator==(const razionale& t) const{
    if(num*t.den==t.num*den){
        return true;
    }
    else{
        return false;
    }
}

razionale razionale::reduce() const{
    if(num != 0){
       return razionale(num,den);
    }
    else{
        return razionale(0,1);
    }
}

double razionale::conversione(const razionale&t){
    double num = t.getNum();
    double den = t.getDen();
    if(den !=0){
        double conv = num/den;
        return conv;
    }
    else{
        return 0;
    }
}

razionale razionale::operator++(int){
    razionale x(*this);
    num+=den;
    return x;
}

razionale razionale::operator++(){
    num+=den;
    return *this;
}

bool razionale::operator<(const razionale& secondo){
    if(razionale::conversione(*this) < razionale::conversione(secondo))
        return true;
    else
        return false;
}
//POST: se primo < secondo true se no false

bool razionale::operator<=(const razionale& secondo){
    if(razionale::conversione(*this) <= razionale::conversione(secondo))
        return true;
    else
        return false;
}
//POST: se primo <= secondo true se no false

bool razionale::operator>=(const razionale& secondo){
    if(razionale::conversione(*this) >= razionale::conversione(secondo))
        return true;
    else
        return false;
}
//POST: se primo >= secondo true se no false

bool razionale::operator>(const razionale& secondo){
    if(razionale::conversione(*this) > razionale::conversione(secondo))
        return true;
    else
        return false;
}
//POST: se primo > secondo true se no false

razionale& razionale::operator=(const razionale& genericalFraction){
    if(this != & genericalFraction){
        num = genericalFraction.num;
        den = genericalFraction.den;
    }
    return *this;
}
//POST: copio elemento

razionale razionale::operator*(const int numero) const{
    return razionale(num*numero,den*numero);
}

razionale razionale::operator*(const razionale&t) const{
   return razionale(num*t.num,den*t.den);
}

razionale razionale::operator+(const razionale&t) const{
  return razionale(num*t.den+den*t.num,t.den*den);
}

razionale razionale::operator/(const razionale&t) const{
   return razionale(num*t.den,den*t.num);
}

razionale razionale::operator-(const razionale&t) const{
   int numerator = num*t.den - den * t.num;
   return razionale(numerator , den * t.den);
}

//controllare
razionale razionale::operator*=(const razionale&m){
   return razionale(num*m.num,den*m.den);
}

razionale razionale::operator^(const int n){
    if(n == 0){
        return razionale(1,1);
    }
    else{
       if(n>0){
        num  = static_cast<int>(pow(num,n));
        den = static_cast<int>(pow (den, n ));
        return *this;
       }
       if(n<0){
          num=pow(num,n);
          den=pow(den,n);
         *this=this->inverso();
         return *this;
       }
    }
}

razionale razionale::inverso() const{
    return razionale(den,num);
}

std::ostream& operator <<(std::ostream& os,const razionale&t){
    if(t.den==1){             //ho solo numeratore della frazione
        os<<t.num;
        return os;
    }
    if((t.num || t.den)<0){
        os<<"-";
    }
    os<<t.num<<"/"<<t.den;
    return os;
}

//da rivedere per l'input, aggiungere eccezioni
std::istream& operator >>(std::istream& in,razionale&t){
    std::cout<<"Inserire numeratore"<<std::endl;
    in>>t.num;
    if(t.num==0){  //eccezione
        std::cout<<"NULL RATIONAL"<<std::endl;
        return in;
    }
    std::cout<<"Inserire denominatore"<<std::endl;
    in>>t.den;
    if(t.den==0){ //eccezione
        std::cout<<"ERROR"<<std::endl;
        t.den=1;
    }
    int i=t.mcd(t.num,t.den);
    if(i!=1){
        t.num=t.num/i;
        t.den=t.den/i;
    }
    return in;
}
