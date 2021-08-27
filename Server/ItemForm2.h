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

	for(cnt=0;cnt<size;cnt++) {
		iFormCode += (((DWORD)lpState[cnt])+ITEM_FORM_ADD1)*((iFromCnt&ITEM_FORM_CODE_MASK)+ITEM_FORM_ADD2);
		iFromCnt+=(cnt+lpState[cnt]+1)*ITEM_FORM_MULT;
	}

	return iFormCode;
}

static DWORD rsGetRefromItemCode2(Item *lpItemInfo , int Key )
{
	iFormCode = (Key*lpItemInfo->sItemID.ToInt())&ITEM_FORM_START_MASK;
	iFromCnt = Key;

	rsReformStateCode2( (char *)&lpItemInfo->fMagicMastery, sizeof(float) );
	rsReformStateCode2( (char *)&lpItemInfo->fMPRegen, sizeof(float) );
	rsReformStateCode2( (char *)&lpItemInfo->fHPRegen, sizeof(float) );
	rsReformStateCode2( (char *)&lpItemInfo->fSPRegen, sizeof(float) );
	rsReformStateCode2( (char *)&lpItemInfo->fAddHP, sizeof(float) );
	rsReformStateCode2( (char *)&lpItemInfo->fAddMP, sizeof(float) );
	rsReformStateCode2( (char *)&lpItemInfo->fAddSP, sizeof(float) );

	rsReformStateCode2( (char *)&lpItemInfo->sMPRecovery, sizeof(MinMax));
	rsReformStateCode2( (char *)&lpItemInfo->sHPRecovery, sizeof(MinMax));
	rsReformStateCode2( (char *)&lpItemInfo->sSPRecovery, sizeof(MinMax));
	
	rsReformStateCode2( (char *)&lpItemInfo->iGold, sizeof(int) );
	rsReformStateCode2( (char *)&lpItemInfo->eSpecialization, sizeof(DWORD) );
	rsReformStateCode2( (char *)&lpItemInfo->sSpecData, sizeof(SpecItemData) );

	rsReformStateCode2( (char *)&lpItemInfo->iItemUniqueID, sizeof(int) );
	rsReformStateCode2( (char *)lpItemInfo->EffectBlink , sizeof(short)*2 );
	rsReformStateCode2( (char *)lpItemInfo->EffectColor , sizeof(short)*4 );
	rsReformStateCode2( (char *)lpItemInfo->ScaleBlink , sizeof(short)*2 );
	rsReformStateCode2( (char *)&lpItemInfo->bEnableEffect, sizeof(BOOL) );

	/////////////////////////////////////////////////////////////////////////////
	rsReformStateCode2( (char *)&lpItemInfo->iWeight, sizeof(int) );
	rsReformStateCode2( (char *)&lpItemInfo->iSalePrice, sizeof(int) );

	rsReformStateCode2( (char *)&lpItemInfo->fAbsorbRating, sizeof(float) );
	rsReformStateCode2( (char *)&lpItemInfo->iDefenseRating, sizeof(int) );
	rsReformStateCode2( (char *)&lpItemInfo->fBlockRating, sizeof(float) );

	rsReformStateCode2( (char *)&lpItemInfo->iAttackRange, sizeof(int) );
	rsReformStateCode2( (char *)&lpItemInfo->iAttackSpeed, sizeof(int) );

	rsReformStateCode2( (char *)&lpItemInfo->iAttackRating, sizeof(int) );
	rsReformStateCode2( (char *)&lpItemInfo->iCritical, sizeof(int) );

	rsReformStateCode2( (char *)&lpItemInfo->fMovementSpeed, sizeof(float) );
	rsReformStateCode2( (char *)&lpItemInfo->iPotionStorage, sizeof(int) );

	rsReformStateCode2( (char *)lpItemInfo->saElementalDef, sizeof(short)*8 );
	rsReformStateCode2( (char *)&lpItemInfo->sDamage, sizeof(MinMax));

	/////////////////////////////////////////////////////////////////////////////
	rsReformStateCode2( (char *)&lpItemInfo->iHealth, sizeof(int) );
	rsReformStateCode2( (char *)&lpItemInfo->iLevel, sizeof(int) );
	rsReformStateCode2( (char *)&lpItemInfo->iStrength, sizeof(int) );
	rsReformStateCode2( (char *)&lpItemInfo->iSpirit, sizeof(int) );
	rsReformStateCode2( (char *)&lpItemInfo->iTalent, sizeof(int) );
	rsReformStateCode2( (char *)&lpItemInfo->iAgility, sizeof(int) );

	rsReformStateCode2( (char *)&lpItemInfo->sItemID, sizeof(DWORD) );
	rsReformStateCode2( (char *)lpItemInfo->szItemName, 32 );

	return iFormCode;
}

#endif


DWORD rsGetItem_ServerForm(Item *lpItemInfo )
{
	DWORD dwCode;

#ifdef	_NEW_ITEM_FORMCODE2

	//서버용 재 인증 아이템 ( 신버전 인증 )
	dwCode = rsGetRefromItemCode2( lpItemInfo , lpItemInfo->iChk2);
	dwCode = dwCode ^ ((lpItemInfo->ItemAgingProtect[0]*7)^(lpItemInfo->ItemAgingProtect[1]*9));	//추가 (믹스/에이징) 프로텍트
	dwCode+= (lpItemInfo->dwCreateTime&0xFFFF)<<2;
	dwCode = dwCode ^ (lpItemInfo->iChk1 ^ ((lpItemInfo->iChk2 +dwCode)<<ITEM_FORM_CODE_SHIFT));

#else

	//서버용 재 인증 아이템
	dwCode = rsGetRefromItemCode( lpItemInfo , lpItemInfo->ItemHeader.dwChkSum );

#ifdef	_NEW_ITEM_FORMCODE
	dwCode = dwCode ^ ((lpItemInfo->ItemAgingProtect[0]*7)^(lpItemInfo->ItemAgingProtect[1]*9));	//추가 (믹스/에이징) 프로텍트
	dwCode+= lpItemInfo->dwCreateTime>>8;
#endif

	dwCode = dwCode ^ lpItemInfo->ItemHeader.Head;
#endif

	return dwCode;
}

