#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <algorithm>



#if (defined (WIN32) || defined (WIN64))
#pragma warning (disable: 4200)
#endif

#include <vector>

#include "trdp_if_light.h"
#include "vos_thread.h"

#include "trdpStruct.h"
#include "myStruct.h"

#include "opencv2/core/core.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/imgcodecs/legacy/constants_c.h>

#define UDP
#define TCPN
#define TCPRR
#define TCPRRC
#define MCAST
#define MCASTN


ETB103 *param103 = nullptr;
ETB105 *param105 = nullptr;
ETB107 *param107 = nullptr;
ETB109 *param109 = nullptr;
ETB111 *param111 = nullptr;
ETB131 *param131 = nullptr;
ETB133 *param133 = nullptr;
std::vector<uint8_t> imgBufVec;
int ImgRecOver=0;
int status = 0;// 当前接收状态
cv::Mat jpgImage;

/* --- convert trdp error code to string --------------------------------------- */

const char *get_result_string (TRDP_ERR_T err)
{
    static char buf[128];

    switch (err)
    {
       case TRDP_NO_ERR:
           return "TRDP_NO_ERR (no error)";
       case TRDP_PARAM_ERR:
           return "TRDP_PARAM_ERR (parameter missing or out of range)";
       case TRDP_INIT_ERR:
           return "TRDP_INIT_ERR (call without valid initialization)";
       case TRDP_NOINIT_ERR:
           return "TRDP_NOINIT_ERR (call with invalid handle)";
       case TRDP_TIMEOUT_ERR:
           return "TRDP_TIMEOUT_ERR (timeout)";
       case TRDP_NODATA_ERR:
           return "TRDP_NODATA_ERR (non blocking mode: no data received)";
       case TRDP_SOCK_ERR:
           return "TRDP_SOCK_ERR (socket error / option not supported)";
       case TRDP_IO_ERR:
           return "TRDP_IO_ERR (socket IO error, data can't be received/sent)";
       case TRDP_MEM_ERR:
           return "TRDP_MEM_ERR (no more memory available)";
       case TRDP_SEMA_ERR:
           return "TRDP_SEMA_ERR (semaphore not available)";
       case TRDP_QUEUE_ERR:
           return "TRDP_QUEUE_ERR (queue empty)";
       case TRDP_QUEUE_FULL_ERR:
           return "TRDP_QUEUE_FULL_ERR (queue full)";
       case TRDP_MUTEX_ERR:
           return "TRDP_MUTEX_ERR (mutex not available)";
       case TRDP_THREAD_ERR:
           return "TRDP_THREAD_ERR (thread error)";
       case TRDP_BLOCK_ERR:
           return "TRDP_BLOCK_ERR (system call would have blocked in blocking mode)";
       case TRDP_INTEGRATION_ERR:
           return "TRDP_INTEGRATION_ERR (alignment or endianess for selected target wrong)";
       case TRDP_NOCONN_ERR:
           return "TRDP_NOCONN:ERR (No TCP connection)";
       case TRDP_NOSESSION_ERR:
           return "TRDP_NOSESSION_ERR (no such session)";
       case TRDP_SESSION_ABORT_ERR:
           return "TRDP_SESSION_ABORT_ERR (session aborted)";
       case TRDP_NOSUB_ERR:
           return "TRDP_NOSUB_ERR (no subscriber)";
       case TRDP_NOPUB_ERR:
           return "TRDP_NOPUB_ERR (no publisher)";
       case TRDP_NOLIST_ERR:
           return "TRDP_NOLIST_ERR (no listener)";
       case TRDP_CRC_ERR:
           return "TRDP_CRC_ERR (wrong CRC)";
       case TRDP_WIRE_ERR:
           return "TRDP_WIRE_ERR (wire error)";
       case TRDP_TOPO_ERR:
           return "TRDP_TOPO_ERR (invalid topo count)";
       case TRDP_COMID_ERR:
           return "TRDP_COMID_ERR (unknown comid)";
       case TRDP_STATE_ERR:
           return "TRDP_STATE_ERR (call in wrong state)";
       case TRDP_APP_TIMEOUT_ERR:
           return "TRDP_APP_TIMEOUT_ERR (application timeout)";
       case TRDP_APP_REPLYTO_ERR:
           return "TRDP_APP_REPLYTO_ERR (application reply sent timeout)";
       case TRDP_APP_CONFIRMTO_ERR:
           return "TRDP_APP_CONFIRMTO_ERR (application confirm sent timeout)";
       case TRDP_REPLYTO_ERR:
           return "TRDP_REPLYTO_ERR (protocol reply timeout)";
       case TRDP_CONFIRMTO_ERR:
           return "TRDP_CONFIRMTO_ERR (protocol confirm timeout)";
       case TRDP_REQCONFIRMTO_ERR:
           return "TRDP_REQCONFIRMTO_ERR (protocol confirm timeout (request sender)";
       case TRDP_PACKET_ERR:
           return "TRDP_PACKET_ERR (Incomplete message data packet)";
       case TRDP_UNRESOLVED_ERR:
           return "TRDP_UNRESOLVED_ERR (URI was not resolved error)";
       case TRDP_XML_PARSER_ERR:
           return "TRDP_XML_PARSER_ERR (error while parsing XML file)";
       case TRDP_INUSE_ERR:
           return "TRDP_INUSE_ERR (Resource is in use error)";
       case TRDP_MARSHALLING_ERR:
           return "TRDP_MARSHALLING_ERR (Mismatch between source size and dataset size)";
       case TRDP_UNKNOWN_ERR:
           return "TRDP_UNKNOWN_ERR (unspecified error)";
    }
    sprintf(buf, "unknown error (%d)", err);
    return buf;
}

/* --- convert message type to string ------------------------------------------ */

const char *get_msg_type_str (TRDP_MSG_T type)
{
    switch (type)
    {
       case TRDP_MSG_MN: return "notification";
       case TRDP_MSG_MR: return "request";
       case TRDP_MSG_MP: return "reply";
       case TRDP_MSG_MQ: return "reply w/cfm";
       case TRDP_MSG_MC: return "confirm";
       default:;
    }
    return "?";
}


/* --- platform helper functions ----------------------------------------------- */
void _sleep_msec (int msec)
{
    vos_threadDelay(msec * 1000);
}


/* --- print text -------------------------------------------------------------- */
#include <QString>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

void printToUI(int type, QString str)
{
    QString resultStr;
    switch (type)
    {
       case -1:
		   resultStr = resultStr + "\n\n!!! : ";
           break;
       case -2:
           resultStr = resultStr + "<== : ";
           break;
       case -3:
           resultStr = resultStr + "<== : ";
           break;
       case -4:
           resultStr = resultStr + "!!! : ";
           break;
       case 0:
		   resultStr = resultStr + "    : ";
           break;
       case 1:
		   resultStr = resultStr + "--> : ";
           break;
       case 2:
		   resultStr = resultStr + "<-- : ";
           break;
    }
	resultStr = resultStr + str;
	resultStr = resultStr + "\n";
    //emit resultReady(resultStr);
    MainWindow::getIntance()->printStrToUI(resultStr);
}

/* --- enqueue/dequeue request or indication ----------------------------------- */

void enqueue (Code code, int param, TRDP_MD_INFO_T *msg, TRDP_FLAGS_T flags)
{
    if (queue.num == queue.cap)
    {
		printToUI(-4, "request/indication queue overflow");
        exit(1);
    }
    /* setup tail record */
    queue.tail->code    = code;
    queue.tail->param   = param;
    if (msg)
    {
        queue.tail->msg = *msg;
    }
    queue.tail->flags = flags;
    /* update tail pointer and number of records */
    queue.tail = queue.rec + ((queue.tail - queue.rec + 1) % queue.cap);
    ++queue.num;
}

void dequeue ()
{
    /* update head pointer and number of records */
    queue.head = queue.rec + ((queue.head - queue.rec + 1) % queue.cap);
    --queue.num;
}


/* --- MD callback function ---------------------------------------------------- */
static UINT32 countMQ = 0;
static UINT32 countMP = 0;

UINT32 countNotificationError = 0;
bool isTesting = false;
long test_tv_sec = 0;         /* seconds */
long test_tv_usec = 0;        /* and microseconds */

UINT32 all_CountNotificationError = 0;
long all_test_tv_sec = 0;         /* seconds */
long all_test_tv_usec = 0;        /* and microseconds */
UINT32 all_testedCount = 0;

