#include "StdAfx.h"
#include ".\PiScript.h"
#include ".\PiScriptLuaCommand.h"
#include "..\\HoNewEffectHeader.h"
#include "..\\HoEffectMain.h"


int luaCommand_Begin(lua_State *pLuaState)
{
	int count = lua_gettop(pLuaState);

	if (lua_isstring(pLuaState, 1))
		MainWindow.LuaBegin(lua_tostring(pLuaState, 1));

	if (count == 2)
		MainWindow.LuaBegin(lua_tostring(pLuaState, 1), lua_tostring(pLuaState, 2));
	return 1;
}

int luaCommand_End(lua_State *pLuaState)
{
	MainWindow.LuaEnd();
	return 1;
}

int luaCommand_InitPos(lua_State *pLuaState)
{

	MainWindow.LuaInitPos((float)lua_tonumber(pLuaState, 1),
		(float)lua_tonumber(pLuaState, 2),
		(float)lua_tonumber(pLuaState, 3));

	return 1;
}

int luaCommand_InitMeshName(lua_State *pLuaState)
{
	int count = lua_gettop(pLuaState);

	if (count == 1)
	{
		MainWindow.LuaInitMeshName(FormatString("Effect\\NewEffect\\%s", lua_tostring(pLuaState, 1)), NULL);
	}
	else if (count == 2)
	{
		MainWindow.LuaInitMeshName(FormatString("Effect\\NewEffect\\%s", lua_tostring(pLuaState, 1)), FormatString("Effect\\NewEffect\\%s", lua_tostring(pLuaState, 2)));
	}
	return 1;
}

int luaCommand_InitMaxFrame(lua_State *pLuaState)
{
	MainWindow.LuaInitMaxFrame((float)lua_tonumber(pLuaState, 1));
	return 1;
}

int luaCommand_InitStartDelayTime(lua_State *pLuaState)
{
	MainWindow.LuaInitStartDelayTime((float)lua_tonumber(pLuaState, 1));
	return 1;
}

int luaCommand_InitLoop(lua_State *pLuaState)
{
	MainWindow.LuaInitLoop((int)lua_tonumber(pLuaState, 1));
	return 1;
}

int luaCommand_InitTextureName(lua_State *pLuaState)
{
	MainWindow.LuaInitTextureName(FormatString("Effect\\NewEffect\\%s", lua_tostring(pLuaState, 1)));
	return 1;
}

int luaCommand_InitAniTextureName(lua_State *pLuaState)
{
	const char *pBuffer = FormatString("Effect\\NewEffect\\%s", lua_tostring(pLuaState, 1));
	MainWindow.LuaInitTextureName(pBuffer);

	MainWindow.LuaInitAniTextureName(pBuffer,
		(int)lua_tonumber(pLuaState, 2),
		(float)lua_tonumber(pLuaState, 3));
	return 1;
}

int luaCommand_InitColor(lua_State *pLuaState)
{
	MainWindow.LuaInitColor((float)lua_tonumber(pLuaState, 1),
		(float)lua_tonumber(pLuaState, 2),
		(float)lua_tonumber(pLuaState, 3),
		(float)lua_tonumber(pLuaState, 4));
	return 1;
}

int luaCommand_EventColor(lua_State *pLuaState)
{
	int count = lua_gettop(pLuaState);
	if (count == 5)
	{
		MainWindow.LuaEventColor((float)lua_tonumber(pLuaState, 1),
			(float)lua_tonumber(pLuaState, 2),
			(float)lua_tonumber(pLuaState, 3),
			(float)lua_tonumber(pLuaState, 4),
			(float)lua_tonumber(pLuaState, 5));
	}
	return 1;
}

int luaCommand_EventSize(lua_State *pLuaState)
{
	int count = lua_gettop(pLuaState);
	if (count == 4)
	{
		MainWindow.LuaEventSize((float)lua_tonumber(pLuaState, 1),
			(float)lua_tonumber(pLuaState, 2),
			(float)lua_tonumber(pLuaState, 3),
			(float)lua_tonumber(pLuaState, 4));
	}
	return 1;
}

int luaCommand_EventFadeColor(lua_State *pLuaState)
{
	int count = lua_gettop(pLuaState);
	if (count == 5) //인자가 4개이다(eventtime, r, g, b, a)
	{
		MainWindow.LuaEventFadeColor((float)lua_tonumber(pLuaState, 1),
			(float)lua_tonumber(pLuaState, 2),
			(float)lua_tonumber(pLuaState, 3),
			(float)lua_tonumber(pLuaState, 4),
			(float)lua_tonumber(pLuaState, 5));
	}
	return 1;
}

