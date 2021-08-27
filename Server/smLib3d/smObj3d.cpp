#include "StdAfx.h"


#define		CLIP_OUT		-32767
#define		ANGCLIP			ANGLE_MASK


int	DEBUG_OBJSUM = 0;

extern  smCONFIG smConfig;

extern int smMergeLight(smRGB *light, int r, int g, int b);

smPOINT3D	smTestVertex;
smVERTEX	smWorldVertex[100];

DWORD		smObjFixPos = 0;			//렌더링 좌표 고정


int TestScreenView(int x, int y, int z, int Bound, POINT3D *LocalAngle, POINT3D *GlobalAngle)
{
	return FALSE;
}

smPOINT3D::smPOINT3D()
{

}

smPOINT3D::smPOINT3D(smVERTEX *pv)
{
	SetTo(pv);
}

smPOINT3D::~smPOINT3D()
{

}

void smPOINT3D::SetTo(smVERTEX *pv)
{
	pVertex = pv;

	rx = pv->x;
	ry = pv->y;
	rz = pv->z;

	sx = pv->nx;
	sy = pv->ny;
	sz = pv->nz;
}
void smPOINT3D::xform2d()
{

	if (Z > 0)
	{
		x2d = MidX + ((X * viewdistZ) / Z);
		y2d = MidY - ((Y * viewdistZ) / Z);
	}
	else
	{
		x2d = CLIP_OUT;
		y2d = CLIP_OUT;
	}
}
void smPOINT3D::GlobalRotate(int *trig)
{
	int i, j, k;

	i = (wz * trig[2] + wx * trig[3]) >> FLOATNS;
	j = wy;
	k = (wz * trig[3] - wx * trig[2]) >> FLOATNS;

	Y = (j * trig[1] - k * trig[0]) >> FLOATNS;
	Z = (j * trig[0] + k * trig[1]) >> FLOATNS;
	j = Y;

	X = (i * trig[5] - j * trig[4]) >> FLOATNS;
	Y = (i * trig[4] + j * trig[5]) >> FLOATNS;

	xform2d();
}

//   지역 중심 좌표 이동
void smPOINT3D::Move(int dx, int dy, int dz)
{
	ox = dx << FLOATNS;
	oy = dy << FLOATNS;
	oz = dz << FLOATNS;

	GlobalXform();
}

//   카메라 좌표
void smPOINT3D::GlobalXform()
{
	wx = rx + ox;
	wy = ry + oy;
	wz = rz + oz;
}





/////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////[ OBJ3D 클래스 ]///////////////////////////////////////// 
/////////////////////////////////////////////////////////////////////////////////////////


smOBJ3D::smOBJ3D()
{
	NodeName[0] = 0;
	NodeParent[0] = 0;
	smIdentityMatrix(Tm);

	pParent = 0;

	TmRot = 0;
	TmPos = 0;
	TmScale = 0;
	TmRotCnt = 0;
	TmPosCnt = 0;
	TmScaleCnt = 0;
	TmPrevRot = 0;

	Face = 0;
	Vertex = 0;
	TexLink = 0;

	Physique = 0;

}

smOBJ3D::~smOBJ3D()
{
	DELETA(TmScale);
	DELETA(TmPos);
	DELETA(TmRot);
	DELETA(TmPrevRot);
	DELETA(TexLink);
	DELETA(Face);
	DELETA(Vertex);
	DELET(Physique);
}

smOBJ3D::smOBJ3D(int nv, int nf)
{
	NodeName[0] = 0;
	NodeParent[0] = 0;
	smIdentityMatrix(Tm);

	pParent = 0;

	TmRot = 0;
	TmPos = 0;
	TmScale = 0;
	TmPrevRot = 0;
	TmRotCnt = 0;
	TmPosCnt = 0;
	TmScaleCnt = 0;

	Face = 0;
	Vertex = 0;
	TexLink = 0;

	Physique = 0;

	Init(nv, nf, 0);

}

//=========================== [ 초기화 및 설정 ] =============================//

// 초기화루틴 ( 버텍스 , 페이스의 수 , 그리고 피지크 사용여부  )
void smOBJ3D::Init(int nv, int nf, int pFlag)
{
	int cnt;

	MaxVertex = nv;
	MaxFace = nf;

	nVertex = 0;
	nFace = 0;

	dBound = 0;							// 바운딩 스페어 값 ^2
	Bound = 0;							// 바운딩 스페어 값 

	maxX = maxY = maxZ = 0;
	minX = minY = minZ = 0;

	ColorEffect = TRUE;							// 색상 효과 사용 기본값 
	//클리핑 모드값
	ClipStates = (SMCLIP_NEARZ | SMCLIP_FARZ | SMCLIP_LEFT | SMCLIP_RIGHT | SMCLIP_TOP | SMCLIP_BOTTOM);

	Vertex = new smVERTEX[nv];
	Face = new smFACE[nf];

	TexLink = new smTEXLINK[nf * 2];
	nTexLink = 0;

	// 피지크 애니메이션 사용시
	if (pFlag) {
		Physique = new smOBJ3D *[nv];
		for (cnt = 0; cnt < nv; cnt++) Physique[cnt] = 0;
	}

	Posi.x = 0;
	Posi.y = 0;
	Posi.z = 0;

	Angle.x = 0;
	Angle.y = 0;
	Angle.z = 0;

	ZeroVertex.x = 0;
	ZeroVertex.y = 0;
	ZeroVertex.z = 0;

	TmFrameCnt = 0;

	smIdentityMatrix(mLocal);



}

// 버텍스 좌표 추가
int smOBJ3D::AddVertex(int x, int y, int z)
{
	int bound;
	int mx, my, mz;

	Vertex[nVertex].x = x;
	Vertex[nVertex].y = y;
	Vertex[nVertex].z = z;
	nVertex++;


	// 좌표 최대치 저장
	mx = abs(x);
	my = abs(y);
	mz = abs(z);

	if (maxX < mx) maxX = mx;
	if (maxZ < my) maxZ = my;
	if (maxY < mz) maxY = mz;

	//바운딩 스페어 만들기
	mx = x >> FLOATNS;
	my = y >> FLOATNS;
	mz = z >> FLOATNS;

	bound = abs((mx*mx) + (my*my) + (mz*mz));

	if (dBound < bound) dBound = bound;

	if (nVertex == MaxVertex)
		Bound = (int)sqrt(float(dBound));

	return nVertex - 1;
}

// 페이스에 버텍스 번호 추가
int smOBJ3D::AddFace(int a, int b, int c)
{

	Face[nFace].v[0] = a;
	Face[nFace].v[1] = b;
	Face[nFace].v[2] = c;
	Face[nFace].v[3] = 0;			// Texture

	Face[nFace].lpTexLink = 0;

	nFace++;

	return nFace - 1;
}


//페이스에 메트리얼 입력
int smOBJ3D::SetFaceMaterial(int FaceNum, int MatNum)
{
	Face[FaceNum].v[3] = MatNum;

	return TRUE;
}

