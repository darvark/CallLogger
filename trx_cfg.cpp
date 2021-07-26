#include "trx_cfg.h"
#include "ui_trx_cfg.h"

trx_cfg::trx_cfg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::trx_cfg)
{
    ui->setupUi(this);
}

trx_cfg::~trx_cfg()
{
    delete ui;
}

void trx_cfg::add_baudrate(Ui::trx_cfg *ui)
{
    ui->baudrate_choose->addItem("2400");
    ui->baudrate_choose->addItem("4800");
    ui->baudrate_choose->addItem("9600");
    ui->baudrate_choose->addItem("14400");
    ui->baudrate_choose->addItem("19200");
    ui->baudrate_choose->addItem("28800");
    ui->baudrate_choose->addItem("38400");
    ui->baudrate_choose->addItem("57600");
    ui->baudrate_choose->addItem("115200");
    ui->baudrate_choose->addItem("230400");
}

void trx_cfg::add_databits(Ui::trx_cfg *ui)
{
    ui->databits_choose->addItem("6");
    ui->databits_choose->addItem("7");
    ui->databits_choose->addItem("8");
}

void trx_cfg::add_dtr(Ui::trx_cfg *ui)
{
    ui->dtr_choose->addItem("None");
    ui->dtr_choose->addItem("Low");
    ui->dtr_choose->addItem("High");
    ui->dtr_choose->addItem("Handshake");
}

void trx_cfg::add_rts(Ui::trx_cfg *ui)
{
    ui->rts_choose->addItem("None");
    ui->rts_choose->addItem("High");
    ui->rts_choose->addItem("Low");
    ui->rts_choose->addItem("Handshake");
}

void trx_cfg::add_parity(Ui::trx_cfg *ui)
{
    ui->parity_choose->addItem("Yes");
    ui->parity_choose->addItem("No");
}

void trx_cfg::add_stopbits(Ui::trx_cfg *ui)
{
    ui->stopbits_choose->addItem("1");
    ui->stopbits_choose->addItem("2");
}
