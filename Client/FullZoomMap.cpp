#include "StdAfx.h"
#include "smwsock.h"
#include "character.h"
#include "playmain.h"
#include "FullZoomMap.h"


#define DMAX_fzmcp_DRAW_TYPE			2
#define DMAX_fzm_CHAR_POS				6

#define dMAX_FZM_EFFECT_SUBNUM			10
#define dMAX_NAME_EFFECT				20
#define	dMAX_FZM_CHAR_POS				6


enum EFzmcpDrawType
{
	EFZMCP_LEFT_TOP = 0,	// ÁÂÃø»ó´Ü.
	EFZMCP_LEFT_BOTTOM = 1,	// ÁÂÃøÇÏ´Ü.
};

//
enum EFzmNameType
{
	EPilait = 1,	// ÇÊ¶óÀÌ.
	Efallfore_1 = 2,	// ¹Ù¶÷ÀÌ ÀÌ²ô´Â ±æ.
	Efallfore_2 = 3,	// °í¿äÀÇ °è°î.
	Efallfore_3 = 4,	// È²È¥ÀÇ ½£.
	EMcavet = 5,	// ¹úÁýµ¿±¼.
	Efallfore_4 = 6,	// Á¤·ÉÀÇ ½£.
	ERuin_3 = 7,	// ·çÀÌ³Ù ºô¸®Áö.
	Edunt = 8,	// °í´ë °¨¿Á.
	ERuin_4 = 9,	// ÀúÁÖ¹ÞÀº ¶¥.
	ERuin_2 = 10,	// Æó¼º°û.
	ERuin_1 = 11,	// °í´ëÀÎÀÇ ¾È½ÄÃ³.
	ETcavet = 12,	// ¹ö¼¸ µ¿±¼.
	Efore_3 = 13,	// ¾ÆÄ«½Ã¾Æ ½£.
	Efore_2 = 14,	// ´ë³ª¹« ½£.
	Efore_1 = 15,	// ÀÚÀ¯ÀÇ Á¤¿ø.
	ERicaT = 16,	// ¸®Ä«¸£ÅÙ.
	Ede_1 = 17,	// ÀØÇôÁø ¶¥.
	Ede_nv = 18,	// ³×ºñ½ºÄÚ.
	Ede_2 = 19,	// ¿À¾Æ½Ã½º.
	Ede_3 = 20,	// °í´ëÀÎÀÇ ÀüÀå.
	Esint = 21,	// ÀúÁÖ¹ÞÀº ½ÅÀü.
	Ede_4 = 22,	// ±Ý´ÜÀÇ ¶¥.
	Eiron_1 = 23,	// È¥µ·ÀÇ Ã¶·Î.
	EDcavet = 24,	// ¾îµÒÀÇ ¼ºÀü.
	Eiron_2 = 25,	// Æó·ëÀÇ ½ÉÀå.
	Eyura_1 = 26,   // À¯¶ó ºô¸®Áö.
	EIce_1 = 27,   // ¾ÆÀÌ½º ÇÊµå
	EGreedy = 28,   // ±×¸®µð È£¼ö
	EIce_2 = 29,   // ¾ÆÀÌ½º ÇÊµå 2
	ELost_1 = 30,   // ·Î½ºÆ® ¾ÆÀÏ·£µå
	ELost_2 = 31,	// ·Î½ºÆ® ÅÛÇÃ
	EFzmNameMax = 31,   // ¸Æ½º ÀÎµ¦½º 
};


//
struct SFullZoomMapInfo
{
	EFzmNameType			eNameType;
	int						iNamePosX;
	int						iNamePosY;

	EFzmcpDrawType			eFzmcpDrawType;
	int						iFzmCharPosX;
	int						iFzmCharPosY;

	int						iZoomMapIsCharPos;
	float					fRatio;
};

//
struct SFullZoomMapImage
{
	int						iCheckWideh;
	int						iCheckHeight;
	smTEXTUREHANDLE	*lpDDS_Name;

	int						iMapOffset_x;
	int						iMapOffset_y;
};

//
struct SMapStageInfo
{
	RECT			rcStageMapRect;
	int				iStageWidth;
	int				iStageHeight;
	float			fRatio;
};

//
struct SFullZoomMapEffectInfo
{
	int				MaxFrameNum;
	int				DelayTime[dMAX_FZM_EFFECT_SUBNUM];
	BYTE		    BlendNum[dMAX_FZM_EFFECT_SUBNUM];
	int				ScaleNum[dMAX_FZM_EFFECT_SUBNUM];
};

//
enum EFzmEffectType
{
	NAME_EFFECT = 1,
	CHAR_POS_EFFECT = 2,
	CHAR_POS_NAME_EFFECT = 3,
};

//
struct SFullZoomMapEffect
{
	EFzmEffectType				eEffectType;
	SFullZoomMapEffectInfo	   *lpEffectInfo;

	int				Life;
	int				FrameTime;
	int				FrameNum;
	int				EventNum;
	POINT			Pos;
	int				HalfSize;
	float			fBlendNum;
	float			fBlendStep;
	float			fScaleNum;
	float			fScaleStep;
};

//
enum ECharType
{
	USER_CHAR = 1,
	PARTY_CHAR = 2,
};

//
struct SFzmCharPos
{
	ECharType		eCharType;
	int				iXpos;
	int				iYpos;
};


//######################################################################################
//
static POINT				s_FzmcpInfo[DMAX_fzm_CHAR_POS] =
{
	{0, 0 }, {10, 0 }, {20, 0 },
	{0, 10}, {10, 10}, {20, 10},
};

