#ifndef QPOLIGONS_H
#define QPOLIGONS_H


#include "QOperazioniPiano.h"
#include "QPianoPoligoni.h"
#include "QPianoCart.h"

class Poligons: public planeOperation{
    Q_OBJECT

private:

    QPoligonsPlane* cartesianPlane;
    QGridLayout* grid;
    QLineEdit* generalDisplay;
    int numeroFigure;
    poligono* poligonoPiano;

public:
    virtual void setDisplayText(QString text) const;
    virtual void drawFigure(QList<PuntoCartesiano*> points);
    virtual void deleteFigures();
    virtual int getNumeroFigure() const;
    poligono* getFiguraPiano() const;
    Poligons(QWidget* p=0);
};

#endif // QPOLIGONS_H
