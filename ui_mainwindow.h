/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_5;
    QPlainTextEdit *editLog;
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_15;
    QLabel *label_16;
    QTabWidget *ModeSelect;
    QWidget *notification;
    QLabel *label_6;
    QLineEdit *lineEdit_5;
    QLabel *label_10;
    QLineEdit *lineEdit_7;
    QWidget *request_reply;
    QLabel *label_11;
    QLineEdit *lineEdit_8;
    QLabel *label_12;
    QLineEdit *lineEdit_9;
    QWidget *request_reply_confirm;
    QLabel *label_13;
    QLineEdit *lineEdit_10;
    QLabel *label_14;
    QLineEdit *lineEdit_11;
    QWidget *tab;
    QLabel *label_17;
    QComboBox *ETBComid;
    QPushButton *ParamSet;
    QWidget *VideoSend;
    QPushButton *VideoSelect;
    QLineEdit *VideoAdr;
    QLineEdit *VideoComid;
    QLabel *label_18;
    QWidget *tab_2;
    QPushButton *HistoryButton;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QLabel *label_4;
    QLineEdit *lineEdit_4;
    QLabel *label;
    QComboBox *comboBox;
    QComboBox *comboBox_2;
    QLabel *label_5;
    QLabel *label_7;
    QLineEdit *lineEdit_6;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *VideoStop;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(576, 721);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 430, 481, 231));
        horizontalLayout_5 = new QHBoxLayout(groupBox);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        editLog = new QPlainTextEdit(groupBox);
        editLog->setObjectName(QString::fromUtf8("editLog"));

        horizontalLayout_5->addWidget(editLog);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(290, 120, 75, 23));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setEnabled(true);
        lineEdit->setGeometry(QRect(380, 120, 81, 20));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(20, 360, 84, 16));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(110, 360, 251, 20));
        label_15 = new QLabel(centralWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(110, 390, 251, 20));
        label_16 = new QLabel(centralWidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(20, 390, 84, 16));
        ModeSelect = new QTabWidget(centralWidget);
        ModeSelect->setObjectName(QString::fromUtf8("ModeSelect"));
        ModeSelect->setGeometry(QRect(10, 0, 561, 111));
        notification = new QWidget();
        notification->setObjectName(QString::fromUtf8("notification"));
        label_6 = new QLabel(notification);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 10, 156, 20));
        lineEdit_5 = new QLineEdit(notification);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(270, 10, 111, 20));
        lineEdit_5->setClearButtonEnabled(false);
        label_10 = new QLabel(notification);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(10, 40, 180, 20));
        lineEdit_7 = new QLineEdit(notification);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));
        lineEdit_7->setGeometry(QRect(270, 40, 111, 20));
        lineEdit_7->setClearButtonEnabled(false);
        ModeSelect->addTab(notification, QString());
        request_reply = new QWidget();
        request_reply->setObjectName(QString::fromUtf8("request_reply"));
        label_11 = new QLabel(request_reply);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 10, 162, 20));
        lineEdit_8 = new QLineEdit(request_reply);
        lineEdit_8->setObjectName(QString::fromUtf8("lineEdit_8"));
        lineEdit_8->setGeometry(QRect(270, 10, 111, 20));
        lineEdit_8->setClearButtonEnabled(false);
        label_12 = new QLabel(request_reply);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(10, 40, 186, 20));
        lineEdit_9 = new QLineEdit(request_reply);
        lineEdit_9->setObjectName(QString::fromUtf8("lineEdit_9"));
        lineEdit_9->setGeometry(QRect(270, 40, 111, 20));
        lineEdit_9->setClearButtonEnabled(false);
        ModeSelect->addTab(request_reply, QString());
        request_reply_confirm = new QWidget();
        request_reply_confirm->setObjectName(QString::fromUtf8("request_reply_confirm"));
        label_13 = new QLabel(request_reply_confirm);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(10, 10, 210, 20));
        lineEdit_10 = new QLineEdit(request_reply_confirm);
        lineEdit_10->setObjectName(QString::fromUtf8("lineEdit_10"));
        lineEdit_10->setGeometry(QRect(270, 10, 111, 20));
        lineEdit_10->setClearButtonEnabled(false);
        label_14 = new QLabel(request_reply_confirm);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(10, 40, 241, 20));
        lineEdit_11 = new QLineEdit(request_reply_confirm);
        lineEdit_11->setObjectName(QString::fromUtf8("lineEdit_11"));
        lineEdit_11->setGeometry(QRect(270, 40, 111, 20));
        lineEdit_11->setClearButtonEnabled(false);
        ModeSelect->addTab(request_reply_confirm, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        label_17 = new QLabel(tab);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(10, 10, 191, 20));
        ETBComid = new QComboBox(tab);
        ETBComid->addItem(QString());
        ETBComid->addItem(QString());
        ETBComid->addItem(QString());
        ETBComid->addItem(QString());
        ETBComid->addItem(QString());
        ETBComid->addItem(QString());
        ETBComid->addItem(QString());
        ETBComid->addItem(QString());
        ETBComid->setObjectName(QString::fromUtf8("ETBComid"));
        ETBComid->setGeometry(QRect(270, 10, 111, 22));
        ParamSet = new QPushButton(tab);
        ParamSet->setObjectName(QString::fromUtf8("ParamSet"));
        ParamSet->setGeometry(QRect(270, 50, 111, 23));
        ModeSelect->addTab(tab, QString());
        VideoSend = new QWidget();
        VideoSend->setObjectName(QString::fromUtf8("VideoSend"));
        VideoSelect = new QPushButton(VideoSend);
        VideoSelect->setObjectName(QString::fromUtf8("VideoSelect"));
        VideoSelect->setGeometry(QRect(460, 50, 75, 23));
        VideoAdr = new QLineEdit(VideoSend);
        VideoAdr->setObjectName(QString::fromUtf8("VideoAdr"));
        VideoAdr->setGeometry(QRect(10, 50, 431, 20));
        VideoComid = new QLineEdit(VideoSend);
        VideoComid->setObjectName(QString::fromUtf8("VideoComid"));
        VideoComid->setEnabled(false);
        VideoComid->setGeometry(QRect(210, 10, 111, 20));
        VideoComid->setClearButtonEnabled(false);
        label_18 = new QLabel(VideoSend);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(10, 10, 180, 20));
        ModeSelect->addTab(VideoSend, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        HistoryButton = new QPushButton(tab_2);
        HistoryButton->setObjectName(QString::fromUtf8("HistoryButton"));
        HistoryButton->setGeometry(QRect(420, 40, 75, 23));
        ModeSelect->addTab(tab_2, QString());
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 190, 61, 31));
        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(130, 200, 231, 20));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 230, 60, 31));
        lineEdit_3 = new QLineEdit(centralWidget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(130, 240, 231, 20));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(470, 110, 60, 31));
        lineEdit_4 = new QLineEdit(centralWidget);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(380, 150, 111, 20));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 110, 36, 31));
        comboBox = new QComboBox(centralWidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(130, 120, 141, 20));
        comboBox_2 = new QComboBox(centralWidget);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(130, 160, 231, 20));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 150, 60, 31));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(20, 280, 60, 23));
        lineEdit_6 = new QLineEdit(centralWidget);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));
        lineEdit_6->setGeometry(QRect(130, 280, 231, 20));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(20, 320, 81, 23));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(120, 320, 71, 23));
        VideoStop = new QPushButton(centralWidget);
        VideoStop->setObjectName(QString::fromUtf8("VideoStop"));
        VideoStop->setGeometry(QRect(240, 320, 75, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 576, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        ModeSelect->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\344\270\273\347\225\214\351\235\242", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "\346\227\245\345\277\227\346\266\210\346\201\257", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\345\267\245\344\275\234", nullptr));
        lineEdit->setText(QApplication::translate("MainWindow", "caller", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "\346\266\210\346\201\257\345\217\221\351\200\201\347\212\266\346\200\201\357\274\232", nullptr));
        label_9->setText(QString());
        label_15->setText(QString());
        label_16->setText(QApplication::translate("MainWindow", "\346\200\247\350\203\275\347\273\237\350\256\241\357\274\232", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "notification - TCP COMID\357\274\232", nullptr));
        lineEdit_5->setText(QApplication::translate("MainWindow", "1000", nullptr));
        label_10->setText(QApplication::translate("MainWindow", "notification - unicast COMID\357\274\232", nullptr));
        lineEdit_7->setText(QApplication::translate("MainWindow", "2000", nullptr));
        ModeSelect->setTabText(ModeSelect->indexOf(notification), QApplication::translate("MainWindow", "notification", nullptr));
        label_11->setText(QApplication::translate("MainWindow", "request/reply - TCP COMID\357\274\232", nullptr));
        lineEdit_8->setText(QApplication::translate("MainWindow", "3000", nullptr));
        label_12->setText(QApplication::translate("MainWindow", "request/reply - unicast COMID\357\274\232", nullptr));
        lineEdit_9->setText(QApplication::translate("MainWindow", "4000", nullptr));
        ModeSelect->setTabText(ModeSelect->indexOf(request_reply), QApplication::translate("MainWindow", "request/reply", nullptr));
        label_13->setText(QApplication::translate("MainWindow", "request/reply/confirm - TCP COMID\357\274\232", nullptr));
        lineEdit_10->setText(QApplication::translate("MainWindow", "5000", nullptr));
        label_14->setText(QApplication::translate("MainWindow", "request/reply/confirm - unicast COMID\357\274\232", nullptr));
        lineEdit_11->setText(QApplication::translate("MainWindow", "6000", nullptr));
        ModeSelect->setTabText(ModeSelect->indexOf(request_reply_confirm), QApplication::translate("MainWindow", "request/reply/confirm", nullptr));
        label_17->setText(QApplication::translate("MainWindow", "request/reply - unicast COMID\357\274\232", nullptr));
        ETBComid->setItemText(0, QApplication::translate("MainWindow", "0", nullptr));
        ETBComid->setItemText(1, QApplication::translate("MainWindow", "102", nullptr));
        ETBComid->setItemText(2, QApplication::translate("MainWindow", "104", nullptr));
        ETBComid->setItemText(3, QApplication::translate("MainWindow", "106", nullptr));
        ETBComid->setItemText(4, QApplication::translate("MainWindow", "108", nullptr));
        ETBComid->setItemText(5, QApplication::translate("MainWindow", "110", nullptr));
        ETBComid->setItemText(6, QApplication::translate("MainWindow", "130", nullptr));
        ETBComid->setItemText(7, QApplication::translate("MainWindow", "132", nullptr));

        ParamSet->setText(QApplication::translate("MainWindow", " \350\256\276\347\275\256\345\217\202\346\225\260", nullptr));
        ModeSelect->setTabText(ModeSelect->indexOf(tab), QApplication::translate("MainWindow", "ETB", nullptr));
        VideoSelect->setText(QApplication::translate("MainWindow", "\351\200\211\346\213\251\350\247\206\351\242\221", nullptr));
        VideoComid->setText(QApplication::translate("MainWindow", "1234", nullptr));
        label_18->setText(QApplication::translate("MainWindow", "notification - unicast COMID\357\274\232", nullptr));
        ModeSelect->setTabText(ModeSelect->indexOf(VideoSend), QApplication::translate("MainWindow", "\350\247\206\351\242\221\344\274\240\350\276\223", nullptr));
        HistoryButton->setText(QApplication::translate("MainWindow", "\347\202\271\345\207\273\346\237\245\350\257\242", nullptr));
        ModeSelect->setTabText(ModeSelect->indexOf(tab_2), QApplication::translate("MainWindow", "\345\216\206\345\217\262\346\225\260\346\215\256\346\237\245\350\257\242", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\346\272\220\345\234\260\345\235\200\357\274\232", nullptr));
        lineEdit_2->setText(QApplication::translate("MainWindow", "192.168.0.181", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "\347\233\256\347\232\204\345\234\260\345\235\200\357\274\232", nullptr));
        lineEdit_3->setText(QApplication::translate("MainWindow", "192.168.0.191", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "\345\244\232\346\222\255\345\234\260\345\235\200\357\274\232", nullptr));
        lineEdit_4->setText(QApplication::translate("MainWindow", "239.2.24.1", nullptr));
        label->setText(QApplication::translate("MainWindow", "\346\250\241\345\274\217\357\274\232", nullptr));
        comboBox->setItemText(0, QApplication::translate("MainWindow", "caller", nullptr));
        comboBox->setItemText(1, QApplication::translate("MainWindow", "replier", nullptr));

        comboBox_2->setItemText(0, QApplication::translate("MainWindow", "TCP", nullptr));
        comboBox_2->setItemText(1, QApplication::translate("MainWindow", "unicast", nullptr));

        label_5->setText(QApplication::translate("MainWindow", "\351\200\232\344\277\241\346\226\271\345\274\217\357\274\232", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "\346\266\210\346\201\257\347\261\273\345\236\213\357\274\232", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow", "\346\270\205\347\251\272", nullptr));
        pushButton_3->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        VideoStop->setText(QApplication::translate("MainWindow", " \345\201\234\346\255\242\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
