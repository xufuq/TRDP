#ifndef MYSTRUCT_H
#define MYSTRUCT_H

#include <stdint.h>

typedef struct
{
    uint8_t versionM;
    uint8_t versionS;
    uint8_t etbId;
    uint8_t cstCnt;
    uint8_t cstList_1[24];
    uint8_t cstList_2[24];
    uint8_t trnTopoCnt[4];
} ETB103;

typedef struct
{
    uint8_t param[16];
} ETB104;

typedef struct
{
    uint8_t versionM;
    uint8_t versionS;
    uint8_t cstClass;
    uint8_t reserved01;
    uint8_t cstId[16];
    uint8_t cstType[16];
    uint8_t cstOwner[16];
    uint8_t cstUUID[16];
    uint8_t reserved02[4];
    uint8_t cstProp[4];
    uint8_t reserved03[2];
    uint8_t etbCnt[2];
    uint8_t etbInfoList[4];
    uint8_t reserved04[2];
    uint8_t vehCnt[2];
    uint8_t vehInfoList[40];
    uint8_t reserved05[2];
    uint8_t fctCnt[2];
    uint8_t fctInfoList[120];
    uint8_t reserved06[2];
    uint8_t ctrlCstCnt[2];
    uint8_t cstTopoCnt[4];
} ETB105;

typedef struct
{
    uint8_t entryCnt[2];
    uint8_t  trnNetDir_1[20];
    uint8_t  trnNetDir_2[20];
    uint8_t etbTopoCnt[4];
} ETB107;

typedef struct
{
    uint8_t versionM;
    uint8_t versionS;
    uint8_t etbId;
    uint8_t opTrnOrient;
    uint8_t opCstCnt;
    uint8_t opCstList_1[20];
    uint8_t opCstList_2[20];
    uint8_t reserved04;
    uint8_t reserved05;
    uint8_t reserved06;
    uint8_t opVehCnt;
    uint8_t opVehList_1[24];
    uint8_t opVehList_2[24];
    uint8_t opVehList_3[24];
    uint8_t opTrnTopoCnt[4];
} ETB109;

typedef struct
{
    uint8_t versionM;
    uint8_t versionS;
    uint8_t etbId;
    uint8_t trnDirState;
    uint8_t opTrnDirState;
    uint8_t trnId[16];
    uint8_t trnOperator[16];
    uint8_t opTrnTopoCnt[4];
    uint8_t crc[4];
    uint8_t opTrnOrient;
    uint8_t opCstCnt;
    uint8_t opCstList_1[20];
    uint8_t opCstList_2[20];
    uint8_t opVehCnt;
    uint8_t opVehList_1[24];
    uint8_t opVehList_2[24];
    uint8_t opVehList_3[24];
    uint8_t cstCnt;
    uint8_t cstList_1[24];
    uint8_t cstList_2[24];
    uint8_t TrnTopoCnt[4];
    uint8_t entryCnt[2];
    uint8_t trnNetDir_1[20];
    uint8_t trnNetDir_2[20];
    uint8_t etbTopoCnt[4];
} ETB111;

typedef struct
{
    uint8_t versionM;
    uint8_t versionS;
    uint8_t reserved01[2];
    uint8_t deviceName[16];
    uint8_t inhibit;
    uint8_t byPassCtrl;
    uint8_t txCtrl;
    uint8_t slCtrl;
    uint8_t reserved02[4];
    uint8_t reserved03[2];
    uint8_t userDataVersionM;
    uint8_t userDataVersionS;
    uint8_t safeSequCount[4];
    uint8_t safetyCode[4];
} ETB130;


typedef struct
{
    uint8_t versionM;
    uint8_t versionS;
    uint8_t deviceName[16];
    uint8_t etbnState;
    uint8_t etbnInaugState;
    uint8_t etbnPosition;
    uint8_t etbnRole;
    uint8_t etbInhibit;
    uint8_t etbLength;
    uint8_t etbShort;
    uint8_t etbLineState;
    uint8_t byPassState;
    uint8_t slState;
    uint8_t etbTopoCnt[4];
    uint8_t userDataVersionM;
    uint8_t userDataVersionS;
    uint8_t safeSequCount[4];
    uint8_t safetyCode[4];
} ETB131;

typedef struct
{
    uint8_t entryCnt[2];
    uint8_t  trnNetDir_1[20];
    uint8_t  trnNetDir_2[20];
    uint8_t etbTopoCnt[4];
} ETB133;


#endif // MYSTRUCT_H
