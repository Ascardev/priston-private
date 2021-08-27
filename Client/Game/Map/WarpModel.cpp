#include "StdAfx.h"
#include "WarpModel.h"

namespace MAP
{
	namespace WARP
	{
		Model::Model() : m_eID(MAPID_Invalid)
		{

		}
		Model::~Model()
		{

		}
		void Model::Init()
		{
			AddIn(MAPID_AcasiaForest, -16638, -6737, 267, 64, 32, 0)->AddOut(MAPID_MushroomCave, 119112, 26028, 510);
			AddIn(MAPID_BambooForest, -3408, -12447, 251, 64, 32, 2)->AddOut(MAPID_BambooForest, -3265, -12583, 214);
			AddIn(MAPID_RicartenTown, 734, -20119, 312, 64, 32, 2)->AddOut(MAPID_RicartenTown, 822, -19956, 254);
			AddIn(MAPID_RicartenTown, 2597, -18243, 236, 32, 32, 0)->AddOut(MAPID_T5QuestArena, 198282, 240400, 1502);
			AddIn(MAPID_RuinenVillage, 4428, 22511, 845, 64, 32, 2)->AddOut(MAPID_RuinenVillage, 4547, 22616, 817);
			AddIn(MAPID_ForgottenLand, 16809, 15407, 501, 128, 32, 0)->AddOut(MAPID_AncientPrisonF1, -15395, -24185, 0);
			AddIn(MAPID_NaviskoTown, 21936, -1833, 855, 64, 32, 2)->AddOut(MAPID_NaviskoTown, 21826, -1712, 825);
			AddIn(MAPID_AncientsBattlefield, 36128, -2162, 804, 64, 32, 0)->AddOut(MAPID_CursedTempleF1, -11088, -41570, 343);
			AddIn(MAPID_ForbiddenLand, 33979, 6080, 969, 64, 32, 2)->AddOut(MAPID_ForbiddenLand, 34100, 6214, 940);
			AddIn(MAPID_AncientPrisonF1, -15388, -24073, 100, 64, 32, 0)->AddOut(MAPID_ForgottenLand, 16649, 15238, 501);
			AddIn(MAPID_AncientPrisonF1, -15305, -28824, 1, 64, 32, 0)->AddOut(MAPID_AncientPrisonF2, -6027, -26881, 99);
			AddIn(MAPID_AncientPrisonF2, -5908, -26878, 136, 64, 32, 0)->AddOut(MAPID_AncientPrisonF1, -15314, -28718, 58);
			AddIn(MAPID_AncientPrisonF2, -8019, -25768, 21, 64, 32, 0)->AddOut(MAPID_AncientPrisonF3, 1810, -28802, 0);
			AddIn(MAPID_AncientPrisonF2, -3918, -27988, 21, 64, 32, 0)->AddOut(MAPID_AncientPrisonF3, 1810, -28802, 0);

			{
				auto pIn = AddIn(MAPID_AncientPrisonF3, 1810, -28924, 0, 64, 32, 0);

				pIn->AddOut(MAPID_AncientPrisonF2, -8176, -25775, 77);
				pIn->AddOut(MAPID_AncientPrisonF2, -3738, -27990, 73);
			}

			AddIn(MAPID_LandOfDusk, -4730, 48107, 1173, 64, 32, 2)->AddOut(MAPID_LandOfDusk, -4615, 48002, 1146);
			AddIn(MAPID_LandOfDusk, -6306, 43241, 779, 64, 32, 0)->AddOut(MAPID_BeehiveCave, 119025, 35680, 499);

			AddIn(MAPID_RoadToTheWind, 1962, 71184, 559, 64, 32, 1)->AddOut(MAPID_PhillaiTown, 1993, 73134, 449);

			AddIn(MAPID_PhillaiTown, 2000, 72907, 474, 64, 32, 1)->AddOut(MAPID_RoadToTheWind, 1958, 70922, 536);
			AddIn(MAPID_PhillaiTown, 2245, 78259, 745, 64, 32, 2)->AddOut(MAPID_PhillaiTown, 2252, 78041, 754);

			AddIn(MAPID_CursedTempleF1, -10860, -41666, 398, 64, 32, 0)->AddOut(MAPID_AncientsBattlefield, 35872, -2016, 804);

			{
				auto pIn = AddIn(MAPID_CursedTempleF1, -12089, -40380, 95, 64, 32, 0);

				pIn->AddOut(MAPID_CursedTempleF2, -2527, -37196, 727);
				pIn->AddOut(MAPID_CursedTempleF2, -3669, -36444, 727);
				pIn->AddOut(MAPID_CursedTempleF2, -4795, -37198, 727);
			}

			AddIn(MAPID_CursedTempleF2, -3665, -36334, 762, 64, 32, 0)->AddOut(MAPID_CursedTempleF1, -12073, -40701, 95);
			AddIn(MAPID_CursedTempleF2, -4895, -37132, 762, 64, 32, 0)->AddOut(MAPID_CursedTempleF1, -12073, -40701, 95);
			AddIn(MAPID_CursedTempleF2, -2441, -37137, 762, 64, 32, 0)->AddOut(MAPID_CursedTempleF1, -12073, -40701, 95);

			{
				auto pIn = AddIn(MAPID_CursedTempleF2, -3207, -43830, 553, 128, 32, 0);

				pIn->AddOut(MAPID_CursedTempleF3, 3650, -45312, 116);
				pIn->AddOut(MAPID_CursedTempleF3, -3668, -50022, 3);
			}

			AddIn(MAPID_MushroomCave, 124391, 32913, 37, 80, 32, 0)->AddOut(MAPID_DarkSanctuary, 158627, 20504, 240);
			AddIn(MAPID_MushroomCave, 118869, 26017, 538, 80, 32, 0)->AddOut(MAPID_AcasiaForest, -16490, -6930, 298);

			AddIn(MAPID_BeehiveCave, 125581, 25086, 480, 80, 32, 0)->AddOut(MAPID_DarkSanctuary, 158543, 19557, 290);
			AddIn(MAPID_BeehiveCave, 118808, 35686, 520, 80, 32, 0)->AddOut(MAPID_LandOfDusk, -6056, 43245, 787);

			AddIn(MAPID_DarkSanctuary, 158042, 19525, 330, 120, 32, 0)->AddOut(MAPID_BeehiveCave, 124396, 33291, 37);
			AddIn(MAPID_DarkSanctuary, 158023, 20453, 240, 120, 32, 0)->AddOut(MAPID_MushroomCave, 125566, 24825, 480);

			AddIn(MAPID_Eura, 30407, 22232, 1349, 64, 32, 2)->AddOut(MAPID_Eura, 30610, 22164, 1304);

			AddIn(MAPID_GallubiaValley, 35361, 31898, 829, 80, 32, 0)->AddOut(MAPID_IceMineF1, 18006, -34698, 222);

			AddIn(MAPID_BlessCastle, 32527, -30693, 774, 64, 32, 2)->AddOut(MAPID_BlessCastle, 32739, -30474, 711);

			AddIn(MAPID_FrozenSanctuary, 37981, 50790, 1216, 64, 32, 0)->AddOut(MAPID_KelvezuLair, 33000, 50036, 1512);

			AddIn(MAPID_KelvezuLair, 33012, 49926, 1533, 64, 32, 0)->AddOut(MAPID_FrozenSanctuary, 37971, 50460, 1209);

			AddIn(MAPID_LandOfChaos, -12610, -1349, 694, 64, 32, 2)->AddOut(MAPID_LandOfChaos, -12555, -1113, 668);

			AddIn(MAPID_EndlessTowerF1, 14241, -41079, 220, 64, 32, 0)->AddOut(MAPID_EndlessTowerF2, 5255, -37897, 84);
			AddIn(MAPID_EndlessTowerF1, 14246, -38912, 220, 64, 32, 0)->AddOut(MAPID_LostTemple, -12272, 11299, 509);

			AddIn(MAPID_EndlessTowerF2, 5253, -37708, 69, 64, 32, 0)->AddOut(MAPID_EndlessTowerF1, 14242, -41199, 220);

			{
				auto pIn = AddIn(MAPID_EndlessTowerF2, 5254, -41500, 139, 64, 32, 0);

				pIn->AddOut(MAPID_EndlessTowerF3, 4896, -42220, 202);
				pIn->AddOut(MAPID_EndlessTowerF3, 6408, -42220, 202);
			}
			{
				auto pIn = AddIn(MAPID_CursedTempleF3, -3655, -50603, 3, 64, 32, 0);
				pIn->AddOut(MAPID_CursedTempleF2, -2851, -43792, 642);
				pIn->AddOut(MAPID_CursedTempleF2, -4422, -43801, 642);
			}
			{
				auto pIn = AddIn(MAPID_CursedTempleF3, -3664, -44886, 145, 64, 32, 0);
				pIn->AddOut(MAPID_CursedTempleF2, -2851, -43792, 642);
				pIn->AddOut(MAPID_CursedTempleF2, -4422, -43801, 642);
			}

			AddIn(MAPID_EndlessTowerF3, 4896, -42090, 230, 64, 32, 0)->AddOut(MAPID_EndlessTowerF2, 5254, -41361, 139);
			AddIn(MAPID_EndlessTowerF3, 6408, -42090, 230, 64, 32, 0)->AddOut(MAPID_EndlessTowerF2, 5254, -41361, 139);

			AddIn(MAPID_IceMineF1, 17944, -34641, 246, 64, 32, 0)->AddOut(MAPID_GallubiaValley, 35352, 31928, 829);

			AddIn(MAPID_SecretLaboratory, -12000, -54163, 374, 64, 32, 0)->AddOut(MAPID_AncientWeapon, 12788, -73633, 458);

			AddIn(MAPID_AncientWeapon, 12790, -74070, 458, 64, 32, 0)->AddOut(MAPID_MysteryDesert1, -37086, -4809, 1457);
			AddIn(MAPID_AncientWeapon, 12799, -62227, 530, 64, 32, 1)->AddOut(MAPID_AncientWeapon, 12772, -59917, 562);
			AddIn(MAPID_AncientWeapon, 12778, -60119, 578, 64, 32, 1)->AddOut(MAPID_AncientWeapon, 12700, -62387, 510);

			AddIn(MAPID_MysteryDesert1, -38593, 295, 1844, 64, 32, 0)->AddOut(MAPID_SecretLaboratory, -12000, -62800, 173);
			AddIn(MAPID_MysteryDesert1, -37290, -4816, 1457, 64, 32, 0)->AddOut(MAPID_AncientWeapon, 12790, -73882, 458);

			AddIn(MAPID_T5QuestArena, 198284, 240295, 1517, 64, 32, 0)->AddOut(MAPID_RicartenTown, 2604, -18130, 236);
		}
		void Model::Update()
		{
			auto pcMap = lpCurPlayer->GetMap();

			if (pcMap)
			{
				auto pIn = GetIn(pcMap->GetID());

				if (pIn && pIn->IsIn(lpCurPlayer->GetPosition()))
				{
					int iLevel = lpCurPlayer->smCharInfo.Level;
					// Norml WarpGate
					if (pIn->iType == 0)
					{
						auto pOut = pIn->GetOut();

						if (pOut)
						{
							if (iLevel >= GetMapLevel(pOut->eID))
							{
								// Translate to Map and Effect;
							}
							else
							{
								MESSAGEBOXTITLE->AddTextEx("No Enough Level");
							}
						}
					}
					//1 v 1 WarpGate
					else if (pIn->iType == 1)
					{
						auto pOut = pIn->GetOut();

						if (pOut)
						{
							if (iLevel >= GetMapLevel(pOut->eID))
							{
								// Translate to Map and Effect;
							}
							else
							{
								MESSAGEBOXTITLE->AddTextEx("No Enough Level");
							}
						}
					}
					// Multi WarpGate
					else if (pIn->iType == 2)
					{
						// Is Select ?
						if (m_eID != MAPID_Invalid)
						{
							// Show Window
						}
						else if (m_eID == pcMap->GetID())
						{
							auto pOut = pIn->GetOut();

							if (pOut)
							{
								// No Effect Translate Self Map

								m_eID = MAPID_Invalid;
							}
						}
						else
						{
							// Get Click WarpGate
							pIn = GetIn(m_eID);

							auto pOut = pIn ? pIn->GetOut() : nullptr;

							if (pOut && iLevel >= GetMapLevel(pOut->eID))
							{
								// Have Effect Translate

								m_eID = MAPID_Invalid;
							}
						}
					}
				}
			}
		}
		In *Model::GetIn(EMapID eID)
		{
			for (auto &v : m_vpIn)
			{
				if (v && v->eID == eID)
					return v;
			}

			return nullptr;
		}
		In *Model::AddIn(EMapID eID, int iX, int iZ, int iY, int iWidth, int iHeight, int iType)
		{
			auto pIn = new In(eID, iX << 8, iZ << 8, iY << 8, iWidth, iHeight, iType);

			m_vpIn.push_back(pIn);

			return pIn;
		}
	}
}