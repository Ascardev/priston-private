/*----------------------------------------------------------------------------*
*	ÆÄÀÏ¸í :  sinParticle.h	
*	ÇÏ´ÂÀÏ :  ÀÌÆåÆ® °ü·Ã ÀÛ¾÷ 
*	ÀÛ¼ºÀÏ :  ÃÖÁ¾¾÷µ¥ÀÌÆ® 2002³â 6¿ù
*	Àû¼ºÀÚ :  ¹Ú»ó¿­ 
*-----------------------------------------------------------------------------*/

#define SIN_MAX_INTER_EFFECT		300

#define SIN_INTER_EFFECT_AGING				1		//¿¡ÀÌÂ¡°ú ¹Í½º½ÃÀÇ ÀÌÆåÆ® 
#define SIN_INTER_EFFECT_AGING2				2		//¿¡ÀÌÂ¡°ú ¹Í½º½ÃÀÇ ÀÌÆåÆ® 
#define SIN_INTER_EFFECT_AGING_SUCCESS		3		//¼º°øÀÌÆåÆ® 
/*----------------------------------------------------------------------------*
*						   ÀÎÅÍÆäÀÌ½º ÀÌÆåÆ® ±¸Á¶Ã¼ 
*-----------------------------------------------------------------------------*/	
struct sINTER_EFFECT{
	smFACE2D Face;
	int Time;
	int Max_Time;
	POINT Speed;
	POINT Speed2;		//¿Õ ³¯Ä¡±â ¼ø °³ÆÇ Â¥ÀÜ!
	int Direction;
	int AniCount;
	int AniKeyFlag;		//ÇÏÇÏÇÏ ¹ü»óÄ¡¾ÊÀº ÀÌ¸§ÀÌ·Î´Ù 
	int AniKeyFlag2;	//¿ÀÈ£! ÀÌ°Å¶ÇÇÑ ¹ü»óÄ¡ ¾Ê±¸³ª ¾ó¾¾±¸ ÁöÈ­ÀÚ
	int FadeType;
	int Kind;			//ÀÌÆåÆ® Á¾·ù
	int Gravity;		//Áß·Â 

	///// ¿òÁ÷ÀÓ ¹æÇâ 

};
/*----------------------------------------------------------------------------*
*						   ³¯Ä¡±â ±¸Á¶Ã¼ 
*-----------------------------------------------------------------------------*/	
struct sINTER_EFFECT3{
	smTEXTUREHANDLE *lpSuccessEffectAging;
	int Flag;
	int x;
	int y;

	int w;
	int h;

	int MoveX;
	int MoveY;

	int MoveX2;
	int MoveY2;

	int Speed;


};


/*----------------------------------------------------------------------------*
*						          ÇÔ¼ö 
*-----------------------------------------------------------------------------*/	
int sinSetParticle(int Kind ,int Color ,  int x , int y, int z);


/*----------------------------------------------------------------------------*
*						      ÀÎÅÍ ÆäÀÌ½º ÆÄÆ¼Å¬    
*-----------------------------------------------------------------------------*/	
 //ÀÌ¹ÌÁö¸¦ ·ÎµåÇÑ´Ù 
int InitInterEffect();

//¿¡ÀÌÂ¡ ÀÌÆåÆ®¸¦ ¼ÂÆÃÇÑ´Ù
int SetInterEffectAging();

//¿¡ÀÌÂ¡ ÀÌÆåÆ® Åõ!!
int SetInterEffectAging2();

//ÀÎÅÍÆäÀÌ½º ÀÌÆåÆ®¸¦ ¿òÁ÷ÀÎ´Ù 
int sinActiveInterEffect();

//ÀÎÅÍÆäÀÌ½º ÀÌÆåÆ®¸¦ ±×¸°´Ù 
int sinDrawInterEffect();

//ÀÎÅÍÆäÀÌ½º ÀÌÆåÆ® ÇÁ·Î¼¼½º ¼ø ³¯Ä¡±â À½ÇÏÇÏÇÏ 
int InterEffectAging2Process();

//¹Í½º, ¿¡ÀÌÂ¡ ¼º°ø ÀÌÆåÆ® 
int sinSuccessCraftEffect();

//¹Í½º, ¿¡ÀÌÂ¡ ¼º°ø ÀÌÆåÆ® 2
int sinSuccessCraftEffect2();

//¼º°øÀÌÆåÆ® 2¸¦ ¿òÁ÷ÀÎ´Ù 
int MoveSuccessCraftEffect2();

//¼º°ø ÀÌÆåÆ® 2¸¦ ±×¸°´Ù 
int DrawSuccessCraftEffect2();

//ÆÛÁñ ÀÌÆåÆ®
int SetPuzzleEffect(int x , int y);

// pluto Á¦·Ã ÀÌÆåÆ®¸¦ ¼ÂÆÃÇÑ´Ù
int SetInterEffectSmelting();

// pluto Á¦ÀÛ ÀÌÆåÆ®¸¦ ¼ÂÆÃÇÑ´Ù
int SetInterEffectManufacture();

int SetInterEffectMixtureReset();

// ÉèÖÃÊôĞÔÏµÍ³Ğ§¹û
int SetInterEffectElement();

/*----------------------------------------------------------------------------*
*						          Extern 
*-----------------------------------------------------------------------------*/	
extern int   StartInterEffectAging2; //ÀÌÆåÆ®ÀÇ ½ÃÀÛÀ» ¾Ë¸°´Ù 
extern int   sinCraftItemStartFlag;
extern int   sinCraftItemStartFlag2;


extern int  sinAgingSuccessFlag2;    //¿¡ÀÌÂ¡°ú ¹Í½ºÃÄÀÇ ¼º°ø ÇÃ·º 
extern DWORD InitCancelMixTime;