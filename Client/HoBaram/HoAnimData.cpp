#include "StdAfx.h"
HoAnimDataMgr	AnimDataMgr;


HoAnimSequenceData::HoAnimSequenceData()
{
	AnimFrameCount = 0;
	AnimFrame = NULL;
	DataFileIndex = -1;
	BlendType = 0;
	InfoFlag = 0;

}
HoAnimSequenceData::~HoAnimSequenceData()
{
	Init();
}
int HoAnimSequenceData::Load(char *iniName, HoAnimDataMgr *animationData)
{
	if (iniName == NULL || animationData == NULL)
		return FALSE;

	std::string str = GetPathFileName(iniName);

	STRINGCOPY(IniName, str.c_str());

	char buffer[512];

	GetPrivateProfileString("ANIMATION", "DataFile", NULL, buffer, sizeof(buffer), iniName);
	DataFileIndex = animationData->GetSearchAnimImageData(buffer);

	StartBlendValue = GetPrivateProfileInt("ANIMATION", "StartBlendValue", 0, iniName);
	BlendType = GetPrivateProfileInt("ANIMATION", "BlendType", 0, iniName);


	ZeroMemory(buffer, sizeof(buffer));
	GetPrivateProfileString("ANIMATION", "ImageNum", NULL, buffer, sizeof(buffer), iniName);
	if (strlen(buffer) == 0)
		return FALSE;
	int count = 0;
	int index = 0;
	for (index = 0; index < (int)strlen(buffer); index++)
	{
		if (buffer[index] == ',')
			count++;
	}
	AnimFrameCount = count + 1;
	AnimFrame = new hoAnimFrame[AnimFrameCount];
	memset(AnimFrame, 1, sizeof(hoAnimFrame)*AnimFrameCount);

	count = 0;
	int start = 0;
	int end = 0;
	char num[64];
	for (index = 0; index < (int)strlen(buffer); index++)
	{
		if (buffer[index] == ',')
		{
			memset(num, 0, sizeof(num));
			memcpy(num, &buffer[start], end - start);

			AnimFrame[count].ImageNum = (unsigned short)atoi(num);
			count++;
			start = index + 1;
			end = index + 1;
		}
		else if (index == (int)(strlen(buffer) - 1))
		{
			memset(num, 0, sizeof(num));
			memcpy(num, &buffer[start], end - start);
			AnimFrame[count].ImageNum = (unsigned short)atoi(num);
		}
		end++;
	}
	InfoFlag |= INFO_IMAGE;

	GetPrivateProfileString("ANIMATION", "Delay", NULL, buffer, sizeof(buffer), iniName);
	if (strlen(buffer) == 0)
		return FALSE;

	count = 0;
	start = 0;
	end = 0;

	for (index = 0; index < (int)strlen(buffer); index++)
	{
		if (buffer[index] == ',')
		{
			memset(num, 0, sizeof(num));
			memcpy(num, &buffer[start], end - start);

			AnimFrame[count].Delay = (unsigned short)atoi(num);
			count++;
			start = index + 1;
			end = index + 1;
		}
		else if (index == (int)(strlen(buffer) - 1))
		{
			memset(num, 0, sizeof(num));
			memcpy(num, &buffer[start], end - start);
			AnimFrame[count].Delay = (unsigned short)atoi(num);
		}
		end++;
	}
	InfoFlag |= INFO_DELAY;

	GetPrivateProfileString("ANIMATION", "BlendValue", NULL, buffer, sizeof(buffer), iniName);
	if (strlen(buffer) == 0)
		return FALSE;

	count = 0;
	start = 0;
	end = 0;
	for (index = 0; index < (int)strlen(buffer); index++)
	{
		if (buffer[index] == ',')
		{
			ZeroMemory(num, sizeof(num));
			memcpy(num, &buffer[start], end - start);

			AnimFrame[count].AlphaValue = (BYTE)atoi(num);
			count++;
			start = index + 1;
			end = index + 1;
		}
		else if (index == (int)(strlen(buffer) - 1))
		{
			ZeroMemory(num, sizeof(num));
			memcpy(num, &buffer[start], end - start);
			AnimFrame[count].AlphaValue = (BYTE)atoi(num);
		}
		end++;
	}
	InfoFlag |= INFO_ALPHA;

	ZeroMemory(buffer, sizeof(buffer));
	GetPrivateProfileString("ANIMATION", "Size", NULL, buffer, sizeof(buffer), iniName);
	if (strlen(buffer) == 0)
		return TRUE;

	count = 0;
	start = 0;
	end = 0;
	for (index = 0; index < (int)strlen(buffer); index++)
	{
		if (buffer[index] == ',')
		{
			ZeroMemory(num, sizeof(num));
			memcpy(num, &buffer[start], end - start);

			AnimFrame[count].SizeWidth = (unsigned short)atoi(num);
			count++;
			start = index + 1;
			end = index + 1;
		}
		else if (index == (int)(strlen(buffer) - 1))
		{
			ZeroMemory(num, sizeof(num));
			memcpy(num, &buffer[start], end - start);
			AnimFrame[count].SizeWidth = (unsigned short)atoi(num);
		}
		end++;
	}
	InfoFlag |= INFO_SIZEWIDTH;

	ZeroMemory(buffer, sizeof(buffer));
	GetPrivateProfileString("ANIMATION", "Angle", NULL, buffer, sizeof(buffer), iniName);
	if (strlen(buffer) == 0)
		return TRUE;

	count = 0;
	start = 0;
	end = 0;
	for (index = 0; index < (int)lstrlen(buffer); index++)
	{
		if (buffer[index] == ',')
		{
			ZeroMemory(num, sizeof(num));
			memcpy(num, &buffer[start], end - start);

			int t = atoi(num);
			AnimFrame[count].Angle = float(ANGLE_360*(float(atoi(num)) / 360.f));
			count++;
			start = index + 1;
			end = index + 1;
		}
		else if (index == (int)(strlen(buffer) - 1))
		{
			ZeroMemory(num, sizeof(num));
			memcpy(num, &buffer[start], end - start);
			AnimFrame[count].Angle = float(ANGLE_360*(float(atoi(num)) / 360.f));
		}
		end++;
	}
	InfoFlag |= INFO_ANGLE;

	return TRUE;
}

