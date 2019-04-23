#ifndef REACTORDIALOG_H
#define REACTORDIALOG_H

#include <QDialog>

namespace Ui {
class reactorDialog;
}

class reactorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit reactorDialog(QWidget *parent = nullptr);
    ~reactorDialog();

    QString getTemper();
    QString getCoil();

private:
    Ui::reactorDialog *ui;
};

#endif // REACTORDIALOG_H
