

#define ADD_TEMPFACE	2048
#define ADD_TEMPVERTEX	2048


//걸어 다닐수 있는 최대 고저차
extern int Stage_StepHeight;
extern int smStage_WaterChk;

class smSTAGE3D 
{
public:
	DWORD	Head;

	DWORD *StageArea[MAP_SIZE][MAP_SIZE];	//구역별 페이스 값 버퍼 리스트
	POINT *AreaList;						//구역별 페이스 리스트 임시저장 
	int AreaListCnt;						//구역 페이스의 커운터

	int	MemMode;							//메모리 설정 모드 ( 예정 )

	DWORD SumCount;							// 렌더링 첵크 카운터 
	int CalcSumCount;						// 연산 번호 카운터

	smSTAGE_VERTEX		*Vertex;			//버텍스 리스트
	smSTAGE_FACE		*Face;				//페이스 리스트
	smTEXLINK			*TexLink;			//텍스쳐 좌표 리스트
	smLIGHT3D			*smLight;			//조명 설정

	smMATERIAL_GROUP	*smMaterialGroup;	//메트리얼 그룹

	smSTAGE_OBJECT		*StageObject;		//맵의 구역상의 오브젝트들
	smMATERIAL			*smMaterial;		//메트리얼 리스트 포인터

	int nVertex;							//버텍스 수
	int nFace;								//페이스 수
	int nTexLink;							//텍스쳐좌표 연결 수
	int	nLight;								//조명 수

	int	nVertColor;								//버텍스 색 입력 카운터

	int	Contrast;								//채도 ( 선명도 )
	int Bright;									//명도 ( 밝기 정도 )

	POINT3D VectLight;							//쉐이드용 라이트 벡터

	DWORD	*lpwAreaBuff;						//구역별 저장 버퍼
	int		wAreaSize;							//구역별 저장 버퍼 크기
	RECT	StageMapRect;

	smSTAGE3D();
	~smSTAGE3D();
	smSTAGE3D( int nv , int nf );


	void Init(void);

	int Init( int nv , int nf );
	int Close();
	int AddVertex ( int x, int y, int z );
	int AddFace ( int a, int b, int c , int matrial=0 );
	int SetFaceMaterial( int FaceNum , int MatNum  );
	int SetVertexColor ( DWORD NumVertex , BYTE r , BYTE g, BYTE b , BYTE a=255 );
	int AddTexLink( int FaceNum , DWORD *hTex ,smFTPOINT *t1 , smFTPOINT *t2 , smFTPOINT *t3 );
	int SetVertexShade( int isSetLight = TRUE );
	int AddVertexLightRound( POINT3D *LightPos , int r, int g, int b, int Range );
	int	InitDynLight( int nl );
	int AddDynLight( int type , POINT3D *LightPos , int r, int g, int b, int Range );
	int CheckFaceIceFoot( POINT3D *Pos, POINT3D *Angle, int CheckHeight );
	int MakeAreaFaceList( int x,int z, int width, int height , int top , int bottom );
	int GetPolyHeight( smSTAGE_FACE *face , int x, int z );
	int GetAreaHeight( int ax, int az , int x, int z );
	int GetAreaHeight2( int ax, int az , int x, int z );
	int GetHeight( int x, int z  );
	int GetHeight2( int x, int z );
	int CheckSolid( int sx, int sy, int sz , int dx, int dy, int dz );
	int GetThroughPlane( smSTAGE_FACE *face , POINT3D *sp , POINT3D *ep );
	int GetPlaneProduct( smSTAGE_FACE *face , POINT3D *p );
	int GetTriangleImact( smSTAGE_FACE *face, smLINE3D *pLines , int LineCnt );
	int CheckNextMove( POINT3D *Posi, POINT3D *Angle , POINT3D *MovePosi, int dist , int ObjWidth , int ObjHeight , int CheckOverLap=0 );
	int CheckVecImpact( POINT3D *Posi, POINT3D *Angle , int dist );
	int CheckVecImpact2( int sx,int sy,int sz, int ex,int ey,int ez );
	int GetFloorHeight( int x, int y, int z , int ObjHeight );
	int GetFloorHeight2( int x, int y, int z , int ObjHeight );
	int GetEmptyHeight( int x, int y, int z , int ObjHeight );
	int CheckFloorFaceHeight( int x, int y, int z , int hSize );
	void clearStageArea();
	int getPolyAreas( POINT3D *ip1 , POINT3D *ip2, POINT3D *ip3 );
	int SetupPolyAreas();
	int RenderGeom();
	int DrawStage(int x , int y, int z, int angX, int angY, int angZ , smEMATRIX *eRotMatrix=0 );
	int DrawStage2(int x , int y, int z, int angX, int angY, int angZ , smEMATRIX *eRotMatrix=0 );
	int DrawOpeningStage(int x, int y, int z, int angX, int angY, int angZ, int FrameStep );
	int	SaveFile( char *szFile );
	int	LoadFile( char *szFile );
};




