#ifndef ERROR_H
#define ERROR_H

#include <QDialog>

namespace Ui {
class error;
}

/**
 * Used to display an error
 */
class error : public QDialog {
  Q_OBJECT

 public:
  /**
   * Used to define a new error
   */
  explicit error(QWidget *parent = nullptr);

  /**
   * Destructor
   */
  ~error();

  /**
   * Used to specify what message needs to be thrown
   */
  void throwErrorMsg(QString msg);

 private:
  Ui::error *ui;
};

#endif  // ERROR_H
