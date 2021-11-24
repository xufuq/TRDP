#include "selectdialog.h"
#include "ui_selectdialog.h"

SelectDialog::SelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectDialog)
{
    ui->setupUi(this);
}

SelectDialog::~SelectDialog()
{
    delete ui;
}

void SelectDialog::on_video_clicked()
{
    emit sendMode(4);
    this->close();
}


void SelectDialog::on_notification_clicked()
{
    emit sendMode(0);
    this->close();
}


void SelectDialog::on_ETB_clicked()
{
    emit sendMode(3);
    this->close();
}


void SelectDialog::on_reply_clicked()
{
    emit sendMode(1);
    this->close();
}


void SelectDialog::on_confirm_clicked()
{
    emit sendMode(2);
    this->close();
}


void SelectDialog::on_history_clicked()
{
    emit sendMode(5);
    this->close();
}

