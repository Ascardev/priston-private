#include "StdAfx.h"
#include "HoEffectView.h"
HoEffectView::HoEffectView()
{
}

HoEffectView::~HoEffectView()
{

}

#define FLOATS_EM				(FLOATNS+3)
#define SM_DIST_NEARZ			16
#define SMFLOAT_DIST_NEARZ		(SM_DIST_NEARZ<<FLOATNS)

static bool UpdateBillboardDefault(const SBillboardRenderInfo *renderInfo)
{
	int width, height;

	smRENDVERTEX *v[4];
	smRENDFACE	 *rf;
	short		sColor[4];

	sColor[SMC_R] = int(renderInfo->m_Color.r);
	sColor[SMC_G] = int(renderInfo->m_Color.g);
	sColor[SMC_B] = int(renderInfo->m_Color.b);
	sColor[SMC_A] = int(renderInfo->m_Color.a);

	auto sPosition = Point3D(int(renderInfo->m_Pos.x * 256.f), int(renderInfo->m_Pos.y * 256.f), int(renderInfo->m_Pos.z * 256.f));

	if (!smRender.GetCameraCoord(sPosition))
		return false;

	width = int(renderInfo->m_Size.x*256.f / 2.f);
	height = int(renderInfo->m_Size.y*256.f / 2.f);

	auto sAngle = Point3D((int)((renderInfo->m_Angle.x / 360.f)*4096.f), (int)((renderInfo->m_Angle.y / 360.f)*4096.f), (int)((renderInfo->m_Angle.z / 360.f)*4096.f)) & ANGCLIP;

	Point3D inVertex[4];

	auto sMatrix = Matrix4D().RotateX(sAngle.iX) * Matrix4D().RotateY(sAngle.iY) * Matrix4D().RotateZ(sAngle.iZ);

	inVertex[0] = (Point3D(-width, -height, 0) * sMatrix) + sPosition;
	inVertex[1] = (Point3D(+width, -height, 0) * sMatrix) + sPosition;
	inVertex[2] = (Point3D(-width, +height, 0) * sMatrix) + sPosition;
	inVertex[2] = (Point3D(+width, -height, 0) * sMatrix) + sPosition;

	v[0] = smRender.AddRendVertex(inVertex[0].iX, inVertex[0].iY, inVertex[0].iZ, sColor);
	v[1] = smRender.AddRendVertex(inVertex[1].iX, inVertex[1].iY, inVertex[1].iZ, sColor);
	v[2] = smRender.AddRendVertex(inVertex[2].iX, inVertex[2].iY, inVertex[2].iZ, sColor);
	v[3] = smRender.AddRendVertex(inVertex[3].iX, inVertex[3].iY, inVertex[3].iZ, sColor);

	//첫번째 폴리곤 ( 1 - 2 - 3 );
	rf = &smRender.RendFace[smRender.nRendFace++];
	rf->lpRendVertex[0] = v[0];
	rf->lpRendVertex[1] = v[1];
	rf->lpRendVertex[2] = v[2];
	rf->Matrial = renderInfo->m_MatID;		//메트리얼 복사
	rf->ClipStatus = v[0]->ClipStatus | v[1]->ClipStatus | v[2]->ClipStatus;
	rf->lpTexLink = 0;
	//텍스쳐 연결
	smRender.AddRendTempTexLink(rf, 0, 0, 1, 1, 1, 0, 0);

	//두번째 폴리곤 ( 2 - 4 - 3 );
	rf = &smRender.RendFace[smRender.nRendFace++];
	rf->lpRendVertex[0] = v[1];
	rf->lpRendVertex[1] = v[3];
	rf->lpRendVertex[2] = v[2];
	rf->Matrial = renderInfo->m_MatID;		//메트리얼 복사
	rf->ClipStatus = v[1]->ClipStatus | v[2]->ClipStatus | v[3]->ClipStatus;
	rf->lpTexLink = 0;
	//텍스쳐 연결
	smRender.AddRendTempTexLink(rf, 0, 1, 1, 1, 0, 0, 0);

	return true;
}
static bool UpdateBillboardAxial(const SBillboardRenderInfo *renderInfo)
{
	auto sc = Point3D(int(renderInfo->m_Pos.x * 256.f), int(renderInfo->m_Pos.y * 256.f), int(renderInfo->m_Pos.z * 256.f));
	auto sd = Point3D(int(renderInfo->m_DesPos.x * 256.f), int(renderInfo->m_DesPos.y * 256.f), int(renderInfo->m_DesPos.z * 256.f));

	if (!smRender.GetCameraCoord(sc))
		return false;

	if (!smRender.GetCameraCoord(sd))
		return true;

	smRENDVERTEX *v[4];
	smRENDFACE	 *rf;
	short		sColor[4];

	sColor[SMC_R] = int(renderInfo->m_Color.r);
	sColor[SMC_G] = int(renderInfo->m_Color.g);
	sColor[SMC_B] = int(renderInfo->m_Color.b);
	sColor[SMC_A] = int(renderInfo->m_Color.a);

	smTEXRECT texRect;
	texRect.left = 0;
	texRect.top = 0;
	texRect.right = 1;
	texRect.bottom = 1;

	float dx = float(sd.iX - sc.iX); //대상 까지의 x축의 기울기를 구한다.
	float dy = float(sd.iY - sc.iY); //대상 까지의 y축의 기울기를 구한다.
	float length = (float)sqrt(dx*dx + dy * dy);        //대상 까지의 거리를 구한다.

	dx = dx / length * renderInfo->m_Size.x*256.f; //날아가는 파티클의 넓이..
	dy = dy / length * renderInfo->m_Size.x*256.f;

	D3DVECTOR persp;
	persp.x = -dy;
	persp.y = +dx;
	persp.z = 0;

	if (abs((int)dx) > 1.0f) sc.iX -= (int)dx;
	if (abs((int)dy) > 1.0f) sc.iY -= (int)dy;
	v[0] = smRender.AddRendVertex(int(sd.iX - persp.x), int(sd.iY - persp.y), int(sd.iZ), sColor);
	v[1] = smRender.AddRendVertex(int(sd.iX + persp.x), int(sd.iY + persp.y), int(sd.iZ), sColor);
	v[2] = smRender.AddRendVertex(int(sc.iX - persp.x), int(sc.iY - persp.y), int(sc.iZ), sColor);
	v[3] = smRender.AddRendVertex(int(sc.iX + persp.x), int(sc.iY + persp.y), int(sc.iZ), sColor);

	//첫번째 폴리곤 ( 1 - 2 - 3 );
	rf = &smRender.RendFace[smRender.nRendFace++];
	rf->lpRendVertex[0] = v[0];
	rf->lpRendVertex[1] = v[1];
	rf->lpRendVertex[2] = v[2];
	rf->Matrial = renderInfo->m_MatID;		//메트리얼 복사
	rf->ClipStatus = v[0]->ClipStatus | v[1]->ClipStatus | v[2]->ClipStatus;
	rf->lpTexLink = 0;

	//텍스쳐 연결
	smRender.AddRendTempTexLink(rf, 0, texRect.left, texRect.bottom,
		texRect.right, texRect.bottom,
		texRect.left, texRect.top);


	//두번째 폴리곤 ( 2 - 4 - 3 );
	rf = &smRender.RendFace[smRender.nRendFace++];
	rf->lpRendVertex[0] = v[1];
	rf->lpRendVertex[1] = v[3];
	rf->lpRendVertex[2] = v[2];
	rf->Matrial = renderInfo->m_MatID;		//메트리얼 복사
	rf->ClipStatus = v[1]->ClipStatus | v[2]->ClipStatus | v[3]->ClipStatus;
	rf->lpTexLink = 0;

	//텍스쳐 연결
	smRender.AddRendTempTexLink(rf, 0, texRect.right, texRect.bottom,
		texRect.right, texRect.top,
		texRect.left, texRect.top);

	return true;
}

