#include "konfiguracja.h"
#include "ui_konfiguracja.h"

konfiguracja::konfiguracja(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::konfiguracja)
{
    ui->setupUi(this);
}

konfiguracja::~konfiguracja()
{
    delete ui;
}