//
static int					s_FzmcpIndex[DMAX_fzmcp_DRAW_TYPE][DMAX_fzm_CHAR_POS] =
{
	{0,1,2,3,4,5},
	{3,4,5,0,1,2},
};
static SFullZoomMapInfo		s_FzmInfo[EFzmNameMax] =
{
	{ EPilait    ,440, 18, EFZMCP_LEFT_TOP   ,440, 32 ,1,508.f },					// 0.  ÇÊ¶óÀÌ.
	{ Efallfore_1,412, 68, EFZMCP_LEFT_TOP	 ,466, 68 ,1,0 },						// 1.  ¹Ù¶÷ÀÌ ÀÌ²ô´Â ±æ.
	{ Efallfore_2,411,143, EFZMCP_LEFT_BOTTOM,411, 122,1,0 },						// 2.  °í¿äÀÇ °è°î.
	{ Efallfore_3,480,177, EFZMCP_LEFT_TOP	 ,480, 191,1,0 },						// 3.  È²È¥ÀÇ ½£.
	{ EMcavet	 ,397,191, EFZMCP_LEFT_TOP	 ,397, 205,0,0 },						// 4.  ¹úÁýµ¿±¼.
	{ Efallfore_4,535,216, EFZMCP_LEFT_TOP	 ,535, 230,1,0 },						// 5.  Á¤·ÉÀÇ ½£.
	{ ERuin_3	 ,456,271, EFZMCP_LEFT_TOP	 ,493, 271,1,0 },						// 6.  ·çÀÌ³Ù ºô¸®Áö.
	{ Edunt		 ,551,298, EFZMCP_LEFT_BOTTOM,569, 276,0,0 },						// 7.  °í´ë °¨¿Á.
	{ ERuin_4	 ,535,327, EFZMCP_LEFT_TOP	 ,535, 341,1,0 },						// 8.  ÀúÁÖ¹ÞÀº ¶¥.
	{ ERuin_2	 ,461,336, EFZMCP_LEFT_TOP	 ,461, 350,1,0 },						// 9.  Æó¼º°û.
	{ ERuin_1	 ,490,392, EFZMCP_LEFT_TOP	 ,539, 392,1,0 },						// 10. °í´ëÀÎÀÇ ¾È½ÄÃ³.
	{ ETcavet	 ,362,386, EFZMCP_LEFT_BOTTOM,381, 365,0,0 },						// 11. ¹ö¼¸ µ¿±¼.
	{ Efore_3	 ,358,424, EFZMCP_LEFT_TOP	 ,380, 438,1,0 },						// 12. ¾ÆÄ«½Ã¾Æ ½£.
	{ Efore_2	 ,413,464, EFZMCP_LEFT_BOTTOM,436, 443,1,0 },						// 13. ´ë³ª¹« ½£.
	{ Efore_1	 ,505,449, EFZMCP_LEFT_TOP	 ,505, 463,1,0 },						// 14. ÀÚÀ¯ÀÇ Á¤¿ø.
	{ ERicaT	 ,502,513, EFZMCP_LEFT_TOP	 ,502, 527,1,477.f },					// 15. ¸®Ä«¸£ÅÙ.
	{ Ede_1		 ,568,376, EFZMCP_LEFT_TOP	 ,588, 391,1,0 },						// 16. ÀØÇôÁø ¶¥.
	{ Ede_nv	 ,621,403, EFZMCP_LEFT_BOTTOM,640, 382,1,0 },						// 17. ³×ºñ½ºÄÚ.
	{ Ede_2		 ,636,460, EFZMCP_LEFT_TOP	 ,636, 474,1,0 },						// 18. ¿À¾Æ½Ã½º.
	{ Ede_3		 ,678,372, EFZMCP_LEFT_TOP	 ,678, 386,1,0 },						// 19. °í´ëÀÎÀÇ ÀüÀå.
	{ Esint		 ,682,417, EFZMCP_LEFT_TOP	 ,733, 417,0,0 },						// 20. ÀúÁÖ¹ÞÀº ½ÅÀü.
	{ Ede_4		 ,655,314, EFZMCP_LEFT_TOP	 ,710, 314,1,0 },						// 21. ±Ý´ÜÀÇ ¶¥.
	{ Eiron_1	 ,746,249, EFZMCP_LEFT_TOP	 ,752, 277,1,0 },						// 22. È¥µ·ÀÇ Ã¶·Î.
	{ EDcavet	 ,367,296, EFZMCP_LEFT_TOP	 ,376, 325,1,0 },						// 23. ¾îµÒÀÇ ¼ºÀü.
	{ Eiron_2	 ,653,248, EFZMCP_LEFT_TOP	 ,663, 270,1,352.f },					// 24. Æó·ëÀÇ ½ÉÀå.
	{ Eyura_1    ,588,178, EFZMCP_LEFT_TOP	 ,598, 205,1,378.f },					// 25. À¯¶ó ºô¸®Áö.
	{ EIce_1     ,655,166, EFZMCP_LEFT_TOP	 ,659, 182,1,0 },					    // 26. ¾ÆÀÌ½º ÇÊµå.
	{ EGreedy    ,565,267, EFZMCP_LEFT_TOP	 ,565, 267,1,0 },					    // 27. ±×¸®µð È£¼ö.
	{ EIce_2     ,712,97 , EFZMCP_LEFT_TOP	 ,712, 97 ,1,0 },					    // 28. ¾ÆÀÌ½º ÇÊµå2.
	{ ELost_1	 ,595,530, EFZMCP_LEFT_BOTTOM,596, 533,1,0 },					    // 29. ·Î½ºÆ® ¾ÆÀÏ·£µå
	{ ELost_2	 ,578,477, EFZMCP_LEFT_TOP	 ,578, 477,1,0 },					    // 30. ·Î½ºÆ® ÅÛÇÃ 

};
static int s_iFzmFieldCodeInfo[] =
{
	12, // ¾ÆÄ«½Ã¾Æ ½£.
		13, // ´ë³ª¹« ½£.
		14, // ÀÚÀ¯ÀÇ Á¤¿ø.
		15, // ¸®Ä«¸£ÅÙ.
		10, // °í´ëÀÎÀÇ ¾È½ÄÃ³.
		9,  // Æó¼º°û.
		6,  // ·çÀÌ³Ù ºô¸®Áö.
		8,  // ÀúÁÖ¹ÞÀº ¶¥.
		16, // ÀØÇôÁø ¶¥.
		17, // ³×ºñ½ºÄÚ.
		18, // ¿À¾Æ½Ã½º.
		19, // °í´ëÀÎÀÇ ÀüÀå.
		21, // ±Ý´ÜÀÇ ¶¥.
		7,  // °í´ë °¨¿Á. (1Ãþ)
		7,  // °í´ë °¨¿Á. (2Ãþ)
		7,  // °í´ë °¨¿Á. (3Ãþ)
		7,  // Àå±âÆÇ.
		5,  // Á¤·ÉÀÇ ½£.
		3,  // È²È¥ÀÇ ½£.
		2,  // °í¿äÀÇ °è°î.
		1,  // ¹Ù¶÷ÀÌ ÀÌ²ô´Â ±æ.
		0,  // ÇÊ¶óÀÌ.
		20, // ÀúÁÖ¹ÞÀº ½ÅÀü. (1Ãþ)
		20, // ÀúÁÖ¹ÞÀº ½ÅÀü. (2Ãþ)
		11, // ¹ö¼¸ µ¿±¼.
		4,  // ¹úÁýµ¿±¼.
		23, // ¾îµÒÀÇ ¼ºÀü.
		22, // È¥µ·ÀÇ Ã¶·Î.
		24,	// Æó·ëÀÇ ½ÉÀå.
		25, // À¯¶ó ºô¸®Áö.	
		4,	// SOD
		26, // ¾ÆÀÌ½º ÇÊµå
		4,  // ´ëÀüÀå
		4,  // °ø¼ºÇÊµå
		27, // ±×¸®µð È£¼ö
		28, // ¾ÆÀÌ½º ÇÊµå2
		// ÇöÀç »ç¿ëÄ¡ ¾ÊÀ½.	
		4,
		29, // ·Î½ºÆ® ¾ÆÀÏ·£µå			
		30, // ·Î½ºÆ® ÅÛÇÃ
		4,
		30, // ÎÞ¾¡Ö®Ëþ1
		30, // ÎÞ¾¡Ö®Ëþ2
		20, // »ÞÆøËÂÃí3
		30, // ÎÞ¾¡Ö®Ëþ3
		28,  // ±ù·â¶´Ñ¨
		4,	// ÄÚÎ¬Ë¹¿Ë¶´Ñ¨
		4,	// Âå¿Ë¶´Ñ¨
		4,	// ÃÔÊ§µºÓì
		4,4,4,4,	// ¹Å´úÉ­ÁÖ
		4,4,4,4,	// »Ã¾³É³Ä®
		4,	// ÌúÂ·3
		4,	// °µºÚBOSS
};

