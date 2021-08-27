#include "StdAfx.h"

#define ERROR_LIST_MAX		256
#define ERROR_LIST_MASK		(ERROR_LIST_MAX-1)


DWORD	VramTotal = 0;

#define	MAX_MAP_BLINK_COLOR_TIME	8

const char *szBlinkTimeScript[MAX_MAP_BLINK_COLOR_TIME] =
{
	"BLINK_TIME1:",
	"BLINK_TIME2:",
	"BLINK_TIME3:",
	"BLINK_TIME4:",
	"BLINK_TIME5:",
	"BLINK_TIME6:",
	"BLINK_TIME7:",
	"BLINK_TIME8:",
};

const DWORD dwBlinkTimeCode[MAX_MAP_BLINK_COLOR_TIME] =
{
	9, 10, 11, 12, 13, 14, 15, 16,
};

int		   MaterialFrame;









smMATERIAL_GROUP::smMATERIAL_GROUP()
{
	MaterialCount = 0;
}

smMATERIAL_GROUP::smMATERIAL_GROUP(int MaterialMax)
{
	Init(MaterialMax);
}

smMATERIAL_GROUP::~smMATERIAL_GROUP()
{
	Close();
}

void smMATERIAL_GROUP::Init(int MaterialMax)
{

	MaterialCount = 0;
	MaxMaterial = MaterialMax;
	ReformTexture = 0;

	smMaterial = new smMATERIAL[MaterialMax];
	ZeroMemory(smMaterial, sizeof(smMATERIAL)*MaterialMax);

}
int smMATERIAL_GROUP::Close()
{
	DWORD cnt, tcnt;

	for (cnt = 0; cnt < MaterialCount; cnt++)
	{
		if (smMaterial[cnt].InUse)
		{
			for (tcnt = 0; tcnt < smMaterial[cnt].TextureCounter; tcnt++)
			{
				
			}

			for (tcnt = 0; tcnt < smMaterial[cnt].AnimTexCounter; tcnt++)
			{
				
			}
		}
	}

	DELETA(smMaterial);

	return TRUE;
}

#define TEXFILENAME_SIZE	64

