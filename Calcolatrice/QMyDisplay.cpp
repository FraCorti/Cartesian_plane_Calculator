#ifndef QMYDISPLAY_CPP
#define QMYDISPLAY_CPP

#include "QMyDisplay.h"

MyInputPointDisplay::MyInputPointDisplay(QWidget * parent): planeOperation(parent){

    cartesianPlane = new PianoCartesiano(this);
    grid = new QGridLayout;  //general grid
    display = new QLineEdit(this);
    inputAxisX = new QLineEdit("$", this);
    inputAxisY = new QLineEdit("$", this);
    stringPlainPoints = new QLineEdit("NULL", this);

    QPushButton* addPoint = new QPushButton("Add Point",this);
    QPushButton* deleteAllPoints = new QPushButton("Delete All", this);
    QPushButton* deleteTargetPoint = new QPushButton("Delete", this );
    QLabel* textInputX = new QLabel("Axes x", this);
    QLabel* textInputY = new QLabel("Axes y", this);
    QLabel* stringPlainPointsText = new QLabel("Points:",this);

    connect(addPoint, SIGNAL(clicked(bool)), this , SLOT(addPointClicked()));
    connect(deleteTargetPoint, SIGNAL(clicked(bool)), this , SLOT(clearClicked()));
    connect(deleteAllPoints, SIGNAL(clicked(bool)), this, SLOT(clearAllClicked()));

    cartesianPlane->setPlanDimension(325);
    stringPlainPoints->setFixedSize(400 , 50);
    inputAxisX->setFixedSize(300, 25);
    inputAxisY->setFixedSize(300 ,25);
    display->setFixedSize(400, 50);
    stringPlainPointsText->setFixedSize(40 ,80);
    textInputX->setFixedSize(40 ,50 );
    textInputY->setFixedSize(40 ,50);
    deleteAllPoints->setFixedSize(95, 50);
    deleteTargetPoint->setFixedSize(95, 50);
    addPoint->setFixedSize(95, 50);

    display->setReadOnly(true);
    display->setStyleSheet("background-color:rgb(191, 191, 191); font-family: Arial;font-style: StyleItalic ;font-size: 12pt;font-weight: white;");

    stringPlainPointsText->setStyleSheet("font-weight: bold; font-size: 8pt");
    stringPlainPoints->setStyleSheet("background-color:rgb(242, 242, 242); font-family: Arial;font-style: StyleItalic ;font-size: 12pt;font-weight: black;");
    stringPlainPoints->setReadOnly(true);

    textInputX->setStyleSheet("font-weight: bold; font-size: 8pt");
    textInputY->setStyleSheet("font-weight: bold; font-size: 8pt");

    //default length 5 and text alignRight
    inputAxisX->setMaxLength(5);
    inputAxisY->setMaxLength(5);
    stringPlainPoints->setAlignment(Qt::AlignRight);
    display->setAlignment(Qt::AlignRight);
    inputAxisX->setAlignment(Qt::AlignRight);
    inputAxisY->setAlignment(Qt::AlignRight);

    grid->addWidget(cartesianPlane, 0 , 0  , 6 , 6);
    grid->addWidget(display , 0 , 7 ,  2  , 4);
    grid->addWidget(textInputX, 2 , 7  , 1 , 1);
    grid->addWidget(inputAxisX, 2 , 8 , 1 , 4);
    grid->addWidget(textInputY, 3 , 7 ,  1 , 1);
    grid->addWidget(inputAxisY, 3 , 8 , 1 , 4);
    grid->addWidget(addPoint, 4 , 8 , 1 , 1);
    grid->addWidget(deleteTargetPoint, 4 , 9, 1 , 1);
    grid->addWidget(deleteAllPoints, 4 , 10 , 1 , 1);
    grid->addWidget(stringPlainPointsText, 5 ,7 , 1 ,1);
    grid->addWidget(stringPlainPoints, 5 , 9 , 2 , 5);

    setLayout(grid);
}

