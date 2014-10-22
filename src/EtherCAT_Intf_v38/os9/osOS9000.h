#ifndef __osOS9000H
#define __osOS9000H

#define CONST 

#ifdef HAWKEYE
#include <lib/slmlib.h>
#endif
#include <sys/endian.h>
#include <alarm.h>

#ifdef __cplusplus
#include <vector>
#include <iostream>
#endif

#include <semaphore.h>
#include <process.h>
#include <UNIX/os9time.h>
#include <types.h>

#define __FORCE_PACKED
#define __UNNAMED_STRUCTS


#undef _RWSTD_NO_NAMESPACE
#ifdef __attribute__(X)
#undef __attribute__(X)
#endif

#define __attribute__(X)
#ifndef __inline
#define __inline inline
#endif
#define WINAPI
#define ECDLL_EXPORT
#define __declspec(x)

#define MYMAXERRLEN 4096
#define HANDLE semaphore
#define ECAT36_SEMA_ALARM_SIG 258
#ifdef __cplusplus
extern "C" {
#endif
#define clockid_t u_int32
#define CLOCK_REALTIME 1
#define CLOCK_MONOTONIC 2
#define CLOCK_SOFTTIME 0
#define TIMER_ABSTIME 1
double mspTIC ();
u_int64 OS9usecSinceUnixStart(void);
u_int32 usec2TICS(u_int64 ); 
int mygettimeofday(struct timeval *,struct timezone *);
u_int64 myclock(void);
int clock_gettime( clockid_t clock_id, struct timespec * tp );
int clock_getres(clockid_t clock_id, struct timespec *res) ;
int clock_nanosleep( clockid_t clock_id,int flags,const struct timespec * rqtp, struct timespec * rmtp );
int nanosleep(const struct timespec *req, struct timespec *rem); 
int usleep (unsigned int usec);
#ifdef __cplusplus
}
#endif

#ifndef __cplusplus
#include <sysglob.h>
#endif

int _os9_ecat_sem_post(semaphore *x);
int _os9_ecat_sem_init(semaphore *x, u_int32 z);
int _os9_ecat_sem_timedwait(semaphore *x,u_int32 z);



void os9_printerr(char*);
void os9_printwarn(char*);
void os9_printinfo(char*);
void Hook_Error_Cnt(u_int64*);
void Hook_Warnings_Cnt(u_int64*);
void Hook_Protocol_Error_Cnt(u_int64*);
void Inc_Protocol_Error_Cnt();

extern char my_error_buf[];
#ifndef CONST
#define CONST
#endif

#ifndef EC_TRACE_ERR
#define EC_TRACE_ERR(fmt, args...) { sprintf(my_error_buf, fmt, ## args);os9_printerr(my_error_buf);}
#endif
#ifndef EC_TRACE_WARN
#define EC_TRACE_WARN(fmt, args...) { sprintf(my_error_buf, fmt, ## args);os9_printwarn(my_error_buf);}
#endif
#ifndef EC_TRACE_INFO
#define EC_TRACE_INFO(fmt, args...) { sprintf(my_error_buf, fmt, ## args);os9_printinfo(my_error_buf);}
#endif

#define SEM_POST(x) _os9_ecat_sem_post((x))
#define SEM_INIT(x,y,z) _os9_ecat_sem_init((x),(z))
//ras time is alarm based ret is zero if no timeout
#define SEM_TIMEDWAIT(x,y,z) _os9_ecat_sem_timedwait((x),(z))
#define SEM_DESTROY(x) _os_sema_term((x))

#ifndef ULONGLONG
#define ULONGLONG u_int64
#endif
#ifndef LONLONG
#define LONGLONG int64
#endif

#ifndef ULONGLONG
#define ULONGLONG u_int64
#endif
#ifndef LONLONG
#define LONGLONG int64
#endif
#ifndef BYTE
#define BYTE u_int8
#endif
typedef struct mutexImpl {
	semaphore sema;
	u_int32	threadid_who_has_mutex;
	u_int32 thread_who_has_mutex_recursive_count;
} mutexType_t;


#define MAKEWORD(a, b)      ((WORD)(((BYTE)((DWORD_PTR)(a) & 0xff)) | ((WORD)((BYTE)((DWORD_PTR)(b) & 0xff))) << 8))
#define MAKELONG(a, b)      ((LONG)(((WORD)((DWORD_PTR)(a) & 0xffff)) | ((DWORD)((WORD)((DWORD_PTR)(b) & 0xffff))) << 16))
#define LODWORD(l)           ((ULONG)((ULONGLONG)(l) & 0xffffffffLL))
#define HIDWORD(l)           ((ULONG)((ULONGLONG)(l) >> 32))
#define LOWORD(l)           ((USHORT)((ULONG)(l) & 0xffff))
#define HIWORD(l)           ((USHORT)((ULONG)(l) >> 16))
#define LOBYTE(w)           ((UCHAR)((USHORT)(w) & 0xff))
#define HIBYTE(w)           ((UCHAR)((USHORT)(w) >> 8))

#endif

