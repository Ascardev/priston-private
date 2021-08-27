#include "StdAfx.h"
#include "GameCore.h"

std::vector<CBaseHandle *> vHandleElement;
std::vector<CBaseWindow *> vWindowElement;

CGameCore::CGameCore()
{
	AddHandle(new SETTING::Handle(EHANDLE_Settings));
	AddHandle(new CHAT::Handle(EHANDLE_Chat));
	AddHandle(new INVENTROY::Handle(EHANDLE_Inventory));
	AddHandle(new PARTY::Handle(EHANDLE_Party));

	m_pcItemHandle = new CItemHandle;

	AddWindow(new SETTING::Window(EWINDOW_Setting));
	AddWindow(new MESSAGE::BOX::Window(EWINDOW_MessageBox));
	AddWindow(new MESSAGE::TITLE::Window(EWINDOW_MessageTitle));
	AddWindow(new ITEMTIME::Window(EWINDOW_Premium));
	AddWindow(new CURSOR::Window(EWINDOW_Cursor));

}
CGameCore::~CGameCore()
{
	for (auto &v : vHandleElement)
	{
		DELET(v);
	}

	for (auto &v : vWindowElement)
	{
		DELET(v);
	}

	DELET(m_pcItemHandle);

	vHandleElement.clear();
	vWindowElement.clear();
}
void CGameCore::Init()
{
	for (auto &v : vHandleElement)
	{
		INIT(v);
	}
	for (auto &v : vWindowElement)
	{
		INIT(v);
	}

	INIT(m_pcItemHandle);

	m_bInit = TRUE;
}
void CGameCore::Shutdown()
{
	for (auto &v : vHandleElement)
	{
		SHUTDOWN(v);
	}
	for (auto &v : vWindowElement)
	{
		SHUTDOWN(v);
	}

	SHUTDOWN(m_pcItemHandle);
}
void CGameCore::Render2D()
{
	for (auto &v : vWindowElement)
	{
		v->Render();
	}
}
void CGameCore::Render3D()
{

}
void CGameCore::Frame()
{

}
void CGameCore::Update(float fTime)
{
	double fdTime = (double)fTime;
	static double fCount_14MS = 0.0f; static double fFPS70 = (1000.0f / 70.0f);
	static double fCount_100MS = 0.0f; static double f100MS = 100.0f;
	static double fCount_1SECO = 0.0f; static double f1SECO = 1000.0f;
	static double fCount_1MINU = 0.0f; static double f1MINU = 60000.0f;

	static int iTimes = 0;

	fCount_14MS += fdTime;
	fCount_100MS += fdTime;
	fCount_1SECO += fdTime;
	fCount_1MINU += fdTime;

	CTITLEBOX->Update(fTime);

	//100ms
	while (fCount_100MS >= f100MS)
	{
		ITEMTIMEBOX ? ITEMTIMEBOX->Loop() : 0;
		PARTYHANDLE ? PARTYHANDLE->Update(fTime) : 0;
		MINIMAPBOX ? MINIMAPBOX->Update(fTime) : 0;

		fCount_100MS -= f100MS;
	}
	//1000ms
	while (fCount_1SECO >= f1SECO)
	{
		MESSAGEBOX ? MESSAGEBOX->Update(fTime) : 0;
		CTITLEBOX ? CTITLEBOX->Tick() : 0;
		ITEMTIMEBOX ? ITEMTIMEBOX->Tick() : 0;

		fCount_1SECO -= f1SECO;
	}
}
BOOL CGameCore::OnMouseClick(class INPUTS::Mouse *pcMouse)
{
	for (int t = (int)vWindowElement.size() - 1; t >= 0; t--)
	{
		if (vWindowElement[t]->OnMouseClick(pcMouse))
		{
			if (pcMouse->GetEvent() == ClickDownL)
				this->SetFocus(vWindowElement[t]);
			return TRUE;
		}
	}
	return FALSE;
}
BOOL CGameCore::OnMouseScroll(class INPUTS::Mouse *pcMouse)
{
	for (int t = (int)vWindowElement.size() - 1; t >= 0; t--)
	{
		if (vWindowElement[t]->OnMouseScroll(pcMouse))
			return TRUE;
	}
	return FALSE;
}
void CGameCore::OnMouseMove(class INPUTS::Mouse *pcMouse)
{
	for (int t = (int)vWindowElement.size() - 1; t >= 0; t--)
	{
		vWindowElement[t]->OnMouseMove(pcMouse);
	}
}
BOOL CGameCore::OnKeyChar(class INPUTS::KeyBoard *pcKeyboard)
{
	for (int t = (int)vWindowElement.size() - 1; t >= 0; t--)
	{
		if (vWindowElement[t]->OnKeyChar(pcKeyboard))
			return TRUE;
	}

	return FALSE;
}
BOOL CGameCore::OnKeyPress(class INPUTS::KeyBoard *pcKeyboard)
{
	for (int t = (int)vWindowElement.size() - 1; t >= 0; t--)
	{
		if (vWindowElement[t]->OnKeyPress(pcKeyboard))
			return TRUE;
	}
	return FALSE;
}
void CGameCore::OnResolutionChanged()
{
	for (auto &v : vWindowElement)
	{
		v->OnResolutionChanged();
	}
}
void CGameCore::SetFocus(CBaseWindow *pWindow)
{
	for (std::vector<CBaseWindow *>::iterator it = vWindowElement.begin(); it != vWindowElement.end(); it++)
	{
		if (*it == pWindow)
		{
			vWindowElement.erase(it);

			int iCount = 0;

			for (auto &v : vWindowElement)
			{
				if (v->GetWindowLevel() <= pWindow->GetWindowLevel())
				{
					iCount++;
				}
			}

			vWindowElement.insert(vWindowElement.begin() + iCount, pWindow);
			break;
		}
	}
}
CBaseHandle *CGameCore::GetHandle(EHandle eID)
{
	for (auto &v : vHandleElement)
	{
		if (v->GetHandleId() == eID)
			return v;
	}

	return nullptr;
}
CBaseWindow *CGameCore::GetWindow(EWindow eID)
{
	for (auto &v : vWindowElement)
	{
		if (v->GetWindowId() == eID)
			return v;
	}

	return nullptr;
}
CBaseWindow *CGameCore::AddWindow(CBaseWindow *pWindow)
{
	vWindowElement.push_back(pWindow);

	struct
	{
		bool operator()(CBaseWindow *a, CBaseWindow *b) const
		{
			return a->GetWindowLevel() < b->GetWindowLevel();
		}

	}Less;

	std::sort(vWindowElement.begin(), vWindowElement.end(), Less);

	return pWindow;
}
CBaseHandle *CGameCore::AddHandle(CBaseHandle *pHandle)
{
	vHandleElement.push_back(pHandle);

	return pHandle;
}
void CGameCore::DelWindow(CBaseWindow *pWindow)
{
	for (auto it = vWindowElement.begin(); it != vWindowElement.end(); it++)
	{
		if (*it == pWindow)
		{
			DELET(pWindow);
			vWindowElement.erase(it);
			break;
		}
	}
}
void CGameCore::DelHandle(CBaseHandle *pHandle)
{
	for (auto it = vHandleElement.begin(); it != vHandleElement.end(); it++)
	{
		if (*it == pHandle)
		{
			DELET(pHandle);
			vHandleElement.erase(it);
			break;
		}
	}
}