void MyInputPointDisplay::setDisplayText(QString text) const{
    display->setText(text);
}

void MyInputPointDisplay::setPointText() const{
    QList<PuntoCartesiano*> tmp = getPlanePoints();
    if(tmp.size() != 0){
        QString disp;
        for(auto i = tmp.begin(); i != tmp.end(); ++i){
            disp.append('(');
            disp.append(QString::number((*i)->rx()));
            disp.append(',');
            disp.append(QString::number((*i)->ry()));
            disp.append(')');
        }
        stringPlainPoints->setText(disp);
        return;
    }
    stringPlainPoints->setText("NULL");
}

void MyInputPointDisplay::delateAllUsedFiguresPoints(){
    cartesianPlane->deleteAllPoint();
    stringPlainPoints->setText("NULL");
}

void MyInputPointDisplay::clearClicked(){
    if(cartesianPlane->getPlainPointsSize() != 0){
        int x,y;

        if(checkInputNumber(inputAxisX,inputAxisY,x,y) && cartesianPlane->deletePoint(x,y)){
            display->setText("Point delete successfully");
            setPointText();
            return;
        }
        display->setText("No point to delete with the value you have insert");
        return;
    }
    display->setText("There aren't any points inside the graph");
}

void MyInputPointDisplay::addPointClicked(){
    int x,y;

    if(checkInputNumber(inputAxisX,inputAxisY,x,y)){
        bool sent = cartesianPlane->addSinglePoint(x,y);
        if(sent){
            display->setText("Point add successfully");
            setPointText();
            return;
        }
        else
            display->setText("There is already a point with this value");
    }
}

void MyInputPointDisplay::clearAllClicked(){
    if(cartesianPlane->getPlainPointsSize() != 0){
        QMessageBox msgBox;
        msgBox.setText("This action is going to cancel all the points");

        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);

        int value = msgBox.exec();
        if(value == QMessageBox::Save){
            cartesianPlane->deleteAllPoint();
        }
        stringPlainPoints->setText("NULL");
        return;
    }
    display->setText("There aren't any points inside the graph");
}

bool MyInputPointDisplay::checkInputNumber(QLineEdit*& x1, QLineEdit*& y1, int& numberX, int& numberY) const{

    if(x1->text() == "$" ){
        display->setText("ERROR: you must insert a number in the line of axis X");
        return false;
    }
    if(y1->text() == "$"){
        display->setText("ERROR: you must insert a number in the line of axis Y");
        return false;
    }

    bool checkX = true;
    bool checkY = true;

    ///accettati solo int ma posso mettere anche double con algoritmo di Euclide
    int valueX = x1->text().toInt(&checkX, 10);  //convert string x int base 10
    int valueY = y1->text().toInt(&checkY, 10);  //convert string y int base 10

    if(!checkX || !checkY){
        display->setText("ERRORE: sono accettati solo interi come input");
        return false;
    }
    if(valueX > 30 || valueX < -30){
        display->setText("ERROR: number of Axis Y has to be >-30 and <30");
        return false;
    }
    if(valueY > 30 || valueY < -30){
        display->setText("ERROR: number of Axis Y has to be >-30 and <30");
        return false;
    }

    numberX = valueX;
    numberY = valueY;
    return true;
}
//POST:

QList<PuntoCartesiano*> MyInputPointDisplay::getPlanePoints() const{
    QList<PuntoCartesiano*> tmp = cartesianPlane->getPointsPublic();
    return tmp;
}

void MyInputPointDisplay::deleteFigures(){}

void MyInputPointDisplay::drawFigure(QList<PuntoCartesiano*> points){}

int MyInputPointDisplay::getNumeroFigure() const{
    int NPoints = cartesianPlane->getPlainPointsSize();
    return NPoints;
}


#endif // QMYDISPLAY_CPP
