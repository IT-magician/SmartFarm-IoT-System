#ifndef DOORLOCKSYSTEM_H
#define DOORLOCKSYSTEM_H

#include <QWidget>
#include <QTimer>
#include <stdio.h>
#include "status.h"

#ifdef __linux__
#include <pigpio.h>
#endif

namespace Ui {
class DoorLockSystem;
}

class DoorLockSystem : public QWidget
{
    Q_OBJECT

public:
    explicit DoorLockSystem(Status *_status, QWidget *_windows[3] = nullptr);
    ~DoorLockSystem();

    Ui::DoorLockSystem *ui;
    Status *status;
private slots:
    void on_pushButton_19_clicked();

    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void OnTimerCallbackFunc();

    void OnTimerCallbackFunc1();

private:
    QWidget **windows;
    const char encrypted_character = '*';
    const int display_count = 10, resetTime = 5000/*5s*/, CycleTime = 500;
    int number_index = 0;
    char input_value[MAX_PASSWORD_COUNT] = {0}, display_letters[MAX_PASSWORD_COUNT] = {0};
    const char *systemSetting = "*#0#*", *controllPanel = "*###*", *changePassword = "*123*", *program_exit = "*0000*", *initialPassword = "0000";


    QTimer *m_pTimer, *m_pTimer1/*target : temporary_password*/;

    void Clear();
    void changeInitImage();
};

#endif // DOORLOCKSYSTEM_H
