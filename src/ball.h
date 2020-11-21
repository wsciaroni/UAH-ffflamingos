#ifndef BALL_H
#define BALL_H

#include <QGraphicsItem>
#include <QColor>
#include <QPainter>
#include <QRect>

class ball : public QGraphicsItem {
 public:
  explicit ball();

  QRectF boundingRect() const;
  QPainterPath shape() const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget);

  void advanceBall();
 protected:


 private:
  QColor color;
  qreal start_x = 305;
  qreal start_y = 305;
  qreal diameter = 20;
  qreal x, y;
  qreal h, w;
  qreal dx;
  qreal dy;
};

#endif  // BALL_H
