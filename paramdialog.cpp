#include "paramdialog.h"
#include "ui_paramdialog.h"


ParamDialog::ParamDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParamDialog)
{
    ui->setupUi(this);
}

ParamDialog::~ParamDialog()
{
    delete ui;
}

void ParamDialog::set103ParamToDialog(ETB103* param)
{
    ui->versionM103->setText(QString::number(param->versionM, 16));
    ui->versionS103->setText(QString::number(param->versionS, 16));
    ui->etbId103->setText(QString::number(param->etbId, 16));
    ui->cstCnt103->setText(QString::number(param->cstCnt, 16));

    QString cstString;
    for(uint32_t i=0;i<sizeof (param->cstList_1);++i)
        cstString += QString::number(int(param->cstList_1[i]), 16) + " ";
    ui->cstList103_1->setText(cstString); // 这个是数组，需要后续单独处理
    cstString.clear();
    for(uint32_t i=0;i<sizeof (param->cstList_2);++i)
        cstString += QString::number(int(param->cstList_2[i]), 16) + " ";
    ui->cstList103_2->setText(cstString); // 这个是数组，需要后续单独处理

    cstString.clear();
    for(uint32_t i=0;i<sizeof (param->trnTopoCnt);++i)
        cstString += QString::number(int(param->trnTopoCnt[i]), 16) + " ";
    ui->trnTopoCnt103->setText(cstString);

    ui->ComidTab->setCurrentIndex(1);
}

void ParamDialog::set105ParamToDialog(ETB105 *param){
    ui->versionM105->setText(QString::number(param->versionM, 16));
    ui->versionS105->setText(QString::number(param->versionS, 16));
    ui->cstClass105->setText(QString::number(param->cstClass, 16));
    QString str;
    for(uint32_t i=0;i<sizeof (param->cstId);++i)
        str += QString::number(int(param->cstId[i]), 16) + " ";
    ui->cstId105->setText(str); // 这个是数组，需要后续单独处理
    str.clear();

    for(uint32_t i=0;i<sizeof (param->cstType);++i)
        str += QString::number(int(param->cstType[i]), 16) + " ";
    ui->cstType105->setText(str); // 这个是数组，需要后续单独处理
    str.clear();

    for(uint32_t i=0;i<sizeof (param->cstOwner);++i)
        str += QString::number(int(param->cstOwner[i]), 16) + " ";
    ui->cstOwner105->setText(str); // 这个是数组，需要后续单独处理
    str.clear();

    for(uint32_t i=0;i<sizeof (param->cstUUID);++i)
        str += QString::number(int(param->cstUUID[i]), 16) + " ";
    ui->cstUUID105->setText(str); // 这个是数组，需要后续单独处理
    str.clear();

    for(uint32_t i=0;i<sizeof (param->cstProp);++i)
        str += QString::number(int(param->cstProp[i]), 16) + " ";
    ui->cstProp105->setText(str); // 这个是数组，需要后续单独处理
    str.clear();

    for(uint32_t i=0;i<sizeof (param->etbCnt);++i)
        str += QString::number(int(param->etbCnt[i]), 16) + " ";
    ui->etbCnt105->setText(str); // 这个是数组，需要后续单独处理
    str.clear();

    for(uint32_t i=0;i<sizeof (param->etbInfoList);++i)
        str += QString::number(int(param->etbInfoList[i]), 16) + " ";
    ui->etbInfoList105->setText(str); // 这个是数组，需要后续单独处理
    str.clear();

    for(uint32_t i=0;i<sizeof (param->vehCnt);++i)
        str += QString::number(int(param->vehCnt[i]), 16) + " ";
    ui->vehCnt105->setText(str); // 这个是数组，需要后续单独处理
    str.clear();

    for(uint32_t i=0;i<sizeof (param->vehInfoList);++i)
        str += QString::number(int(param->vehInfoList[i]), 16) + " ";
    ui->vehInfoList105->setText(str); // 这个是数组，需要后续单独处理
    str.clear();

    for(uint32_t i=0;i<sizeof (param->fctCnt);++i)
        str += QString::number(int(param->fctCnt[i]), 16) + " ";
    ui->fctCnt105->setText(str); // 这个是数组，需要后续单独处理
    str.clear();

    for(uint32_t i=0;i<sizeof (param->fctInfoList);++i)
        str += QString::number(int(param->fctInfoList[i]), 16) + " ";
    ui->fctInfoListList105->setText(str); // 这个是数组，需要后续单独处理
    str.clear();

    for(uint32_t i=0;i<sizeof (param->ctrlCstCnt);++i)
        str += QString::number(int(param->ctrlCstCnt[i]), 16) + " ";
    ui->ctrlCstCnt105->setText(str); // 这个是数组，需要后续单独处理
    str.clear();

    for(uint32_t i=0;i<sizeof (param->cstTopoCnt);++i)
        str += QString::number(int(param->cstTopoCnt[i]), 16) + " ";
    ui->cstTopoCnt->setText(str); // 这个是数组，需要后续单独处理
    str.clear();
    ui->ComidTab->setCurrentIndex(3);
}