void md_callback (void *ref, TRDP_APP_SESSION_T apph,
                  const TRDP_MD_INFO_T *msg, UINT8 *data, UINT32 size)
{
    uintptr_t test;
	QString str;
    QString str1;
    QString str2;
    QString str3;
    str.sprintf("md_callback(%p, %p, %p, %p, %u) - ref %p",
          ref, apph, msg, data, size, (msg != NULL ? msg->pUserRef : 0));
    qDebug()<<"    : "<<str;
    /* test number is encoded into user reference */
    test = (uintptr_t) (msg ? msg->pUserRef : 0);
    /* verify the callback is related to currently executed test */
//    if (msg == NULL || (opts.mode == MODE_CALLER && test != sts.test)) // 这里是自己后期 改的，如果有问题则把条件改回去
    if (msg == NULL )
    {
		str1.sprintf("unexpected callback ! - %s",get_result_string(TRDP_ERR_T(msg != NULL ? msg->resultCode : 0)));
		printToUI(-4,str1);
        sts.err[sts.test]++;
        return;
    }

    /* check result code */
    switch (msg->resultCode)
    {
       case TRDP_NO_ERR:
           /* mesage received */
           recv_msg(msg, data, size);
           break;

       case TRDP_REPLYTO_ERR:
       case TRDP_TIMEOUT_ERR:
            if(isTesting)
                countNotificationError = countNotificationError + 1;
			else
				all_CountNotificationError = all_CountNotificationError + 1;

            if(opts.mode == MODE_CALLER)
               MainWindow::getIntance()->sendMsgResultStrToUI(get_result_string(msg->resultCode));

           /* reply doesn't arrived */
           sts.err[sts.test]++;
		   str2.sprintf("error %s", get_result_string(msg->resultCode));
		   printToUI(-4,str2);
           break;

       default:
            if(isTesting)
                countNotificationError = countNotificationError + 1;
			else
				all_CountNotificationError = all_CountNotificationError + 1;

            if(opts.mode == MODE_CALLER)
               MainWindow::getIntance()->sendMsgResultStrToUI(get_result_string(msg->resultCode));
		   str3.sprintf("error %s", get_result_string(msg->resultCode));
		   printToUI(-4,str3);
           sts.err[sts.test]++;
           break;
    }
}

/* --- setup listeners --------------------------------------------------------- */

void setup_listeners ()
{
    TRDP_ERR_T  err;
    TRDP_LIS_T  lsnrh;

    if (opts.groups & TST_TCP) /* TCP listener */
    {
		QString str1;
	    str1.sprintf("register TCP listener on %s", vos_ipDotted(opts.srcip));
	    printToUI(1,str1);
        err = tlm_addListener(
                apph,                               /* session handle */
                &lsnrh,                             /* listener handle */
                (void *) TST_TCP,                   /* user reference */
                NULL,                               /* callback function */
                FALSE,                              /* no comId listener */
                0u,                                 /* comid (0 .. take all) */ // 接受所有comid发送的内容
                0u,                                 /* topo */
                0u,                                 /* topo */
                VOS_INADDR_ANY,
                VOS_INADDR_ANY,
                opts.srcip,                         /* destination IP address (is source of listener) */
                (TRDP_FLAGS_T) (TRDP_FLAGS_CALLBACK | TRDP_FLAGS_TCP), /* flags */
                NULL,
                opts.uri);                          /* destination URI */
        /* check for errors */
        if (err != TRDP_NO_ERR)
        {
            /* failure */
			QString str2;
	        str2.sprintf("tlm_addListener call error %s", get_result_string(err));
	        printToUI(-4,str2);
            sts.err[sts.test]++;
        }
    }
    if (opts.groups & TST_UCAST) /* UDP unicast listener */
    {
		QString str3;
	    str3.sprintf("register UDP/unicast listener on %s", vos_ipDotted(opts.srcip));
	    printToUI(1,str3);
        err = tlm_addListener(
                apph,                               /* session handle */
                &lsnrh,                             /* listener handle */
                (void *) TST_UCAST,                 /* user reference */
                NULL,                               /* callback function */
                FALSE,                              /* no comId listener */
                0u,                                 /* comid (0 .. take all) */
                0u,                                 /* topo */
                0u,                                 /* topo */
                VOS_INADDR_ANY,
                VOS_INADDR_ANY,
                opts.srcip,                         /* destination IP address */
                TRDP_FLAGS_CALLBACK,                /* flags */
                NULL,
                opts.uri);                          /* destination URI */
        /* check for errors */
        if (err != TRDP_NO_ERR)
        {
            /* failure */
		    QString str4;
	        str4.sprintf("tlm_addListener call error %s", get_result_string(err));
	        printToUI(-4,str4);
            sts.err[sts.test]++;
        }
    }
    if (opts.groups & TST_MCAST) /* UDP multicast listener */
    {
		QString str5;
	    str5.sprintf("register UDP/multicast listener on %s", vos_ipDotted(opts.mcgrp));
	    printToUI(1,str5);
        err = tlm_addListener(
                apph,                               /* session handle */
                &lsnrh,                             /* listener handle */
                (void *) TST_MCAST,                 /* user reference */
                NULL,                               /* callback function */
                FALSE,                              /* no comId listener */
                0u,                                  /* comid (0 .. take all) */
                0u,                                  /* topo */
                0u,                                  /* topo */
                VOS_INADDR_ANY,
                VOS_INADDR_ANY,
                opts.mcgrp,                         /* destination IP address */
                TRDP_FLAGS_CALLBACK,                /* flags */
                NULL,
                opts.uri);                          /* destination URI */
        /* check for errors */
        if (err != TRDP_NO_ERR)
        {
            /* failure */
			QString str6;
	        str6.sprintf("tlm_addListener call error %s", get_result_string(err));
	        printToUI(-4,str6);
            sts.err[sts.test]++;
        }
    }
}

/* --- reply to incoming request ----------------------------------------------- */

void reply (const TRDP_MD_INFO_T *request, TRDP_MSG_T type, TRDP_FLAGS_T flags)
{
    TRDP_MD_INFO_T reply;

    /* prepare confirm message */
    memset(&reply, 0, sizeof(reply));
    reply.msgType       = type;
    reply.comId         = request->comId + 1;
    reply.destIpAddr    = request->srcIpAddr;
    reply.numExpReplies = (type == TRDP_MSG_MQ) ? 1 : 0;
    memcpy(&reply.sessionId, &request->sessionId, sizeof(TRDP_UUID_T));
    strcpy(reply.destUserURI, request->srcUserURI);
    strcpy(reply.srcUserURI, request->destUserURI);

    if (flags & TRDP_FLAGS_TCP)
    {
        qDebug("replying TCP\n");
    }
    else
    {
        qDebug("replying UDP\n");
    }

    /* send message */
    send_msg(&reply, flags,"");
}

/* --- confirm incoming reply -------------------------------------------------- */

void confirm (const TRDP_MD_INFO_T *reply, TRDP_FLAGS_T flags)
{
    TRDP_MD_INFO_T confirm;

    /* prepare confirm message */
    memset(&confirm, 0, sizeof(confirm));
    confirm.msgType         = TRDP_MSG_MC;
    confirm.comId           = reply->comId + 1;
    confirm.destIpAddr      = reply->srcIpAddr;
    confirm.numExpReplies   = 0;
    memcpy(&confirm.sessionId, &reply->sessionId, sizeof(TRDP_UUID_T));
    strcpy(confirm.destUserURI, reply->srcUserURI);
    strcpy(confirm.srcUserURI, reply->destUserURI);

    if (flags & TRDP_FLAGS_TCP)
    {
        qDebug("confirming TCP\n");
    }
    else
    {
        qDebug("confirming UDP\n");
    }
    send_msg(&confirm, flags,"");
}

/* --- send message ------------------------------------------------------------ */

