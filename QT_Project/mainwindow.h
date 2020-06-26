#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>

#include "websocket.h"
#include "status.h"

#ifdef __linux__
#include <pigpio.h>
#endif


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Status *_status, QWidget *_windows[3] = nullptr);
    ~MainWindow();

    WebSocket *websocket;

private slots:
    void on_backPutton_clicked();

    void on_shutdownButton_clicked();

    void on_rebootButton_clicked();

    void on_Exit_Program_clicked();

    void on_Update_Program_clicked();

private:
    Ui::MainWindow *ui;
    QWidget **windows;
    QProcess cmd;
    Status *status;
};

#endif // MAINWINDOW_H
