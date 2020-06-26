/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *shutdownButton;
    QPushButton *rebootButton;
    QPushButton *backPutton;
    QLabel *label;
    QPushButton *Exit_Program;
    QPushButton *Update_Program;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1082, 583);
        MainWindow->setStyleSheet(QLatin1String("QPushButton {\n"
"  border: 1px solid skyblue;\n"
"  background-color: rgba(0,0,0,0);\n"
"  color: skyblue;\n"
"  padding: 5px;\n"
"}\n"
"\n"
"QPushButton:disabled{\n"
"  color: #b5d9e8;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"color:#fff;\n"
"\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        shutdownButton = new QPushButton(centralwidget);
        shutdownButton->setObjectName(QStringLiteral("shutdownButton"));
        shutdownButton->setGeometry(QRect(260, 200, 181, 71));
        rebootButton = new QPushButton(centralwidget);
        rebootButton->setObjectName(QStringLiteral("rebootButton"));
        rebootButton->setGeometry(QRect(620, 200, 181, 71));
        backPutton = new QPushButton(centralwidget);
        backPutton->setObjectName(QStringLiteral("backPutton"));
        backPutton->setGeometry(QRect(10, 500, 111, 41));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(200, 330, 691, 211));
        label->setStyleSheet(QLatin1String("font-size: 25px;\n"
"text-align: center;"));
        label->setAlignment(Qt::AlignCenter);
        Exit_Program = new QPushButton(centralwidget);
        Exit_Program->setObjectName(QStringLiteral("Exit_Program"));
        Exit_Program->setGeometry(QRect(430, 80, 181, 71));
        Update_Program = new QPushButton(centralwidget);
        Update_Program->setObjectName(QStringLiteral("Update_Program"));
        Update_Program->setGeometry(QRect(440, 310, 181, 71));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1082, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "System Control Panel", nullptr));
        shutdownButton->setText(QApplication::translate("MainWindow", "\354\213\234\354\212\244\355\205\234 \354\242\205\353\243\214", nullptr));
        rebootButton->setText(QApplication::translate("MainWindow", "\354\213\234\354\212\244\355\205\234 \354\236\254\353\266\200\355\214\205", nullptr));
        backPutton->setText(QApplication::translate("MainWindow", "\353\217\214\354\225\204\352\260\200\352\270\260", nullptr));
        label->setText(QApplication::translate("MainWindow", "Who Am I", nullptr));
        Exit_Program->setText(QApplication::translate("MainWindow", "\355\224\204\353\241\234\352\267\270\353\236\250 \354\242\205\353\243\214", nullptr));
        Update_Program->setText(QApplication::translate("MainWindow", "\355\224\204\353\241\234\352\267\270\353\236\250 \354\227\205\353\215\260\354\235\264\355\212\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