int luaCommand_EventFadeSize(lua_State *pLuaState)
{
	int count = lua_gettop(pLuaState);
	if (count == 4) //인자가 4개이다(eventtime, r, g, b, a)
	{
		MainWindow.LuaEventFadeSize((float)lua_tonumber(pLuaState, 1),
			(float)lua_tonumber(pLuaState, 2),
			(float)lua_tonumber(pLuaState, 3),
			(float)lua_tonumber(pLuaState, 4));
	}
	return 1;
}


int luaCommand_InitEndTime(lua_State *pLuaState)
{
	int count = lua_gettop(pLuaState);
	if (count == 1)
		MainWindow.LuaInitEndTime((float)lua_tonumber(pLuaState, 1));
	if (count == 2)
		MainWindow.LuaInitEndTime((float)lua_tonumber(pLuaState, 1), (float)lua_tonumber(pLuaState, 2));
	return 1;
}

int luaCommand_InitSize(lua_State *pLuaState)
{
	int count = lua_gettop(pLuaState);
	if (count == 2)
	{
		MainWindow.LuaInitSize((float)lua_tonumber(pLuaState, 1),
			(float)lua_tonumber(pLuaState, 2));
	}

	if (count == 4)
	{
		MainWindow.LuaInitSize((float)lua_tonumber(pLuaState, 1),
			(float)lua_tonumber(pLuaState, 2),
			(float)lua_tonumber(pLuaState, 3),
			(float)lua_tonumber(pLuaState, 4));
	}
	return 1;
}

int luaCommand_InitBlendType(lua_State *pLuaState)
{
	MainWindow.LuaInitBlendType(lua_tostring(pLuaState, 1));
	return 1;
}

int luaCommand_InitSpawnBoundingBox(lua_State *pLuaState)
{
	MainWindow.LuaInitSpawnBoundingBox((float)lua_tonumber(pLuaState, 1),
		(float)lua_tonumber(pLuaState, 2),
		(float)lua_tonumber(pLuaState, 3),
		(float)lua_tonumber(pLuaState, 4),
		(float)lua_tonumber(pLuaState, 5),
		(float)lua_tonumber(pLuaState, 6));
	return 1;
}

int luaCommand_InitSpawnBoundingSphere(lua_State *pLuaState)
{
	MainWindow.LuaInitSpawnBoundingSphere((float)lua_tonumber(pLuaState, 1),
		(float)lua_tonumber(pLuaState, 2));
	return 1;
}

int luaCommand_InitSpawnBoundingDoughnut(lua_State *pLuaState)
{
	MainWindow.LuaInitSpawnBoundingDoughnut((float)lua_tonumber(pLuaState, 1),
		(float)lua_tonumber(pLuaState, 2),
		(float)lua_tonumber(pLuaState, 3),
		(float)lua_tonumber(pLuaState, 4));
	return 1;
}

int luaCommand_InitParticleNum(lua_State *pLuaState)
{
	MainWindow.LuaInitParticleNum((float)lua_tonumber(pLuaState, 1));
	return 1;
}

int luaCommand_InitEmitRate(lua_State *pLuaState)
{
	MainWindow.LuaInitEmitRate((float)lua_tonumber(pLuaState, 1));
	return 1;
}

int luaCommand_InitAxialPos(lua_State *pLuaState)
{
	MainWindow.LuaInitAxialPos((float)lua_tonumber(pLuaState, 1),
		(float)lua_tonumber(pLuaState, 2),
		(float)lua_tonumber(pLuaState, 3),
		(float)lua_tonumber(pLuaState, 4),
		(float)lua_tonumber(pLuaState, 5),
		(float)lua_tonumber(pLuaState, 6));
	return 1;
}

int luaCommand_InitVelocity(lua_State *pLuaState)
{
	MainWindow.LuaInitVelocity((float)lua_tonumber(pLuaState, 1),
		(float)lua_tonumber(pLuaState, 2),
		(float)lua_tonumber(pLuaState, 3),
		(float)lua_tonumber(pLuaState, 4),
		(float)lua_tonumber(pLuaState, 5),
		(float)lua_tonumber(pLuaState, 6));
	return 1;
}

int luaCommand_InitParticleType(lua_State *pLuaState)
{
	MainWindow.LuaInitParticleType(lua_tostring(pLuaState, 1));
	return 1;
}

int luaCommand_InitVelocityType(lua_State *pLuaState)
{
	MainWindow.LuaInitVelocityType(lua_tostring(pLuaState, 1));
	return 1;
}