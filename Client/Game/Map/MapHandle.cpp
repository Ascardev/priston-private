#include "StdAfx.h"
#include "MapHandle.h"

namespace MAP
{
	Handle::Handle() : CBaseHandle()
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
		auto pcAcasiaForest = Add(new Info(MAPID_AcasiaForest, "Acasia Forest"));
		auto pcBambooForest = Add(new Info(MAPID_BambooForest, "Bamboo Forest"));
		auto pcGardenOfFreedom = Add(new Info(MAPID_GardenOfFreedom, "Garden of Freedom"));
		auto pcRicartenTown = Add(new Info(MAPID_RicartenTown, "Ricarten Town"));
		auto pcRefugeOfTheAncients = Add(new Info(MAPID_RefugeOfTheAncients, "Refuge of the Ancients"));
		auto pcCastleOfTheLost = Add(new Info(MAPID_CastleOfTheLost, "Castle of the Lost"));
		auto pcRuinenVillage = Add(new Info(MAPID_RuinenVillage, "Ruinen Village"));
		auto pcForgottenLand = Add(new Info(MAPID_ForgottenLand, "Forgotten Land"));
		auto pcCursedLand = Add(new Info(MAPID_CursedLand, "Cursed Land"));
		auto pcNaviskoTown = Add(new Info(MAPID_NaviskoTown, "Navisko Town"));
		auto pcOasis = Add(new Info(MAPID_Oasis, "Oasis"));
		auto pcBattlefieldOfTheAncients = Add(new Info(MAPID_AncientsBattlefield, "Battlefield of the Ancients"));
		auto pcForbiddenLand = Add(new Info(MAPID_ForbiddenLand, "Forbidden Land"));
		auto pcAncientPrisonF1 = Add(new Info(MAPID_AncientPrisonF1, "Ancient Prison 1F"));
		auto pcAncientPrisonF2 = Add(new Info(MAPID_AncientPrisonF2, "Ancient Prison 2F"));
		auto pcAncientPrisonF3 = Add(new Info(MAPID_AncientPrisonF3, "Ancient Prison 3F"));
		auto pcChessRoom = Add(new Info(MAPID_ChessRoom, "Checker (GM) Room"));
		auto pcForestOfSpirits = Add(new Info(MAPID_ForestOfSpirits, "Forest of Spirits"));
		auto pcLandOfDusk = Add(new Info(MAPID_LandOfDusk, "Land of Dusk"));
		auto pcValleyOfTranquility = Add(new Info(MAPID_ValleyOfTranquility, "Valley of Tranquility"));
		auto pcRoadToTheWind = Add(new Info(MAPID_RoadToTheWind, "Road to the Wind"));
		auto pcPhillaiTown = Add(new Info(MAPID_PhillaiTown, "Pillia Town"));
		auto pcCursedTempleF1 = Add(new Info(MAPID_CursedTempleF1, "Cursed Temple 1F"));
		auto pcCursedTempleF2 = Add(new Info(MAPID_CursedTempleF2, "Cursed Temple 2F"));
		auto pcMushroomCave = Add(new Info(MAPID_MushroomCave, "Cave of Mushrooms"));
		auto pcBeehiveCave = Add(new Info(MAPID_BeehiveCave, "Cave of Beehive"));
		auto pcDarkSanctuary = Add(new Info(MAPID_DarkSanctuary, "Sanctuary of Darkness"));
		auto pcRailwayOfChaos = Add(new Info(MAPID_RailwayOfChaos, "Railway of Chaos"));
		auto pcHeartOfPerum = Add(new Info(MAPID_HeartOfPerum, "Heart of Perum"));
		auto pcEura = Add(new Info(MAPID_Eura, "Eura"));
		auto pcBellatra = Add(new Info(MAPID_Bellatra, "Bellatra Celestial"));
		auto pcGallubiaValley = Add(new Info(MAPID_GallubiaValley, "Gallubia Valley"));
		auto pcQuestArena = Add(new Info(MAPID_QuestArena, "Quest Arena"));
		auto pcBlessCastle = Add(new Info(MAPID_BlessCastle, "Bless Castle"));
		auto pcGreedyLake = Add(new Info(MAPID_GreedyLake, "Greedy Lake"));
		auto pcFrozenSanctuary = Add(new Info(MAPID_FrozenSanctuary, "Frozen Temple"));
		auto pcKelvezuLair = Add(new Info(MAPID_KelvezuLair, "Fire Map"));
		auto pcLandOfChaos = Add(new Info(MAPID_LandOfChaos, "Lost Island"));
		auto pcLostTemple = Add(new Info(MAPID_LostTemple, "Lost Temple"));
		auto pcDistortedForest = Add(new Info(MAPID_GhostCastle, "Ghost Castle"));
		auto pcEndlessTowerF1 = Add(new Info(MAPID_EndlessTowerF1, "Endless Tower 1F"));
		auto pcEndlessTowerF2 = Add(new Info(MAPID_EndlessTowerF2, "Endless Tower 2F"));
		auto pcCursedTempleF3 = Add(new Info(MAPID_CursedTempleF3, "Cursed Temple 3F"));
		auto pcEndlessTowerF3 = Add(new Info(MAPID_EndlessTowerF3, "Endless Tower 3F"));
		auto pcIceMineF1 = Add(new Info(MAPID_IceMineF1, "Ice Mine 1F"));
		auto pcSlab = Add(new Info(MAPID_SecretLaboratory, "Secret Laboratory"));
		auto pcAncientWeapon = Add(new Info(MAPID_AncientWeapon, "Anciient Weapon"));
		auto pcShipyardRuins = Add(new Info(MAPID_ShipyardRuins, "Shipyard Ruins"));
		auto pcMysteryForest3 = Add(new Info(MAPID_MysteryForest3, "Mystery Forest 3"));
		auto pcMysteryForest2 = Add(new Info(MAPID_MysteryForest2, "Mystery Forest 2"));
		auto pcMysteryForest1 = Add(new Info(MAPID_MysteryForest1, "Mystery Forest 1"));
		auto pcAtlantisTown = Add(new Info(MAPID_Atlantis, "Atlantis Town"));
		auto pcBattleTown = Add(new Info(MAPID_BattleTown, "Battle Town"));
		auto pcMysteryDesert3 = Add(new Info(MAPID_MysteryDesert3, "Mystery Desert 3"));
		auto pcMysteryDesert2 = Add(new Info(MAPID_MysteryDesert2, "Mystery Desert 2"));
		auto pcMysteryDesert1 = Add(new Info(MAPID_MysteryDesert1, "Mystery Desert 1"));
		auto pcMiraRemains = Add(new Info(MAPID_MiraRemains, "Mira Remains"));
		auto pcT5QuestArena = Add(new Info(MAPID_T5QuestArena, "T5 Quest Arena"));

		// ½ºÖ®ÁÖ
		pcAcasiaForest->SetTerrainFile("Field\\Forest\\fore-3.ase");
		pcAcasiaForest->SetMiniMapFile("Field\\Map\\fore-3.tga", "Field\\Title\\fore-3t.tga");
		pcAcasiaForest->SetType(MAPTYPE_Forest);
		pcAcasiaForest->SetSky(MAPSKY_Forest_Morning, MAPSKY_Forest_Noon, MAPSKY_Forest_Night);
		pcAcasiaForest->SetBackgroundMusic(BACKGROUNDMUSICID_Forest);
		pcAcasiaForest->AddSpawn(-16419, -7054);
		pcAcasiaForest->AddSpawn(-10585, -11810);
		pcAcasiaForest->AddSpawn(-13659, -9753);
		pcAcasiaForest->AddWarpGate(-16638, -6737, 267, 64, 32, 0)->Add(MAPID_MushroomCave, 119112, 26028, 510);
		pcAcasiaForest->AddBorder(MAPID_BambooForest, -8508, -10576);
		pcAcasiaForest->AddSound(-13819, 226, -8950, 100, 15);

		for (int i = 1; i <= 14; i++)
		{
			pcAcasiaForest->AddModelEx("Field\\Forset\\3ani-%02d.ase", i);
		}

		// ÖñÖ®ÁÖ
		pcBambooForest->SetTerrainFile("Field\\Forest\\fore-2.ase");
		pcBambooForest->SetMiniMapFile("Field\\Map\\fore-2.tga", "Field\\Title\\fore-2t.tga");
		pcBambooForest->SetType(MAPTYPE_Forest);
		pcBambooForest->SetSky(MAPSKY_Forest_Morning, MAPSKY_Forest_Noon, MAPSKY_Forest_Night);
		pcBambooForest->SetBackgroundMusic(BACKGROUNDMUSICID_Forest);
		pcBambooForest->AddSpawn(-5427, -9915);
		pcBambooForest->AddSpawn(-2272, -10314);
		pcBambooForest->AddSpawn(-7192, -11175);
		pcBambooForest->AddSound(-3775, 171, -14447, 160, 13);
		pcBambooForest->AddBorder(MAPID_AcasiaForest, -8508, -10576);
		pcBambooForest->AddBorder(MAPID_GardenOfFreedom, -292, -9548);
		pcBambooForest->AddWarpGate(-3408, -12447, 251, 64, 32, 2)->Add(MAPID_BambooForest, -3265, -12583, 214);
		pcBambooForest->AddStaticModel("Field\\Forset\\2ani-04.ase");