static bool UpdateCreateMesh(const SBillboardRenderInfo *renderInfo)
{
	int width, height;

	smRENDVERTEX *v[4];
	smRENDFACE	 *rf;
	short		sColor[4];

	sColor[SMC_R] = int(renderInfo->m_Color.r);
	sColor[SMC_G] = int(renderInfo->m_Color.g);
	sColor[SMC_B] = int(renderInfo->m_Color.b);
	sColor[SMC_A] = int(renderInfo->m_Color.a);

	Point3D inVertex[4];

	width = int(renderInfo->m_Size.x*256.f / 2.f);
	height = int(renderInfo->m_Size.y*256.f / 2.f);

	auto sPosition = Point3D(int(renderInfo->m_Pos.x * 256.f), int(renderInfo->m_Pos.y * 256.f), int(renderInfo->m_Pos.z * 256.f));
	auto sAngle = Point3D((int)(renderInfo->m_Angle.x), (int)(renderInfo->m_Angle.y), (int)(renderInfo->m_Angle.z)) & ANGCLIP;

	auto sMatrix = Matrix4D().RotateX(sAngle.iX) * Matrix4D().RotateY(sAngle.iY) * Matrix4D().RotateZ(sAngle.iZ);

	inVertex[0] = (Point3D(-width, 0, +height) * sMatrix) + sPosition;
	inVertex[1] = (Point3D(+width, 0, +height) * sMatrix) + sPosition;
	inVertex[2] = (Point3D(-width, 0, -height) * sMatrix) + sPosition;
	inVertex[3] = (Point3D(+width, 0, -height) * sMatrix) + sPosition;

	if (!smRender.GetCameraCoord(inVertex[0])) return false;
	if (!smRender.GetCameraCoord(inVertex[1])) return false;
	if (!smRender.GetCameraCoord(inVertex[2])) return false;
	if (!smRender.GetCameraCoord(inVertex[3])) return false;


	//렌더링 버텍스 추가 ( 좌표 직접 입력 )
	v[0] = smRender.AddRendVertex(inVertex[0].iX, inVertex[0].iY, inVertex[0].iZ, sColor);
	v[1] = smRender.AddRendVertex(inVertex[1].iX, inVertex[1].iY, inVertex[1].iZ, sColor);
	v[2] = smRender.AddRendVertex(inVertex[2].iX, inVertex[2].iY, inVertex[2].iZ, sColor);
	v[3] = smRender.AddRendVertex(inVertex[3].iX, inVertex[3].iY, inVertex[3].iZ, sColor);

	//첫번째 폴리곤 ( 1 - 2 - 3 );
	rf = &smRender.RendFace[smRender.nRendFace++];
	rf->lpRendVertex[0] = v[0];
	rf->lpRendVertex[1] = v[1];
	rf->lpRendVertex[2] = v[2];
	rf->Matrial = renderInfo->m_MatID;		//메트리얼 복사
	rf->ClipStatus = v[0]->ClipStatus | v[1]->ClipStatus | v[2]->ClipStatus;
	rf->lpTexLink = 0;

	//텍스쳐 연결
	smRender.AddRendTempTexLink(rf, 0, 0, 1, 1, 1, 0, 0);


	//두번째 폴리곤 ( 2 - 4 - 3 );
	rf = &smRender.RendFace[smRender.nRendFace++];
	rf->lpRendVertex[0] = v[1];
	rf->lpRendVertex[1] = v[3];
	rf->lpRendVertex[2] = v[2];
	rf->Matrial = renderInfo->m_MatID;		//메트리얼 복사
	rf->ClipStatus = v[1]->ClipStatus | v[2]->ClipStatus | v[3]->ClipStatus;
	rf->lpTexLink = 0;

	//텍스쳐 연결
	smRender.AddRendTempTexLink(rf, 0, 1, 1, 1, 0, 0, 0);
	return true;
}

