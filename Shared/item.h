#pragma once

#define ITEMVIEWMAX					1024
#define	MAX_ITEMSINITEMBOX			250

enum EItemIndex : unsigned int
{
	ITEMINDEX_00			= 0x00000000,
	ITEMINDEX_01			= 0x00000100,
	ITEMINDEX_02			= 0x00000200,
	ITEMINDEX_03			= 0x00000300,
	ITEMINDEX_04			= 0x00000400,
	ITEMINDEX_05			= 0x00000500,
	ITEMINDEX_06			= 0x00000600,
	ITEMINDEX_07			= 0x00000700,
	ITEMINDEX_08			= 0x00000800,
	ITEMINDEX_09			= 0x00000900,
	ITEMINDEX_10			= 0x00000A00,
	ITEMINDEX_11			= 0x00000B00,
	ITEMINDEX_12			= 0x00000C00,
	ITEMINDEX_13			= 0x00000D00,
	ITEMINDEX_14			= 0x00000E00,
	ITEMINDEX_15			= 0x00000F00,
	ITEMINDEX_16			= 0x00001000,
	ITEMINDEX_17			= 0x00001100,
	ITEMINDEX_18			= 0x00001200,
	ITEMINDEX_19			= 0x00001300,
	ITEMINDEX_20			= 0x00001400,
	ITEMINDEX_21			= 0x00001500,
	ITEMINDEX_22			= 0x00001600,
	ITEMINDEX_23			= 0x00001700,
	ITEMINDEX_24			= 0x00001800,
	ITEMINDEX_25			= 0x00001900,
	ITEMINDEX_26			= 0x00002A00,
	ITEMINDEX_27			= 0x00002B00,
	ITEMINDEX_28			= 0x00002C00,
	ITEMINDEX_29			= 0x00002D00,
	ITEMINDEX_30			= 0x00002E00,
	ITEMINDEX_31			= 0x00002F00,
	ITEMINDEX_32			= 0x00003000,
	ITEMINDEX_33			= 0x00003100,
	ITEMINDEX_34			= 0x00003200,
	ITEMINDEX_35			= 0x00003300,
	ITEMINDEX_36			= 0x00003400,
	ITEMINDEX_37			= 0x00003500,
	ITEMINDEX_38			= 0x00003600,
	ITEMINDEX_39			= 0x00003700,
	ITEMINDEX_40			= 0x00003800,
	ITEMINDEX_41			= 0x00003900,
	ITEMINDEX_42			= 0x00003A00,
	ITEMINDEX_43			= 0x00003B00,
	ITEMINDEX_44			= 0x00003C00,
	ITEMINDEX_45			= 0x00003D00,
	ITEMINDEX_46			= 0x00003E00,
	ITEMINDEX_47			= 0x00003F00,
	ITEMINDEX_48			= 0x00004000,
	ITEMINDEX_49			= 0x00004100,
	ITEMINDEX_50			= 0x00004200,
	ITEMINDEX_51			= 0x00004300,
	ITEMINDEX_52			= 0x00004400,
	ITEMINDEX_53			= 0x00004500,
	ITEMINDEX_54			= 0x00004600,
	ITEMINDEX_55			= 0x00004700,
	ITEMINDEX_56			= 0x00004800,
	ITEMINDEX_57			= 0x00004900,
	ITEMINDEX_58			= 0x00004A00,
	ITEMINDEX_59			= 0x00004B00,
	ITEMINDEX_60			= 0x00004C00,
	ITEMINDEX_61			= 0x00004D00,
	ITEMINDEX_62			= 0x00004E00,
	ITEMINDEX_63			= 0x00004F00,
	ITEMINDEX_64			= 0x00005000,
	ITEMINDEX_65			= 0x00005100,
	ITEMINDEX_66			= 0x00005200,
	ITEMINDEX_67			= 0x00005300,
	ITEMINDEX_68			= 0x00005400,
	ITEMINDEX_69			= 0x00005500,
	ITEMINDEX_70			= 0x00005600,
	ITEMINDEX_71			= 0x00005700,
	ITEMINDEX_72			= 0x00005800,
	ITEMINDEX_73			= 0x00005900,
	ITEMINDEX_74			= 0x00005A00,
	ITEMINDEX_75			= 0x00005B00,
	ITEMINDEX_76			= 0x00005C00,
	ITEMINDEX_77			= 0x00005D00,
	ITEMINDEX_78			= 0x00005E00,
	ITEMINDEX_79			= 0x00005F00,
	ITEMINDEX_80			= 0x00006000,
	ITEMINDEX_81			= 0x00006100,
	ITEMINDEX_82			= 0x00006200,
	ITEMINDEX_83			= 0x00006300,
	ITEMINDEX_84			= 0x00006400,
	ITEMINDEX_85			= 0x00006500,
	ITEMINDEX_86			= 0x00006600,
	ITEMINDEX_87			= 0x00006700,
	ITEMINDEX_88			= 0x00006800,
	ITEMINDEX_89			= 0x00006900,
	ITEMINDEX_90			= 0x00006A00,
	ITEMINDEX_91			= 0x00006B00,
	ITEMINDEX_92			= 0x00006C00,
	ITEMINDEX_93			= 0x00006D00,
	ITEMINDEX_94			= 0x00006E00,
	ITEMINDEX_95			= 0x00006F00,
	ITEMINDEX_96			= 0x00007000,
	ITEMINDEX_97			= 0x00007100,
	ITEMINDEX_98			= 0x00007200,
	ITEMINDEX_99			= 0x00007300,
};

enum EItemType : unsigned int
{
	ITEMTYPE_Any			= 0xFFFFFFFF,
	ITEMTYPE_None			= 0x00000000,

	/* Weapons */
	ITEMTYPE_Axe			= 0x01010000, //WA
	ITEMTYPE_Claw			= 0x01020000, //WC
	ITEMTYPE_Hammer			= 0x01030000, //WH
	ITEMTYPE_Wand			= 0x01040000, //WM
	ITEMTYPE_Scythe			= 0x01050000, //WP
	ITEMTYPE_Bow			= 0x01060000, //WS1
	ITEMTYPE_Sword			= 0x01070000, //WS2
	ITEMTYPE_Javelin		= 0x01080000, //WT
	ITEMTYPE_Phantom		= 0x01090000, //WN
	ITEMTYPE_Dagger			= 0x010A0000, //WD

	/* Defenses */
	ITEMTYPE_Armor			= 0x02010000, //DA1
	ITEMTYPE_Costume		= 0x02100000, //CA
	ITEMTYPE_Costume2		= 0x02110000, //CA
	ITEMTYPE_Costume3		= 0x02060000, //CA
	ITEMTYPE_Costume4		= 0x02070000, //CA
	ITEMTYPE_Boots			= 0x02020000, //DB
	ITEMTYPE_Gauntlets		= 0x02030000, //DG
	ITEMTYPE_Shield			= 0x02040000, //DS
	ITEMTYPE_Robe			= 0x02050000, //DA2
	ITEMTYPE_Sheltom		= 0x02350000, //OS

	/* Accessories */
	ITEMTYPE_Amulet			= 0x03010000, //OA1
	ITEMTYPE_Bracelets		= 0x03020000, //OA2
	ITEMTYPE_Orb			= 0x03030000, //OM
	ITEMTYPE_Ring			= 0x03040000, //OR1
	ITEMTYPE_ForceOrb		= 0x03060000, //FO
	ITEMTYPE_Respec			= 0x03070000, //SE or JV
	ITEMTYPE_Smelting		= 0x03090000, //PR2
	ITEMTYPE_Crafting		= 0x03100000, //PR3
	ITEMTYPE_EventPR5		= 0x03130000, //PR5
	ITEMTYPE_Ring2			= 0x03050000, //OR1