		// ×ÔÓÉÍ¥Ôº
		pcGardenOfFreedom->SetTerrainFile("Field\\Forest\\fore-1.ase");
		pcGardenOfFreedom->SetMiniMapFile("Field\\Map\\fore-1.tga", "Field\\Title\\fore-1t.tga");
		pcGardenOfFreedom->SetType(MAPTYPE_Forest);
		pcGardenOfFreedom->SetSky(MAPSKY_Forest_Morning, MAPSKY_Forest_Noon, MAPSKY_Forest_Night);
		pcGardenOfFreedom->SetBackgroundMusic(BACKGROUNDMUSICID_Forest);
		pcGardenOfFreedom->AddSpawn(4184, -11016);
		pcGardenOfFreedom->AddSpawn(1350, -13672);
		pcGardenOfFreedom->AddSpawn(1761, -10815);
		pcGardenOfFreedom->AddSpawn(4777, -10916);
		pcGardenOfFreedom->AddBorder(MAPID_BambooForest, -292, -9548);
		pcGardenOfFreedom->AddBorder(MAPID_RefugeOfTheAncients, 4844, -6835);
		pcGardenOfFreedom->AddBorder(MAPID_RicartenTown, 2275, -14828);

		// Àí²éµÇ
		pcRicartenTown->SetTerrainFile("Field\\Ricarten\\village-2.ase");
		pcRicartenTown->SetMiniMapFile("Field\\Map\\village-2.tga", "Field\\Title\\village-2t.tga");
		pcRicartenTown->SetType(MAPTYPE_Town);
		pcRicartenTown->SetSky(MAPSKY_Forest_Morning, MAPSKY_Forest_Noon, MAPSKY_Forest_Night);
		pcRicartenTown->SetBackgroundMusic(BACKGROUNDMUSICID_Ricarten);
		pcRicartenTown->AddSpawn(2596, -18738);
		pcRicartenTown->AddSpawn(2592, -18566);
		pcRicartenTown->AddSpawn(-1047, -16973);
		pcRicartenTown->AddSound(-1006, 170, -17835, 80, 27);
		pcRicartenTown->AddSound(2632, 321, -17285, 80, 27);
		pcRicartenTown->AddWarpGate(734, -20119, 312, 64, 32, 2)->Add(MAPID_RicartenTown, 822, -19956, 254);
		pcRicartenTown->AddWarpGate(2597, -18243, 236, 32, 32, 0)->Add(MAPID_T5QuestArena, 198282, 240400, 1502);
		pcRicartenTown->AddBorder(MAPID_GardenOfFreedom, 2275, -14828);

		for (int i = 1; i <= 14; i++)
		{
			pcRicartenTown->AddModelEx("Field\\Ricarten\\v-ani%02d.ase", i);
		}

		// ·ÏÐæÄ¹µØ
		pcRefugeOfTheAncients->SetTerrainFile("Field\\Ruin\\ruin-4.ase");
		pcRefugeOfTheAncients->SetMiniMapFile("Field\\Map\\ruin-4.tga", "Field\\Title\\ruin-4t.tga");
		pcRefugeOfTheAncients->SetType(MAPTYPE_Wasteland);
		pcRefugeOfTheAncients->SetSky(MAPSKY_Wasteland_Morning1, MAPSKY_Wasteland_Noon, MAPSKY_Wasteland_Night);
		pcRefugeOfTheAncients->SetBackgroundMusic(BACKGROUNDMUSICID_DesertB);
		pcRefugeOfTheAncients->AddSpawn(1384, -918);
		pcRefugeOfTheAncients->AddSpawn(2578, -5124);
		pcRefugeOfTheAncients->AddSpawn(1873, 3060);
		pcRefugeOfTheAncients->AddBorder(MAPID_CastleOfTheLost, 410, 4902);
		pcRefugeOfTheAncients->AddBorder(MAPID_GardenOfFreedom, 4844, -6835);

		// ·ÏÐæ
		pcCastleOfTheLost->SetTerrainFile("Field\\Ruin\\ruin-3.ase");
		pcCastleOfTheLost->SetMiniMapFile("Field\\Map\\ruin-3.tga", "Field\\Title\\ruin-3t.tga");
		pcCastleOfTheLost->SetType(MAPTYPE_Wasteland);
		pcCastleOfTheLost->SetSky(MAPSKY_Wasteland_Morning1, MAPSKY_Wasteland_Noon, MAPSKY_Wasteland_Night);
		pcCastleOfTheLost->SetBackgroundMusic(BACKGROUNDMUSICID_DesertB);
		pcCastleOfTheLost->AddSpawn(4953, 10922);
		pcCastleOfTheLost->AddSpawn(875, 7910);
		pcCastleOfTheLost->AddSpawn(1576, 14307);
		pcCastleOfTheLost->AddBorder(MAPID_RuinenVillage, 3051, 16124);
		pcCastleOfTheLost->AddBorder(MAPID_RefugeOfTheAncients, 410, 4902);

		// ·ÏÐæ´å×¯
		pcRuinenVillage->SetTerrainFile("Field\\Ruin\\ruin-2.ase");
		pcRuinenVillage->SetMiniMapFile("Field\\Map\\ruin-2.tga", "Field\\Title\\ruin-2t.tga");
		pcRuinenVillage->SetType(MAPTYPE_Wasteland);
		pcRuinenVillage->SetSky(MAPSKY_Wasteland_Morning2, MAPSKY_Wasteland_Noon, MAPSKY_Wasteland_Night);
		pcRuinenVillage->SetBackgroundMusic(BACKGROUNDMUSICID_DesertB);
		pcRuinenVillage->AddSpawn(7459, 23984);
		pcRuinenVillage->AddSpawn(3976, 19645);
		pcRuinenVillage->AddSpawn(5832, 23751);
		pcRuinenVillage->AddSpawn(5615, 25117);
		pcRuinenVillage->AddWarpGate(4428, 22511, 845, 64, 32, 2)->Add(MAPID_RuinenVillage, 4547, 22616, 817);
		pcRuinenVillage->AddBorder(MAPID_ForgottenLand, 10019, 18031);
		pcRuinenVillage->AddBorder(MAPID_ForestOfSpirits, 4470, 27774);
		pcRuinenVillage->AddBorder(MAPID_GreedyLake, 12713, 23409);
		pcRuinenVillage->AddBorder(MAPID_CastleOfTheLost, 3051, 16124);
		pcRuinenVillage->AddStaticModel("Field\\Ruin\\ruin_ani01.ase");

		// ÒÅÍüÖ®µØ
		pcForgottenLand->SetTerrainFile("Field\\Ruin\\ruin-1.ase");
		pcForgottenLand->SetMiniMapFile("Field\\Map\\ruin-1.tga", "Field\\Title\\ruin-1t.tga");
		pcForgottenLand->SetType(MAPTYPE_Wasteland);
		pcForgottenLand->SetSky(MAPSKY_Wasteland_Morning2, MAPSKY_Wasteland_Noon, MAPSKY_Wasteland_Night);
		pcForgottenLand->SetBackgroundMusic(BACKGROUNDMUSICID_DesertB);
		pcForgottenLand->AddSpawn(16362, 14959);
		pcForgottenLand->AddSpawn(12242, 16034);
		pcForgottenLand->AddSpawn(12194, 8969);
		pcForgottenLand->AddWarpGate(16809, 15407, 501, 128, 32, 0)->Add(MAPID_AncientPrisonF1, -15395, -24185, 0);
		pcForgottenLand->AddBorder(MAPID_CursedLand, 13319, 7102);
		pcForgottenLand->AddBorder(MAPID_RuinenVillage, 10019, 18031);

		// ×çÖäÖ®µØ
		pcCursedLand->SetTerrainFile("Field\\Desert\\De-1.ase");
		pcCursedLand->SetMiniMapFile("Field\\Map\\De-1.tga", "Field\\Title\\De-1t.tga");
		pcCursedLand->SetType(MAPTYPE_Desert);
		pcCursedLand->SetSky(MAPSKY_Desert_Morning, MAPSKY_Desert_Noon, MAPSKY_Desert_Night);
		pcCursedLand->SetBackgroundMusic(BACKGROUNDMUSICID_DesertB);
		pcCursedLand->AddSpawn(15005, -1421);
		pcCursedLand->AddSpawn(13306, 2000);
		pcCursedLand->AddSpawn(13083, -2249);
		pcCursedLand->AddBorder(MAPID_Oasis, 13466, -5953);
		pcCursedLand->AddBorder(MAPID_NaviskoTown, 20041, -892);
		pcCursedLand->AddBorder(MAPID_ForgottenLand, 13319, 7102);

		// ÄÚÎ¬Ë¹¿Ë
		pcNaviskoTown->SetTerrainFile("Field\\Forest\\village-1.ase");
		pcNaviskoTown->SetMiniMapFile("Field\\Map\\village-1.tga", "Field\\Title\\village-1t.tga");
		pcNaviskoTown->SetType(MAPTYPE_Desert);
		pcNaviskoTown->SetSky(MAPSKY_Desert_Morning, MAPSKY_Desert_Noon, MAPSKY_Desert_Night);
		pcNaviskoTown->SetBackgroundMusic(BACKGROUNDMUSICID_Navisko);
		pcNaviskoTown->AddSpawn(22214, -1182);
		pcNaviskoTown->AddSpawn(22214, -1182);
		pcNaviskoTown->AddStaticModel("Field\\forest\\v2-ani01.ase");
		pcNaviskoTown->AddWarpGate(21936, -1833, 855, 64, 32 , 2)->Add(MAPID_NaviskoTown, 21826, -1712, 825);
		pcNaviskoTown->AddBorder(MAPID_AncientsBattlefield, 27110, -479);
		pcNaviskoTown->AddBorder(MAPID_Bellatra, 21840, 1062);
		pcNaviskoTown->AddBorder(MAPID_CursedLand, 20041, -892);