TRDP_ERR_T send_msg (TRDP_MD_INFO_T *msg, TRDP_FLAGS_T flags, QString str)
{
    TRDP_UUID_T uuid;
    TRDP_ERR_T  err = TRDP_UNKNOWN_ERR;
    QString str1;
    QString str2;
    QString str3;
    QString str4;
    QString str5;
    QString str6;
    QString str7;
    QString str8;
    QString str9;
    QString str10;

    str1.sprintf("sending %s to %s", get_msg_type_str(msg->msgType), vos_ipDotted(msg->destIpAddr));
	printToUI(1,str1);

    /* depending on message type */
    switch (msg->msgType)
    {
       case TRDP_MSG_MN:
           /* prepare data to send buffer */
            if(MainWindow::getIntance()->currentMode != 4){
               snprintf(buf, opts.msgsz, "<%u:%ub:%#x> ... %d (%s)", msg->comId,
                        opts.msgsz, 0, sts.counter++, get_msg_type_str(msg->msgType));
               str2 = QString("sending content:")+str;
               printToUI(0,str2);
            }
           /* send notification */
           err = tlm_notify(
                   apph,                            /* session handle */
                   (void *) sts.test,               /* user reference */
                   NULL,                            /* callback function */
                   msg->comId,                      /* comid */
                   msg->etbTopoCnt,                 /* topo */
                   msg->opTrnTopoCnt,               /* topo */
                   msg->srcIpAddr,                  /* source IP address */
                   msg->destIpAddr,                 /* destination IP address */
                   flags,                           /* flags */
                   NULL,                            /* send parameters */
                   (const UINT8*)str.toUtf8().data(),           /* dataset buffer */
                   str.toUtf8().size(),                 /* dataset size */
                   msg->srcUserURI,                 /* source URI */
                   msg->destUserURI);               /* destination URI */
           /* check for errors */
           if (err != TRDP_NO_ERR)
           {
               /* failure */
	           str3.sprintf("tlm_notify call error %s", get_result_string(err));
	           printToUI(-4,str3);
               sts.err[sts.test]++;
           }
           break;

       case TRDP_MSG_MR:
           /* prepare data to send buffer */
           snprintf(buf, opts.msgsz, "<%u:%ub:%#x> ... %d (%s)", msg->comId,
                    opts.msgsz, 0, sts.counter++, get_msg_type_str(msg->msgType));
           str4 = QString("sending content:")+str;
           printToUI(0,str4);
           /* send request */
           err = tlm_request(
                   apph,                            /* session handle */
                   (void *) sts.test,        /* user reference */
                   NULL,                            /* callback function */
                   &uuid,                           /* session id */
                   msg->comId,                      /* comid */
                   msg->etbTopoCnt,                 /* topo */
                   msg->opTrnTopoCnt,               /* topo */
                   msg->srcIpAddr,                  /* source IP address */
                   msg->destIpAddr,                 /* destination IP address */
                   flags,                           /* flags */
                   msg->numExpReplies,              /* number of expected replies */
                   opts.tmo * 1000,                 /* reply timeout [usec] */
                   NULL,                            /* send parameters */
                   (const UINT8*)str.toUtf8().data(),                   /* dataset buffer */
                   str.toUtf8().size(),                      /* dataset size */
                   msg->srcUserURI,                 /* source URI */
                   msg->destUserURI);               /* destination URI */
           /* check for errors */
           if (err != TRDP_NO_ERR)
           {
               /* failure */
	           str5.sprintf("tlm_request call error %s", get_result_string(err));
	           printToUI(-4,str5);
               sts.err[sts.test]++;
           }
           break;

       case TRDP_MSG_MP:
           /* prepare data to send buffer */
           snprintf(buf, opts.msgsz, "<%u:%ub:%#x> ... %d (%s)", msg->comId,
                    opts.msgsz, 0, sts.counter++, get_msg_type_str(msg->msgType));
	       str6.sprintf("%s", buf);
           /* send reply */
           err = tlm_reply(
                   apph,                            /* session handle */
                   (const TRDP_UUID_T *) &msg->sessionId,                /* session id */
                   msg->comId,                      /* comid */
                   0,                               /* user status */
                   NULL,                            /* send parameters */
                   (UINT8 *) buf,                   /* dataset buffer */
                   strlen(buf),                      /* dataset size */
                   NULL);                           /* srcURI */
           /* check for errors */
           if (err != TRDP_NO_ERR)
           {
               /* failure */
	           str7.sprintf("tlm_reply call error %s", get_result_string(err));
	           printToUI(-4,str7);
               sts.err[sts.test]++;
           }
           break;

       case TRDP_MSG_MQ:
           /* prepare data to send buffer */
           snprintf(buf, opts.msgsz, "<%u:%ub:%#x> ... %d (%s)", msg->comId,
                    opts.msgsz, 0, sts.counter++, get_msg_type_str(msg->msgType));
	       str8.sprintf("%s", buf);
           /* send reply */
           err = tlm_replyQuery(
                   apph,                            /* session handle */
                   (const TRDP_UUID_T *) &msg->sessionId,  /* session id */
                   msg->comId,                      /* comid */
                   0,                               /* user status */
                   opts.tmo * 1000,                 /* confirm timeout */
                   NULL,                            /* send parameters */
                   (UINT8 *) buf,                   /* dataset buffer */
                   strlen(buf),                      /* dataset size */
                   NULL);                           /* srcURI */
           /* check for errors */
           if (err != TRDP_NO_ERR)
           {
               /* failure */
			   str9.sprintf("tlm_replyQuery call error %s", get_result_string(err));
			   printToUI(-4,str9);
               sts.err[sts.test]++;
           }
           break;

       case TRDP_MSG_MC:
           /* send confirm */
           err = tlm_confirm(
                   apph,                            /* session handle */
                   (const TRDP_UUID_T *) &msg->sessionId,  /* session id */
                   (UINT16) msg->replyStatus,       /* reply status */
                   NULL);                           /* send parameters */

           /* check for errors */
           if (err != TRDP_NO_ERR)
           {
               /* failure */
			   str10.sprintf("tlm_confirm call error %s", get_result_string(err));
			   printToUI(-4,str10);
               sts.err[sts.test]++;
           }
           break;

       default:;
    }
    return err;
}



TRDP_ERR_T send_msg (TRDP_MD_INFO_T *msg, TRDP_FLAGS_T flags,std::vector<uint8_t> str)
{
    TRDP_ERR_T  err = TRDP_UNKNOWN_ERR;
    QString str1;
    QString str2;
    QString str3;

   /* send notification */
   err = tlm_notify(
           apph,                            /* session handle */
           (void *) sts.test,               /* user reference */
           NULL,                            /* callback function */
           msg->comId,                      /* comid */
           msg->etbTopoCnt,                 /* topo */
           msg->opTrnTopoCnt,               /* topo */
           msg->srcIpAddr,                  /* source IP address */
           msg->destIpAddr,                 /* destination IP address */
           flags,                           /* flags */
           NULL,                            /* send parameters */
           (const UINT8*)str.data(),           /* dataset buffer */
           str.size(),                 /* dataset size */
           msg->srcUserURI,                 /* source URI */
           msg->destUserURI);               /* destination URI */
   /* check for errors */
   if (err != TRDP_NO_ERR)
   {
       /* failure */
       str3.sprintf("tlm_notify call error %s", get_result_string(err));
       printToUI(-4,str3);
       sts.err[sts.test]++;
   }
    return err;
}
/* --- receive message --------------------------------------------------------- */
TRDP_TIME_T tbeg;                   /* test begin time */
TRDP_TIME_T tend;                   /* test end time */

