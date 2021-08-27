#include "StdAfx.h"
#include "SceneMap.h"

namespace SCENE
{
	Map::Map()
	{

	}
	Map::~Map()
	{

	}
	void Map::Init()
	{

	}
	void Map::Load()
	{
		auto pcAcasiaForest = AddMap(new MapInfo(MAPID_AcasiaForest, "Acasia Forest"));
		auto pcBambooForest = AddMap(new MapInfo(MAPID_BambooForest, "Bamboo Forest"));
		auto pcGardenOfFreedom = AddMap(new MapInfo(MAPID_GardenOfFreedom, "Garden of Freedom"));
		auto pcRicartenTown = AddMap(new MapInfo(MAPID_RicartenTown, "Ricarten Town"));
		auto pcRefugeOfTheAncients = AddMap(new MapInfo(MAPID_RefugeOfTheAncients, "Refuge of the Ancients"));
		auto pcCastleOfTheLost = AddMap(new MapInfo(MAPID_CastleOfTheLost, "Castle of the Lost"));
		auto pcRuinenVillage = AddMap(new MapInfo(MAPID_RuinenVillage, "Ruinen Village"));
		auto pcForgottenLand = AddMap(new MapInfo(MAPID_ForgottenLand, "Forgotten Land"));
		auto pcCursedLand = AddMap(new MapInfo(MAPID_CursedLand, "Cursed Land"));
		auto pcNaviskoTown = AddMap(new MapInfo(MAPID_NaviskoTown, "Navisko Town"));
		auto pcOasis = AddMap(new MapInfo(MAPID_Oasis, "Oasis"));
		auto pcBattlefieldOfTheAncients = AddMap(new MapInfo(MAPID_AncientsBattlefield, "Battlefield of the Ancients"));
		auto pcForbiddenLand = AddMap(new MapInfo(MAPID_ForbiddenLand, "Forbidden Land"));
		auto pcAncientPrisonF1 = AddMap(new MapInfo(MAPID_AncientPrisonF1, "Ancient Prison 1F"));
		auto pcAncientPrisonF2 = AddMap(new MapInfo(MAPID_AncientPrisonF2, "Ancient Prison 2F"));
		auto pcAncientPrisonF3 = AddMap(new MapInfo(MAPID_AncientPrisonF3, "Ancient Prison 3F"));
		auto pcChessRoom = AddMap(new MapInfo(MAPID_ChessRoom, "Checker (GM) Room"));
		auto pcForestOfSpirits = AddMap(new MapInfo(MAPID_ForestOfSpirits, "Forest of Spirits"));
		auto pcLandOfDusk = AddMap(new MapInfo(MAPID_LandOfDusk, "Land of Dusk"));
		auto pcValleyOfTranquility = AddMap(new MapInfo(MAPID_ValleyOfTranquility, "Valley of Tranquility"));
		auto pcRoadToTheWind = AddMap(new MapInfo(MAPID_RoadToTheWind, "Road to the Wind"));
		auto pcPhillaiTown = AddMap(new MapInfo(MAPID_PhillaiTown, "Pillia Town"));
		auto pcCursedTempleF1 = AddMap(new MapInfo(MAPID_CursedTempleF1, "Cursed Temple 1F"));
		auto pcCursedTempleF2 = AddMap(new MapInfo(MAPID_CursedTempleF2, "Cursed Temple 2F"));
		auto pcMushroomCave = AddMap(new MapInfo(MAPID_MushroomCave, "Cave of Mushrooms"));
		auto pcBeehiveCave = AddMap(new MapInfo(MAPID_BeehiveCave, "Cave of Beehive"));
		auto pcDarkSanctuary = AddMap(new MapInfo(MAPID_DarkSanctuary, "Sanctuary of Darkness"));
		auto pcRailwayOfChaos = AddMap(new MapInfo(MAPID_RailwayOfChaos, "Railway of Chaos"));
		auto pcHeartOfPerum = AddMap(new MapInfo(MAPID_HeartOfPerum, "Heart of Perum"));
		auto pcEura = AddMap(new MapInfo(MAPID_Eura, "Eura"));
		auto pcBellatra = AddMap(new MapInfo(MAPID_Bellatra, "Bellatra Celestial"));
		auto pcGallubiaValley = AddMap(new MapInfo(MAPID_GallubiaValley, "Gallubia Valley"));
		auto pcQuestArena = AddMap(new MapInfo(MAPID_QuestArena, "Quest Arena"));
		auto pcBlessCastle = AddMap(new MapInfo(MAPID_BlessCastle, "Bless Castle"));
		auto pcGreedyLake = AddMap(new MapInfo(MAPID_GreedyLake, "Greedy Lake"));
		auto pcFrozenSanctuary = AddMap(new MapInfo(MAPID_FrozenSanctuary, "Frozen Temple"));
		auto pcKelvezuLair = AddMap(new MapInfo(MAPID_KelvezuLair, "Fire Map"));
		auto pcLandOfChaos = AddMap(new MapInfo(MAPID_LandOfChaos, "Lost Island"));
		auto pcLostTemple = AddMap(new MapInfo(MAPID_LostTemple, "Lost Temple"));
		auto pcDistortedForest = AddMap(new MapInfo(MAPID_GhostCastle, "Ghost Castle"));
		auto pcEndlessTowerF1 = AddMap(new MapInfo(MAPID_EndlessTowerF1, "Endless Tower 1F"));
		auto pcEndlessTowerF2 = AddMap(new MapInfo(MAPID_EndlessTowerF2, "Endless Tower 2F"));
		auto pcCursedTempleF3 = AddMap(new MapInfo(MAPID_CursedTempleF3, "Cursed Temple 3F"));
		auto pcEndlessTowerF3 = AddMap(new MapInfo(MAPID_EndlessTowerF3, "Endless Tower 3F"));
		auto pcIceMineF1 = AddMap(new MapInfo(MAPID_IceMineF1, "Ice Mine 1F"));
		auto pcSlab = AddMap(new MapInfo(MAPID_SecretLaboratory, "Secret Laboratory"));
		auto pcAncientWeapon = AddMap(new MapInfo(MAPID_AncientWeapon, "Anciient Weapon"));
		auto pcShipyardRuins = AddMap(new MapInfo(MAPID_ShipyardRuins, "Shipyard Ruins"));
		auto pcMysteryForest3 = AddMap(new MapInfo(MAPID_MysteryForest3, "Mystery Forest 3"));
		auto pcMysteryForest2 = AddMap(new MapInfo(MAPID_MysteryForest2, "Mystery Forest 2"));
		auto pcMysteryForest1 = AddMap(new MapInfo(MAPID_MysteryForest1, "Mystery Forest 1"));
		auto pcAtlantisTown = AddMap(new MapInfo(MAPID_Atlantis, "Atlantis Town"));
		auto pcBattleTown = AddMap(new MapInfo(MAPID_BattleTown, "Battle Town"));
		auto pcMysteryDesert3 = AddMap(new MapInfo(MAPID_MysteryDesert3, "Mystery Desert 3"));
		auto pcMysteryDesert2 = AddMap(new MapInfo(MAPID_MysteryDesert2, "Mystery Desert 2"));
		auto pcMysteryDesert1 = AddMap(new MapInfo(MAPID_MysteryDesert1, "Mystery Desert 1"));
		auto pcMiraRemains = AddMap(new MapInfo(MAPID_MiraRemains, "Mira Remains"));
		auto pcT5QuestArena = AddMap(new MapInfo(MAPID_T5QuestArena, "T5 Quest Arena"));

		// 胶之林
		pcAcasiaForest->SetFileName("Field\\Forest\\fore-3.ase");
		pcAcasiaForest->SetMapFileName("Field\\Map\\fore-3.tga", "Field\\Title\\fore-3t.tga");
		pcAcasiaForest->SetSky(SCENESKY_Forest_Morning, SCENESKY_Forest_Noon, SCENESKY_Forest_Night);
		pcAcasiaForest->SetType(MAPTYPE_Forest);
		pcAcasiaForest->SetBackgroundMusicID(BACKGROUNDMUSICID_Forest);
		pcAcasiaForest->AddSpawn(-16419, -7054);
		pcAcasiaForest->AddSpawn(-10585, -11810);
		pcAcasiaForest->AddSpawn(-13659, -9753);
		pcAcasiaForest->AddWarpGate(-16638, -6737, 267, 64, 32)->Add(pcMushroomCave, 119112, 26028, 510);
		pcAcasiaForest->AddBorder(pcBambooForest, -8508, -10576);
		pcAcasiaForest->AddSound(-13819, 226, -8950, 100, 15);

		for (int i = 1; i <= 14; i++)
		{
			pcAcasiaForest->AddModelEx("Field\\Forset\\3ani-%02d.ase", i);
		}

		// 竹之林
		pcBambooForest->SetFileName("Field\\Forest\\fore-2.ase");
		pcBambooForest->SetMapFileName("Field\\Map\\fore-2.tga", "Field\\Title\\fore-2t.tga");
		pcBambooForest->SetSky(SCENESKY_Forest_Morning, SCENESKY_Forest_Noon, SCENESKY_Forest_Night);
		pcBambooForest->SetType(MAPTYPE_Forest);
		pcBambooForest->SetBackgroundMusicID(BACKGROUNDMUSICID_Forest);
		pcBambooForest->AddSpawn(-5427, -9915);
		pcBambooForest->AddSpawn(-2272, -10314);
		pcBambooForest->AddSpawn(-7192, -11175);
		pcBambooForest->AddWarpGate(-3408, -12447, 251, 64, 32)->Add(pcBambooForest, -3265, -12583, 214, 2);
		pcBambooForest->AddBorder(pcGardenOfFreedom, -292, -9548);
		pcBambooForest->AddStaticModel("Field\\Forset\\2ani-04.ase");

		// 自由庭院
		pcGardenOfFreedom->SetFileName("Field\\Forest\\fore-1.ase");
		pcGardenOfFreedom->SetMapFileName("Field\\Map\\fore-1.tga", "Field\\Title\\fore-1t.tga");
		pcGardenOfFreedom->SetSky(SCENESKY_Forest_Morning, SCENESKY_Forest_Noon, SCENESKY_Forest_Night);
		pcGardenOfFreedom->SetType(MAPTYPE_Forest);
		pcGardenOfFreedom->SetBackgroundMusicID(BACKGROUNDMUSICID_Forest);
		pcGardenOfFreedom->AddSpawn(4184, -11016);
		pcGardenOfFreedom->AddSpawn(1350, -13672);
		pcGardenOfFreedom->AddSpawn(1761, -10815);
		pcGardenOfFreedom->AddSpawn(4777, -10916);
		pcGardenOfFreedom->AddBorder(pcRefugeOfTheAncients, 4844, -6835);
		pcGardenOfFreedom->AddBorder(pcRicartenTown, 2275, -14828);

		// 理查登
		pcRicartenTown->SetFileName("Field\\Ricarten\\village-2.ase");
		pcRicartenTown->SetMapFileName("Field\\Map\\village-2.tga", "Field\\Title\\village-2t.tga");
		pcRicartenTown->SetSky(SCENESKY_Forest_Morning, SCENESKY_Forest_Noon, SCENESKY_Forest_Night);
		pcRicartenTown->SetType(MAPTYPE_Town);
		pcRicartenTown->SetBackgroundMusicID(BACKGROUNDMUSICID_Ricarten);
		pcRicartenTown->AddSpawn(2596, -18738);
		pcRicartenTown->AddSpawn(2592, -18566);
		pcRicartenTown->AddSpawn(-1047, -16973);
		pcRicartenTown->AddWarpGate(734, -20119, 312, 64, 32)->Add(pcRicartenTown, 822, -19956, 254, 2);
		pcRicartenTown->AddWarpGate(2597, -18243, 236, 32, 32)->Add(pcT5QuestArena, 198282, 240400, 1502);

		for (int i = 1; i <= 14; i++)
		{
			pcRicartenTown->AddModelEx("Field\\Ricarten\\v-ani%02d.ase", i);
		}

		// 废墟墓地
		pcRefugeOfTheAncients->SetFileName("Field\\Ruin\\ruin-4.ase");
		pcRefugeOfTheAncients->SetMapFileName("Field\\Map\\ruin-4.tga", "Field\\Title\\ruin-4t.tga");
		pcRefugeOfTheAncients->SetSky(SCENESKY_Wasteland_Morning1, SCENESKY_Wasteland_Noon, SCENESKY_Wasteland_Night);
		pcRefugeOfTheAncients->SetType(MAPTYPE_Wasteland);
		pcRefugeOfTheAncients->SetBackgroundMusicID(BACKGROUNDMUSICID_DesertB);
		pcRefugeOfTheAncients->AddSpawn(1384, -918);
		pcRefugeOfTheAncients->AddSpawn(2578, -5124);
		pcRefugeOfTheAncients->AddSpawn(1873, 3060);
		pcRefugeOfTheAncients->AddBorder(pcCastleOfTheLost, 410, 4902);

		// 废墟
		pcCastleOfTheLost->SetFileName("Field\\Ruin\\ruin-3.ase");
		pcCastleOfTheLost->SetMapFileName("Field\\Map\\ruin-3.tga", "Field\\Title\\ruin-3t.tga");
		pcCastleOfTheLost->SetSky(SCENESKY_Wasteland_Morning1, SCENESKY_Wasteland_Noon, SCENESKY_Wasteland_Night);
		pcCastleOfTheLost->SetType(MAPTYPE_Wasteland);
		pcCastleOfTheLost->SetBackgroundMusicID(BACKGROUNDMUSICID_DesertB);
		pcCastleOfTheLost->AddSpawn(4953, 10922);
		pcCastleOfTheLost->AddSpawn(875, 7910);
		pcCastleOfTheLost->AddSpawn(1576, 14307);
		pcCastleOfTheLost->AddBorder(pcRuinenVillage, 3051, 16124);

		// 废墟村庄
		pcRuinenVillage->SetFileName("Field\\Ruin\\ruin-2.ase");
		pcRuinenVillage->SetMapFileName("Field\\Map\\ruin-2.tga", "Field\\Title\\ruin-2t.tga");
		pcRuinenVillage->SetSky(SCENESKY_Wasteland_Morning2, SCENESKY_Wasteland_Noon, SCENESKY_Wasteland_Night);
		pcRuinenVillage->SetType(MAPTYPE_Wasteland);
		pcRuinenVillage->SetBackgroundMusicID(BACKGROUNDMUSICID_DesertB);
		pcRuinenVillage->AddSpawn(7459, 23984);
		pcRuinenVillage->AddSpawn(3976, 19645);
		pcRuinenVillage->AddSpawn(5832, 23751);
		pcRuinenVillage->AddSpawn(5615, 25117);
		pcRuinenVillage->AddWarpGate(4428, 22511, 845, 64, 32)->Add(pcRuinenVillage, 4547, 22616, 817, 2);
		pcRuinenVillage->AddBorder(pcForgottenLand, 10019, 18031);
		pcRuinenVillage->AddBorder(pcForestOfSpirits, 4470, 27774);
		pcRuinenVillage->AddBorder(pcGreedyLake, 12713, 23409);
		pcRuinenVillage->AddStaticModel("Field\\Ruin\\ruin_ani01.ase");

		// 遗忘之地
		pcForgottenLand->SetFileName("Field\\Ruin\\ruin-1.ase");
		pcForgottenLand->SetMapFileName("Field\\Map\\ruin-1.tga", "Field\\Title\\ruin-1t.tga");
		pcForgottenLand->SetSky(SCENESKY_Wasteland_Morning2, SCENESKY_Wasteland_Noon, SCENESKY_Wasteland_Night);
		pcForgottenLand->SetType(MAPTYPE_Wasteland);
		pcForgottenLand->SetBackgroundMusicID(BACKGROUNDMUSICID_DesertB);
		pcForgottenLand->AddSpawn(16362, 14959);
		pcForgottenLand->AddSpawn(12242, 16034);
		pcForgottenLand->AddSpawn(12194, 8969);
		pcForgottenLand->AddWarpGate(16809, 15407, 501, 128, 32)->Add(pcAncientPrisonF1, -15395, -24185, 0);
		pcForgottenLand->AddBorder(pcCursedLand, 13319, 7102);

		// 诅咒之地
		pcCursedLand->SetFileName("Field\\Desert\\De-1.ase");
		pcCursedLand->SetMapFileName("Field\\Map\\De-1.tga", "Field\\Title\\De-1t.tga");
		pcCursedLand->SetSky(SCENESKY_Desert_Morning, SCENESKY_Desert_Noon, SCENESKY_Desert_Night);
		pcCursedLand->SetType(MAPTYPE_Desert);
		pcCursedLand->SetBackgroundMusicID(BACKGROUNDMUSICID_DesertB);
		pcCursedLand->AddSpawn(15005, -1421);
		pcCursedLand->AddSpawn(13306, 2000);
		pcCursedLand->AddSpawn(13083, -2249);
		pcCursedLand->AddBorder(pcOasis, 13466, -5953);
		pcCursedLand->AddBorder(pcNaviskoTown, 20041, -892);

		// 内维斯克
		pcNaviskoTown->SetFileName("Field\\Forest\\village-1.ase");
		pcNaviskoTown->SetMapFileName("Field\\Map\\village-1.tga", "Field\\Title\\village-1t.tga");
		pcNaviskoTown->SetSky(SCENESKY_Desert_Morning, SCENESKY_Desert_Noon, SCENESKY_Desert_Night);
		pcNaviskoTown->SetType(MAPTYPE_Desert);
		pcNaviskoTown->SetBackgroundMusicID(BACKGROUNDMUSICID_Navisko);
		pcNaviskoTown->AddSpawn(22214, -1182);
		pcNaviskoTown->AddSpawn(22214, -1182);
		pcNaviskoTown->AddWarpGate(21936, -1833, 855, 64, 32)->Add(pcNaviskoTown, 21826, -1712, 825, 2);
		pcNaviskoTown->AddBorder(pcBattlefieldOfTheAncients, 27110, -479);
		pcNaviskoTown->AddBorder(pcBellatra, 21840, 1062);
		pcNaviskoTown->AddStaticModel("Field\\forest\\v2-ani01.ase");

		// 绿洲
		pcOasis->SetFileName("Field\\Desert\\De-2.ase");
		pcOasis->SetMapFileName("Field\\Map\\De-2.tga", "Field\\Title\\De-2t.tga");
		pcOasis->SetSky(SCENESKY_Desert_Morning, SCENESKY_Desert_Noon, SCENESKY_Desert_Night);
		pcOasis->SetType(MAPTYPE_Desert);
		pcOasis->SetBackgroundMusicID(BACKGROUNDMUSICID_DesertB);
		pcOasis->AddSpawn(15887, -11161);
		pcOasis->AddSpawn(11859, -11257);
		pcOasis->AddSpawn(16169, -12768);

		// 古代战场
		pcBattlefieldOfTheAncients->SetFileName("Field\\Desert\\De-3.ase");
		pcBattlefieldOfTheAncients->SetMapFileName("Field\\Map\\De-3.tga", "Field\\Title\\De-3t.tga");
		pcBattlefieldOfTheAncients->SetSky(SCENESKY_Desert_Morning, SCENESKY_Desert_Noon, SCENESKY_Desert_Night);
		pcBattlefieldOfTheAncients->SetType(MAPTYPE_Desert);
		pcBattlefieldOfTheAncients->SetBackgroundMusicID(BACKGROUNDMUSICID_DesertB);
		pcBattlefieldOfTheAncients->AddSpawn(34758, -1323);
		pcBattlefieldOfTheAncients->AddSpawn(34758, -1323);
		pcBattlefieldOfTheAncients->AddSpawn(29424, 322);
		pcBattlefieldOfTheAncients->AddWarpGate(36128, -2162, 804, 64, 32)->Add(pcCursedTempleF1, -11088, -41570, 343);
		pcBattlefieldOfTheAncients->AddBorder(pcForbiddenLand, 34372, 4277);

		// 封印之地
		pcForbiddenLand->SetFileName("Field\\Desert\\De-4.ase");
		pcForbiddenLand->SetMapFileName("Field\\Map\\De-4.tga", "Field\\Title\\De-4t.tga");
		pcForbiddenLand->SetSky(SCENESKY_Desert_Morning, SCENESKY_Desert_Noon, SCENESKY_Desert_Night);
		pcForbiddenLand->SetType(MAPTYPE_Desert);
		pcForbiddenLand->SetBackgroundMusicID(BACKGROUNDMUSICID_DesertB);
		pcForbiddenLand->AddSpawn(43988, 12053);
		pcForbiddenLand->AddWarpGate(33979, 6080, 969, 64, 32)->Add(pcForbiddenLand, 34100, 6214, 940, 2);
		pcForbiddenLand->AddBorder(pcRailwayOfChaos, 44545, 13063);
		pcForbiddenLand->AddStaticModel("Field\\desert\\d4-ani01.ase");

		// 古代地牢1
		pcAncientPrisonF1->SetFileName("Field\\Dungeon\\dun-1.ase");
		pcAncientPrisonF1->SetMapFileName("Field\\Map\\dun-1.tga", "Field\\Title\\dun-1t.tga");
		pcAncientPrisonF1->SetType(MAPTYPE_Dungeon);
		pcAncientPrisonF1->SetBackgroundMusicID(BACKGROUNDMUSICID_Dungeon);
		pcAncientPrisonF1->AddSpawn(-15384, -24310);
		pcAncientPrisonF1->AddWarpGate(-15388, -24073, 100, 64, 32)->Add(pcForgottenLand, 16649, 15238, 501);
		pcAncientPrisonF1->AddWarpGate(-15305, -28824, 1, 64, 32)->Add(pcAncientPrisonF2, -6027, -26881, 99);
		pcAncientPrisonF1->AddSound(-15385, 100, -24949, 128, 0);
		pcAncientPrisonF1->AddStaticModel("Field\\dungeon\\dun-1-wheel.ase");

		// 古代地牢2
		pcAncientPrisonF2->SetFileName("Field\\Dungeon\\dun-2.ase");
		pcAncientPrisonF2->SetMapFileName("Field\\Map\\dun-2.tga", "Field\\Title\\dun-2t.tga");
		pcAncientPrisonF2->SetType(MAPTYPE_Dungeon);
		pcAncientPrisonF2->SetBackgroundMusicID(BACKGROUNDMUSICID_Dungeon);
		pcAncientPrisonF2->AddSpawn(-6108, -26880);
		pcAncientPrisonF2->AddWarpGate(-5908, -26878, 136, 64, 32)->Add(pcAncientPrisonF1, -15314, -28718, 58);
		pcAncientPrisonF2->AddWarpGate(-8019, -25768, 21, 64, 32)->Add(pcAncientPrisonF3, 1810, -28802, 0);
		pcAncientPrisonF2->AddWarpGate(-3918, -27988, 21, 64, 32)->Add(pcAncientPrisonF3, 1810, -28802, 0);

		// 古代地牢3
		pcAncientPrisonF3->SetFileName("Field\\Dungeon\\dun-3.ase");
		pcAncientPrisonF3->SetMapFileName("Field\\Map\\dun-3.tga", "Field\\Title\\dun-3t.tga");
		pcAncientPrisonF3->SetType(MAPTYPE_Dungeon);
		pcAncientPrisonF3->SetBackgroundMusicID(BACKGROUNDMUSICID_Dungeon);
		pcAncientPrisonF3->AddSpawn(1827, -28586);

		auto pWarpGate = pcAncientPrisonF3->AddWarpGate(1810, -28924, 0, 64, 32);
		pWarpGate->Add(pcAncientPrisonF2, -8176, -25775, 77);
		pWarpGate->Add(pcAncientPrisonF2, -3738, -27990, 73);

		// GM房间
		pcChessRoom->SetFileName("Field\\Room\\office.ase");
		pcChessRoom->SetType(MAPTYPE_ChessRoom);
		pcChessRoom->SetBackgroundMusicID(BACKGROUNDMUSICID_Forest);
		pcChessRoom->AddSpawn(-200000, 200000);

		// 黄昏树林
		pcForestOfSpirits->SetFileName("Field\\Forever-fall\\forever-fall-04.ase");
		pcForestOfSpirits->SetMapFileName("Field\\Map\\forever-fall-04.tga", "Field\\Title\\forever-fall-04t.tga");
		pcForestOfSpirits->SetSky(SCENESKY_ForFAll_Morning, SCENESKY_ForFAll_Noon, SCENESKY_ForFAll_Night);
		pcForestOfSpirits->SetType(MAPTYPE_Forest);
		pcForestOfSpirits->SetBackgroundMusicID(BACKGROUNDMUSICID_Forest);
		pcForestOfSpirits->AddSpawn(-1583, 37905);
		pcForestOfSpirits->AddSpawn(-2135, 33668);
		pcForestOfSpirits->AddSpawn(4073, 32119);
		pcForestOfSpirits->AddBorder(pcLandOfDusk, -2949, 40442);
		pcForestOfSpirits->AddSound(-1448, 827, 34188, 160, 7);
		pcForestOfSpirits->AddSound(618, 531, 35981, 160, 7);
		pcForestOfSpirits->AddSound(2282, 537, 32355, 160, 20);
		pcForestOfSpirits->AddSound(2597, 793, 30745, 0, 20);
		pcForestOfSpirits->AddSound(2562, 641, 32726, 0, 20);
		pcForestOfSpirits->AddSound(3789, 770, 30062, 0, 20);
		pcForestOfSpirits->AddSound(3698, 909, 34179, 60, 14);

		for (int i = 1; i <= 11; i++)
		{
			pcForestOfSpirits->AddModelEx("Field\\forever-fall\\4ani-%02d.ase", i);
		}

		// 心情树林
		pcLandOfDusk->SetFileName("Field\\Forever-fall\\forever-fall-03.ase");
		pcLandOfDusk->SetMapFileName("Field\\Map\\forever-fall-03.tga", "Field\\Title\\forever-fall-03t.tga");
		pcLandOfDusk->SetSky(SCENESKY_ForFAll_Morning, SCENESKY_ForFAll_Noon, SCENESKY_ForFAll_Night);
		pcLandOfDusk->SetType(MAPTYPE_Forest);
		pcLandOfDusk->SetBackgroundMusicID(BACKGROUNDMUSICID_Forest);
		pcLandOfDusk->AddSpawn(-5823, 43244);
		pcLandOfDusk->AddSpawn(-1516, 45437);
		pcLandOfDusk->AddSpawn(-3586, 42886);
		pcLandOfDusk->AddWarpGate(-4730, 48107, 1173, 64, 32)->Add(pcLandOfDusk, -4615, 48002, 1146, 2);
		pcLandOfDusk->AddWarpGate(-6306, 43241, 779, 64, 32)->Add(pcBeehiveCave, 119025, 35680, 499);
		pcLandOfDusk->AddBorder(pcValleyOfTranquility, -2349, 49830);
		pcLandOfDusk->AddSound(-3573, 861, 42603, 0, 15);
		pcLandOfDusk->AddSound(-2160, 943, 42588, 0, 19);

		for (int i = 1; i <= 7; i++)
		{
			pcLandOfDusk->AddModelEx("Field\\forever-fall\\3ani-%02d.ase", i);
		}

		// 秋之谷
		pcValleyOfTranquility->SetFileName("Field\\Forever-fall\\forever-fall-02.ase");
		pcValleyOfTranquility->SetMapFileName("Field\\Map\\forever-fall-02.tga", "Field\\Title\\forever-fall-02t.tga");
		pcValleyOfTranquility->SetSky(SCENESKY_ForFAll_Morning, SCENESKY_ForFAll_Noon, SCENESKY_ForFAll_Night);
		pcValleyOfTranquility->SetType(MAPTYPE_Forest);
		pcValleyOfTranquility->SetBackgroundMusicID(BACKGROUNDMUSICID_Forest);
		pcValleyOfTranquility->AddSpawn(1691, 52599);
		pcValleyOfTranquility->AddSpawn(-1024, 45437);
		pcValleyOfTranquility->AddSpawn(-1543, 52333);
		pcValleyOfTranquility->AddSpawn(-1310, 54945);
		pcValleyOfTranquility->AddBorder(pcRoadToTheWind, 667, 59371);
		pcValleyOfTranquility->AddSound(-266, 862, 57971, 100, 13);
		pcValleyOfTranquility->AddSound(-5014, 629, 56702, 100, 13);
		pcValleyOfTranquility->AddSound(2153, 772, 53576, 80, 13);
		pcValleyOfTranquility->AddSound(-395, 542, 56521, 80, 13);
		pcValleyOfTranquility->AddSound(-3329, 522, 56469, 20, 15);
		pcValleyOfTranquility->AddSound(-39, 604, 54080, 10, 6);

		for (int i = 1; i <= 5; i++)
		{
			pcValleyOfTranquility->AddModelEx("Field\\forever-fall\\2ani-%02d.ase", i);
		}

		// 风之路
		pcRoadToTheWind->SetFileName("Field\\Forever-fall\\forever-fall-01.ase");
		pcRoadToTheWind->SetMapFileName("Field\\Map\\forever-fall-01.tga", "Field\\Title\\forever-fall-01t.tga");
		pcRoadToTheWind->SetSky(SCENESKY_ForFAll_Morning, SCENESKY_ForFAll_Noon, SCENESKY_ForFAll_Night);
		pcRoadToTheWind->SetType(MAPTYPE_Forest);
		pcRoadToTheWind->SetBackgroundMusicID(BACKGROUNDMUSICID_Forest);
		pcRoadToTheWind->AddSpawn(2032, 71183);
		pcRoadToTheWind->AddSpawn(1875, 69871);
		pcRoadToTheWind->AddSpawn(2637, 60219);
		pcRoadToTheWind->AddWarpGate(1962, 71184, 559, 64, 32)->Add(pcPhillaiTown, 1993, 73134, 449, 1);
		pcRoadToTheWind->AddBorder(pcPhillaiTown, -8508, -10576);
		pcRoadToTheWind->AddSound(2849, 577, 67330, 30, 18);
		pcRoadToTheWind->AddSound(317, 653, 64957, 10, 19);
		pcRoadToTheWind->AddSound(-1166, 779, 63268, 40, 18);
		pcRoadToTheWind->AddSound(-181, 864, 62576, 10, 18);
		pcRoadToTheWind->AddSound(190, 686, 61850, 10, 18);
		pcRoadToTheWind->AddSound(-1070, 671, 61561, 10, 18);
		pcRoadToTheWind->AddSound(1815, 562, 65414, 100, 8);
		pcRoadToTheWind->AddSound(1800, 603, 61149, 100, 8);

		for (int i = 1; i <= 27; i++)
		{
			pcRoadToTheWind->AddModelEx("Field\\forever-fall\\1ani-%02d.ase", i);
		}

		// 菲尔拉
		pcPhillaiTown->SetFileName("Field\\Forever-fall\\pilai.ase");
		pcPhillaiTown->SetMapFileName("Field\\Map\\pilai.tga", "Field\\Title\\pilait.tga");
		pcPhillaiTown->SetSky(SCENESKY_ForFAll_Morning, SCENESKY_ForFAll_Noon, SCENESKY_ForFAll_Night);
		pcPhillaiTown->SetType(MAPTYPE_Town);
		pcPhillaiTown->SetBackgroundMusicID(BACKGROUNDMUSICID_Phillai);
		pcPhillaiTown->AddSpawn(2981, 75486);
		pcPhillaiTown->AddSpawn(2287, 74131);
		pcPhillaiTown->AddSpawn(3547, 75500);
		pcPhillaiTown->AddWarpGate(2000, 72907, 474, 64, 32)->Add(pcRoadToTheWind, 1958, 70922, 536, 1);
		pcPhillaiTown->AddWarpGate(2245, 78259, 745, 64, 32)->Add(pcPhillaiTown, 2252, 78041, 754, 2);
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

		for (int i = 1; i <= 43; i++)
		{
			pcPhillaiTown->AddModelEx("Field\\forever-fall\\piani-%02d.ase", i);
		}

		// 古代神殿1
		pcCursedTempleF1->SetFileName("Field\\Dungeon\\dun-4.ase");
		pcCursedTempleF1->SetMapFileName("Field\\Map\\dun-4.tga", "Field\\Title\\dun-4t.tga");
		pcCursedTempleF1->SetType(MAPTYPE_Dungeon);
		pcCursedTempleF1->SetBackgroundMusicID(BACKGROUNDMUSICID_Dungeon);
		pcCursedTempleF1->AddSpawn(-11108, -41681);

		pcCursedTempleF1->AddWarpGate(-10860, -41666, 398, 64, 32)->Add(pcBattlefieldOfTheAncients, 35872, -2016, 804);
		pWarpGate = pcCursedTempleF1->AddWarpGate(-12089, -40380, 95, 64, 32);
		pWarpGate->Add(pcCursedTempleF2, -2527, -37196, 727);
		pWarpGate->Add(pcCursedTempleF2, -3669, -36444, 727);
		pWarpGate->Add(pcCursedTempleF2, -4795, -37198, 727);
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

		// 古代神殿2
		pcCursedTempleF2->SetFileName("Field\\Dungeon\\dun-5.ase");
		pcCursedTempleF2->SetMapFileName("Field\\Map\\dun-5.tga", "Field\\Title\\dun-5t.tga");
	}
}