		// ÂÌÖÞ
		pcOasis->SetTerrainFile("Field\\Desert\\De-2.ase");
		pcOasis->SetMiniMapFile("Field\\Map\\De-2.tga", "Field\\Title\\De-2t.tga");
		pcOasis->SetType(MAPTYPE_Desert);
		pcOasis->SetSky(MAPSKY_Desert_Morning, MAPSKY_Desert_Noon, MAPSKY_Desert_Night);
		pcOasis->SetBackgroundMusic(BACKGROUNDMUSICID_DesertB);
		pcOasis->AddSpawn(15887, -11161);
		pcOasis->AddSpawn(11859, -11257);
		pcOasis->AddSpawn(16169, -12768);
		pcOasis->AddBorder(MAPID_CursedLand, 13466, -5953);

		// ¹Å´úÕ½³¡
		pcBattlefieldOfTheAncients->SetTerrainFile("Field\\Desert\\De-3.ase");
		pcBattlefieldOfTheAncients->SetMiniMapFile("Field\\Map\\De-3.tga", "Field\\Title\\De-3t.tga");
		pcBattlefieldOfTheAncients->SetType(MAPTYPE_Desert);
		pcBattlefieldOfTheAncients->SetSky(MAPSKY_Desert_Morning, MAPSKY_Desert_Noon, MAPSKY_Desert_Night);
		pcBattlefieldOfTheAncients->SetBackgroundMusic(BACKGROUNDMUSICID_DesertB);
		pcBattlefieldOfTheAncients->AddSpawn(34758, -1323);
		pcBattlefieldOfTheAncients->AddSpawn(34758, -1323);
		pcBattlefieldOfTheAncients->AddSpawn(29424, 322);
		pcBattlefieldOfTheAncients->AddWarpGate(36128, -2162, 804, 64, 32, 0)->Add(MAPID_CursedTempleF1, -11088, -41570, 343);
		pcBattlefieldOfTheAncients->AddBorder(MAPID_ForbiddenLand, 34372, 4277);
		pcBattlefieldOfTheAncients->AddBorder(MAPID_NaviskoTown, 27110, -479);

		// ·âÓ¡Ö®µØ
		pcForbiddenLand->SetTerrainFile("Field\\Desert\\De-4.ase");
		pcForbiddenLand->SetMiniMapFile("Field\\Map\\De-4.tga", "Field\\Title\\De-4t.tga");
		pcForbiddenLand->SetType(MAPTYPE_Desert);
		pcForbiddenLand->SetSky(MAPSKY_Desert_Morning, MAPSKY_Desert_Noon, MAPSKY_Desert_Night);
		pcForbiddenLand->SetBackgroundMusic(BACKGROUNDMUSICID_DesertB);
		pcForbiddenLand->AddSpawn(43988, 12053);
		pcForbiddenLand->AddSpawn(33740, 6491);
		pcForbiddenLand->AddSpawn(40691, 11056);
		pcForbiddenLand->AddWarpGate(33979, 6080, 969, 64, 32, 2)->Add(MAPID_ForbiddenLand, 34100, 6214, 940);
		pcForbiddenLand->AddStaticModel("Field\\desert\\d4-ani01.ase");
		pcForbiddenLand->AddBorder(MAPID_RailwayOfChaos, 44545, 13063);
		pcForbiddenLand->AddBorder(MAPID_AncientsBattlefield, 34372, 4277);

		// ¹Å´úµØÀÎ1
		pcAncientPrisonF1->SetTerrainFile("Field\\Dungeon\\dun-1.ase");
		pcAncientPrisonF1->SetMiniMapFile("Field\\Map\\dun-1.tga", "Field\\Title\\dun-1t.tga");
		pcAncientPrisonF1->SetType(MAPTYPE_Dungeon);
		pcAncientPrisonF1->SetBackgroundMusic(BACKGROUNDMUSICID_Dungeon);
		pcAncientPrisonF1->AddStaticModel("Field\\dungeon\\dun-1-wheel.ase");
		pcAncientPrisonF1->AddSpawn(-15384, -24310);
		pcAncientPrisonF1->AddWarpGate(-15388, -24073, 100, 64, 32, 0)->Add(MAPID_ForgottenLand, 16649, 15238, 501);
		pcAncientPrisonF1->AddWarpGate(-15305, -28824, 1, 64, 32, 0)->Add(MAPID_AncientPrisonF2, -6027, -26881, 99);
		pcAncientPrisonF1->AddSound(-15385, 100, -24949, 128, 0);

		// ¹Å´úµØÀÎ2
		pcAncientPrisonF2->SetTerrainFile("Field\\Dungeon\\dun-2.ase");
		pcAncientPrisonF2->SetMiniMapFile("Field\\Map\\dun-2.tga", "Field\\Title\\dun-2t.tga");
		pcAncientPrisonF2->SetType(MAPTYPE_Dungeon);
		pcAncientPrisonF2->SetBackgroundMusic(BACKGROUNDMUSICID_Dungeon);
		pcAncientPrisonF2->AddSpawn(-6108, -26880);
		pcAncientPrisonF2->AddWarpGate(-5908, -26878, 136, 64, 32, 0)->Add(MAPID_AncientPrisonF1, -15314, -28718, 58);
		pcAncientPrisonF2->AddWarpGate(-8019, -25768, 21, 64, 32, 0)->Add(MAPID_AncientPrisonF3, 1810, -28802, 0);
		pcAncientPrisonF2->AddWarpGate(-3918, -27988, 21, 64, 32, 0)->Add(MAPID_AncientPrisonF3, 1810, -28802, 0);

		// ¹Å´úµØÀÎ3
		pcAncientPrisonF3->SetTerrainFile("Field\\Dungeon\\dun-3.ase");
		pcAncientPrisonF3->SetMiniMapFile("Field\\Map\\dun-3.tga", "Field\\Title\\dun-3t.tga");
		pcAncientPrisonF3->SetType(MAPTYPE_Dungeon);
		pcAncientPrisonF3->SetBackgroundMusic(BACKGROUNDMUSICID_Dungeon);
		pcAncientPrisonF3->AddSpawn(1827, -28586);

		{
			auto pWarpGate = pcAncientPrisonF3->AddWarpGate(1810, -28924, 0, 64, 32, 0);

			pWarpGate->Add(MAPID_AncientPrisonF2, -8176, -25775, 77);
			pWarpGate->Add(MAPID_AncientPrisonF2, -3738, -27990, 73);
		}

		// GM·¿¼ä
		pcChessRoom->SetTerrainFile("Field\\Room\\office.ase");
		pcChessRoom->SetType(MAPTYPE_ChessRoom);
		pcChessRoom->SetBackgroundMusic(BACKGROUNDMUSICID_Forest);
		pcChessRoom->AddSpawn(-200000, 200000);

		// »Æ»èÊ÷ÁÖ
		pcForestOfSpirits->SetTerrainFile("Field\\Forever-fall\\forever-fall-04.ase");
		pcForestOfSpirits->SetMiniMapFile("Field\\Map\\forever-fall-04.tga", "Field\\Title\\forever-fall-04t.tga");
		pcForestOfSpirits->SetType(MAPTYPE_Forest);
		pcForestOfSpirits->SetSky(MAPSKY_ForFAll_Morning, MAPSKY_ForFAll_Noon, MAPSKY_ForFAll_Night);
		pcForestOfSpirits->SetBackgroundMusic(BACKGROUNDMUSICID_Forest);
		pcForestOfSpirits->AddSpawn(-1583, 37905);
		pcForestOfSpirits->AddSpawn(-2135, 33668);
		pcForestOfSpirits->AddSpawn(4073, 32119);
		pcForestOfSpirits->AddSound(-1448, 827, 34188, 160, 7);
		pcForestOfSpirits->AddSound(618, 531, 35981, 160, 7);
		pcForestOfSpirits->AddSound(2282, 537, 32355, 160, 20);
		pcForestOfSpirits->AddSound(2597, 793, 30745, 0, 20);
		pcForestOfSpirits->AddSound(2562, 641, 32726, 0, 20);
		pcForestOfSpirits->AddSound(3789, 770, 30062, 0, 20);
		pcForestOfSpirits->AddSound(3698, 909, 34179, 60, 14);
		pcForestOfSpirits->AddBorder(MAPID_LandOfDusk, -2949, 40442);
		pcForestOfSpirits->AddBorder(MAPID_RuinenVillage, 4470, 27774);

		for (int i = 1; i <= 11; i++)
		{
			pcForestOfSpirits->AddModelEx("Field\\forever-fall\\4ani-%02d.ase", i);
		}

		// ÐÄÇéÊ÷ÁÖ
		pcLandOfDusk->SetTerrainFile("Field\\Forever-fall\\forever-fall-03.ase");
		pcLandOfDusk->SetMiniMapFile("Field\\Map\\forever-fall-03.tga", "Field\\Title\\forever-fall-03t.tga");
		pcLandOfDusk->SetType(MAPTYPE_Forest);
		pcLandOfDusk->SetSky(MAPSKY_ForFAll_Morning, MAPSKY_ForFAll_Noon, MAPSKY_ForFAll_Night);
		pcLandOfDusk->SetBackgroundMusic(BACKGROUNDMUSICID_Forest);
		pcLandOfDusk->AddSpawn(-5823, 43244);
		pcLandOfDusk->AddSpawn(-1516, 45437);
		pcLandOfDusk->AddSpawn(-3586, 42886);
		pcLandOfDusk->AddSound(-3573, 861, 42603, 0, 15);
		pcLandOfDusk->AddSound(-2160, 943, 42588, 0, 19);
		pcLandOfDusk->AddWarpGate(-4730, 48107, 1173, 64, 32, 2)->Add(MAPID_LandOfDusk, -4615, 48002, 1146);
		pcLandOfDusk->AddWarpGate(-6306, 43241, 779, 64, 32, 0)->Add(MAPID_BeehiveCave, 119025, 35680, 499);
		pcLandOfDusk->AddBorder(MAPID_ValleyOfTranquility, -2349, 49830);
		pcLandOfDusk->AddBorder(MAPID_ForestOfSpirits, -2949, 40442);

