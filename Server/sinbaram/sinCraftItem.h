//// ��! �������� �ͱ۾� ���� ��������

#define   SIN_ADD_FIRE				0x00000001	//������
#define   SIN_ADD_ICE				0x00000002	//������
#define   SIN_ADD_LIGHTNING			0x00000004	//������
#define   SIN_ADD_POISON			0x00000008	//������
#define   SIN_ADD_BIO				0x00000010	//ħ����
#define   SIN_ADD_CRITICAL			0x00000020	//��ɱ
#define   SIN_ADD_ATTACK_RATE		0x00000040	//����
#define   SIN_ADD_DAMAGE_MIN		0x00000080	//��С������
#define   SIN_ADD_DAMAGE_MAX		0x00000100	//��󹥻���
#define   SIN_ADD_ATTACK_SPEED		0x00000200	//�����ٶ�
#define   SIN_ADD_ABSORB			0x00000400	//����
#define   SIN_ADD_DEFENCE			0x00000800	//����
#define   SIN_ADD_BLOCK_RATE		0x00001000	//��
#define   SIN_ADD_MOVE_SPEED		0x00002000	//�ƶ��ٶ�
#define   SIN_ADD_LIFE				0x00004000	//��������
#define   SIN_ADD_MANA				0x00008000	//ħ������
#define   SIN_ADD_STAMINA			0x00010000	//��������
#define   SIN_ADD_LIFEREGEN			0x00020000  //�����ظ�
#define   SIN_ADD_MANAREGEN			0x00040000  //ħ���ظ�
#define   SIN_ADD_STAMINAREGEN		0x00080000  //�����ظ�

#define   SIN_ADD_NUM				1 
#define   SIN_ADD_PERCENT			2 //����

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
	"��ħ(��)�ϳ�\r","��С���� + 14\r��󹥻� + 16\r��ɱ + 5%\rħ�� + 30\r"
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
	"��ħ(��)�ϳ�\r","��С���� + 14\r��󹥻� + 16\r��ɱ + 4%\r���� + 30\r"
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
	"����(��)�ϳ�\r","��С���� + 14\r��󹥻� + 19\r���� + 150\r���� + 30\r"
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
	"����(��)�ϳ�\r","��С���� + 16\r��󹥻� + 18\r��ɱ + 5%\rħ�� + 40\r"
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
	"����(��)�ϳ�\r","��С���� + 16\r��󹥻� + 18\r��ɱ + 4%\r���� + 35\r"
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
	"����(��)�ϳ�\r","�����ٶ� + 1\r���� + 130\rħ�� + 80\r"
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
	"����(��)�ϳ�\r","��С���� + 17\r��󹥻� + 22\r���� + 180\r���� + 40\r"
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
	"����(��)�ϳ�\r","��С���� + 19\r��󹥻� + 21\r��ɱ + 7%\rħ�� + 50\r"
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
	"����(��)�ϳ�\r","��С���� + 19\r��󹥻� + 21\r��ɱ + 5%\r���� + 40\r"
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
	"����(��)�ϳ�\r","��С���� + 26\r��󹥻� + 26\rħ�� + 40\r"
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
	"����(��)�ϳ�\r","�����ٶ� + 1\r���� + 150\r��ɱ + 6%\rħ�� + 100\r"
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
	"������(��)�ϳ�\r","��С���� + 20\r��󹥻� + 25\r���� + 210\r���� + 50\r"
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
	"������(��)�ϳ�\r","��С���� + 22\r��󹥻� + 24\r��ɱ + 9%\rħ�� + 60\r"
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
	"������(��)�ϳ�\r","��С���� + 22\r��󹥻� + 24\r��ɱ + 7%\r���� + 45\r"
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
	"������(��)�ϳ�\r","��С���� + 29\r��󹥻� + 29\rħ�� + 35\r"
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
	"������(��)�ϳ�\r","�����ٶ� + 1\r���� + 170\r��ɱ + 8\rħ�� + 120\r"
#endif
},

// ����

{
	{sinDA1,sinDA2,0,0,0,0,0,0,0,0},
	{0,	0,	0,	4,	1,	3,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_MANA,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0},
	{10,50,1,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Transparo Fortitude Mix\r","Mana +10\rDefense Rating +50\rAbsorption Rating +1\r"
#else
	"����(��)�ϳ�\r","ħ�� + 10\r���� + 50\r���� + 1\r"
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
	"����(��)�ϳ�\r","���� + 8\r���� + 20\r���� + 0.6\r"
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
	"ˮ��(��)�ϳ�\r","ħ�� + 15\r���� + 75\r���� + 2\r"
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
	"ˮ��(��)�ϳ�\r","���� + 8\r���� + 30\r���� + 1\r"
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
	"����(��)�ϳ�\r","ħ�� + 20\r���� + 100\r���� + 3\r"
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
	"����(��)�ϳ�\r","���� + 25\r���� + 10\r"
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
	"����(��)�ϳ�\r","ħ�� + 30\r���� + 150\r���� + 3.5\r"
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
	"����(��)�ϳ�\r","���� +10\r���� + 50\r���� + 2\r"
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
	"�꾧(��)�ϳ�\r","ħ�� + 50\r���� +200\r���� + 4\r"
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
	"�꾧(��)�ϳ�\r","���� + 15\r���� + 75\r���� + 2.5\r"
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
	"����(��)�ϳ�\r","ħ�� + 70\r���� + 250\r���� + 4.5\r"
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
	"����(��)�ϳ�\r","���� + 25\r���� + 100\r���� + 3\r"
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
	"ʥ��(��)�ϳ�\r","ħ�� + 90\r���� + 300\r���� + 5\r"
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
	"ʥ��(��)�ϳ�\r","���� + 35\r���� + 125\r���� + 3.5\r"
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
	"��ħ(��)�ϳ�\r","ħ�� + 110\r���� + 350\r���� + 6\r"
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
	"��ħ(��)�ϳ�\r","���� + 45\r���� + 150\r���� + 4\r"
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
	"����(��)�ϳ�\r","ħ�� + 130\r���� + 400\r���� + 7\r"
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
	"����(��)�ϳ�\r","���� + 60\r���� + 200\r���� + 5\r"
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
	"����(��)�ϳ�\r","ħ�� + 150\r���� + 450\r���� + 8\r"
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
	"����(��)�ϳ�\r","���� + 75\r���� + 250\r���� + 6\r"
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
	"����(ȫ)�ϳ�\r","���� + 80\r���� + 15\r������ + 15\r������ + 15\r������ + 15\r������ + 15\rħ���� + 15\r"
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
	"������(��)�ϳ�\r","ħ�� + 170\r���� + 500\r���� + 9\r"
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
	"������(��)�ϳ�\r","���� + 90\r���� + 300\r���� + 7\r"
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
	"������(ȫ)�ϳ�\r","���� + 100\r���� + 17\r������ + 17\r������ + 17\r������ + 17\r������ + 17\rħ���� + 17\r"
#endif
},
// ��

{
	{sinDS1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	1,	1,	5,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,0,0,0,0},
	{4,20,0.6f,1,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Transparo Vitality Mix\r","Health +4\rDefense Rating +20\rAbsorption Rating +0.6\rBlock Rating +1\r"
#else
	"����(��)�ϳ�\r","���� + 4\r���� + 20\r���� + 0.6\r�� + 1%\r"
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
	"ˮ��(��)�ϳ�\r","���� + 6\r���� + 25\r���� + 0.8\r�� + 1%\r"
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
	"����(��)�ϳ�\r","���� + 8\r���� + 30\r���� + 1\r�� + 2%\r"
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
	"����(��)�ϳ�\r","���� + 10\r���� + 35\r���� + 1.2\r�� + 2%\r"
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
	"����(��)�ϳ�\r","���� + 15\r���� + 45\r���� + 1.6\r�� + 2%\r"
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
	"�꾧(��)�ϳ�\r","���� + 40\r���� + 80\r���� + 1\r"
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
	"�꾧(��)�ϳ�\r","���� + 25\r���� + 50\r���� + 1.8\r�� + 4%\r"
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
	"����(��)�ϳ�\r","���� + 40\rħ�� + 80\r"
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
	"����(��)�ϳ�\r","���� + 30\r���� + 75\r���� + 2.5\r�� + 4%\r"
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
	"ʥ��(��)�ϳ�\r","���� + 30\r���� + 100\r���� + 3.0\r�� + 5%\r"
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
	"ʥ��(��)�ϳ�\r","���� + 35\rħ�� + 10\r���� + 100\r���� + 2.8\r�� + 5%\r"
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
	"��ħ(��)�ϳ�\r","���� + 40\rħ�� + 10\r���� + 120\r���� + 2.4\r�� + 5%\r"
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
	"��ħ(��)�ϳ�\r","���� + 45\r���� + 150\r���� + 4.6\r�� + 5%\r"
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
	"����(��)�ϳ�\r","���� + 50\r���� + 175\r���� + 5.0\r�� + 6%\r"
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
	"����(��)�ϳ�\r","���� + 60\r���� + 200\r���� + 5.4\r�� + 7%\r"
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
	"����(��)�ϳ�\r","���� + 65\r���� + 225\r���� + 6\r�� + 7%\r"
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
	"����(��)�ϳ�\r","���� + 70\r���� + 250\r���� + 6.5\r�� + 8%\r"
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
	"����(��)�ϳ�\r","���� + 80\r�� + 12%\r"
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
	"������(��)�ϳ�\r","���� + 75\r���� + 275\r���� + 6.9\r�� + 8%\r"
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
	"������(��)�ϳ�\r","���� + 80\r���� + 300\r���� + 7.3\r�� + 9%\r"
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
	"������(��)�ϳ�\r","���� + 90\r�� + 14%\r"
#endif
},
// ����
{
	{sinOM1,0,0,0,0,0,0,0,0,0},
	{0,	0,	2,	0,	2,	6,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,0,0,0,0},
	{4,20,0.6f,1,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Transparo Vitality Mix\r","Health +4\rDefense Rating +20\rAbsorption Rating +0.6\rBlock Rating +1\r"
#else
	"����(��)�ϳ�\r","���� + 4\r���� + 20\r���� + 0.6\r�� + 1\r"
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
	"ˮ��(��)�ϳ�\r","���� + 6\r���� + 30\r���� + 1\r�� + 1\r"
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
	"����(��)�ϳ�\r","���� + 8\r���� + 40\r���� + 1.4\r�� + 1\r"
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
	"����(��)�ϳ�\r","���� + 15\r���� + 60\r���� + 2\r�� + 1\r"
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
	"�꾧(��)�ϳ�\r","���� + 25\r���� + 70\r���� + 2.2\r�� + 1\r"
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
	"����(��)�ϳ�\r","���� + 30\r���� + 95\r���� + 2.8\r�� + 1\r"
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
	"ʥ��(��)�ϳ�\r","���� + 35\r���� + 120\r���� + 3.6\r�� + 2\r"
#endif
},

{
	{sinOM1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	7,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,0,0,0,0},
	{45,170,6.0f,2,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Bellum Vitality Mix\r","Health +45\rDefense Rating +170\rAbsorption Rating +6\r��Block Rating +2\r"
#else
	"��ħ(��)�ϳ�\r","���� + 45\r���� + 170\r���� + 6\r�� + 2\r"
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
	"����(��)�ϳ�\r","���� + 60\r���� + 220\r���� + 7\r�� + 3\r"
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
	"����(��)�ϳ�\r","ħ�� + 200\r���� + 270\r���� + 8\r�� + 5\r"
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
	"����(��)�ϳ�\r","���� + 80\r���� + 270\r���� + 8\r�� + 4\r"
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
	"����(��)�ϳ�\r","���� + 130\r���� + 60\r�� + 10\r"
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
	"������(��)�ϳ�\r","ħ�� + 250\r���� + 320\r���� + 9\r�� + 6\r"
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
	"������(��)�ϳ�\r","���� + 100\r���� + 320\r���� + 9\r�� + 5\r"
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
	"������(��)�ϳ�\r","���� + 150\r���� + 80\r�� + 12\r"
#endif
},
//�ۻ�
{
	{sinOA2,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	2,	2,	6,	0,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_ATTACK_RATE,SIN_ADD_DEFENCE,SIN_ADD_MANA,SIN_ADD_STAMINA,0,0,0,0},
	{20,20,15,12,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Devine Dexterity Mix\r","Attack Rating +20\rDefense Rating +20\rMana +15\rStamina +12\r"
#else
	"����(��)�ϳ�\r","���� + 20\r���� + 20\rħ�� + 15\r���� + 12\r"
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
	"����(��)�ϳ�\r","���� + 3\r���� + 15\rħ�� + 10\r���� + 8\r"
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
	"����(��)�ϳ�\r","���� + 5\r���� + 20\rħ�� + 15\r���� + 10\r"
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
	"����(��)�ϳ�\r","���� + 30\r���� + 25\rħ�� + 20\r���� + 15\r"
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
	"�꾧(��)�ϳ�\r","���� + 10\r���� + 30\rħ�� + 20\r���� + 20\r"
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
	"�꾧(��)�ϳ�\r","���� + 50\r���� + 40\rħ�� + 25\r���� + 25\r"
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
	"����(��)�ϳ�\r","���� + 70\r���� + 55\rħ�� + 30\r���� + 35\r"
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
	"����(��)�ϳ�\r","���� + 15\r���� + 40\rħ�� + 25\r���� + 30\r"
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
	"ʥ��(��)�ϳ�\r","���� + 90\r���� + 70\rħ�� + 35\r���� + 45\r"
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
	"ʥ��(��)�ϳ�\r","���� + 20\r���� + 50\rħ�� + 30\r���� + 40\r"
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
	"��ħ(��)�ϳ�\r","���� + 110\r���� + 95\rħ�� + 40\r���� + 55\r"
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
	"��ħ(��)�ϳ�\r","���� + 25\r���� + 60\rħ�� + 35\r���� + 50\r"
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
	"����(��)�ϳ�\r","���� + 130\r���� + 110\rħ�� + 45\r���� + 65\r"
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
	"����(��)�ϳ�\r","���� + 30\r���� + 70\rħ�� + 40\r���� + 60\r"
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
	"����(��)�ϳ�\r","���� + 150\r���� + 130\rħ�� + 55\r���� + 75\r"
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
	"����(��)�ϳ�\r","���� + 40\r���� + 80\rħ�� + 50\r���� + 70\r"
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
	"������(��)�ϳ�\r","���� + 170\r���� + 150\rħ�� + 65\r���� + 85\r"
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
	"������(��)�ϳ�\r","���� + 50\r���� + 90\rħ�� + 60\r���� + 80\r"
#endif
},
//����
{
	{sinDG1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	4,	2,	5,	0,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_STAMINA,SIN_ADD_ABSORB,SIN_ADD_DEFENCE,0,0,0,0},
	{8,30,0.8f,10,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Devine Vitality Mix\r","Health +8\rStamina +30\rAbsorption Rating +0.8\rDefense Rating +10\r"
#else
	"����(��)�ϳ�\r","���� + 8\r���� + 30\r���� + 0.8\r���� + 10\r"
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
	"����(��)�ϳ�\r","ħ�� + 25\r���� + 30\r���� + 0.8\r���� + 40\r"
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
	"����(��)�ϳ�\r","ħ�� + 30\r���� + 40\r���� + 1\r���� + 50\r"
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
	"����(��)�ϳ�\r","���� + 10\r���� + 40\r���� + 1\r���� + 20\r"
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
	"�꾧(��)�ϳ�\r","ħ�� + 40\r���� + 60\r���� + 2\r���� + 75\r"
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
	"�꾧(��)�ϳ�\r","���� + 15\r���� + 60\r���� + 2\r���� + 40\r"
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
	"����(��)�ϳ�\r","ħ�� + 50\r���� + 80\r���� + 3\r���� + 100\r"
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
	"����(��)�ϳ�\r","���� + 20\r���� + 80\r���� + 3\r���� + 60\r"
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
	"ʥ��(��)�ϳ�\r","ħ�� + 60\r���� + 100\r���� + 4\r���� + 125\r"
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
	"ʥ��(��)�ϳ�\r","���� + 25\r���� + 100\r���� + 4\r���� + 80\r"
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
	"��ħ(��)�ϳ�\r","ħ�� + 70\r���� + 120\r���� + 5\r���� + 150\r"
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
	"��ħ(��)�ϳ�\r","���� + 30\r���� + 120\r���� + 5\r���� + 100\r"
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
	"����(��)�ϳ�\r","ħ�� + 80\r���� + 140\r���� + 6\r���� + 175\r"
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
	"����(��)�ϳ�\r","���� + 35\r���� + 140\r���� + 6\r���� + 120\r"
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
	"����(��)�ϳ�\r","ħ�� + 90\r���� + 160\r���� + 7\r���� + 200\r"
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
	"����(��)�ϳ�\r","���� + 40\r���� + 160\r���� + 7\r���� + 140\r"
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
	"������(��)�ϳ�\r","ħ�� + 100\r���� + 180\r���� + 8.0\r���� + 225\r"
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
	"������(��)�ϳ�\r","���� + 45\r���� + 180\r���� + 8.0\r���� + 160\r"
#endif
},
//Ь��
{
	{sinDB1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	2,	2,	4,	0,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_LIFE,SIN_ADD_ABSORB,SIN_ADD_MOVE_SPEED,0,0,0,0,0},
	{8,1.2f,0.6f,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Devine Velocity Mix\r","Health +8\rAbsorption Rating +1.2\rMovement Speed +0.6\r"
#else
	"����(��)�ϳ�\r","���� + 8\r���� + 1.2\r�ƶ��ٶ� + 0.6\r"
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
	"����(��)�ϳ�\r","���� + 15\rħ�� + 8\r�ƶ��ٶ� + 0.4\r"
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
	"����(��)�ϳ�\r","���� + 20\rħ�� + 10\r�ƶ��ٶ� + 0.6\r"
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
	"����(��)�ϳ�\r","���� + 10\r���� + 1.8\r�ƶ��ٶ� + 1\r"
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
	"�꾧(��)�ϳ�\r","���� + 25\rħ�� + 20\r�ƶ��ٶ� + 1\r"
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
	"�꾧(��)�ϳ�\r","���� + 10\r���� + 2.4\r�ƶ��ٶ� + 1.6\r"
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
	"����(��)�ϳ�\r","���� + 30\rħ�� + 30\r�ƶ��ٶ� + 1.4\r"
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
	"����(��)�ϳ�\r","���� + 15\r���� + 3\r�ƶ��ٶ� + 2.2\r"
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
	"ʥ��(��)�ϳ�\r","���� + 35\rħ�� + 40\r�ƶ��ٶ� + 1.8\r"
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
	"ʥ��(��)�ϳ�\r","���� + 20\r���� + 3.6\r�ƶ��ٶ� + 3\r"
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
	"��ħ(��)�ϳ�\r","���� + 40\rħ�� + 50\r�ƶ��ٶ� + 2.2\r"
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
	"��ħ(��)�ϳ�\r","���� + 25\r���� + 4.2\r�ƶ��ٶ� + 3.8\r"
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
	"����(��)�ϳ�\r","���� + 45\rħ�� + 60\r�ƶ��ٶ� + 2.6\r"
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
	"����(��)�ϳ�\r","���� + 30\r���� + 4.8\r�ƶ��ٶ� + 4.6\r"
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
	"����(��)�ϳ�\r","���� + 60\rħ�� + 70\r�ƶ��ٶ� + 3\r"
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
	"����(��)�ϳ�\r","���� + 35\r���� + 5.5\r�ƶ��ٶ� + 5.4\r"
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
	"������(��)�ϳ�\r","���� + 70\rħ�� + 80\r�ƶ��ٶ� + 3.4\r"
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
	"������(��)�ϳ�\r","���� + 40\r���� + 6.2\r�ƶ��ٶ� + 6\r"
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
	"������(��)�ϳ�\r","���� + 1000\r�ƶ��ٶ� + 9\r"
#endif
},
//����
{
	{sinOA1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	1,	4,	2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_MANA,SIN_ADD_MANAREGEN,0,0,0,0,0,0},
	{3,0.1f,0,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Transpero Efficiency Mix\r","Mana +3\rMana Regen +0.1\r"
#else
	"����(ħ)�ϳ�\r","ħ�� + 3\rħ���ظ� + 0.1\r"
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
	"ˮ��(ħ)�ϳ�\r","ħ�� + 3\rħ���ظ� + 0.2\r"
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
	"����(ħ)�ϳ�\r","ħ�� + 5\r�����ظ� + 0.2\rħ���ظ� + 0.2\r"
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
	"����(ħ)�ϳ�#1\r","ħ�� + 6\r�����ظ� + 0.4\rħ���ظ� + 0.3\r"
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
	"����(ħ)�ϳ�#2\r","ħ�� + 8\r�����ظ� + 0.8\rħ���ظ� + 0.6\r"
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
	"�꾧(ħ)�ϳ�#1\r","ħ�� + 10\r�����ظ� + 1.2\rħ���ظ� + 0.9\r"
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
	"�꾧(ħ)�ϳ�#2\r","ħ�� + 12\r�����ظ� + 1.6\rħ���ظ� + 1.2\r"
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
	"����(ħ)�ϳ�#1\r","ħ�� + 14\r�����ظ� + 2\rħ���ظ� + 1.5\r"
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
	"����(ħ)�ϳ�#2\r","ħ�� + 16\r�����ظ� + 2.4\rħ���ظ� + 1.8\r"
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
	"ʥ��(ħ)�ϳ�#1\r","ħ�� + 18\r�����ظ� + 2.8\rħ���ظ� + 2.1\r"
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
	"ʥ��(ħ)�ϳ�#2\r","ħ�� + 20\r�����ظ� + 3.2\rħ���ظ� + 2.4\r"
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
	"��ħ(ħ)�ϳ�#1\r","ħ�� + 22\r�����ظ� + 3.6\rħ���ظ� + 2.7\r"
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
	"��ħ(ħ)�ϳ�#2\r","ħ�� + 24\r�����ظ� + 4\rħ���ظ� + 3\r"
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
	"����(ħ)�ϳ�#1\r","ħ�� + 26\r�����ظ� + 4.4\rħ���ظ� + 3.3\r"
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
	"����(ħ)�ϳ�#2\r","ħ�� + 28\r�����ظ� + 4.6\rħ���ظ� + 3.6\r"
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
	"����(ħ)�ϳ�#1\r","ħ�� + 30\r�����ظ� + 5.2\rħ���ظ� + 3.9\r"
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
	"����(ħ)�ϳ�#2\r","ħ�� + 32\r�����ظ� + 5.4\rħ���ظ� + 4.2\r"
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
	"������(ħ)�ϳ�#1\r","ħ�� + 34\r�����ظ� + 6\rħ���ظ� + 4.5\r"
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
	"������(ħ)�ϳ�#2\r","ħ�� + 32\r�����ظ� + 5.4\rħ���ظ� + 4.2\r"
#endif
},
//��ָ
{
	{sinOR1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	2,	2,	5,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_STAMINA,SIN_ADD_STAMINAREGEN,0,0,0,0,0,0},
	{3,0.6f,0,0,0,0,0,0},
	{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Transpero Efficiency Mix\r","Stamina +3\rStamina Regen +0.6\r"
#else
	"����(ħ)�ϳ�\r","���� + 3\r�����ظ� + 0.6\r"
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
	"ˮ��(ħ)�ϳ�\r","���� + 4\r�����ظ� + 0.8\r"
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
	"����(ħ)�ϳ�\r","���� + 5\r�����ظ� + 1\r"
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
	"����(ħ)�ϳ�#1\r","���� + 6\r�����ظ� + 1.2\r"
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
	"����(ħ)�ϳ�#2\r","���� + 8\r�����ظ� + 1.6\r"
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
	"�꾧(ħ)�ϳ�#1\r","���� + 2\rħ�� + 6\r���� + 10\r�����ظ� + 1\r"
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
	"�꾧(ħ)�ϳ�#2\r","���� + 4\rħ�� + 8\r���� + 12\r�����ظ� + 1.4\r"
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
	"����(ħ)�ϳ�#1\r","���� + 6\rħ�� + 10\r���� + 14\r�����ظ� + 1.8\r"
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
	"����(ħ)�ϳ�#2\r","���� + 8\rħ�� + 12\r���� + 16\r�����ظ� + 2.2\r"
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
	"ʥ��(ħ)�ϳ�#1\r","���� + 10\rħ�� + 14\r���� + 18\r�����ظ� + 2.6\r"
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
	"ʥ��(ħ)�ϳ�#2\r","���� + 12\rħ�� + 16\r���� + 20\r�����ظ� + 3\r"
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
	"��ħ(ħ)�ϳ�#1\r","���� + 14\rħ�� + 18\r���� + 22\r�����ظ� + 3.4\r"
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
	"��ħ(ħ)�ϳ�#2\r","���� + 16\rħ�� + 20\r���� + 24\r�����ظ� + 3.8\r"
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
	"����(ħ)�ϳ�#1\r","���� + 18\rħ�� + 22\r���� + 26\r�����ظ� + 4.2\r"
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
	"����(ħ)�ϳ�#2\r","���� + 20\rħ�� + 24\r���� + 28\r�����ظ� + 4.6\r"
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
	"����(ħ)�ϳ�#1\r","���� + 22\rħ�� + 26\r���� + 30\r�����ظ� + 5\r"
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
	"����(ħ)�ϳ�#2\r","���� + 24\rħ�� + 28\r���� + 32\r�����ظ� + 5.4\r"
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
	"������(ħ)�ϳ�#1\r","���� + 26\rħ�� + 30\r���� + 34\r�����ظ� + 5.8\r"
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
	"������(ħ)�ϳ�#2\r","���� + 28\rħ�� + 32\r���� + 36\r�����ظ� + 6.2\r"
#endif
},
// ʯͷ
{
	{sinOS1,0,0,0,0,0,0,0,0,0},
	{0,	0,	0,	0,	0,	2,	1,	0,	6,	0,	0,	0,	0,	0,	0,	0},
	{SIN_ADD_DEFENCE,0,0,0,0,0,0,0},
	{25,0,0,0,0,0,0,0},
	{SIN_ADD_NUM,0,0,0,0,0,0,0},
#ifdef ENGLISH_LANGUAGE
	"Celesto Aegis Mix\r","Defense Rating +25\r"
#else
	"����(��)�ϳ�\r","���� + 25\r"
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
	"����(��)�ϳ�\r","��󹥻� + 1\r"
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
	"�꾧(��)�ϳ�\r","���� + 60\r"
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
	"�꾧(��)�ϳ�\r","��С���� + 1\r��󹥻� + 1\r"
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
	"����(��)�ϳ�\r","���� + 95\r"
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
	"����(��)�ϳ�\r","��С���� + 1\r��󹥻� + 2\r"
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
	"ʥ��(��)�ϳ�\r","���� + 130\r"
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
	"ʥ��(��)�ϳ�\r","��С���� + 2\r��󹥻� + 2\r"
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
	"��ħ(��)�ϳ�\r","���� + 165\r"
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
	"��ħ(��)�ϳ�\r","��С���� + 2\r��󹥻� + 3\r"
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
	"����(��)�ϳ�\r","���� + 200\r"
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
	"����(��)�ϳ�\r","��С���� + 3\r��󹥻� + 3\r"
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
	"����(��)�ϳ�\r","���� + 250\r"
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
	"����(��)�ϳ�\r","��С���� + 3\r��󹥻� + 4\r"
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
	"������(��)�ϳ�\r","���� + 300\r"
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
	"������(��)�ϳ�\r","��С���� + 4\r��󹥻� + 4\r"
#endif
},