void ParamDialog::set107ParamToDialog(ETB107* param)
{
    QString cstString;
    for(uint32_t i=0;i<sizeof (param->entryCnt);++i)
        cstString += QString::number(int(param->entryCnt[i]), 16) + " ";
    ui->entryCnt107->setText(cstString);

    cstString.clear();
    for(uint32_t i=0;i<sizeof (param->trnNetDir_1);++i)
        cstString += QString::number(int(param->trnNetDir_1[i]), 16) + " ";
    ui->trnNetDir107_1->setText(cstString);

    cstString.clear();
    for(uint32_t i=0;i<sizeof (param->trnNetDir_2);++i)
        cstString += QString::number(int(param->trnNetDir_2[i]), 16) + " ";
    ui->trnNetDir107_2->setText(cstString);

    cstString.clear();
    for(uint32_t i=0;i<sizeof (param->etbTopoCnt);++i)
        cstString += QString::number(int(param->etbTopoCnt[i]), 16) + " ";
    ui->etbTopoCnt107->setText(cstString);

    ui->ComidTab->setCurrentIndex(5);
}

void ParamDialog::set109ParamToDialog(ETB109* param)
{
    ui->versionM109->setText(QString::number(param->versionM, 16));
    ui->versionS109->setText(QString::number(param->versionS, 16));
    ui->etbId109->setText(QString::number(param->etbId, 16));
    ui->opTrnOrient109->setText(QString::number(param->opTrnOrient, 16));
    ui->opCstCnt109->setText(QString::number(param->opCstCnt, 16));

    QString cstString;
    for(uint32_t i=0;i<sizeof (param->opCstList_1);++i)
        cstString += QString::number(int(param->opCstList_1[i]), 16) + " ";
    ui->opCstList109_1->setText(cstString);

    cstString.clear();
    for(uint32_t i=0;i<sizeof (param->opCstList_2);++i)
        cstString += QString::number(int(param->opCstList_2[i]), 16) + " ";
    ui->opCstList109_2->setText(cstString);

    ui->opVehCnt109->setText(QString::number(param->opVehCnt, 16));

    cstString.clear();
    for(uint32_t i=0;i<sizeof (param->opVehList_1);++i)
        cstString += QString::number(int(param->opVehList_1[i]), 16) + " ";
    ui->opVehList109->setText(cstString);

    cstString.clear();
    for(uint32_t i=0;i<sizeof (param->opVehList_2);++i)
        cstString += QString::number(int(param->opVehList_2[i]), 16) + " ";
    ui->opVehList109_2->setText(cstString);

    cstString.clear();
    for(uint32_t i=0;i<sizeof (param->opVehList_3);++i)
        cstString += QString::number(int(param->opVehList_3[i]), 16) + " ";
    ui->opVehList109_3->setText(cstString);

    cstString.clear();
    for(uint32_t i=0;i<sizeof (param->opTrnTopoCnt);++i)
        cstString += QString::number(int(param->opTrnTopoCnt[i]), 16) + " ";
    ui->opTrnTopoCnt109->setText(cstString);

    ui->ComidTab->setCurrentIndex(7);
}

