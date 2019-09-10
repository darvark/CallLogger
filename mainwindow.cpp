#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    wczytanie konfiguracji z pliku
    cfg.load_settings(&cfg_params);
    log_dbname = cfg_params.dbfile;
    serial_port = cfg_params.serial;

//    tworzy obiekt bazy danych
    static const QString path = log_dbname;
    db = new dbmanager(path);
    if (db->isOpen())
    {
// Creates a table if it doens't exist. Otherwise,
// it will use existing table.
        db->createTable();
    }

//    ustanowienie polaczenia z radiem
//    jak sie  nie uda to okno infomacji i flaga ustawiona na false
//    bedzie zapisywac domyslne wartosci
//    TODO: przerobic zeby mozna bylo recznie wpisywac??
    if (open_rig(r, serial_port.toStdString().c_str()))
    {
        polaczenie = true;
        if (rig.mode != "CW")
        {
            // ustawienie domyslnej wartosci raportu
            ui->rstrecv->setText("59");
            ui->rstsend->setText("59");
        }
        else {
            // ustawienie domyslnej wartosci raportu
            ui->rstrecv->setText("599");
            ui->rstsend->setText("599");
        }
    }
    else
    {
        QMessageBox::warning(this, "Błąd komunikacji z radiem","Nie udało się ustanowić połączenia z radiem");
        polaczenie = false;
        // ustawienie domyslnej wartosci raportu
        ui->rstrecv->setText("599");
        ui->rstsend->setText("599");
    }

//    odczekanie 0.1s od uruchomienia palikacji do pokazania aktualnej daty, oswiezanie na biezaco
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    connect(timer, SIGNAL(timeout()), this, SLOT(showDate()));

    timer->start(100);

//  pokazywanie aktualnej czestotliwosci, modulacji i VFO
    connect(timer, SIGNAL(timeout()), this, SLOT(showFreq()));

//  upewnienie sie ze znak bedzie zawsze duzymi literami
    connect(ui->callsign, SIGNAL(textChanged(const QString &)), this, SLOT(toUpper(const QString &)));
}

MainWindow::~MainWindow()
{
    close_rig(r); //zamykanie polaczenia z radiem
    delete ui;
}

void MainWindow::on_addbutton_clicked()
{
    QString tryb;
    double czestotliwosc;

    QString call = ui->callsign->text();
    int rst_s = ui->rstsend->text().toInt();
    int rst_r = ui->rstrecv->text().toInt();
    QString exch = ui->exchange->text();

    QString godz = QDateTime::currentDateTime().toUTC().toString("h:mm:ss ");
    QString dzis = QDate::currentDate().toString("yyyy/MM/dd");


    if (polaczenie)
    {
        czestotliwosc = rig.freq;
        tryb = rig.mode;
    }
    else
    {
        czestotliwosc = 14200.00;
        tryb = "SSB";
    }
    db->addrecord(call, czestotliwosc, tryb, dzis, godz, rst_s, rst_r, exch);
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
    if (polaczenie)
    {
        fetch_rig_params(r, serial_port.toStdString().c_str(), &rig);
        QString cz = QString().setNum(int(rig.freq));
        QString cz2 = cz.chopped(3) + "." + cz.right(3);
        ui->czestotliwosc->setText(cz2);
        ui->tryb->setText(rig.mode);
        ui->vfo_show->setText(rig.vfo);
    }
    else {
        {
            ui->czestotliwosc->setText("14000.00");
            ui->tryb->setText("SSB");
            ui->vfo_show->setText("A");
        }
    }
}
