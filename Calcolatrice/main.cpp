#include <iostream>
#include <QApplication>
#include "QMainCalc.h"



int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    QMainCalc calc;
    calc.show();
    return a.exec();
    return 0;
}

