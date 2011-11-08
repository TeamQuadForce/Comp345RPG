#include "quitdialog.h"
#include "ui_quitdialog.h"

QuitDialog::QuitDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuitDialog)
{
    ui->setupUi(this);
}

QuitDialog::~QuitDialog()
{
    delete ui;
}
