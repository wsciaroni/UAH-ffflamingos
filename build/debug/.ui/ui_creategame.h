/********************************************************************************
** Form generated from reading UI file 'creategame.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEGAME_H
#define UI_CREATEGAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CreateGame
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *ip;
    QLabel *label_2;
    QLineEdit *port;
    QLabel *label_4;
    QLineEdit *roomCode;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *CreateGame)
    {
        if (CreateGame->objectName().isEmpty())
            CreateGame->setObjectName(QString::fromUtf8("CreateGame"));
        CreateGame->resize(400, 165);
        verticalLayout = new QVBoxLayout(CreateGame);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(CreateGame);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(CreateGame);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        ip = new QLineEdit(CreateGame);
        ip->setObjectName(QString::fromUtf8("ip"));

        formLayout->setWidget(0, QFormLayout::FieldRole, ip);

        label_2 = new QLabel(CreateGame);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        port = new QLineEdit(CreateGame);
        port->setObjectName(QString::fromUtf8("port"));

        formLayout->setWidget(1, QFormLayout::FieldRole, port);

        label_4 = new QLabel(CreateGame);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_4);

        roomCode = new QLineEdit(CreateGame);
        roomCode->setObjectName(QString::fromUtf8("roomCode"));

        formLayout->setWidget(2, QFormLayout::FieldRole, roomCode);


        verticalLayout->addLayout(formLayout);

        verticalSpacer = new QSpacerItem(20, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(CreateGame);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(CreateGame);
        QObject::connect(buttonBox, SIGNAL(accepted()), CreateGame, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), CreateGame, SLOT(reject()));

        QMetaObject::connectSlotsByName(CreateGame);
    } // setupUi

    void retranslateUi(QDialog *CreateGame)
    {
        CreateGame->setWindowTitle(QApplication::translate("CreateGame", "Dialog", nullptr));
        label_3->setText(QApplication::translate("CreateGame", "New Game Setup", nullptr));
        label->setText(QApplication::translate("CreateGame", "IP to Bind", nullptr));
        label_2->setText(QApplication::translate("CreateGame", "Port to Listen On", nullptr));
        label_4->setText(QApplication::translate("CreateGame", "Room Code", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateGame: public Ui_CreateGame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEGAME_H