void ParamDialog::set111ParamToDialog(ETB111* param)
{
    ui->versionM111->setText(QString::number(param->versionM, 16));
    ui->versionS111->setText(QString::number(param->versionS, 16));
    ui->etbId111->setText(QString::number(param->etbId, 16));
    ui->trnDirState111->setText(QString::number(param->trnDirState, 16));
    ui->opTrnDirState111->setText(QString::number(param->opTrnDirState, 16));

    QString cstString;
    for(uint32_t i=0;i<sizeof (param->trnId);++i)
        cstString += QString::number(int(param->trnId[i]), 16) + " ";
    ui->trnId111->setText(cstString);

    cstString.clear();
    for(uint32_t i=0;i<sizeof (param->trnOperator);++i)
        cstString += QString::number(int(param->trnOperator[i]), 16) + " ";
    ui->trnOperator111->setText(cstString);

    cstString.clear();
    for(uint32_t i=0;i<sizeof (param->opTrnTopoCnt);++i)
        cstString += QString::number(int(param->opTrnTopoCnt[i]), 16) + " ";
    ui->opTrnTopoCnt111->setText(cstString);

    cstString.clear();
    for(uint32_t i=0;i<sizeof (param->crc);++i)
        cstString += QString::number(int(param->crc[i]), 16) + " ";
    ui->crc111->setText(cstString);

    ui->opTrnOrient111->setText(QString::number(param->opTrnOrient, 16));
    ui->opCstCnt111->setText(QString::number(param->opCstCnt, 16));

    cstString.clear();
    for(uint32_t i=0;i<sizeof (param->opCstList_1);++i)
        cstString += QString::number(int(param->opCstList_1[i]), 16) + " ";
    ui->opCstList111_1->setText(cstString);

    cstString.clear();
    for(uint32_t i=0;i<sizeof (param->opCstList_2);++i)
        cstString += QString::number(int(param->opCstList_2[i]), 16) + " ";
    ui->opCstList111_2->setText(cstString);

    ui->opVehCnt111->setText(QString::number(param->opVehCnt, 16));

    cstString.clear();
    for(uint32_t i=0;i<sizeof (param->opVehList_1);++i)
        cstString += QString::number(int(param->opVehList_1[i]), 16) + " ";
    ui->opVehList111_1->setText(cstString);

    cstString.clear();
    for(uint32_t i=0;i<sizeof (param->opVehList_2);++i)
        cstString += QString::number(int(param->opVehList_2[i]), 16) + " ";
    ui->opVehList111_2->setText(cstString);

    cstString.clear();
    for(uint32_t i=0;i<sizeof (param->opVehList_3);++i)
        cstString += QString::number(int(param->opVehList_3[i]), 16) + " ";
    ui->opVehList111_3->setText(cstString);

    ui->cstCnt111->setText(QString::number(param->cstCnt, 16));

    cstString.clear();
    for(uint32_t i=0;i<sizeof (param->opCstList_1);++i)
        cstString += QString::number(int(param->opCstList_1[i]), 16) + " ";
    ui->cstList111_1->setText(cstString);

    cstString.clear();
    for(uint32_t i=0;i<sizeof (param->opCstList_2);++i)
        cstString += QString::number(int(param->opCstList_2[i]), 16) + " ";
    ui->cstList111_2->setText(cstString);

    cstString.clear();
    for(uint32_t i=0;i<sizeof (param->TrnTopoCnt);++i)
        cstString += QString::number(int(param->TrnTopoCnt[i]), 16) + " ";
    ui->TrnTopoCnt111->setText(cstString);

    cstString.clear();
    for(uint32_t i=0;i<sizeof (param->entryCnt);++i)
        cstString += QString::number(int(param->entryCnt[i]), 16) + " ";
    ui->entryCnt111->setText(cstString);

    cstString.clear();
    for(uint32_t i=0;i<sizeof (param->trnNetDir_1);++i)
        cstString += QString::number(int(param->trnNetDir_1[i]), 16) + " ";
    ui->trnNetDir111_1->setText(cstString);

    cstString.clear();
    for(uint32_t i=0;i<sizeof (param->trnNetDir_2);++i)
        cstString += QString::number(int(param->trnNetDir_2[i]), 16) + " ";
    ui->trnNetDir111_2->setText(cstString);

    cstString.clear();
    for(uint32_t i=0;i<sizeof (param->etbTopoCnt);++i)
        cstString += QString::number(int(param->etbTopoCnt[i]), 16) + " ";
    ui->etbTopoCnt111->setText(cstString);

    ui->ComidTab->setCurrentIndex(9);
}

