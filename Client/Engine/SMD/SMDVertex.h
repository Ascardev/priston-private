#pragma once


enum EBlendType
{
	BLENDTYPE_None = 0,
	BLENDTYPE_Alpha = 0x00000001,
	BLENDTYPE_Color = 0x00000002,
	BLENDTYPE_Shadow = 0x00000003,
	BLENDTYPE_Lamp = 0x00000004,
	BLENDTYPE_AddColor = 0x00000005,
	BLENDTYPE_InvShadow = 0x00000006,
};

namespace SMD
{
	struct Vertex
	{
		float x;
		float y;
		float z;
		float rhw;
		D3DCOLOR d3dColor;
		D3DCOLOR d3dSpecular;
		float u;
		float v;
	};

	struct Billboard
	{
		Point3D sPosition;
		UINT uWidth;
		UINT uHeight;
		TextureRangle2D sRect;
		UINT uID;
		Color4D sColor;
	};
}