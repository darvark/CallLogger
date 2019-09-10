#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    cfg.save_settings("SP6MI", "test.db", "MOAB", 220, "/dev/ttyUSB0");

    cfg.load_settings(&cfg_params);
    log_dbname = cfg_params.dbfile;
    serial_port = cfg_params.serial;
    open_rig(r, serial_port.toStdString().c_str());

    //    odczekanie 0.1s od uruchomienia palikacji do pokazania aktualnej daty, oswiezanie na biezaco
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    connect(timer, SIGNAL(timeout()), this, SLOT(showDate()));

    timer->start(100);

//  aktualna czestotliwosc
    connect(timer, SIGNAL(timeout()), this, SLOT(showFreq()));

//  upewnienie sie ze znak bedzie zawsze duzymi literami
    connect(ui->callsign, SIGNAL(textChanged(const QString &)), this, SLOT(toUpper(const QString &)));
}

MainWindow::~MainWindow()
{
    close_rig(r);
    delete ui;
}

void MainWindow::on_addbutton_clicked()
{
    QString call = ui->callsign->text();
    int rst_s = ui->rstsend->text().toInt();
    int rst_r = ui->rstrecv->text().toInt();
    QString exch = ui->exchange->text();

    QString godz = QDateTime::currentDateTime().toUTC().toString("h:mm:ss ");
    QString dzis = QDate::currentDate().toString("yyyy/MM/dd");

    database* d = new database();

    double czestotliwosc = rig.freq;
    qDebug() << czestotliwosc;
    QString tryb = rig.mode;
    d->insert_data(log_dbname, call, czestotliwosc, tryb, dzis, godz, rst_s, rst_r, exch);
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
    logw = new logwindow();
    logw->show();
}

void MainWindow::on_quitbutton_clicked()
{
    QWidget::close();
}

void MainWindow::on_run_stateChanged(int arg1)
{
    if (arg1)
    {
        if (sandp_mode && !run_mode)
        {
            sandp_mode = false;
            run_mode = true;
            ui->run->setCheckState(Qt::Checked);
            ui->searchandwork->setCheckState(Qt::Unchecked);
        }
    }
    else
    {
        sandp_mode = true;
        run_mode = false;
        ui->run->setCheckState(Qt::Unchecked);
        ui->searchandwork->setCheckState(Qt::Checked);
    }
}

void MainWindow::on_searchandwork_stateChanged(int arg1)
{
    if (arg1)
    {
        if (!sandp_mode && run_mode)
        {
            sandp_mode = true;
            run_mode = false;
            ui->run->setCheckState(Qt::Unchecked);
            ui->searchandwork->setCheckState(Qt::Checked);
        }
    }
    else
    {
        sandp_mode = false;
        run_mode = true;
        ui->run->setCheckState(Qt::Checked);
        ui->searchandwork->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::showTime()
{
    ui->godzina->setText(QDateTime::currentDateTime().toUTC().toString("h:mm:ss "));
}

void MainWindow::showDate()
{
    ui->data->setText(QDate::currentDate().toString("yyyy/MM/dd"));
}

void MainWindow::toUpper(const QString &text)
{
    QLineEdit *le = qobject_cast<QLineEdit *>(sender());
    if (!le)
        return;
    le->setText(text.toUpper());
}

void MainWindow::on_actionZako_cz_triggered()
{
    QWidget::close();
}

void MainWindow::on_actionNowy_2_triggered()
{
//   zaimplementowac
//    f = new QFile();
//    //create new log and new database
//    f->setFileName(*log_dbname);
//    f->open(QIODevice::ReadWrite);
}

void MainWindow::on_actionZapisz_triggered()
{
    //zapisz log do pliku
    QFileDialog::getSaveFileName(this, tr("Zapisz plik"), QDir::currentPath(), tr("DB files (*.db, *.*)"));
}

void MainWindow::on_actionOtw_rz_triggered()
{
    //optworz baze danych
    QString dbfile = QFileDialog::getOpenFileName(this, tr("Otwórz plik bazy"), QDir::currentPath(), tr("DB files (*.db, *.*)"));
    //przekazac dbfile do handlera bazy danych
}

void MainWindow::showFreq()
{
    fetch_rig_params(r, serial_port.toStdString().c_str(), &rig);
    QString cz = QString().setNum(int(rig.freq));
    QString cz2 = cz.chopped(3) + "." + cz.right(3);
    ui->czestotliwosc->setText(cz2);
    ui->tryb->setText(rig.mode);
    ui->vfo_show->setText(rig.vfo);
}
