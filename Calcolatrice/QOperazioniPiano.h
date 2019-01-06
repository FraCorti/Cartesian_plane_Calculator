#ifndef QOPERAZIONINELPIANO_H
#define QOPERAZIONINELPIANO_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include "QPianoCart.h"
#include "puntoz.h"



class planeOperation: public QWidget{
    Q_OBJECT

public:

    planeOperation(QWidget*q): QWidget(q){}

    virtual void setDisplayText(QString text) const =0;

    virtual ~planeOperation() =default;

    virtual void drawFigure(QList<PuntoCartesiano*> points) =0;

    virtual int getNumeroFigure() const =0;

    virtual void deleteFigures() =0;

};

#endif // QOPERAZIONINELPIANO_H
