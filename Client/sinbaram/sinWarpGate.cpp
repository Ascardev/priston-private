#include "StdAfx.h"

/*----------------------------------------------------------------------------*
*								전역변수
*-----------------------------------------------------------------------------*/
cSINWARPGATE cSinWarpGate;
sUNIONCORE_EFFECT sWarpGateEffect[10];
//x-162  y-73
sSINWARPGATE sSinWarpGate = { { {96,199},{64,21},{88,84},{67,177},{78,116},{150,165},{158,137},{155,65}, {140,225} ,{0,0} } };		//필드선택 좌표
int WarpGateUseCost[10] = { 100,300,500,1000,2000,4000 };																	//실제로 사용되는 돈
int sinWarpGateCODE[10] = { 3,21,18,1,6,9,12,29,37 };																			//이동될 필드	

//블레스 캐슬(이벤트성) 워프게이트------------------------------------------------------------------------/

sSINWARPGATE sHaWarpGate = { {{69,207},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}} };
int haWarpGateCODE[10] = { 33 };
//----------------------------------------------------------------------------------------------/


/*----------------------------------------------------------------------------*
*							클래스 초기, 종료
*-----------------------------------------------------------------------------*/
cSINWARPGATE::cSINWARPGATE()
{

}
cSINWARPGATE::~cSINWARPGATE()
{

}
/*----------------------------------------------------------------------------*
*							     초기화
*-----------------------------------------------------------------------------*/
void cSINWARPGATE::Init()
{
	sSinWarpGate.MapPosi.x = 272 + 200;
	sSinWarpGate.MapPosi.y = 120;

	MatWarpMap = CreateTextureMaterial("Image\\SinImage\\Help\\WG_map.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatIcon = CreateTextureMaterial("Image\\SinImage\\Help\\WG_icon.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatSelect = CreateTextureMaterial("Image\\SinImage\\Help\\WG_slt.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	Load();
}
/*----------------------------------------------------------------------------*
*						    Bmp파일을 로드한다
*-----------------------------------------------------------------------------*/
void cSINWARPGATE::Load()
{
	lpCancelBox = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\msBOX.bmp");
	lpCancelButton = LoadDibSurfaceOffscreen("image\\clanImage\\MessageBox\\c1.bmp");
	lpCancelButton_G = LoadDibSurfaceOffscreen("image\\clanImage\\MessageBox\\c.bmp");
}
/*----------------------------------------------------------------------------*
*						     Release
*-----------------------------------------------------------------------------*/
void cSINWARPGATE::Release()
{

}
/*----------------------------------------------------------------------------*
*							     그리기
*-----------------------------------------------------------------------------*/
void cSINWARPGATE::Draw()
{
	int i = 0;
	if (sSinWarpGate.ShowFlag) {
		//지도 
		dsDrawTexImage(MatWarpMap, sSinWarpGate.MapPosi.x, sSinWarpGate.MapPosi.y, 256, 256, 255);

		//표시
		for (i = 0; i < sSinWarpGate.GateUseIndex; i++) {
			dsDrawTexImage(MatIcon, sSinWarpGate.MapPosi.x + sSinWarpGate.GatePosi[i].x,
				sSinWarpGate.MapPosi.y + sSinWarpGate.GatePosi[i].y, 16, 16, 255);
		}
		//--------------------블레스 캐슬(이벤트)------------------------------------
		for (i = 0; i < sHaWarpGate.GateUseIndex; i++) {
			dsDrawTexImage(MatIcon, sSinWarpGate.MapPosi.x + sHaWarpGate.GatePosi[i].x,
				sSinWarpGate.MapPosi.y + sHaWarpGate.GatePosi[i].y, 16, 16, 255);

		}
		//---------------------------------------------------------------------------
		DrawSprite(sSinWarpGate.CancelPosi.x, sSinWarpGate.CancelPosi.y, lpCancelBox, 0, 0, 48, 23);
		if (sSinWarpGate.CancelFlag) {
			DrawSprite(sSinWarpGate.CancelPosi.x + 8, sSinWarpGate.CancelPosi.y + 4, lpCancelButton, 0, 0, 32, 16);
		}
		else {
			DrawSprite(sSinWarpGate.CancelPosi.x + 8, sSinWarpGate.CancelPosi.y + 4, lpCancelButton_G, 0, 0, 32, 16);
		}
	}

	for (i = 0; i < 10; i++) {
		if (sWarpGateEffect[i].Flag) {
			dsDrawTexImage(sWarpGateEffect[i].MatNum, sWarpGateEffect[i].x, sWarpGateEffect[i].y, sWarpGateEffect[i].w, sWarpGateEffect[i].h,
				sWarpGateEffect[i].Alpha);
		}
	}


	//				DrawSprite(sSinHelp[i].ButtonPosi.x+9,sSinHelp[i].ButtonPosi.y+4,cMessageBox.lpButtonOk[1],0,0,32,16); //확인글자 

}
/*----------------------------------------------------------------------------*
*							     메인
*-----------------------------------------------------------------------------*/
void cSINWARPGATE::Main()
{
	int  i = 0;

	sSinWarpGate.CancelPosi.x = sSinWarpGate.MapPosi.x + 224 - 40;
	sSinWarpGate.CancelPosi.y = sSinWarpGate.MapPosi.y + 238 - 20;

	sSinWarpGate.GateSelect = -1;
	sHaWarpGate.GateSelect = -1;
	sSinWarpGate.CancelFlag = 0;


	if (sSinWarpGate.ShowFlag)
	{
		for (i = 0; i < sSinWarpGate.GateUseIndex; i++)
		{
			if (sSinWarpGate.MapPosi.x + sSinWarpGate.GatePosi[i].x - 5 < pCursorPos.x && sSinWarpGate.MapPosi.x + sSinWarpGate.GatePosi[i].x + 21 > pCursorPos.x && sSinWarpGate.MapPosi.y + sSinWarpGate.GatePosi[i].y - 5 < pCursorPos.y && sSinWarpGate.MapPosi.y + sSinWarpGate.GatePosi[i].y + 21 > pCursorPos.y)
			{
				sSinWarpGate.GateSelect = i;
				SetWarGateSelectEffect(sSinWarpGate.MapPosi.x + sSinWarpGate.GatePosi[i].x, sSinWarpGate.MapPosi.y + sSinWarpGate.GatePosi[i].y);
				cSinHelp.sinShowHelp(SIN_HELP_KIND_WARPGATE, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), WarpGateDoc[i + 1]);
			}

		}

		for (i = 0; i < sHaWarpGate.GateUseIndex; i++)
		{
			if (sSinWarpGate.MapPosi.x + sHaWarpGate.GatePosi[i].x - 5 < pCursorPos.x && sSinWarpGate.MapPosi.x + sHaWarpGate.GatePosi[i].x + 21 > pCursorPos.x && sSinWarpGate.MapPosi.y + sHaWarpGate.GatePosi[i].y - 5 < pCursorPos.y && sSinWarpGate.MapPosi.y + sHaWarpGate.GatePosi[i].y + 21 > pCursorPos.y)
			{
				sHaWarpGate.GateSelect = i;
				SetWarGateSelectEffect(sSinWarpGate.MapPosi.x + sHaWarpGate.GatePosi[i].x, sSinWarpGate.MapPosi.y + sHaWarpGate.GatePosi[i].y);
			}
		}
		//-------------------------------------------------------------------------------------------------------------------/


		if (sSinWarpGate.GateSelect < 0 && sHaWarpGate.GateSelect < 0) { //계속 중복호출되는것을 막는다

			cSinHelp.sinShowHelp(SIN_HELP_KIND_WARPGATE, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), WarpGateDoc[0]);
		}
		if (sSinWarpGate.CancelPosi.x < pCursorPos.x && sSinWarpGate.CancelPosi.x + 32 > pCursorPos.x &&
			sSinWarpGate.CancelPosi.y < pCursorPos.y && sSinWarpGate.CancelPosi.y + 21 > pCursorPos.y) {
			sSinWarpGate.CancelFlag = 1;

		}
	}
	//이펙트
	for (i = 0; i < 10; i++) {
		if (sWarpGateEffect[i].Flag) {
			sWarpGateEffect[i].x--;
			sWarpGateEffect[i].y--;
			sWarpGateEffect[i].w += 2;
			sWarpGateEffect[i].h += 2;
			sWarpGateEffect[i].Alpha -= 5;
			sWarpGateEffect[i].Time++;
			if (sWarpGateEffect[i].Max_Time < sWarpGateEffect[i].Time) {
				memset(&sWarpGateEffect[i], 0, sizeof(sUNIONCORE_EFFECT));

			}
		}
	}

	if (sSinWarpGate.EffectFlag)
	{
		sSinWarpGate.EffectTime++;

		if (sSinWarpGate.EffectTime > 40)
		{
			sSinWarpGate.EffectTime = 0;
			sSinWarpGate.EffectFlag = 0;
		}
	}
}
/*----------------------------------------------------------------------------*
*							     종료
*-----------------------------------------------------------------------------*/
void cSINWARPGATE::Close()
{

}
/*----------------------------------------------------------------------------*
*							   LButtonDown
*-----------------------------------------------------------------------------*/
void cSINWARPGATE::LButtonDown(int x, int y)
{
	sHaWarpGate.MoveFieldNum = 0;
	sSinWarpGate.MoveFieldNum = 0;

	if (sSinWarpGate.ShowFlag)
	{
		if (sSinWarpGate.CancelFlag)
		{
			sSinWarpGate.ShowFlag = 0;
			GAMEMAP->SetWarpGate(MAPID_Invalid);
		}
		if (sSinWarpGate.GateSelect > -1)
		{
			if (MAPLEVEL(sinWarpGateCODE[sSinWarpGate.GateSelect]) > sinChar->iLevel)
			{
				cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_LEVEL);
				return;
			}
			if (sSinWarpGate.GateUseIndex < 4 || sSinWarpGate.GateSelect < 2)
			{
				sSinWarpGate.ShowFlag = 0;
				sSinWarpGate.MoveFieldNum = sSinWarpGate.GateSelect;
				cMessageBox.ShowMessage3(MESSAGE_WARP, WarpGateName[sSinWarpGate.GateSelect + 1]);
			}
			else
			{
				if (lpCurPlayer->iLoadedMapIndex >= 0 && 
					STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == sinWarpGateCODE[sSinWarpGate.GateSelect])
				{
					sSinWarpGate.ShowFlag = 0;
					sSinWarpGate.MoveFieldNum = sSinWarpGate.GateSelect;
					sSinWarpGate.SameAreaFlag = 1;
					cMessageBox.ShowMessage3(MESSAGE_WARP, WarpGateName[sSinWarpGate.GateSelect + 1]);
				}
				else
				{
					sSinWarpGate.SameAreaFlag = 0;
					if (cShop.haBuyMoneyCheck(WarpGateUseCost[sSinWarpGate.GateUseIndex - 4]))
					{
						sSinWarpGate.ShowFlag = 0;
						sSinWarpGate.MoveFieldNum = sSinWarpGate.GateSelect;
						cMessageBox.ShowMessage3(MESSAGE_WARP, WarpGateName[sSinWarpGate.GateSelect + 1]);
					}
					else
						cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_MONEY);
				}
			}
		}

		if (sHaWarpGate.GateSelect > -1)
		{
			if (lpCurPlayer->iLoadedMapIndex >= 0 &&
				STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == haWarpGateCODE[sHaWarpGate.GateSelect])
			{
				sSinWarpGate.ShowFlag = 0;
				sHaWarpGate.MoveFieldNum = sHaWarpGate.GateSelect + 1;
				sSinWarpGate.SameAreaFlag = 0;
				cMessageBox.ShowMessage3(MESSAGE_WARP, HaWarpGateName[sHaWarpGate.GateSelect]);
			}
			else
			{
				sSinWarpGate.SameAreaFlag = 0;
				if (cShop.haBuyMoneyCheck(WarpGateUseCost[sSinWarpGate.GateUseIndex - 4]))
				{
					sSinWarpGate.ShowFlag = 0;
					sHaWarpGate.MoveFieldNum = sHaWarpGate.GateSelect + 1;
					cMessageBox.ShowMessage3(MESSAGE_WARP, HaWarpGateName[sHaWarpGate.GateSelect]);
				}
				else
					cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_MONEY);
			}
		}
	}

}
/*----------------------------------------------------------------------------*
*							   LButtonUp
*-----------------------------------------------------------------------------*/
void cSINWARPGATE::LButtonUp(int x, int y)
{
}
/*----------------------------------------------------------------------------*
*							   RButtonDown
*-----------------------------------------------------------------------------*/
void cSINWARPGATE::RButtonDown(int x, int y)
{

}
/*----------------------------------------------------------------------------*
*							   RButtonUp
*-----------------------------------------------------------------------------*/
void cSINWARPGATE::RButtonUp(int x, int y)
{

}
/*----------------------------------------------------------------------------*
*							    KeyDown
*-----------------------------------------------------------------------------*/
void cSINWARPGATE::KeyDown()
{

}
/*----------------------------------------------------------------------------*
*							TEXT 를 찍어준다
*-----------------------------------------------------------------------------*/
void cSINWARPGATE::DrawText()
{

}
/*----------------------------------------------------------------------------*
*						활성화될 워프게이트를 찾는다
*-----------------------------------------------------------------------------*/
int cSINWARPGATE::SerchUseWarpGate()
{
	sSinWarpGate.ShowFlag = 1;
	ItemData *pItem = 0;
	sSinWarpGate.GateUseIndex = 0;
	sHaWarpGate.GateUseIndex = 0;
	int   i = 0;
	for (i = 0; i < INVENTORY_MAXITEM * 2; i++) {
		if (i < 100) {
			if (!cInvenTory.InvenItem[i].bValid)continue;
			pItem = &cInvenTory.InvenItem[i];
		}
		else {
			if (!cInvenTory.InvenItemTemp[i - 100].bValid)continue;
			pItem = &cInvenTory.InvenItemTemp[i - 100];
		}
		switch (pItem->sItem.sItemID.ToInt()) {
		case (sinQW1 | sin01): //메탈윙
			sSinWarpGate.GateUseIndex = 4;
			break;
		case (sinQW1 | sin02): //실버윙
			sSinWarpGate.GateUseIndex = 5;
			break;
		case (sinQW1 | sin03): //골드윙
			sSinWarpGate.GateUseIndex = 6;
			break;
		case (sinQW1 | sin04): //다이아윙
			sSinWarpGate.GateUseIndex = 7;
			break;
		case (sinQW1 | sin05): //케이아스윙
			sSinWarpGate.GateUseIndex = 8;
			break;
		case (sinQW1 | sin06): //익스트림윙		로스트 아일랜드 (성근추가)
			sSinWarpGate.GateUseIndex = 9;
			break;

		}
	}
	//현재 수성 클랜 만 워프게이트 활성화
	if (rsBlessCastle.dwMasterClan == GetClanCode(lpCurPlayer->sCharacterData.iClanID) &&
		GetClanCode(lpCurPlayer->sCharacterData.iClanID) != 0) {
		sHaWarpGate.GateUseIndex = 1;
	}
	if (!sSinWarpGate.GateUseIndex)
		sSinWarpGate.GateUseIndex = 2;//기본적으로 리카르텐과 필라이는 갈수있다 
	return TRUE;
}

/*----------------------------------------------------------------------------*
*						선택된 워프게이트의 이펙트
*-----------------------------------------------------------------------------*/
int cSINWARPGATE::SetWarGateSelectEffect(int x, int y)
{

	if (sSinWarpGate.EffectFlag)return FALSE;
	int  i = 0;
	for (i = 0; i < 3; i++) {
		if (!sWarpGateEffect[i].Flag) {
			sWarpGateEffect[i].Flag = 1;
			sWarpGateEffect[i].MatNum = MatSelect;
			sWarpGateEffect[i].Max_Time = 20 + (i * 2);
			sWarpGateEffect[i].x = x;
			sWarpGateEffect[i].y = y;
			sWarpGateEffect[i].w = 16;
			sWarpGateEffect[i].h = 16;
			sWarpGateEffect[i].Alpha = 155 + (i * 20);

		}
	}
	sSinWarpGate.EffectFlag = 1;
	return TRUE;
}