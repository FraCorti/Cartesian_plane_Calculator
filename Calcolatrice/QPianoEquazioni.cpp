#include "QPianoEquazioni.h"

bool checkPresenzaretta(const PuntoCartesiano& primo, const PuntoCartesiano& secondo, const QList<PuntoCartesiano*> puntiPresenti){
    bool primoControllo = false;
    bool secondoControllo = false;

    for(auto i = puntiPresenti.begin(); i != puntiPresenti.end(); ++i){
        if(primo.rx()==(*i)->rx() && primo.ry() == (*i)->ry())
            primoControllo = true;
        if(secondo.rx()==(*i)->rx() && secondo.ry() == (*i)->ry())
            secondoControllo = true;
    }
    if(primoControllo == true && secondoControllo == true)
        return true;

    return false;
}

QEquationPlane::QEquationPlane(QWidget *p): PianoCartesiano(p){
    firstStraightLine = nullptr;
    secondStraightLine = nullptr;
    numeroRette = 0;
    distanceLine = 0;
    presenzaPunti = false;

    greenPoints = new QCPGraph(cartesianPlane->xAxis, cartesianPlane->yAxis);
    greenPoints->setAdaptiveSampling(false);
    greenPoints->removeFromLegend();
    greenPoints->setLineStyle(QCPGraph::lsNone);
    greenPoints->setScatterStyle(QCPScatterStyle::ssDisc);
    greenPoints->setPen(QPen(QBrush(Qt::darkGreen),1));

    redPoints = new QCPGraph(cartesianPlane->xAxis, cartesianPlane->yAxis);
    redPoints->setAdaptiveSampling(false);
    redPoints->removeFromLegend();
    redPoints->setLineStyle(QCPGraph::lsNone);
    redPoints->setScatterStyle(QCPScatterStyle::ssDisc);
    redPoints->setPen(QPen(QBrush(Qt::darkRed),1));

}

bool QEquationPlane::eliminaPuntiAppartenza(){
    if(presenzaPunti == true){
       redPoints->data()->clear();
       greenPoints->data()->clear();
       presenzaPunti = false;
       cartesianPlane->replot();
       return true;
    }
    return false;
}

bool QEquationPlane::drawAppartenenzaPunto(const bool appartenenza, const PuntoCartesiano* point){
    if(appartenenza == false)         //il punto non appartiene alla retta
          redPoints->addData(point->rx(), point->ry());
    if(appartenenza == true)          //il punto appartiene alla retta
         greenPoints->addData(point->rx(), point->ry());
    presenzaPunti = true;
    cartesianPlane->replot();
    return true;
}

/*void QEquationPlane::drawDistanceLine(const PuntoCartesiano*begin, const PuntoCartesiano* theEnd){
    if(distanceLine != 0){
         cartesianPlane->removeItem(distanceLine);
    }

    distanceLine = new QCPItemLine(cartesianPlane);
    distanceLine->start->setCoords(*begin);
    distanceLine->end->setCoords(*theEnd);
    distanceLine->setPen(QPen(QBrush(Qt::red),1));
    distanceLine->setHead(QCPLineEnding::esNone);
    distanceLine->setTail(QCPLineEnding::esNone);
    cartesianPlane->replot();
}*/

bool QEquationPlane::drawFigure(const QList<PuntoCartesiano*> points){
    if(points.size() == 2){

        if(firstStraightLine == 0){
            numeroRette++;
            firstStraightLine = new QCPItemStraightLine(cartesianPlane);
            QVector<PuntoCartesiano*> tmp = points.toVector();
            firstStraightLine->setPen(QPen(QBrush(Qt::black),1));
            firstStraightLine->point1->setCoords( tmp[0]->rx(), tmp[0]->ry());  //create the line
            firstStraightLine->point2->setCoords(tmp[1]->rx(), tmp[1]->ry());
            puntiPrimaRetta = points;
            cartesianPlane->replot();
            return true;
        }
        if(checkPresenzaretta(*points.first(), *points.last(),puntiPrimaRetta) == true)
            return false;  //retta con gli stessi valori

        if(secondStraightLine == 0){
            numeroRette++;
            secondStraightLine = new QCPItemStraightLine(cartesianPlane);
            QVector<PuntoCartesiano*> tmp = points.toVector();
            secondStraightLine->setPen(QPen(QBrush(Qt::black),1));
            secondStraightLine->point1->setCoords( tmp[0]->rx(), tmp[0]->ry());
            secondStraightLine->point2->setCoords(tmp[1]->rx(), tmp[1]->ry());
            cartesianPlane->replot();
            return true;
        }
    }
    return false;
}

bool QEquationPlane::delFigure(){

    bool sent = false;
    if(firstStraightLine != nullptr){
        numeroRette--;
        cartesianPlane->removeItem(firstStraightLine);
        firstStraightLine = nullptr;
        sent = true;
        puntiPrimaRetta.clear();
        cartesianPlane->replot();
    }
    if(secondStraightLine != nullptr){
        numeroRette--;
        cartesianPlane->removeItem(secondStraightLine);
        secondStraightLine = nullptr;
        sent = true;
        cartesianPlane->replot();
    }
    return sent;
}
//POST:
