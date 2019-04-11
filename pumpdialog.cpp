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
