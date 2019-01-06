#ifndef QEQUAZIONE_H
#define QEQUAZIONE_H

#include "QOperazioniPiano.h"
#include "QPianoCart.h"
#include "QPianoEquazioni.h"
#include "equazione.h"

class QEquation: public planeOperation{
    Q_OBJECT

private:
    QEquationPlane* cartesianPlane;
    QGridLayout* grid;
    QLineEdit* generalOutPutDisplay;
    int numeroFigure;
    equazione* primaEquazione;
    equazione* secondaEquazione;

public:

    QEquation(QWidget* =0);
    bool drawAppartPunto(const PuntoCartesiano*, bool presenza);
    equazione* getPrimaEquazione() const;
    equazione* getSecondaEquazione() const;
    void delateOperationPoints();
    void displayEquation(const equazione&, const QString&) const;
    virtual int getNumeroFigure() const;
    virtual void deleteFigures();
    virtual void setDisplayText(QString text) const;
    virtual void drawFigure(QList<PuntoCartesiano*> points);

public slots:
    void eliminaPuntiAppartenenza();

};


#endif // QEQUAZIONE_H