int smMATERIAL_GROUP::GetSaveSize()
{
	int size;
	DWORD cnt, tcnt;
	int	len, alen;

	size = sizeof(smMATERIAL_GROUP);

	for (cnt = 0; cnt < MaterialCount; cnt++)
	{
		size += sizeof(smMATERIAL);
		if (smMaterial[cnt].InUse)
		{
			size += sizeof(int);

			for (tcnt = 0; tcnt < smMaterial[cnt].TextureCounter; tcnt++)
			{
				len = lstrlen(smMaterial[cnt].smTexture[tcnt]->Name) + 1;
				alen = lstrlen(smMaterial[cnt].smTexture[tcnt]->NameA) + 1;
				size += len;
				size += alen;
			}

			for (tcnt = 0; tcnt < smMaterial[cnt].AnimTexCounter; tcnt++)
			{
				len = lstrlen(smMaterial[cnt].smAnimTexture[tcnt]->Name) + 1;
				alen = lstrlen(smMaterial[cnt].smAnimTexture[tcnt]->NameA) + 1;
				size += len;
				size += alen;
			}
		}
	}
	return size;
}
int smMATERIAL_GROUP::SaveFile(HANDLE hFile)
{
	DWORD	dwAcess;
	DWORD cnt, tcnt;
	int	len;
	int size;

	size = WriteFile(hFile, &Head, sizeof(smMATERIAL_GROUP), &dwAcess, NULL);

	for (cnt = 0; cnt < MaterialCount; cnt++)
	{
		size += WriteFile(hFile, &smMaterial[cnt], sizeof(smMATERIAL), &dwAcess, NULL);

		if (smMaterial[cnt].InUse)
		{
			len = 0;

			for (tcnt = 0; tcnt < smMaterial[cnt].TextureCounter; tcnt++)
			{
				len += lstrlen(smMaterial[cnt].smTexture[tcnt]->Name) + 1;
				len += lstrlen(smMaterial[cnt].smTexture[tcnt]->NameA) + 1;
			}
			for (tcnt = 0; tcnt < smMaterial[cnt].AnimTexCounter; tcnt++)
			{
				len += lstrlen(smMaterial[cnt].smAnimTexture[tcnt]->Name) + 1;
				len += lstrlen(smMaterial[cnt].smAnimTexture[tcnt]->NameA) + 1;
			}
			size += WriteFile(hFile, &len, sizeof(int), &dwAcess, NULL);

			for (tcnt = 0; tcnt < smMaterial[cnt].TextureCounter; tcnt++)
			{
				len = lstrlen(smMaterial[cnt].smTexture[tcnt]->Name) + 1;
				size += WriteFile(hFile, smMaterial[cnt].smTexture[tcnt]->Name, len, &dwAcess, NULL);
				len = lstrlen(smMaterial[cnt].smTexture[tcnt]->NameA) + 1;
				size += WriteFile(hFile, smMaterial[cnt].smTexture[tcnt]->NameA, len, &dwAcess, NULL);
			}

			for (tcnt = 0; tcnt < smMaterial[cnt].AnimTexCounter; tcnt++)
			{
				len = lstrlen(smMaterial[cnt].smAnimTexture[tcnt]->Name) + 1;
				size += WriteFile(hFile, smMaterial[cnt].smAnimTexture[tcnt]->Name, len, &dwAcess, NULL);
				len = lstrlen(smMaterial[cnt].smAnimTexture[tcnt]->NameA) + 1;
				size += WriteFile(hFile, smMaterial[cnt].smAnimTexture[tcnt]->NameA, len, &dwAcess, NULL);
			}
		}
	}

	return size;
}
int smMATERIAL_GROUP::LoadFile(HANDLE hFile)
{
	DWORD	dwAcess;
	DWORD	cnt, tcnt;
	int		StrLen;
	int		size;
	char	szNameBuff[4096];
	char	*lpNameBuff = NULL;
	char	*szName, *szNameA;

	ZeroMemory(szNameBuff, sizeof(szNameBuff));

	size = ReadFile(hFile, &Head, sizeof(smMATERIAL_GROUP), &dwAcess, NULL);

	smMaterial = new smMATERIAL[MaterialCount];

	for (cnt = 0; cnt < MaterialCount; cnt++)
	{
		size += ReadFile(hFile, &smMaterial[cnt], sizeof(smMATERIAL), &dwAcess, NULL);

		if (smMaterial[cnt].InUse)
		{
			size += ReadFile(hFile, &StrLen, sizeof(int), &dwAcess, NULL);

			size += ReadFile(hFile, szNameBuff, StrLen, &dwAcess, NULL);

			lpNameBuff = szNameBuff;

			for (tcnt = 0; tcnt < smMaterial[cnt].TextureCounter; tcnt++)
			{
				szName = lpNameBuff;
				lpNameBuff += lstrlen(szName) + 1;
				szNameA = lpNameBuff;
				lpNameBuff += lstrlen(szNameA) + 1;
			}
			for (tcnt = 0; tcnt < smMaterial[cnt].AnimTexCounter; tcnt++)
			{
				szName = lpNameBuff;
				lpNameBuff += lstrlen(szName) + 1;
				szNameA = lpNameBuff;
				lpNameBuff += lstrlen(szNameA) + 1;
			}
		}
	}

	return size;
}
int smMATERIAL_GROUP::DeleteUnuseMaterial()
{
	DWORD cnt, dcnt;

	dcnt = 0;
	for (cnt = 0; cnt < MaterialCount; cnt++)
	{
		if (smMaterial[cnt].InUse == TRUE)
		{
			
			ZeroMemory(&smMaterial[cnt], sizeof(smMATERIAL));
			dcnt++;
		}
	}

	return dcnt;
}