	/* Potions */
	ITEMTYPE_ManaPotion		= 0x04010000, //PM
	ITEMTYPE_HealthPotion	= 0x04020000, //PL
	ITEMTYPE_StaminaPotion	= 0x04030000, //PS

	/* Special */
	ITEMTYPE_GoldAndExp		= 0x05010000, //GG
	ITEMTYPE_BellatoStone	= 0x05020000, //BS

	/* Other */
	ITEMTYPE_EtherCore		= 0x06010000, //EC

	/* Quest */
	ITEMTYPE_Quest			= 0x07010000, //QT
	ITEMTYPE_MorionT2Quest	= 0x09020000,

	/* Event */
	ITEMTYPE_Cookie			= 0x08010000,
	ITEMTYPE_MonsterCrystal = 0x08020000, //GP
	ITEMTYPE_Wing			= 0x08030000, //QW
	ITEMTYPE_Gift			= 0x08040000,
	ITEMTYPE_Puzzle1		= 0x08060000,
	ITEMTYPE_Puzzle2		= 0x08070000,
	ITEMTYPE_Chocolate		= 0x08080000,
	ITEMTYPE_Bellatra		= 0x08090000, //SD2
	ITEMTYPE_BlessCastle	= 0x080A0000, //BC
	ITEMTYPE_Premium1		= 0x080B0000, //BI1
	ITEMTYPE_Premium2		= 0x080C0000, //BI2
	ITEMTYPE_Puzzle3		= 0x080D0000,
	ITEMTYPE_Puzzle4		= 0x080E0000,

	/* Custom */
	ITEMTYPE_MixStone		= 0x08A00000, //RS
	ITEMTYPE_MatureStone	= 0x08B00000, //MS
	ITEMTYPE_Crystal		= 0x08C00000, //SC
	ITEMTYPE_Bars			= 0x08D00000, //GB
	ITEMTYPE_PetEggs		= 0x08E00000, //PI
	ITEMTYPE_Event			= 0x08F00000, //EV
};
enum EItemBase : unsigned int
{
	ITEMBASE_Any			= 0xFFFFFFFF,
	ITEMBASE_None			= 0x00000000,

	ITEMBASE_Weapon			= 0x01000000, //W
	ITEMBASE_Defense		= 0x02000000, //D
	ITEMBASE_Accessory		= 0x03000000, //O
	ITEMBASE_Potion			= 0x04000000, //P
	ITEMBASE_Special		= 0x05000000, //G
	ITEMBASE_Core			= 0x06000000, //E
	ITEMBASE_Quest1			= 0x07000000, //Q
	ITEMBASE_Premium		= 0x08000000, //BI
	ITEMBASE_Quest2			= 0x09000000,
	ITEMBASE_Recipe			= 0x0A000000, //SD
};
enum EItemID : unsigned int
{
	ITEMID_None											= 0,

	ITEMID_RecipeCode									= 0x0A020000,
	ITEMID_RuneCodeManufacture1							= 0x03100000,

	ITEMID_HopyCrystal									= 0x08020100,
	ITEMID_HobgoblinCrystal								= 0x08020200,
	ITEMID_DecoyCrystal									= 0x08020300,
	ITEMID_BargonCrystal								= 0x08020400,
	ITEMID_HeadCutterCrystal							= 0x08020500,
	ITEMID_FigonCrystal									= 0x08020600,
	ITEMID_KingHopyCrystal								= 0x08020700,
	ITEMID_HulkCrystal									= 0x08020800,
	ITEMID_MysticCrystal								= 0x08020900,
	ITEMID_GuardianSaintCrystal							= 0x08020A00,
	ITEMID_WebCrystal									= 0x08020B00,
	ITEMID_DarkSpecterCrystal							= 0x08020C00,
	ITEMID_IronGuardCrystal								= 0x08020D00,
	ITEMID_RicartenMilitiaGuardCrystal					= 0x08020E00,
	ITEMID_RicartenGuardCrystal							= 0x08020F00,
	ITEMID_RoyalBlessGuardCrystal						= 0x08021000,
	ITEMID_OccultCrystal								= 0x08021100,
	ITEMID_DoomedCrystal								= 0x08021200,
	ITEMID_DuskyCrystal									= 0x08021300,
	ITEMID_AbysmalCrystal								= 0x08021800, //GP124
	ITEMID_ArcticCrystal								= 0x08021900,

	ITEMTID_Chocolate1									= 0x08080100,
	ITEMTID_Chocolate2									= 0x08080200,
	ITEMTID_Chocolate3									= 0x08080300,
	ITEMTID_Chocolate4									= 0x08080400,

	ITEMID_MatureStoneA									= 0x080B3400,
	ITEMID_MatureStoneB									= 0x080B3500,
	ITEMID_MatureStoneC									= 0x080B3600,

	ITEMID_BlueStone									= 0x080B0100,
	ITEMID_RedStone										= 0x080B0200,
	ITEMID_GreenStone									= 0x080B0300,

	ITEMID_SapphireStone								= 0x080B3900,
	ITEMID_RubyStone									= 0x080B3700,

	//Cores
	ITEMID_RicartenCore									= 0x06010100,
	ITEMID_NaviskoCore									= 0x06010200,
	ITEMID_AtlantisCore									= 0x06010300,
	ITEMID_PillaiCore									= 0x06010400,
	ITEMID_UnionCore									= 0x06010500,

	ITEMID_Athanasia									= 0x080A0100, //BC101
	ITEMID_DeadlyEdge									= 0x080A0200, //BC102
	ITEMID_AvailOfEvade									= 0x080A0300, //BC103
	ITEMID_BolsterRecovery								= 0x080A0400, //BC104
	ITEMID_Restoration									= 0x080A0500, //BC105
	ITEMID_DefianceStoneFire							= 0x080A0600, //BC106
	ITEMID_DefianceStoneIce								= 0x080A0700, //BC107
	ITEMID_DefianceStoneLight							= 0x080A0800, //BC108
	ITEMID_MightPotionFighter							= 0x080A0900, //BC109
	ITEMID_MightPotionMechanician						= 0x080A0A00, //BC110
	ITEMID_MightPotionPikeman							= 0x080A0B00, //BC111
	ITEMID_MightPotionArcher							= 0x080A0C00, //BC112
	ITEMID_MightPotionKnight							= 0x080A0D00, //BC113
	ITEMID_MightPotionAtalanta							= 0x080A0E00, //BC114
	ITEMID_MightPotionMagician							= 0x080A0F00, //BC115
	ITEMID_MightPotionPriestess							= 0x080A1000, //BC116

	ITEMID_FatalEdge									= 0x080B0600, //BI106
	ITEMID_AvertScroll									= 0x080B0700, //BI107

