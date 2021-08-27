#pragma once

#define GAMETIMEHANDLE		(GAME->GetGameTimer())
#define GAMESYSTEMHANDLE	(GAME->GetGameSystem())
#define GAMECOREHANDLE		(GAME->GetGameCore())
#define GAMESCREEN			(GAME->GetGameScreen())
#define GAMEENGINEHANDLE	(GAME->GetGameEngine())
#define GAMESOCKET			(GAME->GetGameSocket())
#define GAMEUNIT			(GAME->GetGameUnit())
#define GAMECHARACTER		(GAME->GetGameCharacter())
#define GAMEMAP				(GAME->GetGameMap())
#define GAMEPACKET			(GAME->GetGamePacket())


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

	BOOL OnKeyPress(class INPUTS::KeyBoard *pcKeyboard);
	BOOL OnKeyChar(class INPUTS::KeyBoard *pcKeyboard);
	void OnMouseMove(class INPUTS::Mouse *pcMouse);
	BOOL OnMouseClick(class INPUTS::Mouse *pcMouse);
	BOOL OnMouseScroll(class INPUTS::Mouse *pcMouse);

	void OnResolutionChanged();

	CGameTime *GetGameTimer() { return m_pcGameTimer; }
	CGameSystem * GetGameSystem() { return m_pcGameSystem; }
	CGameEngine *GetGameEngine() { return m_pcGameEngine; }
	CGameCore *GetGameCore() { return m_pcGameCore; }
	CGameScreen *GetGameScreen() { return m_pcGameScreen; }
	CGameSocket *GetGameSocket() { return m_pcGameSocket; }
	CGameUnit *GetGameUnit() { return m_pcGameUnit; }
	CGameCharacter *GetGameCharacter() { return m_pcGameCharacter; }
	CGameMap *GetGameMap() { return m_pcGameMap; }
	CGamePacket * GetGamePacket() { return m_pcGamePacket; }
private:
	CGameTime *m_pcGameTimer = nullptr;
	CGameSystem * m_pcGameSystem = nullptr;
	CGameCore *m_pcGameCore = nullptr;
	CGameEngine *m_pcGameEngine = nullptr;
	CGameScreen *m_pcGameScreen = nullptr;
	CGameSocket *m_pcGameSocket = nullptr;
	CGameUnit *m_pcGameUnit = nullptr;
	CGameCharacter *m_pcGameCharacter = nullptr;
	CGameMap *m_pcGameMap = nullptr;
	CGamePacket * m_pcGamePacket = nullptr;
};