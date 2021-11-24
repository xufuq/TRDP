#include "videodialog.h"
#include "ui_videodialog.h"
#include <QImage>

VideoDialog::VideoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VideoDialog)
{
    ui->setupUi(this);
}

VideoDialog::~VideoDialog()
{
    delete ui;
}

void VideoDialog::VideoShow(QImage *image)
{
    *image = image->rgbSwapped();
    ui->VideoLabel->setPixmap(QPixmap::fromImage(*image));
}