bool HoEffectView::UpdateBillboard(const SBillboardRenderInfo *renderInfo, int iX, int iY, int iZ, int aX, int aY, int aZ)
{
	if (renderInfo == NULL)
		return false;
	smRender.Init();
	smRender.SetMaterialGroup(smMaterialGroup);
	smRender.SetCameraPosi(iX, iY, iZ, aX, aY, aZ);
	smMaterialGroup->smMaterial[renderInfo->m_MatID].TwoSide = TRUE;

	smMaterial[renderInfo->m_MatID].BlendType = renderInfo->m_iBlendType;
	if (renderInfo->m_Type == BILLBOARD_DEFAULT)
		UpdateBillboardDefault(renderInfo);
	else if (renderInfo->m_Type == BILLBOARD_AXIAL)
		UpdateBillboardAxial(renderInfo);
	else if (renderInfo->m_Type == CREATE_MESH)
		UpdateCreateMesh(renderInfo);

	smRender.SetClipStates(SMCLIP_LEFT | SMCLIP_RIGHT | SMCLIP_TOP | SMCLIP_BOTTOM);
	smRender.ClipRendFace();
	smRender.GeomVertex2D(FALSE);
	smRender.RenderD3D();


	return true;
}

bool HoEffectView::UpdateLineList(const SLineListRenderInfo *renderInfo, int iX, int iY, int iZ, int aX, int aY, int aZ)
{
	if (renderInfo == NULL)
		return false;
	if (renderInfo->m_pList == NULL)
		return false;

	assert(renderInfo);
	smRender.Init();
	smRender.SetMaterialGroup(smMaterialGroup);
	smRender.SetCameraPosi(iX, iY, iZ, aX, aY, aZ);
	smMaterialGroup->smMaterial[renderInfo->m_MatID].TwoSide = TRUE;
	smMaterial[renderInfo->m_MatID].BlendType = renderInfo->m_iBlendType;

	if (renderInfo->m_pList->size() < 2)
		return false;

	std::list<point3>::iterator iter;
	iter = renderInfo->m_pList->begin();

	auto sd = Point3D((int)iter->x * 256, (int)iter->y * 256, (int)iter->z * 256);

	int texSizeCount = 0;
	int test = renderInfo->m_pList->size();
	float cellSize = 1.f / (renderInfo->m_pList->size() - 1);
	++iter;
	POINT3D OldVertex[2];
	memset(OldVertex, 0, sizeof(OldVertex));

	for (; iter != renderInfo->m_pList->end(); iter++)
	{
		auto sc = Point3D((int)iter->x * 256, (int)iter->y * 256, (int)iter->z * 256);

		if (!smRender.GetCameraCoord(sc))
			return false;
		if (!smRender.GetCameraCoord(sd))
			return true;

		smRENDVERTEX *v[4];
		smRENDFACE	 *rf;

		short		sColor[4];

		sColor[SMC_R] = int(renderInfo->m_Color.r);
		sColor[SMC_G] = int(renderInfo->m_Color.g);
		sColor[SMC_B] = int(renderInfo->m_Color.b);
		sColor[SMC_A] = int(renderInfo->m_Color.a);

		smTEXRECT texRect;
		texRect.left = 0;
		texRect.top = (float)texSizeCount*cellSize;
		texRect.right = 1;
		texRect.bottom = (float)(texSizeCount + 1)*cellSize;

		float dx = float(sd.iX - sc.iX); //대상 까지의 x축의 기울기를 구한다.
		float dy = float(sd.iY - sc.iY); //대상 까지의 y축의 기울기를 구한다.
		float length = (float)sqrt(dx*dx + dy * dy);        //대상 까지의 거리를 구한다.

		if (length == 0)
			length = 1;

		dx = dx / length * renderInfo->m_Size.x*256.f;; //날아가는 파티클의 넓이..
		dy = dy / length * renderInfo->m_Size.x*256.f;;

		D3DVECTOR persp;
		persp.x = -dy;
		persp.y = +dx;
		persp.z = 0;

		if (texSizeCount == 0)
		{
			v[0] = smRender.AddRendVertex(int(sd.iX - persp.x), int(sd.iY - persp.y), int(sd.iZ), sColor);
			v[1] = smRender.AddRendVertex(int(sd.iX + persp.x), int(sd.iY + persp.y), int(sd.iZ), sColor);
		}
		else
		{
			v[0] = smRender.AddRendVertex(OldVertex[0].x, OldVertex[0].y, OldVertex[0].z, sColor);
			v[1] = smRender.AddRendVertex(OldVertex[1].x, OldVertex[1].y, OldVertex[1].z, sColor);
		}

		OldVertex[0].x = int(sc.iX - persp.x);
		OldVertex[0].y = int(sc.iY - persp.y);
		OldVertex[0].z = int(sc.iZ);

		OldVertex[1].x = int(sc.iX + persp.x);
		OldVertex[1].y = int(sc.iY + persp.y);
		OldVertex[1].z = int(sc.iZ);

		sd = Point3D(int(iter->x) * 256, int(iter->y) * 256, int(iter->z) * 256);

		v[2] = smRender.AddRendVertex(int(sc.iX - persp.x), int(sc.iY - persp.y), int(sc.iZ), sColor);
		v[3] = smRender.AddRendVertex(int(sc.iX + persp.x), int(sc.iY + persp.y), int(sc.iZ), sColor);

		//첫번째 폴리곤 ( 1 - 2 - 3 );
		rf = &smRender.RendFace[smRender.nRendFace++];
		rf->lpRendVertex[0] = v[0];
		rf->lpRendVertex[1] = v[1];
		rf->lpRendVertex[2] = v[2];
		rf->Matrial = renderInfo->m_MatID;		//메트리얼 복사
		rf->ClipStatus = v[0]->ClipStatus | v[1]->ClipStatus | v[2]->ClipStatus;
		rf->lpTexLink = 0;

		//텍스쳐 연결
		smRender.AddRendTempTexLink(rf, 0, texRect.left, texRect.top,
			texRect.right, texRect.top,
			texRect.left, texRect.bottom);


		//두번째 폴리곤 ( 2 - 4 - 3 );
		rf = &smRender.RendFace[smRender.nRendFace++];
		rf->lpRendVertex[0] = v[1];
		rf->lpRendVertex[1] = v[3];
		rf->lpRendVertex[2] = v[2];
		rf->Matrial = renderInfo->m_MatID;		//메트리얼 복사
		rf->ClipStatus = v[1]->ClipStatus | v[2]->ClipStatus | v[3]->ClipStatus;
		rf->lpTexLink = 0;

		//텍스쳐 연결
		smRender.AddRendTempTexLink(rf, 0, texRect.right, texRect.top,
			texRect.right, texRect.bottom,
			texRect.left, texRect.bottom);

		texSizeCount++;
	}

	smRender.SetClipStates(SMCLIP_LEFT | SMCLIP_RIGHT | SMCLIP_TOP | SMCLIP_BOTTOM);
	smRender.ClipRendFace();
	smRender.GeomVertex2D(FALSE);
	smRender.RenderD3D();

	return true;
}

