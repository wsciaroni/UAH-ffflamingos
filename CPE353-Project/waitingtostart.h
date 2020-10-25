#ifndef WAITINGTOSTART_H
#define WAITINGTOSTART_H

#include <QDialog>

namespace Ui {
class WaitingToStart;
}

class WaitingToStart : public QDialog
{
    Q_OBJECT

public:
    explicit WaitingToStart(QWidget *parent = nullptr);
    ~WaitingToStart();

private:
    Ui::WaitingToStart *ui;
};

#endif // WAITINGTOSTART_H
