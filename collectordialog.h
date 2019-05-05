#ifndef COLLECTORDIALOG_H
#define COLLECTORDIALOG_H

#include <QDialog>

namespace Ui {
class collectorDialog;
}

class collectorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit collectorDialog(QWidget *parent = nullptr);
    ~collectorDialog();

    QString getTable();

private:
    Ui::collectorDialog *ui;
};

#endif // COLLECTORDIALOG_H
