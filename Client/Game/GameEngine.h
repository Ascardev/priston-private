#pragma once

#define GRAPHICENGINE		(GAMEENGINEHANDLE->GetGraphicEngine())
#define MOUSEHANDLER		(GAMEENGINEHANDLE->GetInputEngine()->GetMouse())
#define KEYBOARDHANDLER		(GAMEENGINEHANDLE->GetInputEngine()->GetKeyBoard())
#define EFFECTGLOW			(GAMEENGINEHANDLE->GetEffectEngine()->GetEffectGlow())
#define EFFECTPOSTPROCESS	(GAMEENGINEHANDLE->GetEffectEngine()->GetEffectProcess())

class CGameEngine
{
public:
	CGameEngine();
	virtual ~CGameEngine();

	void Init();
	void Shutdown();
	void Update(float fTime);

	DX::LPGRAPHICSENGINE GetGraphicEngine() { return m_pcGraphicsEngine; }
	EFFECT::Engine *GetEffectEngine() { return m_pcEffectEngine; }
	INPUTS::Engine *GetInputEngine() { return m_pcInputEngine; }
private:
	DX::LPGRAPHICSENGINE m_pcGraphicsEngine = nullptr;
	INPUTS::Engine *m_pcInputEngine = nullptr;
	EFFECT::Engine *m_pcEffectEngine = nullptr;
};