//텍스쳐 좌표연결을 추가한다 
int smOBJ3D::AddTexLink(int FaceNum, DWORD *hTex,
	smFTPOINT *t1, smFTPOINT *t2, smFTPOINT *t3)
{
	int cnt;
	smTEXLINK	*tl;

	//좌표설정
	TexLink[nTexLink].u[0] = t1->u;
	TexLink[nTexLink].v[0] = t1->v;
	TexLink[nTexLink].u[1] = t2->u;
	TexLink[nTexLink].v[1] = t2->v;
	TexLink[nTexLink].u[2] = t3->u;
	TexLink[nTexLink].v[2] = t3->v;
	TexLink[nTexLink].hTexture = hTex;
	TexLink[nTexLink].NextTex = 0;

	//지정된 페이스와 연결시킨다
	if (!Face[FaceNum].lpTexLink) {
		//최초의 텍스쳐좌표일 경우
		Face[FaceNum].lpTexLink = &TexLink[nTexLink];
	}
	else {
		//이미 연결되있는 좌표가 있는경우
		tl = Face[FaceNum].lpTexLink;

		for (cnt = 0; cnt < 8; cnt++) {
			if (!tl->NextTex) {
				//마지막으로 연결된 좌표를 찾아 연결
				tl->NextTex = &TexLink[nTexLink];
				break;
			}
			else {
				//다음 좌표로 넘김
				tl = tl->NextTex;
			}

		}
	}

	nTexLink++;

	return nTexLink - 1;
}

//텍스쳐 좌표연결을 추가한다 
int smOBJ3D::AddTexLinkTP(int FaceNum, DWORD *hTex,
	smTPOINT *t1, smTPOINT *t2, smTPOINT *t3)
{
	smFTPOINT f1, f2, f3;

	f1.u = ((float)t1->u) / 256;
	f1.v = ((float)t1->v) / 256;
	f2.u = ((float)t2->u) / 256;
	f2.v = ((float)t2->v) / 256;
	f3.u = ((float)t3->u) / 256;
	f3.v = ((float)t3->v) / 256;

	return AddTexLink(FaceNum, hTex, &f1, &f2, &f3);
}


// 페이스 와 텍스쳐 동시에 추가
int smOBJ3D::AddFace(int a, int b, int c, smTPOINT *t1, smTPOINT *t2, smTPOINT *t3)
{
	int num;
	smFTPOINT f1, f2, f3;

	f1.u = ((float)t1->u) / 256;
	f1.v = ((float)t1->v) / 256;
	f2.u = ((float)t2->u) / 256;
	f2.v = ((float)t2->v) / 256;
	f3.u = ((float)t3->u) / 256;
	f3.v = ((float)t3->v) / 256;

	num = AddFace(a, b, c);
	AddTexLink(num, 0, &f1, &f2, &f3);

	return num;
}

//텍스쳐 좌표를 형태에 맟춰서 변경한다
int smOBJ3D::ReformTexture(int Type, int MatNum, int MatCnt, POINT3D *pos, POINT3D *size)
{
	int cnt, cnt2;
	smTEXLINK *lpTexLink;
	int rx, ry, rz;
	float fx, fy, fz;
	int vn;

	for (cnt = 0; cnt < nFace; cnt++) {
		if (MatNum == Face[cnt].v[3]) {
			lpTexLink = Face[cnt].lpTexLink;
			for (cnt2 = 0; cnt2 < MatCnt; cnt2++)
				lpTexLink = lpTexLink->NextTex;

			switch (Type) {
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
				for (cnt2 = 0; cnt2 < 3; cnt2++) {
					vn = Face[cnt].v[cnt2];
					rx = smWorldVertex[vn].x;
					ry = smWorldVertex[vn].y;
					rz = smWorldVertex[vn].z;

					rx += pos->x;
					ry += pos->y;
					rz += pos->z;

					rx = ((rx << (FLOATNS)) / size->x);
					fx = ((float)rx) / fONE;
					rz = ((rz << (FLOATNS)) / size->z);
					fz = ((float)rz) / fONE;
					ry = ((ry << (FLOATNS)) / size->y);
					fy = ((float)ry) / fONE;

					fx += 0.50;
					fz += 0.50;
					fy += 0.50;

					lpTexLink->u[cnt2] = -fx;
					lpTexLink->v[cnt2] = -fy;
				}
				break;
			}
		}
	}


	return TRUE;
}



// 노말값 삭제 ( 0으로 초기화 )
void smOBJ3D::ZeroNormals()
{
	int cnt;

	for (cnt = 0; cnt < nVertex; cnt++) {
		Vertex[cnt].nx = 0;
		Vertex[cnt].ny = 0;
		Vertex[cnt].nz = 0;
	}

	//######################################################################################
	//작 성 자 : 오 영 석
	Head &= (~OBJ_HEAD_TYPE_NEW_NORMAL);
	//######################################################################################
}

// 쉐이드 노말값 생성
void smOBJ3D::SetGNormals()
{
	int cnt;
	float i, j, k, d;
	smVERTEX *p1, *p2, *p3;
	int *VNormalCnt;

	VNormalCnt = new int[nVertex];

	for (cnt = 0; cnt < nVertex; cnt++) {
		Vertex[cnt].nx = 0;
		Vertex[cnt].ny = 0;
		Vertex[cnt].nz = 0;
		VNormalCnt[cnt] = 0;
	}

	// Normal 값 계산 노말 좌표 계산하여 Vertex에 더함
	for (cnt = 0; cnt < nFace; cnt++) {

		p1 = &Vertex[Face[cnt].v[0]];
		p2 = &Vertex[Face[cnt].v[1]];
		p3 = &Vertex[Face[cnt].v[2]];


		i = (float)(((p2->y - p1->y) * (p3->z - p1->z)) - ((p2->z - p1->z) * (p3->y - p1->y)));
		j = (float)(((p2->z - p1->z) * (p3->x - p1->x)) - ((p2->x - p1->x) * (p3->z - p1->z)));
		k = (float)(((p2->x - p1->x) * (p3->y - p1->y)) - ((p2->y - p1->y) * (p3->x - p1->x)));

		d = (float)sqrt((double)((i * i) + (j * j) + (k * k)));
		i = (float)(i / d * 32767);
		j = (float)(j / d * 32767);
		k = (float)(k / d * 32767);

		//Normal->SetTo( (long) i, (long) j, (long) k );
		p1->nx += (int)i; p1->ny += (int)j; p1->nz += (int)k;
		VNormalCnt[Face[cnt].v[0]]++;

		p2->nx += (int)i; p2->ny += (int)j; p2->nz += (int)k;
		VNormalCnt[Face[cnt].v[1]]++;

		p3->nx += (int)i; p3->ny += (int)j; p3->nz += (int)k;
		VNormalCnt[Face[cnt].v[2]]++;
	}

	// Vertex 노말의 평균을 구하여 완료
	for (cnt = 0; cnt < nVertex; cnt++) {
		if (VNormalCnt[cnt]) {
			Vertex[cnt].nx /= VNormalCnt[cnt];
			Vertex[cnt].ny /= VNormalCnt[cnt];
			Vertex[cnt].nz /= VNormalCnt[cnt];

			//######################################################################################
			// 작 성 자 : 오 영 석
			Vertex[cnt].nx += Vertex[cnt].x;
			Vertex[cnt].ny += Vertex[cnt].y;
			Vertex[cnt].nz += Vertex[cnt].z;
			//######################################################################################

/*
			d = (float) sqrt(	Vertex[cnt].nx * Vertex[cnt].nx +
								Vertex[cnt].ny * Vertex[cnt].ny +
								Vertex[cnt].nz * Vertex[cnt].nz);

			if (d==0) d=1;

			Vertex[cnt].nx = (32768 * Vertex[cnt].nx) / (int)d;
			Vertex[cnt].ny = (32768 * Vertex[cnt].ny) / (int)d;
			Vertex[cnt].nz = (32768 * Vertex[cnt].nz) / (int)d;
*/
		}
	}

	delete VNormalCnt;

}
// 멀티 텍스쳐일 경우 소트해야 한번에 그리기가 편하다
void smOBJ3D::SortMatrial()
{
	int cnt1, cnt2;

	smFACE tempFace;

	//	for( cnt=0;cnt<16;cnt++) {
	for (cnt1 = 0; cnt1 < nFace; cnt1++) {
		for (cnt2 = cnt1; cnt2 < nFace; cnt2++) {
			if (Face[cnt1].v[3] > Face[cnt2].v[3]) {
				memcpy(&tempFace, &Face[cnt1], sizeof(smFACE));
				memcpy(&Face[cnt1], &Face[cnt2], sizeof(smFACE));
				memcpy(&Face[cnt2], &tempFace, sizeof(smFACE));
			}
		}
	}
	//	}
}

