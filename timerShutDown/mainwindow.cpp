#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    isEnable = false;
    timer = new QTimer();
    time = new QTime();
    ui->textEdit->setEnabled(false);
    checkboxEnable = false;
    ui->statusBar->setEnabled(true);
    in = new QTime();

    connect(timer, SIGNAL(timeout()), SLOT(onTimer()));

    setWindowTitle("Computer ShutDown");
}

void MainWindow::shutDown()
{
    system("shutdown -s -t 0");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_playPause_clicked()
{
    if(isEnable)
    {
        isEnable = false;
        timer->stop();

        ui->playPause->setText("Старт");


    }
    else {
        isEnable = true;
        timer->start(1000);
        ui->playPause->setText("Пауза");
        checkboxEnable = ui->checkBox->isChecked();
    }
}

void MainWindow::onTimer()
{
    if(checkboxEnable)
    {
        if(ui->timeEdit->time().hour() == 0 && ui->timeEdit->time().minute() == 0
                && ui->timeEdit->time().second() == 0)
            shutDown();


        int seconds = ui->timeEdit->time().second();
        int minutes = ui->timeEdit->time().minute();
        int hours = ui->timeEdit->time().hour();
        if(seconds == 0)
        {
            if(minutes == 0)
                time->setHMS(hours - 1, 59, 59);
            else time->setHMS(hours, minutes - 1, 59);

            ui->timeEdit->setTime(*time);
        }

        else
        {
            time->setHMS(hours, minutes, seconds - 1);
            ui->timeEdit->setTime(*time);
        }
        ui->statusBar->showMessage("Компьютер выключится через " + ui->timeEdit->time().toString("HH:mm:ss"));
    }

    else
    {
        ui->statusBar->showMessage("Компьютер выключится в " + ui->timeEdit->time().toString("HH:mm:ss"));
        if(ui->timeEdit->time().hour() == QTime::currentTime().hour() &&
                ui->timeEdit->time().minute() == QTime::currentTime().minute() &&
                ui->timeEdit->time().second() == QTime::currentTime().second())
            shutDown();
    }


}
