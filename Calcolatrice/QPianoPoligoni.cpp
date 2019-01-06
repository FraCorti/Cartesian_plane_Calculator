#include "QPianoPoligoni.h"

QPoligonsPlane::QPoligonsPlane(QWidget*p): PianoCartesiano(p){

   figurePresence = false;
   figure = nullptr;
   first = nullptr;
   second = nullptr;
   third = nullptr;

}

bool QPoligonsPlane::drawFigure(const QList<PuntoCartesiano*> points){

    if(points.size() == 3 && first == nullptr && second == nullptr && third == nullptr){
        QVector<PuntoCartesiano*> tmp = points.toVector();

        first = new QCPItemLine(cartesianPlane);
        first->setHead(QCPLineEnding::esNone);
        first->setPen(QPen(QBrush(Qt::black),1));
        first->start->setCoords(tmp[0]->rx(), tmp[0]->ry());
        first->end->setCoords(tmp[1]->rx(), tmp[1]->ry());

        second = new QCPItemLine(cartesianPlane);
        second->setHead(QCPLineEnding::esNone);
        second->setPen(QPen(QBrush(Qt::black),1));
        second->start->setCoords(tmp[1]->rx(), tmp[1]->ry());
        second->end->setCoords(tmp[2]->rx(), tmp[2]->ry());

        third = new QCPItemLine(cartesianPlane);
        third->setHead(QCPLineEnding::esNone);
        third->setPen(QPen(QBrush(Qt::black),1));
        third->start->setCoords(tmp[2]->rx(), tmp[2]->ry());
        third->end->setCoords(tmp[0]->rx(), tmp[0]->ry());

        cartesianPlane->replot();
        figurePresence = true;

        return true;
    }
    if(points.size() == 4  && figurePresence == false){

        QList<QPointF*> tmp;
        for(auto i = points.begin(); i != points.end(); ++i){
            tmp.push_back(new QPointF((*i)->rx(), (*i)->ry()));
        }
        QPointF altoSinistra;
        QPointF bassoDestra;
        for(auto i = tmp.begin(); i != tmp.end(); ++i){
            if((*i)->rx() <= altoSinistra.rx() && (*i)->ry() > altoSinistra.ry())
                altoSinistra = **i;  //punto alto sinistra

            if((*i)->rx() > bassoDestra.rx() && (*i)->ry() <= bassoDestra.ry())
                bassoDestra = **i; //punto basso destra
        }

        figure = new QCPItemRect(cartesianPlane);
        figure->setPen(QPen(QBrush(Qt::black),1));
        figure->topLeft->setCoords(altoSinistra.rx(), altoSinistra.ry());
        figure->bottomRight->setCoords(bassoDestra.rx(), bassoDestra.ry());
        figurePresence = true;
        tmp.clear();
        cartesianPlane->replot();
        return true;
    }
    return false;
}

bool QPoligonsPlane::delFigure(){
    bool sent = false;
    if(figure != nullptr){
        sent = cartesianPlane->removeItem(figure);
        figurePresence = false;
    }
    if(first != nullptr && second != nullptr && third != nullptr){
        sent = cartesianPlane->removeItem(first);
        first = nullptr;
        cartesianPlane->removeItem(second);
        second = nullptr;
        cartesianPlane->removeItem(third);
        third = nullptr;
        figurePresence = false;
    }
    if(sent){
         cartesianPlane->replot();
    }
    return sent;
}
