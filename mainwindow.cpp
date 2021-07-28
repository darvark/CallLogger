#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (QFileInfo::exists(configFile))
    {
        cfg.load_settings(&cfg_params, &com_params, configFile);
    }
    else
    {
        konf = new configuration();
        konf->exec();

        cfg.load_settings(&cfg_params, &com_params, configFile);
    }

    serial_port = cfg_params.serial;
//    set_comm_param(configFile);
    static const QString path = cfg_params.dbfile;
    db = new dbmanager(path);

    if (db->isOpen())
    {
        db->createTable();
    }

    wzor = cfg_params.pattern.toInt();

    set_default_rst();

/**************************************************************************************************/

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    connect(timer, SIGNAL(timeout()), this, SLOT(showDate()));

    timer->start(100);

//  pass vfo freq
    connect(timer, SIGNAL(timeout()), this, SLOT(showFreq()));

//  capitalics
    connect(ui->callsign, SIGNAL(textChanged(const QString &)), this, SLOT(toUpper(const QString &)));
    connect(ui->wymiana, SIGNAL(textChanged(const QString &)), this, SLOT(toUpper(const QString &)));
    connect(ui->wymiana, SIGNAL(returnPressed()), this, SLOT(on_addbutton_clicked()));
/**************************************************************************************************/
}

