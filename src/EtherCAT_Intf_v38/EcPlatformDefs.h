#ifndef	__ECPLATFORMDEFS_H__
#define	__ECPLATFORMDEFS_H__
//****************************************************************************/
//                                                                           */
//     File   : EcPlatformDefs.h                                             */
//                                                                           */
//     Content: Platform specific defines for EtherCAT Master Lib            */
//                                                                           */
//     Author : Max Fischer                                                  */
//                                                                           */
//     Date   : 3. 1. 2013                                                   */
//                                                                           */
//****************************************************************************/

//**************************** MACROS ****************************************/

///\cond never
//MF from EcGlobal.h
#ifndef BASETYPES
#define BASETYPES
typedef unsigned long long ULONGLONG;
typedef unsigned long ULONG;
typedef ULONG *PULONG;
typedef unsigned short USHORT;
typedef USHORT *PUSHORT;
typedef unsigned char UCHAR;
typedef UCHAR *PUCHAR;
typedef char *PSZ;
typedef unsigned int DWORD;
#endif  /* !BASETYPES */
#ifndef _DEFINED_BOOL
# define _DEFINED_BOOL
typedef int BOOL;
# ifndef TRUE
#  define TRUE 1
#  define FALSE 0
# endif
#endif
typedef unsigned char BYTE;
typedef unsigned char* PBYTE;
#ifndef PCHAR
typedef char* PCHAR;
#endif
typedef unsigned short int USHORT;
typedef unsigned short int * PUSHORT;
typedef unsigned long int ULONG;
typedef int INT;
#ifndef HRESULT
typedef long int HRESULT;
#endif

#define MAKEWORD(a, b)      ((WORD)(((BYTE)((DWORD_PTR)(a) & 0xff)) | ((WORD)((BYTE)((DWORD_PTR)(b) & 0xff))) << 8))
#define MAKELONG(a, b)      ((LONG)(((WORD)((DWORD_PTR)(a) & 0xffff)) | ((DWORD)((WORD)((DWORD_PTR)(b) & 0xffff))) << 16))
#define LODWORD(l)           ((ULONG)((ULONGLONG)(l) & 0xffffffffLL))
#define HIDWORD(l)           ((ULONG)((ULONGLONG)(l) >> 32))
#define LOWORD(l)           ((USHORT)((ULONG)(l) & 0xffff))
#define HIWORD(l)           ((USHORT)((ULONG)(l) >> 16))
#define LOBYTE(w)           ((UCHAR)((USHORT)(w) & 0xff))
#define HIBYTE(w)           ((UCHAR)((USHORT)(w) >> 8))



#ifdef LINUX
#include "linux/osLinux.h" //MF the OS specific stuff should go here, e.g. RS type padding macros
#endif
#ifdef XENOMAI
#include "xenomai/osXenomai.h" //MF the OS specific stuff should go here, e.g. RS type padding macros
#endif
#ifdef MACOSX
#include "macosx/osMacOSX.h" //MF the OS specific stuff should go here, e.g. RS type padding macros
#endif
#ifdef QNX
#include "qnx/osQnx.h" //MF the OS specific stuff should go here, e.g. RS type padding macros
#endif
#ifdef OS9
#include "os9/osOS9000.h" //MF the OS specific stuff should go here, e.g. RS type padding macros
#endif



