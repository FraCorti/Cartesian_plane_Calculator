#ifndef PIANO_CART_H
#define PIANO_CART_H

#include <QLineEdit>
#include <qcustomplot.h>
#include <QPainter>
#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QPushButton>
#include <QBoxLayout>

class PuntoCartesiano: public QPointF{
    private:
        int x , y;
    public:
        PuntoCartesiano(int nX , int nY): x(nX), y(nY){}     
        PuntoCartesiano& operator=(const PuntoCartesiano& genericPoint){
            if(this != &genericPoint){
                x = genericPoint.x;
                y = genericPoint.y;
            }
            return *this;
        }
        int rx() const{
            return x;
        }
        int ry() const{
            return y;
        }
        int getX() const{
            return x;
        }
        int getY() const{
            return y;
        }
};

class PianoCartesiano: public QWidget{
    Q_OBJECT

protected:
    QList<PuntoCartesiano*> planePoints;
    QCustomPlot* cartesianPlane;
    QCPGraph* points;

public:
    bool checkPointIn(const int x, const int y) const;
    QList<PuntoCartesiano*> getPointsPublic() const;
    void setPlanDimension(int);
    int getPlainPointsSize() const;
    bool deletePoint(int,int);
    void deleteAllPoint();
    bool addSinglePoint(int,int);
    void cartesianPlot() const;
    void setCartesianPlanePoint(const QList<PuntoCartesiano*>& actualPoint);
    virtual bool drawFigure(const QList<PuntoCartesiano*> points);
    virtual bool delFigure();
    PianoCartesiano(QWidget* =0);

};

#endif // PIANO_CART_H