bool HoEffectView::UpdateMesh(const SMeshRenderInfo *renderInfo, int iX, int iY, int iZ, int aX, int aY, int aZ)
{
	if (renderInfo == NULL)
		return false;
	assert(renderInfo);
	assert(renderInfo->m_Pat);
	renderInfo->m_Pat->Frame = renderInfo->m_iCurrentFrame;
	if (renderInfo->m_Pat->smMaterialGroup)
	{
		int matCount = renderInfo->m_Pat->smMaterialGroup->MaterialCount;
		for (int i = 0; i < matCount; i++)
			renderInfo->m_Pat->smMaterialGroup->smMaterial[i].BlendType = renderInfo->m_iBlendType;
	}

	POINT3D pos;
	POINT3D angle;

	POINT3D cameraPos;
	POINT3D cameraAngle;

	pos.x = (int)(renderInfo->m_Pos.x * 256.f);
	pos.y = (int)(renderInfo->m_Pos.y * 256.f);
	pos.z = (int)(renderInfo->m_Pos.z * 256.f);

	angle.x = int(renderInfo->m_Angle.x);
	angle.y = int(renderInfo->m_Angle.y);
	angle.z = int(renderInfo->m_Angle.z);

	cameraPos.x = iX;
	cameraPos.y = iY;
	cameraPos.z = iZ;

	cameraAngle.x = aX;
	cameraAngle.y = aY;
	cameraAngle.z = aZ;

	int oldR, oldG, oldB, oldA;
	oldR = smRender.Color_R;
	oldG = smRender.Color_G;
	oldB = smRender.Color_B;
	oldA = smRender.Color_A;

	smRender.Color_R = (int)(renderInfo->m_Color.r - 255.f);
	smRender.Color_G = (int)(renderInfo->m_Color.g - 255.f);
	smRender.Color_B = (int)(renderInfo->m_Color.b - 255.f);
	smRender.Color_A = (int)(renderInfo->m_Color.a - 255.f);

	renderInfo->m_Pat->SetPosi(&pos, &angle);
	renderInfo->m_Pat->RenderD3D(&cameraPos, &cameraAngle);

	smRender.Color_R = oldR;
	smRender.Color_G = oldG;
	smRender.Color_B = oldB;
	smRender.Color_A = oldA;

	return true;
}