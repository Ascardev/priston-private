#define CLANUSER					100		//ÀÏ¹ÝÀ¯Àú
#define CLANCHIP					101		//¯…
#define CLANNO_REGESTER				102		//¹«µî·ÏÀÚ
#define CLAN_NOCONNECT				103		//ÄÁ³ØÆ®°¡ ¾ÈµÇ¼­ ¼³Á¤ºÒ°¡
#define CLAN_SUBCHIP				104		//ºÎÅ¬·£Ä¨





#define CLAN_NPC_START 0

#define CLANMESSAGEBUF_MAX 1024



#define CLAN_MAKE_is	1 //Å¬·£ µî·Ï ÀÇ»ç °áÁ¤ ¸Þ´º
#define CLAN_MONEY_is	2 //Å¬·£ ¸¸µé µ·ÁöºÒ °áÁ¤ ¸Þ´º
#define CLAN_NAME_is	3 //Å¬·£ ÀÌ¸§ ¸¸µé±â ¸Þ´º
#define CLAN_MARK_expl  4 //Å¬·£ ¸¶Å© ¼³¸í ¸Þ´º
#define CLAN_INSPECTION_expl	5 //Å¬·£ ½É»ç¸¦ ¾Ë·ÁÁÖ´Â ¼³¸í ¸Þ´º
#define CLAN_NAME_BEING         6
#define CLAN_MAKE_FINISH        7
#define CLAN_CHIP_ReadDATA		8 //Ä¨¿ë¸Þ´º¸¦ À§ÇØ µ¥ÀÌÅ¸¸¦ Ã£´Â´Ù.
#define CLAN_NONAME	            9
#define CLAN_GO_MAKE			10
#define CLAN_GO_NPCSTART          11
#define CLAN_NotMake			254 //Å¬·£À» ¸¸µéÁö ¸øÇÏ´Ï µ¹¾Æ°¡¶ó
#define CLAN_AllEnd				255 //Å¬·£ÇÔ¼ö¸¦ ³ª°¥¶§ ²À µé¸®´Â ¸Þ´º
#define CLAN_ERROR				1000//¿¡·¯¿ë ½ºÆ®¸µÀ» º¸¿©ÁØÈÄ µÇµ¹¾Æ°£´Ù.




#define CLAN_CHECK_CLANMARK		200
#define CLAN_READ_CLANMARK		201
#define CLAN_REAMMAKR_ERROR       202  
#define CLANMAKE_REAMMAKR_ERROR       203  

#define CLAN_USER_DATA           300 //Å¬·£ À¯Àú·Î ÀÌµ¿ ½ÃÄÑÁÜ





//===============Å¬·£Ä¨ °ü·Ã µðÆÄÀÎ
#define CLAN_CHIP				20 //Ä¨
#define CLAN_WAREHOUSE			21 //Ã¢°í
#define CLAN_WAREHOUSE_RIGHT		22 //Ã¢°í ±ÇÇÑ
#define CLAN_MARK				23 //¸¶Å©
#define CLAN_MARK1				24
#define CLAN_MARK2				25
#define CLAN_MARK3				26
#define CLAN_REMOVE				27 //Ãß¹æ
#define CLAN_RELEASE			28 //ÇØÃ¼
#define CLAN_HELP				29 //µµ¿ò¸»
#define CLAN_NOMAKE				30		//Å¬·£¿øÀÌ 6ÀÎ ÀÌÇÏÀÏ °æ¿ì ¸Þ´º Ã¹¸Ó¸®¿¡ ¾Ë·ÁÁØ´Ù
#define CLAN_HELP_CONTENT		31
#define CLAN_REMOVE_RESULT		32
#define CLAN_RECONF_RELEASE       33
#define CLAN_FINISH_RELEASE       34
#define CLAN_REMOVE_SHORTCLANWON   35
#define CLAN_RELEASE_LOADING       36
#define CLAN_REMOVE_SHORTCLANWON_LOADING 37
#define CLAN_REMOVE_LOADING        38
#define CLAN_REMOVE_SHORTCLANWON_RESULT   39 
//#define CLAN_RELEAE_BEFORE		35 //YGY:Å¬·£ ÇØÃ¼ÇÏ±â Àü¿¡ Å¬·£°ü·Ã Á¤º¸¸¦ ÀÐ¾î¿Â´Ù.

//===============Å¬·£À¯Àú °ü·Ã µðÆÄÀÎ
#define CLAN_USER				40 //Å¬·£ ±¸¼º¿ø
#define CLAN_JOIN				41 //Å¬·£ °¡ÀÔ
#define CLAN_SECESSION			42 //Å¬·£ Å»Åð
#define CLAN_USER_WAREHOUSE		43	//À¯Àú¿ë Ã¢°í
#define CLAN_USER_HELP			44
#define CLAN_USER_NOMAKE			45
#define CLAN_USER_HELP_CONTENT	46
#define CLAN_RECONF_SECESSION    47
#define CLAN_FINISH_SECESSION     48
#define CLAN_USER_NOMAKE_FLAG      49
#define CLAN_USER_FLAG            50
#define CLAN_USER_ReadDATA        51
#define CLAN_RECONF_SECESSION_LOADING     52

#define CLANUSER_RELEASEMESSAGE	53 //ÇØÃ¼µÈ Å¬·£¿ø
#define CLANUSER_GO_RELEASEMESSAGE 54
#define CLANUSER_RELEASE_FLAG		55

//Ãª¸®½ºÆ®¸ÞÀÎ ÇÃ·¯±×==========================================================
//#define CHATLIST_START           900 
#define CHATLIST_END			901
#define CHATLIST_ERROR			902
#define CHATLIST_READDATA		903
#define CLAN_DISPLAY_OPEN		904
#define CLAN_DISPLAY_END			905
#define CLAN_DISPLAY_INFO         906
#define CLAN_DISPLAY_CLOSE			907
#define CLAN_CLOSE_END_BEFORE			908
#define CLAN_CLOSE_ENDING             909
#define CHATLIST_READ_CLANMARK       910
#define CLAN_DISPLAY_BEFORE		911

