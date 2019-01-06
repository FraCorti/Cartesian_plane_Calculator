#ifndef FRAZIONI_H
#define FRAZIONI_H

#include <iostream>
#include <fstream>
#include <math.h>
#include <QVector>


class razionale{
    friend std::ostream& operator<<(std::ostream&,const razionale&);
    friend std::istream& operator>>(std::istream&,razionale&);
private:
    int num, den;
public: 
    razionale();
    razionale(int);
    razionale(int,int);
    int getNum() const;
    int getDen() const;
    int mcd(int,int) const;
    razionale reduce() const;   //minimo comune multiplo
    razionale inverso() const;
    void stampa_razionale() const;
    bool operator==(const razionale&) const ;
    bool operator==(const int) const;
    razionale operator+(const razionale&) const;
    razionale operator*(const razionale&) const;
    razionale operator/(const razionale&) const;
    razionale operator-(const razionale&) const;
    razionale operator++(int);
    razionale operator++();
    razionale operator*=(const razionale&);
    razionale operator*(int ) const;
    razionale operator^(const int);
    razionale& operator=(const razionale&);
    bool operator <(const razionale&);
    bool operator <=(const razionale&);
    bool operator >=(const razionale&);
    bool operator >(const razionale&);

    static double conversione(const razionale&);
};

#endif // FRAZIONI_H
