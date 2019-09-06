#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <QLabel>
#include <QDate>
#include <QTimer>

#include "logwindow.h"

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

private:
    Ui::MainWindow *ui;
    logwindow * logw;
    QLabel *data;
    QLabel *godzina;
    QDateTime *datetime;

    bool run_mode = true; // default mode is run
    bool sandp_mode = false; // default mode is run
};

#endif // MAINWINDOW_H
