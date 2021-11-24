/********************************************************************************
** Form generated from reading UI file 'historydialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTORYDIALOG_H
#define UI_HISTORYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_HistoryDialog
{
public:
    QDateEdit *StartDate;
    QLabel *label;
    QLabel *label_2;
    QDateEdit *EndDate;
    QPushButton *AskButton;
    QTableView *SqlShowView;

    void setupUi(QDialog *HistoryDialog)
    {
        if (HistoryDialog->objectName().isEmpty())
            HistoryDialog->setObjectName(QString::fromUtf8("HistoryDialog"));
        HistoryDialog->resize(1337, 635);
        StartDate = new QDateEdit(HistoryDialog);
        StartDate->setObjectName(QString::fromUtf8("StartDate"));
        StartDate->setGeometry(QRect(90, 10, 110, 22));
        StartDate->setDateTime(QDateTime(QDate(2021, 6, 21), QTime(0, 0, 0)));
        StartDate->setCalendarPopup(true);
        label = new QLabel(HistoryDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 10, 54, 21));
        label_2 = new QLabel(HistoryDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(240, 10, 54, 21));
        EndDate = new QDateEdit(HistoryDialog);
        EndDate->setObjectName(QString::fromUtf8("EndDate"));
        EndDate->setGeometry(QRect(310, 10, 110, 22));
        EndDate->setDateTime(QDateTime(QDate(2021, 6, 21), QTime(0, 0, 0)));
        EndDate->setCalendarPopup(true);
        AskButton = new QPushButton(HistoryDialog);
        AskButton->setObjectName(QString::fromUtf8("AskButton"));
        AskButton->setGeometry(QRect(450, 10, 91, 23));
        SqlShowView = new QTableView(HistoryDialog);
        SqlShowView->setObjectName(QString::fromUtf8("SqlShowView"));
        SqlShowView->setGeometry(QRect(10, 50, 1311, 571));

        retranslateUi(HistoryDialog);

        QMetaObject::connectSlotsByName(HistoryDialog);
    } // setupUi

    void retranslateUi(QDialog *HistoryDialog)
    {
        HistoryDialog->setWindowTitle(QApplication::translate("HistoryDialog", "\345\216\206\345\217\262\346\225\260\346\215\256\346\237\245\350\257\242", nullptr));
        StartDate->setDisplayFormat(QApplication::translate("HistoryDialog", "yyyy-MM-dd", nullptr));
        label->setText(QApplication::translate("HistoryDialog", "\345\274\200\345\247\213\346\227\245\346\234\237", nullptr));
        label_2->setText(QApplication::translate("HistoryDialog", "\347\273\223\346\235\237\346\227\245\346\234\237", nullptr));
        EndDate->setDisplayFormat(QApplication::translate("HistoryDialog", "yyyy-MM-dd", nullptr));
        AskButton->setText(QApplication::translate("HistoryDialog", "\346\237\245\350\257\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HistoryDialog: public Ui_HistoryDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTORYDIALOG_H
