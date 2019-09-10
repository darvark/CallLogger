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
#include <QMessageBox>

#include "logwindow.h"
#include "dbmanager.h"
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

//    bool checkDBselected();
private:
    Ui::MainWindow *ui;
    logwindow * logw;
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

    dbmanager *db;

    rig_params rig;
    RIG* r = init_rig(228, "/dev/ttyUSB0");

    bool run_mode = true; // default mode is run
    bool sandp_mode = false; // default mode is run

    bool polaczenie = true;
};

#endif // MAINWINDOW_H
