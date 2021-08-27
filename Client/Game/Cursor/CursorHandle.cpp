#include "StdAfx.h"
#include "CursorHandle.h"

namespace CURSOR
{
	Handle::Handle()
	{

	}
	Handle::~Handle()
	{
		
	}
	void Handle::Init()
	{
		BuildWindow();
	}
	void Handle::Shutdown()
	{
		m_pWindowMain->Clear();
	}
	void Handle::BuildWindow()
	{
		m_pWindowMain = std::make_shared<UI::Window>(Rectangle2D(0, 0, GRAPHICENGINE->GetBackWidth(), GRAPHICENGINE->GetBackHeight()));

		m_pWindowMain->AddElement(Load(EMOUSEICON_Default, "Resources\\Cursor\\Default.tga"));
		m_pWindowMain->AddElement(Load(EMOUSEICON_Sell, "Resources\\Cursor\\Sell.tga"));
		m_pWindowMain->AddElement(Load(EMOUSEICON_Buy, "Resources\\Cursor\\Buy.tga"));
		m_pWindowMain->AddElement(Load(EMOUSEICON_Repair, "Resources\\Cursor\\Repair.tga"));
		m_pWindowMain->AddElement(Load(EMOUSEICON_Attack, "Resources\\Cursor\\Attack.tga"));
		m_pWindowMain->AddElement(Load(EMOUSEICON_GetItem1, "Resources\\Cursor\\Dropsee.tga"));
		m_pWindowMain->AddElement(Load(EMOUSEICON_GetItem2, "Resources\\Cursor\\Droppick.tga"));
		m_pWindowMain->AddElement(Load(EMOUSEICON_Talk, "Resources\\Cursor\\Talk.tga"));
	}
	UI::LPIMAGEBOX Handle::Load(EMouseIcon eID, const char* pszFile)
	{
		auto pImageBox = std::make_shared<UI::ImageBox>(Rectangle2D(0, 0, 32, 32));
		pImageBox->SetImage(UI::ImageLoader::LoadImage_(pszFile));
		pImageBox->SetID(eID);
		return pImageBox;
	}
	void Handle::Render()
	{
		if (!m_bDisable)
		{
			if (m_eID == EMOUSEICON_RepairAll)
				EMOUSEICON_Repair;

			auto pImageBox = m_pWindowMain->GetElement<UI::ImageBox>(m_eID);

			pImageBox ? pImageBox->Render(MOUSEHANDLER->GetPosition()->iX, MOUSEHANDLER->GetPosition()->iY, GRAPHICENGINE->GetBackWidth(), GRAPHICENGINE->GetBackHeight(), 0, 0) : 0;
		}
	}
}