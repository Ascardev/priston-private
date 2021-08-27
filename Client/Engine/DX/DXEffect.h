#pragma once

namespace DX
{
	typedef std::shared_ptr<class Effect>LPEFFECT;

	class Effect
	{
	public:
		Effect(LPD3DXEFFECT lpEffect,std::string strEffectFile);
		Effect(const Effect & c);
		virtual ~Effect();

		LPD3DXEFFECT Get() {return m_pEffect;}
		const std::string &GetFile() const {return m_strEffectFile;}
		UINT GetPasses() {return m_uPasses;}

		void OnLostDevice();
		void OnResetDevice();

		BOOL SetTechnique(std::string strTechnique);

		int Begin();
		void End();

		BOOL BeginPass(UINT uPass);
		void EndPass();

		void CommitChanges();
		void Renew(LPD3DXEFFECT lpEffect);

		void SetMatrix(const std::string & strVariableName,const D3DXMATRIX &mMatrix);
		void SetMatrixArray(const std::string &strVariableName,const D3DXMATRIX *pmaValue,UINT uCount);
		void SetInt(const std::string &strVariableName,int iValue);
		void SetIntArray(const std::string &strVariableName,const int *piaValue,UINT uCount);
		void SetFloat(const std::string &strVariableName,float fValue);
		void SetFloatArray(const std::string &strVariableName,const float *pfaValue,UINT uCount);
		void SetBool(const std::string &strVariableName,BOOL bValue);
		void SetBoolArray(const std::string &strVariableName,const BOOL *pbaValue,UINT uCount);
		void SetTexture(const std::string &strVariableName, LPDIRECT3DBASETEXTURE9 pTexture);
	private:
		LPD3DXEFFECT m_pEffect;
		std::string m_strEffectFile;
		UINT m_uPasses = 0;
	};
}