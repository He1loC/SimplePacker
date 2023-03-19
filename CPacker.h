#pragma once
#include <vector>


struct ConfigInfo
{
	DWORD m_dwCodeSize;				//解压缩代码大小
	DWORD m_dwPackedDataSize;		//处理前数据大小
	DWORD m_dwUnpackedDataSize;		//处理后的数据大小
};

struct tagImportAPI
{
	bool m_bIsImportByName;
	CString m_strAPIName;
	WORD m_wAPIOrdinal;
};

struct tagImportInFo
{
	CString m_strDllName;
	DWORD m_dwIATRVA;
	std::vector<tagImportAPI> m_vecAPIs;
};



class CPacker
{
public:
	CPacker()
	{

	}
	~CPacker()
	{
		if (m_pSrcPeBuf)
		{
			UnmapViewOfFile(m_pSrcPeBuf);
		}

		if (m_hMap)
		{
			CloseHandle(m_hMap);
		}

		if (m_hFile != INVALID_HANDLE_VALUE)
		{
			CloseHandle(m_hFile);
		}
	}

	bool Pack(CString strOriginFileName, CString strTargetFileName);

	DWORD CalAlignment(DWORD dwSize, DWORD dwAlign)
	{
		if (dwSize%dwAlign == 0)
		{
			return dwSize;
		}

		return (dwSize / dwAlign + 1) * dwAlign;
	}


	DWORD CalFAwithRVA(DWORD IN dwRVA);

	// parse PE
private:
	bool ParsePe(CString strFileName);
	HANDLE m_hFile = INVALID_HANDLE_VALUE;
	HANDLE m_hMap = NULL;
	LPBYTE m_pSrcPeBuf = NULL;

	//PE info
	PIMAGE_DOS_HEADER m_pDosHdr = NULL;
	PIMAGE_NT_HEADERS m_pNtHdr = NULL;
	PIMAGE_SECTION_HEADER m_pSecHdr = NULL;
	PIMAGE_IMPORT_DESCRIPTOR m_pImportTable = NULL;
	LPBYTE m_pOriginImportTable = nullptr;
	DWORD m_dwOriginImportTableSize = 0;

	DWORD  m_dwFileSize = 0;
	DWORD  m_dwFileAlign = 0;
	DWORD  m_dwSectionAlign = 0;
	DWORD  m_dwSecsTotalSize = 0;


	std::vector<tagImportInFo> m_vecImports;

	// compress sections
private:
	bool EncryptSecs();
	LPBYTE m_pEncryptedBuf = NULL; //加密后数据缓冲区
	DWORD  m_dwEncryptedSize = 0;  //加密后数据大小


	// Get Unpack Code
private:
	bool GetUnpackCode();
	LPBYTE	m_pUnpackCode = nullptr;
	DWORD m_dwUnpackCodeSize = 0;
	DWORD m_dwUnpackCodeEPoffset = 0;
	
	// prepare Section Data (config + unpack code + compressed data + data dir)
private:
	bool PrepareSecData();
	LPBYTE	m_pSecData = nullptr;
	DWORD m_dwSecDataSize = 0;

	// prepare Section Table/hdrs
private:
	bool PrepareSecHdrs();
	IMAGE_SECTION_HEADER m_ArrSecHdrs[2] = {};

	// prepare New Hdrs
private:
	bool PrepareNewHdrs();
	LPBYTE m_pNewPeHdrs = NULL; //新的PE头
	DWORD  m_dwNewHdrsSize = 0; //新PE头大小


private:
	bool WriteNewPE(CString strFileName);

};
