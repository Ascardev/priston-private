#define SWAPTEXTURE_MAX		64

#define		MIPMAP_FILELIST				5
#define		SQUARE_MODE					1
#define		NOSQUARE_MODE				2


class smMATERIAL_GROUP
{
	DWORD	Head;
public:
	smMATERIAL *smMaterial;
	DWORD MaterialCount;

	int ReformTexture;

	int MaxMaterial;

	int LastSearchMaterial;
	char szLastSearchName[64];

	smMATERIAL_GROUP();
	smMATERIAL_GROUP(int MaterialMax);
	~smMATERIAL_GROUP();

	void Init(int MaterialMax);
	// ��Ʈ���� ����ȭ
	int Close();

	//������ ����Ÿ�� ũ�⸦ �̸� �˷���
	int GetSaveSize();
	//����Ÿ�� ���Ϸ� ���� 
	int SaveFile(HANDLE hFile);
	//���Ͽ��� ����Ÿ�� �о��
	int LoadFile(HANDLE hFile);

	//������ �ʴ� ��Ʈ���� ����
	int DeleteUnuseMaterial();
	//��Ʈ������ ���
	int AddMaterial(ASE_MATERIAL *aseMaterial, char *szScript = 0);
	//�ؽ��� ��Ʈ���� ����
	int CreateTextureMaterial(char *szBitmap, char *szOpacity, int TwoSide, int Shade, DWORD BlendType);
	//��Ʈ���� �ؽ��ĸ� �߰��Ѵ�
	int	AddTexture(int MatNum, char *szBitmap, char *szOpacity = 0);

	int IncTextureFrame();
	//�ִϸ��̼� ��Ʈ���� ����
	int CreateAnimationMaterial(char **szBitmap, int NumTex, DWORD BlendType, int AutoAnimMode);
	//��Ʈ������ ���ϸ��̼� �����ϰ� ����
	int ChangeMaterialToAnimation(smMATERIAL *lpMaterial, char **szBitmap, int NumTex, DWORD BlendType, int AutoAnimMode);
	//��Ʈ������ ���ϸ��̼� �������� ����
	int SetMaterialAnimFrame(smMATERIAL *lpMaterial, int frame);
	//�ؽ��� �̸����� ��Ʈ������ ã�´�
	smMATERIAL *FindMaterialFromTextureName(char *szName);
	//�ؽ��� �̸����� ���� ��Ʈ������ ã�´�
	smMATERIAL *FindNextMaterialFromTextureName();

	int ReadTextures(int MipMap = 0);
};

#define MATRIAL_MAX			10000

extern smMATERIAL *smMaterial;
extern smMATERIAL_GROUP	*smMaterialGroup;

extern DWORD	VramTotal;

extern int LoadingCount;
extern int LoadingCnt;

int InitMaterial();

int CloseMaterial();

int AddMaterial(ASE_MATERIAL *aseMaterial);

int DeleteUnuseMaterial();
//�ؽ��� ��Ʈ���� ����
int CreateTextureMaterial(char *szBitmap, char *szOpacity, int TwoSide, int Shade, DWORD BlendType);
//��Ʈ���� �ؽ��ĸ� �߰��Ѵ�
int	AddTexture(int MatNum, char *szBitmap, char *szOpacity = 0);
//�ִϸ��̼� ��Ʈ���� ����
int CreateAnimationMaterial(char **szBitmap, int NumTex, DWORD BlendType, int AutoAnimMode = TRUE);
//��Ʈ������ ���ϸ��̼� �����ϰ� ����
int ChangeMaterialToAnimation(smMATERIAL *lpMaterial, char **szBitmap, int NumTex, DWORD BlendType, int AutoAnimMode = TRUE);
//��Ʈ������ ���ϸ��̼� �������� ����
int SetMaterialAnimFrame(smMATERIAL *lpMaterial, int frame);

extern int MaterialFrame;

smMATERIAL *FindMaterialFromTextureName(char *szName);
smMATERIAL *FindNextMaterialFromTextureName();



