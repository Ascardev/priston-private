#include "StdAfx.h"
#include "map.h"

void BaseMap::SetFileName(char * pszName, char * pszTitle)
{
#if defined(_GAME)
	STRINGFORMAT(szStageFilePath, "field\\%s", pszName);
#else
	STRINGFORMAT(szStageFilePath,  "%s", pszName);
#endif
	STRINGFORMAT(szMiniMapNameFilePath,  "field\\title\\%st.tga", pszTitle);
	STRINGFORMAT(szMiniMapFilePath,  "field\\map\\%s.tga", pszTitle);
}

void BaseMap::AddBorder(BaseMap * pcMap, int iX, int iZ, int iY)
{
	if (iBorderCount >= MAX_BORDERMAP)
		return;
	saFieldBorder[iBorderCount].iX = iX << 8;
	saFieldBorder[iBorderCount].iY = iY << 8;
	saFieldBorder[iBorderCount].iZ = iZ << 8;
	saFieldBorder[iBorderCount].pcMap = pcMap;
	iBorderCount++;

	if (pcMap->iBorderCount >= MAX_BORDERMAP)
		return;
	pcMap->saFieldBorder[pcMap->iBorderCount].iX = iX << 8;
	pcMap->saFieldBorder[pcMap->iBorderCount].iY = 0;
	pcMap->saFieldBorder[pcMap->iBorderCount].iZ = iZ << 8;
	pcMap->saFieldBorder[pcMap->iBorderCount].pcMap = this;
	pcMap->iBorderCount++;
}
void BaseMap::AddTeleport1(int iX, int iZ, int iY, int iSize, int iHeight, BaseMap * pcMap, int iXMap, int iZMap, int iYMap, int iLevel, int iWarpType)
{
	if (iWarpGateCount >= MAX_BORDERMAP)
		return;
	iWarpGateCurrent = iWarpGateCount;
	saWarpGate[iWarpGateCount].iX = iX << 8;
	saWarpGate[iWarpGateCount].iY = iY << 8;
	saWarpGate[iWarpGateCount].iZ = iZ << 8;
	saWarpGate[iWarpGateCount].iHeight = iHeight << 8;
	saWarpGate[iWarpGateCount].iSize = iSize << 8;
	saWarpGate[iWarpGateCurrent].iEffect = iWarpType;
	saWarpGate[iWarpGateCount].iLevel = iLevel;
	saWarpGate[iWarpGateCount].iOutFieldCount = 0;
	iWarpGateCount++;

	Teleport * psWarp = saWarpGate + iWarpGateCurrent;
	int iOut = psWarp->iOutFieldCount;

	if (psWarp->iOutFieldCount >= MAX_BORDERMAP)
		return;

	psWarp->saOutFieldBorder[iOut].pcMap = pcMap;
	psWarp->saOutFieldBorder[iOut].iX = iXMap << 8;
	psWarp->saOutFieldBorder[iOut].iY = iYMap << 8;
	psWarp->saOutFieldBorder[iOut].iZ = iZMap << 8;
	psWarp->iOutFieldCount++;

	if (pcMap == this)
	{
		sWarpGatePosition.iX = iXMap << 8;
		sWarpGatePosition.iY = iYMap << 8;
		sWarpGatePosition.iZ = iZMap << 8;
	}
}
void BaseMap::AddTeleport2(int iX, int iZ, int iY, int iSize, int iHeight, BaseMap * pcMap, int iXMap, int iZMap, int iYMap, int iXMap2, int iZMap2, int iYMap2, int iLevel, int iWarpType)
{
	if (iWarpGateCount >= MAX_BORDERMAP)
		return;

	iWarpGateCurrent = iWarpGateCount;
	saWarpGate[iWarpGateCount].iX = iX << 8;
	saWarpGate[iWarpGateCount].iY = iY << 8;
	saWarpGate[iWarpGateCount].iZ = iZ << 8;
	saWarpGate[iWarpGateCount].iHeight = iHeight << 8;
	saWarpGate[iWarpGateCount].iSize = iSize << 8;
	saWarpGate[iWarpGateCount].iEffect = iWarpType;
	saWarpGate[iWarpGateCount].iLevel = iLevel;
	iWarpGateCount++;

	Teleport * psWarp = saWarpGate + iWarpGateCurrent;
	int iOut = psWarp->iOutFieldCount;

	if (psWarp->iOutFieldCount >= MAX_BORDERMAP)
		return;

	psWarp->saOutFieldBorder[iOut].pcMap = pcMap;
	psWarp->saOutFieldBorder[iOut].iX = iXMap << 8;
	psWarp->saOutFieldBorder[iOut].iY = iYMap << 8;
	psWarp->saOutFieldBorder[iOut].iZ = iZMap << 8;
	psWarp->iOutFieldCount++;

	if (pcMap == this)
	{
		sWarpGatePosition.iX = iXMap << 8;
		sWarpGatePosition.iY = iYMap << 8;
		sWarpGatePosition.iZ = iZMap << 8;
	}

	iOut = psWarp->iOutFieldCount;

	if (psWarp->iOutFieldCount >= MAX_BORDERMAP)
		return;

	psWarp->saOutFieldBorder[iOut].pcMap = pcMap;
	psWarp->saOutFieldBorder[iOut].iX = iXMap2 << 8;
	psWarp->saOutFieldBorder[iOut].iY = iYMap2 << 8;
	psWarp->saOutFieldBorder[iOut].iZ = iZMap2 << 8;
	psWarp->iOutFieldCount++;
}
void BaseMap::AddSound(int iX, int iY, int iZ, int iRound, int iCode)
{
	if (iAmbientCount >= MAX_AMBIENTMAP)
		return;

	saAmbientPosition[iAmbientCount].iX = iX << 8;
	saAmbientPosition[iAmbientCount].iY = iY << 8;
	saAmbientPosition[iAmbientCount].iZ = iZ << 8;
	saAmbientPosition[iAmbientCount].iRound = iRound;
	saAmbientPosition[iAmbientCount].iNum = iCode;
	iAmbientCount++;
}
void BaseMap::AddStaticModel(char * pszName, int iAnimationBip)
{
	if (iObjectCount >= MAX_OBJECTMAP)
		return;

	STRINGFORMAT(szaObjectName[iObjectCount], "field\\%s", pszName);
	dwaObjectBip[iObjectCount] = iAnimationBip;
	iObjectCount++;
}
void BaseMap::AddModelEx(char * pszFormat, ...)
{
	if (iObjectCount >= MAX_OBJECTMAP)
		return;

	va_list vl;

	char szStr[128];

	va_start(vl, pszFormat);
	_vsnprintf_s(szStr, _countof(szStr), _TRUNCATE, pszFormat, vl);
	va_end(vl);

	STRINGFORMAT(szaObjectName[iObjectCount], "field\\%s", szStr);
	dwaObjectBip[iObjectCount] = 0;
	iObjectCount++;
}
void BaseMap::SetCamera(int iX, int iY, int iZ, int iLeftX, int iRightX)
{
#if defined(_GAME)
	sActionCamera.sPosition.iX = iX;
	sActionCamera.sPosition.iY = iY;
	sActionCamera.sPosition.iZ = iZ;
	sActionCamera.iLeftX = iLeftX;
	sActionCamera.iRightX = iRightX;
#endif
}
Point3D BaseMap::GetNearPostion(int iX, int iZ)
{
	if (iSpawnCount == 0)
	{
		return sPositionCenter;
	}
	
	int iNearDistance = Point3D(iX, 0, iZ).GetPTDistance(saSpawnPoint[0]);

	Point3D sPosition = saSpawnPoint[0];

	for (int i = 1; i < iSpawnCount; i++)
	{
		int iDistance = Point3D(iX, 0, iZ).GetPTDistance(saSpawnPoint[i]);

		if (iDistance < iNearDistance)
		{
			iNearDistance = iDistance;
			sPosition = saSpawnPoint[i];
		}
	}

	return sPosition;
}
Teleport * BaseMap::GetWarpGate(Point3D sPosition)
{
#if defined(_GAME)
	for (int i = 0; i < iWarpGateCount; i++)
	{
		Teleport * pWarpGate = saWarpGate + i;

		int iX = (pWarpGate->iX - sPosition.iX) >> 8;
		int iZ = (pWarpGate->iZ - sPosition.iZ) >> 8;
		int iY = pWarpGate->iY ? abs(pWarpGate->iY - sPosition.iY) : 0;

		int iSize = pWarpGate->iSize >> 8;

		int iDistance = iX * iX + iZ * iZ;

		if (pWarpGate->iLevel <= UNIT->sCharacterData.iLevel &&
			pWarpGate->iOutFieldCount &&
			abs(iX) < 1024 &&
			abs(iZ) < 1024 &&
			iDistance < iSize * iSize && iY < pWarpGate->iHeight)
		{
			return pWarpGate;
		}
	}

#endif

	return nullptr;
}
BaseMap * BaseMap::GetBorderMap(BaseMap * pcMap, Point3D sPosition)
{
	int iViewDistance = 0x120000;

	BaseMap * pcNearMap = nullptr;

	for (int i = 0; i < iBorderCount; i++)
	{
		MapBorder * pBorder = saFieldBorder + i;

		if (pBorder->pcMap != pcMap)
		{
			int iX = (sPosition.iX - pBorder->iX) >> 8;
			int iZ = (sPosition.iZ - pBorder->iZ) >> 8;

			int iDistance = iX * iX + iZ * iZ;

			if (iDistance < iViewDistance && abs(iX) < 16384 && abs(iZ) < 16384)
			{
				pcNearMap = pBorder->pcMap;
				iViewDistance = iDistance;
			}
		}
	}

	return pcNearMap;
}
BOOL BaseMap::IsStartPoint(int iX, int iZ)
{
	for (int i = 0; i < iSpawnCount; i++)
	{
		Point3D sPosition = saSpawnPoint[i];

		if (abs(sPosition.iX - iX) < 24 * 256 && abs(sPosition.iY - iZ) < 24 * 256)
			return TRUE;
	}

	return FALSE;
}
void BaseMap::PlayAmbient()
{
#if defined(_GAME)
	for (int i = 0; i < iAmbientCount; i++)
	{
		MapPosition * pAmbient = saAmbientPosition + i;

		esPlayObjectSound2(pAmbient->iNum, pAmbient->iRound, pAmbient->iX, pAmbient->iY, pAmbient->iZ);
	}

	if (ResetLastVolumeDist() > 800)
		esPlayObjectSound2(-1, 0, 0, 0, 0);

#endif
}
Map::Map()
{
	ZeroMemory(this, sizeof(Map));
}
void Map::Load(const char *pszFile)
{
	pcStage = new smSTAGE3D;
	smSTAGE3D_ReadASE((char *)pszFile, pcStage);
	pcStage->Head = TRUE;
}
void Map::Free()
{
	DELET(pcStage);
	DELET(pcBaseMap);
}