#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/time.h>
#include <time.h>

#include "lxt_types.h"
#include "lxt_log.h"

#define LXT_NONE         "\033[m"
#define LXT_RED          "\033[0;32;31m"
#define LXT_LIGHT_RED    "\033[1;31m"
#define LXT_GREEN        "\033[0;32;32m"
#define LXT_LIGHT_GREEN  "\033[1;32m"
#define LXT_BLUE         "\033[0;32;34m"
#define LXT_LIGHT_BLUE   "\033[1;34m"
#define LXT_DARY_GRAY    "\033[1;30m"
#define LXT_CYAN         "\033[0;36m"
#define LXT_LIGHT_CYAN   "\033[1;36m"
#define LXT_PURPLE       "\033[0;35m"
#define LXT_LIGHT_PURPLE "\033[1;35m"
#define LXT_BROWN        "\033[0;33m"
#define LXT_YELLOW       "\033[1;33m"
#define LXT_LIGHT_GRAY   "\033[0;37m"
#define LXT_WHITE        "\033[1;37m"

static LOG_LEVEL_E enLogLevel = LOG_LEVEL_IMP;

static char *szLogLevelStr[LOG_LEVEL_MAX] = { LXT_NONE"all", //
		LXT_NONE"debug", //
		LXT_YELLOW"info", //
		LXT_BLUE"imp", //
		LXT_GREEN"warn", //
		LXT_RED"error", //
		LXT_CYAN"accel", //
		LXT_PURPLE"gps", //
		LXT_BROWN"gyro", //
		LXT_NONE"fac" };

extern void LogUartStr(char *fmt, ...)
{
	va_list arg_ptr;

	va_start(arg_ptr, fmt);
	vfprintf(stdout, (char *) fmt, arg_ptr);
	va_end(arg_ptr);

	fprintf(stdout, "%s", "\r\n\r\n"LXT_NONE);
}

extern void LOG_PrintStr(LOG_LEVEL_E enLevel, char * pFile, const char * pFun, uint32_t u32Line, char *pFmt, ...)
{
	struct tm tm;
	struct timeval tv;
	va_list arg_ptr;

	if (enLogLevel > enLevel || enLevel >= LOG_LEVEL_MAX)
	{
		return;
	}

	if ((enLogLevel == LOG_LEVEL_FAC || enLogLevel == LOG_LEVEL_ACCEL || enLogLevel == LOG_LEVEL_GYRO || enLogLevel == LOG_LEVEL_GPS) //
	&& (enLogLevel != enLevel))
	{
		return;
	}

	if (!(enLogLevel == LOG_LEVEL_FAC || enLogLevel == LOG_LEVEL_ACCEL || enLogLevel == LOG_LEVEL_GYRO || enLogLevel == LOG_LEVEL_GPS) //
	&& (enLevel == LOG_LEVEL_FAC || enLevel == LOG_LEVEL_ACCEL || enLevel == LOG_LEVEL_GYRO || enLevel == LOG_LEVEL_GPS))
	{
		return;
	}

	gettimeofday(&tv, NULL);
	localtime_r(&tv.tv_sec, &tm);

	fprintf(stdout, "[%-5s %04d-%02d-%02d %02d:%02d:%02d %-10s %-15s %04u]:", //
			szLogLevelStr[enLevel], tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, pFile, pFun, u32Line);
	va_start(arg_ptr, pFmt);
	vfprintf(stdout, (char *) pFmt, arg_ptr);
	va_end(arg_ptr);
	fprintf(stdout, "%s", "\r\n\r\n"LXT_NONE);
}

extern void LOG_PrintHex(LOG_LEVEL_E enLevel, char * pFile, const char * pFun, uint32_t u32Line, char *pInfo, uint8_t *pHex, uint32_t u32Len)
{
	struct tm tm;
	struct timeval tv;
	uint32_t u32i = 0;
	char szBuffer[64] = { 0 };

	if (enLogLevel > enLevel || enLevel >= LOG_LEVEL_MAX)
	{
		return;
	}

	gettimeofday(&tv, NULL);
	localtime_r(&tv.tv_sec, &tm);
	fprintf(stdout, "[%-5s %04d-%02d-%02d %02d:%02d:%02d %-10s %-15s %04u]:%s:", //
			szLogLevelStr[enLevel], tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, pFile, pFun, u32Line, pInfo);

	for (u32i = 0; u32i < u32Len; u32i++)
	{
		snprintf(&szBuffer[(u32i % 16) * 3], 4, " %02X", pHex[u32i]);
		if ((u32i + 1) % 16 == 0)
		{
			fprintf(stdout, "%s", szBuffer);
			memset(szBuffer, 0x00, sizeof(szBuffer));
		}
	}

	if ((u32i % 16 != 0) && (u32i != 0))
	{
		fprintf(stdout, "%s", szBuffer);
	}

	fprintf(stdout, "%s", "\r\n\r\n"LXT_NONE);
}

extern bool_t LOG_SetLvl(LOG_LEVEL_E enLevel)
{
	if (enLevel >= LOG_LEVEL_MAX)
	{
		return false;
	}
	enLogLevel = enLevel;
	return true;
}
