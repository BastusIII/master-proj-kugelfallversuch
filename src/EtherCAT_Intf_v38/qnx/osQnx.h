#include <sys/param.h>
#include <pthread.h>
#include <semaphore.h>

#define CONST const

#ifdef __BYTE_ORDER
# ifndef BYTE_ORDER
#  define BYTE_ORDER __BYTE_ORDER
# endif
# ifndef __LITTLE_ENDIAN
#  define LITTLE_ENDIAN __LITTLE_ENDIAN
# endif
# ifndef __BIG_ENDIAN
#  define BIG_ENDIAN __BIG_ENDIAN
# endif
#else // have no __BYTE_ORDER
# ifndef BYTE_ORDER
#  error make sure that either BYTEORDER or __BYTEORDER is defined for your architecture
# else
#  if !defined(LITTLE_ENDIAN) || !defined(BIG_ENDIAN)
#   error BYTE_ORDER is defined, but LITTLE_ENDIAN and/or BIG_ENDIAN is missing. Make sure these are defined for your architecture
#  endif // !defined(LITTLE_ENDIAN) || !defined(BIG_ENDIAN)
# endif //BYTE_ORDER
#endif /* __BYTE_ORDER */

//MF for unaligned ARMv7 access routines
#include <gulliver.h>

#if BYTE_ORDER == BIG_ENDIAN
# define SWAPDWORD_INPLACE(x) {char tmp; tmp = ((char*)&x)[0]; \
		((char*)&x)[0] = ((char*)&x)[3]; \
		((char*)&x)[3] = tmp; \
		tmp = ((char*)&x)[1]; \
		((char*)&x)[1] = ((char*)&x)[2]; \
		((char*)&x)[2] = tmp;}
#endif


#define HANDLE sem_t

#define SEM_POST(x) sem_post((x))
#define SEM_INIT(x,y,z) sem_init((x),(y),(z))
#define SEM_TIMEDWAIT(x,y,z) sem_timedwait((x),(y))
#define SEM_DESTROY(x) sem_destroy((x))
#define CLOCK_GETTIME(x,y) clock_gettime((x),(y))

typedef pthread_mutex_t mutexType_t;

typedef unsigned long long int u_int64;