// 겹치거나 사용되지 않는 VERTEX를 찾아내어 정리한다
void smOBJ3D::SortVertex()
{
	int cnt1, cnt2, cnt3, cnt4;
	int x, y, z;


	// 겹치는 VERTEX 제거
	for (cnt1 = 1; cnt1 < nVertex; cnt1++) {
		for (cnt2 = 0; cnt2 < cnt1; cnt2++) {
			x = abs(Vertex[cnt1].x - Vertex[cnt2].x);
			y = abs(Vertex[cnt1].y - Vertex[cnt2].y);
			z = abs(Vertex[cnt1].z - Vertex[cnt2].z);

			if (x == 0 && y == 0 && z == 0 && cnt1 < nVertex) {// 제거 대상
				for (cnt3 = 0; cnt3 < nFace; cnt3++) {

					if (Face[cnt3].v[0] == cnt1) Face[cnt3].v[0] = cnt2;
					if (Face[cnt3].v[1] == cnt1) Face[cnt3].v[1] = cnt2;
					if (Face[cnt3].v[2] == cnt1) Face[cnt3].v[2] = cnt2;

					if (Face[cnt3].v[0] > cnt1) Face[cnt3].v[0]--;
					if (Face[cnt3].v[1] > cnt1) Face[cnt3].v[1]--;
					if (Face[cnt3].v[2] > cnt1) Face[cnt3].v[2]--;

				}
				nVertex--;
				if (cnt1 != nVertex) {
					for (cnt4 = cnt1; cnt4 < nVertex; cnt4++)
						memcpy(&Vertex[cnt4], &Vertex[cnt4 + 1], sizeof(smVERTEX));

					if (Physique) {
						for (cnt4 = cnt1; cnt4 < nVertex; cnt4++)
							Physique[cnt4] = Physique[cnt4 + 1];
					}
				}
			}
		}
	}


	// 사용 되지 않는 VERTEX 제거
	short	*pUseVertex = new short[nVertex];

	ZeroMemory(pUseVertex, sizeof(short)*nVertex);
	for (cnt1 = 0; cnt1 < nFace; cnt1++) {
		pUseVertex[Face[cnt1].v[0]]++;
		pUseVertex[Face[cnt1].v[1]]++;
		pUseVertex[Face[cnt1].v[2]]++;

		if (Face[cnt1].v[0] >= nVertex ||
			Face[cnt1].v[1] >= nVertex ||
			Face[cnt1].v[2] >= nVertex) {

			cnt1 = cnt1;

		}

	}

	for (cnt1 = 0; cnt1 < nVertex; cnt1++) {
		if (pUseVertex[cnt1] == 0) {
			for (cnt3 = 0; cnt3 < nFace; cnt3++) {
				if (Face[cnt3].v[0] > cnt1) Face[cnt3].v[0]--;
				if (Face[cnt3].v[1] > cnt1) Face[cnt3].v[1]--;
				if (Face[cnt3].v[2] > cnt1) Face[cnt3].v[2]--;
			}
			nVertex--;
			if (cnt1 != nVertex) {
				for (cnt4 = cnt1; cnt4 < nVertex; cnt4++)
					memcpy(&Vertex[cnt4], &Vertex[cnt4 + 1], sizeof(smVERTEX));

				if (Physique) {
					for (cnt4 = cnt1; cnt4 < nVertex; cnt4++)
						Physique[cnt4] = Physique[cnt4 + 1];
				}
			}
		}
	}

	delete pUseVertex;

}

// TM의 역행렬을 계산하여 지역 좌표 변환
void smOBJ3D::ReformTM()
{
	int cnt;
	int x, y, z;
	smMATRIX q;
	int scale;

	//스케일 보정 땜빵
	if (!pParent) {
		scale = (sx + sy + sz) / 3;
		if (scale != 0) {
			Tm._11 = (Tm._11 << FLOATNS) / scale;
			Tm._12 = (Tm._12 << FLOATNS) / scale;
			Tm._13 = (Tm._13 << FLOATNS) / scale;
			Tm._21 = (Tm._21 << FLOATNS) / scale;
			Tm._22 = (Tm._22 << FLOATNS) / scale;
			Tm._23 = (Tm._23 << FLOATNS) / scale;
			Tm._31 = (Tm._31 << FLOATNS) / scale;
			Tm._32 = (Tm._32 << FLOATNS) / scale;
			Tm._33 = (Tm._33 << FLOATNS) / scale;

			//######################################################################################
			//작 성 자 : 오 영 석
			//px =0;
			//py =0;
			//pz =0;
			//######################################################################################
		}
	}
	else {
		scale = (pParent->sx + pParent->sy + pParent->sz) / 3;

		if (scale != 0) {
			Tm._11 = (Tm._11 << FLOATNS) / scale;
			Tm._12 = (Tm._12 << FLOATNS) / scale;
			Tm._13 = (Tm._13 << FLOATNS) / scale;
			Tm._21 = (Tm._21 << FLOATNS) / scale;
			Tm._22 = (Tm._22 << FLOATNS) / scale;
			Tm._23 = (Tm._23 << FLOATNS) / scale;
			Tm._31 = (Tm._31 << FLOATNS) / scale;
			Tm._32 = (Tm._32 << FLOATNS) / scale;
			Tm._33 = (Tm._33 << FLOATNS) / scale;
		}
	}

	smMatrixInvert(q, Tm);
	memcpy(&TmInvert, &q, sizeof(smMATRIX));


	for (cnt = 0; cnt < nVertex; cnt++) {

		x = Vertex[cnt].x * q._11 +
			Vertex[cnt].y * q._21 +
			Vertex[cnt].z * q._31;

		y = Vertex[cnt].x * q._12 +
			Vertex[cnt].y * q._22 +
			Vertex[cnt].z * q._32;

		z = Vertex[cnt].x * q._13 +
			Vertex[cnt].y * q._23 +
			Vertex[cnt].z * q._33;

		Vertex[cnt].x = (x >> FLOATNS) + q._41;
		Vertex[cnt].y = (y >> FLOATNS) + q._42;
		Vertex[cnt].z = (z >> FLOATNS) + q._43;

		//######################################################################################
		// 작 성 자 : 오 영 석
		x = Vertex[cnt].nx * q._11 +
			Vertex[cnt].ny * q._21 +
			Vertex[cnt].nz * q._31;

		y = Vertex[cnt].nx * q._12 +
			Vertex[cnt].ny * q._22 +
			Vertex[cnt].nz * q._32;

		z = Vertex[cnt].nx * q._13 +
			Vertex[cnt].ny * q._23 +
			Vertex[cnt].nz * q._33;

		Vertex[cnt].nx = (x >> FLOATNS) + q._41;
		Vertex[cnt].ny = (y >> FLOATNS) + q._42;
		Vertex[cnt].nz = (z >> FLOATNS) + q._43;
		//######################################################################################
	}
}

