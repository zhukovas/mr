#include "reactordialog.h"
#include "ui_reactordialog.h"

reactorDialog::reactorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reactorDialog)
{
    ui->setupUi(this);
    connect(ui->okButton, SIGNAL(clicked()),this,SLOT(accept()));
    connect(ui->cancelButton, SIGNAL(clicked()),this,SLOT(reject));
}

reactorDialog::~reactorDialog()
{
    delete ui;
}

QString reactorDialog::getTemper()
{
    return ui->temperLineEdit->text();
}

QString reactorDialog::getCoil()
{
    return ui->coilLineEdit->text();
}
