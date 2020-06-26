#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Status *_status, QWidget *_windows[3]) :
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("System Control Panel");
    windows = _windows;
    status = _status;

    cmd.start("whoami");
    cmd.waitForFinished(); // sets current thread to sleep and waits for pingProcess end
    QString output("The account that ran this program : " + cmd.readAllStandardOutput());
    ui->label->setText(output);


#ifdef SET_RELEASE_MODE
    setWindowState(Qt::WindowFullScreen);
    setCursor(Qt::BlankCursor);
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_backPutton_clicked()
{
    this->setWindowState(Qt::WindowMaximized);
    windows[SECURITY_WINDOW]->show();
    windows[SECURITY_WINDOW]->raise();
    windows[SECURITY_WINDOW]->setWindowState(Qt::WindowFullScreen);
}

void MainWindow::on_shutdownButton_clicked()
{
#ifdef __linux__
    QProcess::execute("sudo shutdown now");
#endif
}

void MainWindow::on_rebootButton_clicked()
{
#ifdef __linux__
    QProcess::execute("sudo reboot");
#endif
}

void MainWindow::on_Exit_Program_clicked()
{
    status->stopWhile = true;
#ifdef __linux__
    // set Pin Power off
    gpioWrite(BUBL1, RELAY_SW_PIN_LOW);
    gpioWrite(BUBL2, RELAY_SW_PIN_LOW);
    gpioWrite(BUBL3, RELAY_SW_PIN_LOW);
    gpioWrite(BUBL4, RELAY_SW_PIN_LOW);


    gpioWrite(HOT_BUBL1, RELAY_SW_PIN_LOW);
    gpioWrite(HOT_BUBL2, RELAY_SW_PIN_LOW);
    gpioWrite(HOT_BUBL3, RELAY_SW_PIN_LOW);

    gpioWrite(PDLC_PIN, RELAY_SW_PIN_LOW);

    gpioWrite(WATER_PUMP_FB_SIGNAL, status->PIN_LOW);
    gpioWrite(WATER_PUMP_PWM, status->PIN_LOW);


    gpioWrite(DOORLOC_MOTOR_FB_SIGNAL, status->PIN_LOW);
    gpioWrite(DOORLOC_MOTOR_PWM, status->PIN_LOW);

    if(status->fd > -1)
        serClose(status->fd);

    gpioTerminate();
#endif
    exit(0);
}

void MainWindow::on_Update_Program_clicked()
{
    cmd.start("cd /home/pi/doorLock");
    cmd.waitForFinished(); // sets current thread to sleep and waits for pingProcess end

    cmd.start("sudo rm doorLock_System");
    cmd.waitForFinished(); // sets current thread to sleep and waits for pingProcess end


    cmd.start("wget https://github.com/jangsungLee/SmartFarm-IoT-System/raw/master/doorLock_System");
    cmd.waitForFinished(); // sets current thread to sleep and waits for pingProcess end

    cmd.start("chmod +x doorLock_System");
    cmd.waitForFinished(); // sets current thread to sleep and waits for pingProcess end

    cmd.start("sudo reboot");

    //cmd.start("whoami");
    //cmd.waitForFinished(); // sets current thread to sleep and waits for pingProcess end
}
