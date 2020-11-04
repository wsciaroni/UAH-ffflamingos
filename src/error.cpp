#include "error.h"
#include "ui_error.h"

error::error(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::error)
{
    ui->setupUi(this);
    connect(ui->close, &QPushButton::clicked, this, &QDialog::reject);
}

error::~error()
{
    delete ui;
}
