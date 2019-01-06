#include "QEquazione.h"

QString stampaRaz(const razionale& raz){

    QString razionale;
    int num = raz.getNum();
    int den = raz.getDen();

    if(den == 1){
        razionale.append(QString::number(num));
        return razionale;
    }
    if(num<0 && den<0){
        razionale.append(QString::number(num*-1));
        razionale.append("/");
        razionale.append(QString::number(den*-1));
        return razionale;
    }
    if((num<0) | (den<0)){
        razionale.append("-");
    }
    razionale.append(QString::number(num));
    razionale.append("/");
    razionale.append(QString::number(den));
    return razionale;
}
//POST: torna una stringa che stampa il mio razionale

QEquation::QEquation(QWidget*op): planeOperation(op){

    primaEquazione = 0;
    secondaEquazione = 0;
    numeroFigure = 0;
    grid = new QGridLayout(this);
    cartesianPlane = new QEquationPlane(this);
    generalOutPutDisplay = new QLineEdit(this);

    QWidget* mw = static_cast<QWidget*>(op->parent());

    QPushButton* disegnaEquazione = new QPushButton(tr("Disegna \n Equazione"), mw);
    //POST: dati due punti disegna l'equazione corrispondente

    QPushButton* eliminaRette = new QPushButton(tr("Cancella\n rette"), mw);

    QPushButton* appartenenza= new QPushButton(tr("Appartenenza \n punti"), mw);
     //POST: dato punto controlla se appartiene alla equazione

    QPushButton* distanzaPuntoRetta = new QPushButton(tr("Distanza punto \n retta "), mw);
    //POST: ret distanza dal punto all'equazione

    QPushButton* equParallele = new QPushButton(tr("Equazione \n parallela"), mw);
    //POST: dato punto e retta torna retta parallela

    QPushButton* equPerpendicolare = new QPushButton(tr("Equazione \n perpendicolare"), mw);
    //POST: dato punto e equ torna equ perp

    QPushButton* condParallelismo = new QPushButton(tr("Controllo \n parallelismo"), mw);
    //POST: true sse due rette sono parallele

    QPushButton* condPerpendicolare = new QPushButton(tr("Controllo \n perpendicolarità"), mw);
    //POST: torna true se le due rette sono perpendicolari

    QPushButton* eliminaPuntiAppartenenza = new QPushButton(tr("Cancella \n punti"), this);
    //POST: elimino i punti che ho controllato se appartenessero alla retta o meno

    QPushButton* incontroRette = new QPushButton(tr("Punto incontro \n rette"), mw);
    //Disegno il punto di incontro delle rette, se ci sono, nel piano

    eliminaPuntiAppartenenza->setFixedSize(120, 60);
    eliminaRette->setFixedSize(120 , 60);
    disegnaEquazione->setFixedSize(120 , 60);
    appartenenza->setFixedSize(120 , 60);
    distanzaPuntoRetta->setFixedSize(120 , 60);
    equParallele->setFixedSize(120 , 60);
    equPerpendicolare->setFixedSize(120 , 60);
    condParallelismo->setFixedSize(120 , 60);
    condPerpendicolare->setFixedSize(120 , 60);
    incontroRette->setFixedSize(120,60);

    generalOutPutDisplay->setFixedSize(400, 50);
    generalOutPutDisplay->setReadOnly(true);
    generalOutPutDisplay->setStyleSheet("background-color:rgb(191, 191, 191); font-family: Arial;font-style: StyleItalic ;font-size: 12pt;font-weight: white;");
    generalOutPutDisplay->setAlignment(Qt::AlignRight);

    connect(eliminaRette, SIGNAL(clicked(bool)), mw , SLOT(genericalCancel()));
    connect(disegnaEquazione, SIGNAL(clicked(bool)), mw , SLOT(genericalDraw()));
    connect(appartenenza ,SIGNAL(clicked(bool)), mw, SLOT(Eappartenenza()));
    connect(distanzaPuntoRetta ,SIGNAL(clicked(bool)), mw, SLOT(EdistanzaPuntoRetta()));
    connect(equParallele ,SIGNAL(clicked(bool)), mw, SLOT(EequParallela()));
    connect(equPerpendicolare ,SIGNAL(clicked(bool)), mw, SLOT(EequPerpendicolare()));
    connect(condParallelismo ,SIGNAL(clicked(bool)), mw, SLOT(EcondParallelismo()));
    connect(condPerpendicolare ,SIGNAL(clicked(bool)), mw, SLOT(EcondPerpendicolare()));
    connect(incontroRette, SIGNAL(clicked(bool)), mw, SLOT(EincontroRette()));
    connect(eliminaPuntiAppartenenza, SIGNAL(clicked(bool)), this, SLOT(eliminaPuntiAppartenenza()));

    grid->addWidget(cartesianPlane, 0 , 0 , 7 , 7 );
    grid->addWidget(generalOutPutDisplay , 0 , 8 , 2, 4 );
    grid->addWidget(disegnaEquazione, 0 , 7 , 2 , 3);
    grid->addWidget(eliminaRette, 2 , 7 , 1, 1);
    grid->addWidget(distanzaPuntoRetta, 2 , 8 , 1 , 1);
    grid->addWidget(equParallele, 2 , 9 , 1 , 1);
    grid->addWidget(equPerpendicolare,  3 , 7 , 1 , 1);
    grid->addWidget(condParallelismo, 3 , 8 , 1 , 1);
    grid->addWidget(condPerpendicolare , 3 , 9 , 1, 1);
    grid->addWidget(appartenenza, 4 , 8 , 1 , 1);
    grid->addWidget(eliminaPuntiAppartenenza, 4 , 9 , 1 , 1);
    grid->addWidget(incontroRette, 4 , 7 , 1 , 1);
    setLayout(grid);
    //grid->addWidget(puntoCoefficiente, 3 , 6 , 1 , 1);
}

