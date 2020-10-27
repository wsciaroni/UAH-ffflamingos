#ifndef ERROR_H
#define ERROR_H

#include <QDialog>

namespace Ui {
class error;
}

/**
 * Used to display an error
 */
class error : public QDialog
{
    Q_OBJECT

public:
    explicit error(QWidget *parent = nullptr);
    ~error();

private:
    Ui::error *ui;
};

#endif // ERROR_H
