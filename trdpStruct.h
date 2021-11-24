#ifndef TRDPSTRUCT_H
#define TRDPSTRUCT_H

#include "trdp_if_light.h"
#include "vos_thread.h"
/* --- globals ----------------------------------------------------------------- */

/* test modes */
typedef enum
{
    MODE_CALLER,                /* caller */
    MODE_REPLIER,               /* replier */
} Mode;

/* test types */
typedef enum
{
    TST_BEGIN,                  /* test begin */
    TST_NOTIFY_TCP,             /* notification - TCP */
    TST_NOTIFY_UCAST,           /* notification - unicast */
    TST_NOTIFY_MCAST,           /* notification - multicast */
    TST_REQREP_TCP,             /* request/reply - TCP */
    TST_REQREP_UCAST,           /* request/reply - unicast */
    TST_REQREP_MCAST_1,         /* request/reply - multicast (1 reply) */
    TST_REQREP_MCAST_N,         /* request/reply - multicast (? replies) */
    TST_REQREPCFM_TCP,          /* request/reply/confirm - TCP */
    TST_REQREPCFM_UCAST,        /* request/reply/confirm - unicast */
    TST_REQREPCFM_MCAST_1,      /* request/reply/confirm - multicast (1 reply) */
    TST_REQREPCFM_MCAST_N,      /* request/reply/confirm - multicast (? reps.) */
    TST_END,                    /* test end */
} Test;

/* test groups */
typedef enum
{
    TST_TCP         = 0x01,             /* execute TCP tests */
    TST_UCAST       = 0x02,             /* execute UDP unicast tests */
    TST_MCAST       = 0x04,             /* execute UDP multicast tests */
    TST_APROTO      = 0x07,             /* execute all protocols tests */
    TST_NOTIFY      = 0x10,             /* execute notification tests */
    TST_REQREP      = 0x20,             /* execute request/reply tests */
    TST_REQREPCFM   = 0x40,             /* execute request/reply/confirm tests */
    TST_APATTERN    = 0x70,             /* execute all patterns tests */
    TST_ALL         = 0x77,             /* execute all tests */
} Group;

/* test options */
typedef struct
{
    Mode            mode;               /* test mode */
    int             groups;             /* test groups */
    int             once;               /* single test cycle flag */
    unsigned        msgsz;              /* message dataset size [bytes] */
    unsigned        tmo;                /* message timeout [msec] */
    TRDP_URI_USER_T uri;                /* test URI */
    TRDP_IP_ADDR_T  srcip;              /* source (local) IP address */
    TRDP_IP_ADDR_T  dstip;              /* destination (remote) IP address */
    TRDP_IP_ADDR_T  mcgrp;              /* multicast group */
} Options;

/* test status */
typedef struct
{
    uintptr_t   test;                   /* test type executed */
    unsigned    err[TST_END];           /* errors counter */
    unsigned    counter;                /* test counter */
    TRDP_TIME_T tbeg;                   /* test begin time */
    TRDP_TIME_T tend;                   /* test end time */
} Status;

/* request codes */
typedef enum
{
    REQ_WAIT,                           /* wait request */
    REQ_SEND,                           /* send message request */
    REQ_NEXT,                           /* execute next test request */
    REQ_EXIT,                           /* exit the test */
    REQ_STATUS,                         /* print test status */
    REQ_DONE,                           /* call done */
} Code;

/* request record */
typedef struct
{
    Code            code;               /* request code */
    int             param;              /* parameter */
    TRDP_MD_INFO_T  msg;                /* message info */
    TRDP_FLAGS_T    flags;              /* flags */
} Record;

/* request/indication queue */
typedef struct
{
    Record      *head;                  /* head (first) record */
    Record      *tail;                  /* tail (last) record */
    unsigned    num;                    /* number of records */
    unsigned    cap;                    /* queue capacity */
    Record      rec[64];                /* space for records */
} Queue;


TRDP_MEM_CONFIG_T       memcfg;
TRDP_APP_SESSION_T      apph;
TRDP_MD_CONFIG_T        mdcfg;
TRDP_PROCESS_CONFIG_T   proccfg;

const unsigned          tick = 10;      /* 10 msec tick */
char        *buf;                       /* send buffer */
int         rescode = 0;                /* test result code */
Options     opts;                       /* test options */
Status      sts;                        /* test status */
Queue       queue;                      /* request/indication queue */


/* --- function prototypes ----------------------------------------------------- */
#include <QString>

void        setup_listeners (void);
void        exec_next_test (void);
void        print_status (void);
TRDP_ERR_T  send_msg (TRDP_MD_INFO_T    *msg,
                      TRDP_FLAGS_T      flags,QString str);
void        recv_msg (const TRDP_MD_INFO_T  *msg,
                      UINT8                 *data,
                      UINT32                size);
void        reply (const TRDP_MD_INFO_T *msg,
                   TRDP_MSG_T           type,
                   TRDP_FLAGS_T         flags);
void        confirm (const TRDP_MD_INFO_T   *msg,
                     TRDP_FLAGS_T           flags);
const char  *get_result_string (TRDP_ERR_T err);
const char  *get_msg_type_str (TRDP_MSG_T type);
void        print_log (void         *pRefCon,
                       VOS_LOG_T    category,
                       const CHAR8  *pTime,
                       const CHAR8  *pFile,
                       UINT16       line,
                       const CHAR8  *pMsgStr);
void    _set_color_red (void);
void    _set_color_green (void);
void    _set_color_blue (void);
void    _set_color_default (void);
void    _sleep_msec (int msec);
void    print (int          type,
               const char   *fmt,
               ...);
void    enqueue (Code           code,
                 int            param,
                 TRDP_MD_INFO_T *msg,
                 TRDP_FLAGS_T   flags);
void    dequeue (void);
int     process_data (void);
void    md_callback (void                   *ref,
                     TRDP_APP_SESSION_T     apph,
                     const TRDP_MD_INFO_T   *msg,
                     UINT8                  *data,
                     UINT32                 size);


#endif // TRDPSTRUCT_H
