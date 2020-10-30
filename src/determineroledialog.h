#ifndef DETERMINEROLEDIALOG_H
#define DETERMINEROLEDIALOG_H

#include <QDialog>

namespace Ui {
class DetermineRoleDialog;
}

class DetermineRoleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DetermineRoleDialog(QWidget *parent = nullptr);
    ~DetermineRoleDialog();

private:
    Ui::DetermineRoleDialog *ui;
};

#endif // DETERMINEROLEDIALOG_H
