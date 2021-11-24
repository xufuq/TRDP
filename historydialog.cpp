#include "historydialog.h"
#include "ui_historydialog.h"
#include <QVector>

HistoryDialog::HistoryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HistoryDialog)
{
    ui->setupUi(this);


}

HistoryDialog::~HistoryDialog()
{
    delete ui;
}

void HistoryDialog::on_AskButton_clicked()
{
    db = QSqlDatabase::addDatabase("QSQLITE"); //数据库对象
    db.setHostName("127.0.0.1"); //设置数据库主机名
    db.setDatabaseName(QCoreApplication::applicationDirPath()+"/"+"bin.db"); //设置数据库名
    db.setUserName("root"); //设置数据库用户名
    db.setPassword("1234"); //设置数据库密码
    if (!db.open()) {
        QMessageBox::critical(this, "Error", "Failed to connect database.");
        qDebug() << "Error: Failed to connect database." << db.lastError();
        return;
    } else {
        qDebug() << "Succeed to connect database.";
    }

    query=QSqlQuery(db);
    if(!query.exec("CREATE TABLE binFile(id integer primary key, username varchar(10), time varchar(10), mode varchar(11), loss varchar(10), delay varchar(10), sendtext varchar(120))"))
        qDebug() << "bin表已存在" << endl;


//    query.prepare("select * from binFile where time Between '2021-06-21' and  '2021-06-22'"); // 访问全部数据
//    if(!query.exec()){
//        QMessageBox::critical(this, "Warning", "No data now.");
//        qDebug()<<query.lastError();
//        return;
//    }
//    else {
//        query.next();
//        qDebug() << query.value(3).toString();
//    }


//    query.prepare("select * from binFile"); // 访问全部数据
//    if(!query.exec()){
//        QMessageBox::critical(this, "Warning", "No data now.");
//        qDebug()<<query.lastError();
//        return;
//    }

//    QVector<int> hideID;
    QString startTime = ui->StartDate->text();
    QString endTime = ui->EndDate->text();
//    while (query.next()) {
//        QString currentQueryTime = query.value(2).toString();
//        if(currentQueryTime.compare(startTime)<0 || currentQueryTime.compare(endTime)>0){ // 不在所选时间范围内
//            int id = query.value(0).toInt();
//            hideID.push_back(id);
//        }
//    }

    if(model != nullptr)
        delete model;

    model=new QSqlTableModel();
    model->setTable("binFile");
    model->setSort(0, Qt::AscendingOrder);
//    ui->SqlShowView->hideColumn(0);
    // 这里的setHeaderData只是设置表头，而和数据库显示哪几行没有任何关系，如果不设置则按照默认显示
    model->setHeaderData(1, Qt::Horizontal, "username");
    model->setHeaderData(2, Qt::Horizontal, "time");
    model->setHeaderData(3, Qt::Horizontal, "mode");
    model->setHeaderData(4, Qt::Horizontal, "loss rate");
    model->setHeaderData(5, Qt::Horizontal, "time delay");
    model->setHeaderData(6, Qt::Horizontal, "send text");
    model->select();

    ui->SqlShowView->setModel(model);
    ui->SqlShowView->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    ui->SqlShowView->hideColumn(5); // 用隐藏行号可以实现查询

//    for (int i=0;i<hideID.size();++i) {
//        qDebug() << hideID[hideID.size()-1-i] << endl;
//        ui->SqlShowView->hideRow(hideID[hideID.size()-1-i]);
//    }
    model->setFilter(tr("time >= '%1' and time <= '%2'").arg(startTime, endTime));
    model->select();
    ui->SqlShowView->resizeColumnsToContents();
//    db.close();
}

