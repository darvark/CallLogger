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
#include "database.h"
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

    void toUpper(const QString &text);

    void on_actionZako_cz_triggered();

    void on_actionNowy_2_triggered();

    void on_actionZapisz_triggered();

    void on_actionOtw_rz_triggered();

    bool checkDBselected();
private:
    Ui::MainWindow *ui;
    logwindow * logw;
    QLabel *data;
    QLabel *godzina;
    QDateTime *datetime;

    bool run_mode = true; // default mode is run
    bool sandp_mode = false; // default mode is run
    QString *log_dbname = nullptr;
    rig_query *r = new rig_query();
    RIG *rg;
    QFile *f;
    config cfg;
    params p;
    int rig_model;
};

#endif // MAINWINDOW_H
