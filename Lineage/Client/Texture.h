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
		const wstring& wstrFilePath,					//���ϰ��
		const wstring& wstrStateKey = L"",				//���� Ű
		int iImgCount = 0) PURE;						//�̹��� ����

public:
	virtual const TEX_INFO* GetTexInfo(
		const wstring& wstrStateKey = L"",				//���� Ű
		int iIndex = 0) PURE;							//�̹��� ��ȣ
	
protected:
	virtual void Release() PURE;
};

