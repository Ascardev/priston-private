#include "StdAfx.h"
#include "MapModel.h"

namespace MAP
{
	Model::Model()
	{

	}
	Model::~Model()
	{

	}
	void Model::Init()
	{
		Load();
	}
	void Model::Shutdown()
	{
		for (auto &v : m_vpBaseMap)
		{
			DELET(v);
		}

		m_vpBaseMap.clear();
	}
	void Model::Load()
	{
		auto pcAcasiaForest = AddMap(new BaseMap(MAPID_AcasiaForest, "Acasia Forest"));
		auto pcBambooForest = AddMap(new BaseMap(MAPID_BambooForest, "Bamboo Forest"));
		auto pcGardenOfFreedom = AddMap(new BaseMap(MAPID_GardenOfFreedom, "Garden of Freedom"));
		auto pcRicartenTown = AddMap(new BaseMap(MAPID_RicartenTown, "Ricarten Town"));
		auto pcRefugeOfTheAncients = AddMap(new BaseMap(MAPID_RefugeOfTheAncients, "Refuge of the Ancients"));
		auto pcCastleOfTheLost = AddMap(new BaseMap(MAPID_CastleOfTheLost, "Castle of the Lost"));
		auto pcRuinenVillage = AddMap(new BaseMap(MAPID_RuinenVillage, "Ruinen Village"));
		auto pcForgottenLand = AddMap(new BaseMap(MAPID_ForgottenLand, "Forgotten Land"));
		auto pcCursedLand = AddMap(new BaseMap(MAPID_CursedLand, "Cursed Land"));
		auto pcNaviskoTown = AddMap(new BaseMap(MAPID_NaviskoTown, "Navisko Town"));
		auto pcOasis = AddMap(new BaseMap(MAPID_Oasis, "Oasis"));
		auto pcBattlefieldOfTheAncients = AddMap(new BaseMap(MAPID_AncientsBattlefield, "Battlefield of the Ancients"));
		auto pcForbiddenLand = AddMap(new BaseMap(MAPID_ForbiddenLand, "Forbidden Land"));
		auto pcAncientPrisonF1 = AddMap(new BaseMap(MAPID_AncientPrisonF1, "Ancient Prison 1F"));
		auto pcAncientPrisonF2 = AddMap(new BaseMap(MAPID_AncientPrisonF2, "Ancient Prison 2F"));
		auto pcAncientPrisonF3 = AddMap(new BaseMap(MAPID_AncientPrisonF3, "Ancient Prison 3F"));
		auto pcChessRoom = AddMap(new BaseMap(MAPID_ChessRoom, "Checker (GM) Room"));
		auto pcForestOfSpirits = AddMap(new BaseMap(MAPID_ForestOfSpirits, "Forest of Spirits"));
		auto pcLandOfDusk = AddMap(new BaseMap(MAPID_LandOfDusk, "Land of Dusk"));
		auto pcValleyOfTranquility = AddMap(new BaseMap(MAPID_ValleyOfTranquility, "Valley of Tranquility"));
		auto pcRoadToTheWind = AddMap(new BaseMap(MAPID_RoadToTheWind, "Road to the Wind"));
		auto pcPhillaiTown = AddMap(new BaseMap(MAPID_PhillaiTown, "Pillia Town"));
		auto pcCursedTempleF1 = AddMap(new BaseMap(MAPID_CursedTempleF1, "Cursed Temple 1F"));
		auto pcCursedTempleF2 = AddMap(new BaseMap(MAPID_CursedTempleF2, "Cursed Temple 2F"));
		auto pcMushroomCave = AddMap(new BaseMap(MAPID_MushroomCave, "Cave of Mushrooms"));
		auto pcBeehiveCave = AddMap(new BaseMap(MAPID_BeehiveCave, "Cave of Beehive"));
		auto pcDarkSanctuary = AddMap(new BaseMap(MAPID_DarkSanctuary, "Sanctuary of Darkness"));
		auto pcRailwayOfChaos = AddMap(new BaseMap(MAPID_RailwayOfChaos, "Railway of Chaos"));
		auto pcHeartOfPerum = AddMap(new BaseMap(MAPID_HeartOfPerum, "Heart of Perum"));
		auto pcEura = AddMap(new BaseMap(MAPID_Eura, "Eura"));
		auto pcBellatra = AddMap(new BaseMap(MAPID_Bellatra, "Bellatra Celestial"));
		auto pcGallubiaValley = AddMap(new BaseMap(MAPID_GallubiaValley, "Gallubia Valley"));
		auto pcQuestArena = AddMap(new BaseMap(MAPID_QuestArena, "Quest Arena"));
		auto pcBlessCastle = AddMap(new BaseMap(MAPID_BlessCastle, "Bless Castle"));
		auto pcGreedyLake = AddMap(new BaseMap(MAPID_GreedyLake, "Greedy Lake"));
		auto pcFrozenSanctuary = AddMap(new BaseMap(MAPID_FrozenSanctuary, "Frozen Temple"));
		auto pcKelvezuLair = AddMap(new BaseMap(MAPID_KelvezuLair, "Fire Map"));
		auto pcLandOfChaos = AddMap(new BaseMap(MAPID_LandOfChaos, "Lost Island"));
		auto pcLostTemple = AddMap(new BaseMap(MAPID_LostTemple, "Lost Temple"));
		auto pcDistortedForest = AddMap(new BaseMap(MAPID_GhostCastle, "Ghost Castle"));
		auto pcEndlessTowerF1 = AddMap(new BaseMap(MAPID_EndlessTowerF1, "Endless Tower 1F"));
		auto pcEndlessTowerF2 = AddMap(new BaseMap(MAPID_EndlessTowerF2, "Endless Tower 2F"));
		auto pcCursedTempleF3 = AddMap(new BaseMap(MAPID_CursedTempleF3, "Cursed Temple 3F"));
		auto pcEndlessTowerF3 = AddMap(new BaseMap(MAPID_EndlessTowerF3, "Endless Tower 3F"));
		auto pcIceMineF1 = AddMap(new BaseMap(MAPID_IceMineF1, "Ice Mine 1F"));
		auto pcSlab = AddMap(new BaseMap(MAPID_SecretLaboratory, "Secret Laboratory"));
		auto pcAncientWeapon = AddMap(new BaseMap(MAPID_AncientWeapon, "Anciient Weapon"));
		auto pcShipyardRuins = AddMap(new BaseMap(MAPID_ShipyardRuins, "Shipyard Ruins"));
		auto pcMysteryForest3 = AddMap(new BaseMap(MAPID_MysteryForest3, "Mystery Forest 3"));
		auto pcMysteryForest2 = AddMap(new BaseMap(MAPID_MysteryForest2, "Mystery Forest 2"));
		auto pcMysteryForest1 = AddMap(new BaseMap(MAPID_MysteryForest1, "Mystery Forest 1"));
		auto pcAtlantisTown = AddMap(new BaseMap(MAPID_Atlantis, "Atlantis Town"));
		auto pcBattleTown = AddMap(new BaseMap(MAPID_BattleTown, "Battle Town"));
		auto pcMysteryDesert3 = AddMap(new BaseMap(MAPID_MysteryDesert3, "Mystery Desert 3"));
		auto pcMysteryDesert2 = AddMap(new BaseMap(MAPID_MysteryDesert2, "Mystery Desert 2"));
		auto pcMysteryDesert1 = AddMap(new BaseMap(MAPID_MysteryDesert1, "Mystery Desert 1"));
		auto pcMiraRemains = AddMap(new BaseMap(MAPID_MiraRemains, "Mira Remains"));
		auto pcT5QuestArena = AddMap(new BaseMap(MAPID_T5QuestArena, "T5 Quest Arena"));

		// 胶之林
		pcAcasiaForest->SetFileName("Field\\Forest\\fore-3.ase");
		pcAcasiaForest->SetMinMapName("Field\\Map\\fore-3.tga");
		pcAcasiaForest->SetTitleMapName("Field\\Title\\fore-3t.tga");
		pcAcasiaForest->SetType(MAPTYPE_Forest);
		pcAcasiaForest->SetSky(MAPSKY_Forest_Morning, MAPSKY_Forest_Noon, MAPSKY_Forest_Night);
		pcAcasiaForest->SetBackgroundMusicID(BACKGROUNDMUSICID_Forest);
		pcAcasiaForest->SetCenter(-16419, -7054);
		pcAcasiaForest->AddSpawn(-10585, -11810);
		pcAcasiaForest->AddSpawn(-13659, -9753);
		pcAcasiaForest->AddTelePort(-16638, -6737, 267, 64, 32)->Add(pcMushroomCave, 119112, 26028, 510);
		pcAcasiaForest->AddBorder(pcBambooForest, -8508, -10576);
		pcAcasiaForest->AddSound(-13819, 226, -8950, 100, 15);

		for (int i = 1; i <= 14; i++)
		{
			pcAcasiaForest->AddModelEx("Field\\Forset\\3ani-%02d.ase", i);
		}

		// 竹之林

		pcBambooForest->SetFileName("Field\\Forest\\fore-2.ase");
		pcBambooForest->SetMinMapName("Field\\Map\\fore-2.tga");
		pcBambooForest->SetTitleMapName("Field\\Title\\fore-2t.tga");
		pcBambooForest->SetType(MAPTYPE_Forest);
		pcBambooForest->SetSky(MAPSKY_Forest_Morning, MAPSKY_Forest_Noon, MAPSKY_Forest_Night);
		pcBambooForest->SetBackgroundMusicID(BACKGROUNDMUSICID_Forest);
		pcBambooForest->AddStaticModel("Field\\Forset\\2ani-04.ase");
		pcBambooForest->SetCenter(-5427, -9915);
		pcBambooForest->AddSpawn(-2272, -10314);
		pcBambooForest->AddSpawn(-7192, -11175);
		pcBambooForest->AddBorder(pcGardenOfFreedom, -292, -9548);
		pcBambooForest->AddSound(-3775, 171, -14447, 160, 13);
		pcBambooForest->AddTelePort(-3408, -12447, 251, 64, 32)->Add(pcBambooForest, -3265, -12583, 214, 2);

		// 自由庭院

		pcGardenOfFreedom->SetFileName("Field\\Forest\\fore-1.ase");
		pcGardenOfFreedom->SetMinMapName("Field\\Map\\fore-1.tga");
		pcGardenOfFreedom->SetTitleMapName("Field\\Title\\fore-1t.tga");
		pcGardenOfFreedom->SetType(MAPTYPE_Forest);
		pcGardenOfFreedom->SetSky(MAPSKY_Forest_Morning, MAPSKY_Forest_Noon, MAPSKY_Forest_Night);
		pcGardenOfFreedom->SetBackgroundMusicID(BACKGROUNDMUSICID_Forest);
		pcGardenOfFreedom->SetCenter(4184, -11016);
		pcGardenOfFreedom->AddSpawn(1350, -13672);
		pcGardenOfFreedom->AddSpawn(1761, -10815);
		pcGardenOfFreedom->AddSpawn(4777, -10916);
		pcGardenOfFreedom->AddBorder(pcRefugeOfTheAncients, 4844, -6835);
		pcGardenOfFreedom->AddBorder(pcRicartenTown, 2275, -14828);

		// 理查登

		pcRicartenTown->SetFileName("Field\\Ricarten\\village-2.ase");
		pcRicartenTown->SetMinMapName("Field\\Map\\village-2.tga");
		pcRicartenTown->SetTitleMapName("Field\\Title\\village-2t.tga");
		pcRicartenTown->SetType(MAPTYPE_Town);
		pcRicartenTown->SetSky(MAPSKY_Forest_Morning, MAPSKY_Forest_Noon, MAPSKY_Forest_Night);
		pcRicartenTown->SetBackgroundMusicID(BACKGROUNDMUSICID_Ricarten);

		for (int i = 1; i <= 14; i++)
		{
			pcRicartenTown->AddModelEx("Field\\Ricarten\\v-ani%02d.ase", i);
		}

		pcRicartenTown->SetCenter(2596, -18738);
		pcRicartenTown->AddSpawn(2592, -18566);
		pcRicartenTown->AddSpawn(-1047, -16973);
		pcRicartenTown->AddSound(-1006, 170, -17835, 80, 27);
		pcRicartenTown->AddSound(2632, 321, -17285, 80, 27);
		pcRicartenTown->AddTelePort(734, -20119, 312, 64, 32)->Add(pcRicartenTown, 822, -19956, 254, 2);
		pcRicartenTown->AddTelePort(2597, -18243, 236, 32, 32)->Add(pcT5QuestArena, 198282, 240400, 1502);

		// 废墟墓地

		pcRefugeOfTheAncients->SetFileName("Field\\Ruin\\ruin-4.ase");
		pcRefugeOfTheAncients->SetMinMapName("Field\\Map\\ruin-4.tga");
		pcRefugeOfTheAncients->SetTitleMapName("Field\\Title\\ruin-4t.tga");
		pcRefugeOfTheAncients->SetType(MAPTYPE_Wasteland);
		pcRefugeOfTheAncients->SetSky(MAPSKY_Wasteland_Morning1, MAPSKY_Wasteland_Noon, MAPSKY_Wasteland_Night);
		pcRefugeOfTheAncients->SetBackgroundMusicID(BACKGROUNDMUSICID_DesertB);
		pcRefugeOfTheAncients->SetCenter(1384, -918);
		pcRefugeOfTheAncients->AddSpawn(2578, -5124);
		pcRefugeOfTheAncients->AddSpawn(1873, 3060);

		pcRefugeOfTheAncients->AddBorder(pcCastleOfTheLost, 410, 4902);

		// 废墟

		pcCastleOfTheLost->SetFileName("Field\\Ruin\\ruin-3.ase");
		pcCastleOfTheLost->SetMinMapName("Field\\Map\\ruin-3.tga");
		pcCastleOfTheLost->SetTitleMapName("Field\\Title\\ruin-3t.tga");
		pcCastleOfTheLost->SetType(MAPTYPE_Wasteland);
		pcCastleOfTheLost->SetSky(MAPSKY_Wasteland_Morning1, MAPSKY_Wasteland_Noon, MAPSKY_Wasteland_Night);
		pcCastleOfTheLost->SetBackgroundMusicID(BACKGROUNDMUSICID_DesertB);
		pcCastleOfTheLost->SetCenter(4953, 10922);
		pcCastleOfTheLost->AddSpawn(875, 7910);
		pcCastleOfTheLost->AddSpawn(1576, 14307);
		pcCastleOfTheLost->AddBorder(pcRuinenVillage, 3051, 16124);

		// 废墟村庄

		pcRuinenVillage->SetFileName("Field\\Ruin\\ruin-2.ase");
		pcRuinenVillage->SetMinMapName("Field\\Map\\ruin-2.tga");
		pcRuinenVillage->SetTitleMapName("Field\\Title\\ruin-2t.tga");
		pcRuinenVillage->SetType(MAPTYPE_Wasteland);
		pcRuinenVillage->SetSky(MAPSKY_Wasteland_Morning2, MAPSKY_Wasteland_Noon, MAPSKY_Wasteland_Night);
		pcRuinenVillage->SetBackgroundMusicID(BACKGROUNDMUSICID_DesertB);
		pcRuinenVillage->SetCenter(7459, 23984);
		pcRuinenVillage->AddSpawn(3976, 19645);
		pcRuinenVillage->AddSpawn(5832, 23751);
		pcRuinenVillage->AddSpawn(5615, 25117);
		pcRuinenVillage->AddStaticModel("Field\\Ruin\\ruin_ani01.ase");
		pcRuinenVillage->AddTelePort(4428, 22511, 845, 64, 32)->Add(pcRuinenVillage, 4547, 22616, 817, 2);
		pcRuinenVillage->AddBorder(pcForgottenLand, 10019, 18031);
		pcRuinenVillage->AddBorder(pcForestOfSpirits, 4470, 27774);
		pcRuinenVillage->AddBorder(pcGreedyLake, 12713, 23409);

		// 遗忘之地

		pcForgottenLand->SetFileName("Field\\Ruin\\ruin-1.ase");
		pcForgottenLand->SetMinMapName("Field\\Map\\ruin-1.tga");
		pcForgottenLand->SetTitleMapName("Field\\Title\\ruin-1t.tga");
		pcForgottenLand->SetType(MAPTYPE_Wasteland);
		pcForgottenLand->SetSky(MAPSKY_Wasteland_Morning2, MAPSKY_Wasteland_Noon, MAPSKY_Wasteland_Night);
		pcForgottenLand->SetBackgroundMusicID(BACKGROUNDMUSICID_DesertB);
		pcForgottenLand->SetCenter(16362, 14959);
		pcForgottenLand->AddSpawn(12242, 16034);
		pcForgottenLand->AddSpawn(12194, 8969);
		pcForgottenLand->AddBorder(pcCursedLand, 13319, 7102);
		pcForgottenLand->AddTelePort(16809, 15407, 501, 128, 32)->Add(pcAncientPrisonF1, -15395, -24185, 0);

		// 诅咒之地

		pcCursedLand->SetFileName("Field\\Desert\\De-1.ase");
		pcCursedLand->SetMinMapName("Field\\Map\\De-1.tga");
		pcCursedLand->SetTitleMapName("Field\\Title\\De-1t.tga");
		pcCursedLand->SetType(MAPTYPE_Desert);
		pcCursedLand->SetSky(MAPSKY_Desert_Morning, MAPSKY_Desert_Noon, MAPSKY_Desert_Night);
		pcCursedLand->SetBackgroundMusicID(BACKGROUNDMUSICID_DesertB);
		pcCursedLand->SetCenter(15005, -1421);
		pcCursedLand->AddSpawn(13306, 2000);
		pcCursedLand->AddSpawn(13083, -2249);
		pcCursedLand->AddBorder(pcOasis, 13466, -5953);
		pcCursedLand->AddBorder(pcNaviskoTown, 20041, -892);

		// 内维斯克

		pcNaviskoTown->SetFileName("Field\\Forest\\village-1.ase");
		pcNaviskoTown->SetMinMapName("Field\\Map\\village-1.tga");
		pcNaviskoTown->SetTitleMapName("Field\\Title\\village-1t.tga");
		pcNaviskoTown->SetType(MAPTYPE_Desert);
		pcNaviskoTown->SetSky(MAPSKY_Desert_Morning, MAPSKY_Desert_Noon, MAPSKY_Desert_Night);
		pcNaviskoTown->SetBackgroundMusicID(BACKGROUNDMUSICID_Navisko);
		pcNaviskoTown->SetCenter(22214, -1182);
		pcNaviskoTown->AddSpawn(22214, -1182);
		pcNaviskoTown->AddStaticModel("Field\\forest\\v2-ani01.ase");
		pcNaviskoTown->AddBorder(pcBattlefieldOfTheAncients, 27110, -479);
		pcNaviskoTown->AddBorder(pcBellatra, 21840, 1062);
		pcNaviskoTown->AddTelePort(21936, -1833, 855, 64, 32)->Add(pcNaviskoTown, 21826, -1712, 825, 2);

		// 绿洲

		pcOasis->SetFileName("Field\\Desert\\De-2.ase");
		pcOasis->SetMinMapName("Field\\Map\\De-2.tga");
		pcOasis->SetTitleMapName("Field\\Title\\De-2t.tga");
		pcOasis->SetType(MAPTYPE_Desert);
		pcOasis->SetSky(MAPSKY_Desert_Morning, MAPSKY_Desert_Noon, MAPSKY_Desert_Night);
		pcOasis->SetBackgroundMusicID(BACKGROUNDMUSICID_DesertB);
		pcOasis->SetCenter(15887, -11161);
		pcOasis->AddSpawn(11859, -11257);
		pcOasis->AddSpawn(16169, -12768);

		// 古代战场

		pcBattlefieldOfTheAncients->SetFileName("Field\\Desert\\De-3.ase");
		pcBattlefieldOfTheAncients->SetMinMapName("Field\\Map\\De-3.tga");
		pcBattlefieldOfTheAncients->SetTitleMapName("Field\\Title\\De-3t.tga");
		pcBattlefieldOfTheAncients->SetType(MAPTYPE_Desert);
		pcBattlefieldOfTheAncients->SetSky(MAPSKY_Desert_Morning, MAPSKY_Desert_Noon, MAPSKY_Desert_Night);
		pcBattlefieldOfTheAncients->SetBackgroundMusicID(BACKGROUNDMUSICID_DesertB);
		pcBattlefieldOfTheAncients->SetCenter(34758, -1323);
		pcBattlefieldOfTheAncients->AddSpawn(34758, -1323);
		pcBattlefieldOfTheAncients->AddSpawn(29424, 322);
		pcBattlefieldOfTheAncients->AddBorder(pcForbiddenLand, 34372, 4277);
		pcBattlefieldOfTheAncients->AddTelePort(36128, -2162, 804, 64, 32)->Add(pcCursedTempleF1, -11088, -41570, 343);

		// 封印之地

		pcForbiddenLand->SetFileName("Field\\Desert\\De-4.ase");
		pcForbiddenLand->SetMinMapName("Field\\Map\\De-4.tga");
		pcForbiddenLand->SetTitleMapName("Field\\Title\\De-4t.tga");
		pcForbiddenLand->SetType(MAPTYPE_Desert);
		pcForbiddenLand->SetSky(MAPSKY_Desert_Morning, MAPSKY_Desert_Noon, MAPSKY_Desert_Night);
		pcForbiddenLand->SetBackgroundMusicID(BACKGROUNDMUSICID_DesertB);
		pcForbiddenLand->SetCenter(43988, 12053);
		pcForbiddenLand->AddStaticModel("Field\\desert\\d4-ani01.ase");
		pcForbiddenLand->AddSpawn(33740, 6491);
		pcForbiddenLand->AddSpawn(40691, 11056);
		pcForbiddenLand->AddBorder(pcRailwayOfChaos, 44545, 13063);
		pcForbiddenLand->AddTelePort(33979, 6080, 969, 64, 32)->Add(pcForbiddenLand, 34100, 6214, 940, 2);

		// 古代地牢1

		pcAncientPrisonF1->SetFileName("Field\\Dungeon\\dun-1.ase");
		pcAncientPrisonF1->SetMinMapName("Field\\Map\\dun-1.tga");
		pcAncientPrisonF1->SetTitleMapName("Field\\Title\\dun-1t.tga");
		pcAncientPrisonF1->SetType(MAPTYPE_Dungeon);
		pcAncientPrisonF1->SetSky(MAPSKY_None, MAPSKY_None, MAPSKY_None);
		pcAncientPrisonF1->SetBackgroundMusicID(BACKGROUNDMUSICID_Dungeon);
		pcAncientPrisonF1->AddStaticModel("Field\\dungeon\\dun-1-wheel.ase");
		pcAncientPrisonF1->SetCenter(-15384, -24310);
		pcAncientPrisonF1->AddTelePort(-15388, -24073, 100, 64, 32)->Add(pcForgottenLand, 16649, 15238, 501);
		pcAncientPrisonF1->AddTelePort(-15305, -28824, 1, 64, 2)->Add(pcAncientPrisonF2, -6027, -26881, 99);
		pcAncientPrisonF1->AddSound(-15385, 100, -24949, 128, 0);

		// 古代地牢2

		pcAncientPrisonF2->SetFileName("Field\\Dungeon\\dun-2.ase");
		pcAncientPrisonF2->SetMinMapName("Field\\Map\\dun-2.tga");
		pcAncientPrisonF2->SetTitleMapName("Field\\Title\\dun-2t.tga");
		pcAncientPrisonF2->SetType(MAPTYPE_Dungeon);
		pcAncientPrisonF2->SetSky(MAPSKY_None, MAPSKY_None, MAPSKY_None);
		pcAncientPrisonF2->SetBackgroundMusicID(BACKGROUNDMUSICID_Dungeon);
		pcAncientPrisonF2->SetCenter(-6108, -26880);
		pcAncientPrisonF2->AddTelePort(-5908, -26878, 136, 64, 32)->Add(pcAncientPrisonF1, -15314, -28718, 58);
		pcAncientPrisonF2->AddTelePort(-8019, -25768, 21, 64, 32)->Add(pcAncientPrisonF3, 1810, -28802, 0);
		pcAncientPrisonF2->AddTelePort(-3918, -27988, 21, 64, 32)->Add(pcAncientPrisonF3, 1810, -28802, 0);

		// 古代地牢3

		pcAncientPrisonF3->SetFileName("Field\\Dungeon\\dun-3.ase");
		pcAncientPrisonF3->SetMinMapName("Field\\Map\\dun-3.tga");
		pcAncientPrisonF3->SetTitleMapName("Field\\Title\\dun-3t.tga");
		pcAncientPrisonF3->SetType(MAPTYPE_Dungeon);
		pcAncientPrisonF3->SetSky(MAPSKY_None, MAPSKY_None, MAPSKY_None);
		pcAncientPrisonF3->SetBackgroundMusicID(BACKGROUNDMUSICID_Dungeon);
		pcAncientPrisonF3->SetCenter(1827, -28586);
		auto pTelePort = pcAncientPrisonF3->AddTelePort(1810, -28924, 0, 64, 32);

		pTelePort->Add(pcAncientPrisonF2, -8176, -25775, 77);
		pTelePort->Add(pcAncientPrisonF2, -3738, -27990, 73);

		// GM房间

		pcChessRoom->SetFileName("Field\\Room\\office.ase");
		pcChessRoom->SetType(MAPTYPE_ChessRoom);
		pcChessRoom->SetSky(MAPSKY_None, MAPSKY_None, MAPSKY_None);
		pcChessRoom->SetBackgroundMusicID(BACKGROUNDMUSICID_Forest);
		pcChessRoom->SetCenter(-200000, 200000);

		// 黄昏树林

		pcForestOfSpirits->SetFileName("Field\\Forever-fall\\forever-fall-04.ase");
		pcForestOfSpirits->SetMinMapName("Field\\Map\\forever-fall-04.tga");
		pcForestOfSpirits->SetTitleMapName("Field\\Title\\forever-fall-04t.tga");
		pcForestOfSpirits->SetType(MAPTYPE_Forest);
		pcForestOfSpirits->SetSky(MAPSKY_ForFAll_Morning, MAPSKY_ForFAll_Noon, MAPSKY_ForFAll_Night);
		pcForestOfSpirits->SetBackgroundMusicID(BACKGROUNDMUSICID_Forest);
		pcForestOfSpirits->SetCenter(-1583, 37905);
		pcForestOfSpirits->AddSpawn(-2135, 33668);
		pcForestOfSpirits->AddSpawn(4073, 32119);

		for (int i = 1; i <= 11; i++)
		{
			pcForestOfSpirits->AddModelEx("Field\\forever-fall\\4ani-%02d.ase", i);
		}

		pcForestOfSpirits->AddBorder(pcLandOfDusk, -2949, 40442);
		pcForestOfSpirits->AddSound(-1448, 827, 34188, 160, 7);
		pcForestOfSpirits->AddSound(618, 531, 35981, 160, 7);
		pcForestOfSpirits->AddSound(2282, 537, 32355, 160, 20);
		pcForestOfSpirits->AddSound(2597, 793, 30745, 0, 20);
		pcForestOfSpirits->AddSound(2562, 641, 32726, 0, 20);
		pcForestOfSpirits->AddSound(3789, 770, 30062, 0, 20);
		pcForestOfSpirits->AddSound(3698, 909, 34179, 60, 14);

		// 心情树林

		pcLandOfDusk->SetFileName("Field\\Forever-fall\\forever-fall-03.ase");
		pcLandOfDusk->SetMinMapName("Field\\Map\\forever-fall-03.tga");
		pcLandOfDusk->SetTitleMapName("Field\\Title\\forever-fall-03t.tga");
		pcLandOfDusk->SetType(MAPTYPE_Forest);
		pcLandOfDusk->SetSky(MAPSKY_ForFAll_Morning, MAPSKY_ForFAll_Noon, MAPSKY_ForFAll_Night);
		pcLandOfDusk->SetBackgroundMusicID(BACKGROUNDMUSICID_Forest);
		pcLandOfDusk->SetCenter(-5823, 43244);
		pcLandOfDusk->AddSpawn(-1516, 45437);
		pcLandOfDusk->AddSpawn(-3586, 42886);

		for (int i = 1; i <= 7; i++)
		{
			pcLandOfDusk->AddModelEx("Field\\forever-fall\\3ani-%02d.ase", i);
		}

		pcLandOfDusk->AddBorder(pcValleyOfTranquility, -2349, 49830);
		pcLandOfDusk->AddSound(-3573, 861, 42603, 0, 15);
		pcLandOfDusk->AddSound(-2160, 943, 42588, 0, 19);
		pcLandOfDusk->AddTelePort(-4730, 48107, 1173, 64, 32)->Add(pcLandOfDusk, -4615, 48002, 1146, 2);
		pcLandOfDusk->AddTelePort(-6306, 43241, 779, 64, 32)->Add(pcBeehiveCave, 119025, 35680, 499);

		// 秋之谷

		pcValleyOfTranquility->SetFileName("Field\\Forever-fall\\forever-fall-02.ase");
		pcValleyOfTranquility->SetMinMapName("Field\\Map\\forever-fall-02.tga");
		pcValleyOfTranquility->SetTitleMapName("Field\\Title\\forever-fall-02t.tga");
		pcValleyOfTranquility->SetType(MAPTYPE_Forest);
		pcValleyOfTranquility->SetSky(MAPSKY_ForFAll_Morning, MAPSKY_ForFAll_Noon, MAPSKY_ForFAll_Night);
		pcValleyOfTranquility->SetBackgroundMusicID(BACKGROUNDMUSICID_Forest);
		pcValleyOfTranquility->SetCenter(1691, 52599);
		pcValleyOfTranquility->AddSpawn(-1024, 45437);
		pcValleyOfTranquility->AddSpawn(-1543, 52333);
		pcValleyOfTranquility->AddSpawn(-1310, 54945);

		for (int i = 1; i <= 5; i++)
		{
			pcValleyOfTranquility->AddModelEx("Field\\forever-fall\\2ani-%02d.ase", i);
		}

		pcValleyOfTranquility->AddBorder(pcRoadToTheWind, 667, 59371);

		pcValleyOfTranquility->AddSound(-266, 862, 57971, 100, 13);
		pcValleyOfTranquility->AddSound(-5014, 629, 56702, 100, 13);
		pcValleyOfTranquility->AddSound(2153, 772, 53576, 80, 13);
		pcValleyOfTranquility->AddSound(-395, 542, 56521, 80, 13);
		pcValleyOfTranquility->AddSound(-3329, 522, 56469, 20, 15);
		pcValleyOfTranquility->AddSound(-39, 604, 54080, 10, 6);

		// 风之路

		pcRoadToTheWind->SetFileName("Field\\Forever-fall\\forever-fall-01.ase");
		pcRoadToTheWind->SetMinMapName("Field\\Map\\forever-fall-01.tga");
		pcRoadToTheWind->SetTitleMapName("Field\\Title\\forever-fall-01t.tga");

		pcRoadToTheWind->SetType(MAPTYPE_Forest);
		pcRoadToTheWind->SetSky(MAPSKY_ForFAll_Morning, MAPSKY_ForFAll_Noon, MAPSKY_ForFAll_Night);
		pcRoadToTheWind->SetBackgroundMusicID(BACKGROUNDMUSICID_Forest);

		pcRoadToTheWind->SetCenter(2032, 71183);
		pcRoadToTheWind->AddSpawn(1875, 69871);
		pcRoadToTheWind->AddSpawn(2637, 60219);

		pcRoadToTheWind->AddBorder(pcPhillaiTown, -8508, -10576);

		for (int i = 1; i <= 27; i++)
		{
			pcRoadToTheWind->AddModelEx("Field\\forever-fall\\1ani-%02d.ase", i);
		}

		pcRoadToTheWind->AddTelePort(1962, 71184, 559, 64, 32)->Add(pcPhillaiTown, 1993, 73134, 449, 1);

		pcRoadToTheWind->AddSound(2849, 577, 67330, 30, 18);
		pcRoadToTheWind->AddSound(317, 653, 64957, 10, 19);
		pcRoadToTheWind->AddSound(-1166, 779, 63268, 40, 18);
		pcRoadToTheWind->AddSound(-181, 864, 62576, 10, 18);
		pcRoadToTheWind->AddSound(190, 686, 61850, 10, 18);
		pcRoadToTheWind->AddSound(-1070, 671, 61561, 10, 18);
		pcRoadToTheWind->AddSound(1815, 562, 65414, 100, 8);
		pcRoadToTheWind->AddSound(1800, 603, 61149, 100, 8);

		// 菲尔拉

		pcPhillaiTown->SetFileName("Field\\Forever-fall\\pilai.ase");
		pcPhillaiTown->SetMinMapName("Field\\Map\\pilai.tga");
		pcPhillaiTown->SetTitleMapName("Field\\Title\\pilait.tga");

		pcPhillaiTown->SetType(MAPTYPE_Town);
		pcPhillaiTown->SetSky(MAPSKY_ForFAll_Morning, MAPSKY_ForFAll_Noon, MAPSKY_ForFAll_Night);
		pcPhillaiTown->SetBackgroundMusicID(BACKGROUNDMUSICID_Phillai);

		pcPhillaiTown->SetCenter(2981, 75486);

		pcPhillaiTown->AddSpawn(2287, 74131);
		pcPhillaiTown->AddSpawn(3547, 75500);

		for (int i = 1; i <= 43; i++)
		{
			pcPhillaiTown->AddModelEx("Field\\forever-fall\\piani-%02d.ase", i);
		}

		pcPhillaiTown->AddTelePort(2000, 72907, 474, 64, 32)->Add(pcRoadToTheWind, 1958, 70922, 536, 1);
		pcPhillaiTown->AddTelePort(2245, 78259, 745, 64, 32)->Add(pcPhillaiTown, 2252, 78041, 754, 2);

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

		pcCursedTempleF1->SetFileName("Field\\Dungeon\\dun-4.ase");
		pcCursedTempleF1->SetMinMapName("Field\\Map\\dun-4.tga");
		pcCursedTempleF1->SetTitleMapName("Field\\Title\\dun-4t.tga");

		pcCursedTempleF1->SetType(MAPTYPE_Dungeon);
		pcCursedTempleF1->SetSky(MAPSKY_None, MAPSKY_None, MAPSKY_None);
		pcCursedTempleF1->SetBackgroundMusicID(BACKGROUNDMUSICID_Dungeon);

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

		pcCursedTempleF1->SetCenter(-11108, -41681);
		pcCursedTempleF1->AddTelePort(-10860, -41666, 398, 64, 32)->Add(pcBattlefieldOfTheAncients, 35872, -2016, 804);

		pTelePort = pcCursedTempleF1->AddTelePort(-12089, -40380, 95, 64, 32);
		pTelePort->Add(pcCursedTempleF2, -2527, -37196, 727);
		pTelePort->Add(pcCursedTempleF2, -3669, -36444, 727);
		pTelePort->Add(pcCursedTempleF2, -4795, -37198, 727);

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

		// 晦气寺庙2

		pcCursedTempleF2->SetFileName("Field\\Dungeon\\dun-5.ase");
		pcCursedTempleF2->SetMinMapName("Field\\Map\\dun-5.tga");
		pcCursedTempleF2->SetTitleMapName("Field\\Title\\dun-5t.tga");
		pcCursedTempleF2->SetType(MAPTYPE_Dungeon);
		pcCursedTempleF2->SetSky(MAPSKY_None, MAPSKY_None, MAPSKY_None);
		pcCursedTempleF2->SetBackgroundMusicID(BACKGROUNDMUSICID_Dungeon);
		pcCursedTempleF2->SetCenter(-3675, -36597);

		for (int i = 1; i <= 22; i++)
		{
			pcCursedTempleF2->AddModelEx("Field\\dungeon\\dun-5-ani-%02d.ase", i);
		}

		pcCursedTempleF2->AddSound(-3660, 730, -36915, 40, 23);
		pcCursedTempleF2->AddSound(-2166, 732, -36125, 0, 24);
		pcCursedTempleF2->AddSound(-5150, 732, -36123, 0, 24);
		pcCursedTempleF2->AddSound(-6175, 762, -41850, 0, 24);
		pcCursedTempleF2->AddSound(-1239, 762, -41850, 0, 24);
		pcCursedTempleF2->AddSound(-1251, 794, -38207, 0, 24);
		pcCursedTempleF2->AddSound(-2424, 732, -38229, 0, 7);
		pcCursedTempleF2->AddSound(-3611, 885, -39747, 0, 7);
		pcCursedTempleF2->AddSound(-4798, 732, -38212, 0, 7);
		pcCursedTempleF2->AddTelePort(-3665, -36334, 762, 64, 32)->Add(pcCursedTempleF1, -12073, -40701, 95);
		pcCursedTempleF2->AddTelePort(-4895, -37132, 762, 64, 32)->Add(pcCursedTempleF1, -12073, -40701, 95);
		pcCursedTempleF2->AddTelePort(-2441, -37137, 762, 64, 32)->Add(pcCursedTempleF1, -12073, -40701, 95);
		pcCursedTempleF2->AddTelePort(-3207, -43830, 553, 128, 32)->Add(pcCursedTempleF3, -3660, -45200, 114);// 传送到晦气寺庙3层
		pcCursedTempleF2->AddTelePort(-4025, -43821, 553, 128, 32)->Add(pcCursedTempleF3, -3660, -45200, 114);

		pcMushroomCave->SetFileName("Field\\Cave\\Tcave.ase");
		pcMushroomCave->SetMinMapName("Field\\Map\\Tcave.tga");
		pcMushroomCave->SetTitleMapName("Field\\Title\\Tcavet.tga");
		pcMushroomCave->SetType(MAPTYPE_Dungeon);
		pcMushroomCave->SetSky(MAPSKY_None, MAPSKY_None, MAPSKY_None);
		pcMushroomCave->SetBackgroundMusicID(BACKGROUNDMUSICID_Dungeon);
		pcMushroomCave->SetCenter(120126, 26064);
		pcMushroomCave->AddSpawn(119319, 26034);
		pcMushroomCave->AddSpawn(125606, 24541);
		pcMushroomCave->AddTelePort(125581, 25086, 480, 80, 32)->Add(pcDarkSanctuary, 158627, 20504, 240);
		pcMushroomCave->AddTelePort(118869, 26017, 538, 80, 32)->Add(pcAcasiaForest, -16490, -6930, 298);

		for (int i = 1; i <= 16; i++)
		{
			pcMushroomCave->AddModelEx("Field\\cave\\Tcave_ani%02d.ase", i);
		}

		pcBeehiveCave->SetFileName("Field\\Cave\\Mcave.ase");
		pcBeehiveCave->SetMinMapName("Field\\Map\\Mcave.tga");
		pcBeehiveCave->SetTitleMapName("Field\\Title\\Mcavet.tga");
		pcBeehiveCave->SetType(MAPTYPE_Dungeon);
		pcBeehiveCave->SetSky(MAPSKY_None, MAPSKY_None, MAPSKY_None);
		pcBeehiveCave->SetBackgroundMusicID(BACKGROUNDMUSICID_Dungeon);
		pcBeehiveCave->SetCenter(119966, 35466);
		pcBeehiveCave->AddSpawn(119320, 35680);
		pcBeehiveCave->AddSpawn(124380, 33260);
		pcBeehiveCave->AddTelePort(124391, 32913, 37, 80, 32)->Add(pcDarkSanctuary, 158543, 19557, 290);
		pcBeehiveCave->AddTelePort(118808, 35686, 520, 80, 32)->Add(pcLandOfDusk, -6056, 43245, 787);

		for (int i = 1; i <= 17; i++)
		{
			pcBeehiveCave->AddModelEx("Field\\cave\\Mcave_ani%02d.ase", i);
		}

		pcDarkSanctuary->SetFileName("Field\\Cave\\Dcave.ase");
		pcDarkSanctuary->SetMinMapName("Field\\Map\\Dcave.tga");
		pcDarkSanctuary->SetTitleMapName("Field\\Title\\Dcavet.tga");
		pcDarkSanctuary->SetType(MAPTYPE_Dungeon);
		pcDarkSanctuary->SetSky(MAPSKY_None, MAPSKY_None, MAPSKY_None);
		pcDarkSanctuary->SetBackgroundMusicID(BACKGROUNDMUSICID_Dungeon);
		pcDarkSanctuary->SetCenter(158814, 20070);
		pcDarkSanctuary->AddTelePort(158042, 19525, 330, 120, 32)->Add(pcBeehiveCave, 124396, 33291, 37);
		pcDarkSanctuary->AddTelePort(158023, 20453, 240, 120, 32)->Add(pcMushroomCave, 125566, 24825, 480);

		for (int i = 1; i <= 14; i++)
		{
			pcDarkSanctuary->AddModelEx("Field\\cave\\Dcave_ani%02d.ase", i);
		}

		pcRailwayOfChaos->SetFileName("Field\\Iron\\iron-1.ase");
		pcRailwayOfChaos->SetMinMapName("Field\\Map\\iron-1.tga");
		pcRailwayOfChaos->SetTitleMapName("Field\\Title\\iron-1t.tga");
		pcRailwayOfChaos->SetType(MAPTYPE_Iron);
		pcRailwayOfChaos->SetSky(MAPSKY_Iron_Morning, MAPSKY_Iron_Noon, MAPSKY_Iron_Night);
		pcRailwayOfChaos->SetBackgroundMusicID(BACKGROUNDMUSICID_TRIGGERED);
		pcRailwayOfChaos->SetCenter(47617, 13626);
		pcRailwayOfChaos->AddSpawn(46905, 13478);
		pcRailwayOfChaos->AddSpawn(47357, 20845);
		pcRailwayOfChaos->AddSpawn(46741, 21349);
		pcRailwayOfChaos->AddBorder(pcHeartOfPerum, 45316, 21407);

		for (int i = 1; i <= 11; i++)
		{
			pcRailwayOfChaos->AddStaticModel(FormatString("Field\\iron\\i1-ani%02d_Bip.ase", i), TRUE);
		}
		for (int i = 1; i <= 3; i++)
		{
			pcRailwayOfChaos->AddModelEx("Field\\iron\\iron-ani%02d.ase", i);
		}

		pcHeartOfPerum->SetFileName("Field\\Iron\\iron-2.ase");
		pcHeartOfPerum->SetMinMapName("Field\\Map\\iron-2.tga");
		pcHeartOfPerum->SetTitleMapName("Field\\Title\\iron-2t.tga");

		pcHeartOfPerum->SetType(MAPTYPE_Iron);
		pcHeartOfPerum->SetSky(MAPSKY_Iron_Morning, MAPSKY_Iron_Noon, MAPSKY_Iron_Night);
		pcHeartOfPerum->SetBackgroundMusicID(BACKGROUNDMUSICID_TRIGGERED);

		pcHeartOfPerum->SetCenter(33938, 24229);

		pcHeartOfPerum->AddSpawn(35149, 24326);
		pcHeartOfPerum->AddSpawn(44893, 21380);

		pcHeartOfPerum->AddBorder(pcEura, 33618, 24011);
		pcHeartOfPerum->AddTelePort(39937, 29773, 1469, 200, 200);

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

		pcEura->SetFileName("Field\\Ice\\ice_ura.ase");
		pcEura->SetMinMapName("Field\\Map\\ice_ura.tga");
		pcEura->SetTitleMapName("Field\\Title\\ice_urat.tga");
		pcEura->SetType(MAPTYPE_Ice);
		pcEura->SetSky(MAPSKY_ICE1_Morning, MAPSKY_ICE1_Noon, MAPSKY_ICE1_Night);
		pcEura->SetBackgroundMusicID(BACKGROUNDMUSICID_DesertB);
		pcEura->SetCenter(32621, 23865);
		pcEura->AddStaticModel("Field\\ice\\ice_ani_01.ase");
		pcEura->AddBorder(pcGallubiaValley, 31848, 27225);
		pcEura->AddTelePort(30407, 22232, 1349, 64, 32)->Add(pcEura, 30610, 22164, 1304, 2);

		pcBellatra->SetFileName("Field\\Sod\\sod-1.ase");
		pcBellatra->SetMinMapName("Field\\Map\\sod-1.tga");
		pcBellatra->SetTitleMapName("Field\\Title\\sod-1t.tga");

		pcBellatra->SetType(MAPTYPE_Wasteland);
		pcBellatra->SetSky(MAPSKY_Wasteland_Morning2, MAPSKY_Wasteland_Noon, MAPSKY_Wasteland_Night);
		pcBellatra->SetBackgroundMusicID(BACKGROUNDMUSICID_TRIGGERED);

		pcBellatra->SetCenter(22018, 6569);

		for (int i = 1; i <= 18; i++)
		{
			pcBellatra->AddStaticModel(FormatString("Resources\\Field\\sod\\s-1ani%02d_Bip.ase", i), TRUE);
		}

		pcGallubiaValley->SetFileName("Field\\Ice\\ice1.ase");
		pcGallubiaValley->SetMinMapName("Field\\Map\\ice1.tga");
		pcGallubiaValley->SetTitleMapName("Field\\Title\\ice1t.tga");
		pcGallubiaValley->SetType(MAPTYPE_Ice);
		pcGallubiaValley->SetSky(MAPSKY_ICE1_Morning, MAPSKY_ICE1_Noon, MAPSKY_ICE1_Night);
		pcGallubiaValley->SetBackgroundMusicID(BACKGROUNDMUSICID_Ice);

		pcGallubiaValley->SetCenter(32313, 28529);

		pcGallubiaValley->AddBorder(pcFrozenSanctuary, 33729, 38029);

		pcGallubiaValley->AddStaticModel("Field\\ice\\ice_ani_01.ase");
		pcGallubiaValley->AddStaticModel("Field\\ice\\ice_bip_leewood01.ase");
		pcGallubiaValley->AddStaticModel("Field\\ice\\ice_bip_leewood03.ase");
		pcGallubiaValley->AddStaticModel("Field\\ice\\ice_bip_leewood04.ase");

		for (int i = 1; i <= 7; i++)
		{
			pcGallubiaValley->AddModelEx("Field\\ice\\ice_bip_leaf%02d.ase", i);
		}

		pcGallubiaValley->AddTelePort(35361, 31898, 829, 80, 32)->Add(pcIceMineF1, 18006, -34698, 222);

		pcQuestArena->SetFileName("Field\\Quest\\quest_IV.ase");
		pcQuestArena->SetMinMapName("Field\\Map\\quest_IV.tga");
		pcQuestArena->SetTitleMapName("Field\\Title\\quest_IVt.tga");
		pcQuestArena->SetType(MAPTYPE_Dungeon);
		pcQuestArena->SetSky(MAPSKY_None, MAPSKY_None, MAPSKY_None);
		pcQuestArena->SetBackgroundMusicID(BACKGROUNDMUSICID_Bellatra_78);
		pcQuestArena->SetCenter(22497, 9605);

		pcBlessCastle->SetFileName("Field\\Castle\\castle.ase");
		pcBlessCastle->SetMinMapName("Field\\Map\\castle.tga");
		pcBlessCastle->SetTitleMapName("Field\\Title\\castlet.tga");
		pcBlessCastle->SetType(MAPTYPE_BlessCastle);
		pcBlessCastle->SetSky(MAPSKY_Wasteland_Morning2, MAPSKY_Wasteland_Noon, MAPSKY_Wasteland_Night);
		pcBlessCastle->SetBackgroundMusicID(BACKGROUNDMUSICID_Bellatra_78);
		pcBlessCastle->SetCenter(35225, -23847);
		pcBlessCastle->AddSpawn(33920, -23479);
		pcBlessCastle->AddSpawn(35247, -23355);
		pcBlessCastle->AddSpawn(36164, -23446);
		pcBlessCastle->AddTelePort(32527, -30693, 774, 64, 32)->Add(pcBlessCastle, 32739, -30474, 711, 2);
		pcBlessCastle->AddStaticModel("Field\\castle\\wf_gate_ani.ase");

		for (int i = 1; i <= 6; i++)
		{
			pcBlessCastle->AddModelEx("Field\\castle\\crystal_ani%02d.ase", i);
		}

		pcGreedyLake->SetFileName("Field\\Greedy\\Greedy.ase");
		pcGreedyLake->SetMinMapName("Field\\Map\\Greedy.tga");
		pcGreedyLake->SetTitleMapName("Field\\Title\\Greedyt.tga");
		pcGreedyLake->SetType(MAPTYPE_Ice);
		pcGreedyLake->SetSky(MAPSKY_ICE2_Morning, MAPSKY_ICE2_Noon, MAPSKY_ICE2_Night);
		pcGreedyLake->SetBackgroundMusicID(BACKGROUNDMUSICID_DesertB);
		pcGreedyLake->SetCenter(13930, 23206);

		for (int i = 1; i <= 4; i++)
		{
			pcGreedyLake->AddModelEx("Field\\Greedy\\vane%d_ani.ase", i);
		}

		pcGreedyLake->AddStaticModel("Field\\Greedy\\ani_tail.ase");
		pcGreedyLake->AddStaticModel("Field\\Greedy\\ship_ani.ase");

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

		pcGreedyLake->AddStaticModel("Field\\Greedy\\door.ase");


		pcFrozenSanctuary->SetFileName("Field\\Ice\\ice2.ase");
		pcFrozenSanctuary->SetMinMapName("Field\\Map\\ice2.tga");
		pcFrozenSanctuary->SetTitleMapName("Field\\Title\\ice2t.tga");
		pcFrozenSanctuary->SetType(MAPTYPE_Ice);
		pcFrozenSanctuary->SetSky(MAPSKY_ICE1_Morning, MAPSKY_ICE1_Noon, MAPSKY_ICE1_Night);
		pcFrozenSanctuary->SetBackgroundMusicID(BACKGROUNDMUSICID_Ice);
		pcFrozenSanctuary->SetCenter(36264, 40182);
		pcFrozenSanctuary->AddTelePort(37981, 50790, 1216, 64, 32)->Add(pcKelvezuLair, 33000, 50036, 1512);

		pcKelvezuLair->SetFileName("Field\\Boss\\Boss.ase");
		pcKelvezuLair->SetMinMapName("Field\\Map\\Boss.tga");
		pcKelvezuLair->SetTitleMapName("Field\\Title\\Bosst.tga");
		pcKelvezuLair->SetType(MAPTYPE_Dungeon);
		pcKelvezuLair->SetSky(MAPSKY_None, MAPSKY_None, MAPSKY_None);
		pcKelvezuLair->SetBackgroundMusicID(BACKGROUNDMUSICID_Dungeon);
		pcKelvezuLair->SetCenter(33000, 50036);
		pcKelvezuLair->AddTelePort(33012, 49926, 1533, 64, 32)->Add(pcFrozenSanctuary, 37971, 50460, 1209);

		pcLandOfChaos->SetFileName("Field\\Lost\\lostisland.ase");
		pcLandOfChaos->SetMinMapName("Field\\Map\\Lost.tga");
		pcLandOfChaos->SetTitleMapName("Field\\Title\\Lostt.tga");
		pcLandOfChaos->SetType(MAPTYPE_Wasteland);
		pcLandOfChaos->SetSky(MAPSKY_Lost1_Morning, MAPSKY_Lost1_Noon, MAPSKY_Lost1_Night);
		pcLandOfChaos->SetBackgroundMusicID(BACKGROUNDMUSICID_DesertB);
		pcLandOfChaos->SetCenter(-12555, -1113);
		pcLandOfChaos->AddBorder(pcLostTemple, -11586, 7704);
		pcLandOfChaos->AddStaticModel("Field\\lost\\wf_ani.ase");
		pcLandOfChaos->AddTelePort(-12610, -1349, 694, 64, 32)->Add(pcLandOfChaos, -12555, -1113, 668, 2);

		for (int i = 1; i <= 4; i++)
		{
			pcLandOfChaos->AddModelEx("Field\\lost\\ani_ship%02d.ase");
		}

		pcLostTemple->SetFileName("Field\\Losttemple\\lost_temple.ase");
		pcLostTemple->SetMinMapName("Field\\Map\\Losttemple.tga");
		pcLostTemple->SetTitleMapName("Field\\Title\\Losttemplet.tga");
		pcLostTemple->SetType(MAPTYPE_Wasteland);
		pcLostTemple->SetSky(MAPSKY_Lost2_Morning, MAPSKY_Lost2_Noon, MAPSKY_Lost2_Night);
		pcLostTemple->SetBackgroundMusicID(BACKGROUNDMUSICID_DesertB);
		pcLostTemple->SetCenter(-11718, 10794);

		pcDistortedForest->SetFileName("Field\\Fall_Game\\fall_game.ase");
		pcDistortedForest->SetType(MAPTYPE_Distorted);
		pcDistortedForest->SetSky(MAPSKY_None, MAPSKY_None, MAPSKY_None);
		pcDistortedForest->SetBackgroundMusicID(BACKGROUNDMUSICID_Dungeon);
		pcDistortedForest->SetCamera(0, 213140, 36421, 5583, 11483);
		pcDistortedForest->SetCenter(5800, 36747);
		pcDistortedForest->AddStaticModel("Field\\Fall_Game\\chandelier-ani.ase");

		for (int i = 1; i <= 19; i++)
		{
			pcDistortedForest->AddModelEx("Field\\Fall_Game\\chandelier-ani%02d.ase");
		}

		pcEndlessTowerF1->SetFileName("Field\\Endless\\dun-7.ase");
		pcEndlessTowerF1->SetMinMapName("Field\\Map\\dun-7.tga");
		pcEndlessTowerF1->SetTitleMapName("Field\\Title\\dun-7t.tga");
		pcEndlessTowerF1->SetType(MAPTYPE_Dungeon);
		pcEndlessTowerF1->SetSky(MAPSKY_None, MAPSKY_None, MAPSKY_None);
		pcEndlessTowerF1->SetBackgroundMusicID(BACKGROUNDMUSICID_Battle);
		pcEndlessTowerF1->SetCenter(14255, -39099);
		pcEndlessTowerF1->AddTelePort(14241, -41079, 220, 64, 32)->Add(pcEndlessTowerF2, 5255, -37897, 84);
		pcEndlessTowerF1->AddTelePort(14246, -38912, 220, 64, 32)->Add(pcLostTemple, -12272, 11299, 509);

		pcEndlessTowerF2->SetFileName("Field\\Endless\\dun-8.ase");
		pcEndlessTowerF2->SetMinMapName("Field\\Map\\dun-8.tga");
		pcEndlessTowerF2->SetTitleMapName("Field\\Title\\dun-8t.tga");

		pcEndlessTowerF2->SetType(MAPTYPE_Dungeon);
		pcEndlessTowerF2->SetSky(MAPSKY_None, MAPSKY_None, MAPSKY_None);
		pcEndlessTowerF2->SetBackgroundMusicID(BACKGROUNDMUSICID_Battle);
		pcEndlessTowerF2->SetCenter(5255, -37897);

		pcEndlessTowerF2->AddTelePort(5253, -37708, 69, 64, 32)->Add(pcEndlessTowerF1, 14242, -41199, 220);

		pTelePort = pcEndlessTowerF2->AddTelePort(5254, -41500, 139, 64, 32);

		pTelePort->Add(pcEndlessTowerF3, 4896, -42220, 202);
		pTelePort->Add(pcEndlessTowerF3, 6408, -42220, 202);

		pcCursedTempleF3->SetFileName("Field\\Dungeon\\Dun-6a.ase");
		pcCursedTempleF3->SetMinMapName("Field\\Map\\dun-6.tga");
		pcCursedTempleF3->SetTitleMapName("Field\\Title\\dun-6t.tga");

		pcCursedTempleF3->SetType(MAPTYPE_Dungeon);
		pcCursedTempleF3->SetSky(MAPSKY_None, MAPSKY_None, MAPSKY_None);
		pcCursedTempleF3->SetBackgroundMusicID(BACKGROUNDMUSICID_Battle);
		pcCursedTempleF3->SetCenter(-3660, -45200);

		for (int i = 1; i <= 19; i++)
		{
			pcCursedTempleF3->AddModelEx("Field\\dungeon\\Dun-6a-ani-%03d.ase", i);
		}

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

		pTelePort = pcCursedTempleF3->AddTelePort(-3664, -44886, 145, 64, 32);

		pTelePort->Add(pcCursedTempleF2, -2851, -43792, 642);
		pTelePort->Add(pcCursedTempleF2, -4422, -43801, 642);

		// 无尽之塔3层

		pcEndlessTowerF3->SetFileName("Field\\Endless\\dun-9.ase");
		pcEndlessTowerF3->SetMinMapName("Field\\Map\\dun-9.tga");
		pcEndlessTowerF3->SetTitleMapName("Field\\Title\\dun-9t.tga");
		pcEndlessTowerF3->SetType(MAPTYPE_Dungeon);
		pcEndlessTowerF3->SetSky(MAPSKY_None, MAPSKY_None, MAPSKY_None);
		pcEndlessTowerF3->SetBackgroundMusicID(BACKGROUNDMUSICID_Battle);
		pcEndlessTowerF3->SetCenter(4896, -42330);
		pcEndlessTowerF3->AddSpawn(4896, -42330);
		pcEndlessTowerF3->AddSpawn(6418, -42330);
		pcEndlessTowerF3->AddTelePort(4896, -42090, 230, 64, 32)->Add(pcEndlessTowerF2, 5254, -41361, 139);
		pcEndlessTowerF3->AddTelePort(6408, -42090, 230, 64, 32)->Add(pcEndlessTowerF2, 5254, -41361, 139);

		// 冰封洞穴1层

		pcIceMineF1->SetFileName("Field\\Mine\\mine-1.ase");
		pcIceMineF1->SetMinMapName("Field\\Map\\mine-1.tga");
		pcIceMineF1->SetTitleMapName("Field\\Title\\mine-1t.tga");

		pcIceMineF1->SetType(MAPTYPE_Dungeon);
		pcIceMineF1->SetSky(MAPSKY_None, MAPSKY_None, MAPSKY_None);
		pcIceMineF1->SetBackgroundMusicID(BACKGROUNDMUSICID_Battle);

		pcIceMineF1->SetCenter(18006, -34740);
		pcIceMineF1->AddTelePort(17944, -34641, 246, 64, 32)->Add(pcGallubiaValley, 35352, 31928, 829);

		// 内维斯克洞穴

		pcSlab->SetFileName("Field\\Slab\\Slab.ase");
		pcSlab->SetMinMapName("Field\\Map\\Slab.tga");
		pcSlab->SetTitleMapName("Field\\Title\\Slabt.tga");

		pcSlab->SetType(MAPTYPE_Dungeon);
		pcSlab->SetSky(MAPSKY_None, MAPSKY_None, MAPSKY_None);
		pcSlab->SetBackgroundMusicID(BACKGROUNDMUSICID_Eura);

		pcSlab->SetCenter(-12024, -62846);

		pcSlab->AddSpawn(-11976, -62455);
		//pcSlab->AddTelePort(-12000,-54163,374,64,32)->Teleport(pcAncientWeapon, 12788, -73633, 458);

		pcAncientWeapon->SetFileName("Field\\AncientW\\AncientW.ase");
		pcAncientWeapon->SetMinMapName("Field\\Map\\AncientW.tga");
		pcAncientWeapon->SetTitleMapName("Field\\Title\\AncientWt.tga");

		pcAncientWeapon->SetType(MAPTYPE_Dungeon);
		pcAncientWeapon->SetSky(MAPSKY_None, MAPSKY_None, MAPSKY_None);
		pcAncientWeapon->SetBackgroundMusicID(BACKGROUNDMUSICID_Atlantis);

		pcAncientWeapon->SetCenter(12788, -73633);
		pcAncientWeapon->AddSpawn(12788, -73633);

		for (int i = 1; i <= 10; i++)
		{
			pcAncientWeapon->AddModelEx("Field\\ancientW\\RotObj%02d.ASE", i);
		}

		pcAncientWeapon->AddTelePort(12799, -62227, 530, 64, 32)->Add(pcAncientWeapon, 12772, -59917, 562, 1);
		pcAncientWeapon->AddTelePort(12778, -60119, 578, 64, 32)->Add(pcAncientWeapon, 12700, -62387, 510, 1);
		//lpField->AddTelePort(12790,-74070,458,64,32)->Teleport(psField[45], -12000, -54309, 374);

		pcShipyardRuins->SetFileName("Field\\Lost\\lost3.ase");
		pcShipyardRuins->SetMinMapName("Field\\Map\\lost3.tga");
		pcShipyardRuins->SetTitleMapName("Field\\Title\\lost3t.tga");
		pcShipyardRuins->SetType(MAPTYPE_Wasteland);
		pcShipyardRuins->SetSky(MAPSKY_Lost1_Morning, MAPSKY_Lost1_Noon, MAPSKY_Lost1_Night);
		pcShipyardRuins->SetBackgroundMusicID(BACKGROUNDMUSICID_MysteryForest);
		pcShipyardRuins->SetCenter(116360, 92524);
		pcShipyardRuins->AddSpawn(116360, 92524);

		//远古之森3

		pcMysteryForest3->SetFileName("Field\\Custom\\fo3.ase");
		pcMysteryForest3->SetMinMapName("Field\\Map\\fo3.tga");
		pcMysteryForest3->SetTitleMapName("Field\\Title\\fo3t.tga");
		pcMysteryForest3->SetType(MAPTYPE_Forest);
		pcMysteryForest3->SetSky(MAPSKY_Forest_Morning, MAPSKY_Forest_Noon, MAPSKY_Forest_Night);
		pcMysteryForest3->SetBackgroundMusicID(BACKGROUNDMUSICID_BlessCastle);
		pcMysteryForest3->SetCenter(-57048, -6894);
		pcMysteryForest3->AddSpawn(-50646, -6363);
		pcMysteryForest3->AddSpawn(-55880, -9733);

		pcMysteryForest3->AddBorder(pcMysteryForest2, -48393, -10526);

		//远古之森2

		pcMysteryForest2->SetFileName("Field\\Custom\\fo2.ase");
		pcMysteryForest2->SetMinMapName("Field\\Map\\fo2.tga");
		pcMysteryForest2->SetTitleMapName("Field\\Title\\fo2t.tga");

		pcMysteryForest2->SetType(MAPTYPE_Forest);
		pcMysteryForest2->SetSky(MAPSKY_Forest_Morning, MAPSKY_Forest_Noon, MAPSKY_Forest_Night);
		pcMysteryForest2->SetBackgroundMusicID(BACKGROUNDMUSICID_BlessCastle);

		pcMysteryForest2->SetCenter(-46733, -14391);
		pcMysteryForest2->AddSpawn(-46644, -10485);
		pcMysteryForest2->AddSpawn(-41291, -11138);

		pcMysteryForest2->AddBorder(pcMysteryForest1, -40333, -9515);

		//远古之森1

		pcMysteryForest1->SetFileName("Field\\Custom\\fo1.ase");
		pcMysteryForest1->SetMinMapName("Field\\Map\\fo1.tga");
		pcMysteryForest1->SetTitleMapName("Field\\Title\\fo1t.tga");

		pcMysteryForest1->SetType(MAPTYPE_Forest);
		pcMysteryForest1->SetSky(MAPSKY_Forest_Morning, MAPSKY_Forest_Noon, MAPSKY_Forest_Night);
		pcMysteryForest1->SetBackgroundMusicID(BACKGROUNDMUSICID_BlessCastle);

		pcMysteryForest1->SetCenter(-37627, -10754);
		pcMysteryForest1->AddSpawn(-37627, -10754);
		pcMysteryForest1->AddSpawn(-38759, -13582);

		pcMysteryForest1->AddBorder(pcAtlantisTown, -37653, -14972);
		pcMysteryForest1->AddBorder(pcMysteryDesert1, -35228, -7397);

		//阿瑞斯城

		pcAtlantisTown->SetFileName("Field\\Custom\\town1.ase");
		pcAtlantisTown->SetMinMapName("Field\\Map\\town1.tga");
		pcAtlantisTown->SetTitleMapName("Field\\Title\\town1t.tga");

		pcAtlantisTown->SetType(MAPTYPE_Town);
		pcAtlantisTown->SetSky(MAPSKY_Forest_Morning, MAPSKY_Forest_Noon, MAPSKY_Forest_Night);
		pcAtlantisTown->SetBackgroundMusicID(BACKGROUNDMUSICID_Login);

		pcAtlantisTown->SetCenter(-37888, -17150);
		pcAtlantisTown->AddSpawn(-37725, -17198);
		pcAtlantisTown->AddSpawn(-40254, -17511);

		for (int i = 1; i <= 4; i++)
		{
			pcAtlantisTown->AddModelEx("Field\\forest\\v-ani%02d.ASE", i);
		}

		//沙漠地图

		pcBattleTown->SetFileName("Field\\Custom\\ba1.ase");
		pcBattleTown->SetMinMapName("Field\\Map\\ba1.tga");
		pcBattleTown->SetTitleMapName("Field\\Title\\ba1t.tga");
		pcBattleTown->SetType(MAPTYPE_Desert);
		pcBattleTown->SetSky(MAPSKY_Desert_Morning, MAPSKY_Desert_Noon, MAPSKY_Desert_Night);
		pcBattleTown->SetBackgroundMusicID(BACKGROUNDMUSICID_CharacterSelect);

		pcBattleTown->SetCenter(-23793, 19419);
		pcBattleTown->AddSpawn(-25680, 20862);
		pcBattleTown->AddBorder(pcMysteryDesert3, -25122, 20938);
		pcBattleTown->AddBorder(pcMiraRemains, -19022, 21052);
		//pcBattleTown->AddTelePort(-23801,17726,1105,100,100)->Teleport(psField[47], 116358, 91294, 1487);

		//幻境沙漠1

		pcMysteryDesert3->SetFileName("Field\\Custom\\ba2.ase");
		pcMysteryDesert3->SetMinMapName("Field\\Map\\ba2.tga");
		pcMysteryDesert3->SetTitleMapName("Field\\Title\\ba2t.tga");
		pcMysteryDesert3->SetType(MAPTYPE_Desert);
		pcMysteryDesert3->SetSky(MAPSKY_Desert_Morning, MAPSKY_Desert_Noon, MAPSKY_Desert_Night);
		pcMysteryDesert3->SetBackgroundMusicID(BACKGROUNDMUSICID_QuestArena);
		pcMysteryDesert3->SetCenter(-29687, 20686);
		pcMysteryDesert3->AddSpawn(-29687, 21324);
		pcMysteryDesert3->AddBorder(pcMysteryDesert2, -32203, 15803);

		//幻境沙漠2

		pcMysteryDesert2->SetFileName("Field\\Custom\\ba3.ase");
		pcMysteryDesert2->SetMinMapName("Field\\Map\\ba3.tga");
		pcMysteryDesert2->SetTitleMapName("Field\\Title\\ba3t.tga");
		pcMysteryDesert2->SetType(MAPTYPE_Desert);
		pcMysteryDesert2->SetSky(MAPSKY_Desert_Morning, MAPSKY_Desert_Noon, MAPSKY_Desert_Night);
		pcMysteryDesert2->SetBackgroundMusicID(BACKGROUNDMUSICID_QuestArena);
		pcMysteryDesert2->SetCenter(-29541, 8994);
		pcMysteryDesert2->AddSpawn(-32435, 13515);
		pcMysteryDesert2->AddSpawn(-33661, 8804);
		pcMysteryDesert2->AddBorder(pcMysteryDesert1, -32225, 4508);

		//幻境沙漠3

		pcMysteryDesert1->SetFileName("Field\\Custom\\ba4.ase");
		pcMysteryDesert1->SetMinMapName("Field\\Map\\ba4.tga");
		pcMysteryDesert1->SetTitleMapName("Field\\Title\\ba4t.tga");
		pcMysteryDesert1->SetType(MAPTYPE_Desert);
		pcMysteryDesert1->SetSky(MAPSKY_Desert_Morning, MAPSKY_Desert_Noon, MAPSKY_Desert_Night);
		pcMysteryDesert1->SetBackgroundMusicID(BACKGROUNDMUSICID_QuestArena);
		pcMysteryDesert1->SetCenter(-34798, -1959);
		pcMysteryDesert1->AddSpawn(-35393, -2871);

		pcMiraRemains->SetFileName("Field\\Iron\\iron3.ase");
		pcMiraRemains->SetMinMapName("Field\\Map\\iron3.tga");
		pcMiraRemains->SetTitleMapName("Field\\Title\\iron3t.tga");
		pcMiraRemains->SetType(MAPTYPE_Iron);
		pcMiraRemains->SetSky(MAPSKY_Iron_Morning, MAPSKY_Iron_Noon, MAPSKY_Iron_Night);
		pcMiraRemains->SetBackgroundMusicID(BACKGROUNDMUSICID_TRIGGERED);
		pcMiraRemains->SetCenter(-18286, 21104);
		pcMiraRemains->AddSpawn(-18286, 21104);
		pcMiraRemains->AddSound(-15250, 1009, 21677, 80, 2);
		pcMiraRemains->AddSound(-13025, 1126, 21710, 80, 3);

		for (int i = 1; i <= 6; i++)
		{
			pcMiraRemains->AddModelEx("Field\\Iron\\iron3-ani%d.ase", i);
		}

		pcT5QuestArena->SetFileName("Field\\Boss\\dc1.ase");
		pcT5QuestArena->SetMinMapName("Field\\Map\\dc1.tga");
		pcT5QuestArena->SetTitleMapName("Field\\Title\\dc1t.tga");
		pcT5QuestArena->SetType(MAPTYPE_Dungeon);
		pcT5QuestArena->SetSky(MAPSKY_None, MAPSKY_None, MAPSKY_None);
		pcT5QuestArena->SetBackgroundMusicID(BACKGROUNDMUSICID_MysteryDesert);
		pcT5QuestArena->SetCenter(198279, 240452);
		pcT5QuestArena->AddSpawn(198279, 240452);
		pcT5QuestArena->AddTelePort(198284, 240295, 1517, 64, 32)->Add(pcRicartenTown, 2604, -18130, 236);
	}
	void Model::Update()
	{
		if (GameMode == 2)
		{
			Point3D sPosition = lpCurPlayer->GetPosition();

			auto pcMap = lpCurPlayer->GetMap();

			if (pcMap)
			{
				auto pcTerrain = pcMap->GetTerrain();

				if (pcMap->GetType() != MAPTYPE_ChessRoom && (dwGameHour < GAME_HOUR_DAY || dwGameHour >= GAME_HOUR_DARKNESS || pcMap->GetType() == MAPTYPE_Dungeon))
				{
					pcTerrain->SetNightTime(TRUE);
				}
				else
				{
					pcTerrain->SetNightTime(FALSE);
				}

				pcMap->Update(sPosition);
			}

			for (int i = 0; i < 2; i++)
			{
				pcMap = m_pcMap[i] ? m_pcMap[i]->GetBorder(sPosition.iX, sPosition.iZ) : NULL;

				if (pcMap)
				{
					LoadMap(pcMap, m_pcMap[i]);
					break;

				}
			}
		}
	}
	void Model::LoadMap(LPBASEMAP pcMap1, LPBASEMAP pcMap2)
	{
		if (pcMap1 == m_pcMap[0] || pcMap1 == m_pcMap[1])
			return;

		pcMap1->LoadTerrain();
		pcMap1->LoadMinMap();

		if (pcMap2 && pcMap2 == m_pcMap[0])
		{
			m_pcMap[1] = pcMap1;
		}
		else
		{
			if (!pcMap2 || pcMap2 == m_pcMap[1])
			{
				m_pcMap[0] = pcMap1;
			}
		}

		DWORD dwTime = GetCurrentTime();

		if (dwLastRecvGameServerTime && dwLastRecvGameServerTime < dwTime)
			dwLastRecvGameServerTime = dwTime;
		if (dwLastRecvGameServerTime2 && dwLastRecvGameServerTime2 < dwTime)
			dwLastRecvGameServerTime2 = dwTime;
		if (dwLastRecvGameServerTime3 && dwLastRecvGameServerTime3 < dwTime)
			dwLastRecvGameServerTime3 = dwTime;
		if (dwLastRecvGameServerTime4 && dwLastRecvGameServerTime4 < dwTime)
			dwLastRecvGameServerTime4 = dwTime;
	}
	void Model::Render(Point3D sPosition, Point3D sAngle)
	{
		cpRender->ZWriteAuto = TRUE;

		auto bHeightTextureQuality = SETTINGHANDLE->Get().bHightTextureQuality;

		if (!bHeightTextureQuality)
		{
			GRAPHICENGINE->GetDevice()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
			GRAPHICENGINE->GetDevice()->SetSamplerState(0, D3DSAMP_MAXMIPLEVEL, 16);
		}
		for (int i = 0; i < 2; i++)
		{
			m_pcMap[i] ? m_pcMap[i]->Render3D(sPosition, sAngle) : 0;
		}
		if (!bHeightTextureQuality)
		{
			GRAPHICENGINE->GetDevice()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
		}

		cpRender->ZWriteAuto = FALSE;
	}
	int Model::GetHeight(Point3D sPosition)
	{
		smSTAGE3D *pcTerrain = NULL;

		pcTerrain = m_pcMap[0] ? m_pcMap[0]->GetTerrain() : NULL;

		auto iY1 = pcTerrain ? pcTerrain->GetHeight(sPosition) : 0;

		pcTerrain = m_pcMap[1] ? m_pcMap[1]->GetTerrain() : NULL;

		auto iY2 = pcTerrain ? pcTerrain->GetHeight(sPosition) : 0;

		return iY1 < iY2 ? iY2 : iY1;
	}
	Point2D Model::TeleportToCastle()
	{
		Point2D sPosition[11];

		sPosition[0] = { 33931,  -31110 };
		sPosition[1] = { 33931,  -31553 };
		sPosition[2] = { 33931,  -31996 };
		sPosition[3] = { 33973,  -32440 };
		sPosition[4] = { 33863,  -32685 };
		sPosition[5] = { 34561,  -32342 };
		sPosition[6] = { 35242,  -32685 };
		sPosition[7] = { 35203,  -32440 };
		sPosition[8] = { 35167,  -31993 };
		sPosition[9] = { 35169,  -31553 };
		sPosition[10] = { 35175,  -31106 };

		int i = rand() % 11;

		GetMap(MAPID_BlessCastle)->TranslateMap();

		return Point2D(sPosition[i].iX << 8, sPosition[i].iY << 8);
	}
}