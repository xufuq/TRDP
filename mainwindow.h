#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDateTime>
#include <QTimer>
#include <string>
#include <QFileDialog>
#include <QCoreApplication>

#include "logindialog.h"
#include "selectdialog.h"
#include "paramdialog.h"
#include "historydialog.h"
#include "videodialog.h"

#include "opencv2/core/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/opencv.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class WorkerThread;
class MainWindow;

static MainWindow *myselfMainWindow = NULL;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static MainWindow *getIntance();
    void startWorkInAThread();
    void printStrToUI(QString str);
    void recvMsgStrToUI(QString str);
    void sendMsgResultStrToUI(QString str);
    void sendTestResultStrToUI(QString str);
    uint get_request_reply_TCP_COMID();
    uint get_request_reply_unicast_COMID();
    uint get_request_reply_confirm_TCP_COMID();
    uint get_request_reply_confirm_unicast_COMID();
    int  get_current_mode();

    ETB104 Etb104Param;
    uint8_t Etb106id;
    uint8_t Etb110id;
    ETB130  Etb130Param;

    int currentMode;
    ParamDialog  *paramSetGet = nullptr;
    QTimer *Timer103, *VideoTimer;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_comboBox_currentIndexChanged(const QString &text);
    void showAllTestResultStrToUI();

public slots:
    void handleResults(const QString &result);
    void handleThreadFinished();

signals:
    void AppendText(const QString &text);

private slots:
    void SlotAppendText(const QString &text);
    void loginSuccess(QString);
    void setMode(int mode);

    void on_ParamSet_clicked();
    void setEtb104Param(ETB104 etbid);
    void setEtb106Param(uint8_t etbid);
    void setEtb110Param(uint8_t etbid);
    void setEtb130Param(ETB130  etb130);

    void on_ModeSelect_currentChanged(int index);
    void on_HistoryButton_clicked();

    void videoSendAndShow();
    void showETBParam();

    void on_VideoStop_clicked();

    void on_VideoSelect_clicked();

private:
    Ui::MainWindow *ui;
    //WorkerThread *currentWorkerThread;
    bool threadRunning;

    QSqlDatabase db;
    QSqlQuery query;

    LoginDialog *userLogin;
    QString UserName;

    SelectDialog *selectMode;
    VideoDialog  *videoDia;

    cv::VideoCapture videoCapture;
    QImage* image_receive;

private:


};

class WorkerThread : public QThread
{
    Q_OBJECT
    void run() override;
signals:
    void resultReady(const QString &s);
public:
    QString m,sourceip,destinationip,mlticastip;
    //bool shouldExitThread;
};
#endif // MAINWINDOW_H
