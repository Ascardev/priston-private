#pragma once

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
}

static D3DXMATRIX X3DMatrixToD3DXMatrix(const Matrix4DF & m)
{
	D3DXMATRIX c;

	CopyMemory(c.m, m.m, sizeof(float) * 4 * 4);

	return c;
}
static Matrix4DF D3DXMatrixToX3DMatrix(const D3DXMATRIX & m)
{
	Matrix4DF c;

	CopyMemory(c.m, m.m, sizeof(float) * 4 * 4);

	return c;
}

static float easeInOutCircf(float t, float b, float c, float d)
{
	return (t /= d / 2) < 1 ? -c / 2 * (sqrt(1 - t * t) - 1) + b : c / 2 * (sqrt(1 - t * (t -= 2)) + 1) + b;
}
Vector4DF D3DMath_QuaternionSlerp(Vector4DF sVectorA, Vector4DF sVectorB, float fAlpha)
{
	float fScale1, fScale2;

	float fCosTheta = sVectorA.Dot(sVectorB);

	if (fCosTheta < 0.0f)
	{
		sVectorA.Negative();
		fCosTheta = -fCosTheta;
	}
	if (fCosTheta + 1.0f > 0.05f)
	{
		if (1.0f - fCosTheta < 0.05f)
		{
			fScale1 = 1.0f - fAlpha;
			fScale2 = fAlpha;
		}
		else
		{
			float fTheta = (float)acos(fCosTheta);
			float fSinTheta = (float)sin(fTheta);

			fScale1 = (float)sin(fTheta * (1.0f - fAlpha)) / fSinTheta;
			fScale2 = (float)sin(fTheta * fAlpha) / fSinTheta;
		}
	}
	else
	{
		sVectorB = Vector4DF(-sVectorA.fY, +sVectorA.fX, -sVectorA.fW, +sVectorA.fZ);
		fScale1 = (float)sin(D3DX_PI * (0.5f - fAlpha));
		fScale2 = (float)sin(D3DX_PI * fAlpha);
	}

	return sVectorA * fScale1 + sVectorB * fScale2;
}