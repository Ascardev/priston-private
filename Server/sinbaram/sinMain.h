/*----------------------------------------------------------------------------*
*	���ϸ� :  sinMain.h
*	�ϴ��� :  �Źٶ� ���� 
*	�ۼ��� :  ����������Ʈ 12��
*	������ :  �ڻ� 
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
*							�Լ� 

*-----------------------------------------------------------------------------*/	




	
extern int	 quit;
extern POINT pCursorPos;		//���콺 ��ǥ 	

extern HWND  hFocusWnd; //ä�� ��Ŀ�� 

extern HWND hwnd;

extern CharacterData *sinChar;		//ĳ���� ���� ����ü 
extern CharacterData sinCharDisplay; //ĳ���� ���� ����ü (��ŷ������ ���)
extern int sinbaram_Stop;