#ifndef LOGWINDOW_H
#define LOGWINDOW_H

#include <QWidget>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QTimer>
#include "dbmanager.h"

namespace Ui {
class logwindow;
}

class logwindow : public QWidget
{
    Q_OBJECT

public:
    explicit logwindow(dbmanager *db, QWidget *parent = nullptr);
    ~logwindow();
    void close();

private slots:
    void show_records();

private:
    Ui::logwindow *ui;
    dbmanager *baza = nullptr;
};

#endif // LOGWINDOW_H
