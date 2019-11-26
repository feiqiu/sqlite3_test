#ifndef _LXT_DB_H
#define _LXT_DB_H

#include "lxt_types.h"

#if defined(__cplusplus) || defined(c_plusplus)
extern "C"
{
#endif

typedef enum
{
	DB_DELETE_OLDEST, DB_DELETE_ALL, DB_DELETE_BUTT
} DB_DELETE_TYPE_E;

extern void DB_Init(void);

extern void DB_Uninit(void);

extern void DB_Write(uint8_t *pData, uint32_t u32Len);

extern void DB_Delete(DB_DELETE_TYPE_E enType);

extern int32_t DB_Read(uint8_t *pData, uint32_t u32MaxLen);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
