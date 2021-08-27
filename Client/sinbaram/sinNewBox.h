#ifndef _SIN_NEWBOX_
#define _SIN_NEWBOX_


#define MAX_TELEPORT_FIELD 36

struct sNEWTELEPORTS
{
	int		PNo;
	char	*lpMapName;
	int		MapCode;
	int		MapLevel;
	char	szMapFileName[128];
	int		MoveFlag;
};
struct sNEWQUESTTITLE
{
	char	szName[128];
	int		number;
	int		MoveFlag;
	int		OKFlag;
};
class cSINNEWBOX
{
public:
	cSINNEWBOX();
	~cSINNEWBOX();
public:
	LPTEXTUREHANDLE lpBoxWindow[2];
	LPTEXTUREHANDLE lpBoxHeadbg;
	LPTEXTUREHANDLE lpBoxTeleportHead;
	LPTEXTUREHANDLE lpBoxScroll[2];
	LPTEXTUREHANDLE lpBoxLine[2];
	LPTEXTUREHANDLE lpBoxClose[2];
	LPTEXTUREHANDLE lpBoxOk[2];
	LPTEXTUREHANDLE lpBoxEnter[2];
	LPTEXTUREHANDLE lpBoxQuest;
	LPTEXTUREHANDLE lpBoxElement[4];
	LPTEXTUREHANDLE lpBoxSodLogo;
	LPTEXTUREHANDLE lpBoxSodBar;
	LPTEXTUREHANDLE lpBoxCheckBox[2];
	LPTEXTUREHANDLE lpBoxMini[MAX_TELEPORT_FIELD];

	int OpenFlag;
	int Kind;
	int x,y;
	int Page;
	int CountPage;
	int ScrollFlag;
	int CloseFlag;
	int OkFlag;
	int EventFlag;
	sNEWTELEPORTS TelePorts;
	int Count;
	int Element;
	char szFileReadBuf[80*128];
	char szBuff[100][128];
public:
	void Init();
	void Load();
	void Main();
	void Draw();
	void DrawText();
	void Release();
	void LButtonDown(int px,int py);
	void LButtonUp(int px,int py);
	void RButtonDown(int px,int py);
	void RButtonUp(int px,int py);
	void KeyDown();
	void Close();
	void CloseWindow();
	int sinShow(int kind,int px,int py,char *FileName = NULL);
	int ReadFileData(char *FileName);
	int ReadFileDataDivide(char *szBuf);
	int GetTextLen();
	int AddTextInfo(char *buf);
};

extern cSINNEWBOX cSinNewBox;

#endif