#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDebug>
#include <QTime>
#include <QMessageBox>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void shutDown();
    ~MainWindow();

private slots:
    void on_playPause_clicked();
    void onTimer();

private:
    Ui::MainWindow *ui;
    bool isEnable, checkboxEnable;
    QTimer *timer;
    QTime *time, *in;
    int currTime;

};

#endif // MAINWINDOW_H
