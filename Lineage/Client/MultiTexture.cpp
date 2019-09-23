#include "stdafx.h"
#include "MultiTexture.h"


CMultiTexture::CMultiTexture()
{
}


CMultiTexture::~CMultiTexture()
{
	Release();
}

HRESULT CMultiTexture::LoadTexture(
	const wstring & wstrFilePath, 
	const wstring & wstrStateKey,
	int iImgCount)
{
	auto find_iter = m_mapMultiTexture.find(wstrStateKey);

	if (find_iter != m_mapMultiTexture.end())
		return E_FAIL;

	HRESULT hr = 0;
	TEX_INFO* pTexInfo = nullptr;

	LPDIRECT3DDEVICE9 pDevice = m_pDeviceMgr->GetDevice();
	NULL_CHECK_RETURN(pDevice, E_FAIL);

	D3DXIMAGE_INFO tImgInfo;
	ZeroMemory(&tImgInfo, sizeof(D3DXIMAGE_INFO));

	TCHAR szFullPath[256] = L"";
	
	for (int i = 0; i < iImgCount; i++)
	{
		swprintf_s(szFullPath, wstrFilePath.c_str(), i);

		hr = D3DXGetImageInfoFromFile(szFullPath, &tImgInfo);
		FAILED_CHECK_RETURN(hr, E_FAIL);

		LPDIRECT3DTEXTURE9 pTexture = nullptr;

		hr = D3DXCreateTextureFromFileEx(
			pDevice,
			szFullPath,
			tImgInfo.Width,
			tImgInfo.Height,
			tImgInfo.MipLevels,
			0,
			tImgInfo.Format,
			D3DPOOL_MANAGED,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			D3DCOLOR_ARGB(255, 255, 255, 255),
			nullptr,
			nullptr,
			&pTexture);
		FAILED_CHECK_RETURN(hr, E_FAIL);

		pTexInfo = new TEX_INFO;
		pTexInfo->pTexture = pTexture;
		pTexInfo->tImgInfo = tImgInfo;

		m_mapMultiTexture[wstrStateKey].push_back(pTexInfo);
	}

	return S_OK;
}

const TEX_INFO * CMultiTexture::GetTexInfo(
	const wstring & wstrStateKey, 
	int iIndex)
{
	auto iter_find = m_mapMultiTexture.find(wstrStateKey);

	if (iter_find == m_mapMultiTexture.end())
		return nullptr;

	return iter_find->second[iIndex];
}

CMultiTexture * CMultiTexture::Create(
	const wstring wstrFilePath, 
	const wstring wstrStateKey, 
	int iImgCount)
{
	CMultiTexture* pInstance = new CMultiTexture;

	if (FAILED(pInstance->LoadTexture(wstrFilePath, wstrStateKey, iImgCount)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CMultiTexture::Release()
{
	map<wstring, vector<TEX_INFO*>>::iterator iter;

	for (iter = m_mapMultiTexture.begin(); iter != m_mapMultiTexture.end(); ++iter)
	{
		for (size_t i = 0; i < iter->second.size(); i++)
		{
			iter->second[i]->pTexture->Release();
			SafeDelete(iter->second[i]);
		}
			
		iter->second.clear();
		iter->second.shrink_to_fit();
	}

	m_mapMultiTexture.clear();
}
