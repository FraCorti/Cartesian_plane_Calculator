#include "QPoligoni.h"

QList<punto*> pointConverted(const QList<PuntoCartesiano*> points){
    QList<punto*> convertedPoints;
    for(auto i = points.begin(); i != points.end(); ++i){
        convertedPoints.push_back(new punto((*i)->rx(),(*i)->ry()));
    }
    return convertedPoints;
}

Poligons::Poligons(QWidget *p): planeOperation(p){
    numeroFigure = 0;
    poligonoPiano = nullptr;
    cartesianPlane = new QPoligonsPlane(this);
    generalDisplay = new QLineEdit(this);
    grid = new QGridLayout(this);

    QWidget* mw = static_cast<QWidget*>(p->parent());
    QPushButton* disegnaFigura = new QPushButton(tr("Disegna \n figura"), mw);
    QPushButton* eliminaFigura = new QPushButton(tr("Elimina \n figura"), mw);
    QPushButton* area = new QPushButton(tr("Area"), mw);
    QPushButton* perimetro = new QPushButton(tr("Perimetro"), mw);
    QPushButton* areaCircInscritta = new QPushButton(tr("Area \n circonferenza \n inscritta"), mw);
    QPushButton* areaCircCirconscritta = new QPushButton(tr("Area \n circonferenza \n circoscritta"), mw);
    QPushButton* raggioCircInscritta = new QPushButton(tr("Raggio \n circonferenza \n inscritta"), mw);
    QPushButton* raggioCircCircoscritta = new QPushButton(tr("Raggio \n circonferenza \n circoscritta"), mw);

    connect(eliminaFigura, SIGNAL(clicked(bool)), mw, SLOT(genericalCancel()));
    connect(disegnaFigura, SIGNAL(clicked(bool)), mw , SLOT(genericalDraw()));
    connect(area, SIGNAL(clicked(bool)), mw , SLOT(PArea()));
    connect(perimetro , SIGNAL(clicked(bool)), mw , SLOT(PPerimetro()));
    connect(areaCircInscritta, SIGNAL(clicked(bool)), mw , SLOT(PAreaCircInscritta()));
    connect(areaCircCirconscritta, SIGNAL(clicked(bool)), mw , SLOT(PAreaCircCircoscritta()));
    connect(raggioCircCircoscritta, SIGNAL(clicked(bool)), mw, SLOT(PRaggioCircCircoscritta()));
    connect(raggioCircInscritta, SIGNAL(clicked(bool)), mw , SLOT(PRaggioCircInscritta()));

    generalDisplay->setFixedSize(400 , 50);
    generalDisplay->setReadOnly(true);
    generalDisplay->setStyleSheet("background-color:rgb(191, 191, 191); font-family: Arial;font-style: StyleItalic ;font-size: 12pt;font-weight: white;");
    generalDisplay->setAlignment(Qt::AlignRight);

    eliminaFigura->setFixedSize(120 , 60);
    disegnaFigura->setFixedSize(120 , 60);
    area->setFixedSize(120, 60);
    perimetro->setFixedSize(120, 60);
    raggioCircCircoscritta->setFixedSize(120, 60);
    raggioCircInscritta->setFixedSize(120, 60);
    areaCircCirconscritta->setFixedSize(120, 60);
    areaCircInscritta->setFixedSize(120, 60);

    grid->addWidget(cartesianPlane, 0 , 0 , 7 , 7 );
    grid->addWidget(generalDisplay ,  0 , 8 , 2 , 4);
    grid->addWidget(disegnaFigura, 0 , 7 , 2 , 3);
    grid->addWidget(eliminaFigura, 2 , 7 , 1 , 1);
    grid->addWidget(perimetro, 2 , 8 , 1 , 1);
    grid->addWidget(raggioCircCircoscritta, 2 , 9 , 1 , 1);
    grid->addWidget(raggioCircInscritta, 3 , 7  , 1 , 1);
    grid->addWidget(areaCircCirconscritta, 3 , 8 , 1 , 1);
    grid->addWidget(areaCircInscritta, 3 , 9  , 1 , 1);    
    grid->addWidget(area, 4 , 7, 1 , 1);
    setLayout(grid);
}

int Poligons::getNumeroFigure() const{
    return numeroFigure;
}

poligono* Poligons::getFiguraPiano() const{
    return poligonoPiano;
}

void Poligons::setDisplayText(QString text) const{
    generalDisplay->setText(text);
}

void Poligons::deleteFigures(){
    bool sent = cartesianPlane->delFigure();
    if(sent){
        generalDisplay->setText("Figura cancellata correttamente");
        numeroFigure = 0;
        delete poligonoPiano;
        poligonoPiano = nullptr;
    }
    else{
        generalDisplay->setText("Non sono presenti figure nel piano");
    }
}

void Poligons::drawFigure(QList<PuntoCartesiano*> points){

    if(numeroFigure != 0 ){
        generalDisplay->setText("ERRORE: cancellare la figura presente nel piano");
        return;
    }

    QList<punto*> convertedPoints = pointConverted(points);
    if(convertedPoints.size() == 4 && !quadrato::controlloReg(convertedPoints)){
            setDisplayText("ERRORE: il quadrato non è regolare");            
            return;
    }
    cartesianPlane->drawFigure(points);
    if(points.size() == 4)
        poligonoPiano = new quadrato(convertedPoints);

    if(points.size() == 3)
        poligonoPiano = new triangolo(convertedPoints);
    generalDisplay->setText("Figura disegnata correttamente");
    convertedPoints.clear();
    ++numeroFigure;
}