		for (int i = 1; i <= 7; i++)
		{
			pcLandOfDusk->AddModelEx("Field\\forever-fall\\3ani-%02d.ase", i);
		}

		// ÇïÖ®¹È
		pcValleyOfTranquility->SetTerrainFile("Field\\Forever-fall\\forever-fall-02.ase");
		pcValleyOfTranquility->SetMiniMapFile("Field\\Map\\forever-fall-02.tga", "Field\\Title\\forever-fall-02t.tga");
		pcValleyOfTranquility->SetType(MAPTYPE_Forest);
		pcValleyOfTranquility->SetSky(MAPSKY_ForFAll_Morning, MAPSKY_ForFAll_Noon, MAPSKY_ForFAll_Night);
		pcValleyOfTranquility->SetBackgroundMusic(BACKGROUNDMUSICID_Forest);
		pcValleyOfTranquility->AddSpawn(1691, 52599);
		pcValleyOfTranquility->AddSpawn(-1024, 45437);
		pcValleyOfTranquility->AddSpawn(-1543, 52333);
		pcValleyOfTranquility->AddSpawn(-1310, 54945);
		pcValleyOfTranquility->AddSound(-266, 862, 57971, 100, 13);
		pcValleyOfTranquility->AddSound(-5014, 629, 56702, 100, 13);
		pcValleyOfTranquility->AddSound(2153, 772, 53576, 80, 13);
		pcValleyOfTranquility->AddSound(-395, 542, 56521, 80, 13);
		pcValleyOfTranquility->AddSound(-3329, 522, 56469, 20, 15);
		pcValleyOfTranquility->AddSound(-39, 604, 54080, 10, 6);
		pcValleyOfTranquility->AddBorder(MAPID_RoadToTheWind, 667, 59371);
		pcValleyOfTranquility->AddBorder(MAPID_LandOfDusk, -2349, 49830);

		for (int i = 1; i <= 5; i++)
		{
			pcValleyOfTranquility->AddModelEx("Field\\forever-fall\\2ani-%02d.ase", i);
		}

		// ·çÖ®Â·
		pcRoadToTheWind->SetTerrainFile("Field\\Forever-fall\\forever-fall-01.ase");
		pcRoadToTheWind->SetMiniMapFile("Field\\Map\\forever-fall-01.tga", "Field\\Title\\forever-fall-01t.tga");
		pcRoadToTheWind->SetType(MAPTYPE_Forest);
		pcRoadToTheWind->SetSky(MAPSKY_ForFAll_Morning, MAPSKY_ForFAll_Noon, MAPSKY_ForFAll_Night);
		pcRoadToTheWind->SetBackgroundMusic(BACKGROUNDMUSICID_Forest);
		pcRoadToTheWind->AddSpawn(2032, 71183);
		pcRoadToTheWind->AddSpawn(1875, 69871);
		pcRoadToTheWind->AddSpawn(2637, 60219);
		pcRoadToTheWind->AddSound(2849, 577, 67330, 30, 18);
		pcRoadToTheWind->AddSound(317, 653, 64957, 10, 19);
		pcRoadToTheWind->AddSound(-1166, 779, 63268, 40, 18);
		pcRoadToTheWind->AddSound(-181, 864, 62576, 10, 18);
		pcRoadToTheWind->AddSound(190, 686, 61850, 10, 18);
		pcRoadToTheWind->AddSound(-1070, 671, 61561, 10, 18);
		pcRoadToTheWind->AddSound(1815, 562, 65414, 100, 8);
		pcRoadToTheWind->AddSound(1800, 603, 61149, 100, 8);
		pcRoadToTheWind->AddWarpGate(1962, 71184, 559, 64, 32, 1)->Add(MAPID_PhillaiTown, 1993, 73134, 449);
		pcRoadToTheWind->AddBorder(MAPID_PhillaiTown, -8508, -10576);
		pcRoadToTheWind->AddBorder(MAPID_ValleyOfTranquility, 667, 59371);

		for (int i = 1; i <= 27; i++)
		{
			pcRoadToTheWind->AddModelEx("Field\\forever-fall\\1ani-%02d.ase", i);
		}

		// ·Æ¶ûÀ­
		pcPhillaiTown->SetTerrainFile("Field\\Forever-fall\\pilai.ase");
		pcPhillaiTown->SetMiniMapFile("Field\\Map\\pilai.tga", "Field\\Title\\pilait.tga");
		pcPhillaiTown->SetType(MAPTYPE_Town);
		pcPhillaiTown->SetSky(MAPSKY_ForFAll_Morning, MAPSKY_ForFAll_Noon, MAPSKY_ForFAll_Night);
		pcPhillaiTown->SetBackgroundMusic(BACKGROUNDMUSICID_Phillai);
		pcPhillaiTown->AddSpawn(2981, 75486);
		pcPhillaiTown->AddSpawn(2287, 74131);
		pcPhillaiTown->AddSpawn(3547, 75500);
		pcPhillaiTown->AddSound(3557, 613, 75494, 20, 9);
		pcPhillaiTown->AddSound(2256, 745, 78247, 50, 6);
		pcPhillaiTown->AddSound(2066, 463, 73782, 0, 5);
		pcPhillaiTown->AddSound(3032, 554, 73674, 10, 4);
		pcPhillaiTown->AddSound(2246, 554, 76696, 0, 14);
		pcPhillaiTown->AddSound(2531, 544, 74955, 30, 12);
		pcPhillaiTown->AddSound(2034, 544, 74921, 30, 12);
		pcPhillaiTown->AddSound(934, 542, 73886, 0, 17);
		pcPhillaiTown->AddSound(3851, 492, 74639, 0, 17);
		pcPhillaiTown->AddSound(3326, 666, 76387, 0, 17);
		pcPhillaiTown->AddWarpGate(2000, 72907, 474, 64, 32, 1)->Add(MAPID_RoadToTheWind, 1958, 70922, 536);
		pcPhillaiTown->AddWarpGate(2245, 78259, 745, 64, 32, 2)->Add(MAPID_PhillaiTown, 2252, 78041, 754);
		pcPhillaiTown->AddBorder(MAPID_RoadToTheWind, -8508, -10576);

		for (int i = 1; i <= 43; i++)
		{
			pcPhillaiTown->AddModelEx("Field\\forever-fall\\piani-%02d.ase", i);
		}

		//»ÞÆøËÂÃí1²ã
		pcCursedTempleF1->SetTerrainFile("Field\\Dungeon\\dun-4.ase");
		pcCursedTempleF1->SetMiniMapFile("Field\\Map\\dun-4.tga", "Field\\Title\\dun-4t.tga");
		pcCursedTempleF1->SetType(MAPTYPE_Dungeon);
		pcCursedTempleF1->SetBackgroundMusic(BACKGROUNDMUSICID_Dungeon);
		pcCursedTempleF1->AddSpawn(-11108, -41681);
		pcCursedTempleF1->AddSound(-10857, 343, -42634, 10, 24);
		pcCursedTempleF1->AddSound(-11299, 689, -44077, 10, 24);
		pcCursedTempleF1->AddSound(-12995, 689, -43856, 10, 24);
		pcCursedTempleF1->AddSound(-11698, 343, -43240, 10, 24);
		pcCursedTempleF1->AddSound(-13472, 343, -42494, 10, 24);
		pcCursedTempleF1->AddSound(-13447, 343, -40892, 10, 24);
		pcCursedTempleF1->AddSound(-9956, 343, -40637, 10, 24);
		pcCursedTempleF1->AddSound(-9957, 443, -43232, 10, 24);
		pcCursedTempleF1->AddSound(-14113, 443, -42715, 10, 24);
		pcCursedTempleF1->AddSound(-14245, 343, -40555, 10, 24);
		pcCursedTempleF1->AddSound(-12071, 339, -39600, 10, 25);
		pcCursedTempleF1->AddSound(-10236, 443, -44024, 0, 23);
		pcCursedTempleF1->AddSound(-12637, 339, -38716, 0, 23);
		pcCursedTempleF1->AddSound(-12231, 94, -41732, 10, 27);
		pcCursedTempleF1->AddWarpGate(-10860, -41666, 398, 64, 32, 0)->Add(MAPID_AncientsBattlefield, 35872, -2016, 804);

		{
			auto pWarpGate = pcCursedTempleF1->AddWarpGate(-12089, -40380, 95, 64, 32, 0);
			pWarpGate->Add(MAPID_CursedTempleF2, -2527, -37196, 727);
			pWarpGate->Add(MAPID_CursedTempleF2, -3669, -36444, 727);
			pWarpGate->Add(MAPID_CursedTempleF2, -4795, -37198, 727);
		}

		pcCursedTempleF1->AddStaticModel("Field\\dungeon\\dun-4-ani-02.ase");
		pcCursedTempleF1->AddStaticModel("Field\\dungeon\\dun-4-ani-03.ase");
		pcCursedTempleF1->AddStaticModel("Field\\dungeon\\dun-4-ani-06.ase");
		pcCursedTempleF1->AddStaticModel("Field\\dungeon\\dun-4-ani-07.ase");
		pcCursedTempleF1->AddStaticModel("Field\\dungeon\\dun-4-ani-08.ase");
		pcCursedTempleF1->AddStaticModel("Field\\dungeon\\dun-4-ani-09.ase");