//==============cldata¾÷µ¥ÀÌÆ®==================
#define UPDATE_ISCLANMEMBER           1003
#define UPDATE_CLANWON				1004
#define ISPFLAG_USER				1005
#define ISPFLAG_CHIP				1006
#define CLAN_isCheckClanJang_LOADING   1007
#define CLANCHIP_DOWN6_CLANWON_MESSAGE 1008
#define CLANSERVER_INSPECT		    1009
#define CLANSERVER_INSPECT_BEFORE      1010
#define CLANINFO_READMARK			1011
#define CLANINFO_DOWNLOAD			1012
#define CLANINFO_END				1013
#define CLANMAKE_DOWN_INFO			1014
#define CLANMAKE_READ_CLANMARK		1015
#define CLAN_isCheckClanJang_Result	1016	
#define CLANMAKE_NOMONEY				1017
#define CLANUSER_JOIN				1018
#define CLANUSER_REMOVE				1019 //Å¬·£¿øÀÌ Ãß¹æ´çÇßÀ»°æ¿ì
#define CLANUSER_AUTORELEASE			1020 //ÀÚµ¿ÇØÃ¼
#define MYCLAN_UPDATE				1021
#define MYCLAN_CLANMARK_UPDATE		1022
#define CLANCHIP_GO_RELEASEMESSAGE		1023
#define CLANCHIP_RELEASEMESSAGE		1024
#define CLANCHIP_RELEASE_FLAG			1025
#define CLANUSER_CHECKPFLAG			1026
#define CLAN_CLANWONOVER				1027 //Å¬·£¿ø¼ö Ã¼Å©
#define CLAN_ABILITYDOWN				1028
#define CLAN_NOLEVEL				1029
#define CLAN_NOTICE					1030
#define CLAN_DRAWNOTICE				1031
#define CLAN_DRAWNOTICE_END			1032
//ÀÌÀÓ°ü·Ã========================START
#define CLANCHIP_LEAVECLAN			1033
#define CLANCHIP_LEAVECLAN_NOMONEY		1034
#define CLANCHIP_LEAVECLAN_SUCESS		1035
#define CLANCHIP_LEAVECLAN_CONFIRM		1036
#define CLANCHIP_LEAVECLAN_RECONFIRM	1037
#define CLANCHIP_LEAVECLAN_NOLEVEL		1038
#define CLANCHIP_LEAVECLAN_DO			1039
#define CLANCHIP_NOLEAVECLAN			1040
#define CLANCHIP_LEAVECLAN_PFLAG		1041
#define CLANCHIP_LEAVECLAN_MESSAGE		1042
#define CLANUSER_LEAVECLAN_MESSAGE		1043
#define CLANCHIP_LEAVECLAN_MESSAGEEND	1044
#define CLANUSER_LEAVECLAN_MESSAGEEND	1045  //
#define CLANCHIP_LEAVECLANDOWNLEVEL	1046  //Å¬·£¿øÀÌ ·¹º§ÀÌ µÇÁö ¾Ê¾Æ¼­ Å¬·£¿øÀ» ¹Þ¾ÆµéÀÏ¼ö ¾øÀ½
//=================================END


//ºÎ Å¬·£Ä¨ ÀÓ¸í ¹× ÇØÀÓ=====================START
#define CLANCHIP_SUBCHIP_LIST			1047  //Å¬·£¿øµé ¸®½ºÆ® º¸¿©ÁÜ ºÎ Å¬·£Ä¨ÀÌ ÀÖÀ¸¸é µû·Î º¸¿©ÁÜ
#define CLANCHIP_RESUBCHIP_APPOINT		1048  //ºÎ Å¬·£Ä¨ ÀÓ¸í ÀçÈ®ÀÎ
#define CLANCHIP_RESUBCHIP_APPOINT_END	1049  //ºÎ Å¬·£Ä¨ÀÓ¸í ¸¶Áö¸· ¸Þ¼¼Áö
#define CLANCHIP_RELEASESUBCHIP		1050  //ºÎ Å¬·£Ä¨ÇØÀÓ ÀçÈ®ÀÎ
#define CLANCHIP_RELEASESUBCHIP_END	1051  //Å¬·£ºÎÄ¨ ÇØÀÓ ¸¶Áö¸· ¸Þ¼¼Áö
#define CLANCHIP_APPOINTSUBCHIP_DO		1052  //Å¬·£ºÎÄ¨ ÀÓ¸í ASPÈ£Ãâ
#define CLANCHIP_RELEASESUBCHIP_DO		1053  //Å¬·£ºÎÄ¨ ÇØÀÓ ASPÈ£Ãâ

#define CLANCHIP_SUBCHIP_APPOINTMSG	1054  //Å¬·£ºÎÄ§ÀÌ ÀÓ¸íµÇ´Ù°í ÇÑ¹ø º¸¿©ÁÜ
#define CLANCHIP_SUBCHIP_RELEASEMSG	1055  //Å¬·£ºÎÄ§ÀÌ ÇØÀÓµÇ´Ù°í ÇÑ¹ø º¸¿©ÁÜ
#define CLANUSER_SUBCHIP_APPOINTMSG	1056  //Å¬·£ºÎÄ§ÀÌ ÀÓ¸íµÇ´Ù°í ÇÑ¹ø º¸¿©ÁÜ
#define CLANUSER_SUBCHIP_RELEASEMSG	1057  //Å¬·£ºÎÄ§ÀÌ ÇØÀÓµÇ´Ù°í ÇÑ¹ø º¸¿©ÁÜ
#define CLANCHIP_SUBCHIP_APPOINT_FLAG	1058  //Å¬·£ºÎÄ§ÀÌ ÀÓ¸íµÇ¾î´Ù´Â ÇÃ·¡±×¼¼ÆÃ
#define CLANCHIP_SUBCHIP_RELEASE_FLAG	1059  //Å¬·£ºÎÄ§ÀÌ ÇØÀÓµÇ¾î´Ù´Â ÇÃ·¡±×¼¼ÆÃ

#define CLANCHIP_SUBCHIP_READMSG_FLAG	1060  //Å¬·£ÀåÀÌ ºÎÄ¨ÀÌ ÀÓ¸íµÇ¾î´Ù´Â ¸Þ¼¼Áö¸¦ ÀÐ¾úÀ»¶§
#define CLANUSER_SUBCHIP_READMSG_FLAG	1061  //Å¬·£À¯Àú°¡ ºÎÄ§°ü·Ã ¸Þ¼¼Áö¸¦ ÀÐ¾î´Ù´Â ÇÃ·¡±× ¼¼ÆÃ

#define CLANCHIP_SUBCHIP_LOAD			1062  //Å¬·£¿ö¸®½ºÆ® °®¾î¿À±â(¾ÆÁ÷ »ç¿ë¾ÈÇÔ)
#define CLANCHIP_SUBCHIP_LOAD_DATA		1063
#define CLANCHIP_NOSUBCHIP			1064


//================================END
//ºÎÄ¨ÀÌ
#define CLANSUBCHIP_INSERTCLANWON		2000 //ºÎÄ¨ÀÌ Å¬·£¿øÃß°¡

#define CLANWON_MAX					100








#define CLAN_JOIN_before			60
//#define CLAN_JOIN				31
#define CLAN_JOIN_After			62

#define CLAN_JOIN_chip			63
#define CLAN_JOIN_chip_NO		64
#define CLAN_JOIN_chip_YES		65

//È£µ¿ClanÃß°¡
#define CLAN_IS_CHECK_MEMBER		100
#define CLAN_IS_CHECK_MEMBER_END	101


//Ã³À½ ½ÃÀÛ½Ã Å¬·£¸â¹öÀÎÁö ¾Æ´ÑÁö¸¦ ¹Ì¸® ¾Ë¾Æ¾ßÇÔ.
#define CLAN_isClanWon			66

