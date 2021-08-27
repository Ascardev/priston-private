#include "StdAfx.h"
#include "ServerPackets.h"
#include "SrcServer/onserver.h"

CServerPacket::CServerPacket()
{

}
CServerPacket::~CServerPacket()
{

}

BOOL CServerPacket::AnalyzePacket(User * pcUser, PacketReceiving * p)
{
	Packet * psPacket = (Packet*)p->baPacket;

	SERVERNET->OnReceivePacket(pcUser, psPacket);

	PacketsHeader iHeader = (PacketsHeader)psPacket->iHeader;

	switch (iHeader)
	{
	case PKTHDR_LogCheat:
		break;
	case PKTHDR_DCAccount:
		break;
	case PKTHDR_ReconnectedServer:
		break;
	case PKTHDR_SendToLoginServer:
		break;
	case PKTHDR_Microphone:
		break;
	case PKTHDR_LogDataSimple:
		break;
	case PKTHDR_CheckSum:
		break;
	case PKTHDR_LogDebugger:
		break;
	case PKTHDR_UndentifiedPacket:
		break;
	case PKTHDR_PlayDataEx:
		SERVERCHARACTER->OnCharacterSyncDataEx(pcUser, (PacketPlayDataEx*)psPacket);
	case PKTHDR_LoseExp:
		SERVERCHARACTER->OnLoseExp(pcUser, (PacketLoseExperience*)psPacket);
		break;
	case PKTHDR_GetItemData:
		break;
	case PKTHDR_SetItemData:
		break;
	case PKTHDR_WindowList:
		break;
	case PKTHDR_SettingsData:
		SERVERUSER->SettingsDataSet(pcUser, (PacketSettingsData*)psPacket);
		break;
	case PKTHDR_RetryWarehouse:
		break;
	case PKTHDR_WarehouseSaveSuccess:
		break;
	case PKTHDR_DamageQuick:
		break;
	case PKTHDR_QuestNPCOpen:
		break;
	case PKTHDR_QuestNPCAccept:
		break;
	case PKTHDR_QuestStartData:
		break;
	case PKTHDR_QuestUpdateData:
		break;
	case PKTHDR_QuestCancel:
		break;
	case PKTHDR_QuestNPCFinish:
		break;
	case PKTHDR_QuestNPCItemList:
		break;
	case PKTHDR_QuestHandleFinished:
		break;
	case PKTHDR_CharacterDataEx:
		SERVERCHARACTER->HandlePacket(pcUser, (PacketCharacterDataEx*)psPacket);
		break;
	case PKTHDR_ItemSlotHandle:
		SERVERITEM->HandlePacket(pcUser, (PacketSlotItemHandle*)psPacket);
		break;
	case PKTHDR_T5QuestArena:
		break;
	case PKTHDR_DynamicQuestOpen:
		break;
	case PKTHDR_DynamicQuestOpenNPC:
		break;
	case PKTHDR_QuestItemSwap:
		break;
	case PKTHDR_BossTimeUpdate:
		SERVERMAP->HandlePacket(pcUser, (PacketBossTimeUpdate*)psPacket);
		break;
		//Party
	case PKTHDR_RequestParty:
		PARTYHANDLE->HandlePacket(pcUser, (PacketRequestParty*)psPacket);
		break;
	case PKTHDR_JoinParty:
		PARTYHANDLE->HandlePacket(pcUser, (PacketJoinParty*)psPacket);
		break;
	case PKTHDR_ActionParty:
		PARTYHANDLE->HandlePacket(pcUser, (PacketActionParty*)psPacket);
		break;
	case PKTHDR_RequestRaid:
		PARTYHANDLE->HandlePacket(pcUser, (PacketRequestRaid*)psPacket);
		break;
	case PKTHDR_JoinRaid:
		PARTYHANDLE->HandlePacket(pcUser, (PacketJoinRaid*)psPacket);
		break;
	case PKTHDR_PersonalShopMessage:
		break;
	case PKTHDR_SkillStatusContainer:
		break;
	case PKTHDR_SkillStatus:
		break;
	case PKTHDR_PlayDataChar:
		SERVERUSER->HandlePacket(pcUser, (PacketPlayData *)psPacket);
		break;
	case PKTHDR_UnitStatusContainer:
		break;
	case PKTHDR_GameStatus:
		break;
	case PKTHDR_CharacterData:
		SERVERUSER->OnUserSyncData(pcUser, (PacketPlayInfo *)psPacket);
		break;
	case PKTHDR_GetUnitInfoData:
		break;
	case PKTHDR_Disconnect:
		break;
	case PKTHDR_Save:
		break;
	case PKTHDR_ChatGame:
		SERVERCOMMAND->OnReceiveChat(pcUser, (PacketChat*)psPacket);
		break;
	case PKTHDR_ChatMessage:
		break;
	case PKTHDR_ChatItemLink:
		SERVERCHAT->HandlePacket(pcUser, (PacketItemLinkChat*)psPacket);
		break;
	case PKTHDR_Reconnect:
		SERVERUSER->ReconnectUser(pcUser, (PacketReconnectUser*)psPacket);
		break;
	case PKTHDR_ReconnectLogin:
		break;
	case PKTHDR_ChatMessageBox:
		break;
	case PKTHDR_Ping:
		if (((PacketPing*)psPacket)->iLength != sizeof(PacketPing))
			break;
		((PacketPing*)psPacket)->dwTick = GetTickCount();
		SENDPACKET(pcUser, psPacket, TRUE);
		break;
	case PKTHDR_SaveAndClose:
		break;
	case PKTHDR_KillCharacter:
		SERVERUSER->OnKilled(pcUser, (PacketDeadCharacter *)psPacket);
		break;
	case PKTHDR_Connected:
		break;
	case PKTHDR_SaveData:
		SERVERACCOUNT->SaveCharacter(pcUser, (PacketSaveData *)psPacket);
		break;
	case PKTHDR_SelectCharacter:
		SERVERACCOUNT->SelectCharacter(pcUser, (PacketSelectCharacter *)psPacket);
		break;
	case PKTHDR_UserInfo:
		break;
	case PKTHDR_DeleteCharacter:
		SERVERACCOUNT->DeleteCharacter(pcUser, (PacketDeleteCharacter *)psPacket);
		break;
	case PKTHDR_CreateCharacter:
		SERVERACCOUNT->CharacterCreate(pcUser, (PacketCreateCharacter *)psPacket);
		break;
	case PKTHDR_Version:
		break;
	case PKTHDR_ServerList:
		break;
	case PKTHDR_AccountLoginCode:
		break;
	case PKTHDR_LoginUser:
		SERVERACCOUNT->PHAccountLogin(pcUser, (PacketLoginUser*)psPacket);
		break;
	case PKTHDR_UnitStatusMove:
		break;
	case PKTHDR_SetExpOld:
		break;
	case PKTHDR_IceDistortionBuff:
		break;
	case PKTHDR_PoisionDistortionBuff:
		break;
	case PKTHDR_FireDistortionBuff:
		break;
	case PKTHDR_NewItem:
		SERVERITEM->HandlePacket(pcUser, (PacketGetItem *)psPacket);
		break;
	case PKTHDR_PutItem:
		SERVERITEM->HandlePacket(pcUser, (PacketPutItem *)psPacket);
		break;
	case PKTHDR_IntegrityUpdateItem:
		break;
	case PKTHDR_WarpGateField:
		break;
	case PKTHDR_DeleteFlagPoint:
		SERVERMAP->DeleteFlagPoint(pcUser, (PacketDeleteFlagPoint *)psPacket);
		break;
	case PKTHDR_PlayItem:
		break;
	case PKTHDR_TheDeath:
		break;
	case PKTHDR_PacketFun:
		break;
	case PKTHDR_PremiumData:
		break;
	case PKTHDR_SetItemTimer:
		SERVERITEM->HandlePacket(pcUser, (PacketNewItemTimer*)psPacket);
		break;
	case PKTHDR_CancelItemTimer:
		SERVERITEM->HandlePacket(pcUser, (PacketCancelItemTimer*)psPacket);
		break;
	case PKTHDR_CharacterHeadOldUse:
		SERVERITEM->HandlePacket(pcUser, (PacketOldHeadUse*)psPacket);
		break;
	case PKTHDR_DisableGM:
		pcUser->iGameLevel = GAMELEVEL_None;
		SERVERNET->SendGameMaster(pcUser);
		SERVERCHAT->SendChat(pcUser, CHATCOLOR_Error, "> GM Disabled!");
		break;
	case PKTHDR_PVPDataUpdate:
		break;
	case PKTHDR_UserOnline:
		SERVERCOMMAND->CheckUserOnline(pcUser, (PacketUserOnline*)psPacket);
		break;
	case PKTHDR_CancelForceOrb:
		SERVERUSER->CancelForceOrb(pcUser);
		break;
	case PKTHDR_PvPKill:
		break;
	case PKTHDR_BlessCastleInfomation:
		SERVERBLESSCASTLE->HandlePacket(pcUser, (PacketBlessCastleStatusSettingsData *)psPacket);
		break;
	case PKTHDR_BlessCastleTax:
		SERVERBLESSCASTLE->HandlePacket(pcUser, (PacketBlessCastleTex *)psPacket);
		break;
	case PKTHDR_BlessCastleSkill:
		SERVERBLESSCASTLE->HandlePacket(pcUser, (PacketBlessCastleSkill *)psPacket);
		break;
	case PKTHDR_UseEffect:
		SERVERUNIT->HandlePacket(pcUser, (PacketUserEffect *)psPacket);
		break;
	case PKTHDR_UseGold:
		SERVERUNIT->HandlePacket(pcUser, (PacketUseGold *)psPacket);
		break;
	case PKTHDR_UseItem:
		SERVERITEM->HandlePacket(pcUser, (PacketUseItem *)psPacket);
		break;
	case PKTHDR_DamageDebugInfo:
		SERVERMAP->OnSendDebugDamage(pcUser, (PacketDebugDamageInfo*)psPacket);
		break;
		//Coin Shop
	case PKTHDR_CoinShopAmount:
		COINSHOPHANDLE->HandlePacket(pcUser, (PacketCoinAmount*)psPacket);
		break;
	case PKTHDR_CoinShopNPC:
		COINSHOPHANDLE->HandlePacket(pcUser, (PacketCoinShopNPC*)psPacket);
		break;
	case PKTHDR_CoinShopOpenTab:
		COINSHOPHANDLE->HandlePacket(pcUser, (PacketCoinOpenTab*)psPacket);
		break;
	case PKTHDR_CoinShopOpenItemData:
		COINSHOPHANDLE->HandlePacket(pcUser, (PacketCoinOpenItemData*)psPacket);
		break;
	case PKTHDR_CoinShopBuy:
		COINSHOPHANDLE->HandlePacket(pcUser, (PacketCoinBuy*)psPacket);
		break;
	case PKTHDR_CoinServiceBuy:
		COINSHOPHANDLE->HandlePacket(pcUser, (PacketCoinServiceBuy*)psPacket);
		break;
	case PKTHDR_DistrbutorItemShow:
		DISTRIBUTORHANDLE->OpenDistributorItem(pcUser);
		break;
	case PKTHDR_DistrbutorItemAccept:
		DISTRIBUTORHANDLE->AcceptDistributorItem(pcUser);
		break;
	case PKTHDR_DistrbutorItemDelete:
		DISTRIBUTORHANDLE->DeleteDistributorItem(pcUser);
		break;
	case PKTHDR_DistrbutorItemSend:
		DISTRIBUTORHANDLE->HandlePacket(pcUser, (PacketItemBoxSend *)psPacket);
		break;
	case PKTHDR_GameMasterCheck:
		SERVERACCOUNT->OnGameMasterCheck(pcUser);
		break;
	default:
		break;
	}

	OnRecvMessage(pcUser, p);

	return FALSE;
}

