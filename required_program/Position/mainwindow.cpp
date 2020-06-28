#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(status *_share, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    share = _share;

    m_pTimer = new QTimer();
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(OnTimerCallbackFunc()));
    m_pTimer->start(120);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OnTimerCallbackFunc()
{
    if(share->ConnectedClient.count() != isChecked)
    {
        isChecked = share->ConnectedClient.count();
        model->setStringList(share->ConnectedClient);

        ui->listView->setModel(model);

        qDebug() << share->ConnectedClient[0];
    }

}
