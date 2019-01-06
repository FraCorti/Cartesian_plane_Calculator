#ifndef QPIANOPOLIGONI_H
#define QPIANOPOLIGONI_H

#include "QPianoCart.h"
#include "poligoni.h"
#include "triangoli.h"
#include "quadrati.h"

class QPoligonsPlane: public PianoCartesiano{
    Q_OBJECT

private:

    bool figurePresence;
    QCPItemRect* figure;
    QCPItemLine* first;
    QCPItemLine* second;
    QCPItemLine* third;

public:

    QPoligonsPlane(QWidget* = 0);
    poligono* getPoligono() const;
    virtual bool drawFigure(const QList<PuntoCartesiano*> points);
    virtual bool delFigure();
};

#endif // QPIANOPOLIGONI_H
