/********************************************************************************
** Form generated from reading UI file 'havadurumu.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HAVADURUMU_H
#define UI_HAVADURUMU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_havadurumu
{
public:
    QWidget *centralwidget;
    QLineEdit *cityLineEdit;
    QPushButton *fetchButton;
    QLabel *resultLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *havadurumu)
    {
        if (havadurumu->objectName().isEmpty())
            havadurumu->setObjectName("havadurumu");
        havadurumu->resize(800, 600);
        centralwidget = new QWidget(havadurumu);
        centralwidget->setObjectName("centralwidget");
        cityLineEdit = new QLineEdit(centralwidget);
        cityLineEdit->setObjectName("cityLineEdit");
        cityLineEdit->setGeometry(QRect(30, 10, 411, 24));
        fetchButton = new QPushButton(centralwidget);
        fetchButton->setObjectName("fetchButton");
        fetchButton->setGeometry(QRect(120, 50, 181, 24));
        resultLabel = new QLabel(centralwidget);
        resultLabel->setObjectName("resultLabel");
        resultLabel->setGeometry(QRect(30, 90, 391, 131));
        havadurumu->setCentralWidget(centralwidget);
        menubar = new QMenuBar(havadurumu);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        havadurumu->setMenuBar(menubar);
        statusbar = new QStatusBar(havadurumu);
        statusbar->setObjectName("statusbar");
        havadurumu->setStatusBar(statusbar);

        retranslateUi(havadurumu);

        QMetaObject::connectSlotsByName(havadurumu);
    } // setupUi

    void retranslateUi(QMainWindow *havadurumu)
    {
        havadurumu->setWindowTitle(QCoreApplication::translate("havadurumu", "havadurumu", nullptr));
        cityLineEdit->setText(QCoreApplication::translate("havadurumu", "\305\236EH\304\260R \304\260SM\304\260N\304\260 G\304\260R\304\260N\304\260Z:", nullptr));
        fetchButton->setText(QCoreApplication::translate("havadurumu", "HAVA DURUMUNU SORGULA", nullptr));
        resultLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class havadurumu: public Ui_havadurumu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HAVADURUMU_H
