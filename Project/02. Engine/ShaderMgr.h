#pragma once
#include "global.h" // 리소스 일종이지만 리소스로 분류만 안함.

class CShader;
class CCamera;

class CShaderMgr
{
	SINGLE(CShaderMgr);

private:
	map<wstring, CShader*>	m_mapShader;



public:
	void init();
	void AddShader(const wstring& _strKey, CShader* _pShader);

	CShader* FindShader(const wstring& _strKey);
};

