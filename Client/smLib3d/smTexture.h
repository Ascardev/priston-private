#define SWAPTEXTURE_MAX		64

#define		MIPMAP_FILELIST				5
#define		SQUARE_MODE					1
#define		NOSQUARE_MODE				2

class smTEXTURE
{
public:
	DWORD			TexSpeedSum[MAX_TEXTURE];

	smTEXTUREHANDLE Texture[MAX_TEXTURE];

	CRITICAL_SECTION	cTextureSection;

	int LastTextureCnt;
	int TextureCnt;

	smTEXTURE();
	~smTEXTURE();

	void Init();
	int	 Remove();

	int Find(DWORD dwCode, char *Name);

	smTEXTUREHANDLE *Add(char *name, char *nameA = 0);

	int Delete(smTEXTUREHANDLE *lpTex);

	int ReadTexture();

	int Restore();

};

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
	// 메트리얼 말기화
	int Close();

	//저장할 데이타의 크기를 미리 알려줌
	int GetSaveSize();
	//데이타를 파일로 저장 
	int SaveFile(HANDLE hFile);
	//파일에서 데이타를 읽어옴
	int LoadFile(HANDLE hFile);

	//사용되지 않는 메트리얼 제거
	int DeleteUnuseMaterial();
	//메트리얼을 등록
	int AddMaterial(ASE_MATERIAL *aseMaterial, char *szScript = 0);
	//텍스쳐 메트리얼 생성
	int CreateTextureMaterial(char *szBitmap, char *szOpacity, int TwoSide, int Shade, DWORD BlendType);
	//메트리얼에 텍스쳐를 추가한다
	int	AddTexture(int MatNum, char *szBitmap, char *szOpacity = 0);

	int IncTextureFrame();
	//애니메이션 메트리얼 생성
	int CreateAnimationMaterial(char **szBitmap, int NumTex, DWORD BlendType, int AutoAnimMode);
	//메트리얼을 에니메이션 가능하게 변경
	int ChangeMaterialToAnimation(smMATERIAL *lpMaterial, char **szBitmap, int NumTex, DWORD BlendType, int AutoAnimMode);
	//메트리얼의 에니메이션 프레임을 설정
	int SetMaterialAnimFrame(smMATERIAL *lpMaterial, int frame);
	//텍스쳐 이름으로 메트리얼을 찾는다
	smMATERIAL *FindMaterialFromTextureName(char *szName);
	//텍스쳐 이름으로 다음 메트리얼을 찾는다
	smMATERIAL *FindNextMaterialFromTextureName();

	int ReadTextures(int MipMap = 0);
};

#define MATRIAL_MAX			10000

extern smMATERIAL *smMaterial;
extern smMATERIAL_GROUP	*smMaterialGroup;

extern smTEXTURE smTexture;
extern DWORD	VramTotal;

extern int LoadingCount;
extern int LoadingCnt;

int InitMaterial();

int CloseMaterial();

int AddMaterial(ASE_MATERIAL *aseMaterial);

int DeleteUnuseMaterial();
//텍스쳐 메트리얼 생성
int CreateTextureMaterial(char *szBitmap, char *szOpacity, int TwoSide, int Shade, DWORD BlendType);
//메트리얼에 텍스쳐를 추가한다
int	AddTexture(int MatNum, char *szBitmap, char *szOpacity = 0);
//애니메이션 메트리얼 생성
int CreateAnimationMaterial(char **szBitmap, int NumTex, DWORD BlendType, int AutoAnimMode = TRUE);
//메트리얼을 에니메이션 가능하게 변경
int ChangeMaterialToAnimation(smMATERIAL *lpMaterial, char **szBitmap, int NumTex, DWORD BlendType, int AutoAnimMode = TRUE);
//메트리얼의 에니메이션 프레임을 설정
int SetMaterialAnimFrame(smMATERIAL *lpMaterial, int frame);

extern int MaterialFrame;

int IncTextureFrame();


smMATERIAL *FindMaterialFromTextureName(char *szName);
smMATERIAL *FindNextMaterialFromTextureName();


int InitTexture();

int CloseTexture();

int ReadTextures();

int RestoreTextures();

void smLeaveTextureCriticalSection();

void smEnterTextureCriticalSection();


smTEXTUREHANDLE *LoadDibSurfaceOffscreen(char *Filename);



