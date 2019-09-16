#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::set_default_rst()
{
    if (QString().compare(cfg_params.mode, QString("SSB"), Qt::CaseInsensitive))
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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    pobranie konfiguracji z menu konfiguracja jesli nie istnieje w pliku
    if (QFileInfo::exists(configFile))
    {
//    wczytanie pliku
        cfg.load_settings(&cfg_params, configFile);
    }
    else
    {
//    pokazuje okno konfiguracji
        konf = new konfiguracja();
        konf->exec();

        cfg.load_settings(&cfg_params, configFile);
    }

//    konfiguracja.(&cfg_params);
    log_dbname = cfg_params.dbfile;
    serial_port = cfg_params.serial;

        qDebug() << log_dbname;
 //   tworzy obiekt bazy danych
    static const QString path = log_dbname;

    db = new dbmanager(path);
    if (db->isOpen())
    {
        db->createTable();
    }

//    domyslna wartosc raportu zaleznie od modulacji
    set_default_rst();

//    odczekanie 0.1s od uruchomienia palikacji do pokazania aktualnej daty, oswiezanie na biezaco
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    connect(timer, SIGNAL(timeout()), this, SLOT(showDate()));

    timer->start(100);

//  pokazywanie aktualnej czestotliwosci, modulacji i VFO
    connect(timer, SIGNAL(timeout()), this, SLOT(showFreq()));

//  upewnienie sie ze znak i wymiana bedzie zawsze duzymi literami
    connect(ui->callsign, SIGNAL(textChanged(const QString &)), this, SLOT(toUpper(const QString &)));
    connect(ui->exchange, SIGNAL(textChanged(const QString &)), this, SLOT(toUpper(const QString &)));
}

MainWindow::~MainWindow()
{
    if (polaczenie)
        close_rig(r); //zamykanie polaczenia z radiem
    delete ui;
}

// implementacja nacisniecia przycisku dodaj wpis
// jesli nie ma podanego znaku nie wykona dodania do bazy
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
    if (call.length() != 0)
        db->addrecord(call, czestotliwosc, tryb, dzis, godz, rst_s, rst_r, exch);

//    czyszczenie okien po dodaniu
    ui->callsign->clear();
    set_default_rst();
    ui->exchange->clear();
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

// pokazuje okno z logiem z bazy danych
void MainWindow::on_logbutton_clicked()
{
    //show log
    logw = new logwindow(db);
    logw->show();
    qDebug() << db->printAllRecords();
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
    else
    {
        {
            ui->czestotliwosc->setText("14000.00");
            ui->tryb->setText("SSB");
            ui->vfo_show->setText("A");
        }
    }
}

void MainWindow::on_actionUstawienia_triggered()
{
    konf = new konfiguracja();
    konf->show();
}

void MainWindow::on_actionPo_cz_triggered()
{
    //polacz z radiem wykonaj rig_init
//    sutaw flage
    qDebug() << "poczatek funkcji";
    qDebug() << cfg_params.serial.isEmpty() << " " << cfg_params.rig;
    if (!cfg_params.serial.isEmpty() && cfg_params.rig != 0)
    {
        qDebug() << "init rig" << cfg_params.rig << " " << cfg_params.serial;
        r = init_rig(cfg_params.rig, cfg_params.serial.toStdString().c_str());

    //    ustanowienie polaczenia z radiem
    //    jak sie  nie uda to okno infomacji i flaga ustawiona na false
    //    bedzie zapisywac domyslne wartosci
        if (open_rig(r, cfg_params.serial.toStdString().c_str()))
        {
            polaczenie = true;
        }
        else
        {
            QMessageBox::warning(this, "Błąd komunikacji z radiem","Nie udało się ustanowić połączenia z radiem."
                                                                   "Sprawdz port oraz typ radia w pliku konfiguracyjnym");
            polaczenie = false;
        }
    }
}

void MainWindow::on_actionAutor_triggered()
{
    QString mnie = "Marcin SP6MI Iwaniuk\n"
                   "sp6mi@protonmail.com";
    QMessageBox::about(this, "O mnie", mnie);
}

void MainWindow::on_actionInformacja_triggered()
{
    QString program = "Prosty program do logowania łączności w zawodach.\n"
                        "Komunikacja z TRX oparta na bibliotece hamlib.";
    QMessageBox::about(this, "O programie", program);
}

bool MainWindow::check_serial_port()
{
    QString currentPortName;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        currentPortName = info.systemLocation();
    }

    return true;
}

QString MainWindow::find_serial_port()
{
    return "";
}

void MainWindow::on_actionRoz_cz_triggered()
{
    if (polaczenie)
    {
        rig_close(r);
    }
}
