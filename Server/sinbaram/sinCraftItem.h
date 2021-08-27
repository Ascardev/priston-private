//// 磊! 酒捞袍阑 竿臂绢 焊磊 澜窍窍窍

#define   SIN_ADD_FIRE				0x00000001	//火属性
#define   SIN_ADD_ICE				0x00000002	//冰属性
#define   SIN_ADD_LIGHTNING			0x00000004	//雷属性
#define   SIN_ADD_POISON			0x00000008	//毒属性
#define   SIN_ADD_BIO				0x00000010	//魔属性
#define   SIN_ADD_CRITICAL			0x00000020	//必杀
#define   SIN_ADD_ATTACK_RATE		0x00000040	//命中
#define   SIN_ADD_DAMAGE_MIN		0x00000080	//最小攻击力
#define   SIN_ADD_DAMAGE_MAX		0x00000100	//最大攻击力
#define   SIN_ADD_ATTACK_SPEED		0x00000200	//攻击速度
#define   SIN_ADD_ABSORB			0x00000400	//吸收
#define   SIN_ADD_DEFENCE			0x00000800	//防御
#define   SIN_ADD_BLOCK_RATE		0x00001000	//格档
#define   SIN_ADD_MOVE_SPEED		0x00002000	//移动速度
#define   SIN_ADD_LIFE				0x00004000	//生命增加
#define   SIN_ADD_MANA				0x00008000	//魔法增加
#define   SIN_ADD_STAMINA			0x00010000	//耐力增加
#define   SIN_ADD_LIFEREGEN			0x00020000  //生命回复
#define   SIN_ADD_MANAREGEN			0x00040000  //魔法回复
#define   SIN_ADD_STAMINAREGEN		0x00080000  //耐力回复

#define   SIN_ADD_NUM				1 
#define   SIN_ADD_PERCENT			2 //比率

