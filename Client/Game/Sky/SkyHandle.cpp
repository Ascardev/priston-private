#include "StdAfx.h"
#include "SkyHandle.h"

namespace SKY
{
	/*Handle::Handle()
	{

	}
	Handle::~Handle()
	{

	}
	void Handle::Init()
	{
		LoadFile("Effect\\Sky\\test32.txt");
	}
	void Handle::Shutdown()
	{
		for (auto &pInfo : m_pvInfo)
		{
			DELET(pInfo);
		}

		m_pvInfo.clear();
	}
	void Handle::Render(Point3D sCameraPosition, Point3D sCameraAngle)
	{
		if (m_pCurInfo)
			m_pCurInfo->Render(sCameraPosition, sCameraAngle);

		if (m_pNexInfo)
			m_pNexInfo->Render(sCameraPosition, sCameraAngle);
	}
	void Handle::Update(float fTime)
	{
		if (m_pCurInfo)
		{
			m_pCurInfo->Tick(m_iTimeCount);

			if (m_pCurInfo->GetAnimation() == ESKYANIMATION_None)
			{
				if (m_pNexInfo)
				{
					m_pNexInfo->Tick(m_iTimeCount);

					if (m_pNexInfo->GetAnimation() == ESKYANIMATION_None)
						m_pNexInfo = NULL;
				}
			}
		}

		m_iTimeCount++;
	}
	void Handle::SetSky(int iID)
	{
		auto pInfo = GetInfo(iID);

		if (m_pCurInfo && m_pCurInfo == pInfo)
			return;

		if (pInfo)
		{
			if (m_pCurInfo)
			{
				m_pNexInfo = m_pCurInfo;
				m_pCurInfo = pInfo;

				m_pCurInfo->Fade(ESKYANIMATION_FadeIn, MinMax(50, 0));
				m_pNexInfo->Fade(ESKYANIMATION_FadeOut, MinMax(100, 100));
			}
			else
			{
				m_pCurInfo = pInfo;

				m_pCurInfo->Fade(ESKYANIMATION_FadeIn, MinMax(100, 0));
			}

			m_iTimeCount = 0;
		}
	}
	void Handle::LoadFile(const char *pszFileName)
	{
		FILE *pFile;

		fopen_s(&pFile, pszFileName, "rt");

		if (pFile)
		{
			char szBufLine[256];
			char szToken[256];

			while (!feof(pFile))
			{
				fgets(szBufLine, 256, pFile);
				sscanf_s(szBufLine, "%s%s", szToken, sizeof(szToken), szToken, sizeof(szToken));

				if (STRINGCOMPAREI(szToken, "{"))
				{
					Info *pInfo = new Info;

					while (lstrcmpi(szToken, "}") != 0)
					{
						if (STRINGCOMPAREI(szToken, "FileName:"))
						{
							char szFileName[256];
							BOOL bFadeDelay;
							int iR, iG, iB, iA;

							sscanf_s(szBufLine, "%s%s%s%d%s%d%d%d%d",
								szToken, sizeof(szToken),
								szFileName, sizeof(szFileName),
								szToken, sizeof(szToken),
								&bFadeDelay,
								szToken, sizeof(szToken),
								&iR,&iG,&iB,&iA);

							pInfo->AddElement(szFileName, bFadeDelay, Color4D(iR, iG, iB, iA));
						}

						fgets(szBufLine, 256, pFile);
						sscanf_s(szBufLine, "%s", szToken, sizeof(szToken));
					}

					m_pvInfo.push_back(pInfo);
				}
			}

			fclose(pFile);
		}
	}
	Info *Handle::GetInfo(int iID)
	{
		for (size_t i = 0; i < m_pvInfo.size(); i++)
		{
			if (iID == i) 
				return m_pvInfo[i];
		}

		return NULL;
	}
	void Handle::Open(EMapSky eID)
	{
		switch (eID)
		{
		case MAPSKY_Wasteland_Morning1:
			SetSky(0);
			break;
		case MAPSKY_Wasteland_Morning2:
			SetSky(1);
			break;
		case MAPSKY_Wasteland_Noon:
			SetSky(2);
			break;
		case MAPSKY_Wasteland_Night:
			SetSky(3);
			break;
		case MAPSKY_Forest_Morning:
			SetSky(4);
			break;
		case MAPSKY_Forest_Noon:
			SetSky(5);
			break;
		case MAPSKY_Forest_Night:
			SetSky(6);
			break;
		case MAPSKY_Rain:
			SetSky(7);
			break;
		case MAPSKY_Desert_Morning:
			SetSky(8);
			break;
		case MAPSKY_Desert_Noon:
		case MAPSKY_Battle_Sun:
			SetSky(9);
			break;
		case MAPSKY_Desert_Night:
			SetSky(10);
			break;
		case MAPSKY_ForFAll_Morning:
			SetSky(11);
			break;
		case MAPSKY_ForFAll_Noon:
			SetSky(12);
			break;
		case MAPSKY_ForFAll_Night:
			SetSky(13);
			break;
		case MAPSKY_Iron_Morning:
			SetSky(14);
			break;
		case MAPSKY_Iron_Noon:
			SetSky(15);
			break;
		case MAPSKY_Iron_Night:
			SetSky(16);
			break;
		case MAPSKY_Iron_Aurora:
			SetSky(17);
			break;
		case MAPSKY_Battle_Event:
			SetSky(18);
			break;
		case MAPSKY_Battle_Moon:
			SetSky(19);
			break;
		case MAPSKY_Battle_None:
			SetSky(20);
			break;
		case MAPSKY_Iron_BOSS:
			SetSky(21);
			break;
		case 0x80:
			SetSky(22);
			break;
		case MAPSKY_ICE1_Morning:
			SetSky(23);
			break;
		case MAPSKY_ICE1_Noon:
			SetSky(24);
			break;
		case MAPSKY_ICE1_Night:
			SetSky(25);
			break;
		case MAPSKY_ICE2_Morning:
			SetSky(26);
			break;
		case MAPSKY_ICE2_Noon:
			SetSky(27);
			break;
		case MAPSKY_ICE2_Night:
			SetSky(28);
			break;
		case MAPSKY_Lost1_Morning:
			SetSky(29);
			break;
		case MAPSKY_Lost1_Noon:
			SetSky(30);
			break;
		case MAPSKY_Lost1_Night:
			SetSky(31);
			break;
		case MAPSKY_Lost2_Morning:
			SetSky(32);
			break;
		case MAPSKY_Lost2_Noon:
			SetSky(33);
			break;
		case MAPSKY_Lost2_Night:
			SetSky(34);
			break;
		}
	}*/
}