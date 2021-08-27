#include "StdAfx.h"
#include "HoNewParticleLinkHeader.h"

HoNewParticleResMgr  g_NewParticleResMgr;
HoNewParticleMgr     g_NewParticleMgr;

void HoNewParticleResMgr::init()
{
	m_vpMatRes.clear();
	m_vpScriptRes.clear();
}
void HoNewParticleResMgr::Shutdown()
{
	for (auto &v : m_vpMatRes)
	{
		DELET(v);
	}

	m_vpMatRes.clear();

	for (auto &v : m_vpScriptRes)
	{
		DELET(v);
	}

	m_vpScriptRes.clear();
}

HoNewParticleScriptRes *HoNewParticleResMgr::FindScript(const char *pszFileName)
{
	for (auto &v : m_vpScriptRes)
	{
		if (v->name.compare(pszFileName) == 0)
			return v;
	}

	return nullptr;
}
HoNewParticleMatRes *HoNewParticleResMgr::FindMat(const char *pszFileName)
{
	for (auto &v : m_vpMatRes)
	{
		if (v->matName.compare(pszFileName) == 0)
			return v;
	}

	return nullptr;
}

bool HoNewParticleResMgr::LoadScript(char *scr)
{
	if (scr == NULL)
		return false;

	CFILE::Bin cFile;

	if (cFile.Open(scr, BIN_READ))
	{
		int iSize = cFile.GetSize() + 1;

		auto pBuffer = new char[iSize];

		ZeroMemory(pBuffer, iSize);

		cFile.Read(pBuffer, iSize);

		cFile.Close();

		AddScript(pBuffer, (char *)GetPathFileName(scr, FALSE).c_str());

		DELETA(pBuffer);
	}

	return true;
}

HoNewParticleScriptRes *HoNewParticleResMgr::AddScript(char *scr, char *indexName)
{
	if (!FindScript(indexName))
	{
		auto pPartScriptRes = new HoNewParticleScriptRes;

		pPartScriptRes->name.reserve(STRLEN(indexName));
		pPartScriptRes->name = indexName;
		pPartScriptRes->emitterTokenizer.Tokenize(scr);

		m_vpScriptRes.push_back(pPartScriptRes);

		return pPartScriptRes;
	}

	return nullptr;
}

int HoNewParticleResMgr::SearchingAddTexture(const char *directory)
{
	HANDLE hSrch;
	WIN32_FIND_DATA wfd;
	BOOL    bResult = TRUE;
	hSrch = FindFirstFile(directory, &wfd);

	while (bResult)
	{
		if (!(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			if (lstrlen(wfd.cFileName) > 3)
			{
				std::string s = directory;
				s.append(wfd.cFileName);

				AddTexture(s.c_str());
			}
		}

		bResult = FindNextFile(hSrch, &wfd);
	}
	FindClose(hSrch);

	return TRUE;
}

int HoNewParticleResMgr::AddTexture(const char *pszFilePath)
{
	std::string strFileName = GetPathFileName(pszFilePath);

	auto pPartMatRes = FindMat(strFileName.c_str());

	if (!pPartMatRes)
	{
		pPartMatRes = new HoNewParticleMatRes;
		pPartMatRes->matName = strFileName;
		pPartMatRes->matNum = CreateTextureMaterial((char *)pszFilePath, 0, 0, 0, SMMAT_BLEND_LAMP);

		m_vpMatRes.push_back(pPartMatRes);
		smMaterialGroup->ReadTextures();
	}

	return pPartMatRes->matNum;
}
HoNewParticleEmitter *HoNewParticleMgr::GetParticleEmitter(int iID)
{
	if (iID >= 0 && iID < (int)m_vpEmitters.size())
	{
		auto pEmitter = m_vpEmitters.at(iID);

		if (pEmitter->IsRunning())
			return pEmitter;
	}

	return nullptr;
}

void HoNewParticleMgr::Main(float elapsedTime, float timeDelta)
{
	for (std::vector<HoNewParticleEmitter *>::iterator it = m_vpEmitters.begin(); it != m_vpEmitters.end();)
	{
		auto pEmitter = *it;

		if (pEmitter->IsRunning())
		{
			pEmitter->Main(elapsedTime, timeDelta);

			it++;
		}
		else
		{
			pEmitter->init();
			DELET(pEmitter);
			it = m_vpEmitters.erase(it);
		}
	}
}

void HoNewParticleMgr::Draw(int x, int y, int z, int ax, int ay, int az)
{
	for (auto &v : m_vpEmitters)
	{
		if (v->IsRendering())
			v->Draw(x, y, z, ax, ay, az);
	}


}
int HoNewParticleMgr::Start(const char *pszFileName, POINT3D sPosition, float fDelay)
{
	auto pScriptRes = g_NewParticleResMgr.FindScript(pszFileName);

	return pScriptRes ? Start(pScriptRes, Point3D(sPosition.x, sPosition.y, sPosition.z), fDelay) : -1;
}
int HoNewParticleMgr::Start(HoNewParticleScriptRes *pScriptRes, Point3D sPosition, float fDelay)
{
	auto pEmitter = new HoNewParticleEmitter;

	pEmitter->AddScript(pScriptRes);
	pEmitter->SetPos(D3DXVECTOR3((float)sPosition.iX, (float)sPosition.iY, (float)sPosition.iZ));
	pEmitter->Start(fDelay);

	m_vpEmitters.push_back(pEmitter);

	return m_vpEmitters.size() - 1;
}

void HoNewParticleMgr::SetPos(int partID, D3DVECTOR pos)
{
	auto pEmitter = GetParticleEmitter(partID);

	if (pEmitter)
	{
		pEmitter->SetPos(pos);
	}
}

void HoNewParticleMgr::SetAngle(int partID, POINT3D angle)
{
	auto pEmitter = GetParticleEmitter(partID);

	if (pEmitter)
	{
		pEmitter->SetAngle(D3DXVECTOR3((float)angle.x, (float)angle.y, (float)angle.z));
	}
}

bool HoNewParticleMgr::GetRunning(int partID)
{
	return GetParticleEmitter(partID) ? true : false;
}


void HoNewParticleMgr::SetAttachPos(int partID, D3DVECTOR pos)
{
	auto pEmitter = GetParticleEmitter(partID);

	if (pEmitter)
	{
		pEmitter->SetAttachPos(pos);
	}
}

void HoNewParticleMgr::SetStop(int partID)
{
	auto pEmitter = GetParticleEmitter(partID);

	if (pEmitter)
	{
		pEmitter->FadeStop();
	}
}

void HoNewParticleMgr::SetFastStop(int partID)
{
	auto pEmitter = GetParticleEmitter(partID);

	if (pEmitter)
	{
		pEmitter->FastStop();
	}
}

void HoNewParticleMgr::SetRendering(int partID, BOOL flag)
{
	auto pEmitter = GetParticleEmitter(partID);

	if (pEmitter)
	{
		pEmitter->SetRendering(flag);
	}
}

void HoNewParticleMgr::Init()
{
	m_vpEmitters.clear();
	Running = false;
}

void HoNewParticleMgr::Clear()
{
	for (auto &v : m_vpEmitters)
	{
		v->init();
	}
}

void HoNewParticleMgr::Destroy()
{
	for (auto &v : m_vpEmitters)
	{
		v->init();
		DELET(v);
	}

	m_vpEmitters.clear();
}