void recv_msg (const TRDP_MD_INFO_T *msg, UINT8 *data, UINT32 size)
{
    /* print information about incoming message */
	QString str1;
    QString str;
    str1.sprintf("incoming %s: %u/%ub from %s",
          get_msg_type_str(msg->msgType), msg->comId, size,
          vos_ipDotted(msg->srcIpAddr));
    printToUI(2,str1); // 这里是接收到的信息的头信息
    if (size)
    {

		QString str2;
        if(MainWindow::getIntance()->currentMode != 4){ // 视频数据不显示
            str2 = QString("recv content:") + (char *)data;
            printToUI(0,str2);
        }

        // 将ETB模式下接受到的报文显示出来
        if(MainWindow::getIntance()->currentMode == 3){ // ETB模式
            // 解析接收到的数据
            // 通过数组大小来判断是一台机器还是多台机器
            switch (msg->comId) {
            case 103:
                param103 = new ETB103;
                param103->versionM = data[0];
                param103->versionS = data[1];
                param103->etbId    = data[2];
                param103->cstCnt   = data[3];
                std::copy(data+4, data+28, param103->cstList_1);
                if(size==56) {
                    std::copy(data+28, data+52, param103->cstList_2);
                    std::copy(data+52, data+56, param103->trnTopoCnt);
                }
                else {
//                    memset(param103->cstList_2, 0, 24);
                    std::copy(data+28, data+32, param103->trnTopoCnt);
                }

                break;
            case 105:
                param105->versionM=data[0];
                param105->versionS=data[1];
                param105->cstClass=data[2];
                std::copy(data+4, data+20, param105->cstId);
                std::copy(data+20, data+36, param105->cstType);
                std::copy(data+36, data+52, param105->cstOwner);
                std::copy(data+52, data+68, param105->cstUUID);
                std::copy(data+72, data+76, param105->cstProp);
                std::copy(data+78, data+80, param105->etbCnt);
                std::copy(data+80, data+84, param105->etbInfoList);
                std::copy(data+86, data+88, param105->vehCnt);
                std::copy(data+88, data+128, param105->vehInfoList);
                std::copy(data+130, data+132, param105->fctCnt);
                std::copy(data+132, data+252, param105->fctInfoList);
                std::copy(data+254, data+256, param105->ctrlCstCnt);
                std::copy(data+256, data+260, param105->cstTopoCnt);
            case 107:
                param107 = new ETB107;
                std::copy(data+2, data+4, param107->entryCnt);
                std::copy(data+4, data+24, param107->trnNetDir_1);
                if(size==46) {
                    std::copy(data+24, data+44, param107->trnNetDir_2);
                    std::copy(data+44, data+48, param107->etbTopoCnt);
                }
                else
                    std::copy(data+24, data+28, param107->etbTopoCnt);
                break;
            case 109:
                param109 = new ETB109;
                param109->versionM = data[0];
                param109->versionS = data[1];
                param109->etbId    = data[2];
                param109->opTrnOrient = data[3];
                param109->opCstCnt = data[7];
                std::copy(data+8, data+28, param109->opCstList_1);
                if(size==128) {
                    std::copy(data+28, data+48, param109->opCstList_2);
                    param109->opVehCnt = data[51];
                    std::copy(data+52, data+76, param109->opVehList_1);
                    std::copy(data+76, data+100, param109->opVehList_2);
                    std::copy(data+100, data+124, param109->opVehList_3);
                    std::copy(data+124, data+128, param109->opTrnTopoCnt);
                }
                else {
                    param109->opVehCnt = data[31];
                    std::copy(data+32, data+56, param109->opVehList_1);
                    std::copy(data+56, data+60, param109->opTrnTopoCnt);
                }

                break;
            case 111:
                param111 = new ETB111;
                param111->versionM = data[0];
                param111->versionS = data[1];
                param111->etbId    = data[4];
                param111->trnDirState = data[5];
                param111->opTrnDirState = data[6];
                std::copy(data+8, data+24, param111->trnId);
                std::copy(data+24, data+40, param111->trnOperator);
                std::copy(data+40, data+44, param111->opTrnTopoCnt);
                std::copy(data+44, data+48, param111->crc);
                param111->opTrnOrient = data[51];
                param111->opCstCnt = data[55];
                std::copy(data+56, data+76, param111->opCstList_1);
                if(size==280) {
                    std::copy(data+76, data+96, param111->opCstList_2);
                    param111->opVehCnt = data[99];
                    std::copy(data+100, data+124, param111->opVehList_1);
                    std::copy(data+124, data+148, param111->opVehList_2);
                    std::copy(data+148, data+172, param111->opVehList_3);
                    param111->cstCnt = data[179];
                    std::copy(data+180, data+204, param111->cstList_1);
                    std::copy(data+204, data+228, param111->cstList_2);
                    std::copy(data+228, data+232, param111->TrnTopoCnt);
                    std::copy(data+234, data+236, param111->entryCnt);
                    std::copy(data+236, data+256, param111->trnNetDir_1);
                    std::copy(data+256, data+276, param111->trnNetDir_2);
                    std::copy(data+276, data+280, param111->etbTopoCnt);
                }
                else {
                    param111->opVehCnt = data[79];
                    std::copy(data+80, data+104, param111->opVehList_1);
                    param111->cstCnt = data[111];
                    std::copy(data+112, data+136, param111->cstList_1);
                    std::copy(data+136, data+140, param111->TrnTopoCnt);
                    std::copy(data+142, data+144, param111->entryCnt);
                    std::copy(data+144, data+164, param111->trnNetDir_1);
                    std::copy(data+164, data+168, param111->etbTopoCnt);
                }

                break;
            case 131:
                param131 = new ETB131;
                param131->versionM = data[0];
                param131->versionS = data[1];
                std::copy(data+4, data+20, param131->deviceName);
                param131->etbnState = data[20];
                param131->etbnInaugState = data[21];
                param131->etbnPosition = data[22];
                param131->etbnRole = data[23];
                param131->etbInhibit = data[24];
                param131->etbLength = data[25];
                param131->etbShort = data[26];
                param131->etbLineState = data[27];
                param131->byPassState = data[28];
                param131->slState = data[29];
                std::copy(data+32, data+36, param131->etbTopoCnt);
                param131->userDataVersionM = data[42];
                param131->userDataVersionS = data[43];
                std::copy(data+44, data+48, param131->safeSequCount);
                std::copy(data+48, data+52, param131->safetyCode);
                break;
            case 133:
                param133 = new ETB133;
                std::copy(data+2, data+4, param133->entryCnt);
                std::copy(data+4, data+24, param133->trnNetDir_1);
                if(size==48) {
                    std::copy(data+24, data+44, param133->trnNetDir_2);
                    std::copy(data+44, data+48, param133->etbTopoCnt);
                }
                else
                    std::copy(data+24, data+28, param133->etbTopoCnt);
                break;
            default:
                break;
            }
        }
        // 视频传输模式
        else if(MainWindow::getIntance()->currentMode == 4){
            qDebug() << " what is this? " << QString::number(uint8_t(data[0]), 16) << "  " << QString::number(uint8_t(data[1]), 16) <<endl ;
            for(uint32_t i=0;i< size;++i){
                switch (status) {
                case 0:
                    if (0xFF == (unsigned char)(data[i]))
                        status++;
                    imgBufVec.clear();
                    imgBufVec.push_back(data[i]);
                    break;
                case 1:
                    if (0xD8 == (unsigned char)(data[i])) {
                        status++;
                        imgBufVec.push_back(data[i]);
                    }
                    else
                        status = 0;
                    break;
                case 2:
                    imgBufVec.push_back(data[i]);
                    if (0xFF == (unsigned char)(data[i]))
                        status++;
                    break;
                case 3:
                    imgBufVec.push_back(data[i]);
                    if (0xD9 == (unsigned char)(data[i])) // jpg接收完成
                    {
                        qDebug() << "received over a frame" << endl;
                        jpgImage = cv::imdecode(cv::Mat(imgBufVec), CV_LOAD_IMAGE_COLOR);
                        status = 0;
                    }
                    else
                        status = 2;
                    break;
                default:
                    break;
                }
            }
        }
    }

    qDebug()<<"recv_msg msg->msgType:"<<msg->msgType<<" msg->comId:"<<msg->comId;
    /* depending on message type */
    switch (msg->msgType)
    {
       case TRDP_MSG_MN:
           /* notification received */
           if(MainWindow::getIntance()->currentMode!=4)
                MainWindow::getIntance()->recvMsgStrToUI((char *)data);
           break;

       case TRDP_MSG_MR:
           /* request received */

           MainWindow::getIntance()->recvMsgStrToUI((char *)data);

           if(msg->comId == MainWindow::getIntance()->get_request_reply_TCP_COMID() ||
                   msg->comId == MainWindow::getIntance()->get_request_reply_unicast_COMID())
           {
               if(msg->comId == MainWindow::getIntance()->get_request_reply_TCP_COMID())
                 reply(msg, TRDP_MSG_MP, TRDP_FLAGS_CALLBACK|TRDP_FLAGS_TCP);
               else
                 reply(msg, TRDP_MSG_MP, TRDP_FLAGS_CALLBACK);
               countMP++;
           }
           else if(msg->comId == MainWindow::getIntance()->get_request_reply_confirm_TCP_COMID() ||
                        msg->comId == MainWindow::getIntance()->get_request_reply_confirm_unicast_COMID())
           {
               if(msg->comId == MainWindow::getIntance()->get_request_reply_confirm_TCP_COMID())
                 reply(msg, TRDP_MSG_MQ, TRDP_FLAGS_CALLBACK|TRDP_FLAGS_TCP);
               else
                 reply(msg, TRDP_MSG_MQ, TRDP_FLAGS_CALLBACK);
               countMQ++;
           }
           break;

       case TRDP_MSG_MP:
            /* time elapsed from test begin */
            vos_getTime(&tend);
            vos_subTime(&tend, &tbeg);
            /* call finished */
            str.sprintf("call done - %u.%03u sec",tend.tv_sec, tend.tv_usec / 1000);
			if(isTesting)
			{
				test_tv_sec = test_tv_sec + tend.tv_sec;
				test_tv_usec = test_tv_usec + tend.tv_usec;
			}
			else
			{
				all_test_tv_sec = all_test_tv_sec + tend.tv_sec;
				all_test_tv_usec = all_test_tv_usec + tend.tv_usec;
			}
            qDebug()<<"TRDP_MSG_MP "<<str;
            MainWindow::getIntance()->sendMsgResultStrToUI(str);
           /* reply received */
           switch (sts.test)
           {
              case TST_REQREP_TCP:
              case TST_REQREP_UCAST:
              case TST_REQREP_MCAST_1:
                  /* call finished */
                  break;
           }
           break;

       case TRDP_MSG_MQ:
           /* reply, confirm required */
           if(msg->comId == (MainWindow::getIntance()->get_request_reply_confirm_TCP_COMID()+1))
           {
               confirm(msg, TRDP_FLAGS_CALLBACK | TRDP_FLAGS_TCP);
           }
           else
           {
               confirm(msg, TRDP_FLAGS_CALLBACK);
           }
           /* time elapsed from test begin */
           vos_getTime(&tend);
           vos_subTime(&tend, &tbeg);
           /* call finished */
           str.sprintf("call done - %u.%03u sec",tend.tv_sec, tend.tv_usec / 1000);
			if(isTesting)
			{
				test_tv_sec = test_tv_sec + tend.tv_sec;
				test_tv_usec = test_tv_usec + tend.tv_usec;
			}
			else
			{
				all_test_tv_sec = all_test_tv_sec + tend.tv_sec;
				all_test_tv_usec = all_test_tv_usec + tend.tv_usec;
			}
           qDebug()<<"TRDP_MSG_MQ "<<str;
           MainWindow::getIntance()->sendMsgResultStrToUI(str);
           switch (sts.test)
           {
              case TST_REQREPCFM_TCP:
              case TST_REQREPCFM_UCAST:
              case TST_REQREPCFM_MCAST_1:
                  /* call finished */
                  break;
           }
           break;

       case TRDP_MSG_MC:
           /* confirm received */
           break;

       default:;
    }
}