		for (int i = 14; i <= 37; i++)
		{
			pcCursedTempleF1->AddModelEx("Field\\dungeon\\dun-4-ani-%02d.ase", i);
		}

		// »ÞÆøËÂÃí2
		pcCursedTempleF2->SetTerrainFile("Field\\Dungeon\\dun-5.ase");
		pcCursedTempleF2->SetMiniMapFile("Field\\Map\\dun-5.tga", "Field\\Title\\dun-5t.tga");
		pcCursedTempleF2->SetType(MAPTYPE_Dungeon);
		pcCursedTempleF2->SetBackgroundMusic(BACKGROUNDMUSICID_Dungeon);
		pcCursedTempleF2->AddSpawn(-3675, -36597);
		pcCursedTempleF2->AddSound(-3660, 730, -36915, 40, 23);
		pcCursedTempleF2->AddSound(-2166, 732, -36125, 0, 24);
		pcCursedTempleF2->AddSound(-5150, 732, -36123, 0, 24);
		pcCursedTempleF2->AddSound(-6175, 762, -41850, 0, 24);
		pcCursedTempleF2->AddSound(-1239, 762, -41850, 0, 24);
		pcCursedTempleF2->AddSound(-1251, 794, -38207, 0, 24);
		pcCursedTempleF2->AddSound(-2424, 732, -38229, 0, 7);
		pcCursedTempleF2->AddSound(-3611, 885, -39747, 0, 7);
		pcCursedTempleF2->AddSound(-4798, 732, -38212, 0, 7);
		pcCursedTempleF2->AddWarpGate(-3665, -36334, 762, 64, 32, 0)->Add(MAPID_CursedTempleF1, -12073, -40701, 95);
		pcCursedTempleF2->AddWarpGate(-4895, -37132, 762, 64, 32, 0)->Add(MAPID_CursedTempleF1, -12073, -40701, 95);
		pcCursedTempleF2->AddWarpGate(-2441, -37137, 762, 64, 32, 0)->Add(MAPID_CursedTempleF1, -12073, -40701, 95);

		{
			auto pWarpGate = pcCursedTempleF2->AddWarpGate(-3207, -43830, 553, 128, 32, 0);
			pWarpGate->Add(MAPID_CursedTempleF3, 3650, -45312, 116);
			pWarpGate->Add(MAPID_CursedTempleF3, -3668, -50022, 3);
		}

		for (int i = 1; i <= 22; i++)
		{
			pcCursedTempleF2->AddModelEx("Field\\dungeon\\dun-5-ani-%02d.ase", i);
		}

		//Ä¢¹½¶´Ñ¨
		pcMushroomCave->SetTerrainFile("Field\\Cave\\Tcave.ase");
		pcMushroomCave->SetMiniMapFile("Field\\Map\\Tcave.tga", "Field\\Title\\Tcavet.tga");
		pcMushroomCave->SetType(MAPTYPE_Dungeon);
		pcMushroomCave->SetBackgroundMusic(BACKGROUNDMUSICID_Dungeon);
		pcMushroomCave->AddSpawn(120126, 26064);
		pcMushroomCave->AddSpawn(119319, 26034);
		pcMushroomCave->AddSpawn(125606, 24541);
		pcMushroomCave->AddWarpGate(125581, 25086, 480, 80, 32, 0)->Add(MAPID_DarkSanctuary, 158627, 20504, 240);
		pcMushroomCave->AddWarpGate(118869, 26017, 538, 80, 32, 0)->Add(MAPID_AcasiaForest, -16490, -6930, 298);

		for (int i = 1; i <= 16; i++)
		{
			pcMushroomCave->AddModelEx("Field\\cave\\Tcave_ani%02d.ase", i);
		}

		// ·ä·¿¶´Ñ¨
		pcBeehiveCave->SetTerrainFile("Field\\Cave\\Mcave.ase");
		pcBeehiveCave->SetMiniMapFile("Field\\Map\\Mcave.tga", "Field\\Title\\Mcavet.tga");
		pcBeehiveCave->SetType(MAPTYPE_Dungeon);
		pcBeehiveCave->SetBackgroundMusic(BACKGROUNDMUSICID_Dungeon);
		pcBeehiveCave->AddSpawn(119966, 35466);
		pcBeehiveCave->AddSpawn(119320, 35680);
		pcBeehiveCave->AddSpawn(124380, 33260);
		pcBeehiveCave->AddWarpGate(124391, 32913, 37, 80, 32, 0)->Add(MAPID_DarkSanctuary, 158543, 19557, 290);
		pcBeehiveCave->AddWarpGate(118808, 35686, 520, 80, 32, 0)->Add(MAPID_LandOfDusk, -6056, 43245, 787);

		for (int i = 1; i <= 17; i++)
		{
			pcBeehiveCave->AddModelEx("Field\\cave\\Mcave_ani%02d.ase", i);
		}

		//¹Å´úÊ¥µî
		pcDarkSanctuary->SetTerrainFile("Field\\Cave\\Dcave.ase");
		pcDarkSanctuary->SetMiniMapFile("Field\\Map\\Dcave.tga", "Field\\Title\\Dcavet.tga");
		pcDarkSanctuary->SetType(MAPTYPE_Dungeon);
		pcDarkSanctuary->SetBackgroundMusic(BACKGROUNDMUSICID_Dungeon);
		pcDarkSanctuary->AddSpawn(158814, 20070);
		pcDarkSanctuary->AddWarpGate(158042, 19525, 330, 120, 32, 0)->Add(MAPID_BeehiveCave, 124396, 33291, 37);
		pcDarkSanctuary->AddWarpGate(158023, 20453, 240, 120, 32, 0)->Add(MAPID_MushroomCave, 125566, 24825, 480);

		for (int i = 1; i <= 14; i++)
		{
			pcDarkSanctuary->AddModelEx("Field\\cave\\Dcave_ani%02d.ase", i);
		}

		//Ä©ÈÕ¶¼ÊÐ
		pcRailwayOfChaos->SetTerrainFile("Field\\Iron\\iron-1.ase");
		pcRailwayOfChaos->SetMiniMapFile("Field\\Map\\iron-1.tga", "Field\\Title\\iron-1t.tga");
		pcRailwayOfChaos->SetType(MAPTYPE_Iron);
		pcRailwayOfChaos->SetSky(MAPSKY_Iron_Morning, MAPSKY_Iron_Noon, MAPSKY_Iron_Night);
		pcRailwayOfChaos->SetBackgroundMusic(BACKGROUNDMUSICID_TRIGGERED);
		pcRailwayOfChaos->AddSpawn(47617, 13626);
		pcRailwayOfChaos->AddSpawn(46905, 13478);
		pcRailwayOfChaos->AddSpawn(47357, 20845);
		pcRailwayOfChaos->AddSpawn(46741, 21349);
		pcRailwayOfChaos->AddBorder(MAPID_HeartOfPerum, 45316, 21407);
		pcRailwayOfChaos->AddBorder(MAPID_ForbiddenLand, 44545, 13063);

		for (int i = 1; i <= 11; i++)
		{
			pcRailwayOfChaos->AddStaticModel(FormatString("Field\\iron\\i1-ani%02d_Bip.ase", i), TRUE);
		}
		for (int i = 1; i <= 3; i++)
		{
			pcRailwayOfChaos->AddModelEx("Field\\iron\\iron-ani%02d.ase", i);
		}

		//ÆÕÁúÐÄÔà
		pcHeartOfPerum->SetTerrainFile("Field\\Iron\\iron-2.ase");
		pcHeartOfPerum->SetMiniMapFile("Field\\Map\\iron-2.tga", "Field\\Title\\iron-2t.tga");
		pcHeartOfPerum->SetType(MAPTYPE_Iron);
		pcHeartOfPerum->SetSky(MAPSKY_Iron_Morning, MAPSKY_Iron_Noon, MAPSKY_Iron_Night);
		pcHeartOfPerum->SetBackgroundMusic(BACKGROUNDMUSICID_TRIGGERED);
		pcHeartOfPerum->AddSpawn(33938, 24229);
		pcHeartOfPerum->AddSpawn(35149, 24326);
		pcHeartOfPerum->AddSpawn(44893, 21380);
		pcHeartOfPerum->AddBorder(MAPID_Eura, 33618, 24011);
		pcHeartOfPerum->AddBorder(MAPID_RailwayOfChaos, 45316, 21407);

		for (int i = 1; i <= 12; i++)
		{
			if (i == 1 || i == 2 || i == 3 || i == 9 || i == 10)
			{
				pcHeartOfPerum->AddModelEx("Field\\iron\\i2-bip%02d.ase", i);
			}
			else
			{
				pcHeartOfPerum->AddStaticModel(FormatString("Field\\iron\\i2-bip%02d_ani.ase", i), TRUE);
			}
		}

		//ÓÄÀ­´å×¯
		pcEura->SetTerrainFile("Field\\Ice\\ice_ura.ase");
		pcEura->SetMiniMapFile("Field\\Map\\ice_ura.tga", "Field\\Title\\ice_urat.tga");
		pcEura->SetType(MAPTYPE_Ice);
		pcEura->SetSky(MAPSKY_ICE1_Morning, MAPSKY_ICE1_Noon, MAPSKY_ICE1_Night);
		pcEura->SetBackgroundMusic(BACKGROUNDMUSICID_DesertB);
		pcEura->AddSpawn(32621, 23865);
		pcEura->AddStaticModel("Field\\ice\\ice_ani_01.ase");
		pcEura->AddWarpGate(30407, 22232, 1349, 64, 32, 2)->Add(MAPID_Eura, 30610, 22164, 1304);
		pcEura->AddBorder(MAPID_GallubiaValley, 31848, 27225);
		pcEura->AddBorder(MAPID_HeartOfPerum, 33618, 24011);