	//Quest Items
	ITEMID_Roitra										= 0x07010700, //QT107
	ITEMID_TearsOfKalia									= 0x07010800, //QT108
	ITEMID_RoyalAmulet									= 0x07010D00, //QT113
	ITEMID_DemonHunter									= 0x01010800, //WA108 (Quest)
	ITEMID_AncientRevenge								= 0x01020800, //WC108 (Quest)
	ITEMID_DarkSkull									= 0x01040900, //WM109 (Quest)
	ITEMID_DevilScythe									= 0x01050900, //WP109 (Quest)
	ITEMID_Mist											= 0x01060A00, //WS110 (Quest)
	ITEMID_PlatinumSword								= 0x01070A00, //WS210 (Quest)
	ITEMID_Anaconda										= 0x01080900, //WT109 (Quest)
	ITEMID_PlatinumDagger								= 0x010A0900, //WD109 (Quest)
	ITEMID_HutanPhantom									= 0x01090900, //WN109 (Quest)

	ITEMID_MagicRune									= 0x07011300, //QT119 (Frozen Quest)
	ITEMID_BlessOfKalia									= 0x07011900, //QT125 (Frozen Quest)
	ITEMID_GoldBag										= 0x07011700, //QT123
	ITEMID_ValentoEye									= 0x07013200, //QT134 (Tier5)
	ITEMID_PrinceEye									= 0x07013300, //QT135 (Tier5)
	ITEMID_DiamondTears									= 0x07013400, //QT136 (Tier5)
	ITEMID_GreenLiquidTree								= 0x07013500, //QT137 (Green Liquid Frozen Sanctuary Tree)

	//EXP Items
	ITEMID_RebirthScroll								= 0x080B0400, //BI104

	ITEMID_ExpUp1H										= 0x080B0F00,
	ITEMID_ExpUp24H										= 0x080B0D00,
	ITEMID_ExpUp48H										= 0x080B1800,
	ITEMID_ExpUp72H										= 0x080B1900,

	ITEMID_ThirdEye1H									= 0x080F1100,
	ITEMID_ThirdEye24H									= 0x080B0C00,
	ITEMID_ThirdEye48H									= 0x080B0E00,
	ITEMID_ThirdEye72H									= 0x080B5E00,

	ITEMID_PhoenixEgg									= 0x080E0100,
	ITEMID_PhoenixFire									= 0x080B4400,
	ITEMID_PhoenixIce									= 0x080B4500,
	ITEMID_PhoenixLightning								= 0x080B4600,
	ITEMID_PhoenixHealing								= 0x080B4700,

	ITEMID_HPUp12H										= 0x080B1300,
	ITEMID_MPUp12H										= 0x080B1500,
	ITEMID_MPDown12H									= 0x080B1C00,
	ITEMID_SPDown12H									= 0x080B1D00,

	ITEMID_GravityStone72H								= 0x080B6400,

	ITEMID_TeleportCore									= 0x080B0800,

	ITEMID_AgingStone									= 0x080B0A00,
	ITEMID_CopperOre									= 0x080B0B00,

	ITEMID_BigHeadHappyness								= 0x080B6F00,
	ITEMID_BigHeadLove									= 0x080B7000,
	ITEMID_BigHeadSadness								= 0x080B7100,
	ITEMID_BigHeadShyness								= 0x080B7200,
	ITEMID_BigHeadAngry									= 0x08110900,
	ITEMID_BigHeadSurprised								= 0x08110A00,
	ITEMID_BigHeadSensual								= 0x08110B00,

	ITEMID_HairPotionA									= 0x080B1000,
	ITEMID_HairPotionB									= 0x080B1100,
	ITEMID_HairPotionC									= 0x080B1200,
	ITEMID_HairPotionD									= 0x080C0D00,
	ITEMID_HairPotionE									= 0x080C0E00,
	ITEMID_HairPotionF									= 0x080C0F00,
	ITEMID_HairPotionG									= 0x080C1000,
	ITEMID_HairPotionH									= 0x080C1100,
	ITEMID_HairPotionI									= 0x080C1200,
	ITEMID_HairPotionJ									= 0x080C1300,
	ITEMID_HairPotionK									= 0x080C1400,
	ITEMID_HairPotionL									= 0x080C1500,
	ITEMID_HairPotionM									= 0x080C1600,
	ITEMID_HairPotionN									= 0x08110300,
	ITEMID_HairPotionO									= 0x08110400,
	ITEMID_HairPotionP									= 0x08110500,
	ITEMID_HairPotionQ									= 0x08110600,
	ITEMID_HairPotionR									= 0x08110700,
	ITEMID_HairPotionS									= 0x08110C00,
	ITEMID_HairPotionT									= 0x08110D00,

	ITEMID_SheepHat										= 0x080C3800,
	ITEMID_GiraffeHat									= 0x080C3900,
	ITEMID_SoccerHat									= 0x080B6410,

	ITEMID_XMasGreenHat									= 0x080B6415,
	ITEMID_XMasRedHat									= 0x080B6420,
	ITEMID_BCBuff										= 0x080B6416,

	ITEMID_RomanticSuit									= 0x02111200,
	ITEMID_RomanticDress								= 0x02111300,

	ITEMID_CartolaHat									= 0x080B6500,
	ITEMID_WitchHat										= 0x080B6600,

	ITEMID_TurquoiseStone								= 0x080B5000,
	ITEMID_TopazStone									= 0x080B4F00,

	ITEMID_EmeraldStone									= 0x080B3800,

	ITEMID_VampireSuit									= 0x02100900,
	ITEMID_Succubus										= 0x02100B00,

	ITEMID_Jera											= 0x03070100,
	ITEMID_Nied											= 0x03070200,
	ITEMID_Gyfu											= 0x03070300,

	ITEMID_ArcaneRing									= 0x03050200,
	ITEMID_EmperorRing									= 0x03050300,
	ITEMID_FocusRing									= 0x03050400,
	ITEMID_ValentoRing									= 0x03050500,
	ITEMID_KelvezuAmulet								= 0x03012E00,
	ITEMID_TullaAmulet									= 0x03013C00,
	ITEMID_FallenRing									= 0x03054000,
	ITEMID_MokovaBoots									= 0x02022E00,
	ITEMID_AbyssRing									= 0x03054000, //OR210
	ITEMID_GuidanceAmulet								= 0x03011900, //OA125
	ITEMID_GuidanceAmuletPlus1							= 0x03011A00, //OA126
	ITEMID_DraxosBoots									= 0x02024200,

	ITEMID_ManaMystic									= 0x04010400,

	//Halloween
	ITEMID_CoreHW										= 0x0A026001,
	ITEMID_RottenLantern								= 0x080B6001,
	ITEMID_EvilLantern									= 0x080B6002,
	ITEMID_InfernalLantern								= 0x080B6003,
	ITEMID_ToiletPaper									= 0x03106004,
	ITEMID_HopyToy										= 0x03106005,
	ITEMID_SpiderPlastic								= 0x03106006,
	ITEMID_GriffenEgg									= 0x03106007,

	//Sheltom
	ITEMID_Devine										= 0x02350800, //OS108
	ITEMID_Celesto										= 0x02350900, //OS109
	ITEMID_Mirage										= 0x02350A00, //OS110
	ITEMID_Inferna										= 0x02350B00, //OS111
	ITEMID_Enigma										= 0x02350C00, //OS112
	ITEMID_Bellum										= 0x02350D00, //OS113
	ITEMID_Oredo										= 0x02350E00, //OS114
	ITEMID_FurySheltom									= 0x02351500, //OS121

