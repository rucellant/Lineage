#pragma once

class CScrollMgr
{
private:
	static D3DXVECTOR3 m_vScrollPos;

private:
	CScrollMgr();
	~CScrollMgr();

public:
	static D3DXVECTOR3 GetScrollPos();

	static void SetScrollPos(const D3DXVECTOR3& vMove);
};

