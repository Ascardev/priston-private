#include "StdAfx.h"

CServerLog::CServerLog()
{

}
CServerLog::~CServerLog()
{

}
const char * CServerLog::SetLogString(ELogItem eType)
{
	switch (eType)
	{
	case ITEMLOGID_Get:
		return FormatString("[%s](%s) Got Item ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_Put:
		return FormatString("[%s](%s) Dropped Item ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_Mixing:
		return FormatString("[%s](%s) Mixed Item ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_MixLost:
		return FormatString("[%s](%s) Failed Mix on Item ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_Aging:
		return FormatString("[%s](%s) Aged Item ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_AgingLost:
		return FormatString("[%s](%s) Lost Item on Age ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_AgingUp:
		return FormatString("[%s](%s) Age Item Sucess ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_BuyShop:
		return FormatString("[%s](%s) Bought Item from Shop ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_SellShop:
		return FormatString("[%s](%s) Sold Item on Shop ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_Trade:
		return FormatString("[%s](%s) Traded Item to [%s](%s) ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_Used:
		return FormatString("[%s](%s) Used Item ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_Express:
		return FormatString("[%s](%s) Express Item ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_GetWing:
		return FormatString("[%s](%s) Got Wing ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_WingLost:
		return FormatString("[%s](%s) Lost Wing ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_BuyStar:
		return FormatString("[%s](%s) Bought Star ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_Aging2Up:
		return FormatString("[%s](%s) Age Item +2 Sucess ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_Aging2Down:
		return FormatString("[%s](%s) Age Item -2 Fail ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_Aging1Down:
		return FormatString("[%s](%s) Age Item -1 Fail ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_AgingKeep:
		return FormatString("[%s](%s) Age Fail Same Status Fail ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_Present:
		return FormatString("[%s](%s) Got Start Item ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_PersonalShop:
		return FormatString("[%s](%s) Put Item on Personal Shop ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_UseAlchmy:
		return FormatString("[%s](%s) Used Alchemy on Item ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_LostAlchmy:
		return FormatString("[%s](%s) Lost Alchemy on Item ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_GetAlchmy:
		return FormatString("[%s](%s) Get Alchemy on Item ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_GetRecon:
		return FormatString("[%s](%s) Respec Item ( [%s][0x%08X] %d x %d -> %d x %d )");
		break;
	case ITEMLOGID_LostRecon:
		return FormatString("[%s](%s) Respec Item Fail ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_SmeltingLost:
		return FormatString("[%s](%s) Smelting Item Fail ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_SmeltingGet:
		return FormatString("[%s](%s) Smelting Item Sucess ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_ManufactureLost:
		return FormatString("[%s](%s) Craft Item Lost ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_ManufactureGet:
		return FormatString("[%s](%s) Craft Item Sucess ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_ManufactureFail:
		return FormatString("[%s](%s) Craft Item Fail ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_MixtureResetLost:
		return FormatString("[%s](%s) Reset Mix Item Lost ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_MixtureResetFail:
		return FormatString("[%s](%s) Reset Mix Item Fail ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_MixtureResetGet:
		return FormatString("[%s](%s) Reset Mix Item Sucess ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_PremiumTimerOver:
		return FormatString("[%s](%s) Reset Mix Item Sucess ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_TradeItems:
		return FormatString("[%s](%s) Got Item ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_TradeItemsRemove:
		return FormatString("[%s](%s) Got Item ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_RewardEasterGet:
		return FormatString("[%s](%s) Got Item ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_RewardXmasRudolphGet:
		return FormatString("[%s](%s) Got Item ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_TradeItemSuccess:
		return FormatString("[%s](%s) Got Item ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_TradeItemSuccessReceive:
		return FormatString("[%s](%s) Got Item ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_GetPerfectize:
		return FormatString("[%s](%s) Got Item ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_PutPerfectize:
		return FormatString("[%s](%s) Got Item ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_GetSwap:
		return FormatString("[%s](%s) Got Item ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_PutSwap:
		return FormatString("[%s](%s) Got Item ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_PerfectizedItem:
		return FormatString("[%s](%s) Got Item ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_SwappedItem:
		return FormatString("[%s](%s) Got Item ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_RollDiceJoin:
		return FormatString("[%s](%s) Got Item ( [%s][0x%08X] %d x %d )");
		break;
	case ITEMLOGID_RollDiceWon:
		return FormatString("[%s](%s) Got Item ( [%s][0x%08X] %d x %d )");
		break;
	default:
		break;
	}

	return "";
}
void CServerLog::LogCheat(User * pcUser, PacketLogCheat * psPacket)
{
	if (pcUser)
	{
		char szCheatLog[512] = { 0 };

		const char * pszDateTime = GetDateTime();

		BOOL Banned = FALSE;
		BOOL Disconnect = FALSE;
		int iDays = 0;

		char * pszIP = "";
		DWORD dwIP = 0;

		if (pcUser->pcSocketData)
		{
			pszIP = pcUser->pcSocketData->szIP;
			dwIP = pcUser->pcSocketData->lIP;
		}

		char * pszCharacterName = SERVERCHARACTER->GetCharacterName(pcUser);

		SERVERUSER->SetUserID(pcUser);

		switch (psPacket->iCheatID)
		{
		case CHEATLOGID_TooManyPackets:
			SERVERSOCKET->AddBanIP(dwIP);
			STRINGFORMAT(szCheatLog, "IP[%s] Packets[%d/%d] Time[%d] IP Blocked", pszIP, psPacket->iLParam, psPacket->iSParam, psPacket->iEParam);
			break;
		case CHEATLOGID_CopiedItem:
			STRINGFORMAT(szCheatLog, "Character[%s] Copied Item[%d]", pszCharacterName, psPacket->iLParam);
			Banned = TRUE;
			break;
		case CHEATLOGID_ValidateCharacterError:
			STRINGFORMAT(szCheatLog, "Character[%s] Validate Character Error", pszCharacterName);
			Disconnect = TRUE;
			break;
		case CHEATLOGID_DelaySkillHack:
			STRINGFORMAT(szCheatLog, "Character[%s] Delay Skill Hack", pszCharacterName);
			Banned = TRUE;
			break;
		case CHEATLOGID_EasterEggFakeItem:
			STRINGFORMAT(szCheatLog, "Character[%s] Fake Item Easter Reward[%08X][%d x %d]", 
				pszCharacterName, psPacket->iLParam, psPacket->iSParam, psPacket->iEParam);
			break;
		case CHEATLOGID_XmasRudolphFakeBox:
			STRINGFORMAT(szCheatLog, "Character[%s] Fake Item Xmas Rudolph Reward[%08X][%d x %d]",
				pszCharacterName, psPacket->iLParam, psPacket->iSParam, psPacket->iEParam);
			break;

		case CHEATLOGID_RespecFakeItem:
			STRINGFORMAT(szCheatLog, "Character[%s] Fake Item Respec[%s][%08X][%d x %d]", 
				pszCharacterName, (char *)psPacket->iLxParam, psPacket->iLParam, psPacket->iSParam, psPacket->iEParam);
			Banned = TRUE;
			break;

		case CHEATLOGID_NPCItemShopFakeItem:
			STRINGFORMAT(szCheatLog, "Character[%s] Fake Item Buy NPC Shop[%s][%08X x %08X]",
				pszCharacterName, (char *)psPacket->iEParam, psPacket->iLParam, psPacket->iSParam);
			Banned = TRUE;
			break;
		case CHEATLOGID_ItemTimerFakeInventory:
			STRINGFORMAT(szCheatLog, "Character[%s] Fake Item Timer Server[0x%08X][%s][%d x %d]",
				pszCharacterName, psPacket->iLParam, (char *)psPacket->iLxParam, psPacket->iSParam, psPacket->iEParam);
			Disconnect = TRUE;
			break;
		case CHEATLOGID_CopiedItemWarehouse:
			STRINGFORMAT(szCheatLog, "Character[%s] Copied Item in Warehouse[%d]", pszCharacterName, psPacket->iLParam);
			Banned = TRUE;
			break;

		case CHEATLOGID_WarehouseNewClone:
			STRINGFORMAT(szCheatLog, "Character[%s] Warehouse Clone Hack (ItemID[0x%08X] Code[%d x %d])",
				pszCharacterName, psPacket->iLParam, psPacket->iSParam, psPacket->iEParam);
			Banned = TRUE;
			break;

		case CHEATLOGID_WarehouseGold:
			STRINGFORMAT(szCheatLog, "Character[%s] Gold Fake in Warehouse[%d]",
				pszCharacterName, psPacket->iLParam);
			Banned = TRUE;
			break;
		case CHEATLOGID_WarehouseBug:
			STRINGFORMAT(szCheatLog, "Character[%s] Bug Warehouse (cannot saved)", pszCharacterName);
			break;
		case CHEATLOGID_HackDetected:
			STRINGFORMAT(szCheatLog, "Character[%s] Hack Detected[%s]", pszCharacterName, (char*)psPacket->iLParam);
			Disconnect = TRUE;
			break;
		case CHEATLOGID_GoldLimit:
			STRINGFORMAT(szCheatLog, "Character[%s] Gold Hack (Potion Copy[%d][%d])", pszCharacterName,
				psPacket->iSParam, psPacket->iLParam);
			Disconnect = TRUE;
			break;
		case CHEATLOGID_SpeedHack:
			STRINGFORMAT(szCheatLog, "Character[%s] Speed Hack (Velocity[%d])", pszCharacterName, psPacket->iLParam);
			Banned = TRUE;
			break;
		case CHEATLOGID_TimeErrorSpeedHack:
			STRINGFORMAT(szCheatLog, "Character[%s] Speed Time Hack (Velocity[%d] Time[%d])",
				pszCharacterName, psPacket->iLParam, psPacket->iSParam);
			break;
		case CHEATLOGID_TimeMismatch:
			STRINGFORMAT(szCheatLog, "Character[%s] Time Mismatch (Time[%d])", pszCharacterName, psPacket->iLParam);
			break;
		case CHEATLOGID_AttackRatioError:
			STRINGFORMAT(szCheatLog, "Character[%s] Attack Rating error (AttackRating[%d])", pszCharacterName, psPacket->iLParam);
			Disconnect = TRUE;
			break;
		case CHEATLOGID_PotionCheckError:
			STRINGFORMAT(szCheatLog, "Character[%s] Potion error Check (Count[%d])", pszCharacterName, psPacket->iLParam);
			Disconnect = TRUE;
			break;
		case CHEATLOGID_PotionCountError:
			STRINGFORMAT(szCheatLog, "Character[%s] Potion Count Error (Count[%d])", pszCharacterName, psPacket->iLParam);
			break;
		case CHEATLOGID_WrongSavingCharacterName:
			STRINGFORMAT(szCheatLog, "Character[%s] Name Error(Count[%d])", pszCharacterName, psPacket->iLParam);
			break;
		case CHEATLOGID_CharInfoSaveError:
			STRINGFORMAT(szCheatLog, "Character[%s] Saving Error (Code[%d])", pszCharacterName, psPacket->iLParam);
			Banned = TRUE;
			break;
		case CHEATLOGID_DefaultAttackRatingError:
			STRINGFORMAT(szCheatLog, "Character[%s] Attack Rating Error (AttackRating[%d])", pszCharacterName, psPacket->iLParam);
			Banned = TRUE;
			break;
		case CHEATLOGID_DefaultAttackSizeError:
			STRINGFORMAT(szCheatLog, "Character[%s] Attack Size Error (AttackSize[%d])", pszCharacterName, psPacket->iLParam);
			Banned = TRUE;
			break;
		case CHEATLOGID_ContinuousAttackError:
			STRINGFORMAT(szCheatLog, "Character[%s] Attack Continuous Error (AttackError[%d])", pszCharacterName, psPacket->iLParam);
			break;
		case CHEATLOGID_SkillAttackRatingError:
			STRINGFORMAT(szCheatLog, "Character[%s] Attack Rating Error (AttackRating[%d])", pszCharacterName, psPacket->iLParam);
			Banned = TRUE;
			break;
		case CHEATLOGID_SkillContinuousAttackError:
			STRINGFORMAT(szCheatLog, "Character[%s] Skill Continuous Error (Error[%d])", pszCharacterName, psPacket->iLParam);
			Banned = TRUE;
			break;
		case CHEATLOGID_RestrictedAreaTrespassed:
			if (psPacket->iSParam > 0)
			{
				STRINGFORMAT(szCheatLog, "Character[%s] Trespass Stage (Level[%d] StageLevel[%d] Stage[%d])", pszCharacterName, psPacket->iSParam, psPacket->iLParam, pcUser->iMapID);
				Banned = TRUE;
			}
			break;
		case CHEATLOGID_ItemErrorInventory:
			STRINGFORMAT(szCheatLog, "Character[%s] Inventory Game Item Error ([%08X] %d x %d)", pszCharacterName, psPacket->iLParam, psPacket->iSParam, psPacket->iEParam);
			break;
		case CHEATLOGID_TeleportFieldHack:
			STRINGFORMAT(szCheatLog, "Character[%s] Teleport Field Hack (Field[%d -> %d])", pszCharacterName, psPacket->iLParam, psPacket->iSParam);
			Banned = TRUE;
			break;
		case CHEATLOGID_FindThreadHack:
			STRINGFORMAT(szCheatLog, "Character[%s] Find Thread Hack (ThreadID[%d])", pszCharacterName, psPacket->iLParam);
			Banned = TRUE;
			break;
		case CHEATLOGID_ServerMoneyOverflow:
			STRINGFORMAT(szCheatLog, "Character[%s]Level[%d]Tier[%d] Gold Overflow NPC ((%s) Gold(%d) ActionGold(%d) NewGold(%d))",
				pszCharacterName, pcUser->sCharacterData.iLevel, pcUser->sCharacterData.iRank + 1,
				(char *)psPacket->iLxParam, psPacket->iLParam, psPacket->iSParam, psPacket->iEParam);
			Banned = TRUE;
			break;
		case CHEATLOGID_LevelHack:
			STRINGFORMAT(szCheatLog, "Character[%s] Level Hack (Level(%d -> %d) [%d]))",
				pszCharacterName, psPacket->iLParam, psPacket->iSParam, psPacket->iEParam);
			Banned = TRUE;
			break;

		case CHEATLOGID_MatureHack:
			STRINGFORMAT(szCheatLog, "Character[%s] Mature Hack (CodeVerify[%d] Mature[%d / %d] AgeLvl[%d] ([%08X][%d x %d]))",
				pszCharacterName, psPacket->iSParam, psPacket->iEParam, psPacket->iLxParam, psPacket->iWxParam,
				psPacket->iLParam, psPacket->iSxParam, psPacket->iExParam);
			Banned = TRUE;
			break;

		case CHEATLOGID_DefenseMultHack:
			STRINGFORMAT(szCheatLog, "Character[%s] Defense Mult Hack (Num[%f])",
				pszCharacterName, *(float*)&psPacket->iSParam);
			Banned = TRUE;
			break;

		case CHEATLOGID_RegenFormulaHack:
			STRINGFORMAT(szCheatLog, "Character[%s] Regen Formula Hack (Num[%lf])",
				pszCharacterName, *(double*)&psPacket->iSParam);
			Banned = TRUE;
			break;

		case CHEATLOGID_SkillCooldown:
			STRINGFORMAT(szCheatLog, "Character[%s] Skill Cooldown Hack Index[%d] [%d] < [%d]",
				pszCharacterName, psPacket->iSParam, psPacket->iLxParam, psPacket->iEParam);
			Banned = TRUE;
			break;

		case CHEATLOGID_AgingHack:
			STRINGFORMAT(szCheatLog, "Character[%s] Age Hack (AgeLvl[%d] Sheltoms[%d] ([%08X][%d x %d]))",
				pszCharacterName, psPacket->iLParam, psPacket->iSParam, psPacket->iEParam, psPacket->iLxParam, psPacket->iWxParam);
			Banned = TRUE;
			break;

		case CHEATLOGID_FakeGM:
			STRINGFORMAT(szCheatLog, "Character[%s] Fake GameMaster", pszCharacterName);
			Banned = TRUE;
			break;

		case CHEATLOGID_RunSpeedHack:
			STRINGFORMAT(szCheatLog, "Character[%s] Run Speed Hack (Move[%d] Speed[%d])",
				pszCharacterName, psPacket->iLParam, (((psPacket->iLParam << 8) / 460) - 250) / 10);
			Banned = TRUE;
			break;

		case CHEATLOGID_CheckSumFunctionError:
			STRINGFORMAT(szCheatLog, "Character[%s] Checksum Function Error (Size[%d] Addr[0x%08X] Checksum[%d] ChecksumError[%d])",
				pszCharacterName, psPacket->iLParam, psPacket->iSParam, psPacket->iEParam, psPacket->iLxParam);
			Banned = TRUE;
			break;

		case CHEATLOGID_WindowHack:
			STRINGFORMAT(szCheatLog, "Character[%s] Window Hack Found (WindowName[%s])", pszCharacterName, ((PacketLogCheatEx*)psPacket)->szParam);
			Banned = TRUE;
			break;

		case CHEATLOGID_StateCharacterHack:
			STRINGFORMAT(szCheatLog, "Character[%s] State Character Hack", pszCharacterName);
			Banned = TRUE;
			break;

		case CHEATLOGID_DebuggerHack:
			STRINGFORMAT(szCheatLog, "Character[%s] Debugger Hack Found", pszCharacterName);
			Banned = TRUE;
			break;

		case CHEATLOGID_MixingItemHack:
			STRINGFORMAT(szCheatLog, "Character[%s] Mixing Hack Item[0x%08X]", pszCharacterName, psPacket->iLParam);
			break;

		case CHEATLOGID_GoldHackNPC:
			STRINGFORMAT(szCheatLog, "Character[%s] Gold Hack NPC", pszCharacterName);
			Banned = TRUE;
			break;

		case CHEATLOGID_GoldHackWH:
			STRINGFORMAT(szCheatLog, "Character[%s] Gold Hack Warehouse", pszCharacterName);
			//	Banned = TRUE;
			break;

		case CHEATLOGID_ItemPositionError:
			STRINGFORMAT(szCheatLog, "Character[%s] Item Position Error[0x%08X][0x%08X][%d]",
				pszCharacterName, psPacket->iLParam, psPacket->iSParam, psPacket->iEParam);
			Banned = TRUE;
			break;

		case CHEATLOGID_ManufactureItemFake:
			STRINGFORMAT(szCheatLog, "Character[%s] Manufacture Item Fake ([%08X][%d x %d]))",
				pszCharacterName, psPacket->iLParam, psPacket->iSParam, psPacket->iEParam);
			Banned = TRUE;
			break;

		case CHEATLOGID_LimitDamageOver:
		case CHEATLOGID_ClientEnergyBarError:
		case CHEATLOGID_ServerMoneyErrorInventory:
		case CHEATLOGID_ClientWarningSkillForgery2:
		case CHEATLOGID_CopiedItemError:
		case CHEATLOGID_ServerInventoryCopiedItem:
		case CHEATLOGID_WarningInvincibleMode:
		case CHEATLOGID_ClientDamagePacketError:
		case CHEATLOGID_DamagePacketError:
		case CHEATLOGID_WarningMacroMouse:
		case CHEATLOGID_ServerToServerItemError:
		case CHEATLOGID_WeightError:
			// no need
			break;

		case CHEATLOGID_GMReason:
			STRINGFORMAT(szCheatLog, "Character[%s] %s", pszCharacterName, ((PacketLogCheatEx*)psPacket)->szParam);
			Banned = TRUE;
			break;
		case CHEATLOGID_CompareClanCodeError:
			STRINGFORMAT(szCheatLog, "Character[%s] Compare ClanCode Error ClanCode( %d <> %d )", pszCharacterName, psPacket->iLParam, psPacket->iSParam);
			break;

		default:
			STRINGFORMAT(szCheatLog, "Character[%s] Unknown Log[%d]", pszCharacterName, psPacket->iCheatID);
			break;
		}

		if (IsNull(szCheatLog))
			return;

		int iActionType = 0;

		// Get UserID
		SERVERUSER->SetUserID(pcUser);

		if (Banned && pcUser->iGameLevel == GAMELEVEL_None)
		{
			iActionType = 2;
			DWORD dwTime = 0;
			if (iDays)
				dwTime = TICKCOUNT + (60 * 60 * (24 * iDays));

			SQLConnection * pcDB = SQLCONNECTION(DATABASEID_UserDB);
			if (pcDB->Open())
			{
				if (pcDB->Prepare("UPDATE UserInfo SET BanStatus=1, UnbanDate=NULL WHERE AccountName=?"))
				{
					pcDB->BindParameterInput(1, PARAMTYPE_String, pcUser->szAccountName);
					pcDB->Execute();
				}
				pcDB->Close();
			}
		}
		else if (Disconnect && pcUser->iGameLevel == GAMELEVEL_None)
		{
			iActionType = 1;
		}

		BOOL bGameServer = GAME_SERVER;

		SQLConnection * pcDB = SQLCONNECTION(DATABASEID_LogDB);

		if (pcDB->Open())
		{
			if (pcDB->Prepare("INSERT INTO CheatLog VALUES (?,?,?,?,?,?,?)"))
			{
				pcDB->BindParameterInput(1, PARAMTYPE_String, pszIP);
				pcDB->BindParameterInput(2, PARAMTYPE_String, pcUser->szAccountName);
				pcDB->BindParameterInput(3, PARAMTYPE_Integer, &iActionType);
				pcDB->BindParameterInput(4, PARAMTYPE_Integer, &psPacket->iCheatID);
				pcDB->BindParameterInput(5, PARAMTYPE_String, szCheatLog);
				pcDB->BindParameterInput(6, PARAMTYPE_String, (void *)pszDateTime);
				pcDB->BindParameterInput(7, PARAMTYPE_Integer, &bGameServer);
				pcDB->Execute();
			}
			pcDB->Close();
		}

		if ((Banned || Disconnect) && pcUser->iGameLevel == GAMELEVEL_None)
		{
			if (!pcUser->bClosingSocket)
			{
				SENDPACKETBLANK(pcUser, PKTHDR_Disconnect, TRUE);
				pcUser->dwDisconnectTime = TICKCOUNT + 1500;
				//WNDPROC_SOCKETCLOSE( SOCKETSERVER->GetHWND(), pcUserData->pcSocketData );
			}
		}
	}
}
void CServerLog::LogSocketClose(SocketData * pcSocketData, char * pszLocation, void * p)
{
	// Log It
	SQLConnection * pcDB = SQLCONNECTION(DATABASEID_LogDB);
	if (pcSocketData && pcDB->Open())
	{
		char * pszAccountName = pcSocketData->u != nullptr ? pcSocketData->u->szAccountName : "";
		BOOL bNetServer = pcSocketData->u != 0 ? pcSocketData->u->bNetServer : FALSE;
		BOOL bKeepAlive = pcSocketData->bKeepAlive;

		char szRetAddr[32] = { 0 };
		STRINGFORMAT(szRetAddr, "%p", p);
		char szRetAddr2[32] = { 0 };
		STRINGFORMAT(szRetAddr2, "%p", _ReturnAddress());

		char * pszServer = GAME_SERVER != 0 ? "GameServer" : "LoginServer";

		if (pcDB->Prepare("INSERT INTO Disconnects([IP],[AccountName],[NetServer],[KeepAlive],[ServerType],[Location],[ReturnAddress],[ReturnAddressCall],[Date]) VALUES(?,?,?,?,?,?,?,?,GETDATE())"))
		{
			pcDB->BindParameterInput(1, PARAMTYPE_String, pcSocketData->szIP, 16);
			pcDB->BindParameterInput(2, PARAMTYPE_String, pszAccountName, STRLEN(pszAccountName));
			pcDB->BindParameterInput(3, PARAMTYPE_Integer, &bNetServer);
			pcDB->BindParameterInput(4, PARAMTYPE_Integer, &pcSocketData->bKeepAlive);
			pcDB->BindParameterInput(5, PARAMTYPE_String, pszServer, STRLEN(pszServer));
			pcDB->BindParameterInput(6, PARAMTYPE_String, pszLocation, STRLEN(pszLocation));
			pcDB->BindParameterInput(7, PARAMTYPE_String, szRetAddr, 32);
			pcDB->BindParameterInput(8, PARAMTYPE_String, szRetAddr2, 32);
			pcDB->Execute();
		}
		pcDB->Close();
	}
}
void CServerLog::OnLogItem(User * pcUser, int iID, int iChk1, int iChk2, ELogItem eLogItem)
{
	LogItem	sLogItem;

	ZeroMemory(&sLogItem, sizeof(LogItem));

	if (pcUser->pcSocketData)
	{
		sLogItem.eLogItem = eLogItem;

		STRINGCOPY(sLogItem.szUserID, pcUser->szAccountName);
		STRINGCOPY(sLogItem.szCharacterName, pcUser->szCharacterName);

		sLogItem.iIP = pcUser->pcSocketData->lIP;
		sLogItem.sItem[0].dwCode = iID;
		sLogItem.sItem[0].iChk1 = iChk1;
		sLogItem.sItem[0].iChk2 = iChk2;
		sLogItem.iItemCount = 1;
		sLogItem.iLength = sizeof(LogItem) - (sizeof(LogItem::Header) * (32 - sLogItem.iItemCount));

		OnLogItem(LOGTYPEID_LogItem, sLogItem.iLength, &sLogItem);
	}
}
void CServerLog::OnLogItem(int eType, int iSize, void * psLogItem)
{
	switch ((ELogServerType)eType)
	{
	case LOGTYPEID_LogItem:
		OnLogItemData((LogItem*)psLogItem);
		break;
	//case LOGTYPEID_LogItemTrade:
		//OnLogItemTradeData((LogItemTrade*)psLogItem);
		//break;
	//case LOGTYPEID_LogItemExpress:
		//OnLogItemExpressData((LogItemGift*)psLogItem);
		//break;
	default:
		break;
	}
}
void CServerLog::AddFirewallBan(const char * pszIP)
{

}
void CServerLog::OnLogItemData(LogItem * psLog)
{
	ELogItem eType = psLog->eLogItem;

	if (eType == ITEMLOGID_Get)
	{
		if (psLog->sItem[0].dwCode == ITEMID_Gold)
			return;
		if ((psLog->sItem[0].dwCode & 0xFF000000) == ITEMBASE_Potion)
			return;
	}

	char szLog[256] = { 0 };

	char szDateTime[20];
	STRINGCOPY(szDateTime, GetDateTime());

	int iIP = psLog->iIP;

	// Set log format
	char szLogFormat[256] = { 0 };
	STRINGCOPY(szLogFormat, SetLogString(eType));

	// Convert IP to string
	char szIP[20] = { 0 };
	STRINGFORMAT(szIP, "%d.%d.%d.%d", iIP & 0xFF, (iIP >> 8) & 0xFF, (iIP >> 16) & 0xFF, (iIP >> 24) & 0xFF);

	BOOL bStop = FALSE;

	// Set log items
	char szItemName[32] = { 0 };

	BOOL bServer = GAME_SERVER;

	for (int i = 0; i < psLog->iItemCount; i++)
	{
		auto * pItem = SERVERITEM->GetItemDataByID(psLog->sItem[i].dwCode);

		if (pItem)
		{
			STRINGCOPY(szItemName, pItem->szBaseName);

			if (eType == ITEMLOGID_GetRecon)
			{
				STRINGFORMAT(szLog, szLogFormat, psLog->szUserID, psLog->szCharacterName, szItemName, psLog->sItem[0].dwCode, psLog->sItem[0].iChk1, psLog->sItem[0].iChk2,
					psLog->sItem[1].iChk1, psLog->sItem[1].iChk2);
				bStop = TRUE;
			}
			else
				STRINGFORMAT(szLog, szLogFormat, psLog->szUserID, psLog->szCharacterName, szItemName, psLog->sItem[i].dwCode, psLog->sItem[i].iChk1, psLog->sItem[i].iChk2);

			SQLConnection * pcDB = SQLCONNECTION(DATABASEID_LogDB);
			if (pcDB->Open())
			{
				if (pcDB->Prepare("INSERT INTO ItemLog VALUES (?,?,?,?,?,?,?,?)"))
				{
					pcDB->BindParameterInput(1, PARAMTYPE_String, szIP);
					pcDB->BindParameterInput(2, PARAMTYPE_String, psLog->szUserID);
					pcDB->BindParameterInput(3, PARAMTYPE_Integer, &psLog->eLogItem);
					pcDB->BindParameterInput(4, PARAMTYPE_String, szLog);
					pcDB->BindParameterInput(5, PARAMTYPE_Integer, &psLog->sItem[i].iChk1);
					pcDB->BindParameterInput(6, PARAMTYPE_Integer, &psLog->sItem[i].iChk2);
					pcDB->BindParameterInput(7, PARAMTYPE_String, szDateTime);
					pcDB->BindParameterInput(8, PARAMTYPE_Integer, &bServer);
					pcDB->Execute();
				}
				pcDB->Close();
			}
			if (bStop == TRUE)
				break;
		}
	}
}
void CServerLog::OnLogItemEx(User * pcUser, int iLogID, const char * pszLog, ...)
{
	if (pcUser && pcUser->pcSocketData)
	{
		static char szLog[512] = { 0 };

		char szDateTime[20];
		STRINGCOPY(szDateTime, GetDateTime());

		// Convert IP to string
		char szIP[20] = { 0 };
		STRINGFORMAT(szIP, "%s", pcUser->pcSocketData->szIP);

		BOOL bServer = GAME_SERVER;

		// Set log item
		va_list ap;
		va_start(ap, pszLog);
		vsnprintf_s(szLog, 512, pszLog, ap);
		va_end(ap);

		int iUnk = 0;

		SQLConnection * pcDB = SQLCONNECTION(DATABASEID_LogDB);
		if (pcDB->Open())
		{
			if (pcDB->Prepare("INSERT INTO ItemLog VALUES (?,?,?,?,?,?,?,?)"))
			{
				pcDB->BindParameterInput(1, PARAMTYPE_String, szIP, 20);
				pcDB->BindParameterInput(2, PARAMTYPE_String, pcUser->szAccountName, 32);
				pcDB->BindParameterInput(3, PARAMTYPE_Integer, &iLogID);
				pcDB->BindParameterInput(4, PARAMTYPE_String, szLog, 512);
				pcDB->BindParameterInput(5, PARAMTYPE_Integer, &iUnk);
				pcDB->BindParameterInput(6, PARAMTYPE_Integer, &iUnk);
				pcDB->BindParameterInput(7, PARAMTYPE_String, szDateTime, 20);
				pcDB->BindParameterInput(8, PARAMTYPE_Integer, &bServer);
				pcDB->Execute();
			}
			pcDB->Close();
		}
	}
}