	//ForceOrb
	ITEMID_LucidyForce									= 0x03060100,
	ITEMID_SerenoForce									= 0x03060200,
	ITEMID_FadeoForce									= 0x03060300,
	ITEMID_SparkyForce									= 0x03060400,
	ITEMID_RaidentForce									= 0x03060500,
	ITEMID_TransparoForce								= 0x03060600,
	ITEMID_MurkyForce									= 0x03060700,
	ITEMID_DevineForce									= 0x03060800,
	ITEMID_CelestoForce									= 0x03060900,
	ITEMID_MirageForce									= 0x03060A00,
	ITEMID_InfernaForce									= 0x03060B00,
	ITEMID_EnigmaForce									= 0x03060C00,
	ITEMID_BellumForce									= 0x03060D00,
	ITEMID_OredoForce									= 0x03060E00,

	//Socket System
	ITEMID_RuneDrill									= 0x080C4F00, //BI263
	ITEMID_RedRuneDrill									= 0x080C5000, //BI264
	ITEMID_YellowRuneDrill								= 0x080C5100, //BI265
	ITEMID_GreenRuneDrill								= 0x080C5200, //BI266
	ITEMID_BlueRuneDrill								= 0x080C5300, //BI267
	ITEMID_PurpleRuneDrill1								= 0x080C5400, //BI268
	ITEMID_PurpleRuneDrill2								= 0x080C5500, //BI269
	ITEMID_PurpleRuneDrill3								= 0x080C5600, //BI270
	ITEMID_TitaniumDrill								= 0x080C4000, //BI248
	ITEMID_DiamondDrill									= 0x080C4100, //BI249
	ITEMID_IronDrill									= 0x080C4200, //BI250

	ITEMID_RedTriangularGem								= 0x03130100, //PR501
	ITEMID_RedSquareGem									= 0x03130200, //PR502
	ITEMID_RedMarquiseGem								= 0x03130300, //PR503
	ITEMID_YellowTriangularGem							= 0x03130400, //PR504
	ITEMID_YellowSquareGem								= 0x03130500, //PR505
	ITEMID_YellowMarquiseGem							= 0x03130600, //PR506
	ITEMID_GreenTriangularGem							= 0x03130700, //PR507
	ITEMID_GreenSquareGem								= 0x03130800, //PR508
	ITEMID_GreenMarquiseGem								= 0x03130900, //PR509
	ITEMID_BlueTriangularGem							= 0x03130A00, //PR510
	ITEMID_BlueSquareGem								= 0x03130B00, //PR511
	ITEMID_BlueMarquiseGem								= 0x03130C00, //PR512
	ITEMID_PurpleTriangularGem							= 0x03130D00, //PR513
	ITEMID_PurpleSquareGem								= 0x03130E00, //PR514
	ITEMID_PurpleMarquiseGem							= 0x03130F00, //PR515

	ITEMID_GreenGemPiece								= 0x03131500, //PR521
	ITEMID_RedGemPiece									= 0x03131600, //PR522
	ITEMID_BlueGemPiece									= 0x03131700, //PR523
	ITEMID_PurpleGemPiece								= 0x03131800, //PR524
	ITEMID_YellowGemPiece								= 0x03131900, //PR525

	ITEMID_RedElaboratedGem								= 0x03131000, //PR516
	ITEMID_YellowElaboratedGem							= 0x03131100, //PR517
	ITEMID_GreenElaboratedGem							= 0x03131200, //PR518
	ITEMID_BlueElaboratedGem							= 0x03131300, //PR519
	ITEMID_PurpleElaboratedGem							= 0x03131400, //PR520

	ITEMID_PurpleDiamond								= 0x03090100,
	ITEMID_SilverDiamond								= 0x03090200,
	ITEMID_GoldDiamond									= 0x03090300,

	//Respec
	ITEMID_SpecStoneCode								= 0x03076000,
	ITEMID_SpecStoneFS									= 0x03076001,
	ITEMID_SpecStoneMS									= 0x03076002,
	ITEMID_SpecStoneAS									= 0x03076003,
	ITEMID_SpecStonePS									= 0x03076004,
	ITEMID_SpecStoneATA									= 0x03076005,
	ITEMID_SpecStoneKS									= 0x03076006,
	ITEMID_SpecStoneMG									= 0x03076007,
	ITEMID_SpecStonePRS									= 0x03076008,
	ITEMID_SpecStoneASS									= 0x03076009,
	ITEMID_SpecStoneSHA									= 0x0307600A,
	ITEMID_DeluxeSpecStoneFS							= 0x0307600B,
	ITEMID_DeluxeSpecStoneMS							= 0x0307600C,
	ITEMID_DeluxeSpecStoneAS							= 0x0307600D,
	ITEMID_DeluxeSpecStonePS							= 0x0307600E,
	ITEMID_DeluxeSpecStoneATA							= 0x0307600F,
	ITEMID_DeluxeSpecStoneKS							= 0x03076010,
	ITEMID_DeluxeSpecStoneMG							= 0x03076011,
	ITEMID_DeluxeSpecStonePRS							= 0x03076012,
	ITEMID_DeluxeSpecStoneASS							= 0x03076013,
	ITEMID_DeluxeSpecStoneSHA							= 0x03076014,

	ITEMID_CleanItem									= 0x080B6900,

	ITEMID_Fireworks									= 0x080B1700,

	//Suits
	ITEMID_SoccerShirt									= 0x02053F00,
	ITEMID_SouthGraceHanbokM							= 0x02100100,
	ITEMID_SouthGraceHanbokF							= 0x02100200,
	ITEMID_MagnificentHanbokM							= 0x02100300,
	ITEMID_MagnificentHanbokF							= 0x02100500,
	ITEMID_GraySuitM									= 0x02100700,
	ITEMID_GraySuitF									= 0x02100800,
	ITEMID_RomanticSuitM								= 0x02101100,
	ITEMID_RomanticSuitF								= 0x02101200,
	ITEMID_MechanicCostumeM								= 0x02101500,
	ITEMID_MechanicCostumeF								= 0x02101700,
	ITEMID_ChineseSuitM									= 0x02015000,
	ITEMID_ChineseSuitF									= 0x02015100,
	ITEMID_WarriorsHanbokM								= 0x02014A00,
	ITEMID_WarriorsHanbokF								= 0x02014B00,
	ITEMID_KimonoCostumeM								= 0x02014C00,
	ITEMID_KimonoCostumeF								= 0x02014D00,
	ITEMID_FootballM									= 0x02101900,
	ITEMID_FootballF									= 0x02101B00,
	ITEMID_PeruvianSoccer								= 0x02111900,
	ITEMID_BrazilianSoccer								= 0x02111A00,
	ITEMID_ArgentineSoccer								= 0x02111B00,
	ITEMID_ChileanSoccer								= 0x02111C00,
	ITEMID_PinoySoccer									= 0x02111D00,
	ITEMID_VietnameseSoccer								= 0x02111E00,
	ITEMID_FrenchSoccer									= 0x02111F00,
	ITEMID_GermanySoccer								= 0x02112000,
	ITEMID_HollandSoccer								= 0x02112100,
	ITEMID_ItalianSoccer								= 0x02112200,
	ITEMID_MexicanSoccer								= 0x02112300,
	ITEMID_PortugueseSoccer								= 0x02112400,
	ITEMID_SpanishSoccer								= 0x02112500,
	ITEMID_TeamUSASoccer								= 0x02112600,
	ITEMID_ColombianSoccer								= 0x02112700,
	ITEMID_JapanSoccer									= 0x02112800,