#define CLAN_MAKE_examination		67		//Å¬·£½É»çÇÏ±â
#define CLAN_isCheckClanJang      68       //°°Àº °èÁ¤¿¡ Å¬·£ÀåÀÌ ÀÖ´ÂÁö Ã¼Å©
#define CLAN_LOADING			69
//===============Å¬·£ Á¢¼Ó½Ã °ü·Ã ÇÃ·¡±× ¸Þ¼¼Áö
#define CLANCHIP_MAKE_FIRSTMESSAGE     70    //Ã³À½ Å¬·£À» ¸¸µé¾úÀ»¶§ Å¬·£ÀåÀÌ NPC¸¦ Å¬¸¯ÇßÀ»¶§ º¸¿©ÁÖ´Â ¸Þ¼¼Áö
//#define CLANUSER_MAKE_FIRSTMESSAGE     71    //Ã³À½ Å¬·£À» ¸¸µé¾úÀ»¶§ Å¬·£±¸¼º¿øÀÌ NPC¸¦ Å¬¸¯ÇßÀ»¶§ º¸¿©ÁÖ´Â ¸Þ¼¼Áö
#define CLANCHIP_DOWN6_CLANWON         71   //Å¬·£¿øÀÌ 6¸í ÀÌÇÏ·Î ¶³¾îÁü
#define CLANCHIP_BREAKCLAN            72

#define CLANUSER_MAKE_FIRSTMESSAGE    73
#define CLANUSER_DOWN6_CLANWON_MESSAGE  74
#define CLANUSER_DOWN6_CLANWON         75





#define BUTTONBOX_WIDTH   68
#define BUTTONBOX_HEIGHT  27
#define BUTTONTEXT_WIDTH  32
#define BUTTONTEXT_HEIGHT 16

#define BOX_MAX_WIDTH (((4 * BOXCENTER_WIDTH) + (2*BOXCORNER_WIDTH) + 5) )

#define ICON_START       55
#define ICON_ADD		 20
#define SCROLLBAR_LEFT    236
#define SCROOBAR_TOP	54
#define DISPLAY_MAX		8

//Å¬·£ ÀÌ¸§ ÁÂÇ¥
#define CLAN_NAME_POS_X     65
#define CLAN_NAME_POS_Y     8

//Å¬·£ ÇïÇÁ °ü·Ã

#define CLANHELPICON_WIDTH   109
#define CLANHELPICON_HEIGHT   30
#define CLANHELPICON_CAP		 40
#define CLANHELPICON_START_Y   105
#define CLANHELPICON_DISPLAY_MAX		4
#define CLANHELPCONTENT_MARK_X   40
#define CLANHELPCONTENT_MARK_Y   40
#define CLANHELPCONTENT_X   100
#define CLANHELPCONTENT_Y   50
#define HELPWIDTH 256
#define HLEPDISPLAY_MAX		8
#define HELPCONTENT_X        19
#define HELPCONTENT_Y        56
#define HELPCONTENT_CAP      20
#define CLANCHIPHELPINF "image\\clanImage\\help\\ClanHelp.inf"
#define CLANUSERHELPINF "image\\clanImage\\help\\ClanUserHelp.inf"


#define SAVEDATA_DIR	"savedata"
#define CLANDATA_DIR   "savedata\\clanDATA"



//========================================================

#define BOXCORNER_WIDTH		64
#define BOXCORNER_HEIGHT		32
#define BOXCENTER_WIDTH		32
#define BOXCENTER_HEIGHT		32

//Å¬·£ ¸¶Å© ÀÌ¸§ À§Ä¡
#define CLANNAME_X			54  
#define CLANNAME_Y			12

#define CLANNAME_WIDTH		152
#define CLANNAME_HEIGHT		28

#define CLANNAMETEXT_X       128
#define CLANNAMETEXT_Y		20

//Å¬·£ ¸¶Å© ¹Ú À§Ä¡
#define CLANMARKBOX_X		93 
#define CLANMARKBOX_Y		47

//Å¬·£ ¸¶Å© À§Ä¡
#define CLANMARK_X		111
#define CLANMARK_Y		60

//BUTTON¹Ú½º°¡ ÇÑ°³ ÀÏ¶§ ÁÂÇ¥
#define BUTTON1_BOX_X			104
#define BUTTON1_BOX_Y			222

#define BUTTON1_X				BUTTON1_BOX_X + 9
#define BUTTON1_Y				BUTTON1_BOX_Y + 4

//BUTTON¹Ú½º°¡ µÎ°³ ÀÏ¶§ ÁÂÇ¥
#define BUTTON2_BOX_X			69
#define BUTTON2_BOX_Y			221

#define BUTTON2_X				BUTTON2_BOX_X + 9
#define BUTTON2_Y				BUTTON2_BOX_Y + 4

#define BUTTON3_BOX_X			139
#define BUTTON3_BOX_Y			221

#define BUTTON3_X				BUTTON3_BOX_X + 9
#define BUTTON3_Y				BUTTON3_BOX_Y + 4

//Å¬·£Ä¨ ¸ÞÀÎ ¸Þ´º
#define CLANCHIPMENU_RELEASE_X	104
#define CLANCHIPMENU_RELEASE_y	62

#define CLANCHIPMENU_REMOVE_X		104
#define CLANCHIPMENU_REMOVE_Y		92

//ÀÌÀÓ
#define CLANCHIPMENU_LC_X		104
#define CLANCHIPMENU_LC_Y		122
//µµ¿ò¸»
#define CLANCHIPMENU_HELP_X		104
#define CLANCHIPMENU_HELP_Y		182
//ºÎÅ¬·£Ä¨
#define CLANCHIPMENU_SUBCHIP_X	104
#define CLANCHIPMENU_SUBCHIP_Y	152

//Å¬·£ ¸Þ´º Å¸ÀÌÆ²
#define CLANTITLE_X				68
#define CLANTITLE_Y				12

//µµ¿ò¸» ¸ñ·Ï
#define CLANHELPLIST_X			68
#define CLANHELPLIST_Y			76

//Ãß¹æ Å¬·£¿ø ¸®½ºÆ® À§Ä¡
#define CLANWONLIST_X			50
#define CLANWONLIST_Y			60

//Å¬·£À¯Àú Å»Åð
#define CLANUSER_SECESSION_X	64
#define CLANUSER_SECESSION_Y	127

#define CLANUSER_HELP_X			64
#define CLANUSER_HELP_Y			167

//Å¬·£ °á¼º °ü·Ã ÅØ½ºÆ® ÁÂÇ¥
#define CLANMAKETEXT_X			25
#define CLANMAKETEXT_Y			40

#define LOADTEXT_X				70
#define LOADTEXT_Y				50

//Å¬·£Àå ¸Þ´ºÅØ½ºÆ® °ü·Ã
#define CLAN_RELEASE_X			60
#define CLAN_RELEASE_Y			80

#define CLAN_RECONF_RELEASE_X			30
#define CLAN_RECONF_RELEASE_Y			70

#define CLANNOMAKE_X		    30
#define CLANNOMAKE_Y		    60

#define CLANRELEASE_FINISH_X		50
#define CLANRELEASE_FINISH_Y		60

#define CLANUSERTEXT_X           45
#define CLANUSERTEXT_Y			60

#define CLANINPUTNAME_X			78
#define CLANINPUTNAME_Y			70


//========================================================




