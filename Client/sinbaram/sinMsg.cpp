#include "StdAfx.h"


sMESSAGEBOX	sMessageBox[100] = 
{
	{"Not enough space in inventory"},
	{"You have exceeded the inventory weight limit"},   
	{"Item cannot be used yet"},	   
	{"Not enough gold"},
	{"Item can't be mixed"},
	{"Exceeds maximum number of transaction items"},
	{"Transaction cancelled"},
	{"Potions cannot be stored"},
	{"Item Mixture has failed"},
	{"Thank you for your generous donation"},
	{"Too many items in the warehouse"},
	{"Item can not be aged"},
	{"Item has been changed in the trade window. Please check"},
	{"Exceeds maximum amount of gold in possession"}, 
	{"Item aging has failed"},
	{"Statistics has been reset"},
	{"Item image could not be loaded"},
	{"You can reset only once"},
	{"Only clan members can use this item "},
	{"You must be in a clan to use this item"},
	{"Unable to transfer due to level restriction"},
	{"Aging level has been decreased by -1"},
	{"Aging level has been decreased by -2"},
	{"Aging level has been increased by +1"},
	{"Aging level has been increased by +2"},
	{"Decreased ATK speed of quest item"},
	{"Your quest item has been leveled up"},
	{"Vitality (HP) increased with 15"},
	{"The puzzle has been completed"},
	{"   The puzzle is wrong    "},
	{"   No more items to sell  "},
	{"The item was sold already"},
	{"The seller's private store is closed"},
	{"   The seller is not found   "},
	{"    The number of items are wrong     "},
	{"  The male character cannot use this  "},
	{" The female character cannot use this  "},
	{"The female character cannot acquire this item "},
	{"The male character cannot acquire this item "},
	{"    Item price was changed  "},
	{"    No clan prize money    "},
	{"Your level can not use this Force Orb"},
	{"You are already using a Force Orb"},
	{"     ATK POW function is on test    "},
	{"    Force Orb creation has completed    "},
	{"  Increased stat points with 5   "},
	{"  Increased skill points with 1   "},
	{" Stat & Skill points increased by 5 and 1"},
	{" Stat & Skill points increased by 5 and 2"},
	{"Decreased death penalty percentage with 1"},
	{"Vitality (HP) increased with 40" },
	{"You have an undergoing quest" },
	{"After level 80 you will receive 7 stat points each level" },
	{"After level 90 you will receive 10 stat points each level" },
	{"Reset your numbers for training." },
	{"The quest has failed because you exceeded the available time" },
	{"Too many mercenary soldiers."},
	{"You are already using this skill"},
	{"Can't transfer you to Bless Castle, Please request to GM"},	
	{"This item can not be sold in personal shop."},
	{"There is no enough amount of tax to be withdrawn."},
	{"You have already answered the questions."},
	{"Thank you for answering the questions."}, 
	{"The seal-item is not suitable to your level."},
	{"The item was re-constructed."},
	{"Win in the confrontation with Fury."},
	{"Lose in the confrontation with Fury."},
	{"Acquierd items in compensation."},
	{"You cannot use two items of the same type at the same time"},
	{"You are already summoning a pet monster"},
	{"Unable to cancel while sheltom are being mixed."},
	{"Take out sheltoms first."},
	{"Same type Hair Tint Potion used."},
	{"Smelting Process has Failed!"},
	{"Manufacturing Process has Failed!"},
	{"Remove Sheltoms on the right side first before removing the Stone or Crystal"},
	{"When runes are combined, you can not hold recipes."},
	{"These are not same kind of ores or crystals"},
	{"This is not the right way to manufacture"},
};

sMESSAGEBOX2 sMessageBox2[20] = 
{
	{"How many items","do you want to buy?"},
	{"How many items","do you want to sell?"},
	{"How many items","do you want to drop?"},
	{"How much gold  ","do you want to drop?"},
	{"",""}, 
	{"How much gold  "," do you want to trade?"},
	{"How much gold  ","do you want to transfer?"},
	{"How much gold  ","do you want get back?"},
	{"How many stars ","do you want to buy?"},
	{"How much gold  ","do you want to donate?"}, 
	{"Do you want to register","price of item? "}, 
	{"How many items","do you want to buy?"},
	{"How much gold  ","do you want take?"}, 
	{"Do you want to ","buy the item?"}, 
	{"Do you want to ","buy the item?"},
	{"How much gold  ","do you want to take?"},
	{"How many mercenaries","would you like to buy?"}
};

