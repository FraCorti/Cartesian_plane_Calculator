#ifndef CALCOLATRICE_H
#define CALCOLATRICE_H

#include <QWidget>
#include <QMyDisplay.h>

class QMainCalc : public QMainWindow{
    Q_OBJECT

private:
    QWidget* widget;    
    MyInputPointDisplay* display;
    QGridLayout* grid;

public:
    QMainCalc();

public slots:

    void Eappartenenza();
    void EdistanzaPuntoRetta();
    void EequParallela();
    void EequPerpendicolare();
    void EcondParallelismo();
    void EcondPerpendicolare();
    void EincontroRette();
    void PArea();
    void PPerimetro();
    void PRaggioCircInscritta();
    void PRaggioCircCircoscritta();
    void PAreaCircInscritta();
    void PAreaCircCircoscritta();
    void genericalDraw();
    void genericalCancel();
};

#endif // CALCOLATRICE_H
