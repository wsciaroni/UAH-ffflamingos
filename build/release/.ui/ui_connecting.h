/********************************************************************************
** Form generated from reading UI file 'connecting.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTING_H
#define UI_CONNECTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Connecting
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;

    void setupUi(QDialog *Connecting)
    {
        if (Connecting->objectName().isEmpty())
            Connecting->setObjectName(QString::fromUtf8("Connecting"));
        Connecting->resize(217, 70);
        verticalLayout = new QVBoxLayout(Connecting);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(Connecting);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        verticalSpacer = new QSpacerItem(20, 4, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(Connecting);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Connecting);

        QMetaObject::connectSlotsByName(Connecting);
    } // setupUi

    void retranslateUi(QDialog *Connecting)
    {
        Connecting->setWindowTitle(QApplication::translate("Connecting", "Dialog", nullptr));
        label->setText(QApplication::translate("Connecting", "Connecting to Host... Please wait", nullptr));
        pushButton->setText(QApplication::translate("Connecting", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Connecting: public Ui_Connecting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTING_H