	//Armors
	ITEMID_ViperArmor									= 0x02011600,
	ITEMID_KronusArmor									= 0x02012B00,
	ITEMID_DestroyerArmor								= 0x02011A00,

	//Robes
	ITEMID_PhoenixRobe									= 0x02051600,
	ITEMID_KronusRobe									= 0x02052B00,

	ITEMID_Gold											= 0x05010100,
	ITEMID_Experience									= 0x05010200,

	ITEMID_PotionAgingQuestBee							= 0x09010100, //MA101

	//XMas
	ITEMID_RecipeXMas01									= 0x0A026101,
	ITEMID_RecipeXMas02									= 0x0A026102,
	ITEMID_SnowManCrystal								= 0x08022900,
	ITEMID_Cotton										= 0x0310602E,
	ITEMID_RedButton									= 0x0310602F,
	ITEMID_GreenCloth									= 0x03106031,
	ITEMID_XMasElegantCostumeM							= 0x02100F00,
	ITEMID_XMasElegantCostumeF							= 0x02101000,
	ITEMID_XMasCloatCostumeTM							= 0x02014E00,
	ITEMID_XMasCloatCostumeTF							= 0x02014F00,
	ITEMID_XMasCloatCostumeMM							= 0x02054E00,
	ITEMID_XMasCloatCostumeMF							= 0x02054F00,
	ITEMID_Gingerbread									= 0x080E4200,
	ITEMID_GiftBox1										= 0x08010700, //SP107
	ITEMID_GiftBox2										= 0x08011100, //SP117
	
	//Easter
	ITEMID_RedEasterEgg									= 0x080E4600,
	ITEMID_GreenEasterEgg								= 0x080E4700,
	ITEMID_PinkEasterEgg								= 0x080E4800,

	//Bellatra
	ITEMID_BrilliantStone								= 0x08017100,

	ITEMID_GrumpyArmor									= 0x0201EE01,
	ITEMID_GrumpyRobe									= 0x0205EE01,

	//TGF
	ITEMID_KingStone									= 0x07013100,

	//Runes
	ITEMID_LightBlueRune								= 0x03100400,
	ITEMID_DarkRedRune									= 0x03100700, //PR307
	ITEMID_LightGreenRune								= 0x03100800, //PR308


	//Beginner
	ITEMID_BeginnerAxe									= 0x01012E00, //WA130
	ITEMID_BeginnerClaw									= 0x01022D00, //WC129
	ITEMID_BeginnerHammer								= 0x01032F00, //WH131
	ITEMID_BeginnerSword								= 0x01073100, //WS233
	ITEMID_BeginnerStaff								= 0x01042F00, //WM131
	ITEMID_BeginnerJavelin								= 0x01082E00, //WT130
	ITEMID_BeginnerBow									= 0x01062F00, //WS131
	ITEMID_BeginnerScythe								= 0x01052E00, //WP130
	ITEMID_BeginnerPhantom								= 0x01092D00, //WN129
	ITEMID_BeginnerDagger								= 0x010A2D00, //WD129
	ITEMID_BeginnerGauntlet								= 0x02031B00, //DG127
	ITEMID_BeginnerBoots								= 0x02021B00, //DB127
	ITEMID_BeginnerBracelet								= 0x03021B00, //OA227

	//Costumes
	ITEMID_PartyCostumeMale								= 0x02062F00, //CA131
	ITEMID_PartyCostumeFemale							= 0x02063100, //CA133
	ITEMID_IdasCostumeMale								= 0x02063300, //CA135
	ITEMID_IdasCostumeFemale							= 0x02063500, //CA137
	ITEMID_ThalesArmorMale								= 0x02063B00, //CA143
	ITEMID_ThalesArmorFemale							= 0x02063D00, //CA145
	ITEMID_Costume4ArmorMale							= 0x02064600, //CA154
	ITEMID_Costume4ArmorFemale							= 0x02064700, //CA155
	ITEMID_Costume5ArmorMale							= 0x02065200, //CA166
	ITEMID_Costume5ArmorFemale							= 0x02065400, //CA168
	ITEMID_WingArmorMale								= 0x02066500, //CA185
	ITEMID_WingArmorFemale								= 0x02066700, //CA187
	ITEMID_DarkWingArmorMale							= 0x02066900, //CA189
	ITEMID_DarkWingArmorFemale							= 0x02066B00, //CA191
	ITEMID_SummerClotheMale								= 0x02066D00, //CA193
	ITEMID_SummerClotheFemale							= 0x02066F00, //CA195
	ITEMID_SpringCostumeMale							= 0x02100100, //CA501
	ITEMID_SpringCostumeFemale							= 0x02100200, //CA502
	ITEMID_YellowSpringCostumeMale						= 0x02100300, //CA503
	ITEMID_YellowSpringCostumeFemale					= 0x02100500, //CA505
	ITEMID_Costume11ArmorMale							= 0x02100700, //CA507
	ITEMID_Costume11ArmorFemale							= 0x02100800, //CA508
	ITEMID_BlackSuit									= 0x02101100, //CA517
	ITEMID_WhiteDress									= 0x02101300, //CA519
	ITEMID_Costume13ArmorMale							= 0x02101500, //CA521
	ITEMID_Costume13ArmorFemale							= 0x02101700, //CA523
	ITEMID_CasualSchoolUniformMale						= 0x02101F00, //CA531
	ITEMID_CasualSchoolUniformFemale					= 0x02102100, //CA533
	ITEMID_ElegantSchoolUniformMale						= 0x0207A900, //CA353
	ITEMID_ElegantSchoolUniformFemale					= 0x02102500, //CA537
	ITEMID_Costume16ArmorMale							= 0x02102700, //CA539
	ITEMID_Costume16ArmorFemale							= 0x02102900, //CA541
	ITEMID_MarineCostumeMale							= 0x02102B00, //CA543
	ITEMID_MarineCostumeFemale							= 0x02102D00, //CA545
	ITEMID_HopyCostume									= 0x02102F00, //CA547
	ITEMID_CuepyCostume									= 0x02103000, //CA548
	ITEMID_Costume19MaleArmorFemale						= 0x02014000, //DA148
	ITEMID_GaiaArmorMale								= 0x02014100, //DA149
	ITEMID_GaiaArmorFemale								= 0x02014200, //DA150
	ITEMID_IriaRobeMale									= 0x02054100, //DA249
	ITEMID_IriaRobeFemale								= 0x02054200, //DA250
	ITEMID_MartanosRobeMale								= 0x02073300, //CA235
	ITEMID_MartanosRobeFemale							= 0x02073500, //CA237
	ITEMID_MikalRobeMale								= 0x02073B00, //CA243
	ITEMID_MikalRobeFemale								= 0x02073D00, //CA245
	ITEMID_SilverCostumeMale							= 0x02013700, //DA139
	ITEMID_SilverCostumeFemale							= 0x02013900, //DA141
	ITEMID_DarkGaiaArmorMale							= 0x02014300, //DA151
	ITEMID_DarkGaiaArmorFemale							= 0x02014400, //DA152
	ITEMID_DarkIriaRobeMale								= 0x02054300, //DA251
	ITEMID_DarkIriaRobeFemale							= 0x02054400, //DA252
	ITEMID_WeddingSuit									= 0x02014800, //DA156
	ITEMID_WeddingDress									= 0x02014900, //DA157
	ITEMID_Costume23ArmorMale							= 0x02014A00, //DA158
	ITEMID_Costume23ArmorFemale							= 0x02014B00, //DA159
	ITEMID_Costume24ArmorMale							= 0x02014C00, //DA160
	ITEMID_Costume24ArmorFemale							= 0x02014D00, //DA161
	ITEMID_Costume25ArmorMale							= 0x02015000, //DA164
	ITEMID_Costume25ArmorFemale							= 0x02015100, //DA165


