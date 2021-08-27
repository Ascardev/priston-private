#pragma once
#ifndef __CE_CHATTING_HPP__
#define __CE_CHATTING_HPP__

#include <windows.h>
#include "clan_Enti.h"

//=========================================================
#define BOX_X                 656
#define MOVE_X                 400
#define MOVE_Y                 0


#define CHATING_DISPLAY_MAX       8

#define CHATING_CLANWON_LIST_X    620
#define CHATING_CLANWON_LIST_Y    204
#define CHATING_CLANWON_LIST_CAP  20



#define CHATICON_X               625   
#define CHATCLOSE_X              740
#define CHATICON_Y               375


#define CHATLIST_SBAR_X	         770
#define CHATLIST_SBAR_Y          193
#define CHATLIST_MENU                     150


#define CHATLIST_CLANCHIP                 1
#define CHATLIST_CLANUSER				2
#define CHATLIST_CLANNO_REGESTER			3				
#define CHATLIST_BOX_Y					147


typedef struct _tagCHATLIST
{ 
	int MyPositon;              //클랜장인지, 클랜원인지, 클랜미등록인지 체크
	char  clanWon[CLANWON_MAX][30];        //클랜서버에서 보내준 클랜원을 저장(클랜장 제외)
	char  szUserID[40];           //사용자 아이디
	char  szGameServer[40];        //접속한 서버군
	char  szChaName[40];           //사용자 캐릭터 이름
	char  szClanZang_Name[40];
}CHATLIST;

class CLANEntity_chatting: public CLANEntity
{
public:

	//ktj : 임시
	void chat_WhisperPartyPlayer2(int num);
	void chat_WhisperPartyPlayer(int num);
	void chat_WhisperPartyPlayer_close();

	char szFile_hMark[128];

	CLANEntity_chatting();
	~CLANEntity_chatting();

	int Init(int Life);
	void Close();


	void Main();
	void Draw();
	void InitClanWon();
	void InitClanChatList();
	void MoveClose();


	void menuInit(int num);
	void SortClanWonList();
	void Load();
	void Load2();		//2번째로드시
	
	
	//void OpenDrawBox();
	//void CloseDrawBox();
	//void CloseDraw();



	
	void DrawBox();
	void Draw_C_menuN();
	void NoScroll();

	int  chkMenu(int x, int y, RECT *r);
	int  chkeckMenuN();
	void DoubleClick(int i);

	void ChatListParsigClanWon(char* data);
	void ChatListUserData(char *id, char *gserver, char *chaid);
	void ChatListParsingIsClanMember(char* data);
	void SetBoxDraw(BOOL bFlag){bIsBox = bFlag;}
	void SetOpenChatList(BOOL bFlag){bIsClose = bFlag;}
	void DisplayInfo();
public:
	int	hChatListBoxLine;

	int	hChatListBoxTitle2;

	smTEXTUREHANDLE	*hChatListBoxTitle;
	smTEXTUREHANDLE	*hChatIcon[2];
	smTEXTUREHANDLE	*hButtonClose[2];
	smTEXTUREHANDLE	*hClanWon[2];
	smTEXTUREHANDLE	*hChatClanWon;

	smTEXTUREHANDLE	*hMicOption[2];
	smTEXTUREHANDLE	*hMicOptToolTip;
    int	hChatMicOpt;
	smTEXTUREHANDLE	*hMicOptTitle;
	smTEXTUREHANDLE	*hMicSortLine;	// 마이크옵션 가로줄
	smTEXTUREHANDLE	*hMicONBack;	// 마이크on,off백그라운드
	smTEXTUREHANDLE	*hMicONChk;	// 마이크 on체크이미
	smTEXTUREHANDLE	*hMicVolBar;	// 마이크옵션 볼륨바
	smTEXTUREHANDLE	*hMicVOLUPDOWN[2];	// 마이크 볼륨 up,down활성화
	smTEXTUREHANDLE	*hClanChatToolTip;
	smTEXTUREHANDLE	*hBtnCloseToolTip;
	
	int nScl_Bar;           //스크롤바
	RECT scrIconPos;		//스크롤바의 움직이는아이콘위치설정
	int nScl_Save;
	int nTotalClanWon;
	int nRest_Num;
	CHATLIST   ClanChatList;
	BOOL bIsBox;
	char szErrorMsg[255];
	int nBoxMove;
	BOOL bIsClose;
	BOOL bIsDrawBoxFinish;	
	int OCcnt;
	int ChatListBoxX;
	int ChatListBoxY;

	int cnt;
	int AddSize;
	RECT ChatList_menuPos[30];
	int ChatList_menuSu;
	
	int Chatting_button;
	
	int MicOpt_button;
	int nVol;

	int nSaveClanWonPos;
	int nDoublClick;
	
};


#endif 





#ifdef CE_CHATLIST_CPP

	class CLANEntity_chatting cClanChatting;

#else

	extern class CLANEntity_chatting cClanChatting;

#endif