#define XCAP					20 // ÅØ½ºÆ® Ãâ·Â½Ã ½ÃÀÛÇÏ´Â xÀ§Ä¡°ª º¸Á¤
#define YDOWN					-2  //ÅØ½ºÆ® Ãâ·Â½Ã ½ÃÀÛÇÏ´Â yÀ§Ä¡°ª º¸Á¤
#define REMOVE_ICON				20 //Ãß¹æ ¾ÆÀÌÄÜ À§Ä¡ ÀÌµ¿
#define WHR_ICON				30
#define HELP1					"image\\Sinimage\\chipbutton\\help1.txt"
#define HELPMSG_MAX				256
#define CLANMARK_TXT_X           34
#define CLANMARK_TXT_Y           10
//Å©·£ ÇïÇÁ¹öÅÏÀÇ ÅØ½ºÆ® À§Ä¡
#define CLANHELPTEXT_Y               25
//Å¬·£ÅØ½ºÆ® ÀÌ¹ÌÁö Ãâ·Â
#define CLANTEXT_IMAGE_X         68
#define CLANTEXT_IMAGE_Y          12
#define CLANTEXT_IMAGE_WIDTH         120
#define CLANTEXT_IMAGE_HEIGHT         30





#define CLANHELPICON_NUM		100




#define CHIP_BUTTON_X_MOVE		30
#define CHIP_BUTTON_Y_MOVE		20

#define MAKEMONEY 500000			//Å¬·£°á¼ºÀ» À§ÇØ 50¸¸¿øÇÊ¿ä
#define CLANCHIP_LEAVECLAN_MONEY	300000
//#define MAKEMONEY 3000			//Å¬·£°á¼ºÀ» À§ÇØ 4¸¸¿øÇÊ¿ä
#define ABILITY   10000 	        //Å¬·£°á¼ºÀ» À§ÇØ 10000 ´É·ÂÄ¡°¡ ÇÊ¿ä
#define CLAN_MAKELEVEL  40		//Å¬·£À» ¸¸µé¼ö ÀÖ´Â ·¹º§

//web db·Î ºÎÅÍ ´äº¯À» ¹Þ¾Æ ÀúÀåÇÏ´Â°÷.
typedef struct {
	int  ret_val;					//web db¿¡¼­ À¯ÀúÀÇ Å¬·£¿¡¼­ÀÇÀ§Ä¡(Å¬·£Àå,Å¬·£¿ø,°¡ÀÔ¾ÈÇÔ)°¡Á®¿È.
	char ret_Buf[2048];				//web db¸¦ ÅëÇØ µé¾î¿Â ½ºÆ®¸µÀ» ¼¼ÀÌºêÇØµÎ¾ú´Ù°¡ ÇÊ¿äÇÒ¶§ ²¨³»¾²±âÀ§ÇÑ¹öÆÛ


} ANSWERDATA;

typedef struct _tagMyClanInfoHeader
{
	char		ClanMark_Num[40];   //Å¬·£ ¸¶Å© ¹øÈ£
	int		nClanMark;
	char		ClanName[40];   //Å¬·£ ÀÌ¸§		
	char		ClanReport[90];
	char		Gserver[4];
	char		UniqueClaClanInfo_nNum[64];


}MYCLANINFOHEADER;

//=============================================¼ø¼ö À©µµ¿ë
typedef struct {
	HBITMAP hb;
	void *pixBuf;
	char fname[64];
} DIBSectionBUF;


typedef struct 
{
	int  myPosition;			//100:ÀÏ¹Ý Å¬·£¿ø 101:Å¬·£¯…  102:°¡ÀÔ¾ÈµÇ¾îÀÖÀ½. 103: Å¬·£¼­¹ö»óÀÇ ¿¡·¯

	int	 money;					//ÇöÀç À¯Àú°¡ °¡Áø µ·
	int  ability;

	char clanJoinID[64];		
	char clanJoinCharID[64];
	int  clanJoinJob, clanJoinLevel;

	char chipCharID[64];		//Å¬·£¿¡ °¡ÀÔÀ» ±ÇÀ¯ÇÑ Å¬·£¯…ÀÇ id¸¦ ÀúÀåÇØµÐ´Ù.

	char  szJoinClanName[64];		//Á¶ÀÎ Å¬·£ ÀÌ¸§
	char  szJoinClanChipName[64];   //Á¶ÀÎÇÏ´Â Å¬·£Àå ÀÌ¸§

	char name[20];				//Å¬·£ÀÇ ÀÌ¸§
	char explanation[128];		//Å¬·£ÀÇ ¼³¸í±Û(ÇöÀç Å¬·£¸¸µé¶§ ¼ÂÆÃ¾ÈÇÏ°í ÀÖÀ½.)

	//ygy
	char stats[2];
	char sec[30];
	char szRegiD[50];
	char  limitD[30];
	char  DelActive[10];
	char  gserver[30];
	char  szID[64];       //ÀÏ¹Ý °èÁ¤	//´ç À¯ÀúÀÇ id : °ÔÀÓ¸ÞÀÎ¿¡¼­ ¹Þ¾Æ¿È.
	char  ChaName[64];    //Ä³¸¯ÅÍ ÀÌ¸§ //´ç À¯ÀúÀÇ Ä³¸¯ÅÍid : °ÔÀÓ¸ÞÀÎ¿¡¼­ ¹Þ¾Æ¿È.
	char  ClanZang_ID[64];
	char  ClanZang_Name[64];	
	char  ClanMark[64];	//100188

	int intClanMark;
	int nLastDay;  //Å¬·£ÀÌ µî·ÏµÇ±â±îÁö ³²Àº ³¯
	BOOL bIsOneDay;
	int	nMinute;
	int	nHour;

	int nCurrentClanWon_Num;
	int nClanWon_Max;        //Å¬·£¿ø ÃÖ´ë¼ö

	char  clanWon[CLANWON_MAX][30];        //Å¬·£¼­¹ö¿¡¼­ º¸³»ÁØ Å¬·£¿øÀ» ÀúÀå(Å¬·£Àå Á¦¿Ü)
	int	 clanWonStrLen[41];      //°¢ Å¬·£¿ø ¹®ÀÚ¿­ ±æÀÌ
	char  szClanMarkName[50];     //Å¬·£¸¶Å© ºñÆ®¸ÊÀÌ¸§
	int   nTotalClanWonCount;     //ÇöÀç Å¬·£¿ø¼ö
	char  PFlag[5];             //Å¬·£ Ã¹ È­¸é ÇÃ·¡±×
	char  LeaveClanFlag[5];       //kflag
	int	 nKFlag;				//kflag
	int   nKFlag_Count;
	char  OldChipChaName[64];
	char  SubChip[64];			//ºÎ Å¬·£Ä¨
	char	 OldSubChip[64];
	char	 isSubChip[2];

	Unit *TargetChar;

	smTEXTUREHANDLE	*hClanMark;
	smTEXTUREHANDLE	*hClanMark16;

	char  StartMessageFlag[1];


	DWORD CNFlag;
} CLANDATA;

typedef struct _tagClanWonList
{
	char  clanWon[CLANWON_MAX][30];

}CLANWONLIST;


typedef struct _tagHelpContent
{
	char szHelpContent[HELPWIDTH];
	BOOL bFlag;
}HELPCONTENTS;