//
static char	*s_lpFzmINamePtrBuff[EFzmNameMax * 2] =			//¹Ì´Ï¸Ê ÀÌ¸§ ,¹Ì´Ï¸Ê ÀÌ¹ÌÁö
{
	// ÇÊ¶óÀÌ.
	"Pilait.bmp",
		"town_PLX-40Y-36.bmp",

		// ¹Ù¶÷ÀÌ ÀÌ²ô´Â ±æ.
		"fallfore-1t.bmp",
		"fallfore-1X70.bmp",

		// °í¿äÀÇ °è°î.
		"fallfore-2t.bmp",
		"fallfore-2X10.bmp",

		// È²È¥ÀÇ ½£.
		"fallfore-3t.bmp",
		"fallfore-3X5.bmp",

		// ¹úÁýµ¿±¼.
		"_Mcavet.bmp",
		"dun.bmp",				// Áßº¹. Àç»ç¿ë ÇÑ´Ù.

		// Á¤·ÉÀÇ ½£.
		"fallfore-4t.bmp",
		"fallfore-4X30.bmp",

		// ·çÀÌ³Ù ºô¸®Áö.
		"Ruin-3t.bmp",
		"Ruin-3Y10.bmp",

		// °í´ë °¨¿Á.
		"_dunt.bmp",
		"@4",					// "dun.bmp"

		// ÀúÁÖ¹ÞÀº ¶¥.
		"Ruin-4t.bmp",
		"Ruin-4X40.bmp",

		// Æó¼º°û.
		"Ruin-2t.bmp",
		"Ruin-2X0.bmp",

		// °í´ëÀÎÀÇ ¾È½ÄÃ³.
		"Ruin-1t.bmp",
		"Ruin-1X10.bmp",

		// ¹ö¼¸ µ¿±¼.
		"_Tcavet.bmp",
		"@4",					// "dun.bmp"

		// ¾ÆÄ«½Ã¾Æ ½£.
		"fore-3t.bmp",
		"fore-3X2Y20.bmp",

		// ´ë³ª¹« ½£.
		"fore-2t.bmp",
		"fore-2Y-5.bmp",

		// ÀÚÀ¯ÀÇ Á¤¿ø.
		"fore-1t.bmp",
		"fore-1X20.bmp",

		// ¸®Ä«¸£ÅÙ.
		"town_RicaT.bmp",
		"town_RicaX-88Y-77.bmp",

		// ÀØÇôÁø ¶¥.
		"de-1t.bmp",
		"de-1X30.bmp",

		// ³×ºñ½ºÄÚ.
		"de-NVt.bmp",
		"de-NVY40.bmp",

		// ¿À¾Æ½Ã½º.
		"de-2t.bmp",
		"de-2X30.bmp",

		// °í´ëÀÎÀÇ ÀüÀå.
		"de-3t.bmp",
		"de-3Y20.bmp",

		// ÀúÁÖ¹ÞÀº ½ÅÀü.
		"_sint.bmp",
		"@4",					// "dun.bmp"

		// ±Ý´ÜÀÇ ¶¥.
		"de-4t.bmp",
		"de-4Y30.bmp",

		// È¥µ·ÀÇ Ã¶·Î.
		"iron-1t.bmp",
		"iron-1X40.bmp",

		// ¾îµÒÀÇ ¼ºÀü.
		"_Dcavet.bmp",
		"@4",					// "dun.bmp"

		// Æó·ëÀÇ ½ÉÀå.
		"iron_2t.bmp",
		"iron2X-15Y14.bmp",

		// À¯¶ó ºô¸®Áö.
		"yura_1t.bmp",
		"yuraX15Y-22.bmp",

		//¾ÆÀÌ½º ÇÊµå
		"ice1-x655y166.bmp",
		"ice1_X40Y3.bmp",

		//±×¸®µð È£¼ö
		"greedy_x565y267.bmp",
		"greedy_x-15y-28.bmp",

		//¾ÆÀÌ½ºÇÊµå2
		"ice2-x712y97.bmp",
		"ice2_X0Y0.bmp",

		//·Î½ºÆ® ¾ÆÀÏ·£µå 
		"Lost-1t.bmp",
		"lost-1t_x0_y0.bmp",

		//·Î½ºÆ® ÅÛÇÃ 
		"lost-2_x579y478.bmp",
		"lost-2_x0_y0.bmp"

};

