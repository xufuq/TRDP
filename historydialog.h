#ifndef HISTORYDIALOG_H
#define HISTORYDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QHeaderView>
#include <QMessageBox>
#include <QDebug>

namespace Ui {
class HistoryDialog;
}

class HistoryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HistoryDialog(QWidget *parent = nullptr);
    ~HistoryDialog();

private slots:
    void on_AskButton_clicked();

private:
    Ui::HistoryDialog *ui;

    QSqlDatabase db;
    QSqlQuery query;
    QSqlTableModel *model=nullptr;
};

#endif // HISTORYDIALOG_H
