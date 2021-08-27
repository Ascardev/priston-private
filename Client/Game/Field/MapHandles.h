#pragma once

#define MAPMODELHANDLE		(MAPHANDLE->GetModel())
#define MAPTITLEHANDLE		(MAPHANDLE->GetTitle())
#define MAPWARPHANDLE		(MAPHANDLE->GetWarpHandle())

#include "..//Map/Map.h"

namespace MAP
{
	typedef class Handles *LPHANDLE;

	class Handles
	{
	public:
		Handles();
		virtual ~Handles();

		void Init();
		void Shutdown();

		void Update();

		void Render();

		BOOL OnMouseClick(INPUTS::LPMOUSE pcMouse);
		void OnMouseMove(INPUTS::LPMOUSE pcMouse);

		LPMODEL GetModel() { return m_pcModel; }
		LPTITLE GetTitle() { return m_pcTitle; }
		//LPWINDOW GetWarp() { return m_pcWindow; }
		WARP::Handle *GetWarpHandle() { return m_pcWarpHandle; }
	private:
		LPMODEL m_pcModel = NULL;
		LPTITLE m_pcTitle = NULL;
		//LPWARP m_pcWarp = NULL;
		//LPWINDOW m_pcWindow = NULL;
		WARP::Handle *m_pcWarpHandle = NULL;
	};
}