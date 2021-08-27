#define	ITEM_FORM_ADD1			2
#define	ITEM_FORM_ADD2			9
#define	ITEM_FORM_MULT			41
#define	ITEM_FORM_START_MASK	0xF555
#define	ITEM_FORM_CODE_MASK		0xF57
#define	ITEM_FORM_CODE_SHIFT	13

#ifdef	_NEW_ITEM_FORMCODE2

static DWORD rsReformStateCode2( char *lpState , int size )
{
	int cnt;

	for(cnt=0;cnt<size;cnt++)
	{
		iFormCode += (((DWORD)lpState[cnt])+ITEM_FORM_ADD1)*((iFromCnt&ITEM_FORM_CODE_MASK)+ITEM_FORM_ADD2);
		iFromCnt+=(cnt+lpState[cnt]+1)*ITEM_FORM_MULT;
	}

	return iFormCode;
}

static DWORD rsGetRefromItemCode2(Item *lpItemInfo,int Key)
{
	iFormCode = (Key*lpItemInfo->CODE)&ITEM_FORM_START_MASK;
	iFromCnt = Key;

	rsReformStateCode2((char *)&lpItemInfo->CODE			, sizeof(DWORD));
	rsReformStateCode2((char *)lpItemInfo->ItemName			, 32);

	rsReformStateCode2((char *)&lpItemInfo->fMagic_Mastery	, sizeof(float));
	rsReformStateCode2((char *)&lpItemInfo->fMana_Regen		, sizeof(float));
	rsReformStateCode2((char *)&lpItemInfo->fLife_Regen		, sizeof(float));
	rsReformStateCode2((char *)&lpItemInfo->fStamina_Regen	, sizeof(float));
	rsReformStateCode2((char *)&lpItemInfo->fIncrease_Life	, sizeof(float));
	rsReformStateCode2((char *)&lpItemInfo->fIncrease_Mana	, sizeof(float));
	rsReformStateCode2((char *)&lpItemInfo->fIncrease_Stamina, sizeof(float));

	rsReformStateCode2((char *)&lpItemInfo->Level			, sizeof(int));
	rsReformStateCode2((char *)&lpItemInfo->Strength		, sizeof(int));
	rsReformStateCode2((char *)&lpItemInfo->Spirit			, sizeof(int));
	rsReformStateCode2((char *)&lpItemInfo->Talent			, sizeof(int));
	rsReformStateCode2((char *)&lpItemInfo->Dexterity		, sizeof(int));
	rsReformStateCode2((char *)&lpItemInfo->Health			, sizeof(int));

	rsReformStateCode2((char *)lpItemInfo->Mana				, sizeof(short)*2);
	rsReformStateCode2((char *)lpItemInfo->Life				, sizeof(short)*2);
	rsReformStateCode2((char *)lpItemInfo->Stamina			, sizeof(short)*2);

	rsReformStateCode2((char *)&lpItemInfo->Money			, sizeof(int));
	rsReformStateCode2((char *)&lpItemInfo->JobCodeMask		, sizeof(DWORD));
	rsReformStateCode2((char *)&lpItemInfo->JobItem			, sizeof(SpecItemData));

	rsReformStateCode2((char *)&lpItemInfo->UniqueItem		, sizeof(DWORD));
	rsReformStateCode2((char *)lpItemInfo->EffectBlink		, sizeof(short)*2);
	rsReformStateCode2((char *)lpItemInfo->EffectColor		, sizeof(short)*4);
	rsReformStateCode2((char *)lpItemInfo->ScaleBlink		, sizeof(short)*2);
	rsReformStateCode2((char *)&lpItemInfo->DispEffect		, sizeof(DWORD));
	rsReformStateCode2((char *)&lpItemInfo->ItemElement		, sizeof(WORD));

	rsReformStateCode2((char *)&lpItemInfo->Weight			, sizeof(int));
	rsReformStateCode2((char *)&lpItemInfo->Price			, sizeof(int));

	rsReformStateCode2((char *)lpItemInfo->Resistance		, sizeof(short)*8);
	rsReformStateCode2((char *)lpItemInfo->Damage			, sizeof(short)*2);

	rsReformStateCode2((char *)&lpItemInfo->fAbsorb			, sizeof(float));
	rsReformStateCode2((char *)&lpItemInfo->Defence			, sizeof(int));
	rsReformStateCode2((char *)&lpItemInfo->fBlock_Rating	, sizeof(float));

	rsReformStateCode2((char *)&lpItemInfo->Shooting_Range	, sizeof(int));
	rsReformStateCode2((char *)&lpItemInfo->iAttackSpeed	, sizeof(int));

	rsReformStateCode2((char *)&lpItemInfo->Attack_Rating	, sizeof(int));
	rsReformStateCode2((char *)&lpItemInfo->Critical_Hit	, sizeof(int));

	rsReformStateCode2((char *)&lpItemInfo->fSpeed			, sizeof(float));
	rsReformStateCode2((char *)&lpItemInfo->Potion_Space	, sizeof(int));

	return iFormCode;
}

#endif


DWORD rsGetItem_ServerForm(Item *lpItemInfo)
{
	DWORD dwCode;

#ifdef	_NEW_ITEM_FORMCODE2

	dwCode = rsGetRefromItemCode2( lpItemInfo , lpItemInfo->iChk2);
	dwCode = dwCode ^ ((lpItemInfo->ItemAgingProtect[0]*7)^(lpItemInfo->ItemAgingProtect[1]*9));
	dwCode+= (lpItemInfo->dwCreateTime&0xFFFF)<<2;
	dwCode = dwCode ^ (lpItemInfo->iChk1 ^((lpItemInfo->iChk2 +dwCode)<<ITEM_FORM_CODE_SHIFT));

#else

	//서버용 재 인증 아이템
	dwCode = rsGetRefromItemCode( lpItemInfo , lpItemInfo->iChk2);

#ifdef	_NEW_ITEM_FORMCODE
	dwCode = dwCode ^ ((lpItemInfo->ItemAgingProtect[0]*7)^(lpItemInfo->ItemAgingProtect[1]*9));	//추가 (믹스/에이징) 프로텍트
	dwCode+= lpItemInfo->dwCreateTime>>8;
#endif

	dwCode = dwCode ^ lpItemInfo->iChk1;
#endif

	return dwCode;
}

