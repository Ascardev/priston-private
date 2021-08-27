#include "StdAfx.h"

int sinShowEventSmashingTV(int Element, int Count)
{
	HelpBoxKindIndex = SIN_EVENT_SMASHTV;
	cSinHelp.sinShowHelp(SIN_HELP_KIND_SMASHTV, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Event\\SmashTV.sin");
	return TRUE;
}

int sinSendEventItem(int Send) //서버로 이벤트 아이템을 보낸다 (1 서버로보냄 0은 검색)
{
	int MessageFlag = 0;
	for (int i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (cInvenTory.InvenItem[i].bValid)
		{
			if ((cInvenTory.InvenItem[i].sItem.sItemID.ToItemType()) == sinGP1)
			{
				if (Send)
				{
					SendUseItemCodeToServer(&cInvenTory.InvenItem[i].sItem);
					cInvenTory.InvenItem[i].bValid = 0;
					cInvenTory.ReFormInvenItem();
					ResetInvenItemCode();
					MessageFlag = 1;
				}
				else return TRUE;
			}

		}
		if (cInvenTory.InvenItemTemp[i].bValid)
		{
			if ((cInvenTory.InvenItemTemp[i].sItem.sItemID.ToItemType()) == sinGP1)
			{
				if (Send)
				{
					SendUseItemCodeToServer(&cInvenTory.InvenItemTemp[i].sItem);
					cInvenTory.InvenItemTemp[i].bValid = 0;
					cInvenTory.ReFormInvenItem();
					ResetInvenItemCode();
					MessageFlag = 1;
				}
				else return TRUE;

			}
		}
	}
	if (Send)
	{
		if (MessageFlag)
			cMessageBox.ShowMessage(MESSAGE_GYUNGFUM_OK);
	}
	else return FALSE;

	return FALSE;
}