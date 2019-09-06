#ifndef LOGWINDOW_H
#define LOGWINDOW_H

#include <QWidget>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QTimer>

namespace Ui {
class logwindow;
}

class logwindow : public QWidget
{
    Q_OBJECT

public:
    explicit logwindow(QWidget *parent = nullptr);
    ~logwindow();

private slots:
    void readFile();

private:

    Ui::logwindow *ui;
};

#endif // LOGWINDOW_H