int HoAnimSequenceData::Init()
{
	InfoFlag = 0;
	if (AnimFrame != NULL)
	{
		delete[] AnimFrame;
		AnimFrame = NULL;
	}
	ZeroMemory(IniName, sizeof(IniName));

	return TRUE;
}

HoAnimImageData::HoAnimImageData()
{
	AnimationCount = 0;
	MaterialNum = -1;
}
HoAnimImageData::~HoAnimImageData()
{

}
int HoAnimImageData::Load(char *iniName)
{
	int  count = 0;
	for (int index = strlen(iniName); index > 0; index--)
	{
		if (iniName[index] == '\\')
		{
			memcpy(IniName, &iniName[index + 1], count - 1);
			break;
		}
		count++;
	}
	char dataName[512];
	int  dataCount = 0;

	GetPrivateProfileString("IMAGE", "Name", NULL, dataName, sizeof(dataName), iniName);
	dataCount = GetPrivateProfileInt("IMAGE", "Count", 0, iniName);
	Load(dataName, dataCount);

	return TRUE;
}

int HoAnimImageData::Load(char *textureName, int count)
{
	AnimationCount = count;

	char fileName[256];
	char fileExt[64];
	int cnt = 0;
	ZeroMemory(fileName, sizeof(fileName));
	ZeroMemory(fileExt, sizeof(fileExt));

	for (cnt = 0; cnt < lstrlen(textureName); cnt++)
	{
		if (textureName[cnt] == '.')
		{
			ZeroMemory(fileName, sizeof(fileName));
			memcpy(fileName, textureName, cnt);
			memcpy(fileExt, &textureName[cnt + 1], 3);
			break;
		}
	}

	char *szEffect[30];
	ZeroMemory(szEffect, sizeof(szEffect));

	for (cnt = 0; cnt < AnimationCount; cnt++)
	{
		szEffect[cnt] = new char[256];

		if (lstrcmpi(fileExt, "bmp") == 0)
			wsprintf(szEffect[cnt], "%s%d%s", fileName, cnt + 1, ".bmp");
		else if (lstrcmpi(fileExt, "tga") == 0)
			wsprintf(szEffect[cnt], "%s%d%s", fileName, cnt + 1, ".tga");
		else if (lstrcmpi(fileExt, "jpg") == 0)
			wsprintf(szEffect[cnt], "%s%d%s", fileName, cnt + 1, ".jpg");
		else if (lstrcmpi(fileExt, "png") == 0)
			wsprintf(szEffect[cnt], "%s%d%s", fileName, cnt + 1, ".png");
	}

	if (lstrcmpi(fileExt, "bmp") == 0 || lstrcmpi(fileExt, "jpg") == 0)
	{
		MaterialNum = CreateTextureMaterial(szEffect[0], 0, 0, 0, SMMAT_BLEND_COLOR);
		if (smMaterial[MaterialNum].smTexture == NULL)
		{
			for (int index = 0; index < AnimationCount; index++)
				DELET(szEffect[index]);
			return FALSE;
		}
		smMaterialGroup->ChangeMaterialToAnimation(&smMaterial[MaterialNum], szEffect, AnimationCount, SMMAT_BLEND_COLOR, FALSE);
	}
	else if (lstrcmpi(fileExt, "tga") == 0 || lstrcmpi(fileExt, "png") == 0)
	{
		MaterialNum = CreateTextureMaterial(szEffect[0], 0, 0, 0, SMMAT_BLEND_ALPHA);
		if (smMaterial[MaterialNum].smTexture == NULL)
		{
			for (int index = 0; index < AnimationCount; index++)
				DELET(szEffect[index]);

			return FALSE;
		}
		smMaterialGroup->ChangeMaterialToAnimation(&smMaterial[MaterialNum], szEffect, AnimationCount, SMMAT_BLEND_ALPHA, FALSE);
	}

	for (int index = 0; index < AnimationCount; index++)
		DELET(szEffect[index]);

	smMaterial[MaterialNum].TwoSide = TRUE;

	return TRUE;
}