#include "mainwindow.h"
//#include "ui_mainwindow.h"
//#include <QDebug>
#include <QThread>
#include <QTimer>
#include <QMessageBox>
#include <QTextCursor>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->hide();
    //currentWorkerThread = NULL;
    threadRunning = false;
    myselfMainWindow = this;

    connect(this,SIGNAL(AppendText(QString)),this,SLOT(SlotAppendText(QString)));

    setWindowTitle("caller");
    ui->label_7->setText("send msg:");

    ui->label_4->hide();
    ui->lineEdit_4->hide();

    db = QSqlDatabase::addDatabase("QSQLITE"); //数据库对象
    db.setHostName("127.0.0.1"); //设置数据库主机名
    db.setDatabaseName(QCoreApplication::applicationDirPath()+"/"+"bin.db"); //设置数据库名
    db.setUserName("root"); //设置数据库用户名
    db.setPassword("1234"); //设置数据库密码
    if (!db.open()) {
        qDebug() << "Error: Failed to connect database." << db.lastError();
    } else {
        qDebug() << "Succeed to connect database.";
    }

    // 创建历史记录
    query=QSqlQuery(db);
    if(!query.exec("CREATE TABLE binFile(id integer primary key, username varchar(10), time varchar(10), mode varchar(11), loss varchar(10), delay varchar(10), sendtext varchar(120))"))
        qDebug() << "bin表已存在" << endl;

    // 用户库
    query=QSqlQuery(db);
    if(!query.exec("CREATE TABLE userTable(id integer primary key, username varchar(10), password varchar(10), Admin bool)"))
        qDebug() << "用户表已存在";
    else
    {
        query.prepare("INSERT INTO userTable(id, username, password, Admin) VALUES(:id, :username, :password, :Admin)");
        query.bindValue(":username", "root");
        query.bindValue(":password", "123456");
        query.bindValue(":Admin", true);
        qDebug() << "插入表状态 " ;
        qDebug() <<  query.exec();
    }
    this->setWindowIcon(QIcon(":/qss/icon.ico"));
    Timer103 = new QTimer();
    VideoTimer = new QTimer();
    connect(Timer103, SIGNAL(timeout()),this,SLOT(showETBParam()));
    connect(VideoTimer, SIGNAL(timeout()),this,SLOT(videoSendAndShow()));
    Timer103->start(100);
    paramSetGet = new ParamDialog();
    currentMode = 0; // 默认第一页

    videoDia = new VideoDialog();

    userLogin=new LoginDialog(&db);
    connect(userLogin, SIGNAL(loginSuccess(QString)), this, SLOT(loginSuccess(QString)));
    userLogin->exec(); // 通过查看用户名是否为空判断是否往下进行
    if(UserName.size() == 0){
        QMessageBox::critical(this, "warning", "No username login, no function is useable!!!");
        ui->centralWidget->setDisabled(true);
    }

    selectMode=new SelectDialog();
    connect(selectMode, SIGNAL(sendMode(int)), this, SLOT(setMode(int)));
    selectMode->exec();
    currentMode = ui->ModeSelect->currentIndex();
}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow *MainWindow::getIntance()
{
    return myselfMainWindow;
}

void WorkerThread::run()
{
    TRDP_ERR_T      err;
    TRDP_FDS_T      rfds;
    TRDP_TIME_T     tv;
    INT32           noOfDesc;
    struct timeval  tv_null = { 0, 0 };
    int rv;

    printf("TRDP message data test program, version 0\n");
    emit resultReady("TRDP message data test program, version 0\n");
    //emit resultReady("TRDP message data test program, version 0\n");

    qDebug()<<"WorkerThread::run() m:"<<m;
    qDebug()<<"WorkerThread::run() sourceip:"<<sourceip;
    qDebug()<<"WorkerThread::run() destinationip:"<<destinationip;
    qDebug()<<"WorkerThread::run() mlticastip:"<<mlticastip;

/* initialize test status */
    memset(&sts, 0, sizeof(sts));
    sts.test = TST_BEGIN;

    if (m=="caller")
    {
        opts.mode = MODE_CALLER;
    }
    else if (m=="replier")
    {
        opts.mode = MODE_REPLIER;
    }
    else
    {
        printf("invalid program mode\n");
        emit resultReady("invalid program mode\n");
        return;
    }
/* initialize test options */
    opts.groups = TST_ALL;                                         /* run all test groups */
    opts.once   = 0;                                               /* endless test */
    opts.msgsz  = 64 * 1024 - 200;                                 /* message size [bytes] */
    opts.tmo    = 3000;                                            /* timeout [msec] */
    strncpy(opts.uri, "message.test", sizeof(opts.uri));           /* test URI */
    opts.srcip  = vos_dottedIP(sourceip.toLatin1());            /* source (local) IP address */
    opts.dstip  = vos_dottedIP(destinationip.toLatin1());            /* destination (remote) IP address */
    opts.mcgrp  = vos_dottedIP(mlticastip.toLatin1());            /* multicast group */
    if (!opts.srcip || !opts.dstip || !vos_isMulticast(opts.mcgrp))
    {
        printf("invalid input arguments\n");
        emit resultReady("invalid input arguments\n");
        return ;
    }
    /* initialize request queue */
    queue.head  = queue.rec;
    queue.tail  = queue.rec;
    queue.num   = 0;
    queue.cap   = sizeof(queue.rec) / sizeof(queue.rec[0]);

/* allocate send buffer */
    buf = (char *) malloc(opts.msgsz);
    if (!buf)
    {
        printf("out of memory\n");
        emit resultReady("out of memory\n");
        return;
    }

    memset(&memcfg, 0, sizeof(memcfg));
    memset(&proccfg, 0, sizeof(proccfg));
/* initialize TRDP protocol library */
    err = tlc_init(NULL, NULL, &memcfg);
    if (err != TRDP_NO_ERR)
    {
      printf("tlc_init() failed, err: %s\n", get_result_string(err));
      emit resultReady(QString("tlc_init() failed, err: ")+get_result_string(err)+"\n");
      return;
    }

    /* prepare default md configuration */
    mdcfg.pfCbFunction      = md_callback;
    mdcfg.pRefCon           = NULL;
    mdcfg.sendParam.qos     = 3;
    mdcfg.sendParam.ttl     = 64;
    mdcfg.sendParam.retries = 2;
    mdcfg.flags             = (TRDP_FLAGS_T) (TRDP_FLAGS_CALLBACK | TRDP_FLAGS_TCP);
    mdcfg.replyTimeout      = 1000 * opts.tmo;
    mdcfg.confirmTimeout    = 1000 * opts.tmo;
    mdcfg.connectTimeout    = 1000 * opts.tmo;
    mdcfg.udpPort           = 17225;
    mdcfg.tcpPort           = 17225;
    mdcfg.maxNumSessions    = 64;

/* open session */
   err = tlc_openSession(&apph, opts.srcip, 0, NULL, NULL, &mdcfg, &proccfg);
   if (err != TRDP_NO_ERR)
   {
       printf("tlc_openSession() failed, err: %s\n", get_result_string(err));
       emit resultReady(QString("tlc_openSession() failed, err: ")+get_result_string(err)+"\n");
       return;
   }
   switch (opts.mode)
   {
      case MODE_CALLER:
          /* begin testing */
        if(MainWindow::getIntance()->get_current_mode() == 3) //ETB 模式
            setup_listeners();
          break;
      case MODE_REPLIER:
          /* setup listeners */
          setup_listeners();
          break;
   }
   /* main test loop */
   // 所有的接受发送处理都在这个子线程循环中进行
  while (1)
  {
      FD_ZERO(&rfds);
      noOfDesc = 0;
      tlc_getInterval(apph, &tv, &rfds, &noOfDesc);
      rv = vos_select(noOfDesc + 1, &rfds, NULL, NULL, &tv_null);
      tlc_process(apph, &rfds, &rv);
      /* wait a while */
      _sleep_msec(tick);

  }
  qDebug()<<"WorkerThread::run() exit!!!";
  return;
}

