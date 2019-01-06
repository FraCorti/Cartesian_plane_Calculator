#ifndef QPIANOEQUAZIONI_H
#define QPIANOEQUAZIONI_H

#include "QPianoCart.h"

class QEquationPlane: public PianoCartesiano{
    Q_OBJECT

private:

    QCPItemStraightLine* firstStraightLine;

    QList<PuntoCartesiano*> puntiPrimaRetta;

    QCPItemStraightLine* secondStraightLine;

    QCPItemLine* distanceLine;

    bool presenzaPunti;

    QCPGraph* greenPoints;

    QCPGraph* redPoints;

    int numeroRette;

public:

    QEquationPlane(QWidget* = 0);

    bool drawAppartenenzaPunto(const bool presenza,const PuntoCartesiano*);

    //void drawDistanceLine(const PuntoCartesiano*,const PuntoCartesiano*);

    bool eliminaPuntiAppartenza();

    virtual bool drawFigure(const QList<PuntoCartesiano*>);

    virtual bool delFigure();

};

#endif // QPIANOEQUAZIONI_H