int smMATERIAL_GROUP::AddMaterial(ASE_MATERIAL *aseMaterial, char *szScript)
{
	int cnt, len;
	int	AnimCount, FrameSpeed;
	int MatNum;
	char	*lpAnimFileList[16];
	char	*szDirectory;
	char	*lpScript;
	char	szTemp[64];

	MatNum = MaterialCount;
	MaterialCount++;

	smMaterial[MatNum].InUse = TRUE;
	smMaterial[MatNum].Shade = TRUE;
	smMaterial[MatNum].BlendType = SMMAT_BLEND_ALPHA;
	smMaterial[MatNum].TwoSide = aseMaterial->TwoSide;
	smMaterial[MatNum].ReformTexture = 0;

	if (!aseMaterial->MAP_OPACITY[0])
	{
		for (cnt = 0; cnt < aseMaterial->TextureCounter; cnt++)
		{
			smMaterial[MatNum].TextureStageState[cnt] = aseMaterial->BitmapStateState[cnt];
			smMaterial[MatNum].TextureFormState[cnt] = aseMaterial->BitmapFormState[cnt];
			smMaterial[MatNum].ReformTexture += aseMaterial->BitmapFormState[cnt];
		}
		smMaterial[MatNum].MapOpacity = FALSE;
	}
	else
	{
		if (aseMaterial->TextureCounter > 1)
		{
			for (cnt = 0; cnt < aseMaterial->TextureCounter - 1; cnt++)
			{
				smMaterial[MatNum].TextureStageState[cnt] = aseMaterial->BitmapStateState[cnt];
				smMaterial[MatNum].TextureFormState[cnt] = aseMaterial->BitmapFormState[cnt];
				smMaterial[MatNum].ReformTexture += aseMaterial->BitmapFormState[cnt];
			}

			smMaterial[MatNum].TextureStageState[cnt] = aseMaterial->BitmapStateState[cnt];
			smMaterial[MatNum].TextureFormState[cnt] = aseMaterial->BitmapFormState[cnt];
			smMaterial[MatNum].ReformTexture += aseMaterial->BitmapFormState[cnt];
		}
		else
		{
			for (cnt = 0; cnt < aseMaterial->TextureCounter; cnt++)
			{
				smMaterial[MatNum].TextureStageState[cnt] = aseMaterial->BitmapStateState[cnt];
				smMaterial[MatNum].TextureFormState[cnt] = aseMaterial->BitmapFormState[cnt];
				smMaterial[MatNum].ReformTexture += aseMaterial->BitmapFormState[cnt];
			}
		}

		smMaterial[MatNum].MapOpacity = TRUE;
	}

	if (smMaterial[MatNum].ReformTexture)
		ReformTexture++;

	smMaterial[MatNum].TextureCounter = aseMaterial->TextureCounter;
	smMaterial[MatNum].Transparency = aseMaterial->Transparency;
	smMaterial[MatNum].SelfIllum = aseMaterial->SelfIllum;
	smMaterial[MatNum].Diffuse = aseMaterial->Diffuse;

	smMaterial[MatNum].UseState = aseMaterial->ScriptState;
	smMaterial[MatNum].TextureType = SMTEX_TYPE_MULTIMIX;

	if (aseMaterial->BlendType)
		smMaterial[MatNum].BlendType = aseMaterial->BlendType;

	if (smMaterial[MatNum].Transparency == 0)
		smMaterial[MatNum].MeshState = SMMAT_STAT_CHECK_FACE;

	if ((aseMaterial->ScriptState&sMATS_SCRIPT_WIND))
	{
		smMaterial[MatNum].WindMeshBottom = sMATS_SCRIPT_WINDZ1;
		smMaterial[MatNum].MeshState = 0;
	}
	if ((aseMaterial->ScriptState&sMATS_SCRIPT_WINDX1))
	{
		smMaterial[MatNum].WindMeshBottom = sMATS_SCRIPT_WINDX1;
		smMaterial[MatNum].MeshState = 0;
	}
	if ((aseMaterial->ScriptState&sMATS_SCRIPT_WINDX2))
	{
		smMaterial[MatNum].WindMeshBottom = sMATS_SCRIPT_WINDX2;
		smMaterial[MatNum].MeshState = 0;
	}
	if ((aseMaterial->ScriptState&sMATS_SCRIPT_WINDZ1))
	{
		smMaterial[MatNum].WindMeshBottom = sMATS_SCRIPT_WINDZ1;
		smMaterial[MatNum].MeshState = 0;
	}
	if ((aseMaterial->ScriptState&sMATS_SCRIPT_WINDZ2))
	{
		smMaterial[MatNum].WindMeshBottom = sMATS_SCRIPT_WINDZ2;
		smMaterial[MatNum].MeshState = 0;
	}

	if ((aseMaterial->ScriptState&sMATS_SCRIPT_WINDZ2))
	{
		smMaterial[MatNum].WindMeshBottom = sMATS_SCRIPT_WINDZ2;
		smMaterial[MatNum].MeshState = 0;
	}

	if ((aseMaterial->ScriptState&sMATS_SCRIPT_WATER))
	{
		smMaterial[MatNum].WindMeshBottom = sMATS_SCRIPT_WATER;
		smMaterial[MatNum].MeshState = 0;
	}

	if ((aseMaterial->ScriptState&sMATS_SCRIPT_NOTPASS))
		smMaterial[MatNum].MeshState = SMMAT_STAT_CHECK_FACE;
	else
	{
		if ((aseMaterial->ScriptState&sMATS_SCRIPT_PASS))
			smMaterial[MatNum].MeshState = 0;
	}

	if ((aseMaterial->ScriptState&sMATS_SCRIPT_RENDLATTER))
		smMaterial[MatNum].MeshState |= sMATS_SCRIPT_RENDLATTER;

	if ((aseMaterial->ScriptState & sMATS_SCRIPT_CHECK_ICE))
		smMaterial[MatNum].MeshState |= sMATS_SCRIPT_CHECK_ICE;

	if ((aseMaterial->ScriptState & sMATS_SCRIPT_ORG_WATER))
		smMaterial[MatNum].MeshState = sMATS_SCRIPT_ORG_WATER;

	AnimCount = 0;
	if (szScript)
	{
		if (aseMaterial->ScriptState&sMATS_SCRIPT_ANIM2)
			AnimCount = 2;
		if (aseMaterial->ScriptState&sMATS_SCRIPT_ANIM4)
			AnimCount = 4;
		if (aseMaterial->ScriptState&sMATS_SCRIPT_ANIM8)
			AnimCount = 8;
		if (aseMaterial->ScriptState&sMATS_SCRIPT_ANIM16)
			AnimCount = 16;
	}

	if (AnimCount)
	{
		len = lstrlen(szScript);

		for (cnt = 0; cnt < len; cnt++)
		{
			if (szScript[cnt] == 'a' && szScript[cnt + 1] == 'n' && szScript[cnt + 2] == 'i' && szScript[cnt + 3] == 'm')
			{
				for (cnt = cnt; cnt < len; cnt++)
				{
					if (szScript[cnt] == ':')
						break;
				}
				break;
			}
		}

		if (cnt < len)
		{
			cnt++;
			lpScript = &szScript[cnt];
			FrameSpeed = 0;

			for (cnt = cnt; cnt < len; cnt++)
			{
				if (szScript[cnt] == ':')
				{
					FrameSpeed = atoi(&szScript[cnt + 1]);
					szScript[cnt] = 0;
					break;
				}
			}

			szDirectory = SetDirectoryFromFile(aseMaterial->BITMAP[0]);

			if (szDirectory)
			{
				for (cnt = 0; cnt < AnimCount; cnt++)
				{
					lpAnimFileList[cnt] = new char[64];
					lstrcpy(szTemp, szDirectory);
					lstrcat(szTemp, lpScript);
					wsprintf(lpAnimFileList[cnt], szTemp, cnt);
				}

				ChangeMaterialToAnimation(&smMaterial[MatNum], lpAnimFileList, AnimCount, smMaterial[MatNum].BlendType, TRUE);
				if (FrameSpeed) smMaterial[MatNum].Shift_FrameSpeed = FrameSpeed;

				smMaterial[MatNum].Transparency = aseMaterial->Transparency;

				for (cnt = AnimCount - 1; cnt >= 0; cnt--) delete lpAnimFileList[cnt];
			}
		}
	}
	if ((aseMaterial->ScriptState & sMATS_SCRIPT_BLINK_COLOR) && smMaterial[MatNum].WindMeshBottom == 0)
	{
		for (cnt = 0; cnt < MAX_MAP_BLINK_COLOR_TIME; cnt++)
		{
			if (strstr(szScript, szBlinkTimeScript[cnt]) != 0)
				break;
		}

		if (cnt >= MAX_MAP_BLINK_COLOR_TIME)
			smMaterial[MatNum].WindMeshBottom = dwBlinkTimeCode[0];
		else
			smMaterial[MatNum].WindMeshBottom = dwBlinkTimeCode[cnt];
	}

	aseMaterial->Regist++;
	aseMaterial->RegistNum = MatNum;

	return MatNum;
}
int smMATERIAL_GROUP::CreateTextureMaterial(char *szBitmap, char *szOpacity, int TwoSide, int Shade, DWORD BlendType)
{
	int MatNum;

	MatNum = MaterialCount;
	MaterialCount++;

	smMaterial[MatNum].InUse = TRUE;
	smMaterial[MatNum].Shade = Shade;
	smMaterial[MatNum].TwoSide = TwoSide;


	smMaterial[MatNum].ReformTexture = 0;

	smMaterial[MatNum].TextureStageState[0] = 0;
	smMaterial[MatNum].TextureFormState[0] = 0;

	smMaterial[MatNum].MapOpacity = FALSE;

	smMaterial[MatNum].TextureCounter = 1;
	smMaterial[MatNum].Transparency = 0;

	smMaterial[MatNum].UseState = 0;
	smMaterial[MatNum].TextureType = SMTEX_TYPE_MULTIMIX;
	smMaterial[MatNum].BlendType = BlendType;


	smMaterial[MatNum].InUse++;

	return MatNum;
}
int	smMATERIAL_GROUP::AddTexture(int MatNum, char *szBitmap, char *szOpacity)
{
	int cnt;

	cnt = smMaterial[MatNum].TextureCounter;


	if (smMaterial[MatNum].smTexture[cnt])
		smMaterial[MatNum].TextureCounter++;

	return TRUE;
}
smMATERIAL *smMATERIAL_GROUP::FindNextMaterialFromTextureName()
{
	DWORD cnt, cnt2;

	char *szName;

	szName = szLastSearchName;

	for (cnt = LastSearchMaterial; cnt < MaterialCount; cnt++)
	{
		if (smMaterial[cnt].InUse)
		{
			for (cnt2 = 0; cnt2 < smMaterial[cnt].TextureCounter; cnt2++)
			{
				if (lstrcmpi(smMaterial[cnt].smTexture[cnt2]->Name, szName) == 0)
					return	&smMaterial[cnt];
			}

			for (cnt2 = 0; cnt2 < smMaterial[cnt].AnimTexCounter; cnt2++)
			{
				if (lstrcmpi(smMaterial[cnt].smAnimTexture[cnt2]->Name, szName) == 0)
					return	&smMaterial[cnt];
			}
		}
	}

	return NULL;
}
smMATERIAL *smMATERIAL_GROUP::FindMaterialFromTextureName(char *szName)
{
	LastSearchMaterial = 0;

	lstrcpy(szLastSearchName, szName);

	return FindNextMaterialFromTextureName();
}