sMESSAGEBOX3 sMessageBox3[MESSAGE3_MAX] = 
{
	{"Do you want to","acquire the skills?"},
	{"Do you want to", "rank up?"}, //��� �۽�ũ��
	{"Do you want to", "carry out the quest?"},
	{"Do you want to","redistribute?"},
	{"You have to pay gold"," for this event!"},
	{"Do you want to","redistribute?"},			
	{"Do you want to", "carry out the quest?"}, //��� ����̿�
	{"Do you want to", "receive the item?"}, //PostBox
	{"Do you want to", "register Union Core?"}, //LinkCore
	{"Do you want to", "receive the item?"}, //RecvOthers
	{"Do you want to", "teleport?"}, //RecvOthers
	{"","Please type in the number"}, //RecvOthers
	{"Do you want to","purchase star item?"}, //RecvOthers
	{"Do you want to", "sell this item?"}, //������ �ȱ�
	{"Do you want to", "carry out the quest?"}, //��� 3������
	{"Do you want to", "pay the donation?"}, //������ �ȱ�
	{"Personal Shop", " "}, //������ �ȱ�
	{"Do you want to", "exchange? "}, //����� �����۱�ȯ
	{"Do you want to", "buy this item?"}, //���λ��� �����ۻ��
	{"Do you want to ", "stop selling this item?"}, //���λ��� ������ ��� ���
	{"Do you want to", "exchange the item?"}, //�ٺ��ǻ� ���������� ��ȯ�ϱ�
	{"Do you want to", "exchange the item?"}, //����ȣ ���������� ��ȯ�ϱ�
	{"Do you want to", "carry out the quest?"}, //Level30
	{"Do you want to", "carry out the quest?"}, //Level55
	{"Do you want to", "carry out the quest?"}, //Level55_2
	{"Do you want to", "carry out the quest?"}, //Level70
	{"Do you want to", "carry out the quest?"}, //Level80
	{"Do you want to", "carry out the quest?"}, //Level85
	{"Do you want to", "carry out the quest?"}, //Level90
	{"Do you want to", "teleport?"}, //�ڷ���Ʈ
	{"Do you want to", "carry out the quest?"}, //Level80
	{"Do you want to", "carry out the quest?"}, //Level90_2
	{"Do you want to", "carry out the quest?"}, //4������
	{"Do you want to", "rank up?"}, //4�� ����
	{"Do you want to", "exchange the item? "},//�ϰ����� ũ����Ż�� ���������� ��ȯ�ϱ�
	{"Do you want to", "teleport?"},    //Teleport
	{"Do you want to buy","a crystal tower?"},      //ũ����Ż Ÿ���� �����ϴ�.
	{"Do you want to", "carry out the quest?"}, //A
	{"Do you want to", "carry out the quest?"}, //B
	{"Do you want to", "carry out the quest?"}, //C
	{"Do you want to", "carry out the quest?"}, //D
	{"Do you want to", "carry out the quest?"}, //E
	{"Do you want to", "carry out the quest?"}, //F
	{"Do you want to", "carry out the quest?"}, //G
	{"Do you want to", "use this item?"},       //���� ������ ���
	{"Do you want to", "carry out the quest?"},//100LV����Ʈ ���ؿ��� 
	{"Do you want to ", "receive the item?"},   //100LV������ 
	{"Do you want to","move to the Quest Arena?"},   //100LV����Ʈ ����� �̵�����
	{"Do you want to", "teleport?"},
	{"Do you want to", "exchange the item? "}, //�����°��� ���������� ��ȯ�ϱ�
	{"Do you want to", "teleport?"},    //Ⱦ��ũ�� �ʵ�
	{"Do you want to", " manufacture?"}, // pluto ���� �޼���
	{"Do you want to", "teleport?"},    // pluto �߰� ���� ������ ž MESSAGE_TELEPORT_DUNGEON
	{"Do you want to", "exchange the item?"},//����� - ���� ��ƿ���(7���� ������ ���������� ��ȯ�ϱ�) MESSAGE_WATERMELON_EVENTITEM53
	{"Do you want to", "exchange the item?"},//�庰 - �߷�Ÿ�� ���ݸ� ��ƿ���(7���� ���ݸ��� ���������� ��ȯ�ϱ�) MESSAGE_VALENTINE_EVENTITEM54
	{"Do you want to", "exchange the item?"}, // // ����� - ���ĺ� ���� �̺�Ʈ(7���� ���ĺ��� ���������� ��ȯ�ϱ�) MESSAGE_PRISTON_ALPHABET_EVENTITEM55
	{"Do you want to", "exchange the item?"},// �庰 - ĵ������(7���� ĵ�� ���������� ��ȯ�ϱ�) MESSAGE_CANDYDAYS_EVENTITEM56
	{"Do you want to", "exchange the item?"},// �庰 - �����ñ׸�- MESSAGE_MAGICALGREEN_EVENTITEM 57
	{"Do you want to", "exchange the item?"}, // �庰 - �����ñ׸� - MESSAGE_MAGICALGREEN_EVENTITEM_EMERALD58
	{"Do you want to", "exchange the item?"}, // �庰 - ī���� ���� - MESSAGE_TEAROFKARA_EVENTITEM59
	{"Do you want to", "exchange the item?"}, // �庰 - ����� - MESSAGE_FIND_EVENTITEM60
	{"Do you want to", "exchange the item?"}, // �庰 - ����� - MESSAGE_FINDKAMIU_EVENTITEM61
	{"Do you want to", "exchange the item?"}, // �庰 - ����� - MESSAGE_FINDETO_EVENTITEM62
	{"Are you sure you want to", "cancel this?"},    //ȡ��ˮ�� 63
	{"Are you sure you want to", "cancel this Quest?"},    //ȡ������ 64
	{"Do you wann to", "upgrade your Rank?"},	//רְ65
	{"Do you want to", "eat the Devil Fruit?"},	//רְ66
	{"Do you want to", "carry out the quest?"}, //67
	{"Do you want to", "carry out the quest?"}, //H68
	{"Do you want to", "carry out the quest?"}, //I69
	{"Do you want to", "carry out the quest?"}, //J70
	{"Do you want to", "carry out the quest?"}, //K71
};
char *SkillMaster[4] = 
{
	"Learn Skill",
	"Change Class",
	"Quit Game"
};
char *SkillMaster2[4] = 
{
	"",
	"",
	""

};
char *ReStartMsg[4] = 
{
	"Revive in field",
	"Revive in town",
	"Quit Game",
	"Not enough EXP or Gold"
};
char *ReStartMsg2[4] = 
{
	"Costs EXP and Gold",
	"",
	"",
	" to revive in field",
};
char *SkillUseInfoText[10]= 
{ 
	"      Skill Training",
	"   Select a skill that you",
	"   want to train",
	"   Not enough skill points",
	"   to train a new skill" 
};
char *WarpGateName[] = {"Warp gate","Ricarten","Pillai","Land of Dusk","Bamboo Forest","Ruinen Village","Navisko Town","Forbidden Land", "Eura Village", "Lost Island"};
char *HaWarpGateName[] = {"Bless Castle",0};
char *FallGameName = "�ϱ׷��� ��";