// 피지크의 대응 TM의 역행렬을 계산하여 지역 좌표 변환
void smOBJ3D::ReformPhysique()
{
	int cnt;
	int x, y, z;
	smMATRIX q;
	smOBJ3D *pBone;

	for (cnt = 0; cnt < nVertex; cnt++) {

		pBone = Physique[cnt];

		smMatrixInvert(q, pBone->Tm);

		x = Vertex[cnt].x * q._11 +
			Vertex[cnt].y * q._21 +
			Vertex[cnt].z * q._31;

		y = Vertex[cnt].x * q._12 +
			Vertex[cnt].y * q._22 +
			Vertex[cnt].z * q._32;

		z = Vertex[cnt].x * q._13 +
			Vertex[cnt].y * q._23 +
			Vertex[cnt].z * q._33;


		Vertex[cnt].x = (x >> FLOATNS) + q._41;
		Vertex[cnt].y = (y >> FLOATNS) + q._42;
		Vertex[cnt].z = (z >> FLOATNS) + q._43;

		//######################################################################################
		// 작 성 자 : 오 영 석
		x = Vertex[cnt].nx * q._11 +
			Vertex[cnt].ny * q._21 +
			Vertex[cnt].nz * q._31;

		y = Vertex[cnt].nx * q._12 +
			Vertex[cnt].ny * q._22 +
			Vertex[cnt].nz * q._32;

		z = Vertex[cnt].nx * q._13 +
			Vertex[cnt].ny * q._23 +
			Vertex[cnt].nz * q._33;


		Vertex[cnt].nx = (x >> FLOATNS) + q._41;
		Vertex[cnt].ny = (y >> FLOATNS) + q._42;
		Vertex[cnt].nz = (z >> FLOATNS) + q._43;
		//######################################################################################
	}
}


//=========================== [ 렌더링  관련 ] =============================//

// 이건 바보다.
int smOBJ3D::TestRotate(int x, int y, int z, POINT3D *LocalAngle, POINT3D *GlobalAngle)
{
	return FALSE;
}

// 오브젝트 렌더링 준비
int smOBJ3D::BeginRender()
{
	

	return TRUE;

}


//######################################################################################
//작 성 자 : 오 영 석
//회전 쿼터니언을 보간 , 중간 프레임의 행열을 구함 
int smOBJ3D::GetRotFrame(smFMATRIX &gmat, smFMATRIX *PrevRot, smTM_ROT *tmRot, int frame, SMotionStEndInfo *lpFrameInfo)
//######################################################################################
{

	float qx, qy, qz, qw;
	float ax, ay, az, aw;
	float bx, by, bz, bw;
	int cnt;
	int s, e, ch, sh;
	float alpha;

	cnt = 0;

	if (tmRot[cnt].frame > frame) return frame;

	while (1) {
		s = tmRot[cnt].frame;
		e = tmRot[cnt + 1].frame;
		if (s <= frame && e > frame) break;
		cnt++;
	}

	ch = e - s;
	sh = frame - s;

	alpha = (float)sh / (float)ch;

	ax = tmRot[cnt].x;
	ay = tmRot[cnt].y;
	az = tmRot[cnt].z;
	aw = tmRot[cnt].w;

	bx = tmRot[cnt + 1].x;
	by = tmRot[cnt + 1].y;
	bz = tmRot[cnt + 1].z;
	bw = tmRot[cnt + 1].w;

	//######################################################################################
	//작 성 자 : 오 영 석
	if (lpFrameInfo && e > (int)lpFrameInfo->EndFrame)
	{
		::CopyMemory(&gmat, &PrevRot[cnt], sizeof(smFMATRIX));
		return s;
	}
	//######################################################################################

	//smTM_ROT tRot;

	D3DMath_QuaternionSlerp(qx, qy, qz, qw, 0, 0, 0, 0, bx, by, bz, bw, alpha);

	//######################################################################################
	//작 성 자 : 오 영 석
	smFMatrixFromQuaternion(gmat, qx, qy, qz, qw);
	smFMatrixMult(gmat, PrevRot[cnt], gmat);
	//######################################################################################

	return s;
}


//######################################################################################
//작 성 자 : 오 영 석
//이동 좌표를 보간 , 중간 프레임의 이동 좌표를 구함 
int smOBJ3D::GetPosFrame(float &x, float &y, float &z, smTM_POS *tmPos, int frame)
//######################################################################################
{
	int s, e, ch, sh;
	int	cnt = 0;

	//######################################################################################
	//작 성 자 : 오 영 석
	float alpha;
	//######################################################################################

	if (tmPos[cnt].frame > frame) return frame;

	while (1) {
		s = tmPos[cnt].frame;
		e = tmPos[cnt + 1].frame;
		if (s <= frame && e > frame) break;
		cnt++;
	}

	ch = e - s;
	sh = frame - s;

	//######################################################################################
	//작 성 자 : 오 영 석
	alpha = float(sh) / float(ch);

	x = tmPos[cnt].x + ((tmPos[cnt + 1].x - tmPos[cnt].x) * alpha);
	y = tmPos[cnt].y + ((tmPos[cnt + 1].y - tmPos[cnt].y) * alpha);
	z = tmPos[cnt].z + ((tmPos[cnt + 1].z - tmPos[cnt].z) * alpha);
	//######################################################################################

	return s;
}


//스케일 좌표를 보간 , 중간 프레임의 스케일 좌표를 구함 
int smOBJ3D::GetScaleFrame(int &x, int &y, int &z, smTM_SCALE *tmSclae, int frame)
{
	int s, e, ch, sh;
	int	cnt = 0;
	int alpha;

	if (tmSclae[cnt].frame > frame) return frame;

	while (1) {
		s = tmSclae[cnt].frame;
		e = tmSclae[cnt + 1].frame;
		if (s <= frame && e > frame) break;
		cnt++;
	}

	ch = e - s;
	sh = frame - s;
	alpha = (sh << 8) / ch;

	x = tmSclae[cnt].x + (((tmSclae[cnt + 1].x - tmSclae[cnt].x) * alpha) >> 8);
	y = tmSclae[cnt].y + (((tmSclae[cnt + 1].y - tmSclae[cnt].y) * alpha) >> 8);
	z = tmSclae[cnt].z + (((tmSclae[cnt + 1].z - tmSclae[cnt].z) * alpha) >> 8);
	return s;
}


