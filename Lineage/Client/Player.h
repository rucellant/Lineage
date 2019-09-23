#pragma once
#include "GameObj.h"

class CTexture;

class CPlayer : public CGameObj
{
private:
	CPlayer();

public:
	virtual ~CPlayer();

public:
	// CGameObj을(를) 통해 상속됨
	virtual int Update() override;
	virtual int Render(HDC hdc) override;

private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

private:
	void KeyInput();

public:
	static CPlayer* Create();
};

