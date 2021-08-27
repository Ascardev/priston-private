#include "StdAfx.h"
#include "CursorWindow.h"

namespace CURSOR
{
	Window::Window() : CBaseWindow()
	{

	}
	Window::Window(EWindow eID) : CBaseWindow(eID)
	{
		SetWindowLevel(9);
	}
	Window::~Window()
	{

	}
	void Window::Init()
	{
		BuildWindow();
	}
	void Window::Shutdown()
	{
		m_pWindowMain->Clear();
	}
	void Window::BuildWindow()
	{
		m_pWindowMain = std::make_shared<UI::Window>(Rectangle2D(0, 0, GRAPHICENGINE->GetBackWidth(), GRAPHICENGINE->GetBackHeight()));

		m_pWindowMain->AddElement(Load(ECURSORICON_Default, "Resources\\Cursor\\Default.tga"));
		m_pWindowMain->AddElement(Load(ECURSORICON_Sell, "Resources\\Cursor\\Sell.tga"));
		m_pWindowMain->AddElement(Load(ECURSORICON_Buy, "Resources\\Cursor\\Buy.tga"));
		m_pWindowMain->AddElement(Load(ECURSORICON_Repair, "Resources\\Cursor\\Repair.tga"));
		m_pWindowMain->AddElement(Load(ECURSORICON_Attack, "Resources\\Cursor\\Attack.tga"));
		m_pWindowMain->AddElement(Load(ECURSORICON_GetItem1, "Resources\\Cursor\\Dropsee.tga"));
		m_pWindowMain->AddElement(Load(ECURSORICON_GetItem2, "Resources\\Cursor\\Droppick.tga"));
		m_pWindowMain->AddElement(Load(ECURSORICON_Talk, "Resources\\Cursor\\Talk.tga"));
	}
	UI::LPIMAGEBOX Window::Load(ECursorIcon eID, const char* pszFile)
	{
		auto pImageBox = std::make_shared<UI::ImageBox>(Rectangle2D(0, 0, 32, 32));
		pImageBox->SetImage(UI::ImageLoader::LoadImage_(pszFile));
		pImageBox->SetID(eID);
		return pImageBox;
	}
	void Window::Render()
	{
		if (m_bShow)
		{
			if (m_eID == ECURSORICON_RepairAll)
				ECURSORICON_Repair;

			auto pImageBox = m_pWindowMain->GetElement<UI::ImageBox>(m_eID);

			pImageBox ? pImageBox->Render(MOUSEHANDLER->GetPosition()->iX, MOUSEHANDLER->GetPosition()->iY, GRAPHICENGINE->GetBackWidth(), GRAPHICENGINE->GetBackHeight(), 0, 0) : 0;
		}
	}
}