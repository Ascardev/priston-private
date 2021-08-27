#pragma once
#ifndef __CLAN_ENTI_HPP__
#define __CLAN_ENTI_HPP__

//#define PARKMENU
//#define CLANHELPICON_NUM_ENIT		100

class CLANEntity
{
public:
	int				life;	
	CLANEntity      *parent;


public:
	CLANEntity();
	~CLANEntity();

	virtual int Init() ;
	virtual int Clear();

	virtual void Main();
	virtual void RenderMain();

	void	setParent(CLANEntity      *p){parent = p;}
	void			Kill()			{ life = 0; };
	int				IsDead()		{ return(life); };

	virtual void Draw();

	virtual void menuInit(int num);

	void Draw_C_Text(char *str, int x, int y, int sw=0);
	void Draw_C_Text2(char *str, int x, int y, int sw=0);
	void Draw_C_Text3(char *str, int x, int y, int sw=0);

	void Draw_C_TextPark(char *str, int x, int y, int RedColor, int GreenColor, int BlueColor, int sw);

	
	int  chkMenu(int x, int y, RECT *r);
	int  chkeckMenuN();

	void ParsingIsClanMember(char* data);
	void ParsingIsClanMember2(char *data);
	int chk_readStrBuf(char *cmd, char *readbuf, char *retBuf);
	void ParsingData(char* cmd, char* data, char* save);
	void ParsingMakeClanMoney(char* data,int* money);


	void ParsigClanWon(char* data);
	
	void ParsingClanWonStrLen();

	void LoadToFile();
	
	void LoadHelp(char *help);
	void DestroyClanHelpIcon();
	void LoadHelpImage();
	BOOL ReadClanHelpScr(char *filename);
	void ReMoveClanWon(char *src);

	void WriteMyClanInfo();
	int CheckMark(BOOL bFlag);

	void CheckClanExp(char* byte);


	void Load();
	void Load2();

	virtual void Close();
	void copy_LoadResource(CLANEntity *copyDest);
	void copy_LoadResource2(CLANEntity *copyDest);
	
	inline void SetBase(CLANEntity *copyDest){parent = copyDest;}

	int	MatPartyBackGround;		//배경
	int	hBoxCorner,hBoxLine;	//박스그리기
	int	hBox1,hBox2,hBox3,hBox4,hBox6,hBox7,hBox8,hBox9; //박스그리기
	int	hScl_Bar_tj;
	int	hScl_icon_tj;
	int   hLine;
	

	inline smTEXTUREHANDLE * GetClanMark(){return parent->hMark;}

	smTEXTUREHANDLE *hBt_Help;
	smTEXTUREHANDLE *hMark_box;
	smTEXTUREHANDLE *hOk_Gray,*hOk_Yellow; //확인
	smTEXTUREHANDLE *hCancel_Gray,*hCancel_Yellow; //취소
	smTEXTUREHANDLE *hYes_Gray,*hYes_Yellow; // 예
	smTEXTUREHANDLE *hNo_Gray,*hNo_Yellow; //아니오

	smTEXTUREHANDLE *hMark,*hClanName;
	smTEXTUREHANDLE *hSecession[2];
	smTEXTUREHANDLE *hClose[2];
	smTEXTUREHANDLE *hIcon;
	smTEXTUREHANDLE *hIcon_Click;
	smTEXTUREHANDLE *hHelp1;
	smTEXTUREHANDLE *hClinetMark;
	smTEXTUREHANDLE *hServerMark;
	smTEXTUREHANDLE *hWareHouse[2]; //마우스가 위로 올라왔을때
	smTEXTUREHANDLE *hWHRight[2];
	smTEXTUREHANDLE *hClanMark[2];
	smTEXTUREHANDLE *hRemove[2];
	smTEXTUREHANDLE *hClanRelease[2];
	smTEXTUREHANDLE *hHelp[2];
	smTEXTUREHANDLE *hOut[2];

	smTEXTUREHANDLE *hButton_Box;
	smTEXTUREHANDLE *hClanTitle;
	smTEXTUREHANDLE *hRemoveToMenu[2];
	smTEXTUREHANDLE *hScl_Bar;
	smTEXTUREHANDLE *hScl_icon;
	smTEXTUREHANDLE *hClanHelpIcon[CLANHELPICON_NUM][4];
	smTEXTUREHANDLE *hClanNameInput;

	smTEXTUREHANDLE *hTxt_Remove[2];
	smTEXTUREHANDLE *hTxt_Release[2];
	smTEXTUREHANDLE *hTxt_Mark[2];
	smTEXTUREHANDLE *hTxt_Help[2];
	smTEXTUREHANDLE *hTxt_Secession[2];
	smTEXTUREHANDLE *hTxt_LeaveClan[2];
	smTEXTUREHANDLE *hTxt_SubChip[2];
	smTEXTUREHANDLE *hSubChip;

	char		szHelpMsg1[HELPMSG_MAX];
	char		szErrorMsg[256];

	BOOL bImageDown;
};

#endif //__CLAN_ENTI_HPP__





#if defined (CLAN_EITI_CPP)


	class CLANEntity  cBaseMenu;

#else

	extern class CLANEntity  cBaseMenu;


#endif




