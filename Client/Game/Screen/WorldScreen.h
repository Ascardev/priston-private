#pragma once

class CWorldScreen : public CScreen
{
public:
	CWorldScreen();
	virtual ~CWorldScreen();

	BOOL Init();
	void Shutdown();

	void Render3D();
	void Render2D();

	EScreen Frame();

	void OnMouseMove(class INPUTS::Mouse *pcMouse);
	BOOL OnMouseClick(class INPUTS::Mouse *pcMouse);

	void UpdateObjectsSettings();
};
