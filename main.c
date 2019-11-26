#include <stdio.h>
#include "lxt_db.h"
#include "lxt_types.h"
#include "lxt_log.h"

static void db_oldest_show(void)
{
	int32_t s32ReadLen = 0;
	uint8_t szRead[64] = { 0 };

	s32ReadLen = DB_Read(szRead, sizeof(szRead));
	LOG_Imp("DB read len:%d\t\t%s", s32ReadLen, szRead);
}

static void db_bust_add(uint32_t u32Cnt)
{
	int32_t s32Loop = 0;
	uint8_t szWrite[64] = { 0 };
	static uint64_t u64Info = 0;

	for (s32Loop = 0; s32Loop < u32Cnt; s32Loop++)
	{
		snprintf(szWrite, sizeof(szWrite), "write db info: %d", u64Info++);
		LOG_Imp("DB ADD len:%d\t\t%s", sizeof(szWrite), szWrite);
		DB_Write(szWrite, sizeof(szWrite));
	}
}

static void db_bust_delete(uint32_t u32Cnt)
{
	int32_t s32Loop = 0;

	for (s32Loop = 0; s32Loop < u32Cnt; s32Loop++)
	{
		db_oldest_show();
		DB_Delete(DB_DELETE_OLDEST);
	}
}

int main(int argc, char ** argv)
{
	char u8Cmd = 0;
	uint32_t u32Cnt = 0;

	DB_Init();

	while (1)
	{
		LOG_Imp("s:show db oldest");
		LOG_Imp("d:delete db data");
		LOG_Imp("a:add db data");

		scanf("%c", &u8Cmd);
		switch (u8Cmd)
		{
			case 's':
				db_oldest_show();
				break;
			case 'd':
				LOG_Imp("input delete cnt");
				scanf("%u", &u32Cnt);
				db_bust_delete(u32Cnt);
				break;
			case 'a':
				LOG_Imp("input add cnt");
				scanf("%u", &u32Cnt);
				db_bust_add(u32Cnt);
				break;
			default:
				break;
		}
	}
	DB_Uninit();
	return 0;
}
