#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QStringListModel>
#include "status.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void OnTimerCallbackFunc();
public:
    MainWindow(status *_share, QWidget *parent = nullptr);
    ~MainWindow();
    status *share;
    QTimer *m_pTimer;
private:
    Ui::MainWindow *ui;
    int isChecked = 0;
    QStringListModel *model = new QStringListModel();
};
#endif // MAINWINDOW_H
