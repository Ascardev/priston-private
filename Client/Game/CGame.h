#pragma once

#define GAMETIMEHANDLE		(GAME->GetGameTimer())
#define ENGINEHANDLE		(GAME->GetEngine())
#define GAMECOREHANDLE		(GAME->GetGameCore())

typedef class CGame *LPCGAME;

class CGame
{
public:
	CGame();
	virtual ~CGame();

	void Init();
	void Shutdown();

	void Begin();
	void End();

	void Frame();
	void Update(float fTime);

	void Render2D();
	void Render3D();

	BOOL OnKeyPress(INPUTS::LPKEYBOARD pcKeyboard);
	BOOL OnKeyChar(INPUTS::LPKEYBOARD pcKeyboard);
	void OnMouseMove(INPUTS::LPMOUSE pcMouse);
	BOOL OnMouseClick(INPUTS::LPMOUSE pcMouse);
	BOOL OnMouseScroll(INPUTS::LPMOUSE pcMouse);

	LPGAMETIME GetGameTimer() { return m_pcGameTimer; }
	LPENGINE GetEngine() { return m_pcEngine; }
	LPGAMECORE GetGameCore() { return m_pcGameCore; }
private:
	LPGAMETIME m_pcGameTimer = NULL;
	LPENGINE m_pcEngine = NULL;
	LPGAMECORE m_pcGameCore = NULL;
};