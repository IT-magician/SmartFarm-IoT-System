#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QWidget>
#include <QPalette>
#include <QTimer>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QMessageBox>
#include "status.h"

#ifdef __linux__
#include <pigpio.h>
#endif

namespace Ui {
class ControlPanel;
}

class ControlPanel : public QWidget
{
    Q_OBJECT

public:
    explicit ControlPanel(Status *_status, QWidget *_windows[3], QWidget *parent = nullptr);
    ~ControlPanel();
    QWidget **windows;

    int ButtonControl(QString button_name);
    Status *status;

    void turnOnBulb(void);
    void turnOffBulb(void);
    void turnOnHotBulb(void);
    void turnOffHotBulb(void);
    void turnOnPDLC(void);
    void turnOffPDLC(void);
    void turnOnWaterPump(void);
    void turnOffWaterPump(void);
    void turnOnDoorMotor(void);
    void turnOffDoorMotor(void);

private slots:

    void on_pushButton_bulbs_clicked();

    void on_pushButton_hotBulbs_clicked();

    void on_pushButton_PDLC_clicked();

    void on_pushButton_waterPump_clicked();

    void on_pushButton_doorMotor_clicked();

    void on_horizontalSlider_waterPumpSlider_valueChanged(int value);

    void on_horizontalSlider_doorLock_valueChanged(int value);

    void OnTimerCallbackFunc1();

    void OnTimerCallbackFunc2();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_backButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_checkBox_pullUp_stateChanged(int arg1);

private:
    Ui::ControlPanel *ui;

    QTimer *m_pTimer, *m_pTimer2;
    int CheckCycleTime = CONTROL_PANEL_CHECK_CYCLE_TIME;
    bool isCheckPower_Cycle = true;

};

#endif // CONTROLPANEL_H
