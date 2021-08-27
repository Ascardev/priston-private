#include "StdAfx.h"
#include "WarpHandle.h"

namespace MAP
{
	namespace WARP
	{
		/*Handle::Handle() : CBaseHandle()
		{

		}
		Handle::Handle(EHandle eID) : CBaseHandle(eID)
		{

		}
		Handle::~Handle()
		{

		}
		void Handle::Init()
		{
			AddElement(MAPID_AcasiaForest, -16638, -6737, 267, 64, 32, 0)->AddElement(MAPID_MushroomCave, 119112, 26028, 510);
			AddElement(MAPID_BambooForest, -3408, -12447, 251, 64, 32, 2)->AddElement(MAPID_BambooForest, -3265, -12583, 214);
			AddElement(MAPID_RicartenTown, 734, -20119, 312, 64, 32, 2)->AddElement(MAPID_RicartenTown, 822, -19956, 254);
			AddElement(MAPID_RicartenTown, 2597, -18243, 236, 32, 32, 0)->AddElement(MAPID_T5QuestArena, 198282, 240400, 1502);
			AddElement(MAPID_RuinenVillage, 4428, 22511, 845, 64, 32, 2)->AddElement(MAPID_RuinenVillage, 4547, 22616, 817);
			AddElement(MAPID_ForgottenLand, 16809, 15407, 501, 128, 32, 0)->AddElement(MAPID_AncientPrisonF1, -15395, -24185, 0);
			AddElement(MAPID_NaviskoTown, 21936, -1833, 855, 64, 32, 2)->AddElement(MAPID_NaviskoTown, 21826, -1712, 825);
			AddElement(MAPID_AncientsBattlefield, 36128, -2162, 804, 64, 32, 0)->AddElement(MAPID_CursedTempleF1, -11088, -41570, 343);
			AddElement(MAPID_ForbiddenLand, 33979, 6080, 969, 64, 32, 2)->AddElement(MAPID_ForbiddenLand, 34100, 6214, 940);
			AddElement(MAPID_AncientPrisonF1, -15388, -24073, 100, 64, 32, 0)->AddElement(MAPID_ForgottenLand, 16649, 15238, 501);
			AddElement(MAPID_AncientPrisonF1, -15305, -28824, 1, 64, 32, 0)->AddElement(MAPID_AncientPrisonF2, -6027, -26881, 99);
			AddElement(MAPID_AncientPrisonF2, -5908, -26878, 136, 64, 32, 0)->AddElement(MAPID_AncientPrisonF1, -15314, -28718, 58);
			AddElement(MAPID_AncientPrisonF2, -8019, -25768, 21, 64, 32, 0)->AddElement(MAPID_AncientPrisonF3, 1810, -28802, 0);
			AddElement(MAPID_AncientPrisonF2, -3918, -27988, 21, 64, 32, 0)->AddElement(MAPID_AncientPrisonF3, 1810, -28802, 0);

			{
				auto pElement = AddElement(MAPID_AncientPrisonF3, 1810, -28924, 0, 64, 32, 0);

				pElement->AddElement(MAPID_AncientPrisonF2, -8176, -25775, 77);
				pElement->AddElement(MAPID_AncientPrisonF2, -3738, -27990, 73);
			}

			AddElement(MAPID_LandOfDusk, -4730, 48107, 1173, 64, 32, 2)->AddElement(MAPID_LandOfDusk, -4615, 48002, 1146);
			AddElement(MAPID_LandOfDusk, -6306, 43241, 779, 64, 32, 0)->AddElement(MAPID_BeehiveCave, 119025, 35680, 499);

			AddElement(MAPID_RoadToTheWind, 1962, 71184, 559, 64, 32, 1)->AddElement(MAPID_PhillaiTown, 1993, 73134, 449);

			AddElement(MAPID_PhillaiTown, 2000, 72907, 474, 64, 32, 1)->AddElement(MAPID_RoadToTheWind, 1958, 70922, 536);
			AddElement(MAPID_PhillaiTown, 2245, 78259, 745, 64, 32, 2)->AddElement(MAPID_PhillaiTown, 2252, 78041, 754);

			AddElement(MAPID_CursedTempleF1, -10860, -41666, 398, 64, 32, 0)->AddElement(MAPID_AncientsBattlefield, 35872, -2016, 804);

			{
				auto pElement = AddElement(MAPID_CursedTempleF1, -12089, -40380, 95, 64, 32, 0);

				pElement->AddElement(MAPID_CursedTempleF2, -2527, -37196, 727);
				pElement->AddElement(MAPID_CursedTempleF2, -3669, -36444, 727);
				pElement->AddElement(MAPID_CursedTempleF2, -4795, -37198, 727);
			}

			AddElement(MAPID_CursedTempleF2, -3665, -36334, 762, 64, 32, 0)->AddElement(MAPID_CursedTempleF1, -12073, -40701, 95);
			AddElement(MAPID_CursedTempleF2, -4895, -37132, 762, 64, 32, 0)->AddElement(MAPID_CursedTempleF1, -12073, -40701, 95);
			AddElement(MAPID_CursedTempleF2, -2441, -37137, 762, 64, 32, 0)->AddElement(MAPID_CursedTempleF1, -12073, -40701, 95);

			{
				auto pElement = AddElement(MAPID_CursedTempleF2, -3207, -43830, 553, 128, 32, 0);

				pElement->AddElement(MAPID_CursedTempleF3, 3650, -45312, 116);
				pElement->AddElement(MAPID_CursedTempleF3, -3668, -50022, 3);
			}

			AddElement(MAPID_MushroomCave, 124391, 32913, 37, 80, 32, 0)->AddElement(MAPID_DarkSanctuary, 158627, 20504, 240);
			AddElement(MAPID_MushroomCave, 118869, 26017, 538, 80, 32, 0)->AddElement(MAPID_AcasiaForest, -16490, -6930, 298);

			AddElement(MAPID_BeehiveCave, 125581, 25086, 480, 80, 32, 0)->AddElement(MAPID_DarkSanctuary, 158543, 19557, 290);
			AddElement(MAPID_BeehiveCave, 118808, 35686, 520, 80, 32, 0)->AddElement(MAPID_LandOfDusk, -6056, 43245, 787);

			AddElement(MAPID_DarkSanctuary, 158042, 19525, 330, 120, 32, 0)->AddElement(MAPID_BeehiveCave, 124396, 33291, 37);
			AddElement(MAPID_DarkSanctuary, 158023, 20453, 240, 120, 32, 0)->AddElement(MAPID_MushroomCave, 125566, 24825, 480);

			AddElement(MAPID_Eura, 30407, 22232, 1349, 64, 32, 2)->AddElement(MAPID_Eura, 30610, 22164, 1304);

			AddElement(MAPID_GallubiaValley, 35361, 31898, 829, 80, 32, 0)->AddElement(MAPID_IceMineF1, 18006, -34698, 222);

			AddElement(MAPID_BlessCastle, 32527, -30693, 774, 64, 32, 2)->AddElement(MAPID_BlessCastle, 32739, -30474, 711);

			AddElement(MAPID_FrozenSanctuary, 37981, 50790, 1216, 64, 32, 0)->AddElement(MAPID_KelvezuLair, 33000, 50036, 1512);

			AddElement(MAPID_KelvezuLair, 33012, 49926, 1533, 64, 32, 0)->AddElement(MAPID_FrozenSanctuary, 37971, 50460, 1209);

			AddElement(MAPID_LandOfChaos, -12610, -1349, 694, 64, 32, 2)->AddElement(MAPID_LandOfChaos, -12555, -1113, 668);

			AddElement(MAPID_EndlessTowerF1, 14241, -41079, 220, 64, 32, 0)->AddElement(MAPID_EndlessTowerF2, 5255, -37897, 84);
			AddElement(MAPID_EndlessTowerF1, 14246, -38912, 220, 64, 32, 0)->AddElement(MAPID_LostTemple, -12272, 11299, 509);

			AddElement(MAPID_EndlessTowerF2, 5253, -37708, 69, 64, 32, 0)->AddElement(MAPID_EndlessTowerF1, 14242, -41199, 220);

			{
				auto pElement = AddElement(MAPID_EndlessTowerF2, 5254, -41500, 139, 64, 32, 0);

				pElement->AddElement(MAPID_EndlessTowerF3, 4896, -42220, 202);
				pElement->AddElement(MAPID_EndlessTowerF3, 6408, -42220, 202);
			}
			{
				auto pElement = AddElement(MAPID_CursedTempleF3, -3655, -50603, 3, 64, 32, 0);

				pElement->AddElement(MAPID_CursedTempleF2, -2851, -43792, 642);
				pElement->AddElement(MAPID_CursedTempleF2, -4422, -43801, 642);
			}
			{
				auto pElement = AddElement(MAPID_CursedTempleF3, -3664, -44886, 145, 64, 32, 0);

				pElement->AddElement(MAPID_CursedTempleF2, -2851, -43792, 642);
				pElement->AddElement(MAPID_CursedTempleF2, -4422, -43801, 642);
			}

			AddElement(MAPID_EndlessTowerF3, 4896, -42090, 230, 64, 32, 0)->AddElement(MAPID_EndlessTowerF2, 5254, -41361, 139);
			AddElement(MAPID_EndlessTowerF3, 6408, -42090, 230, 64, 32, 0)->AddElement(MAPID_EndlessTowerF2, 5254, -41361, 139);

			AddElement(MAPID_IceMineF1, 17944, -34641, 246, 64, 32, 0)->AddElement(MAPID_GallubiaValley, 35352, 31928, 829);

			AddElement(MAPID_SecretLaboratory, -12000, -54163, 374, 64, 32, 0)->AddElement(MAPID_AncientWeapon, 12788, -73633, 458);

			AddElement(MAPID_AncientWeapon, 12790, -74070, 458, 64, 32, 0)->AddElement(MAPID_MysteryDesert1, -37086, -4809, 1457);
			AddElement(MAPID_AncientWeapon, 12799, -62227, 530, 64, 32, 1)->AddElement(MAPID_AncientWeapon, 12772, -59917, 562);
			AddElement(MAPID_AncientWeapon, 12778, -60119, 578, 64, 32, 1)->AddElement(MAPID_AncientWeapon, 12700, -62387, 510);

			AddElement(MAPID_MysteryDesert1, -38593, 295, 1844, 64, 32, 0)->AddElement(MAPID_SecretLaboratory, -12000, -62800, 173);
			AddElement(MAPID_MysteryDesert1, -37290, -4816, 1457, 64, 32, 0)->AddElement(MAPID_AncientWeapon, 12790, -73882, 458);

			AddElement(MAPID_T5QuestArena, 198284, 240295, 1517, 64, 32, 0)->AddElement(MAPID_RicartenTown, 2604, -18130, 236);
		}
		void Handle::Shutdown()
		{
			for (auto &v : m_vpElement)
			{
				DELET(v);
			}

			m_vpElement.clear();
		}
		void Handle::Tick()
		{
			auto pElementIn = GetElement(lpCurPlayer->GetPosition());

			if (pElementIn)
			{
				int iLevel = lpCurPlayer->smCharInfo.Level;

				if (pElementIn->m_iType == 0)
				{
					auto pElement = pElementIn->GetElement();

					if (pElement)
					{
						if (iLevel >= GetMapLevel(pElement->m_eID))
						{
							// Translate to Map and Effect;
						}
						else
						{
							CTITLEBOX->SetText("No Enough Level");
						}
					}
				}
				else if (pElementIn->m_iType == 1)
				{
					auto pElement = pElementIn->GetElement();

					if (pElement)
					{
						if (iLevel >= GetMapLevel(pElement->m_eID))
						{
							// Translate to Map and Effect;
						}
						else
						{
							CTITLEBOX->SetText("No Enough Level");
						}
					}
				}
				else if (pElementIn->m_iType == 2)
				{
					if (!m_bHover)
					{
						//Show Window
						static_cast<Window *>(CGameCore::GetWindow(EWINDOW_WarpGate))->Show();

						m_bHover = TRUE;
					}
				}
			}
		}
		void Handle::SetWarpGate(EMapID eID)
		{
			if (m_bHover)
			{
				if (eID == MAPID_Invalid)
				{
					auto pElementIn = GetElement(lpCurPlayer->GetMap()->GetID(), 2);

					if (pElementIn)
					{
						auto pElement = pElementIn->GetElement();

						if (pElement)
						{
							//Translate Map();
						}
					}
				}
				else
				{
					auto pElementIn = GetElement(eID, 2);

					if (pElementIn)
					{
						int iLevel = lpCurPlayer->smCharInfo.Level;

						auto pElement = pElementIn->GetElement();

						if (pElement && iLevel >= GetMapLevel(pElement->m_eID))
						{
							//Translate Map and Effect()
						}
					}
				}

				m_bHover = FALSE;
			}
		}
		ElementIn *Handle::GetElement(EMapID eID, int iType)
		{
			for (auto &v : m_vpElement)
			{
				if (v->m_eID == eID && v->m_iType == iType)
					return v;
			}

			return nullptr;
		}
		ElementIn *Handle::GetElement(Point3D sPosition)
		{
			for (auto &v : m_vpElement)
			{
				if (v->IsInto(sPosition))
					return v;
			}

			return nullptr;
		}
		ElementIn *Handle::AddElement(EMapID eID, int iX, int iZ, int iY, int iWidth, int iHeight, int iType)
		{
			auto pElement = new ElementIn(eID, iX << 8, iZ << 8, iY << 8, iWidth, iHeight, iType);

			m_vpElement.push_back(pElement);

			return pElement;
		}*/
	}
}