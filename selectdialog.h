#pragma once
#ifndef SELECTDIALOG_H
#define SELECTDIALOG_H

#include <QDialog>

namespace Ui {
class SelectDialog;
}

class SelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectDialog(QWidget *parent = nullptr);
    ~SelectDialog();

private slots:
    void on_video_clicked();

    void on_notification_clicked();

    void on_ETB_clicked();

    void on_reply_clicked();

    void on_confirm_clicked();

    void on_history_clicked();

private:
    Ui::SelectDialog *ui;
signals:
    void sendMode(int mode);
};

#endif // SELECTDIALOG_H