//
static int s_iFzmMapOffset[EFzmNameMax][2] =
{
	{-40, -36}, // ÇÊ¶óÀÌ.
	{ 70,   0}, // ¹Ù¶÷ÀÌ ÀÌ²ô´Â ±æ.
	{ 10,   0}, // °í¿äÀÇ °è°î.
	{  5,   0}, // È²È¥ÀÇ ½£.
	{  0,   0}, // ¹úÁýµ¿±¼.
	{ 30,   0}, // Á¤·ÉÀÇ ½£.
	{  0,  10}, // ·çÀÌ³Ù ºô¸®Áö.
	{  0,   0}, // °í´ë °¨¿Á.
	{ 40,   0}, // ÀúÁÖ¹ÞÀº ¶¥.
	{  0,   0}, // Æó¼º°û.
	{ 10,   0}, // °í´ëÀÎÀÇ ¾È½ÄÃ³.
	{  0,   0}, // ¹ö¼¸ µ¿±¼.
	{  2,  20}, // ¾ÆÄ«½Ã¾Æ ½£.
	{  0,  -5}, // ´ë³ª¹« ½£.
	{ 20,   0}, // ÀÚÀ¯ÀÇ Á¤¿ø.
	{-88, -77}, // ¸®Ä«¸£ÅÙ.
	{ 30,   0}, // ÀØÇôÁø ¶¥.
	{  0,  40}, // ³×ºñ½ºÄÚ.
	{ 30,   0}, // ¿À¾Æ½Ã½º.
	{  0,  20}, // °í´ëÀÎÀÇ ÀüÀå.
	{  0,   0}, // ÀúÁÖ¹ÞÀº ½ÅÀü.
	{  0,  30}, // ±Ý´ÜÀÇ ¶¥.
	{ 40,   0}, // È¥µ·ÀÇ Ã¶·Î.
	{  0,   0}, // ¾îµÒÀÇ ¼ºÀü.
	{-15,  14}, // Æó·ëÀÇ ½ÉÀå.
	{ 15, -22}, // À¯¶ó ºô¸®Áö.
	{ 40,   3}, // ¾ÆÀÌ½º ÇÊµå
	{ 15,  -4}, // ±×¸®µð È£¼ö
	{ 20,  -4}, // ¾ÆÀÌ½º ÇÊµå 2
	{ 30,  18}, // ·Î½ºÆ® ¾ÆÀÏ·£µå
	{ 7 ,  38}, // ·Î½ºÆ® ÅÛÇÃ
};

//
static SFullZoomMapEffectInfo   s_NameEffectDataInfo =
{
	{  3 },
	{  0,  16, 30, 0,},
	{100, 255, 20, 0,},
	{  0,  12, 24, 0,},
};

//
static SFullZoomMapEffectInfo   s_CharPosEffectDataInfo =
{
	{  4 },
	{  0,  20,  30,  30, 0, },
	{255, 255, 255, 100, 0, },
	{  0,   6,   6,   6, 0, },
};


//######################################################################################
//
extern float g_fWinSizeRatio_X;
extern float g_fWinSizeRatio_Y;

extern int MatArrow;
extern int psDrawTexImage2(smTEXTUREHANDLE *hTexHandle, float *x, float *y, float fx, float fy, float fw, float fh, int Transp, int specular);

//
static void	CreateFullZoomMap(void);
static void DestroyFullZoomMap(void);
static int  LoadZoomInMap(SFullZoomMapInfo  *lpZoomMapInfo);
static void	SetFzmEffect(EFzmEffectType eEffectType, SFullZoomMapEffectInfo *lpEffectInfo, int EventNum, int ActiveName);
static void	MainFzmEffect(void);
static void	DrawFzmEffect(void);
static void	SetMapStageInfo(void);
static void	SetFzmCharPos(void);

//
static SMapStageInfo			s_MapStageInfoBuff[256];
static SFullZoomMapImage		s_FzmImage[EFzmNameMax];

static int						s_iMouseLButtonState[2] = { -1,-1 };
static POINT					s_CurPlayerPos;
static int						s_iFzmActiveName = -1;
static int						s_iFzmFocusName = -1;
static smTEXTUREHANDLE		*s_lpDDS_FzmActiveMap;

static smTEXTUREHANDLE		*s_lpDDS_Exit;
static smTEXTUREHANDLE		*s_lpDDS_ExitImage;
static smTEXTUREHANDLE		*s_lpDDS_ExitFocusImage;
static POINT					s_ExitButtonPos;

static SFullZoomMapEffect		s_NameEffectBuff[dMAX_NAME_EFFECT];
static int						s_iFzmNameEffectMatNum;

static int						s_iFzmCharPosNameEffectTime;

static SFzmCharPos				s_FzmCharPosBuff[dMAX_FZM_CHAR_POS];
static int						s_iFzmCharPosNum;

static smTEXTUREHANDLE		*s_lpDDS_FullMapImage;
static int						s_iFzmUserLargeMatNum;
static int						s_iFzmPartyLargeMatNum;
static int						s_iFzmUserSmallMatNum;

//
int								g_iFzmCursorFocusGame;

int								g_iFzmCursorPosX;
int								g_iFzmCursorPosY;
int								g_FzmMouseButton[3];


