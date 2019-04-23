#include "pumpdialog.h"
#include "ui_pumpdialog.h"

pumpDialog::pumpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pumpDialog)
{
    ui->setupUi(this);
    connect(ui->okButton, SIGNAL(clicked()),this,SLOT(accept()));
    connect(ui->cancelButton, SIGNAL(clicked()),this,SLOT(reject));

}

pumpDialog::~pumpDialog()
{
    delete ui;
}

QString pumpDialog::getName()
{
    return ui->nameLineEdit->text();
}

QString pumpDialog::getConc()
{
    return ui->concLineEdit->text();
}

QString pumpDialog::getFeed()
{
    return  ui->feedLineEdit->text();
}

QString pumpDialog::getPump()
{
    return ui->pumpComboBox->currentText();
}
