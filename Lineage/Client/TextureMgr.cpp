#include "stdafx.h"
#include "TextureMgr.h"
#include "MultiTexture.h"
#include "SingleTexture.h"


IMPLEMENT_SINGLETON(CTextureMgr)


CTextureMgr::CTextureMgr()
{
}


CTextureMgr::~CTextureMgr()
{
	Release();
}

const TEX_INFO * CTextureMgr::GetTexInfo(
	const wstring & wstrObjectKey, 
	const wstring & wstrStateKey, 
	int iIndex)
{
	auto find_iter = m_mapTexture.find(wstrObjectKey);

	if (find_iter == m_mapTexture.end())
		return nullptr;

	return find_iter->second->GetTexInfo(wstrStateKey, iIndex);
}

HRESULT CTextureMgr::LoadTexture(
	TEXTURE_TYPE eType, 
	const wstring & wstrFilePath, 
	const wstring & wstrObjectKey, 
	const wstring & wstrStateKey, 
	int iImgCount)
{
	auto find_iter = m_mapTexture.find(wstrObjectKey);


	//오브젝트키가 없는 경우
	//오브젝트키가 있고 멀티텍스쳐인 경우
	if (find_iter == m_mapTexture.end())
	{
		CTexture* pTexture = nullptr;

		switch (eType)
		{
		case SINGLE_TEXTURE:
			pTexture = CSingleTexture::Create(wstrFilePath);
			break;
		case MULTI_TEXTURE:
			pTexture = CMultiTexture::Create(wstrFilePath, wstrStateKey, iImgCount);
			break;
		}

		NULL_CHECK_RETURN(pTexture, E_FAIL);
		m_mapTexture.insert({ wstrObjectKey,pTexture });
	}
	else if (eType == MULTI_TEXTURE)
	{
		HRESULT hr = m_mapTexture[wstrObjectKey]->LoadTexture(
			wstrFilePath, wstrStateKey, iImgCount);
		FAILED_CHECK_RETURN(hr, E_FAIL);
	}

	return S_OK;
}

void CTextureMgr::Release()
{
	for (auto& MyPair : m_mapTexture)
		SafeDelete(MyPair.second);

	m_mapTexture.clear();
}