		//±´À­¶ûËþ
		pcBellatra->SetTerrainFile("Field\\Sod\\sod-1.ase");
		pcBellatra->SetMiniMapFile("Field\\Map\\sod-1.tga","Field\\Title\\sod-1t.tga");
		pcBellatra->SetType(MAPTYPE_Wasteland);
		pcBellatra->SetSky(MAPSKY_Wasteland_Morning2, MAPSKY_Wasteland_Noon, MAPSKY_Wasteland_Night);
		pcBellatra->SetBackgroundMusic(BACKGROUNDMUSICID_TRIGGERED);
		pcBellatra->AddSpawn(22018, 6569);

		for (int i = 1; i <= 18; i++)
		{
			pcBellatra->AddStaticModel(FormatString("Resources\\Field\\sod\\s-1ani%02d_Bip.ase", i), TRUE);
		}

		//¿­À­±ÊÉ½¹È
		pcGallubiaValley->SetTerrainFile("Field\\Ice\\ice1.ase");
		pcGallubiaValley->SetMiniMapFile("Field\\Map\\ice1.tga","Field\\Title\\ice1t.tga");
		pcGallubiaValley->SetType(MAPTYPE_Ice);
		pcGallubiaValley->SetSky(MAPSKY_ICE1_Morning, MAPSKY_ICE1_Noon, MAPSKY_ICE1_Night);
		pcGallubiaValley->SetBackgroundMusic(BACKGROUNDMUSICID_Ice);
		pcGallubiaValley->AddSpawn(32313, 28529);
		pcGallubiaValley->AddWarpGate(35361, 31898, 829, 80, 32, 0)->Add(MAPID_IceMineF1, 18006, -34698, 222);
		pcGallubiaValley->AddBorder(MAPID_FrozenSanctuary, 33729, 38029);
		pcGallubiaValley->AddBorder(MAPID_Eura, 31848, 27225);
		pcGallubiaValley->AddStaticModel("Field\\ice\\ice_ani_01.ase");
		pcGallubiaValley->AddStaticModel("Field\\ice\\ice_bip_leewood01.ase");
		pcGallubiaValley->AddStaticModel("Field\\ice\\ice_bip_leewood03.ase");
		pcGallubiaValley->AddStaticModel("Field\\ice\\ice_bip_leewood04.ase");

		for (int i = 1; i <= 7; i++)
		{
			pcGallubiaValley->AddModelEx("Field\\ice\\ice_bip_leaf%02d.ase", i);
		}

		//ÈÎÎñµØÍ¼
		pcQuestArena->SetTerrainFile("Field\\Quest\\quest_IV.ase");
		pcQuestArena->SetType(MAPTYPE_Dungeon);
		pcQuestArena->SetBackgroundMusic(BACKGROUNDMUSICID_Bellatra_78);
		pcQuestArena->AddSpawn(22497, 9605);

		//×£¸£³Ç±¤
		pcBlessCastle->SetTerrainFile("Field\\Castle\\castle.ase");
		pcBlessCastle->SetMiniMapFile("Field\\Map\\castle.tga", "Field\\Title\\castlet.tga");
		pcBlessCastle->SetType(MAPTYPE_BlessCastle);
		pcBlessCastle->SetSky(MAPSKY_Wasteland_Morning2, MAPSKY_Wasteland_Noon, MAPSKY_Wasteland_Night);
		pcBlessCastle->SetBackgroundMusic(BACKGROUNDMUSICID_Bellatra_78);
		pcBlessCastle->AddSpawn(35225, -23847);
		pcBlessCastle->AddSpawn(33920, -23479);
		pcBlessCastle->AddSpawn(35247, -23355);
		pcBlessCastle->AddSpawn(36164, -23446);
		pcBlessCastle->AddWarpGate(32527, -30693, 774, 64, 32, 0)->Add(MAPID_BlessCastle, 32739, -30474, 711);
		pcBlessCastle->AddStaticModel("Field\\castle\\wf_gate_ani.ase");

		for (int i = 1; i <= 6; i++)
		{
			pcBlessCastle->AddModelEx("Field\\castle\\crystal_ani%02d.ase", i);
		}

		//Ì°À·Ö®ºþ
		pcGreedyLake->SetTerrainFile("Field\\Greedy\\Greedy.ase");
		pcGreedyLake->SetMiniMapFile("Field\\Map\\Greedy.tga", "Field\\Title\\Greedyt.tga");
		pcGreedyLake->SetType(MAPTYPE_Ice);
		pcGreedyLake->SetSky(MAPSKY_ICE2_Morning, MAPSKY_ICE2_Noon, MAPSKY_ICE2_Night);
		pcGreedyLake->SetBackgroundMusic(BACKGROUNDMUSICID_DesertB);
		pcGreedyLake->AddSpawn(13930, 23206);
		pcGreedyLake->AddStaticModel("Field\\Greedy\\ani_tail.ase");
		pcGreedyLake->AddStaticModel("Field\\Greedy\\ship_ani.ase");
		pcGreedyLake->AddStaticModel("Field\\Greedy\\door.ase");

		for (int i = 1; i <= 4; i++)
		{
			pcGreedyLake->AddModelEx("Field\\Greedy\\vane%d_ani.ase", i);
		}
		for (int i = 1; i <= 3; i++)
		{
			pcGreedyLake->AddModelEx("Field\\Greedy\\ship%d_ani.ase", i);
		}
		for (int i = 1; i <= 10; i++)
		{
			pcGreedyLake->AddModelEx("Field\\Greedy\\flower_animi%02d.ase", i);
		}
		for (int i = 0; i <= 9; i++)
		{
			pcGreedyLake->AddModelEx("Field\\Greedy\\flower_ani%02d.ase", i);
		}

		//±ù·ç¹È
		pcFrozenSanctuary->SetTerrainFile("Field\\Ice\\ice2.ase");
		pcFrozenSanctuary->SetMiniMapFile("Field\\Map\\ice2.tga", "Field\\Title\\ice2t.tga");
		pcFrozenSanctuary->SetType(MAPTYPE_Ice);
		pcFrozenSanctuary->SetSky(MAPSKY_ICE1_Morning, MAPSKY_ICE1_Noon, MAPSKY_ICE1_Night);
		pcFrozenSanctuary->SetBackgroundMusic(BACKGROUNDMUSICID_Ice);
		pcFrozenSanctuary->AddSpawn(36264, 40182);
		pcFrozenSanctuary->AddWarpGate(37981, 50790, 1216, 64, 32, 0)->Add(MAPID_KelvezuLair, 33000, 50036, 1512);
		pcFrozenSanctuary->AddBorder(MAPID_GallubiaValley, 33729, 38029);

		//¿­¶ûÎ¬ËÕ¶´Ñ¨
		pcKelvezuLair->SetTerrainFile("Field\\Boss\\Boss.ase");
		pcKelvezuLair->SetMiniMapFile("Field\\Map\\Boss.tga", "Field\\Title\\Bosst.tga");
		pcKelvezuLair->SetType(MAPTYPE_Dungeon);
		pcKelvezuLair->SetBackgroundMusic(BACKGROUNDMUSICID_Dungeon);
		pcKelvezuLair->AddSpawn(33000, 50036);
		pcKelvezuLair->AddWarpGate(33012, 49926, 1533, 64, 32, 0)->Add(MAPID_FrozenSanctuary, 37971, 50460, 1209);

		//ÃÔÊ§Ö®µØ
		pcLandOfChaos->SetTerrainFile("Field\\Lost\\lostisland.ase");
		pcLandOfChaos->SetMiniMapFile("Field\\Map\\Lost.tga", "Field\\Title\\Lostt.tga");
		pcLandOfChaos->SetType(MAPTYPE_Wasteland);
		pcLandOfChaos->SetSky(MAPSKY_Lost1_Morning, MAPSKY_Lost1_Noon, MAPSKY_Lost1_Night);
		pcLandOfChaos->SetBackgroundMusic(BACKGROUNDMUSICID_DesertB);
		pcLandOfChaos->AddSpawn(-12555, -1113);
		pcLandOfChaos->AddStaticModel("Field\\lost\\wf_ani.ase");
		pcLandOfChaos->AddWarpGate(-12610, -1349, 694, 64, 32, 2)->Add(MAPID_LandOfChaos, -12555, -1113, 668);
		pcLandOfChaos->AddBorder(MAPID_LostTemple, -11586, 7704);

		for (int i = 1; i <= 4; i++)
		{
			pcLandOfChaos->AddModelEx("Field\\lost\\ani_ship%02d.ase");
		}

		//ÃÔÊ§ËÂÃí
		pcLostTemple->SetTerrainFile("Field\\Losttemple\\lost_temple.ase");
		pcLostTemple->SetMiniMapFile("Field\\Map\\Losttemple.tga", "Field\\Title\\Losttemplet.tga");
		pcLostTemple->SetType(MAPTYPE_Wasteland);
		pcLostTemple->SetSky(MAPSKY_Lost2_Morning, MAPSKY_Lost2_Noon, MAPSKY_Lost2_Night);
		pcLostTemple->SetBackgroundMusic(BACKGROUNDMUSICID_DesertB);
		pcLostTemple->AddSpawn(-11718, 10794);
		pcLostTemple->AddBorder(MAPID_LandOfChaos, -11586, 7704);

