#include <QMainCalc.h>

#include <QPoligoni.h>
#include <QEquazione.h>
#include "poligoni.h"
#include "puntoz.h"
#include "triangoli.h"
#include "quadrati.h"
#include "equazione.h"

QList<punto*> conversionPoints(const QList<PuntoCartesiano*> points){
    QList<punto*> convertedPoints;
    for(auto i = points.begin(); i != points.end(); ++i){
        convertedPoints.push_back(new punto((*i)->rx(),(*i)->ry()));
    }
    return convertedPoints;
}

PuntoCartesiano* convertedPoint(const punto* point){
    int x = static_cast<int>(razionale::conversione(point->get_ascisse()));
    int y = static_cast<int>(razionale::conversione(point->get_ordinate()));
    return new PuntoCartesiano(x,y);
}

QMainCalc::QMainCalc(){

    //Titolo Calc
    setWindowTitle("The Cartesian Plane calc");

    //Dimensioni della mia calc
    setMaximumWidth(1000);
    setMinimumSize(1100, 800);

    widget = new QWidget;
    setCentralWidget(widget);

    grid = new QGridLayout;
    display = new MyInputPointDisplay(this);

    QTabWidget* tab = new QTabWidget(this);
    tab->addTab(new QEquation(tab), tr("Equazione"));
    tab->addTab(new Poligons(tab), tr("Poligoni")),
    tab->setStyleSheet("background-color: rgb(217, 217, 217)");
    tab->setTabPosition(QTabWidget::West);

    grid->addWidget(display, 0 , 0);
    grid->addWidget(tab , 1 ,0);

    widget->setLayout(grid);
}

void QMainCalc::Eappartenenza(){
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    planeOperation* op = static_cast<planeOperation*>(clickedButton->parent());
    QList<PuntoCartesiano*> displayPoints = display->getPlanePoints();

    if(displayPoints.size() == 0){
        op->setDisplayText("Non sono presenti punti nel Piano cartesiano");
    }
    else{
        QList<punto*> convertedDisplayPoints = conversionPoints(displayPoints);
        if(op->getNumeroFigure() >= 1){
            if(dynamic_cast<QEquation*>(op)){              
                QEquation* plain = static_cast<QEquation*>(op);
                equazione* primaRettaPresente = plain->getPrimaEquazione();
                auto j = displayPoints.begin();
                op->setDisplayText("Verde appartiene, Rosso non appartiene");
                if(op->getNumeroFigure() == 2){
                    equazione* secondaRettaPresente = plain->getSecondaEquazione();
                    for(auto i = convertedDisplayPoints.begin(); i != convertedDisplayPoints.end(); i++,j++){
                        bool primoControllo = primaRettaPresente->appartenenza(**i);
                        bool secondoControllo = secondaRettaPresente->appartenenza(**i);
                        if(primoControllo == false && secondoControllo == false)
                            plain->drawAppartPunto(*j,false);
                        else
                            plain->drawAppartPunto(*j,true);
                    }
                }
                else if(op->getNumeroFigure() == 1){
                    for(auto i = convertedDisplayPoints.begin(); i != convertedDisplayPoints.end(); i++,j++){
                        bool tmp = primaRettaPresente->appartenenza(**i);
                        plain->drawAppartPunto(*j,tmp);
                    }
                }
                convertedDisplayPoints.clear();
                return;
            }
        }
        else
            op->setDisplayText("Deve essere presente almeno una retta");
    }
}
//POST: dato punto controlla se appartiene all'equazione presente nel piano

void QMainCalc::EdistanzaPuntoRetta(){
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    planeOperation* op = static_cast<planeOperation*>(clickedButton->parent());
    QList<PuntoCartesiano*> displayPoints = display->getPlanePoints();

    if(displayPoints.size() != 1){
        op->setDisplayText("Distanza calcolabile solo con un punto");
        return;
    }

    if(op->getNumeroFigure() == 2){
        op->setDisplayText("Errore: sono presenti due rette nel piano");
        return;
    }
    if(op->getNumeroFigure() == 0){
        op->setDisplayText("Errore: non sono presenti rette nel piano");
        return;
    }
    if(op->getNumeroFigure() == 1){

        if(dynamic_cast<QEquation*>(op)){
           QEquation* plainEquation = static_cast<QEquation*>(op);

           punto* convertedDisplayPoint = (conversionPoints(displayPoints)).first();
           equazione* rettaPresente = plainEquation->getPrimaEquazione();
           equazione* equParallela = equazione::parallela(*rettaPresente, *convertedDisplayPoint);

           if(*equParallela==*rettaPresente ){
               plainEquation->setDisplayText("Il punto appartiene alla retta");
               return;
           }
           double distanza = rettaPresente->distanza(rettaPresente,*convertedDisplayPoint);
           op->setDisplayText(QString::number(distanza));
           delete equParallela;
        }
    }
}
//POST: data retta calcola distanza dal punto all'equazione