//LITTLE or BIG Endian?
#ifndef BYTE_ORDER
# error Make sure that 'youros/osYouros.h' defines BYTE_ORDER
#endif
#if BYTE_ORDER == LITTLE_ENDIAN
# ifndef _LIL_END
# define _LIL_END
# endif
#else
# if BYTE_ORDER != BIG_ENDIAN
#  error Make sure that 'youros/osYouros.h' defines BYTE_ORDER either as LITTLE_ENDIAN or as BIG_ENDIAN (example: see linux/osLinux.h)
# endif
#endif
// __FORCE_PACKED is to be defined by #define __FORCE_PACKED if
// the compiler doesnot support __attribute__ (packed) to pack
// struct componennts space free together in one piece
#ifndef _LIL_END
/* here it goes _BIG_END */
# ifndef	SWAPWORD
#  define  SWAPWORD(w)	(HIBYTE((w)) | (LOBYTE((w)) << 8))
# endif
# ifndef	SWAPDWORD
#  define  SWAPDWORD(d)	(SWAPWORD(HIWORD(d)) | (SWAPWORD(LOWORD(d)) << 16))
# endif
# ifndef	SWAPWORD_INPLACE
#  define  SWAPWORD_INPLACE(w)	((w)=(HIBYTE((w)) | (LOBYTE((w)) << 8)))
# endif
# ifndef	SWAPDWORD_INPLACE
#  define  SWAPDWORD_INPLACE(d) ((d)=(SWAPWORD_ALWAYS(HIWORD((ULONG)(d))) | (SWAPWORD_ALWAYS(LOWORD((ULONG)(d))) << 16)))
# endif
# ifndef	SWAPDDWORD_INPLACE
#  define  SWAPDDWORD_INPLACE(dd) ((dd)=(((ULONGLONG)SWAPDWORD_ALWAYS(HIDWORD((dd)))& 0x00000000ffffffffLL) | ( 0xffffffff00000000LL& ((ULONGLONG)SWAPDWORD_ALWAYS(LODWORD(dd)) << 32) )))
# endif

#else /* LITTLEENDIAN */
# ifndef	SWAPWORD
#  define SWAPWORD(w)  (w)
# endif
# ifndef	SWAPDWORD
#  define SWAPDWORD(d) (d)
# endif
# ifndef	SWAPWORD_INPLACE
#  define  SWAPWORD_INPLACE(w)
# endif
# ifndef	SWAPDWORD_INPLACE
#  define  SWAPDWORD_INPLACE(d)
# endif
# ifndef	SWAPDDWORD_INPLACE
#  define  SWAPDDWORD_INPLACE(dd)
# endif

#endif

#ifndef	SWAPWORD_ALWAYS
# define  SWAPWORD_ALWAYS(w)	(HIBYTE((w)) | (LOBYTE((w)) << 8))
#endif
#ifndef	SWAPDWORD_ALWAYS
# define  SWAPDWORD_ALWAYS(d)	(SWAPWORD_ALWAYS(HIWORD(d)) | (SWAPWORD_ALWAYS(LOWORD(d)) << 16))
#endif

//MF101204 arm7 needs some alignment on internal data structures; as this is more robust, we do it for all platforms
#define MF_ALIGN4(x) ((((x)+3)/4)*4)

//MF20110710 ARMv7 unaligned access fixes in QNX: QNX defines these in gulliver.h, other OS don't need them...
#ifndef UNALIGNED_RET16
#define UNALIGNED_RET16(ptr) (*ptr)
#define UNALIGNED_RET32(ptr) (*ptr)
#define UNALIGNED_RET64(ptr) (*ptr)
#define UNALIGNED_PUT16(ptr,val)  *ptr = val;
#define UNALIGNED_PUT32(ptr,val)  *ptr = val;
#define UNALIGNED_PUT64(ptr,val)  *ptr = val;
#endif


#ifndef __FORCE_PACKED
#define OS9S2L(x) (x)
#define OS9B2S(x) (x)
#else
#define __attribute__(X)
#define __inline inline
#define OS9S2L(x) (*((ULONG*)&(x)))
#define OS9B2S(x) (*((USHORT*)&(x)))
#endif

// __UNNAMED_STRUCTS is to be define by #define __UNNAMED_STRUCTS if
// the compiler does not support unnamed structs within structs if the struct component names 
// are uniq
#ifndef __UNNAMED_STRUCTS
#define SOS9(x)
#define SOS9A(x)
#else
#define SOS9(x) foo ## x
#define SOS9A(x) foo ## x.
#endif

#endif //__ECPLATFORMDEFS_H__
