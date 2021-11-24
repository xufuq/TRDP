/********************************************************************************
** Form generated from reading UI file 'selectdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTDIALOG_H
#define UI_SELECTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SelectDialog
{
public:
    QPushButton *notification;
    QPushButton *reply;
    QPushButton *confirm;
    QPushButton *ETB;
    QPushButton *video;
    QPushButton *history;
    QLabel *label;

    void setupUi(QDialog *SelectDialog)
    {
        if (SelectDialog->objectName().isEmpty())
            SelectDialog->setObjectName(QString::fromUtf8("SelectDialog"));
        SelectDialog->resize(400, 300);
        notification = new QPushButton(SelectDialog);
        notification->setObjectName(QString::fromUtf8("notification"));
        notification->setGeometry(QRect(120, 60, 131, 23));
        reply = new QPushButton(SelectDialog);
        reply->setObjectName(QString::fromUtf8("reply"));
        reply->setGeometry(QRect(120, 100, 131, 23));
        confirm = new QPushButton(SelectDialog);
        confirm->setObjectName(QString::fromUtf8("confirm"));
        confirm->setGeometry(QRect(120, 140, 131, 23));
        ETB = new QPushButton(SelectDialog);
        ETB->setObjectName(QString::fromUtf8("ETB"));
        ETB->setGeometry(QRect(120, 180, 131, 23));
        video = new QPushButton(SelectDialog);
        video->setObjectName(QString::fromUtf8("video"));
        video->setGeometry(QRect(120, 220, 131, 23));
        history = new QPushButton(SelectDialog);
        history->setObjectName(QString::fromUtf8("history"));
        history->setGeometry(QRect(120, 260, 131, 23));
        label = new QLabel(SelectDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(150, 20, 51, 21));

        retranslateUi(SelectDialog);

        QMetaObject::connectSlotsByName(SelectDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectDialog)
    {
        SelectDialog->setWindowTitle(QApplication::translate("SelectDialog", "Dialog", nullptr));
        notification->setText(QApplication::translate("SelectDialog", "notification", nullptr));
        reply->setText(QApplication::translate("SelectDialog", "request/reply", nullptr));
        confirm->setText(QApplication::translate("SelectDialog", "requ/reply/confirm", nullptr));
        ETB->setText(QApplication::translate("SelectDialog", "ETB", nullptr));
        video->setText(QApplication::translate("SelectDialog", "\350\247\206\351\242\221\344\274\240\350\276\223", nullptr));
        history->setText(QApplication::translate("SelectDialog", "\345\216\206\345\217\262\346\225\260\346\215\256\346\237\245\350\257\242", nullptr));
        label->setText(QApplication::translate("SelectDialog", "\351\200\211\346\213\251\345\212\237\350\203\275", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectDialog: public Ui_SelectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTDIALOG_H