void QMainCalc::EincontroRette(){
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    planeOperation* op = static_cast<planeOperation*>(clickedButton->parent());
    if(op->getNumeroFigure() == 2){
        if(dynamic_cast<QEquation*>(op)){
            QEquation* plain = static_cast<QEquation*>(op);
            equazione* primaRetta = plain->getPrimaEquazione();
            equazione* secondaRetta = plain->getSecondaEquazione();
            if(equazione::condParallelismo(*primaRetta,*secondaRetta))
                op->setDisplayText("Le rette sono parallele");
            else{
                punto* incontro = equazione::incontro(*primaRetta,*secondaRetta);

                PuntoCartesiano* puntoIncontro = convertedPoint(incontro);
                QString testo;
                testo.append("Punto incontro rette: ");
                testo.append('(');
                testo.append(QString::number(puntoIncontro->rx()));
                testo.append(',');
                testo.append(QString::number(puntoIncontro->ry()));
                testo.append(')');
                if(puntoIncontro->rx() <=30 && puntoIncontro->ry() <= 30)
                    plain->drawAppartPunto(puntoIncontro,true);
                else
                    testo.append("esce dal grafico");
                op->setDisplayText(testo);
            }
        }
    }
}

void QMainCalc::EequPerpendicolare(){
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    planeOperation* op = static_cast<planeOperation*>(clickedButton->parent());

    if(op->getNumeroFigure() != 1){
        if(op->getNumeroFigure() == 2)
            op->setDisplayText("ERRORE: sono presenti due rette nel piano cartesiano");
        if(op->getNumeroFigure() == 0 )
            op->setDisplayText("ERRORE: non sono presenti rette nel piano cartesiano");

        return;
    }
    if(display->getPlanePoints().size() != 1){
        op->setDisplayText("ERRORE: retta perpendicolare calcolabile solo con un punto");
        return;
    }

    if(dynamic_cast<QEquation*>(op)){
        QEquation* sender = static_cast<QEquation*>(op);

        QList<punto*> onePoint = conversionPoints(display->getPlanePoints()); //punto singolo
        equazione* equ = sender->getPrimaEquazione();
        equazione* equPerpendicolare = equazione::perpendicolare(*equ, *onePoint.first()); //creo retta
        sender->displayEquation(*equPerpendicolare,"Equazione perpendicolare: ");
        delete equPerpendicolare;
    }
}
//POST: dato punto e retta torna retta parallela

void QMainCalc::EequParallela(){
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    planeOperation* op = static_cast<planeOperation*>(clickedButton->parent());

    if(op->getNumeroFigure() != 1){
        if(op->getNumeroFigure() == 2)
            op->setDisplayText("ERRORE: sono presenti due rette nel piano cartesiano");
        if(op->getNumeroFigure() == 0 )
            op->setDisplayText("ERRORE: non sono presenti rette nel piano cartesiano");

        return;
    }
    if(display->getPlanePoints().size() != 1){
        op->setDisplayText("ERRORE: retta parallela calcolabile solo con un punto");
        return;
    }
    if(dynamic_cast<QEquation*>(op)){
        QEquation* sender = static_cast<QEquation*>(op);
        QList<punto*> onePoint = conversionPoints(display->getPlanePoints()); //punto singolo
        equazione* equ = sender->getPrimaEquazione();
        equazione* equParallela = equazione::parallela(*equ, *onePoint.first()); //creo retta
        if(*equParallela == *equ){
            op->setDisplayText("Il punto appartiene alla retta");
            return;
        }
        sender->displayEquation(*equParallela,"Equazione parallela: ");
        delete equParallela;
    }
}
//POST: dato punto e equazione torna equazione perpependicolare

void QMainCalc::EcondParallelismo(){
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    planeOperation* op = static_cast<planeOperation*>(clickedButton->parent());

    if(op->getNumeroFigure() == 2 ){
        if(dynamic_cast<QEquation*>(op)){
            QEquation* sender = static_cast<QEquation*>(op);
            equazione* prima = sender->getPrimaEquazione();
            equazione* seconda = sender->getSecondaEquazione();
            bool check = equazione::condParallelismo(*prima, *seconda);
            if(check==true)
                op->setDisplayText("Le rette sono parallele");
            else
                op->setDisplayText("Le rette non sono parallele");
        }
    }
    else{
        if(op->getNumeroFigure() == 1){
            op->setDisplayText("Parallelismo verificabile solo con due rette");
        }
        if(op->getNumeroFigure() == 0){
            op->setDisplayText("Non sono presenti rette nel piano");
        }
    }
}
//POST: true sole se due rette sono parallele

