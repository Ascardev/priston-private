#define _EVENT_GAME_

#ifdef _EVENT_GAME_

#define NPC_NUM			2
#define REVEDUSER_MAX	5000

struct rsEVENT_REVEDUSER 
{
	DWORD	dwIDCode;
	char	szID[32];
};

static int rsHopeEventNpcPos[][3] = 
{
	{ 3 , 2419 , -16324 },
	{ 0 , 0 , 0 },
	{ 0,0,0 }

};

extern char *StateInitEvent1;
extern char *StateInitEvent2;
extern char *StateInitEvent3;
extern char *StateInitEvent4;

#endif

int rsEventGame_State_Init (User *lpPlayInfo , smTRANS_COMMAND *lpTransCommand)
{

	return TRUE;
}

