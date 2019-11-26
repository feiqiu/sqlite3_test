#ifndef _LXT_COMM_H
#define _LXT_COMM_H

#if defined(__cplusplus) || defined(c_plusplus)
extern "C"
{
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#endif

#ifndef MAX
#define MAX(a, b) (((a) < (b)) ? (b) : (a))
#endif

#ifndef MIN
#define MIN(a, b) (((a) > (b)) ? (b) : (a))
#endif

#ifndef SWAP
#define SWAP(a, b) (a=(a)+(b),b=(a)-(b),a=(a)-(b))
#endif

/** Mutex Lock */
#define MUTEX_Init(mutex)  		do { pthread_mutex_init(&mutex, NULL); } while(0)
#define MUTEX_Lock(mutex)       do { pthread_mutex_lock(&mutex); } while(0)
#define MUTEX_Unlock(mutex)     do { pthread_mutex_unlock(&mutex); } while(0)
#define MUTEX_Destroy(mutex)    do { pthread_mutex_destroy(&mutex); } while(0)

/** Cond */
#ifndef CONS_ABS_TIME_WAIT
#define COND_Init(cond) \
    do { \
            pthread_condattr_t condattr; \
            pthread_condattr_init(&condattr); \
            pthread_condattr_setclock(&condattr, CLOCK_MONOTONIC); \
            pthread_cond_init(&cond, &condattr); \
            pthread_condattr_destroy(&condattr); \
    }while(0)

#define COND_TimeWait(cond,mutex,usec) \
    do { \
            struct timespec ts = {.tv_sec=0,.tv_nsec=0}; \
            clock_gettime(CLOCK_MONOTONIC, &ts); \
            ts.tv_sec += (usec/1000000LL); \
            ts.tv_nsec += (usec*1000LL%1000000000LL); \
            pthread_cond_timedwait(&cond, &mutex, &ts); \
    }while(0)

#else
#define COND_Init(cond) \
    do { \
            pthread_cond_init(&cond, NULL); \
    }while(0)

#define COND_TimeWait(cond,mutex,usec) \
    do { \
            struct timespec ts = {.tv_sec=0,.tv_nsec=0}; \
            ts.tv_sec += (usec/1000000LL); \
            ts.tv_nsec += (usec*1000LL%1000000000LL); \
            pthread_cond_timedwait(&cond, &mutex, &ts); \
    }while(0)
#endif

#define COND_Wait(cond,mutex)            do { pthread_cond_wait(&cond,&mutex); } while(0)
#define COND_Signal(cond)                do { pthread_cond_signal(&cond); } while(0)
#define COND_Destroy(cond)               do { pthread_cond_destroy(&cond); } while(0)

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
