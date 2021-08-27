#include "StdAfx.h"


smSTAGE_OBJECT::smSTAGE_OBJECT()
{
	int x, y;
	nObj = 0;

	for (y = 0; y < MAP_SIZE; y++) {
		for (x = 0; x < MAP_SIZE; x++) {
			ObjectMap[x][y] = 0;
		}
	}

	SumCnt = 0;
}

smSTAGE_OBJECT::~smSTAGE_OBJECT()
{
	int cnt;

	for (cnt = nObj - 1; cnt >= 0; cnt--) {
		if (mObj[cnt].Pattern) delete mObj[cnt].Pattern;
	}

}

int smSTAGE_OBJECT::AddObject(smPAT3D *Pat, int x, int y, int z, int angX, int angY, int angZ)
{
	int w, h;
	smSTAGE_OBJ3D *obj;

	if (nObj >= MAX_STAGEOBJ) return FALSE;

	mObj[nObj].Pattern = Pat;

	mObj[nObj].Posi.x = x;
	mObj[nObj].Posi.y = y;
	mObj[nObj].Posi.z = z;

	mObj[nObj].Angle.x = angX;
	mObj[nObj].Angle.y = angY;
	mObj[nObj].Angle.z = angZ;

	mObj[nObj].sum = 0;
	mObj[nObj].LinkObj = 0;
	mObj[nObj].LastDrawTime = GetCurrentTime();

	w = (x >> (6 + FLOATNS)) & 0xFF;
	h = (z >> (6 + FLOATNS)) & 0xFF;

	if (ObjectMap[w][h] == 0) {
		ObjectMap[w][h] = &mObj[nObj];
	}
	else {
		obj = ObjectMap[w][h];
		while (obj != 0) {
			if (obj->LinkObj == 0) break;
			obj = obj->LinkObj;
		}
		obj->LinkObj = &mObj[nObj];
	}

	nObj++;

	return TRUE;
}

//¿ÀºêÁ§Æ® »ðÀÔ ÀÚµ¿ÁÂÇ¥ ( ¸Ê¿¡ »ðÀÔµÈ ¿ÀºêÁ§Æ® )
int smSTAGE_OBJECT::AddObject(smPAT3D *Pat)
{
	int w, h;
	smSTAGE_OBJ3D *obj;
	int x, y, z;

	if (nObj >= MAX_STAGEOBJ) return FALSE;

	mObj[nObj].Pattern = Pat;

	x = Pat->obj3d[0]->Tm._41;
	y = Pat->obj3d[0]->Tm._43;
	z = Pat->obj3d[0]->Tm._42;

	mObj[nObj].Posi.x = x;
	mObj[nObj].Posi.y = y;
	mObj[nObj].Posi.z = z;

	mObj[nObj].Angle.x = 0;
	mObj[nObj].Angle.y = 0;
	mObj[nObj].Angle.z = 0;

	mObj[nObj].sum = 0;
	mObj[nObj].LinkObj = 0;
	mObj[nObj].LastDrawTime = GetCurrentTime();

	w = (x >> (6 + FLOATNS)) & 0xFF;
	h = (z >> (6 + FLOATNS)) & 0xFF;

	if (ObjectMap[w][h] == 0) {
		ObjectMap[w][h] = &mObj[nObj];
	}
	else {
		obj = ObjectMap[w][h];
		while (obj != 0) {
			if (obj->LinkObj == 0) break;
			obj = obj->LinkObj;
		}
		obj->LinkObj = &mObj[nObj];
	}

	nObj++;

	return TRUE;
}


