#include "ball.h"
#include <QtMath>
#include <qglobal.h>
#include <QRandomGenerator>
#include <QDebug>

ball::ball() {
  color = QColor("yellow");
  dx = 2.00;
  dy = 2.00;
  x = 0.0;
  y = 0.0;
  w = 10.0;
  h = 10.0;
}

void ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                 QWidget *widget) {

  painter->setBrush(color);
  painter->drawEllipse(-w / 2, -h / 2, w, h);
}

QRectF ball::boundingRect() const {
  qreal adjust = 1.0;
  return QRectF(-w / 2 - adjust, -h / 2 - adjust, w + adjust, h + adjust);
}

void ball::advanceBall() {
  if (isHidden) {
    return;
  }

  x = this->pos().rx();
  y = this->pos().ry();

  if (qSqrt(qPow(x, 2) + qPow(y, 2)) + 5 >= 300) {
    // qDebug() << "Hits edge\n";
    double beta = 300;
    int megaPi = M_PI * 10000;
    qreal angleOffset = static_cast<qreal>(
        static_cast<double>(
            QRandomGenerator::global()->bounded(-megaPi, megaPi)) /
        static_cast<double>(10000));
    dx = (-x / beta) + qSin(angleOffset);
    dy = (-y / beta) + qCos(angleOffset);
  }
  x += dx;
  y += dy;
  setPos(x, y);
}

void ball::hideBall() {
  isHidden = true;
  dx = 0;
  dy = 0;
  setPos(0, 0);
  hide();
}

QPainterPath ball::shape() const {
  QPainterPath path;
  path.addEllipse(-w / 2, -h / 2, w, h);
  return path;
}

void ball::initializeBall(qreal xPos, qreal yPos, qreal dxIn, qreal dyIn) {
  setPos(xPos, yPos);
  this->dx = dxIn;
  this->dy = dyIn;
}