void CServerPacket::Send(User * pcUser, void * pPacket, BOOL bEncrypted)
{
	if (pcUser && pcUser->pcSocketData)
		pcUser->pcSocketData->SendPacket((Packet*)pPacket, bEncrypted);
}

void CServerPacket::SendPacketBlank(User * pcUser, int iPacket, BOOL bEncrypted)
{
	struct PacketBlank : Packet
	{
		int						iUnk[4];
	};
	PacketBlank sPacket;
	sPacket.iLength = sizeof(PacketBlank);
	sPacket.iHeader = iPacket;

	SENDPACKET(pcUser, &sPacket, bEncrypted);
}
void CServerPacket::SendPacketStage(void * pPacket, int iStageID, BOOL bEncrypt)
{
	for (int i = 0; i < PLAYERS_MAX; i++)
	{
		User * u = USERSDATA + i;

		if (u && u->IsConnected() && u->IsInGame() && u->iMapID == iStageID)
		{
			SENDPACKET(u, pPacket, bEncrypt);
		}
	}
}
void CServerPacket::SendPacketRange(void * pPacket, Point3D * psPos, int iDistance, BOOL bEncrypt)
{
	for (int i = 0; i < PLAYERS_MAX; i++)
	{
		User * u = USERSDATA + i;

		if (u && u->IsConnected() && u->IsInGame())
		{
			int iShrDistance = iDistance / 72;
			int iX = (psPos->iX - u->sPosition.iX) >> 8;
			int iZ = (psPos->iZ - u->sPosition.iZ) >> 8;
			int iDist = (iX*iX + iZ * iZ);
			if (iDist < iDistance && abs(iX) < iShrDistance && abs(iZ) < iShrDistance)
				SENDPACKET(u, pPacket, bEncrypt);
		}
	}
}