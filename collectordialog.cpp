#include "collectordialog.h"
#include "ui_collectordialog.h"

collectorDialog::collectorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::collectorDialog)
{
    ui->setupUi(this);
    connect(ui->okButton, SIGNAL(clicked()),this,SLOT(accept()));
}

collectorDialog::~collectorDialog()
{
    delete ui;
}