		//ÓÄÁé³Ç±¤
		pcDistortedForest->SetTerrainFile("Field\\Fall_Game\\fall_game.ase");
		pcDistortedForest->SetType(MAPTYPE_Distorted);
		pcDistortedForest->SetBackgroundMusic(BACKGROUNDMUSICID_Dungeon);
		//pcDistortedForest->SetCamera(0, 213140, 36421, 5583, 11483);
		pcDistortedForest->AddSpawn(5800, 36747);
		pcDistortedForest->AddStaticModel("Field\\Fall_Game\\chandelier-ani.ase");

		for (int i = 1; i <= 19; i++)
		{
			pcDistortedForest->AddModelEx("Field\\Fall_Game\\chandelier-ani%02d.ase");
		}

		//ÎÞ¾¡Ö®Ëþ1²ã
		pcEndlessTowerF1->SetTerrainFile("Field\\Endless\\dun-7.ase");
		pcEndlessTowerF1->SetMiniMapFile("Field\\Map\\dun-7.tga", "Field\\Title\\dun-7t.tga");
		pcEndlessTowerF1->SetType(MAPTYPE_Dungeon);
		pcEndlessTowerF1->SetBackgroundMusic(BACKGROUNDMUSICID_Battle);
		pcEndlessTowerF1->AddSpawn(14255, -39099);
		pcEndlessTowerF1->AddWarpGate(14241, -41079, 220, 64, 32, 0)->Add(MAPID_EndlessTowerF2, 5255, -37897, 84);
		pcEndlessTowerF1->AddWarpGate(14246, -38912, 220, 64, 32,0)->Add(MAPID_LostTemple, -12272, 11299, 509);

		//ÎÞ¾¡Ö®Ëþ2²ã
		pcEndlessTowerF2->SetTerrainFile("Field\\Endless\\dun-8.ase");
		pcEndlessTowerF2->SetMiniMapFile("Field\\Map\\dun-8.tga", "Field\\Title\\dun-8t.tga");
		pcEndlessTowerF2->SetType(MAPTYPE_Dungeon);
		pcEndlessTowerF2->SetBackgroundMusic(BACKGROUNDMUSICID_Battle);
		pcEndlessTowerF2->AddSpawn(5255, -37897);
		pcEndlessTowerF2->AddWarpGate(5253, -37708, 69, 64, 32, 0)->Add(MAPID_EndlessTowerF1, 14242, -41199, 220);

		{
			auto pWarpGate = pcEndlessTowerF2->AddWarpGate(5254, -41500, 139, 64, 32, 0);

			pWarpGate->Add(MAPID_EndlessTowerF3, 4896, -42220, 202);
			pWarpGate->Add(MAPID_EndlessTowerF3, 6408, -42220, 202);
		}

		//»ÞÆøËÂÃí3²ã
		pcCursedTempleF3->SetTerrainFile("Field\\Dungeon\\Dun-6a.ase");
		pcCursedTempleF3->SetMiniMapFile("Field\\Map\\dun-6.tga", "Field\\Title\\dun-6t.tga");
		pcCursedTempleF3->SetType(MAPTYPE_Dungeon);
		pcCursedTempleF3->SetSky(MAPSKY_None, MAPSKY_None, MAPSKY_None);
		pcCursedTempleF3->SetBackgroundMusic(BACKGROUNDMUSICID_Battle);
		pcCursedTempleF3->AddSpawn(-3660, -45200);
		pcCursedTempleF3->AddSound(-3648, 3, -50013, 0, 7);
		pcCursedTempleF3->AddSound(-4349, 454, -47777, 0, 7);
		pcCursedTempleF3->AddSound(-5130, 454, -47587, 0, 7);
		pcCursedTempleF3->AddSound(-2183, 172, -47864, 0, 7);
		pcCursedTempleF3->AddSound(-1785, 167, -48077, 0, 7);
		pcCursedTempleF3->AddSound(-3725, 116, -46758, 0, 7);
		pcCursedTempleF3->AddSound(-3632, 3, -47999, 0, 7);
		pcCursedTempleF3->AddSound(-627, 229, -45987, 0, 7);
		pcCursedTempleF3->AddSound(-1896, 116, -45010, 0, 7);
		pcCursedTempleF3->AddSound(-5077, 116, -45555, 0, 7);
		pcCursedTempleF3->AddSound(-5289, 116, -46422, 0, 7);

		{
			auto pWarpGate = pcCursedTempleF3->AddWarpGate(-3655, -50603, 3, 64, 32, 0);

			pWarpGate->Add(MAPID_CursedTempleF2, -2851, -43792, 642);
			pWarpGate->Add(MAPID_CursedTempleF2, -4422, -43801, 642);
		}
		{
			auto pWarpGate = pcCursedTempleF3->AddWarpGate(-3664, -44886, 145, 64, 32, 0);

			pWarpGate->Add(MAPID_CursedTempleF2, -2851, -43792, 642);
			pWarpGate->Add(MAPID_CursedTempleF2, -4422, -43801, 642);
		}

		for (int i = 1; i <= 19; i++)
		{
			pcCursedTempleF3->AddModelEx("Field\\dungeon\\Dun-6a-ani-%03d.ase", i);
		}

		//ÎÞ¾¡Ö®Ëþ3²ã
		pcEndlessTowerF3->SetTerrainFile("Field\\Endless\\dun-9.ase");
		pcEndlessTowerF3->SetMiniMapFile("Field\\Map\\dun-9.tga", "Field\\Title\\dun-9t.tga");
		pcEndlessTowerF3->SetType(MAPTYPE_Dungeon);
		pcEndlessTowerF3->SetBackgroundMusic(BACKGROUNDMUSICID_Battle);
		pcEndlessTowerF3->AddSpawn(4896, -42330);
		pcEndlessTowerF3->AddSpawn(4896, -42330);
		pcEndlessTowerF3->AddSpawn(6418, -42330);
		pcEndlessTowerF3->AddWarpGate(4896, -42090, 230, 64, 32, 0)->Add(MAPID_EndlessTowerF2, 5254, -41361, 139);
		pcEndlessTowerF3->AddWarpGate(6408, -42090, 230, 64, 32, 0)->Add(MAPID_EndlessTowerF2, 5254, -41361, 139);

		// ±ù·â¶´Ñ¨1²ã
		pcIceMineF1->SetTerrainFile("Field\\Mine\\mine-1.ase");
		pcIceMineF1->SetMiniMapFile("Field\\Map\\mine-1.tga", "Field\\Title\\mine-1t.tga");
		pcIceMineF1->SetType(MAPTYPE_Dungeon);
		pcIceMineF1->SetBackgroundMusic(BACKGROUNDMUSICID_Battle);
		pcIceMineF1->AddSpawn(18006, -34740);
		pcIceMineF1->AddWarpGate(17944, -34641, 246, 64, 32, 0)->Add(MAPID_GallubiaValley, 35352, 31928, 829);

		// ÄÚÎ¬Ë¹¿Ë¶´Ñ¨
		pcSlab->SetTerrainFile("Field\\Slab\\Slab.ase");
		pcSlab->SetMiniMapFile("Field\\Map\\Slab.tga", "Field\\Title\\Slabt.tga");
		pcSlab->SetType(MAPTYPE_Dungeon);
		pcSlab->SetBackgroundMusic(BACKGROUNDMUSICID_Eura);
		pcSlab->AddSpawn(-12024, -62846);
		pcSlab->AddSpawn(-11976, -62455);
		pcSlab->AddWarpGate(-12000, -54163, 374, 64, 32, 0)->Add(MAPID_AncientWeapon, 12788, -73633, 458);

		//Âå¿Ë¶´Ñ¨
		pcAncientWeapon->SetTerrainFile("Field\\AncientW\\AncientW.ase");
		pcAncientWeapon->SetMiniMapFile("Field\\Map\\AncientW.tga","Field\\Title\\AncientWt.tga");
		pcAncientWeapon->SetType(MAPTYPE_Dungeon);
		pcAncientWeapon->SetBackgroundMusic(BACKGROUNDMUSICID_Atlantis);
		pcAncientWeapon->AddSpawn(12788, -73633);
		pcAncientWeapon->AddSpawn(12788, -73633);
		pcAncientWeapon->AddWarpGate(12799, -62227, 530, 64, 32, 1)->Add(MAPID_AncientWeapon, 12772, -59917, 562);
		pcAncientWeapon->AddWarpGate(12778, -60119, 578, 64, 32, 1)->Add(MAPID_AncientWeapon, 12700, -62387, 510);
		pcAncientWeapon->AddWarpGate(12790, -74070, 458, 64, 32, 0)->Add(MAPID_MysteryDesert1, -37086, -4809, 1457);

		//´¬³§Ä¹µØ
		pcShipyardRuins->SetTerrainFile("Field\\Lost\\lost3.ase");
		pcShipyardRuins->SetMiniMapFile("Field\\Map\\lost3.tga","Field\\Title\\lost3t.tga");
		pcShipyardRuins->SetType(MAPTYPE_Wasteland);
		pcShipyardRuins->SetSky(MAPSKY_Lost1_Morning, MAPSKY_Lost1_Noon, MAPSKY_Lost1_Night);
		pcShipyardRuins->SetBackgroundMusic(BACKGROUNDMUSICID_MysteryForest);
		pcShipyardRuins->AddSpawn(116360, 92524);
		pcShipyardRuins->AddSpawn(116360, 92524);

