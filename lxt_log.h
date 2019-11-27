#ifndef _LXT_LOG_H
#define _LXT_LOG_H
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "lxt_types.h"

#if defined(__cplusplus) || defined(c_plusplus)
extern "C"
{
#endif

typedef enum LOG_LEVEL_E
{
	LOG_LEVEL_ALL, //
	LOG_LEVEL_DEBUG,
	LOG_LEVEL_INFO,
	LOG_LEVEL_IMP,
	LOG_LEVEL_WARN,
	LOG_LEVEL_ERR,
	LOG_LEVEL_ACCEL,
	LOG_LEVEL_GPS,
	LOG_LEVEL_GYRO,
	LOG_LEVEL_FAC,
	LOG_LEVEL_MAX
} LOG_LEVEL_E;

extern bool_t LOG_SetLvl(LOG_LEVEL_E enLevel);

extern void LOG_UartStr(char *pFmt, ...);

extern void LOG_PrintHex(LOG_LEVEL_E enLevel, char * pFile, const char * pFun, uint32_t u32Line, char *pInfo, uint8_t *pHex, uint32_t u32Len);

extern void LOG_PrintStr(LOG_LEVEL_E enLevel, char * pFile, const char * pFun, uint32_t u32Line, char *pFmt, ...);

#define  LOG_AllHex(pInfo, pHex, u32Len) 	LOG_PrintHex(LOG_LEVEL_ALL, basename(__FILE__), __FUNCTION__, __LINE__, pInfo, pHex, u32Len)

#define  LOG_DebugHex(pInfo, pHex, u32Len) 	LOG_PrintHex(LOG_LEVEL_DEBUG, basename(__FILE__), __FUNCTION__, __LINE__, pInfo, pHex, u32Len)

#define  LOG_ErrorHex(pInfo, pHex, u32Len) 	LOG_PrintHex(LOG_LEVEL_ERR, basename(__FILE__), __FUNCTION__, __LINE__, pInfo, pHex, u32Len)

#define  LOG_All(pFmt, ...) 				LOG_PrintStr(LOG_LEVEL_ALL, basename(__FILE__), __FUNCTION__, __LINE__, pFmt, ##__VA_ARGS__)

#define  LOG_Debug(pFmt, ...) 				LOG_PrintStr(LOG_LEVEL_DEBUG, basename(__FILE__), __FUNCTION__, __LINE__, pFmt, ##__VA_ARGS__)

#define  LOG_Uart(pFmt, ...) 				LOG_UartStr(pFmt, ##__VA_ARGS__)

#define  LOG_Info(pFmt, ...) 				LOG_PrintStr(LOG_LEVEL_INFO, basename(__FILE__), __FUNCTION__, __LINE__, pFmt, ##__VA_ARGS__)

#define  LOG_Imp(pFmt, ...) 				LOG_PrintStr(LOG_LEVEL_IMP, basename(__FILE__), __FUNCTION__, __LINE__, pFmt, ##__VA_ARGS__)

#define  LOG_Wrn(pFmt, ...)			 		LOG_PrintStr(LOG_LEVEL_WARN, basename(__FILE__), __FUNCTION__, __LINE__, pFmt, ##__VA_ARGS__)

#define  LOG_Err(pFmt, ...) 				LOG_PrintStr(LOG_LEVEL_ERR, basename(__FILE__), __FUNCTION__, __LINE__, pFmt, ##__VA_ARGS__)

#define  LOG_Accel(pFmt, ...) 				LOG_PrintStr(LOG_LEVEL_ACCEL, basename(__FILE__), __FUNCTION__, __LINE__, pFmt, ##__VA_ARGS__)

#define  LOG_Gps(pFmt, ...) 				LOG_PrintStr(LOG_LEVEL_GPS, basename(__FILE__), __FUNCTION__, __LINE__, pFmt, ##__VA_ARGS__)

#define  LOG_Gyro(pFmt, ...) 				LOG_PrintStr(LOG_LEVEL_GYRO, basename(__FILE__), __FUNCTION__, __LINE__, pFmt, ##__VA_ARGS__)

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif
#endif
