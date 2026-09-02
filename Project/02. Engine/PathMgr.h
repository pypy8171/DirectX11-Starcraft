#pragma once

#include "global.h"

class CPathMgr
{
private:
	static wchar_t g_szResPath[255];
	static wchar_t g_szIncPath[255];
	static wchar_t g_szProjectPath[255];

public:
	static void init();
	static wchar_t* GetResPath();
	static wchar_t* GetIncPath();
	static wchar_t* GetProjectPath();


private:
	CPathMgr() {};
	~CPathMgr() {};
};

