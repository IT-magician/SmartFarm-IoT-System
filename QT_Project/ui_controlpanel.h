/********************************************************************************
** Form generated from reading UI file 'controlpanel.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLPANEL_H
#define UI_CONTROLPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ControlPanel
{
public:
    QPushButton *pushButton_bulbs;
    QPushButton *pushButton_hotBulbs;
    QPushButton *pushButton_PDLC;
    QPushButton *pushButton_waterPump;
    QPushButton *pushButton_doorMotor;
    QSlider *horizontalSlider_doorLock;
    QLabel *doorLock_OpenSW;
    QLabel *doorLock_closeSW;
    QSlider *horizontalSlider_waterPumpSlider;
    QLabel *Qlabel_IPADDRESS;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QPushButton *backButton;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *slider_waterPump;
    QLabel *slider_doorLockMotor;
    QLabel *isWaterValid;
    QCheckBox *checkBox_pullUp;
    QButtonGroup *buttonGroup_2;
    QButtonGroup *buttonGroup;

    void setupUi(QWidget *ControlPanel)
    {
        if (ControlPanel->objectName().isEmpty())
            ControlPanel->setObjectName(QStringLiteral("ControlPanel"));
        ControlPanel->resize(1082, 583);
        ControlPanel->setStyleSheet(QLatin1String("QPushButton {\n"
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
        pushButton_bulbs = new QPushButton(ControlPanel);
        pushButton_bulbs->setObjectName(QStringLiteral("pushButton_bulbs"));
        pushButton_bulbs->setGeometry(QRect(70, 30, 131, 71));
        pushButton_hotBulbs = new QPushButton(ControlPanel);
        pushButton_hotBulbs->setObjectName(QStringLiteral("pushButton_hotBulbs"));
        pushButton_hotBulbs->setGeometry(QRect(70, 170, 131, 71));
        pushButton_PDLC = new QPushButton(ControlPanel);
        pushButton_PDLC->setObjectName(QStringLiteral("pushButton_PDLC"));
        pushButton_PDLC->setGeometry(QRect(60, 340, 131, 71));
        pushButton_waterPump = new QPushButton(ControlPanel);
        pushButton_waterPump->setObjectName(QStringLiteral("pushButton_waterPump"));
        pushButton_waterPump->setGeometry(QRect(330, 220, 131, 71));
        pushButton_doorMotor = new QPushButton(ControlPanel);
        pushButton_doorMotor->setObjectName(QStringLiteral("pushButton_doorMotor"));
        pushButton_doorMotor->setGeometry(QRect(660, 220, 301, 141));
        horizontalSlider_doorLock = new QSlider(ControlPanel);
        horizontalSlider_doorLock->setObjectName(QStringLiteral("horizontalSlider_doorLock"));
        horizontalSlider_doorLock->setGeometry(QRect(660, 130, 301, 68));
        horizontalSlider_doorLock->setStyleSheet(QLatin1String(".QSlider::groove:horizontal {\n"
"    border: 1px solid #2565AE;\n"
"    background: #66D3FA;\n"
"    height: 5px;\n"
"    margin: 0 12px;\n"
"}\n"
"\n"
".QSlider::handle:horizontal {\n"
"    background: #3C99DC;\n"
"    border: 5px solid #3C99DC;\n"
"    width: 23px;\n"
"    height: 100px;\n"
"    margin: -24px -12px;\n"
"}"));
        horizontalSlider_doorLock->setMaximum(100);
        horizontalSlider_doorLock->setOrientation(Qt::Horizontal);
        doorLock_OpenSW = new QLabel(ControlPanel);
        doorLock_OpenSW->setObjectName(QStringLiteral("doorLock_OpenSW"));
        doorLock_OpenSW->setGeometry(QRect(660, 370, 301, 51));
        doorLock_OpenSW->setAlignment(Qt::AlignCenter);
        doorLock_closeSW = new QLabel(ControlPanel);
        doorLock_closeSW->setObjectName(QStringLiteral("doorLock_closeSW"));
        doorLock_closeSW->setGeometry(QRect(660, 430, 301, 51));
        doorLock_closeSW->setAlignment(Qt::AlignCenter);
        horizontalSlider_waterPumpSlider = new QSlider(ControlPanel);
        horizontalSlider_waterPumpSlider->setObjectName(QStringLiteral("horizontalSlider_waterPumpSlider"));
        horizontalSlider_waterPumpSlider->setGeometry(QRect(330, 130, 131, 51));
        horizontalSlider_waterPumpSlider->setStyleSheet(QLatin1String(".QSlider::groove:horizontal {\n"
"    border: 1px solid #2565AE;\n"
"    background: #66D3FA;\n"
"    height: 5px;\n"
"    margin: 0 12px;\n"
"}\n"
"\n"
".QSlider::handle:horizontal {\n"
"    background: #3C99DC;\n"
"    border: 5px solid #3C99DC;\n"
"    width: 23px;\n"
"    height: 100px;\n"
"    margin: -24px -12px;\n"
"}"));
        horizontalSlider_waterPumpSlider->setMaximum(100);
        horizontalSlider_waterPumpSlider->setOrientation(Qt::Horizontal);
        Qlabel_IPADDRESS = new QLabel(ControlPanel);
        Qlabel_IPADDRESS->setObjectName(QStringLiteral("Qlabel_IPADDRESS"));
        Qlabel_IPADDRESS->setGeometry(QRect(220, 380, 371, 161));
        Qlabel_IPADDRESS->setAlignment(Qt::AlignCenter);
        radioButton = new QRadioButton(ControlPanel);
        buttonGroup = new QButtonGroup(ControlPanel);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(radioButton);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(340, 70, 90, 21));
        radioButton->setChecked(true);
        radioButton_2 = new QRadioButton(ControlPanel);
        buttonGroup->addButton(radioButton_2);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(340, 100, 90, 21));
        radioButton_3 = new QRadioButton(ControlPanel);
        buttonGroup_2 = new QButtonGroup(ControlPanel);
        buttonGroup_2->setObjectName(QStringLiteral("buttonGroup_2"));
        buttonGroup_2->addButton(radioButton_3);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setGeometry(QRect(770, 70, 90, 16));
        radioButton_3->setChecked(true);
        radioButton_4 = new QRadioButton(ControlPanel);
        buttonGroup_2->addButton(radioButton_4);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));
        radioButton_4->setGeometry(QRect(770, 110, 90, 16));
        checkBox = new QCheckBox(ControlPanel);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(650, 20, 191, 20));
        checkBox_2 = new QCheckBox(ControlPanel);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setGeometry(QRect(870, 20, 191, 20));
        backButton = new QPushButton(ControlPanel);
        backButton->setObjectName(QStringLiteral("backButton"));
        backButton->setGeometry(QRect(10, 530, 111, 41));
        pushButton = new QPushButton(ControlPanel);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(440, 22, 131, 31));
        pushButton_2 = new QPushButton(ControlPanel);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(440, 60, 131, 31));
        slider_waterPump = new QLabel(ControlPanel);
        slider_waterPump->setObjectName(QStringLiteral("slider_waterPump"));
        slider_waterPump->setGeometry(QRect(360, 190, 71, 21));
        slider_waterPump->setAlignment(Qt::AlignCenter);
        slider_doorLockMotor = new QLabel(ControlPanel);
        slider_doorLockMotor->setObjectName(QStringLiteral("slider_doorLockMotor"));
        slider_doorLockMotor->setGeometry(QRect(770, 190, 71, 21));
        slider_doorLockMotor->setAlignment(Qt::AlignCenter);
        isWaterValid = new QLabel(ControlPanel);
        isWaterValid->setObjectName(QStringLiteral("isWaterValid"));
        isWaterValid->setGeometry(QRect(330, 310, 131, 51));
        isWaterValid->setAlignment(Qt::AlignCenter);
        checkBox_pullUp = new QCheckBox(ControlPanel);
        checkBox_pullUp->setObjectName(QStringLiteral("checkBox_pullUp"));
        checkBox_pullUp->setGeometry(QRect(350, 550, 191, 20));

        retranslateUi(ControlPanel);

        QMetaObject::connectSlotsByName(ControlPanel);
    } // setupUi

    void retranslateUi(QWidget *ControlPanel)
    {
        ControlPanel->setWindowTitle(QApplication::translate("ControlPanel", "Control Panel", nullptr));
        pushButton_bulbs->setText(QApplication::translate("ControlPanel", "\354\240\204\352\265\254", nullptr));
        pushButton_hotBulbs->setText(QApplication::translate("ControlPanel", "\354\227\264\354\240\204\352\265\254", nullptr));
        pushButton_PDLC->setText(QApplication::translate("ControlPanel", "PDLC", nullptr));
        pushButton_waterPump->setText(QApplication::translate("ControlPanel", "\353\254\274\355\216\214\355\224\204", nullptr));
        pushButton_doorMotor->setText(QApplication::translate("ControlPanel", "\353\217\204\354\226\264\353\235\275 \353\252\250\355\204\260", nullptr));
        doorLock_OpenSW->setText(QApplication::translate("ControlPanel", "\353\217\204\354\226\264\353\235\275 \354\227\264\353\246\274\352\260\220\354\247\200 \354\212\244\354\234\204\354\271\230", nullptr));
        doorLock_closeSW->setText(QApplication::translate("ControlPanel", "\353\217\204\354\226\264\353\235\275 \353\213\253\355\236\230\352\260\220\354\247\200 \354\212\244\354\234\204\354\271\230", nullptr));
        Qlabel_IPADDRESS->setText(QApplication::translate("ControlPanel", "Qlabel_IPADDRESS", nullptr));
        radioButton->setText(QApplication::translate("ControlPanel", "\354\210\234\353\260\251\355\226\245", nullptr));
        radioButton_2->setText(QApplication::translate("ControlPanel", "\354\227\255\353\260\251\355\226\245", nullptr));
        radioButton_3->setText(QApplication::translate("ControlPanel", "\354\210\234\353\260\251\355\226\245", nullptr));
        radioButton_4->setText(QApplication::translate("ControlPanel", "\354\227\255\353\260\251\355\226\245", nullptr));
        checkBox->setText(QApplication::translate("ControlPanel", "ignore_openSW", nullptr));
        checkBox_2->setText(QApplication::translate("ControlPanel", "ignore_closeSW", nullptr));
        backButton->setText(QApplication::translate("ControlPanel", "\353\217\214\354\225\204\352\260\200\352\270\260", nullptr));
        pushButton->setText(QApplication::translate("ControlPanel", "STOP CH_TIMER", nullptr));
        pushButton_2->setText(QApplication::translate("ControlPanel", "START CH_TIMER", nullptr));
        slider_waterPump->setText(QApplication::translate("ControlPanel", "100%", nullptr));
        slider_doorLockMotor->setText(QApplication::translate("ControlPanel", "100%", nullptr));
        isWaterValid->setText(QApplication::translate("ControlPanel", "\353\254\274 \352\260\220\354\247\200", nullptr));
        checkBox_pullUp->setText(QApplication::translate("ControlPanel", "PULL-UP", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ControlPanel: public Ui_ControlPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLPANEL_H