int smMATERIAL_GROUP::SetMaterialAnimFrame(smMATERIAL *lpMaterial, int frame)
{
	int OldFrame;

	OldFrame = lpMaterial->AnimationFrame;
	lpMaterial->AnimationFrame = frame;

	return OldFrame;
}

int smMATERIAL_GROUP::ChangeMaterialToAnimation(smMATERIAL *lpMaterial, char **szBitmap, int NumTex, DWORD BlendType, int AutoAnimMode)
{
	lpMaterial->MapOpacity = FALSE;
	lpMaterial->TextureCounter = 1;
	lpMaterial->Transparency = 0;

	lpMaterial->AnimTexCounter = NumTex;
	lpMaterial->FrameMask = NumTex - 1;
	lpMaterial->Shift_FrameSpeed = 6;

	lpMaterial->UseState = 0;
	lpMaterial->TextureType = SMTEX_TYPE_ANIMATION;
	lpMaterial->BlendType = BlendType;

	if (AutoAnimMode)
		lpMaterial->AnimationFrame = SMTEX_AUTOANIMATION;
	else
		lpMaterial->AnimationFrame = 0;

	lpMaterial->InUse++;

	return TRUE;
}
int smMATERIAL_GROUP::CreateAnimationMaterial(char **szBitmap, int NumTex, DWORD BlendType, int AutoAnimMode)
{
	int cnt;

	smMATERIAL *lpMaterial;

	cnt = MaterialCount;
	MaterialCount++;

	lpMaterial = &smMaterial[cnt];

	lpMaterial->InUse = TRUE;
	lpMaterial->Shade = FALSE;
	lpMaterial->TwoSide = TRUE;

	ChangeMaterialToAnimation(lpMaterial, szBitmap, NumTex, BlendType, AutoAnimMode);

	return cnt;
}
int smMATERIAL_GROUP::IncTextureFrame()
{
	return TRUE;
}
int smMATERIAL_GROUP::ReadTextures(int MipMap)
{
	return 0;
}