//애니메이션 프레임 위치를 찾는다 ( 다중 결합 애니메이션 경우 )
int smOBJ3D::GetTmFramePos(int frame)
{
	int cnt;

	if (TmFrameCnt > 0) {
		for (cnt = 0; cnt < TmFrameCnt; cnt++) {
			if (TmPosFrame[cnt].PosCnt > 0 && TmPosFrame[cnt].StartFrame <= frame &&
				TmPosFrame[cnt].EndFrame > frame) {

				return TmPosFrame[cnt].PosNum;

			}
		}

	}

	return -1;
}


//애니메이션 프레임 크기를 찾는다 ( 다중 결합 애니메이션 경우 )
int smOBJ3D::GetTmFrameScale(int frame)
{
	int cnt;

	if (TmFrameCnt > 0) {
		for (cnt = 0; cnt < TmFrameCnt; cnt++) {
			if (TmScaleFrame[cnt].PosCnt > 0 && TmScaleFrame[cnt].StartFrame <= frame &&
				TmScaleFrame[cnt].EndFrame > frame) {

				return TmScaleFrame[cnt].PosNum;

			}
		}

	}

	return -1;
}

//애니메이션 프레임 위치를 찾는다 ( 다중 결합 애니메이션 경우 )
int smOBJ3D::GetTmFrameRot(int frame)
{
	int cnt;

	if (TmFrameCnt > 0) {
		for (cnt = 0; cnt < TmFrameCnt; cnt++) {
			if (TmRotFrame[cnt].PosCnt > 0 && TmRotFrame[cnt].StartFrame <= frame &&
				TmRotFrame[cnt].EndFrame > frame) {

				return TmRotFrame[cnt].PosNum;

			}
		}

	}

	return -1;
}
int smOBJ3D::TmTalkAnimation(int frame)
{
	smFMATRIX qmat;

	int cnt;
	int NumTmRot, NumTmPos, NumTmScale;

	smFMATRIX	fMat;
	smMATRIX	Mat;

	smFIdentityMatrix(qmat);

	NumTmRot = GetTmFrameRot(frame);
	NumTmPos = GetTmFramePos(frame);
	NumTmScale = GetTmFrameScale(frame);

	if (TmFrameCnt && (NumTmRot >= 0 || NumTmPos >= 0 || NumTmScale > 0))
	{
		if (TmRotCnt > 0 && NumTmRot >= 0)
			cnt = GetRotFrame(qmat, &TmPrevRot[NumTmRot], &TmRot[NumTmRot], frame);
		else
			smFMatrixFromMatrix(qmat, TmRotate);

		if (TmScaleCnt > 0 && NumTmScale >= 0)
		{
			smIdentityMatrix(Mat);
			GetScaleFrame(Mat._11, Mat._22, Mat._33, &TmScale[NumTmScale], frame);
			smFMatrixFromMatrix(fMat, Mat);
			smFMatrixMult(qmat, qmat, fMat);
		}

		if (TmPosCnt > 0 && NumTmPos >= 0)
			GetPosFrame(qmat._41, qmat._42, qmat._43, &TmPos[NumTmPos], frame);
		else
		{
			qmat._41 = float(px) / fONE;
			qmat._42 = float(py) / fONE;
			qmat._43 = float(pz) / fONE;
		}

		memcpy(&TmResult, &qmat, sizeof(qmat));
	}
	else
		smFIdentityMatrix(TmResult);

	return TRUE;
}
int smOBJ3D::TmAnimation(int frame, int ax, int ay, int az, smPAT3D *TalkPattern, SMotionStEndInfo *lpFrameInfo)
{
	return TRUE;
}
int smOBJ3D::TmAnimation(int frame, int ax, int ay, int az, SMotionStEndInfo *lpFrameInfo)
{

	return TRUE;
}
int smOBJ3D::WorldForm()
{
	smVERTEX	*pV;
	smMATRIX	*mMat;

	int cnt;
	int rx, ry, rz;

	if (Physique)
	{
		for (cnt = 0; cnt < nVertex; cnt++)
		{
			pV = &Vertex[cnt];
			mMat = &Physique[cnt]->mWorld;

			rx = pV->x * mMat->_11 + pV->y * mMat->_21 + pV->z * mMat->_31;

			ry = pV->x * mMat->_12 + pV->y * mMat->_22 + pV->z * mMat->_32;

			rz = pV->x * mMat->_13 + pV->y * mMat->_23 + pV->z * mMat->_33;

			smWorldVertex[cnt].x = (rx >> FLOATNS) + mMat->_41;
			smWorldVertex[cnt].z = (ry >> FLOATNS) + mMat->_42;
			smWorldVertex[cnt].y = (rz >> FLOATNS) + mMat->_43;

			if (Head & OBJ_HEAD_TYPE_NEW_NORMAL)
				mMat = &Physique[cnt]->mWorld;
			else
				mMat = &Physique[cnt]->mLocal;

			rx = pV->nx * mMat->_11 + pV->ny * mMat->_21 + pV->nz * mMat->_31;

			ry = pV->nx * mMat->_12 + pV->ny * mMat->_22 + pV->nz * mMat->_32;

			rz = pV->nx * mMat->_13 + pV->ny * mMat->_23 + pV->nz * mMat->_33;

			smWorldVertex[cnt].nx = (rx >> FLOATNS) + mMat->_41;
			smWorldVertex[cnt].nz = (ry >> FLOATNS) + mMat->_42;
			smWorldVertex[cnt].ny = (rz >> FLOATNS) + mMat->_43;


		}
	}
	else
	{
		for (cnt = 0; cnt < nVertex; cnt++)
		{

			pV = &Vertex[cnt];

			rx = pV->x * mWorld._11 + pV->y * mWorld._21 + pV->z * mWorld._31;

			ry = pV->x * mWorld._12 + pV->y * mWorld._22 + pV->z * mWorld._32;

			rz = pV->x * mWorld._13 + pV->y * mWorld._23 + pV->z * mWorld._33;

			smWorldVertex[cnt].x = (rx >> FLOATNS) + mWorld._41;
			smWorldVertex[cnt].z = (ry >> FLOATNS) + mWorld._42;
			smWorldVertex[cnt].y = (rz >> FLOATNS) + mWorld._43;

			if (Head & OBJ_HEAD_TYPE_NEW_NORMAL)
				mMat = &mWorld;
			else
				mMat = &mLocal;

			rx = pV->nx * mMat->_11 + pV->ny * mMat->_21 + pV->nz * mMat->_31;

			ry = pV->nx * mMat->_12 + pV->ny * mMat->_22 + pV->nz * mMat->_32;

			rz = pV->nx * mMat->_13 + pV->ny * mMat->_23 + pV->nz * mMat->_33;

			smWorldVertex[cnt].nx = (rx >> FLOATNS) + mMat->_41;
			smWorldVertex[cnt].nz = (ry >> FLOATNS) + mMat->_42;
			smWorldVertex[cnt].ny = (rz >> FLOATNS) + mMat->_43;
		}
	}

	return TRUE;
}
void smOBJ3D::SetPosi(POINT3D *point, POINT3D *angle)
{
	Posi.x = point->x;
	Posi.y = point->y;
	Posi.z = point->z;

	Angle.x = angle->x;
	Angle.y = angle->y;
	Angle.z = angle->z;
}
int smOBJ3D::TestRender(POINT3D *camera, POINT3D *angle)
{
	

	return FALSE;
}
int smOBJ3D::ActionRenderD3D()
{
	return TRUE;
}