typedef struct _tagClanHelpIcon
{	
	char ImagePath[255];
	char ImagePath2[255];	
	char ImagePath3[255];	
	char TextFilePath[255];
}CLANHELPICON;
//end-ygy
typedef struct _tagMenuBMP
{
	HBITMAP membmp;
}MENUBMP;

class CLAN_MENU
{
public:
	CLAN_MENU();
	~CLAN_MENU();
	int menu_joinOpen(char *chipCharID);
	int menu_joinOpen_Chip(int joinOK, char *clanWonID, char *clanWonCharID, int clanWonJob, int clanWonLevel);
	int IsCheckClanMember(Unit *pChar);

	int	MatPartyBackGround;
	int	hBox1,hBox2,hBox3,hBox4,hBox5,hBox6,hBox7,hBox8,hBox9;
	int	hScl_Bar_tj;
	int	hScl_icon_tj;

	char		szHelpMsg1[HELPMSG_MAX];
	char		szErrorMsg[256];
	int  nReleaseClanWon;

	int nScl_Bar;
	int g_HelpIconNumber;
	char szHelpContent[1024];

	char     szRemoveClanWonResultMsg[1024];
	char     szReconfReleaseMsg[2048];


	typedef struct _tagButtonClick
	{
		char szClanWon[20];
		BOOL bIsClick;
	}BUTTONCLICK;
	BUTTONCLICK buttonclick[30];
	BUTTONCLICK removeclick[30];
	int	nClanWon[40];
	char szRemoveClanWon[500];
	CLANHELPICON ClanHelpIcon[CLANHELPICON_NUM];

	MENUBMP *membmp;
	int MatTitle[4];

	int xLeft, xRight;


	RECT scrIconPos;
	void InitMenuSet(int menuN);
	int chk_readStrBuf(char *cmd, char *readbuf, char *retBuf);

	void Init();
	void NoticeMessage_Init();
	void Init2();
	void NoticeMessage_Init2();

	void Load();
	void Close();

	int	 Main(int sw);
	int	 Draw();
	int	 DrawBox(int x,int y,int x_width,int y_height);
	void menuInit(int num);
	void Draw_C_menuN();
	void Draw_C_Text(char *str, int x, int y, int sw);

	void RenderMenu();
	int chkMenu(int x, int y, RECT *r) ;
	int chkeckMenuN();
	void menuSet(int sw);

	int		nChkMark;

	int chkMark(char *clanName);

	void SetUserData(char* id, char* chaname, char* gserver,int money, int ability);
	void SetJoinData(char *joinclanname, char *joinclanchip);
	void clanCheckMark_main();

	void clanJoin_main();
	void Loading();
	void ClanJoin();
	void joinClanMember();
	void CLANmenu_INIT();
	int  CLANmenu_clanPOSITION();
	int  CLANmenu_meetNPC();

	void CLANmenu_ChatList(int sw);
	void CLANmenu_DeleteCha();

	void GuideHelpDraw();
};

typedef struct _tagClanMsg
{
	POINT pos;
	char szMsg[1024];
}CLANMSG;

void Draw_Text(int x, int y,char *str);
void Text_Out(HDC hdc,int x, int y,char *str);

#ifdef TJCLAN_CPP

CLAN_MENU	Interface_clanmenu;




//auth.cpp¿¡¼­ ´äº¯À» ¹Þ¾Æ¿À´Â º¯¼ö ( class¿¡ ³ÖÀ¸¸é ´äÀÌ ÀÌ»óÇÏ°Ô ³ª¿È)
ANSWERDATA ANSdata;

CLANDATA cldata;		//web µðºñ¿¡¼­ ¹ÞÀº ½ºÆ®¸µÀ» ÆÄ½ÌÇØ¼­ ³Ö¾îµÐ°÷
CLANDATA chacldata[5];	//°èÁ¤¿¡ ¸¸µé¾îÁø Ä³¸¯ÅÍµéÀÌ °¡ÀÔÇÑ Å¬·£Á¤º¸ ÀúÀå




//=======================================Ãâ·Â ¸Þ¼¼Áö======================start

//Å¬·£ ¸¸µé±â °ü·Ã ¸Þ¼¼Áö
CLANMSG clanMake1;
CLANMSG clanMake2;
CLANMSG clanMake3;
CLANMSG clanMake4;
CLANMSG clanMake5;
CLANMSG clanMake6;
CLANMSG clanMsg21;
CLANMSG clanMsg254;
CLANMSG clanMsg15;
CLANMSG clanJoin;
CLANMSG clanSecession;
CLANMSG clanServerConnectErrorMsg;
CLANMSG clanszError_Msg;
CLANMSG clanDeleteChaError;
CLANMSG clanCancelMakeClan;
CLANMSG clanClanNameError;
CLANMSG clanSecession6DownMsg;
CLANMSG clanClanJoinMsg;
CLANMSG clanClanJoinCancelMsg;
CLANMSG clanClanJoinsucesssMsg;
CLANMSG clanszReMoveClanWonMsg;
CLANMSG clanReMoveHeaderMsg;
CLANMSG clanszReConfReleaseMsg;
CLANMSG clanNoRecordReleaseMsg;
CLANMSG clanFinishReleaseMsg;
CLANMSG clanSecessionMsg;
CLANMSG clanFinishSecessionMsg;
CLANMSG clanisCheckClanJangErrorMsg;
CLANMSG clanMoneyErrorMsg;
CLANMSG clanAbilityErrorMsg;
CLANMSG clanszRemoveShortClanWonMsg;
CLANMSG clanNoName;
CLANMSG clanLoading;
CLANMSG clanMsg6;
CLANMSG clanMsg7;
CLANMSG clanClanWon6Down;
CLANMSG clanClanUserNoMakeMsg;
CLANMSG clanMakeFinishClanWon;
CLANMSG clanClanServerInspect;
CLANMSG clanClanUserRelease;
CLANMSG clanClanUserReleaseMsg;
CLANMSG clanClanMakedowninfo;
CLANMSG clanClanUserRemove;
CLANMSG clanClanWonOver;
CLANMSG clanNoLevel;
CLANMSG clanMakeFinishClan;
CLANMSG clanRemoveShowrtClanWonResultMsg;
CLANMSG clanRemoveSecond;
CLANMSG clanRemoveSecondResult;
CLANMSG LeaveClanConfirm;
CLANMSG LeaveClanNoMoney;
CLANMSG LeaveClanSuccess;
CLANMSG LeaveClanNoLevel;
CLANMSG LeaveClanReConfirm;
CLANMSG NoLeaveClan;
CLANMSG LeaveClanMessage;
CLANMSG LeaveClanDownLevel;
CLANMSG SubChipAppoint;
CLANMSG SubChipAppointEnd;
CLANMSG SubChipRelease;
CLANMSG SubChipReleaseEnd;
CLANMSG NoSubChip;

//È£µ¿ClanÃß°¡
CLANMSG ClanIs4DayCheckMsg;


