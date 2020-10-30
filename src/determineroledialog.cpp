#include "determineroledialog.h"
#include "ui_determineroledialog.h"

DetermineRoleDialog::DetermineRoleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DetermineRoleDialog)
{
    ui->setupUi(this);
}

DetermineRoleDialog::~DetermineRoleDialog()
{
    delete ui;
}
