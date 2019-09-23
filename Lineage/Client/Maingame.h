#pragma once

class CGameObj;
class CMaingame
{
private:
	HDC			m_hDC;
		
	CDeviceMgr*		m_pDeviceMgr;
	CTextureMgr*	m_pTextureMgr;

	CGameObj* m_pPlayer;
	CGameObj* m_pTerrain;

private:
	CMaingame();

public:
	~CMaingame();

public:
	int Update();
	int Render();

private:
	HRESULT Initialize();
	void Release();

public:
	static CMaingame* Create();
};