int smOBJ3D::RenderD3D(POINT3D *camera, POINT3D *angle)
{
	
	return FALSE;
}

int smOBJ3D::RenderD3dOpening(POINT3D *camera, POINT3D *angle)
{
	return TRUE;
}
int smOBJ3D::GetSaveSize()
{
	int size;

	size = sizeof(smOBJ3D);
	size += sizeof(smVERTEX) * nVertex;
	size += sizeof(smFACE) * nFace;
	size += sizeof(smTEXLINK) * nTexLink;

	size += sizeof(smTM_ROT) * TmRotCnt;
	size += sizeof(smTM_POS) * TmPosCnt;
	size += sizeof(smTM_SCALE) * TmScaleCnt;
	size += sizeof(smMATRIX) * TmRotCnt;

	if (Physique)
		size += 32 * nVertex;

	return size;
}
int smOBJ3D::SaveFile(HANDLE hFile)
{
	DWORD	dwAcess;
	char	szBuff[64];
	int		cnt;
	int		size;

	Head = 0x41424344;

	Head |= OBJ_HEAD_TYPE_NEW_NORMAL;

	size = WriteFile(hFile, &Head, sizeof(smOBJ3D), &dwAcess, NULL);
	size += WriteFile(hFile, Vertex, sizeof(smVERTEX)	* nVertex, &dwAcess, NULL);
	size += WriteFile(hFile, Face, sizeof(smFACE)		* nFace, &dwAcess, NULL);
	size += WriteFile(hFile, TexLink, sizeof(smTEXLINK)	* nTexLink, &dwAcess, NULL);
	size += WriteFile(hFile, TmRot, sizeof(smTM_ROT)	* TmRotCnt, &dwAcess, NULL);
	size += WriteFile(hFile, TmPos, sizeof(smTM_POS)	* TmPosCnt, &dwAcess, NULL);
	size += WriteFile(hFile, TmScale, sizeof(smTM_SCALE)	* TmScaleCnt, &dwAcess, NULL);
	size += WriteFile(hFile, TmPrevRot, sizeof(smMATRIX)	* TmRotCnt, &dwAcess, NULL);

	if (Physique)
	{
		for (cnt = 0; cnt < nVertex; cnt++)
		{
			ZeroMemory(szBuff, 32);
			lstrcpy(szBuff, Physique[cnt]->NodeName);
			size += WriteFile(hFile, szBuff, 32, &dwAcess, NULL);
		}
	}

	return size;
}
int smOBJ3D::LoadFile(HANDLE hFile, smPAT3D *PatPhysique)
{
	DWORD	dwAcess;
	char	*szBuff;
	int		cnt;
	int		len;
	smTEXLINK	*lpOldTexLink;
	int		SubTexLink;

	len = ReadFile(hFile, &Head, sizeof(smOBJ3D), &dwAcess, NULL);

	lpOldTexLink = TexLink;

	Vertex = new smVERTEX[nVertex];
	len += ReadFile(hFile, Vertex, sizeof(smVERTEX) * nVertex, &dwAcess, NULL);

	Face = new smFACE[nFace];
	len += ReadFile(hFile, Face, sizeof(smFACE) * nFace, &dwAcess, NULL);

	TexLink = new smTEXLINK[nTexLink];
	len += ReadFile(hFile, TexLink, sizeof(smTEXLINK) * nTexLink, &dwAcess, NULL);

	TmRot = new smTM_ROT[TmRotCnt];
	len += ReadFile(hFile, TmRot, sizeof(smTM_ROT) * TmRotCnt, &dwAcess, NULL);

	TmPos = new smTM_POS[TmPosCnt];
	len += ReadFile(hFile, TmPos, sizeof(smTM_POS) * TmPosCnt, &dwAcess, NULL);

	TmScale = new smTM_SCALE[TmScaleCnt];
	len += ReadFile(hFile, TmScale, sizeof(smTM_SCALE) * TmScaleCnt, &dwAcess, NULL);

	TmPrevRot = new smFMATRIX[TmRotCnt];
	len += ReadFile(hFile, TmPrevRot, sizeof(smFMATRIX) * TmRotCnt, &dwAcess, NULL);

	SubTexLink = TexLink - lpOldTexLink;

	for (cnt = 0; cnt < nTexLink; cnt++)
	{
		if (TexLink[cnt].NextTex)
		{
			SubTexLink = TexLink[cnt].NextTex - lpOldTexLink;
			TexLink[cnt].NextTex = TexLink + SubTexLink;
		}
	}

	for (cnt = 0; cnt < nFace; cnt++)
	{
		if (Face[cnt].lpTexLink)
		{
			SubTexLink = Face[cnt].lpTexLink - lpOldTexLink;
			Face[cnt].lpTexLink = TexLink + SubTexLink;
		}
	}

	if (Physique && PatPhysique)
	{
		Physique = new smOBJ3D *[nVertex];
		szBuff = new char[nVertex * 32];
		len += ReadFile(hFile, szBuff, nVertex * 32, &dwAcess, NULL);

		for (cnt = 0; cnt < nVertex; cnt++)
			Physique[cnt] = PatPhysique->GetObjectFromName(szBuff + cnt * 32);

		delete szBuff;
	}

	return len;
}

smPAT3D::smPAT3D()
{
	Init();

}

smPAT3D::~smPAT3D()
{
	Close();
}