//######################################################################################
//ÀÛ ¼º ÀÏ : 2004-04-08 ¿ÀÈÄ 3:27:06
//¸® ÅÏ °ª :
//¼³    ¸í :
//ÀÛ ¼º ÀÚ : ¿À ¿µ ¼®
//######################################################################################
static void SetFzmEffect(EFzmEffectType eEffectType, SFullZoomMapEffectInfo *lpEffectInfo, int EventNum, int ActiveName)
{
	if (ActiveName < 0)
		return;

	for (int i = 0; i < dMAX_NAME_EFFECT; i++)
	{
		if (s_NameEffectBuff[i].Life == 0)
		{
			SFullZoomMapInfo  *lpZoomMapInfo = &s_FzmInfo[ActiveName];
			SFullZoomMapImage *lpZoomMapImage = &s_FzmImage[lpZoomMapInfo->eNameType - 1];

			::ZeroMemory(&s_NameEffectBuff[i], sizeof(s_NameEffectBuff[i]));
			s_NameEffectBuff[i].lpEffectInfo = lpEffectInfo;
			s_NameEffectBuff[i].eEffectType = eEffectType;

			s_NameEffectBuff[i].Life = 1;
			s_NameEffectBuff[i].EventNum = EventNum;
			s_NameEffectBuff[i].Pos.x = lpZoomMapInfo->iNamePosX + (lpZoomMapImage->iCheckWideh >> 1);
			s_NameEffectBuff[i].Pos.y = lpZoomMapInfo->iNamePosY + (lpZoomMapImage->iCheckHeight >> 1);
			s_NameEffectBuff[i].HalfSize = 8;
			s_NameEffectBuff[i].fBlendNum = float(lpEffectInfo->BlendNum[0]);
			s_NameEffectBuff[i].fScaleNum = float(lpEffectInfo->ScaleNum[0]);
			return;
		}
	}
}
static void MainFzmEffect(void)
{
	//
	static int iFieldCode;
	if (s_iFzmCharPosNameEffectTime > 160)
	{
		if (lpCurPlayer->iLoadedMapIndex >= 0)
		{
			iFieldCode = STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID;
			SetFzmEffect(CHAR_POS_NAME_EFFECT, &s_NameEffectDataInfo, 2, s_iFzmFieldCodeInfo[iFieldCode]);
		}

		s_iFzmCharPosNameEffectTime = 0;
	}
	else
		s_iFzmCharPosNameEffectTime++;

	for (int i = 0; i < dMAX_NAME_EFFECT; i++)
	{
		if (s_NameEffectBuff[i].Life)
		{
			SFullZoomMapEffect *lpNameEffect = &s_NameEffectBuff[i];
			lpNameEffect->FrameTime++;

			if (lpNameEffect->FrameTime >= lpNameEffect->lpEffectInfo->DelayTime[lpNameEffect->FrameNum])
			{
				lpNameEffect->FrameNum++;
				if (lpNameEffect->EventNum == lpNameEffect->FrameNum)
				{
					if (lpNameEffect->eEffectType == NAME_EFFECT)
						SetFzmEffect(NAME_EFFECT, &s_NameEffectDataInfo, 0, s_iFzmActiveName);
					else if (lpNameEffect->eEffectType == CHAR_POS_EFFECT)
						SetFzmEffect(CHAR_POS_EFFECT, &s_CharPosEffectDataInfo, 3, s_iFzmActiveName);
					else if (lpNameEffect->eEffectType == CHAR_POS_NAME_EFFECT)
						SetFzmEffect(CHAR_POS_NAME_EFFECT, &s_NameEffectDataInfo, 0, s_iFzmFieldCodeInfo[iFieldCode]);
				}

				if (lpNameEffect->FrameNum >= lpNameEffect->lpEffectInfo->MaxFrameNum)
					lpNameEffect->Life = 0;
				else
				{
					lpNameEffect->FrameTime = 0;
					lpNameEffect->fBlendNum = float(lpNameEffect->lpEffectInfo->BlendNum[lpNameEffect->FrameNum - 1]);
					lpNameEffect->fScaleNum = float(lpNameEffect->lpEffectInfo->ScaleNum[lpNameEffect->FrameNum - 1]);

					float fDelayTime = float(lpNameEffect->lpEffectInfo->DelayTime[lpNameEffect->FrameNum]);
					lpNameEffect->fBlendStep = (lpNameEffect->lpEffectInfo->BlendNum[lpNameEffect->FrameNum] - lpNameEffect->fBlendNum) / fDelayTime;
					lpNameEffect->fScaleStep = (lpNameEffect->lpEffectInfo->ScaleNum[lpNameEffect->FrameNum] - lpNameEffect->fScaleNum) / fDelayTime;
				}
			}
			else
			{
				lpNameEffect->fBlendNum += lpNameEffect->fBlendStep;
				lpNameEffect->fScaleNum += lpNameEffect->fScaleStep;
			}
		}
	}
}
static void DrawFzmEffect(void)
{
	for (int i = 0; i < dMAX_NAME_EFFECT; i++)
	{
		if (s_NameEffectBuff[i].Life && s_NameEffectBuff[i].eEffectType != CHAR_POS_EFFECT)
		{
			SFullZoomMapEffect *lpNameEffect = &s_NameEffectBuff[i];

			DrawFzmBackToTexture2D(smMaterial[s_iFzmNameEffectMatNum].smTexture[0], lpNameEffect->Pos.x, lpNameEffect->Pos.y, 0, lpNameEffect->HalfSize + int(lpNameEffect->fScaleNum), int(lpNameEffect->fBlendNum));
		}
	}
}
static void SetMapStageInfo(void)
{
	FILE *fp = NULL;

	fopen_s(&fp, "image\\GuideMap\\StageInfo.dat", "rb");
	if (fp)
	{
		fread(s_MapStageInfoBuff, sizeof(s_MapStageInfoBuff), 1, fp);
		fclose(fp);
	}
#ifdef _DEBUG
	else
	{
		smSTAGE3D			 MapStage;
		SFullZoomMapInfo	*lpZoomMapInfo;
		int					 Width, Height;
		float				 fRatio;

		MapStage.Init();
		for (int i = 0; i < NUM_MAPS; i++)
		{
			BaseMap * pcMap = GAMEMAP->pcaBaseMap + i;

			if (smSTAGE3D_ReadASE(pcMap->szStageFilePath, &MapStage))
			{
				::CopyMemory(&s_MapStageInfoBuff[i].rcStageMapRect, &MapStage.StageMapRect, sizeof(RECT));
				s_MapStageInfoBuff[i].iStageWidth = MapStage.StageMapRect.right - MapStage.StageMapRect.left;
				s_MapStageInfoBuff[i].iStageHeight = MapStage.StageMapRect.bottom - MapStage.StageMapRect.top;

				Width = s_MapStageInfoBuff[i].iStageWidth;
				Height = s_MapStageInfoBuff[i].iStageHeight;

				lpZoomMapInfo = &s_FzmInfo[s_iFzmFieldCodeInfo[i]];
				if (lpZoomMapInfo->fRatio)
				{
					if (Width > Height)
						fRatio = float(Width) / lpZoomMapInfo->fRatio;
					else
						fRatio = float(Height) / lpZoomMapInfo->fRatio;
				}
				else
				{
					if (Width > Height)
						fRatio = float(Width) / 320.f;
					else
						fRatio = float(Height) / 320.f;
				}

				s_MapStageInfoBuff[i].fRatio = fRatio;

				MapStage.Close();
				MapStage.Init();
			}
		}

		fopen_s(&fp, "image\\GuideMap\\StageInfo.dat", "wb");
		if (fp)
		{
			fwrite(s_MapStageInfoBuff, sizeof(s_MapStageInfoBuff), 1, fp);
			fclose(fp);
		}
	}
#endif
}
static void SetFzmCharPos(void)
{
	if (s_iFzmActiveName < 0)
		return;
	s_iFzmCharPosNum = 0;

	SFullZoomMapInfo  *lpZoomMapInfo = &s_FzmInfo[s_iFzmActiveName];
	SFullZoomMapImage *lpZoomMapImage = &s_FzmImage[lpZoomMapInfo->eNameType - 1];

	if (STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == MAPID_EndlessTowerF1 ||
		STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == MAPID_EndlessTowerF2 ||
		STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == MAPID_EndlessTowerF3 ||
		STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == MAPID_IceMineF1)
		return;
	if (lpZoomMapInfo->iZoomMapIsCharPos <= 0)
		return;

	int	   cnt;
	float  fRatio = 0;
	RECT  *lpRect = NULL;

	// User ////////////////////////////////////////////////////////////////////////
	if (lpCurPlayer->iLoadedMapIndex >= 0)
	{
		int iFieldCode = STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID;
		if (s_iFzmActiveName == s_iFzmFieldCodeInfo[iFieldCode])
		{

			lpRect = &s_MapStageInfoBuff[iFieldCode].rcStageMapRect;
			fRatio = s_MapStageInfoBuff[iFieldCode].fRatio;

			s_FzmCharPosBuff[s_iFzmCharPosNum].eCharType = USER_CHAR;

			s_FzmCharPosBuff[s_iFzmCharPosNum].iXpos = int(float(lpCurPlayer->pX - lpRect->left) / fRatio);
			s_FzmCharPosBuff[s_iFzmCharPosNum].iYpos = int(float(lpRect->bottom - lpCurPlayer->pZ) / fRatio);
			s_iFzmCharPosNum++;
		}
	}
	if (InterfaceParty.PartyMemberCount)
	{
		if (s_iFzmCharPosNum <= 0)
		{
			for (cnt = 0; cnt < NUM_MAPS; cnt++)
			{
				if (s_iFzmActiveName == s_iFzmFieldCodeInfo[cnt])
				{
					lpRect = &s_MapStageInfoBuff[cnt].rcStageMapRect;
					fRatio = s_MapStageInfoBuff[cnt].fRatio;
					break;
				}
			}
		}

		if (lpRect == NULL)
			return;

		for (cnt = 0; cnt < InterfaceParty.PartyMemberCount; cnt++)
		{
			if (InterfaceParty.PartyMember[cnt].ChrCode != lpCurPlayer->iID)
			{
				POINT3D *lpChPos = &InterfaceParty.PartyMember[cnt].CharacterPos;
				if (lpChPos->x > lpRect->left && lpChPos->x < lpRect->right &&
					lpChPos->z > lpRect->top  && lpChPos->z < lpRect->bottom)
				{
					if (s_iFzmCharPosNum >= dMAX_FZM_CHAR_POS)
						return;

					s_FzmCharPosBuff[s_iFzmCharPosNum].eCharType = PARTY_CHAR;
					s_FzmCharPosBuff[s_iFzmCharPosNum].iXpos = int(float(lpChPos->x - lpRect->left) / fRatio);
					s_FzmCharPosBuff[s_iFzmCharPosNum].iYpos = int(float(lpRect->bottom - lpChPos->z) / fRatio);
					s_iFzmCharPosNum++;
				}
			}
		}
	}
}
static void CreateFullZoomMap(void)
{
	if (g_IsDxProjectZoomIn > 0)
		return;

	char szFullName[128];
	char szDirectory[32];
	lstrcpy(szDirectory, "image\\GuideMap\\");

	CopyMemory(szFullName, szDirectory, 32);
	lstrcat(szFullName, "_AFull.bmp");
	s_lpDDS_FullMapImage = LoadDibSurfaceOffscreen(szFullName);

	CopyMemory(szFullName, szDirectory, 32);
	lstrcat(szFullName, "exit_1.bmp");
	s_lpDDS_ExitImage = LoadDibSurfaceOffscreen(szFullName);

	s_lpDDS_Exit = s_lpDDS_ExitImage;
	s_ExitButtonPos.x = 682;
	s_ExitButtonPos.y = 547;

	CopyMemory(szFullName, szDirectory, 32);
	lstrcat(szFullName, "exit_2.bmp");
	s_lpDDS_ExitFocusImage = LoadDibSurfaceOffscreen(szFullName);

	for (int i = 0; i < EFzmNameMax; i++)
	{
		CopyMemory(szFullName, szDirectory, 32);
		lstrcat(szFullName, s_lpFzmINamePtrBuff[i * 2]);
		s_FzmImage[i].lpDDS_Name = LoadDibSurfaceOffscreen(szFullName);

		if (s_FzmImage[i].lpDDS_Name)
		{
			s_FzmImage[i].iCheckWideh = s_FzmImage[i].lpDDS_Name->Width;
			s_FzmImage[i].iCheckHeight = s_FzmImage[i].lpDDS_Name->Height;
		}

		s_FzmImage[i].iMapOffset_x = s_iFzmMapOffset[i][0];
		s_FzmImage[i].iMapOffset_y = s_iFzmMapOffset[i][1];
	}

	SetMapStageInfo();
}
static void DestroyFullZoomMap(void)
{
	DELET(s_lpDDS_FullMapImage);
	DELET(s_lpDDS_ExitImage);
	DELET(s_lpDDS_ExitFocusImage);

	for (int i = 0; i < EFzmNameMax; i++)
	{
		DELET(s_FzmImage[i].lpDDS_Name);
	}

	DELET(s_lpDDS_FzmActiveMap);
}
static int LoadZoomInMap(SFullZoomMapInfo  *lpZoomMapInfo)
{
	if (lpZoomMapInfo == NULL)
		return FALSE;

	char szFullName[128] = { 0, };
	::lstrcpy(szFullName, "image\\GuideMap\\");

	int index = ((lpZoomMapInfo->eNameType - 1) << 1) + 1;
	if (*s_lpFzmINamePtrBuff[index] != '@')
		::lstrcat(szFullName, s_lpFzmINamePtrBuff[index]);
	else
	{
		index = ::atoi(s_lpFzmINamePtrBuff[index] + 1);
		::lstrcat(szFullName, s_lpFzmINamePtrBuff[(index << 1) + 1]);
	}

	smTEXTUREHANDLE *lpDDS_FzmActiveMap = LoadDibSurfaceOffscreen(szFullName);
	if (lpDDS_FzmActiveMap == NULL)
		return FALSE;

	DELET(s_lpDDS_FzmActiveMap);

	s_lpDDS_FzmActiveMap = lpDDS_FzmActiveMap;
	return TRUE;
}