char szMsg1[CLANMESSAGEBUF_MAX];
char szMsg2[CLANMESSAGEBUF_MAX];
char szMsg21[CLANMESSAGEBUF_MAX];
char szMsg3[CLANMESSAGEBUF_MAX];
char szMsg4[CLANMESSAGEBUF_MAX];
char szMsg5[CLANMESSAGEBUF_MAX];
char szClanMakeFinishMsg[CLANMESSAGEBUF_MAX];
char szMsg254[CLANMESSAGEBUF_MAX];
char szMsg15[CLANMESSAGEBUF_MAX];
char szMark1[CLANMESSAGEBUF_MAX];
char szMark2[CLANMESSAGEBUF_MAX];
char szMark3[CLANMESSAGEBUF_MAX];
char szJoin[CLANMESSAGEBUF_MAX];
char szSecession[CLANMESSAGEBUF_MAX];
char szMsg6[CLANMESSAGEBUF_MAX];
char szServerConnectErrorMsg[CLANMESSAGEBUF_MAX];
char szReadClanMarkErrorMsg[CLANMESSAGEBUF_MAX];
char szCancelMakeClan[CLANMESSAGEBUF_MAX];
char szTranzationError[CLANMESSAGEBUF_MAX];
char szInsertClanWonError1[CLANMESSAGEBUF_MAX];
char szClanNameError[CLANMESSAGEBUF_MAX];
char sz100Error[CLANMESSAGEBUF_MAX];
char szDefaultError[CLANMESSAGEBUF_MAX];
char szReleseError[CLANMESSAGEBUF_MAX];
char szSecessionSuccess[CLANMESSAGEBUF_MAX];
char szSecession6DownMsg[CLANMESSAGEBUF_MAX];
char szSecessionChipMsg[CLANMESSAGEBUF_MAX];
char szSecession2ErrorMsg[CLANMESSAGEBUF_MAX];
char szClanJoinMsg[CLANMESSAGEBUF_MAX];
char szClanJoinError2Msg[CLANMESSAGEBUF_MAX];
char szClanJoinError3Msg[CLANMESSAGEBUF_MAX];
char szClanJoinError4Msg[CLANMESSAGEBUF_MAX];
char szClanJoinCancelMsg[CLANMESSAGEBUF_MAX];
char szClanJoinsucesssMsg[CLANMESSAGEBUF_MAX];
char szReMoveClanWonMsg[CLANMESSAGEBUF_MAX];
char szReMoveHeaderMsg[CLANMESSAGEBUF_MAX];
char szReConfReleaseMsg[CLANMESSAGEBUF_MAX];

char szNoRecordReleaseMsg[CLANMESSAGEBUF_MAX];
char szFinishReleaseMsg[CLANMESSAGEBUF_MAX];
char szSecessionMsg[CLANMESSAGEBUF_MAX];
char szFinishSecessionMsg[CLANMESSAGEBUF_MAX];
char szisCheckClanJangErrorMsg[CLANMESSAGEBUF_MAX];
char szMoneyErrorMsg[CLANMESSAGEBUF_MAX];
char szAbilityErrorMsg[CLANMESSAGEBUF_MAX];
char szRemoveShortClanWonMsg[CLANMESSAGEBUF_MAX];
char szRemoveShowrtClanWonResultMsg[CLANMESSAGEBUF_MAX];
char szNoName[CLANMESSAGEBUF_MAX];
char szLoading[CLANMESSAGEBUF_MAX];
/////////Ä³¸¯ÅÍ »èÁ¦ ¸Þ¼¼Áö
char szDeleteChaReleaseBefore[CLANMESSAGEBUF_MAX];
char szDeleteChaReleaseFinish[CLANMESSAGEBUF_MAX];
char szDeleteChaSecessionBefore[CLANMESSAGEBUF_MAX];
char szDeleteChaSecessionFinish[CLANMESSAGEBUF_MAX];

char szDeleteChaError[CLANMESSAGEBUF_MAX];
char szMakeFinishClan[CLANMESSAGEBUF_MAX];
char szClanWon6Down[CLANMESSAGEBUF_MAX];
char szClanUserNoMakeMsg[CLANMESSAGEBUF_MAX];
char szMakeFinishClanWon[CLANMESSAGEBUF_MAX];
char ClanServerInspect[CLANMESSAGEBUF_MAX];
char szClanUserRelease[CLANMESSAGEBUF_MAX];
char Replay[CLANMESSAGEBUF_MAX];
char szClanMakedowninfo[CLANMESSAGEBUF_MAX];
char szClanUserReleaseMsg[CLANMESSAGEBUF_MAX];
char szClanUserRemove[CLANMESSAGEBUF_MAX];
char szClanWonOver[CLANMESSAGEBUF_MAX];
char szError_Msg[CLANMESSAGEBUF_MAX];
char szMsg7[CLANMESSAGEBUF_MAX];
char szNoLevel[CLANMESSAGEBUF_MAX];
//=======================================Ãâ·Â ¸Þ¼¼Áö======================end



int C_menuN;			//Å¬·£ÀÇ ¸Þ´º´Â ¿©·¯°¡Áö°¡ ÀÖ±â¶§¹®¿¡ ¹øÈ£¸¦ ¼ÂÆÃÇØ¼­ ³ª´²ÁØ´Ù.
int C_menuN2;			//À¥¼­¹ö¿Í¿¬°á½Ã ¾²·¹µåÀÇ µ¥ÀÌÅ¸¸¦ ±â´Ù¸®±âÀ§ÇØ ¼ÂÆÃµÇ´Â Ã½Å©¿ë¹øÈ£ÀÓ.
int CLAN_ERROR_ret;		//¿¡·¯¸Þ´ºº¸¿©ÁØÈÄ Ã£¾Æ°¥°÷ Á¤ÇÑ´Ù.



int  nClanWon_Num;			//Å¬·£¿øÆÄ½ÌÈÄ Å¬·£¿øÀÇ ¸í¼ö(Å¬·£ÀåÁ¦¿Ü)
POINT BackStartPos;		//ÀÎÅÍÆäÀÌ½º ±âº»À§Ä¡
int g_HelpIconNumber;    //ÇöÀç ½ºÄÚ·Ñ À§Ä¡¸¦ ÀúÀå
HELPCONTENTS HelpContents[100];
int g_nClanIconNum;
int g_HelpDisPlay;
int g_HelpIConNumber;
RECT menuPos[30];		//¸Þ´º¼ÂÆÃ.
int		menuMouseOver[30];
int menuSu;
CLANHELPICON ClanHelpIcon[CLANHELPICON_NUM];
char szRemoveClanWonResult[5][64];
int keydownEnt =0;
int TJwheel =0;// ÈÙµ¥ÀÌÅ¸
int OpenFlag =0;
char banisBuf1[64];
char banisBuf2[512];
int  banisCnt;

DIBSectionBUF Dback;		//¹é¹öÆÛ¿ë.
int joinAnswer;
BOOL bIsLoading = FALSE; 
BOOL bOpenChatList = FALSE;
BOOL bIsReadData = FALSE;
int  ChatList_CmenuN = 0;
int	ChatList_CmenuN2 = 0;

int TJmb[3] = { 0,0,0 };
int TJmb2[3] = { 0,0,0 };

BOOL bCheckHostNameandPort = FALSE;
MYCLANINFOHEADER MyClanInfo;

CLANWONLIST ClanWonList;
BOOL		bcldataclanmark = FALSE;






int isDrawClanMenu=0;	//¸Þ´º°¡ ¶°ÀÖÀ¸¸é 1

