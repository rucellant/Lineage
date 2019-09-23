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
	// CGameObj��(��) ���� ��ӵ�
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

