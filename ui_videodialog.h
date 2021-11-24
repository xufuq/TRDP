/********************************************************************************
** Form generated from reading UI file 'videodialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEODIALOG_H
#define UI_VIDEODIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_VideoDialog
{
public:
    QLabel *VideoLabel;

    void setupUi(QDialog *VideoDialog)
    {
        if (VideoDialog->objectName().isEmpty())
            VideoDialog->setObjectName(QString::fromUtf8("VideoDialog"));
        VideoDialog->resize(342, 258);
        VideoLabel = new QLabel(VideoDialog);
        VideoLabel->setObjectName(QString::fromUtf8("VideoLabel"));
        VideoLabel->setGeometry(QRect(10, 0, 320, 240));

        retranslateUi(VideoDialog);

        QMetaObject::connectSlotsByName(VideoDialog);
    } // setupUi

    void retranslateUi(QDialog *VideoDialog)
    {
        VideoDialog->setWindowTitle(QApplication::translate("VideoDialog", "Dialog", nullptr));
        VideoLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class VideoDialog: public Ui_VideoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEODIALOG_H
