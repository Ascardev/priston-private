#include "StdAfx.h"
#include "BorderHandle.h"

namespace MAP
{
	namespace BORDER
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
			AddElement(MAPID_AcasiaForest, MAPID_BambooForest, -8508, -10576);

			AddElement(MAPID_BambooForest, MAPID_GardenOfFreedom, -292, -9548);

			AddElement(MAPID_GardenOfFreedom, MAPID_RicartenTown, 2275, -14828);
			AddElement(MAPID_GardenOfFreedom, MAPID_RefugeOfTheAncients, 4844, -6835);

			AddElement(MAPID_RefugeOfTheAncients, MAPID_CastleOfTheLost, 410, 4902);

			AddElement(MAPID_CastleOfTheLost, MAPID_RuinenVillage, 3051, 16124);

			AddElement(MAPID_RuinenVillage, MAPID_ForgottenLand, 10019, 18031);
			AddElement(MAPID_RuinenVillage, MAPID_ForestOfSpirits, 4470, 27774);
			AddElement(MAPID_RuinenVillage, MAPID_GreedyLake, 12713, 23409);

			AddElement(MAPID_ForgottenLand, MAPID_CursedLand, 13319, 7102);

			AddElement(MAPID_CursedLand, MAPID_Oasis, 13466, -5953);
			AddElement(MAPID_CursedLand, MAPID_NaviskoTown, 20041, -892);

			AddElement(MAPID_NaviskoTown, MAPID_AncientsBattlefield, 27110, -479);
			AddElement(MAPID_NaviskoTown, MAPID_Bellatra, 21840, 1062);

			AddElement(MAPID_AncientsBattlefield, MAPID_ForbiddenLand, 34372, 4277);

			AddElement(MAPID_ForbiddenLand, MAPID_RailwayOfChaos, 44545, 13063);

			AddElement(MAPID_ForestOfSpirits, MAPID_LandOfDusk, -2949, 40442);

			AddElement(MAPID_LandOfDusk, MAPID_ValleyOfTranquility, -2349, 49830);

			AddElement(MAPID_ValleyOfTranquility, MAPID_RoadToTheWind, 667, 59371);

			AddElement(MAPID_RoadToTheWind, MAPID_PhillaiTown, -8508, -10576);

			AddElement(MAPID_RailwayOfChaos, MAPID_HeartOfPerum, 45316, 21407);

			AddElement(MAPID_HeartOfPerum, MAPID_Eura, 33618, 24011);

			AddElement(MAPID_Eura, MAPID_GallubiaValley, 31848, 27225);

			AddElement(MAPID_GallubiaValley, MAPID_FrozenSanctuary, 33729, 38029);

			AddElement(MAPID_LandOfChaos, MAPID_LostTemple, -11586, 7704);

			AddElement(MAPID_MysteryForest3, MAPID_MysteryForest2, -48393, -10526);

			AddElement(MAPID_MysteryForest2, MAPID_MysteryForest1, -40333, -9515);

			AddElement(MAPID_MysteryForest1, MAPID_Atlantis, -37653, -14972);
			AddElement(MAPID_MysteryForest1, MAPID_MysteryDesert1, -35228, -7397);

			AddElement(MAPID_BattleTown, MAPID_MysteryDesert3, -25122, 20938);
			AddElement(MAPID_BattleTown, MAPID_MiraRemains, -19022, 21052);

			AddElement(MAPID_MysteryDesert3, MAPID_MysteryDesert2, -32203, 15803);

			AddElement(MAPID_MysteryDesert2, MAPID_MysteryDesert1, -32225, 4508);
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
			auto pElement = GetElement(lpCurPlayer->GetPosition());

			if (pElement)
			{
				//Load(pElement->m_eCurID);
				//Load(pElement->m_eNexID)
			}
		}
		void Handle::AddElement(EMapID eOneID, EMapID eTwoID, int iX, int iZ, int iY)
		{
			m_vpElement.push_back(new Element(eOneID, eTwoID, iX << 8, iZ << 8, iY << 8));
		}
		Element *Handle::GetElement(Point3D sPosition)
		{
			for (auto &v : m_vpElement)
			{
				if (v->IsInto(sPosition))
					return v;
			}

			return nullptr;
		}*/
	}
}