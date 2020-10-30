/********************************************************************************
** Form generated from reading UI file 'waitingtostart.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WAITINGTOSTART_H
#define UI_WAITINGTOSTART_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_WaitingToStart
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;

    void setupUi(QDialog *WaitingToStart)
    {
        if (WaitingToStart->objectName().isEmpty())
            WaitingToStart->setObjectName(QString::fromUtf8("WaitingToStart"));
        WaitingToStart->resize(400, 86);
        verticalLayout = new QVBoxLayout(WaitingToStart);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(WaitingToStart);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        verticalSpacer = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(WaitingToStart);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(WaitingToStart);

        QMetaObject::connectSlotsByName(WaitingToStart);
    } // setupUi

    void retranslateUi(QDialog *WaitingToStart)
    {
        WaitingToStart->setWindowTitle(QApplication::translate("WaitingToStart", "Dialog", nullptr));
        label->setText(QApplication::translate("WaitingToStart", "<html><head/><body><p><span style=\" font-size:14pt;\">Waiting for Host to start the game...</span></p></body></html>", nullptr));
        pushButton->setText(QApplication::translate("WaitingToStart", "Disconnect From Game (Quit)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WaitingToStart: public Ui_WaitingToStart {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WAITINGTOSTART_H
