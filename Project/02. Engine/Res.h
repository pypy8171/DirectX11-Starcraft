#pragma once
#include "Entity.h"
#include "Ptr.h"

class CMesh;
class CPrefab;
class CMaterial;
class CSound;
class CTexture;

class CRes :
	public CEntity
{
private:
	UINT		m_iRef; // 리소스 참조 횟수

protected:
	wstring		m_strPath;  // 리소스의 상대 경로(저장 위치)

private: // 이게 왜 public? private아닌가
	void AddRef() { ++m_iRef; }
	void SubRef() { --m_iRef; }
	void SetPath(const wstring& _strPath) { m_strPath = _strPath; }

public:
	virtual int update() { return 0; }

public:
	virtual void Load(const wstring& _strFullPath, const wstring& _strKey) {};
	virtual void FileSave(FILE* _pFile) = 0;
public:
	CLONE_DISABLE(CRes);

public:
	CRes();
	virtual ~CRes();

	friend class CMesh;
	friend class CPrefab;
	friend class CMaterial;
	friend class CSound;
	friend class CTexture;

	friend class CResMgr;
};

