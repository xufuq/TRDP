#ifndef PARAMDIALOG_H
#define PARAMDIALOG_H

#include <QDialog>
#include <QDebug>
#include "myStruct.h"


namespace Ui {
class ParamDialog;
}

class ParamDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ParamDialog(QWidget *parent = nullptr);
    ~ParamDialog();

    void setCurrentComidTab(int index);

    void set103ParamToDialog(ETB103*);
    void set105ParamToDialog(ETB105*);
    void set107ParamToDialog(ETB107*);
    void set109ParamToDialog(ETB109*);
    void set111ParamToDialog(ETB111*);
    void set131ParamToDialog(ETB131*);
    void set133ParamToDialog(ETB133*);

private slots:
    void on_Confirm104_clicked();
    void on_Confirm106_clicked();
    void on_Confirm110_clicked();
    void on_Confirm130_clicked();
    void on_pushButton_clicked();

signals:
    void get104ParamFromDialog(ETB104 etbid);
    void get106ParamFromDialog(uint8_t etbid);
    void get110ParamFromDialog(uint8_t etbid);
    void get130ParamFromDialog(ETB130  etb130);

private:
    Ui::ParamDialog *ui;


};

#endif // PARAMDIALOG_H
