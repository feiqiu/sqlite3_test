#include <stdio.h>
#include <pthread.h>
#include "sqlite3.h"
#include "lxt_check.h"
#include "lxt_log.h"
#include "lxt_types.h"
#include "lxt_db.h"
#include "lxt_comm.h"

#define DB_PATH		"db.s3db"
#define DB_CREATE	("CREATE TABLE IF NOT EXISTS [post] ([hex] BLOB  NOT NULL)")
#define DB_TRIGGER  ("CREATE TRIGGER IF NOT EXISTS [recover]\n" \
					"AFTER INSERT ON [post]\n" \
					"FOR EACH ROW\n"\
					"BEGIN\n"\
					"\n"\
					"delete from post where \"oid\" in (select \"oid\" from post order by \"oid\" desc limit -1 offset 8000);"\
					"\n"\
					"END")

#define DB_SYNCHRONOUS	("PRAGMA synchronous = FULL")

typedef struct
{
	pthread_mutex_t Mutex;
	sqlite3 * dbHandle;
} DB_ST;

static DB_ST stDb = { .Mutex = PTHREAD_MUTEX_INITIALIZER, .dbHandle = NULL };

extern void DB_Init(void)
{
	int32_t s32Ret = SQLITE_ERROR;

	MUTEX_Lock(stDb.Mutex);
	if (stDb.dbHandle != NULL)
	{
		goto end;
	}

	s32Ret = sqlite3_open(DB_PATH, &stDb.dbHandle);
	CHECK_EQGoEnd(s32Ret, SQLITE_OK);

	s32Ret = sqlite3_exec(stDb.dbHandle, DB_CREATE, NULL, NULL, NULL);
	CHECK_EQGoEnd(s32Ret, SQLITE_OK);

	s32Ret = sqlite3_exec(stDb.dbHandle, DB_SYNCHRONOUS, NULL, NULL, NULL);
	CHECK_EQGoEnd(s32Ret, SQLITE_OK);

	s32Ret = sqlite3_exec(stDb.dbHandle, DB_TRIGGER, NULL, NULL, NULL);
	CHECK_EQGoEnd(s32Ret, SQLITE_OK);

	end : ;
	MUTEX_Unlock(stDb.Mutex);
}

extern void DB_Uninit(void)
{
	MUTEX_Lock(stDb.Mutex);
	if (stDb.dbHandle)
	{
		sqlite3_close(stDb.dbHandle);
	}
	stDb.dbHandle = NULL;
	MUTEX_Unlock(stDb.Mutex);
}

extern void DB_Write(uint8_t *pData, uint32_t u32Len)
{
	CHECK_PtrRetVoid(pData);
	CHECK_GTRetVoid(u32Len, 0);
	CHECK_PtrRetVoid(stDb.dbHandle);

	sqlite3_stmt *pstStmt = NULL;
	char szStrPre[255] = { 0 };
	int32_t s32Ret = SQLITE_ERROR;

	MUTEX_Lock(stDb.Mutex);
	snprintf(szStrPre, sizeof(szStrPre), "%s", "INSERT INTO post (\"hex\") VALUES (?)");

	s32Ret = sqlite3_prepare(stDb.dbHandle, szStrPre, strlen(szStrPre), &pstStmt, NULL);
	CHECK_EQGoEnd(s32Ret, SQLITE_OK);

	s32Ret = sqlite3_bind_blob(pstStmt, 1, pData, u32Len, NULL);
	CHECK_EQGoEnd(s32Ret, SQLITE_OK);

	s32Ret = sqlite3_step(pstStmt);
	CHECK_EQGoEnd(s32Ret, SQLITE_DONE);

	end : ;
	if (pstStmt != NULL)
	{
		sqlite3_finalize(pstStmt);
	}
	MUTEX_Unlock(stDb.Mutex);
}

extern int32_t DB_Read(uint8_t *pData, uint32_t u32MaxLen)
{
	CHECK_PtrRetInt(pData);
	CHECK_GTRetInt(u32MaxLen, 0);
	CHECK_PtrRetInt(stDb.dbHandle);

	uint8_t *pReadData = NULL;
	char szStrPre[255] = { 0 };
	sqlite3_stmt *pstStmt = NULL;
	int32_t s32Ret = SQLITE_ERROR, s32ReadLen = -1;

	MUTEX_Lock(stDb.Mutex);
	snprintf(szStrPre, sizeof(szStrPre), "%s", "select * from post order by \"oid\" ASC LIMIT 1");

	s32Ret = sqlite3_prepare(stDb.dbHandle, szStrPre, strlen(szStrPre), &pstStmt, NULL);
	CHECK_EQGoEnd(s32Ret, SQLITE_OK);

	s32Ret = sqlite3_step(pstStmt);
	if (s32Ret == SQLITE_DONE)
	{
		LOG_Imp("db is empty");
	}
	else if (s32Ret == SQLITE_ROW)
	{
		s32ReadLen = sqlite3_column_bytes(pstStmt, 0);
		CHECK_GEGoEnd(u32MaxLen, s32ReadLen);

		pReadData = sqlite3_column_blob(pstStmt, 0);
		CHECK_PtrGoEnd(pReadData);

		memcpy(pData, pReadData, s32ReadLen);
	}
	else
	{
		LOG_Err("db read failed");
	}

	end : ;
	if (pstStmt != NULL)
	{
		sqlite3_finalize(pstStmt);
	}
	MUTEX_Unlock(stDb.Mutex);

	return s32ReadLen;
}

extern void DB_Delete(DB_DELETE_TYPE_E enType)
{
	CHECK_PtrRetVoid(stDb.dbHandle);

	char szStrExec[255] = { 0 };
	int32_t s32Ret = SQLITE_ERROR;

	MUTEX_Lock(stDb.Mutex);
	if (enType == DB_DELETE_OLDEST)
	{
		snprintf(szStrExec, sizeof(szStrExec), "%s", "delete from post where \"oid\" in (select \"oid\" from post order by \"oid\" ASC LIMIT 1)");
	}
	else if (enType == DB_DELETE_ALL)
	{
		snprintf(szStrExec, sizeof(szStrExec), "%s", "delete from post");
	}
	else
	{
		LOG_Err("db delete type unknown");
		goto end;
	}

	LOG_Imp("%s", szStrExec);
	s32Ret = sqlite3_exec(stDb.dbHandle, szStrExec, NULL, NULL, NULL);
	CHECK_EQGoEnd(s32Ret, SQLITE_OK);

	end : ;
	MUTEX_Unlock(stDb.Mutex);
}
