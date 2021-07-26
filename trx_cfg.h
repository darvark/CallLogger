#ifndef TRX_CFG_H
#define TRX_CFG_H

#include <QDialog>

namespace Ui {
class trx_cfg;
}

class trx_cfg : public QDialog
{
    Q_OBJECT

public:
    explicit trx_cfg(QWidget *parent = 0);
    ~trx_cfg();

private:
    Ui::trx_cfg *ui;

    void add_parity(Ui::trx_cfg* ui);
    void add_databits(Ui::trx_cfg* ui);
    void add_stopbits(Ui::trx_cfg* ui);
    void add_baudrate(Ui::trx_cfg* ui);
    void add_dtr(Ui::trx_cfg* ui);
    void add_rts(Ui::trx_cfg* ui);

};

#endif // TRX_CFG_H