	//Axes
	ITEMID_MythologyAxe									= 0x01012B00, //WA127
	ITEMID_DeathAxe										= 0x01012C00, //WA128

	//Claws
	ITEMID_MythologyTalon								= 0x01022A00, //WC126
	ITEMID_DeathTalon									= 0x01022B00, //WC127

	//Hammers
	ITEMID_MythologyHammer								= 0x01032C00, //WH128
	ITEMID_DeathHammer									= 0x01032D00, //WH129

	//Staffs
	ITEMID_MythologyStaff								= 0x01042C00, //WM128
	ITEMID_DeathStaff									= 0x01042D00, //WM129

	//Scythes
	ITEMID_MythologySpear								= 0x01052B00, //WP127
	ITEMID_DeathSpear									= 0x01052C00, //WP128

	//Bows
	ITEMID_MythologyBow									= 0x01062C00, //WS128
	ITEMID_DeathBow										= 0x01062D00, //WS129

	//Swords
	ITEMID_MythologySword								= 0x01072E00, //WS230
	ITEMID_DeathSword									= 0x01072F00, //WS231

	//Javelins
	ITEMID_MythologyJavelin								= 0x01082B00, //WT127
	ITEMID_DeathJavelin									= 0x01082C00, //WT128

	//Phantoms
	ITEMID_MythologyPhantom								= 0x01092A00, //WN126
	ITEMID_DeathPhantom									= 0x01092B00, //WN127

	//Daggers
	ITEMID_MythologyDagger								= 0x010A2A00, //WD126
	ITEMID_DeathDagger									= 0x010A2B00, //WD127

	//Armors
	ITEMID_MythologyArmor								= 0x02012C00, //DA128
	ITEMID_DeathArmor									= 0x02012D00, //DA129

	//Shields
	ITEMID_MythologyShield								= 0x02041900, //DS125
	ITEMID_DeathShield									= 0x02041A00, //DS126

	//Orbs
	ITEMID_MythologyOrb									= 0x03031A00, //OM126
	ITEMID_DeathOrb										= 0x03031B00, //OM127

	//Robes
	ITEMID_MythologyRobe								= 0x02052C00, //DA228
	ITEMID_DeathRobe									= 0x02052D00, //DA229

	//Boots
	ITEMID_DeathBoots									= 0x02021A00, //DB126

	//Gauntlets
	ITEMID_DeathGauntlets								= 0x02031A00, //DG126

	//Bracelets
	ITEMID_DeathBracelets								= 0x03021A00, //OA226
};

enum EItemSlotFlag : unsigned int
{
	ITEMSLOTFLAG_None			= 0,
	ITEMSLOTFLAG_Inventory		= 1 << 0,				//1
	ITEMSLOTFLAG_LeftHand		= 1 << 1,				//2
	ITEMSLOTFLAG_RightHand		= 1 << 2,				//4
	ITEMSLOTFLAG_LeftRightHand	= (1 << 2) | (1 << 1),	//6
	ITEMSLOTFLAG_Armor			= 1 << 3,				//8
	ITEMSLOTFLAG_Boots			= 1 << 4,				//16
	ITEMSLOTFLAG_Gauntlets		= 1 << 5,				//32
	ITEMSLOTFLAG_RingLeft		= 1 << 6,				//64
	ITEMSLOTFLAG_RingRight		= 1 << 7,				//128
	ITEMSLOTFLAG_Ring			= (1 << 6) | (1 << 7),
	ITEMSLOTFLAG_Sheltom		= 1 << 8,				//256
	ITEMSLOTFLAG_Amulet			= 1 << 9,				//512
	ITEMSLOTFLAG_Bracelets		= 1 << 11,				//2048
	ITEMSLOTFLAG_Potion			= 1 << 13,				//8192
	ITEMSLOTFLAG_Costume		= 1 << 14,				//16384
	ITEMSLOTFLAG_WingLeft		= 1 << 15,
	ITEMSLOTFLAG_WingRight		= 1 << 16,
	ITEMSLOTFLAG_Wing			= (1 << 15) | (1 << 16),
};
enum EItemInvSound
{
	ITEMINVSOUND_None			= 0,
	ITEMINVSOUND_Axe			= 1,
	ITEMINVSOUND_Claw			= 2,
	ITEMINVSOUND_Hammer			= 3,
	ITEMINVSOUND_Magical		= 4,
	ITEMINVSOUND_Poles			= 5,
	ITEMINVSOUND_Shooters		= 6,
	ITEMINVSOUND_Swords			= 7,
	ITEMINVSOUND_Throwing		= 8,
	ITEMINVSOUND_Armor			= 9,
	ITEMINVSOUND_Boots			= 10,
	ITEMINVSOUND_Gauntlets		= 11,
	ITEMINVSOUND_Shields		= 12,
	ITEMINVSOUND_Amulet			= 13,
	ITEMINVSOUND_Armlet			= 14,
	ITEMINVSOUND_Ring			= 15,
	ITEMINVSOUND_Sheltom		= 16,
	ITEMINVSOUND_Potion			= 17,
	ITEMINVSOUND_Gold			= 18,
	ITEMINVSOUND_Staff			= 19,
};
class ItemID
{
public:
	ItemID() { iIDHigh = 0; iIDLow = 0; sItemType = 0; };
	ItemID(int i) { *(int *)(this) = i; }

	char									iIDHigh;	//always zero
	char									iIDLow;		//++ counter
	short									sItemType;

	//inline void operator = (int i){ *(int *)(this) = i; }

	inline unsigned int						ToInt() { return *(unsigned int *)(this); }
	inline EItemID							ToItemID() { return *(EItemID*)(this); }
	inline EItemType						ToItemType() { return (EItemType)(*(unsigned int *)(this) & 0xFFFF0000); }
	inline EItemBase						ToItemBase() { return (EItemBase)(*(unsigned int *)(this) & 0xFF000000); }
	inline EItemIndex						ToItemIndex() { return (EItemIndex)(*(unsigned int *)(this) & 0x0000FFFF); }

	static inline ItemID					* ToItemID(EItemID * i) { return (ItemID *)i; }
};

enum EItemCraftType : int
{
	ITEMCRAFTTYPE_NPC			= -1,
	ITEMCRAFTTYPE_None			= 0,
	ITEMCRAFTTYPE_Mixing		= 1,
	ITEMCRAFTTYPE_Aging			= 2,
	ITEMCRAFTTYPE_Quest			= 3,
	ITEMCRAFTTYPE_Event			= 4,
	ITEMCRAFTTYPE_Bottle		= 5,
	ITEMCRAFTTYPE_BottleElement = 6,
	ITEMCRAFTTYPE_QuestWeapon	= 7,
	ITEMCRAFTTYPE_Special		= 8,
	ITEMCRAFTTYPE_TGFKingFury	= 9,
	ITEMCRAFTTYPE_TGFLordBabel	= 10,
};

enum EIntegrityUpdate : BYTE
{
	INTEGRITYUPDATE_None,