//¿ÀºêÁ§Æ® »ðÀÔ ÀÚµ¿ÁÂÇ¥ ( ¸Ê¿¡ »ðÀÔµÈ ¿ÀºêÁ§Æ® )
int smSTAGE_OBJECT::AddObjectFile(char *szFile, char *szBipFile)
{
	int w, h;
	smSTAGE_OBJ3D *obj;
	smPAT3D *Pat;
	smPAT3D *BipPat;
	int x, y, z;

	if (nObj >= MAX_STAGEOBJ)
		return FALSE;

	if (szBipFile)
	{
		smASE_SetPhysique(0);

		BipPat = smASE_ReadBone(szBipFile);
		smASE_SetPhysique(BipPat);
		if (!BipPat) return FALSE;
	}
	else {
		smASE_SetPhysique(0);
		BipPat = 0;
	}

	Pat = smASE_Read(szFile);
	if (!Pat)
	{
		if (BipPat)
		{
			delete BipPat;
			BipPat = 0;
		}
		return FALSE;
	}

	mObj[nObj].Pattern = Pat;
	mObj[nObj].BipPattern = BipPat;

	x = Pat->obj3d[0]->Tm._41;
	y = Pat->obj3d[0]->Tm._43;
	z = Pat->obj3d[0]->Tm._42;

	mObj[nObj].Posi.x = x;
	mObj[nObj].Posi.y = y;
	mObj[nObj].Posi.z = z;

	mObj[nObj].Angle.x = 0;
	mObj[nObj].Angle.y = 0;
	mObj[nObj].Angle.z = 0;

	mObj[nObj].sum = 0;
	mObj[nObj].LinkObj = 0;
	mObj[nObj].LastDrawTime = GetCurrentTime();

	w = (x >> (6 + FLOATNS)) & 0xFF;
	h = (z >> (6 + FLOATNS)) & 0xFF;

	if (ObjectMap[w][h] == 0) {
		ObjectMap[w][h] = &mObj[nObj];
	}
	else {
		obj = ObjectMap[w][h];
		while (obj != 0) {
			if (obj->LinkObj == 0) break;
			obj = obj->LinkObj;
		}
		obj->LinkObj = &mObj[nObj];
	}

	nObj++;

	return TRUE;
}





int smSTAGE_OBJECT::Draw(smSTAGE_OBJ3D *mobj)
{
	return 0;

}


int smSTAGE_OBJECT::Draw(int x, int y, int z, int ax, int ay, int az)
{
	int h, w;
	int x1, x2, t;
	smSTAGE_OBJ3D *mobj;

	Camera.x = x;
	Camera.y = y;
	Camera.z = z;
	CameraAngle.x = ax;
	CameraAngle.y = ay;
	CameraAngle.z = az;

	for (h = MapPosiTop; h < MapPosiBot; h++) {
		x1 = MapPosiLeft[h & 0xFF];
		x2 = MapPosiRight[h & 0xFF];
		if (x1 > x2) { t = x1; x1 = x2; x2 = t; }  // x1<->x2 ¹Ù²Þ

		for (w = x1; w < x2; w++) {
			mobj = ObjectMap[w & 0xFF][h & 0xFF];
			if (mobj) {
				while (mobj != 0) {
					if (mobj->sum != SumCnt) Draw(mobj);
					mobj = mobj->LinkObj;
				}
			}
		}
	}

	SumCnt++;

	return TRUE;
}


int smSTAGE_OBJECT::Draw2(int x, int y, int z, int ax, int ay, int az)
{
	int h, w;
	int x1, x2, t;
	smSTAGE_OBJ3D *mobj;

	Camera.x = x;
	Camera.y = y;
	Camera.z = z;
	CameraAngle.x = ax;
	CameraAngle.y = ay;
	CameraAngle.z = az;

	CameraX = x >> FLOATNS;
	CameraY = y >> FLOATNS;
	CameraZ = z >> FLOATNS;

	CameraAngX = ax & ANGCLIP;
	CameraAngY = ay & ANGCLIP;
	CameraAngZ = az & ANGCLIP;

	SetViewLength();

	SetViewRadian();

	if (MakeMapTable()) {
		for (h = MapPosiTop; h < MapPosiBot; h++) {
			x1 = MapPosiLeft[h & 0xFF];
			x2 = MapPosiRight[h & 0xFF];
			if (x1 > x2) { t = x1; x1 = x2; x2 = t; }  // x1<->x2 ¹Ù²Þ

			for (w = x1; w < x2; w++) {
				mobj = ObjectMap[w & 0xFF][h & 0xFF];
				if (mobj) {
					while (mobj != 0) {
						if (mobj->sum != SumCnt) Draw(mobj);
						mobj = mobj->LinkObj;
					}
				}

			}

		}
	}
	SumCnt++;

	return TRUE;
}
int smSTAGE_OBJECT::DrawOpening(smSTAGE_OBJ3D *mobj, int FrameStep)
{
	return 0;
}


int smSTAGE_OBJECT::DrawOpening(int x, int y, int z, int ax, int ay, int az, int FrameStep)
{
	return TRUE;
}