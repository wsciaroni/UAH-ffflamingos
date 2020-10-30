#ifndef CONNECTING_H
#define CONNECTING_H

#include <QDialog>

namespace Ui {
class Connecting;
}

/**
 * Used to indicate to a guest that his machine is attempting to connect
 */
class Connecting : public QDialog
{
    Q_OBJECT

public:
    explicit Connecting(QWidget *parent = nullptr);
    ~Connecting();

private:
    Ui::Connecting *ui;
};

#endif // CONNECTING_H
