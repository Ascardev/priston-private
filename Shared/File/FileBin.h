#pragma once

enum EBINID
{
	BIN_READ,
	BIN_WRITE,
	BIN_UPDATE,
};

namespace CFILE
{
	typedef class Bin *LPBIN;

	class Bin
	{
	public:
		Bin();
		Bin(const std::string &strFile,int iMode);
		virtual ~Bin();
		BOOL Open(const std::string &strFile,int iMode);
		BOOL IsOpen() const;
		void Read(void *ptr,UINT uSize);
		void Read(void *ptr,size_t iElementSize,size_t iCount);
		void Write(void *ptr,UINT uSize);
		void Seek(UINT uPos);
		int GetSize();
		void Close();
	private:
		FILE *m_pFile;
	};
}