		//Ô¶¹ÅÖ®É­3
		pcMysteryForest3->SetTerrainFile("Field\\Custom\\fo3.ase");
		pcMysteryForest3->SetMiniMapFile("Field\\Map\\fo3.tga", "Field\\Title\\fo3t.tga");
		pcMysteryForest3->SetType(MAPTYPE_Forest);
		pcMysteryForest3->SetSky(MAPSKY_Forest_Morning, MAPSKY_Forest_Noon, MAPSKY_Forest_Night);
		pcMysteryForest3->SetBackgroundMusic(BACKGROUNDMUSICID_BlessCastle);
		pcMysteryForest3->AddSpawn(-57048, -6894);
		pcMysteryForest3->AddSpawn(-50646, -6363);
		pcMysteryForest3->AddSpawn(-55880, -9733);
		pcMysteryForest3->AddBorder(MAPID_MysteryForest2, -48393, -10526);

		//Ô¶¹ÅÖ®É­2
		pcMysteryForest2->SetTerrainFile("Field\\Custom\\fo2.ase");
		pcMysteryForest2->SetMiniMapFile("Field\\Map\\fo2.tga", "Field\\Title\\fo2t.tga");
		pcMysteryForest2->SetType(MAPTYPE_Forest);
		pcMysteryForest2->SetSky(MAPSKY_Forest_Morning, MAPSKY_Forest_Noon, MAPSKY_Forest_Night);
		pcMysteryForest2->SetBackgroundMusic(BACKGROUNDMUSICID_BlessCastle);
		pcMysteryForest2->AddSpawn(-46733, -14391);
		pcMysteryForest2->AddSpawn(-46644, -10485);
		pcMysteryForest2->AddSpawn(-41291, -11138);
		pcMysteryForest2->AddBorder(MAPID_MysteryForest1, -40333, -9515);
		pcMysteryForest2->AddBorder(MAPID_MysteryForest3, -48393, -10526);

		//Ô¶¹ÅÖ®É­1
		pcMysteryForest1->SetTerrainFile("Field\\Custom\\fo1.ase");
		pcMysteryForest1->SetMiniMapFile("Field\\Map\\fo1.tga", "Field\\Title\\fo1t.tga");
		pcMysteryForest1->SetType(MAPTYPE_Forest);
		pcMysteryForest1->SetSky(MAPSKY_Forest_Morning, MAPSKY_Forest_Noon, MAPSKY_Forest_Night);
		pcMysteryForest1->SetBackgroundMusic(BACKGROUNDMUSICID_BlessCastle);
		pcMysteryForest1->AddSpawn(-37627, -10754);
		pcMysteryForest1->AddSpawn(-37627, -10754);
		pcMysteryForest1->AddSpawn(-38759, -13582);
		pcMysteryForest1->AddBorder(MAPID_Atlantis, -37653, -14972);
		pcMysteryForest1->AddBorder(MAPID_MysteryDesert1, -35228, -7397);
		pcMysteryForest1->AddBorder(MAPID_MysteryForest2, -40333, -9515);

		//°¢ÈðË¹³Ç
		pcAtlantisTown->SetTerrainFile("Field\\Custom\\town1.ase");
		pcAtlantisTown->SetMiniMapFile("Field\\Map\\town1.tga", "Field\\Title\\town1t.tga");
		pcAtlantisTown->SetType(MAPTYPE_Town);
		pcAtlantisTown->SetSky(MAPSKY_Forest_Morning, MAPSKY_Forest_Noon, MAPSKY_Forest_Night);
		pcAtlantisTown->SetBackgroundMusic(BACKGROUNDMUSICID_Login);
		pcAtlantisTown->AddSpawn(-37888, -17150);
		pcAtlantisTown->AddSpawn(-37725, -17198);
		pcAtlantisTown->AddSpawn(-40254, -17511);

		for (int i = 1; i <= 4; i++)
		{
			pcAtlantisTown->AddModelEx("Field\\forest\\v-ani%02d.ASE", i);
		}

		//¹Å´úÄÚÍþË¹¿Ë
		pcBattleTown->SetTerrainFile("Field\\Custom\\ba1.ase");
		pcBattleTown->SetMiniMapFile("Field\\Map\\ba1.tga","Field\\Title\\ba1t.tga");
		pcBattleTown->SetType(MAPTYPE_Desert);
		pcBattleTown->SetSky(MAPSKY_Desert_Morning, MAPSKY_Desert_Noon, MAPSKY_Desert_Night);
		pcBattleTown->SetBackgroundMusic(BACKGROUNDMUSICID_CharacterSelect);
		pcBattleTown->AddSpawn(-23793, 19419);
		pcBattleTown->AddSpawn(-25680, 20862);
		pcBattleTown->AddBorder(MAPID_MysteryDesert3, -25122, 20938);
		pcBattleTown->AddBorder(MAPID_MiraRemains, -19022, 21052);

		//»Ã¾³É³Ä®3
		pcMysteryDesert3->SetTerrainFile("Field\\Custom\\ba2.ase");
		pcMysteryDesert3->SetMiniMapFile("Field\\Map\\ba2.tga", "Field\\Title\\ba2t.tga");
		pcMysteryDesert3->SetType(MAPTYPE_Desert);
		pcMysteryDesert3->SetSky(MAPSKY_Desert_Morning, MAPSKY_Desert_Noon, MAPSKY_Desert_Night);
		pcMysteryDesert3->SetBackgroundMusic(BACKGROUNDMUSICID_QuestArena);
		pcMysteryDesert3->AddSpawn(-29687, 20686);
		pcMysteryDesert3->AddSpawn(-29687, 21324);
		pcMysteryDesert3->AddBorder(MAPID_MysteryDesert2, -32203, 15803);
		pcMysteryDesert3->AddBorder(MAPID_BattleTown, -25122, 20938);

		//»Ã¾³É³Ä®2
		pcMysteryDesert2->SetTerrainFile("Field\\Custom\\ba3.ase");
		pcMysteryDesert2->SetMiniMapFile("Field\\Map\\ba3.tga", "Field\\Title\\ba3t.tga");
		pcMysteryDesert2->SetType(MAPTYPE_Desert);
		pcMysteryDesert2->SetSky(MAPSKY_Desert_Morning, MAPSKY_Desert_Noon, MAPSKY_Desert_Night);
		pcMysteryDesert2->SetBackgroundMusic(BACKGROUNDMUSICID_QuestArena);
		pcMysteryDesert2->AddSpawn(-29541, 8994);
		pcMysteryDesert2->AddSpawn(-32435, 13515);
		pcMysteryDesert2->AddSpawn(-33661, 8804);
		pcMysteryDesert2->AddBorder(MAPID_MysteryDesert1, -32225, 4508);
		pcMysteryDesert2->AddBorder(MAPID_MysteryDesert3, -32203, 15803);

		//»Ã¾³É³Ä®1
		pcMysteryDesert1->SetTerrainFile("Field\\Custom\\ba4.ase");
		pcMysteryDesert1->SetMiniMapFile("Field\\Map\\ba4.tga", "Field\\Title\\ba4t.tga");
		pcMysteryDesert1->SetType(MAPTYPE_Desert);
		pcMysteryDesert1->SetSky(MAPSKY_Desert_Morning, MAPSKY_Desert_Noon, MAPSKY_Desert_Night);
		pcMysteryDesert1->SetBackgroundMusic(BACKGROUNDMUSICID_QuestArena);
		pcMysteryDesert1->AddSpawn(-34798, -1959);
		pcMysteryDesert1->AddSpawn(-35393, -2871);
		pcMysteryDesert1->AddBorder(MAPID_MysteryForest1, -35228, -7397);


		//Ã×À­ÒÅ¼£
		pcMiraRemains->SetTerrainFile("Field\\Iron\\iron3.ase");
		pcMiraRemains->SetMiniMapFile("Field\\Map\\iron3.tga", "Field\\Title\\iron3t.tga");
		pcMiraRemains->SetType(MAPTYPE_Iron);
		pcMiraRemains->SetSky(MAPSKY_Iron_Morning, MAPSKY_Iron_Noon, MAPSKY_Iron_Night);
		pcMiraRemains->SetBackgroundMusic(BACKGROUNDMUSICID_TRIGGERED);
		pcMiraRemains->AddSpawn(-18286, 21104);
		pcMiraRemains->AddSpawn(-18286, 21104);
		pcMiraRemains->AddSound(-15250, 1009, 21677, 80, 2);
		pcMiraRemains->AddSound(-13025, 1126, 21710, 80, 3);
		pcMiraRemains->AddBorder(MAPID_BattleTown, -19022, 21052);

		for (int i = 1; i <= 6; i++)
		{
			pcMiraRemains->AddModelEx("Field\\Iron\\iron3-ani%d.ase", i);
		}

		//ÈÛÑÒ¶´Ñ¨
		pcT5QuestArena->SetTerrainFile("Field\\Boss\\dc1.ase");
		pcT5QuestArena->SetMiniMapFile("Field\\Map\\dc1.tga", "Field\\Title\\dc1t.tga");
		pcT5QuestArena->SetType(MAPTYPE_Dungeon);
		pcT5QuestArena->SetSky(MAPSKY_None, MAPSKY_None, MAPSKY_None);
		pcT5QuestArena->SetBackgroundMusic(BACKGROUNDMUSICID_MysteryDesert);
		pcT5QuestArena->AddSpawn(198279, 240452);
		pcT5QuestArena->AddSpawn(198279, 240452);
		pcT5QuestArena->AddWarpGate(198284, 240295, 1517, 64, 32, 0)->Add(MAPID_RicartenTown, 2604, -18130, 236);
	}
}