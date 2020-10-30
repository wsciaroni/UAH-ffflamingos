/********************************************************************************
** Form generated from reading UI file 'joinexistinggame.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JOINEXISTINGGAME_H
#define UI_JOINEXISTINGGAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_JoinExistingGame
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *ip;
    QLabel *label_2;
    QLineEdit *port;
    QLabel *label_3;
    QLineEdit *roomCode;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *JoinExistingGame)
    {
        if (JoinExistingGame->objectName().isEmpty())
            JoinExistingGame->setObjectName(QString::fromUtf8("JoinExistingGame"));
        JoinExistingGame->resize(400, 142);
        verticalLayout = new QVBoxLayout(JoinExistingGame);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(JoinExistingGame);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        ip = new QLineEdit(JoinExistingGame);
        ip->setObjectName(QString::fromUtf8("ip"));

        formLayout->setWidget(0, QFormLayout::FieldRole, ip);

        label_2 = new QLabel(JoinExistingGame);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        port = new QLineEdit(JoinExistingGame);
        port->setObjectName(QString::fromUtf8("port"));

        formLayout->setWidget(1, QFormLayout::FieldRole, port);

        label_3 = new QLabel(JoinExistingGame);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        roomCode = new QLineEdit(JoinExistingGame);
        roomCode->setObjectName(QString::fromUtf8("roomCode"));

        formLayout->setWidget(2, QFormLayout::FieldRole, roomCode);


        verticalLayout->addLayout(formLayout);

        buttonBox = new QDialogButtonBox(JoinExistingGame);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(JoinExistingGame);
        QObject::connect(buttonBox, SIGNAL(accepted()), JoinExistingGame, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), JoinExistingGame, SLOT(reject()));

        QMetaObject::connectSlotsByName(JoinExistingGame);
    } // setupUi

    void retranslateUi(QDialog *JoinExistingGame)
    {
        JoinExistingGame->setWindowTitle(QApplication::translate("JoinExistingGame", "Dialog", nullptr));
        label->setText(QApplication::translate("JoinExistingGame", "Host IP", nullptr));
        label_2->setText(QApplication::translate("JoinExistingGame", "Host Port:", nullptr));
        label_3->setText(QApplication::translate("JoinExistingGame", "Room Code:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class JoinExistingGame: public Ui_JoinExistingGame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JOINEXISTINGGAME_H
