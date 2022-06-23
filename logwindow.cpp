#include "logwindow.h"
#include "ui_logwindow.h"

logwindow::logwindow(dbmanager *db, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::logwindow),
    baza(db)
{
    ui->setupUi(this);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(show_records()));
    timer->start(100);
}

logwindow::~logwindow()
{
    delete ui;
}

void logwindow::close()
{
    QWidget::close();
}

void logwindow::show_records()
{
    if(baza->isOpen())
        ui->logbrowser->setHtml(baza->printAllRecords());
    else
        ui->logbrowser->setHtml(QString(""));
}