void CreateBeforeFullZoomMap(void)
{
	s_iFzmNameEffectMatNum = cSinWarpGate.MatSelect;

	s_iFzmUserLargeMatNum = MatArrow;
	s_iFzmPartyLargeMatNum = CreateTextureMaterial("image\\GuideMap\\User_P.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	s_iFzmUserSmallMatNum = CreateTextureMaterial("image\\GuideMap\\User_PSR.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
}

void DrawFzmBackToSurface(int dest_x, int dest_y, smTEXTUREHANDLE *lpDDS, int x, int y, int width, int height)
{
	RECT destRect;
	destRect.left = int(dest_x * g_fWinSizeRatio_X);
	destRect.top = int(dest_y * g_fWinSizeRatio_Y);
	destRect.right = int((dest_x + width)  * g_fWinSizeRatio_X);
	destRect.bottom = int((dest_y + height) * g_fWinSizeRatio_Y);

	RECT srcRect;
	srcRect.left = x;
	srcRect.top = y;
	srcRect.right = width;
	srcRect.bottom = height;

	if (lpDDS)
		dsDrawTexImage(lpDDS, &destRect, &srcRect);
}
void DrawFzmBackToTexture2D(smTEXTUREHANDLE *hTexHandle, int X, int Y, int Angle, int HalfSize, int Blend)
{
	int ix[4], iy[4];
	ix[0] = -HalfSize; iy[0] = -HalfSize;
	ix[1] = -HalfSize; iy[1] = HalfSize;
	ix[2] = HalfSize; iy[2] = -HalfSize;
	ix[3] = HalfSize; iy[3] = HalfSize;

	int cnt;
	float fx[4], fy[4];

	if (Angle)
	{
		int sinY = GetSin[Angle & ANGCLIP];
		int cosY = GetCos[(Angle + ANGLE_180) & ANGCLIP];

		for (cnt = 0; cnt < 4; cnt++)
		{
			fx[cnt] = (float)((iy[cnt] * sinY + ix[cnt] * cosY) >> 8);
			fy[cnt] = (float)((iy[cnt] * cosY - ix[cnt] * sinY) >> 8);
			fx[cnt] /= 256;
			fy[cnt] /= 256;
			fx[cnt] += (float)X;
			fy[cnt] += (float)Y;
		}
	}
	else
	{
		for (cnt = 0; cnt < 4; cnt++)
		{
			fx[cnt] = float(ix[cnt] + X);
			fy[cnt] = float(iy[cnt] + Y);
		}
	}

	for (cnt = 0; cnt < 4; cnt++)
	{
		fx[cnt] *= g_fWinSizeRatio_X;
		fy[cnt] *= g_fWinSizeRatio_Y;
	}

	psDrawTexImage2(hTexHandle, fx, fy, 0, 0, 1, 1, Blend, 0);
}


//######################################################################################
//ÀÛ ¼º ÀÏ : 2004-04-08 ¿ÀÈÄ 3:31:43
//¸® ÅÏ °ª :
//¼³    ¸í :
//ÀÛ ¼º ÀÚ : ¿À ¿µ ¼®
//######################################################################################
int SetFullZoomMap(int IsSet)
{
	if (IsSet)
	{
		SFullZoomMapInfo *lpZoomMapInfo;
		int				  iFieldCode;

		if (lpCurPlayer->iLoadedMapIndex >= 0)
		{
			iFieldCode = STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID;

			s_iFzmActiveName = s_iFzmFieldCodeInfo[iFieldCode];
			if (iFieldCode == 40 || iFieldCode == 41 || iFieldCode == 43 || iFieldCode == 44)
				lpZoomMapInfo = &s_FzmInfo[4];
			else
				lpZoomMapInfo = &s_FzmInfo[s_iFzmActiveName];

			LoadZoomInMap(lpZoomMapInfo);
		}
		else
		{
			s_iFzmActiveName = 0;
			lpZoomMapInfo = &s_FzmInfo[s_iFzmActiveName];

			LoadZoomInMap(lpZoomMapInfo);
		}

		if (g_IsDxProjectZoomIn <= 0)
		{
			CreateFullZoomMap();
			g_IsDxProjectZoomIn = 1;
			SetFzmEffect(CHAR_POS_EFFECT, &s_CharPosEffectDataInfo, 3, s_iFzmActiveName);
		}

		return 1;
	}
	else
	{
		DestroyFullZoomMap();

		g_IsDxProjectZoomIn = 0;
		s_iFzmCharPosNameEffectTime = 0;

		ZeroMemory(s_NameEffectBuff, sizeof(s_NameEffectBuff));
		s_iFzmFocusName = -1;
		s_iFzmActiveName = -1;
		g_FzmMouseButton[0] = FALSE;
		g_FzmMouseButton[1] = FALSE;
		g_FzmMouseButton[2] = FALSE;
		return 1;
	}
}

void DrawFullZoomMapCharPos(void)
{
	SFullZoomMapInfo  *lpZoomMapInfo;
	SFullZoomMapImage *lpZoomMapImage;

	if (s_iFzmCharPosNum > 0 && s_iFzmActiveName >= 0)
	{
		lpZoomMapInfo = &s_FzmInfo[s_iFzmActiveName];
		lpZoomMapImage = &s_FzmImage[lpZoomMapInfo->eNameType - 1];

		for (int cnt = 0; cnt < s_iFzmCharPosNum; cnt++)
		{
			switch (s_FzmCharPosBuff[cnt].eCharType)
			{
			case USER_CHAR:
				for (int i = 0; i < dMAX_NAME_EFFECT; i++)
				{
					if (s_NameEffectBuff[i].Life && s_NameEffectBuff[i].eEffectType == CHAR_POS_EFFECT)
					{
						SFullZoomMapEffect *lpCharPosEffect = &s_NameEffectBuff[i];

						DrawFzmBackToTexture2D(smMaterial[s_iFzmUserLargeMatNum].smTexture[0],
							30 + lpZoomMapImage->iMapOffset_x + s_FzmCharPosBuff[cnt].iXpos,
							15 + lpZoomMapImage->iMapOffset_y + s_FzmCharPosBuff[cnt].iYpos,
							lpCurPlayer->Angle.y,
							lpCharPosEffect->HalfSize + int(lpCharPosEffect->fScaleNum),
							int(lpCharPosEffect->fBlendNum));
					}
				}
				break;

			case PARTY_CHAR:
				DrawFzmBackToTexture2D(smMaterial[s_iFzmPartyLargeMatNum].smTexture[0],
					30 + lpZoomMapImage->iMapOffset_x + s_FzmCharPosBuff[cnt].iXpos,
					15 + lpZoomMapImage->iMapOffset_y + s_FzmCharPosBuff[cnt].iYpos,
					0, 8, 255);
				break;
			}
		}
	}
}

void DrawFullZoomMap(void)
{
	SFullZoomMapInfo  *lpZoomMapInfo;
	SFullZoomMapImage *lpZoomMapImage;

	if (s_lpDDS_FzmActiveMap)
		DrawFzmBackToSurface(30, 15, s_lpDDS_FzmActiveMap, 0, 0, 320, 320);

	DrawFullZoomMapCharPos();

	DrawFzmBackToSurface(0, 0, s_lpDDS_FullMapImage, 0, 0, 800, 600);

	DrawFzmBackToSurface(s_ExitButtonPos.x, s_ExitButtonPos.y, s_lpDDS_Exit, 0, 0, 64, 34);

	if (s_iFzmFocusName >= 0 && s_iFzmFocusName != s_iFzmActiveName)
	{
		lpZoomMapInfo = &s_FzmInfo[s_iFzmFocusName];
		lpZoomMapImage = &s_FzmImage[lpZoomMapInfo->eNameType - 1];

		DrawFzmBackToSurface(lpZoomMapInfo->iNamePosX - 1, lpZoomMapInfo->iNamePosY, lpZoomMapImage->lpDDS_Name, 0, 0, lpZoomMapImage->iCheckWideh, lpZoomMapImage->iCheckHeight);
	}

	if (s_iFzmActiveName >= 0)
	{
		lpZoomMapInfo = &s_FzmInfo[s_iFzmActiveName];
		lpZoomMapImage = &s_FzmImage[lpZoomMapInfo->eNameType - 1];

		DrawFzmBackToSurface(lpZoomMapInfo->iNamePosX, lpZoomMapInfo->iNamePosY, lpZoomMapImage->lpDDS_Name, 0, 0, lpZoomMapImage->iCheckWideh, lpZoomMapImage->iCheckHeight);
	}

	DrawFzmEffect();
}


//######################################################################################
//ÀÛ ¼º ÀÏ : 2004-04-08 ¿ÀÈÄ 3:32:13
//¸® ÅÏ °ª :
//¼³    ¸í :
//ÀÛ ¼º ÀÚ : ¿À ¿µ ¼®
//######################################################################################
void MainFullZoomMap(void)
{
	int st_x, st_y, end_x, end_y, i;

	if (lpCurPlayer->iLoadedMapIndex >= 0)
	{
		if (lpCurPlayer->pX != s_CurPlayerPos.x || lpCurPlayer->pZ != s_CurPlayerPos.y)
		{
			if (s_iFzmActiveName != s_iFzmFieldCodeInfo[STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID])
				SetFullZoomMap(1);
		}

		s_CurPlayerPos.x = lpCurPlayer->pX;
		s_CurPlayerPos.y = lpCurPlayer->pZ;
	}

	MainFzmEffect();

	st_x = int(682 * g_fWinSizeRatio_X);
	st_y = int(547 * g_fWinSizeRatio_Y);
	end_x = int((682 + 64) * g_fWinSizeRatio_X);
	end_y = int((547 + 34) * g_fWinSizeRatio_Y);

	if (g_iFzmCursorPosX > st_x && g_iFzmCursorPosX < end_x && g_iFzmCursorPosY > st_y && g_iFzmCursorPosY < end_y)
	{
		if (s_lpDDS_Exit == s_lpDDS_ExitImage)
		{
			s_lpDDS_Exit = s_lpDDS_ExitFocusImage;

			s_iMouseLButtonState[0] = g_FzmMouseButton[0];
			s_iMouseLButtonState[1] = -1;
		}

		if (s_iMouseLButtonState[0] == 0)
		{
			if (s_iMouseLButtonState[1] == 1)
			{
				s_ExitButtonPos.x = 682 + 1;
				s_ExitButtonPos.y = 547 + 1;

				if (g_FzmMouseButton[0] == 0)
					SetFullZoomMap(0);
			}
			else
				s_iMouseLButtonState[1] = g_FzmMouseButton[0];
		}
		else
			s_iMouseLButtonState[0] = g_FzmMouseButton[0];
	}
	else
	{
		s_lpDDS_Exit = s_lpDDS_ExitImage;
		s_ExitButtonPos.x = 682;
		s_ExitButtonPos.y = 547;
	}

	SFullZoomMapInfo  *lpZoomMapInfo;
	SFullZoomMapImage *lpZoomMapImage;

	for (i = 0; i < EFzmNameMax; i++)
	{
		lpZoomMapInfo = &s_FzmInfo[i];
		lpZoomMapImage = &s_FzmImage[lpZoomMapInfo->eNameType - 1];

		st_x = int(lpZoomMapInfo->iNamePosX * g_fWinSizeRatio_X);
		st_y = int(lpZoomMapInfo->iNamePosY * g_fWinSizeRatio_Y);
		end_x = int((lpZoomMapInfo->iNamePosX + lpZoomMapImage->iCheckWideh)  * g_fWinSizeRatio_X);
		end_y = int((lpZoomMapInfo->iNamePosY + lpZoomMapImage->iCheckHeight) * g_fWinSizeRatio_Y);

		if (g_iFzmCursorPosX > st_x && g_iFzmCursorPosX < end_x && g_iFzmCursorPosY > st_y && g_iFzmCursorPosY < end_y)
		{
			if (s_iFzmFocusName == i)
			{
				if (s_iMouseLButtonState[0] == 0)
				{
					if (s_iMouseLButtonState[1] == 1)
					{
						if (g_FzmMouseButton[0] == 0)
						{
							s_iMouseLButtonState[1] = 0;

							LoadZoomInMap(lpZoomMapInfo);
							s_iFzmActiveName = i;

							SetFzmEffect(NAME_EFFECT, &s_NameEffectDataInfo, 2, s_iFzmActiveName);
						}
					}
					else
						s_iMouseLButtonState[1] = g_FzmMouseButton[0];
				}
				else
					s_iMouseLButtonState[0] = g_FzmMouseButton[0];
			}
			else
			{
				s_iFzmFocusName = i;

				s_iMouseLButtonState[0] = g_FzmMouseButton[0];
				s_iMouseLButtonState[1] = -1;
			}

			break;
		}
	}
	if (i >= EFzmNameMax)
		s_iFzmFocusName = -1;

	SetFzmCharPos();
}

int KeyFullZoomMap(WPARAM wParam)
{
	if (wParam >= 0x70 && wParam <= 0x77)
		return 1;

	if (wParam >= 0x23 && wParam <= 0x28)
		return 1;

	if (wParam == VK_CONTROL || wParam == 0x31 || wParam == 0x32 || wParam == 0x33)
		return 1;

	return 0;
}

