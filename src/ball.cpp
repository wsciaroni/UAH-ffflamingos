#include "ball.h"
#include <QtMath>
#include <qglobal.h>
#include <QRandomGenerator>
#include <QDebug>

ball::ball()
{
   color = QColor("yellow");
   dx = 2.00;
   dy = 2.00;
   x = 0.0;
   y = 0.0;
   w = 10.0;
   h = 10.0;

}

void ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(color);
    painter->drawEllipse(-w/2, -h/2, w, h);
}

QRectF ball::boundingRect() const
{
    qreal adjust = 1.0;
    return QRectF(-w/2 - adjust, -h/2 - adjust, w + adjust, h + adjust);
}

void ball::advanceBall()
{


    if(qSqrt(qPow(this->pos().rx(),2) +  qPow(this->pos().y(),2)) + 5 >= 100)
    {

     qDebug() << "Hits edge\n";



    double random = ((double) rand() /RAND_MAX);
    if((this->pos().x() < 2) && (this->pos().x() > -2)){
        if(this->pos().y() < 0){
            dx = 2;
            dy = 2;
            qDebug() << "a\n";
        }
        else{
            dx = -2;
            dy = -2;
            qDebug() << "b\n";
        }
    }
    else if((this->pos().y() < 2) && (this->pos().y() > -2)){
        if(this->pos().x() < 0){
            dx = 2;
            dy = 2;
            qDebug() << "c\n";
        }
        else{
            dx = -2;
            dy = -2;
            qDebug() << "d\n";
        }
    }
    else {
        dy = - random * (this->pos().y())/110 * 2;
        dx = - (1 - random) * (this->pos().x())/110 * 2;
    }


    if(qSqrt(qPow(dx,2) + qPow(dy,2)) < 2){
        if(dx >= 0){
            dx += 0.5;
        }
        else{
            dx  -= 0.5;
        }
        if(dy >= 0){
            dy += 0.5;
        }
        else{
            dy += -0.5;
        }
    }

    qDebug() << dx << " " << dy << this->pos().x() << " " << this->pos().y()<< '\n';
    }
    x = this->pos().rx();
    y = this->pos().ry();
    x = x + dx;
    y = y + dy;

    setPos(x,y);
}

QPainterPath ball::shape() const
{
    QPainterPath path;
    path.addEllipse(-w/2, -h/2, w, h);
    return path;
}

