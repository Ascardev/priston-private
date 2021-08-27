#pragma once

#define GAMEWINDOW  (CGAMEWINDOW::GetInstance())
#define GAME		(GAMEWINDOW->GetGame())

typedef class CGAMEWINDOW *LPCGAMEWINDOW;

class CGAMEWINDOW : public CWINDOW
{
public:
	CGAMEWINDOW();
	virtual ~CGAMEWINDOW();

	UINT Init();
	void Shutdown();
	BOOL Run();

	static LPCGAMEWINDOW GetInstance() {return m_pcInstance;}
	LPCGAME GetGame() {return m_pcGame;}
protected:
	LRESULT WndProc(UINT uMsg,WPARAM wParam,LPARAM lParam);
	void Loop();
	BOOL ResetCheck();
	void Render();
	void Update(double fTime);
	BOOL Quit();
private:
	BOOL m_bRender;
	static LPCGAMEWINDOW m_pcInstance;
	UINT m_uTimerID;
	int m_iWindowInactiveFrameSleepTime;
	LPCGAME m_pcGame;
	CINFO::LPTIMER m_pcTimer;
};