void QEquation::eliminaPuntiAppartenenza(){
    bool check = cartesianPlane->eliminaPuntiAppartenza();
    if(check)
        generalOutPutDisplay->setText("Punti eliminati correttamente");
    else
        generalOutPutDisplay->setText("Non sono presenti punti nel piano");
}
//POST: elimino punti rossi e verdi


void QEquation::displayEquation(const equazione& e, const QString& string) const{

    QString equ;
    equ.append(string);
    razionale y = e.getY();
    razionale x = e.getX();

    if(y.getNum() == 0){
       razionale tmp= e.getX().razionale::inverso();
       equ.append("x=");
       razionale q1 = e.getQ()*tmp;
       QString raz = stampaRaz(q1);
       equ.append(raz);
       generalOutPutDisplay->setText(equ);
       return;
    }
    if(x.getNum() == 0){
       razionale tmp= e.getY().razionale::inverso();
       equ.append("y=");
       razionale q1 = e.getQ()*tmp;
       QString raz = stampaRaz(q1);
       equ.append(raz);
       generalOutPutDisplay->setText(equ);
       return;
    }
    else{
       equazione tmp=e.esplicita();
       equ.append("y=");
       if(razionale::conversione(tmp.getX())!=1){
           QString raz =stampaRaz(tmp.getX());
           equ.append(raz);
       }
       equ.append("x");
       if(razionale::conversione(tmp.getQ())>0){
           equ.append("+");
       }
       if(tmp.getQ().getNum() !=0){
          QString raz =stampaRaz(tmp.getQ());
          equ.append(raz);
       }
       generalOutPutDisplay->setText(equ);
    }
}
//POST: stampo sul display la mia equazione

void QEquation::setDisplayText(QString text) const{
    generalOutPutDisplay->setText(text);
}

int QEquation::getNumeroFigure() const{
    return numeroFigure;
}


void QEquation::drawFigure(QList<PuntoCartesiano*> points){
    bool sent = cartesianPlane->drawFigure(points);
    if(!sent){
        generalOutPutDisplay->setText("ERRORE: punti>2 oppure rette uguale già presente");
    }
    else{
        if(primaEquazione == nullptr){
            punto* a = new punto((*points.first()).rx(), (*points.first()).ry());
            punto* b = new punto((*points.last()).rx(), (*points.last()).ry());
            primaEquazione = equazione::punti(a, b);
            delete a;
            delete b;
            generalOutPutDisplay->setText("Retta disegnata correttamente");
            numeroFigure++;
            return;
        }
        if(secondaEquazione == nullptr){
            generalOutPutDisplay->setText("Retta disegnata correttamente");
            punto* a = new punto((*points.first()).rx(),(*points.first()).ry());
            punto* b = new punto((*points.last()).rx(), (*points.last()).ry());
            secondaEquazione = equazione::punti(a,b);
            delete a;
            delete b;
            numeroFigure++;
            return;
        }
        return;
    }
}

equazione* QEquation::getPrimaEquazione() const{
    return primaEquazione;
}
//POST: get prima equazione

equazione* QEquation::getSecondaEquazione() const{
    return secondaEquazione;
}
//POST: get seconda equazione

bool QEquation::drawAppartPunto(const PuntoCartesiano*point, bool presenza){
    bool sent = cartesianPlane->drawAppartenenzaPunto(presenza,point);
    return sent;
}

void QEquation::deleteFigures(){
    numeroFigure = 0;
    bool sent = cartesianPlane->delFigure();
    if(sent){
        generalOutPutDisplay->setText("Rette cancellate correttamente");
        if(primaEquazione != nullptr){
            delete primaEquazione;
            primaEquazione = nullptr;
        }
        if(secondaEquazione != nullptr){
            delete secondaEquazione;
            secondaEquazione = nullptr;
        }
    }
    else{
        generalOutPutDisplay->setText("Non sono presenti rette nel piano");
    }
}

