#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <QLabel>
#include <QDate>
#include <QTimer>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QtSerialPort/QSerialPortInfo>

#include "logwindow.h"
#include "dbmanager.h"
#include "konfiguracja.h"
#include "rig.h"
#include "config.h"
#include "cbr.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void set_default_rst();
    bool check_serial_port();
    QString find_serial_port();
    
private slots:
    void on_addbutton_clicked();

    void on_clearbutton_clicked();

    void on_savebutton_clicked();

    void on_logbutton_clicked();

    void on_quitbutton_clicked();

    void on_run_stateChanged(int arg1);

    void on_searchandwork_stateChanged(int arg1);

    void showTime();

    void showDate();

    void showFreq();

    void toUpper(const QString &text);

    void on_actionZakoncz_triggered();

    void on_actionNowy_2_triggered();

    void on_actionZapisz_triggered();

    void on_actionOtworz_triggered();

    void on_actionUstawienia_triggered();

    void on_actionPolacz_triggered();

    void on_actionAutor_triggered();

    void on_actionInformacja_triggered();

    void on_actionRozlacz_triggered();

private:
    QLabel *czestotliwosc;
    QDateTime *datetime;
    QFile *file_pointer;
    QString serial_port;
    Ui::MainWindow *ui;
    konfiguracja *konf;
    QString log_dbname;
    params cfg_params;
    logwindow * logw;
    int moja_wymiana;
    QLabel *godzina;
    rig_params rig;
    dbmanager *db;
    cbr *cabrillo;
    int rig_model;
    QLabel *data;
    QLabel *tryb;
    config cfg;
    RIG* r;

    bool run_mode = true; // default mode is run
    bool sandp_mode = false; // default mode is run
    bool polaczenie = false;
    QString configFile = "contest_logger.conf";

    int oblicz_moja_wymiane(bool wymiana, int wymiana_wzor);
};

#endif // MAINWINDOW_H