int	HoAnimImageData::Init()
{
	ZeroMemory(IniName, sizeof(IniName));
	MaterialNum = 0;
	AnimationCount = 0;
	return TRUE;
}

HoAnimDataMgr::HoAnimDataMgr()
{
	Init();
}

HoAnimDataMgr::~HoAnimDataMgr()
{
	Init();
}
int HoAnimDataMgr::SequenceLoad(char *iniName)
{
	if (SequenceDataBufferCount < MAX_SEQUENCEDATA_BUFFER)
	{
		if (!SequenceDataBuffer[SequenceDataBufferCount].Load(iniName, this))
			return FALSE;

		SequenceDataBufferCount++;
		return TRUE;
	}
	return FALSE;
}
int HoAnimDataMgr::ImageLoad(char *iniName)
{
	if (ImageDataBufferCount < MAX_IMAGEDATA_BUFFER)
	{
		if (!ImageDataBuffer[ImageDataBufferCount].Load(iniName))
			return FALSE;
		ImageDataBufferCount++;
		return TRUE;
	}

	return FALSE;
}
int HoAnimDataMgr::Init()
{
	int index;

	for (index = 0; index < MAX_IMAGEDATA_BUFFER; index++)
		ImageDataBuffer[index].Init();

	for (index = 0; index < MAX_SEQUENCEDATA_BUFFER; index++)
		SequenceDataBuffer[index].Init();

	ImageDataBufferCount = 0;
	SequenceDataBufferCount = 0;

	return TRUE;
}
int HoAnimDataMgr::GetSearchSequenceData(char *iniName)
{
	for (int index = 0; index < SequenceDataBufferCount; index++)
	{
		if (lstrcmpi(SequenceDataBuffer[index].IniName, iniName) == 0)
			return index;
	}

	return -1;
}
int HoAnimDataMgr::GetSearchAnimImageData(char *iniName)
{
	for (int index = 0; index < ImageDataBufferCount; index++)
	{
		if (lstrcmpi(ImageDataBuffer[index].IniName, iniName) == 0)
			return index;
	}

	return -1;
}