#ifndef VIDEODIALOG_H
#define VIDEODIALOG_H

#include <QDialog>

namespace Ui {
class VideoDialog;
}

class VideoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VideoDialog(QWidget *parent = nullptr);
    ~VideoDialog();
    void VideoShow(QImage *image);

private:
    Ui::VideoDialog *ui;
};

#endif // VIDEODIALOG_H
