#include "stdafx.h"
#include "SingleTexture.h"


CSingleTexture::CSingleTexture()
	:m_pTexInfo(nullptr)
{
}


CSingleTexture::~CSingleTexture()
{
	Release();
}

HRESULT CSingleTexture::LoadTexture(
	const wstring & wstrFilePath, 
	const wstring & wstrStateKey, 
	int iImgCount)
{
	HRESULT hr = 0;

	LPDIRECT3DDEVICE9 pDevice = m_pDeviceMgr->GetDevice();
	NULL_CHECK_MSG_RETURN(pDevice, L"SingleTexture GetDevice Failed!", E_FAIL);

	D3DXIMAGE_INFO tImgInfo;
	ZeroMemory(&tImgInfo, sizeof(D3DXIMAGE_INFO));

	hr = D3DXGetImageInfoFromFile(
		wstrFilePath.c_str(),
		&tImgInfo);
	FAILED_CHECK_RETURN(hr, E_FAIL);

	LPDIRECT3DTEXTURE9 pTexture = nullptr;

	hr = D3DXCreateTextureFromFileEx(
		pDevice,
		wstrFilePath.c_str(),
		tImgInfo.Width,
		tImgInfo.Height,
		tImgInfo.MipLevels,
		0,
		tImgInfo.Format,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		nullptr,
		nullptr,
		&pTexture);
	FAILED_CHECK_RETURN(hr, E_FAIL);

	m_pTexInfo = new TEX_INFO;
	m_pTexInfo->pTexture = pTexture;
	m_pTexInfo->tImgInfo = tImgInfo;

	return S_OK;
}

const TEX_INFO * CSingleTexture::GetTexInfo(
	const wstring & wstrStateKey,
	int iIndex)
{
	return m_pTexInfo;
}

CSingleTexture * CSingleTexture::Create(const wstring & wstrFilePath)
{
	CSingleTexture* pInstance = new CSingleTexture;

	if (FAILED(pInstance->LoadTexture(wstrFilePath)))
	{
		SafeDelete(pInstance);
		
		return nullptr;
	}

	return pInstance;
}

void CSingleTexture::Release()
{
	m_pTexInfo->pTexture->Release();
	SafeDelete(m_pTexInfo);
}