	INTEGRITYUPDATE_KilledMonster,
	INTEGRITYUPDATE_KilledUser,
};

enum EMixTypeName : unsigned int
{
	MIXTYPENAME_None,

	MIXTYPENAME_Devine,
	MIXTYPENAME_Celesto,
	MIXTYPENAME_Mirage,
	MIXTYPENAME_Inferna,
	MIXTYPENAME_Enigma,
	MIXTYPENAME_Bellum,
	MIXTYPENAME_Oredo,

	MIXTYPENAME_NextMixFlag = 50,
	MIXTYPENAME_Devine2,
	MIXTYPENAME_Celesto2,
	MIXTYPENAME_Mirage2,
	MIXTYPENAME_Inferna2,
	MIXTYPENAME_Enigma2,
	MIXTYPENAME_Bellum2,
	MIXTYPENAME_Oredo2,
};

enum EMixAttributeType
{
	MIXATTRTYPE_Fire			= 1,
	MIXATTRTYPE_Ice				= 2,
	MIXATTRTYPE_Lightning		= 4,
	MIXATTRTYPE_Poison			= 8,
	MIXATTRTYPE_Organic			= 16,
	MIXATTRTYPE_Critical		= 32,
	MIXATTRTYPE_AttackRating	= 64,
	MIXATTRTYPE_DamageMin		= 128,
	MIXATTRTYPE_DamageMax		= 256,
	MIXATTRTYPE_AttackSpeed		= 512,
	MIXATTRTYPE_Absorption		= 1024,
	MIXATTRTYPE_Defense			= 2048,
	MIXATTRTYPE_BlockRating		= 4096,
	MIXATTRTYPE_WalkSpeed		= 8192,
	MIXATTRTYPE_HP				= 16384,
	MIXATTRTYPE_MP				= 32768,
	MIXATTRTYPE_SP				= 65536,
	MIXATTRTYPE_HPRegen			= 131072,
	MIXATTRTYPE_MPRegen			= 262144,
	MIXATTRTYPE_SPRegen			= 524288,
};
enum EMixEffect : unsigned int
{
	MIXEFFECT_None				= 0x00000000,
	MIXEFFECT_Flame				= 0x00000001,
	MIXEFFECT_Frost				= 0x00000002,
	MIXEFFECT_Light				= 0x00000004,
	MIXEFFECT_Poison			= 0x00000008,
	MIXEFFECT_Organic			= 0x00000010,
	MIXEFFECT_Critical			= 0x00000020,
	MIXEFFECT_AttackRating		= 0x00000040,
	MIXEFFECT_MinAttackPower	= 0x00000080,
	MIXEFFECT_MaxAttackPower	= 0x00000100,
	MIXEFFECT_WeaponSpeed		= 0x00000200,
	MIXEFFECT_AbsorbRating		= 0x00000400,
	MIXEFFECT_DefenseRating		= 0x00000800,
	MIXEFFECT_Block				= 0x00001000,
	MIXEFFECT_WalkSpeed			= 0x00002000,
	MIXEFFECT_HP				= 0x00004000,
	MIXEFFECT_MP				= 0x00008000,
	MIXEFFECT_SP				= 0x00010000,
	MIXEFFECT_HPRegen			= 0x00020000,
	MIXEFFECT_MPRegen			= 0x00040000,
	MIXEFFECT_SPRegen			= 0x00080000,
};
enum ESocketType : unsigned char
{
	SOCKETTYPE_None,

	SOCKETTYPE_Prismatic,
	SOCKETTYPE_Emerald,
	SOCKETTYPE_Ruby,
	SOCKETTYPE_Aquamarine,
	SOCKETTYPE_Amethyst,
	SOCKETTYPE_Topaz,

	SOCKETTYPE_Count = 7,
};
enum EGemType : unsigned char
{
	GEMTYPE_None,

	GEMTYPE_Triangular,
	GEMTYPE_Square,
	GEMTYPE_Marquise,
};
enum EGemItem : unsigned char
{
	GEMITEM_None,

	/*Normal Gems*/
	GEMITEM_Emerald,
	GEMITEM_Ruby,
	GEMITEM_Aquamarine,
	GEMITEM_Amethyst,
	GEMITEM_Topaz,

	/*Special Gems*/
	GEMITEM_RainbowOpal,
	GEMITEM_DemonSlayer,
	GEMITEM_BloodyPerl,
	GEMITEM_NavyPerl,
	GEMITEM_TempskronMartyr,
	GEMITEM_MorionMartyr,
	GEMITEM_RoyalDiamond,
	GEMITEM_PolishedCitrine,
	GEMITEM_ElementalTourmaline,
	GEMITEM_DivineHeart,
	GEMITEM_LuckyCirclet,
};

enum ESlotTypeHandle
{
	ITEMSLOTHANDLE_Get,
	ITEMSLOTHANDLE_Put,
};

enum ESlotTypeHandleWhere
{
	ITEMSLOTHANDLEWHERE_Perfectize,
	ITEMSLOTHANDLEWHERE_Swap,
	ITEMSLOTHANDLEWHERE_Sender,
};


struct SocketItem
{
	ESocketType 	eSocketType;
	EGemType		eGemType;
	EGemItem		eGemItem;
};

struct PriceItem
{
	int				iRealPrice;
	int				iPrice;
	int				iRepairPrice;
};

struct DropSettingsData
{
	int		iItemID;
	int		iPercent;
	CurMax	sGold;
};

struct SpecItemData
{
	float	fSpecAbsorbRating;
	int     iSpecDefenseRating;
	float   fSpecMovementSpeed;
	float   fSpecBlockRating;
	int     iSpecAttackSpeed;
	int     iSpecCritical;
	int     iSpecAttackRange;
	float   fSpecMagicMastery;
	short	saSpecElementalDef[8];
	short	saSpecElementalAtkDiv[8];
	int		iSpecAddMPDiv;
	int		iSpecAddHPDiv;
	int     iSpecAttackRatingDiv;
	short	iSpecAttackPowerDivMin;
	short	iSpecAttackPowerDiv;
	float	fSpecMPRegen;
	float	fSpecHPRegen;
	float	fSpecSPRegen;

	int		iPadding99[32];
};

struct Item
{
	DWORD					dwSize;

	ITEMCHECKSUM			iChk1;
	DWORD					dwVersion;
	DWORD					dwTime;
	ITEMCHECKSUM			iChk2;

	CurMax					sIntegrity;

	ItemID					sItemID;

	char					szItemName[32];

	int						iWeight;
	int						iSalePrice;

	int						iIndex;
	int						iPotionCount;

	short					saElementalDef[8];

	int						iSight;

	DWORD					Temp0;

	MinMax					sDamage;
	int						iAttackRange;
	int						iAttackSpeed;
	int						iAttackRating;
	int						iCritical;
	float					fAbsorbRating;
	int						iDefenseRating;
	float					fBlockRating;

	float					fMovementSpeed;
	int						iPotionStorage;

	float					fMagicMastery;
	float					fMPRegen;
	float					fHPRegen;
	float					fSPRegen;
	float					fAddHP;
	float					fAddMP;
	float					fAddSP;

	int						iLevel;
	int						iStrength;
	int						iSpirit;
	int						iTalent;
	int						iAgility;
	int						iHealth;

	MinMax					sMPRecovery;
	MinMax					sHPRecovery;
	MinMax					sSPRecovery;

	int						iGold;
	BOOL					bCanNotUse;

