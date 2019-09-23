#include "stdafx.h"
#include "GameObj.h"


CGameObj::CGameObj()
	:m_pDeviceMgr(CDeviceMgr::GetInstance()),
	m_pTextureMgr(CTextureMgr::GetInstance())
{
}


CGameObj::~CGameObj()
{
}
