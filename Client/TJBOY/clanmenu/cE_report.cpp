#include "StdAfx.h"
#define CE_REPORT_CPP
#include "tjclanDEF.h"
#include "..\\..\\HoBaram\\HoTextFile.h"

#include "tjclan.h"
#include "cE_report.h"


CLANEntity_report::CLANEntity_report()
{
	ZeroMemory(szReport, sizeof(char)*REPORT_MAX);
}

CLANEntity_report::~CLANEntity_report()
{

}
int CLANEntity_report::Init(int Life)
{
	life = Life;
	return 1;
}

int CLANEntity_report::Clear()
{
	return 1;
}
void CLANEntity_report::Main()
{
	int i;
	if (life == 0) return;

	switch (C_menuN)
	{
	case CLAN_ERROR:

		i = chkeckMenuN();
		switch (i)
		{
		case 0:
			menuMouseOver[0] = 1;
			break;
		default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
			break;
		}
		if (MOUSE0())
		{
			MOUSE0() = 0;
			i = i;
			switch (i)
			{
			case 0:
				C_menuN = CLAN_AllEnd;
				C_menuN2 = -1;
				CLAN_ERROR_ret = -1;
				break;
			default:
				i = i;
				break;

			}
		}
		break;
	}
}
void CLANEntity_report::RenderMain()
{
	if (life == 0) return;

}
void CLANEntity_report::menuInit(int num, LONG x, LONG y)
{
	int bx = 0, by = 0;

	switch (num)
	{
	case CLAN_ERROR:
		menuSu = 3;
		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		menuPos[1].left = BackStartPos.x + (int)x;
		menuPos[1].top = BackStartPos.y + (int)y;

		bx = 64;
		by = 16;

		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;

		break;
	}
}

void CLANEntity_report::InitMsg(char *msg)
{
	lstrcpy(szReport, msg);
}

void CLANEntity_report::Draw()
{
	switch (C_menuN)
	{
	case CLAN_AllEnd:
		break;
	case CLAN_ERROR:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);

		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		Draw_C_Text(szReport, menuPos[1].left, menuPos[1].top);
		break;

	}
}