char  szChatClanWon[CLANWON_MAX][30];        //Å¬·£¼­¹ö¿¡¼­ º¸³»ÁØ Å¬·£¿øÀ» ÀúÀå(Å¬·£Àå Á¦¿Ü)

#else	//=================================================================//




extern BOOL		bcldataclanmark;
extern CLANWONLIST ClanWonList;
extern MYCLANINFOHEADER MyClanInfo;

extern BOOL bCheckHostNameandPort;  //Å¬·£ ¼­¹ö ¾ÆÀÌÇÇÁÖ¼Ò°ú Æ÷Æ® »óÅÂ¸¦ Ã¼Å©
extern int TJmb[3] ;
extern int TJmb2[3];

extern int  ChatList_CmenuN;
extern int  ChatList_CmenuN2;
extern BOOL bIsReadData;
extern BOOL bOpenChatList;
extern BOOL bIsLoading; 
extern int joinAnswer;
extern DIBSectionBUF Dback;		//¹é¹öÆÛ¿ë.


//extern HBITMAP membmp;




extern int TJwheel; //ktj : ÈÙµ¥ÀÌÅ¸
extern int menuSu;
extern HWND			g_hwnd;
extern POINT		pCursorPos;
extern HINSTANCE	g_hInst;

extern CLAN_MENU	Interface_clanmenu;
extern ANSWERDATA	ANSdata;
extern int OpenFlag;



extern    int C_menuN;			//Å¬·£ÀÇ ¸Þ´º´Â ¿©·¯°¡Áö°¡ ÀÖ±â¶§¹®¿¡ ¹øÈ£¸¦ ¼ÂÆÃÇØ¼­ ³ª´²ÁØ´Ù.
extern 	int C_menuN2;			//À¥¼­¹ö¿Í¿¬°á½Ã ¾²·¹µåÀÇ µ¥ÀÌÅ¸¸¦ ±â´Ù¸®±âÀ§ÇØ ¼ÂÆÃµÇ´Â Ã½Å©¿ë¹øÈ£ÀÓ.
extern 	int CLAN_ERROR_ret;		//¿¡·¯¸Þ´ºº¸¿©ÁØÈÄ Ã£¾Æ°¥°÷ Á¤ÇÑ´Ù.
extern int  banisF[100];
extern char banisBuf1[64];
extern char banisBuf2[512];
extern int  banisCnt;
extern CLANDATA cldata;		//web µðºñ¿¡¼­ ¹ÞÀº ½ºÆ®¸µÀ» ÆÄ½ÌÇØ¼­ ³Ö¾îµÐ°÷
extern CLANDATA chacldata[5];	//°èÁ¤¿¡ ¸¸µé¾îÁø Ä³¸¯ÅÍµéÀÌ °¡ÀÔÇÑ Å¬·£Á¤º¸ ÀúÀå


extern int  nClanWon_Num;			//Å¬·£¿øÆÄ½ÌÈÄ Å¬·£¿øÀÇ ¸í¼ö(Å¬·£ÀåÁ¦¿Ü)
extern POINT BackStartPos;		//ÀÎÅÍÆäÀÌ½º ±âº»À§Ä¡
extern int g_HelpIconNumber;    //ÇöÀç ½ºÄÚ·Ñ À§Ä¡¸¦ ÀúÀå
extern HELPCONTENTS HelpContents[100];
extern int g_nClanIconNum;
extern int g_HelpDisPlay;
extern int g_HelpIConNumber;
extern RECT menuPos[30];		//¸Þ´º¼ÂÆÃ.
extern int		menuMouseOver[30];
extern int MouseButton[3] ;	//¸¶¿ì½º¹öÆ°´­¸²Ã½Å© : winmain.cpp¿¡ Á¤ÀÇÇÔ
extern CLANHELPICON ClanHelpIcon[CLANHELPICON_NUM];
extern char szRemoveClanWonResult[5][64];
#define MOUSE0() MouseButton[0]
extern int keydownEnt;



extern CLANMSG clanMake1;
extern CLANMSG clanMake2;
extern CLANMSG clanMake3;
extern CLANMSG clanMake4;
extern CLANMSG clanMake5;
extern CLANMSG clanMake6;


extern CLANMSG clanMsg21;
extern CLANMSG clanMsg254;
extern CLANMSG clanMsg15;
extern CLANMSG clanJoin;
extern CLANMSG clanSecession;
extern CLANMSG clanServerConnectErrorMsg;
extern CLANMSG clanszError_Msg;
extern CLANMSG clanDeleteChaError;
extern CLANMSG clanCancelMakeClan;
extern CLANMSG clanClanNameError;
extern CLANMSG clanSecession6DownMsg;
extern CLANMSG clanClanJoinMsg;
extern CLANMSG clanClanJoinCancelMsg;
extern CLANMSG clanClanJoinsucesssMsg;
extern CLANMSG clanszReMoveClanWonMsg;
extern CLANMSG clanReMoveHeaderMsg;
extern CLANMSG clanszReConfReleaseMsg;
extern CLANMSG clanNoRecordReleaseMsg;
extern CLANMSG clanFinishReleaseMsg;
extern CLANMSG clanSecessionMsg;
extern CLANMSG clanFinishSecessionMsg;
extern CLANMSG clanisCheckClanJangErrorMsg;
extern CLANMSG clanMoneyErrorMsg;
extern CLANMSG clanAbilityErrorMsg;
extern CLANMSG clanszRemoveShortClanWonMsg;
extern CLANMSG clanNoName;
extern CLANMSG clanLoading;
extern CLANMSG clanMsg6;
extern CLANMSG clanMsg7;
extern CLANMSG clanClanWon6Down;
extern CLANMSG clanClanUserNoMakeMsg;
extern CLANMSG clanMakeFinishClanWon;
extern CLANMSG clanClanServerInspect;
extern CLANMSG clanClanUserRelease;
extern CLANMSG clanClanUserReleaseMsg;
extern CLANMSG clanClanMakedowninfo;
extern CLANMSG clanClanUserRemove;
extern CLANMSG clanClanWonOver;
extern CLANMSG clanNoLevel;
extern CLANMSG clanMakeFinishClan;
extern CLANMSG clanRemoveShowrtClanWonResultMsg;
extern CLANMSG clanRemoveSecond;
extern CLANMSG clanRemoveSecondResult;
extern CLANMSG LeaveClanConfirm;
extern CLANMSG LeaveClanNoMoney;
extern CLANMSG LeaveClanSuccess;
extern CLANMSG LeaveClanNoLevel;
extern CLANMSG LeaveClanReConfirm;
extern CLANMSG NoLeaveClan;
extern CLANMSG LeaveClanMessage;
extern CLANMSG LeaveClanDownLevel;
extern CLANMSG SubChipAppoint;
extern CLANMSG SubChipAppointEnd;
extern CLANMSG SubChipRelease;
extern CLANMSG SubChipReleaseEnd;
extern CLANMSG NoSubChip;

////È£µ¿ClanÃß°¡
extern CLANMSG ClanIs4DayCheckMsg;


