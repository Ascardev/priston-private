#include "StdAfx.h"
#include "DXEffect.h"

namespace DX
{
	Effect::Effect(LPD3DXEFFECT lpEffect,std::string strEffectFile):m_pEffect(lpEffect),m_strEffectFile(strEffectFile)
	{
		ADDREF(m_pEffect);
	}
	Effect::Effect(const Effect &c):m_pEffect(c.m_pEffect),m_strEffectFile(c.m_strEffectFile)
	{
		ADDREF(m_pEffect);
	}
	Effect::~Effect()
	{
		RELEASE(m_pEffect);
	}
	void Effect::OnLostDevice()
	{
		m_pEffect ? m_pEffect->OnLostDevice() : 0;
	}
	void Effect::OnResetDevice()
	{
		m_pEffect ? m_pEffect->OnResetDevice() : 0;
	}
	BOOL Effect::SetTechnique(std::string strTechnique)
	{
		if (m_pEffect)
			return SUCCEEDED(m_pEffect->SetTechnique(strTechnique.c_str()));

		return FALSE;
	}
	int Effect::Begin()
	{
		if (m_pEffect)
		{
			m_uPasses = 0;
			return SUCCEEDED(m_pEffect->Begin(&m_uPasses,D3DXFX_DONOTSAVESAMPLERSTATE)) ? m_uPasses : -1;
		}

		return -1;
	}
	void Effect::End()
	{
		m_pEffect ? m_pEffect->End() : 0;
	}
	BOOL Effect::BeginPass(UINT uPass)
	{
		if (m_pEffect)
			return SUCCEEDED(m_pEffect->BeginPass(uPass));

		return FALSE;
	}
	void Effect::EndPass()
	{
		m_pEffect ? m_pEffect->EndPass() : 0;
	}
	void Effect::SetMatrix(const std::string & strVariableName,const D3DXMATRIX &mMatrix)
	{
		HRESULT hr;
		Logger DXLog;

		if (m_pEffect)
		{
			if (FAILED(hr = m_pEffect->SetMatrix(strVariableName.c_str(),&mMatrix)))
			{
				DXLog.Print("ID3DXEffect::SetMatrix() failed");
			}
		}
	}
	void Effect::SetMatrixArray(const std::string &strVariableName,const D3DXMATRIX *pmaValue,UINT uCount)
	{
		HRESULT hr;
		Logger DXLog;

		if (m_pEffect)
		{
			if (FAILED(hr = m_pEffect->SetMatrixArray(strVariableName.c_str(),pmaValue,uCount)))
			{
				DXLog.Print("ID3DXEffect::SetMatrixArray() failed");
			}
		}
	}
	void Effect::SetInt(const std::string &strVariableName,int iValue)
	{
		m_pEffect ? m_pEffect->SetInt(strVariableName.c_str(), iValue) : 0;
	}
	void Effect::SetIntArray(const std::string &strVariableName,const int *piaValue,UINT uCount)
	{
		m_pEffect ? m_pEffect->SetIntArray(strVariableName.c_str(), piaValue, uCount) : 0;
	}
	void Effect::SetFloat(const std::string &strVariableName,float fValue)
	{
		m_pEffect ? m_pEffect->SetFloat(strVariableName.c_str(), fValue) : 0;
	}
	void Effect::SetFloatArray(const std::string &strVariableName,const float *pfaValue,UINT uCount)
	{
		m_pEffect ? m_pEffect->SetFloatArray(strVariableName.c_str(), pfaValue, uCount) : 0;
	}
	void Effect::SetBool(const std::string &strVariableName,BOOL bValue)
	{
		m_pEffect ? m_pEffect->SetBool(strVariableName.c_str(), bValue) : 0;
	}
	void Effect::SetBoolArray(const std::string &strVariableName,const BOOL *pbaValue,UINT uCount)
	{
		m_pEffect ? m_pEffect->SetBoolArray(strVariableName.c_str(), pbaValue, uCount) : 0;
	}
	void Effect::SetTexture(const std::string &strVariableName, LPDIRECT3DBASETEXTURE9 pTexture)
	{
		m_pEffect ? m_pEffect->SetTexture(strVariableName.c_str(), pTexture) : 0;
	}
	void Effect::CommitChanges()
	{
		m_pEffect ? m_pEffect->CommitChanges() : 0;
	}
	void Effect::Renew(LPD3DXEFFECT lpEffect)
	{
		RELEASE(m_pEffect);

		m_pEffect = lpEffect;

		ADDREF(m_pEffect);
	}
}