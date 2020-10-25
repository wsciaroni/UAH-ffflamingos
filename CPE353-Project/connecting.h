#ifndef CONNECTING_H
#define CONNECTING_H

#include <QDialog>

namespace Ui {
class Connecting;
}

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
