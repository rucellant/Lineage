#pragma once
#include "Texture.h"

class CSingleTexture : public CTexture
{
private:
	TEX_INFO* m_pTexInfo;

private:
	CSingleTexture();

public:
	virtual ~CSingleTexture();

public:
	// CTexture��(��) ���� ��ӵ�
	virtual HRESULT LoadTexture(
		const wstring & wstrFilePath, 
		const wstring & wstrStateKey = L"",
		int iImgCount = 0) override;

	virtual const TEX_INFO * GetTexInfo(
		const wstring & wstrStateKey = L"", 
		int iIndex = 0) override;

	static CSingleTexture* Create(const wstring& wstrFilePath);

private:
	// CTexture��(��) ���� ��ӵ�
	virtual void Release() override;

};