void smPAT3D::Init()
{

	nObj3d = 0;
	TmParent = 0;

	MaxFrame = 0;
	Frame = 0;

	SizeWidth = 0;
	SizeHeight = 0;

	Bound = 0;
	dBound = 0;

	TmFrameCnt = 0;

	TmLastFrame = -1;
	TmLastAngle.x = -1;
	TmLastAngle.y = -1;
	TmLastAngle.z = -1;

	for (int cnt = 0; cnt < 128; cnt++)
		TmSort[cnt] = cnt;

	smMaterialGroup = 0;

}
void smPAT3D::Close()
{
	int cnt;

	for (cnt = nObj3d - 1; cnt >= 0; cnt--)
		DELET(obj3d[cnt]);

	DELET(smMaterialGroup);
}
int smPAT3D::AddObject(smOBJ3D *obj)
{
	int frame;

	if (nObj3d < 128)
	{
		obj3d[nObj3d] = obj;
		nObj3d++;

		frame = 0;

		if (obj->TmRotCnt > 0 && obj->TmRot)
			frame = obj->TmRot[obj->TmRotCnt - 1].frame;
		if (obj->TmPosCnt > 0 && obj->TmPos)
			frame = obj->TmPos[obj->TmPosCnt - 1].frame;
		if (MaxFrame < frame)
			MaxFrame = frame;

		if (SizeWidth < obj->maxX)
			SizeWidth = obj->maxX;
		if (SizeWidth < obj->maxZ)
			SizeWidth = obj->maxZ;
		if (SizeHeight < obj->maxY)
			SizeHeight = obj->maxY;

		if (Bound < obj->Bound)
		{
			Bound = obj->Bound;
			dBound = obj->dBound;
		}

		return TRUE;
	}

	return FALSE;
}
int smPAT3D::ReformTM()
{
	int cnt;

	for (cnt = 0; cnt < nObj3d; cnt++)
	{
		obj3d[cnt]->SetGNormals();
		obj3d[cnt]->ReformTM();
	}

	return TRUE;
}
int smPAT3D::ReformPhysique()
{
	int cnt;

	for (cnt = 0; cnt < nObj3d; cnt++)
	{
		obj3d[cnt]->SetGNormals();
		obj3d[cnt]->ReformPhysique();
	}
	MaxFrame = TmParent->MaxFrame;

	return TRUE;
}
int smPAT3D::LinkObject()
{

	int cnt, cnt2, ocnt;

	for (cnt = 0; cnt < nObj3d; cnt++)
	{
		if (obj3d[cnt]->NodeParent[0])
		{
			for (ocnt = 0; ocnt < nObj3d; ocnt++)
			{
				if (lstrcmp(obj3d[cnt]->NodeParent, obj3d[ocnt]->NodeName) == 0)
				{
					obj3d[cnt]->pParent = obj3d[ocnt];
					break;
				}
			}
		}
		else
			cnt2 = 0;
	}

	int NodeCnt = 0;

	for (cnt = 0; cnt < 128; cnt++)
		TmSort[cnt] = 0;

	for (cnt = 0; cnt < nObj3d; cnt++)
	{
		if (obj3d[cnt]->pParent == 0)
			TmSort[NodeCnt++] = cnt;
	}

	for (cnt2 = 0; cnt2 < nObj3d; cnt2++)
	{
		for (cnt = 0; cnt < nObj3d; cnt++)
		{
			if (obj3d[cnt]->pParent != 0 && obj3d[TmSort[cnt2]] == obj3d[cnt]->pParent)
				TmSort[NodeCnt++] = cnt;
		}
	}

	return TRUE;
}
smOBJ3D *smPAT3D::GetObjectFromName(char *name)
{
	int cnt;

	for (cnt = 0; cnt < nObj3d; cnt++)
	{
		if (lstrcmpi(obj3d[cnt]->NodeName, name) == 0)
			return obj3d[cnt];
	}

	return NULL;
}
void smPAT3D::ZeroNormals()
{
	int cnt;

	for (cnt = 0; cnt < nObj3d; cnt++)
		obj3d[cnt]->ZeroNormals();
}
void smPAT3D::SetPosi(POINT3D *point, POINT3D *angle)
{
	int cnt;

	Posi.x = point->x;
	Posi.y = point->y;
	Posi.z = point->z;

	Angle.x = angle->x;
	Angle.y = angle->y;
	Angle.z = angle->z;


	for (cnt = 0; cnt < nObj3d; cnt++)
	{
		if (obj3d[cnt])
			obj3d[cnt]->SetPosi(point, angle);
	}

}
void smPAT3D::SetFixPosi()
{
	int cnt;
	POINT3D	pos, ang;


	Posi.x = obj3d[0]->Tm._41;
	Posi.y = obj3d[0]->Tm._43;
	Posi.z = obj3d[0]->Tm._42;

	Angle.x = 0;
	Angle.y = 0;
	Angle.z = 0;

	ang.x = 0;
	ang.y = 0;
	ang.z = 0;

	for (cnt = 0; cnt < nObj3d; cnt++)
	{
		pos.x = obj3d[cnt]->Tm._41;
		pos.y = obj3d[cnt]->Tm._43;
		pos.z = obj3d[cnt]->Tm._42;
		obj3d[cnt]->SetPosi(&pos, &ang);
	}

}
int smPAT3D::RenderD3D(POINT3D *camera, POINT3D *angle, smPAT3D *TalkPattern, SMotionStEndInfo *lpFrameInfo)
{
	return 0;
}


int smPAT3D::ChoiseRenderD3D(POINT3D *camera, POINT3D *angle, char **szNodeList, int ListCnt, smPAT3D *TalkPattern, SMotionStEndInfo *lpFrameInfo)
{
	return 0;
}
int smPAT3D::RenderD3D(POINT3D *camera, POINT3D *angle, SMotionStEndInfo *lpFrameInfo)
{
	
	return 0;
}
int smPAT3D::ChoiseRenderD3D(POINT3D *camera, POINT3D *angle, char **szNodeList, int ListCnt, SMotionStEndInfo *lpFrameInfo)
{
	
	return 0;
}
int smPAT3D::RenderD3dOpening(POINT3D *camera, POINT3D *angle)
{

	return 0;
}
int smPAT3D::SetFrame(int frame, smPAT3D *TalkPattern, SMotionStEndInfo *lpFrameInfo)
{
	if (frame < 0 || TalkPattern->Frame < 0)
		return FALSE;

	TalkPattern->TmTalkAnimation(TalkPattern->Frame);

	if (TmParent)
		TmParent->TmAnimation(frame, Angle.x, Angle.y, Angle.z, TalkPattern, lpFrameInfo);
	else
		TmAnimation(frame, Angle.x, Angle.y, Angle.z, TalkPattern, lpFrameInfo);
	return TRUE;
}

int smPAT3D::TmTalkAnimation(int frame)
{
	int cnt;

	if (TmLastFrame == frame)
		return TRUE;

	TmLastFrame = frame;
	for (cnt = 0; cnt < nObj3d; cnt++)
		obj3d[TmSort[cnt]]->TmTalkAnimation(frame);

	return TRUE;
}

int smPAT3D::TmAnimation(int frame, int ax, int ay, int az, smPAT3D *TalkPattern, SMotionStEndInfo *lpFrameInfo)
{
	int cnt;

	if (TmLastFrame == frame && TmLastAngle.x == ax && TmLastAngle.y == ay && TmLastAngle.z == az)
		return TRUE;

	TmLastFrame = frame;
	TmLastAngle.x = ax;
	TmLastAngle.y = ay;
	TmLastAngle.z = az;

	for (cnt = 0; cnt < nObj3d; cnt++)
		obj3d[TmSort[cnt]]->TmAnimation(frame, ax, ay, az, TalkPattern, lpFrameInfo);

	return TRUE;

}

