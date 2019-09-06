#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    connect(timer, SIGNAL(timeout()), this, SLOT(showDate()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addbutton_clicked()
{
    //add new record to database
}

void MainWindow::on_clearbutton_clicked()
{
    //clear entry before save/add
    ui->callsign->clear();
    ui->rstrecv->clear();
    ui->rstsend->clear();
    ui->exchange->clear();
}

void MainWindow::on_savebutton_clicked()
{
    //save to logfile, not to db
}

void MainWindow::on_logbutton_clicked()
{
    //show log
}

void MainWindow::on_quitbutton_clicked()
{
    QWidget::close();
}

void MainWindow::on_run_stateChanged(int arg1)
{
    //set as run mode
    //zaznaczyc to w logu
    //odznaczyc S&P
}

void MainWindow::on_searchandwork_stateChanged(int arg1)
{
    //set as S&P mode
    //zaznaczyc to w logu
    //odznaczyc RUN
}

//ui->frequency->display("987");
// this is how to display something.
void MainWindow::showTime()
{
    ui->godzina->setText(QDateTime::currentDateTime().toUTC().toString("h:mm:ss "));
}

void MainWindow::showDate()
{
    ui->data->setText(QDate::currentDate().toString("yyyy/MM/dd"));
}