	DWORD					BackUpKey;
	DWORD					BackUpChkSum;

	short					ScaleBlink[2];
	int						iItemUniqueID;
	short					EffectBlink[2];
	short					EffectColor[4];
	BOOL					bEnableEffect;

	int						eSpecialization;
	SpecItemData			sSpecData;

	EItemCraftType			eCraftType;
	UINT					eMixEffect;

	union
	{
		USHORT				sAgeLevel;
		USHORT				sMixID;
	};
	USHORT					bMaturing;

	UMinMax					sMatureBar;
	short					ItemAgingProtect[2];

	short					SpecialItemFlag[2];

	DWORD					dwCreateTime;
	WORD					ItemCraftCode;
	WORD					ItemElement;
	BYTE					ItemSocket[4];
	SocketItem				sSocketData[2];
	DWORD					eMixTypeName;

	BOOL					bPerfectItem;

	char					cPadding[14];
};
struct sRECORD_ITEM 
{
	int	ItemCount;
	int x, y;
	int	ItemPosition;

	Item sItemInfo;
};

struct RecordItem
{
	int			iItemCount;

	Point2D		sItemPosition;
	int			iItemPosition;

	Item	sItem;
};

class ItemData
{
public:
	ItemID							sBaseItemID;
	char							szBaseName[32];
	char							szInventoryName[16];
	int								iWidth;
	int								iHeight;
	char							szCategory[64];
	EItemSlotFlag					iItemSlotFlag;
	char							szModelName[64];
	EItemSlotFlag					iVisibleItemType;
	EItemInvSound					iInvItemSound;
	int								iItemWpnDmg;
	BOOL							bValid;
	Point2D							sPosition;
	int								iPlaceX;
	int								iPlaceY;

	void							* pcInventoryTexture;
	int								iItemSlot;
	int								iPotionCount;
	int								iNotUse;
	int								iSalePrice;
	int								iOldX;
	int								iOldY;
	void							* pcTempInventoryTexture;
	Item							sItem;

	BOOL							IsOneHandedWeapon()
	{
		if (iItemSlotFlag & ITEMSLOTFLAG_RightHand)
		{
			if (iItemSlotFlag & ITEMSLOTFLAG_LeftHand)
				return FALSE;

			return TRUE;
		}

		return FALSE;
	}
	BOOL							IsTwoHandedWeapon()
	{
		if ((iItemSlotFlag & ITEMSLOTFLAG_RightHand) && (iItemSlotFlag & ITEMSLOTFLAG_LeftHand))
			return TRUE;

		return FALSE;
	}
};

struct DropItemData
{
	DWORD dwCode;
	DWORD dwKey;
	DWORD dwSum;
};
struct SellItemShopData
{
	DWORD	dwCode;
	DWORD	dwHead;
	DWORD	dwChkSum;
	int		Price;
};
struct	DefinitionItem
{
	Item sItem;

	CurMax	sIntegrity;
	union
	{
		struct
		{
			CurMax sOrganic;
			CurMax sEarth;
			CurMax sFire;
			CurMax sFrost;
			CurMax sLightning;
			CurMax sPoison;
			CurMax sWater;
			CurMax sWind;
		};

		CurMax	saElementalDef[8];
	};
	
	short	sDamage[4];
	short	sAttack_Rating[2];
	short	sDefence[2];
	float	fBlock_Rating[2];
	float	fAbsorb[2];
	float	fSpeed[2];
	int		Increase_Life[2];
	int		Increase_Mana[2];
	int		Increase_Stamina[2];

	float	fMana_Regen[2];
	float	fLife_Regen[2];
	float	fStamina_Regen[2];
	short	sSpecial_Defence[2];
	float	fSpecial_Absorb[2];
	float	fSpecial_fSpeed[2];
	float	fSpecial_Magic_Mastery[2];
	float	fSpecial_Mana_Regen[2];
	int     Lev_Attack_Rating[2];
	DWORD	dwJobBitCode_Random[12];
	int		JobBitCodeRandomCount;
	short	sGenDay[2];

	BYTE	*DefCompressData[sizeof(Item)];
	int		DefCompressDataLen;
};
struct LootItem
{
	BOOL		  bUse;
	DWORD		  dwReserved1;
	Item		  sItem;
};
struct MapLoot
{
	BOOL			  bInUse;
	Point3D			  sPosition;
	LootItem		  sLootItem;
	DWORD			  dwDropTime;
	DWORD			  dwEndTime;
	ID				  lExclusiveOwnerID;
	BOOL			  bExclusive;
};

struct ItemBoxItem
{
	int										iID;
	BOOL									bValid;
	int										iItemID;
	int										iAmount;
	int										iSpecialization;
};

struct ItemBoxSlot
{
	int										iNumItems;
	ItemBoxItem								saItemBox[MAX_ITEMSINITEMBOX];
};

struct ItemBoxItemEx
{
	int										iID;
	BOOL									bValid;
	char									szCharName[32];
	Item									sItem;
};
struct ItemBoxSlotEx
{
	int										iNumItems;
	ItemBoxItemEx							saItemBoxEx[MAX_ITEMSINITEMBOX];
};

struct ItemLogBox
{
	int										iSize;
	int										iID;
	struct SPlayer
	{
		char								szAccountName[32];
		char								szCharacterName[32];
		IN_ADDR								iIP;
	};

	struct SItem
	{
		int									iItemID;
		int									iAmount;
		int									iChecksum1;
		int									iChecksum2;
	};

	int										iActionCode;

	SPlayer									sPlayer;
	SItem									sItem;
};

struct ItemInventoryData
{
	int					iItemSlot;
	Rectangle2D			sBox;
	int					iItemIndex;
	int					iWeaponClass;
};
struct ItemLoadData
{
	BOOL				bState;
	DWORD				dwSerial;
	Item				sItem;
};
struct PacketItem : Packet
{
	Item			sItem;
	int				iX;
	int				iY;
	int				iZ;
	DWORD			dwSecCode[4];
};
struct PacketItemData : Packet
{
	int						iItemIndex;
	//ItemData				sItem;
};
struct PacketUpdateIntegrity : Packet
{
	EIntegrityUpdate	eUpdate;
};

struct PacketItemLinkChat : Packet
{
	char				szCharacterName[32];
	char				szMessage[256];
	int					eChatColor;
	ItemData			cItemData;
};

struct PacketGetItem : Packet
{
	int						iState;
	Point3D					sPosition;

	class Map			  * pcMap;
};
struct PacketPutItem : Packet 
{
	int			iItemID;
	int			iChk1;
	int			iChk2;
	int			iGold;
	DWORD		dwSeCode[4];
};
struct PacketUseGold : Packet
{
	int iGold;
	enum EWhereAction eWhere;
};
struct PacketUseItem : Packet
{
	ItemID sItem;
	int iChk1;
	int iChk2;
	int iPotionCount;
};
struct PacketSlotItemHandle : Packet
{

	ESlotTypeHandle			iTypeHandle;
	ESlotTypeHandleWhere	iTypeWhere;

	int					iItemID;

	int					iChk1;
	int					iChk2;
};
struct PacketItemBoxShow : Packet
{
	int						iItemID;
	int						sWeight;
	char					szPlayerName[32];
	char					szMessage[128];
};
struct PacketItemBoxAccept : Packet
{
	Item					sItem;
};
struct PacketItemBoxSend : Packet
{
	char					szCharacterName[32];
	Item					sItem;
};