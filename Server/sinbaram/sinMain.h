/*----------------------------------------------------------------------------*
*	파일명 :  sinMain.h
*	하는일 :  신바람 메인 
*	작성일 :  최종업데이트 12월
*	적성자 :  박상열 
*-----------------------------------------------------------------------------*/	

#define		 SINLBUTTONDOWN			10
#define		 SINLBUTTONUP 			11
#define		 SINRBUTTONDOWN			110
#define		 SINRBUTTONUP 			111

#define		 SINMOUSEMOVE			2
#define		 SINKEYDOWN				3

#define      SIN_CHAR_FIGHTER		1
#define      SIN_CHAR_MECANICIAN	2
#define      SIN_CHAR_ARCHER		3
#define      SIN_CHAR_PIKEMAN		4
#define		 SIN_CHAR_KNIGHT		6
#define		 SIN_CHAR_ATALANTA		5
#define		 SIN_CHAR_PRIESTESS		8
#define		 SIN_CHAR_MAGICIAN		7

/*----------------------------------------------------------------------------*
*							함수 

*-----------------------------------------------------------------------------*/	




	
extern int	 quit;
extern POINT pCursorPos;		//마우스 좌표 	

extern HWND  hFocusWnd; //채팅 포커스 

extern HWND hwnd;

extern CharacterData *sinChar;		//캐릭터 정보 구조체 
extern CharacterData sinCharDisplay; //캐릭터 정보 구조체 (해킹방지용 백업)
extern int sinbaram_Stop;