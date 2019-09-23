#include "stdafx.h"
#include "Terrain.h"


CTerrain::CTerrain()
{
}


CTerrain::~CTerrain()
{
	Release();
}

int CTerrain::Update()
{
	return 0;
}

int CTerrain::Render(HDC hdc)
{
	D3DXMATRIX matScale, matTrans;

	const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(L"Terrain", L"Tile");

	int iColEnd = WINCX / pTexInfo->tImgInfo.Width + 2;
	int iRowEnd = WINCY / pTexInfo->tImgInfo.Height * 2 + 2;

	for (int iRow = 0; iRow < iRowEnd; iRow++)
	{
		for (int iCol = 0; iCol < iColEnd; iCol++)
		{
			int iIndex = iRow*(WINCX / pTexInfo->tImgInfo.Width) * 2 + iCol;

			D3DXMatrixScaling(
				&matScale,
				m_vecTile[iIndex]->vSize.x,
				m_vecTile[iIndex]->vSize.y,
				0.f);

			D3DXMatrixTranslation(
				&matTrans,
				m_vecTile[iIndex]->vPos.x - CScrollMgr::GetScrollPos().x,
				m_vecTile[iIndex]->vPos.y - CScrollMgr::GetScrollPos().y,
				0.f);

			m_tInfo.matWorld = matScale*matTrans;

			const TEX_INFO* pTexInfo =
				m_pTextureMgr->GetTexInfo(L"Terrain", L"Tile", m_vecTile[iIndex]->byDrawID);
			NULL_CHECK_MSG_RETURN(pTexInfo, L"Terrain GetTexInfo Failed!", E_FAIL);

			float fCenterX = pTexInfo->tImgInfo.Width*0.5f;
			float fCenterY = pTexInfo->tImgInfo.Height*0.5f;

			m_pDeviceMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
			m_pDeviceMgr->GetSprite()->Draw(
				pTexInfo->pTexture,
				nullptr,
				&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
				nullptr,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
	/*for (size_t i = 0; i < m_vecTile.size(); i++)
	{
		D3DXMatrixScaling(
			&matScale,
			m_vecTile[i]->vSize.x,
			m_vecTile[i]->vSize.y,
			0.f);

		D3DXMatrixTranslation(
			&matTrans,
			m_vecTile[i]->vPos.x,
			m_vecTile[i]->vPos.y,
			0.f);

		m_tInfo.matWorld = matScale*matTrans;

		const TEX_INFO* pTexInfo = 
			m_pTextureMgr->GetTexInfo(L"Terrain", L"Tile", m_vecTile[i]->byDrawID);
		NULL_CHECK_MSG_RETURN(pTexInfo, L"Terrain GetTexInfo Failed!", E_FAIL);

		float fCenterX = pTexInfo->tImgInfo.Width*0.5f;
		float fCenterY = pTexInfo->tImgInfo.Height*0.5f;

		m_pDeviceMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
		m_pDeviceMgr->GetSprite()->Draw(
			pTexInfo->pTexture,
			nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
			nullptr,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}*/

	return 0;
}

HRESULT CTerrain::Initialize()
{
	HRESULT hr = 0;

	//텍스처 로드
	hr = m_pTextureMgr->LoadTexture(
		CTextureMgr::MULTI_TEXTURE,
		L"../Texture/Tile/NormalTile/Tile_%d.png",
		L"Terrain",
		L"Tile",
		216);
	FAILED_CHECK_RETURN(hr, E_FAIL);

	const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(L"Terrain", L"Tile");

	int iColEnd = (WINCX / pTexInfo->tImgInfo.Width) * 2;
	int iRowEnd = (WINCY / pTexInfo->tImgInfo.Height) * 3;

	float fX = 0.f, fY = 0.f;

	for (int iRow = 0; iRow < iRowEnd; iRow++)
	{
		for (int iCol = 0; iCol < iColEnd; iCol++)
		{
			fX = iCol*pTexInfo->tImgInfo.Width + (iRow % 2)*pTexInfo->tImgInfo.Width*0.5f;
			fY = iRow*pTexInfo->tImgInfo.Height*0.5f;

			TILE_INFO* pTile = new TILE_INFO;
			pTile->vSize = { 1.f,1.f,0.f };
			pTile->vPos = { fX,fY,0.f };
			pTile->byOption = 0;
			pTile->byDrawID = 2;

			m_vecTile.push_back(pTile);
		}
	}

	return S_OK;
}

void CTerrain::Release()
{
	vector<TILE_INFO*>::iterator iter;

	for (iter = m_vecTile.begin(); iter != m_vecTile.end(); ++iter)
		SafeDelete(*iter);

	m_vecTile.clear();
	m_vecTile.shrink_to_fit();
}

CTerrain * CTerrain::Create()
{
	CTerrain* pInstance = new CTerrain;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);

		return nullptr;
	}

	return pInstance;
}
