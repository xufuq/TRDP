#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

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
#include <QString>


namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QSqlDatabase *db, QWidget *parent = nullptr);
    ~LoginDialog();


private:
    Ui::LoginDialog *ui;
    QSqlDatabase *Logindb;

private slots:
    void loginPush();
    void createPush();

signals:
    void loginSuccess(QString name);
};

#endif // LOGINDIALOG_H
