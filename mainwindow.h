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

    void on_actionZako_cz_triggered();

    void on_actionNowy_2_triggered();

    void on_actionZapisz_triggered();

    void on_actionOtw_rz_triggered();

    void on_actionUstawienia_triggered();

    void on_actionPo_cz_triggered();

    void on_actionAutor_triggered();

    void on_actionInformacja_triggered();

    void on_actionRoz_cz_triggered();

private:
    Ui::MainWindow *ui;
    logwindow * logw;
    konfiguracja *konf;
    QLabel *data;
    QLabel *godzina;
    QLabel *czestotliwosc;
    QLabel *tryb;
    QDateTime *datetime;

    QString log_dbname;
    QString serial_port;
    QFile *file_pointer;
    config cfg;
    params cfg_params;
    int rig_model;
    int moja_wymiana = 1;

    dbmanager *db;

    rig_params rig;
    RIG* r;
    bool run_mode = true; // default mode is run
    bool sandp_mode = false; // default mode is run
    bool polaczenie = false;
    QString configFile = "contest_logger.conf";

    void oblicz_moja_wymiane(bool wymiana, QString wymiana_wzor);
};

#endif // MAINWINDOW_H
