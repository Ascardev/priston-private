#include "StdAfx.h"
#include "HoEffectResMgr.h"
HoEffectResTexture::HoEffectResTexture()
{
}

HoEffectResTexture::~HoEffectResTexture()
{
}

bool HoEffectResTexture::LoadingRes(const std::string &fileName)
{
	m_iMatNum = CreateTextureMaterial((char *)fileName.c_str(), 0, 0, 0, SMMAT_BLEND_LAMP);
	smMaterialGroup->ReadTextures();

	return true;
}

int HoEffectResTexture::GetRes()
{
	return m_iMatNum;
}

HoEffectResMesh::HoEffectResMesh() :m_Mesh(NULL),
m_Bone(NULL)
{
}

HoEffectResMesh::~HoEffectResMesh()
{
	DELET(m_Mesh);
	DELET(m_Bone);
}

bool HoEffectResMesh::LoadingRes(const std::string &meshName)
{
	smASE_SetPhysique(NULL);
	m_Mesh = smASE_Read((char *)meshName.c_str());
	if (m_Mesh == NULL)
		return false;

	m_Mesh->ZeroNormals();
	m_Mesh->smMaterialGroup->ReadTextures();

	if (m_Mesh->smMaterialGroup)
	{
		int matCount = m_Mesh->smMaterialGroup->MaterialCount;
		for (int i = 0; i < matCount; i++)
		{
			m_Mesh->smMaterialGroup->smMaterial[i].BlendType = SMMAT_BLEND_LAMP;
		}
	}
	return true;
}

smPAT3D *HoEffectResMesh::GetRes()
{
	return m_Mesh;
}

smPAT3D *HoEffectResMesh::GetBoneRes()
{
	return m_Bone;
}

bool HoEffectResMesh::LoadingRes(const std::string &meshName, const std::string &boneName)
{
	m_Bone = smASE_ReadBone((char *)boneName.c_str());
	smASE_SetPhysique(m_Bone);

	m_Mesh = smASE_Read((char *)meshName.c_str());
	m_Mesh->ZeroNormals();
	m_Mesh->smMaterialGroup->ReadTextures();

	if (m_Mesh->smMaterialGroup)
	{
		int matCount = m_Mesh->smMaterialGroup->MaterialCount;
		for (int i = 0; i < matCount; i++)
		{
			m_Mesh->smMaterialGroup->smMaterial[i].BlendType = SMMAT_BLEND_LAMP;
		}
	}

	return true;
}

HoEffectResManager::HoEffectResManager()
{
}

HoEffectResManager::~HoEffectResManager()
{
	Clear();
}

HoEffectResManager* HoEffectResManager::m_Instance = 0;
HoEffectResManager* HoEffectResManager::GetInstance()
{
	if (m_Instance == 0)
		m_Instance = new HoEffectResManager;
	return m_Instance;
}

smPAT3D *HoEffectResManager::GetResMesh(const std::string &meshName, const std::string &boneName)
{
	if (m_ResMeshMap.find(meshName) == m_ResMeshMap.end())
	{
		HoEffectResMesh *resMesh = new HoEffectResMesh;
		if (boneName.size() == 0)
			resMesh->LoadingRes(meshName);
		else
			resMesh->LoadingRes(meshName, boneName);
		m_ResMeshMap[meshName] = resMesh;
		return resMesh->GetRes();
	}
	else
		return m_ResMeshMap[meshName]->GetRes();

	return NULL;
}

smPAT3D *HoEffectResManager::GetResBone(const std::string &meshName)
{
	if (m_ResMeshMap.find(meshName) != m_ResMeshMap.end())
		return m_ResMeshMap[meshName]->GetBoneRes();

	return NULL;
}

int HoEffectResManager::GetResTexture(const std::string &fileName)
{
	if (m_ResTextureMap.find(fileName) == m_ResTextureMap.end())
	{
		HoEffectResTexture *resTexture = new HoEffectResTexture;
		resTexture->LoadingRes(fileName);
		m_ResTextureMap[fileName] = resTexture;
		return resTexture->GetRes();
	}
	else
		return m_ResTextureMap[fileName]->GetRes();
	return -1;
}

void HoEffectResManager::Clear()
{
	for (auto &v : m_ResTextureMap)
	{
		DELET(v.second);
	}

	m_ResTextureMap.clear();

	for (auto &v : m_ResMeshMap)
	{
		DELET(v.second);
	}

	m_ResMeshMap.clear();
}