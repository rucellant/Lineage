#pragma once

class CDeviceMgr
{
DECLARE_SINGLETON(CDeviceMgr)

private:
	CDeviceMgr();
	~CDeviceMgr();

private:
	LPDIRECT3D9			m_pSDK;
	LPDIRECT3DDEVICE9	m_pDevice;
	LPD3DXSPRITE		m_pSprite;

public:
	enum MODE { MODE_FULL, MODE_WIN };

public:
	HRESULT InitDevice(MODE eMode);

	void Render_Begin();
	void Render_End();

private:
	void Release();

public:
	LPDIRECT3DDEVICE9	GetDevice();
	LPD3DXSPRITE		GetSprite();

};