char *QuestMonsterName[] = 
{
	"Bargon",
	"Skeleton Warrior",
	"Head Cutter",
	"Armored Beetle ",
	"Skeleton Ranger",
	"Titan" ,
	"Forbidden Land's Monster",
	"Oasis' Monster",
	"Ancient Prison 1F's Monster"
};
char *VampOption[10] =
{
	"Increase Aging: \r",
		"Vampire: \r",
		"Ref Damage: \r",
		"Decrease HP: \r",
		"Lucky: \r"
};
char *Quest3ItemName[]=
{
	"Demon Hunter",
		"Ancient Revenge",
		"Mist",
		"Devil Scythe",
		"Anaconda",
		"Platinum Sword",
		"Ghost",
		"Platinum Dagger",
		"Hutan Phantom"
};

char *WatermelonItem	="7���� ������";

char *PumpkinItem	="7���� ȣ����";
char *StarItem = "7���� ��������";
char *ValentineItem	= "7���� ���ݸ���";
char *PristonAlphabetItem = "7���� ���ĺ�����";
char *CandydaysItem	="7���� ĵ��";
char *MagicalGreenEmeraldItem	="7���� ���޶��带"; 
char *MagicalGreenJadeItem	="7���� ���븦";
char *TearOfKaraItem	="7���� ī���� ������"; 
char *ExpireItem = "�Ⱓ����";
char *FindinvestigatorItem	="���ξƹķ���"; 
char *FindinvestigatorNineItem = "���ξƹķ���";
char *FindinvestigatorTaleItem	="���Ͼƹķ���"; 