{
	{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1,sinWD1,sinWN1},
	{0,	0,	1,	0,	3,	5,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_CRITICAL,0,0,0,0,0},
	{3,4,1,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
	"Transparo Critical Mix\r","Minimum Attack Power +3\rMaximum Attack Power +4\rCritical Rate +1\r"
},

{
	{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1,sinWD1,sinWN1},
	{0,	0,	1,	1,	0,	3,	4,	0,	0,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_DAMAGE_MAX,SIN_ADD_ATTACK_RATE,SIN_ADD_LIFE,0,0,0,0,0},
	{6,45,10,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
	"Murky Dexterity Mix\r","Maximum Attack Power +6\rAttack Rating +45\rHealth +10\r"
},

{
	{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1,sinWD1,sinWN1},
	{0,	0,	0,	2,	0,	2,	5,	0,	0,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_CRITICAL,0,0,0,0,0},
	{4,5,2,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
	"Murky Critical Mix\r","Minimum Attack Power +4\rMaximum Attack Power +5\rCritical Rate +2\r"
},

{
	{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1,sinWD1,sinWN1},
	{0,	0,	0,	0,	0,	1,	4,	3,	0,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_ATTACK_RATE,SIN_ADD_LIFE,0,0,0,0},
	{4,7,55,15,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
	"Devine Dexterity Mix\r","Minimum Attack Power +4\rMaximum Attack Power +7\rAttack Rating +55\rHealth +15\r"
},

{
	{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1,sinWD1,sinWN1},
	{0,	0,	0,	0,	0,	1,	3,	4,	0,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_CRITICAL,0,0,0,0,0},
	{5,6,2,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
	"Devine Critical Mix\r","Minimum Attack Power +5\rMaximum Attack Power +6\rCritical Rate +2\r"
},

{
	{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1,sinWD1,sinWN1},
	{0,	0,	0,	0,	1,	1,	2,	0,	2,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_ATTACK_RATE,SIN_ADD_LIFE,0,0,0,0},
	{5,9,75,20,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
	"Celesto Dexterity Mix\r","Minimum Attack Power +5\rMaximum Attack Power +9\rAttack Rating +75\rHealth +20\r"
},

{
	{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1,sinWD1,sinWN1},
	{0,	0,	0,	0,	0,	0,	4,	1,	3,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_CRITICAL,SIN_ADD_MANA,0,0,0,0},
	{8,8,3,20,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
	"Celesto Critical Mix #1\r","Minimum Attack Power +8\rMaximum Attack Power +8\rCritical Rate +3\rMana +20\r"
},

{
	{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1,sinWD1,sinWN1},
	{0,	0,	0,	0,	0,	0,	4,	2,	4,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_CRITICAL,SIN_ADD_LIFE,0,0,0,0},
	{8,8,2,20,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
	"Celesto Critical Mix #2\r","Minimum Attack Power +8\rMaximum Attack Power +8\rCritical Rate +2\rHealth +20\r"
},

{
	{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1,sinWD1,sinWN1},
	{0,	0,	0,	0,	2,	0,	3,	1,	1,	2,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_ATTACK_RATE,SIN_ADD_LIFE,0,0,0,0},
	{6,11,90,20,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
	"Mirage Dexterity Mix\r","Minimum Attack Power +6\rMaximum Attack Power +11\rAttack Rating +90\rHealth +20\r"
},

{
	{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1,sinWD1,sinWN1},
	{0,	0,	0,	0,	0,	3,	0,	2,	2,	4,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_CRITICAL,SIN_ADD_MANA,0,0,0,0},
	{8,10,3,25,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
	"Mirage Critical Mix #1\r","Minimum Attack Power +8\rMaximum Attack Power +10\rCritical Rate +3\rMana +25\r"
},

{
	{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1,sinWD1,sinWN1},
	{0,	0,	0,	0,	0,	0,	1,	1,	3,	5,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_CRITICAL,SIN_ADD_LIFE,0,0,0,0},
	{8,10,2,20,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
	"Mirage Critical Mix #2\r","Minimum Attack Power +8\rMaximum Attack Power +10\rCritical Rate +2\rHealth +20\r"
},

{
	{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1,sinWD1,sinWN1},
	{0,	0,	0,	0,	0,	0,	0,	1,	1,	4,	3,	0,	0,	0,	0,	0},
	{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_ATTACK_RATE,SIN_ADD_LIFE,0,0,0,0},
	{8,13,100,25,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
	"Inferna Dexterity Mix\r","Minimum Attack Power +8\rMaximum Attack Power +13\rAttack Rating +100\rHealth +25\r"
},

{
	{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1,sinWD1,sinWN1},
	{0,	0,	0,	0,	0,	0,	2,	1,	0,	2,	4,	0,	0,	0,	0,	0},
	{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_CRITICAL,SIN_ADD_MANA,0,0,0,0},
	{10,12,4,25,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
	"Inferna Critical Mix #1\r","Minimum Attack Power +10\rMaximum Attack Power +12\rCritical Rate +4\rMana +25\r"
},

{
	{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1,sinWD1,sinWN1},
	{0,	0,	0,	0,	0,	0,	2,	0,	1,	2,	5,	0,	0,	0,	0,	0},
	{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_CRITICAL,SIN_ADD_LIFE,0,0,0,0},
	{10,12,3,25,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
	"Inferna Critical Mix #2\r","Minimum Attack Power +10\rMaximum Attack Power +12\rCritical Rate +3\rHealth +25\r"
},

{
	{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1,sinWD1,sinWN1},
	{0,	0,	0,	0,	0,	0,	0,	1,	1,	1,	2,	4,	0,	0,	0,	0},
	{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_ATTACK_RATE,SIN_ADD_LIFE,0,0,0,0},
	{10,15,115,25,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
	"Enigma Dexterity Mix\r","Minimum Attack Power +10\rMaximum Attack Power +15\rAttack Rating +115\rHealth +25\r"
},

{
	{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1,sinWD1,sinWN1},
	{0,	0,	0,	0,	1,	1,	0,	0,	0,	3,	2,	5,	0,	0,	0,	0},
	{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_CRITICAL,SIN_ADD_MANA,0,0,0,0},
	{12,14,4,30,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
	"Enigma Critical Mix #1\r","Minimum Attack Power +12\rMaximum Attack Power +14\rCritical Rate +4\rMana +30\r"
},

{
	{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1,sinWD1,sinWN1},
	{0,	0,	0,	0,	0,	0,	0,	1,	0,	3,	3,	5,	0,	0,	0,	0},
	{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_CRITICAL,SIN_ADD_LIFE,0,0,0,0},
	{12,14,3,25,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
	"Enigma Critical Mix #2\r","Minimum Attack Power +12\rMaximum Attack Power +14\rCritical Rate +3\rHealth +25\r"
},

{
	{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1,sinWD1,sinWN1},
	{0,	0,	0,	0,	0,	0,	0,	0,	3,	1,	2,	3,	3,	0,	0,	0},
	{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_ATTACK_RATE,SIN_ADD_LIFE,0,0,0,0},
	{12,17,130,30,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
	"Bellum Dexterity Mix\r","Minimum Attack Power +12\rMaximum Attack Power +17\rAttack Rating +130\rHealth +30\r"
},

{
	{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1,sinWD1,sinWN1},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	2,	2,	5,	0,	0,	0},
	{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_CRITICAL,SIN_ADD_MANA,0,0,0,0},
	{14,16,5,30,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Bellum Critical Mix #1\r","Minimum Attack Power +14\rMaximum Attack Power +16\rCritical Rate +5\rMana +30\r"
#else
	"恶魔(力)合成\r","最小攻击 + 14\r最大攻击 + 16\r必杀 + 5%\r魔法 + 30\r"
#endif
},

{
	{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1,sinWD1,sinWN1},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	2,	3,	6,	0,	0,	0},
	{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_CRITICAL,SIN_ADD_LIFE,0,0,0,0},
	{14,16,4,30,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Bellum Critical Mix #2\r","Minimum Attack Power +14\rMaximum Attack Power +16\rCritical Rate +4\rHealth +30\r"
#else
	"恶魔(暴)合成\r","最小攻击 + 14\r最大攻击 + 16\r必杀 + 4%\r生命 + 30\r"
#endif
},

{
	{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1,sinWD1,sinWN1},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	2,	6,	2,	0,	0},
	{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_ATTACK_RATE,SIN_ADD_LIFE,0,0,0,0},
	{14,19,150,30,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Oredo Dexterity Mix\r","Minimum Attack Power +14\rMaximum Attack Power +19\rAttack Rating +150\rHealth +30\r"
#else
	"荣誉(技)合成\r","最小攻击 + 14\r最大攻击 + 19\r命中 + 150\r生命 + 30\r"
#endif
},

{
	{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1,sinWD1,sinWN1},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	2,	3,	6,	0,	0},
	{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_CRITICAL,SIN_ADD_MANA,0,0,0,0},
	{16,18,5,40,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Oredo Critical Mix #1\r","Minimum Attack Power +16\rMaximum Attack Power +18\rCritical Rate +5\rMana +40\r"
#else
	"荣誉(力)合成\r","最小攻击 + 16\r最大攻击 + 18\r必杀 + 5%\r魔法 + 40\r"
#endif
},

{
	{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1,sinWD1,sinWN1},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	4,	6,	0,	0},
	{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_CRITICAL,SIN_ADD_LIFE,0,0,0,0},
	{16,18,4,35,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Oredo Critical Mix #2\r","Minimum Attack Power +16\rMaximum Attack Power +18\rCritical Rate +4\rHealth +35\r"
#else
	"荣誉(暴)合成\r","最小攻击 + 16\r最大攻击 + 18\r必杀 + 4%\r生命 + 35\r"
#endif
},

{
	{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1,sinWD1,sinWN1},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	3,	9,	0,	0},
	{SIN_ADD_ATTACK_SPEED,SIN_ADD_ATTACK_RATE,SIN_ADD_MANA,0,0,0,0,0},
	{1,130,80,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Oredo Swiftness Mix\r","Weapon Speed +1\rAttack Rating +130\rMana +80\r"
#else
	"荣誉(速)合成\r","攻击速度 + 1\r命中 + 130\r魔法 + 80\r"
#endif
},

{
	{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1,sinWD1,sinWN1},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	2,	4,	4,	0},
	{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_ATTACK_RATE,SIN_ADD_LIFE,0,0,0,0},
	{17,22,180,40,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sapphire Dexterity Mix\r","Minimum Attack Power +17\rMaximum Attack Power +22\rAttack Rating +180\rHealth +40\r"
#else
	"蓝晶(技)合成\r","最小攻击 + 17\r最大攻击 + 22\r命中 + 180\r生命 + 40\r"
#endif
},

{
	{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1,sinWD1,sinWN1},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	1,	4,	5,	0},
	{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_CRITICAL,SIN_ADD_MANA,0,0,0,0},
	{19,21,7,50,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sapphire Critical Mix #1\r","Minimum Attack Power +19\rMaximum Attack Power +21\rCritical Rate +7\rMana +50\r"
#else
	"蓝晶(力)合成\r","最小攻击 + 19\r最大攻击 + 21\r必杀 + 7%\r魔法 + 50\r"
#endif
},

{
	{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1,sinWD1,sinWN1},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	3,	2,	6,	0},
	{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_CRITICAL,SIN_ADD_LIFE,0,0,0,0},
	{19,21,5,40,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sapphire Critical Mix #2\r","Minimum Attack Power +19\rMaximum Attack Power +21\rCritical Rate +5\rHealth +40\r"
#else
	"蓝晶(暴)合成\r","最小攻击 + 19\r最大攻击 + 21\r必杀 + 5%\r生命 + 40\r"
#endif
},

{
	{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1,sinWD1,sinWN1},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	2,	8,	0},
	{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_MANA,0,0,0,0,0},
	{26,26,25,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sapphire Vigor Mix\r","Minimum Attack Power +26\rMaximum Attack Power +26\rMana +25\r"
#else
	"蓝晶(极)合成\r","最小攻击 + 26\r最大攻击 + 26\r魔法 + 40\r"
#endif
},


{
	{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1,sinWD1,sinWN1},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	3,	9,	0},
	{SIN_ADD_ATTACK_SPEED,SIN_ADD_ATTACK_RATE,SIN_ADD_CRITICAL,SIN_ADD_MANA,0,0,0,0},
	{1,150,6,100,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sapphire Swiftness Mix\r","Weapon Speed +1\rAttack Rating +150\rCritical Rate +6\rMana +100\r"
#else
	"蓝晶(速)合成\r","攻击速度 + 1\r命中 + 150\r必杀 + 6%\r魔法 + 100\r"
#endif
},

{
	{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1,sinWD1,sinWN1},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	4,	6},
	{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_ATTACK_RATE,SIN_ADD_LIFE,0,0,0,0,},
	{20,25,210,50,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sol Dexterity Mix\r","Minimum Attack Power +20\rMaximum Attack Power +25\rAttack Rating +210\rHealth +50\r"
#else
	"阿波罗(技)合成\r","最小攻击 + 20\r最大攻击 + 25\r命中 + 210\r生命 + 50\r"
#endif
},

{
	{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1,sinWD1,sinWN1},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	4,	7},
	{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_CRITICAL,SIN_ADD_MANA,0,0,0,0,},
	{22,24,9,60,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sol Critical Mix #1\r","Minimum Attack Power +22\rMaximum Attack Power +24\rCritical Rate +9\rMana +60\r"
#else
	"阿波罗(力)合成\r","最小攻击 + 22\r最大攻击 + 24\r必杀 + 9%\r魔法 + 60\r"
#endif
},

{
	{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1,sinWD1,sinWN1},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	2,	8},
	{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_CRITICAL,SIN_ADD_LIFE,0,0,0,0,},
	{22,24,7,45,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sol Critical Mix #2\r","Minimum Attack Power +22\rMaximum Attack Power +24\rCritical Rate +7\rHealth +45\r"
#else
	"阿波罗(暴)合成\r","最小攻击 + 22\r最大攻击 + 24\r必杀 + 7%\r生命 + 45\r"
#endif
},

{
	{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1,sinWD1,sinWN1},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	2,	9},
	{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_MANA,0,0,0,0,0,},
	{29,29,35,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sol Vigor Mix\r","Minimum Attack Power +29\rMaximum Attack Power +29\rMana +35\r"
#else
	"阿波罗(极)合成\r","最小攻击 + 29\r最大攻击 + 29\r魔法 + 35\r"
#endif
},

{
	{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1,sinWD1,sinWN1},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	3,	9},
	{SIN_ADD_ATTACK_SPEED,SIN_ADD_ATTACK_RATE,SIN_ADD_CRITICAL,SIN_ADD_MANA,0,0,0,0,},
	{1,170,8,120,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sol Swiftness Mix\r","Weapon Speed +1\rAttack Rating +170\rCritical Rate +8\rMana +120\r"
#else
	"阿波罗(速)合成\r","攻击速度 + 1\r命中 + 170\r必杀 + 8\r魔法 + 120\r"
#endif
},

// 铠甲

{
	{sinDA1,sinDA2,0,0,0,0,0,0,0,0},
	{0,	0,	0,	4,	1,	3,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_MANA,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0},
	{10,50,1,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Transparo Fortitude Mix\r","Mana +10\rDefense Rating +50\rAbsorption Rating +1\r"
#else
	"玄风(刚)合成\r","魔法 + 10\r防御 + 50\r吸收 + 1\r"
#endif
},

{
	{sinDA1,sinDA2,0,0,0,0,0,0,0,0},
	{0,	0,	0,	4,	2,	4,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0},
	{8,20,0.6f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Transparo Vitality Mix\r","Health +8\rDefense Rating +20\rAbsorption Rating +0.6\r"
#else
	"玄风(活)合成\r","生命 + 8\r防御 + 20\r吸收 + 0.6\r"
#endif
},

{
	{sinDA1,sinDA2,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	1,	5,	3,	0,	0,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_MANA,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0},
	{15,75,2,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Murky Fortitude Mix\r","Mana +15\rDefense Rating +75\rAbsorption Rating +2\r"
#else
	"水晶(刚)合成\r","魔法 + 15\r防御 + 75\r吸收 + 2\r"
#endif
},

{
	{sinDA1,sinDA2,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	4,	1,	5,	0,	0,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0},
	{8,30,1,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Murky Vitality Mix\r","Health +8\rDefense Rating +30\rAbsorption Rating +1\r"
#else
	"水晶(活)合成\r","生命 + 8\r防御 + 30\r吸收 + 1\r"
#endif
},

{
	{sinDA1,sinDA2,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	1,	4,	3,	0,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_MANA,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0},
	{20,100,3,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Devine Fortitude Mix\r","Mana +20\rDefense Rating +100\rAbsorption Rating +3\r"
#else
	"虎翼(刚)合成\r","魔法 + 20\r防御 + 100\r吸收 + 3\r"
#endif
},

{
	{sinDA1,sinDA2,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	4,	4,	0,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0},
	{25,10,0,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Devine Vitality Mix\r","Health +25\rDefense Rating +10\r"
#else
	"虎翼(活)合成\r","生命 + 25\r防御 + 10\r"
#endif
},

{
	{sinDA1,sinDA2,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	2,	3,	3,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_MANA,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0},
	{30,150,3.5f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Celesto Fortitude Mix\r","Mana +30\rDefense Rating +150\rAbsorption Rating +3.5\r"
#else
	"龙鳞(刚)合成\r","魔法 + 30\r防御 + 150\r吸收 + 3.5\r"
#endif
},

{
	{sinDA1,sinDA2,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	1,	2,	4,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0},
	{10,50,2,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Celesto Vitality Mix\r","Health +10\rDefense Rating +50\rAbsorption Rating +2\r"
#else
	"龙鳞(活)合成\r","生命 +10\r防御 + 50\r吸收 + 2\r"
#endif
},

{
	{sinDA1,sinDA2,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	2,	2,	3,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_MANA,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0},
	{50,200,4,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Mirage Fortitude Mix\r","Mana +50\rDefense Rating +200\rAbsorption Rating +4\r"
#else
	"钻晶(刚)合成\r","魔法 + 50\r防御 +200\r吸收 + 4\r"
#endif
},

{
	{sinDA1,sinDA2,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	3,	2,	4,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0},
	{15,75,2.5f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Mirage Vitality Mix\r","Health +15\rDefense Rating +75\rAbsorption Rating +2.5\r"
#else
	"钻晶(活)合成\r","生命 + 15\r防御 + 75\r吸收 + 2.5\r"
#endif
},

{
	{sinDA1,sinDA2,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	2,	5,	3,	0,	0,	0,	0,	0},
	{SIN_ADD_MANA,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0},
	{70,250,4.5f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Inferna Fortitude Mix\r","Mana +70\rDefense Rating +250\rAbsorption Rating +4.5\r"
#else
	"龙睛(刚)合成\r","魔法 + 70\r防御 + 250\r吸收 + 4.5\r"
#endif
},

{
	{sinDA1,sinDA2,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	1,	4,	5,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0},
	{25,100,3,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Inferna Vitality Mix\r","Health +25\rDefense Rating +100\rAbsorption Rating +3\r"
#else
	"龙睛(活)合成\r","生命 + 25\r防御 + 100\r吸收 + 3\r"
#endif
},

{
	{sinDA1,sinDA2,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	3,	4,	0,	0,	0,	0},
	{SIN_ADD_MANA,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0},
	{90,300,5,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Enigma Fortitude Mix\r","Mana +90\rDefense Rating +300\rAbsorption Rating +5\r"
#else
	"圣晶(刚)合成\r","魔法 + 90\r防御 + 300\r吸收 + 5\r"
#endif
},

{
	{sinDA1,sinDA2,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	1,	2,	3,	6,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0},
	{35,125,3.5f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Enigma Vitality Mix\r","Health +35\rDefense Rating +125\rAbsorption Rating +3.5\r"
#else
	"圣晶(活)合成\r","生命 + 35\r防御 + 125\r吸收 + 3.5\r"
#endif
},

{
	{sinDA1,sinDA2,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	2,	2,	4,	0,	0,	0},
	{SIN_ADD_MANA,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0},
	{110,350,6,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Bellum Fortitude Mix\r","Mana +110\rDefense Rating +350\rAbsorption Rating +6\r"
#else
	"恶魔(刚)合成\r","魔法 + 110\r防御 + 350\r吸收 + 6\r"
#endif
},

{
	{sinDA1,sinDA2,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	2,	3,	5,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0},
	{45,150,4,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Bellum Vitality Mix\r","Health +45\rDefense Rating +150\rAbsorption Rating +4\r"
#else
	"恶魔(活)合成\r","生命 + 45\r防御 + 150\r吸收 + 4\r"
#endif
},

{
	{sinDA1,sinDA2,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	3,	5,	0,	0},
	{SIN_ADD_MANA,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0},
	{130,400,7,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Oredo Fortitude Mix\r","Mana +130\rDefense Rating +400\rAbsorption Rating +7\r"
#else
	"荣誉(刚)合成\r","魔法 + 130\r防御 + 400\r吸收 + 7\r"
#endif
},

{
	{sinDA1,sinDA2,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	4,	7,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0},
	{60,200,5,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Oredo Vitality Mix\r","Health +60\rDefense Rating +200\rAbsorption Rating +5\r"
#else
	"荣誉(活)合成\r","生命 + 60\r防御 + 200\r吸收 + 5\r"
#endif
},

{
	{sinDA1,sinDA2,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	2,	0,	3,	5,	0},
	{SIN_ADD_MANA,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0},
	{150,450,8,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sapphire Fortitude Mix\r","Mana +150\rDefense Rating +450\rAbsorption Rating +8\r"
#else
	"蓝晶(刚)合成\r","魔法 + 150\r防御 + 450\r吸收 + 8\r"
#endif
},

{
	{sinDA1,sinDA2,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	2,	3,	6,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0},
	{75,250,6,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sapphire Vitality Mix\r","Health +75\rDefense Rating +250\rAbsorption Rating +6\r"
#else
	"蓝晶(活)合成\r","生命 + 75\r防御 + 250\r吸收 + 6\r"
#endif
},

{
	{sinDA1,sinDA2,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	10,	0},
	{SIN_ADD_LIFE,SIN_ADD_ABSORB,SIN_ADD_FIRE,SIN_ADD_ICE,SIN_ADD_LIGHTNING,SIN_ADD_POISON,SIN_ADD_BIO,0},
	{80,15,15,15,15,15,15,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0},
#ifdef ENGLISH_LANGUAGE
	"Sapphire Finesse Mix\r","Health +80\rAbsorption Rating +15\rFlame Type +15\rFrost Type +15\rLightning Type +15\rPoison Type +15\rOrganic Type+15\r"
#else
	"蓝晶(全)合成\r","生命 + 80\r吸收 + 15\r火属性 + 15\r冰属性 + 15\r雷属性 + 15\r毒属性 + 15\r魔属性 + 15\r"
#endif
},

{
	{sinDA1,sinDA2,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	2,	0,	3,	5},
	{SIN_ADD_MANA,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0},
	{170,500,9,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sol Fortitude Mix\r","Mana +170\rDefense Rating +500\rAbsorption Rating +9\r"
#else
	"阿波罗(刚)合成\r","魔法 + 170\r防御 + 500\r吸收 + 9\r"
#endif
},

{
	{sinDA1,sinDA2,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	2,	3,	6},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0},
	{90,300,7,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sol Vitality Mix\r","Health +90\rDefense Rating +300\rAbsorption Rating +7\r"
#else
	"阿波罗(活)合成\r","生命 + 90\r防御 + 300\r吸收 + 7\r"
#endif
},

{
	{sinDA1,sinDA2,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	10},
	{SIN_ADD_LIFE,SIN_ADD_ABSORB,SIN_ADD_FIRE,SIN_ADD_ICE,SIN_ADD_LIGHTNING,SIN_ADD_POISON,SIN_ADD_BIO,0},
	{100,17,17,17,17,17,17,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0},
#ifdef ENGLISH_LANGUAGE
	"Sol Finesse Mix\r","Health +100\rAbsorption Rating +17\rFlame Type +17\rFrost Type +17\rLightning Type +17\rPoison Type +17\rOrganic Type+17\r"
#else
	"阿波罗(全)合成\r","生命 + 100\r吸收 + 17\r火属性 + 17\r冰属性 + 17\r雷属性 + 17\r毒属性 + 17\r魔属性 + 17\r"
#endif
},
// 盾

{
	{sinDS1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	1,	1,	5,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,0,0,0,0},
	{4,20,0.6f,1,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Transparo Vitality Mix\r","Health +4\rDefense Rating +20\rAbsorption Rating +0.6\rBlock Rating +1\r"
#else
	"玄风(活)合成\r","生命 + 4\r防御 + 20\r吸收 + 0.6\r格档 + 1%\r"
#endif
},

{
	{sinDS1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	4,	6,	0,	0,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,0,0,0,0},
	{6,25,0.8f,1,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Murky Vitality Mix\r","Health +6\rDefense Rating +25\rAbsorption Rating +0.8\rBlock Rating +1\r"
#else
	"水晶(活)合成\r","生命 + 6\r防御 + 25\r吸收 + 0.8\r格档 + 1%\r"
#endif
},

{
	{sinDS1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	1,	2,	6,	0,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,0,0,0,0},
	{8,30,1,2,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Devine Vitality Mix\r","Health +8\rDefense Rating +30\rAbsorption Rating +1\rBlock Rating +2\r"
#else
	"虎翼(活)合成\r","生命 + 8\r防御 + 30\r吸收 + 1\r格档 + 2%\r"
#endif
},

{
	{sinDS1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	1,	2,	5,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,0,0,0,0},
	{10,35,1.2f,2,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Celesto Vitality Mix #1\r","Health +10\rDefense Rating +35\rAbsorption Rating +1.2\rBlock Rating +2\r"
#else
	"龙鳞(刚)合成\r","生命 + 10\r防御 + 35\r吸收 + 1.2\r格档 + 2%\r"
#endif
},

{
	{sinDS1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	2,	3,	6,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,0,0,0,0},
	{15,45,1.6f,2,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Celesto Vitality Mix #2\r","Health +15\rDefense Rating +45\rAbsorption Rating +1.6\rBlock Rating +2\r"
#else
	"龙鳞(活)合成\r","生命 + 15\r防御 + 45\r吸收 + 1.6\r格档 + 2%\r"
#endif
},

{
	{sinDS1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	2,	3,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0},
	{40,80,1,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Mirage Fortitude Mix\r","Health +40\rDefense Rating +80\rAbsorption Rating +1\r"
#else
	"钻晶(刚)合成\r","生命 + 40\r防御 + 80\r吸收 + 1\r"
#endif
},

{
	{sinDS1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	3,	1,	4,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,0,0,0,0},
	{25,50,1.8f,4,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Mirage Vitality Mix\r","Health +25\rDefense Rating +50\rAbsorption Rating +1.8\rBlock Rating +4\r"
#else
	"钻晶(活)合成\r","生命 + 25\r防御 + 50\r吸收 + 1.8\r格档 + 4%\r"
#endif
},

{
	{sinDS1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	1,	4,	2,	4,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_MANA,0,0,0,0,0,0},
	{40,80,0,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Inferna Fortitude Mix\r","Health +40\rMana +80\r"
#else
	"龙睛(刚)合成\r","生命 + 40\r魔法 + 80\r"
#endif
},

{
	{sinDS1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	1,	1,	2,	5,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,0,0,0,0},
	{30,75,2.5f,4,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Inferna Vitality Mix\r","Health +30\rDefense Rating +75\rAbsorption Rating +2.5\rBlock Rating +4\r"
#else
	"龙睛(活)合成\r","生命 + 30\r防御 + 75\r吸收 + 2.5\r格档 + 4%\r"
#endif
},

{
	{sinDS1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	2,	3,	2,	2,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,0,0,0,0},
	{30,100,3.0f,5,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Enigma Vitality Mix\r","Health +30\rDefense Rating +100\rAbsorption Rating +3\rBlock Rating +5\r"
#else
	"圣晶(刚)合成\r","生命 + 30\r防御 + 100\r吸收 + 3.0\r格档 + 5%\r"
#endif
},

{
	{sinDS1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	3,	0,	2,	3,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_MANA,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,0,0,0},
	{35,10,100,2.8f,5,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Enigma Fortitude Mix\r","Health +35\rMana +10\rDefense Rating +100\rAbsorption Rating +2.8\rBlock Rating +5\r"
#else
	"圣晶(活)合成\r","生命 + 35\r魔法 + 10\r防御 + 100\r吸收 + 2.8\r格档 + 5%\r"
#endif
},

{
	{sinDS1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	3,	4,	2,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_MANA,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,0,0,0},
	{40,10,120,2.4f,5,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Bellum Fortitude Mix\r","Health +40\rMana +10\rDefense Rating +120\rAbsorption Rating +2.4\rBlock Rating +5\r"
#else
	"恶魔(刚)合成\r","生命 + 40\r魔法 + 10\r防御 + 120\r吸收 + 2.4\r格档 + 5%\r"
#endif
},

{
	{sinDS1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	3,	2,	2,	5,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,0,0,0,0},
	{45,150,4.6f,5,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Bellum Vitality Mix\r","Health +45\rDefense Rating +150\rAbsorption Rating +4.6\rBlock Rating +5\r"
#else
	"恶魔(活)合成\r","生命 + 45\r防御 + 150\r吸收 + 4.6\r格档 + 5%\r"
#endif
},

{
	{sinDS1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	1,	2,	3,	3,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,0,0,0,0},
	{50,175,5.0f,6,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Oredo Vitality Mix #1\r","Health +50\rDefense Rating +175\rAbsorption Rating +5\rBlock Rating +6\r"
#else
	"荣誉(刚)合成\r","生命 + 50\r防御 + 175\r吸收 + 5.0\r格档 + 6%\r"
#endif
},

{
	{sinDS1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	1,	4,	6,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,0,0,0,0},
	{60,200,5.4f,7,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Oredo Vitality Mix #2\r","Health +60\rDefense Rating +200\rAbsorption Rating +5.4\rBlock Rating +7\r"
#else
	"荣誉(活)合成\r","生命 + 60\r防御 + 200\r吸收 + 5.4\r格档 + 7%\r"
#endif
},

{
	{sinDS1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	3,	1,	3,	2,	3,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,0,0,0,0},
	{65,225,6.0f,7,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sapphire Vitality Mix #1\r","Health +65\rDefense Rating +225\rAbsorption Rating +6\rBlock Rating +7\r"
#else
	"蓝晶(刚)合成\r","生命 + 65\r防御 + 225\r吸收 + 6\r格档 + 7%\r"
#endif
},

{
	{sinDS1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	4,	7,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,0,0,0,0},
	{70,250,6.5f,8,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sapphire Vitality Mix #2\r","Health +70\rDefense Rating +250\rAbsorption Rating +6.5\rBlock Rating +8\r"
#else
	"蓝晶(活)合成\r","生命 + 70\r防御 + 250\r吸收 + 6.5\r格档 + 8%\r"
#endif
},

{
	{sinDS1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	10,	0},
	{SIN_ADD_LIFE,SIN_ADD_BLOCK_RATE,0,0,0,0,0,0},
	{80,12,0,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sapphire Block Mix\r","Health +80\rBlock Rating +12\r"
#else
	"蓝晶(格档)合成\r","生命 + 80\r格档 + 12%\r"
#endif
},

{
	{sinDS1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	3,	3,	5},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,0,0,0,0},
	{75,275,6.9f,8,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sol Vitality Mix #1\r","Health +75\rDefense Rating +275\rAbsorption Rating +6.9\rBlock Rating +8\r"
#else
	"阿波罗(刚)合成\r","生命 + 75\r防御 + 275\r吸收 + 6.9\r格档 + 8%\r"
#endif
},

{
	{sinDS1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	4,	7},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,0,0,0,0},
	{80,300,7.3f,9,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sol Vitality Mix #2\r","Health +80\rDefense Rating +300\rAbsorption Rating +7.3\rBlock Rating +9\r"
#else
	"阿波罗(活)合成\r","生命 + 80\r防御 + 300\r吸收 + 7.3\r格档 + 9%\r"
#endif
},

{
	{sinDS1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	10},
	{SIN_ADD_LIFE,SIN_ADD_BLOCK_RATE,0,0,0,0,0,0},
	{90,14,0,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sol Block Mix\r","Health +90\rBlock Rating +14\r"
#else
	"阿波罗(格档)合成\r","生命 + 90\r格档 + 14%\r"
#endif
},
// 法珠
{
	{sinOM1,0,0,0,0,0,0,0,0,0},
	{0,	0,	2,	0,	2,	6,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,0,0,0,0},
	{4,20,0.6f,1,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Transparo Vitality Mix\r","Health +4\rDefense Rating +20\rAbsorption Rating +0.6\rBlock Rating +1\r"
#else
	"玄风(活)合成\r","生命 + 4\r防御 + 20\r吸收 + 0.6\r格档 + 1\r"
#endif
},

{
	{sinOM1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	1,	2,	5,	0,	0,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,0,0,0,0},
	{6,30,1.0f,1,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Murky Vitality Mix\r","Health +6\rDefense Rating +30\rAbsorption Rating +1\rBlock Rating +1\r"
#else
	"水晶(活)合成\r","生命 + 6\r防御 + 30\r吸收 + 1\r格档 + 1\r"
#endif
},

{
	{sinOM1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	1,	2,	4,	0,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,0,0,0,0},
	{8,40,1.4f,1,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Devine Vitality Mix\r","Health +8\rDefense Rating +40\rAbsorption Rating +1.4\rBlock Rating +1\r"
#else
	"虎翼(活)合成\r","生命 + 8\r防御 + 40\r吸收 + 1.4\r格档 + 1\r"
#endif
},

{
	{sinOM1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	2,	2,	6,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,0,0,0,0},
	{15,60,2.0f,1,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Celesto Vitality Mix\r","Health +15\rDefense Rating +60\rAbsorption Rating +2\rBlock Rating +1\r"
#else
	"龙鳞(活)合成\r","生命 + 15\r防御 + 60\r吸收 + 2\r格档 + 1\r"
#endif
},

{
	{sinOM1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	3,	2,	4,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,0,0,0,0},
	{25,70,2.2f,1,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Mirage Vitality Mix\r","Health +25\rDefense Rating +70\rAbsorption Rating +2.2\rBlock Rating +1\r"
#else
	"钻晶(活)合成\r","生命 + 25\r防御 + 70\r吸收 + 2.2\r格档 + 1\r"
#endif
},

{
	{sinOM1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	5,	7,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,0,0,0,0},
	{30,95,2.8f,1,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Inferna Vitality Mix\r","Health +30\rDefense Rating +95\rAbsorption Rating +2.8\rBlock Rating +1\r"
#else
	"龙睛(活)合成\r","生命 + 30\r防御 + 95\r吸收 + 2.8\r格档 + 1\r"
#endif
},

{
	{sinOM1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	3,	7,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,0,0,0,0},
	{35,120,3.6f,2,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Enigma Vitality Mix\r","Health +35\rDefense Rating +120\rAbsorption Rating +3.6\rBlock Rating +2\r"
#else
	"圣晶(活)合成\r","生命 + 35\r防御 + 120\r吸收 + 3.6\r格档 + 2\r"
#endif
},

{
	{sinOM1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	7,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,0,0,0,0},
	{45,170,6.0f,2,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Bellum Vitality Mix\r","Health +45\rDefense Rating +170\rAbsorption Rating +6\r格Block Rating +2\r"
#else
	"恶魔(活)合成\r","生命 + 45\r防御 + 170\r吸收 + 6\r格档 + 2\r"
#endif
},

{
	{sinOM1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	3,	7,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,0,0,0,0},
	{60,220,7.0f,3,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Oredo Vitality Mix\r","Health +60\rDefense Rating +220\rAbsorption Rating +7\rBlock Rating +3\r"
#else
	"荣誉(活)合成\r","生命 + 60\r防御 + 220\r吸收 + 7\r格档 + 3\r"
#endif
},

{
	{sinOM1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	2,	3,	5,	3,	0},
	{SIN_ADD_MANA,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,0,0,0,0},
	{200,270,8.0f,5,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sapphire Fortitude Mix\r","Mana +200\rDefense Rating +270\rAbsorption Rating +8\rBlock Rating +5\r"
#else
	"蓝晶(刚)合成\r","魔法 + 200\r防御 + 270\r吸收 + 8\r格档 + 5\r"
#endif
},

{
	{sinOM1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	2,	2,	3,	3,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,0,0,0,0},
	{80,270,8.0f,4,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sapphire Vitality Mix\r","Health +80\rDefense Rating +270\rAbsorption Rating +8\rBlock Rating +4\r"
#else
	"蓝晶(活)合成\r","生命 + 80\r防御 + 270\r吸收 + 8\r格档 + 4\r"
#endif
},

{
	{sinOM1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	10,	0},
	{SIN_ADD_LIFE,SIN_ADD_STAMINA,SIN_ADD_BLOCK_RATE,0,0,0,0,0},
	{130,60,10,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sapphire Block Mix\r","Health +130\rStamina +60\rBlock Rating +10\r"
#else
	"蓝晶(格档)合成\r","生命 + 130\r耐力 + 60\r格档 + 10\r"
#endif
},

{
	{sinOM1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	2,	3,	2,	3},
	{SIN_ADD_MANA,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,0,0,0,0},
	{250,320,9.0f,6,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sol Fortitude Mix\r","Mana +250\rDefense Rating +320\rAbsorption Rating +9\rBlock Rating +6\r"
#else
	"阿波罗(刚)合成\r","魔法 + 250\r防御 + 320\r吸收 + 9\r格档 + 6\r"
#endif
},

{
	{sinOM1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	2,	2,	3,	3},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,0,0,0,0},
	{100,320,9,5,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sol Vitality Mix\r","Health +100\rDefense Rating +320\rAbsorption Rating +9\rBlock Rating +5\r"
#else
	"阿波罗(活)合成\r","生命 + 100\r防御 + 320\r吸收 + 9\r格档 + 5\r"
#endif
},

{
	{sinOM1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	10},
	{SIN_ADD_LIFE,SIN_ADD_STAMINA,SIN_ADD_BLOCK_RATE,0,0,0,0,0},
	{150,80,12,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sol Block Mix\r","Health +150\rStamina +80\rBlock Rating +12\r"
#else
	"阿波罗(格档)合成\r","生命 + 150\r耐力 + 80\r格档 + 12\r"
#endif
},
//臂环
{
	{sinOA2,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	2,	2,	6,	0,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_ATTACK_RATE,SIN_ADD_DEFENCE,SIN_ADD_MANA,SIN_ADD_STAMINA,0,0,0,0},
	{20,20,15,12,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Devine Dexterity Mix\r","Attack Rating +20\rDefense Rating +20\rMana +15\rStamina +12\r"
#else
	"虎翼(技)合成\r","命中 + 20\r防御 + 20\r魔法 + 15\r耐力 + 12\r"
#endif
},
{
	{sinOA2,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	1,	3,	6,	0,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_MANA,SIN_ADD_STAMINA,0,0,0,0},
	{3,15,10,8,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Devine Vitality Mix\r","Health +3\rDefense Rating +15\rMana +10\rStamina +8\r"
#else
	"虎翼(活)合成\r","生命 + 3\r防御 + 15\r魔法 + 10\r耐力 + 8\r"
#endif
},
{
	{sinOA2,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	2,	2,	4,	3,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_MANA,SIN_ADD_STAMINA,0,0,0,0},
	{5,20,15,10,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Celesto Vitality Mix\r","Health +5\rDefense Rating +20\rMana +15\rStamina +10\r"
#else
	"龙鳞(活)合成\r","生命 + 5\r防御 + 20\r魔法 + 15\r耐力 + 10\r"
#endif
},
{
	{sinOA2,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	1,	4,	3,	4,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_ATTACK_RATE,SIN_ADD_DEFENCE,SIN_ADD_MANA,SIN_ADD_STAMINA,0,0,0,0},
	{30,25,20,15,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Celesto Dexterity Mix\r","Attack Rating +30\rDefense Rating +25\rMana +20\rStamina +15\r"
#else
	"龙鳞(技)合成\r","命中 + 30\r防御 + 25\r魔法 + 20\r耐力 + 15\r"
#endif
},
{
	{sinOA2,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	3,	0,	1,	3,	5,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_MANA,SIN_ADD_STAMINA,0,0,0,0},
	{10,30,20,20,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Mirage Vitality Mix\r","Health +10\rDefense Rating +30\rMana +20\rStamina +20\r"
#else
	"钻晶(活)合成\r","生命 + 10\r防御 + 30\r魔法 + 20\r耐力 + 20\r"
#endif
},
{
	{sinOA2,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	2,	5,	5,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_ATTACK_RATE,SIN_ADD_DEFENCE,SIN_ADD_MANA,SIN_ADD_STAMINA,0,0,0,0},
	{50,40,25,25,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Mirage Dexterity Mix\r","Attack Rating +50\rDefense Rating +40\rMana +25\rStamina +25\r"
#else
	"钻晶(技)合成\r","命中 + 50\r防御 + 40\r魔法 + 25\r耐力 + 25\r"
#endif
},
{
	{sinOA2,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	2,	1,	4,	4,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_MANA,SIN_ADD_STAMINA,0,0,0,0},
	{70,55,30,35,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Inferna Dexterity Mix\r","Attack Rating +70\rDefense Rating +55\rMana +30\rStamina +35\r"
#else
	"龙睛(活)合成\r","生命 + 70\r防御 + 55\r魔法 + 30\r耐力 + 35\r"
#endif
},
{
	{sinOA2,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	1,	2,	5,	4,	0,	0,	0,	0,	0},
	{SIN_ADD_ATTACK_RATE,SIN_ADD_DEFENCE,SIN_ADD_MANA,SIN_ADD_STAMINA,0,0,0,0},
	{15,40,25,30,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Inferna Vitality Mix\r","Health +15\rDefense Rating +40\rMana +25\rStamina +30\r"
#else
	"龙睛(技)合成\r","命中 + 15\r防御 + 40\r魔法 + 25\r耐力 + 30\r"
#endif
},
{
	{sinOA2,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	2,	4,	2,	3,	0,	0,	0,	0},
	{SIN_ADD_ATTACK_RATE,SIN_ADD_DEFENCE,SIN_ADD_MANA,SIN_ADD_STAMINA,0,0,0,0},
	{90,70,35,45,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Enigma Dexterity Mix\r","Attack Rating +90\rDefense Rating +70\rMana +35\rStamina +45\r"
#else
	"圣晶(技)合成\r","命中 + 90\r防御 + 70\r魔法 + 35\r耐力 + 45\r"
#endif
},
{
	{sinOA2,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	3,	5,	4,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_MANA,SIN_ADD_STAMINA,0,0,0,0},
	{20,50,30,40,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Enigma Vitality Mix\r","Health +20\rDefense Rating +50\rMana +30\rStamina +40\r"
#else
	"圣晶(活)合成\r","生命 + 20\r防御 + 50\r魔法 + 30\r耐力 + 40\r"
#endif
},
{
	{sinOA2,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	2,	3,	5,	0,	0,	0},
	{SIN_ADD_ATTACK_RATE,SIN_ADD_DEFENCE,SIN_ADD_MANA,SIN_ADD_STAMINA,0,0,0,0},
	{110,95,40,55,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Bellum Dexterity Mix\r","Attack Rating +110\rDefense Rating +95\rMana +40\rStamina +55\r"
#else
	"恶魔(技)合成\r","命中 + 110\r防御 + 95\r魔法 + 40\r耐力 + 55\r"
#endif
},
{
	{sinOA2,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	3,	4,	5,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_MANA,SIN_ADD_STAMINA,0,0,0,0},
	{25,60,35,50,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Bellum Vitality Mix\r","Health +25\rDefense Rating +60\rMana +35\rStamina +50\r"
#else
	"恶魔(活)合成\r","生命 + 25\r防御 + 60\r魔法 + 35\r耐力 + 50\r"
#endif
},
{
	{sinOA2,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	6,	3,	0,	0},
	{SIN_ADD_ATTACK_RATE,SIN_ADD_DEFENCE,SIN_ADD_MANA,SIN_ADD_STAMINA,0,0,0,0},
	{130,110,45,65,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Oredo Dexterity Mix\r","Attack Rating +130\rDefense Rating +110\rMana +45\rStamina +65\r"
#else
	"荣誉(技)合成\r","命中 + 130\r防御 + 110\r魔法 + 45\r耐力 + 65\r"
#endif
},
{
	{sinOA2,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	7,	3,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_MANA,SIN_ADD_STAMINA,0,0,0,0},
	{30,70,40,60,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Oredo Vitality Mix\r","Health +30\rDefense Rating +70\rMana +40\rStamina +60\r"
#else
	"荣誉(活)合成\r","生命 + 30\r防御 + 70\r魔法 + 40\r耐力 + 60\r"
#endif
},
{
	{sinOA2,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	4,	3,	4,	0},
	{SIN_ADD_ATTACK_RATE,SIN_ADD_DEFENCE,SIN_ADD_MANA,SIN_ADD_STAMINA,0,0,0,0},
	{150,130,55,75,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sapphire Dexterity Mix\r","Attack Rating +150\rDefense Rating +130\rMana +55\rStamina +75\r"
#else
	"蓝晶(技)合成\r","命中 + 150\r防御 + 130\r魔法 + 55\r耐力 + 75\r"
#endif
},
{
	{sinOA2,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	3,	4,	4,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_MANA,SIN_ADD_STAMINA,0,0,0,0},
	{40,80,50,70,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sapphire Vitality Mix\r","Health +40\rDefense Rating +80\rMana +50\rStamina +70\r"
#else
	"蓝晶(活)合成\r","生命 + 40\r防御 + 80\r魔法 + 50\r耐力 + 70\r"
#endif
},
{
	{sinOA2,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	4,	3,	4},
	{SIN_ADD_ATTACK_RATE,SIN_ADD_DEFENCE,SIN_ADD_MANA,SIN_ADD_STAMINA,0,0,0,0},
	{170,150,65,85,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sol Dexterity Mix\r","Attack Rating +170\rDefense Rating +150\rMana +65\rStamina +85\r"
#else
	"阿波罗(技)合成\r","命中 + 170\r防御 + 150\r魔法 + 65\r耐力 + 85\r"
#endif
},
{
	{sinOA2,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	3,	4,	4},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_MANA,SIN_ADD_STAMINA,0,0,0,0},
	{50,90,60,80,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sol Vitality Mix\r","Health +50\rDefense Rating +90\rMana +60\rStamina +80\r"
#else
	"阿波罗(活)合成\r","生命 + 50\r防御 + 90\r魔法 + 60\r耐力 + 80\r"
#endif
},
//护手
{
	{sinDG1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	4,	2,	5,	0,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_STAMINA,SIN_ADD_ABSORB,SIN_ADD_DEFENCE,0,0,0,0},
	{8,30,0.8f,10,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Devine Vitality Mix\r","Health +8\rStamina +30\rAbsorption Rating +0.8\rDefense Rating +10\r"
#else
	"虎翼(活)合成\r","生命 + 8\r耐力 + 30\r吸收 + 0.8\r防御 + 10\r"
#endif
},
{
	{sinDG1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	1,	3,	5,	0,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_MANA,SIN_ADD_STAMINA,SIN_ADD_ABSORB,SIN_ADD_DEFENCE,0,0,0,0},
	{25,30,0.8f,40,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Devine Fortitude Mix\r","Mana +25\rStamina +30\rAbsorption Rating +0.8\rDefense Rating +40\r"
#else
	"虎翼(刚)合成\r","魔法 + 25\r耐力 + 30\r吸收 + 0.8\r防御 + 40\r"
#endif
},
{
	{sinDG1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	2,	1,	0,	1,	4,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_MANA,SIN_ADD_STAMINA,SIN_ADD_ABSORB,SIN_ADD_DEFENCE,0,0,0,0},
	{30,40,1.0f,50,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Celesto Fortitude Mix\r","Mana +30\rStamina +40\rAbsorption Rating +1\rDefense Rating +50\r"
#else
	"龙鳞(刚)合成\r","魔法 + 30\r耐力 + 40\r吸收 + 1\r防御 + 50\r"
#endif
},
{
	{sinDG1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	1,	0,	1,	2,	4,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_STAMINA,SIN_ADD_ABSORB,SIN_ADD_DEFENCE,0,0,0,0},
	{10,40,1.0f,20,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Celesto Vitality Mix\r","Health +10\rStamina +40\rAbsorption Rating +1\rDefense Rating +20\r"
#else
	"龙鳞(活)合成\r","生命 + 10\r耐力 + 40\r吸收 + 1\r防御 + 20\r"
#endif
},
{
	{sinDG1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	1,	0,	3,	0,	3,	2,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_MANA,SIN_ADD_STAMINA,SIN_ADD_ABSORB,SIN_ADD_DEFENCE,0,0,0,0},
	{40,60,2.0f,75,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Mirage Fortitude Mix\r","Mana +40\rStamina +60\rAbsorption Rating +2\rDefense Rating +75\r"
#else
	"钻晶(刚)合成\r","魔法 + 40\r耐力 + 60\r吸收 + 2\r防御 + 75\r"
#endif
},
{
	{sinDG1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	2,	0,	1,	3,	3,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_STAMINA,SIN_ADD_ABSORB,SIN_ADD_DEFENCE,0,0,0,0},
	{15,60,2.0f,40,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Mirage Vitality Mix\r","Health +15\rStamina +60\rAbsorption Rating +2\rDefense Rating +40\r"
#else
	"钻晶(活)合成\r","生命 + 15\r耐力 + 60\r吸收 + 2\r防御 + 40\r"
#endif
},
{
	{sinDG1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	1,	2,	0,	3,	0,	3,	0,	0,	0,	0,	0},
	{SIN_ADD_MANA,SIN_ADD_STAMINA,SIN_ADD_ABSORB,SIN_ADD_DEFENCE,0,0,0,0},
	{50,80,3.0f,100,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Inferna Fortitude Mix\r","Mana +50\rStamina +80\rAbsorption Rating +3\rDefense Rating +100\r"
#else
	"龙睛(刚)合成\r","魔法 + 50\r耐力 + 80\r吸收 + 3\r防御 + 100\r"
#endif
},
{
	{sinDG1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	4,	0,	1,	1,	3,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_STAMINA,SIN_ADD_ABSORB,SIN_ADD_DEFENCE,0,0,0,0},
	{20,80,3.0f,60,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Inferna Vitality Mix\r","Health +20\rStamina +80\rAbsorption Rating +3\rDefense Rating +60\r"
#else
	"龙睛(活)合成\r","生命 + 20\r耐力 + 80\r吸收 + 3\r防御 + 60\r"
#endif
},
{
	{sinDG1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	1,	3,	0,	1,	4,	0,	0,	0,	0},
	{SIN_ADD_MANA,SIN_ADD_STAMINA,SIN_ADD_ABSORB,SIN_ADD_DEFENCE,0,0,0,0},
	{60,100,4.0f,125,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Enigma Fortitude Mix\r","Mana +60\rStamina +100\rAbsorption Rating +4\rDefense Rating +125\r"
#else
	"圣晶(刚)合成\r","魔法 + 60\r耐力 + 100\r吸收 + 4\r防御 + 125\r"
#endif
},
{
	{sinDG1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	2,	1,	2,	4,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_STAMINA,SIN_ADD_ABSORB,SIN_ADD_DEFENCE,0,0,0,0},
	{25,100,4.0f,80,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Enigma Vitality Mix\r","Health +25\rStamina +100\rAbsorption Rating +4\rDefense Rating +80\r"
#else
	"圣晶(活)合成\r","生命 + 25\r耐力 + 100\r吸收 + 4\r防御 + 80\r"
#endif
},
{
	{sinDG1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	4,	3,	0,	0,	0},
	{SIN_ADD_MANA,SIN_ADD_STAMINA,SIN_ADD_ABSORB,SIN_ADD_DEFENCE,0,0,0,0},
	{70,120,5.0f,150,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Bellum Fortitude Mix\r","Mana +70\rStamina +120\rAbsorption Rating +5\rDefense Rating +150\r"
#else
	"恶魔(刚)合成\r","魔法 + 70\r耐力 + 120\r吸收 + 5\r防御 + 150\r"
#endif
},
{
	{sinDG1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	1,	3,	0,	1,	4,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_STAMINA,SIN_ADD_ABSORB,SIN_ADD_DEFENCE,0,0,0,0},
	{30,120,5.0f,100,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Bellum Vitality Mix\r","Health +30\rStamina +120\rAbsorption Rating +5\rDefense Rating +100\r"
#else
	"恶魔(活)合成\r","生命 + 30\r耐力 + 120\r吸收 + 5\r防御 + 100\r"
#endif
},
{
	{sinDG1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	2,	3,	0,	3,	0,	0},
	{SIN_ADD_MANA,SIN_ADD_STAMINA,SIN_ADD_ABSORB,SIN_ADD_DEFENCE,0,0,0,0},
	{80,140,6.0f,175,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Oredo Fortitude Mix\r","Mana +80\rStamina +140\rAbsorption Rating +6\rDefense Rating +175\r"
#else
	"荣誉(刚)合成\r","魔法 + 80\r耐力 + 140\r吸收 + 6\r防御 + 175\r"
#endif
},
{
	{sinDG1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	2,	2,	1,	3,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_STAMINA,SIN_ADD_ABSORB,SIN_ADD_DEFENCE,0,0,0,0},
	{35,140,6.0f,120,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Oredo Vitality Mix\r","Health +35\rStamina +140\rAbsorption Rating +6\rDefense Rating +120\r"
#else
	"荣誉(活)合成\r","生命 + 35\r耐力 + 140\r吸收 + 6\r防御 + 120\r"
#endif
},
{
	{sinDG1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	2,	3,	2,	4,	0},
	{SIN_ADD_MANA,SIN_ADD_STAMINA,SIN_ADD_ABSORB,SIN_ADD_DEFENCE,0,0,0,0},
	{90,160,7.0f,200,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sapphire Fortitude Mix\r","Mana +90\rStamina +160\rAbsorption Rating +7\rDefense Rating +200\r"
#else
	"蓝晶(刚)合成\r","魔法 + 90\r耐力 + 160\r吸收 + 7\r防御 + 200\r"
#endif
},
{
	{sinDG1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	5,	3,	4,	0},
	{SIN_ADD_LIFE,SIN_ADD_STAMINA,SIN_ADD_ABSORB,SIN_ADD_DEFENCE,0,0,0,0},
	{40,160,7.0f,140,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sapphire Vitality Mix\r","Health +40\rStamina +160\rAbsorption Rating +7\rDefense Rating +140\r"
#else
	"蓝晶(活)合成\r","生命 + 40\r耐力 + 160\r吸收 + 7\r防御 + 140\r"
#endif
},
{
	{sinDG1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	2,	3,	2,	4},
	{SIN_ADD_MANA,SIN_ADD_STAMINA,SIN_ADD_ABSORB,SIN_ADD_DEFENCE,0,0,0,0},
	{100,180,8.0f,225,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sol Fortitude Mix\r","Mana +100\rStamina +180\rAbsorption Rating +8\rDefense Rating +225\r"
#else
	"阿波罗(刚)合成\r","魔法 + 100\r耐力 + 180\r吸收 + 8.0\r防御 + 225\r"
#endif
},
{
	{sinDG1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	5,	3,	4},
	{SIN_ADD_LIFE,SIN_ADD_STAMINA,SIN_ADD_ABSORB,SIN_ADD_DEFENCE,0,0,0,0},
	{45,180,8.0f,160,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sol Vitality Mix\r","Health +45\rStamina +180\rAbsorption Rating +8\rDefense Rating +160\r"
#else
	"阿波罗(活)合成\r","生命 + 45\r耐力 + 180\r吸收 + 8.0\r防御 + 160\r"
#endif
},
//鞋子
{
	{sinDB1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	2,	2,	4,	0,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_ABSORB,SIN_ADD_MOVE_SPEED,0,0,0,0,0},
	{8,1.2f,0.6f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Devine Velocity Mix\r","Health +8\rAbsorption Rating +1.2\rMovement Speed +0.6\r"
#else
	"虎翼(活)合成\r","生命 + 8\r吸收 + 1.2\r移动速度 + 0.6\r"
#endif
},
{
	{sinDB1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	2,	1,	5,	0,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_MANA,SIN_ADD_MOVE_SPEED,0,0,0,0,0},
	{15,8,0.4f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Devine Fortitude Mix\r","Health +15\rMana +8\rMovement Speed +0.4\r"
#else
	"虎翼(刚)合成\r","生命 + 15\r魔法 + 8\r移动速度 + 0.4\r"
#endif
},
{
	{sinDB1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	1,	3,	4,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_MANA,SIN_ADD_MOVE_SPEED,0,0,0,0,0},
	{20,10,0.6f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Celesto Fortitude Mix\r","Health +20\rMana +10\rMovement Speed +0.6\r"
#else
	"龙鳞(刚)合成\r","生命 + 20\r魔法 + 10\r移动速度 + 0.6\r"
#endif
},
{
	{sinDB1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	2,	3,	5,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_ABSORB,SIN_ADD_MOVE_SPEED,0,0,0,0,0},
	{10,1.8f,1.0f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Celesto Velocity Mix\r","Health +10\rAbsorption Rating +1.8\rMovement Speed +1\r"
#else
	"龙鳞(活)合成\r","生命 + 10\r吸收 + 1.8\r移动速度 + 1\r"
#endif
},
{
	{sinDB1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	1,	0,	3,	2,	4,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_MANA,SIN_ADD_MOVE_SPEED,0,0,0,0,0},
	{25,20,1.0f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Mirage Fortitude Mix\r","Health +25\rMana +20\rMovement Speed +1\r"
#else
	"钻晶(刚)合成\r","生命 + 25\r魔法 + 20\r移动速度 + 1\r"
#endif
},
{
	{sinDB1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	5,	5,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_ABSORB,SIN_ADD_MOVE_SPEED,0,0,0,0,0},
	{10,2.4f,1.6f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Mirage Velocity Mix\r","Health +10\rAbsorption Rating +2.4\rMovement Speed +1.6\r"
#else
	"钻晶(活)合成\r","生命 + 10\r吸收 + 2.4\r移动速度 + 1.6\r"
#endif
},
{
	{sinDB1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	1,	2,	5,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_MANA,SIN_ADD_MOVE_SPEED,0,0,0,0,0},
	{30,30,1.4f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Inferna Fortitude Mix\r","Health +30\rMana +30\rMovement Speed +1.4\r"
#else
	"龙睛(刚)合成\r","生命 + 30\r魔法 + 30\r移动速度 + 1.4\r"
#endif
},
{
	{sinDB1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	2,	3,	5,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_ABSORB,SIN_ADD_MOVE_SPEED,0,0,0,0,0},
	{15,3.0f,2.2f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Inferna Velocity Mix\r","Health +15\rAbsorption Rating +3\rMovement Speed +2.2\r"
#else
	"龙睛(活)合成\r","生命 + 15\r吸收 + 3\r移动速度 + 2.2\r"
#endif
},
{
	{sinDB1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	4,	2,	4,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_MANA,SIN_ADD_MOVE_SPEED,0,0,0,0,0},
	{35,40,1.8f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Enigma Fortitude Mix\r","Health +35\rMana +40\rMovement Speed +1.8\r"
#else
	"圣晶(刚)合成\r","生命 + 35\r魔法 + 40\r移动速度 + 1.8\r"
#endif
},
{
	{sinDB1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	6,	2,	4,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_ABSORB,SIN_ADD_MOVE_SPEED,0,0,0,0,0},
	{20,3.6f,3.0f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Enigma Velocity Mix\r","Health +20\rAbsorption Rating +3.6\rMovement Speed +3\r"
#else
	"圣晶(活)合成\r","生命 + 20\r吸收 + 3.6\r移动速度 + 3\r"
#endif
},
{
	{sinDB1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	2,	6,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_MANA,SIN_ADD_MOVE_SPEED,0,0,0,0,0},
	{40,50,2.2f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Bellum Fortitude Mix\r","Health +40\rMana +50\rMovement Speed +2.2\r"
#else
	"恶魔(刚)合成\r","生命 + 40\r魔法 + 50\r移动速度 + 2.2\r"
#endif
},
{
	{sinDB1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	3,	7,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_ABSORB,SIN_ADD_MOVE_SPEED,0,0,0,0,0},
	{25,4.2f,3.8f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Bellum Velocity Mix\r","Health +25\rAbsorption Rating +4.2\rMovement Speed +3.8\r"
#else
	"恶魔(活)合成\r","生命 + 25\r吸收 + 4.2\r移动速度 + 3.8\r"
#endif
},
{
	{sinDB1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	3,	6,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_MANA,SIN_ADD_MOVE_SPEED,0,0,0,0,0},
	{45,60,2.6f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Oredo Fortitude Mix\r","Health +45\rMana +60\rMovement Speed +2.6\r"
#else
	"荣誉(刚)合成\r","生命 + 45\r魔法 + 60\r移动速度 + 2.6\r"
#endif
},
{
	{sinDB1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	3,	9,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_ABSORB,SIN_ADD_MOVE_SPEED,0,0,0,0,0},
	{30,4.8f,4.6f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Oredo Velocity Mix\r","Health +30\rAbsorption Rating +4.8\rMovement Speed +4.6\r"
#else
	"荣誉(活)合成\r","生命 + 30\r吸收 + 4.8\r移动速度 + 4.6\r"
#endif
},
{
	{sinDB1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	2,	3,	6,	0},
	{SIN_ADD_LIFE,SIN_ADD_MANA,SIN_ADD_MOVE_SPEED,0,0,0,0,0},
	{60,70,3.0f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sapphire Fortitude Mix\r","Health +60\rMana +70\rMovement Speed +3\r"
#else
	"蓝晶(刚)合成\r","生命 + 60\r魔法 + 70\r移动速度 + 3\r"
#endif
},
{
	{sinDB1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	3,	9,	0},
	{SIN_ADD_LIFE,SIN_ADD_ABSORB,SIN_ADD_MOVE_SPEED,0,0,0,0,0},
	{35,5.5f,5.4f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sapphire Velocity Mix\r","Health +35\rAbsorption Rating +5.5\rMovement Speed +5.4\r"
#else
	"蓝晶(活)合成\r","生命 + 35\r吸收 + 5.5\r移动速度 + 5.4\r"
#endif
},
{
	{sinDB1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	2,	3,	6},
	{SIN_ADD_LIFE,SIN_ADD_MANA,SIN_ADD_MOVE_SPEED,0,0,0,0,0},
	{70,80,3.4f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sol Fortitude Mix\r","Health +70\rMana +80\rMovement Speed +3.4\r"
#else
	"阿波罗(刚)合成\r","生命 + 70\r魔法 + 80\r移动速度 + 3.4\r"
#endif
},
{
	{sinDB1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	3,	9},
	{SIN_ADD_LIFE,SIN_ADD_ABSORB,SIN_ADD_MOVE_SPEED,0,0,0,0,0},
	{40,6.2f,6.0f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sol Velocity Mix\r","Health +40\rAbsorption Rating +6.2\rMovement Speed +6\r"
#else
	"阿波罗(活)合成\r","生命 + 40\r吸收 + 6.2\r移动速度 + 6\r"
#endif
},
{
	{sinDB1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	10},
	{SIN_ADD_STAMINA,SIN_ADD_MOVE_SPEED,0,0,0,0,0,0},
	{1000,9.0f,0,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sol Endurance Mix\r","Stamina +1000\rMovement Speed +9\r"
#else
	"阿波罗(速)合成\r","耐力 + 1000\r移动速度 + 9\r"
#endif
},
//项链
{
	{sinOA1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	1,	4,	2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_MANA,SIN_ADD_MANAREGEN,0,0,0,0,0,0},
	{3,0.1f,0,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Transpero Efficiency Mix\r","Mana +3\rMana Regen +0.1\r"
#else
	"玄风(魔)合成\r","魔法 + 3\r魔法回复 + 0.1\r"
#endif
},
{
	{sinOA1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	1,	2,	4,	0,	0,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_MANA,SIN_ADD_MANAREGEN,0,0,0,0,0,0},
	{3,0.2f,0,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Murky Efficiency Mix\r","Mana +3\rMana Regen +0.2\r"
#else
	"水晶(魔)合成\r","魔法 + 3\r魔法回复 + 0.2\r"
#endif
},
{
	{sinOA1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	3,	2,	5,	0,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_MANA,SIN_ADD_LIFEREGEN,SIN_ADD_MANAREGEN,0,0,0,0,0},
	{5,0.2f,0.2f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Devine Efficiency Mix\r","Mana +5\rHealth Regen +0.2\rMana Regen +0.2\r"
#else
	"虎翼(魔)合成\r","魔法 + 5\r生命回复 + 0.2\r魔法回复 + 0.2\r"
#endif
},
{
	{sinOA1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	1,	0,	3,	4,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_MANA,SIN_ADD_LIFEREGEN,SIN_ADD_MANAREGEN,0,0,0,0,0},
	{6,0.4f,0.3f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Celesto Efficiency Mix #1\r","Mana +6\rHealth Regen +0.4\rMana Regen +0.3\r"
#else
	"龙鳞(魔)合成#1\r","魔法 + 6\r生命回复 + 0.4\r魔法回复 + 0.3\r"
#endif
},
{
	{sinOA1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	1,	4,	5,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_MANA,SIN_ADD_LIFEREGEN,SIN_ADD_MANAREGEN,0,0,0,0,0},
	{8,0.8f,0.6f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Celesto Efficiency Mix #2\r","Mana +8\rHealth Regen +0.8\rMana Regen +0.6\r"
#else
	"龙鳞(魔)合成#2\r","魔法 + 8\r生命回复 + 0.8\r魔法回复 + 0.6\r"
#endif
},
{
	{sinOA1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	1,	2,	4,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_MANA,SIN_ADD_LIFEREGEN,SIN_ADD_MANAREGEN,0,0,0,0,0},
	{10,1.2f,0.9f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Mirage Efficiency Mix #1\r","Mana +10\rHealth Regen +1.2\rMana Regen +0.9\r"
#else
	"钻晶(魔)合成#1\r","魔法 + 10\r生命回复 + 1.2\r魔法回复 + 0.9\r"
#endif
},
{
	{sinOA1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	3,	6,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_MANA,SIN_ADD_LIFEREGEN,SIN_ADD_MANAREGEN,0,0,0,0,0},
	{12,1.6f,1.2f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Mirage Efficiency Mix #2\r","Mana +12\rHealth Regen +1.6\rMana Regen +1.2\r"
#else
	"钻晶(魔)合成#2\r","魔法 + 12\r生命回复 + 1.6\r魔法回复 + 1.2\r"
#endif
},
{
	{sinOA1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	4,	3,	0,	0,	0,	0,	0},
	{SIN_ADD_MANA,SIN_ADD_LIFEREGEN,SIN_ADD_MANAREGEN,0,0,0,0,0},
	{14,2.0f,1.5f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Inferna Efficiency Mix #1\r","Mana +14\rHealth Regen +2\rMana Regen +1.5\r"
#else
	"龙睛(魔)合成#1\r","魔法 + 14\r生命回复 + 2\r魔法回复 + 1.5\r"
#endif
},
{
	{sinOA1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	1,	2,	5,	0,	0,	0,	0,	0},
	{SIN_ADD_MANA,SIN_ADD_LIFEREGEN,SIN_ADD_MANAREGEN,0,0,0,0,0},
	{16,2.4f,1.8f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Inferna Efficiency Mix #2\r","Mana +16\rHealth Regen +2.4\rMana Regen +1.8\r"
#else
	"龙睛(魔)合成#2\r","魔法 + 16\r生命回复 + 2.4\r魔法回复 + 1.8\r"
#endif
},
{
	{sinOA1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	4,	3,	0,	0,	0,	0},
	{SIN_ADD_MANA,SIN_ADD_LIFEREGEN,SIN_ADD_MANAREGEN,0,0,0,0,0},
	{18,2.8f,2.1f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Enigma Efficiency Mix #1\r","Mana +18\rHealth Regen +2.8\rMana Regen +2.1\r"
#else
	"圣晶(魔)合成#1\r","魔法 + 18\r生命回复 + 2.8\r魔法回复 + 2.1\r"
#endif
},
{
	{sinOA1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	3,	1,	5,	0,	0,	0,	0},
	{SIN_ADD_MANA,SIN_ADD_LIFEREGEN,SIN_ADD_MANAREGEN,0,0,0,0,0},
	{20,3.2f,2.4f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Enigma Efficiency Mix #2\r","Mana +20\rHealth Regen +3.2\rMana Regen +2.4\r"
#else
	"圣晶(魔)合成#2\r","魔法 + 20\r生命回复 + 3.2\r魔法回复 + 2.4\r"
#endif
},
{
	{sinOA1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	3,	4,	0,	0,	0},
	{SIN_ADD_MANA,SIN_ADD_LIFEREGEN,SIN_ADD_MANAREGEN,0,0,0,0,0},
	{22,3.6f,2.7f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Bellum Efficiency Mix #1\r","Mana +22\rHealth Regen +3.6\rMana Regen +2.7\r"
#else
	"恶魔(魔)合成#1\r","魔法 + 22\r生命回复 + 3.6\r魔法回复 + 2.7\r"
#endif
},
{
	{sinOA1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	3,	6,	0,	0,	0},
	{SIN_ADD_MANA,SIN_ADD_LIFEREGEN,SIN_ADD_MANAREGEN,0,0,0,0,0},
	{24,4.0f,3.0f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Bellum Efficiency Mix #2\r","Mana +24\rHealth Regen +4\rMana Regen +3\r"
#else
	"恶魔(魔)合成#2\r","魔法 + 24\r生命回复 + 4\r魔法回复 + 3\r"
#endif
},
{
	{sinOA1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	4,	4,	0,	0},
	{SIN_ADD_MANA,SIN_ADD_LIFEREGEN,SIN_ADD_MANAREGEN,0,0,0,0,0},
	{26,4.4f,3.3f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Oredo Efficiency Mix #1\r","Mana +26\rHealth Regen +4.4\rMana Regen +3.3\r"
#else
	"荣誉(魔)合成#1\r","魔法 + 26\r生命回复 + 4.4\r魔法回复 + 3.3\r"
#endif
},
{
	{sinOA1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	2,	6,	0,	0},
	{SIN_ADD_MANA,SIN_ADD_LIFEREGEN,SIN_ADD_MANAREGEN,0,0,0,0,0},
	{28,4.6f,3.6f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Oredo Efficiency Mix #2\r","Mana +28\rHealth Regen +4.6\rMana Regen +3.6\r"
#else
	"荣誉(魔)合成#2\r","魔法 + 28\r生命回复 + 4.6\r魔法回复 + 3.6\r"
#endif
},
{
	{sinOA1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	3,	0,	2,	5,	0},
	{SIN_ADD_MANA,SIN_ADD_LIFEREGEN,SIN_ADD_MANAREGEN,0,0,0,0,0},
	{30,5.2f,3.9f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sapphire Efficiency Mix #1\r","Mana +30\rHealth Regen +5.2\rMana Regen +3.9\r"
#else
	"蓝晶(魔)合成#1\r","魔法 + 30\r生命回复 + 5.2\r魔法回复 + 3.9\r"
#endif
},
{
	{sinOA1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	3,	7,	0},
	{SIN_ADD_MANA,SIN_ADD_LIFEREGEN,SIN_ADD_MANAREGEN,0,0,0,0,0},
	{32,5.4f,4.2f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sapphire Efficiency Mix #2\r","Mana +32\rHealth Regen +5.4\rMana Regen +4.2\r"
#else
	"蓝晶(魔)合成#2\r","魔法 + 32\r生命回复 + 5.4\r魔法回复 + 4.2\r"
#endif
},
{
	{sinOA1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	3,	0,	2,	5},
	{SIN_ADD_MANA,SIN_ADD_LIFEREGEN,SIN_ADD_MANAREGEN,0,0,0,0,0},
	{34,6.0f,4.5f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sol Efficiency Mix #1\r","Mana +34\rHealth Regen +6\rMana Regen +4.5\r"
#else
	"阿波罗(魔)合成#1\r","魔法 + 34\r生命回复 + 6\r魔法回复 + 4.5\r"
#endif
},
{
	{sinOA1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	3,	7},
	{SIN_ADD_MANA,SIN_ADD_LIFEREGEN,SIN_ADD_MANAREGEN,0,0,0,0,0},
	{32,5.4f,4.2f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sapphire Efficiency Mix #2\r","Mana +32\rHealth Regen +5.4\rMana Regen +4.2\r"
#else
	"阿波罗(魔)合成#2\r","魔法 + 32\r生命回复 + 5.4\r魔法回复 + 4.2\r"
#endif
},
//戒指
{
	{sinOR1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	2,	2,	5,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_STAMINA,SIN_ADD_STAMINAREGEN,0,0,0,0,0,0},
	{3,0.6f,0,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Transpero Efficiency Mix\r","Stamina +3\rStamina Regen +0.6\r"
#else
	"玄风(魔)合成\r","耐力 + 3\r耐力回复 + 0.6\r"
#endif
},
{
	{sinOR1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	3,	2,	4,	0,	0,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_STAMINA,SIN_ADD_STAMINAREGEN,0,0,0,0,0,0},
	{4,0.8f,0,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Murky Efficiency Mix\r","Stamina +4\rStamina Regen +0.8\r"
#else
	"水晶(魔)合成\r","耐力 + 4\r耐力回复 + 0.8\r"
#endif
},
{
	{sinOR1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	1,	3,	4,	0,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_STAMINA,SIN_ADD_STAMINAREGEN,0,0,0,0,0,0},
	{5,1.0f,0,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Devine Efficiency Mix\r","Stamina +5\rStamina Regen +1\r"
#else
	"虎翼(魔)合成\r","耐力 + 5\r耐力回复 + 1\r"
#endif
},
{
	{sinOR1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	1,	3,	4,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_STAMINA,SIN_ADD_STAMINAREGEN,0,0,0,0,0,0},
	{6,1.2f,0,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Celesto Efficiency Mix #1\r","Stamina +6\rStamina Regen +1.2\r"
#else
	"龙鳞(魔)合成#1\r","耐力 + 6\r耐力回复 + 1.2\r"
#endif
},
{
	{sinOR1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	2,	3,	5,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_STAMINA,SIN_ADD_STAMINAREGEN,0,0,0,0,0,0},
	{8,1.6f,0,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Celesto Efficiency Mix #2\r","Stamina +8\rStamina Regen +1.6\r"
#else
	"龙鳞(魔)合成#2\r","耐力 + 8\r耐力回复 + 1.6\r"
#endif
},
{
	{sinOR1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	1,	4,	4,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_MANA,SIN_ADD_STAMINA,SIN_ADD_STAMINAREGEN,0,0,0,0},
	{2,6,10,1.0f,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Mirage Efficiency Mix #1\r","Health +2\rStamina +10\rMana +6\rStamina Regen +1\r"
#else
	"钻晶(魔)合成#1\r","生命 + 2\r魔法 + 6\r耐力 + 10\r耐力回复 + 1\r"
#endif
},
{
	{sinOR1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	2,	6,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_MANA,SIN_ADD_STAMINA,SIN_ADD_STAMINAREGEN,0,0,0,0},
	{4,8,12,1.4f,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Mirage Efficiency Mix #2\r","Health +4\rStamina +12\rMana +8\rStamina Regen +1.4\r"
#else
	"钻晶(魔)合成#2\r","生命 + 4\r魔法 + 8\r耐力 + 12\r耐力回复 + 1.4\r"
#endif
},
{
	{sinOR1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	3,	4,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_MANA,SIN_ADD_STAMINA,SIN_ADD_STAMINAREGEN,0,0,0,0},
	{6,10,14,1.8f,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Inferna Efficiency Mix #1\r","Health +6\rStamina +14\rMana +10\rStamina Regen +1.8\r"
#else
	"龙睛(魔)合成#1\r","生命 + 6\r魔法 + 10\r耐力 + 14\r耐力回复 + 1.8\r"
#endif
},
{
	{sinOR1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	5,	5,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_MANA,SIN_ADD_STAMINA,SIN_ADD_STAMINAREGEN,0,0,0,0},
	{8,12,16,2.2f,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Inferna Efficiency Mix #2\r","Health +8\rStamina +16\rMana +12\rStamina Regen +2.2\r"
#else
	"龙睛(魔)合成#2\r","生命 + 8\r魔法 + 12\r耐力 + 16\r耐力回复 + 2.2\r"
#endif
},
{
	{sinOR1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	3,	2,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_MANA,SIN_ADD_STAMINA,SIN_ADD_STAMINAREGEN,0,0,0,0},
	{10,14,18,2.6f,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Enigma Efficiency Mix #1\r","Health +10\rStamina +18\rMana +14\rStamina Regen +2.6\r"
#else
	"圣晶(魔)合成#1\r","生命 + 10\r魔法 + 14\r耐力 + 18\r耐力回复 + 2.6\r"
#endif
},
{
	{sinOR1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	4,	3,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_MANA,SIN_ADD_STAMINA,SIN_ADD_STAMINAREGEN,0,0,0,0},
	{12,16,20,3.0f,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Enigma Efficiency Mix #2\r","Health +12\rStamina +20\rMana +16\rStamina Regen +3\r"
#else
	"圣晶(魔)合成#2\r","生命 + 12\r魔法 + 16\r耐力 + 20\r耐力回复 + 3\r"
#endif
},
{
	{sinOR1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	2,	2,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_MANA,SIN_ADD_STAMINA,SIN_ADD_STAMINAREGEN,0,0,0,0},
	{14,18,22,3.4f,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Bellum Efficiency Mix #1\r","Health +14\rStamina +22\rMana +18\rStamina Regen +3.4\r"
#else
	"恶魔(魔)合成#1\r","生命 + 14\r魔法 + 18\r耐力 + 22\r耐力回复 + 3.4\r"
#endif
},
{
	{sinOR1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	2,	4,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_MANA,SIN_ADD_STAMINA,SIN_ADD_STAMINAREGEN,0,0,0,0},
	{16,20,24,3.8f,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Bellum Efficiency Mix #2\r","Health +16\rStamina +24\rMana +20\rStamina Regen +3.8\r"
#else
	"恶魔(魔)合成#2\r","生命 + 16\r魔法 + 20\r耐力 + 24\r耐力回复 + 3.8\r"
#endif
},
{
	{sinOR1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	3,	3,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_MANA,SIN_ADD_STAMINA,SIN_ADD_STAMINAREGEN,0,0,0,0},
	{18,22,26,4.2f,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Oredo Efficiency Mix #1\r","Health +18\rStamina +26\rMana +22\rStamina Regen +4.2\r"
#else
	"荣誉(魔)合成#1\r","生命 + 18\r魔法 + 22\r耐力 + 26\r耐力回复 + 4.2\r"
#endif
},
{
	{sinOR1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	3,	4,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_MANA,SIN_ADD_STAMINA,SIN_ADD_STAMINAREGEN,0,0,0,0},
	{20,24,28,4.6f,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Oredo Efficiency Mix #2\r","Health +20\rStamina +28\rMana +24\rStamina Regen +4.6\r"
#else
	"荣誉(魔)合成#2\r","生命 + 20\r魔法 + 24\r耐力 + 28\r耐力回复 + 4.6\r"
#endif
},
{
	{sinOR1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	4,	3,	2,	3,	0},
	{SIN_ADD_LIFE,SIN_ADD_MANA,SIN_ADD_STAMINA,SIN_ADD_STAMINAREGEN,0,0,0,0},
	{22,26,30,5.0f,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sapphire Efficiency Mix #1\r","Health +22\rStamina +30\rMana +26\rStamina Regen +5\r"
#else
	"蓝晶(魔)合成#1\r","生命 + 22\r魔法 + 26\r耐力 + 30\r耐力回复 + 5\r"
#endif
},
{
	{sinOR1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	3,	2,	3,	4,	0},
	{SIN_ADD_LIFE,SIN_ADD_MANA,SIN_ADD_STAMINA,SIN_ADD_STAMINAREGEN,0,0,0,0},
	{24,28,32,5.4f,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sapphire Efficiency Mix #2\r","Health +24\rStamina +32\rMana +28) \rStamina Regen +5.4\r"
#else
	"蓝晶(魔)合成#2\r","生命 + 24\r魔法 + 28\r耐力 + 32\r耐力回复 + 5.4\r"
#endif
},
{
	{sinOR1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	4,	3,	2,	3},
	{SIN_ADD_LIFE,SIN_ADD_MANA,SIN_ADD_STAMINA,SIN_ADD_STAMINAREGEN,0,0,0,0},
	{26,30,34,5.8f,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sol Efficiency Mix #1\r","Health +26\rStamina +34\rMana +30\rStamina Regen +5.8\r"
#else
	"阿波罗(魔)合成#1\r","生命 + 26\r魔法 + 30\r耐力 + 34\r耐力回复 + 5.8\r"
#endif
},
{
	{sinOR1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	3,	2,	3,	4},
	{SIN_ADD_LIFE,SIN_ADD_MANA,SIN_ADD_STAMINA,SIN_ADD_STAMINAREGEN,0,0,0,0},
	{28,32,36,6.2f,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sol Efficiency Mix #2\r","Health +28\rStamina +36\rMana +32\rStamina Regen +6.2\r"
#else
	"阿波罗(魔)合成#2\r","生命 + 28\r魔法 + 32\r耐力 + 36\r耐力回复 + 6.2\r"
#endif
},
// 石头
{
	{sinOS1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	2,	1,	0,	6,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_DEFENCE,0,0,0,0,0,0,0},
	{25,0,0,0,0,0,0,0},
	{SIN_ADD_NUM,0,0,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Celesto Aegis Mix\r","Defense Rating +25\r"
#else
	"龙鳞(防)合成\r","防御 + 25\r"
#endif
},
{
	{sinOS1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	2,	0,	0,	1,	6,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_DAMAGE_MAX,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0},
	{SIN_ADD_NUM,0,0,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Celesto Vigor Mix\r","Maximum Attack Power +1\r"
#else
	"龙鳞(攻)合成\r","最大攻击 + 1\r"
#endif
},
{
	{sinOS1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	2,	1,	0,	6,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_DEFENCE,0,0,0,0,0,0,0},
	{60,0,0,0,0,0,0,0},
	{SIN_ADD_NUM,0,0,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Mirage Aegis Mix\r","Defense Rating +60\r"
#else
	"钻晶(防)合成\r","防御 + 60\r"
#endif
},
{
	{sinOS1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	2,	0,	0,	1,	6,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,0,0,0,0,0,0},
	{1,1,0,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Mirage Vigor Mix\r","Minimum Attack Power +1\rMaximum Attack Power +1\r"
#else
	"钻晶(攻)合成\r","最小攻击 + 1\r最大攻击 + 1\r"
#endif
},
{
	{sinOS1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	2,	1,	0,	6,	0,	0,	0,	0,	0},
	{SIN_ADD_DEFENCE,0,0,0,0,0,0,0},
	{95,0,0,0,0,0,0,0},
	{SIN_ADD_NUM,0,0,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Inferna Aegis Mix\r","Defense Rating +95\r"
#else
	"龙睛(防)合成\r","防御 + 95\r"
#endif
},
{
	{sinOS1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	2,	0,	0,	1,	6,	0,	0,	0,	0,	0},
	{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,0,0,0,0,0,0},
	{1,2,0,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Inferna Vigor Mix\r","Minimum Attack Power +1\rMaximum Attack Power +2\r"
#else
	"龙睛(攻)合成\r","最小攻击 + 1\r最大攻击 + 2\r"
#endif
},
{
	{sinOS1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	2,	1,	0,	6,	0,	0,	0,	0},
	{SIN_ADD_DEFENCE,0,0,0,0,0,0,0},
	{130,0,0,0,0,0,0,0},
	{SIN_ADD_NUM,0,0,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Enigma Aegis Mix\r","Defense Rating +130\r"
#else
	"圣晶(防)合成\r","防御 + 130\r"
#endif
},
{
	{sinOS1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	2,	0,	0,	1,	6,	0,	0,	0,	0},
	{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,0,0,0,0,0,0},
	{2,2,0,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Enigma Vigor Mix\r","Minimum Attack Power +2\rMaximum Attack Power +2\r"
#else
	"圣晶(攻)合成\r","最小攻击 + 2\r最大攻击 + 2\r"
#endif
},
{
	{sinOS1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	1,	0,	6,	0,	0,	0},
	{SIN_ADD_DEFENCE,0,0,0,0,0,0,0},
	{165,0,0,0,0,0,0,0},
	{SIN_ADD_NUM,0,0,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Bellum Aegis Mix\r","Defense Rating +165\r"
#else
	"恶魔(防)合成\r","防御 + 165\r"
#endif
},
{
	{sinOS1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	0,	1,	6,	0,	0,	0},
	{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,0,0,0,0,0,0},
	{2,3,0,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Bellum Vigor Mix\r","Minimum Attack Power +2\rMaximum Attack Power +3\r"
#else
	"恶魔(攻)合成\r","最小攻击 + 2\r最大攻击 + 3\r"
#endif
},
{
	{sinOS1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	1,	0,	6,	0,	0},
	{SIN_ADD_DEFENCE,0,0,0,0,0,0,0},
	{200,0,0,0,0,0,0,0},
	{SIN_ADD_NUM,0,0,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Oredo Aegis Mix\r","Defense Rating +200\r"
#else
	"荣誉(防)合成\r","防御 + 200\r"
#endif
},
{
	{sinOS1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	1,	6,	0,	0},
	{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,0,0,0,0,0,0},
	{3,3,0,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Oredo Vigor Mix\r","Minimum Attack Power +3\rMaximum Attack Power +3\r"
#else
	"荣誉(攻)合成\r","最小攻击 + 3\r最大攻击 + 3\r"
#endif
},
{
	{sinOS1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	2,	6,	0},
	{SIN_ADD_DEFENCE,0,0,0,0,0,0,0},
	{250,0,0,0,0,0,0,0},
	{SIN_ADD_NUM,0,0,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sapphire Aegis Mix\r","Defense Rating +250\r"
#else
	"蓝晶(防)合成\r","防御 + 250\r"
#endif
},
{
	{sinOS1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	3,	6,	0},
	{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,0,0,0,0,0,0},
	{3,4,0,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sapphire Vigor Mix\r","Minimum Attack Power +3\rMaximum Attack Power +4\r"
#else
	"蓝晶(攻)合成\r","最小攻击 + 3\r最大攻击 + 4\r"
#endif
},
{
	{sinOS1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	2,	2,	6},
	{SIN_ADD_DEFENCE,0,0,0,0,0,0,0},
	{300,0,0,0,0,0,0,0},
	{SIN_ADD_NUM,0,0,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sol Aegis Mix\r","Defense Rating +300\r"
#else
	"阿波罗(防)合成\r","防御 + 300\r"
#endif
},
{
	{sinOS1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	2,	3,	6},
	{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,0,0,0,0,0,0},
	{4,4,0,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Sol Vigor Mix\r","Minimum Attack Power +4\rMaximum Attack Power +4\r"
#else
	"阿波罗(攻)合成\r","最小攻击 + 4\r最大攻击 + 4\r"
#endif
},