extern char szMsg1[CLANMESSAGEBUF_MAX];
extern char szMsg2[CLANMESSAGEBUF_MAX];
extern char szMsg21[CLANMESSAGEBUF_MAX];
extern char szMsg3[CLANMESSAGEBUF_MAX];
extern char szMsg4[CLANMESSAGEBUF_MAX];
extern char szMsg5[CLANMESSAGEBUF_MAX]; 
extern char szMsg6[CLANMESSAGEBUF_MAX];
extern char sz100Error[CLANMESSAGEBUF_MAX];
extern char szAbilityErrorMsg[CLANMESSAGEBUF_MAX];
extern char szCancelMakeClan[CLANMESSAGEBUF_MAX];
extern char szMsg254[CLANMESSAGEBUF_MAX];
extern char szClanMakeFinishMsg[CLANMESSAGEBUF_MAX];
extern char szMsg15[CLANMESSAGEBUF_MAX]; 
extern char szMark1[CLANMESSAGEBUF_MAX]; 
extern char szMark2[CLANMESSAGEBUF_MAX]; 
extern char szMark3[CLANMESSAGEBUF_MAX]; 
extern char szJoin[CLANMESSAGEBUF_MAX];
extern char szSecession[CLANMESSAGEBUF_MAX]; 
extern char szServerConnectErrorMsg[CLANMESSAGEBUF_MAX]; 
extern char szReadClanMarkErrorMsg[CLANMESSAGEBUF_MAX];
extern char szTranzationError[CLANMESSAGEBUF_MAX];
extern char szInsertClanWonError1[CLANMESSAGEBUF_MAX];
extern char szClanNameError[CLANMESSAGEBUF_MAX];
extern char szDefaultError[CLANMESSAGEBUF_MAX];
extern char szReleseError[CLANMESSAGEBUF_MAX];
extern char szSecessionSuccess[CLANMESSAGEBUF_MAX];
extern char szSecession6DownMsg[CLANMESSAGEBUF_MAX];
extern char szSecessionChipMsg[CLANMESSAGEBUF_MAX];
extern char szSecession2ErrorMsg[CLANMESSAGEBUF_MAX];
extern char szClanJoinMsg[CLANMESSAGEBUF_MAX];
extern char szClanJoinError2Msg[CLANMESSAGEBUF_MAX]; 
extern char szClanJoinError3Msg[CLANMESSAGEBUF_MAX];
extern char szClanJoinError4Msg[CLANMESSAGEBUF_MAX];
extern char szClanJoinCancelMsg[CLANMESSAGEBUF_MAX];
extern char szClanJoinsucesssMsg[CLANMESSAGEBUF_MAX];
extern char szReMoveClanWonMsg[CLANMESSAGEBUF_MAX];
extern char szReMoveHeaderMsg[CLANMESSAGEBUF_MAX];
extern char szReConfReleaseMsg[CLANMESSAGEBUF_MAX];
extern char szNoRecordReleaseMsg[CLANMESSAGEBUF_MAX];
extern char szFinishReleaseMsg[CLANMESSAGEBUF_MAX];
extern char szSecessionMsg[CLANMESSAGEBUF_MAX];
extern char szFinishSecessionMsg[CLANMESSAGEBUF_MAX];
extern char szisCheckClanJangErrorMsg[CLANMESSAGEBUF_MAX];
extern char szMoneyErrorMsg[CLANMESSAGEBUF_MAX];
extern char szRemoveShortClanWonMsg[CLANMESSAGEBUF_MAX];
extern char szRemoveShowrtClanWonResultMsg[CLANMESSAGEBUF_MAX];
extern char szClanUserNoMakeMsg[CLANMESSAGEBUF_MAX];
extern char szNoName[CLANMESSAGEBUF_MAX];
extern char szLoading[CLANMESSAGEBUF_MAX];

extern char szDeleteChaReleaseBefore[CLANMESSAGEBUF_MAX];
extern char szDeleteChaReleaseFinish[CLANMESSAGEBUF_MAX];
extern char szDeleteChaSecessionBefore[CLANMESSAGEBUF_MAX];
extern char szDeleteChaSecessionFinish[CLANMESSAGEBUF_MAX];

extern char szDeleteChaError[CLANMESSAGEBUF_MAX];
extern char szMakeFinishClan[CLANMESSAGEBUF_MAX];
extern char szClanWon6Down[CLANMESSAGEBUF_MAX];
extern char szMakeFinishClanWon[CLANMESSAGEBUF_MAX];
extern char ClanServerInspect[CLANMESSAGEBUF_MAX];
extern char szClanUserRelease[CLANMESSAGEBUF_MAX]; 
extern char Replay[CLANMESSAGEBUF_MAX];
extern char szClanMakedowninfo[CLANMESSAGEBUF_MAX]; 
extern char szClanUserReleaseMsg[CLANMESSAGEBUF_MAX];
extern char szClanUserRemove[CLANMESSAGEBUF_MAX];
extern char szClanWonOver[CLANMESSAGEBUF_MAX];
extern char szError_Msg[CLANMESSAGEBUF_MAX];

extern char szMsg7[CLANMESSAGEBUF_MAX];
extern char szNoLevel[CLANMESSAGEBUF_MAX];

extern int ClanCharMove;	//¸Þ´ºÆÇ¾ÈÀÇ ¸¶¿ì½ºÀÇ ¿òÁ÷ÀÓ¿¡ Ä³¸¯ÅÍ°¡ ¿µÇâ¾øµµ·Ï ÇÑ´Ù.
extern int ClanCLCharMove;//




extern int isDrawClanMenu;	//¸Þ´º°¡ ¶°ÀÖÀ¸¸é 1



extern int ktj_imsiDRAWinfo ;



extern char  szChatClanWon[CLANWON_MAX][30];        //Å¬·£¼­¹ö¿¡¼­ º¸³»ÁØ Å¬·£¿øÀ» ÀúÀå(Å¬·£Àå Á¦¿Ü)


#endif


void ClanJoin(char *oneClanName, char *oneChipCharid);
void menu_joinOpen_Chip(int isOK, char *clanWonID, char *clanWonCharID);
void menu_joinOpen_Chip(int isOK, char *clanWonID, char *clanWonCharID, int clanWonJob, int clanWonLevel);

//È£µ¿ClanÃß°¡
void g_IsCheckClanMember(Unit *pChar);

//cldata ¾øµ¥ÀÌÆ®¿ë
void Updatecldata();


int ReadClanInfo(DWORD dwClanNum);
int ReadClanInfo_32X32(DWORD dwClanNum);


void web_DB_ip_port_init(char *ip0, int port0, char *ip1, int port1);
void web_DB_ip_port_init(char *ip0, int port0, char *ip1, int port1,int ticket);


void CLANmenu_DeleteCha_SetCharacter(char *id, char *gserver, char *chaname);


extern int usehFocus;


int TJBscrollWheel(int wheel);

int chatlistSPEAKERflag();
void chatlistSPEAKERflagChg(int flag);//0,1À» ³ÖÀ»¼öÀÖÀ½.


int GetNoticeUrl(char *url);



void CheckMsgPos(CLANMSG* clanmsg,int width, int height);
void InitHelp();
void GoNotice();
int GetNoticeUrl(char *url);

extern int GoNotice_chking;