char *InventoryFull = "�κ��丮 ��������";

char *PotionCntDoc2 = "Potion Price";
char *ItemPrice7 = "Item Price";

char *BuyMyShopItem7 = "%s bought %s from you for %d, quantity: %d";
char *BuyMyShopItem8 = "%s sold you a %s for %d, quantity: %d";
char *ItemName87 = "item";

char *sinEvent87 = "Request of the danger collector";
char *sinAddDamageItem = "Added ATK Power: \r";
char *sinContinueTimeItem = "Duration: \r";
char *BuyPotionMoney = "Money:";
char *BuyPotionKind = "Number:";
char *SheltomName2[] = {"Lucidy","Sereneo","Fadeo","Sparky","Raident","Transparo","Murky","Devine","Celesto", "Mirage", "Inferna", "Enigma","Bellum","Oredo","Sapphire","Sol"};
char *CrystalName2[] = 
{
	"Hopy",
		"Hobgoblin",
		"Decoy",
		"Bargon",
		"Head Cutter",
		"Figon",
		"King Hopy",
		"Hulk",
		"Mystic", 
		"Guardian Saint",
		"Web",
		"Dark Specter",
		"Iron Guard",
		"","","","","","","","","",
		"Ice Goblin",
		"Frozen Mist",
		"","","","","","","","","","","","","","","","","",
		"Blizzard Giant",
		"Mimic",
		"Hell Hound",
		"King Spider",
		"Hobo Golem",
		"Gorgon",
		"Igolation",
		"Xetan",
		"Lena",
		"Ice Serpent",
		"Armed Invader",
		"Nihil",
		"Arhdyra"
};
char *SodMessage_Etc[]= 
{
	"Click Ranking for top Clan SoD scores!",
		"Survive or Die 2",
		"Current tax rate is %d%s.",
};
char *SodMessage_Clan[] = 
{
	"Your clan is the managing clan",
		"of Survive or Die 2",
};
char *SodMessage_Master[] = 
{
	"Your clan is the managing clan",
		"of Survive or Die 2",
		"Click Amount to take gold",
};
char *OtherClanMaster[] = 
{
	"Bellatra Tax System",
		"Do you want to withdraw?",
};
char *SiegeMessage_Taxrates[] = 
{
	"The tax rate is changed %d%s.",
	"Total of tax has been accumulating",
	"Gold.",
	"Would you like to withdraw?.",
	"The tax rate is now %d%s.",
};
char *SiegeMessage_MercenrayA[] = 
{
	"Ricarten Militia",
	"It consists of the Militia",
	"Weak fighting ability but cheap.",
	"Maximum amount of Mercenary: %d / 20",
};
char *SiegeMessage_MercenrayB[] = 
{
	"Ricarten Guard",
	"Balanced level of Mercenary",
	"It has the middle fighting ability.",
	"Maximum amount of Mercenary: %d / 20",
};
char *SiegeMessage_MercenrayC[] = 
{
	"Bless Royal Guard",
	"The most high level of Mercenary",
	"It has the most fighting ability.",
	"Maximum amount of Mercenary: %d / 20",
};
char *SiegeMessage_TowerIce[] = 
{
	"Ice Crystal Tower",
	"Ice attribute has the ability",
	"to decrease their movement speed.",
	"Ice Crystal is set!",
};
char *SiegeMessage_TowerFire[] = 
{
	"Fire Crystal Tower",
	"Fire attribute has no special ability",
	"but deal the most damage.",
	"Fire Crystal is set!",
};
char *SiegeMessage_TowerLighting[] = 
{
	"Lightning Crystal Tower",
	"Lightning attribute has the ability",
	"to stun the enemy and deal damage.",
	"Lightning Crystal is set!",
};
char *sinLevelQuestMonster[]={"Bargon","Muffin","Dire Bee","Typhoon","Ratoo","Grotesque","Iron Fist"};
char *sinTeleportDoc[] = {"Mushroom Cave","Beehive Cave","Cursed land","Forbidden land"};
char *sinLevelQuest90_2Mon[] = {"Omega","D-Machine","Mountain"};

