#include "QPianoCart.h"

PianoCartesiano::PianoCartesiano(QWidget *parent): QWidget(parent){

    cartesianPlane = new QCustomPlot(this);
    points = new QCPGraph(cartesianPlane->xAxis, cartesianPlane->yAxis);

    cartesianPlane->xAxis->setLabel("x");
    cartesianPlane->yAxis->setLabel("y");
    cartesianPlane->setFixedSize(400,400);

    cartesianPlane->xAxis->setRange(-31,31);
    cartesianPlane->yAxis->setRange(-31,31);
    cartesianPlane->xAxis2->setRange(-31,31);
    cartesianPlane->yAxis2->setRange(-31,31);

    points->setAdaptiveSampling(false);
    points->removeFromLegend();
    points->setLineStyle(QCPGraph::lsNone);
    points->setScatterStyle(QCPScatterStyle::ssDisc);
    points->setPen(QPen(QBrush(Qt::black),1));

}

bool PianoCartesiano::checkPointIn(int x,int y) const{
    bool sent = false;
    for(auto i = planePoints.begin(); !sent && i != planePoints.end() ; ++i){
        if((*i)->rx() == x && (*i)->ry() == y)
            sent = true;
    }
    return sent;
}
//POST: return true if there is a point with x and y value inside the graph

void PianoCartesiano::cartesianPlot() const{
    points->data()->clear();
    if(planePoints.size() != 0 ){
        for(auto i = planePoints.begin(); i != planePoints.end(); ++i){
            points->addData((*i)->rx(), (*i)->ry());
        }
    }    
    cartesianPlane->replot();
}
//POST: replot all of my points inside my cartesian plane

QList<PuntoCartesiano*> PianoCartesiano::getPointsPublic() const{
    return planePoints;
}
//POST: return all of my QPointF

void PianoCartesiano::setPlanDimension(int dimension){
    cartesianPlane->setFixedSize(dimension, dimension);
}
//POST: set the dimension of my cartesian plan

bool PianoCartesiano::addSinglePoint(int x,int y){
    if(checkPointIn(x,y)){
        return false;
    }
    else{
        planePoints.push_back(new PuntoCartesiano(x,y));
        cartesianPlot();
        return true;
    }
}
//POST: if there is no point(x,y) a new QPointF is pushed inside my planePoints list

int PianoCartesiano::getPlainPointsSize() const{
    return planePoints.size();
}
//POST: return the size of my PlainPoints list

void PianoCartesiano::deleteAllPoint(){
    planePoints.clear();
    points->data()->clear();
    cartesianPlane->replot();
}
//POST: delete all of my points and replot the plan

bool PianoCartesiano::deletePoint(int x, int y){
    for(auto i= planePoints.begin(); i != planePoints.end(); ++i){
        if((*i)->rx() == x && (*i)->ry() == y){
            delete *i;
            i = planePoints.erase(i);
            cartesianPlot();
            return true;
        }
    }
    return false;
}
//POST: if there is the function delete a point inside my graph

bool PianoCartesiano::drawFigure(const QList<PuntoCartesiano*> points){
    return false;
}

bool PianoCartesiano::delFigure(){
    return false;
}


