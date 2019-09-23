#pragma once
#include "Texture.h"

class CMultiTexture : public CTexture
{
private:
	map<wstring, vector<TEX_INFO*>> m_mapMultiTexture;

private:
	CMultiTexture();

public:
	virtual ~CMultiTexture();

public:
	// CTexture을(를) 통해 상속됨
	virtual HRESULT LoadTexture(
		const wstring & wstrFilePath,
		const wstring & wstrStateKey = L"",
		int iImgCount = 0) override;

	virtual const TEX_INFO * GetTexInfo(
		const wstring & wstrStateKey = L"",
		int iIndex = 0) override;

	static CMultiTexture* Create(
		const wstring wstrFilePath,
		const wstring wstrStateKey,
		int iImgCount);

private:
	virtual void Release() override;
};

