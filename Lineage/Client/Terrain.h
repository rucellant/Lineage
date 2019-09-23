#pragma once
#include "GameObj.h"

class CTerrain : public CGameObj
{
private:
	vector<TILE_INFO*> m_vecTile;

private:
	CTerrain();

public:
	virtual ~CTerrain();

public:
	// CGameObj을(를) 통해 상속됨
	virtual int Update() override;
	virtual int Render(HDC hdc) override;
	
private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CTerrain* Create();
};