void MainWindow::startWorkInAThread()
{
    QString m,sourceip,destinationip,mlticastip;
    m = ui->comboBox->currentText().trimmed();
    sourceip = ui->lineEdit_2->text().trimmed();
    destinationip = ui->lineEdit_3->text().trimmed();
    mlticastip = ui->lineEdit_4->text().trimmed();

    WorkerThread *workerThread = new WorkerThread();
    workerThread->m = m;
    workerThread->sourceip = sourceip;
    workerThread->destinationip = destinationip;
    workerThread->mlticastip = mlticastip;
    connect(workerThread, &WorkerThread::resultReady, this, &MainWindow::handleResults);
    connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
    workerThread->start(); // 开始多线程
}

void MainWindow::printStrToUI(QString str)
{
    qDebug()<<"MainWindow::printStrToUI() str:"<<str;
    handleResults(str);
}

void MainWindow::recvMsgStrToUI(QString str)
{
    ui->lineEdit_6->setText(str);
}

void MainWindow::sendMsgResultStrToUI(QString str)
{
    ui->label_9->setText(str);
}

void MainWindow::sendTestResultStrToUI(QString str)
{
   ui->label_15->setText(str);
}

uint MainWindow::get_request_reply_TCP_COMID()
{
    return ui->lineEdit_8->text().trimmed().toUInt();
}

uint MainWindow::get_request_reply_unicast_COMID()
{
    return ui->lineEdit_9->text().trimmed().toUInt();
}

uint MainWindow::get_request_reply_confirm_TCP_COMID()
{
    return ui->lineEdit_10->text().trimmed().toUInt();
}

uint MainWindow::get_request_reply_confirm_unicast_COMID()
{
    return ui->lineEdit_11->text().trimmed().toUInt();
}

