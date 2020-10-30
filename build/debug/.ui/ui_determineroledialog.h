/********************************************************************************
** Form generated from reading UI file 'determineroledialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DETERMINEROLEDIALOG_H
#define UI_DETERMINEROLEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DetermineRoleDialog
{
public:
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *userName;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QRadioButton *createGame;
    QRadioButton *joinGame;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DetermineRoleDialog)
    {
        if (DetermineRoleDialog->objectName().isEmpty())
            DetermineRoleDialog->setObjectName(QString::fromUtf8("DetermineRoleDialog"));
        DetermineRoleDialog->resize(400, 182);
        horizontalLayout_3 = new QHBoxLayout(DetermineRoleDialog);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(DetermineRoleDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFrameShape(QFrame::NoFrame);

        horizontalLayout_2->addWidget(label_2);

        userName = new QLineEdit(DetermineRoleDialog);
        userName->setObjectName(QString::fromUtf8("userName"));

        horizontalLayout_2->addWidget(userName);


        verticalLayout_2->addLayout(horizontalLayout_2);

        label = new QLabel(DetermineRoleDialog);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        createGame = new QRadioButton(DetermineRoleDialog);
        createGame->setObjectName(QString::fromUtf8("createGame"));

        verticalLayout->addWidget(createGame);

        joinGame = new QRadioButton(DetermineRoleDialog);
        joinGame->setObjectName(QString::fromUtf8("joinGame"));

        verticalLayout->addWidget(joinGame);


        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(DetermineRoleDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);


        horizontalLayout_3->addLayout(verticalLayout_2);


        retranslateUi(DetermineRoleDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), DetermineRoleDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DetermineRoleDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(DetermineRoleDialog);
    } // setupUi

    void retranslateUi(QDialog *DetermineRoleDialog)
    {
        DetermineRoleDialog->setWindowTitle(QApplication::translate("DetermineRoleDialog", "Dialog", nullptr));
        label_2->setText(QApplication::translate("DetermineRoleDialog", "<html><head/><body><p><span style=\" font-size:14pt;\">What is Your username?</span></p></body></html>", nullptr));
        label->setText(QApplication::translate("DetermineRoleDialog", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:600;\">What would you like to do?</span></p></body></html>", nullptr));
        createGame->setText(QApplication::translate("DetermineRoleDialog", "Create New Game", nullptr));
        joinGame->setText(QApplication::translate("DetermineRoleDialog", "Join Existing Game", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DetermineRoleDialog: public Ui_DetermineRoleDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DETERMINEROLEDIALOG_H
