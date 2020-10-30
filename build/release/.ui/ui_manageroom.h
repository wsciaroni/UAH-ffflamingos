/********************************************************************************
** Form generated from reading UI file 'manageroom.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANAGEROOM_H
#define UI_MANAGEROOM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ManageRoom
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QListView *players;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QLabel *label_2;
    QSpacerItem *verticalSpacer_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ManageRoom)
    {
        if (ManageRoom->objectName().isEmpty())
            ManageRoom->setObjectName(QString::fromUtf8("ManageRoom"));
        ManageRoom->resize(400, 300);
        verticalLayout_3 = new QVBoxLayout(ManageRoom);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(ManageRoom);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        players = new QListView(ManageRoom);
        players->setObjectName(QString::fromUtf8("players"));

        verticalLayout->addWidget(players);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        label_2 = new QLabel(ManageRoom);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(ManageRoom);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_3->addWidget(buttonBox);


        retranslateUi(ManageRoom);
        QObject::connect(buttonBox, SIGNAL(accepted()), ManageRoom, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ManageRoom, SLOT(reject()));

        QMetaObject::connectSlotsByName(ManageRoom);
    } // setupUi

    void retranslateUi(QDialog *ManageRoom)
    {
        ManageRoom->setWindowTitle(QApplication::translate("ManageRoom", "Dialog", nullptr));
        label->setText(QApplication::translate("ManageRoom", "Players Joined:", nullptr));
        label_2->setText(QApplication::translate("ManageRoom", "Press OK to start the game", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ManageRoom: public Ui_ManageRoom {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANAGEROOM_H