smMATERIAL *smMaterial;

smMATERIAL_GROUP	*smMaterialGroup;

// 메트리얼 초기화
int InitMaterial()
{
	smMaterialGroup = new smMATERIAL_GROUP(MATRIAL_MAX);
	smMaterial = smMaterialGroup->smMaterial;

	MaterialFrame = 0;

	return TRUE;
}

int CloseMaterial()
{
	delete smMaterialGroup;
	return TRUE;
}

int DeleteUnuseMaterial()
{
	return smMaterialGroup->DeleteUnuseMaterial();
}

int AddMaterial(ASE_MATERIAL *aseMaterial)
{
	return smMaterialGroup->AddMaterial(aseMaterial);
}

int CreateTextureMaterial(char *szBitmap, char *szOpacity, int TwoSide, int Shade, DWORD BlendType)
{
	return smMaterialGroup->CreateTextureMaterial(szBitmap, szOpacity, TwoSide, Shade, BlendType);
}

int	AddTexture(int MatNum, char *szBitmap, char *szOpacity)
{
	return smMaterialGroup->AddTexture(MatNum, szBitmap, szOpacity);
}

smMATERIAL *FindNextMaterialFromTextureName()
{
	return smMaterialGroup->FindNextMaterialFromTextureName();
}

smMATERIAL *FindMaterialFromTextureName(char *szName)
{
	return smMaterialGroup->FindMaterialFromTextureName(szName);
}

int SetMaterialAnimFrame(smMATERIAL *lpMaterial, int frame)
{
	return smMaterialGroup->SetMaterialAnimFrame(lpMaterial, frame);
}

int ChangeMaterialToAnimation(smMATERIAL *lpMaterial, char **szBitmap, int NumTex, DWORD BlendType, int AutoAnimMode)
{
	return smMaterialGroup->ChangeMaterialToAnimation(lpMaterial, szBitmap, NumTex, BlendType, AutoAnimMode);
}

int CreateAnimationMaterial(char **szBitmap, int NumTex, DWORD BlendType, int AutoAnimMode)
{
	return smMaterialGroup->CreateAnimationMaterial(szBitmap, NumTex, BlendType, AutoAnimMode);
}