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
    timer->start(100);

    checkDBselected();
//    cfg.save_settings("sp6mi", "test.db", "MOBA");

    connect(ui->callsign, SIGNAL(textChanged(const QString &)), this, SLOT(toUpper(const QString &)));
}

// check if db is selected, and pop-up if not
bool MainWindow::checkDBselected()
{
    const char* msg = "Plik bazy danych nie został wybrany.";
    const char* msg2 = "\nProszę utworzyć nową bazę lub wybrać istniejącą";
    if (!log_dbname)
    {
        //pop up message
        QMessageBox::warning(this,tr(msg), tr(msg2));
        cfg.save_settings("SP6MI", "test.db", "MOAB", 220); //220 is Kenwood TS-480
        QMessageBox::information(this,tr("Nowa konfiguracja"), tr("Domyślna konfiguracja została wczytana"));
    }
    else
    {
        p = cfg.load_settings();
        log_dbname = &p.dbfile;
        rig_model = p.rig;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addbutton_clicked()
{
    if (checkDBselected())
    {
        QString call = ui->callsign->text();
        int rst_s = ui->rstsend->text().toInt();
        int rst_r = ui->rstrecv->text().toInt();
        QString exch = ui->exchange->text();

        QString godz = QDateTime::currentDateTime().toUTC().toString("h:mm:ss ");
        QString dzis = QDate::currentDate().toString("yyyy/MM/dd");

        database* d = new database();
        const char* serial = "/dev/ttyuSB0";

        rg = r->init_rig(rig_model, serial);

        r->fetch_vfo(rg, serial);
        double czestotliwosc = r->fetch_freq(rg, serial);
        QString tryb = r->fetch_mode(rg, serial);

        d->insert_data(*log_dbname, call, czestotliwosc, tryb, dzis, godz, rst_s, rst_r, exch);
    }
    else
    {
//        connect(this, SIGNAL(), this, SLOT(on_actionNowy_2_triggered()));
    }
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
