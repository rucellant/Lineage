#include "stdafx.h"
#include "ScrollMgr.h"


D3DXVECTOR3 CScrollMgr::m_vScrollPos = { 0.f, 0.f, 0.f };


CScrollMgr::CScrollMgr()
{
}


CScrollMgr::~CScrollMgr()
{
}

D3DXVECTOR3 CScrollMgr::GetScrollPos()
{
	return m_vScrollPos;
}

void CScrollMgr::SetScrollPos(const D3DXVECTOR3 & vMove)
{
	m_vScrollPos += vMove;
}