void QMainCalc::EcondPerpendicolare(){
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    planeOperation* op = static_cast<planeOperation*>(clickedButton->parent());

    if(op->getNumeroFigure() == 2 ){
        if(dynamic_cast<QEquation*>(op)){
            QEquation* sender = static_cast<QEquation*>(op);
            equazione* prima = sender->getPrimaEquazione();
            equazione* seconda = sender->getSecondaEquazione();
            bool check = equazione::condPerpendicolari(*prima, *seconda);
            sender->displayEquation(*prima," seconda");
            if(check==true)
                op->setDisplayText("Le rette sono perpendicolari");
            else
                op->setDisplayText("Le rette non sono perpendicolari");
        }
    }
    else{
        op->setDisplayText("Perpendicolarità verificabile solo con due rette");
    }
}
//POST: torna true solo se le due rette sono perpendicolari

void QMainCalc::PPerimetro(){
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    planeOperation* op = static_cast<planeOperation*>(clickedButton->parent());

    if(op->getNumeroFigure() == 0){
        op->setDisplayText("ERRORE: non è presente una figura nel piano");
        return;
    }
    if(dynamic_cast<Poligons*>(op)){
        Poligons* sender = static_cast<Poligons*>(op);
        poligono* pol = sender->getFiguraPiano();
        double peri = pol->perimetro();
        op->setDisplayText(QString::number(peri));
    }
}
//POST: calcolo perimetro figura

void QMainCalc::PArea(){
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    planeOperation* op = static_cast<planeOperation*>(clickedButton->parent());

    if(op->getNumeroFigure() == 0){
        op->setDisplayText("ERRORE: non è presente una figura nel piano");
        return;
    }
    if(dynamic_cast<Poligons*>(op)){
        Poligons* sender = static_cast<Poligons*>(op);
        poligono* pol = sender->getFiguraPiano();
        double area = pol->area();
        op->setDisplayText(QString::number(area));
    }
}

void QMainCalc::PRaggioCircInscritta(){
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    planeOperation* op = static_cast<planeOperation*>(clickedButton->parent());

    if(op->getNumeroFigure() == 0){
        op->setDisplayText("ERRORE: non è presente una figura nel piano");
        return;
    }
    if(dynamic_cast<Poligons*>(op)){
        Poligons* sender = static_cast<Poligons*>(op);
        poligono* pol = sender->getFiguraPiano();
        double raggioCircInscritta = pol->raggioCircInscritta();
        op->setDisplayText(QString::number(raggioCircInscritta));
    }
}

void QMainCalc::PRaggioCircCircoscritta(){
   QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
   planeOperation* op = static_cast<planeOperation*>(clickedButton->parent());

   if(op->getNumeroFigure() == 0){
       op->setDisplayText("ERRORE: non è presente una figura nel piano");
       return;
   }
   if(dynamic_cast<Poligons*>(op)){
       Poligons* sender = static_cast<Poligons*>(op);
       poligono* pol = sender->getFiguraPiano();
       double raggioCircCircoscritta = pol->raggioCircCircoscritta();
       op->setDisplayText(QString::number(raggioCircCircoscritta));
   }
}

void QMainCalc::PAreaCircInscritta(){
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    planeOperation* op = static_cast<planeOperation*>(clickedButton->parent());

    if(op->getNumeroFigure() == 0){
        op->setDisplayText("ERRORE: non è presente una figura nel piano");
        return;
    }
    if(dynamic_cast<Poligons*>(op)){
        Poligons* sender = static_cast<Poligons*>(op);
        poligono* pol = sender->getFiguraPiano();
        double areaCircInscritta = pol->areaCircInscritta();
        op->setDisplayText(QString::number(areaCircInscritta));
    }
}

void QMainCalc::PAreaCircCircoscritta(){
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    planeOperation* op = static_cast<planeOperation*>(clickedButton->parent());

    if(op->getNumeroFigure() == 0){
        op->setDisplayText("ERRORE: non è presente una figura nel piano");
        return;
    }
    if(dynamic_cast<Poligons*>(op)){
        Poligons* sender = static_cast<Poligons*>(op);
        poligono* pol = sender->getFiguraPiano();
        double areaCircCircoscritta = pol->areaCircCircoscritta();
        op->setDisplayText(QString::number(areaCircCircoscritta));
    }
}

void QMainCalc::genericalDraw(){
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    planeOperation* op = static_cast<planeOperation*>(clickedButton->parent());
    int NPoints = (display->getPlanePoints()).size();
    if(NPoints == 2 || NPoints == 3 || NPoints == 4){
        QList<PuntoCartesiano*> points = display->getPlanePoints();
        op->drawFigure(points);
    }
    else{
        if(NPoints > 4)
            op->setDisplayText("Troppi punti presenti nel Piano");
        if(NPoints == 0 )
            op->setDisplayText("Non sono presenti punti nel piano");
    }
}

void QMainCalc::genericalCancel(){
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    planeOperation* op = static_cast<planeOperation*>(clickedButton->parent());    
    op->deleteFigures();
}
//POST: cancella figura presente nel piano
