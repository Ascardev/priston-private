#include "StdAfx.h"
#define CE_NOUSER_CPP

#include "tjclanDEF.h"
#include "..\\..\\HoBaram\\HoTextFile.h"

#include "tjclan.h"
#include "cE_nouser.h"


CLANEntity_nouser::CLANEntity_nouser()
{

}

CLANEntity_nouser::~CLANEntity_nouser()
{

}
int CLANEntity_nouser::Init(int Life)
{
	life = Life;
	return 1;
}

int CLANEntity_nouser::Clear()
{
	return 1;
}
void CLANEntity_nouser::Main()
{
	if (life == 0) return;


}
void CLANEntity_nouser::RenderMain()
{
	if (life == 0) return;

}
void CLANEntity_nouser::menuInit(int num)
{
	int bx = 0, by = 0;

	switch (num)
	{
	case CLAN_MAKE_is:
		menuSu = 2;

		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;
		menuPos[0].top = BackStartPos.y + +BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;
		menuPos[1].left = BackStartPos.x + BUTTON2_X;
		menuPos[1].top = BackStartPos.y + BUTTON2_Y;
		menuPos[1].right = menuPos[1].left + bx;
		menuPos[1].bottom = menuPos[1].top + by;
		menuPos[2].left = BackStartPos.x + 55;
		menuPos[2].top = BackStartPos.y + 70;
		menuPos[2].right = menuPos[2].left + 280;
		menuPos[2].bottom = menuPos[2].top + 250;

		bx = 68;
		by = 27;

		menuPos[3].left = BackStartPos.x + BUTTON1_BOX_X;
		menuPos[3].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[3].right = menuPos[3].left + bx;
		menuPos[3].bottom = menuPos[3].top + by;
		menuPos[4].left = BackStartPos.x + BUTTON2_BOX_X;
		menuPos[4].top = BackStartPos.y + BUTTON2_BOX_Y;
		menuPos[4].right = menuPos[4].left + bx;
		menuPos[4].bottom = menuPos[4].top + by;

		break;
	case CLAN_MONEY_is:
		menuSu = 2;

		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;
		menuPos[1].left = BackStartPos.x + BUTTON2_X;
		menuPos[1].top = BackStartPos.y + BUTTON2_Y;
		menuPos[1].right = menuPos[1].left + bx;
		menuPos[1].bottom = menuPos[1].top + by;
		menuPos[2].left = BackStartPos.x + 65;
		menuPos[2].top = BackStartPos.y + 80;
		menuPos[2].right = menuPos[2].left + 280;
		menuPos[2].bottom = menuPos[2].top + 250;

		bx = 68;
		by = 27;

		menuPos[3].left = BackStartPos.x + BUTTON1_BOX_X;
		menuPos[3].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[3].right = menuPos[3].left + bx;
		menuPos[3].bottom = menuPos[3].top + by;
		menuPos[4].left = BackStartPos.x + BUTTON2_BOX_X;
		menuPos[4].top = BackStartPos.y + BUTTON2_BOX_Y;
		menuPos[4].right = menuPos[4].left + bx;
		menuPos[4].bottom = menuPos[4].top + by;

		break;
	case CLAN_NAME_is:

		if (hFocusWnd == 0)
		{
			ZeroMemory(cldata.name, sizeof(cldata.name));
			hFocusWnd = hTextWnd;
			SetWindowText(hFocusWnd, "");
		}

		menuSu = 2;

		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON3_X;		//Ȯ��
		menuPos[0].top = BackStartPos.y + BUTTON3_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		menuPos[2].left = BackStartPos.x + 55;
		menuPos[2].top = BackStartPos.y + 70;
		menuPos[2].right = menuPos[2].left + 190;
		menuPos[2].bottom = menuPos[2].top + 180;

		bx = 68;
		by = 27;


		menuPos[3].left = BackStartPos.x + BUTTON3_BOX_X;		//Ȯ�� �׵θ� �ڽ�
		menuPos[3].top = BackStartPos.y + BUTTON3_BOX_Y;
		menuPos[3].right = menuPos[3].left + bx;
		menuPos[3].bottom = menuPos[3].top + by;

		break;
	case CLAN_NONAME:
		menuSu = 3;

		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON3_X;		//Ȯ��
		menuPos[0].top = BackStartPos.y + BUTTON3_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;
		menuPos[1].left = BackStartPos.x + 55;
		menuPos[1].top = BackStartPos.y + 70;

		bx = 64;
		by = 16;

		menuPos[2].left = BackStartPos.x + BUTTON3_BOX_X;		//Ȯ��
		menuPos[2].top = BackStartPos.y + BUTTON3_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;
		break;
	case CLAN_NAME_BEING:
		menuSu = 3;

		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON3_X;		//Ȯ��
		menuPos[0].top = BackStartPos.y + BUTTON3_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;
		menuPos[1].left = BackStartPos.x + 55;
		menuPos[1].top = BackStartPos.y + 70;

		bx = 64;
		by = 16;

		menuPos[2].left = BackStartPos.x + BUTTON3_BOX_X;		//Ȯ��
		menuPos[2].top = BackStartPos.y + BUTTON3_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;
		break;
	case CLAN_MARK_expl: //Ŭ�� ��ũ Ȯ��
		menuSu = 1;

		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON3_X;		//Ȯ��
		menuPos[0].top = BackStartPos.y + BUTTON3_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;
		menuPos[1].left = BackStartPos.x + 55;
		menuPos[1].top = BackStartPos.y + 70;
		menuPos[1].right = menuPos[1].left + 190;
		menuPos[1].bottom = menuPos[1].top + 180;

		bx = 68;
		by = 27;

		menuPos[2].left = BackStartPos.x + BUTTON3_BOX_X;		//Ȯ�� �׵θ� �ڽ�
		menuPos[2].top = BackStartPos.y + BUTTON3_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;
		break;
	case CLAN_INSPECTION_expl:		//Ŭ���ɻ�
		menuSu = 5;

		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;		//Ȯ��
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;
		menuPos[1].left = BackStartPos.x + 55;
		menuPos[1].top = BackStartPos.y + 70;
		menuPos[1].right = menuPos[1].left + 260;
		menuPos[1].bottom = menuPos[1].top + 180;

		bx = 68;
		by = 27;


		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;		//Ȯ�� �׵θ� �ڽ�
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;

		bx = 32;
		by = 16;

		menuPos[3].left = BackStartPos.x + BUTTON2_X;		//���
		menuPos[3].top = BackStartPos.y + BUTTON2_Y;
		menuPos[3].right = menuPos[3].left + bx;
		menuPos[3].bottom = menuPos[3].top + by;

		bx = 68;
		by = 27;

		menuPos[4].left = BackStartPos.x + BUTTON2_BOX_X;		//��� �׵θ� �ڽ�
		menuPos[4].top = BackStartPos.y + BUTTON2_BOX_Y;
		menuPos[4].right = menuPos[4].left + bx;
		menuPos[4].bottom = menuPos[4].top + by;
		break;
	case CLAN_NotMake:
		menuSu = 3;

		bx = 64;
		by = 64;

		menuPos[0].left = BackStartPos.x + BUTTON3_X;
		menuPos[0].top = BackStartPos.y + BUTTON3_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;
		menuPos[1].left = BackStartPos.x + 55;
		menuPos[1].top = BackStartPos.y + 70;
		menuPos[1].right = menuPos[1].left + 260;
		menuPos[1].bottom = menuPos[1].top + 180;

		bx = 68;
		by = 27;

		menuPos[2].left = BackStartPos.x + BUTTON3_BOX_X;
		menuPos[2].top = BackStartPos.y + BUTTON3_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;
		break;
	case CLAN_MAKE_FINISH:
		menuSu = 3;

		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON3_X;
		menuPos[0].top = BackStartPos.y + BUTTON3_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;
		menuPos[1].left = BackStartPos.x + 55;
		menuPos[1].top = BackStartPos.y + 70;

		bx = 64;
		by = 16;

		menuPos[2].left = BackStartPos.x + BUTTON3_BOX_X;
		menuPos[2].top = BackStartPos.y + BUTTON3_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;
		break;
	}
}