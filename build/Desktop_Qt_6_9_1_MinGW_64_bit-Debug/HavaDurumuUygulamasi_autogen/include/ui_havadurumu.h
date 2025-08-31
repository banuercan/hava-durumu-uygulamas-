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
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_havadurumu
{
public:
    QWidget *centralwidget;
    QLineEdit *cityLineEdit;
    QRadioButton *CelciusButton;
    QRadioButton *FahreneitButton;
    QPushButton *fetchButton;
    QScrollArea *resultScrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QLabel *resultLabel;
    QPushButton *exitButton;
    QLabel *weatherImageLabel;
    QLabel *weatherInfoLabel;
    QPushButton *suggestionButton;
    QLabel *suggestionLabel;
    QLabel *suggestionLabel_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *havadurumu)
    {
        if (havadurumu->objectName().isEmpty())
            havadurumu->setObjectName("havadurumu");
        havadurumu->resize(825, 610);
        havadurumu->setStyleSheet(QString::fromUtf8("background-color: rgb(183, 233, 255);\n"
"\n"
"\n"
""));
        centralwidget = new QWidget(havadurumu);
        centralwidget->setObjectName("centralwidget");
        cityLineEdit = new QLineEdit(centralwidget);
        cityLineEdit->setObjectName("cityLineEdit");
        cityLineEdit->setGeometry(QRect(10, 10, 221, 31));
        cityLineEdit->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
        cityLineEdit->setStyleSheet(QString::fromUtf8("color: black;\n"
"background-color: rgb(255, 249, 217);"));
        CelciusButton = new QRadioButton(centralwidget);
        CelciusButton->setObjectName("CelciusButton");
        CelciusButton->setGeometry(QRect(320, 10, 41, 31));
        CelciusButton->setStyleSheet(QString::fromUtf8("QRadioButton {\n"
"    color: black; \n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QRadioButton::indicator {\n"
"    width: 14px;\n"
"    height: 14px;\n"
"    border-radius: 7px;               \n"
"    border: 2px solid #222;           \n"
"    color: black;\n"
"    background-color: rgb(183, 233, 255);\n"
"}\n"
"\n"
"QRadioButton::indicator:checked {\n"
"    background-color:#888888;          \n"
"    border: 2px solid #000;          \n"
"}\n"
""));
        FahreneitButton = new QRadioButton(centralwidget);
        FahreneitButton->setObjectName("FahreneitButton");
        FahreneitButton->setGeometry(QRect(370, 10, 41, 31));
        FahreneitButton->setStyleSheet(QString::fromUtf8("QRadioButton {\n"
"    color: black; \n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QRadioButton::indicator {\n"
"    width: 14px;\n"
"    height: 14px;\n"
"    border-radius: 7px;               \n"
"    border: 2px solid #222;           \n"
"    color: black;\n"
"    background-color: rgb(183, 233, 255);\n"
"}\n"
"\n"
"QRadioButton::indicator:checked {\n"
"    background-color:#888888;          \n"
"    border: 2px solid #000;          \n"
"}"));
        fetchButton = new QPushButton(centralwidget);
        fetchButton->setObjectName("fetchButton");
        fetchButton->setGeometry(QRect(240, 10, 71, 31));
        fetchButton->setStyleSheet(QString::fromUtf8("color: black;\n"
"background-color: rgb(255, 249, 217);\n"
" font-weight: bold;"));
        resultScrollArea = new QScrollArea(centralwidget);
        resultScrollArea->setObjectName("resultScrollArea");
        resultScrollArea->setGeometry(QRect(0, 40, 511, 521));
        resultScrollArea->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustToContents);
        resultScrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 509, 519));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setObjectName("verticalLayout");
        resultLabel = new QLabel(scrollAreaWidgetContents);
        resultLabel->setObjectName("resultLabel");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(resultLabel->sizePolicy().hasHeightForWidth());
        resultLabel->setSizePolicy(sizePolicy);
        resultLabel->setMouseTracking(true);
        resultLabel->setStyleSheet(QString::fromUtf8("color: black;\n"
"background-color: rgb(255, 249, 217);\n"
"\n"
"\n"
""));
        resultLabel->setTextFormat(Qt::TextFormat::RichText);
        resultLabel->setWordWrap(true);

        verticalLayout->addWidget(resultLabel);

        resultScrollArea->setWidget(scrollAreaWidgetContents);
        exitButton = new QPushButton(centralwidget);
        exitButton->setObjectName("exitButton");
        exitButton->setGeometry(QRect(730, 10, 81, 31));
        exitButton->setStyleSheet(QString::fromUtf8("color: black;\n"
"background-color: rgb(255, 39, 39);\n"
" font-weight: bold;"));
        weatherImageLabel = new QLabel(centralwidget);
        weatherImageLabel->setObjectName("weatherImageLabel");
        weatherImageLabel->setGeometry(QRect(520, 50, 291, 271));
        weatherImageLabel->setStyleSheet(QString::fromUtf8("color: black;\n"
"background-color: rgb(255, 249, 217);"));
        weatherInfoLabel = new QLabel(centralwidget);
        weatherInfoLabel->setObjectName("weatherInfoLabel");
        weatherInfoLabel->setGeometry(QRect(520, 330, 291, 91));
        weatherInfoLabel->setStyleSheet(QString::fromUtf8("color: black;\n"
"background-color: rgb(255, 249, 217);"));
        suggestionButton = new QPushButton(centralwidget);
        suggestionButton->setObjectName("suggestionButton");
        suggestionButton->setGeometry(QRect(730, 430, 80, 31));
        suggestionButton->setStyleSheet(QString::fromUtf8("color: black;\n"
"background-color: rgb(255, 249, 217);"));
        suggestionLabel = new QLabel(centralwidget);
        suggestionLabel->setObjectName("suggestionLabel");
        suggestionLabel->setGeometry(QRect(520, 470, 291, 41));
        suggestionLabel->setStyleSheet(QString::fromUtf8("color: black;\n"
"background-color: rgb(255, 249, 217);"));
        suggestionLabel_2 = new QLabel(centralwidget);
        suggestionLabel_2->setObjectName("suggestionLabel_2");
        suggestionLabel_2->setGeometry(QRect(520, 430, 201, 31));
        suggestionLabel_2->setStyleSheet(QString::fromUtf8("color: black;\n"
"background-color: rgb(255, 249, 217);"));
        havadurumu->setCentralWidget(centralwidget);
        menubar = new QMenuBar(havadurumu);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 825, 21));
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
        cityLineEdit->setText(QString());
        CelciusButton->setText(QCoreApplication::translate("havadurumu", "C", nullptr));
        FahreneitButton->setText(QCoreApplication::translate("havadurumu", "F", nullptr));
        fetchButton->setText(QCoreApplication::translate("havadurumu", "RECEIVE", nullptr));
        resultLabel->setText(QString());
        exitButton->setText(QCoreApplication::translate("havadurumu", "EXIT", nullptr));
        weatherImageLabel->setText(QString());
        weatherInfoLabel->setText(QString());
        suggestionButton->setText(QCoreApplication::translate("havadurumu", "SUGGEST", nullptr));
        suggestionLabel->setText(QString());
        suggestionLabel_2->setText(QCoreApplication::translate("havadurumu", "Please press for event suggestion =>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class havadurumu: public Ui_havadurumu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HAVADURUMU_H
