#ifndef _HO_NEW_PARTICLE_MGR_
#define _H0_NEW_PARTICLE_MGR_

struct HoNewParticleMatRes
{
    int     matNum;
    string  matName;
};

#define MAX_TOKEN_VECTORS   486
#define MAX_MATERIAL        300
#define MAX_EMITTER         300

class HoNewParticleScriptRes
{
public:
	string name;
	HoNewParticleEmitterTokenizer emitterTokenizer;
};
class HoNewParticleResMgr
{
public:
	HoNewParticleResMgr()
	{
		init();
	}

	~HoNewParticleResMgr()
	{
		Shutdown();
	}

private:

	std::vector<HoNewParticleScriptRes *> m_vpScriptRes;
	std::vector<HoNewParticleMatRes*> m_vpMatRes;

public:
	void init();
	void Shutdown();
	bool LoadScript(char *scr);
	HoNewParticleScriptRes *AddScript(char *scr, char *indexName = "test");
	int AddTexture(const char *pszFilePath);
	int SearchingAddTexture(const char *directory);
	HoNewParticleScriptRes *FindScript(const char *pszFileName);
	HoNewParticleMatRes *FindMat(const char *pszFileName);
};

class HoNewParticleMgr
{
public:
	HoNewParticleMgr()
	{
		m_vpEmitters.clear();
		Running = false;
	}

	~HoNewParticleMgr()
	{
		Destroy();
	}

private:
	std::vector<HoNewParticleEmitter *> m_vpEmitters;
public:
	void	Init();
	bool    Running;
	void    Clear();
	void    Destroy();
	void    Main(float elapsedTime, float timeDelta);
	void    Draw(int x, int y, int z, int ax, int ay, int az);
	bool    IsRunning() { return Running; }
	int Start(const char *pszFileName, POINT3D sPosition, float fDelay = 0.0f);
	void    SetPos(int partID, D3DVECTOR pos);
	void    SetAttachPos(int partID, D3DVECTOR pos);
	void    SetStop(int partID);
	void    SetFastStop(int partID);
	void	SetAngle(int partID, POINT3D angle);
	bool	GetRunning(int partID);
	void    SetRendering(int partID, BOOL flag);
protected:
	HoNewParticleEmitter *GetParticleEmitter(int iID);
	int Start(HoNewParticleScriptRes *pScriptRes, Point3D sPosition, float fDelay);
};

extern HoNewParticleResMgr  g_NewParticleResMgr;
extern HoNewParticleMgr     g_NewParticleMgr;

#endif
