#ifndef PUMPDIALOG_H
#define PUMPDIALOG_H

#include <QDialog>

namespace Ui {
class pumpDialog;
}

class pumpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit pumpDialog(QWidget *parent = nullptr);
    ~pumpDialog();

private:
    Ui::pumpDialog *ui;
};

#endif // PUMPDIALOG_H
