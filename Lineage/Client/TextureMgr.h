#pragma once

class CTexture;
class CTextureMgr
{
DECLARE_SINGLETON(CTextureMgr)

private:
	CTextureMgr();
	~CTextureMgr();

public:
	enum TEXTURE_TYPE { SINGLE_TEXTURE, MULTI_TEXTURE };

private:
	map<wstring, CTexture*> m_mapTexture;

public:
	const TEX_INFO* GetTexInfo(
		const wstring& wstrObjectKey,
		const wstring& wstrStateKey = L"",
		int iIndex = 0);

	HRESULT LoadTexture(
		TEXTURE_TYPE eType,
		const wstring& wstrFilePath,
		const wstring& wstrObjectKey,
		const wstring& wstrStateKey = L"",
		int iImgCount = 0);

private:
	void Release();
};

