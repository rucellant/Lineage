// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

//Standard Headers
#include <string>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>

using namespace std;


//DirectX
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")

#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")

//Users Headers
#include "Define.h"
#include "Enum.h"
#include "Extern.h"
#include "Functor.h"
#include "Function.h"
#include "Struct.h"

//Managers
#include "DeviceMgr.h"
#include "TextureMgr.h"
#include "ScrollMgr.h"

//vld
#include "vld.h"