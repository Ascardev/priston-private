#ifndef _SIN_BOX_
#define _SIN_BOX_

struct sTELEPORTS
{
	int		PNo;
	char	szFileName[128];
	int		FileCode;
	int		FileLevel;
	int		Flag;
	int		MoveFlag;
};
struct sSODELEMENT
{
	int Element;
	int Count;
};

class cSINBOX
{
public:
	cSINBOX();
	~cSINBOX();
public:
	LPDIRECT3DTEXTURE9 lpBoxClose[2];
	LPDIRECT3DTEXTURE9 lpBoxEnter[2];
	LPDIRECT3DTEXTURE9 lpBoxTelePort[2];
	LPDIRECT3DTEXTURE9 lpBoxButtonHelp[2];
	LPDIRECT3DTEXTURE9 lpBoxTransLogo;
	LPDIRECT3DTEXTURE9 lpBoxSodLogo;
	LPDIRECT3DTEXTURE9 lpBoxElement[4];
	LPDIRECT3DTEXTURE9 lpBoxScrollbar[2];
	LPDIRECT3DTEXTURE9 lpBoxTitle[2];
	LPDIRECT3DTEXTURE9 lpBoxTitleSub[2];
	LPDIRECT3DTEXTURE9 lpBoxWindow[2];
	LPDIRECT3DTEXTURE9 lpBoxCheckBox[2];
	LPDIRECT3DTEXTURE9 lpBoxLine;
	LPDIRECT3DTEXTURE9 lpBoxLeftArrow[2];
	LPDIRECT3DTEXTURE9 lpBoxRightArrow[2];
	LPDIRECT3DTEXTURE9 lpBoxSodBar;
	int OpenFlag;
	int Kind;
	int x,y;
	int CloseFlag;
	int EnterFlag;
	int PageFlag[2];
	int Page;
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
	int sinShow(int kind,int px,int py,char *FileName = NULL);
	int ReadFileData(char *FileName);
	int ReadFileDataDivide(char *szBuf);
};

extern cSINBOX cSinBox;
extern sSODELEMENT sSODElement;

#endif