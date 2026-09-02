#pragma once
#include "Component.h"
class CTransform :
	public CComponent
{
private:
	Vec3		m_vLocalPos;
	Vec3		m_vLocalScale;
	Vec3		m_vLocalRotate;

	Vec3		m_vLocalDir[(UINT)DIR_TYPE::END];
	Vec3		m_vWorldDir[(UINT)DIR_TYPE::END];

	Vec3		m_vParentScale;
	Vec3		m_vParentPos;

	Matrix		m_matWorld;
	Matrix		m_matEachWorld;

	bool		m_bUseParent;

public:
	void SetLocalPos(Vec3 _vLocalPos) { m_vLocalPos = _vLocalPos; }
	void SetLocalScale(Vec3 _vLocalScale) { m_vLocalScale = _vLocalScale; }
	void SetLocalRotate(Vec3 _vLocalRotate) { m_vLocalRotate = _vLocalRotate; }

	void SetUseParent(bool _b) { m_bUseParent = _b; }

public:
	const Vec3& GetLocalPos() { return m_vLocalPos; }
	const Vec3& GetLocalScale() { return m_vLocalScale; }
	const Vec3& GetLocalAngle() { return m_vLocalRotate; }
	const Vec3& GetLocalDir(DIR_TYPE _eType) { return m_vLocalDir[(UINT)_eType]; }
	const Vec3& GetWorldDir(DIR_TYPE _eType) { return m_vWorldDir[(UINT)_eType]; }

	Vec3 GetWolrdPos();

	const Vec3& GetParentScale() { return m_vParentScale; }
	const Vec3& GetParentPos() { return m_vParentPos; }

public:
	const Matrix& GetWolrdMat() { return m_matWorld; }
	const Matrix& GetEachWolrdMat() { return m_matEachWorld; }

public:
	virtual int update();
	virtual int finalupdate();

	void UpdateData();
	
public:
	//void MoveDir(); // 나중에 카메라로 이동할 것

 public:
	CLONE(CTransform);
	virtual void Save(FILE* _pFile);
	virtual void Load(FILE* _pFile);


public:
	CTransform();
	virtual ~CTransform();
};