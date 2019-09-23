#include "stdafx.h"
#include "Maingame.h"
#include "Player.h"
#include "Terrain.h"

CMaingame::CMaingame()
	:m_pDeviceMgr(CDeviceMgr::GetInstance()),
	m_pTextureMgr(CTextureMgr::GetInstance()),
	m_pPlayer(nullptr),
	m_pTerrain(nullptr)
{
}


CMaingame::~CMaingame()
{
	Release();
}

int CMaingame::Update()
{
	m_pPlayer->Update();

	return 0;
}

int CMaingame::Render()
{
	m_pDeviceMgr->Render_Begin();

	m_pTerrain->Render(m_hDC);

	m_pPlayer->Render(m_hDC);

	m_pDeviceMgr->Render_End();

	return 0;
}

HRESULT CMaingame::Initialize()
{
	HRESULT hr = 0;
	hr = m_pDeviceMgr->InitDevice(m_pDeviceMgr->MODE_WIN);
	FAILED_CHECK_MSG_RETURN(hr, L"InitDevice Failed!", E_FAIL);

	m_hDC = GetDC(g_hWnd);

	m_pPlayer = CPlayer::Create();
	NULL_CHECK_MSG_RETURN(m_pPlayer, L"Player Create Failed!", E_FAIL);

	m_pTerrain = CTerrain::Create();
	NULL_CHECK_MSG_RETURN(m_pPlayer, L"Terrain Create Failed!", E_FAIL);

	return S_OK;
}

void CMaingame::Release()
{
	SafeDelete(m_pPlayer);
	SafeDelete(m_pTerrain);
	
	m_pTextureMgr->DestroyInstance();
	m_pDeviceMgr->DestroyInstance();
}

CMaingame * CMaingame::Create()
{
	CMaingame* pInstance = new CMaingame;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
