#ifndef KONFIGURACJA_H
#define KONFIGURACJA_H

#include <QDialog>

namespace Ui {
class konfiguracja;
}

class konfiguracja : public QDialog
{
    Q_OBJECT

public:
    explicit konfiguracja(QWidget *parent = nullptr);
    ~konfiguracja();

private:
    Ui::konfiguracja *ui;
};

#endif // KONFIGURACJA_H