int smPAT3D::SetFrame(int frame, SMotionStEndInfo *lpFrameInfo)
{
	int cnt;

	if (frame < 0)
		return FALSE;

	if (TmParent)
	{
		TmParent->TmAnimation(frame, Angle.x, Angle.y, Angle.z, lpFrameInfo);
		for (cnt = 0; cnt < nObj3d; cnt++)
		{
			if (obj3d[cnt] && obj3d[cnt]->pParent)
				memcpy(&obj3d[cnt]->mWorld, &obj3d[cnt]->pParent->mWorld, sizeof(smMATRIX));
		}
	}
	else
		TmAnimation(frame, Angle.x, Angle.y, Angle.z, lpFrameInfo);

	return TRUE;
}
int smPAT3D::TmAnimation(int frame, int ax, int ay, int az, SMotionStEndInfo *lpFrameInfo)
{
	int cnt;

	if (TmLastFrame == frame &&
		TmLastAngle.x == ax && TmLastAngle.y == ay && TmLastAngle.z == az)
		return TRUE;

	TmLastFrame = frame;
	TmLastAngle.x = ax;
	TmLastAngle.y = ay;
	TmLastAngle.z = az;


	for (cnt = 0; cnt < nObj3d; cnt++) {
		obj3d[TmSort[cnt]]->TmAnimation(frame, ax, ay, az, lpFrameInfo);
	}

	return TRUE;

}

//부모를 정하구 모든 오브젝트를 부모의 특정 오브젝트로 연결 시킨다
int smPAT3D::LinkParentObject(smPAT3D *patParent, smOBJ3D *objParent)
{
	int cnt;

	TmParent = patParent;

	//if ( objParent ) {
	for (cnt = 0; cnt < nObj3d; cnt++) {
		obj3d[cnt]->pParent = objParent;
	}
	//}

	return TRUE;

}
static char *szSMDFileHeader = "SMD Model data Ver 0.62";


int	smPAT3D::SaveFile(char *szFile)
{

	HANDLE	hFile;
	DWORD	dwAcess;
	int		cnt;
	int		pFile;
	int		size;

	smDFILE_HEADER	FileHeader;
	smDFILE_OBJINFO *FileObjInfo;


	lstrcpy(FileHeader.szHeader, szSMDFileHeader);

	if (smMaterialGroup)
		FileHeader.MatCounter = smMaterialGroup->MaterialCount;
	else
		FileHeader.MatCounter = 0;

	FileHeader.ObjCounter = nObj3d;


	FileObjInfo = new smDFILE_OBJINFO[nObj3d];

	//파일 포인터
	pFile = sizeof(smDFILE_HEADER) + sizeof(smDFILE_OBJINFO) * nObj3d;// + sizeof( smPAT3D );

	FileHeader.MatFilePoint = pFile;

	//메트리얼 데이타 저장 크기
	if (smMaterialGroup)
		pFile += smMaterialGroup->GetSaveSize();

	FileHeader.First_ObjInfoPoint = pFile;

	FileHeader.TmFrameCounter = TmFrameCnt;
	memcpy(FileHeader.TmFrame, TmFrame, sizeof(smFRAME_POS) * OBJ_FRAME_SEARCH_MAX);


	//포함한 OBJ포인터랑 정보 관련 블럭
	for (cnt = 0; cnt < nObj3d; cnt++) {
		lstrcpy(FileObjInfo[cnt].szNodeName, obj3d[cnt]->NodeName);
		size = obj3d[cnt]->GetSaveSize();
		FileObjInfo[cnt].ObjFilePoint = pFile;
		FileObjInfo[cnt].Length = size;

		pFile += size;
	}

	//파일로 저장
	hFile = CreateFile(szFile, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	//헤더 저장
	WriteFile(hFile, &FileHeader, sizeof(smDFILE_HEADER), &dwAcess, NULL);
	WriteFile(hFile, FileObjInfo, sizeof(smDFILE_OBJINFO) * nObj3d, &dwAcess, NULL);
	//WriteFile( hFile , &Head , sizeof( smPAT3D ), &dwAcess , NULL );

	//메트리얼 데이타 저장
	if (smMaterialGroup) smMaterialGroup->SaveFile(hFile);

	//오브젝트 데이타 저장
	for (cnt = 0; cnt < nObj3d; cnt++) {
		size = obj3d[cnt]->SaveFile(hFile);
		if (!size) {		//에러다!
			CloseHandle(hFile);
			delete FileObjInfo;
			return FALSE;
		}
	}

	//핸들 닫구 종료
	CloseHandle(hFile);
	delete FileObjInfo;

	return TRUE;
}
int	smPAT3D::LoadFile(char *szFile, char *szNodeName)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	int		cnt;
	int		size;
	smOBJ3D	*obj;
	smPAT3D *BipPat;

	smDFILE_HEADER	FileHeader;
	smDFILE_OBJINFO *FileObjInfo;

	Init();

	BipPat = smASE_GetPhysique();

	hFile = CreateFile(szFile, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	size = ReadFile(hFile, &FileHeader, sizeof(smDFILE_HEADER), &dwAcess, NULL);

	if (lstrcmp(FileHeader.szHeader, szSMDFileHeader) != 0)
	{
		CloseHandle(hFile);
		return FALSE;
	}

	FileObjInfo = new smDFILE_OBJINFO[FileHeader.ObjCounter];
	size = ReadFile(hFile, FileObjInfo, sizeof(smDFILE_OBJINFO) * FileHeader.ObjCounter, &dwAcess, NULL);

	TmFrameCnt = FileHeader.TmFrameCounter;
	memcpy(TmFrame, FileHeader.TmFrame, sizeof(smFRAME_POS) * OBJ_FRAME_SEARCH_MAX);

	if (FileHeader.MatCounter)
	{
		smMaterialGroup = new smMATERIAL_GROUP;
		smMaterialGroup->LoadFile(hFile);
	}

	if (szNodeName)
	{
		for (cnt = 0; cnt < FileHeader.ObjCounter; cnt++)
		{
			if (lstrcmpi(szNodeName, FileObjInfo[cnt].szNodeName) == 0)
			{
				obj = new smOBJ3D;
				if (obj)
				{
					SetFilePointer(hFile, FileObjInfo[cnt].ObjFilePoint, NULL, FILE_BEGIN);
					obj->LoadFile(hFile, BipPat);
					AddObject(obj);
				}
				break;
			}
		}
	}
	else
	{
		for (cnt = 0; cnt < FileHeader.ObjCounter; cnt++)
		{
			obj = new smOBJ3D;
			if (obj)
			{
				obj->LoadFile(hFile, BipPat);
				AddObject(obj);
			}
		}
		LinkObject();
	}

	TmParent = BipPat;

	CloseHandle(hFile);
	delete FileObjInfo;

	return TRUE;
}
int smFindPatFile(char *szfile, char *FileExt)
{
	HANDLE	hFile;
	DWORD	dwAcess;

	smDFILE_HEADER	FileHeader;

	char *szFileName = smFindFile(szfile, FileExt);
	if (szFileName)
	{
		hFile = CreateFile(szFileName, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(hFile, &FileHeader, sizeof(smDFILE_HEADER), &dwAcess, NULL);
		CloseHandle(hFile);

		if (lstrcmp(FileHeader.szHeader, szSMDFileHeader) != 0)
			return FALSE;

		return TRUE;
	}

	return FALSE;
}