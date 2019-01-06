#ifndef QMYDISPLAY_H
#define QMYDISPLAY_H

#include "QPianoCart.h"
#include "QOperazioniPiano.h"

class MyInputPointDisplay: public planeOperation{
    Q_OBJECT

private:
    PianoCartesiano* cartesianPlane;

    QGridLayout* grid;  //my Main grid

    QLineEdit* display;

    QLineEdit* inputAxisX;

    QLineEdit* inputAxisY;

    QLineEdit* stringPlainPoints;

    bool checkInputNumber(QLineEdit*& x1, QLineEdit*& y1, int& numberX, int& numberY) const;

    void setPointText() const;

private slots:

    void addPointClicked();
    void clearClicked();
    void clearAllClicked();

public:
    MyInputPointDisplay(QWidget* =0);

    void delateAllUsedFiguresPoints();

    QList<PuntoCartesiano*> getPlanePoints() const;

    virtual void deleteFigures();

    virtual void setDisplayText(QString text) const;

    virtual void drawFigure(QList<PuntoCartesiano*> points);

    virtual int getNumeroFigure() const;
};


#endif // QMYDISPLAY_H