void MainWindow::on_pushButton_clicked()
{
    if(ui->comboBox->currentText().trimmed() == "caller")
    {
        setWindowTitle("caller");
    }
    else if(ui->comboBox->currentText().trimmed() == "replier")
    {
        setWindowTitle("replier");
    }

    qDebug()<<"MainWindow::on_pushButton_clicked()";
    QRegExp regExp("\\b(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b");
    if(regExp.exactMatch(ui->lineEdit_2->text().trimmed()) == false ||
       regExp.exactMatch(ui->lineEdit_3->text().trimmed()) == false ||
       regExp.exactMatch(ui->lineEdit_4->text().trimmed()) == false)
    {
        QMessageBox::critical(this, "错误", "请填写好相应参数");
        return;
    }

    TRDP_IP_ADDR_T srcip  = vos_dottedIP(ui->lineEdit_2->text().trimmed().toLatin1());            /* source (local) IP address */
    TRDP_IP_ADDR_T dstip  = vos_dottedIP(ui->lineEdit_3->text().trimmed().toLatin1());            /* destination (remote) IP address */
    TRDP_IP_ADDR_T mcgrp  = vos_dottedIP(ui->lineEdit_4->text().trimmed().toLatin1());            /* multicast group */
    if (!srcip || !dstip || !vos_isMulticast(mcgrp))
    {
        QMessageBox::critical(this, "错误", "请填写好相应参数");
        return;
    }
    if(threadRunning == false)
    {
        startWorkInAThread(); // 开始多线程
        threadRunning = true;
        ui->pushButton->setText("停止工作");
    }
    else
        QApplication::quit(); // 退出程序

    if(ui->ModeSelect->currentIndex()==4 && ui->comboBox->currentText().trimmed() == "replier"){ // 图像传输，且为接收方
        VideoTimer->start(40);
        videoDia->show();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit_6->clear();
}

// 发送响应函数
void MainWindow::on_pushButton_3_clicked()
{
    QString currentModeStr;
    if(threadRunning == false)
    {
        QMessageBox::critical(this, "错误", "please click start work");
        return;
    }

    if(ui->lineEdit_5->text().size() <= 0)
    {
        QMessageBox::critical(this, "错误", "please set right comid");
        return;
    }

    int comid = ui->lineEdit_5->text().toInt();
    if(comid < 1000)
    {
        QMessageBox::critical(this, "错误", "please set right comid");
        return;
    }

    if(ui->lineEdit_7->text().size() <= 0)
    {
        QMessageBox::critical(this, "错误", "please set right comid");
        return;
    }

    int comid2 = ui->lineEdit_7->text().toInt();
    if(comid2 < 1000)
    {
        QMessageBox::critical(this, "错误", "please set right comid");
        return;
    }

    if(ui->lineEdit_8->text().size() <= 0)
    {
        QMessageBox::critical(this, "错误", "please set right comid");
        return;
    }

    int comid3 = ui->lineEdit_8->text().toInt();
    if(comid3 < 1000)
    {
        QMessageBox::critical(this, "错误", "please set right comid");
        return;
    }

    if(ui->lineEdit_9->text().size() <= 0)
    {
        QMessageBox::critical(this, "错误", "please set right comid");
        return;
    }

    int comid4 = ui->lineEdit_9->text().toInt();
    if(comid4 < 1000)
    {
        QMessageBox::critical(this, "错误", "please set right comid");
        return;
    }

    if(ui->lineEdit_10->text().size() <= 0)
    {
        QMessageBox::critical(this, "错误", "please set right comid");
        return;
    }

    int comid5 = ui->lineEdit_10->text().toInt();
    if(comid5 < 1000)
    {
        QMessageBox::critical(this, "错误", "please set right comid");
        return;
    }

    if(ui->lineEdit_11->text().size() <= 0)
    {
        QMessageBox::critical(this, "错误", "please set right comid");
        return;
    }

    int comid6 = ui->lineEdit_11->text().toInt();
    if(comid6 < 1000)
    {
        QMessageBox::critical(this, "错误", "please set right comid");
        return;
    }

    if(ui->lineEdit_6->text().trimmed().size() <= 0 && ui->ModeSelect->currentIndex() < 3) // ETB及之后的模式不需要在这个框内设置发送内容
    {
        QMessageBox::critical(this, "错误", "please set right send msg content");
        return;
    }

    int ETBcomid = ui->ETBComid->currentText().toInt();
    if(ui->ETBComid->currentText().size() <= 0)
    {
        QMessageBox::critical(this, "错误", "please set right comid");
        return;
    }
    if(ETBcomid > 140)
    {
        QMessageBox::critical(this, "错误", "please set right comid");
        return;
    }

    TRDP_MD_INFO_T  msg;
    TRDP_FLAGS_T    flags = TRDP_FLAGS_FORCE_CB;
    /* prepare request message */
    memset(&msg, 0, sizeof(msg));
    strcpy(msg.destUserURI, opts.uri);
    strcpy(msg.srcUserURI, opts.uri);

    QString sendStr = ui->lineEdit_6->text().trimmed();

    if(ui->comboBox_2->currentText()== "TCP" && ui->ModeSelect->currentIndex() == 0)
    {
        currentModeStr = "N-TCP";
        if ((opts.groups & TST_TCP) && (opts.groups & TST_NOTIFY))
        {
            QString str1;
            str1.sprintf("TEST -- notification - TCP");
            msg.msgType          = TRDP_MSG_MN;
            msg.comId            = comid;
            msg.destIpAddr       = opts.dstip;
            msg.numExpReplies    = 0;
            flags = (TRDP_FLAGS_T) (flags | TRDP_FLAGS_TCP);
        }
    }
    else if(ui->comboBox_2->currentText()== "unicast" && ui->ModeSelect->currentIndex() == 0)
    {
        currentModeStr = "N-unicast";
        if ((opts.groups & TST_UCAST) && (opts.groups & TST_NOTIFY))
        {
            QString str2;
            str2.sprintf("TEST -- notification - UDP - unicast");
            msg.msgType          = TRDP_MSG_MN;
            msg.comId            = comid2;
            msg.destIpAddr       = opts.dstip;
            msg.numExpReplies    = 0;
        }
    }
    else if(ui->comboBox_2->currentText()== "TCP" && ui->ModeSelect->currentIndex() == 1)
    {
        currentModeStr = "RR-TCP";
        if ((opts.groups & TST_TCP) && (opts.groups & TST_REQREP))
        {
            QString str4;
            str4.sprintf("TEST -- request/reply - TCP");
            msg.msgType          = TRDP_MSG_MR;
            msg.comId            = comid3;
            msg.destIpAddr       = opts.dstip;
            msg.numExpReplies    = 1;
            flags = (TRDP_FLAGS_T) (flags | TRDP_FLAGS_TCP);
        }
    }
    else if(ui->comboBox_2->currentText()== "unicast" && ui->ModeSelect->currentIndex() == 1)
    {
        currentModeStr = "RR-unicast";
        if ((opts.groups & TST_UCAST) && (opts.groups & TST_REQREP))
        {
            QString str5;
            str5.sprintf("TEST -- request/reply - UDP - unicast");
            msg.msgType          = TRDP_MSG_MR;
            msg.comId            = comid4;
            msg.destIpAddr       = opts.dstip;
            msg.numExpReplies    = 1;
        }
    }
    else if(ui->comboBox_2->currentText()== "TCP" && ui->ModeSelect->currentIndex() == 2)
    {
        currentModeStr = "RRC-TCP";
        if ((opts.groups & TST_TCP) && (opts.groups & TST_REQREPCFM))
        {
            QString str8;
            str8.sprintf("TEST -- request/reply/confirm - TCP");
            msg.msgType          = TRDP_MSG_MR;
            msg.comId            = comid5;
            msg.destIpAddr       = opts.dstip;
            msg.numExpReplies    = 1;
            flags = (TRDP_FLAGS_T) (flags | TRDP_FLAGS_TCP);
        }
    }
    else if(ui->comboBox_2->currentText()== "unicast" && ui->ModeSelect->currentIndex() == 2)
    {
        currentModeStr = "RRC-unicast";
        if ((opts.groups & TST_UCAST) && (opts.groups & TST_REQREPCFM))
        {
            QString str9;
            str9.sprintf("TEST -- request/reply/confirm - UDP - unicast");
            msg.msgType          = TRDP_MSG_MR;
            msg.comId            = comid6;
            msg.destIpAddr       = opts.dstip;
            msg.numExpReplies    = 1;
        }
    }

    //  ETB使用RR UDP方式，且发送内容固定,comid固定
    else if(ui->ModeSelect->currentIndex() == 3)
    {
        currentModeStr = "ETB";
        if ((opts.groups & TST_UCAST) && (opts.groups & TST_REQREP))
        {
            QString str5;
            str5.sprintf("TEST -- request/reply - UDP - unicast");
            msg.msgType          = TRDP_MSG_MR;
            msg.comId            = ui->ETBComid->currentText().toInt();
            msg.destIpAddr       = opts.dstip;
            msg.numExpReplies    = 1;
        }


        // 设置需要发送的内容
        if(ui->ETBComid->currentText().toInt() == 102)
            sendStr = ""; // 设置发送内容为空
        else if(ui->ETBComid->currentText().toInt() == 104) {
            sendStr = "";
            for (uint32_t i=0;i<sizeof (Etb104Param.param) ;++i )
                sendStr.append(Etb104Param.param[i]);
        }
        else if(ui->ETBComid->currentText().toInt() == 106){
            sendStr = "";
            sendStr.append(uint8_t(Etb106id));
        }
        else if(ui->ETBComid->currentText().toInt() == 108){
            sendStr = "";
        }
        else if(ui->ETBComid->currentText().toInt() == 110){
            sendStr = "";
            sendStr.append(uint8_t(Etb110id));
        }
        else if(ui->ETBComid->currentText().toInt() == 130){ // 这里有复杂数据需要处理
            sendStr = "";
            sendStr.append(Etb130Param.versionM);
            sendStr.append(Etb130Param.versionS);
            for (uint32_t i=0;i<sizeof (Etb130Param.reserved01) ;++i )
                sendStr.append(Etb130Param.reserved01[i]);
            for (uint32_t i=0;i<sizeof (Etb130Param.deviceName) ;++i )
                sendStr.append(Etb130Param.deviceName[i]);
            sendStr.append(Etb130Param.inhibit);
            sendStr.append(Etb130Param.byPassCtrl);
            sendStr.append(Etb130Param.txCtrl);
            sendStr.append(Etb130Param.slCtrl);
            for (uint32_t i=0;i<sizeof (Etb130Param.reserved02) ;++i )
                sendStr.append(Etb130Param.reserved02[i]);
            for (uint32_t i=0;i<sizeof (Etb130Param.reserved03) ;++i )
                sendStr.append(Etb130Param.reserved03[i]);
            sendStr.append(Etb130Param.userDataVersionM);
            sendStr.append(Etb130Param.userDataVersionS);
            for (uint32_t i=0;i<sizeof (Etb130Param.safeSequCount) ;++i )
                sendStr.append(Etb130Param.safeSequCount[i]);
            for (uint32_t i=0;i<sizeof (Etb130Param.safetyCode) ;++i )
                sendStr.append(Etb130Param.safetyCode[i]);
        }
        else if(ui->ETBComid->currentText().toInt() == 132){
            sendStr = "";
        }
    }

    // 发送视频
    else if(ui->ModeSelect->currentIndex() == 4){
        // 消息类型
        currentModeStr = "Video";

        QString videoaddr = ui->VideoAdr->text();
        videoaddr = videoaddr.replace('/',0x5c);
        videoCapture.open(videoaddr.toStdString());
        VideoTimer->start(40); // 25hz的刷新频率
        videoDia->show();

        // 只在数据库中记录文件名
        query=QSqlQuery(db);
        query.prepare("INSERT INTO binFile(id, username, time, mode, loss, delay, sendtext) VALUES(:id, :username, :time, :mode, :loss, :delay, :sendtext)");
        query.bindValue(":username", UserName);
        QString thisTime = QDate::currentDate().toString("yyyy-MM-dd");
        query.bindValue(":time", thisTime);
        query.bindValue(":mode", currentModeStr);

        // 这里记录视频文件名
        query.bindValue(":sendtext", ui->VideoAdr->text());
        query.exec();
    }

    if(msg.msgType == TRDP_MSG_MN)
    {
        /* store test begin time */
        vos_getTime(&tbeg);
    }
    /* send message */ // 在这里发送需要的数据
    if(ui->ModeSelect->currentIndex() != 4)
        send_msg(&msg, flags,sendStr);


    /* when sending notifications */
    if (msg.msgType == TRDP_MSG_MN) /* call done (no reply/timeout) */
    {
        /* time elapsed from test begin */
        vos_getTime(&tend);
        vos_subTime(&tend, &tbeg);
        /* call finished */

        QString str;
        str.sprintf("call done - %u.%03u sec",tend.tv_sec, tend.tv_usec / 1000);
        all_test_tv_sec = all_test_tv_sec + tend.tv_sec;
        all_test_tv_usec = all_test_tv_usec + tend.tv_usec;
        qDebug()<<"TRDP_MSG_MN "<<str;
        MainWindow::getIntance()->sendMsgResultStrToUI(str);
    }
    else
    {
        /* store test begin time */
        vos_getTime(&tbeg);
    }
    all_testedCount = all_testedCount + 1;
    QTimer::singleShot(3000, this, SLOT(showAllTestResultStrToUI()));

    // 数据库相关操作,视频传输过程不记录
    if(ui->ModeSelect->currentIndex() != 4)
    {
        query=QSqlQuery(db);
        query.prepare("INSERT INTO binFile(id, username, time, mode, loss, delay, sendtext) VALUES(:id, :username, :time, :mode, :loss, :delay, :sendtext)");
        query.bindValue(":username", UserName);
        QString thisTime = QDate::currentDate().toString("yyyy-MM-dd");
        query.bindValue(":time", thisTime);
        query.bindValue(":mode", currentModeStr);
        double loss = all_CountNotificationError*100/all_testedCount;
        QString lossStr = QString::number(loss) + "%";
        query.bindValue(":loss", lossStr);
        QString delayTime;
        delayTime.sprintf("%u.%03u",tend.tv_sec, tend.tv_usec / 1000);
        query.bindValue(":delay", delayTime);

        // str这里需要用空格间隔，待会弄
        QString dbStr;
        for (auto s : sendStr )
            dbStr = dbStr + QString::number(int(s.toLatin1()), 16) + " ";
        query.bindValue(":sendtext", dbStr);
        query.exec();
    }
}

#include <QProgressDialog>
#define TEST_COUNT (100)


void MainWindow::on_comboBox_currentIndexChanged(const QString &text)
{
    if(text == "caller")
    {
        setWindowTitle("caller");
        ui->label_7->setText("send msg:");
        ui->pushButton_3->show();
        ui->label_8->show();
        ui->label_9->show();
        ui->lineEdit_6->setReadOnly(false);
        ui->label_5->show();
        ui->comboBox_2->show();
        //ui->label_6->show();
        //ui->lineEdit_5->show();
        ui->label_15->show();
        ui->label_16->show();
    }
    else if(text == "replier")
    {
        setWindowTitle("replier");
        ui->label_7->setText("recv msg:");
        ui->pushButton_3->hide();
        ui->label_8->hide();
        ui->label_9->hide();
        ui->lineEdit_6->setReadOnly(true);
        ui->label_5->hide();
        ui->comboBox_2->hide();
        ui->label_15->hide();
        ui->label_16->hide();
        //ui->label_6->hide();
        //ui->lineEdit_5->hide();
    }
}

void MainWindow::showAllTestResultStrToUI()
{
    qDebug()<<"all_test_tv_sec:"<<all_test_tv_sec;
    qDebug()<<"all_test_tv_usec 1:"<<all_test_tv_usec;
    all_test_tv_usec = all_test_tv_usec + all_test_tv_sec*1000*1000;
    qDebug()<<"all_test_tv_usec 2:"<<all_test_tv_usec;

    long all_avg_usec = all_test_tv_usec/all_testedCount;
    qDebug()<<"all_avg_usec:"<<all_avg_usec;
    long all_avgSecond = all_avg_usec/1000000;
    qDebug()<<"all_avgSecond:"<<all_avgSecond;
    long all_leftUsec = all_avg_usec%1000000;
    qDebug()<<"all_leftUsec:"<<all_leftUsec;

    QString all_testSendResStr;
    all_testSendResStr.sprintf("Click all_testedCount:%d drop:%d(%) avgTime:%u.%03u sec", all_testedCount,all_CountNotificationError*100/all_testedCount,all_avgSecond,all_leftUsec/1000);
    sendTestResultStrToUI(all_testSendResStr);
    qDebug()<<"all_Test finished count Error:"<<all_CountNotificationError;
    qDebug()<<"all_Test finished all_testedCount:"<<all_testedCount;
}

void MainWindow::handleResults(const QString &result)
{
    emit AppendText(result);
}

void MainWindow::SlotAppendText(const QString &text)
{
    ui->editLog->appendPlainText(text);
}

void MainWindow::handleThreadFinished()
{
#if 0
    if(currentWorkerThread != NULL)
    {
        currentWorkerThread->deleteLater();
        currentWorkerThread = NULL;
    }
#endif
}

void MainWindow::loginSuccess(QString user)
{
    UserName = user;
    qDebug() << "UserName" << UserName << endl;
}

void MainWindow::setMode(int mode)
{
    ui->ModeSelect->setCurrentIndex(mode);
}

int  MainWindow::get_current_mode()
{
    return ui->ModeSelect->currentIndex();
}

void MainWindow::on_ParamSet_clicked()
{
    connect(paramSetGet, SIGNAL(get104ParamFromDialog(ETB104)), this, SLOT(setEtb104Param(ETB104)));
    connect(paramSetGet, SIGNAL(get106ParamFromDialog(uint8_t)), this, SLOT(setEtb106Param(uint8_t)));
    connect(paramSetGet, SIGNAL(get110ParamFromDialog(uint8_t)), this, SLOT(setEtb110Param(uint8_t)));
    connect(paramSetGet, SIGNAL(get130ParamFromDialog(ETB130)), this, SLOT(setEtb130Param(ETB130)));

    switch (ui->ETBComid->currentIndex()) {
    case 1: // 102
        paramSetGet->setCurrentComidTab(0);
        break;
    case 2: // 104
        paramSetGet->setCurrentComidTab(2);
        break;
    case 3: // 106
        paramSetGet->setCurrentComidTab(4);
        break;
    case 4: // 108
        paramSetGet->setCurrentComidTab(6);
        break;
    case 5: // 110
        paramSetGet->setCurrentComidTab(8);
        break;
    case 6: // 130
        paramSetGet->setCurrentComidTab(10);
        break;
    case 7: // 132
        paramSetGet->setCurrentComidTab(12);
        break;
    default:
        paramSetGet->setCurrentComidTab(0);
        break;
    }
    paramSetGet->show();
}

// 三个信号槽函数
void MainWindow::setEtb104Param(ETB104 etbid) {
    Etb104Param=etbid;
}

void MainWindow::setEtb106Param(uint8_t etbid)
{
    Etb106id = etbid;
}
void MainWindow::setEtb110Param(uint8_t etbid)
{
    Etb110id = etbid;
}
void MainWindow::setEtb130Param(ETB130  etb130)
{
    Etb130Param = etb130;
}

void MainWindow::on_ModeSelect_currentChanged(int index)
{
    currentMode = index;
}

void MainWindow::showETBParam()
{
    if(param103 != nullptr){
        paramSetGet->set103ParamToDialog(param103);
        delete param103;
        param103 = nullptr;
        paramSetGet->show();
    }
    else if(param105 != nullptr){
        paramSetGet->set105ParamToDialog(param105);
        delete param105;
        param105 = nullptr;
        paramSetGet->show();
    }
    else if(param107 != nullptr){
        paramSetGet->set107ParamToDialog(param107);
        delete param107;
        param107 = nullptr;
        paramSetGet->show();
    }
    else if(param109 != nullptr){
        paramSetGet->set109ParamToDialog(param109);
        delete param109;
        param109 = nullptr;
        paramSetGet->show();
    }
    else if(param111 != nullptr){
        paramSetGet->set111ParamToDialog(param111);
        delete param111;
        param111 = nullptr;
        paramSetGet->show();
    }
    else if(param131 != nullptr){
        paramSetGet->set131ParamToDialog(param131);
        delete param131;
        param131 = nullptr;
        paramSetGet->show();
    }
    else if(param133 != nullptr){
        paramSetGet->set133ParamToDialog(param133);
        delete param133;
        param133 = nullptr;
        paramSetGet->show();
    }
}

void MainWindow::on_HistoryButton_clicked()
{
    HistoryDialog *test = new HistoryDialog;
    test->exec();
}

const uchar *pSrc;

void MainWindow::videoSendAndShow()
{
    std::vector<uint8_t> jpgbuff;
    std::vector<int> param = std::vector<int>(2);
    param[0] = CV_IMWRITE_JPEG_QUALITY;
    param[1] = 95;
    std::string stdStrJpg;
    QString imageJpgStr;
    TRDP_MD_INFO_T  msg;
    TRDP_FLAGS_T    flags = TRDP_FLAGS_FORCE_CB;
    memset(&msg, 0, sizeof(msg));
    strcpy(msg.destUserURI, opts.uri);
    strcpy(msg.srcUserURI, opts.uri);
    QStringList strList;
    switch (opts.mode)
    {
       case MODE_CALLER:
           videoCapture >> jpgImage;
           if(!jpgImage.empty()){
               cv::resize(jpgImage, jpgImage, cv::Size(320,240));
               pSrc = (const uchar*)jpgImage.data;
               image_receive = new QImage(pSrc, jpgImage.cols, jpgImage.rows, jpgImage.step, QImage::Format_RGB888);
               videoDia->VideoShow(image_receive);
               // 编码
               cv::imencode(".jpg", jpgImage, jpgbuff, param);

               if ((opts.groups & TST_UCAST) && (opts.groups & TST_NOTIFY))
               {
                   msg.msgType          = TRDP_MSG_MN;
                   msg.comId            = ui->VideoComid->text().toInt();
                   msg.destIpAddr       = opts.dstip;
                   msg.numExpReplies    = 0;
               }
                send_msg(&msg, flags,jpgbuff);
           }
           break;
       case MODE_REPLIER: // caller在这里需要进行解码操作，但是应该先判断
           if(jpgImage.size().height == 240){ // 当前有有效图像
               pSrc = (const uchar*)jpgImage.data;
               image_receive = new QImage(pSrc, jpgImage.cols, jpgImage.rows, jpgImage.step, QImage::Format_RGB888);
               videoDia->VideoShow(image_receive);
           }
           break;
    }
}

void MainWindow::on_VideoStop_clicked()
{
    VideoTimer->stop();
    videoDia->close();
}

void MainWindow::on_VideoSelect_clicked()
{
    QString filePath = QCoreApplication::applicationDirPath();
    QString filename = QFileDialog::getOpenFileName(this, tr("选择目标视频"), filePath, tr("视频文件(*avi)"));
    ui->VideoAdr->setText(filename);
}
