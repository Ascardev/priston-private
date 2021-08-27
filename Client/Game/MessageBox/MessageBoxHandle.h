#pragma once

#define MESSAGEBOXWINDOW	(MESSAGEBOXHANDLE->GetModel())
#define MESSAGEBOXTITLE		(MESSAGEBOXHANDLE->GetTitle())

namespace MESSAGEBOX
{
	typedef class Handle *LPHANDLE;

	class Handle : public CBase
	{
	public:
		Handle();
		virtual ~Handle();

		void Init();
		void Shutdown();
		void Clear();

		void Update(float fTime);
		void Tick();
		void Render();
		BOOL OnKeyPress(INPUTS::LPKEYBOARD pcKeyboard);
		void OnMouseMove(INPUTS::LPMOUSE pcMouse);
		BOOL OnMouseClick(INPUTS::LPMOUSE pcMouse);
		LPTITLE GetTitle() { return m_pcTitle; }
		LPMODEL GetModel() { return m_pcModel; }
	private:
		LPTITLE m_pcTitle = NULL;
		LPMODEL m_pcModel = NULL;
	};
}
