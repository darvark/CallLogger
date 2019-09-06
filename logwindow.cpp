#include "logwindow.h"
#include "ui_logwindow.h"

logwindow::logwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::logwindow)
{
    ui->setupUi(this);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(readFile()));
    timer->start(100);
}

logwindow::~logwindow()
{
    delete ui;
}

void logwindow::readFile()
{
    ui->logbrowser->setText("Abrakadabra");
}
