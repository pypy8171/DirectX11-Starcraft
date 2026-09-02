#include "PathMgr.h"

wchar_t CPathMgr::g_szResPath[255] = L"";
wchar_t CPathMgr::g_szIncPath[255] = L"";
wchar_t CPathMgr::g_szProjectPath[255] = L"";

void CPathMgr::init()
{
	//// Resources 폴더까지의 경로를 구한다.
	//GetCurrentDirectory(255, g_szResPath);
	//wstring strPath = g_szResPath;

	//int iIdx = 0;
	//iIdx = strPath.rfind(L'Project\\', strPath.length()); // find first parameter from last.
	//strPath = strPath.substr(0, iIdx); // return except first parameter part.

	//// -> bin -> Resources
	//strPath += L"\\Game_Release\\content\\";
	//wcscpy_s(g_szResPath, 255, strPath.c_str());

	//// Resources 폴더까지의 경로를 구한다.
	GetCurrentDirectory(255, g_szResPath);

	//// 상위폴더 경로 
	for (UINT i = wcslen(g_szResPath) - 1; i > 0; --i)
	{
		if ('\\' == g_szResPath[i])
		{
			g_szResPath[i + 1] = 0;
			break;
		}
	}

	// -> bin -> Resources
	wcscat_s(g_szResPath, L"content\\");

	// Inc 폴더 경로 
	GetCurrentDirectory(255, g_szIncPath);

	int iCount = 0;
	for (UINT i = wcslen(g_szIncPath) - 1; i > 0; --i)
	{
		if ('\\' == g_szIncPath[i])
		{
			g_szIncPath[i + 1] = 0;
			++iCount;
		}

		if (iCount == 2)
			break;
	}

	wcscat_s(g_szIncPath, L"Project\\Include\\");


	// Proj 폴더 경로 
	GetCurrentDirectory(255, g_szProjectPath);

	iCount = 0;
	for (UINT i = wcslen(g_szProjectPath) - 1; i > 0; --i)
	{
		if ('\\' == g_szProjectPath[i])
		{
			g_szProjectPath[i + 1] = 0;
			++iCount;
		}

		if (iCount == 2)
			break;
	}

	wcscat_s(g_szProjectPath, L"Project\\");
}

wchar_t * CPathMgr::GetResPath()
{	
	return g_szResPath;
}

wchar_t * CPathMgr::GetIncPath()
{
	return g_szIncPath;
}

wchar_t * CPathMgr::GetProjectPath()
{
	return g_szProjectPath;
}