void MainWindow::set_default_rst()
{
//  default report for SSB 59
    if (QString().compare(cfg_params.cat_mode, QString("SSB"), Qt::CaseInsensitive))
    {
        ui->rstrecv->setText("599");
        ui->rstsend->setText("599");
    }
    else
    {
        ui->rstrecv->setText("59");
        ui->rstsend->setText("59");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    if (rig_connection)
    {
        close_rig(r);
    }
    delete logw;
    delete mode;
    delete data;
    delete godzina;
    delete konf;
    delete vfo_frequency;
    delete datetime;
    delete file_pointer;
    delete db;
    delete cabrillo;
    delete r;
}

void MainWindow::oblicz_moja_wymiane(bool czy_stala_wymiana, int* wymiana_wartosc)
{
    if (!czy_stala_wymiana)
    {
        *wymiana_wartosc += 1;
    }
}

void MainWindow::on_addbutton_clicked()
{
    ui->callsign->setFocus();
    double czestotliwosc;
    QString tryb;
    oblicz_moja_wymiane(cfg_params.wymiana, &wzor);
    qDebug() << "z addbutton: " << QString::number(wzor);

    QString call = ui->callsign->text();
    int rst_s = ui->rstsend->text().toInt();
    int rst_r = ui->rstrecv->text().toInt();
    QString exch = ui->wymiana->text();

    QString godz = QDateTime::currentDateTime().toUTC().toString("h:mm:ss");
    QString dzis = QDate::currentDate().toString("yyyy/MM/dd");


    if (rig_connection)
    {
        czestotliwosc = rig.freq;
        tryb = rig.mode;
    }
    else
    {
        czestotliwosc = 14.000;
        tryb = cfg_params.cat_mode;
    }

    record_params p;
    p.callsign = call;
    p.date = dzis;
    p.freq = czestotliwosc;
    p.mode = tryb;
    p.time = godz;
    p.rst_r = rst_r;
    p.rst_s = rst_s;
    p.exchange = exch;
    p.moja_exchange = QString::number(wzor);

    if (call.length() != 0)
    {
        db->addrecord(&p);
    }

    ui->callsign->clear();
    set_default_rst();
    ui->wymiana->clear();
}

void MainWindow::on_clearbutton_clicked()
{
    ui->callsign->clear();
    ui->rstrecv->clear();
    ui->rstsend->clear();
    ui->wymiana->clear();
}

void MainWindow::on_savebutton_clicked()
{
        
    cabrillo = new cbr(db, &cfg);
    QString cbrfile = cfg_params.callsign + ".cbr";
    cabrillo->saveFile(cbrfile);
}

void MainWindow::on_logbutton_clicked()
{
    logw = new logwindow(db);
    logw->show();
}

void MainWindow::on_quitbutton_clicked()
{
    if (logw != nullptr)
        logw->close();
    
    QWidget::close();
}

void MainWindow::on_actionZakoncz_triggered()
{
    this->on_quitbutton_clicked();
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
    ui->godzina->setText(QDateTime::currentDateTime().toUTC().toString("h:mm:ss"));
}

void MainWindow::showDate()
{
    ui->data->setText(QDate::currentDate().toString("yyyy/MM/dd"));
}

void MainWindow::toUpper(const QString &text)
{
    QLineEdit *le = qobject_cast<QLineEdit *>(sender());
    if (!le)
    {
        return;
    }
    le->setText(text.toUpper());
}

//przetestowac !!
//  zakladamy nowa baze danych i nowy log
void MainWindow::on_actionNowy_2_triggered()
{
    if(rig_connection)
        close_rig(r);

    cfg.reset(&cfg_params, &com_params);

    konf = new configuration();
    konf->show();

//    pobranie konfiguracji z menu konfiguracja jesli nie istnieje w pliku
    if (QFileInfo::exists(configFile))
    {
//    wczytanie pliku
        cfg.load_settings(&cfg_params, &com_params, configFile);
    }
    else
    {
//    pokazuje okno konfiguracji
        konf = new configuration();
        konf->exec();

        cfg.load_settings(&cfg_params, &com_params,  configFile);
    }

//    konfiguracja.(&cfg_params);
    log_dbname = cfg_params.dbfile;
    serial_port = cfg_params.serial;

 //   tworzy obiekt bazy danych
    static const QString path = log_dbname;
    db = new dbmanager(path);

    if (db->isOpen())
    {
        db->createTable();
    }

    cabrillo = new cbr(db, &cfg);
    set_default_rst();
}

void MainWindow::on_actionZapisz_triggered()
{
    QFileDialog::getSaveFileName(this, tr("Zapisz plik"), QDir::currentPath(), tr("DB files (*.db, *.*)"));
}

void MainWindow::on_actionOtworz_triggered()
{
    QString dbfile = QFileDialog::getOpenFileName(this, tr("Otwórz plik bazy"), QDir::currentPath(), tr("DB files (*.db, *.*)"));
    //TODO: przekazac dbfile do handlera bazy danych
}

void MainWindow::showFreq()
{
    if (rig_connection)
    {
        fetch_rig_params(r, /*serial_port.toStdString().c_str(),*/ &rig);
        QString cz = QString().setNum(int(rig.freq));
        QString cz2 = cz.left(2) + "." + cz.mid(2);
        ui->czestotliwosc->setText(cz2);
        ui->tryb->setText(rig.mode);
        ui->vfo_show->setText(rig.vfo);
    }
    else
    {
        {
            ui->czestotliwosc->setText("14100.00");
            ui->tryb->setText("SSB");
            ui->vfo_show->setText("A");
        }
    }
}

void MainWindow::on_actionUstawienia_triggered()
{
    konf = new configuration();
    konf->show();
}

void MainWindow::on_actionPolacz_triggered()
{
//     qDebug() << "poczatek funkcji";
//     qDebug() << cfg_params.serial.isEmpty() << " " << cfg_params.rig;
    if (!cfg_params.serial.isEmpty() && cfg_params.rig != 0)
    {
        qDebug() << "init rig" << cfg_params.rig << " " << cfg_params.serial;
        r = init_rig(cfg_params.rig, cfg_params.serial.toStdString().c_str());

    //    ustanowienie polaczenia z radiem
    //    jak sie  nie uda to okno infomacji i flaga ustawiona na false
    //    bedzie zapisywac domyslne wartosci
        if (open_rig(r, cfg_params.serial.toStdString().c_str()))
        {
            rig_connection = true;
        }
        else
        {
            QMessageBox::warning(this, "Błąd komunikacji z radiem","Nie udało się ustanowić połączenia z radiem."
                                                                   "Sprawdz port oraz typ radia w pliku konfiguracyjnym");
            rig_connection = false;
        }
    }
}

void MainWindow::on_actionAutor_triggered()
{
    QString mnie = "Marcin Iwaniuk SP6MI\n"
                   "   sp6mi@yahoo.com  \n";
    QMessageBox::about(this, "O mnie", mnie);
}

void MainWindow::on_actionInformacja_triggered()
{
    QString program = "Prosty program do logowania łączności w zawodach.\n"
                      "Komunikacja z TRX oparta na bibliotece hamlib.\n"
                      "Całość napisana z wykorzystaniem bibliotek:\n"
                      "QT5, hamlib, libconfig++, sqlite3\n"
                      "\n"
                      "Autor programu nie ponosi żadnej odpowiedzialności\n"
                      "za uszkodzenia i problemy wynikające z niewłaściwego\n"
                      "użycia niniejszego oprogramowania, lub nieumiejętnego\n"
                      "podłączenia/korzystania z TRX.";
    QMessageBox::about(this, "O programie", program);
}

//bool MainWindow::check_serial_port()
//{
//    QString currentPortName;
//    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
//    {
//        currentPortName = info.systemLocation();
//    }

//    return true;
//}

//QString MainWindow::find_serial_port()
//{
//    return "";
//}

void MainWindow::on_actionRozlacz_triggered()
{
    if (rig_connection)
    {
        rig_close(r);
    }
}
