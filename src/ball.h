#ifndef BALL_H
#define BALL_H

#include <QGraphicsItem>
#include <QColor>
#include <QPainter>
#include <QRect>

/**
 * Used to instantiate and control individual balls.
 */
class ball : public QGraphicsItem {
 public:
  /**
   * Default constructor.
   */
  explicit ball();

  QRectF boundingRect() const;
  QPainterPath shape() const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget);

  /**
   * Used to move the ball.
   * If the ball is outside the circle, we want to give it a new velocity.  This
   * is calculated with the following equations for the partial velocities in
   * the X and Y components. \n
   * For the X component: \f$dx = \frac{-x}{\beta} + Sin(angleOffset)\f$ \n
   * For the Y component: \f$dy = \frac{-y}{\beta} + Cos(angleOffset)\f$ \n \n
   * Then, no matter the location of the ball, the velocity is added to the
   * current location of the ball. \n
   * \f$x += dx\f$ \n
   * \f$y += dy\f$
   */
  void advanceBall();

  /**
   * Sets the ball's location and velocity.
   * @param xPos The X coordinate of the ball
   * @param yPos The Y coordinate of the ball
   * @param dxIn The new value for dx
   * @param dyIn The new value for dy
   */
  void initializeBall(qreal xPos, qreal yPos, qreal dxIn, qreal dyIn);

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