void ParamDialog::set131ParamToDialog(ETB131* param)
{
    ui->versionM131->setText(QString::number(param->versionM, 16));
    ui->versionS131->setText(QString::number(param->versionS, 16));

    QString cstString;
    for(uint32_t i=0;i<sizeof (param->deviceName);++i)
        cstString += QString::number(int(param->deviceName[i]), 16) + " ";
    ui->deviceName131->setText(cstString);

    ui->etbnState131->setText(QString::number(param->etbnState, 16));
    ui->etbnInaugState131->setText(QString::number(param->etbnInaugState, 16));
    ui->etbnPosition131->setText(QString::number(param->etbnPosition, 16));
    ui->etbnRole131->setText(QString::number(param->etbnRole, 16));
    ui->etbInhibit131->setText(QString::number(param->etbInhibit, 16));
    ui->etbLength131->setText(QString::number(param->etbLength, 16));
    ui->etbShort131->setText(QString::number(param->etbShort, 16));
    ui->etbLineState131->setText(QString::number(param->etbLineState, 16));
    ui->byPassState131->setText(QString::number(param->byPassState, 16));
    ui->slState131->setText(QString::number(param->slState, 16));

    cstString.clear();
    for(uint32_t i=0;i<sizeof (param->etbTopoCnt);++i)
        cstString += QString::number(int(param->etbTopoCnt[i]), 16) + " ";
    ui->etbTopoCnt131->setText(cstString);

    ui->userDataVersionM131->setText(QString::number(param->userDataVersionM, 16));
    ui->userDataVersionS131->setText(QString::number(param->userDataVersionS, 16));

    cstString.clear();
    for(uint32_t i=0;i<sizeof (param->safeSequCount);++i)
        cstString += QString::number(int(param->safeSequCount[i]), 16) + " ";
    ui->safeSequCount131->setText(cstString);

    cstString.clear();
    for(uint32_t i=0;i<sizeof (param->safetyCode);++i)
        cstString += QString::number(int(param->safetyCode[i]), 16) + " ";
    ui->safetyCode131->setText(cstString);

    ui->ComidTab->setCurrentIndex(11);
}
void ParamDialog::set133ParamToDialog(ETB133* param)
{
    QString cstString;
    for(uint32_t i=0;i<sizeof (param->entryCnt);++i)
        cstString += QString::number(int(param->entryCnt[i]), 16) + " ";
    ui->entryCnt133->setText(cstString);

    cstString.clear();
    for(uint32_t i=0;i<sizeof (param->trnNetDir_1);++i)
        cstString += QString::number(int(param->trnNetDir_1[i]), 16) + " ";
    ui->trnNetDir133_1->setText(cstString);

    cstString.clear();
    for(uint32_t i=0;i<sizeof (param->trnNetDir_2);++i)
        cstString += QString::number(int(param->trnNetDir_2[i]), 16) + " ";
    ui->trnNetDir133_2->setText(cstString);

    cstString.clear();
    for(uint32_t i=0;i<sizeof (param->etbTopoCnt);++i)
        cstString += QString::number(int(param->etbTopoCnt[i]), 16) + " ";
    ui->etbTopoCnt133->setText(cstString);

    ui->ComidTab->setCurrentIndex(13);
}

void ParamDialog::on_Confirm104_clicked()
{
    ETB104 etb104;
    QStringList strList = ui->param104->text().split(" ");
    int i=0;
    for(const auto &str : qAsConst(strList))
    {
        uint8_t a = str.toInt(nullptr, 16);
        etb104.param[i++] = a;
    }
    emit get104ParamFromDialog(etb104);
    this->close();
}


void ParamDialog::on_Confirm106_clicked()
{
    uint8_t etbid = ui->etbId106->value();
    emit get106ParamFromDialog(etbid);
    this->close();
}


void ParamDialog::on_Confirm110_clicked()
{
    uint8_t etbid = ui->etbId110->value();
    emit get110ParamFromDialog(etbid);
    this->close();
}


void ParamDialog::on_Confirm130_clicked()
{
    ETB130 etb130;
    etb130.versionM = ui->versionM130->value();
    etb130.versionS = ui->versionS130->value();

    QStringList strList = ui->reserved01_130->text().split(" ");
    int i=0;
    for(const auto &str : qAsConst(strList))
    {
        uint8_t a = str.toInt(nullptr, 16);
        etb130.reserved01[i++] = a;
    }

    strList.clear();
    strList = ui->deviceName130->text().split(" ");
    i=0;
    for(const auto &str : qAsConst(strList))
    {
        uint8_t a = str.toInt(nullptr, 16);
        etb130.deviceName[i++] = a;
    }


    etb130.inhibit = ui->inhibit130->value();
    etb130.byPassCtrl = ui->byPassCtrl130->value();
    etb130.txCtrl = ui->txCtrl130->value();
    etb130.slCtrl = ui->slCtrl130->value();

    strList.clear();
    strList = ui->reserved02_130->text().split(" ");
    i=0;
    for(const auto &str : qAsConst(strList))
    {
        uint8_t a = str.toInt(nullptr, 16);
        etb130.reserved02[i++] = a;
    }

    strList.clear();
    strList = ui->reserved03_130->text().split(" ");
    i=0;
    for(const auto &str : qAsConst(strList))
    {
        uint8_t a = str.toInt(nullptr, 16);
        etb130.reserved03[i++] = a;
    }

    etb130.userDataVersionM = ui->userDataVersionM130->value();
    etb130.userDataVersionS = ui->userDataVersionS130->value();

    strList.clear();
    strList = ui->safeSequCount130->text().split(" ");
    i=0;
    for(const auto &str : qAsConst(strList))
    {
        uint8_t a = str.toInt(nullptr, 16);
        etb130.safeSequCount[i++] = a;
    }

    strList.clear();
    strList = ui->safetyCode130->text().split(" ");
    i=0;
    for(const auto &str : qAsConst(strList))
    {
        uint8_t a = str.toInt(nullptr, 16);
        etb130.safetyCode[i++] = a;
    }

    emit get130ParamFromDialog(etb130);
    this->close();
}

void ParamDialog::setCurrentComidTab(int index)
{
    ui->ComidTab->setCurrentIndex(index);
}

void ParamDialog::on_pushButton_clicked()
{
    this->close();
}



