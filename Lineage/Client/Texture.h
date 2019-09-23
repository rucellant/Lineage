#pragma once

class CTexture
{
protected:
	CDeviceMgr* m_pDeviceMgr;

protected:
	CTexture();

public:
	virtual ~CTexture();

public:
	virtual HRESULT LoadTexture(
		const wstring& wstrFilePath,					//파일경로
		const wstring& wstrStateKey = L"",				//상태 키
		int iImgCount = 0) PURE;						//이미지 갯수

public:
	virtual const TEX_INFO* GetTexInfo(
		const wstring& wstrStateKey = L"",				//상태 키
		int iIndex = 0) PURE;							//이미지 번호
	
protected:
	virtual void Release() PURE;
};

