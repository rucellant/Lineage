#pragma once

class CGameObj
{
protected:
	INFO m_tInfo;
	MOVE_INFO m_tMoveInfo;

	CDeviceMgr* m_pDeviceMgr;
	CTextureMgr* m_pTextureMgr;

protected:
	CGameObj();

public:
	virtual ~CGameObj();

public:
	virtual int Update() PURE;
	virtual int Render(HDC hdc) PURE;

private:
	virtual HRESULT Initialize() PURE;
	virtual void Release() PURE;
};