char *sinMonCodeName[]=
{
	0,
		"Bargon",
		"Skeleton Warrior",
		"Head Cutter",
		"Armored Bettle",
		"Skeleton Ranger",     //5
		"Titan",
		"Muffin",
		"Dire Bee",
		"Typhoon",
		"Ratoo",                //10
		"Grotesque",
		"Iron Fist",
		"Omega",
		"D-Machine",
		"Mountain",              //15
		"Skeleton Knight",
		"Solid Snail",
		"Thorn Crawler",
		"Mummy",
		"Doom Guard",             //20
		"Figon",            
		"Stone Giant",
		"Stone Golem",
		"Iron Guard",
		"Avelin",       //25
		"Avelisk-L",
		"BeEvil",
		"Illusion Knight",
		"Nightmare",
		"Witch",                //30
		"Heavy Goblin",
		"Dawlin",
		"Stygian",
		"Incubus",
		"Chain Golem",           //35
		"Dark Specter",
		"Metron",
		"Avelisk Lord",
		"Dusk",
		"Sadnesst",            //40
		0,
};
char *sinAttackType2[2] ={"Manual\r","Automatic\r"};

char *CastlItemInfo[] =
{
	{"Actives God Mode but\r"},  
	{"5% Critical Rate\r"},
	{"5% Evasion Rate\r"},
	{"Recovers HP, MP and STM\r"},
	{"Resurrects dead body\r"},
	{"Reduces ATK of tower by 50%\r"},     //
	{"Increases ATK Power by 5%\r"},
	0,
};
char *CastlItemInfo2[] =
{
	{"reduce ATK Power by 50%\r"},
	{"\r"},
	{"\r"},
	{"of all party members\r"},
	{"\r"},
	{"\r"},
	{"\r"},
	0,
};
char *CharClassTarget[10]=
{
	"Target Fighter\r",
	"Target Mechanician\r",
	"Target Pikeman\r",
	"Target Archer\r",
	"Target Knight\r",
	"Target Atalanta\r",
	"Target Magician\r",
	"Target Priestess\r",
	"Target Assassin\r",
	"Target Shaman\r",
};
char *AttributeTower[4]=
{
	"Fire Attribute\r",
	"Ice Attribute\r",
	"Lightning Attribute\r",
	"Last %d play seconds\r",
};
char *ha100LVQuestItemName[]=
{
	"Minotaur Axe",
		"Extreme Talon",
		"Dragon Bone Hammer ",
		"Hellfire Scythe",
		"Revenge Bow",
		"Immortal Sword",
		"Salamander Javelin",
		"Gothic Staff",
		"Phantom Dagger",
		"Kahsehtha Phantom",
		0,
};
char *PremiumItemDoc[][2]=
{
	{"�������Ե�\r"     ,""},
	{"���ü��ܵ�\r"     ,""},
	{"��������/���ܵ�\r",""},
	{"ʹ���������\r"    ,"�Զ�����.\r"},
	{"��˲����޵�״̬.\r","���������ή��1/2\r"},
	{"����15%��\r","����һ��.\r"},
	{"����15%��\r","��ܻ���.\r"},
};
char *BoosterItemInfo[] =
{
	{"Boosts your health by 15%\r"},  
	{"Boosts your mana by 15%\r"},
	{"Boosts your stamina by 15%\r"},
	0,
};
char *BoosterItemInfo2[] =
{
	{"15% .\r"},
	{"15% ��½�Ų��.\r"},
	{"15% ��½�Ų��.\r"},
	0,
};
char *SkillDelayItemInfo[] =
{
	{"�����ð����� ��ų �����̸�\r"},  
		0,
};
char *SkillDelayItemInfo2[] =
{
	{"50% ���� ��Ų��.\r"},
		0,
};