#include "stdafx.h"
#include "DeviceMgr.h"


IMPLEMENT_SINGLETON(CDeviceMgr)


CDeviceMgr::CDeviceMgr()
	:m_pSDK(nullptr),
	m_pDevice(nullptr),
	m_pSprite(nullptr)
{
}


CDeviceMgr::~CDeviceMgr()
{
	Release();
}

HRESULT CDeviceMgr::InitDevice(MODE eMode)
{
	HRESULT hr = 0;

	// IDirect3D9 객체 생성
	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);
	NULL_CHECK_MSG_RETURN(m_pSDK, L"Direct3DCreate9 Failed!", E_FAIL);

	// 장치 조사
	D3DCAPS9 d3dcaps;
	ZeroMemory(&d3dcaps, sizeof(D3DCAPS9));

	hr = m_pSDK->GetDeviceCaps(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		&d3dcaps);
	FAILED_CHECK_MSG_RETURN(hr, L"GetDeviceCaps Failed!", E_FAIL);

	//버텍스 프로세싱 조사
	DWORD vp = 0;

	if (d3dcaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	// IDirect3DDevice9 객체 생성
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	// 렌더링 환경 설정.
	d3dpp.BackBufferWidth = WINCX;
	d3dpp.BackBufferHeight = WINCY;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = g_hWnd;
	d3dpp.Windowed = eMode;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	/* FullScreen_RefreshRateInHz must be zero for Windowed mode */
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	hr = m_pSDK->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		g_hWnd,
		vp,
		&d3dpp,
		&m_pDevice);
	FAILED_CHECK_MSG_RETURN(hr, L"CreateDevice Failed!", E_FAIL);

	hr = D3DXCreateSprite(m_pDevice, &m_pSprite);
	FAILED_CHECK_MSG_RETURN(hr, L"D3DXCreateSprite Failed", E_FAIL);

	return S_OK;
}

void CDeviceMgr::Render_Begin()
{
	m_pDevice->Clear(
		0,
		nullptr,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		D3DCOLOR_ARGB(255, 0, 0, 255),
		1.f,
		0);

	m_pDevice->BeginScene();
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void CDeviceMgr::Render_End()
{
	m_pSprite->End();
	m_pDevice->EndScene();

	m_pDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

void CDeviceMgr::Release()
{
	m_pSprite->Release();
	m_pDevice->Release();
	m_pSDK->Release();
}

LPDIRECT3DDEVICE9 CDeviceMgr::GetDevice()
{
	return m_pDevice;
}

LPD3DXSPRITE CDeviceMgr::GetSprite()
{
	return m_pSprite;
}
