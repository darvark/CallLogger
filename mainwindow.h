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
    Ui::MainWindow *ui;
    QLabel* vfo_frequency = nullptr;
    QDateTime* datetime = nullptr;
    QTimer* timer = nullptr;
    QFile* file_pointer = nullptr;
    configuration* konf = nullptr;
    logwindow* logw = nullptr;
    QLabel* godzina = nullptr;
    dbmanager* db = nullptr;
    QLabel* data = nullptr;
    QLabel* mode = nullptr;
    cbr* cabrillo = nullptr;
    RIG* r = nullptr;
    
    QString serial_port;
    QString log_dbname;
    params cfg_params;
    comcfg com_params;
    rig_params rig;
    int rig_model;
    config cfg;
    bool czy_stala_wymiana;

    bool run_mode = true; // default mode is run
    bool sandp_mode = false; // default mode is run
    bool rig_connection = false;
    QString configFile = "contest_logger.conf";

    void oblicz_moja_wymiane(bool, QString&);
};

#endif // MAINWINDOW_H
