#include "stdafx.h"
#include "Player.h"
#include "SingleTexture.h"


CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
	Release();
}

int CPlayer::Update()
{
	KeyInput();

	D3DXMATRIX matScale, matRotZ, matTrans;

	D3DXMatrixScaling(
		&matScale,
		m_tInfo.vSize.x,
		m_tInfo.vSize.y,
		0.f);

	D3DXMatrixRotationZ(
		&matRotZ,
		D3DXToRadian(-m_tMoveInfo.fAngle));

	D3DXMatrixTranslation(
		&matTrans,
		m_tInfo.vPos.x - CScrollMgr::GetScrollPos().x,
		m_tInfo.vPos.y - CScrollMgr::GetScrollPos().y,
		0.f);

	m_tInfo.matWorld = matScale*matRotZ*matTrans;

	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);

	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

	return 0;
}

int CPlayer::Render(HDC hdc)
{
	
	float fCenterX = m_pTextureMgr->GetTexInfo(L"Player", L"Idle")->tImgInfo.Width*0.5f;
	float fCenterY = m_pTextureMgr->GetTexInfo(L"Player", L"Idle")->tImgInfo.Height*0.5f;

	m_pDeviceMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(
		m_pTextureMgr->GetTexInfo(L"Player", L"Idle")->pTexture,
		nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	return 0;
}

HRESULT CPlayer::Initialize()
{
	m_tInfo.vDir = { 0.f,0.f,0.f };
	m_tInfo.vLook = { 0.f,-1.f,0.f };
	m_tInfo.vPos = { WINCX*0.5f,WINCY*0.5f,0.f };
	m_tInfo.vSize = { 1.f,1.f,0.f };

	m_tMoveInfo.fAngle = 0.f;
	m_tMoveInfo.vSpeed = { 10.f,10.f,0.f };

	D3DXMatrixIdentity(&m_tInfo.matWorld);

	HRESULT hr = m_pTextureMgr->LoadTexture(
		m_pTextureMgr->SINGLE_TEXTURE,
		L"../Cube.png",
		L"Player",
		L"Idle");
	FAILED_CHECK_MSG_RETURN(hr, L"LoadTexture Failed!", E_FAIL);

	return S_OK;
}

void CPlayer::Release()
{
}

void CPlayer::KeyInput()
{
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_tInfo.vPos.x += m_tMoveInfo.vSpeed.x*m_tInfo.vDir.x;
		m_tInfo.vPos.y += m_tMoveInfo.vSpeed.y*m_tInfo.vDir.y;

		D3DXVECTOR3 vMove = { m_tMoveInfo.vSpeed.x*m_tInfo.vDir.x ,
			m_tMoveInfo.vSpeed.y*m_tInfo.vDir.y ,0.f };

		CScrollMgr::SetScrollPos(vMove);
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_tInfo.vPos.x -= m_tMoveInfo.vSpeed.x*m_tInfo.vDir.x;
		m_tInfo.vPos.y -= m_tMoveInfo.vSpeed.y*m_tInfo.vDir.y;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_tMoveInfo.fAngle += 5.f;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_tMoveInfo.fAngle -= 5.f;
}

CPlayer * CPlayer::Create()
{
	CPlayer* pInstance = new CPlayer;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
