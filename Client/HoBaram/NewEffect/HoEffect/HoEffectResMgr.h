#ifndef _HO_EFFECT_RES_H_
#define _HO_EFFECT_RES_H_

#include "HoNewEffectHeader.h"


class HoEffectResTexture
{
private:
    int     m_iMatNum;
public:
    HoEffectResTexture();
    ~HoEffectResTexture();

    bool    LoadingRes(const std::string &fileName);
    int     GetRes();
};


class HoEffectResMesh
{
private:
    smPAT3D *m_Mesh;
    smPAT3D *m_Bone;
public:
    HoEffectResMesh();
    ~HoEffectResMesh();

    bool    LoadingRes(const std::string &meshName);
    bool    LoadingRes(const std::string &meshName, const std::string &boneName);
    smPAT3D *GetRes();
	smPAT3D *GetBoneRes();
};


class HoEffectResManager
{
public:
    HoEffectResManager();
    ~HoEffectResManager();
protected:
    typedef std::map<std::string, HoEffectResTexture *> ResTextureMap;
    typedef std::map<std::string, HoEffectResMesh *>    ResMeshMap;

private:
    ResMeshMap          m_ResMeshMap;
    ResTextureMap       m_ResTextureMap;

    static HoEffectResManager*              m_Instance;
public:
    static HoEffectResManager*              GetInstance();

    smPAT3D *GetResMesh(const std::string &meshName, const std::string &boneName);
    smPAT3D *GetResBone(const std::string &meshName);

	int      GetResTexture(const std::string &textureName);
	

    void    Clear();
};

#endif
